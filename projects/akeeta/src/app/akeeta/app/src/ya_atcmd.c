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

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "ya_common.h"
#include "ya_hal_os.h"
#include "cJSON.h"
#include "ya_config.h"
#include "ya_atcmd.h"
#include "ya_common_func.h"
#include "infra_defs.h"
#include "ya_aes_md5.h"
#include "ya_flash.h"


typedef enum{
	CMD_RET_DATA_ERROR   = -1,
	CMD_RET_SUCCESS,
	CMD_RET_FAILURE,
}cmd_hanle_t;

#define RESP_HEAD 		"rsp:"
#define RESP_ERR 		"rsp:ERROR"
#define RESP_OK 		"rsp:OK"
#define GET_MAC_BACK 	"getmac"
#define RESP_NO_LICENSE "rsp:0,0,0"
#define OTA_URL_CN 		"http://device-open.oss-cn-shanghai.aliyuncs.com/index/top/"
#define OTA_URL_OVERSEA "http://oemapp-panel-us.s3.us-west-2.amazonaws.com/OtaFirmware/"
extern int32_t ya_set_enter_ota_test_mode(char *ota_test_url);
extern int32_t ya_set_exit_ota_test_mode(void);
#define CMD_BUFFER_SIZE  (12*1024)
static char *pcmd_buffer = NULL;
static uint32_t pcmd_buffer_index = 0;
static uint8_t md5_string[33] = {0};
static uint8_t get_md5_string_flag = 0;
static uint8_t enter_get_rssi_mode = 0;
#define LICENSE_LEN_MAX     (16*1024)
void set_enter_get_rssi_mode(void)
{
	enter_get_rssi_mode = 1;
}
void clear_enter_get_rssi_mode(void)
{
	enter_get_rssi_mode = 0;
}
uint8_t check_enter_get_rssi_mode(void)
{
	return enter_get_rssi_mode;
}

extern int32_t ya_set_factory_rssi_info(char *rssi_name);
typedef enum
{
	AWS_CERT = 0,
	ALI_CERT,
	UNKNOWN_CERT
}ya_cert_t;
uint8_t license_md5_string(uint8_t *md5_string)
{
	if(!md5_string)
	{	
		ya_printf(C_AT_CMD,"md5_string error\n");
		return C_ERROR;
	}
	if(get_md5_string_flag == 1)
		return C_OK;
	cJSON *license_key_US = NULL, *license_US_info = NULL, *license_key_CN = NULL, *license_CN_info = NULL;
	char *buf_US = NULL, *buf_CN = NULL, *buf_all = NULL;
	uint8_t return_ret = C_OK;
	license_key_US = cJSON_CreateObject();
	if(!license_key_US)
	{	
		ya_printf(C_AT_CMD,"cJSON_CreateObject license_key_US error\n");
		return_ret =  C_ERROR;
		goto exit;
	}
	license_US_info = cJSON_CreateObject();
	if(!license_US_info)
	{
		ya_printf(C_AT_CMD,"cJSON_CreateObject license_US_info error\n");
		return_ret =  C_ERROR;
		goto exit;
	}
	
	license_key_CN = cJSON_CreateObject();
	if(!license_key_CN)
	{	
		ya_printf(C_AT_CMD,"cJSON_CreateObject license_key_CN error\n");
		return_ret =  C_ERROR;
		goto exit;
	}
	license_CN_info = cJSON_CreateObject();
	if(!license_CN_info)
	{
		ya_printf(C_AT_CMD,"cJSON_CreateObject license_CN_info error\n");
		return_ret =  C_ERROR;
		goto exit;
	}

	cJSON_AddStringToObject(license_key_US, "server", "US");
	cJSON_AddItemToObject(license_key_US, "license", license_US_info);
	if((ya_get_client_cert() != NULL)&&(ya_aws_get_client_id() != NULL)&&(ya_get_private_key() != NULL)&&(ya_aws_get_thing_type() != NULL))
	{
		cJSON_AddStringToObject(license_US_info, "client_cert", ya_get_client_cert());
		cJSON_AddStringToObject(license_US_info, "client_id", ya_aws_get_client_id());
		cJSON_AddStringToObject(license_US_info, "private_key", ya_get_private_key());
		cJSON_AddStringToObject(license_US_info, "thing_type", ya_aws_get_thing_type());
	}
	else
	{	
		ya_printf(C_AT_CMD,"license_key_US not exit\n");
		return_ret =  C_ERROR;
		goto exit;
	}

	cJSON_AddStringToObject(license_key_CN, "server", "CN");
	cJSON_AddItemToObject(license_key_CN, "license", license_CN_info);

	char product_key[IOTX_PRODUCT_KEY_LEN + 1] = {0};
	uint16_t get_productKey_ret = ya_get_productKey(product_key);
	if(get_productKey_ret > 0)
	{
		cJSON_AddStringToObject(license_CN_info, "product_key", product_key);
	}
	else
	{	
		ya_printf(C_AT_CMD,"get_productKey_ret <= 0\n");
		return_ret =  C_ERROR;
		goto exit;
	}
	char device_id[YA_DEVICE_ID_LEN + 1] = {0};
	uint16_t get_deviceID_ret = ya_get_deviceID(device_id);
	if(get_deviceID_ret > 0)
	{
		cJSON_AddStringToObject(license_CN_info, "device_id", (char *)device_id);
	}
	else
	{	
		ya_printf(C_AT_CMD,"get_deviceID_ret <= 0\n");
		return_ret =  C_ERROR;
		goto exit;
	}

	char device_secret[YA_DEVICE_SECRET_LEN + 1] = {0};
	uint16_t get_device_secret_ret = ya_get_deviceSecret(device_secret);
	if(get_device_secret_ret > 0)
	{
		cJSON_AddStringToObject(license_CN_info, "device_secret", device_secret);
	}	
	else
	{	
		ya_printf(C_AT_CMD,"get_device_secret_ret <= 0\n");
		return_ret =  C_ERROR;
		goto exit;
	}

	buf_US = cJSON_PrintUnformatted(license_key_US);

	buf_CN = cJSON_PrintUnformatted(license_key_CN);

	buf_all = (char *)ya_hal_os_memory_alloc(strlen(buf_CN)+strlen(buf_US)+1);
	if(!buf_all)
	{
		ya_printf(C_AT_CMD,"ya_hal_os_memory_alloc error\n");
		return_ret =  C_ERROR;
		goto exit;
	}
	memset(buf_all,0,strlen(buf_CN)+strlen(buf_US)+1);
	memcpy(buf_all,buf_CN,strlen(buf_CN));
	memcpy(buf_all+strlen(buf_CN),buf_US,strlen(buf_US));
	buf_all[strlen(buf_CN)+strlen(buf_US)] = '\0';
	uint8_t license_md5[16] = {0};
	ya_mbedtls_md5((uint8_t *)buf_all,license_md5,strlen(buf_CN)+strlen(buf_US));
	HexArrayToString(license_md5, 16, (char *)md5_string);	
	get_md5_string_flag = 1;
exit:
	if(license_key_US)
	{
		cJSON_Delete(license_key_US);
		license_key_US = NULL;
	}
	if(license_key_CN)
	{
		cJSON_Delete(license_key_CN);
		license_key_CN = NULL;
	}
	if(buf_US)
	{
		ya_hal_os_memory_free(buf_US);
		buf_US = NULL;
	}
	if(buf_CN)
	{
		ya_hal_os_memory_free(buf_CN);
		buf_CN = NULL;
	}
	if(buf_all)
	{
		ya_hal_os_memory_free(buf_all);
		buf_all = NULL;
	}
	return return_ret;
}

static int at_cmd_hex2num(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	return -1;
}
uint8_t at_cmd_LOG_FLAG = 1;

void at_cmd_log_ON(void)
{
	at_cmd_LOG_FLAG = 1;
}
void at_cmd_log_OFF(void)
{
	at_cmd_LOG_FLAG = 0;
}

void at_response(char * str)
{
	ya_printf(C_AT_CMD,"%s\n", str);
}
static uint16_t crc_check(uint8_t *puchMsg, uint16_t usDataLen)
{
	uint16_t wCRCin = 0xFFFF;
	uint16_t wCPoly = 0x1021;
	uint8_t wChar = 0;
	int i = 0;

	while(usDataLen--) 
	{
		wChar = *(puchMsg++);
		wCRCin ^= (wChar << 8);
		for(i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
		else
			wCRCin = wCRCin << 1;
		}
	}
	return (wCRCin) ;
}
static char *mystrtok(char *s,const char *delim) 
{
    static char *last;
    char *tok;
    char *ucdelim;
    char *spanp;
    int c,sc;
    if (s == NULL && (s = last) == NULL)
        return NULL;
    int found = 0;
    cont:
    c=*s++;
    for (spanp = (char *)delim;(sc = *spanp++) != 0;)
    {
        if (c == sc)
            goto cont;
    }
    if (c == 0) 
    {
        last = NULL;
        return NULL;
    }

    tok = s-1;
    while (!found && *s != '\0') 
    {
        ucdelim = (char *) delim;
        while (*ucdelim) 
        {
            if (*s == *ucdelim) 
            {
                found = 1;
                *s = '\0';
                last = s + 1;
                break;
            }
            ucdelim++;
        }
        if (!found)
        {
            s++;
            if(*s=='\0')
                last = NULL;
        }
    }

    return tok;
}

uint8_t ya_at_config_flag = 0;

int ya_data_atcmd_handler(void)
{
	int32_t at_cmd_ret = CMD_RET_DATA_ERROR;
	uint8_t i = 0;
	uint16_t json_len = 0;
	uint16_t arg1_len = 0;
	uint16_t arg2_len = 0;
	uint16_t arg3_len = 0;
	char *token = NULL;
	uint32_t crc16_arg = 0;
	uint32_t crc16_cal = 0;
	cJSON *JSObject = NULL;
	uint8_t mac[6]={0};
	char tmp_str[16]={0};
	char str_buf[48]={0};
	uint16_t crc_16;
	uint8_t *license_addr = NULL;
	
	if((strcmp(pcmd_buffer, "getmac") == 0))
	{
		at_cmd_log_OFF();
		memset(mac,0,sizeof(mac));
		memset(tmp_str,0,sizeof(tmp_str));
		memset(str_buf,0,sizeof(str_buf));
		ya_hal_wlan_get_mac_address(mac);

		snprintf(tmp_str, sizeof(tmp_str), "%02x%02x%02x%02x%02x%02x", mac[0],mac[1],
												mac[2],mac[3],mac[4],mac[5]);

		crc_16 = crc_check(mac, 6);

		snprintf(str_buf, sizeof(str_buf), "%s%s%04x", RESP_HEAD, tmp_str, crc_16);
		at_response(GET_MAC_BACK);
		at_response(str_buf);

		at_cmd_ret = CMD_RET_SUCCESS; 
	}	
	else if((strcmp(pcmd_buffer, "getversion") == 0))
	{
		at_cmd_log_OFF();
		memset(str_buf,0,sizeof(str_buf));
		strcpy(str_buf, RESP_HEAD);
		ya_get_ver_string(str_buf + strlen(RESP_HEAD));
		at_response(str_buf);
		at_cmd_ret = CMD_RET_SUCCESS; 
	}
	else if((strcmp(pcmd_buffer, "yasoftap") == 0))
	{
		at_response(RESP_OK);
		ya_set_ap_mode();
		at_cmd_ret = CMD_RET_SUCCESS; 
	}
	else if((strcmp(pcmd_buffer, "yasniffer") == 0))
	{
		at_response(RESP_OK);
		ya_set_sniffer_mode();
		at_cmd_ret = CMD_RET_SUCCESS; 
	}
	else if((strcmp(pcmd_buffer, "yable") == 0))
	{
		at_response(RESP_OK);
		ya_set_ble_config_mode();
		at_cmd_ret = CMD_RET_SUCCESS; 
	}
	else if((strcmp(pcmd_buffer, "yareset") == 0))
	{
		at_response(RESP_OK);
		ya_hal_sys_reboot();
		at_cmd_ret = CMD_RET_SUCCESS; 
	}
	else if((strcmp(pcmd_buffer, "yafac") == 0))
	{
		at_response(RESP_OK);
		ya_reset_module_to_factory();
		at_cmd_ret = CMD_RET_SUCCESS; 
	}
	else if(strcmp(pcmd_buffer, "getlicense") == 0)
	{
		ya_read_license_from_flash(2); 
		int ret_us = ya_check_us_license_exit();
		int ret_cn = ya_check_cn_license_exit();

		at_cmd_ret = CMD_RET_SUCCESS; 
		if (ret_us == 0 && ret_cn == 0)
		{
			char product_key[IOTX_PRODUCT_KEY_LEN + 1] = {0};
			char device_ID[YA_DEVICE_ID_LEN + 1] = {0};
			uint16_t get_productKey_ret = ya_get_productKey(product_key);
			if(get_productKey_ret > 0)
			{
				uint8_t response_buf[IOTX_PRODUCT_KEY_LEN + 1 +YA_DEVICE_ID_LEN + 1 + 5 + 34] = {0};
				memcpy(response_buf,"rsp:",strlen("rsp:"));
				memcpy(response_buf+4,product_key,get_productKey_ret);
				memcpy(response_buf+4+get_productKey_ret,",",1);
				uint16_t get_deviceID_ret = ya_get_deviceID(device_ID);
				if(get_deviceID_ret > 0)
				{
					memcpy(response_buf+4+get_productKey_ret+1,device_ID,get_deviceID_ret);
					uint8_t get_license_md5_ret = license_md5_string(md5_string);
					if(get_license_md5_ret == C_OK)
					{
						memcpy(response_buf+4+get_productKey_ret+1+get_deviceID_ret,",",1);
						memcpy(response_buf+4+get_productKey_ret+1+get_deviceID_ret+1,md5_string,strlen((char *)md5_string));
						at_response((char *)response_buf);
						goto END;
					}
					else
					{
						ya_printf(C_AT_CMD,"get_license_md5_ret error \r\n");
						at_response(RESP_NO_LICENSE);
						goto END;
					}					
				}
				else
				{
					ya_printf(C_AT_CMD,"get_productKey_ret error \r\n");
					at_response(RESP_NO_LICENSE);
					goto END;
				}							
			}
			else
			{
				ya_printf(C_AT_CMD,"get_deviceID_ret error \r\n");
				at_response(RESP_NO_LICENSE);
				goto END;
			}	
		}
		else
		{
			ya_printf(C_AT_CMD,"license not exit \r\n");
			at_response(RESP_NO_LICENSE);
			goto END;
		}		
	}
	else if(strcmp(pcmd_buffer, "ya_ota_exit") == 0)
	{
		ya_set_exit_ota_test_mode();
	}
	else if(strstr(pcmd_buffer, "getrssi "))
	{
		at_cmd_ret = CMD_RET_SUCCESS; 
		
		if(check_enter_get_rssi_mode())
		{
			ya_printf(C_AT_CMD,"enter_get_rssi_mode \r\n");
			at_cmd_ret = CMD_RET_FAILURE;
			goto END;
		}
		uint8_t getrssi_name_len = strlen(pcmd_buffer)-strlen("getrssi ");
		if(getrssi_name_len <= 0 || getrssi_name_len > 32)
		{
			ya_printf(C_AT_CMD,"rssi_name_len error \r\n");
			at_cmd_ret = CMD_RET_FAILURE;
			goto END;
		}
		set_enter_get_rssi_mode();
		char getrssi_name[33] = {0};
		memcpy(getrssi_name,pcmd_buffer+strlen("getrssi "),strlen(pcmd_buffer)-strlen("getrssi "));
		ya_set_factory_rssi_info(getrssi_name);
	}
	else if (strstr(pcmd_buffer, "ya_write_cert") || strstr(pcmd_buffer, "setmac") || strstr(pcmd_buffer, "ya_ota_test") )
	{
		token = mystrtok(pcmd_buffer, " ");
		if(token && (strcmp(token, "ya_write_cert") == 0))
		{
			arg1_len = strlen("ya_write_cert");
			token = mystrtok(NULL, " ");
			if(token != NULL)
			{
				arg2_len = strlen(token);
				for(i=0;i<strlen(token);i++)
					json_len += at_cmd_hex2num(token[i])<<(4*(strlen(token)-i-1));

				ya_printf(C_AT_CMD,"json_len = 0x%x\r\n", json_len);
				if(json_len > 0 && json_len < CMD_BUFFER_SIZE)
				{
					token = mystrtok(NULL, " ");
					arg3_len = strlen(token);
					sscanf(token,"%x",&crc16_arg);
					if(crc16_arg)
					{
						license_addr = (uint8_t *)pcmd_buffer + arg1_len + arg2_len + arg3_len + 3;
					
						crc16_cal = crc_check(license_addr, json_len);
						ya_printf(C_AT_CMD,"crc16_cal==%x,crc16_arg==%x\n",crc16_cal,crc16_arg);
						if (crc16_cal != crc16_arg)
						{
							ya_printf(C_AT_CMD,"crc16_cal error \r\n");
							at_cmd_ret = CMD_RET_FAILURE;
							goto END;
						}
						
						at_cmd_ret = ya_write_flash(YA_LICENSE_DEVICE_ADDR, license_addr, json_len, 3, FLASH_AES_ENABLE);

						if(at_cmd_ret != CMD_RET_SUCCESS)
						{
							ya_printf(C_AT_CMD,"ya_hal_flash_write error \r\n");
							at_cmd_ret = CMD_RET_FAILURE;
							goto END;
						}	
						ya_delay(20);
						at_response(RESP_OK);
						at_cmd_ret = CMD_RET_SUCCESS;
					}
					else
					{
						ya_printf(C_AT_CMD,"crc16 format error \r\n");
						at_cmd_ret = CMD_RET_FAILURE;
						goto END;
					}	
				}
				else
				{
					ya_printf(C_AT_CMD,"json_len format error \r\n");
					at_cmd_ret = CMD_RET_FAILURE;
					goto END;
				}	
			}
			else
			{
				ya_printf(C_AT_CMD,"cmd format error \r\n");
				at_cmd_ret = CMD_RET_FAILURE;
				goto END;
			}					
		}
		else if(token && (strcmp(token, "ya_ota_test") == 0))
		{
			at_cmd_ret = CMD_RET_SUCCESS; 
			token = mystrtok(NULL, " ");
			if(token != NULL)
			{
				char ota_name[100]={0};
				memcpy(ota_name,token,strlen(token));
				ya_printf(C_AT_CMD,"ota_name==%s\r\n",ota_name);
				token = mystrtok(NULL, " ");
				if(token != NULL)
				{
					char ota_size[20]={0};
					memcpy(ota_size,token,strlen(token));
					ya_printf(C_AT_CMD,"ota_size==%s\r\n",ota_size);
					token = mystrtok(NULL, " ");
					if(token != NULL)
					{
						char ota_ver_new[100]={0};
						memcpy(ota_ver_new,token,strlen(token));
						ya_printf(C_AT_CMD,"ota_ver_new==%s\r\n",ota_ver_new);
						token = mystrtok(NULL, " ");
						if(token != NULL)
						{
							uint8_t cloud_type = atoi(token);
							ya_printf(C_AT_CMD,"cloud_type==%d\r\n",cloud_type);
							if(cloud_type > 1)
							{
								ya_printf(C_AT_CMD,"ya_ota_test cmd format error %s,%d\r\n",__FUNCTION__,__LINE__);
								at_cmd_ret = CMD_RET_FAILURE;
								goto END;
							}	
							token = mystrtok(NULL, " ");
							if(token != NULL)
							{
								char ota_md5[33]={0};
								memcpy(ota_md5,token,strlen(token));
								ya_printf(C_AT_CMD,"ota_md5==%s\r\n",ota_md5);
								cJSON *ota_cmd = NULL, *ota_cmd_data = NULL;
								ota_cmd = cJSON_CreateObject();
								if(!ota_cmd)
								{	
									ya_printf(C_AT_CMD,"cJSON_CreateObject ota_cmd error\n");
									at_cmd_ret = CMD_RET_FAILURE;
									goto END;
								}
								ota_cmd_data = cJSON_CreateObject();
								if(!ota_cmd_data)
								{
									ya_printf(C_AT_CMD,"cJSON_CreateObject ota_cmd_data error\n");
									at_cmd_ret = CMD_RET_FAILURE;
									goto END;
								}
								cJSON_AddItemToObject(ota_cmd, "data", ota_cmd_data);	
								cJSON_AddStringToObject(ota_cmd_data, "failRetryInternal", "0");
								cJSON_AddStringToObject(ota_cmd_data, "failRetryTimes", "3");
								cJSON_AddStringToObject(ota_cmd_data, "firmwareType", "module");
								cJSON_AddStringToObject(ota_cmd_data, "md5sum", ota_md5);
								cJSON_AddStringToObject(ota_cmd_data, "size", ota_size);
								cJSON_AddStringToObject(ota_cmd_data, "type", "wifi");

								char ota_url[200]={0};
								if(cloud_type == 0)//CN
								{
									memcpy(ota_url,OTA_URL_CN,strlen(OTA_URL_CN));
									memcpy(ota_url+strlen(OTA_URL_CN),ota_name,strlen(ota_name));
								}
								else//OVERSEA
								{
									memcpy(ota_url,OTA_URL_OVERSEA,strlen(OTA_URL_OVERSEA));
									memcpy(ota_url+strlen(OTA_URL_OVERSEA),ota_name,strlen(ota_name));
								}
								cJSON_AddStringToObject(ota_cmd_data, "url", ota_url);
								cJSON_AddStringToObject(ota_cmd_data, "version", ota_ver_new);
								cJSON_AddStringToObject(ota_cmd, "method", "thing.service.device.upgrade");
								char *ota_cmd_string = cJSON_PrintUnformatted(ota_cmd);
								ya_set_enter_ota_test_mode(ota_cmd_string);
							}
						}
						else
						{
							ya_printf(C_AT_CMD,"ya_ota_test cmd format error %s,%d\r\n",__FUNCTION__,__LINE__);
							at_cmd_ret = CMD_RET_FAILURE;
							goto END;
						}
					}
					else
					{
						ya_printf(C_AT_CMD,"ya_ota_test cmd format error %s,%d\r\n",__FUNCTION__,__LINE__);
						at_cmd_ret = CMD_RET_FAILURE;
						goto END;
					}
				}
				else
				{
					ya_printf(C_AT_CMD,"ya_ota_test cmd format error %s,%d\r\n",__FUNCTION__,__LINE__);
					at_cmd_ret = CMD_RET_FAILURE;
					goto END;
				}
			}
			else
			{
				ya_printf(C_AT_CMD,"ya_ota_test cmd format error %s,%d\r\n",__FUNCTION__,__LINE__);
				at_cmd_ret = CMD_RET_FAILURE;
				goto END;
			}		
		}
		else if(token && (strcmp(token, "setmac") == 0))
		{
			token = mystrtok(NULL, " ");
			if(token != NULL)
			{
				ya_printf(C_AT_CMD,"\r\n");
				for (i=0; i<6; i++)
				{
					mac[i] = at_cmd_hex2num(token[i*2]) * 0x10 + at_cmd_hex2num(token[i*2+1]);
					ya_printf(C_AT_CMD,"%02x ",mac[i]);
				}
				ya_printf(C_AT_CMD,"\r\n");
				crc16_cal = crc_check(mac, 6);
				if(crc16_cal)
				{
					token = mystrtok(NULL, "\0");
					if(token != NULL)
						sscanf(token,"%x",&crc16_arg);
					else
					{
						ya_printf(C_AT_CMD,"get crc16_cal error \r\n");
						at_cmd_ret = CMD_RET_FAILURE;
						goto END;
					}	
				}
				else
				{
					ya_printf(C_AT_CMD,"cal crc16 error \r\n");
					at_cmd_ret = CMD_RET_FAILURE;
					goto END;
				}	
				ya_printf(C_AT_CMD,"crc16_arg===%x, crc16_cal===%x\r\n",crc16_arg,crc16_cal);
				if (crc16_arg != crc16_cal)
				{
					at_cmd_ret = CMD_RET_FAILURE;
					goto END;
				}	
				if(0 == ya_hal_wlan_set_mac_address(mac))
				{
					at_response(RESP_OK);
					at_cmd_ret = CMD_RET_SUCCESS;
				} else
				{
					ya_printf(C_AT_CMD,"ya_hal_wlan_set_mac_address error \r\n");
					at_cmd_ret = CMD_RET_FAILURE;
					goto END;
				}	
			}
			else
			{
				ya_printf(C_AT_CMD,"cmd format error \r\n");
				at_cmd_ret = CMD_RET_FAILURE;
				goto END;
			}	
		}
		else
		{
			at_cmd_ret = CMD_RET_DATA_ERROR;
			goto END;
		}			
	}
END:
	if (JSObject)
	{
		cJSON_Delete(JSObject);
		JSObject = NULL;
	}

	if (at_cmd_ret == CMD_RET_FAILURE)
		at_response(RESP_ERR);
	
	return at_cmd_ret;
}

uint8_t ya_at_frame_get = 0;

void at_cmd_thread(void *param)
{

	while(1)
	{
		if (ya_at_frame_get)
		{
			ya_data_atcmd_handler();
			if (pcmd_buffer)
			{
				ya_hal_os_memory_free(pcmd_buffer);
				pcmd_buffer = NULL;
			}
			ya_at_frame_get = 0;
		}

		ya_delay(20);
	}
}

void at_cmd_thread_create(void)
{
	int32_t ret = 0;
	ret = ya_hal_os_thread_create(NULL, "at_cmd_thread", at_cmd_thread, 0, (2*1024), 5);
	if(ret != C_OK)
	{
		ya_printf(C_AT_CMD, "create at_cmd_thread error\n");
	}			
}

int ya_atcmd_handler(char *cmd)
{

	#ifdef UART_POLLING_DATA
	static uint8_t init_ya_at_flag = 0;

	if (ya_at_frame_get || !cmd)
		return CMD_RET_DATA_ERROR;

	if (!init_ya_at_flag)
	{
		if (cmd[0] == '\r' || cmd[0] == '\n')
			return CMD_RET_DATA_ERROR;

		at_cmd_thread_create();
		init_ya_at_flag = 1;
	}

	if (pcmd_buffer == NULL)
	{
		pcmd_buffer = (char *)ya_hal_os_memory_alloc(CMD_BUFFER_SIZE);
		pcmd_buffer_index = 0;
		if (!pcmd_buffer)
		{
			ya_printf(C_AT_CMD,"pcmd_buffer malloc fail\r\n");
			return CMD_RET_DATA_ERROR;
		}
	}
	
	pcmd_buffer[pcmd_buffer_index++] = *cmd;

	if (pcmd_buffer[pcmd_buffer_index - 1] == '\r' || pcmd_buffer[pcmd_buffer_index - 1] == '\n')
	{
		pcmd_buffer[pcmd_buffer_index - 1] = 0;
		
		if (strncmp (pcmd_buffer, "getmac", strlen("getmac")) == 0
			|| strncmp (pcmd_buffer, "setmac", strlen("setmac")) == 0
			|| strncmp (pcmd_buffer, "getrssi", strlen("getrssi")) == 0
			|| strncmp (pcmd_buffer, "getversion", strlen("getversion")) == 0)
		{
			ya_at_config_flag = 1;
		}
		
		ya_at_frame_get = 1;
		pcmd_buffer_index = 0;
	}

	if (pcmd_buffer_index >= CMD_BUFFER_SIZE)
		pcmd_buffer_index = 0;

	if (ya_at_config_flag)
		return 0;

	return CMD_RET_DATA_ERROR;

	#else

	if (!cmd)
		return CMD_RET_DATA_ERROR;

	pcmd_buffer = cmd;
	return ya_data_atcmd_handler();
	#endif
}


