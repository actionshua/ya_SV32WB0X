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
#include "ya_hal_uart.h"
#include "ya_app_main.h"
#include "ya_thing_data_api.h"
#include "ya_mode_api.h"
#include "ya_api_thing_uer_define.h"
#include "cJSON.h"
#include "ya_mcu_ota_user_define.h"
#include "ya_user_uart_with_task_example.h"

ya_hal_os_thread_t uart_test = NULL;

ya_app_main_para_t test_uart_main_para;
uint8_t ya_mcu_ota_file_download_finish = 0;

uint32_t ya_mcu_ota_download_addr(void)
{
	return 0x08180000;
}

void ya_mcu_download_finish(uint32_t ota_size, char *new_version)
{
	ya_mcu_ota_file_download_finish = 1;
	return;
}

void ya_thing_handle_downlink_data(uint8_t *buf, uint16_t len)
{
	// do your job here
	ya_printf(C_LOG_INFO, "cloud data: %s\n", buf);
}

void ya_thing_handle_cloud_status(ya_cloud_status_t ya_cloud_status)
{
	if (ya_cloud_status == YA_CLOUD_ONLINE)
		ya_printf(C_LOG_INFO, "cloud online\n");
	else if (ya_cloud_status == YA_CLOUD_OFFLINE)
		ya_printf(C_LOG_INFO, "cloud offline\n");
	else
		ya_printf(C_LOG_INFO, "cloud debind device\n");

}

void ya_thing_handle_router_status_callback(ya_router_status_t ya_app_router_status, void *data)
{
	ya_printf(C_LOG_INFO, "router status: %d\n", ya_app_router_status);
}

int32_t ya_uart_report_packet_to_cloud_formulate(uint8_t value)
{
	int32_t ret = -1;
	cJSON *property = NULL;
	char *buf = NULL;
	
	property = cJSON_CreateObject();
	if(!property)
	{	
		return -1;
	}

	if(value)
		cJSON_AddStringToObject(property, "SwitchMultiple", "1");
	else
		cJSON_AddStringToObject(property, "SwitchMultiple", "0");

	buf = cJSON_PrintUnformatted(property);	
	if(buf)
	{
		ret = ya_thing_report_to_cloud((uint8_t *)buf, strlen(buf));
		if(ret != 0)
			ya_printf(C_LOG_ERROR, "ya_thing_report_to_cloud error\n");

		free(buf);
	}

	if(property)
		cJSON_Delete(property);

	return 0;
}


void uart_test_app(void *param)
{
	int32_t ret = -1;	
	uint8_t uart_buf[256];

	ret = ya_hal_uart_open();
	if(ret != 0)
		return;

	int32_t mcu_ota_process = 0;
	
	while (1) 
	{
		ret = ya_hal_uart_recv(uart_buf, 256, 40);
		if(ret > 0)
		{		
			ya_printf(C_LOG_INFO, "get uart len: %d\n", ret);

			//may reponse to the uart
			ya_hal_uart_write(uart_buf, ret);

			//may resonse to cloud, but need to change to json string
			ya_uart_report_packet_to_cloud_formulate(1);
		}

		if(ya_mcu_ota_file_download_finish)
		{
			mcu_ota_process = 10;
			while(1)
			{
				if(mcu_ota_process >= 100)
				{
					ya_report_mcu_ota_result(100);
					ya_mcu_ota_file_download_finish = 0;
					break;
				}
					
				ya_report_mcu_ota_result(mcu_ota_process);
				mcu_ota_process += 10;
				ya_delay(1000);
			}

		}
    }
}

int32_t uart_app_test(void)
{
	int32_t ret = 0;
	
	ret = ya_hal_os_thread_create(&uart_test, "uart_test thread", uart_test_app, 0, (2*1024), 5);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create uart_test error\n");
		return -1;
	}
		
	return 0;
}

void ya_handle_server_timer_callback(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t week)
{
	ya_printf(C_LOG_INFO, "[timer]: y: %d, m: %d, d: %d, h: %d, m: %d, s: %d, w: %d\n", year, month, day, hour, minute, second, week);
}

void ya_user_uart_with_task_example(void)
{
	memset(&test_uart_main_para, 0, sizeof(ya_app_main_para_t));

#if (UART_CLOUD == 0)
	test_uart_main_para.cloud_type = AKEETA_CN;
#elif (UART_CLOUD == 1)
	test_uart_main_para.cloud_type = AKEETA_OVERSEA;
#else
	test_uart_main_para.cloud_type = UNKNOWN_CLOUD_TYPE;
#endif

	test_uart_main_para.sniffer_timeout = 300;
	test_uart_main_para.ap_timeout = 300;
	test_uart_main_para.ya_init_mode = AP_MODE;	
	test_uart_main_para.enable_factory_uart = 0;
	strcpy(test_uart_main_para.cur_version, TEST_WIFI_UART_VERSION);
	strcpy(test_uart_main_para.mcu_version, MCU_UART_VERSION);
	test_uart_main_para.mcu_ota_enable = 1;
	test_uart_main_para.enable_low_power = 0;
	test_uart_main_para.server_timer_callback = &ya_handle_server_timer_callback;
	
	ya_start_app_main(&test_uart_main_para);
	
	// do your job here  like uart example
	uart_app_test();
}


