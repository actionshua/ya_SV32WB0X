
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

#ifndef __YA_BLE_APP_H__
#define __YA_BLE_APP_H__


#define BLE_NET_CONFIG_VERSION 	1

//#define BLE_APP_DEBUG 	1

typedef enum
{
	BLE_MSG_CMD = 0,
	BLE_MSG_CONNECT,
	BLE_MSG_DISCONNECT,
	BLE_MSG_CLOSE,
}ya_ble_msg_type_t;

typedef enum
{
	YA_BLE_FRAME_HEADER_POS 	= 0,
	YA_BLE_FRAME_CMD_POS,
	YA_BLE_FRAME_SN_POS,
	YA_BLE_FRAME_DATA_POS,
}ya_ble_frame_pos_t;

typedef enum
{
	YA_BLE_RANDOM_CMD 		= 0x00,
	YA_BLE_GET_TOKEN_CMD,
	YA_BLE_NET_CONFIG_CMD,
}ya_ble_cmd_t;
	
typedef enum
{
	BLE_CONFIG_FINISH = 0,
	BLE_TIME_OUT,
	BLE_ERROR,
}ya_ble_state_t;
	
typedef struct 
{
	char router_ssid[32+1];
	char router_pwd[64+1];
	char random[32+1];
	uint8_t cloud_type;
	uint8_t code;
} ya_ble_router_para_t;

typedef struct 
{
	int timeout;						
	uint8_t cloud_support_type;
	uint8_t ble_token_get;
	uint8_t ble_token[16];
	void (*p_ble_config_cb)(uint8_t code, ya_ble_router_para_t *ya_ap_router_para);  
} ble_conf_param_st; 


extern int32_t ya_start_ble_app(ble_conf_param_st *ble_param);

extern void ya_stop_ble_app(void);

#endif

