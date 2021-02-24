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


#include "ya_common.h"
#include "ya_hal_button.h"

#define DEBUNCE_NUM   3

#if (BUTTON_NUM > 0)

typedef struct
{
	uint8_t 		pin;
	uint8_t 		pindiretion;
	uint8_t 		mode;
	int 			push_value;
	uint32_t   		overtime;
	void (*ya_button_push_time_handler)(uint32_t button_push_ms);
}ya_button_para_t;

ya_button_para_t ya_button_para[BUTTON_NUM] = YA_BUTTON_PARA_INIT;

typedef struct
{
	uint8_t  cur_value;
	uint32_t trigger_num;
}ya_button_handle_para_t;

ya_button_handle_para_t ya_button_interupt_para[BUTTON_NUM] = {{0},{0},{0}};

void ya_set_button_callback(uint8_t index, ya_button_push_time_func ya_button_push_time_callback, uint32_t overtime)
{
	if(BUTTON_NUM == 0 || index > BUTTON_NUM)
	{
		return;
	}

	ya_button_para[index].ya_button_push_time_handler = ya_button_push_time_callback;
	ya_button_para[index].overtime = overtime;
}

void ya_button_listen(void *arg)
{
	uint8_t index = 0;

	while(1)
	{
		for(index = 0; index < BUTTON_NUM; index++)
		{
			ya_button_interupt_para[index].cur_value = drv_gpio_get_logic(ya_button_para[index].pin);

			if((ya_button_interupt_para[index].cur_value) != ya_button_para[index].push_value)
			{
				if(ya_button_interupt_para[index].trigger_num > DEBUNCE_NUM)
				{
					if(ya_button_para[index].ya_button_push_time_handler)
						ya_button_para[index].ya_button_push_time_handler(ya_button_interupt_para[index].trigger_num*10);
				}
				ya_button_interupt_para[index].trigger_num = 0;
			}
			else
			{
				ya_button_interupt_para[index].trigger_num++;

				if ((ya_button_interupt_para[index].trigger_num*10) >= ya_button_para[index].overtime && ya_button_para[index].overtime != 0)
				{
					if(ya_button_para[index].ya_button_push_time_handler)
						ya_button_para[index].ya_button_push_time_handler(ya_button_interupt_para[index].trigger_num*10);

					ya_button_interupt_para[index].trigger_num = 0;
				}
			}	
		}
		ya_delay(10);
	}
}


int ya_button_init(void)
{
	uint8_t index = 0;

	for(index = 0; index < BUTTON_NUM; index++)
	{
		drv_gpio_set_mode(ya_button_para[index].pin, PIN_MODE_GPIO);
		if (ya_button_para[index].pindiretion == 0)
		{
			drv_gpio_set_dir(ya_button_para[index].pin, GPIO_DIR_IN);
			hal_gpio_set_pull(ya_button_para[index].pin, ya_button_para[index].mode);//1 pull-up
		}
		else
		{
			drv_gpio_set_dir(ya_button_para[index].pin, GPIO_DIR_OUT);
		}
	}

	if(xTaskCreate(ya_button_listen, "ya_button_listen", (512), NULL, 5, NULL) != pdPASS)
		return -1;

	return 0;
}

#endif


