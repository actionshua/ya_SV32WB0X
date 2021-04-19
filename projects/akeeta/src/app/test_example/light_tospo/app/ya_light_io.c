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
#include "ya_light_io.h"
#include "ya_light_example.h"
#include "ya_flash.h"
#include "ya_mode_api.h"

extern void ya_clear_user_data(void);
void ya_light_read_power_on_flag(void)
{
	uint8_t buf[10];
	int32_t ret = -1;
	uint16_t flash_read_len = 0;

	memset(buf, 0, 10);
	flash_read_len = 10;
	ret = ya_read_flash_with_var_len(YA_LIGHT_FLASH_PARA_ADDR, buf, &flash_read_len, 1, FLASH_AES_DISABLE);

	if (ret != 0)
		memset(buf, 0, 10);

	buf[0]++;

	ya_printf(C_LOG_INFO,"power flag: %d\r\n", buf[0]); 	

	if (buf[0] >= 5)
	{
		ya_clear_user_data();
		ya_set_toggle_mode(1);
		buf[0] = 0;
	}
		
	ret = ya_write_flash(YA_LIGHT_FLASH_PARA_ADDR, buf, 10, 1, FLASH_AES_DISABLE);
}

void ya_light_clear_power_on_flag(void)
{
	int32_t ret = -1;
	uint8_t buf[10];

	memset(buf, 0, 10);
	ret = ya_write_flash(YA_LIGHT_FLASH_PARA_ADDR, buf, 10,1, FLASH_AES_DISABLE);

	if(ret == 0)
		ya_printf(C_LOG_INFO,"ya_light_clear_power_on_flag ok\r\n");		
}

static void ya_clear_power_on_flag_callback( TimerHandle_t xTimer )
{
	ya_light_clear_power_on_flag();
}

void ya_init_light_io(void)
{
	TimerHandle_t xTimer;
	xTimer = xTimerCreate("power_on_clear_flag", ya_hal_os_msec_to_ticks(5000), pdFALSE, (void * )0, ya_clear_power_on_flag_callback);
	if( xTimer != NULL )
	{
		xTimerStart(xTimer, 0);
	}

	ya_light_read_power_on_flag();	
}

