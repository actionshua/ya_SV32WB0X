#include "ssv_gap_test.h"
#include "ssv_gattc_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btc/btc_task.h"
#include "ssv_gap_ble_api.h"
#include "ssv_gatts_api.h"
#include "ssv_gattc_api.h"
#include "ssv_bt_defs.h"
#include "ssv_gatt_common_api.h"
#include "ssv_log.h"
#include "sdkconfig.h"

#define GAP_TAG "GAP_DEMO"
static const char remote_device_name[] = "ssvgattsdemo";
static bool connect    = false;
uint8_t adv_config_done = 0;

/* One gatt-based profile one app_id and one gattc_if, this array will store the gattc_if returned by ESP_GATTS_REG_EVT */
extern struct gattc_profile_inst gattc_gl_profile_tab[GATTC_PROFILE_NUM];

ssv_ble_adv_params_t adv_params = {
    .adv_int_min        = 0x20,
    .adv_int_max        = 0x40,
    .adv_type           = ADV_TYPE_IND,
    .own_addr_type      = BLE_ADDR_TYPE_PUBLIC,
    //.peer_addr            =
    //.peer_addr_type       =
    .channel_map        = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

void gap_event_handler(ssv_gap_ble_cb_event_t event, ssv_ble_gap_cb_param_t *param)
{
    uint8_t *adv_name = NULL;
    uint8_t adv_name_len = 0;

    //SSV_LOGW(GAP_TAG, "%s event %d\n", __FUNCTION__, event);
    switch (event) {
#ifdef CONFIG_SET_RAW_ADV_DATA
    case SSV_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:
        adv_config_done &= (~adv_config_flag);
        if (adv_config_done==0){
            ssv_ble_gap_start_advertising(&adv_params);
        }
        break;
    case SSV_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT:
        adv_config_done &= (~scan_rsp_config_flag);
        if (adv_config_done==0){
            ssv_ble_gap_start_advertising(&adv_params);
        }
        break;
#else
    case SSV_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
        adv_config_done &= (~adv_config_flag);
        if (adv_config_done == 0){
            ssv_ble_gap_start_advertising(&adv_params);
        }
        break;
    case SSV_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
        adv_config_done &= (~scan_rsp_config_flag);
        if (adv_config_done == 0){
            ssv_ble_gap_start_advertising(&adv_params);
        }
        break;
#endif
    case SSV_GAP_BLE_ADV_START_COMPLETE_EVT:
        //advertising start complete event to indicate advertising start successfully or failed
        if (param->adv_start_cmpl.status != SSV_BT_STATUS_SUCCESS) {
            SSV_LOGE(GAP_TAG, "Advertising start failed\n");
        } else
            SSV_LOGE(GAP_TAG, "Advertising start success\n");
        break;
    case SSV_GAP_BLE_ADV_STOP_COMPLETE_EVT:
        if (param->adv_stop_cmpl.status != SSV_BT_STATUS_SUCCESS) {
            SSV_LOGE(GAP_TAG, "Advertising stop failed\n");
        } else {
            SSV_LOGI(GAP_TAG, "Stop adv successfully\n");
        }
        break;
    case SSV_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
         SSV_LOGI(GAP_TAG, "update connection params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d",
                  param->update_conn_params.status,
                  param->update_conn_params.min_int,
                  param->update_conn_params.max_int,
                  param->update_conn_params.conn_int,
                  param->update_conn_params.latency,
                  param->update_conn_params.timeout);
        break;

    case SSV_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT: {
            //the unit of the duration is second
            uint32_t duration = 30;
            ssv_ble_gap_start_scanning(duration);
            break;
        }

    case SSV_GAP_BLE_SCAN_START_COMPLETE_EVT:
        //scan start complete event to indicate scan start successfully or failed
        if (param->scan_start_cmpl.status != SSV_BT_STATUS_SUCCESS) {
            SSV_LOGE(GAP_TAG, "scan start failed, error status = %x", param->scan_start_cmpl.status);
            break;
        }
        SSV_LOGI(GAP_TAG, "scan start success");

        break;
    case SSV_GAP_BLE_SCAN_RESULT_EVT: {
        ssv_ble_gap_cb_param_t *scan_result = (ssv_ble_gap_cb_param_t *)param;
        switch (scan_result->scan_rst.search_evt) {
            case SSV_GAP_SEARCH_INQ_RES_EVT:
                SSV_LOGI(GAP_TAG, "bd addr %02X:%02X:%02X:%02X:%02X:%02X",
                    scan_result->scan_rst.bda[5], scan_result->scan_rst.bda[4], scan_result->scan_rst.bda[3],
                    scan_result->scan_rst.bda[2], scan_result->scan_rst.bda[1], scan_result->scan_rst.bda[0]);
                //ssv_log_buffer_hex(GAP_TAG, scan_result->scan_rst.bda, 6);
                SSV_LOGI(GAP_TAG, "searched Adv Data Len %d, Scan Response Len %d", scan_result->scan_rst.adv_data_len, scan_result->scan_rst.scan_rsp_len);
                adv_name = ssv_ble_resolve_adv_data(scan_result->scan_rst.ble_adv,
                                                    SSV_BLE_AD_TYPE_NAME_CMPL, &adv_name_len);
                SSV_LOGI(GAP_TAG, "searched Device Name Len %d", adv_name_len);
                ssv_log_buffer_char(GAP_TAG, adv_name, adv_name_len);

    #if CONFIG_EXAMPLE_DUMP_ADV_DATA_AND_SCAN_RESP
                if (scan_result->scan_rst.adv_data_len > 0) {
                    SSV_LOGI(GAP_TAG, "adv data:");
                    ssv_log_buffer_hex(GAP_TAG, &scan_result->scan_rst.ble_adv[0], scan_result->scan_rst.adv_data_len);
                }
                if (scan_result->scan_rst.scan_rsp_len > 0) {
                    SSV_LOGI(GAP_TAG, "scan resp:");
                    ssv_log_buffer_hex(GAP_TAG, &scan_result->scan_rst.ble_adv[scan_result->scan_rst.adv_data_len], scan_result->scan_rst.scan_rsp_len);
                }
    #endif
                SSV_LOGI(GAP_TAG, "\n");

                if (adv_name != NULL) {
                    if (strlen(remote_device_name) == adv_name_len && strncmp((char *)adv_name, remote_device_name, adv_name_len) == 0) {
                        SSV_LOGI(GAP_TAG, "searched device %s\n", remote_device_name);
                        if (connect == false) {
                            connect = true;
                            SSV_LOGI(GAP_TAG, "connect to the remote device.");
                            ssv_ble_gap_stop_scanning();
                            #if BLE_GATTC_EN
                            SSV_LOGI(GAP_TAG, "connect bd addr %02X:%02X:%02X:%02X:%02X:%02X",
                                scan_result->scan_rst.bda[5], scan_result->scan_rst.bda[4], scan_result->scan_rst.bda[3],
                                scan_result->scan_rst.bda[2], scan_result->scan_rst.bda[1], scan_result->scan_rst.bda[0]);
                            ssv_ble_gattc_open(gattc_gl_profile_tab[GATTC_PROFILE_A_APP_ID].gattc_if, scan_result->scan_rst.bda, scan_result->scan_rst.ble_addr_type, true);
                            #endif
                        }
                    }
                }

                break;

            //TODO
            case SSV_GAP_SEARCH_INQ_CMPL_EVT:
            case SSV_GAP_SEARCH_DISC_RES_EVT:
            case SSV_GAP_SEARCH_DISC_BLE_RES_EVT:
            case SSV_GAP_SEARCH_DISC_CMPL_EVT:
            case SSV_GAP_SEARCH_DI_DISC_CMPL_EVT:
            case SSV_GAP_SEARCH_SEARCH_CANCEL_CMPL_EVT:
            case SSV_GAP_SEARCH_INQ_DISCARD_NUM_EVT:
                break;
        }//scan_result->scan_rst.search_evt end
    }//SSV_GAP_BLE_SCAN_RESULT_EVT




    default:
        break;
    }
}