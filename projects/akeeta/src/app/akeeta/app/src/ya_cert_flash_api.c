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
#include "ya_config.h"
#include "mbedtls/ssl.h"
#include "mbedtls/platform.h"
#include "ya_emq_cloud.h"
#include "cJSON.h"
#include "ya_aes_md5.h"

extern uint8_t flash_aes_key[16];

char *aws_certificateBuff = NULL;    //device cert
char *aws_privateKeyBuff = NULL;     //device rsa
char *aws_client_id = NULL; 			//device client id
char *aws_thing_type = NULL; 		//device thing type

int ya_aws_para_free(void)
{
	if (aws_certificateBuff)
	{
		ya_hal_os_memory_free(aws_certificateBuff);
		aws_certificateBuff = NULL;
	}

	if (aws_privateKeyBuff)
	{
		ya_hal_os_memory_free(aws_privateKeyBuff);
		aws_privateKeyBuff = NULL;
	}

	if (aws_client_id)
	{
		ya_hal_os_memory_free(aws_client_id);
		aws_client_id = NULL;
	}

	if (aws_thing_type)
	{
		ya_hal_os_memory_free(aws_thing_type);
		aws_thing_type = NULL;
	}

	return 0;
}

char *ya_get_private_key(void)
{
	return aws_privateKeyBuff;
}

char *ya_get_client_cert(void)
{
	return aws_certificateBuff;
}

char *ya_aws_get_client_id(void)
{
	#if (!EMQ_ENABLE)
	return aws_client_id;
	#else
	return TEST_EMQ_CLIENT_ID;
	#endif
}

char *ya_aws_get_thing_type(void)
{
	#if (!EMQ_ENABLE)
	return aws_thing_type;
	#else
	return TEST_EMQ_THING_TYPE;
	#endif
}

#if (EMQ_ENABLE)
char *ya_emq_get_client_id(void)
{
	return TEST_EMQ_CLIENT_ID;
}

char *ya_emq_get_thing_type(void)
{
	return TEST_EMQ_THING_TYPE;
}
#endif

char *aliyun_productkey = NULL;    
char *aliyun_deviceid = NULL;     
char *aliyun_productsecret = NULL; 	

int ya_get_productKey(char product_key[YA_PRODUCT_KEY_LEN + 1])
{
	if (aliyun_productkey)
	{
		strcpy(product_key, aliyun_productkey);
		return strlen(product_key);
	} else
	{
		memset(product_key, 0, YA_PRODUCT_KEY_LEN + 1);
		return 0;
	}
}

int ya_get_deviceID(char device_id[YA_DEVICE_ID_LEN + 1])
{
	if (aliyun_deviceid)
	{
		strcpy(device_id, aliyun_deviceid);
		return strlen(device_id);
	} else
	{
		memset(device_id, 0, YA_DEVICE_ID_LEN + 1);
		return 0;
	}
}

int ya_get_deviceSecret(char device_secret[YA_DEVICE_SECRET_LEN + 1])
{
	if (aliyun_productsecret)
	{
		strcpy(device_secret, aliyun_productsecret);
		return strlen(device_secret);
	} else 
	{
		memset(device_secret, 0, YA_DEVICE_SECRET_LEN + 1);
		return 0;
	}
}

int ya_aliyun_para_free(void)
{
	if (aliyun_productkey)
	{
		ya_hal_os_memory_free(aliyun_productkey);
		aliyun_productkey = NULL;
	}

	if (aliyun_deviceid)
	{
		ya_hal_os_memory_free(aliyun_deviceid);
		aliyun_deviceid = NULL;
	}

	if (aliyun_productsecret)
	{
		ya_hal_os_memory_free(aliyun_productsecret);
		aliyun_productsecret = NULL;
	}

	return 0;
}


int ya_check_us_license_exit(void)
{
	if (aws_certificateBuff == NULL || aws_privateKeyBuff == NULL || 
		aws_client_id == NULL || aws_thing_type == NULL)
	{
		ya_printf(C_LOG_ERROR, "no ya_check_us_license_exit\r\n");
		return -1;
	}
	return 0;

}

int ya_check_cn_license_exit(void)
{
	if (aliyun_productkey == NULL || aliyun_deviceid == NULL || aliyun_productsecret == NULL)
	{
		ya_printf(C_LOG_ERROR, "no ya_check_cn_license_exit\r\n");
		return -1;
	}
	return 0;
}


int ya_get_cloud_type(char *cloud_type)
{
	if (ya_get_productKey(cloud_type) == 0)
	{
		if (aws_thing_type)
		{
			strcpy(cloud_type, aws_thing_type);
			return 0;
		}

		return -1;
	}

	return 0;
}

int ya_get_cloud_device_id(char *device_id)
{
	if (ya_get_deviceID(device_id) == 0)
	{
		if (aws_client_id)
		{
			strcpy(device_id, aws_client_id);
			return 0;
		}

		return -1;
	}

	return 0;	
}


int ya_read_license_from_flash(uint8_t domain_check)
{
	uint8_t header[4];	
	int32_t ret = -1;
	uint16_t total_len = 0, decyt_len = 0;
	
	cJSON *license_ojb = NULL, *license_CN = NULL, *license_OVERSEA = NULL, *sub_object = NULL;
	char *license_addr = NULL;
	
	ret = ya_hal_flash_read(YA_LICENSE_DEVICE_ADDR, header, 4);
	if(ret != 0)
	{
		ya_printf(C_LOG_ERROR, "read header error\r\n");
		return -1;
	}

	ya_printf(C_LOG_INFO, "r-v-header %02x, %02x, %02x, %02x\r\n", header[0], header[1], header[2], header[3]);
	
	if(header[0] != 0xAA)
	{
		ya_printf(C_LOG_ERROR, "magic error\r\n");
		return -1;
	}

	total_len = header[1] + ((header[2] & 0x00FF)<<8);

	if (total_len%16 != 0 || total_len == 0 || total_len > MAX_LICENSE_LEN)
	{
		ya_printf(C_LOG_ERROR, "r-flash len error\r\n");
		return -1;
	}

	license_addr = (char *)ya_hal_os_memory_alloc(total_len + 5);
	
	if(!license_addr)
		return -1;

	ret = ya_hal_flash_read(YA_LICENSE_DEVICE_ADDR, (uint8_t *)license_addr, total_len + 4);
	if(ret != 0)
	{
		ya_printf(C_LOG_ERROR, "read data error\r\n");
		ret = C_ERROR;
		goto err;
	}

	decyt_len = AES_ECB_PKCS5Padding_decrypt(flash_aes_key, (uint8_t *)license_addr + 4, total_len);
	if (decyt_len <= 0)
	{
		ya_printf(C_LOG_ERROR, "AES_ECB_PKCS5Padding_decrypt error\r\n");
		ret = C_ERROR;
		goto err;
	}

	license_addr[decyt_len + 4] = '\0';

	license_ojb = cJSON_Parse(license_addr+4);
	if(!license_ojb)
	{
		ya_printf(C_LOG_ERROR, "cJSON_Parse license error\n");
		ret = C_ERROR;
		goto err;
	}

	if (domain_check == 0 || domain_check == 2)
	{
		license_CN = cJSON_GetObjectItem(license_ojb, "license_CN");
		if(!license_CN)
		{
			ya_printf(C_LOG_ERROR, "license_CN error\n");
			ret = C_ERROR;
			goto err;
		}
		
		sub_object = cJSON_GetObjectItem(license_CN, "product_key");
		if(!sub_object || strlen(sub_object->valuestring) > YA_PRODUCT_KEY_LEN)
		{
			ret = C_ERROR;
			ya_printf(C_LOG_ERROR, "cJSON_GetObjectItem product_key error\n");
			goto err;		
		}
		
		if (aliyun_productkey == NULL)
		{
			aliyun_productkey = (char *)ya_hal_os_memory_alloc(strlen(sub_object->valuestring) + 1);
			if(!aliyun_productkey) 
			{
				ya_printf(C_LOG_ERROR, "malloc aliyun_productkey error\n");
				ret = C_ERROR;
				goto err;
			}	
		}	
		memset(aliyun_productkey,0,(strlen(sub_object->valuestring) + 1));
		memcpy(aliyun_productkey, sub_object->valuestring, strlen(sub_object->valuestring));

		sub_object = cJSON_GetObjectItem(license_CN, "device_id");
		if(!sub_object || strlen(sub_object->valuestring) > YA_DEVICE_ID_LEN)
		{
			ret = C_ERROR;
			ya_printf(C_LOG_ERROR, "cJSON_GetObjectItem device_id error\n");
			goto err;		
		}

		if (aliyun_deviceid == NULL)
		{
			aliyun_deviceid = (char *)ya_hal_os_memory_alloc(strlen(sub_object->valuestring) + 1);
			if(!aliyun_deviceid) 
			{
				ya_printf(C_LOG_ERROR, "malloc aliyun_deviceid error\n");
				ret = C_ERROR;
				goto err;
			}	
		}	
		memset(aliyun_deviceid,0,(strlen(sub_object->valuestring) + 1));
		memcpy(aliyun_deviceid, sub_object->valuestring, strlen(sub_object->valuestring));

		sub_object= cJSON_GetObjectItem(license_CN, "device_secret");
		if(!sub_object || strlen(sub_object->valuestring) > YA_DEVICE_SECRET_LEN)
		{
			ret = C_ERROR;
			ya_printf(C_LOG_ERROR, "cJSON_GetObjectItem device_secret error\n");
			goto err;		
		}

		if (aliyun_productsecret == NULL)
		{
			aliyun_productsecret = (char *)ya_hal_os_memory_alloc(strlen(sub_object->valuestring) + 1);
			if(!aliyun_productsecret) 
			{
				ya_printf(C_LOG_ERROR, "malloc aliyun_productsecret error\n");
				ret = C_ERROR;
				goto err;
			}	
		}	
		memset(aliyun_productsecret,0,(strlen(sub_object->valuestring) + 1));
		memcpy(aliyun_productsecret, sub_object->valuestring, strlen(sub_object->valuestring));

		ya_printf(C_LOG_INFO, "client_id: %s\r\n", aliyun_deviceid);
	}

	if (domain_check == 1 || domain_check == 2)
	{
		license_OVERSEA = cJSON_GetObjectItem(license_ojb, "license_oversea");
		if(!license_OVERSEA)
		{
			ya_printf(C_LOG_ERROR, "license_OVERSEA error\n");
			ret = C_ERROR;
			goto err;
		}

		sub_object = cJSON_GetObjectItem(license_OVERSEA, "client_cert");
		if(!sub_object)
		{
			ret = C_ERROR;
			ya_printf(C_LOG_ERROR, "cJSON_GetObjectItem client_cert error\n");
			goto err;		
		}

		if (aws_certificateBuff == NULL)
		{
			aws_certificateBuff = (char *)ya_hal_os_memory_alloc(strlen(sub_object->valuestring) + 1);
			if(!aws_certificateBuff) 
			{
				ya_printf(C_LOG_ERROR, "malloc aws_certificateBuff error\n");
				ret = C_ERROR;
				goto err;
			}	
		}	
		memset(aws_certificateBuff,0,(strlen(sub_object->valuestring) + 1));
		memcpy(aws_certificateBuff, sub_object->valuestring, strlen(sub_object->valuestring));


		sub_object = cJSON_GetObjectItem(license_OVERSEA, "private_key");
		if(!sub_object)
		{
			ret = C_ERROR;
			ya_printf(C_LOG_ERROR, "cJSON_GetObjectItem private_key error\n");
			goto err;		
		}

		if (aws_privateKeyBuff == NULL)
		{
			aws_privateKeyBuff = (char *)ya_hal_os_memory_alloc(strlen(sub_object->valuestring) + 1);
			if(!aws_privateKeyBuff) 
			{
				ya_printf(C_LOG_ERROR, "malloc aws_privateKeyBuff error\n");
				ret = C_ERROR;
				goto err;
			}	
		}	
		memset(aws_privateKeyBuff,0,(strlen(sub_object->valuestring) + 1));
		memcpy(aws_privateKeyBuff, sub_object->valuestring, strlen(sub_object->valuestring));

		sub_object = cJSON_GetObjectItem(license_OVERSEA, "client_id");
		if(!sub_object || strlen(sub_object->valuestring) > YA_DEVICE_ID_LEN)
		{
			ret = C_ERROR;
			ya_printf(C_LOG_ERROR, "cJSON_GetObjectItem client_id error\n");
			goto err;		
		}

		if (aws_client_id == NULL)
		{
			aws_client_id = (char *)ya_hal_os_memory_alloc(strlen(sub_object->valuestring) + 1);
			if(!aws_client_id) 
			{
				ya_printf(C_LOG_ERROR, "malloc aws_client_id error\n");
				ret = C_ERROR;
				goto err;
			}	
		}	
		memset(aws_client_id,0,(strlen(sub_object->valuestring) + 1));
		memcpy(aws_client_id, sub_object->valuestring, strlen(sub_object->valuestring));


		sub_object = cJSON_GetObjectItem(license_OVERSEA, "thing_type");
		if(!sub_object || strlen(sub_object->valuestring) > YA_PRODUCT_KEY_LEN)
		{
			ret = C_ERROR;
			ya_printf(C_LOG_ERROR, "cJSON_GetObjectItem thing_type error\n");
			goto err;		
		}

		if (aws_thing_type == NULL)
		{
			aws_thing_type = (char *)ya_hal_os_memory_alloc(strlen(sub_object->valuestring) + 1);
			if(!aws_thing_type) 
			{
				ya_printf(C_LOG_ERROR, "malloc aws_thing_type error\n");
				ret = C_ERROR;
				goto err;
			}	
		}	
		memset(aws_thing_type,0,(strlen(sub_object->valuestring) + 1));
		memcpy(aws_thing_type, sub_object->valuestring, strlen(sub_object->valuestring));

		ya_printf(C_LOG_INFO, "client_id: %s\r\n", aws_client_id);
	}

	ya_printf(C_LOG_INFO, "license exit\r\n");

#if 0
	ya_printf(C_LOG_INFO, "aliyun_productkey: \n");
	ya_printf(C_LOG_INFO, "%s", aliyun_productkey);
	ya_printf(C_LOG_INFO, "\n");
	ya_printf(C_LOG_INFO, "aliyun_deviceid: \n");
	ya_printf(C_LOG_INFO, "%s", aliyun_deviceid);
	ya_printf(C_LOG_INFO, "\n");
	ya_printf(C_LOG_INFO, "aliyun_productsecret: \n");
	ya_printf(C_LOG_INFO, "%s", aliyun_productsecret);
	ya_printf(C_LOG_INFO, "\n");
	
	ya_printf(C_LOG_INFO, "aws_certificateBuff: \n");
	ya_printf(C_LOG_INFO, "%s", aws_certificateBuff);
	ya_printf(C_LOG_INFO, "\n");
	ya_printf(C_LOG_INFO, "aws_privateKeyBuff: \n");
	ya_printf(C_LOG_INFO, "%s", aws_privateKeyBuff);
	ya_printf(C_LOG_INFO, "\n");
	ya_printf(C_LOG_INFO, "aws_client_id: \n");
	ya_printf(C_LOG_INFO, "%s", aws_client_id);
	ya_printf(C_LOG_INFO, "\n");
	ya_printf(C_LOG_INFO, "aws_thing_type: \n");
	ya_printf(C_LOG_INFO, "%s", aws_thing_type);
	ya_printf(C_LOG_INFO, "\n");

#endif
	ret = C_OK;
err:

	if (license_addr)
	{
		ya_hal_os_memory_free(license_addr);
		license_addr = NULL;
	}
	if (license_ojb)
		cJSON_Delete(license_ojb);

	if (ret == C_ERROR)
	{
		ya_aliyun_para_free();
		ya_aws_para_free();			
	}
	return ret;

}


int ya_test_akeeta_cn_with_obj_cert(char *productkey, char *deviceid, char *secret)
{
	if(productkey == NULL || deviceid == NULL || secret == NULL)
		return C_ERROR;

	if(strlen(productkey) > YA_PRODUCT_KEY_LEN || strlen(deviceid) > YA_DEVICE_ID_LEN || strlen(secret) > YA_DEVICE_SECRET_LEN )
		return C_ERROR;

	if(aliyun_productkey == NULL)
		aliyun_productkey = (char *)ya_hal_os_memory_alloc(YA_PRODUCT_KEY_LEN + 1);
	
	memset(aliyun_productkey, 0, YA_PRODUCT_KEY_LEN + 1);

	if(aliyun_deviceid == NULL)
		aliyun_deviceid = (char *)ya_hal_os_memory_alloc(YA_DEVICE_ID_LEN + 1);
	
	memset(aliyun_deviceid, 0, YA_DEVICE_ID_LEN + 1);

	if(aliyun_productsecret == NULL)
		aliyun_productsecret = (char *)ya_hal_os_memory_alloc(YA_DEVICE_SECRET_LEN + 1);
	
	memset(aliyun_productsecret, 0, YA_DEVICE_SECRET_LEN + 1);

	strcpy(aliyun_productkey, productkey);
	strcpy(aliyun_deviceid, deviceid);
	strcpy(aliyun_productsecret, secret);

	return C_OK;
}

int ya_test_akeeta_us_with_obj_cert(char *certificateBuff, char *privateKeyBuff, char *client_id,  char *thing_type)
{
	if(certificateBuff == NULL || privateKeyBuff == NULL || client_id == NULL || thing_type == NULL)
		return C_ERROR;

	if(aws_certificateBuff == NULL)
		aws_certificateBuff = (char *)ya_hal_os_memory_alloc(strlen(certificateBuff) + 1);
	
	memset(aws_certificateBuff, 0, strlen(certificateBuff) + 1);

	if(aws_privateKeyBuff == NULL)
		aws_privateKeyBuff = (char *)ya_hal_os_memory_alloc(strlen(privateKeyBuff) + 1);
	
	memset(aws_privateKeyBuff, 0, strlen(privateKeyBuff) + 1);

	if(aws_client_id == NULL)
		aws_client_id = (char *)ya_hal_os_memory_alloc(strlen(client_id) + 1);
	
	memset(aws_client_id, 0, strlen(client_id) + 1);

	if(aws_thing_type == NULL)
		aws_thing_type = (char *)ya_hal_os_memory_alloc(strlen(thing_type) + 1);
	
	memset(aws_thing_type, 0, strlen(thing_type) + 1);

	strcpy(aws_certificateBuff, certificateBuff);
	strcpy(aws_privateKeyBuff, privateKeyBuff);
	strcpy(aws_client_id, client_id);
	strcpy(aws_thing_type, thing_type);

	return C_OK;
}


