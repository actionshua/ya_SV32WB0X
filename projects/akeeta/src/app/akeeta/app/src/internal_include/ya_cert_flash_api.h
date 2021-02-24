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

#ifndef _YA_CERT_FLASH_API_H_
#define _YA_CERT_FLASH_API_H_

#define MAX_LICENSE_LEN  (12*1024 - 32)

/**
 * @brief This function is the one used to get the private key pointer
 *
 * @return private key pointer
 */
extern char *ya_get_private_key(void);

/**
 * @brief This function is the one used to get the client id pointer
 *
 * @return client id pointer
 */
extern char *ya_get_client_cert(void);

/**
 * @brief This function is the one used to get the client id pointer
 *
 * @return client id pointer
 */
extern char *ya_aws_get_client_id(void);

/**
 * @brief This function is the one used to get the thingname pointer
 *
 * @return client id pointer
 */
extern char *ya_aws_get_thing_type(void);

/**
* @brief: free aws para
*
* @return 0: sucess, -1: failed
*/
extern int ya_aws_para_free(void);

/**
 * @brief Get product key from user's system persistent storage
 *
 * @param [ou] product_key: array to store product key, max length is YA_PRODUCT_KEY_LEN
 * @return  the actual length of product key
 */
#define YA_PRODUCT_KEY_LEN (20)
extern int ya_get_productKey(char product_key[YA_PRODUCT_KEY_LEN + 1]);
/**
 * @brief Get device name from user's system persistent storage
 *
 * @param [ou] device_name: array to store device name, max length is YA_DEVICE_NAME_LEN
 * @return the actual length of device name
 */
 #define YA_DEVICE_ID_LEN (32)
extern int ya_get_deviceID(char device_id[YA_DEVICE_ID_LEN + 1]);

/**
 * @brief Get device secret from user's system persistent storage
 *
 * @param [ou] device_secret: array to store device secret, max length is YA_DEVICE_SECRET_LEN
 * @return the actual length of device secret
 */
#define YA_DEVICE_SECRET_LEN (64)
int ya_get_deviceSecret(char device_secret[YA_DEVICE_SECRET_LEN + 1]);


/**
 * @brief: aliyun cert para free
 *
 * @return 0: sucess, -1: failed
 */
extern int ya_aliyun_para_free(void);


extern int ya_get_cloud_type(char *cloud_type);


extern int ya_get_cloud_device_id(char *device_id);


extern int ya_read_license_from_flash(uint8_t domain_check);


extern char *ya_emq_get_client_id(void);


extern char *ya_emq_get_thing_type(void);


#endif

