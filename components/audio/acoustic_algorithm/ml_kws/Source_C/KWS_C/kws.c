/*
 * Copyright (C) 2018 Arm Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Description: Keyword spotting example code using MFCC feature extraction
 * and neural network.
 */

#include <stdio.h>
#include "mfcc.h"
#include "nn.h"
#include "kws.h"
#include "dnn.h"
#include "osal.h"

int16_t* kws_audio_buffer;
q7_t *kws_output;
q7_t *kws_predictions;
q7_t *kws_averaged_output;
int kws_num_frames;
int kws_frame_len;
int kws_frame_shift;
int kws_num_out_classes;
int kws_audio_block_size;
int kws_audio_buffer_size;

#define FRAME_TAIL (kws_frame_len - kws_frame_shift)

q7_t *mfcc_buffer;
static int num_mfcc_features;

static int recording_win;
static int sliding_window_len;

#define KWS_STARTED 1
#define KWS_STANDBY 2
#define KWS_SLEEPING 3
#define KWS_STOPPED 4
static int kws_state;
static int kws_silence_count;
static int kws_silence_threshold;

#define DNN_EN

static void kws_deinit()
{
  if(mfcc_buffer)
    free(mfcc_buffer);
  if(kws_output)
    free(kws_output);
  if(kws_predictions)
    free(kws_predictions);
  if(kws_averaged_output)
    free(kws_averaged_output);
  mfcc_deinit();
}

static void kws_init()
{
#ifdef DNN_EN
  num_mfcc_features = dnn_get_num_mfcc_features();
  kws_num_frames = dnn_get_num_frames();
  kws_frame_len = dnn_get_frame_len();
  kws_frame_shift = dnn_get_frame_shift();
  int mfcc_dec_bits = dnn_get_in_dec_bits();
  kws_num_out_classes = dnn_get_num_out_classes();
#else
  num_mfcc_features = nn_get_num_mfcc_features();
  kws_num_frames = nn_get_num_frames();
  kws_frame_len = nn_get_frame_len();
  kws_frame_shift = nn_get_frame_shift();
  int mfcc_dec_bits = nn_get_in_dec_bits();
  kws_num_out_classes = nn_get_num_out_classes();
#endif

  mfcc_init(num_mfcc_features, kws_frame_len, mfcc_dec_bits);
  mfcc_buffer = malloc(sizeof(q7_t) * kws_num_frames*num_mfcc_features);
  if(!mfcc_buffer) {
    printf("[%d] %s malloc fail\n", __LINE__,  __func__);
    configASSERT(mfcc_buffer);
  }
  memset(mfcc_buffer, 0, sizeof(q7_t) * kws_num_frames*num_mfcc_features);
  kws_output = malloc(sizeof(q7_t) * kws_num_out_classes);
  if(!kws_output) {
    printf("[%d] %s malloc fail\n", __LINE__,  __func__);
    configASSERT(kws_output);
  }
  memset(kws_output, 0, sizeof(q7_t) * kws_num_out_classes);
  kws_averaged_output = malloc(sizeof(q7_t) * kws_num_out_classes);
  if(!kws_averaged_output) {
    printf("[%d] %s malloc fail\n", __LINE__,  __func__);
    configASSERT(kws_averaged_output);
  }
  memset(kws_averaged_output, 0, sizeof(q7_t) * kws_num_out_classes);
  kws_predictions = malloc(sizeof(q7_t) * sliding_window_len*kws_num_out_classes);
  if(!kws_predictions) {
    printf("[%d] %s malloc fail\n", __LINE__,  __func__);
    configASSERT(kws_predictions);
  }
  memset(kws_predictions, 0, sizeof(q7_t) * sliding_window_len*kws_num_out_classes);
  kws_audio_block_size = recording_win*kws_frame_shift;
  kws_audio_buffer_size = kws_audio_block_size + FRAME_TAIL;

  kws_state = KWS_STANDBY;
  kws_silence_count = 0;

  //consider 1s silence as inactive
  kws_silence_threshold = SAMP_FREQ / kws_frame_shift;
}

void kws_nn_init(int record_win, int sliding_win_len)
{
#ifdef DNN_EN
  dnn_init();
#else
  nn_init();
#endif
  recording_win = record_win;
  sliding_window_len = sliding_win_len;
  kws_init();
}

void kws_nn_init_with_buffer(int16_t* audio_data_buffer)
{
#ifdef DNN_EN
  dnn_init();
#else
  nn_init();
#endif
  kws_audio_buffer = audio_data_buffer;
#ifdef DNN_EN
  recording_win = dnn_get_num_frames();
#else
  recording_win = nn_get_num_frames();
#endif
  sliding_window_len = 1;
  kws_init();
}

void kws_nn_deinit()
{
  kws_deinit();
#ifdef DNN_EN
  dnn_deinit();
#else
  nn_deinit();
#endif
}

void kws_enable(int enable)
{
  if (enable && kws_state == KWS_STOPPED) {
    kws_state = KWS_STANDBY;
  } else if (!enable && kws_state != KWS_STOPPED) {
    kws_state = KWS_STOPPED;
  }
}

static void kws_extract_features_with_frames(int16_t *frames, int num_frames)
{
  q7_t *mfcc_buffer_head;
  int silence;

  if (kws_state == KWS_STOPPED)
    return;

  if (kws_state == KWS_SLEEPING) {
    //put pending features to the end of buffer
    mfcc_buffer_head = mfcc_buffer+(kws_num_frames-1)*num_mfcc_features;
  } else {
    //move old features left
    memmove(mfcc_buffer,mfcc_buffer+num_frames*num_mfcc_features,sizeof(q7_t)*(kws_num_frames-num_frames)*num_mfcc_features);
    //compute features only for the new audio
    mfcc_buffer_head = mfcc_buffer+(kws_num_frames-num_frames)*num_mfcc_features;
  }

  while (num_frames--) {
    silence = mfcc_compute(frames,mfcc_buffer_head);
    frames += kws_frame_shift;

    if (silence && kws_state != KWS_SLEEPING)
      kws_silence_count++;
    else
      kws_silence_count = 0;

    //handle sleep
    if (kws_silence_count >= kws_num_frames) {
      kws_state = KWS_SLEEPING;
      break;
    }

    //handle active
    if (kws_state != KWS_STARTED && !silence) {
      //fill the old features with unknown
      memset(mfcc_buffer,0,sizeof(q7_t)*(kws_num_frames-1)*num_mfcc_features);

      kws_state = KWS_STARTED;
      break;
    }

    //handle inactive
    if (kws_state == KWS_STARTED && kws_silence_count >= kws_silence_threshold) {
      kws_state = KWS_STANDBY;
    }

    //forward mfcc buffer
    if (kws_state != KWS_SLEEPING)
      mfcc_buffer_head += num_mfcc_features;
  }

  //handle remaining frames
  if (num_frames > 0)
    kws_extract_features_with_frames(frames, num_frames);
}

void kws_extract_features()
{
  if (!kws_audio_buffer)
    return;

  kws_extract_features_with_frames(kws_audio_buffer, recording_win);
}

void kws_classify()
{
  int i = 0;
  if (kws_state == KWS_STOPPED) {
    memset(kws_output,0,sizeof(q7_t) * kws_num_out_classes);
    kws_output[1] = 126;
    return;
  }

  if (kws_state == KWS_SLEEPING) {
    memset(kws_output,0,sizeof(q7_t) * kws_num_out_classes);
    kws_output[0] = 126;
    return;
  }

#ifdef DNN_EN
  dnn_run_nn(mfcc_buffer, kws_output);
#else
  nn_run_nn(mfcc_buffer, kws_output);
#endif
  // Softmax
  arm_softmax_q7(kws_output,kws_num_out_classes,kws_output);
}

int kws_get_top_class(char* prediction)
{
  int max_ind=0;
  int max_val=-128;
  for(int i=0;i<kws_num_out_classes;i++) {
    if(max_val<prediction[i]) {
      max_val = prediction[i];
      max_ind = i;
    }
  }
  return max_ind;
}

void kws_average_predictions()
{
  // shift the old kws_predictions left
  arm_copy_q7((q7_t *)(kws_predictions+kws_num_out_classes), (q7_t *)kws_predictions, (sliding_window_len-1)*kws_num_out_classes);

  // add new kws_predictions at the end
  arm_copy_q7((q7_t *)kws_output, (q7_t *)(kws_predictions+(sliding_window_len-1)*kws_num_out_classes), kws_num_out_classes);
  //compute averages
  int sum;
  for(int j=0;j<kws_num_out_classes;j++) {
    sum=0;
    for(int i=0;i<sliding_window_len;i++) {
      sum += kws_predictions[i*kws_num_out_classes+j];
    }
    kws_averaged_output[j] = (q7_t)(sum/sliding_window_len);
  }
}

