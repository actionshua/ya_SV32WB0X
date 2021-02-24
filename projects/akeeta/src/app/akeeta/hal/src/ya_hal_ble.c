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

#include <FreeRTOS.h>
#include <semphr.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <task.h>
#include <timers.h>
#include <ya_hal_os.h>
#include "ya_common.h"
#include "ya_hal_ble.h"
#include "infra_defs.h"

extern  int hci_driver_init(void);
extern int32_t ya_hal_wlan_get_mac_address(uint8_t *mac_addr);

//#define BT_UUID_WIFI_PROV   BT_UUID_DECLARE_16(0xffff)
//#define BT_UUID_WIFIPROV_WRITE    BT_UUID_DECLARE_16(0xff01)
//#define BT_UUID_WIFIPROV_READ     BT_UUID_DECLARE_16(0xff02)

//1cf0fe66-3ecf-4d6e-a9fc-e287ab124b96
#define BT_UUID_WIFI_PROV     	   NULL

//1f80af6a-2b71-4e35-94e5-00f854d8f16f
#define BT_UUID_WIFIPROV_WRITE     NULL

//1f80af6c-2b71-4e35-94e5-00f854d8f16f
#define BT_UUID_WIFIPROV_READ      NULL





static ya_ble_connected_state p_connect_state = NULL;

void ya_hal_ble_set_connect_state_cb(ya_ble_connected_state func)
{
}


void ya_hal_ble_set_rcv_cb(ble_rcv_call_back_func_t func)
{
}


int ya_hal_ble_send_bytes(uint8_t *data, uint16_t len)
{
	return -1;
}

char *ya_hal_ble_get_name(void)
{
	static char ble_name[24]={0};
	uint8_t device_mac[6]={0};
	
	memset(ble_name, 0, 24);
	ya_hal_wlan_get_mac_address(device_mac);
	device_mac[5]++;
	snprintf(ble_name, sizeof(ble_name), "ARGRACE_01%02x%02x%02x%02x%02x%02x", device_mac[0], device_mac[1], device_mac[2], device_mac[3], device_mac[4], device_mac[5]);
	return ble_name;
}

void ya_hal_ble_start_adv(uint8_t *adv_ff_string, uint8_t len)
{
	
}

void ya_hal_disconnect_ble_conn(void)
{

}

void ya_hal_stop_ble(void)
{
	
}


void ya_hal_ble_init(void)
{

}


