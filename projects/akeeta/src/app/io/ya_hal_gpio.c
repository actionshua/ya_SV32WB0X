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
#include "ya_hal_gpio.h"

#if (GPIO_NUM > 0)
typedef struct{
	uint8_t 		pin;
	uint8_t 		pindiretion;
	uint8_t 		mode;
}ya_gpio_para_t;

ya_gpio_para_t ya_gpio_para[GPIO_NUM] = YA_GPIO_PARA_INIT;

void ya_gpio_write(uint8_t index, int value)
{
	if(GPIO_NUM == 0 || index > GPIO_NUM)
	{
		return;
	}
	drv_gpio_set_logic (ya_gpio_para[index].pin, (uint8_t)value);
}

int ya_gpio_read(uint8_t index)
{
	uint8_t pin_value = 0;

	if(GPIO_NUM == 0 || index > GPIO_NUM)
	{
		return -1;
	}

	pin_value = drv_gpio_get_logic(ya_gpio_para[index].pin);
	return pin_value;
}

void ya_gpio_init(void)
{
	uint8_t index = 0;

	for(index = 0; index < GPIO_NUM; index++)
	{
		drv_gpio_set_mode(ya_gpio_para[index].pin, PIN_MODE_GPIO);
		if (ya_gpio_para[index].pindiretion == 0)
		{
			drv_gpio_set_dir(ya_gpio_para[index].pin, GPIO_DIR_IN);
			hal_gpio_set_pull(ya_gpio_para[index].pin, ya_gpio_para[index].mode);
		}
		else
		{
			drv_gpio_set_dir(ya_gpio_para[index].pin, GPIO_DIR_OUT);
		}
	}
}
#endif

