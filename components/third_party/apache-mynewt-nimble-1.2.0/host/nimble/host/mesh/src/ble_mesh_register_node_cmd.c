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

//#include "soc/soc.h"
//#include "ssv_bt.h"
//#include "ssv_bt_device.h"

#include "ssv_ble_mesh_defs.h"
#include "ssv_ble_mesh_common_api.h"
#include "ssv_ble_mesh_provisioning_api.h"
#include "ssv_ble_mesh_networking_api.h"
#include "ssv_ble_mesh_config_model_api.h"
#include "ssv_timer.h"
#include "ble_mesh_adapter.h"
#include "test.h"
#include "client_common.h"
#include "test_data.h"
#include "access.h"
#include "osal.h"
#include "adv.h"
static uint16_t node_net_idx = SSV_BLE_MESH_KEY_UNUSED;
static uint16_t node_app_idx = SSV_BLE_MESH_KEY_UNUSED;

typedef struct {
    struct arg_str *static_val;
    struct arg_int *static_val_len;
    struct arg_int *output_size;
    struct arg_int *output_actions;
    struct arg_int *input_size;
    struct arg_int *input_actions;
    struct arg_int *prov_start_address;
    struct arg_end *end;
} ble_mesh_prov_t;
static ble_mesh_prov_t oob;

typedef struct {
    struct arg_int *model_type;
    struct arg_int *config_index;
    struct arg_int *pub_config;
    struct arg_end *end;
} ble_mesh_comp_t;
static ble_mesh_comp_t component;

typedef struct {
    struct arg_int *bearer;
    struct arg_int *enable;
    struct arg_end *end;
} ble_mesh_bearer_t;
static ble_mesh_bearer_t bearer;

typedef struct {
    struct arg_str *net_key;
    struct arg_int *net_idx;
    struct arg_int *unicast_addr;
    struct arg_str *dev_key;
    struct arg_str *app_key;
    struct arg_int *app_idx;
    struct arg_int *group_addr;
    struct arg_end *end;
} ble_mesh_node_network_info_t;
ble_mesh_node_network_info_t node_network_info;

#if CONFIG_PERFORMANCE_CLIENT_MODEL
typedef struct {
    struct arg_str *action_type;
    struct arg_int *package_num;
    struct arg_end *end;
} ble_mesh_node_statistices_t;
ble_mesh_node_statistices_t node_statistices;
#endif

typedef struct {
    struct arg_str *action_type;
    struct arg_int *tx_sense_power;
    struct arg_end *end;
} ble_mesh_tx_sense_power;
static ble_mesh_tx_sense_power power_set;

ble_mesh_node_status node_status = {
    .previous = 0x0,
    .current = 0x0,
};

SemaphoreHandle_t ble_mesh_node_sema;

void ble_mesh_register_node_cmd(void);
// Register callback function
void ble_mesh_prov_cb(ssv_ble_mesh_prov_cb_event_t event, ssv_ble_mesh_prov_cb_param_t *param);
void ble_mesh_model_cb(ssv_ble_mesh_model_cb_event_t event, ssv_ble_mesh_model_cb_param_t *param);

static void ssv_ble_mesh_generic_server_cb(ssv_ble_mesh_generic_server_cb_event_t event,
                                               ssv_ble_mesh_generic_server_cb_param_t *param);

static void ssv_ble_mesh_config_server_cb(ssv_ble_mesh_cfg_server_cb_event_t event,
                                              ssv_ble_mesh_cfg_server_cb_param_t *param);

static void ssv_ble_mesh_generic_client_cb(ssv_ble_mesh_generic_client_cb_event_t event,
                                               ssv_ble_mesh_generic_client_cb_param_t *param);



void ble_mesh_register_mesh_node(void)
{
    ble_mesh_register_node_cmd();
}

int ble_mesh_register_node_cb(int argc, char** argv)
{
    SSV_LOGD(TAG, "enter %s\n", __func__);
    ble_mesh_node_init();
    ssv_ble_mesh_register_prov_callback(ble_mesh_prov_cb);
    ssv_ble_mesh_register_custom_model_callback(ble_mesh_model_cb);//mesh_test_perf
    //onoff server
    ssv_ble_mesh_register_config_server_callback(ssv_ble_mesh_config_server_cb);
    ssv_ble_mesh_register_generic_server_callback(ssv_ble_mesh_generic_server_cb);
    //onoff client
    ssv_ble_mesh_register_generic_client_callback(ssv_ble_mesh_generic_client_cb);
    SSV_LOGI(TAG, "Node:Reg,OK");
    SSV_LOGD(TAG, "exit %s\n", __func__);
    return 0;
}

void ble_mesh_prov_cb(ssv_ble_mesh_prov_cb_event_t event, ssv_ble_mesh_prov_cb_param_t *param)
{
    SSV_LOGD(TAG, "enter %s, event = %d", __func__, event);
    switch (event) {
    case SSV_BLE_MESH_PROV_REGISTER_COMP_EVT:
        ble_mesh_callback_check_err_code(param->prov_register_comp.err_code, "Provisioning:Register");
        break;
    case SSV_BLE_MESH_NODE_PROV_ENABLE_COMP_EVT:
        ble_mesh_callback_check_err_code(param->node_prov_enable_comp.err_code, "Node:EnBearer");
        break;
    case SSV_BLE_MESH_NODE_PROV_DISABLE_COMP_EVT:
        ble_mesh_callback_check_err_code(param->node_prov_disable_comp.err_code, "Node:DisBearer");
        break;
    case SSV_BLE_MESH_NODE_PROV_LINK_OPEN_EVT:
        SSV_LOGI(TAG, "Node:LinkOpen,OK,%d", param->node_prov_link_open.bearer);
        break;
    case SSV_BLE_MESH_NODE_PROV_LINK_CLOSE_EVT:
        SSV_LOGI(TAG, "Node:LinkClose,OK,%d", param->node_prov_link_close.bearer);
        break;
    case SSV_BLE_MESH_NODE_PROV_OUTPUT_NUMBER_EVT:
        SSV_LOGI(TAG, "Node:OutPut,%d,%d", param->node_prov_output_num.action, param->node_prov_output_num.number);
        break;
    case SSV_BLE_MESH_NODE_PROV_OUTPUT_STRING_EVT:
        SSV_LOGI(TAG, "Node:OutPutStr,%s", param->node_prov_output_str.string);
        break;
    case SSV_BLE_MESH_NODE_PROV_INPUT_EVT:
        SSV_LOGI(TAG, "Node:InPut,%d,%d", param->node_prov_input.action, param->node_prov_input.size);
        break;
    case SSV_BLE_MESH_NODE_PROV_COMPLETE_EVT:
        SSV_LOGI(TAG, "Node:OK,%d,%d", param->node_prov_complete.net_idx, param->node_prov_complete.addr);
        ble_mesh_set_node_prestore_params(param->node_prov_complete.net_idx, param->node_prov_complete.addr);
        break;
    case SSV_BLE_MESH_NODE_PROV_RESET_EVT:
        SSV_LOGI(TAG, "Node:Reset");
        break;
    case SSV_BLE_MESH_NODE_PROV_INPUT_NUMBER_COMP_EVT:
        ble_mesh_callback_check_err_code(param->node_prov_input_num_comp.err_code, "Node:InputNum");
        break;
    case SSV_BLE_MESH_NODE_PROV_INPUT_STRING_COMP_EVT:
        ble_mesh_callback_check_err_code(param->node_prov_input_str_comp.err_code, "Node:InputStr");
        break;
    case SSV_BLE_MESH_NODE_SET_UNPROV_DEV_NAME_COMP_EVT:
        ble_mesh_callback_check_err_code(param->node_set_unprov_dev_name_comp.err_code, "Node:SetName");
        break;
    case SSV_BLE_MESH_NODE_PROXY_IDENTITY_ENABLE_COMP_EVT:
        ble_mesh_callback_check_err_code(param->node_proxy_identity_enable_comp.err_code, "Node:ProxyIndentity");
        break;
    case SSV_BLE_MESH_NODE_PROXY_GATT_ENABLE_COMP_EVT:
        ble_mesh_callback_check_err_code(param->node_proxy_gatt_enable_comp.err_code, "Node:EnProxyGatt");
        break;
    case SSV_BLE_MESH_NODE_PROXY_GATT_DISABLE_COMP_EVT:
        ble_mesh_callback_check_err_code(param->node_proxy_gatt_disable_comp.err_code, "Node:DisProxyGatt");
        break;
#if (CONFIG_BLE_MESH_PROVISIONER)
    case SSV_BLE_MESH_PROVISIONER_RECV_UNPROV_ADV_PKT_EVT:
        SSV_LOGI(TAG, "Provisioner recv unprovisioned device beacon:");
        SSV_LOG_BUFFER_HEX("Device UUID %s", param->provisioner_recv_unprov_adv_pkt.dev_uuid, 16);
        SSV_LOG_BUFFER_HEX("Address %s", param->provisioner_recv_unprov_adv_pkt.addr, 6);
        SSV_LOGI(TAG, "Address type 0x%x, oob_info 0x%04x, adv_type 0x%x, bearer 0x%x",
            param->provisioner_recv_unprov_adv_pkt.addr_type, param->provisioner_recv_unprov_adv_pkt.oob_info,
            param->provisioner_recv_unprov_adv_pkt.adv_type, param->provisioner_recv_unprov_adv_pkt.bearer);
        break;
    case SSV_BLE_MESH_PROVISIONER_PROV_LINK_OPEN_EVT:
        SSV_LOGI(TAG, "Provisioner:LinkOpen,OK,%d", param->provisioner_prov_link_open.bearer);
        break;
    case SSV_BLE_MESH_PROVISIONER_PROV_LINK_CLOSE_EVT:
        SSV_LOGI(TAG, "Provisioner:LinkClose,OK,%d,%d",
                 param->provisioner_prov_link_close.bearer, param->provisioner_prov_link_close.reason);
        break;
    case SSV_BLE_MESH_PROVISIONER_ADD_UNPROV_DEV_COMP_EVT:
        ble_mesh_callback_check_err_code(param->provisioner_add_unprov_dev_comp.err_code, "Provisioner:DevAdd");
        break;
    case SSV_BLE_MESH_PROVISIONER_DELETE_DEV_COMP_EVT:
        ble_mesh_callback_check_err_code(param->provisioner_delete_dev_comp.err_code, "Provisioner:DevDel");
        break;
    case SSV_BLE_MESH_PROVISIONER_PROV_COMPLETE_EVT:
        SSV_LOGI(TAG, "Provisioner:OK,%d,%d", param->provisioner_prov_complete.netkey_idx, param->provisioner_prov_complete.unicast_addr);
        break;
    case SSV_BLE_MESH_PROVISIONER_PROV_ENABLE_COMP_EVT:
        ble_mesh_callback_check_err_code(param->provisioner_prov_enable_comp.err_code, "Provisioner:EnBearer");
        break;
    case SSV_BLE_MESH_PROVISIONER_PROV_DISABLE_COMP_EVT:
        ble_mesh_callback_check_err_code(param->provisioner_prov_disable_comp.err_code, "Provisioner:DisBearer");
        break;
    case SSV_BLE_MESH_PROVISIONER_SET_DEV_UUID_MATCH_COMP_EVT:
        ble_mesh_callback_check_err_code(param->provisioner_set_dev_uuid_match_comp.err_code, "Provisioner:UuidMatch");
        break;
    case SSV_BLE_MESH_PROVISIONER_SET_PROV_DATA_INFO_COMP_EVT:
        ble_mesh_callback_check_err_code(param->provisioner_set_prov_data_info_comp.err_code, "Provisioner:DataInfo");
        break;
    case SSV_BLE_MESH_PROVISIONER_SET_NODE_NAME_COMP_EVT:
        ble_mesh_callback_check_err_code(param->provisioner_set_node_name_comp.err_code, "Provisioner:NodeName");
        break;
    case SSV_BLE_MESH_PROVISIONER_ADD_LOCAL_APP_KEY_COMP_EVT:
        ble_mesh_callback_check_err_code(param->provisioner_add_app_key_comp.err_code, "Provisioner:AppKeyAdd");
        break;
    case SSV_BLE_MESH_PROVISIONER_BIND_APP_KEY_TO_MODEL_COMP_EVT:
        ble_mesh_callback_check_err_code(param->provisioner_bind_app_key_to_model_comp.err_code, "Provisioner:AppKeyBind");
        break;
    case SSV_BLE_MESH_PROVISIONER_ADD_LOCAL_NET_KEY_COMP_EVT:
        ble_mesh_callback_check_err_code(param->provisioner_add_net_key_comp.err_code, "Provisioner:NetKeyAdd");
        break;
#endif
    default:
        break;
    }
    SSV_LOGD(TAG, "exit %s\n", __func__);
}
extern struct ble_mesh_sync_bitmap g_st_acked_bitmap;
void ble_mesh_model_cb(ssv_ble_mesh_model_cb_event_t event, ssv_ble_mesh_model_cb_param_t *param)
{
    ssv_err_t result = SSV_BM_OK;
    uint8_t status;
    uint8_t test_ack_msg[BLE_MESH_TEST_VDNDOR_MODEL_ACK_LENGTH] = {0x0};
    uint8_t result_status_msg[TEST_RESULT_RETUEN_END] = {0};
    ssv_ble_mesh_model_t *model;
    uint64_t current_time = 0;

    SSV_LOGD(TAG, "enter %s, event=%x, opcode 0x%x\n", __func__, event, param->model_operation.opcode);

    switch (event) {
    case SSV_BLE_MESH_MODEL_OPERATION_EVT:
        if (param->model_operation.model != NULL && param->model_operation.model->op != NULL) {
            if (param->model_operation.opcode == SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_GET) {
                SSV_LOGI(TAG, "Node:GetStatus,OK");
                ble_mesh_node_get_state(status);
                result = ssv_ble_mesh_server_model_send_msg(param->model_operation.model, param->model_operation.ctx, SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS,
                         sizeof(status), &status);
            } else if (param->model_operation.opcode == SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_SET) {
                ble_mesh_node_set_state(param->model_operation.msg[0]);
                SSV_LOGI(TAG, "Node:SetAck,OK,%d,%d", param->model_operation.msg[0], param->model_operation.ctx->recv_ttl);
                result = ssv_ble_mesh_server_model_send_msg(param->model_operation.model, param->model_operation.ctx, SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS,
                         sizeof(status), param->model_operation.msg);
            } else if (param->model_operation.opcode == SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_SET_UNACK) {
                ble_mesh_node_set_state(param->model_operation.msg[0]);
                SSV_LOGI(TAG, "Node:SetUnAck,OK,%d,%d", param->model_operation.msg[0], param->model_operation.ctx->recv_ttl);
            } else if (param->model_operation.opcode == SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS) {
                SSV_LOGI(TAG, "Node:Status,Success,%d", param->model_operation.length);
            }
#if CONFIG_PERFORMANCE_CLIENT_MODEL
            else if (param->model_operation.opcode == SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_GET) {
                SSV_LOGI(TAG, "VendorModel:TEST_PERF_GET,OK,%d", param->model_operation.ctx->recv_ttl);
            } else if (param->model_operation.opcode == SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_SET) {
                SSV_LOGI(TAG, "VendorModel:TEST_PERF_SET,OK,%d", param->model_operation.ctx->recv_ttl);
            } else if (param->model_operation.opcode == SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_SET_UNACK) {
                SSV_LOGI(TAG, "VendorModel:TEST_PERF_SET_UNACK,OK,%d", param->model_operation.ctx->recv_ttl);
            } else if (param->model_operation.opcode == SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_STATUS) {
                SSV_LOGI(TAG, "VendorModel:TEST_PERF_STATUS,OK,%d", param->model_operation.ctx->recv_ttl);
                uint64_t current_time = ssv_timer_get_time();
                result = ble_mesh_test_performance_client_model_accumulate_time(((uint32_t)(current_time - start_time) / 1000), param->model_operation.msg, param->model_operation.ctx->recv_ttl, param->model_operation.length);
                SSV_LOGI(TAG, "VendorModel:Status,OK,%d", param->model_operation.ctx->recv_ttl);
                if (ble_mesh_test_perf_send_sema != NULL && result == SSV_BM_OK) {
                    xSemaphoreGive(ble_mesh_test_perf_send_sema);
                }
            } else if (param->model_operation.opcode == SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_ITEM_SET) {
                /* receive item set from phone(or test controll) */
                SSV_LOGI(TAG, "VendorModel:SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_ITEM_SET,OK,%d", param->model_operation.ctx->recv_ttl);
                if (ble_mesh_do_test_item(param->model_operation.msg, param->model_operation.length)) {
                    //this device is sender, so send ack to phone(or controll)
                    status = SSV_TEST_WORK;
                    result = ssv_ble_mesh_server_model_send_msg(param->model_operation.model, param->model_operation.ctx,
                        SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_ITEM_SET_STATUS, sizeof(status), &status);//send ack msg

                }
            } else if (param->model_operation.opcode == SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_ITEM_SET_STATUS) {
                SSV_LOGI(TAG, "VendorModel:ITEM_SET_STATUS,OK,%d from %d", param->model_operation.ctx->recv_ttl,
                    param->model_operation.ctx->addr);

            } else if (param->model_operation.opcode == SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST) {
                if (param->model_operation.ctx->addr != bt_mesh_primary_addr()) {
                    /*sender send vendor with ack ok 0x30*/
                    SSV_LOGI(TAG, "VendorModel:TEST_PERF_TEST,OK,%d, send status ack", param->model_operation.ctx->recv_ttl);
                    ble_mesh_test_add_msg_count();
                    memset(test_ack_msg, 0xFF, sizeof(test_ack_msg));
                    model = ble_mesh_get_model(SSV_BLE_MESH_VND_MODEL_ID_TEST_PERF_CLI);
                    param->model_operation.ctx->model = model;
                    //send 20bytes ack msg
                    result = ssv_ble_mesh_client_model_send_msg(model, param->model_operation.ctx,
                        SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_STATUS, sizeof(test_ack_msg), test_ack_msg, 0, false, ROLE_NODE);
                }

            } else if (param->model_operation.opcode == SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_UNACK) {
                /* sender/receiver send vendor no ack ok 0x31, item 5 node2 receive msg
                       * Display in sender side, just for observe how many unack msg is send.
                       */
                if (param->model_operation.ctx->addr != bt_mesh_primary_addr()) {
                    ble_mesh_test_add_msg_count();
                    SSV_LOGI(TAG, "VendorModel:TEST_PERF_TEST_UNACK,OK,%d, RX %d from %d",
                        param->model_operation.ctx->recv_ttl, ble_mesh_test_get_msg_count(),
                        param->model_operation.ctx->addr);
                }
            } else if (param->model_operation.opcode == SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_STATUS) {
                if (param->model_operation.ctx->addr != bt_mesh_primary_addr()) {
                    u8 shift_bit = 0, low = 0, result = 0;
                    /*receive vendor msg 20 bytes ack*/
                    //SSV_LOGE(TAG, "VendorModel:TEST_STATUS,OK,%d from %d", param->model_operation.ctx->recv_ttl,
                    //    param->model_operation.ctx->addr);
                    //printf("Vf %d", param->model_operation.ctx->addr);

                    if (param->model_operation.ctx->addr && (param->model_operation.ctx->addr < (sizeof(g_st_acked_bitmap)*8))) {
                        result = get_shift_bit(param->model_operation.ctx->addr, &shift_bit, &low);
                        if (result) {
                            if (low)
                                g_st_acked_bitmap.low |= (1 << shift_bit);
                            else
                                g_st_acked_bitmap.high |= (1 << shift_bit);
                        }
                    }
                    ble_mesh_test_decrease_expect_ack_count(VENDOR_RECEIVE_ACK);
                }

            } /*else if (param->model_operation.opcode == SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_RESULT_STATUS) {//delete
                ble_mesh_test_get_result_return(param->model_operation.ctx->addr,
                    param->model_operation.msg, param->model_operation.length);
                ble_mesh_test_decrease_expect_ack_count(GET_TEST_RESULT);
            } */else if (param->model_operation.opcode == SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_RESULT) {
                SSV_LOGI(TAG, "VendorModel:TEST_PERF_TEST_RESULT,OK,%d, Reply Test Result %d",
                    param->model_operation.ctx->recv_ttl, ble_mesh_test_get_msg_count());
                model = ble_mesh_get_model(SSV_BLE_MESH_VND_MODEL_ID_TEST_PERF_CLI);
                param->model_operation.ctx->model = model;
                result_status_msg[TEST_RESULT_RETUEN_ACK_COUNT_A] = ((ble_mesh_test_get_msg_count() >> 8) & 0xFF);
                result_status_msg[TEST_RESULT_RETUEN_ACK_COUNT_B] = (ble_mesh_test_get_msg_count() & 0xFF);
                result_status_msg[TEST_RESULT_RETUEN_ACK_ADDR] = bt_mesh_primary_addr();
                result = ssv_ble_mesh_client_model_send_msg(model, param->model_operation.ctx,
                    SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_RESULT_STATUS, sizeof(result_status_msg), result_status_msg, 0, false, ROLE_NODE);
            }
#endif
        }
        break;
    case SSV_BLE_MESH_MODEL_SEND_COMP_EVT:
        if (param->model_send_comp.err_code == SSV_BM_OK) {
            SSV_LOGI(TAG, "Node:ModelSend,OK");
        } else {
            SSV_LOGE(TAG, "Node:ModelSend,Fail,%d,0x%X,0x%04X", param->model_send_comp.err_code, param->model_send_comp.model->model_id, param->model_send_comp.model->op->opcode);
        }
        break;
    case SSV_BLE_MESH_MODEL_PUBLISH_COMP_EVT:
        SSV_LOGI(TAG, "Node:PublishSend,OK,0x%X,%d", param->model_publish_comp.model->model_id, param->model_publish_comp.model->pub->msg->len);
        break;
    case SSV_BLE_MESH_CLIENT_MODEL_RECV_PUBLISH_MSG_EVT:
        SSV_LOGI(TAG, "Node:PublishReceive,OK,0x%04X,%d,%d", param->client_recv_publish_msg.opcode, param->client_recv_publish_msg.length, param->client_recv_publish_msg.msg[1]);
#if CONFIG_PERFORMANCE_CLIENT_MODEL
        if (param->model_operation.model != NULL && param->model_operation.model->op != NULL) {
            switch (param->model_operation.opcode)
            {
                case SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_RESULT_STATUS:
                    ble_mesh_test_get_result_return(param->model_operation.ctx->addr,
                    param->model_operation.msg, param->model_operation.length);
                    ble_mesh_test_decrease_expect_ack_count(GET_TEST_RESULT);
                    break;

                case SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_SET:
                    current_time = ssv_timer_get_time();
                    result = ble_mesh_test_performance_client_model_accumulate_time(((uint32_t)(current_time - start_time) / 2000), param->client_recv_publish_msg.msg, param->client_recv_publish_msg.ctx->recv_ttl, param->client_recv_publish_msg.length);
                    if (ble_mesh_test_perf_send_sema != NULL && param->client_recv_publish_msg.msg[2] == VENDOR_MODEL_PERF_OPERATION_TYPE_SET_UNACK && result == SSV_BM_OK) {
                        xSemaphoreGive(ble_mesh_test_perf_send_sema);
                    }
                    break;

                default:
                    break;

            }
        }
#endif
        break;
    case SSV_BLE_MESH_MODEL_PUBLISH_UPDATE_EVT:
        SSV_LOGI(TAG, "Node:PublishUpdate,OK");
        break;
    case SSV_BLE_MESH_CLIENT_MODEL_SEND_TIMEOUT_EVT:
        SSV_LOGI(TAG, "Node:TimeOut, 0x%04X", param->client_send_timeout.opcode);
        ble_mesh_test_event_set_bit(MSG_TIMEOUT_EVT);/*vendor msg timeout*/
#if CONFIG_PERFORMANCE_CLIENT_MODEL
        if (ble_mesh_test_perf_send_sema != NULL) {
            xSemaphoreGive(ble_mesh_test_perf_send_sema);
        }
#endif
        break;
    case SSV_BLE_MESH_MODEL_EVT_MAX:
        SSV_LOGI(TAG, "Node:MaxEvt");
        break;
    default:
        break;
    }

    SSV_LOGD(TAG, "exit %s\n", __func__);
}

int ble_mesh_power_set(int argc, char **argv)
{
    ssv_err_t result = SSV_BM_OK;
    int nerrors = arg_parse(argc, argv, (void **) &power_set);

    SSV_LOGD(TAG, "enter %s todo\n", __func__);
    return SSV_BM_OK;
#if 0
    if (nerrors != 0) {
        arg_print_errors(stderr, power_set.end, argv[0]);
        return 1;
    }

    if (strcmp(power_set.action_type->sval[0], "tx") == 0) {
        result = ssv_ble_tx_power_set(SSV_BLE_PWR_TYPE_ADV, power_set.tx_sense_power->ival[0]);
    } else if (strcmp(power_set.action_type->sval[0], "sense") == 0) {
        uint32_t *reg = (uint32_t *)(0x6001c07c);
        int reg_addr = 0x6001c07c;
        uint32_t flag = 0x00FF0000;
        uint32_t sense_new = power_set.tx_sense_power->ival[0];
        uint32_t reg_to_write = ((*reg) &= ~flag) | ((256 - sense_new) << 16);
        REG_WRITE(reg_addr, reg_to_write);

    }
#endif
    if (result == SSV_BM_OK) {
        SSV_LOGI(TAG, "Node:SetPower,OK\n");
    }

    SSV_LOGD(TAG, "exit %s\n", __func__);
    return result;
}

extern uint8_t ble_hs_id_pub[6];

int ble_mesh_load_oob(int argc, char **argv)
{
    uint8_t *static_val;

    SSV_LOGD(TAG, "enter %s \n", __func__);

    int nerrors = arg_parse(argc, argv, (void **) &oob);
    if (nerrors != 0) {
        arg_print_errors(stderr, oob.end, argv[0]);
        return 1;
    }

    //parsing prov
#if CONFIG_BLE_MESH_NODE
    prov.uuid = dev_uuid;

    memcpy(dev_uuid + 2, ble_hs_id_pub, BD_ADDR_LEN);
    /*SSV_LOGI(TAG, "uuid is %02x%02x %02x%02x%02x%02x%02x%02x...\n", dev_uuid[0], dev_uuid[1],
        dev_uuid[2], dev_uuid[3], dev_uuid[4], dev_uuid[5], dev_uuid[6], dev_uuid[7]);*/

    //memcpy(dev_uuid, ssv_bt_dev_get_address(), 6);//todo
    if (oob.static_val->count != 0) {
        static_val = osi_malloc(oob.static_val_len->ival[0] + 1);
        if (static_val == NULL) {
            SSV_LOGE(TAG, "malloc fail,%s,%d\n", __func__, __LINE__);
        }
        get_value_string((char *)oob.static_val->sval[0], (char *)static_val);
        prov.static_val = static_val;
    }

    arg_int_to_value(oob.static_val_len, prov.static_val_len, "static value length");
    arg_int_to_value(oob.output_size, prov.output_size, "output size");
    arg_int_to_value(oob.output_actions, prov.output_actions, "output actions");
    arg_int_to_value(oob.input_size, prov.input_size, "input size");
    arg_int_to_value(oob.input_actions, prov.input_actions, "input actions");
#endif

#if CONFIG_BLE_MESH_PROVISIONER
    if (oob.static_val->count != 0) {
        static_val = osi_malloc(oob.static_val_len->ival[0] + 1);
        if (static_val == NULL) {
            SSV_LOGE(TAG, "malloc fail,%s,%d\n", __func__, __LINE__);
        }
        get_value_string((char *)oob.static_val->sval[0], (char *)static_val);
        prov.prov_static_oob_val = static_val;
    }
    arg_int_to_value(oob.prov_start_address, prov.prov_start_address, "provisioner start address");
    arg_int_to_value(oob.static_val_len, prov.prov_static_oob_len, "provisioner static value length");
#endif

    SSV_LOGI(TAG, "OOB:Load,OK\n");

    SSV_LOGD(TAG, "exit %s\n", __func__);
    return 0;
}

int ble_mesh_init(int argc, char **argv)
{
    int err;
    ssv_ble_mesh_comp_t *local_component = NULL;

    int nerrors = arg_parse(argc, argv, (void **) &component);
    if (nerrors != 0) {
        arg_print_errors(stderr, component.end, argv[0]);
        return 1;
    }

    SSV_LOGD(TAG, "enter %s, module %x\n", __func__, component.model_type->ival[0]);
    local_component = ble_mesh_get_component(component.model_type->ival[0]);

    err = ssv_ble_mesh_init(&prov, local_component);
    if (err) {
        SSV_LOGE(TAG, "Initializing mesh failed (err %d)\n", err);
        return err;
    }

    SSV_LOGD(TAG, "exit %s\n", __func__);
    return err;
}

int ble_mesh_provisioner_enable_bearer(int argc, char **argv)
{
    ssv_err_t  err = 0;

    SSV_LOGD(TAG, "enter %s \n", __func__);

    int nerrors = arg_parse(argc, argv, (void **) &bearer);
    if (nerrors != 0) {
        arg_print_errors(stderr, bearer.end, argv[0]);
        return 1;
    }

    if (bearer.enable->count != 0) {
        if (bearer.enable->ival[0]) {
            err = ssv_ble_mesh_provisioner_prov_enable(bearer.bearer->ival[0]);
        } else {
            err = ssv_ble_mesh_provisioner_prov_disable(bearer.bearer->ival[0]);
        }
    } else {
        return 1;
    }

    SSV_LOGD(TAG, "exit %s\n", __func__);
    return err;
}

void ble_mesh_register_node_cmd(void)
{
    oob.static_val = arg_str0("s", NULL, "<value>", "Static OOB value");
    oob.static_val_len = arg_int0("l", NULL, "<length>", "Static OOB value length");
    oob.output_size = arg_int0("x", NULL, "<size>", "Maximum size of Output OOB");
    oob.output_actions = arg_int0("o", NULL, "<actions>", "Supported Output OOB Actions");
    oob.input_size = arg_int0("y", NULL, "<size>", "Maximum size of Input OOB");
    oob.input_actions = arg_int0("i", NULL, "<actions>", "Supported Input OOB Actions");
    oob.prov_start_address = arg_int0("p", NULL, "<address>", "start address assigned by provisioner");
    oob.prov_start_address->ival[0] = 0x0005;
    oob.end = arg_end(1);

    component.model_type = arg_int0("m", NULL, "<model>", "mesh model");
    component.config_index = arg_int0("c", NULL, "<index>", "mesh model op");
    component.config_index->ival[0] = 0; // set default value
    component.pub_config = arg_int0("p", NULL, "<publish>", "publish message buffer");
    component.end = arg_end(1);

    bearer.bearer = arg_int0("b", NULL, "<bearer>", "supported bearer");
    bearer.enable = arg_int0("e", NULL, "<enable/disable>", "bearers node supported");
    bearer.end = arg_end(1);

    power_set.tx_sense_power = arg_int0("t", NULL, "<power>", "tx power or sense");
    power_set.action_type = arg_str1("z", NULL, "<action>", "action type");
    power_set.end = arg_end(1);

#if CONFIG_PERFORMANCE_CLIENT_MODEL
    node_statistices.action_type = arg_str1("z", NULL, "<action>", "action type");
    node_statistices.package_num = arg_int0("p", NULL, "<package>", "package number");
    node_statistices.end = arg_end(1);
#endif

    node_network_info.net_key = arg_str1("k", NULL, "<net key>", "network key");
    node_network_info.net_idx = arg_int1("n", NULL, "<net index>", "network key index");
    node_network_info.unicast_addr = arg_int1("u", NULL, "<unicast address>", "unicast address");
    node_network_info.dev_key = arg_str1("d", NULL, "<device key>", "device key");
    node_network_info.app_key = arg_str1("a", NULL, "<appkey>", "app key");
    node_network_info.app_idx = arg_int1("i", NULL, "<app index>", "appkey index");
    node_network_info.group_addr = arg_int1("g", NULL, "<group address>", "group address");
    node_network_info.end = arg_end(1);

}

static void ssv_ble_mesh_generic_server_cb(ssv_ble_mesh_generic_server_cb_event_t event,
                                               ssv_ble_mesh_generic_server_cb_param_t *param)
{
    SSV_LOGD(TAG, "event 0x%02x, opcode 0x%04x, src 0x%04x, dst 0x%04x",
        event, param->ctx.recv_op, param->ctx.addr, param->ctx.recv_dst);

    switch (event) {
    case SSV_BLE_MESH_GENERIC_SERVER_STATE_CHANGE_EVT:
        SSV_LOGD(TAG, "SSV_BLE_MESH_GENERIC_SERVER_STATE_CHANGE_EVT");
        if (param->ctx.recv_op == SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_SET ||
            param->ctx.recv_op == SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_SET_UNACK) {
            SSV_LOGI(TAG, "onoff 0x%02x", param->value.state_change.onoff_set.onoff);
            //todo
            //example_change_led_state(param->model, &param->ctx, param->value.state_change.onoff_set.onoff);
        }
        break;
    case SSV_BLE_MESH_GENERIC_SERVER_RECV_GET_MSG_EVT:
        SSV_LOGD(TAG, "SSV_BLE_MESH_GENERIC_SERVER_RECV_GET_MSG_EVT");
        if (param->ctx.recv_op == SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_GET) {
            //todo
            //example_handle_gen_onoff_msg(param->model, &param->ctx, NULL);
        }
        break;
    case SSV_BLE_MESH_GENERIC_SERVER_RECV_SET_MSG_EVT://rsp by app, client receive ack is in ble_mesh_generic_onoff_client_model_cb
        SSV_LOGD(TAG, "SSV_BLE_MESH_GENERIC_SERVER_RECV_SET_MSG_EVT");
        if (param->ctx.recv_op == SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_SET ||
            param->ctx.recv_op == SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_SET_UNACK) {
            ble_mesh_test_add_msg_count();

            SSV_LOGI(TAG, "onoff 0x%02x, tid 0x%02x, rx_cnt=%d, from %d",
                param->value.set.onoff.onoff, param->value.set.onoff.tid, ble_mesh_test_get_msg_count(), param->ctx.addr);
            if (param->value.set.onoff.op_en) {
                SSV_LOGI(TAG, "trans_time 0x%02x, delay 0x%02x",
                    param->value.set.onoff.trans_time, param->value.set.onoff.delay);
            }
            //OS_MsDelay(50*(OS_Random()&0x7));
            ssv_ble_mesh_relay_enable(0);
//            OS_MsDelay((bt_mesh_primary_addr()%3)*30);
            ssv_handle_gen_onoff_msg(param->model, &param->ctx, &param->value.set.onoff);
            ssv_ble_mesh_relay_enable(1);
        }
        break;
    default:
        SSV_LOGD(TAG, "Unknown Generic Server event 0x%02x", event);
        break;
    }
}

static void ssv_ble_mesh_config_server_cb(ssv_ble_mesh_cfg_server_cb_event_t event,
                                              ssv_ble_mesh_cfg_server_cb_param_t *param)
{
    if (event == SSV_BLE_MESH_CFG_SERVER_STATE_CHANGE_EVT) {
        switch (param->ctx.recv_op) {
        case SSV_BLE_MESH_MODEL_OP_APP_KEY_ADD:
            SSV_LOGD(TAG, "SSV_BLE_MESH_MODEL_OP_APP_KEY_ADD");
            SSV_LOGD(TAG, "net_idx 0x%04x, app_idx 0x%04x",
                param->value.state_change.appkey_add.net_idx,
                param->value.state_change.appkey_add.app_idx);
            SSV_LOG_BUFFER_HEX("AppKey", param->value.state_change.appkey_add.app_key, 16);
            break;
        case SSV_BLE_MESH_MODEL_OP_MODEL_APP_BIND:
            SSV_LOGD(TAG, "SSV_BLE_MESH_MODEL_OP_MODEL_APP_BIND");
            SSV_LOGD(TAG, "elem_addr 0x%04x, app_idx 0x%04x, cid 0x%04x, mod_id 0x%04x",
                param->value.state_change.mod_app_bind.element_addr,
                param->value.state_change.mod_app_bind.app_idx,
                param->value.state_change.mod_app_bind.company_id,
                param->value.state_change.mod_app_bind.model_id);
            if (param->value.state_change.mod_app_bind.company_id == 0xFFFF &&
                param->value.state_change.mod_app_bind.model_id == SSV_BLE_MESH_MODEL_ID_GEN_ONOFF_CLI) {
                node_app_idx = param->value.state_change.mod_app_bind.app_idx;
            }
            break;

        case SSV_BLE_MESH_MODEL_OP_MODEL_SUB_ADD:
           SSV_LOGD(TAG, "SSV_BLE_MESH_MODEL_OP_MODEL_SUB_ADD");
           SSV_LOGD(TAG, "elem_addr 0x%04x, sub_addr 0x%04x, cid 0x%04x, mod_id 0x%04x",
               param->value.state_change.mod_sub_add.element_addr,
               param->value.state_change.mod_sub_add.sub_addr,
               param->value.state_change.mod_sub_add.company_id,
               param->value.state_change.mod_sub_add.model_id);
           break;
        default:
            break;
        }
    }
}

static void ssv_ble_mesh_generic_client_cb(ssv_ble_mesh_generic_client_cb_event_t event,
                                               ssv_ble_mesh_generic_client_cb_param_t *param)
{
    SSV_LOGD(TAG, "%s: event is %d, error code is %d, opcode is 0x%x",
        __func__, event, param->error_code, param->params->opcode);

    switch (event) {
    case SSV_BLE_MESH_GENERIC_CLIENT_GET_STATE_EVT:
        SSV_LOGD(TAG, "SSV_BLE_MESH_GENERIC_CLIENT_GET_STATE_EVT");
        if (param->params->opcode == SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_GET) {
            SSV_LOGI(TAG, "SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_GET, onoff %d", param->status_cb.onoff_status.present_onoff);
        }
        break;
    case SSV_BLE_MESH_GENERIC_CLIENT_SET_STATE_EVT:
        SSV_LOGD(TAG, "SSV_BLE_MESH_GENERIC_CLIENT_SET_STATE_EVT");
        if (param->params->opcode == SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_SET) {
            SSV_LOGI(TAG, "SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_SET, onoff %d", param->status_cb.onoff_status.present_onoff);
        }
        break;
    case SSV_BLE_MESH_GENERIC_CLIENT_PUBLISH_EVT:
        SSV_LOGD(TAG, "SSV_BLE_MESH_GENERIC_CLIENT_PUBLISH_EVT");
        break;
    case SSV_BLE_MESH_GENERIC_CLIENT_TIMEOUT_EVT:
        SSV_LOGD(TAG, "SSV_BLE_MESH_GENERIC_CLIENT_TIMEOUT_EVT");
        if (param->params->opcode == SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_SET) {
            /* If failed to get the response of Generic OnOff Set, resend Generic OnOff Set  */
            //example_ble_mesh_send_gen_onoff_set();//todo
        }
        break;
    default:
        break;
    }

}

int ble_mesh_node_reset(int argc, char** argv)
{
    ssv_err_t err;
    SSV_LOGD(TAG, "enter %s\n", __func__);

    err = ssv_ble_mesh_node_local_reset();

    SSV_LOGD(TAG, "exit %s\n", __func__);
    return err;
}

int ble_mesh_node_suspend(int argc, char** argv)
{
    ssv_err_t err;
    SSV_LOGD(TAG, "enter %s\n", __func__);

    err = ssv_ble_mesh_node_local_suspend();

    SSV_LOGD(TAG, "exit %s\n", __func__);
    return err;
}

int ble_mesh_node_resume(int argc, char** argv)
{
    ssv_err_t err;
    SSV_LOGD(TAG, "enter %s\n", __func__);

    err = ssv_ble_mesh_node_local_resume();

    SSV_LOGD(TAG, "exit %s\n", __func__);
    return err;
}


#if CONFIG_PERFORMANCE_CLIENT_MODEL
int ble_mesh_node_statistics_regist(int argc, char **argv)
{
    int result = SSV_BM_OK;

    int nerrors = arg_parse(argc, argv, (void **) &node_statistices);
    if (nerrors != 0) {
        arg_print_errors(stderr, node_statistices.end, argv[0]);
        return 1;
    }

    SSV_LOGD(TAG, "enter %s\n", __func__);

    if (strcmp(node_statistices.action_type->sval[0], "init") == 0) {
        result = ble_mesh_node_statistics_init(node_statistices.package_num->ival[0]);
        SSV_LOGI(TAG, "Node:InitStatistics,OK\n");
    } else if (strcmp(node_statistices.action_type->sval[0], "get") == 0) {
        ble_mesh_node_statistics_get();
        SSV_LOGI(TAG, "Node:GetStatistics,OK\n");
    } else if (strcmp(node_statistices.action_type->sval[0], "destroy") == 0) {
        ble_mesh_node_statistics_destroy();
        SSV_LOGI(TAG, "Node:DestroyStatistics\n");
    }

    SSV_LOGD(TAG, "exit %s\n", __func__);
    return result;
}
#endif
int ble_mesh_node_enter_network_auto(int argc, char **argv)
{
    ssv_err_t err = SSV_BM_OK;
    struct bt_mesh_device_network_info info;

    memset(&info, 0, sizeof(info));
    int nerrors = arg_parse(argc, argv, (void **) &node_network_info);
    if (nerrors != 0) {
        arg_print_errors(stderr, node_network_info.end, argv[0]);
        return 1;
    }

    SSV_LOGD(TAG, "enter %s\n", __func__);

    arg_int_to_value(node_network_info.net_idx, info.net_idx, "network key index");
    arg_int_to_value(node_network_info.unicast_addr, info.unicast_addr, "unicast address");
    arg_int_to_value(node_network_info.app_idx, info.app_idx, "appkey index");
    arg_int_to_value(node_network_info.group_addr, info.group_addr, "group address");
    err = get_value_string((char *)node_network_info.net_key->sval[0], (char *)info.net_key);
    err = get_value_string((char *)node_network_info.dev_key->sval[0], (char *)info.dev_key);
    err = get_value_string((char *)node_network_info.app_key->sval[0], (char *)info.app_key);

    err = bt_mesh_device_auto_enter_network(&info);
    if (err == SSV_BM_OK) {
        SSV_LOGD(TAG, "NODE:EnNetwork,OK");
    } else {
        SSV_LOGE(TAG, "NODE:EnNetwork,FAIL,%d", err);
    }

    SSV_LOGD(TAG, "exit %s\n", __func__);
    return err;
}

int ble_mesh_node_enable_bearer(int argc, char **argv)
{
    ssv_err_t  err = 0;

    SSV_LOGD(TAG, "enter %s \n", __func__);

    int nerrors = arg_parse(argc, argv, (void **) &bearer);
    if (nerrors != 0) {
        arg_print_errors(stderr, bearer.end, argv[0]);
        return 1;
    }

    if (bearer.enable->count != 0) {
        if (bearer.enable->ival[0]) {
            //err = esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_N12);
            err = ssv_ble_mesh_node_prov_enable(bearer.bearer->ival[0]);
        } else {
            err = ssv_ble_mesh_node_prov_disable(bearer.bearer->ival[0]);
        }
    } else {
        return 1;
    }

    SSV_LOGD(TAG, "exit %s\n", __func__);
    return err;
}

int ble_mesh_get_publish_ack_count(int argc, char **argv)
{
    uint8_t publish_ack_count = 0;
    SSV_LOGD(TAG, "enter %s \n", __func__);
    publish_ack_count = get_publish_ack_count();
    set_publish_ack_count(0);
    SSV_LOGI(TAG, "publish_ack_count %d", publish_ack_count);
    SSV_LOGD(TAG, "exit %s\n", __func__);
    return 0;
}

