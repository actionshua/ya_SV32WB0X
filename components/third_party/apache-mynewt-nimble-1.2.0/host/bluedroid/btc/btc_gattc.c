#include <string.h>

#include "bta/bta_gatt_api.h"

#include "btc/btc_task.h"
#include "btc/btc_manage.h"
#include "btc/btc_gattc.h"
#include "btc_gatt_util.h"
//#include "osi/future.h"
#include "osi/allocator.h"
//#include "btc/btc_main.h"
#include "ssv_gattc_api.h"
#include "ssv_gatt_defs.h"
#include "btc/btc_gatt_common.h"
#include "btc/btc_gap_ble.h"
#include "host/ble_gatt.h"
#include <host/ble_hs_mbuf.h>

void btc_gattc_arg_deep_copy(btc_msg_t *msg, void *p_dest, void *p_src)
{
    btc_ble_gattc_args_t *dst = (btc_ble_gattc_args_t *) p_dest;
    btc_ble_gattc_args_t *src = (btc_ble_gattc_args_t *)p_src;

    switch (msg->act) {
    case BTC_GATTC_ACT_WRITE_CHAR: {
        dst->write_char.value = (uint8_t *)osi_malloc(src->write_char.value_len);
        if (dst->write_char.value) {
            memcpy(dst->write_char.value, src->write_char.value, src->write_char.value_len);
        } else {
            BTC_TRACE_ERROR("%s %d no mem\n", __func__, msg->act);
        }
        break;
    }
    case BTC_GATTC_ACT_WRITE_CHAR_DESCR: {
        dst->write_descr.value = (uint8_t *)osi_malloc(src->write_descr.value_len);
        if (dst->write_descr.value) {
            memcpy(dst->write_descr.value, src->write_descr.value, src->write_descr.value_len);
        } else {
            BTC_TRACE_ERROR("%s %d no mem\n", __func__, msg->act);
        }
        break;
    }
    case BTC_GATTC_ACT_PREPARE_WRITE: {
        dst->prep_write.value = (uint8_t *)osi_malloc(src->prep_write.value_len);
        if (dst->prep_write.value) {
            memcpy(dst->prep_write.value, src->prep_write.value, src->prep_write.value_len);
        } else {
            BTC_TRACE_ERROR("%s %d no mem\n", __func__, msg->act);
        }
        break;
    }
    case BTC_GATTC_ACT_PREPARE_WRITE_CHAR_DESCR: {
        dst->prep_write_descr.value = (uint8_t *)osi_malloc(src->prep_write_descr.value_len);
        if (dst->prep_write_descr.value) {
            memcpy(dst->prep_write_descr.value, src->prep_write_descr.value, src->prep_write_descr.value_len);
        } else {
            BTC_TRACE_ERROR("%s %d no mem\n", __func__, msg->act);
        }
        break;
    }
    default:
        BTC_TRACE_DEBUG("%s Unhandled deep copy %d\n", __func__, msg->act);
        break;
    }
}

void btc_gattc_arg_deep_free(btc_msg_t *msg)
{
    btc_ble_gattc_args_t *arg = (btc_ble_gattc_args_t *)msg->arg;

    switch (msg->act) {
    case BTC_GATTC_ACT_WRITE_CHAR: {
        if (arg->write_char.value) {
            osi_free(arg->write_char.value);
        }
        break;
    }
    case BTC_GATTC_ACT_WRITE_CHAR_DESCR: {
        if (arg->write_descr.value) {
            osi_free(arg->write_descr.value);
        }
        break;
    }
    case BTC_GATTC_ACT_PREPARE_WRITE: {
        if (arg->prep_write.value) {
            osi_free(arg->prep_write.value);
        }
        break;
    }
    case BTC_GATTC_ACT_PREPARE_WRITE_CHAR_DESCR: {
        if (arg->prep_write_descr.value) {
            osi_free(arg->prep_write_descr.value);
        }
        break;
    }
    default:
        BTC_TRACE_DEBUG("%s Unhandled deep free %d\n", __func__, msg->act);
        break;
    }

}

static void btc_gattc_free_req_data(btc_msg_t *msg)
{
    tBTA_GATTC *arg = (tBTA_GATTC *)(msg->arg);
    switch (msg->act) {
        case BTA_GATTC_READ_DESCR_EVT:
        case BTA_GATTC_READ_CHAR_EVT:
        case BTA_GATTC_READ_MULTIPLE_EVT: {
            if (arg->read.p_value) {
                osi_free(arg->read.p_value);
            }
            break;
        }
        case BTA_GATTC_GET_ADDR_LIST_EVT: {
            if (arg->get_addr_list.bda_list) {
                osi_free(arg->get_addr_list.bda_list);
            }
            break;
        }
        default:
            break;
    }
    return;
}
uint16_t g_gattc_app_id = 0;

static void btc_gattc_app_register(btc_ble_gattc_args_t *arg)
{
    tBTA_GATTC reg;
    //tBT_UUID app_uuid;
    //app_uuid.len = 2;
    //app_uuid.uu.uuid16 = arg->app_reg.app_id;
    //BTA_GATTC_AppRegister(&app_uuid, btc_gattc_cback);

    reg.reg_oper.client_if = CLIENT_IF_ID;
    reg.reg_oper.status = SSV_GATT_OK;
    reg.reg_oper.app_uuid.len = 2;
    reg.reg_oper.app_uuid.uu.uuid16 = arg->app_reg.app_id;/* APP ID */
    g_gattc_app_id = arg->app_reg.app_id;
    btc_gatt_com_to_cb_handler((void*)&reg, sizeof(reg), BTA_GATTC_REG_EVT, BTC_PID_GATTC);
}

static void btc_gattc_app_unregister(btc_ble_gattc_args_t *arg)
{
    tBTA_GATTC reg;
    //tBT_UUID app_uuid;
    //app_uuid.len = 2;
    //app_uuid.uu.uuid16 = arg->app_reg.app_id;
    //BTA_GATTC_AppRegister(&app_uuid, btc_gattc_cback);

    reg.reg_oper.client_if = CLIENT_IF_ID;
    reg.reg_oper.status = SSV_GATT_OK;
    reg.reg_oper.app_uuid.len = 2;
    reg.reg_oper.app_uuid.uu.uuid16 = arg->app_reg.app_id;/* APP ID */
    g_gattc_app_id = 0;
    btc_gatt_com_to_cb_handler((void*)&reg, sizeof(reg), BTA_GATTC_DEREG_EVT, BTC_PID_GATTC);
}

static void btc_gattc_open(btc_ble_gattc_args_t *arg)
{
    tBTA_GATT_TRANSPORT transport = BTA_GATT_TRANSPORT_LE;
    /*    struct open_arg {
        ssv_gatt_if_t gattc_if;
        ssv_bd_addr_t remote_bda;
        ssv_ble_addr_type_t remote_addr_type;
        bool is_direct;
    } open;
    */

    btc_gap_ble_conn_create(arg->open.gattc_if, arg->open.remote_bda,
        arg->open.remote_addr_type, arg->open.is_direct, transport);
    //BTA_GATTC_Open(arg->open.gattc_if, arg->open.remote_bda, arg->open.remote_addr_type, arg->open.is_direct, transport);
}

int btc_gattc_mtu_cb(uint16_t conn_handle, const struct ble_gatt_error *error,
    uint16_t mtu, void *arg)
{
    tBTA_GATTC cfg_mtu;
    int ret = 0;

    if (error) {
        if (error->status) {
            printf("%s status %d\n", __FUNCTION__, error->status);
            return ret;
        }
    } else /*error is NULL*/
        return ret;

    printf("%s conn_handle %d, mtu %d\n", __FUNCTION__, conn_handle, mtu);

    if (mtu) {
        cfg_mtu.cfg_mtu.conn_id = BTC_GATT_CREATE_CONN_ID(CLIENT_IF_ID, conn_handle);
        cfg_mtu.cfg_mtu.mtu = mtu;
        cfg_mtu.cfg_mtu.status = error->status;
        btc_gatt_com_to_cb_handler((void*)&cfg_mtu, sizeof(cfg_mtu), BTA_GATTC_CFG_MTU_EVT, BTC_PID_GATTC);
    }
    return ret;
}

static void btc_gattc_cfg_mtu(btc_ble_gattc_args_t *arg)
{
    printf("btc_gattc_cfg_mtu conn_id %d\n", BTC_GATT_GET_CONN_ID(arg->cfg_mtu.conn_id));
    ble_gattc_exchange_mtu(BTC_GATT_GET_CONN_ID(arg->cfg_mtu.conn_id),
        btc_gattc_mtu_cb, NULL);

}

int btc_gattc_write_char_cb(uint16_t conn_handle,
    const struct ble_gatt_error *error,
    struct ble_gatt_attr *attr,
    void *arg)
{
    int ret = 0;

    if (error) {
        printf("%s conn_handle = %d, error = %d, att_handle = %d\n", __FUNCTION__,
            conn_handle, error->status, error->att_handle);
    }

    return ret;
}

static void btc_gattc_write_char(btc_ble_gattc_args_t *arg)
{
    struct os_mbuf *om = NULL;
    int ret = 0;
    tBTA_GATTC write_char;

    write_char.write.conn_id = BTC_GATT_CREATE_CONN_ID(CLIENT_IF_ID, arg->write_char.conn_id);
    write_char.write.handle = arg->write_char.handle;
    write_char.write.offset = 0;

    do
    {
        if (arg->write_char.value_len == 0 || arg->write_char.value == NULL) {
            printf("%s value_len = %d or value is NULL\n", __FUNCTION__,
                arg->write_char.value_len);

            write_char.write.status = SSV_GATT_INVALID_PDU;
            break;
        }

        om = ble_hs_mbuf_from_flat(arg->write_char.value, arg->write_char.value_len);

        if (om == NULL) {
            printf("%s om create fail\n", __FUNCTION__);
            write_char.write.status = SSV_GATT_NO_RESOURCES;
            break;
        }

        ret = ble_gattc_write(BTC_GATT_GET_CONN_ID(arg->write_char.conn_id), arg->write_char.handle,
            om, btc_gattc_write_char_cb, NULL);

        if (ret){
            printf("%s ble_gattc_write fail %d\n", __FUNCTION__, ret);
            write_char.write.status = SSV_GATT_ERROR;
            break;
        }

        write_char.write.status = SSV_GATT_OK;
    } while(0);

    btc_gatt_com_to_cb_handler((void*)&write_char, sizeof(write_char), BTA_GATTC_WRITE_CHAR_EVT, BTC_PID_GATTC);
}

void btc_gattc_call_handler(btc_msg_t *msg)
{
    btc_ble_gattc_args_t *arg = (btc_ble_gattc_args_t *)(msg->arg);
    switch (msg->act) {
    case BTC_GATTC_ACT_APP_REGISTER:
        btc_gattc_app_register(arg);
        break;
    case BTC_GATTC_ACT_APP_UNREGISTER:
        btc_gattc_app_unregister(arg);
        break;
    case BTC_GATTC_ACT_OPEN:
        btc_gattc_open(arg);
        break;
    case BTC_GATTC_ACT_CLOSE:
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
        //btc_gattc_close(arg);
        break;
    case BTC_GATTC_ACT_CFG_MTU:
        btc_gattc_cfg_mtu(arg);
        break;
    case BTC_GATTC_ACT_SEARCH_SERVICE:
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
        //btc_gattc_search_service(arg);
        break;
    case BTC_GATTC_ACT_READ_CHAR:
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
        //btc_gattc_read_char(arg);
        break;
    case BTC_GATTC_ACT_READ_MULTIPLE_CHAR:
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
        //btc_gattc_read_multiple_char(arg);
        break;
    case BTC_GATTC_ACT_READ_CHAR_DESCR:
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
        //btc_gattc_read_char_descr(arg);
        break;
    case BTC_GATTC_ACT_WRITE_CHAR:
        btc_gattc_write_char(arg);
        break;
    case BTC_GATTC_ACT_WRITE_CHAR_DESCR:
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
        //btc_gattc_write_char_descr(arg);
        break;
    case BTC_GATTC_ACT_PREPARE_WRITE:
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
        //btc_gattc_prepare_write(arg);
        break;
    case BTC_GATTC_ACT_PREPARE_WRITE_CHAR_DESCR:
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
        //btc_gattc_prepare_write_char_descr(arg);
        break;
    case BTC_GATTC_ACT_EXECUTE_WRITE:
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
        //btc_gattc_execute_write(arg);
        break;
    case BTC_GATTC_ACT_REG_FOR_NOTIFY:
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
        //btc_gattc_reg_for_notify(arg);
        break;
    case BTC_GATTC_ACT_UNREG_FOR_NOTIFY:
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
        //btc_gattc_unreg_for_notify(arg);
        break;
    case BTC_GATTC_ACT_CACHE_REFRESH:
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
        //BTA_GATTC_Refresh(arg->cache_refresh.remote_bda, true);
        break;
    case BTC_GATTC_ACT_CACHE_ASSOC:
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
        //BTA_GATTC_CacheAssoc(arg->cache_assoc.gattc_if,
        //                        arg->cache_assoc.src_addr,
        //                        arg->cache_assoc.assoc_addr,
        //                        arg->cache_assoc.is_assoc);
        break;
    case BTC_GATTC_ATC_CACHE_GET_ADDR_LIST:
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
        //BTA_GATTC_CacheGetAddrList(arg->get_addr_list.gattc_if);
        break;
    case BTC_GATTC_ACT_CACHE_CLEAN:
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
        //BTA_GATTC_Clean(arg->cache_clean.remote_bda);
        break;
    default:
        BTC_TRACE_ERROR("%s: Unhandled event (%d)!\n", __FUNCTION__, msg->act);
        break;
    }

    btc_gattc_arg_deep_free(msg);

}

static inline void btc_gattc_cb_to_app(ssv_gattc_cb_event_t event, ssv_gatt_if_t gattc_if, ssv_ble_gattc_cb_param_t *param)
{
    ssv_gattc_cb_t btc_gattc_cb = (ssv_gattc_cb_t )btc_profile_cb_get(BTC_PID_GATTC);
    if (btc_gattc_cb) {
	    btc_gattc_cb(event, gattc_if, param);
    }
}

void btc_gattc_cb_handler(btc_msg_t *msg)
{
#if 1
    tBTA_GATTC *arg = (tBTA_GATTC *)(msg->arg);
    ssv_gatt_if_t gattc_if = 0;
    ssv_ble_gattc_cb_param_t param;

    memset(&param, 0, sizeof(ssv_ble_gattc_cb_param_t));

    switch (msg->act) {
    case BTA_GATTC_REG_EVT: {
        tBTA_GATTC_REG *reg_oper = &arg->reg_oper;

        gattc_if = reg_oper->client_if;
        param.reg.status = reg_oper->status;
        param.reg.app_id = reg_oper->app_uuid.uu.uuid16;
        btc_gattc_cb_to_app(SSV_GATTC_REG_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_DEREG_EVT: {
        tBTA_GATTC_REG *reg_oper = &arg->reg_oper;

        gattc_if = reg_oper->client_if;
        btc_gattc_cb_to_app(SSV_GATTC_UNREG_EVT, gattc_if, NULL);
        break;
    }
    case BTA_GATTC_READ_CHAR_EVT: {
        set_read_value(&gattc_if, &param, &arg->read);
        btc_gattc_cb_to_app(SSV_GATTC_READ_CHAR_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_WRITE_CHAR_EVT:
    case BTA_GATTC_PREP_WRITE_EVT: {
        tBTA_GATTC_WRITE *write = &arg->write;
        uint32_t ret_evt = (msg->act == BTA_GATTC_WRITE_CHAR_EVT) ?
                           SSV_GATTC_WRITE_CHAR_EVT : SSV_GATTC_PREP_WRITE_EVT;

        gattc_if = BTC_GATT_GET_GATT_IF(write->conn_id);
        param.write.conn_id = BTC_GATT_GET_CONN_ID(write->conn_id);
        param.write.status = write->status;
        param.write.handle = write->handle;
        param.write.offset = write->offset;
        btc_gattc_cb_to_app(ret_evt, gattc_if, &param);
        break;
    }

    case BTA_GATTC_EXEC_EVT: {
        tBTA_GATTC_EXEC_CMPL *exec_cmpl = &arg->exec_cmpl;

        gattc_if = BTC_GATT_GET_GATT_IF(exec_cmpl->conn_id);
        param.exec_cmpl.conn_id = BTC_GATT_GET_CONN_ID(exec_cmpl->conn_id);
        param.exec_cmpl.status = exec_cmpl->status;
        btc_gattc_cb_to_app(SSV_GATTC_EXEC_EVT, gattc_if, &param);
        break;
    }

    case BTA_GATTC_SEARCH_CMPL_EVT: {
        tBTA_GATTC_SEARCH_CMPL *search_cmpl = &arg->search_cmpl;

        gattc_if = BTC_GATT_GET_GATT_IF(search_cmpl->conn_id);
        param.search_cmpl.conn_id = BTC_GATT_GET_CONN_ID(search_cmpl->conn_id);
        param.search_cmpl.status = search_cmpl->status;
        param.search_cmpl.searched_service_source = search_cmpl->searched_service_source;
        btc_gattc_cb_to_app(SSV_GATTC_SEARCH_CMPL_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_SEARCH_RES_EVT: {
        tBTA_GATTC_SRVC_RES *srvc_res = &arg->srvc_res;

        gattc_if = BTC_GATT_GET_GATT_IF(srvc_res->conn_id);
        param.search_res.conn_id = BTC_GATT_GET_CONN_ID(srvc_res->conn_id);
        param.search_res.start_handle = srvc_res->start_handle;
        param.search_res.end_handle = srvc_res->end_handle;
        param.search_res.is_primary = srvc_res->is_primary;
        bta_to_btc_gatt_id(&param.search_res.srvc_id, &srvc_res->service_uuid);
        btc_gattc_cb_to_app(SSV_GATTC_SEARCH_RES_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_READ_DESCR_EVT: {
        set_read_value(&gattc_if, &param, &arg->read);
        btc_gattc_cb_to_app(SSV_GATTC_READ_DESCR_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_READ_MULTIPLE_EVT: {
        set_read_value(&gattc_if, &param, &arg->read);
        btc_gattc_cb_to_app(SSV_GATTC_READ_MULTIPLE_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_WRITE_DESCR_EVT: {
        tBTA_GATTC_WRITE *write = &arg->write;

        gattc_if = BTC_GATT_GET_GATT_IF(write->conn_id);
        param.write.conn_id = BTC_GATT_GET_CONN_ID(write->conn_id);
        param.write.status = write->status;
        param.write.handle = write->handle;
        btc_gattc_cb_to_app(SSV_GATTC_WRITE_DESCR_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_NOTIF_EVT: {
        tBTA_GATTC_NOTIFY *notify = &arg->notify;

        gattc_if = BTC_GATT_GET_GATT_IF(notify->conn_id);
        param.notify.conn_id = BTC_GATT_GET_CONN_ID(notify->conn_id);
        memcpy(param.notify.remote_bda, notify->bda, sizeof(ssv_bd_addr_t));
        param.notify.handle = notify->handle;
        param.notify.is_notify = (notify->is_notify == TRUE) ? true : false;
        param.notify.value_len = (notify->len > SSV_GATT_MAX_ATTR_LEN) ? \
                                 SSV_GATT_MAX_ATTR_LEN : notify->len;
        param.notify.value = notify->value;

        if (notify->is_notify == FALSE) {
            //BTA_GATTC_SendIndConfirm(notify->conn_id, notify->handle);
        }
        printf("btc_gattc_cb_handler BTA_GATTC_NOTIF_EVT gattc_if 0x%x, conn_id 0x%x\n", gattc_if, notify->conn_id);
        btc_gattc_cb_to_app(SSV_GATTC_NOTIFY_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_OPEN_EVT: {
        tBTA_GATTC_OPEN *open = &arg->open;

        gattc_if = open->client_if;
        param.open.status = open->status;
        param.open.conn_id = BTC_GATT_GET_CONN_ID(open->conn_id);
        memcpy(param.open.remote_bda, open->remote_bda, sizeof(ssv_bd_addr_t));
        param.open.mtu = open->mtu;
        btc_gattc_cb_to_app(SSV_GATTC_OPEN_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_CONNECT_EVT: {
        tBTA_GATTC_CONNECT *connect = &arg->connect;

        gattc_if = connect->client_if;
        param.connect.conn_id = BTC_GATT_GET_CONN_ID(connect->conn_id);
        memcpy(param.connect.remote_bda, connect->remote_bda, sizeof(ssv_bd_addr_t));
        param.connect.conn_params.interval = connect->conn_params.interval;
        param.connect.conn_params.latency = connect->conn_params.latency;
        param.connect.conn_params.timeout = connect->conn_params.timeout;
        //printf("call btc_gattc_cb_to_app SSV_GATTC_CONNECT_EVT %d\n", gattc_if);
        btc_gattc_cb_to_app(SSV_GATTC_CONNECT_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_CLOSE_EVT: {
        tBTA_GATTC_CLOSE *close = &arg->close;

        gattc_if = close->client_if;
        param.close.status = close->status;
        param.close.conn_id = BTC_GATT_GET_CONN_ID(close->conn_id);
        memcpy(param.close.remote_bda, close->remote_bda, sizeof(ssv_bd_addr_t));
        param.close.reason = close->reason;
        btc_gattc_cb_to_app(SSV_GATTC_CLOSE_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_DISCONNECT_EVT: {
        tBTA_GATTC_DISCONNECT *disconnect = &arg->disconnect;

        gattc_if = disconnect->client_if;
        param.disconnect.reason = disconnect->reason;
        param.disconnect.conn_id = BTC_GATT_GET_CONN_ID(disconnect->conn_id);
        memcpy(param.disconnect.remote_bda, disconnect->remote_bda, sizeof(ssv_bd_addr_t));
        btc_gattc_cb_to_app(SSV_GATTC_DISCONNECT_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_CFG_MTU_EVT: {
        tBTA_GATTC_CFG_MTU *cfg_mtu = &arg->cfg_mtu;

        gattc_if = BTC_GATT_GET_GATT_IF(cfg_mtu->conn_id);
        param.cfg_mtu.conn_id = BTC_GATT_GET_CONN_ID(cfg_mtu->conn_id);
        param.cfg_mtu.status = cfg_mtu->status;
        param.cfg_mtu.mtu = cfg_mtu->mtu;
        btc_gattc_cb_to_app(SSV_GATTC_CFG_MTU_EVT, gattc_if, &param);
        break;
    }

    case BTA_GATTC_ACL_EVT: {
        /* Currently, this event will never happen */
        break;
    }
    case BTA_GATTC_CANCEL_OPEN_EVT: {
        /* Currently, this event will never happen */
        break;
    }
    case BTA_GATTC_CONGEST_EVT: {
        tBTA_GATTC_CONGEST *congest = &arg->congest;

        gattc_if = BTC_GATT_GET_GATT_IF(congest->conn_id);
        param.congest.conn_id = BTC_GATT_GET_CONN_ID(congest->conn_id);
        param.congest.congested = (congest->congested == TRUE) ? true : false;
        btc_gattc_cb_to_app(SSV_GATTC_CONGEST_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_SRVC_CHG_EVT: {
        tBTA_GATTC_SERVICE_CHANGE *srvc_change = &arg->srvc_chg;
        gattc_if = BTC_GATT_GET_GATT_IF(srvc_change->conn_id);
        memcpy(param.srvc_chg.remote_bda, srvc_change->remote_bda, sizeof(ssv_bd_addr_t));
        btc_gattc_cb_to_app(SSV_GATTC_SRVC_CHG_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_QUEUE_FULL_EVT: {
        tBTA_GATTC_QUEUE_FULL *queue_full = &arg->queue_full;
        gattc_if = BTC_GATT_GET_GATT_IF(queue_full->conn_id);
        param.queue_full.conn_id = BTC_GATT_GET_CONN_ID(queue_full->conn_id);
        param.queue_full.status = arg->status;
        param.queue_full.is_full = queue_full->is_full;
        btc_gattc_cb_to_app(SSV_GATTC_QUEUE_FULL_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_ASSOC_EVT: {
        gattc_if = arg->set_assoc.client_if;
        param.set_assoc_cmp.status = arg->set_assoc.status;
        btc_gattc_cb_to_app(SSV_GATTC_SET_ASSOC_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_GET_ADDR_LIST_EVT: {
        gattc_if = arg->get_addr_list.client_if;
        param.get_addr_list.status = arg->get_addr_list.status;
        param.get_addr_list.num_addr = arg->get_addr_list.num_addr;
        param.get_addr_list.addr_list = arg->get_addr_list.bda_list;
        btc_gattc_cb_to_app(SSV_GATTC_GET_ADDR_LIST_EVT, gattc_if, &param);
        break;
    }
    case BTA_GATTC_DIS_SRVC_CMPL_EVT:
        gattc_if = BTC_GATT_GET_GATT_IF(arg->dis_cmpl.conn_id);
        param.dis_srvc_cmpl.status = arg->dis_cmpl.status;
        param.dis_srvc_cmpl.conn_id = BTC_GATT_GET_CONN_ID(arg->dis_cmpl.conn_id);
        btc_gattc_cb_to_app(SSV_GATTC_DIS_SRVC_CMPL_EVT, gattc_if, &param);
        break;
    default:
        BTC_TRACE_DEBUG("%s: Unhandled event (%d)!", __FUNCTION__, msg->act);
        break;
    }

    // free the deep-copied data
    btc_gattc_free_req_data(msg);
#endif
}

ssv_gatt_status_t btc_ble_gattc_get_service(uint16_t conn_id, ssv_bt_uuid_t *svc_uuid,
    ssv_gattc_service_elem_t *result,
    uint16_t *count, uint16_t offset)
{
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);

    return SSV_GATT_OK;
}

ssv_gatt_status_t btc_ble_gattc_get_all_char(uint16_t conn_id,
    uint16_t start_handle,
    uint16_t end_handle,
    ssv_gattc_char_elem_t *result,
    uint16_t *count, uint16_t offset)
{
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    return SSV_GATT_OK;
}

ssv_gatt_status_t btc_ble_gattc_get_all_descr(uint16_t conn_id,
    uint16_t char_handle,
    ssv_gattc_descr_elem_t *result,
    uint16_t *count, uint16_t offset)
{
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    return SSV_GATT_OK;
}

ssv_gatt_status_t btc_ble_gattc_get_char_by_uuid(uint16_t conn_id,
    uint16_t start_handle,
    uint16_t end_handle,
    ssv_bt_uuid_t char_uuid,
    ssv_gattc_char_elem_t *result,
    uint16_t *count)
{
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    return SSV_GATT_OK;
}

ssv_gatt_status_t btc_ble_gattc_get_descr_by_uuid(uint16_t conn_id,
    uint16_t start_handle,
    uint16_t end_handle,
    ssv_bt_uuid_t char_uuid,
    ssv_bt_uuid_t descr_uuid,
    ssv_gattc_descr_elem_t *result,
    uint16_t *count)
{
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    return SSV_GATT_OK;
}

ssv_gatt_status_t btc_ble_gattc_get_descr_by_char_handle(uint16_t conn_id,
    uint16_t char_handle,
    ssv_bt_uuid_t descr_uuid,
    ssv_gattc_descr_elem_t *result,
    uint16_t *count)
{
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    return SSV_GATT_OK;
}

ssv_gatt_status_t btc_ble_gattc_get_include_service(uint16_t conn_id,
    uint16_t start_handle,
    uint16_t end_handle,
    ssv_bt_uuid_t *incl_uuid,
    ssv_gattc_incl_svc_elem_t *result,
    uint16_t *count)
{
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    return SSV_GATT_OK;
}

ssv_gatt_status_t btc_ble_gattc_get_attr_count(uint16_t conn_id,
    ssv_gatt_db_attr_type_t type,
    uint16_t start_handle,
    uint16_t end_handle,
    uint16_t char_handle,
    uint16_t *count)
{
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    return SSV_GATT_OK;
}

ssv_gatt_status_t btc_ble_gattc_get_db(uint16_t conn_id, uint16_t start_handle, uint16_t end_handle,
    ssv_gattc_db_elem_t *db, uint16_t *count)
{
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    return SSV_GATT_OK;
}



















