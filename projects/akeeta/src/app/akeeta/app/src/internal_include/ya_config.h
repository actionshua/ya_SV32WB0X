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

#ifndef _YA_CONFIG_H_
#define _YA_CONFIG_H_

typedef enum
{
	WIRELESS_SWITCH = 0,
	GATEWAY,
	LIGHT,
	WIRE_SWITCH,
	STRILIGHTS,
	SOCKET,
}YA_PRODUCT_LIST_t;


#define US_CLOUD_SUPPORT   		 0
#define CN_CLOUD_SUPPORT   		 1
#define US_CN_CLOUD_SUPPORT      2      

#define CLOUD_SUPPORT			US_CN_CLOUD_SUPPORT

//==============================chips choose==============================================
#define	 YA_8710_BX	   		0
#define  YA_8710_CX		 	1
#define  YA_6260_S1			2
#define  YA_7231U			3
#define  YA_LN8825			4
#define  YA_BL602			5
#define  YA_SV6x66			6

#define YA_CHIP   			6

//2M flash
//bootloader          	0~0xFFFF     			64K
//FOTA data          	0x10000~0x10FFF    		4K
//RF config          	0x11000~0x11FFF     	4K
//MAC config          	0x12000~0x12FFF     	4K
//PAD config          	0x13000~0x13FFF     	4K
//Boot Info          	0x14000~0x14FFF     	4K
//RAW User         		0x15000~0x24FFF     	64K
//Main Partition        0x25000~0xFBFFF     	860K
//FileSystem          	0xFC000~0x200000     	1040K

#if (YA_CHIP == YA_SV6x66)
#define YA_USER_DATA_ADDR									(0x15000)   //RAW User
#define YA_USER_DATA_BACK_ADDR 								(YA_USER_DATA_ADDR + 0x1000)
#define YA_LICENSE_DEVICE_ADDR								(YA_USER_DATA_BACK_ADDR + 0x1000)
#define YA_OTA_DATA_ADDR 									(YA_LICENSE_DEVICE_ADDR + 0x3000)
#define YA_DEVICE_TIMER_ADDR								(YA_OTA_DATA_ADDR + 0x1000)   //size 8K
#endif

#define 	WIF_SDK_VERSION			"akeeta.sdk.300"
typedef enum{
	WIFI_CN = 0,
	WIFI_US,
	WIFI_EU,

	WIFI_MAX,
}MODULE_DOMAIN;


#define YA_BLE_CONFIG_ENABLE	0
#define YA_SOFTAP_CONFIG_ENABLE	1
#define YA_SMART_CONFIG_ENABLE  0


#define AWS_DOMAIN_SUPPORT					((1<<WIFI_US) + (1<<WIFI_EU))

#define AWS_IOT_MQTT_HOST_US              "a1q3ywz7wfeo4i-ats.iot.us-west-2.amazonaws.com" ///< Customer specific MQTT HOST. The same will be used for Thing Shadow
#define AWS_IOT_MQTT_HOST_EU			  "a1q3ywz7wfeo4i-ats.iot.eu-central-1.amazonaws.com"

#define AWS_IOT_MQTT_PORT              443  ///< default port for MQTT/S


#include "ya_app_main.h"
#include "cloud.h"
#include "ya_mode_api.h"
#include "ya_cert_flash_api.h"
#include "ya_api_thing_uer_define.h"

extern bool ya_get_debind_enable(void);

extern void ya_debind_enable(void);

extern void ya_debind_disable(void);

extern int ya_get_randomnum(char *num);

extern void ya_clear_randomnum(void);

extern void ya_get_ver_string(char* obj);

extern void ya_get_mcu_ver_string(char* obj);

extern void ya_set_mcu_ver_string(char* obj);

extern bool ya_get_mcu_ota_enbale(void);

extern int ya_get_cloud_support(void);

/**
 * @brief This function is used to get the mac string.
 * @param obj is the mac string.
 * @return 0: sucess, -1: failed
 */
extern void ya_get_mac_addr_string(char* obj);


extern void ya_callback_servertimer_set(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t week);

extern uint32_t ya_get_wifi_cloud_support(void);

#endif

