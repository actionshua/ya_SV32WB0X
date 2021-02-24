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
#include "cJSON.h"
#include "ya_app_main.h"
#include "ya_thing_data_api.h"
#include "ya_mode_api.h"
#include "ya_api_thing_uer_define.h"
#include "ya_mcu_ota_api.h"
#include "ya_hal_gpio.h"
#include "ya_hal_button.h"
#include "ya_outlet_example.h"

static int32_t scan_result[4];

#define YA_STRING_ON		"1"
#define YA_STRING_OFF		"0"

uint8_t switch_state = SWITCH1_OFF;
uint8_t factory_enable = 0;
static ya_router_status_t ya_router_status = MODULE_UNKNOWN;

extern int32_t ya_report_packet_formulate(char *value);

uint8_t ya_mcu_ota_file_download_finish = 0;
int32_t mcu_ota_process = 0;

uint32_t ya_mcu_ota_download_addr(void)
{
	return 0x08180000;
}

void ya_mcu_download_finish(uint32_t ota_size, char *new_version)
{
	ya_printf(C_LOG_INFO, "ya_mcu_download_finish: %d, %s\n", ota_size, new_version);
	ya_mcu_ota_file_download_finish = 1;
	return;

}

void ya_set_led_according_switch_value(void)
{
	if(switch_state == SWITCH1_ON)
	{
		ya_gpio_write(LED1, LED1_ON);
	}else
	{
		ya_gpio_write(LED1, LED1_OFF);
	}
}

void ya_button_callback_handle(uint32_t button_push_ms)
{
	msg_t msg;

	ya_printf(C_LOG_INFO, "button time: %d\n", button_push_ms);
	memset(&msg, 0, sizeof(msg_t));

	if(button_push_ms >= (1000 * 5))
	{
		ya_set_toggle_mode(0);
	}else
	{
		if(factory_enable)
		{
			ya_printf(C_LOG_INFO, "factory switch\r\n");
			if(switch_state)
			{
				switch_state = SWITCH1_OFF;
				ya_gpio_write(SWITCH1, SWITCH1_OFF);

				ya_delay(300);

				switch_state = SWITCH1_ON;
				ya_gpio_write(SWITCH1, SWITCH1_ON);

				ya_delay(300);

				switch_state = SWITCH1_OFF;
				ya_gpio_write(SWITCH1, SWITCH1_OFF);

			}else
			{
				switch_state = SWITCH1_ON;
				ya_gpio_write(SWITCH1, SWITCH1_ON);
				
				ya_delay(300);

				switch_state = SWITCH1_OFF;
				ya_gpio_write(SWITCH1, SWITCH1_OFF);

				ya_delay(300);

				switch_state = SWITCH1_ON;
				ya_gpio_write(SWITCH1, SWITCH1_ON);
			}

		} else
		{
			if(switch_state)
			{
				switch_state = SWITCH1_OFF;
				ya_gpio_write(SWITCH1, SWITCH1_OFF);

				if(ya_router_status == MODULE_CONNECT)
					ya_report_packet_formulate(YA_STRING_OFF);
			}else
			{
				switch_state = SWITCH1_ON;
				ya_gpio_write(SWITCH1, SWITCH1_ON);

				if(ya_router_status == MODULE_CONNECT)
					ya_report_packet_formulate(YA_STRING_ON);
			}

			if(ya_router_status != MODULE_AP && ya_router_status != MODULE_SNIFFER)
			{
				ya_set_led_according_switch_value();
			}
		}
	}
}


int32_t ya_report_packet_formulate(char *value)
{
	int32_t ret = -1;
	cJSON *property = NULL;
	char *buf = NULL;
	
	property = cJSON_CreateObject();
	if(!property)
	{	
		return -1;
	}

	cJSON_AddStringToObject(property, "SwitchMultiple", value);

	buf = cJSON_PrintUnformatted(property);	
	if(buf)
	{
		ret = ya_thing_report_to_cloud((uint8_t *)buf, strlen(buf));
		if(ret != 0)
			ya_printf(C_LOG_ERROR, "ya_thing_report_to_cloud error\n");

		ya_hal_os_memory_free(buf);
	}

	if(property)
		cJSON_Delete(property);

	return 0;
}


void ya_thing_handle_downlink_data(uint8_t *buf, uint16_t len)
{
	cJSON *property = NULL, *Switch_1 = NULL;
	uint32_t value = 0;

	property = cJSON_Parse((char *)buf);
	if(!property)
		goto err;

	Switch_1 = cJSON_GetObjectItem(property, "SwitchMultiple");
	if(!Switch_1)
		goto err;

	if(Switch_1->type !=cJSON_String)
		goto err;

	value = atoi(Switch_1->valuestring);
	if(value)
	{
		ya_gpio_write(SWITCH1, SWITCH1_ON);
		ya_gpio_write(LED1, LED1_ON);
		ya_report_packet_formulate(YA_STRING_ON);
	}
	else
	{
		ya_gpio_write(SWITCH1, SWITCH1_OFF);
		ya_gpio_write(LED1, LED1_OFF);
		ya_report_packet_formulate(YA_STRING_OFF);
	}

	if(property)
		cJSON_Delete(property);

	return;
	
	err:

	if(property)
		cJSON_Delete(property);

	return;
}

static uint8_t led_state = 0;

void ya_thing_handle_cloud_status(ya_cloud_status_t ya_cloud_status)
{
	if (ya_cloud_status == YA_CLOUD_ONLINE)
	{
		if(switch_state)
		{
			ya_report_packet_formulate(YA_STRING_ON);
		}
		else
		{
			ya_report_packet_formulate(YA_STRING_OFF);
		}
	}else if (ya_cloud_status == YA_CLOUD_DEBIND)
	{
		ya_reset_module_to_factory();
	}
}

void ya_thing_handle_router_status_callback(ya_router_status_t ya_app_router_status, void *data)
{
	int32_t *p = (int32_t *)data;
	if (ya_app_router_status == MODULE_FACTORY_TEST)
	{
		scan_result[0] = p[0];
		scan_result[1] = p[1];
		scan_result[2] = p[2];
		scan_result[3] = p[3];		
		ya_printf(C_LOG_INFO, "[scan]: %d, %d, %d, %d\n", scan_result[0], scan_result[1], scan_result[2], scan_result[3]);
	}
	
	ya_router_status = ya_app_router_status;
}

void ya_handle_server_timer_callback(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t week)
{
	ya_printf(C_LOG_INFO, "[timer]: y: %d, m: %d, d: %d, h: %d, m: %d, s: %d, w: %d\n", year, month, day, hour, minute, second, week);
}

void ya_outlet_init(void)
{
	ya_gpio_init();

	//set led off
	led_state = 0;
	ya_gpio_write(LED1, LED1_OFF);

	//set switch off
	ya_gpio_write(SWITCH1, SWITCH1_OFF);
	
	ya_button_init();
	ya_set_button_callback(BUTTON1, ya_button_callback_handle, 5000);
}

void ya_outlet_factory_test(CLOUD_T cloud_type)
{
	uint32_t  time_blink = 0;
	time_blink = 200;

	if (cloud_type == AKEETA_OVERSEA)
	{
		if (ya_check_us_license_exit()==0)
			factory_enable = 1;
		
	}else if (cloud_type == AKEETA_CN)
	{
		if (ya_check_cn_license_exit()==0)
			factory_enable = 1;
	}else
	{
		if (ya_check_us_license_exit()==0 && ya_check_cn_license_exit()==0)
			factory_enable = 1;
		else
			factory_enable = 0;
	}

	while(1)
	{
		if(led_state)
		{
			led_state = 0;
			ya_gpio_write(LED1, LED1_OFF);
		}else
		{
			led_state = 1;
			ya_gpio_write(LED1, LED1_ON);
		}

		ya_delay(200);
	}

}

ya_app_main_para_t test_outlet_main_para;
static void ya_start_akeeta_sdk(void)
{
	memset(&test_outlet_main_para, 0, sizeof(ya_app_main_para_t));
	
#if (OUTLET_CLOUD == 0)
	test_outlet_main_para.cloud_type = AKEETA_CN;
#elif (OUTLET_CLOUD == 1)
	test_outlet_main_para.cloud_type = AKEETA_OVERSEA;
#else
	test_outlet_main_para.cloud_type = UNKNOWN_CLOUD_TYPE;
#endif

	test_outlet_main_para.sniffer_timeout = 300;
	test_outlet_main_para.ap_timeout = 300;
	test_outlet_main_para.ya_init_mode = BLE_CFG_MODE;
	test_outlet_main_para.mcu_ota_enable = 0;
	test_outlet_main_para.enable_factory_uart = 0;
	test_outlet_main_para.enable_factory_router_scan = 1;
	test_outlet_main_para.enable_low_power = 1;
	test_outlet_main_para.enable_debind = 1;
	strcpy(test_outlet_main_para.cur_version, TEST_WIFI_OUTLET_VERSION);
	strcpy(test_outlet_main_para.mcu_version, MCU_OUTLET_VERSION);
	test_outlet_main_para.server_timer_callback = &ya_handle_server_timer_callback;
	
	ya_start_app_main(&test_outlet_main_para);
}

void ya_outlet_task(void *arg)
{
	uint32_t  time_blink = 0;
	ya_router_status_t outlet_router_status = MODULE_UNKNOWN;
	Ya_Timer ya_hardware_timer_blink;

	ya_outlet_init();
	ya_start_akeeta_sdk();
	factory_enable = 0;

	while(1)
	{
		if( outlet_router_status != ya_router_status)
		{

			outlet_router_status = ya_router_status;

			if (outlet_router_status != MODULE_FACTORY_TEST)
			{
				if(outlet_router_status == MODULE_BLE)
				{
					time_blink = 500;
				}else if(outlet_router_status == MODULE_AP)
				{
					time_blink = 2000;
				}else if(outlet_router_status == MODULE_CONNECTING || outlet_router_status == MODULE_IDLE ||outlet_router_status == MODLUE_CONNECT)
				{
					time_blink = 0;
					ya_set_led_according_switch_value();
				}	

				if(time_blink > 0)
				{
					ya_init_timer(&ya_hardware_timer_blink);
					ya_countdown_ms(&ya_hardware_timer_blink, time_blink);
					
					led_state = 1;
					ya_gpio_write(LED1, LED1_ON);
				}
			}else
			{
				if (scan_result[0] == 1 || scan_result[2] == 1)
				{
					ya_printf(C_LOG_INFO, "go into factory test state\r\n");				
					#if (OUTLET_CLOUD == 0)
					ya_outlet_factory_test(AKEETA_CN);
					#elif (OUTLET_CLOUD == 1)
					ya_outlet_factory_test(AKEETA_OVERSEA);
					#else
					ya_outlet_factory_test(UNKNOWN_CLOUD_TYPE);
					#endif
				} 
			}
		}

		if(time_blink)
		{		
			if(ya_has_timer_expired(&ya_hardware_timer_blink) == 0)
			{
				ya_countdown_ms(&ya_hardware_timer_blink, time_blink);
				
				if(led_state)
				{
					led_state = 0;
					ya_gpio_write(LED1, LED1_OFF);
				}else
				{
					led_state = 1;
					ya_gpio_write(LED1, LED1_ON);
				}
			}	
		}
		
		if(ya_mcu_ota_file_download_finish)
		{
			if(mcu_ota_process >= 100)
			{
				ya_report_mcu_ota_result(100);
				ya_mcu_ota_file_download_finish = 0;
				mcu_ota_process = 0;
			}else
			{
				mcu_ota_process += 10; // consider the file has been download
				ya_report_mcu_ota_result(mcu_ota_process);
				ya_delay(1000);
			}
		}
		ya_delay(50);

	}	
}


void ya_outlet_example(void)
{
	int ret = -1;
	
	ret = ya_hal_os_thread_create(NULL, "ya_light_task", ya_outlet_task, 0, (1*1024), 3);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create ya_light_task error\n");
	}
}

