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


#ifndef _YA_FLASH_H_
#define _YA_FLASH_H_


typedef enum
{
	FLASH_AES_DISABLE = 0,
	FLASH_AES_ENABLE,
}flash_aes_t;

uint8_t ya_flash_checksum(uint8_t *data, uint32_t data_len);

int32_t ya_write_flash(uint32_t flash_addr, uint8_t *data, uint16_t data_len, uint8_t flash_block, uint8_t flag_aes);

int32_t ya_read_flash_with_var_len(uint32_t flash_addr, uint8_t *data, uint16_t *data_len, uint8_t flash_block, uint8_t flag_aes);

int32_t ya_erase_flash(uint32_t flash_addr, uint32_t data_len);

int32_t ya_init_flash_handle(void);

#endif


