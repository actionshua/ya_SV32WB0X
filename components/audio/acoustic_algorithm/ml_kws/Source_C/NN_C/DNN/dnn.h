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

#ifndef __DNN_H__
#define __DNN_H__

#include "nn.h"
#include "dnn_weights.h"
#include "arm_nnfunctions.h"
#include "arm_math.h"

/* Network Structure 

  10x25 input features
    |
   IP1 : Innerproduct (weights: 250x144)
    |
   IP2 : Innerproduct (weights: 144x144)
    |
   IP3 : Innerproduct (weights: 144x144)
    |
   IP4 : Innerproduct (weights: 144x12)
    |
   12 outputs

*/

#define SAMP_FREQ 16000
#define MFCC_DEC_BITS 2
#define FRAME_SHIFT_MS 40
#define FRAME_SHIFT ((int16_t)(SAMP_FREQ * 0.001 * FRAME_SHIFT_MS))
#define NUM_FRAMES 25
#define NUM_MFCC_COEFFS 10
#define MFCC_BUFFER_SIZE (NUM_FRAMES*NUM_MFCC_COEFFS)
#define FRAME_LEN_MS 40
#define FRAME_LEN ((int16_t)(SAMP_FREQ * 0.001 * FRAME_LEN_MS))

#define IN_DIM (NUM_FRAMES*NUM_MFCC_COEFFS)
#define OUT_DIM 12
#define IP1_OUT_DIM 144
#define IP2_OUT_DIM 144
#define IP3_OUT_DIM 144
#define IP1_WT_DIM (IP1_OUT_DIM*IN_DIM)
#define IP2_WT_DIM (IP2_OUT_DIM*IP1_OUT_DIM)
#define IP3_WT_DIM (IP3_OUT_DIM*IP2_OUT_DIM)
#define IP4_WT_DIM (OUT_DIM*IP3_OUT_DIM)
#define SCRATCH_BUFFER_SIZE (2*(IN_DIM+3*IP1_OUT_DIM))

int dnn_get_frame_len();
int dnn_get_frame_shift();
int dnn_get_num_mfcc_features();
int dnn_get_num_frames();
int dnn_get_num_out_classes();
int dnn_get_in_dec_bits();
void dnn_init();
void dnn_deinit();
void dnn_run_nn(q7_t* in_data, q7_t* out_data);

#endif
