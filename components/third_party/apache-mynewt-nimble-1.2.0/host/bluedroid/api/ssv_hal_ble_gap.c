#include <bsp.h>
#include <stdio.h>
#include <soc_types.h>
#include <net_types.h>

#include "ssv_hal_ble_common.h"
#include "ssv_hal_ble_gap.h"
#include "ssv_gap_ble_api.h"
#include "ssv_log.h"

#include "ssv_gap_ble_api.h"
#include "ssv_gatt_common_api.h"

#define SSV_HAL_GAP "SSV_HAL_GAP"
EventGroupHandle_t g_gap_eg = NULL;/*eg is event group*/
uint32_t g_gap_value = 0;

ssv_hal_gap_ble_event_cb_t hal_gap_cb = NULL;

void ssv_api_gap_event_set_by_evtntval(u32 event_val,u32 bit)
{
    BaseType_t val = 0;
    if(g_gap_eg)
    {
        if(gOsFromISR)
            xEventGroupSetBitsFromISR(g_gap_eg, bit, &val);
        else
            xEventGroupSetBits(g_gap_eg, bit);

        SSV_API_SET_BIT(g_gap_value, bit);
    }
}
void ssv_api_gap_event_set(uint32_t bit)
{
    ssv_api_gap_event_set_by_evtntval(g_gap_value, bit);
}

void ssv_hal_gap_event_handler(ssv_gap_ble_cb_event_t event, ssv_ble_gap_cb_param_t *param)
{
    uint8_t *adv_name = NULL;
    uint8_t adv_name_len = 0;

    switch (event) {

        case SSV_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:

            ssv_api_gap_event_set(SSV_API_GAP_CFG_ADV_DATA_RAW);
            break;
        case SSV_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT:

            ssv_api_gap_event_set(SSV_API_GAP_CFG_SCAN_RSP_DATA_RAW);
            break;

        case SSV_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:

            ssv_api_gap_event_set(SSV_API_GAP_CFG_ADV_DATA);
            break;
        case SSV_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:

            ssv_api_gap_event_set(SSV_API_GAP_CFG_SCAN_RSP_DATA);
            break;

        case SSV_GAP_BLE_ADV_START_COMPLETE_EVT:

            //advertising start complete event to indicate advertising start successfully or failed
            if (param->adv_start_cmpl.status != SSV_BT_STATUS_SUCCESS) {
                SSV_LOGE(SSV_HAL_GAP, "Advertising start failed\n");

            } else {
                ssv_api_gap_event_set(SSV_API_GAP_ADV_START_EVENT);
                SSV_LOGI(SSV_HAL_GAP, "Advertising start success\n");
            }

            break;
        case SSV_GAP_BLE_ADV_STOP_COMPLETE_EVT:
            if (param->adv_stop_cmpl.status != SSV_BT_STATUS_SUCCESS) {
                SSV_LOGE(SSV_HAL_GAP, "Advertising stop failed\n");
            } else {
                ssv_api_gap_event_set(SSV_API_GAP_ADV_STOP_EVENT);
                SSV_LOGI(SSV_HAL_GAP, "Stop adv successfully\n");
            }

            break;
        case SSV_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
            SSV_LOGI(SSV_HAL_GAP, "update connection params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d",
                    param->update_conn_params.status,
                    param->update_conn_params.min_int,
                    param->update_conn_params.max_int,
                    param->update_conn_params.conn_int,
                    param->update_conn_params.latency,
                    param->update_conn_params.timeout);
            break;

        case SSV_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT: {
                //the unit of the duration is second
                //uint32_t duration = 30;
                //ssv_ble_gap_start_scanning(duration);
                ssv_api_gap_event_set(SSV_API_GAP_SCAN_PARAM_SET_COMPLETE_EVT);
                break;
            }

        case SSV_GAP_BLE_SCAN_START_COMPLETE_EVT:
            //scan start complete event to indicate scan start successfully or failed
            if (param->scan_start_cmpl.status != SSV_BT_STATUS_SUCCESS) {
                SSV_LOGE(SSV_HAL_GAP, "scan start failed, error status = %x", param->scan_start_cmpl.status);
                break;
            }
            ssv_api_gap_event_set(SSV_API_GAP_SCAN_START_COMPLETE_EVT);
            SSV_LOGI(SSV_HAL_GAP, "scan start success");

            break;
        case SSV_GAP_BLE_SCAN_RESULT_EVT: {
            /*ssv_ble_gap_cb_param_t *scan_result = (ssv_ble_gap_cb_param_t *)param;
            switch (scan_result->scan_rst.search_evt) {
                case SSV_GAP_SEARCH_INQ_RES_EVT:
                    SSV_LOGI(SSV_HAL_GAP, "bd addr %02X:%02X:%02X:%02X:%02X:%02X",
                        scan_result->scan_rst.bda[5], scan_result->scan_rst.bda[4], scan_result->scan_rst.bda[3],
                        scan_result->scan_rst.bda[2], scan_result->scan_rst.bda[1], scan_result->scan_rst.bda[0]);
                    //ssv_log_buffer_hex(SSV_HAL_GAP, scan_result->scan_rst.bda, 6);
                    SSV_LOGI(SSV_HAL_GAP, "searched Adv Data Len %d, Scan Response Len %d", scan_result->scan_rst.adv_data_len, scan_result->scan_rst.scan_rsp_len);
                    adv_name = ssv_ble_resolve_adv_data(scan_result->scan_rst.ble_adv,
                                                        SSV_BLE_AD_TYPE_NAME_CMPL, &adv_name_len);
                    SSV_LOGI(SSV_HAL_GAP, "searched Device Name Len %d", adv_name_len);
                    ssv_log_buffer_char(SSV_HAL_GAP, adv_name, adv_name_len);
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
            }*///scan_result->scan_rst.search_evt end
            break;
        }//SSV_GAP_BLE_SCAN_RESULT_EVT

    default:
        break;
    }


     if (hal_gap_cb)
        hal_gap_cb(event, param);
}

int ssv_hal_ble_gap_init()
{
	ssv_err_t ret = 0;

	ret = ssv_ble_gap_register_callback(ssv_hal_gap_event_handler);
    if (ret){
        SSV_LOGE(SSV_HAL_GAP, "ssv_ble_gap_register_callback error, error code = %x", ret);
        return ret;
    }

	g_gap_eg = xEventGroupCreate();

	if (g_gap_eg == NULL)
        SSV_LOGE(SSV_HAL_GAP, "%s create group event fail", __FUNCTION__);

    return ret;
}

void ssv_api_gap_event_clear_bit(uint32_t bitval)
{
	SSV_API_CLEAR_BIT(g_gap_value, bitval);
}

int ssv_api_gap_wait_event(uint32_t bit, char *failmsg)
{
	int ret = 0;
    EventBits_t evtrlt;
	WAIT_API_EVENT(g_gap_eg, bit, API_EVENT_WAIT_TIME,
            failmsg, SSV_HAL_GAP);
	return ret;
}

void ssv_hal_ble_gap_set_event_cb(ssv_hal_gap_ble_event_cb_t cb)
{
    hal_gap_cb = cb;
}