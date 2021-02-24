// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
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

#include "ssv_gattc_api.h"
//#include "ssv_bt_main.h"
#include "btc/btc_manage.h"
#include "btc/btc_gattc.h"
#include "btc_gatt_util.h"
#include "mesh_trace.h"
//#include "stack/l2cdefs.h"
//#include "stack/l2c_api.h"


#if (GATTC_INCLUDED == TRUE)
ssv_err_t ssv_ble_gattc_register_callback(ssv_gattc_cb_t callback)
{
    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    if (callback == NULL) {
        return SSV_FAIL;
    }

    btc_profile_cb_set(BTC_PID_GATTC, callback);
    return SSV_BM_OK;
}

ssv_err_t ssv_ble_gattc_app_register(uint16_t app_id)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    if (app_id > SSV_APP_ID_MAX) {
        return SSV_ERR_INVALID_ARG;
    }

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_APP_REGISTER;
    arg.app_reg.app_id = app_id;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_app_unregister(ssv_gatt_if_t gattc_if)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_APP_UNREGISTER;
    arg.app_unreg.gattc_if = gattc_if;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_open(ssv_gatt_if_t gattc_if, ssv_bd_addr_t remote_bda, ssv_ble_addr_type_t remote_addr_type, bool is_direct)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_OPEN;
    arg.open.gattc_if = gattc_if;
    memcpy(arg.open.remote_bda, remote_bda, SSV_BD_ADDR_LEN);
    arg.open.remote_addr_type = remote_addr_type;
    arg.open.is_direct = is_direct;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_close (ssv_gatt_if_t gattc_if, uint16_t conn_id)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_CLOSE;
    arg.close.conn_id = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_send_mtu_req (ssv_gatt_if_t gattc_if, uint16_t conn_id)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_CFG_MTU;
    arg.cfg_mtu.conn_id = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_search_service(ssv_gatt_if_t gattc_if, uint16_t conn_id, ssv_bt_uuid_t *filter_uuid)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_SEARCH_SERVICE;
    arg.search_srvc.conn_id = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);

    if (filter_uuid) {
        arg.search_srvc.filter_uuid_enable = true;
        memcpy(&arg.search_srvc.filter_uuid, filter_uuid, sizeof(ssv_bt_uuid_t));
    } else {
        arg.search_srvc.filter_uuid_enable = false;
    }

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_gatt_status_t ssv_ble_gattc_get_service(ssv_gatt_if_t gattc_if, uint16_t conn_id, ssv_bt_uuid_t *svc_uuid,
                                            ssv_gattc_service_elem_t *result, uint16_t *count, uint16_t offset)
{
    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    if (result == NULL || count == NULL || *count == 0) {
        return SSV_GATT_INVALID_PDU;
    }

    uint16_t conn_hdl = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    return btc_ble_gattc_get_service(conn_hdl, svc_uuid, result, count, offset);
}


ssv_gatt_status_t ssv_ble_gattc_get_all_char(ssv_gatt_if_t gattc_if,
                                             uint16_t conn_id,
                                             uint16_t start_handle,
                                             uint16_t end_handle,
                                             ssv_gattc_char_elem_t *result,
                                             uint16_t *count, uint16_t offset)
{
    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    if ((start_handle == 0) && (end_handle == 0)) {
        *count = 0;
        return SSV_GATT_INVALID_HANDLE;
    }

    if (result == NULL || count == NULL || *count == 0) {
        return SSV_GATT_INVALID_PDU;
    }

    uint16_t conn_hdl = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    return btc_ble_gattc_get_all_char(conn_hdl, start_handle, end_handle, result, count, offset);
}

ssv_gatt_status_t ssv_ble_gattc_get_all_descr(ssv_gatt_if_t gattc_if,
                                              uint16_t conn_id,
                                              uint16_t char_handle,
                                              ssv_gattc_descr_elem_t *result,
                                              uint16_t *count, uint16_t offset)
{
    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    if (char_handle == 0) {
        return SSV_GATT_INVALID_HANDLE;
    }

    if (result == NULL || count == NULL || *count == 0) {
        return SSV_GATT_INVALID_PDU;
    }

    uint16_t conn_hdl = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    return btc_ble_gattc_get_all_descr(conn_hdl, char_handle, result, count, offset);
}

ssv_gatt_status_t ssv_ble_gattc_get_char_by_uuid(ssv_gatt_if_t gattc_if,
                                                 uint16_t conn_id,
                                                 uint16_t start_handle,
                                                 uint16_t end_handle,
                                                 ssv_bt_uuid_t char_uuid,
                                                 ssv_gattc_char_elem_t *result,
                                                 uint16_t *count)
{
    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    if (start_handle == 0 && end_handle == 0) {
        *count = 0;
        return SSV_GATT_INVALID_HANDLE;
    }

    if (result == NULL || count == NULL || *count == 0) {
        return SSV_GATT_INVALID_PDU;
    }

    uint16_t conn_hdl = BTC_GATT_CREATE_CONN_ID(gattc_if,conn_id);
    return btc_ble_gattc_get_char_by_uuid(conn_hdl, start_handle, end_handle, char_uuid, result, count);
}


ssv_gatt_status_t ssv_ble_gattc_get_descr_by_uuid(ssv_gatt_if_t gattc_if,
                                                  uint16_t conn_id,
                                                  uint16_t start_handle,
                                                  uint16_t end_handle,
                                                  ssv_bt_uuid_t char_uuid,
                                                  ssv_bt_uuid_t descr_uuid,
                                                  ssv_gattc_descr_elem_t *result,
                                                  uint16_t *count)
{
    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    if (result == NULL || count == NULL || *count == 0) {
        return SSV_GATT_INVALID_PDU;
    }

    uint16_t conn_hdl = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    return btc_ble_gattc_get_descr_by_uuid(conn_hdl, start_handle, end_handle, char_uuid, descr_uuid, result, count);
}

ssv_gatt_status_t ssv_ble_gattc_get_descr_by_char_handle(ssv_gatt_if_t gattc_if,
                                                         uint16_t conn_id,
                                                         uint16_t char_handle,
                                                         ssv_bt_uuid_t descr_uuid,
                                                         ssv_gattc_descr_elem_t *result,
                                                         uint16_t *count)
{
    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    if (char_handle == 0) {
        *count = 0;
        return SSV_GATT_INVALID_HANDLE;
    }

    if (result == NULL || count == NULL || *count == 0) {
        return SSV_GATT_INVALID_PDU;
    }

    uint16_t conn_hdl = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    return btc_ble_gattc_get_descr_by_char_handle(conn_hdl, char_handle, descr_uuid, result, count);
}

ssv_gatt_status_t ssv_ble_gattc_get_include_service(ssv_gatt_if_t gattc_if,
                                                    uint16_t conn_id,
                                                    uint16_t start_handle,
                                                    uint16_t end_handle,
                                                    ssv_bt_uuid_t *incl_uuid,
                                                    ssv_gattc_incl_svc_elem_t *result,
                                                    uint16_t *count)
{
    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    if (start_handle == 0 && end_handle == 0) {
        *count = 0;
        return SSV_GATT_INVALID_HANDLE;
    }

    if (result == NULL || count == NULL || *count == 0) {
        return SSV_GATT_INVALID_PDU;
    }

    uint16_t conn_hdl = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    return btc_ble_gattc_get_include_service(conn_hdl, start_handle, end_handle, incl_uuid, result, count);
}

ssv_gatt_status_t ssv_ble_gattc_get_attr_count(ssv_gatt_if_t gattc_if,
                                               uint16_t conn_id,
                                               ssv_gatt_db_attr_type_t type,
                                               uint16_t start_handle,
                                               uint16_t end_handle,
                                               uint16_t char_handle,
                                               uint16_t *count)
{
    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    if ((start_handle == 0 && end_handle == 0) && (type != SSV_GATT_DB_DESCRIPTOR)) {
        *count = 0;
        return SSV_GATT_INVALID_HANDLE;
    }

    if (count == NULL) {
        return SSV_GATT_INVALID_PDU;
    }

    uint16_t conn_hdl = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    return btc_ble_gattc_get_attr_count(conn_hdl, type, start_handle, end_handle, char_handle, count);
}

ssv_gatt_status_t ssv_ble_gattc_get_db(ssv_gatt_if_t gattc_if, uint16_t conn_id, uint16_t start_handle, uint16_t end_handle,
                                       ssv_gattc_db_elem_t *db, uint16_t *count)
{
    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    if (start_handle == 0 && end_handle == 0) {
        *count = 0;
        return SSV_GATT_INVALID_HANDLE;
    }

    if (db == NULL || count == NULL || *count == 0) {
        return SSV_GATT_INVALID_PDU;
    }

    uint16_t conn_hdl = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    return btc_ble_gattc_get_db(conn_hdl, start_handle, end_handle, db, count);
}


ssv_err_t ssv_ble_gattc_read_char (ssv_gatt_if_t gattc_if,
                                   uint16_t conn_id, uint16_t handle,
                                   ssv_gatt_auth_req_t auth_req)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    /*if (L2CA_CheckIsCongest(L2CAP_ATT_CID, conn_id)) {
        LOG_DEBUG("%s, the l2cap chanel is congest.", __func__);
        return SSV_FAIL;
    }*/

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_READ_CHAR;
    arg.read_char.conn_id = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    arg.read_char.handle = handle;
    arg.read_char.auth_req = auth_req;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_read_multiple(ssv_gatt_if_t gattc_if,
                                      uint16_t conn_id, ssv_gattc_multi_t *read_multi,
                                      ssv_gatt_auth_req_t auth_req)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    /*if (L2CA_CheckIsCongest(L2CAP_ATT_CID, conn_id)) {
        LOG_DEBUG("%s, the l2cap chanel is congest.", __func__);
        return SSV_FAIL;
    }*/

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_READ_MULTIPLE_CHAR;
    arg.read_multiple.conn_id = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    arg.read_multiple.num_attr = read_multi->num_attr;
    arg.read_multiple.auth_req = auth_req;

    if (read_multi->num_attr > 0) {
        memcpy(arg.read_multiple.handles, read_multi->handles, sizeof(uint16_t)*read_multi->num_attr);
    } else {
        LOG_ERROR("%s(), the num_attr should not be 0.", __func__);
        return SSV_FAIL;
    }
    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}


ssv_err_t ssv_ble_gattc_read_char_descr (ssv_gatt_if_t gattc_if,
                                         uint16_t conn_id, uint16_t handle,
                                         ssv_gatt_auth_req_t auth_req)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    /*if (L2CA_CheckIsCongest(L2CAP_ATT_CID, conn_id)) {
        LOG_DEBUG("%s, the l2cap chanel is congest.", __func__);
        return SSV_FAIL;
    }*/

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_READ_CHAR_DESCR;
    arg.read_descr.conn_id = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    arg.read_descr.handle = handle;
    arg.read_descr.auth_req = auth_req;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_write_char(ssv_gatt_if_t gattc_if,
                                   uint16_t conn_id, uint16_t handle,
                                   uint16_t value_len,
                                   uint8_t *value,
                                   ssv_gatt_write_type_t write_type,
                                   ssv_gatt_auth_req_t auth_req)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    /*if (L2CA_CheckIsCongest(L2CAP_ATT_CID, conn_id)) {
        LOG_DEBUG("%s, the l2cap chanel is congest.", __func__);
        return SSV_FAIL;
    }*/

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_WRITE_CHAR;
    arg.write_char.conn_id = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    arg.write_char.handle = handle;
    arg.write_char.value_len = value_len > SSV_GATT_MAX_ATTR_LEN ? SSV_GATT_MAX_ATTR_LEN : value_len;
    arg.write_char.value = value;
    arg.write_char.write_type = write_type;
    arg.write_char.auth_req = auth_req;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), btc_gattc_arg_deep_copy) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_write_char_descr (ssv_gatt_if_t gattc_if,
                                          uint16_t conn_id, uint16_t handle,
                                          uint16_t value_len,
                                          uint8_t *value,
                                          ssv_gatt_write_type_t write_type,
                                          ssv_gatt_auth_req_t auth_req)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    /*if (L2CA_CheckIsCongest(L2CAP_ATT_CID, conn_id)) {
        LOG_DEBUG("%s, the l2cap chanel is congest.", __func__);
        return SSV_FAIL;
    }*/

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_WRITE_CHAR_DESCR;
    arg.write_descr.conn_id = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    arg.write_descr.handle = handle;
    arg.write_descr.value_len = value_len > SSV_GATT_MAX_ATTR_LEN ? SSV_GATT_MAX_ATTR_LEN : value_len;
    arg.write_descr.value = value;
    arg.write_descr.write_type = write_type;
    arg.write_descr.auth_req = auth_req;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), btc_gattc_arg_deep_copy) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_prepare_write(ssv_gatt_if_t gattc_if,
                                      uint16_t conn_id, uint16_t handle,
                                      uint16_t offset,
                                      uint16_t value_len,
                                      uint8_t *value,
                                      ssv_gatt_auth_req_t auth_req)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    /*if (L2CA_CheckIsCongest(L2CAP_ATT_CID, conn_id)) {
        LOG_DEBUG("%s, the l2cap chanel is congest.", __func__);
        return SSV_FAIL;
    }*/

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_PREPARE_WRITE;
    arg.prep_write.conn_id = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    arg.prep_write.handle = handle;
    arg.prep_write.offset = offset;
    arg.prep_write.value_len = value_len > SSV_GATT_MAX_ATTR_LEN ? SSV_GATT_MAX_ATTR_LEN : value_len; // length check ?
    arg.prep_write.value = value;
    arg.prep_write.auth_req = auth_req;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), btc_gattc_arg_deep_copy) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_prepare_write_char_descr(ssv_gatt_if_t gattc_if,
                                                 uint16_t conn_id, uint16_t handle,
                                                 uint16_t offset,
                                                 uint16_t value_len,
                                                 uint8_t *value,
                                                 ssv_gatt_auth_req_t auth_req)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    /*if (L2CA_CheckIsCongest(L2CAP_ATT_CID, conn_id)) {
        LOG_DEBUG("%s, the l2cap chanel is congest.", __func__);
        return SSV_FAIL;
    }*/

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_PREPARE_WRITE_CHAR_DESCR;
    arg.prep_write_descr.conn_id = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    arg.prep_write_descr.handle = handle;
    arg.prep_write_descr.offset = offset;
    arg.prep_write_descr.value_len = value_len > SSV_GATT_MAX_ATTR_LEN ? SSV_GATT_MAX_ATTR_LEN : value_len; // length check ?
    arg.prep_write_descr.value = value;
    arg.prep_write_descr.auth_req = auth_req;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), btc_gattc_arg_deep_copy) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_execute_write (ssv_gatt_if_t gattc_if, uint16_t conn_id, bool is_execute)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_EXECUTE_WRITE;
    arg.exec_write.conn_id = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    arg.exec_write.is_execute = is_execute;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_register_for_notify (ssv_gatt_if_t gattc_if,
                                             ssv_bd_addr_t server_bda, uint16_t handle)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_REG_FOR_NOTIFY;
    arg.reg_for_notify.gattc_if = gattc_if;
    memcpy(arg.reg_for_notify.remote_bda, server_bda, sizeof(ssv_bd_addr_t));
    arg.reg_for_notify.handle = handle;

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_unregister_for_notify (ssv_gatt_if_t gattc_if,
                                               ssv_bd_addr_t server_bda, uint16_t handle)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_UNREG_FOR_NOTIFY;
    arg.unreg_for_notify.gattc_if = gattc_if;
    arg.unreg_for_notify.handle = handle;
    memcpy(arg.unreg_for_notify.remote_bda, server_bda, sizeof(ssv_bd_addr_t));
    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_cache_refresh(ssv_bd_addr_t remote_bda)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_CACHE_REFRESH;
    memcpy(arg.cache_refresh.remote_bda, remote_bda, sizeof(ssv_bd_addr_t));

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_cache_clean(ssv_bd_addr_t remote_bda)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_CACHE_CLEAN;
    memcpy(arg.cache_clean.remote_bda, remote_bda, sizeof(ssv_bd_addr_t));

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_cache_assoc(ssv_gatt_if_t gattc_if, ssv_bd_addr_t src_addr, ssv_bd_addr_t assoc_addr, bool is_assoc)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ACT_CACHE_ASSOC;
    arg.cache_assoc.is_assoc = is_assoc;
    arg.cache_assoc.gattc_if = gattc_if;
    memcpy(arg.cache_assoc.src_addr, src_addr, sizeof(ssv_bd_addr_t));
    memcpy(arg.cache_assoc.assoc_addr, assoc_addr, sizeof(ssv_bd_addr_t));

    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

ssv_err_t ssv_ble_gattc_cache_get_addr_list(ssv_gatt_if_t gattc_if)
{
    btc_msg_t msg;
    btc_ble_gattc_args_t arg;

    SSV_BLUEDROID_STATUS_CHECK(SSV_BLUEDROID_STATUS_ENABLED);

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_GATTC;
    msg.act = BTC_GATTC_ATC_CACHE_GET_ADDR_LIST;
    arg.get_addr_list.gattc_if = gattc_if;
    return (btc_transfer_context(&msg, &arg, sizeof(btc_ble_gattc_args_t), NULL) == BT_STATUS_SUCCESS ? SSV_BM_OK : SSV_FAIL);
}

#endif  ///GATTC_INCLUDED == TRUE

