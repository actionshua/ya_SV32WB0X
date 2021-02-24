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
 

#ifndef __YA_ATCMD_H_
#define __YA_ATCMD_H_

/*****如果uart驱动一次只返回一个数据，需要打开UART_POLLING_DATA宏*****/
#define UART_POLLING_DATA   
extern int ya_atcmd_handler(char *cmd);
extern void clear_enter_get_rssi_mode(void);
extern uint8_t check_enter_get_rssi_mode(void);

extern void at_cmd_log_ON(void);
extern void at_cmd_log_OFF(void);

#endif

