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

#ifndef _YA_CLOUD_ALY_APP_H_
#define _YA_CLOUD_ALY_APP_H_

/**
 * @brief This function is used to create the aliyun cloud obj
 *
 * @return cloud_context_t obj poniter, if create failed, then return NULL
 */
extern cloud_context_t* aliyun_cloud_create(void);

extern char *ya_aly_get_client_id(void);

extern char *ya_aly_get_thing_name(void);

#endif

