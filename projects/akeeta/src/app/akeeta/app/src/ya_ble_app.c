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
#include "ya_ble_app.h"
#include "ya_aes_md5.h"
#include "ya_common_func.h"

typedef enum{
	NET_CONFIG_SUCCESS = 0,
	NET_CONFIG_STATUS_ERROR,
	NET_CONFIG_ARG_ERROR,
	NET_CONFIG_CLOUD_TYPE_NOT_SUPPORT,
}ya_net_config_pare_error_code_t;

typedef enum
{
	YA_BLE_SESSION_CONSULT = 0,
	YA_BLE_TOKEN_CHECK,
	YA_BLE_SECURE,
}ya_ble_secure_stage_t;


#define YA_BLE_FRAME_LEN_MAX   256
#define YA_BLE_FRAME_PKG_SIZE  20
#define YA_BLE_FRAME_PKG_MSG_MARK 0x80 //0b10000000
#define YA_BLE_FRAME_PKG_LEN_MARK 0x1F //0b00011111


static ya_hal_os_queue_t ya_ble_msg_queue = NULL;
uint8_t *ble_frame_rece_buf = NULL;
uint8_t *ble_frame_decode_buf = NULL;
uint16_t ble_buffer_index = 0;

static uint8_t msg_rece_sn = 0xFF;

static uint8_t ya_ble_session_key[16]= {0};
static uint8_t ya_ble_session_iv[16]= {0};
static uint8_t ya_ble_session_token[16]= {0};

ble_conf_param_st  g_ble_param;
static uint8_t aes_key_default[16]={0};

uint8_t ya_ble_secure_stage = YA_BLE_SESSION_CONSULT;

void ya_ble_app_debug_array(char *string_start, uint8_t *buf, uint16_t buf_len)
{
#if BLE_APP_DEBUG
	uint16_t i = 0;
	ya_printf(C_LOG_INFO, "\r\n##############debug start################\r\n");
	ya_printf(C_LOG_INFO, "%s\r\nlen===%d\r\n", string_start,buf_len);

	for(i=0; i<buf_len;	i++)
	{
		ya_printf(C_LOG_INFO, "%02x ",	buf[i]);
	}

	ya_printf(C_LOG_INFO, "\r\n##############debug end##################\r\n\r\n");
#endif
}

static int  ya_ble_app_frame_send(uint8_t * data, uint16_t len)
{
	#define  FRAME_VALID_DATA_LEN 18
	uint8_t buf[20]={0};
	uint8_t pkg_len = 0;
	uint8_t pkg_num =  len / FRAME_VALID_DATA_LEN ;
	pkg_num += (len % FRAME_VALID_DATA_LEN )> 0? 1:0;	

	for(int i = 0;i<pkg_num;i++)
	{
		pkg_len  = FRAME_VALID_DATA_LEN;
		buf[0] = 0x00;
		buf[0] &= ~(YA_BLE_FRAME_PKG_MSG_MARK);
		
		if(i+1 == pkg_num)
		{
			if(len % FRAME_VALID_DATA_LEN)
				pkg_len =  len % FRAME_VALID_DATA_LEN;

			buf[0] |= YA_BLE_FRAME_PKG_MSG_MARK ;
		}				
		buf[1] = (i+1) & 0xFF;//pkg index
		buf[0] |= (pkg_len & YA_BLE_FRAME_PKG_LEN_MARK);

		memcpy(buf+2,data+(FRAME_VALID_DATA_LEN*i),pkg_len);
		ya_ble_app_debug_array("frame_send",buf,pkg_len+2);
		if (ya_hal_ble_send_bytes(buf,pkg_len+2)<0)
		{
			ya_printf(C_LOG_ERROR,"hal ble send error\r\n");
			return -1;
		}
	}
	
	return 0;
}

static int ya_ble_get_default_key(uint8_t *aes_key)
{
	char ble_name[64]={0};

	memset(ble_name, 0, 64);	
	sprintf(ble_name, "%s%s", ya_hal_ble_get_name(), "anm123##&");
	ya_mbedtls_md5((uint8_t *)ble_name,aes_key,strlen(ble_name));
	return 0;
}

int ya_ble_app_device_reply_msg_handle(uint8_t *data, uint16_t len, uint8_t cmd_type)
{
	int ret =-1;
	uint8_t iv[16]={0};	
	uint16_t encrypt_data_len = 0;
	uint8_t *send_buff = NULL;
	uint16_t pos = 0, msg_crc16 = 0;

	if (!data || len > (YA_BLE_FRAME_LEN_MAX - 32))
		return -1;

	send_buff = (uint8_t *)ya_hal_os_memory_alloc(YA_BLE_FRAME_LEN_MAX);
	if (!send_buff)
		return -1;

	memset(send_buff, 0, YA_BLE_FRAME_LEN_MAX);
	
	send_buff[pos++] = 0xAA;
	send_buff[pos++] = cmd_type;	
	send_buff[pos++] = msg_rece_sn;
	memcpy(send_buff + pos, data, len);
	
	msg_crc16 = crc16(send_buff+YA_BLE_FRAME_SN_POS, len+1, 0xffff);

	if(cmd_type == YA_BLE_RANDOM_CMD)
	{
		memcpy(iv, aes_key_default, 16);	
		encrypt_data_len = AES_CBC_PKCS5Padding_encrypt(aes_key_default,iv,send_buff+YA_BLE_FRAME_SN_POS,send_buff+YA_BLE_FRAME_SN_POS,len+1);
	}else
	{
		memcpy(iv,ya_ble_session_iv,16);
		encrypt_data_len = AES_CBC_PKCS5Padding_encrypt(ya_ble_session_key,iv,send_buff+YA_BLE_FRAME_SN_POS,send_buff+YA_BLE_FRAME_SN_POS,len+1);
	}
		
	if (!encrypt_data_len)
	{
		ya_hal_os_memory_free(send_buff);
		return -1;		
	}	
	pos = pos + encrypt_data_len - 1;
	
	//Package crc16
	send_buff[pos++] = (uint8_t)(msg_crc16 & 0x00FF);
	send_buff[pos++] = (uint8_t)((msg_crc16 & 0xFF00) >> 8);

	//reply msg
	ret = ya_ble_app_frame_send(send_buff, pos);
	ya_hal_os_memory_free(send_buff);

	return ret;
}

static int ya_ble_app_random_cmd_handle(uint8_t *data,uint16_t len)
{
	int ret = -1;
	uint16_t i = 0;
	uint8_t random_R2[32]={0};

	if(msg_rece_sn == data[0])
		return -1;		
	
	msg_rece_sn = data[0];
	
	ya_os_get_random(random_R2, 32);

	memset(ya_ble_session_iv,0,16);
	memset(ya_ble_session_key,0,16);

	for(i=0; i<16; i++)
	{
		ya_ble_session_iv[i] = data[1+i] ^ random_R2[i];
		ya_ble_session_key[i] = data[1+i+16] ^ random_R2[16+i];
	}

	ya_ble_app_debug_array("ya_ble_session_iv", ya_ble_session_iv, 16);
	ya_ble_app_debug_array("ya_ble_session_key", ya_ble_session_key, 16);
	
	ret = ya_ble_app_device_reply_msg_handle(random_R2, 32, YA_BLE_RANDOM_CMD);

	return ret;
}

static int ya_ble_app_token_cmd_handle(uint8_t * data,uint16_t len)
{
	int ret = -1;
	uint8_t error_code[1] = {0}; 

	if(msg_rece_sn == data[0])
		return -1;

	msg_rece_sn = data[0];

	if (len < 16)
		return -1;

	if (g_ble_param.ble_token_get)
	{
		if (memcmp(ya_ble_session_token, data + 1, 16) == 0)
			error_code[0] = 0;
	} else
	{
		memcpy(ya_ble_session_token, data + 1, 16);
	}
	
	ret = ya_ble_app_device_reply_msg_handle(error_code, 1, YA_BLE_GET_TOKEN_CMD);
	return ret;
}


ya_ble_router_para_t ble_router_info;

static int ya_ble_app_netconfig_cmd_handle(uint8_t * data,uint16_t len)
{
	int ret = 0;
	uint16_t pos = 0;
	uint8_t ssidLength = 0, pwdLength = 0;
	uint8_t error_code = NET_CONFIG_SUCCESS;
	uint8_t plaintext_buf[16];

	memset(&ble_router_info, 0, sizeof(ya_ble_router_para_t));

	if(msg_rece_sn == data[0])
		return -1;

	msg_rece_sn = data[0];

	pos++;
	ssidLength = data[pos];
	if (ssidLength > 32)
	{
		error_code = NET_CONFIG_ARG_ERROR;
		goto OUT;
	}
		
	pos++;
	memcpy(ble_router_info.router_ssid ,data+pos, ssidLength);
	pos += ssidLength;
	pwdLength = data[pos];
		
	if (pwdLength > 64)
	{
		error_code = NET_CONFIG_ARG_ERROR;
		goto OUT;
	}
		
	pos++;
	memcpy(ble_router_info.router_pwd,data+pos,pwdLength);
	pos += pwdLength;
	
	ble_router_info.cloud_type = data[pos];
	pos += 1;
	if(!(ya_get_wifi_cloud_support() & (0x01<<ble_router_info.cloud_type))) // select_cloud_type: CN 0,US 1,EU 2
	{
		error_code = NET_CONFIG_CLOUD_TYPE_NOT_SUPPORT;
		goto OUT;
	}
	
	HexArrayToString(ya_ble_session_token, 16, ble_router_info.random);
	
OUT:
	memset(plaintext_buf, 0, 16);

	plaintext_buf[0] = 0x00;
	plaintext_buf[1] = 0x80;
	plaintext_buf[2] = error_code;
	plaintext_buf[3] = (uint8_t)ya_get_wifi_cloud_support();

	ret = ya_ble_app_device_reply_msg_handle(plaintext_buf, 4, YA_BLE_NET_CONFIG_CMD);
	ya_delay(200); 
	ret = ya_ble_app_device_reply_msg_handle(plaintext_buf, 4, YA_BLE_NET_CONFIG_CMD);
	ya_delay(200); 
	
	if (error_code == NET_CONFIG_SUCCESS)
	{
		ble_router_info.code = 1;
		ya_stop_ble_app();
	}else
		ret = -1;
		
	return ret;

}

static int ya_ble_secure_data_process_handle(uint8_t *data,uint16_t len, uint8_t cmd)
{
	if(msg_rece_sn == data[0])
		return -1;

	msg_rece_sn = data[0];
	//ya_stripLights_app_ble_event_into_queue(data, len, cmd);
	return 0;
}

static int ya_ble_app_data_handle(uint8_t *data, uint16_t len)
{
	int ret = -1;
	uint16_t decrypt_data_len = 0, crc16_get = 0, crc16_cac = 0;
	uint8_t iv[16]={0};
	
	ya_ble_app_debug_array("ble recv msg",data,len);
	memset(ble_frame_decode_buf, 0, YA_BLE_FRAME_LEN_MAX);
	if (data[YA_BLE_FRAME_HEADER_POS] != 0xAA)
		return -1;

	if (len < 20)
		return -1;
	
	crc16_get = data[len-2] + (uint16_t)((data[len-1] & 0x00FF) << 8);
	memset(iv, 0, 16);

	ya_printf(C_LOG_INFO,"ble cmd: %d\r\n", data[YA_BLE_FRAME_CMD_POS]);

	if (ya_ble_secure_stage == YA_BLE_SESSION_CONSULT)
	{
		if (data[YA_BLE_FRAME_CMD_POS] == YA_BLE_RANDOM_CMD)
		{
			memcpy(iv, aes_key_default, 16);
			decrypt_data_len = AES_CBC_PKCS5Padding_decrypt(aes_key_default, iv, data+YA_BLE_FRAME_SN_POS, ble_frame_decode_buf, len-4);
			if(!decrypt_data_len)
			{
				ya_printf(C_LOG_ERROR,"default deocode error");
				return -1;	
			}

			ya_ble_app_debug_array("default decode", ble_frame_decode_buf, decrypt_data_len);

			crc16_cac = crc16(ble_frame_decode_buf, decrypt_data_len, 0xffff);

			if( crc16_cac != crc16_get)
			{
				ya_printf(C_LOG_ERROR,"ble default crc error");
				return -1;
			}

			ret = ya_ble_app_random_cmd_handle(ble_frame_decode_buf, decrypt_data_len);
			if (ret != 0)
				return -1;

			ya_ble_secure_stage = YA_BLE_TOKEN_CHECK;
		} else
		{
			return -1;
		}
	} else 
	{
		memcpy(iv, ya_ble_session_iv, 16);
		decrypt_data_len = AES_CBC_PKCS5Padding_decrypt(ya_ble_session_key, iv, data+YA_BLE_FRAME_SN_POS, ble_frame_decode_buf, len-4);

		if(!decrypt_data_len)
		{
			ya_printf(C_LOG_ERROR,"session deocode error");
			return -1;
		}
		
		ya_ble_app_debug_array("session decode", ble_frame_decode_buf, decrypt_data_len);

		crc16_cac = crc16(ble_frame_decode_buf, decrypt_data_len, 0xffff);

		if( crc16_cac != crc16_get)
		{
			ya_printf(C_LOG_ERROR,"ble session crc error\r\n");
			return -1;
		}


		if (ya_ble_secure_stage == YA_BLE_TOKEN_CHECK && data[YA_BLE_FRAME_CMD_POS] == YA_BLE_GET_TOKEN_CMD)
		{
			ret = ya_ble_app_token_cmd_handle(ble_frame_decode_buf, decrypt_data_len);
			if (ret != 0)
				return -1;

			ya_ble_secure_stage = YA_BLE_SECURE;
		} else if (ya_ble_secure_stage == YA_BLE_SECURE && data[YA_BLE_FRAME_CMD_POS] > YA_BLE_GET_TOKEN_CMD)
		{
			switch (data[YA_BLE_FRAME_CMD_POS])
			{
				case YA_BLE_NET_CONFIG_CMD:
					ret = ya_ble_app_netconfig_cmd_handle(ble_frame_decode_buf, decrypt_data_len);
				break;

				default:
					ret = ya_ble_secure_data_process_handle(ble_frame_decode_buf, decrypt_data_len, data[YA_BLE_FRAME_CMD_POS]);
				break;
			}

			ya_ble_secure_stage = YA_BLE_SECURE;
		} else 
		{
			return -1;
		}
	} 
	return ret;
}


int ya_ble_msg_send_queue(uint8_t *data,uint16_t len, ya_ble_msg_type_t type)
{
	int ret = -1;
	msg_t ms_msg;
	uint8_t * pdata = NULL;
	
	if(len >0)
	{
		pdata = (uint8_t *)ya_hal_os_memory_alloc(len);
		if(pdata==NULL)
			return ret;

		memset(pdata,0,len);
		memcpy(pdata,data,len);
	}

	memset(&ms_msg, 0, sizeof(msg_t));
	ms_msg.addr = pdata;
	ms_msg.len = len;
	ms_msg.type = type;

	ret = ya_hal_os_queue_send(&ya_ble_msg_queue, &ms_msg, 10);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR,"Send msg to ya_ble_msg_queue error!!!!\r\n");
		
		if(ms_msg.addr)
			ya_hal_os_memory_free(ms_msg.addr);

		return -1;
	}

	return 0;
}


static void ya_ble_recv_data(uint8_t *data, uint16_t len)
{
	int i = 0;
	uint8_t data_len=0;

	if(len < 3)
		return;
	
	if(len > YA_BLE_FRAME_PKG_SIZE)
		return;
	
	data_len = data[0] & YA_BLE_FRAME_PKG_LEN_MARK;
	if (data_len > 18 || (ble_buffer_index + data_len) >= YA_BLE_FRAME_LEN_MAX)
		goto out;

	if(data_len != (len-2))
		goto out;

	for (i=2; i<len; i++)
	{		
		ble_frame_rece_buf[ble_buffer_index] = data[i];
		ble_buffer_index++;
	}

	if (data[0] & YA_BLE_FRAME_PKG_MSG_MARK)//final frame
	{				
		ya_ble_msg_send_queue(ble_frame_rece_buf, ble_buffer_index,BLE_MSG_CMD);			
		goto out;
	}

	return;

	out:
	memset(ble_frame_rece_buf,0,YA_BLE_FRAME_LEN_MAX);
	ble_buffer_index = 0;

	return;
}

static void ya_ble_connect_state_handle(uint8_t state)
{
	static uint8_t ble_connect_state = 0;

	if (ble_connect_state != state)
	{
		ble_connect_state = state;
		ya_printf(C_LOG_INFO, "ya_ble_connect_state_handle to queue: %d\r\n", ble_connect_state);
		if (ble_connect_state == 1)
			ya_ble_msg_send_queue(NULL, 0, BLE_MSG_CONNECT);
		else
			ya_ble_msg_send_queue(NULL, 0, BLE_MSG_DISCONNECT);
	}

	return;
}


void ya_ble_task(void *arg)
{
	int ret = -1;
	uint8_t flag_terminate = 0, pos = 0, connect_flag = 0;
	Ya_Timer ya_ble_timer;
	msg_t ble_app_msg;
	uint32_t ble_connect_time = 0, cur_time = 0;
	uint8_t ble_ff_string[31] = {0};

	memset(ble_ff_string, 0, 31);

	ble_ff_string[pos++] = BLE_NET_CONFIG_VERSION;
	ble_ff_string[pos++] = LIGHT;
	ble_ff_string[pos++] = 0;

	ret = ya_get_cloud_type((char *)(ble_ff_string + pos));
	if (ret != 0) 
		goto END;	

	pos += strlen((char *)(ble_ff_string + pos));
	
	if(!ble_frame_rece_buf)
	{
		ble_frame_rece_buf = (uint8_t*)ya_hal_os_memory_alloc(YA_BLE_FRAME_LEN_MAX);
		if (!ble_frame_rece_buf) goto END;
		memset(ble_frame_rece_buf,0,YA_BLE_FRAME_LEN_MAX);
	}
	
	if(!ble_frame_decode_buf)
	{
		ble_frame_decode_buf = (uint8_t*)ya_hal_os_memory_alloc(YA_BLE_FRAME_LEN_MAX);
		if(!ble_frame_decode_buf) goto END;
		memset(ble_frame_decode_buf,0,YA_BLE_FRAME_LEN_MAX);
	}
	
	msg_rece_sn = 0xFF;
	ble_buffer_index = 0;
	ya_ble_secure_stage = YA_BLE_SESSION_CONSULT;

	ya_ble_get_default_key(aes_key_default);

	ya_hal_ble_set_rcv_cb(ya_ble_recv_data);
	ya_hal_ble_set_connect_state_cb(ya_ble_connect_state_handle);
	
	ya_hal_ble_init();
	ya_delay(200);
	
	ya_hal_ble_start_adv(ble_ff_string, pos);

	ya_init_timer(&ya_ble_timer);
	ya_countdown_ms(&ya_ble_timer, g_ble_param.timeout*1000);
	
	while(1)
	{
		cur_time = ya_hal_os_ticks_to_msec();
		memset(&ble_app_msg, 0, sizeof(msg_t));

		if (connect_flag)
		{
			if (ya_timer_compare(ble_connect_time, cur_time, 6000) == C_OK)
			{
				ya_hal_disconnect_ble_conn();
				connect_flag = 0;
			}
		}
		
		ret = ya_hal_os_queue_recv(&ya_ble_msg_queue, &ble_app_msg, 50);

		if(ret == C_OK)
		{
			switch(ble_app_msg.type)
			{
				case BLE_MSG_CMD:
					ret = ya_ble_app_data_handle(ble_app_msg.addr, ble_app_msg.len);
					if (ret < 0)
						ya_printf(C_LOG_ERROR, "ya_ble_app_data_handle error\r\n");
					
					ble_connect_time = ya_hal_os_ticks_to_msec();
					break;

				case BLE_MSG_CONNECT:
					ya_printf(C_LOG_INFO, "BLE_MSG_CONNECT\r\n");
					ble_connect_time = ya_hal_os_ticks_to_msec();
					connect_flag = 1;
					break;

				case BLE_MSG_DISCONNECT:
					ya_printf(C_LOG_INFO, "BLE_MSG_DISCONNECT\r\n");
					msg_rece_sn = 0xFF;
					ble_buffer_index = 0;
					ya_ble_secure_stage = YA_BLE_SESSION_CONSULT;
					ya_hal_ble_start_adv(ble_ff_string, pos);
					connect_flag = 0;
					break;
					
				case BLE_MSG_CLOSE:
					flag_terminate = 1;
					ya_hal_stop_ble();
					if (ble_router_info.code)
						g_ble_param.p_ble_config_cb(BLE_CONFIG_FINISH, &ble_router_info);

					break;
				default:
					break;
			}

			if (ble_app_msg.addr)
			{
				ya_hal_os_memory_free(ble_app_msg.addr);
				ble_app_msg.addr = NULL;
			}
		}

		if (flag_terminate == 1) break;

		if (ya_has_timer_expired(&ya_ble_timer) == 0)
		{
			printf("ble timeout stop\r\n");
			g_ble_param.p_ble_config_cb(BLE_TIME_OUT, NULL);
			ya_hal_stop_ble();
			break;
		}
	}

	END:
	if(ble_frame_rece_buf)
	{
		ya_hal_os_memory_free(ble_frame_rece_buf);
		ble_frame_rece_buf = NULL;
	}
	if(ble_frame_decode_buf)
	{
		ya_hal_os_memory_free(ble_frame_decode_buf);
		ble_frame_decode_buf = NULL;
	}

	vTaskDelete(NULL);
}

void ya_stop_ble_app(void)
{
	ya_ble_msg_send_queue(NULL, 0, BLE_MSG_CLOSE);
}

int32_t ya_start_ble_app(ble_conf_param_st *ble_param)
{
	int ret = -1;

	memcpy(&g_ble_param, ble_param, sizeof(ble_conf_param_st));
	
	ret = ya_hal_os_queue_create(&ya_ble_msg_queue, "ya_ble_msg_queue", sizeof(msg_t), MSG_QUEUE_LENGTH);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create ble queue error\r\n");
		return -1;
	}
	
	ret = ya_hal_os_thread_create(NULL, "ya_ble_task", ya_ble_task, NULL, (4*1024), 3);
	if(ret != 0)
	{
		ya_printf(C_LOG_ERROR, "create ya_ble_task error\r\n");
		return -1;
	}

	return 0;
}


