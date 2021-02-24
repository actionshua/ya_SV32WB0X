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
#include "ya_hal_uart.h"
#include "ya_uart_app.h"
#include "ya_flash.h"

#define UART_RETRY_NUM						3
#define UART_RETRY_INTERVAL					1000
#define UART_MAX_FRAME_LEN					1024

#define CMD_HEADER_HIGH  					0X55
#define CMD_HEADER_LOW						0xAA

#define UART_HEADER_LEN						4	
#define UART_HEADER_WITH_LEN  				6

typedef enum{

	UART_HEADER_HIGH_POS = 0,
	UART_HEADER_LOW_POS,
	UART_VERSION_POS,
	UART_CMD_POS,
	UART_LEN_HIGH_POS,
	UART_LEN_LOW_POS,
	UART_DATA_POS,
}uart_pos_t;

ya_hal_os_thread_t ya_uart = NULL;
ya_hal_os_queue_t ya_uart_queue = NULL;


static uint8_t *cert_buffer = NULL;//modify by hua
static uint8_t *rx_buf = NULL;
static uint8_t *tx_buf = NULL;

uint8_t get_checksum(uint8_t *buf, int len)
{
	int i;
	uint32_t sum=0;

	for (i=0; i<len; i++)
	{
		sum +=buf[i];
	}
	
	return (sum%256);
}

int32_t ya_handle_uart_msg_send_to_queue(uint8_t *data, uint16_t data_len, uint8_t reply_flag)
{
	int32_t ret = -1;
	uint8_t *buf = NULL;
	msg_t ms_msg;
	
	buf = (uint8_t *)ya_hal_os_memory_alloc(data_len);
	memset( buf, 0, data_len);
	memcpy( buf, data, data_len);
	
	memset(&ms_msg, 0, sizeof(msg_t));
	ms_msg.addr = buf;
	ms_msg.len = data_len;

	if(reply_flag == 0)
		ms_msg.type = UART_WITHOUT_REPLY;
	else
		ms_msg.type = UART_WITH_REPLY;
	
	ret = ya_hal_os_queue_send(&ya_uart_queue, &ms_msg, 10);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR,"cloud queue error\n");
	
		if(ms_msg.addr)
			ya_hal_os_memory_free(ms_msg.addr);
	
		return -1;
	}
	
	return 0;
}

int32_t ya_handle_uart_body_send_to_queue(uint8_t cmd, uint8_t *data, uint16_t data_len)
{
	int32_t ret = -1;
	uint8_t *buf = NULL;
	uint16_t pos  = 0;
	
	buf = (uint8_t *)ya_hal_os_memory_alloc(data_len + UART_HEADER_WITH_LEN + 1);

	if(!buf)
		return -1;

	buf[pos++] = CMD_HEADER_HIGH;
	buf[pos++] = CMD_HEADER_LOW;
	buf[pos++] = 0x00;
	buf[pos++] = cmd;

	buf[pos++] = (uint8_t)((data_len & 0xFF00) >> 8);
	buf[pos++] = (uint8_t)(data_len & 0x00FF);

	if (data_len)
		memcpy(buf + pos, data, data_len);

	pos = pos + data_len;
	buf[pos] = get_checksum(buf, pos);
	pos++;

	ret = ya_handle_uart_msg_send_to_queue(buf, pos, UART_WITHOUT_REPLY);

	if (buf)
		ya_hal_os_memory_free(buf);

	return ret;
}

int32_t ya_response_cmd_ack(uint8_t cmd, uint8_t *data, uint16_t len)
{
	uint16_t pos = 0, reply_buf_len = 0;
	
	tx_buf[UART_HEADER_HIGH_POS] = CMD_HEADER_HIGH;
	tx_buf[UART_HEADER_LOW_POS] = CMD_HEADER_LOW;
	tx_buf[UART_VERSION_POS] = 0x00;
	tx_buf[UART_CMD_POS] = cmd;
	tx_buf[UART_LEN_HIGH_POS] = (uint8_t)((len & 0xFF00) >> 8);
	tx_buf[UART_LEN_LOW_POS] = (uint8_t)(len & 0x00FF);

	pos = pos + UART_HEADER_WITH_LEN;

	if (len || data)
		memcpy(tx_buf+pos, data, len);

	pos = pos + len;
	tx_buf[pos++] = get_checksum(tx_buf, UART_HEADER_WITH_LEN + len);
	reply_buf_len = pos;

	if(reply_buf_len)
		ya_hal_uart_write(tx_buf, reply_buf_len);

	
	return 0;
}

void ya_handle_uart_data(uint8_t *buf, uint16_t buf_len)
{
	uint8_t buf_temp[32];
	uint8_t crc = 0;
	uint16_t data_len = 0;

	#if 1
	uint16_t index = 0;
	ya_printf(C_LOG_INFO, "uart_data: ");
	for (index = 0; index < buf_len; index++)
		ya_printf(C_LOG_INFO, " %02x", buf[index]);
	ya_printf(C_LOG_INFO, "\n");
	#endif

	if (buf_len < (UART_HEADER_WITH_LEN + 1))
		return;

	data_len = ((buf[UART_LEN_HIGH_POS] & 0x00FF) << 8) + (buf[UART_LEN_LOW_POS] & 0x00FF);

	if ((data_len + 1 + UART_HEADER_WITH_LEN) > buf_len)
		return;

	crc = get_checksum(buf, buf_len - 1);
	if(crc != buf[buf_len - 1])
	{
		ya_printf(C_LOG_ERROR, "crc error, rec: %02x, cac: %02x\n", buf[buf_len - 1], crc);
		return;
	}

	memset(buf_temp, 0, 32);
	
	switch(buf[UART_CMD_POS])
	{
		case CMD_RESET_WIFI:
			ya_reset_module_to_factory();
			ya_response_cmd_ack(CMD_RESET_WIFI, NULL, 0);
			break;
				
		case CMD_RESET_WIFE_CONFIG:
			if (buf[UART_DATA_POS] == 0)
				ya_set_sniffer_mode();
			else if (buf[UART_DATA_POS] == 1)
				ya_set_ap_mode();
			else if (buf[UART_DATA_POS] == 2)
				ya_set_ble_config_mode();

			ya_response_cmd_ack(CMD_RESET_WIFE_CONFIG, NULL, 0);
			break;

		case CMD_GET_MAC:
			ya_hal_wlan_get_mac_address(buf_temp);
			ya_response_cmd_ack(CMD_GET_MAC, buf_temp, 6);
		break;

		case CMD_SET_MAC:		
			if(buf_len >= (UART_DATA_POS + 1 + 6))
			{
				if(ya_hal_wlan_set_mac_address(buf + UART_DATA_POS) != 0)
					buf_temp[0] = 0;
				else
					buf_temp[0] = 1;
			}else
			{
				buf_temp[0] = 0;
			}

			ya_response_cmd_ack(CMD_SET_MAC, buf_temp, 1);			
			break;			

		default:
			break;
	}

}


void ya_uart_app(void *param)
{
	int32_t ret = -1;	
	uint16_t msg_len = 0;
	uint8_t queue_rece_enable = 0;
	uint8_t cur_requeire_cmd  = 0;
	uint8_t count = 0;

	Ya_Timer ya_uart_resend_timer;
	msg_t msg;

	rx_buf = (uint8_t *)ya_hal_os_memory_alloc(UART_MAX_FRAME_LEN);
	if(!rx_buf)
		return;

	tx_buf = (uint8_t *)ya_hal_os_memory_alloc(UART_MAX_FRAME_LEN);
	if(!tx_buf)
		return;
	
	ret = ya_hal_uart_open();
	if(ret != 0)
		return;

	queue_rece_enable = 1;
	ya_init_timer(&ya_uart_resend_timer);

	ya_printf(C_LOG_INFO, "start ya_uart\n");
	
	while (1) 
	{
		ret = ya_hal_uart_recv(rx_buf, UART_HEADER_WITH_LEN, 20);
		
		if(ret == UART_HEADER_WITH_LEN)
		{
			//ya_printf(C_LOG_INFO, "header: %02x, %02x, %02x, %02x, %02x, %02x\n", rx_buf[0], rx_buf[1], rx_buf[2], rx_buf[3], rx_buf[4], rx_buf[5]);
			if(rx_buf[UART_HEADER_HIGH_POS] == CMD_HEADER_HIGH && rx_buf[UART_HEADER_LOW_POS] == CMD_HEADER_LOW)
			{
				msg_len = (uint16_t)(rx_buf[UART_LEN_HIGH_POS] << 8) + rx_buf[UART_LEN_LOW_POS];
				if(msg_len < UART_MAX_FRAME_LEN)
				{
					ret = ya_hal_uart_recv(rx_buf+UART_HEADER_WITH_LEN, (msg_len+1), 200);					
					if(ret == (msg_len+1))
					{
						ya_handle_uart_data(rx_buf, (UART_HEADER_WITH_LEN + msg_len + 1));
						//cmd compare
						if(queue_rece_enable)
						{
							if(rx_buf[UART_CMD_POS] == cur_requeire_cmd)
							{
								count = 0;
								queue_rece_enable = 1;
								if(msg.addr) ya_hal_os_memory_free(msg.addr);

							}
						}
					}
				}
			}			
		}

		if(queue_rece_enable)
		{
			memset(&msg, 0, sizeof(msg_t));
			ret = ya_hal_os_queue_recv(&ya_uart_queue, &msg, 0);
			if(ret == C_OK)
			{
				ya_printf(C_LOG_INFO, "[U-T]: %02x\n",msg.type);

				switch(msg.type)
				{
					case UART_WITH_REPLY:
						count = 0;
						queue_rece_enable = 0;
						ret = ya_hal_uart_write(msg.addr, msg.len);

						if(ret != msg.len)
							ya_printf(C_LOG_ERROR,"uart send error\n");
						else
							ya_countdown_ms(&ya_uart_resend_timer, UART_RETRY_INTERVAL);

						break;

					case UART_WITHOUT_REPLY:
						queue_rece_enable = 1;
						ret = ya_hal_uart_write(msg.addr, msg.len);

						if(ret != msg.len)
							ya_printf(C_LOG_ERROR,"uart send error\n");	

						if(msg.addr)
							ya_hal_os_memory_free(msg.addr);
						break;

					default:
						if(msg.addr)
							ya_hal_os_memory_free(msg.addr);
					break;
				}
			}
		}

		if(queue_rece_enable == 0)
		{
			if(ya_has_timer_expired(&ya_uart_resend_timer) == 0)
			{
				if(count < UART_RETRY_NUM)
				{
					ret = ya_hal_uart_write(msg.addr, msg.len);
					if(ret != C_OK)
						ya_printf(C_LOG_ERROR,"uart re-send error\n"); 

					count++;
				}else
				{
					count = 0;
					queue_rece_enable = 1;
				}
			}
		}
    }

	if(rx_buf)
		ya_hal_os_memory_free(rx_buf);

	rx_buf = NULL;

	if(tx_buf)
		ya_hal_os_memory_free(tx_buf);

	tx_buf = NULL;
    vTaskDelete(NULL);
}

int32_t ya_start_uart_app(void)
{
	int32_t ret = 0;

	if(ya_uart)
		return 0;

	ret = ya_hal_os_queue_create(&ya_uart_queue, "ya uart queue", sizeof(msg_t), MSG_QUEUE_LENGTH);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create os queue error\n");
		return -1;
	}

	ret = ya_hal_os_thread_create(&ya_uart, "ya_uart thread", ya_uart_app, 0, (2*1024), 5);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create ya_uart error\n");
		return -1;
	}

	return 0;
}

