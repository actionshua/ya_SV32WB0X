#include "ssv_gap_test.h"
#include "ssv_gattc_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btc/btc_task.h"
#include "ssv_gap_ble_api.h"
#include "ssv_gattc_api.h"
#include "ssv_bt_defs.h"
#include "ssv_gatt_common_api.h"
#include "ssv_log.h"
#include "sdkconfig.h"

#define GATTC_TAG "GATTC_DEMO"

static bool connect    = false;
static bool get_server = false;
static ssv_gattc_char_elem_t *char_elem_result   = NULL;
static ssv_gattc_descr_elem_t *descr_elem_result = NULL;


#if BLE_GATTC_EN
static void ssv_gattc_cb(ssv_gattc_cb_event_t event, ssv_gatt_if_t gattc_if, ssv_ble_gattc_cb_param_t *param);
static void gattc_profile_event_handler(ssv_gattc_cb_event_t event, ssv_gatt_if_t gattc_if, ssv_ble_gattc_cb_param_t *param);
#endif
static ssv_bt_uuid_t remote_filter_service_uuid = {
    .len = SSV_UUID_LEN_16,
    .uuid = {.uuid16 = REMOTE_SERVICE_UUID,},
};

static ssv_bt_uuid_t remote_filter_char_uuid = {
    .len = SSV_UUID_LEN_16,
    .uuid = {.uuid16 = REMOTE_NOTIFY_CHAR_UUID,},
};

static ssv_bt_uuid_t notify_descr_uuid = {
    .len = SSV_UUID_LEN_16,
    .uuid = {.uuid16 = SSV_GATT_UUID_CHAR_CLIENT_CONFIG,},
};

static ssv_ble_scan_params_t ble_scan_params = {
    .scan_type              = BLE_SCAN_TYPE_ACTIVE,
    .own_addr_type          = BLE_ADDR_TYPE_PUBLIC,
    .scan_filter_policy     = BLE_SCAN_FILTER_ALLOW_ALL,
    .scan_interval          = 0x50,
    .scan_window            = 0x30,
    .scan_duplicate         = BLE_SCAN_DUPLICATE_DISABLE
};
#if BLE_GATTC_EN
/* One gatt-based profile one app_id and one gattc_if, this array will store the gattc_if returned by SSV_GATTS_REG_EVT */
struct gattc_profile_inst gattc_gl_profile_tab[GATTC_PROFILE_NUM] = {
    [GATTC_PROFILE_A_APP_ID] = {
        .gattc_cb = gattc_profile_event_handler,
        .gattc_if = SSV_GATT_IF_NONE,       /* Not get the gatt_if, so initial is SSV_GATT_IF_NONE */
    },
};

static void gattc_profile_event_handler(ssv_gattc_cb_event_t event, ssv_gatt_if_t gattc_if, ssv_ble_gattc_cb_param_t *param)
{
    ssv_ble_gattc_cb_param_t *p_data = (ssv_ble_gattc_cb_param_t *)param;

    switch (event) {
    case SSV_GATTC_REG_EVT:
        SSV_LOGI(GATTC_TAG, "REG_EVT");
        ssv_err_t scan_ret = ssv_ble_gap_set_scan_params(&ble_scan_params);
        if (scan_ret){
            SSV_LOGE(GATTC_TAG, "set scan params error, error code = %x", scan_ret);
        }
        break;
    case SSV_GATTC_CONNECT_EVT:{
        SSV_LOGI(GATTC_TAG, "SSV_GATTC_CONNECT_EVT conn_id %d, if %d", p_data->connect.conn_id, gattc_if);
        gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].conn_id = p_data->connect.conn_id;
        memcpy(gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].remote_bda, p_data->connect.remote_bda, sizeof(ssv_bd_addr_t));
        SSV_LOGI(GATTC_TAG, "REMOTE BDA: %02X:%02X:%02X:%02X:%02X:%02X",
            gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].remote_bda[5],
            gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].remote_bda[4],
            gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].remote_bda[3],
            gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].remote_bda[2],
            gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].remote_bda[1],
            gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].remote_bda[0]);
        //ssv_log_buffer_hex(GATTC_TAG, gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].remote_bda, sizeof(ssv_bd_addr_t));
        ssv_err_t mtu_ret = ssv_ble_gattc_send_mtu_req (gattc_if, p_data->connect.conn_id);
        if (mtu_ret){
            SSV_LOGE(GATTC_TAG, "config MTU error, error code = %x", mtu_ret);
        }
        break;
    }
    case SSV_GATTC_OPEN_EVT:
        if (param->open.status != SSV_GATT_OK){
            SSV_LOGE(GATTC_TAG, "open failed, status %d", p_data->open.status);
            break;
        }
        SSV_LOGI(GATTC_TAG, "open success");
        break;
    case SSV_GATTC_DIS_SRVC_CMPL_EVT:
        if (param->dis_srvc_cmpl.status != SSV_GATT_OK){
            SSV_LOGE(GATTC_TAG, "discover service failed, status %d", param->dis_srvc_cmpl.status);
            break;
        }
        SSV_LOGI(GATTC_TAG, "discover service complete conn_id %d", param->dis_srvc_cmpl.conn_id);
        ssv_ble_gattc_search_service(gattc_if, param->cfg_mtu.conn_id, &remote_filter_service_uuid);
        break;
    case SSV_GATTC_CFG_MTU_EVT:
        if (param->cfg_mtu.status != SSV_GATT_OK){
            SSV_LOGE(GATTC_TAG,"config mtu failed, error status = %x", param->cfg_mtu.status);
        }
        SSV_LOGI(GATTC_TAG, "SSV_GATTC_CFG_MTU_EVT, Status %d, MTU %d, conn_id %d", param->cfg_mtu.status, param->cfg_mtu.mtu, param->cfg_mtu.conn_id);
        break;
    case SSV_GATTC_SEARCH_RES_EVT: {
        SSV_LOGI(GATTC_TAG, "SEARCH RES: conn_id = %x is primary service %d", p_data->search_res.conn_id, p_data->search_res.is_primary);
        SSV_LOGI(GATTC_TAG, "start handle %d end handle %d current handle value %d", p_data->search_res.start_handle, p_data->search_res.end_handle, p_data->search_res.srvc_id.inst_id);
        if (p_data->search_res.srvc_id.uuid.len == SSV_UUID_LEN_16 && p_data->search_res.srvc_id.uuid.uuid.uuid16 == REMOTE_SERVICE_UUID) {
            SSV_LOGI(GATTC_TAG, "service found");
            get_server = true;
            gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].service_start_handle = p_data->search_res.start_handle;
            gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].service_end_handle = p_data->search_res.end_handle;
            SSV_LOGI(GATTC_TAG, "UUID16: %x", p_data->search_res.srvc_id.uuid.uuid.uuid16);
        }
        break;
    }
    case SSV_GATTC_SEARCH_CMPL_EVT:
        if (p_data->search_cmpl.status != SSV_GATT_OK){
            SSV_LOGE(GATTC_TAG, "search service failed, error status = %x", p_data->search_cmpl.status);
            break;
        }
        if(p_data->search_cmpl.searched_service_source == SSV_GATT_SERVICE_FROM_REMOTE_DEVICE) {
            SSV_LOGI(GATTC_TAG, "Get service information from remote device");
        } else if (p_data->search_cmpl.searched_service_source == SSV_GATT_SERVICE_FROM_NVS_FLASH) {
            SSV_LOGI(GATTC_TAG, "Get service information from flash");
        } else {
            SSV_LOGI(GATTC_TAG, "unknown service source");
        }
        SSV_LOGI(GATTC_TAG, "SSV_GATTC_SEARCH_CMPL_EVT");
        if (get_server){
            uint16_t count = 0;
            ssv_gatt_status_t status = ssv_ble_gattc_get_attr_count( gattc_if,
                                                                     p_data->search_cmpl.conn_id,
                                                                     SSV_GATT_DB_CHARACTERISTIC,
                                                                     gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].service_start_handle,
                                                                     gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].service_end_handle,
                                                                     INVALID_HANDLE,
                                                                     &count);
            if (status != SSV_GATT_OK){
                SSV_LOGE(GATTC_TAG, "ssv_ble_gattc_get_attr_count error");
            }

            if (count > 0){
                char_elem_result = (ssv_gattc_char_elem_t *)malloc(sizeof(ssv_gattc_char_elem_t) * count);
                if (!char_elem_result){
                    SSV_LOGE(GATTC_TAG, "gattc no mem");
                }else{
                    status = ssv_ble_gattc_get_char_by_uuid( gattc_if,
                                                             p_data->search_cmpl.conn_id,
                                                             gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].service_start_handle,
                                                             gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].service_end_handle,
                                                             remote_filter_char_uuid,
                                                             char_elem_result,
                                                             &count);
                    if (status != SSV_GATT_OK){
                        SSV_LOGE(GATTC_TAG, "ssv_ble_gattc_get_char_by_uuid error");
                    }

                    /*  Every service have only one char in our 'SSV_GATTS_DEMO' demo, so we used first 'char_elem_result' */
                    if (count > 0 && (char_elem_result[0].properties & SSV_GATT_CHAR_PROP_BIT_NOTIFY)){
                        gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].char_handle = char_elem_result[0].char_handle;
                        ssv_ble_gattc_register_for_notify (gattc_if, gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].remote_bda, char_elem_result[0].char_handle);
                    }
                }
                /* free char_elem_result */
                free(char_elem_result);
            }else{
                SSV_LOGE(GATTC_TAG, "no char found");
            }
        }
         break;
    case SSV_GATTC_REG_FOR_NOTIFY_EVT: {
        SSV_LOGI(GATTC_TAG, "SSV_GATTC_REG_FOR_NOTIFY_EVT");
        if (p_data->reg_for_notify.status != SSV_GATT_OK){
            SSV_LOGE(GATTC_TAG, "REG FOR NOTIFY failed: error status = %d", p_data->reg_for_notify.status);
        }else{
            uint16_t count = 0;
            uint16_t notify_en = 1;
            ssv_gatt_status_t ret_status = ssv_ble_gattc_get_attr_count( gattc_if,
                                                                         gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].conn_id,
                                                                         SSV_GATT_DB_DESCRIPTOR,
                                                                         gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].service_start_handle,
                                                                         gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].service_end_handle,
                                                                         gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].char_handle,
                                                                         &count);
            if (ret_status != SSV_GATT_OK){
                SSV_LOGE(GATTC_TAG, "ssv_ble_gattc_get_attr_count error");
            }
            if (count > 0){
                descr_elem_result = malloc(sizeof(ssv_gattc_descr_elem_t) * count);
                if (!descr_elem_result){
                    SSV_LOGE(GATTC_TAG, "malloc error, gattc no mem");
                }else{
                    ret_status = ssv_ble_gattc_get_descr_by_char_handle( gattc_if,
                                                                         gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].conn_id,
                                                                         p_data->reg_for_notify.handle,
                                                                         notify_descr_uuid,
                                                                         descr_elem_result,
                                                                         &count);
                    if (ret_status != SSV_GATT_OK){
                        SSV_LOGE(GATTC_TAG, "ssv_ble_gattc_get_descr_by_char_handle error");
                    }
                    /* Every char has only one descriptor in our 'SSV_GATTS_DEMO' demo, so we used first 'descr_elem_result' */
                    if (count > 0 && descr_elem_result[0].uuid.len == SSV_UUID_LEN_16 && descr_elem_result[0].uuid.uuid.uuid16 == SSV_GATT_UUID_CHAR_CLIENT_CONFIG){
                        ret_status = ssv_ble_gattc_write_char_descr( gattc_if,
                                                                     gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].conn_id,
                                                                     descr_elem_result[0].handle,
                                                                     sizeof(notify_en),
                                                                     (uint8_t *)&notify_en,
                                                                     SSV_GATT_WRITE_TYPE_RSP,
                                                                     SSV_GATT_AUTH_REQ_NONE);
                    }

                    if (ret_status != SSV_GATT_OK){
                        SSV_LOGE(GATTC_TAG, "ssv_ble_gattc_write_char_descr error");
                    }

                    /* free descr_elem_result */
                    free(descr_elem_result);
                }
            }
            else{
                SSV_LOGE(GATTC_TAG, "decsr not found");
            }

        }
        break;
    }
    case SSV_GATTC_NOTIFY_EVT:
        if (p_data->notify.is_notify){
            SSV_LOGI(GATTC_TAG, "SSV_GATTC_NOTIFY_EVT, receive notify value:");
        }else{
            SSV_LOGI(GATTC_TAG, "SSV_GATTC_NOTIFY_EVT, receive indicate value:");
        }
        ssv_log_buffer_hex(GATTC_TAG, p_data->notify.value, p_data->notify.value_len);
        break;
    case SSV_GATTC_WRITE_DESCR_EVT:
        if (p_data->write.status != SSV_GATT_OK){
            SSV_LOGE(GATTC_TAG, "write descr failed, error status = %x", p_data->write.status);
            break;
        }
        SSV_LOGI(GATTC_TAG, "write descr success ");
        uint8_t write_char_data[35];
        for (int i = 0; i < sizeof(write_char_data); ++i)
        {
            write_char_data[i] = i % 256;
        }
        ssv_ble_gattc_write_char( gattc_if,
                                  gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].conn_id,
                                  gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].char_handle,
                                  sizeof(write_char_data),
                                  write_char_data,
                                  SSV_GATT_WRITE_TYPE_RSP,
                                  SSV_GATT_AUTH_REQ_NONE);
        break;
    case SSV_GATTC_SRVC_CHG_EVT: {
        ssv_bd_addr_t bda;
        memcpy(bda, p_data->srvc_chg.remote_bda, sizeof(ssv_bd_addr_t));
        SSV_LOGI(GATTC_TAG, "SSV_GATTC_SRVC_CHG_EVT, bd_addr:");
        ssv_log_buffer_hex(GATTC_TAG, bda, sizeof(ssv_bd_addr_t));
        break;
    }
    case SSV_GATTC_WRITE_CHAR_EVT:
        if (p_data->write.status != SSV_GATT_OK){
            SSV_LOGE(GATTC_TAG, "write char failed, error status = %x", p_data->write.status);
            break;
        }
        SSV_LOGI(GATTC_TAG, "write char success ");
        break;
    case SSV_GATTC_DISCONNECT_EVT:
        connect = false;
        get_server = false;
        SSV_LOGI(GATTC_TAG, "SSV_GATTC_DISCONNECT_EVT, reason = %d", p_data->disconnect.reason);
        break;
    default:
        break;
    }
}
#endif
static void ssv_gattc_cb(ssv_gattc_cb_event_t event, ssv_gatt_if_t gattc_if, ssv_ble_gattc_cb_param_t *param)
{
    /* If event is register event, store the gattc_if for each profile */
    if (event == SSV_GATTC_REG_EVT) {
        if (param->reg.status == SSV_GATT_OK) {
            gattc_gl_profile_tab[param->reg.app_id].gattc_if = gattc_if;
        } else {
            SSV_LOGI(GATTC_TAG, "reg app failed, app_id %04x, status %d",
                    param->reg.app_id,
                    param->reg.status);
            return;
        }
    }

    /* If the gattc_if equal to profile A, call profile A cb handler,
     * so here call each profile's callback */
    do {
        int idx;
        for (idx = 0; idx < GATTC_PROFILE_NUM; idx++) {
            if (gattc_if == SSV_GATT_IF_NONE || /* SSV_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
                    gattc_if == gattc_gl_profile_tab[idx].gattc_if) {
                if (gattc_gl_profile_tab[idx].gattc_cb) {
                    gattc_gl_profile_tab[idx].gattc_cb(event, gattc_if, param);
                }
            }
        }
    } while (0);
}

void gatc_app_main(void)
{
    ssv_err_t ret = 0;

    //register the  callback function to the gap module
    ret = ssv_ble_gap_register_callback(gap_event_handler);
    if (ret){
        SSV_LOGE(GATTC_TAG, "%s gap register failed, error code = %x\n", __func__, ret);
        return;
    }

    //register the callback function to the gattc module
    ret = ssv_ble_gattc_register_callback(ssv_gattc_cb);
    if(ret){
        SSV_LOGE(GATTC_TAG, "%s gattc register failed, error code = %x\n", __func__, ret);
        return;
    }


    ret = ssv_ble_gattc_app_register(GATTC_PROFILE_A_APP_ID);
    if (ret){
        SSV_LOGE(GATTC_TAG, "%s gattc app register failed, error code = %x\n", __func__, ret);
    }
    ssv_err_t local_mtu_ret = ssv_ble_gatt_set_local_mtu(500);
    if (local_mtu_ret){
        SSV_LOGE(GATTC_TAG, "set local  MTU failed, error code = %x", local_mtu_ret);
    }

}

void ble_gattc_test_run()
{
    int rc;
    rc = btc_init();
    if (rc != 0) {
        SSV_LOGE(GATTC_TAG,"%s btc_init err %d\n", __func__, rc);
        return;
    }

    gatc_app_main();
}
