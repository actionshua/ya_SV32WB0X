
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
#include "ya_aes_md5.h"
#include "ya_common_func.h"
#include "infra_defs.h"
#include "ya_melody_broadcast.h"

#define RHYTHM_BROADCAST_DEBUG 1

typedef enum
{
	YA_RHYTHM_FRAME_HEADER_POS 	= 0,
	YA_RHYTHM_FRAME_DATA_LEN_LOW_POS,
	YA_RHYTHM_FRAME_DATA_LEN_HIGH_POS,
	YA_RHYTHM_FRAME_CMD_POS,
	YA_RHYTHM_FRAME_CNT_POS_0,
	YA_RHYTHM_FRAME_CNT_POS_1,
	YA_RHYTHM_FRAME_CNT_POS_2,
	YA_RHYTHM_FRAME_CNT_POS_3,
	YA_RHYTHM_FRAME_DATA_POS,
}ya_rhythm_frame_pos_t;


typedef struct 
{
	struct sockaddr_in sock_addr_in;
	socklen_t sock_addr_len;

	uint8_t ya_rhythm_session_key[16];
	uint8_t ya_rhythm_session_iv[16];
	uint32_t cnt;
	uint32_t timer;
	uint8_t exit;
} ya_rhythm_session_t;

#define YA_RHYTHM_UNICAST_PORT  			8001   
#define YA_RHYTHM_LISTEN_PORT				8000
#define RHYTHM_FRAME_LEN_MAX   				256
#define UDP_LEAST_LEN 						11
#define UDP_SESSION_NUM_MAX 				5
#define RHYTHM_UDP_RECE_TIMEOUT				1000

uint8_t wlan_token[16];
ya_rhythm_session_t ya_rhythm_session[UDP_SESSION_NUM_MAX];
static uint8_t *rhythm_rece_buffer = NULL;
static uint8_t *rhythm_decode_buffer = NULL;
int32_t udp_fd = -1;

void ya_rhythm_debug_array(char *string_start, uint8_t *buf, uint16_t buf_len)
{
#if RHYTHM_BROADCAST_DEBUG
	uint16_t i = 0;
	ya_printf(C_LOG_INFO, "\r\n %s: len===%d\r\n", string_start,buf_len);

	for(i=0; i<buf_len;	i++)
	{
		ya_printf(C_LOG_INFO, "%02x ",	buf[i]);
	}
	ya_printf(C_LOG_INFO, "\r\n");
#endif
}


static int ya_rhythm_reply_msg_unicast(int fd,in_addr_t addr,uint8_t* buf,uint16_t len)
{
	struct sockaddr_in addrto;
	int nlen;
	int ret = -1;

	memset(&addrto, 0, sizeof(struct sockaddr_in));
	addrto.sin_family = AF_INET;
	addrto.sin_addr.s_addr = addr;
	addrto.sin_port=htons(YA_RHYTHM_UNICAST_PORT);
	nlen=sizeof(addrto);

	ret = ya_hal_socket_sendto(fd, buf, len, 0, (struct sockaddr*)&addrto, nlen);
	return ret;
}


static int ya_rhythm_reply_msg_process(uint8_t *data, uint16_t len, uint8_t cmd_type, uint8_t *cnt, uint8_t current_session_id)
{
	int ret =-1;
	uint8_t iv[16]={0};	
	uint16_t encrypt_data_len = 0;
	uint8_t *send_buff = NULL;
	uint16_t pos = 0, msg_crc16 = 0;

	if (!data || len > (RHYTHM_FRAME_LEN_MAX - 32))
		goto out;

	send_buff = (uint8_t *)ya_hal_os_memory_alloc(RHYTHM_FRAME_LEN_MAX);
	if (!send_buff)
		goto out;

	memset(send_buff, 0, RHYTHM_FRAME_LEN_MAX);
	send_buff[pos++] = 0xAA;
	pos = pos + 2;
	send_buff[pos++] = cmd_type;
	memcpy(send_buff + pos, cnt, 4);
	memcpy(send_buff + 4 + pos, data, len);	
	msg_crc16 = crc16(send_buff+YA_RHYTHM_FRAME_CNT_POS_0, len+4, 0xffff);

	if(cmd_type == YA_RHYTHM_DEVICE_DISCOVER_CMD)
	{
		memcpy(iv, wlan_token, 16);	
		encrypt_data_len = AES_CBC_PKCS5Padding_encrypt(wlan_token,iv,send_buff+YA_RHYTHM_FRAME_CNT_POS_0,send_buff+YA_RHYTHM_FRAME_CNT_POS_0,len+4);
	}
	else
	{
		memcpy(iv,ya_rhythm_session[current_session_id].ya_rhythm_session_iv,16);
		encrypt_data_len = AES_CBC_PKCS5Padding_encrypt(ya_rhythm_session[current_session_id].ya_rhythm_session_key,iv,send_buff+YA_RHYTHM_FRAME_CNT_POS_0,send_buff+YA_RHYTHM_FRAME_CNT_POS_0,len+4);
	}
		
	if (!encrypt_data_len)
	{
		ya_printf(C_LOG_ERROR,"\r\nAES_CBC_PKCS5Padding_encrypt error:%s,%d\r\n",__FUNCTION__,__LINE__);
		goto out;
	}	
	send_buff[YA_RHYTHM_FRAME_DATA_LEN_LOW_POS] = encrypt_data_len;
	send_buff[YA_RHYTHM_FRAME_DATA_LEN_HIGH_POS] = encrypt_data_len >> 8;
	pos = pos + encrypt_data_len;
	
	send_buff[pos++] = (uint8_t)(msg_crc16 & 0x00FF);
	send_buff[pos++] = (uint8_t)((msg_crc16 & 0xFF00) >> 8);

	ret = ya_rhythm_reply_msg_unicast(udp_fd, ya_rhythm_session[current_session_id].sock_addr_in.sin_addr.s_addr,send_buff,pos);	

out:
	if(send_buff)
	{
		ya_hal_os_memory_free(send_buff);
		send_buff = NULL;
	}

	return ret;
}

static int ya_rhythm_discover_cmd_handle(uint8_t *data, uint16_t len, uint8_t current_session_id)
{
	uint16_t i = 0;
	int ret = -1;
	uint8_t random_R2[32]={0}, get_deviceID_len = 0;
	char device_id[YA_DEVICE_ID_LEN + 1] = {0};
	uint8_t plaintext_buf[128] = {0};
	uint16_t pos = 0;
	uint32_t ip_addr = 0;

	if (len < (4 + 1 + 1 + 32) || len < (4 + 1 + data[4] + 32))
	{
		ya_printf(C_LOG_ERROR, "ya_rhythm_discover_cmd_handle fail:%s,%d\n",__FUNCTION__,__LINE__);
		return -1;
	}
	
	ret = ya_get_cloud_device_id(device_id);
	if (ret != 0) 
	{
		ya_printf(C_LOG_ERROR, "\r\n====no device id eixt====\r\n");
		return -1;
	}	

	get_deviceID_len = strlen(device_id);

	if (get_deviceID_len== data[4] && 0 == memcmp(data+5,device_id,data[4]))
	{
		ya_os_get_random(random_R2, 32);

		memset(ya_rhythm_session[current_session_id].ya_rhythm_session_iv,0,16);
		memset(ya_rhythm_session[current_session_id].ya_rhythm_session_key,0,16);

		for (i=0; i<16; i++)
		{
			ya_rhythm_session[current_session_id].ya_rhythm_session_iv[i] = data[5+get_deviceID_len+i] ^ random_R2[i];
			ya_rhythm_session[current_session_id].ya_rhythm_session_key[i] = data[5+get_deviceID_len+i+16] ^ random_R2[i+16];
		}

		memset(plaintext_buf, 0, 128);
		plaintext_buf[pos++] = get_deviceID_len;
		memcpy(plaintext_buf+pos,device_id,get_deviceID_len);
		pos += get_deviceID_len;
		
		ya_hal_wlan_get_ip_address(&ip_addr);
		plaintext_buf[pos++] = 0;
		plaintext_buf[pos++] = (uint8_t)(ip_addr & 0x000000FF);
		plaintext_buf[pos++] = (uint8_t)((ip_addr & 0x0000FF00) >> 8);
		plaintext_buf[pos++] = (uint8_t)((ip_addr & 0x00FF0000) >> 16);
		plaintext_buf[pos++] = (uint8_t)((ip_addr & 0xFF000000) >> 24);	
		ya_hal_wlan_get_mac_address(plaintext_buf+pos);
		pos += 6;
		memcpy(plaintext_buf+pos,random_R2,32);
		pos += 32;
		plaintext_buf[pos++] = 0x01;

		ya_printf(C_LOG_INFO, "\r\n====send cmd discover response====\r\n");
		ret = ya_rhythm_reply_msg_process(plaintext_buf, pos, YA_RHYTHM_DEVICE_DISCOVER_CMD, data, current_session_id);
	}
	
	return ret;		
}

extern void ya_stripLights_app_udp_event_into_queue(uint8_t *buf, uint16_t len, uint8_t cmd);
static int ya_rhythm_app_cmd_handle(uint8_t *data, uint16_t len, uint8_t cmd, uint8_t current_session_id)
{
	uint8_t buf_send[1];
	int ret = -1;
	uint32_t cnt_tmp = 0;

	if (len < (4 + 1))
	{
		ya_printf(C_LOG_ERROR, "ya_rhythm_app_cmd_handle fail:%s,%d\n",__FUNCTION__,__LINE__);
		return -1;
	}
	
	cnt_tmp = ((data[3] & 0x000000FF)<<24) + ((data[2] & 0x000000FF)<<16) + 
									((data[1] & 0x000000FF)<<8) + (data[0] & 0x000000FF);

	if (ya_rhythm_session[current_session_id].cnt  < 0xFF000000)
	{
		if (ya_rhythm_session[current_session_id].cnt > cnt_tmp)
		{
			ya_printf(C_LOG_ERROR,"cnt repeat!,%s,%d\r\n",__FUNCTION__,__LINE__);
			return ret;
		} 
	}
	
	ya_rhythm_session[current_session_id].cnt = cnt_tmp;
	ya_rhythm_session[current_session_id].cnt++;
	

	if(cmd == YA_RHYTHM_DEVICE_CONFIRM_CMD)
	{
		buf_send[0] = 0;
		ret = ya_rhythm_reply_msg_process(buf_send, 1, YA_RHYTHM_DEVICE_CONFIRM_CMD, data, current_session_id);
	} else
	{
		ya_stripLights_app_udp_event_into_queue(data+4, len-4, cmd);
		ret = 0;
	}
	
	return ret;		
}

static int ya_rhythm_rece_data_handle(uint8_t *buffer, uint16_t len, uint8_t session_id)
{
	int ret = -1;
	uint8_t iv[16]={0};
	uint16_t crc16_cac = 0, crc16_get = 0;
	uint32_t cipher_data_len = 0, decrypt_data_len = 0;
	uint8_t cmd_type = 0;
	
	if (buffer[YA_RHYTHM_FRAME_HEADER_POS] != 0xAA)
		return ret;	

	crc16_get = buffer[len-2] + ((buffer[len-1] & 0x00FF) << 8);
	cmd_type = buffer[YA_RHYTHM_FRAME_CMD_POS];

	cipher_data_len = ((buffer[YA_RHYTHM_FRAME_DATA_LEN_HIGH_POS] & 0x00FF) <<8) + buffer[YA_RHYTHM_FRAME_DATA_LEN_LOW_POS];

	if(cipher_data_len == 0 || cipher_data_len > RHYTHM_FRAME_LEN_MAX || (cipher_data_len + 4) > len)
	{
		ya_printf(C_LOG_ERROR,"\r\ncipher_data_len error: %d!\r\n", cipher_data_len);
		return ret;
	}

	if (cmd_type == YA_RHYTHM_DEVICE_DISCOVER_CMD) {
		memcpy(iv, wlan_token, 16);		
		decrypt_data_len = AES_CBC_PKCS5Padding_decrypt(wlan_token, iv, buffer+YA_RHYTHM_FRAME_CNT_POS_0, rhythm_decode_buffer, cipher_data_len);
	} else {
		memcpy(iv, ya_rhythm_session[session_id].ya_rhythm_session_iv, 16);
		decrypt_data_len = AES_CBC_PKCS5Padding_decrypt(ya_rhythm_session[session_id].ya_rhythm_session_key, iv, buffer+YA_RHYTHM_FRAME_CNT_POS_0, rhythm_decode_buffer, cipher_data_len);
	}
	
	if (!decrypt_data_len) {
		ya_printf(C_LOG_ERROR,"\r\nmsg deocode error\r\n");
		return ret; 
	}
		
	crc16_cac = crc16(rhythm_decode_buffer, decrypt_data_len, 0xffff);
	
	if (crc16_cac != crc16_get) {
		ya_printf(C_LOG_ERROR,"\r\n msg crc error,crc16_cac==0x%x,crc16_get==0x%x\r\n",crc16_cac,crc16_get);
		return ret;
	}

	ya_printf(C_LOG_INFO, "get cmd type: %d\n", cmd_type);

	ya_rhythm_debug_array("decode wlan data", rhythm_decode_buffer, decrypt_data_len);
	
	if (cmd_type == YA_RHYTHM_DEVICE_DISCOVER_CMD) {
		ret = ya_rhythm_discover_cmd_handle(rhythm_decode_buffer,decrypt_data_len,session_id);
		if (ret >= 0)
			ya_rhythm_session[session_id].cnt = 0;
	} else {
		ret = ya_rhythm_app_cmd_handle(rhythm_decode_buffer, decrypt_data_len, cmd_type, session_id);
	}

	if (ret >= 0) {
		ya_rhythm_session[session_id].exit = 1;
		ya_rhythm_session[session_id].timer = ya_hal_os_ticks_to_msec();
	} else {
		ya_rhythm_session[session_id].exit = 0;
	}
	return ret;
}


int32_t ya_check_udp_session_exit(struct sockaddr_in *sock_addr_in)
{
	uint8_t index = 0;

	for (index = 0; index < UDP_SESSION_NUM_MAX; index++)
	{
		if (ya_rhythm_session[index].exit)
		{
			if (memcmp(&(ya_rhythm_session[index].sock_addr_in.sin_addr), &(sock_addr_in->sin_addr), sizeof(struct in_addr))==0)
				return index;
		}
	}

	for (index = 0; index < UDP_SESSION_NUM_MAX; index++)
	{
		if (ya_rhythm_session[index].exit == 0)
		{
			memcpy(&(ya_rhythm_session[index].sock_addr_in), sock_addr_in, sizeof(struct sockaddr_in));		
			printf("add ip is: %d, index: %d\r\n", ya_rhythm_session[index].sock_addr_in.sin_addr, index);
			return index;
		}
	}

	return -1;
}

void ya_check_udp_session_timer(void)
{
	uint8_t index = 0;
	uint32_t cur_time = ya_hal_os_ticks_to_msec();

	for (index = 0; index < UDP_SESSION_NUM_MAX; index++)
	{
		if (ya_rhythm_session[index].exit)
		{
			if (ya_timer_compare(ya_rhythm_session[index].timer, cur_time, 5*60*1000)== 0)
			{
				printf("clear session: %d\r\n", index);
				ya_rhythm_session[index].exit = 0;
			}
		}
	}
}


static int ya_rhythm_session_init(void)
{	
	uint8_t i = 0;
	if(!rhythm_rece_buffer)
	{
		rhythm_rece_buffer = (uint8_t*)ya_hal_os_memory_alloc(RHYTHM_FRAME_LEN_MAX);
		if (!rhythm_rece_buffer) 
		{
			ya_printf(C_LOG_ERROR, "ya_hal_os_memory_alloc fail:%s,%d\n",__FUNCTION__,__LINE__);
			return -1;
		}	
	}

	memset(rhythm_rece_buffer,0,RHYTHM_FRAME_LEN_MAX);
	
	if(!rhythm_decode_buffer)
	{
		rhythm_decode_buffer = (uint8_t*)ya_hal_os_memory_alloc(RHYTHM_FRAME_LEN_MAX);
		if (!rhythm_decode_buffer) 
		{
			ya_printf(C_LOG_ERROR, "ya_hal_os_memory_alloc fail:%s,%d\n",__FUNCTION__,__LINE__);
			return -1;
		}
	}

	memset(rhythm_decode_buffer,0,RHYTHM_FRAME_LEN_MAX);	

	for(i = 0;i < UDP_SESSION_NUM_MAX; i++)
	{
		memset(&ya_rhythm_session[i],0,sizeof(ya_rhythm_session_t));

		ya_rhythm_session[i].sock_addr_in.sin_family = AF_INET; 
		ya_rhythm_session[i].sock_addr_len = sizeof(struct sockaddr);	
	}

	return 0;
}

ya_hal_os_thread_t ya_rhythm_udp_server_thread = NULL;

static void ya_rhythm_wlan_udp_server(void *param)
{
	int ret = -1;
	int32_t udp_rece_msg_len = 0;

	struct sockaddr_in sock_addr_in;
	socklen_t sock_addr_len;

	ret = ya_rhythm_session_init();
	if (ret != 0)
	{
		ya_printf(C_LOG_ERROR, "udp_server_init error\r\n");
		goto out; 
	}
	
	udp_fd = ya_udp_server(YA_RHYTHM_LISTEN_PORT, RHYTHM_UDP_RECE_TIMEOUT);
	if (udp_fd < 0)
	{
		ya_printf(C_LOG_ERROR, "ya_udp_server error\r\n");
		goto out; 
	}

	ya_printf(C_LOG_INFO, "ya_rhythm_wlan_udp_server start\r\n");
	
	while(1)
	{			
		sock_addr_len = sizeof(struct sockaddr);

		memset(rhythm_decode_buffer, 0, RHYTHM_FRAME_LEN_MAX);
		udp_rece_msg_len = 0;
		
		udp_rece_msg_len = ya_hal_socket_recvform(udp_fd, rhythm_rece_buffer, RHYTHM_FRAME_LEN_MAX, 0, (struct sockaddr*)&sock_addr_in, &sock_addr_len);

		if (udp_rece_msg_len > UDP_LEAST_LEN)
		{		
			ret = ya_check_udp_session_exit(&sock_addr_in);
			if (ret >= 0)
				ya_rhythm_rece_data_handle(rhythm_rece_buffer, udp_rece_msg_len, ret);
		}

		ya_check_udp_session_timer();

	}
out:
	if (udp_fd >= 0)
	{
		close(udp_fd);
		udp_fd = -1;
	}

	if (rhythm_rece_buffer)
	{
		ya_hal_os_memory_free(rhythm_rece_buffer);
		rhythm_rece_buffer = NULL;
	}

	
	if (rhythm_decode_buffer)
	{
		ya_hal_os_memory_free(rhythm_decode_buffer);
		rhythm_decode_buffer = NULL;
	}

	ya_hal_os_thread_delete(&ya_rhythm_udp_server_thread);
	ya_rhythm_udp_server_thread = NULL;
	return;
}

int32_t ya_start_rhythm_broadcast(void)
{
	int ret = C_ERROR;
	
	ya_printf(C_LOG_INFO, "start ya_rhythm_udp_server_thread\r\n");

	if (ya_rhythm_udp_server_thread)
		return 0;
	
	memset(wlan_token, 0, 16);

	ret = ya_get_wlan_token(wlan_token);
	
	if (ret < 0)
	{
		ya_printf(C_LOG_ERROR, "\r\n====no token eixt====\r\n");
		return -1;
	}
	
	ret = ya_hal_os_thread_create(&ya_rhythm_udp_server_thread, "rhy_udp_server", ya_rhythm_wlan_udp_server, 0, (3*1024), 3);
	if(ret != C_OK)
		ya_printf(C_LOG_ERROR, "create ya_rhythm_udp_server error\n");
		
	return ret;
}


