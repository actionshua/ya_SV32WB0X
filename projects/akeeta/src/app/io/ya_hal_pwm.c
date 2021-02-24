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

#include "FreeRTOS.h"
#include "ya_hal_pwm.h"
#include "ya_common.h"

#if (PWM_NUM > 0)

typedef struct{
	uint8_t pin;
	int pwm_channel;
	int pwm_period;
	float pwm_percent;
}ya_pwm_para_t;

ya_pwm_para_t ya_pwm_para[PWM_NUM] = YA_PWM_PARA_INIT;

void ya_hal_pwm_init(void)
{
	uint16_t index = 0;

	for(index = 0; index < PWM_NUM; index++)
	{	
		drv_pwm_init(ya_pwm_para[index].pwm_channel);
		drv_pwm_config(ya_pwm_para[index].pwm_channel,ya_pwm_para[index].pwm_period, (int)ya_pwm_para[index].pwm_percent,0);
	}
}

void ya_hal_pwm_write(uint8_t index, float percent)
{
	int _percent = (int)percent;
	if(_percent == 0)
		drv_pwm_disable(ya_pwm_para[index].pwm_channel);
	else
	{
		drv_pwm_config(ya_pwm_para[index].pwm_channel,ya_pwm_para[index].pwm_period, _percent,0);
		drv_pwm_enable(ya_pwm_para[index].pwm_channel);
	}
}

#endif

