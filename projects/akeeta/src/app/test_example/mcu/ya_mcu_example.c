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
#include "ya_mcu_example.h"

typedef enum{

	MCU_OK = 0,
	MCU_ERROR,
}MCU_RESULT_T;

typedef enum{

	AKEETA_HEADER_HIGH_POS = 0,
	AKEETA_HEADER_LOW_POS,
	AKEETA_VERSION_POS,
	AKEETA_CMD_POS,
	AKEETA_LEN_HIGH_POS,
	AKEETA_LEN_LOW_POS,
	AKEETA_DATA_POS,
}akeeta_uart_pos_t;


typedef enum{

	AKEETA_BLE_CONFIG = 0,
	AKEETA_AP_CONFIG,
	AKEETA_CONNECTING_ROUTER,
	AKEETA_CONNECTING_CLOUD,
	AKEETA_CONNECT_CLOUD,
	AKEETA_IDLE,
}akeeta_net_state_t;


#define AKEETA_HEADER_HIGH  					0X55
#define AKEETA_HEADER_LOW						0xAA

#define MCU_UART_HEADER_LEN						4	
#define MCU_UART_HEADER_WITH_LEN  				6

#define MCU_CMD_GET_PRODUCT_ID 					0x01
#define MCU_CMD_GET_NET_STATUS 					0X02
#define MCU_CMD_RESET_WIFI 						0x03
#define MCU_CMD_RESET_WIFI_CONFIG				0x04
#define MCU_CMD_GET_STATUS						0x05
#define MCU_CMD_GET_LOCAL_T 					0x06
#define MCU_CMD_WIFE_FUNC_TEST 					0x07
#define MCU_CMD_REPORT_STATUS 					0x08
#define MCU_CMD_SET_COMMAND 					0x09
#define MCU_CMD_GET_CURRENT_WIFI_INTENTITY 		0x0b
#define MCU_CMD_NET_STATUS_REQUEST				0x0c


#define AKEETA_HEADER_LEN						4	
#define AKEETA_HEADER_WITH_LEN  				6

extern void akeeta_update_device_state(uint8_t cmd);

uint8_t akeeta_get_checksum(uint8_t *buf, int len)
{
	int i;
	uint32_t sum=0;

	for (i=0; i<len; i++)
	{
		sum +=buf[i];
	}
	
	return (sum%256);
}

void uart_send(uint8_t *data, uint16_t len)
{
	//to do by user
}

void akeeta_cmd_send(uint8_t cmd, uint8_t *data, uint16_t len)
{
	uint16_t pos = 0, buf_len = 0;
	uint8_t tx_buf[64];

	memset(tx_buf, 0, 64);

	if (len + MCU_UART_HEADER_WITH_LEN + 1 > 64)
		return;
	
	tx_buf[AKEETA_HEADER_HIGH_POS] = AKEETA_HEADER_HIGH;
	tx_buf[AKEETA_HEADER_LOW_POS] = AKEETA_HEADER_LOW;
	tx_buf[AKEETA_VERSION_POS] = 0x00;
	tx_buf[AKEETA_CMD_POS] = cmd;
	tx_buf[AKEETA_LEN_HIGH_POS] = (uint8_t)((len & 0xFF00) >> 8);
	tx_buf[AKEETA_LEN_LOW_POS] = (uint8_t)(len & 0x00FF);

	pos = pos + AKEETA_HEADER_WITH_LEN;

	if (len || data)
		memcpy(tx_buf+pos, data, len);

	pos = pos + len;
	tx_buf[pos++] = akeeta_get_checksum(tx_buf, AKEETA_HEADER_WITH_LEN + len);
	buf_len = pos;
	
	// to do by user
	uart_send(tx_buf, buf_len);
}

void akeeta_reset_wifi(void)
{
	akeeta_cmd_send(MCU_CMD_RESET_WIFI, NULL, 0);
}

void akeeta_reset_wifi_config(void)
{
	uint8_t data[1];
	data[0] = 0x02;
	akeeta_cmd_send(MCU_CMD_RESET_WIFI_CONFIG, data, 1);
}

void akeeta_get_wifi_state(void)
{
	akeeta_cmd_send(MCU_CMD_NET_STATUS_REQUEST, NULL, 0);
}


void akeeta_response_product_id(void)
{
	uint8_t data[64];
	uint8_t pos = 0;
	
	memset(data, 0, 64);
	data[pos++] = strlen(PRODUCT_ID);
	memcpy(data + pos, PRODUCT_ID, strlen(PRODUCT_ID));
	pos += strlen(PRODUCT_ID);

	data[pos++] = strlen(VERSION);
	memcpy(data + pos, VERSION, strlen(VERSION));
	pos += strlen(VERSION);
	
	akeeta_cmd_send(MCU_CMD_GET_PRODUCT_ID, data, pos);
}

void akeeta_handle_net_state(uint8_t netstate)
{
	if (netstate == AKEETA_BLE_CONFIG)
	{
		//1. set the light 500ms blink
		
	} else 
	{
		// 1. set the light according light2pwm
		
		if (netstate == AKEETA_CONNECT_CLOUD)
			akeeta_update_device_state(MCU_CMD_REPORT_STATUS);
	}
}

typedef struct {
	uint8_t device_switch;
	uint8_t mode;
	uint8_t lightness;
	uint8_t	temp;
	uint8_t scene;
}light2pwd_device_t;

light2pwd_device_t	light2pwm_device;


void akeeta_update_device_state(uint8_t cmd)
{
	uint8_t data[32];
	uint8_t pos = 0;
	
	memset(data, 0, 32);
	data[pos++] = SWTICH_ID;
	data[pos++] = light2pwm_device.device_switch;
	data[pos++] = MODE_ID;
	data[pos++] = light2pwm_device.mode;
	data[pos++] = LIGHTESS_ID;
	data[pos++] = light2pwm_device.lightness;
	data[pos++] = TEMP_ID;
	data[pos++] = light2pwm_device.temp;
	data[pos++] = SCENE_ID;
	data[pos++] = light2pwm_device.scene;

	akeeta_cmd_send(cmd, data, pos);
}

void akeeta_control_device(uint8_t *data, uint16_t data_len)
{
	uint16_t index = 0;
	for (index = 0; index < data_len; index++)
	{	
		switch(data[index])
		{
			case SWTICH_ID:
				index++;
				if (index < data_len)
					light2pwm_device.device_switch = data[index];
				else
					return;
			break;

			case MODE_ID:
				index++;
				if (index < data_len)
					light2pwm_device.mode = data[index];
				else
					return;
			break;

			case LIGHTESS_ID:
				if (index < data_len)
					light2pwm_device.lightness = data[index]; 
				else
					return;
			break;

			case TEMP_ID:
				if (index < data_len)
					light2pwm_device.temp = data[index]; 
				else
					return;
			break;

			case SCENE_ID:
				if (index < data_len)
					light2pwm_device.scene = data[index]; 
				else
					return;
			break;

		}
	}

	//control pwm according light2pwm
}	

void akeeta_device_init(void)
{
	light2pwm_device.device_switch = 1;
	light2pwm_device.mode = 0;
	light2pwm_device.lightness = 100;
	light2pwm_device.temp = 100;
	light2pwm_device.scene = 0;

	// set the light according light2pwm 
}

void akeeta_handle_uart_rece_data(uint8_t *buf, uint16_t buf_len)
{
	uint8_t crc = 0;
	uint16_t data_len = 0;

	if (buf_len < (MCU_UART_HEADER_WITH_LEN + 1))
		return;

	data_len = ((buf[AKEETA_LEN_HIGH_POS] & 0x00FF) << 8) + (buf[AKEETA_LEN_LOW_POS] & 0x00FF);

	if ((data_len + 1 + MCU_UART_HEADER_WITH_LEN) > buf_len)
		return;

	crc = akeeta_get_checksum(buf, buf_len - 1);
	if(crc != buf[buf_len - 1])
		return;
	
	switch(buf[AKEETA_CMD_POS])
	{
		case MCU_CMD_GET_PRODUCT_ID:
			akeeta_response_product_id();
			break;

		case MCU_CMD_GET_NET_STATUS:
			akeeta_handle_net_state(buf[AKEETA_DATA_POS]);
			akeeta_cmd_send(MCU_CMD_GET_NET_STATUS, NULL, 0);		
			break;

		case MCU_CMD_GET_STATUS:
			akeeta_update_device_state(MCU_CMD_GET_STATUS);
			break;

		case MCU_CMD_SET_COMMAND:
			akeeta_control_device(buf + AKEETA_DATA_POS, data_len);
			akeeta_cmd_send(MCU_CMD_SET_COMMAND, NULL, 0);		
			break;

		default:
			break;
	}

}

