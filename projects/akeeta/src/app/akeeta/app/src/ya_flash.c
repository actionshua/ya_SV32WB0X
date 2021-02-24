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
#include "ya_flash.h"
#include "ya_aes_md5.h"

#define MAX_DATA_LEN	(4*1024)    //4K   

uint8_t flash_aes_key[16] = {0};

static uint8_t flash_init = 0;

int32_t ya_init_flash_handle(void)
{
	char flash_string_key[] = "abcdargrace##";

	memset(flash_aes_key, 0, 16);
	ya_mbedtls_md5((uint8_t *)flash_string_key, flash_aes_key, strlen(flash_string_key));

	return 0;
}

uint8_t ya_flash_checksum(uint8_t *data, uint32_t data_len)
{
	uint8_t checksum = 0;
	uint32_t index = 0;
	for(index = 0; index < data_len; index++)
	{
		checksum += data[index];
	}

	return checksum;
}


int32_t ya_write_flash(uint32_t flash_addr, uint8_t *data, uint16_t data_len, uint8_t flash_block, uint8_t flag_aes)
{
	int32_t ret = -1;
	uint8_t *buf = NULL;

	uint16_t alloc_len = 0;

	if (!flash_init)
	{
		ya_init_flash_handle();
		flash_init = 1;
	}

	if(flash_block == 0)
		return -1;
	
	if(data_len == 0 || data_len > (MAX_DATA_LEN*flash_block - 32))
	{
		ya_printf(C_AT_CMD, "write len error: %d\r\n", data_len);
		return -1;
	}

	alloc_len = (data_len/16 + 1) * 16;
	buf = (uint8_t *)ya_hal_os_memory_alloc(alloc_len + 4);

	if(!buf)
		return -1;

	if (flag_aes == 1)
		memset(buf + 4, (16 - (data_len % 16)), alloc_len);
	else
		memset(buf + 4, 0, alloc_len);

	buf[0] = 0xAA;
	buf[1] = (uint8_t)(alloc_len & 0x00FF);
	buf[2] = (uint8_t)((alloc_len>>8) & 0x00FF);

	memcpy(buf + 4, data, data_len);	

	if (flag_aes == 1)
		AES_ECB_PKCS5Padding_encrypt(flash_aes_key, buf + 4, alloc_len);

	buf[3] = ya_flash_checksum(buf + 4, alloc_len);

	ya_printf(C_AT_CMD, "w-h: %02x, %02x, %02x, %02x\r\n", buf[0], buf[1], buf[2],buf[3]);
	
	ret = ya_hal_flash_write(flash_addr, buf, (alloc_len+4));
	ya_hal_os_memory_free(buf);
	
	return ret;
}


int32_t ya_read_flash_with_var_len(uint32_t flash_addr, uint8_t *data, uint16_t *data_len, uint8_t flash_block, uint8_t flag_aes)
{
	int32_t ret = -1, decyt_len = 0;
	uint16_t total_len = 0;
	uint8_t header[4];	
	uint8_t *buf = NULL;

	if (!flash_init)
	{
		ya_init_flash_handle();
		flash_init = 1;
	}

	if(flash_block == 0 || (*data_len) == 0)
		return -1;

	ret = ya_hal_flash_read(flash_addr, header, 4);
	if(ret != 0)
	{
		ya_printf(C_LOG_ERROR, "read header error\r\n");
		(*data_len) = 0;
		return -1;
	}

	ya_printf(C_LOG_INFO, "r-v-header %02x, %02x, %02x, %02x\r\n", header[0], header[1], header[2], header[3]);
	
	if(header[0] != 0xAA)
	{
		ya_printf(C_LOG_ERROR, "magic error\r\n");
		(*data_len) = 0;
		return -1;
	}
	total_len = header[1] + ((header[2] & 0x00FF)<<8);

	if (total_len%16 != 0 || total_len == 0 || total_len > (MAX_DATA_LEN*flash_block - 32))
	{
		ya_printf(C_LOG_ERROR, "r-flash len error\r\n");
		(*data_len) = 0;
		return -1;
	}

	buf = (uint8_t *)ya_hal_os_memory_alloc(total_len + 4);

	if(!buf)
		return -1;

	ret = ya_hal_flash_read(flash_addr, buf, total_len + 4);
	if(ret != 0)
	{
		ya_printf(C_LOG_ERROR, "read data error\r\n");
		(*data_len) = 0;
		ya_hal_os_memory_free(buf);
		return -1;
	}
	
	if(buf[3] != ya_flash_checksum(buf + 4, total_len))
	{
		ya_printf(C_LOG_ERROR, "read var checksum error\r\n");
		(*data_len) = 0;
		ya_hal_os_memory_free(buf);
		return -1;
	}

	//decode it
	if (flag_aes)
	{
		decyt_len = AES_ECB_PKCS5Padding_decrypt(flash_aes_key, buf + 4, total_len);
		if (decyt_len <= 0)
		{
			ya_printf(C_LOG_ERROR, "AES_ECB_PKCS5Padding_decrypt error\r\n");
			(*data_len) = 0;
			ya_hal_os_memory_free(buf);
			return -1;
		}
	} else
	{
		decyt_len = total_len;
	}
	
	if (decyt_len < (*data_len))
	{
		memcpy(data, buf + 4, decyt_len);
		(*data_len) = decyt_len;
	} else
	{
		memcpy(data, buf + 4, (*data_len));
	}

	ya_hal_os_memory_free(buf);	
	return 0;
}


int32_t ya_erase_flash(uint32_t flash_addr, uint32_t data_len)
{
	int32_t ret = -1; 
	ret = ya_hal_flash_erase(flash_addr, data_len);

	if(!ret)
		return -1;

	return 0;
}


