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

#ifndef _YA_OTA_HAL_H_
#define _YA_OTA_HAL_H_

#include "ya_config.h" 

#define MAX_OTA_SIZE		0xD7000     //Main Partition SIZE

#define HTTP_BUF_SIZE   				4096

/*���������ota�ļ�ǰ�������ֽڣ������ļ���У��*/
#if (YA_CHIP == YA_8710_CX)
#define HTTP_FILE_HEADER_LEN			32
#elif (YA_CHIP == YA_8710_BX)
#define HTTP_FILE_HEADER_LEN			8
#elif (YA_CHIP == YA_BL602)
#define HTTP_FILE_HEADER_LEN			512
#elif (YA_CHIP == YA_SV6x66)
#define HTTP_FILE_HEADER_LEN			84
#else
#define HTTP_FILE_HEADER_LEN			8
#endif

typedef enum
{
	YA_WIFI_OTA = 0,
	YA_MCU_OTA,
}ya_source_type_t;

typedef struct
{
	uint32_t header_len;
	uint32_t toatal_rece_len;
	uint32_t file_len;
	
	int32_t  body_read_len;
	uint32_t body_cur_pos;

	uint16_t body_flie_header_cur_len;
	uint8_t	 *body_file_header;

	uint8_t  body_file_header_enbable;

}http_file_para_t;

/*��У���ļ��ɹ���ִ����������������� */
void ya_hal_ota_done(void);

/*�Ƿ���Ҫ��ota�ļ��п�ͷ����ΪHTTP_FILE_HEADER_LEN �����ع����оʹ���flash�У���ЩоƬУ��ͨ������һ�����Ŵ洢��
 *���Ҫ�������棬�򷵻�1�����У��ͨ����Ŵ洢���򷵻�0.
*/	
uint32_t ya_get_file_header_writer_flash_enable(void);

/*�����ļ�ota�����ص�ַ
*/	
uint32_t ya_get_ota_download_addr(uint32_t *max_ota_size);


/*������ota�ļ���У���ļ��Ƿ�Ϸ�
* 0���ɹ�����0��ʧ��
*/
int32_t ya_verify_ota_checksum(uint32_t addr, uint32_t file_size, uint8_t *pre_file, uint8_t *file_md5, uint8_t *buf);

/*���8710bxоƬ��ֻ��Ҫ����0����
*/
int32_t ya_http_prefile_header_init(void);

/*���8710bxоƬ��ֻ��Ҫ����1����
*/
int32_t ya_http_prefile_header_handle(http_file_para_t *ya_http_file, int socket_id, uint8_t *buf);


/*�˺������8710bxоƬ��ֻ��Ҫ����0����
*/
int32_t ya_get_download_whole_file_finish(void);

/*�˺����ͷ�ota������hal����Դ��Ŀǰ��ţоƬ��Ҫʹ�ã�
*/
void ya_ota_hal_free(void);

/*����ota���������
* 0���ɹ�����0��ʧ��
*/
int32_t ya_http_ota_sector_erase(uint32_t address, uint32_t size, uint8_t type);

/*��ota����д����
* 0���ɹ�����0��ʧ��
*/
int32_t ya_http_ota_sector_write(uint32_t address ,uint32_t Length, uint8_t *data, uint8_t type);

/*������mcu�ļ��󣬶�mcu�ļ�����У��
* 0���ɹ�����0��ʧ��
*/
int32_t ya_verify_mcu_file_checksum(uint32_t addr, uint32_t file_size, uint8_t *file_md5, uint8_t *buf);

#endif

