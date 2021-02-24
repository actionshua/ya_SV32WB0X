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

#include "ya_common.h"
#include "bl602_gpio.h"
#include "bl_gpio.h"
#include "bl_timer.h"

#include "hal_hwtimer.h"
#include "hal_gpio.h"

#include "ya_ir_app.h"
#include "ya_stripLights_app.h"
#include "ya_ir_app.h"


#define IR_IRQ_PIN     GLB_GPIO_PIN_7

typedef struct{
	uint8_t stage;
	uint8_t ir_num;
	uint8_t header_get;
	uint16_t holdnum;
}ya_ir_t;

ya_ir_t ya_ir;
uint32_t ir_value;
uint32_t ir_value_get = 0;
uint8_t set_one_time = 0;

void ir_irq_handler(void *arg)
{
	uint64_t delta_time = 0;
	static uint64_t cur_interupt_time = 0;

	delta_time = bl_timer_now_us64() - cur_interupt_time;
	cur_interupt_time  = bl_timer_now_us64();

	//printf("%d\r\n", (uint32_t)delta_time);

	if (ya_ir.header_get)
	{
		if (ya_ir.stage == 0)
		{
			if (ya_ir.ir_num < 32)
			{
				if (delta_time > 1700 && delta_time < 3000)
					ir_value |= (1<<ya_ir.ir_num);	
				else if (delta_time > 3000)
					ya_ir.header_get = 0;

				ya_ir.ir_num++;	

				if (ya_ir.ir_num == 32)
		 		{
					ya_ir.stage = 1;
					ya_ir.ir_num = 0;
					ya_ir.holdnum = 1;
					ya_printf(C_LOG_INFO, "ir: 0x%08x\r\n", ir_value);
					if (ir_value == 0xff00ef00)
						set_one_time = 0;
				
					ir_value_get = ir_value;
		 		}				
	 		} else 
	 			ya_ir.header_get = 0;	

		} else if (ya_ir.stage == 1)
		{
			if (delta_time > 90000 && delta_time < (90000 + 10000))
				ya_ir.holdnum++;
			else if (delta_time >  (90000 + 10000))
				ya_ir.header_get = 0;
		} else
			ya_ir.header_get = 0;
	}else
	{
		if (delta_time > 12000 && delta_time < 14000)
		{	
			ya_ir.header_get = 1;
		}
	}

	if (ya_ir.header_get == 0)
	{
		memset(&ya_ir, 0, sizeof(ya_ir_t));
		ir_value = 0;
	}
	bl_gpio_intmask(IR_IRQ_PIN, 0);
	
}

int32_t ya_ir_scan(uint8_t *sub_msg)
{
	uint8_t buf[4];

	if (ir_value_get)
	{
		if (ir_value_get == 0xff00ef00)
		{
			if (ya_ir.holdnum >= 46)
			{
				ir_value_get = 0;
				(*sub_msg) = KEYCMD_CONFIG;
				return C_OK;
				
			} else if (set_one_time == 0)
			{
				(*sub_msg) = 0x00;
				set_one_time = 1;
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

	
void ya_ir_init(void)
{
	int ret = -1;
	
	bl_gpio_enable_input(IR_IRQ_PIN, 1, 0);
	hal_gpio_register_handler((void *)ir_irq_handler,IR_IRQ_PIN,GPIO_INT_CONTROL_ASYNC,GPIO_INT_TRIG_NEG_PULSE,NULL);

	ret = ya_hal_os_thread_create(NULL, "ya_ir_task", ya_ir_task, 0, 1024, 5);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create ya_ir_task error\r\n");
	}
	
}

	
