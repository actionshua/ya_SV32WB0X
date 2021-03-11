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


#ifndef _YA_HAL_BLE_H__
#define _YA_HAL_BLE_H__

typedef void (*ble_rcv_call_back_func_t)(uint8_t *, uint16_t);

typedef void (*ya_ble_connected_state)(uint8_t);

extern void ya_hal_ble_set_rcv_cb(ble_rcv_call_back_func_t func);

extern void ya_hal_ble_set_connect_state_cb(ya_ble_connected_state func);

extern int ya_hal_ble_send_bytes(uint8_t *data, uint16_t len);

extern char *ya_hal_ble_get_name(void);

extern int ya_hal_ble_start_adv(uint8_t *adv_ff_string, uint8_t len);

extern int ya_hal_ble_init(void);

extern void ya_hal_stop_ble(void);

extern void ya_hal_disconnect_ble_conn(void);

#endif
