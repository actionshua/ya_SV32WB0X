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


#include "btc/btc_gap_ble.h"
#include "btc/btc_manage.h"
#include "osi/allocator.h"
#include "bta/bta_api.h"

#include "ssv_gatt_api.h"
#include "adv.h"
#include "btc/btc_util.h"
#include "btc_gatt_util.h"
#include "services/gap/ble_svc_gap.h"
#include "btc/btc_gatts.h"
#include "btc/btc_gattc.h"
#include "bta/bta_gatt_api.h"
#include "btc/btc_gatt_common.h"
#include "btm_ble_api.h"

#include "osi/mutex.h"
#if (BLE_INCLUDED == TRUE)
#define BTC_GAP_BLE_TAG "btc_gap_ble"

#if SCAN_QUEUE_CONGEST_CHECK
static list_t *adv_filter_list;
static osi_mutex_t adv_list_lock;
#endif

static void btc_search_callback(tBTA_DM_SEARCH_EVT event, tBTA_DM_SEARCH *p_data);
static int btc_gap_ble_event_cb(struct ble_gap_event *event, void *arg);

static void btc_gap_to_cb_handler(void *arg, int arg_len, uint8_t act)
{
    bt_status_t ret;
    btc_msg_t msg;

    msg.sig = BTC_SIG_API_CB;
    msg.pid = BTC_PID_GAP_BLE;
    msg.act = act;

    ret = btc_transfer_context(&msg, arg,
                               arg_len, NULL);

    if (ret != BT_STATUS_SUCCESS) {
        BTC_TRACE_ERROR("%s btc_transfer_context failed\n", __func__);
    }
}

static inline void btc_gap_ble_cb_to_app(ssv_gap_ble_cb_event_t event, ssv_ble_gap_cb_param_t *param)
{
    ssv_gap_ble_cb_t btc_gap_ble_cb = (ssv_gap_ble_cb_t)btc_profile_cb_get(BTC_PID_GAP_BLE);
    if (btc_gap_ble_cb) {
        btc_gap_ble_cb(event, param);
    }
}

void btc_gap_ble_cb_handler(btc_msg_t *msg)
{
    ssv_ble_gap_cb_param_t *param = (ssv_ble_gap_cb_param_t *)msg->arg;

    if (msg->act < SSV_GAP_BLE_EVT_MAX) {
        btc_gap_ble_cb_to_app(msg->act, param);
    } else {
        BTC_TRACE_ERROR("%s, unknow msg->act = %d", __func__, msg->act);
    }

    btc_gap_ble_cb_deep_free(msg);
}

static void btc_adv_data_callback(tBTA_STATUS status)
{
    ssv_ble_gap_cb_param_t param;
    bt_status_t ret;
    btc_msg_t msg;

    msg.sig = BTC_SIG_API_CB;
    msg.pid = BTC_PID_GAP_BLE;
    msg.act = SSV_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT;
    param.adv_data_cmpl.status = status;

    ret = btc_transfer_context(&msg, &param,
                               sizeof(ssv_ble_gap_cb_param_t), NULL);

    if (ret != BT_STATUS_SUCCESS) {
        BTC_TRACE_ERROR("%s btc_transfer_context failed\n", __func__);
    }
}

static void btc_scan_rsp_data_callback(tBTA_STATUS status)
{
    ssv_ble_gap_cb_param_t param;
    bt_status_t ret;
    btc_msg_t msg;

    msg.sig = BTC_SIG_API_CB;
    msg.pid = BTC_PID_GAP_BLE;
    msg.act = SSV_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT;
    param.scan_rsp_data_cmpl.status = status;

    ret = btc_transfer_context(&msg, &param,
                               sizeof(ssv_ble_gap_cb_param_t), NULL);

    if (ret != BT_STATUS_SUCCESS) {
        BTC_TRACE_ERROR("%s btc_transfer_context failed\n", __func__);
    }
}

static void btc_stop_adv_callback(uint8_t status)
{
    ssv_ble_gap_cb_param_t param;
    bt_status_t ret;
    btc_msg_t msg;

    msg.sig = BTC_SIG_API_CB;
    msg.pid = BTC_PID_GAP_BLE;
    msg.act = SSV_GAP_BLE_ADV_STOP_COMPLETE_EVT;
    param.adv_stop_cmpl.status = btc_hci_to_ssv_status(status);

    ret = btc_transfer_context(&msg, &param,
                               sizeof(ssv_ble_gap_cb_param_t), NULL);

    if (ret != BT_STATUS_SUCCESS) {
        BTC_TRACE_ERROR("%s btc_transfer_context failed\n", __func__);
    }
}

static void btc_adv_data_raw_callback(tBTA_STATUS status)
{
    ssv_ble_gap_cb_param_t param;
    bt_status_t ret;
    btc_msg_t msg;

    msg.sig = BTC_SIG_API_CB;
    msg.pid = BTC_PID_GAP_BLE;
    msg.act = SSV_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT;
    param.adv_data_raw_cmpl.status = status;

    ret = btc_transfer_context(&msg, &param,
                               sizeof(ssv_ble_gap_cb_param_t), NULL);

    if (ret != BT_STATUS_SUCCESS) {
        BTC_TRACE_ERROR("%s btc_transfer_context failed\n", __func__);
    }
}

#define AD_DATA_ARRAY_SIZE 5

struct ssv_bt_adv_param g_adv_param;
static void btc_ble_set_adv_data(ssv_ble_adv_data_t *adv_data,
                                 tBTA_SET_ADV_DATA_CMPL_CBACK p_adv_data_cback)
{
    struct ssv_bt_adv_data ad[AD_DATA_ARRAY_SIZE];
    uint8_t ad_count = 0;
    int err = 0;
    uint8_t buf[BLE_HS_ADV_MAX_SZ];
    uint8_t buf_len = 0;

    //tBTA_BLE_AD_MASK data_mask = 0;
    g_adv_param.options = 0U;/* todo */
    g_adv_param.interval_min = ADV_SCAN_UNIT(adv_data->min_interval);
    g_adv_param.interval_max = ADV_SCAN_UNIT(adv_data->max_interval);

    //flag
    ad[ad_count].type = 0x1;
    ad[ad_count].data_len = 1;
    ad[ad_count].data = &adv_data->flag;
    ad_count++;

    //appearance
    if (adv_data->appearance) {
        ad[ad_count].type = 0x19;
        ad[ad_count].data_len = 1;
        ad[ad_count].data = (u8_t*)&adv_data->appearance;
        ad_count++;
    }

    //manufacturer
    if (adv_data->manufacturer_len) {
        ad[ad_count].type = 0xFF;
        ad[ad_count].data_len = adv_data->manufacturer_len;
        ad[ad_count].data = adv_data->p_manufacturer_data;
        ad_count++;
    }

    //service_data
    if (adv_data->service_data_len) {
        ad[ad_count].type = 0x16;
        ad[ad_count].data_len = adv_data->service_data_len;
        ad[ad_count].data = adv_data->p_service_data;
        ad_count++;
    }

    //service_uuid
    if (adv_data->service_uuid_len) {
        if (adv_data->service_uuid_len == 2)/*16 bit*/
            ad[ad_count].type = 0x16;
        else if (adv_data->service_uuid_len == 4)/*32 bit*/
           ad[ad_count].type = 0x20;
        else/*128 bit*/
            ad[ad_count].type = 0x21;

        ad[ad_count].data_len = adv_data->service_uuid_len;
        ad[ad_count].data = adv_data->p_service_uuid;
        ad_count++;
    }

    err = set_ad(ad, ad_count, buf, &buf_len);

    if (buf_len > BLE_HS_ADV_MAX_SZ) {
        BT_ERR("error set_ad data_len %d\n", buf_len);
        goto btc_ble_set_adv_data_end;
    }

    if (err) {
        BT_ERR("set_ad failed: err %d", err);
        goto btc_ble_set_adv_data_end;
    }

    if (adv_data->set_scan_rsp) {
        err = ble_gap_adv_rsp_set_data(buf, buf_len);
        if (err != 0) {
            BT_ERR("Scan rsp failed: err %d", err);
            goto btc_ble_set_adv_data_end;
        }
    } else {
        err = ble_gap_adv_set_data(buf, buf_len);
        if (err != 0) {
            BT_ERR("Advertising set failed: err %d", err);
        }
    }

btc_ble_set_adv_data_end:

    if (p_adv_data_cback)
        p_adv_data_cback(err);
}

static void btc_scan_rsp_data_raw_callback(tBTA_STATUS status)
{
    ssv_ble_gap_cb_param_t param;
    bt_status_t ret;
    btc_msg_t msg;

    msg.sig = BTC_SIG_API_CB;
    msg.pid = BTC_PID_GAP_BLE;
    msg.act = SSV_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT;
    param.scan_rsp_data_raw_cmpl.status = status;

    ret = btc_transfer_context(&msg, &param,
                               sizeof(ssv_ble_gap_cb_param_t), NULL);

    if (ret != BT_STATUS_SUCCESS) {
        BTC_TRACE_ERROR("%s btc_transfer_context failed\n", __func__);
    }
}

static void btc_ble_set_adv_data_raw(uint8_t *raw_adv, uint32_t raw_adv_len,
                                 tBTA_SET_ADV_DATA_CMPL_CBACK p_adv_data_cback)
{
    int err = 0;

    if (NULL==p_adv_data_cback)
        return;

    err = ble_gap_adv_set_data(raw_adv, raw_adv_len);
    if (err) {
        BT_ERR("Advertising set failed: err %d", err);
        p_adv_data_cback(SSV_BT_STATUS_PARM_INVALID);
    } else
        p_adv_data_cback(SSV_BT_STATUS_SUCCESS);
}

ssv_ble_scan_params_t g_scan_param;

int btc_gap_ble_conn_create(tBTA_GATTC_IF client_if, BD_ADDR remote_bda, tBTA_ADDR_TYPE remote_addr_type,
                    BOOLEAN is_direct, tBTA_GATT_TRANSPORT transport)
{
    int ret = 0;
    tBTA_GATTC gattc_open;

    ble_addr_t peer_addr;
    struct ble_gap_conn_params conn_params;
    peer_addr.type = remote_addr_type;
    memcpy(peer_addr.val, remote_bda, BD_ADDR_LEN);

    memset(&gattc_open, 0, sizeof(gattc_open));

    conn_params.scan_itvl = g_scan_param.scan_interval;
    conn_params.scan_window = g_scan_param.scan_window;

    /** Minimum value for connection interval in 1.25ms units */
    conn_params.itvl_min = 50;
    conn_params.itvl_max = 100;
    conn_params.latency = 0;
    conn_params.supervision_timeout = 3000;/* > itvl*(latency + 1))*/
    conn_params.min_ce_len = conn_params.max_ce_len = 0;

    ret = ble_gap_connect(BLE_OWN_ADDR_PUBLIC, &peer_addr, BLE_HS_FOREVER, &conn_params,
        btc_gap_ble_event_cb, NULL);

    gattc_open.open.client_if = CLIENT_IF_ID;//BTC_GATT_CREATE_CONN_ID(CLIENT_IF_ID, open->conn_id);

    if (ret) {
        gattc_open.open.status = ret;
        SSV_LOGE(BTC_GAP_BLE_TAG, "%s ret %d\n", __FUNCTION__, ret);
    }

    btc_gatt_com_to_cb_handler((void*)&gattc_open, sizeof(gattc_open), BTA_GATTC_OPEN_EVT, BTC_PID_GATTC);

    return ret;
}
static u8_t g_num_adv_resps = 0;
static int btc_gap_ble_event_cb(struct ble_gap_event *event, void *arg)
{
    struct ble_gap_conn_desc desc;
    tBTA_GATTS gatts_data;
    tBTA_GATTC gattc_data;
    ssv_ble_gatts_cb_param_t param;
    tBTA_GATTS_REQ_DATA *preq_data = NULL;
    int rc;

    switch (event->type) {
        case BLE_GAP_EVENT_CONNECT:
            ble_gap_conn_find(event->connect.conn_handle, &desc);

            /* A new connection was established or a connection attempt failed. */
            printf("btc_gap connection %s; status=%d\n",
                event->connect.status == 0 ? "established" : "failed",
                event->connect.status);

            if (desc.role == BLE_GAP_ROLE_SLAVE) {
                printf("btc_gap slave\n");
                memcpy(gatts_data.conn.remote_bda, desc.peer_id_addr.val, SSV_BD_ADDR_LEN);
                gatts_data.conn.server_if = SERVER_IF_ID;
                gatts_data.conn.conn_id = BTC_GATT_CREATE_CONN_ID(SERVER_IF_ID, event->connect.conn_handle);
                gatts_data.conn.conn_params.interval = desc.conn_itvl;
                gatts_data.conn.conn_params.latency = desc.conn_latency;
                gatts_data.conn.conn_params.timeout = desc.supervision_timeout;
                btc_gatt_com_to_cb_handler((void*)&gatts_data, sizeof(gatts_data), BTA_GATTS_CONNECT_EVT, BTC_PID_GATTS);
                gatts_data.req_data.conn_id = BTC_GATT_CREATE_CONN_ID(SERVER_IF_ID, event->connect.conn_handle);
                preq_data = OS_MemZalloc(sizeof(tBTA_GATTS_REQ_DATA));
                if (preq_data) {
                    preq_data->mtu = bt_gatt_get_preferred_mtu();
                    gatts_data.req_data.p_data = preq_data;
                    btc_gatt_com_to_cb_handler((void*)&gatts_data, sizeof(gatts_data), BTA_GATTS_MTU_EVT, BTC_PID_GATTS);
                    //OS_MemFree(preq_data);
                }
            } else {
                printf("btc_gap master\n");
                memcpy(gattc_data.connect.remote_bda, desc.peer_id_addr.val, SSV_BD_ADDR_LEN);
                gattc_data.connect.conn_params.interval = desc.conn_itvl;
                gattc_data.connect.conn_params.latency = desc.conn_latency;
                gattc_data.connect.conn_params.timeout = desc.supervision_timeout;
                memcpy(gattc_data.connect.remote_bda, desc.peer_id_addr.val, SSV_BD_ADDR_LEN);
                gattc_data.connect.client_if = CLIENT_IF_ID;
                gattc_data.connect.conn_id = BTC_GATT_CREATE_CONN_ID(CLIENT_IF_ID, event->connect.conn_handle);
                btc_gatt_com_to_cb_handler((void*)&gattc_data, sizeof(gattc_data), BTA_GATTC_CONNECT_EVT, BTC_PID_GATTC);
            }

            break;

        case BLE_GAP_EVENT_DISCONNECT:
            printf(" btc_gap disconnection conn_handle %d reason=%d\n",
                event->disconnect.conn.conn_handle, event->disconnect.reason);

            if (event->disconnect.conn.role == BLE_GAP_ROLE_SLAVE) {//todo
                printf("btc_gap slave\n");
                gatts_data.conn.server_if = SERVER_IF_ID;
                gatts_data.conn.conn_id = BTC_GATT_CREATE_CONN_ID(SERVER_IF_ID, event->disconnect.conn.conn_handle);
                gatts_data.conn.reason = event->disconnect.reason;
                memcpy(gatts_data.conn.remote_bda, event->disconnect.conn.peer_id_addr.val, SSV_BD_ADDR_LEN);
                btc_gatt_com_to_cb_handler((void*)&gatts_data, sizeof(gatts_data), BTA_GATTS_DISCONNECT_EVT, BTC_PID_GATTS);
            } else  if (event->disconnect.conn.role == BLE_GAP_ROLE_MASTER){
                printf("btc_gap master\n");
            } else
                printf("btc_gap unknow\n");

            break;

        case BLE_GAP_EVENT_NOTIFY_TX:
            /* gatt server */
            printf("btc_gap NOTIFY_TX conn_handle=%d attr_handle=%d indication=%d\n",
                event->notify_tx.conn_handle,
                event->notify_tx.attr_handle,
                event->notify_tx.indication);

            switch (event->notify_tx.status) {
                case 0:
                    printf("btc_gap NOTIFY_TX Command successfully sent\n");
                    if (event->notify_tx.indication) {
                        gatts_data.confirm.status = SSV_GATT_OK;
                        gatts_data.confirm.conn_id = BTC_GATT_CREATE_CONN_ID(SERVER_IF_ID, event->notify_tx.conn_handle);
                        printf("btc_gap conn_id 0x%0x\n", gatts_data.confirm.conn_id);
                        btc_gatt_com_to_cb_handler((void*)&gatts_data, sizeof(gatts_data), BTA_GATTS_CONF_EVT, BTC_PID_GATTS);
                    }
                    break;
                case BLE_HS_EDONE:
                    printf("btc_gap NOTIFY_TX Command EDONE\n");
                    if (event->notify_tx.indication) {
                        gatts_data.confirm.status = SSV_GATT_ERROR;
                        gatts_data.confirm.conn_id = BTC_GATT_CREATE_CONN_ID(SERVER_IF_ID, event->notify_tx.conn_handle);
                        btc_gatt_com_to_cb_handler((void*)&gatts_data, sizeof(gatts_data), BTA_GATTS_CONF_EVT, BTC_PID_GATTS);
                    }

                    break;
                case BLE_HS_ETIMEOUT:
                    printf("btc_gap NOTIFY_TX Command TIMEOUT\n");
                    if (event->notify_tx.indication) {
                        gatts_data.confirm.status = SSV_GATT_ERROR;
                        gatts_data.confirm.conn_id = BTC_GATT_CREATE_CONN_ID(SERVER_IF_ID, event->notify_tx.conn_handle);
                        btc_gatt_com_to_cb_handler((void*)&gatts_data, sizeof(gatts_data), BTA_GATTS_CONF_EVT, BTC_PID_GATTS);
                    }
                    break;
            }


            break;

        case BLE_GAP_EVENT_NOTIFY_RX:
            /* gatt client */
            printf("btc_gap NOTIFY_RX conn_handle=%d attr_handle=%d indication=%d\n",
                event->notify_rx.conn_handle,
                event->notify_rx.attr_handle,
                event->notify_rx.indication);

            ble_gap_conn_find(event->connect.conn_handle, &desc);

            gattc_data.notify.conn_id = BTC_GATT_CREATE_CONN_ID(CLIENT_IF_ID, event->notify_rx.conn_handle);
            memcpy(gattc_data.notify.bda, desc.peer_id_addr.val, BD_ADDR_LEN);
            gattc_data.notify.handle = event->notify_rx.conn_handle;
            rc = ble_hs_mbuf_to_flat(event->notify_rx.om, gattc_data.notify.value, BTA_GATT_MAX_ATTR_LEN, &gattc_data.notify.len);
            gattc_data.notify.is_notify = (!event->notify_rx.indication);
            if (rc)
                printf("%s ble_hs_mbuf_to_flat %d\n", __FUNCTION__, rc);

            btc_gatt_com_to_cb_handler((void*)&gattc_data, sizeof(gattc_data), BTA_GATTC_NOTIF_EVT, BTC_PID_GATTC);
            break;

        case BLE_GAP_EVENT_DISC: {
                tBTA_DM_SEARCH scan_data;
                u16_t data_len = 0;
                u8_t *pflags_value = 0;
                u8_t flags_len = 0;
                memcpy(scan_data.inq_res.bd_addr, event->disc.addr.val, BD_ADDR_LEN);

                //search_data.inq_res.dev_class
                scan_data.inq_res.rssi = event->disc.rssi;
                #if (BLE_INCLUDED == TRUE)
                //scan_data.dev_class
                scan_data.inq_res.ble_addr_type = event->disc.addr.type;
                scan_data.inq_res.ble_evt_type = event->disc.event_type;
                //detect flag
                pflags_value = BTM_CheckAdvData(event->disc.data, SSV_BLE_AD_TYPE_FLAG, &flags_len);

                if (pflags_value) {
                    if ((*pflags_value) & 0x1)//LE Limited Discoverable Mode
                        scan_data.inq_res.is_limited = true;
                    else
                        scan_data.inq_res.is_limited = false;

                    if ((*pflags_value) & 0x4)//BR/EDR Not Supported.
                        scan_data.inq_res.device_type = BT_DEVICE_TYPE_BLE;
                    else
                        scan_data.inq_res.device_type = BT_DEVICE_TYPE_DUMO;
                }
                /*while (data_len < event->disc.length_data - 1) {
                    ad_type = event->disc.data[data_len + 1];
                    if (ad_type == SSV_BLE_AD_TYPE_FLAG) {//flags
                        flags_value = event->disc.data[data_len + 2];
                        if (flags_value & 0x1)//LE Limited Discoverable Mode
                            scan_data.inq_res.is_limited = true;
                        else
                            scan_data.inq_res.is_limited = false;

                        if (flags_value & 0x4)//BR/EDR Not Supported.
                            scan_data.inq_res.device_type = BT_DEVICE_TYPE_BLE;
                        else
                            scan_data.inq_res.device_type = BT_DEVICE_TYPE_DUMO;


                        break;
                    }
                    data_len += (event->disc.data[data_len] + 1);
                }*/
                scan_data.inq_res.p_eir = event->disc.data;
                scan_data.inq_res.adv_data_len = event->disc.length_data;
                /*scan data is padding ing the end of p_eir, we do not padding now, so set scan length is 0*/
                scan_data.inq_res.scan_rsp_len = 0;
                g_num_adv_resps ++;
                #endif
                btc_search_callback(BTA_DM_INQ_RES_EVT, &scan_data);
            }
            break;

        case BLE_GAP_EVENT_DISC_COMPLETE:{
                tBTA_DM_SEARCH scan_comp;

                scan_comp.inq_cmpl.num_resps = g_num_adv_resps;
                btc_search_callback(BTA_DM_INQ_CMPL_EVT, &scan_comp);
            }
            break;

        case BLE_GAP_EVENT_MTU:
            printf("btc_gap BLE_GAP_EVENT_MTU conn_handle=%d channel_id=%d mtu_value=%d\n",
                event->mtu.conn_handle,
                event->mtu.channel_id,
                event->mtu.value);

            //ble_hs_hci_util_set_data_len();
            break;
    }

    return 0;
}

static void btc_start_adv_callback(uint8_t status)
{
    ssv_ble_gap_cb_param_t param;
    bt_status_t ret;
    btc_msg_t msg;

    msg.sig = BTC_SIG_API_CB;
    msg.pid = BTC_PID_GAP_BLE;
    msg.act = SSV_GAP_BLE_ADV_START_COMPLETE_EVT;
    param.adv_start_cmpl.status = status;//btc_hci_to_ssv_status(status);

    ret = btc_transfer_context(&msg, &param,
                               sizeof(ssv_ble_gap_cb_param_t), NULL);

    if (ret != BT_STATUS_SUCCESS) {
        BTC_TRACE_ERROR("%s btc_transfer_context failed\n", __func__);
    }
}

static void btc_ble_start_advertising (ssv_ble_adv_params_t *ble_adv_params, tBTA_START_ADV_CMPL_CBACK start_adv_cback)
{
    struct ble_gap_adv_params adv_params;
    ble_addr_t peer_addr, *ppeer_addr = NULL;
    int err = 0;

    memset(&adv_params, 0, sizeof adv_params);
    adv_params.itvl_min = ble_adv_params->adv_int_min;
    adv_params.itvl_max = ble_adv_params->adv_int_max;
    adv_params.channel_map = ble_adv_params->channel_map;
    adv_params.filter_policy = ble_adv_params->adv_filter_policy;


    switch (ble_adv_params->adv_type){
        case ADV_TYPE_IND:
            adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
            adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;
            break;

        case ADV_TYPE_DIRECT_IND_HIGH:
            adv_params.conn_mode = BLE_GAP_CONN_MODE_DIR;
            adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;
            adv_params.high_duty_cycle = 1;
            break;

        case ADV_TYPE_SCAN_IND:
            adv_params.conn_mode = BLE_GAP_CONN_MODE_NON;
            adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;
            break;

        case ADV_TYPE_NONCONN_IND:
            adv_params.conn_mode = BLE_GAP_CONN_MODE_NON;
            adv_params.disc_mode = BLE_GAP_DISC_MODE_NON;
            break;

        case ADV_TYPE_DIRECT_IND_LOW:
            adv_params.conn_mode = BLE_GAP_CONN_MODE_DIR;
            adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;
            adv_params.high_duty_cycle = 0;
            break;
    }

    if (ble_adv_params->peer_addr) {
        memcpy(peer_addr.val, ble_adv_params->peer_addr, 6);
        peer_addr.type = ble_adv_params->peer_addr_type;

        ppeer_addr = &peer_addr;
    }

    err = ble_gap_adv_start(ble_adv_params->own_addr_type, ppeer_addr, BLE_HS_FOREVER, &adv_params,
                            btc_gap_ble_event_cb, NULL);

    if (start_adv_cback)
        start_adv_cback(err);
}

static void btc_ble_stop_advertising(tBTA_START_STOP_ADV_CMPL_CBACK *stop_adv_cb)
{
    int ret = 0;

    ret = bt_le_adv_disable();
    if (ret)
        printf("ret ble_gap_adv_stop return %d\n", ret);

    if (stop_adv_cb)
        stop_adv_cb(ret);
}

static void btc_ble_set_scan_rsp_data_raw(uint8_t *raw_scan_rsp, uint32_t raw_scan_rsp_len,
                                 tBTA_SET_ADV_DATA_CMPL_CBACK p_scan_rsp_data_cback)
{
    int ret = 0;

    ret = ble_gap_adv_rsp_set_data(raw_scan_rsp, raw_scan_rsp_len);
    if (ret)
        BT_ERR("Scan rsp failed: err %d", ret);

    if (p_scan_rsp_data_cback)
        p_scan_rsp_data_cback(ret);
    //BTA_DmBleSetScanRspRaw(raw_scan_rsp, raw_scan_rsp_len, p_scan_rsp_data_cback);
}

static void btc_scan_params_callback(tGATT_IF gatt_if, tBTM_STATUS status)
{
    ssv_ble_gap_cb_param_t param;
    bt_status_t ret;
    btc_msg_t msg;

    msg.sig = BTC_SIG_API_CB;
    msg.pid = BTC_PID_GAP_BLE;
    msg.act = SSV_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT;
    param.scan_param_cmpl.status = status;

    ret = btc_transfer_context(&msg, &param,
                               sizeof(ssv_ble_gap_cb_param_t), NULL);

    if (ret != BT_STATUS_SUCCESS) {
        BTC_TRACE_ERROR("%s btc_transfer_context failed\n", __func__);
    }
}

static void btc_ble_set_scan_params(ssv_ble_scan_params_t *scan_params, tBLE_SCAN_PARAM_SETUP_CBACK scan_param_setup_cback)
{
    struct ble_gap_disc_params scan_param;

    if (BLE_ISVALID_PARAM(scan_params->scan_interval, BTM_BLE_SCAN_INT_MIN, BTM_BLE_SCAN_INT_MAX) &&
        BLE_ISVALID_PARAM(scan_params->scan_window, BTM_BLE_SCAN_WIN_MIN, BTM_BLE_SCAN_WIN_MAX) &&
        BLE_ISVALID_PARAM(scan_params->own_addr_type, BLE_ADDR_TYPE_PUBLIC, BLE_ADDR_TYPE_RPA_RANDOM) &&
        BLE_ISVALID_PARAM(scan_params->scan_filter_policy, BLE_SCAN_FILTER_ALLOW_ALL, BLE_SCAN_FILTER_ALLOW_WLIST_PRA_DIR) &&
        BLE_ISVALID_PARAM(scan_params->scan_duplicate, BLE_SCAN_DUPLICATE_DISABLE, BLE_SCAN_DUPLICATE_MAX -1) &&
        (scan_params->scan_type == BTM_BLE_SCAN_MODE_ACTI || scan_params->scan_type == BTM_BLE_SCAN_MODE_PASS)) {

        memcpy(&g_scan_param, scan_params, sizeof(ssv_ble_scan_params_t));
        btc_scan_params_callback(CLIENT_IF_ID, BTM_SUCCESS);//todo
        /*rc = ble_gap_disc(BLE_OWN_ADDR_PUBLIC, BLE_HS_FOREVER, &scan_param, disc_cb, NULL);
        if (rc != 0) {
            BT_ERR("%s, Invalid status %d", __func__, rc);
            break;
        }*/
        /*BTA_DmSetBleScanFilterParams(SSV_DEFAULT_GATT_IF,	//client_if
            scan_params->scan_interval,
            scan_params->scan_window,
            scan_params->scan_type,
            scan_params->scan_filter_policy,
            scan_params->own_addr_type,
            scan_params->scan_duplicate,
            scan_param_setup_cback);*/
    } else {
        btc_scan_params_callback(SSV_DEFAULT_GATT_IF, BTM_ILLEGAL_VALUE);
    }
}
tBTA_DM_SEARCH_CBACK *g_results_cb = NULL;
static void btc_ble_start_scanning(uint32_t duration,
                                   tBTA_DM_SEARCH_CBACK *results_cb,
                                   tBTA_START_STOP_SCAN_CMPL_CBACK *start_scan_cb)
{
    int rc = 0;
    struct ble_gap_disc_params scan_param;

    if ((results_cb != NULL) && (start_scan_cb != NULL)) {
#if SCAN_QUEUE_CONGEST_CHECK
        btc_adv_list_refresh();
#endif
        g_results_cb = NULL;
        //Start scan the device
        /** Scan interval in 0.625ms units */
        scan_param.itvl = g_scan_param.scan_interval;
        scan_param.window = g_scan_param.scan_window;
        scan_param.filter_policy = g_scan_param.scan_filter_policy;
        scan_param.limited = 0;
        scan_param.filter_duplicates = g_scan_param.scan_duplicate;
        if (g_scan_param.scan_type == BLE_SCAN_TYPE_PASSIVE) {
            scan_param.passive = 1;
        } else
            scan_param.passive = 0;//BLE_SCAN_TYPE_ACTIVE

        g_num_adv_resps = 0;
        rc = ble_gap_disc(BLE_OWN_ADDR_PUBLIC, duration * 1000, &scan_param, btc_gap_ble_event_cb, NULL);
        if (rc != 0) {
            BT_ERR("%s, ble_gap_disc Invalid status %d", __func__, rc);
        }

        if (start_scan_cb) {
            if (rc)
                start_scan_cb(BTM_ILLEGAL_VALUE);
            else {
                start_scan_cb(BTM_SUCCESS);
                g_results_cb = results_cb;
            }
        }


        //BTA_DmBleScan(true, duration, results_cb, start_scan_cb);
    } else {
        BTC_TRACE_ERROR("The start_scan_cb or results_cb invalid\n");
    }
}

static void btc_ble_stop_scanning(tBTA_START_STOP_SCAN_CMPL_CBACK *stop_scan_cb)
{
    int rc = 0;

    rc = ble_gap_disc_cancel();
    if (rc)
        BT_ERR("%s, ble_gap_disc_cancel Invalid status %d", __func__, rc);

    if (stop_scan_cb) {
        if (rc)
            stop_scan_cb(BTM_ILLEGAL_VALUE);
        else
            stop_scan_cb(BTM_SUCCESS);
    }
    //uint8_t duration = 0;
    //BTA_DmBleScan(false, duration, NULL, stop_scan_cb);
}

static void btc_search_callback(tBTA_DM_SEARCH_EVT event, tBTA_DM_SEARCH *p_data)
{
    ssv_ble_gap_cb_param_t param;
    btc_msg_t msg;

    msg.sig = BTC_SIG_API_CB;
    msg.pid = BTC_PID_GAP_BLE;
    msg.act = SSV_GAP_BLE_SCAN_RESULT_EVT;

    param.scan_rst.search_evt = event;
    switch (event) {
    case BTA_DM_INQ_RES_EVT: {
#if SCAN_QUEUE_CONGEST_CHECK
        if(btc_check_queue_is_congest()) {
            BTC_TRACE_DEBUG("BtcQueue is congested");
            if(btc_get_adv_list_length() > BTC_ADV_LIST_MAX_LENGTH || btc_adv_list_count > BTC_ADV_LIST_MAX_COUNT) {
                btc_adv_list_refresh();
                btc_adv_list_count = 0;
            }
            if(btc_check_adv_list(p_data->inq_res.bd_addr, p_data->inq_res.ble_addr_type)) {
                return;
            }
        }
        btc_adv_list_count ++;
#endif
        bdcpy(param.scan_rst.bda, p_data->inq_res.bd_addr);
        param.scan_rst.dev_type = p_data->inq_res.device_type;
        param.scan_rst.rssi = p_data->inq_res.rssi;
        param.scan_rst.ble_addr_type = p_data->inq_res.ble_addr_type;
        param.scan_rst.ble_evt_type = p_data->inq_res.ble_evt_type;
        param.scan_rst.flag = p_data->inq_res.flag;
        param.scan_rst.num_resps = 1;
        param.scan_rst.adv_data_len = p_data->inq_res.adv_data_len;
        param.scan_rst.scan_rsp_len = p_data->inq_res.scan_rsp_len;
        memcpy(param.scan_rst.ble_adv, p_data->inq_res.p_eir, sizeof(param.scan_rst.ble_adv));
        break;
    }
    case BTA_DM_INQ_CMPL_EVT: {
        param.scan_rst.num_resps = p_data->inq_cmpl.num_resps;
        BTC_TRACE_DEBUG("%s  BLE observe complete. Num Resp %d\n", __FUNCTION__, p_data->inq_cmpl.num_resps);
        break;
    }
    case BTA_DM_DISC_RES_EVT:
        BTC_TRACE_DEBUG("BTA_DM_DISC_RES_EVT\n");
        break;
    case BTA_DM_DISC_BLE_RES_EVT:
        BTC_TRACE_DEBUG("BTA_DM_DISC_BLE_RES_EVT\n");
        break;
    case BTA_DM_DISC_CMPL_EVT:
        BTC_TRACE_DEBUG("BTA_DM_DISC_CMPL_EVT\n");
        break;
    case BTA_DM_DI_DISC_CMPL_EVT:
        BTC_TRACE_DEBUG("BTA_DM_DI_DISC_CMPL_EVT\n");
        break;
    case BTA_DM_SEARCH_CANCEL_CMPL_EVT:
        BTC_TRACE_DEBUG("BTA_DM_SEARCH_CANCEL_CMPL_EVT\n");
        break;
    case BTA_DM_INQ_DISCARD_NUM_EVT:
        param.scan_rst.num_dis = p_data->inq_dis.num_dis;
        break;
    default:
        BTC_TRACE_ERROR("%s : Unknown event 0x%x\n", __FUNCTION__, event);
        return;
    }
    btc_transfer_context(&msg, &param, sizeof(ssv_ble_gap_cb_param_t), NULL);
}

static void btc_start_scan_callback(uint8_t status)
{
    ssv_ble_gap_cb_param_t param;
    bt_status_t ret;
    btc_msg_t msg;

    msg.sig = BTC_SIG_API_CB;
    msg.pid = BTC_PID_GAP_BLE;
    msg.act = SSV_GAP_BLE_SCAN_START_COMPLETE_EVT;
    param.scan_start_cmpl.status = status;

    ret = btc_transfer_context(&msg, &param,
                               sizeof(ssv_ble_gap_cb_param_t), NULL);

    if (ret != BT_STATUS_SUCCESS) {
        BTC_TRACE_ERROR("%s btc_transfer_context failed\n", __func__);
    }
}

static void btc_stop_scan_callback(tBTA_STATUS status)
{
    ssv_ble_gap_cb_param_t param;
    bt_status_t ret;
    btc_msg_t msg;

    msg.sig = BTC_SIG_API_CB;
    msg.pid = BTC_PID_GAP_BLE;
    msg.act = SSV_GAP_BLE_SCAN_STOP_COMPLETE_EVT;
    param.scan_stop_cmpl.status = status;

    ret = btc_transfer_context(&msg, &param,
                               sizeof(ssv_ble_gap_cb_param_t), NULL);

    if (ret != BT_STATUS_SUCCESS) {
        BTC_TRACE_ERROR("%s btc_transfer_context failed\n", __func__);
    }
#if SCAN_QUEUE_CONGEST_CHECK
    btc_adv_list_refresh();
#endif
}

static void btc_ble_disconnect(BD_ADDR bd_addr)
{
    //BTA_DmBleDisconnect(bd_addr);
    ble_addr_t ble_addr;
    struct ble_gap_conn_desc desc;

    ble_addr.type = BLE_ADDR_TYPE_PUBLIC;
    memcpy(ble_addr.val, bd_addr, BD_ADDR_LEN);

    int ret = ble_gap_conn_find_by_addr(&ble_addr, &desc);

    if (ret) {
        printf("do not find pub\n");
        ble_addr.type = BLE_ADDR_TYPE_RANDOM;
        ret = ble_gap_conn_find_by_addr(&ble_addr, &desc);
        if (ret) {
            printf("do not find rand, just conn_cancel\n");
            ble_gap_conn_cancel();
        }
        else
            printf("find rand\n");

    }
    else
        printf("disc conn_handle 0x%x\n",
            desc.conn_handle);

    ble_gap_terminate(desc.conn_handle, BLE_ERR_CONN_TERM_LOCAL);
}

void btc_gap_ble_call_handler(btc_msg_t *msg)
{
    int ret = 0;
    btc_ble_gap_args_t *arg = (btc_ble_gap_args_t *)msg->arg;

    BTC_TRACE_DEBUG("%s act %d\n", __FUNCTION__, msg->act);

    switch (msg->act) {
    case BTC_GAP_BLE_ACT_CFG_ADV_DATA: {
        ble_svc_gap_device_appearance_set(arg->cfg_adv_data.adv_data.appearance);
        if (arg->cfg_adv_data.adv_data.set_scan_rsp == false) {
            btc_ble_set_adv_data(&arg->cfg_adv_data.adv_data, btc_adv_data_callback);
        } else {
            btc_ble_set_adv_data(&arg->cfg_adv_data.adv_data, btc_scan_rsp_data_callback);
        }
        break;
    }
    case BTC_GAP_BLE_ACT_SET_SCAN_PARAM:
        btc_ble_set_scan_params(&arg->set_scan_param.scan_params, btc_scan_params_callback);
        break;
    case BTC_GAP_BLE_ACT_START_SCAN:
        btc_ble_start_scanning(arg->start_scan.duration, btc_search_callback, btc_start_scan_callback);
        break;
    case BTC_GAP_BLE_ACT_STOP_SCAN:
        btc_ble_stop_scanning(btc_stop_scan_callback);
        break;
    case BTC_GAP_BLE_ACT_START_ADV:
        btc_ble_start_advertising(&arg->start_adv.adv_params, btc_start_adv_callback);
        break;
    case BTC_GAP_BLE_ACT_STOP_ADV:
        btc_ble_stop_advertising(btc_stop_adv_callback);
        break;

    case BTC_GAP_BLE_ACT_UPDATE_CONN_PARAM:
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        btc_ble_update_conn_params(arg->conn_update_params.conn_params.bda,
                                   arg->conn_update_params.conn_params.min_int,
                                   arg->conn_update_params.conn_params.max_int,
                                   arg->conn_update_params.conn_params.latency,
                                   arg->conn_update_params.conn_params.timeout);
    #endif
        break;

    case BTC_GAP_BLE_ACT_SET_PKT_DATA_LEN:
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        btc_ble_set_pkt_data_len(arg->set_pkt_data_len.remote_device, arg->set_pkt_data_len.tx_data_length, btc_set_pkt_length_callback);
    #endif
        break;

    case BTC_GAP_BLE_ACT_SET_RAND_ADDRESS:
    {
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        BD_ADDR bd_addr;
        memcpy(bd_addr, arg->set_rand_addr.rand_addr, sizeof(BD_ADDR));
        btc_ble_set_rand_addr(bd_addr, btc_set_rand_addr_callback);
    #endif
        break;
    }

    case BTC_GAP_BLE_ACT_CLEAR_RAND_ADDRESS: {
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        btc_ble_clear_rand_addr();
    #endif
        break;
    }
    case BTC_GAP_BLE_ACT_CONFIG_LOCAL_PRIVACY:
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        btc_ble_config_local_privacy(arg->cfg_local_privacy.privacy_enable, btc_set_local_privacy_callback);
    #endif
        break;
    case BTC_GAP_BLE_ACT_CONFIG_LOCAL_ICON:
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        btc_ble_config_local_icon(arg->cfg_local_icon.icon);
    #endif
        break;

    case BTC_GAP_BLE_ACT_UPDATE_WHITE_LIST:
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        BTA_DmUpdateWhiteList(arg->update_white_list.add_remove, arg->update_white_list.remote_bda, arg->update_white_list.wl_addr_type, btc_add_whitelist_complete_callback);
    #endif
        break;

    case BTC_GAP_BLE_ACT_READ_RSSI:
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        BTA_DmBleReadRSSI(arg->read_rssi.remote_addr, BTA_TRANSPORT_LE, btc_read_ble_rssi_cmpl_callback);
    #endif
        break;

    case BTC_GAP_BLE_ACT_SET_CONN_PARAMS:
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        BTA_DmSetBlePrefConnParams(arg->set_conn_params.bd_addr, arg->set_conn_params.min_conn_int,
                                                        arg->set_conn_params.max_conn_int, arg->set_conn_params.slave_latency,
                                                        arg->set_conn_params.supervision_tout);
    #endif
        break;

    case BTC_GAP_BLE_ACT_SET_DEV_NAME:
        ble_svc_gap_device_name_set(arg->set_dev_name.device_name);
        //BTA_DmSetDeviceName(arg->set_dev_name.device_name);
        break;

    case BTC_GAP_BLE_ACT_CFG_ADV_DATA_RAW:
        btc_ble_set_adv_data_raw(arg->cfg_adv_data_raw.raw_adv,
                                 arg->cfg_adv_data_raw.raw_adv_len,
                                 btc_adv_data_raw_callback);
        break;
    case BTC_GAP_BLE_ACT_CFG_SCAN_RSP_DATA_RAW:
        btc_ble_set_scan_rsp_data_raw(arg->cfg_scan_rsp_data_raw.raw_scan_rsp,
                                      arg->cfg_scan_rsp_data_raw.raw_scan_rsp_len,
                                      btc_scan_rsp_data_raw_callback);
        break;

    case BTC_GAP_BLE_UPDATE_DUPLICATE_SCAN_EXCEPTIONAL_LIST:
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        btc_ble_update_duplicate_exceptional_list(arg->update_duplicate_exceptional_list.subcode,
                                                arg->update_duplicate_exceptional_list.info_type,
                                                arg->update_duplicate_exceptional_list.device_info,
                                                btc_update_duplicate_exceptional_list_callback);
    #endif
        break;

#if (SMP_INCLUDED == TRUE)
    case BTC_GAP_BLE_SET_ENCRYPTION_EVT: {
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        BD_ADDR bd_addr;
        memcpy(bd_addr, arg->set_encryption.bd_addr, sizeof(BD_ADDR));
        BTA_DmSetEncryption(bd_addr, BT_TRANSPORT_LE, btc_set_encryption_callback,
                                          (tBTA_DM_BLE_SEC_ACT)arg->set_encryption.sec_act);
    #endif
        break;
    }

    case BTC_GAP_BLE_SET_SECURITY_PARAM_EVT: {
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        uint8_t *value = arg->set_security_param.value;
        switch(arg->set_security_param.param_type) {
            case SSV_BLE_SM_PASSKEY:
                break;
            case SSV_BLE_SM_AUTHEN_REQ_MODE: {
                uint8_t authen_req = 0;
                STREAM_TO_UINT8(authen_req, value);
                bta_dm_co_ble_set_auth_req(authen_req);
                break;
            }
            case SSV_BLE_SM_IOCAP_MODE: {
                uint8_t iocap = 0;
                STREAM_TO_UINT8(iocap, value);
                bta_dm_co_ble_set_io_cap(iocap);
                break;
            }
            case SSV_BLE_SM_SET_INIT_KEY: {
                uint8_t init_key = 0;
                STREAM_TO_UINT8(init_key, value);
                bta_dm_co_ble_set_init_key_req(init_key);
                break;
            }
            case SSV_BLE_SM_SET_RSP_KEY: {
                uint8_t rsp_key = 0;
                STREAM_TO_UINT8(rsp_key, value);
                bta_dm_co_ble_set_rsp_key_req(rsp_key);
                break;
            }
            case SSV_BLE_SM_MAX_KEY_SIZE: {
                uint8_t key_size = 0;
                STREAM_TO_UINT8(key_size, value);
                bta_dm_co_ble_set_max_key_size(key_size);
                break;
            }
            case SSV_BLE_SM_MIN_KEY_SIZE: {
                uint8_t key_size = 0;
                STREAM_TO_UINT8(key_size, value);
                bta_dm_co_ble_set_min_key_size(key_size);
                break;
            }
            case SSV_BLE_SM_SET_STATIC_PASSKEY: {
                uint32_t passkey = 0;
                for(uint8_t i = 0; i < arg->set_security_param.len; i++)
                {
                    passkey += (((uint8_t *)value)[i]<<(8*i));
                }
                BTA_DmBleSetStaticPasskey(true, passkey);
                break;
            }
            case SSV_BLE_SM_CLEAR_STATIC_PASSKEY: {
                BTA_DmBleSetStaticPasskey(false, 0);
                break;
            }
            case SSV_BLE_SM_ONLY_ACCEPT_SPECIFIED_SEC_AUTH: {
                uint8_t enable = 0;
                STREAM_TO_UINT8(enable, value);
                bta_dm_co_ble_set_accept_auth_enable(enable);
                break;
            }
            case SSV_BLE_SM_OOB_SUPPORT: {
                uint8_t enable = 0;
                STREAM_TO_UINT8(enable, value);
                bta_dm_co_ble_oob_support(enable);
                break;
            }
            default:
                break;
        }
    #endif
    break;
    }

    case BTC_GAP_BLE_SECURITY_RSP_EVT: {
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        BD_ADDR bd_addr;
        tBTA_DM_BLE_SEC_GRANT res = arg->sec_rsp.accept ? BTA_DM_SEC_GRANTED : BTA_DM_SEC_PAIR_NOT_SPT;
        memcpy(bd_addr, arg->sec_rsp.bd_addr, sizeof(BD_ADDR));
        BTA_DmBleSecurityGrant(bd_addr, res);
    #endif
        break;
    }

    case BTC_GAP_BLE_PASSKEY_REPLY_EVT: {
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        BD_ADDR bd_addr;
        memcpy(bd_addr, arg->enc_passkey_replay.bd_addr, sizeof(BD_ADDR));
        BTA_DmBlePasskeyReply(bd_addr, arg->enc_passkey_replay.accept, arg->enc_passkey_replay.passkey);
    #endif
        break;
    }

    case BTC_GAP_BLE_CONFIRM_REPLY_EVT: {
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        BD_ADDR bd_addr;
        memcpy(bd_addr, arg->enc_comfirm_replay.bd_addr, sizeof(BD_ADDR));
        BTA_DmBleConfirmReply(bd_addr, arg->enc_comfirm_replay.accept);
    #endif
        break;
    }

    case BTC_GAP_BLE_REMOVE_BOND_DEV_EVT: {
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        BD_ADDR bd_addr;
        memcpy(bd_addr, arg->remove_bond_device.bd_addr, sizeof(BD_ADDR));
        BTA_DmRemoveDevice(bd_addr, BT_TRANSPORT_LE);
    #endif
        break;
    }
    case BTC_GAP_BLE_OOB_REQ_REPLY_EVT:
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        BTA_DmOobReply(arg->oob_req_reply.bd_addr, arg->oob_req_reply.len, arg->oob_req_reply.p_value);
    #endif  ///SMP_INCLUDED == TRUE
        break;
#endif  ///SMP_INCLUDED == TRUE
    case BTC_GAP_BLE_DISCONNECT_EVT:
        btc_ble_disconnect(arg->disconnect.remote_device);
        break;
    default:
        break;
    }

    btc_gap_ble_arg_deep_free(msg);

}

void btc_gap_ble_arg_deep_copy(btc_msg_t *msg, void *p_dest, void *p_src)
{
    switch (msg->act) {
    case BTC_GAP_BLE_ACT_CFG_ADV_DATA: {
        btc_ble_gap_args_t *src = (btc_ble_gap_args_t *)p_src;
        btc_ble_gap_args_t  *dst = (btc_ble_gap_args_t *) p_dest;

        if (src->cfg_adv_data.adv_data.p_manufacturer_data) {
            dst->cfg_adv_data.adv_data.p_manufacturer_data = osi_malloc(src->cfg_adv_data.adv_data.manufacturer_len);
            memcpy(dst->cfg_adv_data.adv_data.p_manufacturer_data, src->cfg_adv_data.adv_data.p_manufacturer_data,
                   src->cfg_adv_data.adv_data.manufacturer_len);
        }

        if (src->cfg_adv_data.adv_data.p_service_data) {
            dst->cfg_adv_data.adv_data.p_service_data = osi_malloc(src->cfg_adv_data.adv_data.service_data_len);
            memcpy(dst->cfg_adv_data.adv_data.p_service_data, src->cfg_adv_data.adv_data.p_service_data, src->cfg_adv_data.adv_data.service_data_len);
        }

        if (src->cfg_adv_data.adv_data.p_service_uuid) {
            dst->cfg_adv_data.adv_data.p_service_uuid = osi_malloc(src->cfg_adv_data.adv_data.service_uuid_len);
            memcpy(dst->cfg_adv_data.adv_data.p_service_uuid, src->cfg_adv_data.adv_data.p_service_uuid, src->cfg_adv_data.adv_data.service_uuid_len);
        }
        break;
    }
    case BTC_GAP_BLE_ACT_CFG_ADV_DATA_RAW: {
        btc_ble_gap_args_t *src = (btc_ble_gap_args_t *)p_src;
        btc_ble_gap_args_t *dst = (btc_ble_gap_args_t *) p_dest;

        if (src && src->cfg_adv_data_raw.raw_adv && src->cfg_adv_data_raw.raw_adv_len > 0) {
            dst->cfg_adv_data_raw.raw_adv = osi_malloc(src->cfg_adv_data_raw.raw_adv_len);
            if (dst->cfg_adv_data_raw.raw_adv) {
                memcpy(dst->cfg_adv_data_raw.raw_adv, src->cfg_adv_data_raw.raw_adv, src->cfg_adv_data_raw.raw_adv_len);
            }
        }
        break;
    }
    case BTC_GAP_BLE_ACT_CFG_SCAN_RSP_DATA_RAW: {
        btc_ble_gap_args_t *src = (btc_ble_gap_args_t *)p_src;
        btc_ble_gap_args_t *dst = (btc_ble_gap_args_t *) p_dest;

        if (src && src->cfg_scan_rsp_data_raw.raw_scan_rsp && src->cfg_scan_rsp_data_raw.raw_scan_rsp_len > 0) {
            dst->cfg_scan_rsp_data_raw.raw_scan_rsp = osi_malloc(src->cfg_scan_rsp_data_raw.raw_scan_rsp_len);
            if (dst->cfg_scan_rsp_data_raw.raw_scan_rsp) {
                memcpy(dst->cfg_scan_rsp_data_raw.raw_scan_rsp, src->cfg_scan_rsp_data_raw.raw_scan_rsp, src->cfg_scan_rsp_data_raw.raw_scan_rsp_len);
            }
        }
          break;
       }
    case BTC_GAP_BLE_SET_SECURITY_PARAM_EVT: {
        btc_ble_gap_args_t *src = (btc_ble_gap_args_t *)p_src;
        btc_ble_gap_args_t  *dst = (btc_ble_gap_args_t *) p_dest;
        uint8_t length = 0;
        if (src->set_security_param.value) {
            length = dst->set_security_param.len;
            dst->set_security_param.value = osi_malloc(length);
            if (dst->set_security_param.value != NULL) {
                memcpy(dst->set_security_param.value, src->set_security_param.value, length);
            } else {
                BTC_TRACE_ERROR("%s %d no mem\n",__func__, msg->act);
            }
        }
        break;
    }
    case BTC_GAP_BLE_OOB_REQ_REPLY_EVT: {
        btc_ble_gap_args_t *src = (btc_ble_gap_args_t *)p_src;
        btc_ble_gap_args_t  *dst = (btc_ble_gap_args_t *) p_dest;
        uint8_t length = 0;
        if (src->oob_req_reply.p_value) {
            length = dst->oob_req_reply.len;
            dst->oob_req_reply.p_value = osi_malloc(length);
            if (dst->oob_req_reply.p_value != NULL) {
                memcpy(dst->oob_req_reply.p_value, src->oob_req_reply.p_value, length);
            } else {
                BTC_TRACE_ERROR("%s %d no mem\n",__func__, msg->act);
            }
        }
        break;
    }
    default:
        BTC_TRACE_ERROR("Unhandled deep copy %d\n", msg->act);
        break;
    }
}

void btc_gap_ble_cb_deep_copy(btc_msg_t *msg, void *p_dest, void *p_src)
{
    switch (msg->act) {
    default:
       BTC_TRACE_ERROR("%s, Unhandled deep copy %d\n", __func__, msg->act);
       break;
    }
}

void btc_gap_ble_arg_deep_free(btc_msg_t *msg)
{
    BTC_TRACE_DEBUG("%s \n", __func__);
    switch (msg->act) {
    case BTC_GAP_BLE_ACT_CFG_ADV_DATA: {
        ssv_ble_adv_data_t *adv = &((btc_ble_gap_args_t *)msg->arg)->cfg_adv_data.adv_data;
        if (adv->p_service_data) {
            osi_free(adv->p_service_data);
        }

        if (adv->p_service_uuid) {
            osi_free(adv->p_service_uuid);
        }

        if (adv->p_manufacturer_data) {
            osi_free(adv->p_manufacturer_data);
        }
        break;
    }
    case BTC_GAP_BLE_ACT_CFG_ADV_DATA_RAW: {
        uint8_t *raw_adv = ((btc_ble_gap_args_t *)msg->arg)->cfg_adv_data_raw.raw_adv;
        if (raw_adv) {
            osi_free(raw_adv);
        }
        break;
    }
    case BTC_GAP_BLE_ACT_CFG_SCAN_RSP_DATA_RAW: {
        uint8_t *raw_scan_rsp = ((btc_ble_gap_args_t *)msg->arg)->cfg_scan_rsp_data_raw.raw_scan_rsp;
        if (raw_scan_rsp) {
            osi_free(raw_scan_rsp);
        }
        break;
    }
    case BTC_GAP_BLE_SET_SECURITY_PARAM_EVT: {
        uint8_t *value = ((btc_ble_gap_args_t *)msg->arg)->set_security_param.value;
        if (value) {
            osi_free(value);
        }
        break;
    }
    case BTC_GAP_BLE_OOB_REQ_REPLY_EVT: {
        uint8_t *value = ((btc_ble_gap_args_t *)msg->arg)->oob_req_reply.p_value;
        if (value) {
            osi_free(value);
        }
        break;
    }
    default:
        BTC_TRACE_DEBUG("Unhandled deep free %d\n", msg->act);
        break;
    }
}

void btc_gap_ble_cb_deep_free(btc_msg_t *msg)
{
    BTC_TRACE_DEBUG("%s", __func__);
    switch (msg->act) {
        default:
            BTC_TRACE_DEBUG("Unhandled deep free %d", msg->act);
            break;
    }
}

void btc_get_whitelist_size(uint16_t *length)
{
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    //BTM_BleGetWhiteListSize(length);
    return;
}


#if SCAN_QUEUE_CONGEST_CHECK
void btc_adv_list_free(void *data)
{
    osi_free(data);
}

void btc_adv_list_init(void)
{
    osi_mutex_new(&adv_list_lock);
    adv_filter_list = list_new(btc_adv_list_free);
}

void btc_adv_list_deinit(void)
{
    osi_mutex_free(&adv_list_lock);
    if(adv_filter_list) {
        list_free(adv_filter_list);
        adv_filter_list = NULL;
    }
}
void btc_adv_list_add_packet(void * data)
{
    if(!data) {
        BTC_TRACE_ERROR("%s data is NULL", __func__);
        return;
    }
    btc_adv_list_lock();
    list_prepend(adv_filter_list, data);
    btc_adv_list_unlock();
}

uint32_t btc_get_adv_list_length(void)
{
    if(!adv_filter_list) {
        BTC_TRACE_ERROR("%s adv_filter_list is NULL", __func__);
        return 0;
    }
    btc_adv_list_lock();
    size_t length = list_length(adv_filter_list);
    btc_adv_list_unlock();

    return length;
}

void btc_adv_list_refresh(void)
{
    if(!adv_filter_list) {
        BTC_TRACE_ERROR("%s adv_filter_list is NULL", __func__);
        return ;
    }
    btc_adv_list_lock();
    list_clear(adv_filter_list);
    btc_adv_list_unlock();
}

bool btc_check_adv_list(uint8_t * addr, uint8_t addr_type)
{
    bool found = false;
    if(!adv_filter_list || !addr) {
        BTC_TRACE_ERROR("%s adv_filter_list is NULL", __func__);
        return found;
    }

    btc_adv_list_lock();
    for (const list_node_t *node = list_begin(adv_filter_list); node != list_end(adv_filter_list); node = list_next(node)) {
        btc_adv_packet_t *packet = (btc_adv_packet_t *)list_node(node);
        if(!bdcmp(addr, packet->addr) && packet->addr_type == addr_type) {
            found = true;
            break;
        }
     }
     btc_adv_list_unlock();
     if(!found) {
         btc_adv_packet_t *adv_packet = osi_malloc(sizeof(btc_adv_packet_t));
         if(adv_packet) {
             adv_packet->addr_type = addr_type;
             bdcpy(adv_packet->addr, addr);
             btc_adv_list_add_packet(adv_packet);
         } else {
             BTC_TRACE_ERROR("%s adv_packet malloc failed", __func__);
         }
     }
    return found;
}

void btc_adv_list_lock(void)
{
    osi_mutex_lock(&adv_list_lock, OSI_MUTEX_MAX_TIMEOUT);
}

void btc_adv_list_unlock(void)
{
    osi_mutex_unlock(&adv_list_lock);
}
#endif


#endif  ///BLE_INCLUDED == TRUE
