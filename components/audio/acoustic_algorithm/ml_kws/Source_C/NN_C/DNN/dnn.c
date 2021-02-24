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

#include "dnn.h"
#include "stdlib.h"

static int frame_len;
static int frame_shift;
static int num_mfcc_features;
static int num_frames;
static int num_out_classes;
static int in_dec_bits;

static q7_t* scratch_pad;
static q7_t* buffer1;
static q7_t* buffer2;
static q7_t* buffer3;

q15_t* vec_buffer;

static const q7_t ip1_wt[IP1_WT_DIM]=IP1_WT;
static const q7_t ip1_bias[IP1_OUT_DIM]=IP1_BIAS;
static const q7_t ip2_wt[IP2_WT_DIM]=IP2_WT;
static const q7_t ip2_bias[IP2_OUT_DIM]=IP2_BIAS;
static const q7_t ip3_wt[IP3_WT_DIM]=IP3_WT;
static const q7_t ip3_bias[IP3_OUT_DIM]=IP3_BIAS;
static const q7_t ip4_wt[IP4_WT_DIM]=IP4_WT;
static const q7_t ip4_bias[OUT_DIM]=IP4_BIAS;

int dnn_get_frame_len() {
  return frame_len;
}

int dnn_get_frame_shift() {
  return frame_shift;
}

int dnn_get_num_mfcc_features() {
  return num_mfcc_features;
}

int dnn_get_num_frames() {
  return num_frames;
}

int dnn_get_num_out_classes() {
  return num_out_classes;
}

int dnn_get_in_dec_bits() {
  return in_dec_bits;
}

void dnn_init()
{
  scratch_pad = malloc(sizeof(q7_t) * SCRATCH_BUFFER_SIZE);
  buffer1 = scratch_pad;
  buffer2 = buffer1 +IP1_OUT_DIM;
  buffer3 = buffer1;
  
  vec_buffer =(q15_t*)(buffer1+IP1_OUT_DIM+IP2_OUT_DIM);
  frame_len = FRAME_LEN;
  frame_shift = FRAME_SHIFT;
  num_mfcc_features = NUM_MFCC_COEFFS;
  num_frames = NUM_FRAMES;
  num_out_classes = OUT_DIM;
  in_dec_bits = MFCC_DEC_BITS;
}

void dnn_deinit()
{
  free(scratch_pad);
}

void dnn_run_nn(q7_t* in_data, q7_t* out_data)
{
    // Run all layers

    // IP1 
    arm_fully_connected_q7(in_data, ip1_wt, IN_DIM, IP1_OUT_DIM, 1, 7, ip1_bias, buffer1, vec_buffer);
        // RELU1
    arm_relu_q7(buffer1, IP1_OUT_DIM);

    // IP2 
    arm_fully_connected_q7(buffer1, ip2_wt, IP1_OUT_DIM, IP2_OUT_DIM, 2, 8, ip2_bias, buffer2, vec_buffer);
        // RELU2
    arm_relu_q7(buffer2, IP2_OUT_DIM);

    // IP3 
    arm_fully_connected_q7(buffer2, ip3_wt, IP2_OUT_DIM, IP3_OUT_DIM, 2, 9, ip3_bias, buffer3, vec_buffer);
        // RELU3
    arm_relu_q7(buffer3, IP3_OUT_DIM);

    // IP4 
    arm_fully_connected_q7(buffer3, ip4_wt, IP3_OUT_DIM, OUT_DIM, 0, 6, ip4_bias, out_data, vec_buffer);
}

