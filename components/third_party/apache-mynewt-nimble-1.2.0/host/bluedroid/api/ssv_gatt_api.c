/*
 * Copyright (c) 2017 Nordic Semiconductor ASA
 * Copyright (c) 2015-2016 Intel Corporation
 * Additional Copyright (c) 2018 Espressif Systems (Shanghai) PTE LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>

#include "sdkconfig.h"

#include "btc/btc_task.h"
#include "osi/alarm.h"

#include "mbedtls/aes.h"
#include "mbedtls/ecp.h"

#include "host/ble_hs.h"
#include "host/ble_uuid.h"
#include "host/ble_att.h"
#include "host/ble_gatt.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"

#include "mesh_hci.h"
#include "mesh_aes_encrypt.h"
#include "mesh_bearer_adapt.h"
#include "mesh_trace.h"
#include "mesh_buf.h"
#include "mesh_atomic.h"

#include "ssv_ble_mesh_defs.h"

#include "provisioner_prov.h"
#include "mesh_common.h"
#include "osal.h"

#include "ssv_gatt_api.h"


void bt_gattc_disconnect(uint16_t conn_handle)
{
    ble_gap_terminate(conn_handle, BLE_ERR_REM_USER_CONN_TERM);
}


static gatt_mtu_cb_t gatt_mtu_cb_handler=NULL;
static int gatt_mtu_cb(uint16_t conn_handle,
                  const struct ble_gatt_error *error,
                  uint16_t mtu, void *arg)
{
    if(NULL!=gatt_mtu_cb_handler)
    {
        gatt_mtu_cb_handler(mtu);
    }
    return 0;
}
void bt_gattc_exchanged_mtu(uint16_t conn_handle, gatt_mtu_cb_t cb, void *cb_arg)
{
    gatt_mtu_cb_handler=cb;
    ble_gattc_exchange_mtu(conn_handle, gatt_mtu_cb, NULL);
}

int bt_gatt_set_preferred_mtu(uint16_t value)
{
    ble_att_set_preferred_mtu(value);
    return 0;
}

u16_t bt_gatt_get_preferred_mtu(void)
{
    return ble_att_preferred_mtu();
}

extern void ms_test_ble_service_ff82_indicate_cb(void);
extern uint16_t gatt_svr_val_handle;
static gaps_hal_evt_cb_t _gaps_evt_cb=NULL;
static int ssv_gaps_event_cb(struct ble_gap_event *event, void *arg)
{
    struct ble_gap_conn_desc desc;
    int rc;
    switch (event->type) {
    case BLE_GAP_EVENT_CONNECT:
        /* A new connection was established or a connection attempt failed. */
        printf("\33[32mSSV connection %s; status=%d\33[0m\n",
                    event->connect.status == 0 ? "established" : "failed",
                    event->connect.status);
        break;

    case BLE_GAP_EVENT_DISCONNECT:
        printf("\33[32mSSV disconnect; reason=%d\33[0m\n", event->disconnect.reason);
        break;

    case BLE_GAP_EVENT_CONN_UPDATE:
        /* The central has updated the connection parameters. */
        printf("\33[32mSSV connection updated; status=%d\33[0m\n",
                    event->conn_update.status);
        break;

    case BLE_GAP_EVENT_ADV_COMPLETE:
        printf("\33[32mSSV advertise complete; reason=%d\33[0m\n",
                    event->adv_complete.reason);
        break;

    case BLE_GAP_EVENT_MTU:
        printf("\33[32mmtu update event; conn_handle=%d cid=%d mtu=%d\33[0m\n",
                    event->mtu.conn_handle,
                    event->mtu.channel_id,
                    event->mtu.value);

        break;

    case BLE_GAP_EVENT_NOTIFY_TX:
        switch (event->notify_tx.status) {
            case 0:
                printf("\33[32mNOTIFY_TX Command successfully sent\33[0m\n");
                break;
            case BLE_HS_EDONE:
                printf("\33[32mNOTIFY_TX Command EDONE\33[0m\n");
                break;
            case BLE_HS_ETIMEOUT:
                printf("\33[32mNOTIFY_TX Command TIMEOUT\33[0m\n");
                break;
        }
         printf("\33[32mNOTIFY_TX conn_handle=%d attr_handle=%d indication=%d\33[0m\n",
                event->notify_tx.conn_handle,
                event->notify_tx.attr_handle,
                event->notify_tx.indication);

        break;

    case BLE_GAP_EVENT_NOTIFY_RX:
        printf("\33[32mNOTIFY_RX conn_handle=%d attr_handle=%d indication=%d\33[0m\n",
                event->notify_rx.conn_handle,
                event->notify_rx.attr_handle,
                event->notify_rx.indication);

        break;
    }

    if(_gaps_evt_cb) /* call ms_hal_ble_gaps_evt_cb*/
            _gaps_evt_cb(event);

    return 0;
}

int set_ad(const struct ssv_bt_adv_data *ad, size_t ad_len, u8_t *buf, u8_t *buf_len)
{
    int i;

    for (i = 0; i < ad_len; i++) {
        buf[(*buf_len)++] = ad[i].data_len + 1;
        buf[(*buf_len)++] = ad[i].type;

        memcpy(&buf[*buf_len], ad[i].data,
               ad[i].data_len);
        *buf_len += ad[i].data_len;
    }

    return 0;
}
/* APIs functions */
int bt_le_adv_enable(const struct ssv_bt_adv_param *param,
                    const struct ssv_bt_adv_data *ad, size_t ad_len,
                    const struct ssv_bt_adv_data *sd, size_t sd_len,
                    gaps_hal_evt_cb_t gaps_cb)
{
    uint8_t buf[BLE_HS_ADV_MAX_SZ];
    uint8_t buf_len = 0;
    int err;
    struct ble_gap_adv_params adv_params;

    //debug
    if ((ad[0].data_len + 2) > BLE_HS_ADV_MAX_SZ) {
        printf("error ad data_len, may assert\n", ad[0].data_len);
        ASSERT(0);//length dbg
    }
    //debug end

    err = set_ad(ad, ad_len, buf, &buf_len);
    if (buf_len > BLE_HS_ADV_MAX_SZ) {
        printf("error set_ad data_len %d\n", buf_len);
        ASSERT(0);//length dbg
    }

    if (err) {
        BT_ERR("set_ad failed: err %d", err);
        return err;
    }

    err = ble_gap_adv_set_data(buf, buf_len);
    if (err != 0) {
        BT_ERR("Advertising set failed: err %d", err);
        return err;
    }

    if (sd && (param->options & BLE_MESH_ADV_OPT_CONNECTABLE)) {
        buf_len = 0;

        err = set_ad(sd, sd_len, buf, &buf_len);
        if (err) {
            BT_ERR("set_ad failed: err %d", err);
            return err;
        }

        err = ble_gap_adv_rsp_set_data(buf, buf_len);
        if (err != 0) {
            BT_ERR("Scan rsp failed: err %d", err);
            return err;
        }
    }

    memset(&adv_params, 0, sizeof adv_params);
    adv_params.itvl_min = param->interval_min;
    adv_params.itvl_max = param->interval_max;

    if (param->options & BLE_MESH_ADV_OPT_CONNECTABLE) {
        adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
        adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;
    } else if (sd != NULL) {
        adv_params.conn_mode = BLE_GAP_CONN_MODE_NON;
        adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;
    } else {
        adv_params.conn_mode = BLE_GAP_CONN_MODE_NON;
        adv_params.disc_mode = BLE_GAP_DISC_MODE_NON;
    }
    _gaps_evt_cb=gaps_cb;
    err = ble_gap_adv_start(BLE_OWN_ADDR_PUBLIC, NULL, BLE_HS_FOREVER, &adv_params,
                            ssv_gaps_event_cb, NULL);
    if (err) {
        BT_ERR("Advertising start failed: err %d", err);
        return err;
    }

    return 0;
}

int bt_le_adv_disable(void)
{
    return ble_gap_adv_stop();
}




static gapc_evt_cb_t _gapc_evt_cb=NULL;
static int ssv_gapc_event_cb(struct ble_gap_event *event, void *arg)
{/* master */
    printf("\33[32mssv_gapc_event_cb start\33[0m\r\n");
    switch (event->type) {
    case BLE_GAP_EVENT_CONNECT:
        if (event->connect.status == 0) {
            /* Connection successfully established. */
            printf("\33[32mgap_cb:BLE_GAP_EVENT_CONNECT\33[0m\r\n");
            if(NULL!=_gapc_evt_cb)
            {
                _gapc_evt_cb(event->connect.conn_handle, BLE_GAP_EVENT_CONNECT);
            }
        }
        break;
    case BLE_GAP_EVENT_DISCONNECT:
        printf("\33[32mgap_cb:BLE_GAP_EVENT_DISCONNECT\33[0m\r\n");
        if(NULL!=_gapc_evt_cb)
        {
            _gapc_evt_cb(event->connect.conn_handle,BLE_GAP_EVENT_DISCONNECT);
        }
        break;
    case BLE_GAP_EVENT_MTU:
        printf("\33[32mgap_cb:BLE_GAP_EVENT_MTU\33[0m\r\n");
        break;
    default:
        printf("\33[32unknow event type %d\33[0m\r\n",event->type);
        break;
    }
    printf("\33[32mssv_gapc_event_cb end\33[0m\r\n");
    return 0;
}

int bt_gattc_conn_create(void *param, u8_t *addr, u8_t addr_type, gapc_evt_cb_t gapc_cb)
{
        /* Min_interval: 250ms
     * Max_interval: 250ms
     * Slave_latency: 0x0
     * Supervision_timeout: 32 sec
     */
    struct ble_gap_conn_params conn_params = {0};
    ble_addr_t peer_addr;
    conn_params.itvl_min = 0xC8; /* (250 * 1000) / 1250 = 200 = 0xC8 */
    conn_params.itvl_max = 0xC8; /* (250 * 1000) / 1250 = 200 = 0xC8 */
    conn_params.latency = 0;
    conn_params.supervision_timeout = 0xC80;
    conn_params.scan_itvl = 0x0020; //0x0010
    conn_params.scan_window = 0x0020; //0x0010
    conn_params.min_ce_len = BLE_GAP_INITIAL_CONN_MIN_CE_LEN;
    conn_params.max_ce_len = BLE_GAP_INITIAL_CONN_MAX_CE_LEN;



    memcpy(peer_addr.val, addr, 6);
    peer_addr.type = addr_type;
    _gapc_evt_cb = gapc_cb;
    ble_gap_connect(BLE_OWN_ADDR_PUBLIC, &peer_addr, BLE_HS_FOREVER, &conn_params,
                     ssv_gapc_event_cb, NULL);

    return 0;
}

extern void ble_att_print_ha_cb(void);
void bt_gatt_init(struct ble_gatt_svc_def *defs)
{
    int rc = 0;
    ble_att_set_preferred_mtu(BLE_ATT_MTU_DFLT);

    //ble_hs_cfg.gatts_register_cb = gatt_register_cb;


    ble_svc_gap_init();
    ble_svc_gatt_init();
#if 1
    rc = ble_gatts_count_cfg(defs);
    printf("\33[31mIan %s():%d rc=%d\33[0m\r\n",__FUNCTION__ ,__LINE__,rc);
    assert(rc == 0);
    rc = ble_gatts_add_svcs(defs);
    printf("\33[31mIan %s():%d rc=%d\33[0m\r\n",__FUNCTION__ ,__LINE__,rc);
    assert(rc == 0);
    ble_att_print_ha_cb();
    ble_gatts_start();

    //ble_gatts_svc_set_visibility(prov_svc_start_handle, 1);
    //ble_gatts_svc_set_visibility(proxy_svc_start_handle, 0);
#else
     ble_gatts_start();
#endif
}
#if 0
static struct ble_gap_disc_params scan_param;
static int start_le_scan(u8_t scan_type, u16_t interval, u16_t window, u8_t filter_dup)
{

    scan_param.filter_duplicates = filter_dup;
    scan_param.itvl = interval;
    scan_param.window = window;

    if (scan_type == 0x00) { //BLE_MESH_SCAN_PASSIVE
        scan_param.passive = 1;
    } else {
        scan_param.passive = 0;
    }
    ble_gap_disc(BLE_OWN_ADDR_PUBLIC, INT32_MAX, &scan_param, disc_cb, NULL);//# define INT32_MAX		(2147483647)


    return 0;
}
#endif
int bt_le_scan_enable(const struct ssv_bt_scan_param *param, ssv_bt_scan_cb_t cb)
{
    int err = 0;
#if 0
    err = start_le_scan(param->type, param->interval, param->window, param->filter_dup);
    if (err) {
        return err;
    }
#endif
    return err;
}

int bt_le_scan_disable(void)
{
    ble_gap_disc_cancel();
    return 0;
}