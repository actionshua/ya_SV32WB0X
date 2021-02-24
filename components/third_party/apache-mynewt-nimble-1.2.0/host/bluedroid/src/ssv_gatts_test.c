#include "ssv_gatts_test.h"
#include "ssv_gap_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btc/btc_task.h"
#include "ssv_gap_ble_api.h"
#include "ssv_gatts_api.h"
#include "ssv_bt_defs.h"
#include "ssv_gatt_common_api.h"
#include "ssv_log.h"
#include "sdkconfig.h"

#define GATTS_TAG "GATTS_DEMO"

///Declare the static function
static void gatts_profile_a_event_handler(ssv_gatts_cb_event_t event, ssv_gatt_if_t gatts_if, ssv_ble_gatts_cb_param_t *param);
static void gatts_profile_b_event_handler(ssv_gatts_cb_event_t event, ssv_gatt_if_t gatts_if, ssv_ble_gatts_cb_param_t *param);



static uint8_t char1_str[] = {0x11,0x22,0x33};
static ssv_gatt_char_prop_t a_property = 0;
static ssv_gatt_char_prop_t b_property = 0;

extern ssv_ble_adv_params_t adv_params;

static ssv_attr_value_t gatts_demo_char1_val =
{
    .attr_max_len = GATTS_DEMO_CHAR_VAL_LEN_MAX,
    .attr_len     = sizeof(char1_str),
    .attr_value   = char1_str,
};

extern uint8_t adv_config_done;

#ifdef CONFIG_SET_RAW_ADV_DATA
static uint8_t raw_adv_data[] = {
        0x02, 0x01, 0x06,
        0x02, 0x0a, 0xeb, 0x03, 0x03, 0xab, 0xcd
};
static uint8_t raw_scan_rsp_data[] = {
        0x0f, 0x09, 0x53, 0x53, 0x56, 0x5f, 0x47, 0x41, 0x54, 0x54, 0x53, 0x5f, 0x44,
        0x45, 0x4d, 0x4f
};
#else

static uint8_t adv_service_uuid128[32] = {
    /* LSB <--------------------------------------------------------------------------------> MSB */
    //first uuid, 16bit, [12],[13] is the value
    0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0xEE, 0x00, 0x00, 0x00,
    //second uuid, 32bit, [12], [13], [14], [15] is the value
    0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
};

// The length of adv data must be less than 31 bytes
//static uint8_t test_manufacturer[TEST_MANUFACTURER_DATA_LEN] =  {0x12, 0x23, 0x45, 0x56};
//adv data
static ssv_ble_adv_data_t adv_data = {
    .set_scan_rsp = false,
    .include_name = true,
    .include_txpower = false,
    .min_interval = 0x0006, //slave connection min interval, Time = min_interval * 1.25 msec
    .max_interval = 0x0010, //slave connection max interval, Time = max_interval * 1.25 msec
    .appearance = 0x00,
    .manufacturer_len = 0, //TEST_MANUFACTURER_DATA_LEN,
    .p_manufacturer_data =  NULL, //&test_manufacturer[0],
    .service_data_len = 0,
    .p_service_data = NULL,
    .service_uuid_len = sizeof(adv_service_uuid128),
    .p_service_uuid = adv_service_uuid128,
    .flag = (SSV_BLE_ADV_FLAG_GEN_DISC | SSV_BLE_ADV_FLAG_BREDR_NOT_SPT),
};
// scan response data
static ssv_ble_adv_data_t scan_rsp_data = {
    .set_scan_rsp = true,
    .include_name = true,
    .include_txpower = true,
    //.min_interval = 0x0006,
    //.max_interval = 0x0010,
    .appearance = 0x00,
    .manufacturer_len = 0, //TEST_MANUFACTURER_DATA_LEN,
    .p_manufacturer_data =  NULL, //&test_manufacturer[0],
    .service_data_len = 0,
    .p_service_data = NULL,
    .service_uuid_len = sizeof(adv_service_uuid128),
    .p_service_uuid = adv_service_uuid128,
    .flag = (SSV_BLE_ADV_FLAG_GEN_DISC | SSV_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

#endif /* CONFIG_SET_RAW_ADV_DATA */

struct gatts_profile_inst {
    ssv_gatts_cb_t gatts_cb;
    uint16_t gatts_if;
    uint16_t app_id;
    uint16_t conn_id;
    uint16_t service_handle;
    ssv_gatt_srvc_id_t service_id;
    uint16_t char_handle;
    ssv_bt_uuid_t char_uuid;
    ssv_gatt_perm_t perm;
    ssv_gatt_char_prop_t property;
    uint16_t descr_handle;
    ssv_bt_uuid_t descr_uuid;
};

/* One gatt-based profile one app_id and one gatts_if, this array will store the gatts_if returned by SSV_GATTS_REG_EVT */
static struct gatts_profile_inst gl_profile_tab[PROFILE_NUM] = {
    [PROFILE_A_APP_ID] = {
        .gatts_cb = gatts_profile_a_event_handler,
        .gatts_if = SSV_GATT_IF_NONE,       /* Not get the gatt_if, so initial is SSV_GATT_IF_NONE */
    },
    [PROFILE_B_APP_ID] = {
        .gatts_cb = gatts_profile_b_event_handler,                   /* This demo does not implement, similar as profile A */
        .gatts_if = SSV_GATT_IF_NONE,       /* Not get the gatt_if, so initial is SSV_GATT_IF_NONE */
    },
};

typedef struct {
    uint8_t                 *prepare_buf;
    int                     prepare_len;
} prepare_type_env_t;

static prepare_type_env_t a_prepare_write_env;
static prepare_type_env_t b_prepare_write_env;

void example_write_event_env(ssv_gatt_if_t gatts_if, prepare_type_env_t *prepare_write_env, ssv_ble_gatts_cb_param_t *param);
void example_exec_write_event_env(prepare_type_env_t *prepare_write_env, ssv_ble_gatts_cb_param_t *param);



void example_write_event_env(ssv_gatt_if_t gatts_if, prepare_type_env_t *prepare_write_env, ssv_ble_gatts_cb_param_t *param){
    ssv_gatt_status_t status = SSV_GATT_OK;
    if (param->write.need_rsp){
        if (param->write.is_prep){
            if (prepare_write_env->prepare_buf == NULL) {
                prepare_write_env->prepare_buf = (uint8_t *)malloc(PREPARE_BUF_MAX_SIZE*sizeof(uint8_t));
                prepare_write_env->prepare_len = 0;
                if (prepare_write_env->prepare_buf == NULL) {
                    SSV_LOGE(GATTS_TAG, "Gatt_server prep no mem\n");
                    status = SSV_GATT_NO_RESOURCES;
                }
            } else {
                if(param->write.offset > PREPARE_BUF_MAX_SIZE) {
                    status = SSV_GATT_INVALID_OFFSET;
                } else if ((param->write.offset + param->write.len) > PREPARE_BUF_MAX_SIZE) {
                    status = SSV_GATT_INVALID_ATTR_LEN;
                }
            }

            ssv_gatt_rsp_t *gatt_rsp = (ssv_gatt_rsp_t *)malloc(sizeof(ssv_gatt_rsp_t));
            gatt_rsp->attr_value.len = param->write.len;
            gatt_rsp->attr_value.handle = param->write.handle;
            gatt_rsp->attr_value.offset = param->write.offset;
            gatt_rsp->attr_value.auth_req = SSV_GATT_AUTH_REQ_NONE;
            memcpy(gatt_rsp->attr_value.value, param->write.value, param->write.len);
            ssv_err_t response_err = ssv_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, status, gatt_rsp);
            if (response_err != SSV_BM_OK){
               SSV_LOGE(GATTS_TAG, "Send response error\n");
            }
            free(gatt_rsp);
            if (status != SSV_GATT_OK){
                return;
            }
            memcpy(prepare_write_env->prepare_buf + param->write.offset,
                   param->write.value,
                   param->write.len);
            prepare_write_env->prepare_len += param->write.len;

        }else{
            ssv_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, status, NULL);
        }
    }
}

void example_exec_write_event_env(prepare_type_env_t *prepare_write_env, ssv_ble_gatts_cb_param_t *param){
    if (param->exec_write.exec_write_flag == SSV_GATT_PREP_WRITE_EXEC){
        ssv_log_buffer_hex(GATTS_TAG, prepare_write_env->prepare_buf, prepare_write_env->prepare_len);
    }else{
        SSV_LOGI(GATTS_TAG,"SSV_GATT_PREP_WRITE_CANCEL");
    }
    if (prepare_write_env->prepare_buf) {
        free(prepare_write_env->prepare_buf);
        prepare_write_env->prepare_buf = NULL;
    }
    prepare_write_env->prepare_len = 0;
}

static void gatts_profile_a_event_handler(ssv_gatts_cb_event_t event, ssv_gatt_if_t gatts_if, ssv_ble_gatts_cb_param_t *param) {
    ssv_ble_conn_update_params_t conn_params;
    SSV_LOGW(GATTS_TAG, "%s event %d\n", __FUNCTION__, event);

    switch (event) {
    case SSV_GATTS_REG_EVT:
        SSV_LOGI(GATTS_TAG, "REGISTER_APP_EVT, status %d, app_id %d\n", param->reg.status, param->reg.app_id);
        gl_profile_tab[PROFILE_A_APP_ID].service_id.is_primary = true;
        gl_profile_tab[PROFILE_A_APP_ID].service_id.id.inst_id = 0x00;
        gl_profile_tab[PROFILE_A_APP_ID].service_id.id.uuid.len = SSV_UUID_LEN_16;
        gl_profile_tab[PROFILE_A_APP_ID].service_id.id.uuid.uuid.uuid16 = GATTS_SERVICE_UUID_TEST_A;

        ssv_err_t set_dev_name_ret = ssv_ble_gap_set_device_name(TEST_DEVICE_NAME);
        if (set_dev_name_ret){
            SSV_LOGE(GATTS_TAG, "set device name failed, error code = %x", set_dev_name_ret);
        }
#ifdef CONFIG_SET_RAW_ADV_DATA
        ssv_err_t raw_adv_ret = ssv_ble_gap_config_adv_data_raw(raw_adv_data, sizeof(raw_adv_data));
        if (raw_adv_ret){
            SSV_LOGE(GATTS_TAG, "config raw adv data failed, error code = %x ", raw_adv_ret);
        }
        adv_config_done |= adv_config_flag;
        ssv_err_t raw_scan_ret = ssv_ble_gap_config_scan_rsp_data_raw(raw_scan_rsp_data, sizeof(raw_scan_rsp_data));
        if (raw_scan_ret){
            SSV_LOGE(GATTS_TAG, "config raw scan rsp data failed, error code = %x", raw_scan_ret);
        }
        adv_config_done |= scan_rsp_config_flag;
#else
        //config adv data
        ssv_err_t ret = ssv_ble_gap_config_adv_data(&adv_data);
        if (ret){
            SSV_LOGE(GATTS_TAG, "config adv data failed, error code = %x", ret);
        }
        adv_config_done |= adv_config_flag;
        //config scan response data
        ret = ssv_ble_gap_config_adv_data(&scan_rsp_data);
        if (ret){
            SSV_LOGE(GATTS_TAG, "config scan response data failed, error code = %x", ret);
        }
        adv_config_done |= scan_rsp_config_flag;

#endif
        ssv_ble_gatts_create_service(gatts_if, &gl_profile_tab[PROFILE_A_APP_ID].service_id, GATTS_NUM_HANDLE_TEST_A);
        /* SSV_GATTS_CREATE_EVT for end of ssv_ble_gatts_create_service*/
        break;
    case SSV_GATTS_READ_EVT: {
        SSV_LOGW(GATTS_TAG, "GATT_READ_EVT, conn_id %d, trans_id %d, handle %d\n", param->read.conn_id, param->read.trans_id, param->read.handle);
        ssv_gatt_rsp_t rsp;
        memset(&rsp, 0, sizeof(ssv_gatt_rsp_t));
        rsp.attr_value.handle = param->read.handle;
        rsp.attr_value.len = 4;
        rsp.attr_value.value[0] = 0xde;
        rsp.attr_value.value[1] = 0xed;
        rsp.attr_value.value[2] = 0xbe;
        rsp.attr_value.value[3] = 0xef;
        SSV_LOGW(GATTS_TAG, "GATT_READ_EVT, call ssv_ble_gatts_send_response\n");
        ssv_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id,
                                    SSV_GATT_OK, &rsp);
        break;
    }
    case SSV_GATTS_WRITE_EVT: {
        SSV_LOGW(GATTS_TAG, "GATT_WRITE_EVT, conn_id %d, trans_id %d, handle %d", param->write.conn_id, param->write.trans_id, param->write.handle);
        if (!param->write.is_prep){
            SSV_LOGW(GATTS_TAG, "GATT_WRITE_EVT, value len %d, value :", param->write.len);
            ssv_log_buffer_hex(GATTS_TAG, param->write.value, param->write.len);
            if (gl_profile_tab[PROFILE_A_APP_ID].descr_handle == param->write.handle && param->write.len == 2){
                uint16_t descr_value = param->write.value[1]<<8 | param->write.value[0];
                if (descr_value == 0x0001){
                    if (a_property & SSV_GATT_CHAR_PROP_BIT_NOTIFY){
                        SSV_LOGW(GATTS_TAG, "notify enable");
                        uint8_t notify_data[15];
                        for (int i = 0; i < sizeof(notify_data); ++i)
                        {
                            notify_data[i] = i%0xff;
                        }
                        //the size of notify_data[] need less than MTU size
                        ssv_ble_gatts_send_indicate(gatts_if, param->write.conn_id, gl_profile_tab[PROFILE_A_APP_ID].char_handle,
                                                sizeof(notify_data), notify_data, false);
                    }
                }else if (descr_value == 0x0002){
                    if (a_property & SSV_GATT_CHAR_PROP_BIT_INDICATE){
                        SSV_LOGW(GATTS_TAG, "indicate enable");
                        uint8_t indicate_data[15];
                        for (int i = 0; i < sizeof(indicate_data); ++i)
                        {
                            indicate_data[i] = i%0xff;
                        }
                        //the size of indicate_data[] need less than MTU size
                        ssv_ble_gatts_send_indicate(gatts_if, param->write.conn_id, gl_profile_tab[PROFILE_A_APP_ID].char_handle,
                                                sizeof(indicate_data), indicate_data, true);
                    }
                }
                else if (descr_value == 0x0000){
                    SSV_LOGW(GATTS_TAG, "notify/indicate disable ");
                }else{
                    SSV_LOGE(GATTS_TAG, "unknown descr value");
                    ssv_log_buffer_hex(GATTS_TAG, param->write.value, param->write.len);
                }

            }
        }
        example_write_event_env(gatts_if, &a_prepare_write_env, param);
        break;
    }
    case SSV_GATTS_EXEC_WRITE_EVT:
        SSV_LOGI(GATTS_TAG,"SSV_GATTS_EXEC_WRITE_EVT");
        ssv_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, SSV_GATT_OK, NULL);
        example_exec_write_event_env(&a_prepare_write_env, param);
        break;
    case SSV_GATTS_MTU_EVT:
        SSV_LOGI(GATTS_TAG, "SSV_GATTS_MTU_EVT, MTU %d", param->mtu.mtu);
        break;
    case SSV_GATTS_UNREG_EVT:
        break;
    case SSV_GATTS_CREATE_EVT:
        SSV_LOGI(GATTS_TAG, "CREATE_SERVICE_EVT, status %d,  service_handle %d\n", param->create.status, param->create.service_handle);
        gl_profile_tab[PROFILE_A_APP_ID].service_handle = param->create.service_handle;
        gl_profile_tab[PROFILE_A_APP_ID].char_uuid.len = SSV_UUID_LEN_16;
        gl_profile_tab[PROFILE_A_APP_ID].char_uuid.uuid.uuid16 = GATTS_CHAR_UUID_TEST_A;

        ssv_ble_gatts_start_service(gl_profile_tab[PROFILE_A_APP_ID].service_handle);
        a_property = SSV_GATT_CHAR_PROP_BIT_READ | SSV_GATT_CHAR_PROP_BIT_WRITE | SSV_GATT_CHAR_PROP_BIT_NOTIFY;
        ssv_err_t add_char_ret = ssv_ble_gatts_add_char(gl_profile_tab[PROFILE_A_APP_ID].service_handle, &gl_profile_tab[PROFILE_A_APP_ID].char_uuid,
                                                        SSV_GATT_PERM_READ | SSV_GATT_PERM_WRITE,
                                                        a_property,
                                                        &gatts_demo_char1_val, NULL);
        if (add_char_ret){
            SSV_LOGE(GATTS_TAG, "add char failed, error code =%x",add_char_ret);
        }
        break;
    case SSV_GATTS_ADD_INCL_SRVC_EVT:
        break;
    case SSV_GATTS_ADD_CHAR_EVT: {
        uint16_t length = 0;
        const uint8_t *prf_char;

        SSV_LOGI(GATTS_TAG, "ADD_CHAR_EVT, status %d,  attr_handle %d, service_handle %d\n",
                param->add_char.status, param->add_char.attr_handle, param->add_char.service_handle);
        gl_profile_tab[PROFILE_A_APP_ID].char_handle = param->add_char.attr_handle;
        gl_profile_tab[PROFILE_A_APP_ID].descr_uuid.len = SSV_UUID_LEN_16;
        gl_profile_tab[PROFILE_A_APP_ID].descr_uuid.uuid.uuid16 = SSV_GATT_UUID_CHAR_CLIENT_CONFIG;
        ssv_err_t get_attr_ret = ssv_ble_gatts_get_attr_value(param->add_char.attr_handle,  &length, &prf_char);
        if (get_attr_ret == SSV_FAIL){
            SSV_LOGE(GATTS_TAG, "ILLEGAL HANDLE");
        }

        SSV_LOGI(GATTS_TAG, "the gatts demo char length = %x\n", length);
        for(int i = 0; i < length; i++){
            SSV_LOGI(GATTS_TAG, "prf_char[%x] =%x\n",i,prf_char[i]);
        }
        ssv_err_t add_descr_ret = ssv_ble_gatts_add_char_descr(gl_profile_tab[PROFILE_A_APP_ID].service_handle, &gl_profile_tab[PROFILE_A_APP_ID].descr_uuid,
                                                                SSV_GATT_PERM_READ | SSV_GATT_PERM_WRITE, NULL, NULL);
        if (add_descr_ret){
            SSV_LOGE(GATTS_TAG, "add char descr failed, error code =%x", add_descr_ret);
        }
        break;
    }
    case SSV_GATTS_ADD_CHAR_DESCR_EVT:
        gl_profile_tab[PROFILE_A_APP_ID].descr_handle = param->add_char_descr.attr_handle;
        SSV_LOGI(GATTS_TAG, "ADD_DESCR_EVT, status %d, attr_handle %d, service_handle %d\n",
                 param->add_char_descr.status, param->add_char_descr.attr_handle, param->add_char_descr.service_handle);
        break;
    case SSV_GATTS_DELETE_EVT:
        break;
    case SSV_GATTS_START_EVT:
        SSV_LOGI(GATTS_TAG, "SERVICE_START_EVT, status %d, service_handle %d\n",
                 param->start.status, param->start.service_handle);
        break;
    case SSV_GATTS_STOP_EVT:
        break;
    case SSV_GATTS_CONNECT_EVT: {
        memcpy(conn_params.bda, param->connect.remote_bda, sizeof(ssv_bd_addr_t));
        /* For the IOS system, please reference the apple official documents about the ble connection parameters restrictions. */
        conn_params.latency = 0;
        conn_params.max_int = 0x20;    // max_int = 0x20*1.25ms = 40ms
        conn_params.min_int = 0x10;    // min_int = 0x10*1.25ms = 20ms
        conn_params.timeout = 400;    // timeout = 400*10ms = 4000ms
        SSV_LOGI(GATTS_TAG, "SSV_GATTS_CONNECT_EVT, conn_id %d, remote %02x:%02x:%02x:%02x:%02x:%02x",
                 param->connect.conn_id,
                 param->connect.remote_bda[0], param->connect.remote_bda[1], param->connect.remote_bda[2],
                 param->connect.remote_bda[3], param->connect.remote_bda[4], param->connect.remote_bda[5]);
        gl_profile_tab[PROFILE_A_APP_ID].conn_id = param->connect.conn_id;
        //start sent the update connection parameters to the peer device.
        ssv_ble_gap_update_conn_params(&conn_params);
        break;
    }
    case SSV_GATTS_DISCONNECT_EVT:
        SSV_LOGI(GATTS_TAG, "SSV_GATTS_DISCONNECT_EVT, disconnect reason 0x%x", param->disconnect.reason);
        ssv_ble_gap_start_advertising(&adv_params);
        break;
    case SSV_GATTS_CONF_EVT:
        SSV_LOGI(GATTS_TAG, "SSV_GATTS_CONF_EVT, status %d attr_handle %d", param->conf.status, param->conf.handle);
        if (param->conf.status != SSV_GATT_OK){
            ssv_log_buffer_hex(GATTS_TAG, param->conf.value, param->conf.len);
        }
        break;
    case SSV_GATTS_OPEN_EVT:
    case SSV_GATTS_CANCEL_OPEN_EVT:
    case SSV_GATTS_CLOSE_EVT:
    case SSV_GATTS_LISTEN_EVT:
    case SSV_GATTS_CONGEST_EVT:
    default:
        break;
    }
}

static void gatts_profile_b_event_handler(ssv_gatts_cb_event_t event, ssv_gatt_if_t gatts_if, ssv_ble_gatts_cb_param_t *param) {
    switch (event) {
    case SSV_GATTS_REG_EVT:
        SSV_LOGI(GATTS_TAG, "REGISTER_APP_EVT, status %d, app_id %d\n", param->reg.status, param->reg.app_id);
        gl_profile_tab[PROFILE_B_APP_ID].service_id.is_primary = true;
        gl_profile_tab[PROFILE_B_APP_ID].service_id.id.inst_id = 0x00;
        gl_profile_tab[PROFILE_B_APP_ID].service_id.id.uuid.len = SSV_UUID_LEN_16;
        gl_profile_tab[PROFILE_B_APP_ID].service_id.id.uuid.uuid.uuid16 = GATTS_SERVICE_UUID_TEST_B;

        ssv_ble_gatts_create_service(gatts_if, &gl_profile_tab[PROFILE_B_APP_ID].service_id, GATTS_NUM_HANDLE_TEST_B);
        break;
    case SSV_GATTS_READ_EVT: {
        SSV_LOGI(GATTS_TAG, "GATT_READ_EVT, conn_id %d, trans_id %d, handle %d\n", param->read.conn_id, param->read.trans_id, param->read.handle);
        ssv_gatt_rsp_t rsp;
        memset(&rsp, 0, sizeof(ssv_gatt_rsp_t));
        rsp.attr_value.handle = param->read.handle;
        rsp.attr_value.len = 4;
        rsp.attr_value.value[0] = 0xde;
        rsp.attr_value.value[1] = 0xed;
        rsp.attr_value.value[2] = 0xbe;
        rsp.attr_value.value[3] = 0xef;
        ssv_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id,
                                    SSV_GATT_OK, &rsp);
        break;
    }
    case SSV_GATTS_WRITE_EVT: {
        SSV_LOGI(GATTS_TAG, "GATT_WRITE_EVT, conn_id %d, trans_id %d, handle %d\n", param->write.conn_id, param->write.trans_id, param->write.handle);
        if (!param->write.is_prep){
            SSV_LOGI(GATTS_TAG, "GATT_WRITE_EVT, value len %d, value :", param->write.len);
            ssv_log_buffer_hex(GATTS_TAG, param->write.value, param->write.len);
            if (gl_profile_tab[PROFILE_B_APP_ID].descr_handle == param->write.handle && param->write.len == 2){
                uint16_t descr_value= param->write.value[1]<<8 | param->write.value[0];
                if (descr_value == 0x0001){
                    if (b_property & SSV_GATT_CHAR_PROP_BIT_NOTIFY){
                        SSV_LOGI(GATTS_TAG, "notify enable");
                        uint8_t notify_data[15];
                        for (int i = 0; i < sizeof(notify_data); ++i)
                        {
                            notify_data[i] = i%0xff;
                        }
                        //the size of notify_data[] need less than MTU size
                        ssv_ble_gatts_send_indicate(gatts_if, param->write.conn_id, gl_profile_tab[PROFILE_B_APP_ID].char_handle,
                                                sizeof(notify_data), notify_data, false);
                    }
                }else if (descr_value == 0x0002){
                    if (b_property & SSV_GATT_CHAR_PROP_BIT_INDICATE){
                        SSV_LOGI(GATTS_TAG, "indicate enable");
                        uint8_t indicate_data[15];
                        for (int i = 0; i < sizeof(indicate_data); ++i)
                        {
                            indicate_data[i] = i%0xff;
                        }
                        //the size of indicate_data[] need less than MTU size
                        ssv_ble_gatts_send_indicate(gatts_if, param->write.conn_id, gl_profile_tab[PROFILE_B_APP_ID].char_handle,
                                                sizeof(indicate_data), indicate_data, true);
                    }
                }
                else if (descr_value == 0x0000){
                    SSV_LOGI(GATTS_TAG, "notify/indicate disable ");
                }else{
                    SSV_LOGE(GATTS_TAG, "unknown value");
                }

            }
        }
        example_write_event_env(gatts_if, &b_prepare_write_env, param);
        break;
    }
    case SSV_GATTS_EXEC_WRITE_EVT:
        SSV_LOGI(GATTS_TAG,"SSV_GATTS_EXEC_WRITE_EVT");
        ssv_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, SSV_GATT_OK, NULL);
        example_exec_write_event_env(&b_prepare_write_env, param);
        break;
    case SSV_GATTS_MTU_EVT:
        SSV_LOGI(GATTS_TAG, "SSV_GATTS_MTU_EVT, MTU %d", param->mtu.mtu);
        break;
    case SSV_GATTS_UNREG_EVT:
        break;
    case SSV_GATTS_CREATE_EVT:
        SSV_LOGI(GATTS_TAG, "CREATE_SERVICE_EVT, status %d,  service_handle %d\n", param->create.status, param->create.service_handle);
        gl_profile_tab[PROFILE_B_APP_ID].service_handle = param->create.service_handle;
        gl_profile_tab[PROFILE_B_APP_ID].char_uuid.len = SSV_UUID_LEN_16;
        gl_profile_tab[PROFILE_B_APP_ID].char_uuid.uuid.uuid16 = GATTS_CHAR_UUID_TEST_B;

        /*ssv_ble_gatts_start_service(gl_profile_tab[PROFILE_B_APP_ID].service_handle);
        b_property = SSV_GATT_CHAR_PROP_BIT_READ | SSV_GATT_CHAR_PROP_BIT_WRITE | SSV_GATT_CHAR_PROP_BIT_NOTIFY;
        ssv_err_t add_char_ret =ssv_ble_gatts_add_char( gl_profile_tab[PROFILE_B_APP_ID].service_handle, &gl_profile_tab[PROFILE_B_APP_ID].char_uuid,
                                                        SSV_GATT_PERM_READ | SSV_GATT_PERM_WRITE,
                                                        b_property,
                                                        NULL, NULL);
        if (add_char_ret){
            SSV_LOGE(GATTS_TAG, "add char failed, error code =%x",add_char_ret);
        }*/
        break;
    case SSV_GATTS_ADD_INCL_SRVC_EVT:
        break;
    case SSV_GATTS_ADD_CHAR_EVT:
        SSV_LOGI(GATTS_TAG, "ADD_CHAR_EVT, status %d,  attr_handle %d, service_handle %d\n",
                 param->add_char.status, param->add_char.attr_handle, param->add_char.service_handle);

        gl_profile_tab[PROFILE_B_APP_ID].char_handle = param->add_char.attr_handle;
        gl_profile_tab[PROFILE_B_APP_ID].descr_uuid.len = SSV_UUID_LEN_16;
        gl_profile_tab[PROFILE_B_APP_ID].descr_uuid.uuid.uuid16 = SSV_GATT_UUID_CHAR_CLIENT_CONFIG;
        ssv_ble_gatts_add_char_descr(gl_profile_tab[PROFILE_B_APP_ID].service_handle, &gl_profile_tab[PROFILE_B_APP_ID].descr_uuid,
                                     SSV_GATT_PERM_READ | SSV_GATT_PERM_WRITE,
                                     NULL, NULL);
        break;
    case SSV_GATTS_ADD_CHAR_DESCR_EVT:
        gl_profile_tab[PROFILE_B_APP_ID].descr_handle = param->add_char_descr.attr_handle;
        SSV_LOGI(GATTS_TAG, "ADD_DESCR_EVT, status %d, attr_handle %d, service_handle %d\n",
                 param->add_char_descr.status, param->add_char_descr.attr_handle, param->add_char_descr.service_handle);
        break;
    case SSV_GATTS_DELETE_EVT:
        break;
    case SSV_GATTS_START_EVT:
        SSV_LOGI(GATTS_TAG, "SERVICE_START_EVT, status %d, service_handle %d\n",
                 param->start.status, param->start.service_handle);
        break;
    case SSV_GATTS_STOP_EVT:
        break;
    case SSV_GATTS_CONNECT_EVT:
        SSV_LOGI(GATTS_TAG, "CONNECT_EVT, conn_id %d, remote %02x:%02x:%02x:%02x:%02x:%02x:",
                 param->connect.conn_id,
                 param->connect.remote_bda[0], param->connect.remote_bda[1], param->connect.remote_bda[2],
                 param->connect.remote_bda[3], param->connect.remote_bda[4], param->connect.remote_bda[5]);
        gl_profile_tab[PROFILE_B_APP_ID].conn_id = param->connect.conn_id;
        break;
    case SSV_GATTS_CONF_EVT:
        SSV_LOGI(GATTS_TAG, "SSV_GATTS_CONF_EVT status %d attr_handle %d", param->conf.status, param->conf.handle);
        if (param->conf.status != SSV_GATT_OK){
            ssv_log_buffer_hex(GATTS_TAG, param->conf.value, param->conf.len);
        }
    break;
    case SSV_GATTS_DISCONNECT_EVT:
    case SSV_GATTS_OPEN_EVT:
    case SSV_GATTS_CANCEL_OPEN_EVT:
    case SSV_GATTS_CLOSE_EVT:
    case SSV_GATTS_LISTEN_EVT:
    case SSV_GATTS_CONGEST_EVT:
    default:
        break;
    }
}

static void gatts_event_handler(ssv_gatts_cb_event_t event, ssv_gatt_if_t gatts_if, ssv_ble_gatts_cb_param_t *param)
{
    SSV_LOGW(GATTS_TAG, "%s event %d, gatts_if %d\n", __FUNCTION__, event, gatts_if);
    /* If event is register event, store the gatts_if for each profile */
    if (event == SSV_GATTS_REG_EVT) {
        if (param->reg.status == SSV_GATT_OK) {
            gl_profile_tab[param->reg.app_id].gatts_if = gatts_if;
        } else {
            SSV_LOGI(GATTS_TAG, "Reg app failed, app_id %04x, status %d\n",
                    param->reg.app_id,
                    param->reg.status);
            return;
        }
    }

    /* If the gatts_if equal to profile A, call profile A cb handler,
     * so here call each profile's callback */
    do {
        int idx;
        for (idx = 0; idx < PROFILE_NUM; idx++) {
            if (gatts_if == SSV_GATT_IF_NONE || /* SSV_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
                    gatts_if == gl_profile_tab[idx].gatts_if) {
                if (gl_profile_tab[idx].gatts_cb) {
                    gl_profile_tab[idx].gatts_cb(event, gatts_if, param);
                }
            }
        }
    } while (0);
}

void gatts_app_main(void)
{
    ssv_err_t ret;

    ret = ssv_ble_gatts_register_callback(gatts_event_handler);
    if (ret){
        SSV_LOGE(GATTS_TAG, "gatts register error, error code = %x", ret);
        return;
    }
    ret = ssv_ble_gap_register_callback(gap_event_handler);
    if (ret){
        SSV_LOGE(GATTS_TAG, "gap register error, error code = %x", ret);
        return;
    }
    ret = ssv_ble_gatts_app_register(PROFILE_A_APP_ID);
    if (ret){
        SSV_LOGE(GATTS_TAG, "gatts app register error, error code = %x", ret);
        return;
    }
    /*ret = ssv_ble_gatts_app_register(PROFILE_B_APP_ID);
    if (ret){
        SSV_LOGE(GATTS_TAG, "gatts app register error, error code = %x", ret);
        return;
    }
    ssv_err_t local_mtu_ret = ssv_ble_gatt_set_local_mtu(500);
    if (local_mtu_ret){
        SSV_LOGE(GATTS_TAG, "set local  MTU failed, error code = %x", local_mtu_ret);
    }*/

    return;
}

void ble_gatts_test_run()
{
    int rc;
    rc = btc_init();
    if (rc != 0) {
        SSV_LOGE(GATTS_TAG,"%s btc_init err %d\n", __func__, rc);
        return;
    }
    gatts_app_main();
}
