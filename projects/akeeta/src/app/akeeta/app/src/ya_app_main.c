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
#include "ya_config.h"
#include "smnt_pub.h"
#include "ya_sniffer_broadcast.h"
#include "ya_softap_update.h"
#include "ya_flash.h"

#include "ya_ota.h"
#include "ya_uart_app.h"
#include "ya_hardware_app.h"
#include "ya_aliyun_cloud.h"
#include "ya_atcmd.h"
#include "ya_common_func.h"
#include "ya_ble_app.h"
#include "ya_api_thing_uer_define.h"
#include "ya_log_update.h"

#define TEST_WIFI_1_SSID 	"akeeta_mdev_test1"
#define TEST_WIFI_2_SSID 	"akeeta_mdev_test2"

#define TEST_URL_LEN   400

typedef enum
{
	YA_SNIFFER_SUCCESS	   		= 0x00,
	YA_SNIFFER_FAIL,

	YA_AP_CONFIG_FAIL,
	YA_AP_CONFIG_SUCCESS,

	YA_BLE_CONFIG_SUCCESS,
	YA_BLE_CONFIG_FAIL,

	YA_CONNECT_SUCCESS,
	YA_CONNECT_FAIL,

	YA_LINK_LOST,
	YA_CHANGE_TOGGLE_MODE,
	YA_CHANGE_AP_MODE,
	YA_CHANGE_SNIFFER_MODE,
	YA_CHANGE_BLE_MODE,

	YA_CHANGE_IDLE_NEXT_REBOOT,
	YA_SET_SCAN_RSSI,
	YA_SET_OTA_TEST,
	YA_FACTORY_MODE,
}ya_app_main_queue_type_t;

typedef struct{
	uint8_t mode;
	uint8_t ssid[33];
	uint8_t ssid_len;
	uint8_t pwd[65];
	uint8_t pwd_len;
	uint8_t bssid[6];
	uint8_t cloud_select;
	uint8_t server_ip_len;
	uint8_t server_ip[6];
	uint8_t factory_get_rssi_flag;
	uint8_t factory_get_rssi_name[33];
	uint8_t wlan_token[16];
	uint8_t reser1;
	uint8_t reser2;
	uint8_t reser3;
	uint8_t reboot_check_license_mode_tick;
	char 	ota_test_url[TEST_URL_LEN];
	uint32_t ota_test_all_num;
	uint32_t ota_test_success_num;
}ya_user_data_t;

typedef enum{
	INIT_MODE = 0,
	SNIFFER_SUCCESS,
	START_BROADCAST,
	BROADCAST_WAIT,
}ya_sniffer_broadcast_state;

ya_hal_os_thread_t ya_app_main_thread = NULL;
ya_hal_os_queue_t ya_main_msg_queue = NULL;

ya_user_data_t ya_user_data;
uint8_t ya_timer_watchdog_flag = 0;
uint8_t sniffer_ap_mode = 0;
uint8_t ble_ap_mode = 0;
uint8_t debine_enable = 1;
uint8_t support_cloud = 1;
ya_app_status_t ya_app_state = 0;
char config_random_num[32+1] = {0};
ya_app_main_para_t ya_app_main_para_obj;

static uint32_t ya_wifiCloud = 0;

ya_thing_handle_router_status ya_thing_handle_router = ya_thing_handle_router_status_callback;
void ya_callback_servertimer_set(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t week)
{
	if(ya_app_main_para_obj.server_timer_callback)
		ya_app_main_para_obj.server_timer_callback(year, month, day, hour, minute, second, week);
}

void ya_printf_verion(void)
{
	ya_printf(C_LOG_INFO, "device ver: %s\r\n", ya_app_main_para_obj.cur_version);
}

void ya_get_ver_string(char* obj)
{
	strcpy(obj, ya_app_main_para_obj.cur_version);
}

void ya_get_mcu_ver_string(char* obj)
{
	strcpy(obj, ya_app_main_para_obj.mcu_version);
}

void ya_set_mcu_ver_string(char* obj)
{
	if(strlen(obj) <= MCU_MAX_VERSION_LEN)
		strcpy(ya_app_main_para_obj.mcu_version, obj);
}


bool ya_get_mcu_ota_enbale(void)
{
	return ya_app_main_para_obj.mcu_ota_enable;
}

bool ya_get_debind_enable(void)
{
	return debine_enable;
}

void ya_debind_enable(void)
{
	debine_enable = 1;
}

void ya_debind_disable(void)
{
	debine_enable = 0;
}

int ya_get_randomnum(char *num)
{
	if (config_random_num[0] == 0)
		return -1;
	else
		strcpy(num, config_random_num);

	return 0;
}

void ya_clear_randomnum(void)
{
	memset(config_random_num, 0, 33);
}

int ya_get_cloud_support(void)
{
	return support_cloud;
}

void ya_printf_mac(void)
{
	uint8_t device_mac[6];
	ya_hal_wlan_get_mac_address(device_mac);
	ya_printf(C_LOG_INFO, "device mac is: %02x:%02x:%02x:%02x:%02x:%02x\r\n", device_mac[0],device_mac[1],device_mac[2], device_mac[3],device_mac[4],device_mac[5]);
}

void ya_get_mac_addr_string(char* obj)
{
	uint8_t device_mac[6];
	ya_hal_wlan_get_mac_address(device_mac);
	snprintf(obj, 50, "%02x%02x%02x%02x%02x%02x", device_mac[0],device_mac[1],device_mac[2], device_mac[3],device_mac[4],device_mac[5]);
}

int32_t ya_save_user_data(void)
{
	int32_t ret = 0, ret1 = 0;
	ret= ya_write_flash(YA_USER_DATA_BACK_ADDR, (uint8_t *)&ya_user_data, sizeof(ya_user_data_t),1,FLASH_AES_ENABLE);
	ret1 = ya_write_flash(YA_USER_DATA_ADDR, (uint8_t *)&ya_user_data, sizeof(ya_user_data_t),1,FLASH_AES_ENABLE);

	if(ret != 0 || ret1 != 0)
	{
		ya_printf(C_LOG_ERROR, "ya_save_user_data error\r\n");
		return C_ERROR;
	}

	ya_printf(C_LOG_INFO, "save user data ok\r\n");
	return C_OK;
}

int32_t ya_read_user_data(void)
{
	int32_t ret = 0;
	uint8_t read_error = 0;
	uint16_t flash_data_read = 0;

	memset(&ya_user_data, 0, sizeof(ya_user_data_t));
	flash_data_read = sizeof(ya_user_data_t);
	ret = ya_read_flash_with_var_len(YA_USER_DATA_ADDR, (uint8_t *)&ya_user_data, &flash_data_read, 1, FLASH_AES_ENABLE);
	
	if(ret != 0)
	{
		ya_printf(C_LOG_ERROR, "ya_read_user_data main error\r\n");
		ret = ya_read_flash_with_var_len(YA_USER_DATA_BACK_ADDR, (uint8_t *)&ya_user_data, &flash_data_read, 1, FLASH_AES_ENABLE);
		if(ret != 0)
		{	
			ya_printf(C_LOG_ERROR, "ya_read_user_data backup error\r\n");
			read_error = 1;
		}else
		{
			ya_printf(C_LOG_INFO, "ya_read_user_data backup ok\r\n");
			ya_write_flash(YA_USER_DATA_ADDR, (uint8_t *)&ya_user_data, sizeof(ya_user_data_t),1,FLASH_AES_ENABLE);
		}
	}else
	{
		ya_printf(C_LOG_INFO, "ya_read_user_data main ok\r\n");
	}

	if (read_error == 0)
	{
		if(ya_user_data.mode == CONNECT_MODE)
		{
			if(ya_user_data.ssid_len == 0 || ya_user_data.ssid_len > 32 || ya_user_data.pwd_len > 64
				|| ya_user_data.ssid[0] == 0)

			{
				read_error =  1;
			}
		}
	}

	if(read_error)
	{
		ya_printf(C_LOG_INFO, "read error, then init\r\n");
		ya_updata_log_string("flash data error");
		memset(&ya_user_data, 0, sizeof(ya_user_data_t));
		ya_user_data.mode = ya_app_main_para_obj.ya_init_mode;
		ya_save_user_data();
	}

	return 0;
}
int32_t ya_set_enter_ota_test_mode(char *ota_test_url)
{

	int32_t ret = -1;
	msg_t msg;
	uint8_t *pbuf = NULL;
	memset(&msg, 0, sizeof(msg_t));
	msg.type = YA_SET_OTA_TEST;
	pbuf = ya_hal_os_memory_alloc(strlen(ota_test_url) + 1);
	memset(pbuf, 0, strlen(ota_test_url) + 1);
	strcpy((char *)pbuf, ota_test_url);

	msg.addr = pbuf;
	msg.len = strlen(ota_test_url) + 1;
	ret = ya_hal_os_queue_send(&ya_main_msg_queue, &msg, 100);
	
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR,"ya_set_enter_ota_test_mode error\r\n");
		return C_ERROR;
	}

	return C_OK;
}

int32_t ya_set_enter_ota_test_mode_internal(char *ota_test_url)
{
	ya_printf(C_LOG_INFO, "ota_test_url==%s\r\n",ota_test_url);
	memset(ya_user_data.ota_test_url, 0, TEST_URL_LEN);
	memcpy(ya_user_data.ota_test_url,ota_test_url,strlen(ota_test_url));
	ya_save_user_data();
	ya_printf(C_LOG_INFO, "reboot to enter ota test mode\r\n");
	ya_delay(50);
	ya_hal_sys_reboot();

	return 0;
}
int32_t ya_check_enter_ota_test_mode(void)
{
	ya_user_data.ota_test_url[TEST_URL_LEN-1] = 0;
	if(strlen(ya_user_data.ota_test_url))
		return 1;
	else
		return 0;
}
void ya_cal_ota_test_num(uint8_t ota_flag)
{
	ya_user_data.ota_test_all_num++;
	if(ota_flag == 1)
		ya_user_data.ota_test_success_num++;
	ya_printf(C_LOG_INFO, "ota test total num ===%d,success num ===%d\r\n",ya_user_data.ota_test_all_num,ya_user_data.ota_test_success_num);
	ya_save_user_data();
}
int32_t ya_set_exit_ota_test_mode(void)
{
	ya_read_user_data();
	if(strlen(ya_user_data.ota_test_url))
	{
		memset(ya_user_data.ota_test_url, 0, TEST_URL_LEN);
		ya_user_data.ota_test_all_num = 0;
		ya_user_data.ota_test_success_num = 0;
		ya_save_user_data();
		ya_printf(C_LOG_INFO, "reboot to exit ota test mode\r\n");
		ya_delay(50);
		ya_hal_sys_reboot();
	}

	return 0;
}

char *ya_get_ota_test_mode_url(void)
{
	if(strlen(ya_user_data.ota_test_url))
		return ya_user_data.ota_test_url;
	else
		return NULL;
}

int32_t ya_get_wlan_token(uint8_t *token)
{
	uint8_t zero_token[16];
	memset(zero_token, 0, 16);
	if (memcmp(zero_token, ya_user_data.wlan_token, 16) != 0)
	{
		memcpy(token, ya_user_data.wlan_token, 16);
		return 0;
	}
	
	return -1;
}

int32_t ya_set_factory_rssi_info(char *rssi_name)
{

	int32_t ret = -1;
	msg_t msg;
	uint8_t *pbuf = NULL;
	memset(&msg, 0, sizeof(msg_t));
	msg.type = YA_SET_SCAN_RSSI;
	pbuf = ya_hal_os_memory_alloc(strlen(rssi_name) + 1);
	memset(pbuf, 0, strlen(rssi_name) + 1);
	strcpy((char *)pbuf, rssi_name);
	msg.addr = pbuf;
	msg.len = strlen(rssi_name) + 1;
	ret = ya_hal_os_queue_send(&ya_main_msg_queue, &msg, 100);
	
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR,"ya_set_factory_rssi_info error\r\n");
		return C_ERROR;
	}

	return C_OK;
}

void ya_set_factory_rssi_info_internal(uint8_t *buf)
{
	ya_user_data.factory_get_rssi_flag = 1;
	memset(ya_user_data.factory_get_rssi_name, 0, 33);
	memcpy(ya_user_data.factory_get_rssi_name, buf, strlen((char *)buf));
	ya_save_user_data();
	ya_printf(C_AT_CMD,"\nreboot to get rssi mode!!\r\n");
	ya_delay(50);
	ya_hal_sys_reboot();
}

int32_t ya_check_cloud_support(uint8_t save_cloud_type)
{
	char *product_key = NULL, *client_id = NULL;
	uint8_t cloud_type;

	cloud_type = save_cloud_type - 1;
	if (cloud_type >= WIFI_MAX)
	{
		ya_printf(C_LOG_ERROR, "save_cloud_type error\r\n");
		return -1;
	}
	
	if ((ya_app_main_para_obj.cloud_type == AKEETA_CN && cloud_type != WIFI_CN) || 
			(ya_app_main_para_obj.cloud_type == AKEETA_OVERSEA && cloud_type == WIFI_CN))
	{
		ya_printf(C_LOG_ERROR, "not support this cloud type\r\n");
		return -1;
	}

	ya_app_main_para_obj.cloud_type = cloud_type;

	if (cloud_type == 0)
	{
		product_key = ya_aly_get_thing_name();
		client_id = ya_aly_get_client_id();
	} else 
	{
		product_key = ya_aws_get_thing_type();
		client_id = ya_aws_get_client_id();
	}

	if (product_key == NULL || client_id == NULL) 
	{
		ya_printf(C_LOG_ERROR, "no license in it\r\n");
		return -1;
	}

	if (strlen(product_key) == 0 || strlen(client_id) == 0)
	{
		ya_printf(C_LOG_ERROR, "license error\r\n");
		return -1;
	}

	
	return 0;
}

int32_t ya_wifi_cloud_support(void)
{
	ya_wifiCloud = 0;
	
	if (ya_app_main_para_obj.cloud_type == AKEETA_CN)
	{
		if (ya_aly_get_thing_name() && ya_aly_get_client_id())
			ya_wifiCloud += (1 << WIFI_CN);
		
	} else if (ya_app_main_para_obj.cloud_type== AKEETA_OVERSEA)
	{
		if (ya_aws_get_thing_type() && ya_aws_get_client_id())
			ya_wifiCloud += AWS_DOMAIN_SUPPORT;    
	} else 
	{
		if (ya_aly_get_thing_name() && ya_aly_get_client_id())
			ya_wifiCloud += (1 << WIFI_CN);

		if (ya_aws_get_thing_type() && ya_aws_get_client_id())
			ya_wifiCloud += AWS_DOMAIN_SUPPORT;
	}
	return 0;
}

uint32_t ya_get_wifi_cloud_support(void)
{
	return ya_wifiCloud;
}

uint32_t ya_get_connect_cloud_type(void)
{
	return ya_app_main_para_obj.cloud_type;
}

void ya_start_cloud_apps(uint8_t cloud_type)
{
	int32_t ret = C_ERROR;
	if (cloud_type == WIFI_CN)
	{
		ya_aws_para_free();
	}else 
	{
		ya_aliyun_para_free();
	}
	cloud_create(cloud_type);

	ya_add_hareware_listen_event_from_cloud();
	
	ret = cloud_start(cloud_type);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "start aws cloud error\r\n");
		ya_delay(50);
		ya_hal_sys_reboot();
	}		
	ret = ya_start_ota_app();
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "ya_start_ota_app error\r\n");
		ya_delay(50);
		ya_hal_sys_reboot();
	}
	ya_printf(C_LOG_INFO, "cloud type is %d\r\n", cloud_type);
}

void ya_start_other_apps(void)
{
	int32_t ret = C_ERROR;
	
	if(ya_app_main_para_obj.enable_factory_uart == 1)
	{
		ret = ya_start_uart_app();
		if(ret != C_OK)
		{
			ya_printf(C_LOG_ERROR, "ya_start_uart_app error\r\n");
			ya_delay(50);
			ya_hal_sys_reboot();
		}	
	}

	ret = ya_start_hardware_app();
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "ya_start_hardware_app error\r\n");
		ya_delay(50);
		ya_hal_sys_reboot();
	}

	if (ya_app_state == YA_APP_TO_CONNECT && ya_app_main_para_obj.cloud_type < WIFI_MAX)
	{
		ya_start_cloud_apps(ya_app_main_para_obj.cloud_type);
	}
}


void ya_softap_callback(uint8_t errorcode, ya_ap_router_para_t *ya_para)
{
	msg_t msg;
	memset(&msg, 0, sizeof(msg_t));

	ya_printf(C_LOG_INFO,"get the softap result: %d\r\n", errorcode);

	if(errorcode == SOFTAP_CONFIG_FINISH)
	{
		if(ya_para->router_ssid == NULL || strlen(ya_para->router_ssid) == 0 
			|| strlen(ya_para->router_ssid) > 32 || strlen(ya_para->router_pwd)  > 64)
		{
			msg.type = YA_AP_CONFIG_FAIL;	
		}else
		{
			memset(&ya_user_data, 0, sizeof(ya_user_data_t));
			ya_user_data.mode = CONNECT_MODE;
			ya_user_data.ssid_len = strlen(ya_para->router_ssid);
			memcpy(ya_user_data.ssid, ya_para->router_ssid, strlen(ya_para->router_ssid));

			if(ya_para->router_pwd != NULL)
			{
				ya_user_data.pwd_len = strlen(ya_para->router_pwd);
				memcpy(ya_user_data.pwd, ya_para->router_pwd, strlen(ya_para->router_pwd));
			}

			ya_printf(C_LOG_INFO,"ssid: %s, pwd: %s\r\n", ya_user_data.ssid, ya_user_data.pwd);
			memcpy(ya_user_data.bssid, ya_para->router_bssid, 6);
			ya_printf(C_LOG_INFO,"bssid: %02x:%02x:%02x:%02x:%02x:%02x\r\n", ya_user_data.bssid[0], ya_user_data.bssid[1], ya_user_data.bssid[2], \
																			ya_user_data.bssid[3], ya_user_data.bssid[4], ya_user_data.bssid[5]);
			
			ya_user_data.cloud_select = ya_para->cloud_type + 1;
			
			memset(config_random_num, 0, 32+1);
			strcpy(config_random_num, ya_para->random);
			
			StringToHexArray(ya_user_data.wlan_token, 16, ya_para->random);
			
			ya_printf(C_LOG_INFO,"random: %s\r\n", config_random_num);

			msg.type = YA_AP_CONFIG_SUCCESS;
		}
	}else
	{
		msg.type = YA_AP_CONFIG_FAIL;	
	}
	
	ya_hal_os_queue_send(&ya_main_msg_queue, &msg, 100);	

}

void ya_app_ap_start_para_init(softap_param_st *ap_para)
{
	uint8_t device_mac[6];

	ya_hal_wlan_get_mac_address(device_mac);
	memset(ap_para, 0, sizeof(softap_param_st));
	ap_para->timeout = ya_app_main_para_obj.ap_timeout;
	snprintf(ap_para->ap_ssid,33,"ARGRACE_01%02X%02X",device_mac[4],device_mac[5]);
	ap_para->cloud_support_type = ya_app_main_para_obj.cloud_type;
	ap_para->p_softap_config_cb = ya_softap_callback;
}

void ya_ble_conf_callback(uint8_t errorcode, ya_ble_router_para_t *ya_para)
{
	msg_t msg;
	memset(&msg, 0, sizeof(msg_t));

	ya_printf(C_LOG_INFO,"get the ble result: %d\r\n", errorcode);

	if(errorcode == BLE_CONFIG_FINISH)
	{
		if(ya_para->router_ssid == NULL || strlen(ya_para->router_ssid) == 0 
			|| strlen(ya_para->router_ssid) > 32 || strlen(ya_para->router_pwd)  > 64)
		{
			msg.type = YA_BLE_CONFIG_FAIL;	

		}else
		{
			memset(&ya_user_data, 0, sizeof(ya_user_data_t));
			ya_user_data.mode = CONNECT_MODE;
			ya_user_data.ssid_len = strlen(ya_para->router_ssid);
			memcpy(ya_user_data.ssid, ya_para->router_ssid, strlen(ya_para->router_ssid));

			if(ya_para->router_pwd != NULL)
			{
				ya_user_data.pwd_len = strlen(ya_para->router_pwd);
				memcpy(ya_user_data.pwd, ya_para->router_pwd, strlen(ya_para->router_pwd));
			}

			ya_printf(C_LOG_INFO,"ssid: %s, pwd: %s\r\n", ya_user_data.ssid, ya_user_data.pwd);
			ya_printf(C_LOG_INFO,"bssid: %02x:%02x:%02x:%02x:%02x:%02x\r\n", ya_user_data.bssid[0], ya_user_data.bssid[1], ya_user_data.bssid[2], \
																			ya_user_data.bssid[3], ya_user_data.bssid[4], ya_user_data.bssid[5]);
			
			ya_user_data.cloud_select = ya_para->cloud_type + 1;
			
			memset(config_random_num, 0, 32+1);
			strcpy(config_random_num, ya_para->random);
			
			StringToHexArray(ya_user_data.wlan_token, 16, ya_para->random);
			ya_printf(C_LOG_INFO,"random: %s\r\n", config_random_num);

			msg.type = YA_BLE_CONFIG_SUCCESS;
		}
	}else
	{
		msg.type = YA_BLE_CONFIG_FAIL;	
	}

	ya_hal_os_queue_send(&ya_main_msg_queue, &msg, 100);	

}


void ya_app_ble_start_para_init(ble_conf_param_st *ble_para)
{
	uint8_t buf_zero[16] = {0};	

	memset(ble_para, 0, sizeof(ble_conf_param_st));

	memset(buf_zero, 0, 16);
	ble_para->timeout = ya_app_main_para_obj.ble_timeout;
	ble_para->p_ble_config_cb = ya_ble_conf_callback;

	if (memcmp(ble_para->ble_token, buf_zero, 16) != 0)
	{
		ble_para->ble_token_get = 1;
	}
}

void ya_smart_config_result_callback(smnt_result_t* smart_config_result)
{
	ya_printf(C_LOG_INFO,"get the sniffer result: %d\r\n", smart_config_result->smnt_result_status);

	uint8_t error = 0;
	msg_t msg;
	memset(&msg, 0, sizeof(msg_t));
	
	if(smart_config_result->smnt_result_status != smnt_result_ok )
	{
		error = 1;
	}else
	{
		if(smart_config_result->ssid_len == 0 || smart_config_result->ssid_len > 32 || smart_config_result->password_len > 64
			|| smart_config_result->ssid[0] == 0)
		{
			error = 1;
		}
	}

	if(error)
	{
		msg.type = YA_SNIFFER_FAIL;
		ya_hal_os_queue_send(&ya_main_msg_queue, &msg, 100);
	}
	else
	{
		memset(&ya_user_data, 0, sizeof(ya_user_data_t));
		ya_user_data.mode = CONNECT_MODE;
		ya_user_data.ssid_len = smart_config_result->ssid_len;
		memcpy(ya_user_data.ssid, smart_config_result->ssid, smart_config_result->ssid_len);

		ya_user_data.pwd_len = smart_config_result->password_len;
		memcpy(ya_user_data.pwd, smart_config_result->password, smart_config_result->password_len);
		memcpy(ya_user_data.bssid, smart_config_result->bssid, 6);	

		ya_user_data.cloud_select = smart_config_result->cloud_select + 1;

		memset(config_random_num, 0, 32+1);
		strcpy(config_random_num, smart_config_result->rand);
		StringToHexArray(ya_user_data.wlan_token, 16, smart_config_result->rand);
		
		msg.type = YA_SNIFFER_SUCCESS;
		ya_hal_os_queue_send(&ya_main_msg_queue, &msg, 100);
	}

	return ;
}


void ya_app_ap_start_sniffer_init(smnt_param_t *ya_smart_conf_param)
{
	ya_smart_conf_param->get_result_callback = ya_smart_config_result_callback;
	ya_smart_conf_param->timeout = ya_app_main_para_obj.sniffer_timeout;
}

int ya_app_wlan_event_callback(ya_hal_wlan_event_t event, void *data)
{
	int32_t ret = 0;
	msg_t msg;
	memset(&msg, 0, sizeof(msg_t));

	switch(event)
	{
		case YA_HAL_EVT_LINK_LOST:
		ya_printf(C_LOG_ERROR, "YA_HAL_EVT_LINK_LOST\r\n");

		msg.type = YA_LINK_LOST;
		ret = ya_hal_os_queue_send(&ya_main_msg_queue, &msg, 100);

		break;

		case YA_HAL_EVT_STA_CONNECT_SUCCESS:
		ya_printf(C_LOG_INFO, "YA_HAL_EVT_STA_CONNECT_SUCCESS\r\n");

		msg.type = YA_CONNECT_SUCCESS;
		ret = ya_hal_os_queue_send(&ya_main_msg_queue, &msg, 100);
		break;

		case YA_HAL_EVT_STA_CONNECT_FAILED:
		ya_printf(C_LOG_ERROR, "YA_HAL_EVT_STA_CONNECT_FAILED\r\n");

		msg.type = YA_CONNECT_FAIL;
		ret = ya_hal_os_queue_send(&ya_main_msg_queue, &msg, 100);

		break;

		default:
			return C_ERROR;
	}

	if(ret != 0)
		ya_printf(C_LOG_ERROR, "ya_app_wlan_event_callback queue error\r\n");

	return C_OK;
}

void ya_set_sniffer_ap_mode(void)
{
	sniffer_ap_mode = 1;
}

uint8_t ya_get_sniffer_ap_mode(void)
{
	return sniffer_ap_mode;
}

void ya_set_ble_ap_mode(void)
{
	ble_ap_mode = 1;
}

uint8_t ya_get_ble_ap_mode(void)
{
	return ble_ap_mode;
}


void ya_init_start_mode(void)
{		
#if (YA_BLE_CONFIG_ENABLE == 1)
	if(ya_get_ble_ap_mode())
	{


		if (ya_user_data.mode == BLE_CFG_MODE)
			ya_user_data.mode = AP_MODE;
		else if (ya_user_data.mode == AP_MODE)
			ya_user_data.mode = BLE_CFG_MODE;
		else
		{
			if (ya_app_main_para_obj.ya_init_mode == BLE_CFG_MODE)
				ya_user_data.mode = BLE_CFG_MODE;
			else if (ya_app_main_para_obj.ya_init_mode == AP_MODE)
				ya_user_data.mode = AP_MODE;
			else
				ya_user_data.mode = BLE_CFG_MODE;
		}
		
		ya_user_data.reser1 = 1;
		ya_save_user_data();
		ya_save_flash_log_string("num-reach");
	}
#elif (YA_SMART_CONFIG_ENABLE == 1)
	if(ya_get_sniffer_ap_mode())
	{
		if (ya_user_data.mode == SNIFFER_MODE)
			ya_user_data.mode = AP_MODE;
		else if (ya_user_data.mode == AP_MODE)
			ya_user_data.mode = SNIFFER_MODE;
		else
		{
			if (ya_app_main_para_obj.ya_init_mode == SNIFFER_MODE)
				ya_user_data.mode = SNIFFER_MODE;
			else if (ya_app_main_para_obj.ya_init_mode == AP_MODE)
				ya_user_data.mode = AP_MODE;
			else
				ya_user_data.mode = AP_MODE;
		}
		ya_save_user_data();
		ya_save_flash_log_string("num-reach");
	}
#endif

	
	switch(ya_user_data.mode)
	{
		case AP_MODE:
			ya_app_state = YA_APP_AP_START;
			break;

		case SNIFFER_MODE:
			ya_app_state = YA_APP_SNIFFER_START;
			break;		

		case CONNECT_MODE:
			ya_app_state = YA_APP_TO_CONNECT;
			break;

		case IDLE_MODE:
			ya_app_state = YA_APP_IDLE;
			break;
		case BLE_CFG_MODE:
			ya_app_state = YA_APP_BLE_CFG_START;
			break;

		default:
			ya_app_state = YA_APP_SNIFFER_START;
			break;			
	}

}


void ya_erase_all_user_data(void)
{
	ya_erase_flash(YA_USER_DATA_BACK_ADDR, sizeof(ya_user_data_t));
	ya_erase_flash(YA_USER_DATA_ADDR, sizeof(ya_user_data_t));
	ya_erase_flash(YA_OTA_DATA_ADDR, 0x1000);
	ya_erase_flash(YA_DEVICE_TIMER_ADDR, 0x1000);
	ya_clear_user_data();

	ya_printf(C_LOG_INFO, "ya_erase_all_user_data\r\n");
}

void ya_set_idle_internal(void)
{
	ya_user_data.mode = IDLE_MODE;
	ya_save_user_data();
}

void ya_set_mode_internal(uint8_t obj_mode, uint8_t flag)
{
	uint8_t mode_toggle = ya_user_data.mode;

	#if (CONFIG_OLD_ROUTER == 0)
	memset(&ya_user_data, 0, sizeof(ya_user_data_t));
	#endif

	if (flag)
	{
		if (ya_app_state == YA_APP_BLE_CFG_START || ya_app_state == YA_APP_BLE_STATE)
			mode_toggle = AP_MODE;
		else if (ya_app_state == YA_APP_AP_START || ya_app_state == YA_APP_AP_STATE)
			mode_toggle = BLE_CFG_MODE;
		else
		{
			if (ya_app_main_para_obj.ya_init_mode == BLE_CFG_MODE)
				mode_toggle = BLE_CFG_MODE;
			else if (ya_app_main_para_obj.ya_init_mode == AP_MODE)
				mode_toggle = AP_MODE;
			else
				mode_toggle = BLE_CFG_MODE;
		}
	}else
	{
		mode_toggle = obj_mode;
	}
	
	ya_user_data.mode = mode_toggle;

	//then save the user data into flash
	ya_save_user_data();
	ya_erase_flash(YA_OTA_DATA_ADDR, 0x1000);
	ya_erase_flash(YA_DEVICE_TIMER_ADDR, 0x1000);	
	ya_clear_user_data();

	ya_printf(C_LOG_INFO, "change to mode: %d\r\n", ya_user_data.mode);
	ya_delay(50);

	if (ya_app_main_para_obj.enable_debind)
	{
		if (ya_get_cloud_status())
		{
			ya_cloud_unregister();
			ya_delay(2000);
		}
	}

	ya_hal_sys_reboot();
}

int32_t ya_set_ap_mode(void)
{
	int32_t ret = -1;
	msg_t msg;
	memset(&msg, 0, sizeof(msg_t));
	msg.type = YA_CHANGE_AP_MODE;
	ret = ya_hal_os_queue_send(&ya_main_msg_queue, &msg, 100);
	
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR,"ya_set_ap_mode error\r\n");
		return C_ERROR;
	}

	return C_OK;
}

int32_t ya_set_sniffer_mode(void)
{
	int32_t ret = -1;
	msg_t msg;
	memset(&msg, 0, sizeof(msg_t));
	msg.type = YA_CHANGE_SNIFFER_MODE;
	ret = ya_hal_os_queue_send(&ya_main_msg_queue, &msg, 100);
	
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR,"ya_set_sniffer_mode error\r\n");
		return C_ERROR;
	}

	return C_OK;
}

int32_t ya_set_ble_config_mode(void)
{
	int32_t ret = -1;
	msg_t msg;
	memset(&msg, 0, sizeof(msg_t));
	msg.type = YA_CHANGE_BLE_MODE;
	ret = ya_hal_os_queue_send(&ya_main_msg_queue, &msg, 100);
	
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR,"ya_set_ble_config_mode error\r\n");
		return C_ERROR;
	}

	return C_OK;
}


int32_t ya_set_idle_next_reboot(void)
{
	int32_t ret = -1;
	msg_t msg;
	memset(&msg, 0, sizeof(msg_t));
	msg.type = YA_CHANGE_IDLE_NEXT_REBOOT;
	ret = ya_hal_os_queue_send(&ya_main_msg_queue, &msg, 100);

	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR,"ya_hardware_set_toggle_mode error\r\n");
		return C_ERROR;
	}

	return C_OK;
}

int32_t ya_set_toggle_mode(uint8_t change_with_power_on)
{
	int32_t ret = -1;

	if(change_with_power_on)
	{
		#if (YA_SMART_CONFIG_ENABLE == 1)
		ya_set_sniffer_ap_mode();
		#elif (YA_BLE_CONFIG_ENABLE == 1)
		ya_set_ble_ap_mode();
		#endif
	}
	else
	{
		msg_t msg;
		memset(&msg, 0, sizeof(msg_t));
		msg.type = YA_CHANGE_TOGGLE_MODE;
		ret = ya_hal_os_queue_send(&ya_main_msg_queue, &msg, 100);

		if(ret != C_OK)
		{
			ya_printf(C_LOG_ERROR,"ya_hardware_set_toggle_mode error\r\n");
			return C_ERROR;
		}
	}

	return C_OK;
}

void ya_reset_module_to_factory_internal(void)
{
	ya_erase_all_user_data();
	ya_delay(50);
	ya_hal_sys_reboot();
}

int32_t ya_reset_module_to_factory(void)
{
	int ret = -1;
	msg_t msg;
	memset(&msg, 0, sizeof(msg_t));
	msg.type = YA_FACTORY_MODE;
	
	ret = ya_hal_os_queue_send(&ya_main_msg_queue, &msg, 100);
	if(ret != 0)
	{
		ya_printf(C_LOG_ERROR, "ya_reset_module_to_factory queue error\r\n");
		return C_ERROR;
	}
	return C_OK;
}

ya_app_status_t ya_get_app_status(void)
{
	return ya_app_state;
}

int ya_enter_scan_specific_ssid_rssi_mode(void)
{
	static uint8_t scan_specific_ssid_flag = 0;
	int ret = -1;
	ya_obj_ssid_result_t scan_ssid[1];
	uint8_t resend_tick;
Rescan:
	memset(scan_ssid, 0, sizeof(ya_obj_ssid_result_t));
	memcpy(scan_ssid[0].scan_ssid, ya_user_data.factory_get_rssi_name,strlen((char *)ya_user_data.factory_get_rssi_name));
	ret = ya_hal_wlan_scan_obj_ssid(scan_ssid, 1);
	if (ret == 0)
	{
		if (scan_ssid[0].scan_result == 1)
		{
			uint8_t response_buf[50] = {0};
			memcpy(response_buf,"rsp:",strlen("rsp:"));
			uint32_t abs_rssi = -scan_ssid[0].rssi;
			response_buf[4] = '-';
			memcpy(response_buf+5,ya_int_to_string(abs_rssi),strlen(ya_int_to_string(abs_rssi)));
			for(resend_tick=0;resend_tick<2;resend_tick++)
			{
				ya_printf(C_AT_CMD,"\n%s\n", response_buf);
				ya_delay(100);
			}
			clear_enter_get_rssi_mode();
			return 0;
		}
		else
		{
			scan_specific_ssid_flag++;
			if(scan_specific_ssid_flag < 1)
				goto Rescan;
			else
				ya_printf(C_AT_CMD,"\nrsp:ERROR\n");
		}
	}
	scan_specific_ssid_flag = 0;
	return -1;
}


int ya_check_enter_factory_mode(void)
{
	int32_t data[4];
	int ret = -1;
	uint8_t index = 0;	
	ya_obj_ssid_result_t obj_scan_ssid[2];
	
	if(check_enter_get_rssi_mode())
		return -1;
		
	for(index = 0; index < 2; index++)
	{
		memset(&(obj_scan_ssid[index]), 0, sizeof(ya_obj_ssid_result_t));

		if (index == 0)
			strcpy(obj_scan_ssid[index].scan_ssid, TEST_WIFI_1_SSID);
		else
			strcpy(obj_scan_ssid[index].scan_ssid, TEST_WIFI_2_SSID);
	}

	ret = ya_hal_wlan_scan_obj_ssid_with_fix_channel(obj_scan_ssid, 2);

	if (ret == 0)
	{
		if (obj_scan_ssid[0].scan_result == 1 || obj_scan_ssid[1].scan_result == 1)
		{
			data[0] = obj_scan_ssid[0].scan_result;
			data[1] = obj_scan_ssid[0].rssi;
			data[2] = obj_scan_ssid[1].scan_result;
			data[3] = obj_scan_ssid[1].rssi;
		
			ya_thing_handle_router(MODULE_FACTORY_TEST, data);
			return 0;
		}
	}

	return -1;
}


void ya_config_fail_handle(void)
{
	#if CONFIG_OLD_ROUTER
	if (ya_user_data.ssid_len > 0 && ya_user_data.ssid_len <= 32 && ya_user_data.pwd_len <= 64)
	{
		ya_app_state = YA_APP_TO_CONNECT;
		ya_thing_handle_router(MODULE_CONNECT, NULL);
		
		if (ya_check_cloud_support(ya_user_data.cloud_select) == 0)
			ya_start_cloud_apps(ya_app_main_para_obj.cloud_type);

		if (ya_user_data.mode != CONNECT_MODE)
		{
			ya_user_data.mode = CONNECT_MODE;
			ya_save_user_data();
		}

	} else
	{
		ya_app_state = YA_APP_IDLE;
		ya_thing_handle_router(MODULE_IDLE, NULL);

		if (ya_user_data.mode != IDLE_MODE)
		{
			ya_user_data.mode = IDLE_MODE;
			ya_save_user_data();
		}
	}

	#else
	ya_app_state = YA_APP_IDLE;
	ya_thing_handle_router(MODULE_IDLE, NULL);
	#endif
}

void ya_clear_app_main_flag_callback( TimerHandle_t xTimer )
{
	static uint8_t flag = 0;
	if (ya_timer_watchdog_flag == 0 && flag == 0)
	{
		ya_printf(C_LOG_INFO, "sys error!!!\r\n");
		ya_save_flash_log_string("sys error!!!");
		flag = 1;
		//ya_hal_sys_reboot();
	}

	ya_timer_watchdog_flag = 0;
}

void ya_timer_watchdog()
{
	TimerHandle_t xTimer2;
	xTimer2 = xTimerCreate("power_on_clear_flag", ya_hal_os_msec_to_ticks(30000), pdTRUE, (void * )0, ya_clear_app_main_flag_callback);
	if( xTimer2 != NULL )
	{
		xTimerStart(xTimer2, 0);
	}
}

extern int32_t ya_disable_wifi_power_saving(void);

void ya_app_main(void *arg)
{
	uint8_t flash_ble_flag = 0;
	uint8_t link_connect = 0, ya_sniffer_broadcast_enable = INIT_MODE;
	int32_t ret = -1; 
	uint32_t app_main_cur_timer = 0;
	uint32_t wait_connect_router_start_timer = 0, check_memmory_timer = 0;

	uint16_t reconnect_count = 0, reconnect_timer = 3000;
	msg_t ms_msg;
		
	ya_hal_wlan_ap_connect_param_t y_sta_param;

	#if YA_SOFTAP_CONFIG_ENABLE == 1
	softap_param_st	softap_param;
	#endif

	#if YA_SMART_CONFIG_ENABLE == 1
	smnt_param_t ya_smart_conf_param;
	#endif

	#if YA_BLE_CONFIG_ENABLE == 1
	ble_conf_param_st ya_ble_conf_param;
	#endif

	ya_wifi_cloud_support();
	
	if (ya_app_state == YA_APP_TO_CONNECT)
	{
		ya_app_main_para_obj.cloud_type = ya_user_data.cloud_select - 1;
		
		if (ya_app_main_para_obj.cloud_type >= WIFI_MAX)
		{
			ya_app_main_para_obj.cloud_type = WIFI_CN;
		} 

		ya_printf(C_LOG_INFO, "connect cloud_type: %d\r\n", ya_app_main_para_obj.cloud_type);
	}

	if (ya_app_state == YA_APP_IDLE)
		ya_thing_handle_router(MODULE_IDLE, NULL);
	else if (ya_app_state == YA_APP_SNIFFER_START)
		ya_thing_handle_router(MODULE_SNIFFER, NULL);
	else if (ya_app_state == YA_APP_AP_START)
		ya_thing_handle_router(MODULE_AP, NULL);
	else if (ya_app_state == YA_APP_TO_CONNECT)
		ya_thing_handle_router(MODULE_CONNECTING, NULL);
	else if (ya_app_state == YA_APP_BLE_CFG_START)
		ya_thing_handle_router(MODULE_BLE, NULL);

	//init smart config para. Only need init one time
	#if YA_SMART_CONFIG_ENABLE == 1
	ya_app_ap_start_sniffer_init(&ya_smart_conf_param);
	#endif
	
	//init softap para. Only need init one time
	#if YA_SOFTAP_CONFIG_ENABLE == 1
	ya_app_ap_start_para_init(&softap_param);
	#endif

	#if YA_BLE_CONFIG_ENABLE == 1
	ya_app_ble_start_para_init(&ya_ble_conf_param);
	#endif

	//init wifi event callback
	ya_hal_wlan_start(ya_app_wlan_event_callback);
	if(ya_user_data.factory_get_rssi_flag == 1)
	{
		at_cmd_log_OFF();
		ya_app_main_para_obj.enable_factory_router_scan = 0;
		ya_enter_scan_specific_ssid_rssi_mode();
		ya_user_data.factory_get_rssi_flag = 0;
		memset(ya_user_data.factory_get_rssi_name,0,sizeof(ya_user_data.factory_get_rssi_name));
		ya_save_user_data();
		at_cmd_log_ON();
	}
	if(0 == ya_check_enter_ota_test_mode())
	{
		if (ya_app_main_para_obj.enable_factory_router_scan) 
		{
			ya_printf(C_LOG_INFO, "\r\n enter scanning now \r\n");
			if (ya_check_enter_factory_mode() == 0)
			{
				ya_printf(C_LOG_INFO, "\r\n === get the desired factory ssid == \r\n");
				ya_app_state = YA_APP_FACTORY_TEST;
			}
		}		
	}
	
	//init other para
	ya_start_other_apps();
	ya_printf(C_LOG_INFO, "\r\nmain state is: %d\r\n", ya_app_state);

	#if 0
	if (ya_app_main_para_obj.enable_low_power == 1)
	{
		ya_printf(C_LOG_INFO, "enable low power\r\n");
		ya_enable_wifi_power_saving();
	}
	#endif

	if(ya_app_state == YA_APP_TO_CONNECT || ya_app_main_para_obj.enable_debind == 0)
		ya_debind_disable();
	else
		ya_debind_enable();	

	ya_clear_randomnum();
	
	//enable watch-dog
	ret = ya_hal_wdt_set_timeout(4000);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "ya_hal_wdt_set_timeout error\r\n");
		ya_delay(50);
		ya_hal_sys_reboot();
	}
	
	ya_hal_wdt_start();


	while(1)
	{
		ya_timer_watchdog_flag = 1;
		app_main_cur_timer = ya_hal_os_ticks_to_msec();

		if (ya_timer_compare(check_memmory_timer, app_main_cur_timer, 5000) == C_OK)
		{
			check_memmory_timer = ya_hal_os_ticks_to_msec();			
			if (ya_get_remain_heap() < (25*1024) && flash_ble_flag == 0)
			{
				ya_save_flash_log_string("heap error!!!");
				flash_ble_flag = 1;
			}
			
			if (ya_get_remain_heap() < (6*1024))
			{
				ya_printf(C_LOG_ERROR, "ya_get_remain_heap error\r\n");
				ya_delay(50);
				ya_hal_sys_reboot();
			}
		}
	
		switch(ya_app_state)
		{
			case YA_APP_SNIFFER_START:
				#if (YA_SMART_CONFIG_ENABLE == 1)
				ya_thing_handle_router(MODULE_SNIFFER, NULL);
				ret = start_smnt(ya_smart_conf_param);
			
				if(ret != C_OK)
				{
					ya_printf(C_LOG_ERROR, "start_smnt error\r\n");
					ya_delay(50);
					ya_hal_sys_reboot();
				}
				ya_updata_log_string("sniffer");
				ya_app_state = YA_APP_SNIFFER;
				#endif

			break;

			case YA_APP_SNIFFER:
	
			break;
		
			case YA_APP_AP_START:
				#if (YA_SOFTAP_CONFIG_ENABLE == 1)
				ya_thing_handle_router(MODULE_AP, NULL);
				ya_updata_log_string("ap");
				ya_start_softap(&softap_param);
				ya_app_state = YA_APP_AP_STATE;
				#endif
			break;

			case YA_APP_AP_STATE:

			break;

			case YA_APP_BLE_CFG_START:
				#if (YA_BLE_CONFIG_ENABLE == 1)
				ya_updata_log_string("ble");
				ya_start_ble_app(&ya_ble_conf_param);
				ya_app_state = YA_APP_BLE_STATE;
				#endif
			break;
				
			case YA_APP_BLE_STATE:
				break;

			case YA_APP_TO_CONNECT:
				ya_thing_handle_router(MODULE_CONNECTING, NULL);
				ya_updata_log_string("connect ssid");
				ya_updata_log_string((char *)ya_user_data.ssid);
				
				memset(&y_sta_param, 0, sizeof(ya_hal_wlan_ap_connect_param_t));
				memcpy(y_sta_param.ssid, ya_user_data.ssid, ya_user_data.ssid_len);
				memcpy(y_sta_param.pwd, ya_user_data.pwd, ya_user_data.pwd_len);
				memcpy(y_sta_param.bssid, ya_user_data.bssid, 6);

				ya_printf(C_LOG_INFO,"ssid: %s, pwd: %s\r\n", y_sta_param.ssid, y_sta_param.pwd);
				
				ret = ya_hal_wlan_connect_ap(&y_sta_param);

				if(ret != C_OK)
				{
					ya_printf(C_LOG_ERROR, "connect ap error\r\n");
					ya_delay(50);
					ya_hal_sys_reboot();
				}
				ya_app_state = YA_APP_CONNECTING;

			break;

			case YA_APP_CONNECTING:

			break;

			case YA_APP_CONNECTED:

			break;

			case YA_APP_IDLE:

			break;

			case YA_APP_FACTORY_TEST:

			break;

			case YA_APP_WAIT_TO_CONNECT:
			if (reconnect_count > 10)
				reconnect_timer = 10000;
			else
				reconnect_timer = 3000;
				
			if (ya_timer_compare(wait_connect_router_start_timer, app_main_cur_timer, reconnect_timer) == C_OK)
			{
				reconnect_count++;
				ya_hal_set_sta_mode();
				ya_app_state = YA_APP_TO_CONNECT;
			}
			break;
		}

		memset(&ms_msg, 0, sizeof(msg_t));
		ret = ya_hal_os_queue_recv(&ya_main_msg_queue, &ms_msg, 100);

		if(ret == C_OK)
		{
			ya_printf(C_LOG_INFO, "type: %02x, %02x\r\n", ms_msg.source, ms_msg.type);
			switch(ms_msg.type)
			{
				case YA_SNIFFER_SUCCESS:
					ya_printf(C_LOG_INFO,"sniffer success\r\n");
					ya_updata_log_string("sniffer ok");
					//then save the user data into flash
					ya_save_user_data();
					ya_clear_timer_flash_into_hardware_queue();

					if (ya_check_cloud_support(ya_user_data.cloud_select) == 0)
						ya_start_cloud_apps(ya_app_main_para_obj.cloud_type);
					else
						support_cloud = 0;

					ya_hal_set_sta_mode();
					ya_app_state = YA_APP_TO_CONNECT;

					ya_sniffer_broadcast_enable = SNIFFER_SUCCESS;

				break;
				
				case YA_SNIFFER_FAIL:
					ya_printf(C_LOG_ERROR, "sniffer fail\r\n");
					ya_hal_set_sta_mode();
					ya_config_fail_handle();
				break;

				case YA_CONNECT_SUCCESS:
					ya_printf(C_LOG_INFO,"connect router success\r\n");
					reconnect_count = 0;
					ya_thing_handle_router(MODULE_CONNECT, NULL);
					
					ya_app_state = YA_APP_CONNECTED;
					link_connect = 1;
					if(ya_sniffer_broadcast_enable == SNIFFER_SUCCESS)
					{
						ya_sniffer_broadcast_enable = BROADCAST_WAIT;
						ya_printf(C_LOG_INFO,"start broadcast\r\n");
						ya_start_sniffer_broadcast();
					}
				break;

				case YA_CONNECT_FAIL:
					ya_app_state = YA_APP_WAIT_TO_CONNECT;
					ya_hal_wlan_disconnnect_wifi();
					wait_connect_router_start_timer = ya_hal_os_ticks_to_msec();
				break;

				case YA_AP_CONFIG_SUCCESS:
					ya_printf(C_LOG_INFO,"YA_AP_CONFIG_SUCCESS\r\n");
					ya_updata_log_string("ap ok");
					ya_save_user_data();
					ya_clear_timer_flash_into_hardware_queue();
					ya_hal_wlan_stop_ap();

					if (ya_check_cloud_support(ya_user_data.cloud_select) == 0)
						ya_start_cloud_apps(ya_app_main_para_obj.cloud_type);
					else
						support_cloud = 0;

					ya_hal_set_sta_mode();
					ya_app_state = YA_APP_TO_CONNECT;
				break;

				case YA_AP_CONFIG_FAIL:
					ya_printf(C_LOG_INFO,"connect fail\r\n");
					ya_hal_wlan_stop_ap();
					ya_hal_set_sta_mode();
					ya_config_fail_handle();
				break;

				case YA_BLE_CONFIG_SUCCESS:
					ya_printf(C_LOG_INFO,"YA_BLE_CONFIG_SUCCESS\r\n");
					ya_updata_log_string("ble ok");
					ya_save_user_data();
					ya_clear_timer_flash_into_hardware_queue();

					if (ya_check_cloud_support(ya_user_data.cloud_select) == 0)
						ya_start_cloud_apps(ya_app_main_para_obj.cloud_type);
					else
						support_cloud = 0;

					ya_hal_set_sta_mode();
					ya_app_state = YA_APP_TO_CONNECT;
				break;
				
				case YA_BLE_CONFIG_FAIL:
					ya_config_fail_handle();
				break;

				case YA_CHANGE_TOGGLE_MODE:
					ya_set_mode_internal(0, 1);
				break;

				case YA_CHANGE_AP_MODE:
					ya_set_mode_internal(AP_MODE, 0);
				break;

				case YA_CHANGE_SNIFFER_MODE:
					ya_set_mode_internal(SNIFFER_MODE, 0);
				break;

				case YA_CHANGE_BLE_MODE:
					ya_set_mode_internal(BLE_CFG_MODE, 0);
				break;

				case YA_FACTORY_MODE:
					ya_reset_module_to_factory_internal();
				break;

				case YA_CHANGE_IDLE_NEXT_REBOOT:
					ya_set_idle_internal();
				break;

				case YA_LINK_LOST:
				if(link_connect)
				{
					ya_app_state = YA_APP_TO_CONNECT;
					link_connect = 0;
				}
				break;

				case YA_SET_SCAN_RSSI:
					ya_set_factory_rssi_info_internal(ms_msg.addr);
				break;

				case YA_SET_OTA_TEST:
					ya_set_enter_ota_test_mode_internal((char *)ms_msg.addr);
				break;

				default:
					break;
			}

			if(ms_msg.addr)
				ya_hal_os_memory_free(ms_msg.addr);
		}
		
		ya_hal_wdt_feed();
	}
}

void ya_start_app_main(ya_app_main_para_t *ya_app_main_para)
{
	int32_t ret = 0;

	ya_update_log_init();
	ya_timer_watchdog();

	memset(&ya_app_main_para_obj, 0, sizeof(ya_app_main_para_t));
	memcpy(&ya_app_main_para_obj, ya_app_main_para, sizeof(ya_app_main_para_t));

	//printf system para
	ya_printf_verion();
	ya_printf_mac();

	ya_printf(C_LOG_INFO, "\r\n========sdk version: %s========\r\n", WIF_SDK_VERSION);

	ya_read_user_data();
	ya_init_start_mode();
	
	ya_printf(C_LOG_INFO, "=========user cloud: %d=========\r\n", ya_user_data.cloud_select);

#if (CLOUD_SUPPORT == US_CN_CLOUD_SUPPORT)
	ya_read_license_from_flash(2); 
#elif (CLOUD_SUPPORT == US_CLOUD_SUPPORT)
	ya_read_license_from_flash(1);
#else
	ya_read_license_from_flash(0);
#endif

	ret = ya_hal_os_queue_create(&ya_main_msg_queue, "ya_aws main msg queue", sizeof(msg_t), MSG_QUEUE_LENGTH);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create os queue error\r\n");
		return;
	}

	ret = ya_hal_os_thread_create(&ya_app_main_thread, "ya_app_main_thread", ya_app_main, 0, (2*1024), 5);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create ya_app_main error\r\n");
		return;
	}
		
	return;
}


