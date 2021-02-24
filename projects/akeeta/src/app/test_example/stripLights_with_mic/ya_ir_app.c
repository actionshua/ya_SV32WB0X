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
#include "ya_stripLights_example.h"
#if (STRIP_LIGHT_WITH_IR == 1)

#include "ya_common.h"
#include "ya_ir_app.h"
#include "timer_api.h"

#include "gpio_api.h"
#include "gpio_irq_api.h"
#include "diag.h"
#include "us_ticker_api.h"
#include "gpio_irq_ex_api.h"
#include "ya_stripLights_app.h"

#define IR_IRQ_PIN        PA_19


gtimer_t ir_timer;
gpio_irq_t gpio_level;
int current_level = 3;

typedef struct{
	uint16_t iq_timer_count;
	uint16_t low_count;
	uint16_t hight_count;
	uint8_t  header_find;
	uint8_t  ir_num;
	uint8_t  hold_get;
	uint8_t repeat_num;
}ya_ir_t;

ya_ir_t ya_ir;
uint32_t ir_value;
uint32_t ir_value_get = 0;

void ir_level_timer_get(void)
{
	int value = 0;	
	ya_ir.iq_timer_count++;

	if (ya_ir.hold_get)
	{
		value = gpio_read(&gpio_level);

		if(value)
			ya_ir.hight_count++;
		else
			ya_ir.low_count++;

		if (ya_ir.hight_count > 1800 )
		{
			ir_value = 0;
			memset(&ya_ir, 0, sizeof(ya_ir_t));
		}
	}

	if (ya_ir.header_find == 0)
	{
		value = gpio_read(&gpio_level);
	
		if(value)
			ya_ir.hight_count++;
		else
			ya_ir.low_count++;

		if (ya_ir.low_count > 120 && ya_ir.hight_count > 60)
		{
			ya_ir.header_find = 1;
		}		
	}
}

void ir_irq_handler(uint32_t id, gpio_irq_event event)
{
    gpio_irq_disable(&gpio_level);

	if (ya_ir.hold_get)
	{
		if (ya_ir.low_count > 120 && ya_ir.hight_count > 60)
		{
			ir_value = 0;
			memset(&ya_ir, 0, sizeof(ya_ir_t));
			ya_ir.header_find = 1;

		} else if (ya_ir.low_count > 100 && ya_ir.hight_count < 60 && ya_ir.hight_count > 10)
		{
			ya_ir.repeat_num++;
		}
	}

	if (ya_ir.header_find == 1)
	{
		ya_ir.header_find = 2;
	} else if (ya_ir.header_find == 2)
	{
		if (ya_ir.hold_get == 0)
		{
			if	(ya_ir.iq_timer_count < 60)
			{
				if (ya_ir.iq_timer_count > 20 && ya_ir.iq_timer_count < 60)
				{
					ir_value |= (1<<ya_ir.ir_num);			
				}
				ya_ir.ir_num++;

				if (ya_ir.ir_num == 32)
				{
					ya_printf(C_LOG_INFO, "ir: 0x%08x\n", ir_value);
					ir_value_get = ir_value;
					
					if (ir_value == 0xfc03ef00)
					{
						ya_ir.hold_get = 1;
					}else
					{
						ya_ir.header_find = 0;
					}
					
					ir_value = 0;
					ya_ir.ir_num = 0;
				}
			} else
			{
				ir_value = 0;
				memset(&ya_ir, 0, sizeof(ya_ir_t));
			}
		}
	}

	
	ya_ir.iq_timer_count = 0;
	ya_ir.low_count = 0;
	ya_ir.hight_count = 0;

	gtimer_stop(&ir_timer);
	gtimer_start_periodical(&ir_timer, 50, (void*)ir_level_timer_get, 0);
	gpio_irq_enable(&gpio_level);
}

int32_t ya_ir_scan(uint8_t *sub_msg)
{
	uint8_t buf[4];

	if (ir_value_get)
	{
		if (ir_value_get == 0xfc03ef00)
		{
			if (ya_ir.repeat_num >= 48)
			{
				ir_value_get = 0;
				(*sub_msg) = KEYCMD_CONFIG;
				return C_OK;
				
			} else if (ya_ir.header_find != 2)
			{
				ir_value_get = 0;
				(*sub_msg) = 0x03;
				return C_OK;
			}
		} else
		{
			buf[0] = (uint8_t) (ir_value_get & 0x000000FF);
			buf[1] = (uint8_t) ((ir_value_get >> 8) & 0x000000FF);
			buf[2] = (uint8_t) ((ir_value_get >> 16) & 0x000000FF);
			buf[3] = (uint8_t) ((ir_value_get >> 24) & 0x000000FF);
			ir_value_get = 0;

			if (buf[0] == 0x00 && buf[1] == 0xef && (buf[2] + buf[3] == 0xFF))
			{
				(*sub_msg) = buf[2];
				return C_OK;
			} 
		}
	}
	return C_ERROR;
}

extern ya_hal_os_queue_t ya_striplight_queue;

#if 1
void ya_ir_task(void *arg)
{
	int32_t ret = -1;
	msg_t msg;
	uint8_t sub_msg = 0;

	while(1)
	{
		ret = ya_ir_scan(&sub_msg);
		if (ret == C_OK)
		{
			memset(&msg, 0, sizeof(msg_t));	
			if (sub_msg == KEYCMD_CONFIG)
				msg.type = CONFIG_TYPE;
			else
				msg.type = IR_TYPE;

			msg.subtype = sub_msg;
			ya_hal_os_queue_send(&ya_striplight_queue, &msg, 0);
		}
		ya_delay(10);
	}

}
#endif

#endif


void ya_ir_init(void)
{
#if (STRIP_LIGHT_WITH_IR == 1)
	int ret = -1;
	
	sys_jtag_off();

	gtimer_init(&ir_timer, TIMER3);
	gpio_irq_init(&gpio_level,IR_IRQ_PIN,ir_irq_handler,(uint32_t)(&current_level));
	gpio_irq_set(&ya_ir,IRQ_FALL,1);
	gpio_irq_enable(&gpio_level);


	ret = ya_hal_os_thread_create(NULL, "ya_ir_task", ya_ir_task, 0, 1024, 5);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create ya_ir_task error\n");
	}
#endif
}

