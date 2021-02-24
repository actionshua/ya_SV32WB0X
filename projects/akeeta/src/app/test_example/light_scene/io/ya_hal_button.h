/*
 * Copyright(c) 2018 - 2020 Yaguan Technology Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


/*
reatlek 8710cx
Note
    1, Supported GPIO pins, PA_0, PA_1, PA_2, PA_3, PA_4, PA_7, PA_8, PA_9, PA_10, PA_11, PA_12, PA_13, PA_14, PA_15, PA_16, PA_17, PA_18, PA_19, PA_20, and PA_23.
    2, Please off JTAG/SWD, when using PA_0, PA_1, PA_2, PA_3, and PA_4.
    3, Please off log UART, when using PA_15, and PA_16.
    4, PA_7, PA_8, PA_9, PA_10, PA_11 and PA_12 only available on RTL8720CF.

*/


#ifndef _YA_HAL_BUTTON_H_
#define _YA_HAL_BUTTON_H_

#include "drv_gpio.h"

#define BUTTON1_PIN          GPIO_20
#define BUTTON1_DIRECTION    0
#define BUTTON1_PULL_MODE    1

#define BUTTON2_PIN          GPIO_21
#define BUTTON2_DIRECTION    0
#define BUTTON2_PULL_MODE    1

#define BUTTON3_PIN          GPIO_22
#define BUTTON3_DIRECTION    0
#define BUTTON3_PULL_MODE    1


#define BUTTON_PUSH_VALUE		0
#define BUTTON_RELEASE_VALUE	1


#define BUTTON_NUM				3		

#define YA_BUTTON_PARA_INIT	 {{BUTTON1_PIN, BUTTON1_DIRECTION, BUTTON1_PULL_MODE,BUTTON_PUSH_VALUE, 0,NULL},\
                              {BUTTON2_PIN, BUTTON2_DIRECTION, BUTTON2_PULL_MODE,BUTTON_PUSH_VALUE, 0,NULL},\
							  {BUTTON3_PIN, BUTTON3_DIRECTION, BUTTON3_PULL_MODE,BUTTON_PUSH_VALUE, 0,NULL}}

typedef enum
{
	BUTTON_NAME_M = 0,
	BUTTON_NAME_BS = 1,
	BUTTON_NAME_ONOFF = 2,
}YA_BUTTON_NAME;

typedef void (*ya_button_push_time_func)(uint32_t button_push_ms);

#if (BUTTON_NUM > 0)

extern int ya_button_init(void);

extern void ya_set_button_callback(uint8_t index, ya_button_push_time_func ya_button_push_time_callback, uint32_t overtime);

#endif

#endif




