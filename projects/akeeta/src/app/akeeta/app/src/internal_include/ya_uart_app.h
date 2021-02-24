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
 

#ifndef __UART_CMD_H_
#define __UART_CMD_H_

typedef enum
{
	UART_WITHOUT_REPLY = 0,
	UART_WITH_REPLY,
}uart_msg_pos_t;

typedef enum
{
	UART_BLE_SET_CONFIG = 0,
	UART_BLE_INFO_REPONSE,
}ble_uart_main_event_t;

#define CMD_GET_PRODUCT_ID 					0x01
#define CMD_REPORT_NET_STATUS 				0X02
#define CMD_RESET_WIFI 						0x03
#define CMD_RESET_WIFE_CONFIG				0x04
#define CMD_GET_LOCAL_T 					0x06
#define CMD_WIFE_FUNC_TEST 					0x07
#define CMD_MCU_REPORT_STATUS 				0x08
#define CMD_SET_COMMAND 					0x09
#define CMD_GET_CURRENT_WIFI_INTENTITY 		0x0b
#define CMD_NET_STATUS_REQUEST				0x0c


#define BLE_CONFIG_WIFI_WITH_UART			0x20
#define BLE_RESET_MESH_NETWORK				0x21
#define BLE_SUBDEVCIE_GET					0x22
#define BLE_SUBDEVICE_NOTIFY				0x23
#define BLE_SUBDEVICE_STATUS				0x24
#define BLE_SUBDEVICE_GROUP_REQUEST			0x25
#define BLE_SUBDEVICE_GROUP_RESPONSE		0x26
#define BLE_SUBDEVICE_CONTROL				0x27
#define BLE_SUBDEVICE_STATE					0x28

#define BLE_UART_OTA_START					0x29
#define BLE_UART_OTA_SUBPACKET				0x2A
#define BLE_UART_OTA_CONFIRM				0x2B					

//new define cmd
#define CMD_GET_MAC							0xF0
#define CMD_SET_MAC							0xF3


extern int32_t ya_handle_uart_body_send_to_queue(uint8_t cmd, uint8_t *data, uint16_t data_len);

extern int32_t ya_handle_uart_msg_send_to_queue(uint8_t *data, uint16_t data_len, uint8_t reply_flag);

extern int32_t ya_start_uart_app(void);



#endif

