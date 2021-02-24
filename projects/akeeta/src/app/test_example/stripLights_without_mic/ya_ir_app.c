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
#include "ya_ir_app.h"
#include "ya_stripLights_app.h"
#include "ya_ir_app.h"

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






int32_t ya_ir_scan(uint8_t *sub_msg)
{
	uint8_t buf[4];
	uint8_t read_value;

	if (ir_value_get)
	{
		if (ir_value_get == 0xff00ef00)
		{	
			if(read_value)
			{
				ya_ir.hight_count++;
			}else
			{
				//ya_ir.hight_count = 0;
			}



			if(ya_ir.hight_count > 11 && ya_ir.repeat_num > 0 && ya_ir.repeat_num < 45)
			{
				ya_ir.header_find = 2;
				ya_printf(C_LOG_INFO,"hight_count:%d,repeat_num:%d \n",ya_ir.hight_count,ya_ir.repeat_num);
			}

			if (ya_ir.repeat_num >= 45)
			{
				ir_value_get = 0;
				(*sub_msg) = KEYCMD_CONFIG;
				ya_ir.repeat_num = 0;
				ya_ir.hight_count = 0;
				ya_ir.header_find = 0;
				ya_ir.hold_get = 0;
				return C_OK;

			} else if (ya_ir.header_find == 2)
			{
				ir_value_get = 0;
				(*sub_msg) = 0x00;
				ya_ir.repeat_num = 0;
				ya_ir.hight_count = 0;
				ya_ir.header_find = 0;
				ya_ir.hold_get = 0;
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
	uint32_t last_time;
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
			ya_printf(C_LOG_INFO, "sub_msg:%d %d,%d",msg.type , sub_msg,ya_ir.repeat_num);
			ya_hal_os_queue_send(&ya_striplight_queue, &msg, 0);
		}
		ya_delay(10);
	}

}
#endif



void ya_ir_init(void)
{
	int ret = -1;
	

#if 1
	ret = ya_hal_os_thread_create(NULL, "ya_ir_task", ya_ir_task, 0, 1024, 3);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create ya_ir_task error\n");
	}
#endif
	
}
	
	
