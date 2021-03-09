#include <string.h>

#include "bta/bta_gatt_api.h"

//#include "btc/btc_task.h"
//#include "btc/btc_manage.h"
#include "btc/btc_gatts.h"
#include "btc_gatt_util.h"
//#include "osi/future.h"
//#include "osi/allocator.h"
//#include "btc/btc_main.h"
//#include "ssv_gatts_api.h"
#include "osi/allocator.h"
#include "bt_types.h"
#include "mesh_trace.h"
#include "btc/btc_manage.h"
#include <host/ble_gatt.h>
#include <host/ble_hs_mbuf.h>
#include "host/ble_gap.h"
#include "btc/btc_gatt_common.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"

void btc_gatts_arg_deep_free(btc_msg_t *msg)
{
    btc_ble_gatts_args_t *arg = (btc_ble_gatts_args_t *)msg->arg;

    switch (msg->act) {
    case BTC_GATTS_ACT_SEND_INDICATE: {
        if (arg->send_ind.value) {
            osi_free(arg->send_ind.value);
        }
        break;
    }
    case BTC_GATTS_ACT_SEND_RESPONSE: {
        if (arg->send_rsp.rsp) {
            osi_free(arg->send_rsp.rsp);
        }
        break;
    }
    case BTC_GATTS_ACT_ADD_CHAR:{
        if (arg->add_char.char_val.attr_value != NULL) {
            osi_free(arg->add_char.char_val.attr_value);
        }
        break;
    }
    case BTC_GATTS_ACT_ADD_CHAR_DESCR:{
        if (arg->add_descr.descr_val.attr_value != NULL){
            osi_free(arg->add_descr.descr_val.attr_value);
        }
        break;
    }
    case BTC_GATTS_ACT_CREATE_ATTR_TAB:{
        if (arg->create_attr_tab.gatts_attr_db != NULL){
            osi_free(arg->create_attr_tab.gatts_attr_db);
        }
        break;
    }
    case BTC_GATTS_ACT_SET_ATTR_VALUE:{
        if (arg->set_attr_val.value != NULL){
            osi_free(arg->set_attr_val.value);
        }
    }
        break;

    default:
        BTC_TRACE_DEBUG("%s Unhandled deep free %d\n", __func__, msg->act);
        break;
    }

}

/*static void btc_gatts_inter_cb(tBTA_GATTS_EVT event, tBTA_GATTS *p_data)
{
    bt_status_t status;
    btc_msg_t msg;

    msg.sig = BTC_SIG_API_CB;
    msg.pid = BTC_PID_GATTS;
    msg.act = event;


}*/

/* post message to btc_gatts_cb_handler*/
static bt_status_t btc_ble_gatts_callback(uint8_t act)
{
    btc_msg_t msg = {0};
    bt_status_t ret;

    msg.sig = BTC_SIG_API_CB;
    msg.pid = BTC_PID_GATTS;
    msg.act = act;

    //ret = btc_transfer_context(&msg, param, sizeof(esp_ble_mesh_prov_cb_param_t), NULL);
    ret = btc_transfer_context(&msg, NULL, 0, NULL);
    if (ret != BT_STATUS_SUCCESS) {
        LOG_ERROR("%s, btc_transfer_context failed", __func__);
    }
    return ret;

}

static osi_sem_t svr_chr_access_sem;
uint16_t g_app_id = 0;

void SSV_GATTS_AppRegister(tBT_UUID *uuid)
{
    tBTA_GATTS reg;
    int ret;
    reg.reg_oper.server_if = SERVER_IF_ID;
    reg.reg_oper.status = SSV_GATT_OK;
    reg.reg_oper.uuid.uu.uuid16 = uuid->uu.uuid16;/* APP ID */
    g_app_id = uuid->uu.uuid16;

    if (!osi_sem_valid(&svr_chr_access_sem)) {
        printf("init svr_chr_access_sem\n");
        ret = osi_sem_new(&svr_chr_access_sem, 1, 0);
        if (ret) {
            printf("osi_sem_new svr_chr_access_sem error\n");
        }
    }
    reg.reg_oper.uuid.len = uuid->len;
    btc_gatt_com_to_cb_handler((void*)&reg, sizeof(reg), BTA_GATTS_REG_EVT, BTC_PID_GATTS);
}

void SSV_GATTS_AppUnRegister(ssv_gatt_if_t gatts_if)
{
    tBTA_GATTS unreg;

    g_app_id = 0;

    unreg.reg_oper.server_if = SERVER_IF_ID;
    btc_gatt_com_to_cb_handler((void*)&unreg, sizeof(unreg), BTA_GATTS_DEREG_EVT, BTC_PID_GATTS);
}

void SSV_GATTS_CreateService(tBTA_GATTS_IF server_if, const tBT_UUID * p_service_uuid, UINT8 inst,
    UINT16 num_handle, BOOLEAN is_primary)
{
    tBTA_GATTS    cb_data;

    cb_data.create.status = BTA_GATT_OK;//BTA_GATT_ERROR;
    cb_data.create.service_id = SERVER_IF_ID;//service_id;
    cb_data.create.is_primary = is_primary;
    cb_data.create.server_if = server_if;

    //tBTA_GATT_ID        service_uuid;
    //todo
    memcpy(&cb_data.create.uuid, p_service_uuid, sizeof(tBT_UUID));
    cb_data.create.svc_instance = inst;

    btc_gatt_com_to_cb_handler((void*)&cb_data, sizeof(cb_data), BTA_GATTS_CREATE_EVT, BTC_PID_GATTS);
}

void SSV_GATTS_HandleValueIndication (UINT16 conn_id, UINT16 attr_id, UINT16 data_len,
                                      UINT8 *p_data, BOOLEAN need_confirm)
{
    struct os_mbuf *om = NULL;
    int rc = 0;

    if (!data_len) {
        printf("ble_gatts data_len = 0, error\n", data_len);
        return;
    }
    printf("%s data_len %d\n", __FUNCTION__, data_len);
    om = ble_hs_mbuf_from_flat(p_data, data_len);

    if (om) {
        printf("ble_gatts tx conn handle %d, connid %d\n",
            conn_id, BTC_GATT_GET_CONN_ID(conn_id));
        rc = ble_gattc_indicate_custom(BTC_GATT_GET_CONN_ID(conn_id),
            attr_id,
            om);

        if (rc)
            printf("ble_gatts indicate_custom error\n");
    } else
        printf("%s om is NULL\n", __FUNCTION__);
}

#define BTC_GATTS_CHR_ACCESS_TIMEOUT 3000
#define BTC_GATTS_CHR_ACCESS_BUF_SIZE 256

ssv_gatts_attr_db_t *g_p_assign_attr_db = NULL;
uint16_t g_db_max_num = 0;
uint16_t g_db_start_handle = 0;

uint32_t g_transfer_id = 0;
uint16_t gatt_svr_val_handle = 0;
uint8_t gatt_svr_buf[SSV_GATT_MAX_ATTR_LEN];
int gatt_svr_buf_len = -1;
static int ssv_gatt_svr_chr_access_cb(uint16_t conn_handle, uint16_t attr_handle,
    struct ble_gatt_access_ctxt *ctxt,
    void *arg)
{
    const ble_uuid_t *uuid = NULL;
    int rc = 0;
    tBTA_GATTS    cb_data;
    struct ble_gap_conn_desc desc;
    tGATTS_DATA *pgatt_data = NULL;
    //ms_hal_ble_attrib_callback_t *att_cb = NULL;

    uuid = ctxt->chr->uuid;
    printf("\33[32m%s():start\33[0m\r\n",__FUNCTION__);
    printf("conn_handle=%d,attr_handle=%d, UUID=0x%x\n", conn_handle, attr_handle, (int) BLE_UUID16(uuid)->value);
    if(NULL!=arg)
    {
        printf("arg=> %s\n",arg);
    }
    ble_gap_conn_find(conn_handle, &desc);

    //if (ble_uuid_cmp(uuid, &gatt_svr_chr_sec_test_static_uuid.u) == 0)
    switch (ctxt->op) {
        case BLE_GATT_ACCESS_OP_READ_CHR:
        case BLE_GATT_ACCESS_OP_READ_DSC:
            if (ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR)
                printf("read chr\n");
            else if (ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR)
                printf("read dsc\n");


            memcpy(cb_data.req_data.remote_bda, desc.peer_id_addr.val, SSV_BD_ADDR_LEN);
            cb_data.req_data.conn_id = BTC_GATT_CREATE_CONN_ID(SERVER_IF_ID, conn_handle);
            cb_data.req_data.handle = attr_handle;
            g_transfer_id ++;
            cb_data.req_data.trans_id = g_transfer_id;

            pgatt_data = osi_malloc(sizeof(tGATTS_DATA));

            pgatt_data->read_req.handle = attr_handle;
            pgatt_data->read_req.is_long = 0;
            pgatt_data->read_req.need_rsp = 1;
            pgatt_data->read_req.offset = 0;
            cb_data.req_data.p_data = pgatt_data;

            if (g_p_assign_attr_db &&  (attr_handle >= g_db_start_handle) && g_db_max_num) {//check is auto response
                uint16_t db_num = attr_handle - g_db_start_handle;
                if (db_num >= g_db_max_num) {
                    printf("db_num(%d) >= g_db_max_num(%d)\n", db_num, g_db_max_num);
                    return 0;
                }

                if (g_p_assign_attr_db[db_num].attr_control.auto_rsp == SSV_GATT_AUTO_RSP) {
                    printf("db_num %d AUTO_RSP\n", db_num);
                    rc = os_mbuf_append(ctxt->om, g_p_assign_attr_db[db_num].att_desc.value, g_p_assign_attr_db[db_num].att_desc.length);
                    if (rc)
                        printf("read chr os_mbuf_append fail %d", rc);

                    return 0;
                }
            }

            btc_gatt_com_to_cb_handler((void*)&cb_data, sizeof(cb_data), BTA_GATTS_READ_EVT, BTC_PID_GATTS);
            osi_sem_take(&svr_chr_access_sem, BTC_GATTS_CHR_ACCESS_TIMEOUT);
            if (gatt_svr_buf_len >= 0){
                rc = os_mbuf_append(ctxt->om, gatt_svr_buf, gatt_svr_buf_len);
                if (rc)
                    printf("read chr os_mbuf_append fail %d", rc);
            }

            gatt_svr_buf_len = -1;
            break;
        case BLE_GATT_ACCESS_OP_WRITE_CHR:
        case BLE_GATT_ACCESS_OP_WRITE_DSC:
            if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR)
                printf("write chr\n");
            else if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR)
                printf("write dsc\n");

            cb_data.req_data.conn_id = BTC_GATT_CREATE_CONN_ID(SERVER_IF_ID, conn_handle);
            cb_data.req_data.handle = attr_handle;
            g_transfer_id ++;
            cb_data.req_data.trans_id = g_transfer_id;

            pgatt_data = osi_malloc(sizeof(tGATTS_DATA));

            rc = ble_hs_mbuf_to_flat(ctxt->om, pgatt_data->write_req.value, sizeof(pgatt_data->write_req.value), &pgatt_data->write_req.len);
            printf("write len %d\n", pgatt_data->write_req.len);

            pgatt_data->write_req.handle = attr_handle;
            pgatt_data->write_req.is_prep = 0;
            pgatt_data->write_req.need_rsp = 0;
            pgatt_data->write_req.offset = 0;
            cb_data.req_data.p_data = pgatt_data;

            btc_gatt_com_to_cb_handler((void*)&cb_data, sizeof(cb_data), BTA_GATTS_WRITE_EVT, BTC_PID_GATTS);
            //if (att_cb)
            //    att_cb->write_cb(buf_chr, buf_len);

            break;

        default:
            return 0;
    }

    printf("\33[32m%s():end\33[0m\r\n",__FUNCTION__);
    return 0;
}

#if 0
static struct ble_gatt_svc_def ssv_svc_defs [] = {
    {
    .type = BLE_GATT_SVC_TYPE_PRIMARY,
    .uuid = BLE_UUID16_DECLARE(0xFF80),
    .includes = NULL,
#if 1
    .characteristics = (struct ble_gatt_chr_def[])
        { {
                .uuid = BLE_UUID16_DECLARE(0xFF81),
                .access_cb = ssv_gatt_svr_chr_access_cb,
                .flags = (BLE_GATT_CHR_F_WRITE),
                .val_handle = NULL,
                #if 1
                .descriptors = (struct ble_gatt_dsc_def[])
                { {
                        .uuid = BLE_UUID16_DECLARE(0x2901),
                        .att_flags = (BLE_GATT_CHR_F_READ|BLE_GATT_CHR_F_WRITE),
                        .access_cb = ssv_gatt_svr_chr_access_cb,
                        .arg = (void*) "test write",
                    },
                    {
                        0 // No more descriptors
                    },
                }
                #endif
            },{
                .uuid = BLE_UUID16_DECLARE(0xFF82),
                .access_cb = ssv_gatt_svr_chr_access_cb,
                .flags = BLE_GATT_CHR_F_INDICATE,
                .val_handle = &gatt_svr_val_handle,
                #if 1
                .descriptors = (struct ble_gatt_dsc_def[])
                { {
                        .uuid = BLE_UUID16_DECLARE(0x2901),
                        .att_flags = (BLE_GATT_CHR_F_READ|BLE_GATT_CHR_F_WRITE),
                        .access_cb = ssv_gatt_svr_chr_access_cb,
                        .arg = NULL,//(void*) "test write",
                    },
                    {
                        0 // No more descriptors
                    },
                }
                #endif
            },
            {
                0, /* No more characteristics in this service. */
            }
        },
#endif
    },
    {
        0, /* No more services. */
    },
};
#endif

static inline void btc_gatts_cb_to_app(ssv_gatts_cb_event_t event, ssv_gatt_if_t gatts_if, ssv_ble_gatts_cb_param_t *param)
{
    ssv_gatts_cb_t btc_gatts_cb = (ssv_gatts_cb_t)btc_profile_cb_get(BTC_PID_GATTS);
    if (btc_gatts_cb) {
        btc_gatts_cb(event, gatts_if, param);
    }
}

uint16_t g_gatts_chr_count = 0;
uint16_t g_gatts_dsc_count = 0;

static ble_uuid_t *_declare_uuid(uint8_t uuid_type, uint8_t *_uuid)
{
    ble_uuid_t *uuid=NULL;
    switch(uuid_type)
    {
        case BLE_UUID_TYPE_16:
            uuid=OS_MemZalloc(sizeof(ble_uuid16_t));
            if(NULL!=uuid)
            {
                ((ble_uuid16_t *)(uuid))->u.type = BLE_UUID_TYPE_16;
                ((ble_uuid16_t *)(uuid))->value = (_uuid[0]|_uuid[1]<<8);
                printf("\33[31m%s(): 16bit %04x  \33[0m\r\n", __FUNCTION__, ((ble_uuid16_t *)(uuid))->value);
            }
            break;
        case BLE_UUID_TYPE_32:
            uuid=OS_MemZalloc(sizeof(ble_uuid32_t));
            if(NULL!=uuid)
            {
                ((ble_uuid32_t *)(uuid))->u.type = BLE_UUID_TYPE_32;
                ((ble_uuid32_t *)(uuid))->value = (_uuid[0]|_uuid[1]<<8|_uuid[2]<<16|_uuid[3]<<24);
                printf("\33[31m%s(): 16bit %08x  \33[0m\r\n", __FUNCTION__, ((ble_uuid32_t *)(uuid))->value);
            }
            break;

        case BLE_UUID_TYPE_128:
            uuid=OS_MemZalloc(sizeof(ble_uuid128_t));
            if(NULL!=uuid)
            {
                ((ble_uuid128_t *)(uuid))->u.type = BLE_UUID_TYPE_128;
                for(int i = 0; i < 16;i++) {
                    ((ble_uuid128_t *)(uuid))->value[i] = _uuid[i];
                }
            }
            break;
        default:
            printf("\33[31m%s(): !!! Inavlid case\33[0m\r\n",__FUNCTION__);
            break;
    }

    return uuid;

}
#define FIND_SERVICE 1
#define FIND_CHAR 2
#define FIND_DESC 3
static uint8_t btc_gatts_find_chr_des_count(ssv_gatts_attr_db_t *attr_db,
    uint8_t now_nb_attr, uint8_t max_nb_attr, uint8_t type)
{
    uint8_t count = 0;
    const uint16_t primary_service         = SSV_GATT_UUID_PRI_SERVICE;
    const uint16_t secondary_service       = SSV_GATT_UUID_SEC_SERVICE;
    const uint16_t include_service         = SSV_GATT_UUID_INCLUDE_SERVICE;
    const uint16_t character_declaration   = SSV_GATT_UUID_CHAR_DECLARE;
    const uint16_t character_user_desc = SSV_GATT_UUID_CHAR_DESCRIPTION;
    const uint16_t character_client_config = SSV_GATT_UUID_CHAR_CLIENT_CONFIG;

    ble_uuid_any_t uuid_primary_service;//= BLE_UUID16_DECLARE(SSV_GATT_UUID_PRI_SERVICE);
    ble_uuid_any_t uuid_secondary_service;//    = BLE_UUID16_DECLARE(SSV_GATT_UUID_SEC_SERVICE);
    ble_uuid_any_t uuid_include_service;//     = BLE_UUID16_DECLARE(SSV_GATT_UUID_INCLUDE_SERVICE);
    ble_uuid_any_t uuid_character_declaration;// = BLE_UUID16_DECLARE(SSV_GATT_UUID_CHAR_DECLARE);
    ble_uuid_any_t uuid_character_user_desc;// = BLE_UUID16_DECLARE(SSV_GATT_UUID_CHAR_DESCRIPTION);
    ble_uuid_any_t uuid_character_client_config;//= BLE_UUID16_DECLARE(SSV_GATT_UUID_CHAR_CLIENT_CONFIG);

    ble_uuid_any_t db_uuid;
    ble_uuid16_t uuid16;
    ble_uuid32_t uuid32;
    ble_uuid128_t uuid128;
    char uuid_buf1[128] = {0};
    char uuid_buf2[128] = {0};

    ble_uuid_init_from_buf(&uuid_primary_service, &primary_service, SSV_UUID_LEN_16);
    ble_uuid_init_from_buf(&uuid_secondary_service, &secondary_service, SSV_UUID_LEN_16);
    ble_uuid_init_from_buf(&uuid_include_service, &include_service, SSV_UUID_LEN_16);
    ble_uuid_init_from_buf(&uuid_character_declaration, &character_declaration, SSV_UUID_LEN_16);
    ble_uuid_init_from_buf(&uuid_character_user_desc, &character_user_desc, SSV_UUID_LEN_16);
    ble_uuid_init_from_buf(&uuid_character_client_config, &character_client_config, SSV_UUID_LEN_16);

    for (int i = now_nb_attr + 1; i < max_nb_attr; i++) {
        ble_uuid_init_from_buf(&db_uuid, attr_db[i].att_desc.uuid_p, attr_db[i].att_desc.uuid_length);

        if (type == FIND_SERVICE) {
            if (ble_uuid_cmp(&db_uuid.u, &uuid_primary_service.u) == 0) {
                count ++;
            }
        } else  if (type == FIND_CHAR) {
            if (ble_uuid_cmp(&db_uuid.u, &uuid_character_declaration.u) == 0) {
                count ++;
            } else  if (ble_uuid_cmp(&db_uuid.u, &uuid_primary_service.u) == 0 ||
                ble_uuid_cmp(&db_uuid.u, &uuid_secondary_service.u) == 0) {
                break;
            }
        } else  if (type == FIND_DESC) {
            if (ble_uuid_cmp(&db_uuid.u, &uuid_character_user_desc.u) == 0){
                count++;
            } else  if (ble_uuid_cmp(&db_uuid.u, &uuid_primary_service.u) == 0 ||
                ble_uuid_cmp(&db_uuid.u, &uuid_secondary_service.u) == 0 ||
                ble_uuid_cmp(&db_uuid.u, &uuid_character_declaration.u) == 0) {
                break;
            }
        }


    }

    return count;
}

static int btc_gatts_gen_svc_def_by_attrdb(ssv_gatts_attr_db_t *attr_db, uint8_t max_nb_attr,
    struct ble_gatt_svc_def *svc_def)
{
    uint8_t count = 0;
    int ret = 0;
    int8_t service_ind = -1;
    const uint16_t primary_service         = SSV_GATT_UUID_PRI_SERVICE;
    const uint16_t secondary_service       = SSV_GATT_UUID_SEC_SERVICE;
    const uint16_t include_service         = SSV_GATT_UUID_INCLUDE_SERVICE;
    const uint16_t character_declaration   = SSV_GATT_UUID_CHAR_DECLARE;
    const uint16_t character_user_desc = SSV_GATT_UUID_CHAR_DESCRIPTION;
    const uint16_t character_client_config = SSV_GATT_UUID_CHAR_CLIENT_CONFIG;

    ble_uuid_any_t uuid_primary_service;//= BLE_UUID16_DECLARE(SSV_GATT_UUID_PRI_SERVICE);
    ble_uuid_any_t uuid_secondary_service;//    = BLE_UUID16_DECLARE(SSV_GATT_UUID_SEC_SERVICE);
    ble_uuid_any_t uuid_include_service;//     = BLE_UUID16_DECLARE(SSV_GATT_UUID_INCLUDE_SERVICE);
    ble_uuid_any_t uuid_character_declaration;// = BLE_UUID16_DECLARE(SSV_GATT_UUID_CHAR_DECLARE);
    ble_uuid_any_t uuid_character_user_desc;// = BLE_UUID16_DECLARE(SSV_GATT_UUID_CHAR_DESCRIPTION);
    ble_uuid_any_t uuid_character_client_config;//= BLE_UUID16_DECLARE(SSV_GATT_UUID_CHAR_CLIENT_CONFIG);

    ble_uuid_any_t db_uuid;
    ble_uuid16_t uuid16;
    ble_uuid32_t uuid32;
    ble_uuid128_t uuid128;
    char uuid_buf1[32] = {0};
    char uuid_buf2[32] = {0};

    uint8_t chr_idx = 0, dsc_idx = 0;
    struct ble_gatt_chr_def *characteristics = NULL;
    struct ble_gatt_dsc_def *dsc = NULL;

    ble_uuid_init_from_buf(&uuid_primary_service, &primary_service, SSV_UUID_LEN_16);
    ble_uuid_init_from_buf(&uuid_secondary_service, &secondary_service, SSV_UUID_LEN_16);
    ble_uuid_init_from_buf(&uuid_include_service, &include_service, SSV_UUID_LEN_16);
    ble_uuid_init_from_buf(&uuid_character_declaration, &character_declaration, SSV_UUID_LEN_16);
    ble_uuid_init_from_buf(&uuid_character_user_desc, &character_user_desc, SSV_UUID_LEN_16);
    ble_uuid_init_from_buf(&uuid_character_client_config, &character_client_config, SSV_UUID_LEN_16);




    for (int i = 0; i < max_nb_attr; i++) {
        ble_uuid_init_from_buf(&db_uuid, attr_db[i].att_desc.uuid_p, attr_db[i].att_desc.uuid_length);
        /*service*/
        if (ble_uuid_cmp(&db_uuid.u, &uuid_primary_service.u) == 0) {
            service_ind ++;
            svc_def[service_ind].type = BLE_GATT_SVC_TYPE_PRIMARY;
            if (attr_db[i].att_desc.length == SSV_UUID_LEN_16) {
                svc_def[service_ind].uuid = _declare_uuid(BLE_UUID_TYPE_16, attr_db[i].att_desc.value);
            }
            else if (attr_db[i].att_desc.length == SSV_UUID_LEN_32)
                svc_def[service_ind].uuid = _declare_uuid(BLE_UUID_TYPE_32, attr_db[i].att_desc.value);
            else if (attr_db[i].att_desc.length == SSV_UUID_LEN_128) {
                svc_def[service_ind].uuid = _declare_uuid(BLE_UUID_TYPE_128, attr_db[i].att_desc.value);
            }

            //printf("%s  assign primary_service uuid  %02x%02x\n", __FUNCTION__, attr_db[i].att_desc.value[1], attr_db[i].att_desc.value[0]);
            //printf("primary_service uuid %d  uuid %s\n",
            //    service_ind, ble_uuid_to_str(svc_def[service_ind].uuid, uuid_buf1));
            svc_def[service_ind].includes = NULL;
            count = btc_gatts_find_chr_des_count(attr_db, i, max_nb_attr, FIND_CHAR);
            characteristics = OS_MemZalloc(sizeof(struct ble_gatt_chr_def)*(count+1));/*add one empty*/

            if (characteristics == NULL) {
                printf("characteristics allocate fail\n");
                return ret;
            }

            svc_def[service_ind].characteristics = characteristics;
            chr_idx = 0;
            continue;
        } else if (ble_uuid_cmp(&db_uuid.u, &uuid_secondary_service.u) == 0) {
            printf("%s  add secondary_service %d\n", __FUNCTION__, i);
            service_ind ++;
            svc_def[service_ind].type = BLE_GATT_SVC_TYPE_SECONDARY;
            //svc_def[service_ind].uuid = BLE_UUID16_DECLARE((uint16_t)*attr_db[i].att_desc.value);
            svc_def[service_ind].uuid = _declare_uuid(BLE_UUID_TYPE_16, attr_db[i].att_desc.value);
            svc_def[service_ind].includes = NULL;

            characteristics = OS_MemZalloc(sizeof(struct ble_gatt_chr_def) * (count + 1));/*add one empty*/
            if (characteristics == NULL) {
                printf("characteristics allocate fail\n");
                return ret;
            }

            svc_def[service_ind].characteristics = characteristics;
            chr_idx = 0;
            continue;
        } else if (ble_uuid_cmp(&db_uuid.u, &uuid_include_service.u) == 0) {
            characteristics = OS_MemZalloc(sizeof(struct ble_gatt_chr_def) * (count + 1));/*add one empty*/
            if (characteristics == NULL) {
                printf("characteristics allocate fail\n");
                return ret;
            }

            svc_def[service_ind].characteristics = characteristics;
            chr_idx = 0;
            printf("%s  add  include_service %d\n", __FUNCTION__, i);
            service_ind ++;
            printf("%s service_ind %d,include_service todo\n", __FUNCTION__, service_ind);
            continue;
            //svc_def[service_ind].includes
        }

        /*characteristics*/
        if (ble_uuid_cmp(&db_uuid.u, &uuid_character_declaration.u) == 0) {

            count = btc_gatts_find_chr_des_count(attr_db, i, max_nb_attr, FIND_DESC);
            dsc = OS_MemZalloc(sizeof(struct ble_gatt_dsc_def) * (count + 1));/*add one empty*/
            dsc_idx = 0;
            if (dsc == NULL) {
                printf("dsc allocate fail\n");
                return ret;
            }
            characteristics[chr_idx].descriptors = dsc;

            if (attr_db[i + 1].att_desc.uuid_length == SSV_UUID_LEN_16) {
                characteristics[chr_idx].uuid = _declare_uuid(BLE_UUID_TYPE_16, attr_db[i + 1].att_desc.uuid_p);
                //printf("%s  16bit  chr %d value  %s\n", __FUNCTION__, g_gatts_chr_count, ble_uuid_to_str(characteristics[chr_idx].uuid, uuid_buf1));
            } else if (attr_db[i + 1].att_desc.uuid_length == SSV_UUID_LEN_32) {
                characteristics[chr_idx].uuid = _declare_uuid(BLE_UUID_TYPE_32, attr_db[i + 1].att_desc.uuid_p);
            } if (attr_db[i + 1].att_desc.uuid_length == SSV_UUID_LEN_128) {
                characteristics[chr_idx].uuid = _declare_uuid(BLE_UUID_TYPE_128, attr_db[i + 1].att_desc.uuid_p);
            }

            characteristics[chr_idx].access_cb = ssv_gatt_svr_chr_access_cb;
            characteristics[chr_idx].flags = (*attr_db[i].att_desc.value);//attr_db[i].att_desc.perm;
            characteristics[chr_idx].val_handle = NULL;
            g_gatts_chr_count ++;

            chr_idx ++;
            i += 1;/*get characteristics value already*/
            continue;
        }

        /*descriptors ccc*/
        if (ble_uuid_cmp(&db_uuid.u, &uuid_character_client_config.u) == 0) {
            continue;
        }

        /*descriptors*/
        if (ble_uuid_cmp(&db_uuid.u, &uuid_character_user_desc.u) == 0) {
            uint8_t modify_chr_idx = chr_idx - 1;
            //dsc
            //printf("%s  modify desc chr_idx %d, dsc_idx %d\n", __FUNCTION__, modify_chr_idx, dsc_idx);
            //printf("%s %d %d descriptors  %s %s\n", __FUNCTION__,
            //   i, dsc_idx, ble_uuid_to_str(&db_uuid.u, uuid_buf1), ble_uuid_to_str(&uuid_character_user_desc.u, uuid_buf2));

            characteristics[modify_chr_idx].descriptors[dsc_idx].uuid = _declare_uuid(BLE_UUID_TYPE_16, (uint8_t*)&character_user_desc);
            characteristics[modify_chr_idx].descriptors[dsc_idx].att_flags = attr_db[i].att_desc.perm;
            characteristics[modify_chr_idx].descriptors[dsc_idx].access_cb = ssv_gatt_svr_chr_access_cb;
            if (dsc_idx)
                characteristics[modify_chr_idx].descriptors[dsc_idx].arg = NULL;
            else
                characteristics[modify_chr_idx].descriptors[dsc_idx].arg = attr_db[i].att_desc.value;
            g_gatts_dsc_count ++;

            dsc_idx ++;
            continue;
        }
            //svc_def[service_ind]

    }

    return ret;
}

struct ble_gatt_svc_def *g_svc_defs = NULL;

static void btc_gatts_act_create_attr_tab(ssv_gatts_attr_db_t *gatts_attr_db,
    ssv_gatt_if_t gatts_if, uint8_t max_nb_attr, uint8_t srvc_inst_id)
{
    int ret = 0;
    ssv_ble_gatts_cb_param_t param;
    uint16_t service_start_handle = 0;
    uint8_t svc_count = 0;
    uint16_t *return_start_handles = NULL;

    printf("%s max_nb_attr %d\n", __FUNCTION__, max_nb_attr);

    for (int i = 0; i < max_nb_attr; i++) {
        printf("%s %d uuid  %02x%02x\n", __FUNCTION__, i, gatts_attr_db[i].att_desc.uuid_p[1], gatts_attr_db[i].att_desc.uuid_p[0]);
    }

    svc_count = btc_gatts_find_chr_des_count(gatts_attr_db, 0, max_nb_attr, FIND_SERVICE);

    g_svc_defs = OS_MemZalloc(sizeof(struct ble_gatt_chr_def)*(svc_count + 1));

    if (g_p_assign_attr_db)
        OS_MemFree(g_p_assign_attr_db);

    g_p_assign_attr_db = OS_MemZalloc(sizeof(ssv_gatts_attr_db_t)*max_nb_attr);
    if (g_p_assign_attr_db) {
        memcpy(g_p_assign_attr_db, gatts_attr_db, sizeof(ssv_gatts_attr_db_t)*max_nb_attr);
    } else
        printf("%s OS_MemZalloc g_p_assign_attr_db error\n", __FUNCTION__, ret);

    ret = btc_gatts_gen_svc_def_by_attrdb(gatts_attr_db, max_nb_attr,
        g_svc_defs);

    ble_svc_gap_init();
    ble_svc_gatt_init();

    ret = ble_gatts_count_cfg(g_svc_defs);
    if (ret)
        printf("%s ble_gatts_count_cfg fail ret %d\n", __FUNCTION__, ret);

    ret = ble_gatts_add_svcs(g_svc_defs);
    if (ret)
        printf("%s ble_gatts_add_svcs fail ret %d\n", __FUNCTION__, ret);

    ret = ble_gatts_start();
    if (ret)
        printf("%s ble_gatts_start fail ret %d\n", __FUNCTION__, ret);

    ble_gatts_find_svc(g_svc_defs->uuid, &service_start_handle);
    ble_gatts_show_local();

    if (ret)
        param.add_attr_tab.status = SSV_GATT_ERROR;
    else
        param.add_attr_tab.status = SSV_GATT_OK;

    param.add_attr_tab.num_handle = ble_gatts_get_att_total_count() - service_start_handle + 1;

    return_start_handles = OS_MemAlloc(sizeof(uint16_t) * param.add_attr_tab.num_handle);
    if (!return_start_handles)
        printf("%s ****return_start_handles OS_MemZalloc fail****\n", __FUNCTION__);

    g_db_start_handle = service_start_handle;
    g_db_max_num = max_nb_attr;

    for (int i = 0; i < param.add_attr_tab.num_handle; i ++)
        return_start_handles[i] = service_start_handle + i;

    param.add_attr_tab.handles = return_start_handles;

    btc_gatts_cb_to_app(SSV_GATTS_CREAT_ATTR_TAB_EVT, gatts_if, &param);

    OS_MemFree(return_start_handles);
#if 0
    /*show svc_defs*/
    for (int i = 0; i < SSV_MAX_GATTS_SERVICE_COUNT; i++) {
        if (svc_defs[i].type){
            printf("service %d\n", i);
            printf("type %d, uuid %s\n", svc_defs[i].type, ble_uuid_to_str(svc_defs[i].uuid, uuid_buf1));
            if (svc_defs[i].includes == NULL)
                printf("include is NULL\n");
            else
                printf("include service is used\n");
            /*show characteristics*/
            for (int j = 0; j < SSV_MAX_GATTS_CHR_COUNT; j++) {
                if (svc_defs[i].characteristics[j].flags) {
                    printf("  characteristics %d\n", j);
                    printf("  i %d, j %d uuid %s flag 0x%02x\n", i, j,
                        ble_uuid_to_str(svc_defs[i].characteristics[j].uuid, uuid_buf1), svc_defs[i].characteristics[j].flags);
                    printf("  access_cb %p\n", svc_defs[i].characteristics[j].access_cb);
                    if (svc_defs[i].characteristics[j].arg == NULL)
                        printf("  arg is NULL\n");
                    else
                        printf("  arg is used\n");

                    if (svc_defs[i].characteristics[j].val_handle == NULL)
                        printf("  val_handle is NULL\n");
                    else
                        printf("  val_handle is used\n");

                    printf("  min_key_size %d\n", svc_defs[i].characteristics[j].min_key_size);

                    /*show descriptors*/
                    for (int k = 0; k < SSV_MAX_GATTS_CHR_COUNT; k++) {
                        if (svc_defs[i].characteristics[j].descriptors[k].att_flags) {
                            printf("    descriptors %d\n", k);
                            printf("    uuid %s att_flags 0x%02x\n",
                                ble_uuid_to_str(svc_defs[i].characteristics[j].descriptors[k].uuid, uuid_buf1),
                                svc_defs[i].characteristics[j].descriptors[k].att_flags);
                            printf("    min_key_size 0x%d\n",
                                svc_defs[i].characteristics[j].descriptors[k].min_key_size);

                            if (svc_defs[i].characteristics[j].descriptors[k].access_cb == NULL)
                                printf("    access_cb is NULL\n");
                            else
                                printf("    access_cb is used\n");

                            if (svc_defs[i].characteristics[j].descriptors[k].arg == NULL)
                                printf("    arg is NULL\n");
                            else
                                printf("    arg is used\n");

                        } else
                         break;
                    }
                } else
                    break;

            }

        } else
            break;
    }
#endif

}

/* TODO call btc_gatts_free_svr_def in somewhere*/
void btc_gatts_free_svr_def()
{
    for (int i = 0; ; i++) {
        if (g_svc_defs[i].type){
            printf("service %d\n", i);
            if (g_svc_defs[i].includes == NULL)
                printf("include is NULL\n");
            else
                printf("include service is used\n");
            /*characteristics*/
            for (int j = 0; ; j++) {
                if (g_svc_defs[i].characteristics[j].flags) {
                    if (g_svc_defs[i].characteristics[j].uuid)
                        osi_free((ble_uuid_t *)g_svc_defs[i].characteristics[j].uuid);

                    /*descriptors*/
                    for (int k = 0; ; k++) {
                        if (g_svc_defs[i].characteristics[j].descriptors[k].att_flags) {
                            if (g_svc_defs[i].characteristics[j].descriptors[k].uuid) {
                                //ble_uuid_t *uuid = g_svc_defs[i].characteristics[j].descriptors[k].uuid;
                                osi_free((ble_uuid_t *)g_svc_defs[i].characteristics[j].descriptors[k].uuid);
                            }
                        } else {
                            osi_free(g_svc_defs[i].characteristics[j].descriptors);
                            break;
                        }
                    }
                } else {
                    osi_free((struct ble_gatt_chr_def *)g_svc_defs[i].characteristics);
                    break;
                }

            }
        } else {
            osi_free(g_svc_defs);
            break;
        }
    }

}

void btc_gatts_startservice(UINT16 service_id, tBTA_GATT_TRANSPORT sup_transport)
{
    int ret = 0;
    ssv_ble_gatts_cb_param_t param;

    if (g_svc_defs==NULL){
        printf("%s g_svc_defs is null, please add att tab first\n", __FUNCTION__);
    }

    /*ble_gatts_start already called in btc_gatts_act_create_attr_tab*/
    //ret = ble_gatts_start();
    //if (ret)
    //    printf("%s ble_gatts_start fail ret %d\n", __FUNCTION__, ret);

    if (ret)
        param.start.status = SSV_GATT_ERROR;
    else
        param.start.status = SSV_GATT_OK;


    param.start.service_handle = service_id;
    btc_gatts_cb_to_app(SSV_GATTS_START_EVT, g_app_id, &param);

}

void btc_gatts_call_handler(btc_msg_t *msg)
{
    btc_ble_gatts_args_t *arg = (btc_ble_gatts_args_t *)msg->arg;
    tBTA_GATTS          cb_data;
    int rc = 0;

    /* refer to bta_gatts_create_srvc in bta_gatts_act.c*/
    switch (msg->act) {
    case BTC_GATTS_ACT_APP_REGISTER: {
        tBT_UUID uuid;

        uuid.len = LEN_UUID_16;
        uuid.uu.uuid16 = arg->app_reg.app_id;

        //BTA_GATTS_AppRegister(&uuid, btc_gatts_inter_cb);
        SSV_GATTS_AppRegister(&uuid);
        break;
    }

    case BTC_GATTS_ACT_APP_UNREGISTER:
        //BTA_GATTS_AppDeregister(arg->app_unreg.gatts_if);
        SSV_GATTS_AppUnRegister(arg->app_unreg.gatts_if);
        break;
    case BTC_GATTS_ACT_CREATE_SERVICE: {
        tBTA_GATT_SRVC_ID srvc_id;
        btc_to_bta_srvc_id(&srvc_id, &arg->create_srvc.service_id);
        SSV_GATTS_CreateService(arg->create_srvc.gatts_if, &srvc_id.id.uuid,
            srvc_id.id.inst_id, arg->create_srvc.num_handle,
            srvc_id.is_primary);

        #if 0//only for test
        rc = ble_gatts_count_cfg(ssv_svc_defs);
        printf("\33[31m %s():%d rc=%d, please remove\33[0m\r\n",__FUNCTION__ ,__LINE__,rc);
        printf("\33[31m %s():%d please remove\33[0m\r\n",__FUNCTION__ ,__LINE__);
        printf("\33[31m %s():%d please remove\33[0m\r\n",__FUNCTION__ ,__LINE__);
        assert(rc == 0);
        rc = ble_gatts_add_svcs(ssv_svc_defs);
        printf("\33[31m %s():%d rc=%d\33[0m\r\n",__FUNCTION__ ,__LINE__,rc);
        ble_gatts_start();
        #endif

        break;
    }
    case BTC_GATTS_ACT_CREATE_ATTR_TAB:
        btc_gatts_act_create_attr_tab(arg->create_attr_tab.gatts_attr_db,
            arg->create_attr_tab.gatts_if,
            arg->create_attr_tab.max_nb_attr,
            arg->create_attr_tab.srvc_inst_id);
        break;
    case BTC_GATTS_ACT_DELETE_SERVICE:
    #if 1
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        //todo free service
        //BTA_GATTS_DeleteService(arg->delete_srvc.service_handle);
    #endif
        break;
    case BTC_GATTS_ACT_START_SERVICE:
        btc_gatts_startservice(arg->start_srvc.service_handle, BTA_GATT_TRANSPORT_LE);
        //BTA_GATTS_StartService(arg->start_srvc.service_handle, BTA_GATT_TRANSPORT_LE);
        break;
    case BTC_GATTS_ACT_STOP_SERVICE:
    #if 1
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        //BTA_GATTS_StopService(arg->stop_srvc.service_handle);
    #endif
        break;
    case BTC_GATTS_ACT_ADD_INCLUDE_SERVICE:
    #if 1
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        //BTA_GATTS_AddIncludeService(arg->add_incl_srvc.service_handle, arg->add_incl_srvc.included_service_handle);
    #endif
        break;
    case BTC_GATTS_ACT_ADD_CHAR: {
    #if 1
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        //tBT_UUID uuid;
        //btc_to_bta_uuid(&uuid, &arg->add_char.char_uuid);

        //BTA_GATTS_AddCharacteristic(arg->add_char.service_handle, &uuid,
        //    arg->add_char.perm, arg->add_char.property,
        //    (tGATT_ATTR_VAL *)&arg->add_char.char_val,
        //    (tBTA_GATTS_ATTR_CONTROL *)&arg->add_char.attr_control);
    #endif
        break;
    }
    case BTC_GATTS_ACT_ADD_CHAR_DESCR: {
    #if 1
        printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        //tBT_UUID uuid;
        //btc_to_bta_uuid(&uuid, &arg->add_descr.descr_uuid);
        //BTA_GATTS_AddCharDescriptor(arg->add_descr.service_handle, arg->add_descr.perm, &uuid,
        //    (tBTA_GATT_ATTR_VAL *)&arg->add_descr.descr_val,
        //    (tBTA_GATTS_ATTR_CONTROL *)&arg->add_descr.attr_control);
    #endif
        break;
    }
    case BTC_GATTS_ACT_SEND_INDICATE:
        SSV_GATTS_HandleValueIndication(arg->send_ind.conn_id, arg->send_ind.attr_handle,
            arg->send_ind.value_len, arg->send_ind.value, arg->send_ind.need_confirm);
        break;
    case BTC_GATTS_ACT_SEND_RESPONSE: {
        ssv_ble_gatts_cb_param_t param;
        ssv_gatt_rsp_t *p_rsp = arg->send_rsp.rsp;
        if (p_rsp) {
            memcpy(gatt_svr_buf, p_rsp->attr_value.value, p_rsp->attr_value.len);
            gatt_svr_buf_len = p_rsp->attr_value.len;
            g_transfer_id = arg->send_rsp.trans_id;
            osi_sem_give(&svr_chr_access_sem);
            tBTA_GATTS_RSP rsp_struct;
            btc_to_bta_response(&rsp_struct, p_rsp);
            //BTA_GATTS_SendRsp(arg->send_rsp.conn_id, arg->send_rsp.trans_id,
            //    arg->send_rsp.status, &rsp_struct);
            param.rsp.handle = rsp_struct.attr_value.handle;
        } else {
            gatt_svr_buf_len = 0;
            g_transfer_id = arg->send_rsp.trans_id;
            osi_sem_give(svr_chr_access_sem);
            //BTA_GATTS_SendRsp(arg->send_rsp.conn_id, arg->send_rsp.trans_id,
            //    arg->send_rsp.status, NULL);
        }

        param.rsp.status = 0;
        btc_gatts_cb_to_app(SSV_GATTS_RESPONSE_EVT, BTC_GATT_GET_GATT_IF(arg->send_rsp.conn_id), &param);
        break;
    }
    case BTC_GATTS_ACT_SET_ATTR_VALUE:
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        //BTA_SetAttributeValue(arg->set_attr_val.handle, arg->set_attr_val.length,
        //    arg->set_attr_val.value);
    #endif
    break;
    case BTC_GATTS_ACT_OPEN: {
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        // Ensure device is in inquiry database
        //tBTA_GATT_TRANSPORT transport = BTA_GATT_TRANSPORT_LE;

        //TODO : implement address type and device type
#if  0
        if (_get_address_type(arg->remote_bda, &addr_type) &&
                btif_get_device_type(arg->remote_bda, &device_type) &&
                device_type != BT_DEVICE_TYPE_BREDR) {
            BTA_DmAddBleDevice(p_cb->bd_addr.address, addr_type, device_type);
        }
#else
        //BTA_DmAddBleDevice(p_cb->bd_addr.address, addr_type, device_type);
#endif
        /*
         not support background connection
        // Mark background connections
        if (!arg->open.is_direct) {
            BTA_DmBleSetBgConnType(BTM_BLE_CONN_AUTO, NULL);
        }
        */

        //transport = BTA_GATT_TRANSPORT_LE;

        // Connect!
        //BTA_GATTS_Open(arg->open.gatts_if, arg->open.remote_bda,
        //    arg->open.is_direct, transport);
    #endif
        break;
    }
    case BTC_GATTS_ACT_CLOSE:
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        // TODO : implement cancel open
        // Cancel pending foreground/background connections
        //BTA_GATTS_CancelOpen(p_cb->server_if, p_cb->bd_addr.address, TRUE);
        //BTA_GATTS_CancelOpen(p_cb->server_if, p_cb->bd_addr.address, FALSE);

        // Close active connection
        if (arg->close.conn_id != 0) {
            //BTA_GATTS_Close(arg->close.conn_id);
        }
    #endif
    break;
    case BTC_GATTS_ACT_SEND_SERVICE_CHANGE: {
    #if 1
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
    #else
        BD_ADDR remote_bda;
        memcpy(remote_bda, arg->send_service_change.remote_bda, BD_ADDR_LEN);
        //BTA_GATTS_SendServiceChangeIndication(arg->send_service_change.gatts_if, remote_bda);
    #endif
        break;
    }

    default:
        break;
    }
    btc_gatts_arg_deep_free(msg);
}

static void btc_gatts_cb_param_copy_free(btc_msg_t *msg, tBTA_GATTS *p_data)
{
    uint16_t event = msg->act;

    switch (event) {
    case BTA_GATTS_READ_EVT:
    case BTA_GATTS_WRITE_EVT:
    case BTA_GATTS_EXEC_WRITE_EVT:
    case BTA_GATTS_MTU_EVT:
        if (p_data && p_data->req_data.p_data) {
            osi_free(p_data->req_data.p_data);
        }
        break;
    case BTA_GATTS_CONF_EVT:
        break;
    default:
        break;
    }
}

void btc_gatts_cb_handler(btc_msg_t *msg)
{

    ssv_ble_gatts_cb_param_t param;
    tBTA_GATTS *p_data = (tBTA_GATTS *)msg->arg;
    ssv_gatt_if_t gatts_if;

    switch (msg->act) {

    case BTA_GATTS_REG_EVT: {
        gatts_if = p_data->reg_oper.server_if;
        param.reg.status = p_data->reg_oper.status;
        param.reg.app_id = p_data->reg_oper.uuid.uu.uuid16;

        btc_gatts_cb_to_app(SSV_GATTS_REG_EVT, gatts_if, &param);
        break;
    }

    case BTA_GATTS_DEREG_EVT: {
        gatts_if = p_data->reg_oper.server_if;
        btc_gatts_cb_to_app(SSV_GATTS_UNREG_EVT, gatts_if, NULL);
        break;
    }
    case BTA_GATTS_READ_EVT: {
        gatts_if = BTC_GATT_GET_GATT_IF(p_data->req_data.conn_id);
        param.read.conn_id = BTC_GATT_GET_CONN_ID(p_data->req_data.conn_id);
        param.read.trans_id = p_data->req_data.trans_id;
        memcpy(param.read.bda, p_data->req_data.remote_bda, SSV_BD_ADDR_LEN);
        param.read.handle = p_data->req_data.p_data->read_req.handle;
        param.read.offset = p_data->req_data.p_data->read_req.offset;
        param.read.is_long = p_data->req_data.p_data->read_req.is_long;
        printf("read.handle %d, %d\n", param.read.handle, p_data->req_data.p_data->read_req.handle);
        param.read.need_rsp = p_data->req_data.p_data->read_req.need_rsp;
        btc_gatts_cb_to_app(SSV_GATTS_READ_EVT, gatts_if, &param);
        break;
    }
    case BTA_GATTS_WRITE_EVT: {
        gatts_if = BTC_GATT_GET_GATT_IF(p_data->req_data.conn_id);
        param.write.conn_id = BTC_GATT_GET_CONN_ID(p_data->req_data.conn_id);
        param.write.trans_id = p_data->req_data.trans_id;
        memcpy(param.write.bda, p_data->req_data.remote_bda, SSV_BD_ADDR_LEN);
        if (p_data->req_data.p_data == NULL) {
            break;
        }
        param.write.handle = p_data->req_data.p_data->write_req.handle;
        param.write.offset = p_data->req_data.p_data->write_req.offset;
        param.write.need_rsp = p_data->req_data.p_data->write_req.need_rsp;
        param.write.is_prep = p_data->req_data.p_data->write_req.is_prep;
        param.write.len = p_data->req_data.p_data->write_req.len;
        param.write.value = p_data->req_data.p_data->write_req.value;

        btc_gatts_cb_to_app(SSV_GATTS_WRITE_EVT, gatts_if, &param);

        break;
    }
    case BTA_GATTS_EXEC_WRITE_EVT: {
        gatts_if = BTC_GATT_GET_GATT_IF(p_data->req_data.conn_id);
        param.exec_write.conn_id = BTC_GATT_GET_CONN_ID(p_data->req_data.conn_id);
        param.exec_write.trans_id = p_data->req_data.trans_id;
        memcpy(param.exec_write.bda, p_data->req_data.remote_bda, SSV_BD_ADDR_LEN);
        if (p_data->req_data.p_data == NULL) {
            break;
        }
        param.exec_write.exec_write_flag = p_data->req_data.p_data->exec_write;

        btc_gatts_cb_to_app(SSV_GATTS_EXEC_WRITE_EVT, gatts_if, &param);
        break;
    }
    case BTA_GATTS_MTU_EVT:
        gatts_if = BTC_GATT_GET_GATT_IF(p_data->req_data.conn_id);
        param.mtu.conn_id = BTC_GATT_GET_CONN_ID(p_data->req_data.conn_id);
        param.mtu.mtu = p_data->req_data.p_data->mtu;

        btc_gatts_cb_to_app(SSV_GATTS_MTU_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_CONF_EVT:
        gatts_if = BTC_GATT_GET_GATT_IF(p_data->confirm.conn_id);
        param.conf.conn_id = BTC_GATT_GET_CONN_ID(p_data->confirm.conn_id);
        param.conf.status = p_data->confirm.status;
        param.conf.handle = 0;
        printf("0x%x ,gatts_if 0x%x, conn_id 0x%x\n", p_data->confirm.conn_id, gatts_if, param.conf.conn_id);

        btc_gatts_cb_to_app(SSV_GATTS_CONF_EVT, gatts_if, &param);
        break;

    case BTA_GATTS_CREATE_EVT:
        gatts_if = p_data->create.server_if;
        param.create.status = p_data->create.status;
        param.create.service_handle = p_data->create.service_id;
        param.create.service_id.is_primary = p_data->create.is_primary;
        param.create.service_id.id.inst_id = p_data->create.svc_instance;
        bta_to_btc_uuid(&param.create.service_id.id.uuid, &p_data->create.uuid);

        btc_gatts_cb_to_app(SSV_GATTS_CREATE_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_ADD_INCL_SRVC_EVT:
        gatts_if = p_data->add_result.server_if;
        param.add_incl_srvc.status = p_data->add_result.status;
        param.add_incl_srvc.attr_handle = p_data->add_result.attr_id;
        param.add_incl_srvc.service_handle = p_data->add_result.service_id;

        btc_gatts_cb_to_app(SSV_GATTS_ADD_INCL_SRVC_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_ADD_CHAR_EVT:
        gatts_if = p_data->add_result.server_if;
        param.add_char.status = p_data->add_result.status;
        param.add_char.attr_handle = p_data->add_result.attr_id;
        param.add_char.service_handle = p_data->add_result.service_id;
        bta_to_btc_uuid(&param.add_char.char_uuid, &p_data->add_result.char_uuid);

        btc_gatts_cb_to_app(SSV_GATTS_ADD_CHAR_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_ADD_CHAR_DESCR_EVT:
        gatts_if = p_data->add_result.server_if;
        param.add_char_descr.status = p_data->add_result.status;
        param.add_char_descr.attr_handle = p_data->add_result.attr_id;
        param.add_char_descr.service_handle = p_data->add_result.service_id;
        bta_to_btc_uuid(&param.add_char_descr.descr_uuid, &p_data->add_result.char_uuid);

        btc_gatts_cb_to_app(SSV_GATTS_ADD_CHAR_DESCR_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_DELELTE_EVT:
        gatts_if = p_data->srvc_oper.server_if;
        param.del.status = p_data->srvc_oper.status;
        param.del.service_handle = p_data->srvc_oper.service_id;

        btc_gatts_cb_to_app(SSV_GATTS_DELETE_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_START_EVT:
        gatts_if = p_data->srvc_oper.server_if;
        param.start.status = p_data->srvc_oper.status;
        param.start.service_handle = p_data->srvc_oper.service_id;

        btc_gatts_cb_to_app(SSV_GATTS_START_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_STOP_EVT:
        gatts_if = p_data->srvc_oper.server_if;
        param.stop.status = p_data->srvc_oper.status;
        param.stop.service_handle = p_data->srvc_oper.service_id;

        btc_gatts_cb_to_app(SSV_GATTS_STOP_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_CONNECT_EVT:
        gatts_if = p_data->conn.server_if;
        param.connect.conn_id = BTC_GATT_GET_CONN_ID(p_data->conn.conn_id);
        memcpy(param.connect.remote_bda, p_data->conn.remote_bda, SSV_BD_ADDR_LEN);
        param.connect.conn_params.interval = p_data->conn.conn_params.interval;
        param.connect.conn_params.latency = p_data->conn.conn_params.latency;
        param.connect.conn_params.timeout = p_data->conn.conn_params.timeout;
        btc_gatts_cb_to_app(SSV_GATTS_CONNECT_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_DISCONNECT_EVT:
        gatts_if = p_data->conn.server_if;
        param.disconnect.conn_id = BTC_GATT_GET_CONN_ID(p_data->conn.conn_id);
        param.disconnect.reason = p_data->conn.reason;
        memcpy(param.disconnect.remote_bda, p_data->conn.remote_bda, SSV_BD_ADDR_LEN);

        btc_gatts_cb_to_app(SSV_GATTS_DISCONNECT_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_OPEN_EVT:
        gatts_if = p_data->open.server_if;
        param.open.status = p_data->open.status;

        btc_gatts_cb_to_app(BTA_GATTS_OPEN_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_CANCEL_OPEN_EVT:
        gatts_if = p_data->cancel_open.server_if;
        param.cancel_open.status = p_data->cancel_open.status;

        btc_gatts_cb_to_app(BTA_GATTS_CANCEL_OPEN_EVT, gatts_if, &param);
        break;

    case BTA_GATTS_CLOSE_EVT:
        gatts_if = BTC_GATT_GET_GATT_IF(p_data->close.conn_id);
        param.close.status = p_data->close.status;
        param.close.conn_id = BTC_GATT_GET_CONN_ID(p_data->close.conn_id);

        btc_gatts_cb_to_app(BTA_GATTS_CLOSE_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_SEND_SERVICE_CHANGE_EVT:
        gatts_if = p_data->service_change.server_if;
        param.service_change.status = p_data->service_change.status;
        btc_gatts_cb_to_app(SSV_GATTS_SEND_SERVICE_CHANGE_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_LISTEN_EVT:
        // do nothing
        break;
    case BTA_GATTS_CONGEST_EVT:
        gatts_if = BTC_GATT_GET_GATT_IF(p_data->congest.conn_id);
        param.congest.conn_id = BTC_GATT_GET_CONN_ID(p_data->congest.conn_id);
        param.congest.congested = p_data->congest.congested;
        btc_gatts_cb_to_app(SSV_GATTS_CONGEST_EVT, gatts_if, &param);
        break;
    case BTA_GATTS_SET_ATTR_VAL_EVT:
        gatts_if = p_data->attr_val.server_if;
        param.set_attr_val.srvc_handle = p_data->attr_val.service_id;
        param.set_attr_val.attr_handle = p_data->attr_val.attr_id;
        param.set_attr_val.status = p_data->attr_val.status;
        btc_gatts_cb_to_app(SSV_GATTS_SET_ATTR_VAL_EVT, gatts_if, &param);
        break;

    default:
        // do nothing
        break;
    }

    btc_gatts_cb_param_copy_free(msg, p_data);// free bta
}

void btc_gatts_arg_deep_copy(btc_msg_t *msg, void *p_dest, void *p_src)
{
    btc_ble_gatts_args_t *dst = (btc_ble_gatts_args_t *) p_dest;
    btc_ble_gatts_args_t *src = (btc_ble_gatts_args_t *)p_src;

    switch (msg->act) {
    case BTC_GATTS_ACT_SEND_INDICATE: {
        if (src->send_ind.value && (src->send_ind.value_len > 0)) {
            dst->send_ind.value = (uint8_t *) osi_malloc(src->send_ind.value_len);
            if (dst->send_ind.value) {
                memcpy(dst->send_ind.value, src->send_ind.value, src->send_ind.value_len);
            } else {
                BTC_TRACE_ERROR("%s %d no mem\n", __func__, msg->act);
            }
        } else {
            dst->send_ind.value = NULL;
            if (src->send_ind.value) {
                BTC_TRACE_ERROR("%s %d, invalid length", __func__, msg->act);
            }
        }
        break;
    }
    case BTC_GATTS_ACT_SEND_RESPONSE: {
        if (src->send_rsp.rsp) {
            dst->send_rsp.rsp = (ssv_gatt_rsp_t *) osi_malloc(sizeof(ssv_gatt_rsp_t));
            if (dst->send_rsp.rsp) {
                memcpy(dst->send_rsp.rsp, src->send_rsp.rsp, sizeof(ssv_gatt_rsp_t));
            } else {
                BTC_TRACE_ERROR("%s %d no mem\n", __func__, msg->act);
            }
        }
        break;

    }
    case BTC_GATTS_ACT_ADD_CHAR: {
        if (src->add_char.char_val.attr_value && (src->add_char.char_val.attr_len > 0)) {
            dst->add_char.char_val.attr_value = (uint8_t *) osi_malloc(src->add_char.char_val.attr_len);
            if (dst->add_char.char_val.attr_value) {
                memcpy(dst->add_char.char_val.attr_value, src->add_char.char_val.attr_value,
                        src->add_char.char_val.attr_len);
            } else {
                BTC_TRACE_ERROR("%s %d no mem\n", __func__, msg->act);
            }
        } else {
            dst->add_char.char_val.attr_value = NULL;
            if (src->add_char.char_val.attr_value) {
                BTC_TRACE_ERROR("%s %d, invalid length", __func__, msg->act);
            }
        }
        break;
    }
    case BTC_GATTS_ACT_ADD_CHAR_DESCR: {
        if (src->add_descr.descr_val.attr_value && (src->add_descr.descr_val.attr_len > 0)) {
            dst->add_descr.descr_val.attr_value = (uint8_t *) osi_malloc(src->add_descr.descr_val.attr_len);
            if (dst->add_descr.descr_val.attr_value) {
                memcpy(dst->add_descr.descr_val.attr_value, src->add_descr.descr_val.attr_value,
                        src->add_descr.descr_val.attr_len);
            } else {
                BTC_TRACE_ERROR("%s %d no mem\n", __func__, msg->act);
            }
        } else {
            dst->add_descr.descr_val.attr_value = NULL;
            if (src->add_descr.descr_val.attr_value) {
                BTC_TRACE_ERROR("%s %d, invalid length", __func__, msg->act);
            }
        }
        break;
    }
    case BTC_GATTS_ACT_CREATE_ATTR_TAB: {
        uint8_t num_attr = src->create_attr_tab.max_nb_attr;
        if (src->create_attr_tab.gatts_attr_db && (num_attr > 0)) {
            dst->create_attr_tab.gatts_attr_db = (ssv_gatts_attr_db_t *) osi_malloc(sizeof(ssv_gatts_attr_db_t) * num_attr);
            if (dst->create_attr_tab.gatts_attr_db) {
                memcpy(dst->create_attr_tab.gatts_attr_db, src->create_attr_tab.gatts_attr_db,
                        sizeof(ssv_gatts_attr_db_t) * num_attr);
            } else {
                BTC_TRACE_ERROR("%s %d no mem\n",__func__, msg->act);
            }
        } else {
            BTC_TRACE_ERROR("%s %d, NULL data", __func__, msg->act);
        }
        break;
    }
   case BTC_GATTS_ACT_SET_ATTR_VALUE: {
        if (src->set_attr_val.value && (src->set_attr_val.length > 0)) {
            dst->set_attr_val.value = (uint8_t *) osi_malloc(src->set_attr_val.length);
            if (dst->set_attr_val.value) {
                memcpy(dst->set_attr_val.value, src->set_attr_val.value, src->set_attr_val.length);
            } else {
                BTC_TRACE_ERROR("%s %d no mem\n",__func__, msg->act);
            }
        } else {
            dst->set_attr_val.value = NULL;
            if (src->set_attr_val.value) {
                BTC_TRACE_ERROR("%s %d, invalid length", __func__, msg->act);
            } else {
                BTC_TRACE_WARNING("%s %d, NULL value", __func__, msg->act);
            }
        }
        break;
    }
    default:
        BTC_TRACE_DEBUG("%s Unhandled deep copy %d\n", __func__, msg->act);
        break;
    }

}

ssv_gatt_status_t btc_gatts_get_attr_value(uint16_t attr_handle, uint16_t *length, uint8_t **value)
{
    printf("\33[31m%s():%d It's not implemented \33[0m\r\n",__FUNCTION__ ,__LINE__);
     //return BTA_GetAttributeValue(attr_handle, length, value);
     return 0;//todo
}