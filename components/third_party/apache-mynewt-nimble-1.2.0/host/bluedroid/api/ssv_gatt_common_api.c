// Copyright 2015-2017 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string.h>
#include "ssv_gatt_common_api.h"
//#include "bt_main.h"
#include "ssv_gatt_defs.h"
#include "btc/btc_gatt_common.h"

/**
 * @brief           This function is called to set local MTU,
 *                  the function is called before BLE connection.
 *
 * @param[in]       mtu: the size of MTU.
 *
 * @return
 *                  - SSV_OK: success
 *                  - other: failed
 *
 */
ssv_err_t ssv_ble_gatt_set_local_mtu (uint16_t mtu)
{
    btc_msg_t msg;
    btc_ble_gatt_com_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(ESP_BLUEDROID_STATUS_ENABLED);

    if ((mtu < SSV_GATT_DEF_BLE_MTU_SIZE) || (mtu > SSV_GATT_MAX_MTU_SIZE)) {
        return SSV_ERR_INVALID_SIZE;
    }

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATT_COMMON;
    msg.act = BTC_GATT_ACT_SET_LOCAL_MTU;
    arg.set_mtu.mtu = mtu;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gatt_com_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}