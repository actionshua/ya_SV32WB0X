// Copyright 2017-2019 Espressif Systems (Shanghai) PTE LTD
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

#include <stdint.h>

#include "btc/btc_task.h"
#include "btc/btc_manage.h"

#include "btc_ble_mesh_config_model.h"
#include "ssv_ble_mesh_config_model_api.h"

ssv_err_t ssv_ble_mesh_register_config_client_callback(ssv_ble_mesh_cfg_client_cb_t callback)
{
    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);

    return (btc_profile_cb_set(BTC_PID_CONFIG_CLIENT, callback) == 0 ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_register_config_server_callback(ssv_ble_mesh_cfg_server_cb_t callback)
{
    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);

    return (btc_profile_cb_set(BTC_PID_CONFIG_SERVER, callback) == 0 ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_config_client_get_state(ssv_ble_mesh_client_common_param_t *params,
        ssv_ble_mesh_cfg_client_get_state_t *get_state)
{
    btc_ble_mesh_config_client_args_t arg;
    btc_msg_t msg = {0};

    if (!params || !params->model || !params->ctx.addr || !get_state) {
        return SSV_ERR_INVALID_ARG;
    }

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_CONFIG_CLIENT;
    msg.act = BTC_BLE_MESH_ACT_CONFIG_CLIENT_GET_STATE;
    arg.cfg_client_get_state.params = params;
    arg.cfg_client_get_state.get_state = get_state;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_config_client_args_t), btc_ble_mesh_config_client_arg_deep_copy)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_config_client_set_state(ssv_ble_mesh_client_common_param_t *params,
        ssv_ble_mesh_cfg_client_set_state_t *set_state)
{
    btc_ble_mesh_config_client_args_t arg;
    btc_msg_t msg = {0};

    if (!params || !params->model || !params->ctx.addr || !set_state) {
        return SSV_ERR_INVALID_ARG;
    }

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_CONFIG_CLIENT;
    msg.act = BTC_BLE_MESH_ACT_CONFIG_CLIENT_SET_STATE;
    arg.cfg_client_set_state.params = params;
    arg.cfg_client_set_state.set_state = set_state;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_config_client_args_t), btc_ble_mesh_config_client_arg_deep_copy)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}
