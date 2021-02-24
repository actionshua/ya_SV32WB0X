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

#include "ssv_err.h"

#include "btc_ble_mesh_prov.h"
#include "ssv_ble_mesh_provisioning_api.h"

#define MAX_PROV_LINK_IDX   (CONFIG_BLE_MESH_PBA_SAME_TIME + CONFIG_BLE_MESH_PBG_SAME_TIME)
#define MAX_OOB_INPUT_NUM   0x5F5E0FF   /* Decimal: 99999999 */

ssv_err_t ssv_ble_mesh_register_prov_callback(ssv_ble_mesh_prov_cb_t callback)
{
    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);

    return (btc_profile_cb_set(BTC_PID_PROV, callback) == 0 ? SSV_BM_OK : SSV_FAIL);
}

bool ssv_ble_mesh_node_is_provisioned(void)
{
    return bt_mesh_is_provisioned();
}

ssv_err_t ssv_ble_mesh_node_prov_enable(ssv_ble_mesh_prov_bearer_t bearers)
{
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_PROV_ENABLE;
    arg.node_prov_enable.bearers = bearers;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_node_prov_disable(ssv_ble_mesh_prov_bearer_t bearers)
{
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_PROV_DISABLE;
    arg.node_prov_disable.bearers = bearers;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_node_set_oob_pub_key(uint8_t pub_key_x[32], uint8_t pub_key_y[32],
        uint8_t private_key[32])
{
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    if (!pub_key_x || !pub_key_y || !private_key) {
        return SSV_ERR_INVALID_ARG;
    }

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_SET_OOB_PUB_KEY;

    memcpy(arg.set_oob_pub_key.pub_key_x, pub_key_x, 32);
    memcpy(arg.set_oob_pub_key.pub_key_y, pub_key_y, 32);
    memcpy(arg.set_oob_pub_key.private_key, private_key, 32);

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_node_input_number(uint32_t number)
{
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    if (number > MAX_OOB_INPUT_NUM) {
        return SSV_ERR_INVALID_ARG;
    }

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_INPUT_NUMBER;
    arg.input_number.number = number;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_node_input_string(const char *string)
{
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    if (!string) {
        return SSV_ERR_INVALID_ARG;
    }

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_INPUT_STRING;
    memset(arg.input_string.string, 0, sizeof(arg.input_string.string));
    strncpy(arg.input_string.string, string, strlen(string));

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_set_unprovisioned_device_name(const char *name)
{
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    if (!name || strlen(name) > SSV_BLE_MESH_DEVICE_NAME_MAX_LEN) {
        return SSV_ERR_INVALID_ARG;
    }

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_SET_DEVICE_NAME;

    memset(arg.set_device_name.name, 0, sizeof(arg.set_device_name.name));
    memcpy(arg.set_device_name.name, name, strlen(name));
    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

#if (CONFIG_BLE_MESH_PROVISIONER)
ssv_err_t ssv_ble_mesh_provisioner_read_oob_pub_key(uint8_t link_idx, uint8_t pub_key_x[32],
        uint8_t pub_key_y[32])
{
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    if (!pub_key_x || !pub_key_y || link_idx >= MAX_PROV_LINK_IDX) {
        return SSV_ERR_INVALID_ARG;
    }

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_PROVISIONER_READ_OOB_PUB_KEY;

    arg.provisioner_read_oob_pub_key.link_idx = link_idx;
    memcpy(arg.provisioner_read_oob_pub_key.pub_key_x, pub_key_x, 32);
    memcpy(arg.provisioner_read_oob_pub_key.pub_key_y, pub_key_y, 32);

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_provisioner_input_string(const char *string, uint8_t link_idx)
{
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    if (!string || link_idx >= MAX_PROV_LINK_IDX) {
        return SSV_ERR_INVALID_ARG;
    }

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_PROVISIONER_INPUT_STR;

    memset(arg.provisioner_input_str.string, 0, sizeof(arg.provisioner_input_str.string));
    strncpy(arg.provisioner_input_str.string, string, strlen(string));
    arg.provisioner_input_str.link_idx = link_idx;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_provisioner_input_number(uint32_t number, uint8_t link_idx)
{
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    if (number > MAX_OOB_INPUT_NUM || link_idx >= MAX_PROV_LINK_IDX) {
        return SSV_ERR_INVALID_ARG;
    }

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_PROVISIONER_INPUT_NUM;

    arg.provisioner_input_num.number = number;
    arg.provisioner_input_num.link_idx = link_idx;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_provisioner_prov_enable(ssv_ble_mesh_prov_bearer_t bearers)
{
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_PROVISIONER_ENABLE;

    arg.provisioner_enable.bearers = bearers;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_provisioner_prov_disable(ssv_ble_mesh_prov_bearer_t bearers)
{
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_PROVISIONER_DISABLE;

    arg.provisioner_disable.bearers = bearers;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_provisioner_add_unprov_dev(ssv_ble_mesh_unprov_dev_add_t *add_dev,
        ssv_ble_mesh_dev_add_flag_t flags)
{
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    if (add_dev == NULL) {
        return SSV_ERR_INVALID_ARG;
    }

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_PROVISIONER_DEV_ADD;

    arg.provisioner_dev_add.add_dev.addr_type = add_dev->addr_type;
    arg.provisioner_dev_add.add_dev.oob_info = add_dev->oob_info;
    arg.provisioner_dev_add.add_dev.bearer = add_dev->bearer;
    memcpy(arg.provisioner_dev_add.add_dev.addr, add_dev->addr, sizeof(ssv_ble_mesh_bd_addr_t));
    memcpy(arg.provisioner_dev_add.add_dev.uuid, add_dev->uuid, 16);
    arg.provisioner_dev_add.flags = flags;
    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_provisioner_delete_dev(ssv_ble_mesh_device_delete_t *del_dev)
{
    uint8_t val = DEL_DEV_ADDR_FLAG | DEL_DEV_UUID_FLAG;
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    if (del_dev == NULL || (__builtin_popcount(del_dev->flag & val) != 1)) {
        return SSV_ERR_INVALID_ARG;
    }

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_PROVISIONER_DEV_DEL;

    arg.provisioner_dev_del.del_dev.flag = del_dev->flag;
    if (del_dev->flag & DEL_DEV_ADDR_FLAG) {
        arg.provisioner_dev_del.del_dev.addr_type = del_dev->addr_type;
        memcpy(arg.provisioner_dev_del.del_dev.addr, del_dev->addr, sizeof(ssv_ble_mesh_bd_addr_t));
    } else if (del_dev->flag & DEL_DEV_UUID_FLAG) {
        memcpy(arg.provisioner_dev_del.del_dev.uuid, del_dev->uuid, 16);
    }
    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_provisioner_set_dev_uuid_match(const uint8_t *match_val, uint8_t match_len,
        uint8_t offset, bool prov_after_match)
{
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_PROVISIONER_SET_DEV_UUID_MATCH;

    if (match_len && match_val) {
        memcpy(arg.set_dev_uuid_match.match_val, match_val, match_len);
    }
    arg.set_dev_uuid_match.match_len = match_len;
    arg.set_dev_uuid_match.offset = offset;
    arg.set_dev_uuid_match.prov_after_match = prov_after_match;
    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_provisioner_set_prov_data_info(ssv_ble_mesh_prov_data_info_t *prov_data_info)
{
    uint8_t val = PROV_DATA_NET_IDX_FLAG | PROV_DATA_FLAGS_FLAG | PROV_DATA_IV_INDEX_FLAG;
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    if (prov_data_info == NULL || (__builtin_popcount(prov_data_info->flag & val) != 1)) {
        return SSV_ERR_INVALID_ARG;
    }

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_PROVISIONER_SET_PROV_DATA_INFO;

    arg.set_prov_data_info.prov_data.flag = prov_data_info->flag;
    if (prov_data_info->flag & PROV_DATA_NET_IDX_FLAG) {
        arg.set_prov_data_info.prov_data.net_idx = prov_data_info->net_idx;
    } else if (prov_data_info->flag & PROV_DATA_FLAGS_FLAG) {
        arg.set_prov_data_info.prov_data.flags = prov_data_info->flags;
    } else if (prov_data_info->flag & PROV_DATA_IV_INDEX_FLAG) {
        arg.set_prov_data_info.prov_data.iv_index = prov_data_info->iv_index;
    }
    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

#endif /* CONFIG_BLE_MESH_PROVISIONER */

/* The following APIs are for fast provisioning */

#if (CONFIG_BLE_MESH_FAST_PROV)

ssv_err_t ssv_ble_mesh_set_fast_prov_info(ssv_ble_mesh_fast_prov_info_t *fast_prov_info)
{
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    if (fast_prov_info == NULL) {
        return SSV_ERR_INVALID_ARG;
    }

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_SET_FAST_PROV_INFO;

    arg.set_fast_prov_info.unicast_min = fast_prov_info->unicast_min;
    arg.set_fast_prov_info.unicast_max = fast_prov_info->unicast_max;
    arg.set_fast_prov_info.net_idx = fast_prov_info->net_idx;
    arg.set_fast_prov_info.flags = fast_prov_info->flags;
    arg.set_fast_prov_info.iv_index = fast_prov_info->iv_index;
    arg.set_fast_prov_info.offset = fast_prov_info->offset;
    arg.set_fast_prov_info.match_len = fast_prov_info->match_len;
    if (fast_prov_info->match_len && fast_prov_info->match_val) {
        memcpy(arg.set_fast_prov_info.match_val, fast_prov_info->match_val, fast_prov_info->match_len);
    }
    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_mesh_set_fast_prov_action(ssv_ble_mesh_fast_prov_action_t action)
{
    btc_ble_mesh_prov_args_t arg;
    btc_msg_t msg = {0};

    if (action >= FAST_PROV_ACT_MAX) {
        return SSV_ERR_INVALID_ARG;
    }
    memset(&arg, 0, sizeof(arg));
    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_SET_FAST_PROV_ACTION;

    arg.set_fast_prov_action.action = action;
    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL)
            == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

#endif /* CONFIG_BLE_MESH_FAST_PROV */

