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
#include <bsp.h>
#include "flash.h"
#include "ya_common.h"

#define AKEETA_SECTOR_SIZE  		0x1000
#define AKEETA_FLASH_PAGE_SIZE 		0x100
#define AKEETA_FLASH_BASE_ADDR  	0x30000000
#define ROUND_DOWN(a,b) (((a) / (b)) * (b))
#define MIN(a,b)        (((a) < (b)) ? (a) : (b))

int32_t ya_hal_flash_read(uint32_t flash_addr, uint8_t *data, uint32_t data_len)
{
	if(NULL == data) 
	{
		return -1;
	}

	uint8_t *src = (uint8_t *)(flash_addr);
	uint8_t *dstBuf = (uint8_t *)(data);

	OS_EnterCritical();
	memcpy(dstBuf,(void *)(AKEETA_FLASH_BASE_ADDR+src),data_len);
	OS_ExitCritical();
	return 0;
}

int32_t ya_hal_flash_erase(uint32_t flash_addr, uint32_t size)
{
	int remaining = size;
	uint32_t  dst_addr = flash_addr;

	OS_EnterCritical();
	do {
		uint32_t fl_addr = ROUND_DOWN(dst_addr, AKEETA_SECTOR_SIZE);
		int len = MIN(AKEETA_SECTOR_SIZE , remaining);

		flash_sector_erase((unsigned int)fl_addr);

		dst_addr += len;
		remaining -= len;
	}while (remaining > 0);
	OS_ExitCritical();

	return 0;
}

int32_t ya_hal_flash_write(uint32_t flash_addr, uint8_t *data, uint32_t data_len)
{
	if(NULL == data) 
	{
		return -1;
	}

	int remaining = data_len;
	uint8_t * src_addr = (uint8_t *) data;
	uint32_t  dst_addr = flash_addr; 

	uint8_t * page_cache = NULL;

	ya_hal_flash_erase(flash_addr,data_len);
	page_cache = (uint8_t *)OS_MemAlloc(AKEETA_FLASH_PAGE_SIZE);
	if (page_cache == NULL) 
	{
		return -1;
	}
	memset(page_cache, 0, AKEETA_FLASH_PAGE_SIZE);

	do {
		uint32_t fl_addr = ROUND_DOWN(dst_addr, AKEETA_FLASH_PAGE_SIZE);
		int fl_offset = dst_addr - fl_addr;
		int len = MIN(AKEETA_FLASH_PAGE_SIZE - fl_offset, remaining);
		
		memcpy(page_cache, (void *) (AKEETA_FLASH_BASE_ADDR+fl_addr), AKEETA_FLASH_PAGE_SIZE); 
		
		memcpy((uint8_t *)page_cache + fl_offset, src_addr, len);

		OS_EnterCritical();
		flash_page_program(fl_addr, AKEETA_FLASH_PAGE_SIZE, page_cache);
		OS_ExitCritical();
		
		dst_addr += len;
		src_addr += len;
		remaining -= len;

	}while (remaining > 0);

	OS_MemFree(page_cache);
	return 0;
}
