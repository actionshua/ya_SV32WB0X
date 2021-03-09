#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

/* SMP include */
//#include "smp/smp.h"
//#include "smpble/smp_ble.h"
#include "atcmd_general.h"
#include "ssv_hal_ble_common.h"
#include "ssv_gap_ble_api.h"
#include "ssv_gatts_api.h"
#include "ssv_gatt_common_api.h"

#define hexdump(buf, len) \
    do { \
        int i; \
        for (i = 0; i < (len); i++) { \
            if (0 == ((i+1) % 16)) { \
                printf("\n"); \
            } \
            printf(" %X", ((uint8_t *)buf)[i]); \
        } \
    } while(0)

#define BLE_UART_DEFAULT_DEVICE_NAME    ("UART")
#define BLE_UART_GATTC_MTU_SIZE         (256)
#define MAX_DEVNAME_LEN                 (16)

//#define CONFIG_SET_RAW_ADV_DATA
#ifdef CONFIG_SET_RAW_ADV_DATA
uint8_t raw_adv_data[] = {
    /* flags */
    0x02, 0x01, 0x06,
    /* tx power*/
    0x02, 0x0a, 0xeb,
    /* service uuid */
    0x11, 0x07,
    0x9e, 0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 0x01, 0x00, 0x40, 0x6e
};
static uint8_t raw_scan_rsp_data[] = {
    // SSV_GATT_DEMO
    0x0F, 0x09,
    0x53, 0x53, 0x56, 0x5F, 0x47, 0x41, 0x54,
    0x54, 0x53, 0x5f, 0x44, 0x45, 0x4d, 0x4F};
#endif

enum
{
    BLE_UART_IDX_SVC,

    BLE_UART_IDX_TX_CHAR,
    BLE_UART_IDX_TX_VAL,
    BLE_UART_IDX_TX_NOTIFY_CFG,

    BLE_UART_IDX_RX_CHAR,
    BLE_UART_IDX_RX_VAL,

    BLE_UART_IDX_NB,
};

uint16_t ble_uart_handle_table[BLE_UART_IDX_NB];
char sg_ble_uart_device_name[MAX_DEVNAME_LEN];

#define BLE_UART_PROFILE_NUM                       1
#define BLE_UART_PROFILE_APP_IDX                   0
#define SSV_BLE_UART_APP_ID                        0
//#define SSV_BLE_UART_APP_ID                        0x716

#define SVC_INST_ID 0

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

static ssv_gatt_if_t sg_gatts_if = 0xff;
static uint16_t sg_conn_id = 0xffff;

static void gatts_ble_uart_profile_event_handler(ssv_gatts_cb_event_t event, ssv_gatt_if_t gatts_if, ssv_ble_gatts_cb_param_t *param);

/* One gatt-based profile one app_id and one gatts_if, this array will store the gatts_if returned by SSV_GATTS_REG_EVT */
static struct gatts_profile_inst sg_ble_uart_profile_table[BLE_UART_PROFILE_NUM] = {
    [BLE_UART_PROFILE_APP_IDX] = {
        .gatts_cb = gatts_ble_uart_profile_event_handler,
        .gatts_if = SSV_GATT_IF_NONE,       /* Not get the gatt_if, so initial is SSV_GATT_IF_NONE */
    },
};

static uint8_t adv_config_done = 0;
#define ADV_CONFIG_FLAG      (1 << 0)
#define SCAN_RSP_CONFIG_FLAG (1 << 1)

static ssv_ble_adv_params_t adv_params = {
	.adv_int_min        = 0x20,
	.adv_int_max        = 0x40,
	.adv_type           = ADV_TYPE_IND,
	.own_addr_type      = BLE_ADDR_TYPE_PUBLIC,
	.channel_map        = ADV_CHNL_ALL,
	.adv_filter_policy  = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

static uint8_t ble_uart_service_uuid128[] = {
    /* LSB <--------------------------------------------------------------------------------> MSB */
    0x9e, 0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 0x01, 0x00, 0x40, 0x6e
};

static uint8_t ble_uart_tx_uuid128[] = {
    /* LSB <--------------------------------------------------------------------------------> MSB */
    0x9e, 0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 0x03, 0x00, 0x40, 0x6e
};

static uint8_t ble_uart_rx_uuid128[] = {
    /* LSB <--------------------------------------------------------------------------------> MSB */
    0x9e, 0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 0x02, 0x00, 0x40, 0x6e
};

static ssv_ble_adv_data_t adv_data = {
	.set_scan_rsp        = 0,
	.include_name        = 0,
	.include_txpower     = 1,
	.min_interval        = 0x20,
	.max_interval        = 0x40,
	.appearance          = 0x00,
	.manufacturer_len    = 0,
	.p_manufacturer_data = NULL,
	.service_data_len    = 0,
	.p_service_data      = NULL,
	.service_uuid_len    = sizeof(ble_uart_service_uuid128),
	.p_service_uuid      = ble_uart_service_uuid128,
	.flag                = (SSV_BLE_ADV_FLAG_GEN_DISC | SSV_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

static ssv_ble_adv_data_t scan_rsp_data = {
    .set_scan_rsp        = 1,
    .include_name        = 1,
    .include_txpower     = 1,
    //.min_interval      = 0x20,
    //.max_interval      = 0x40,
    .appearance          = 0x00,
    .manufacturer_len    = 0,
    .p_manufacturer_data = NULL,
    .service_data_len    = 0,
    .p_service_data      = NULL,
//    .service_uuid_len    = sizeof(ble_uart_service_uuid128),
//    .p_service_uuid      = ble_uart_service_uuid128,
    .flag                = (SSV_BLE_ADV_FLAG_GEN_DISC | SSV_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

static const uint16_t primary_service_uuid         = SSV_GATT_UUID_PRI_SERVICE;
static const uint16_t character_declaration_uuid   = SSV_GATT_UUID_CHAR_DECLARE;
static const uint16_t character_client_config_uuid = SSV_GATT_UUID_CHAR_CLIENT_CONFIG;
static const uint8_t char_prop_read                = SSV_GATT_CHAR_PROP_BIT_READ;
static const uint8_t char_prop_write               = SSV_GATT_CHAR_PROP_BIT_WRITE;
static const uint8_t char_prop_notify              = SSV_GATT_CHAR_PROP_BIT_NOTIFY;
static const uint8_t char_prop_read_write_notify   = SSV_GATT_CHAR_PROP_BIT_WRITE | SSV_GATT_CHAR_PROP_BIT_READ | SSV_GATT_CHAR_PROP_BIT_NOTIFY;
static const uint8_t char_prop_write_write_nr      = SSV_GATT_CHAR_PROP_BIT_WRITE_NR | SSV_GATT_CHAR_PROP_BIT_WRITE;

static const uint8_t ble_uart_ccc[2]               = {0x00, 0x00};


#define CHAR_DECLARATION_SIZE       (sizeof(uint8_t))
#define BLE_UART_TX_MAX_LEN         (256)
#define BLE_UART_RX_MAX_LEN         (256)

static uint8_t ble_tx_data[BLE_UART_TX_MAX_LEN] = "abc";
static uint8_t ble_rx_data[BLE_UART_RX_MAX_LEN] = "abc";

/* Full Database Description - Used to add attributes into the database */
static const ssv_gatts_attr_db_t ble_uart_gatt_db[BLE_UART_IDX_NB] =
{
    // Service Declaration
    [BLE_UART_IDX_SVC]            =
    {{SSV_GATT_AUTO_RSP}, {SSV_UUID_LEN_16, (uint8_t *)&primary_service_uuid, SSV_GATT_PERM_READ,
      sizeof(ble_uart_service_uuid128), sizeof(ble_uart_service_uuid128), (uint8_t *)ble_uart_service_uuid128}},

    /* Characteristic Declaration */
    [BLE_UART_IDX_TX_CHAR]        =
    {{SSV_GATT_AUTO_RSP}, {SSV_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, SSV_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_notify}},

    /* Characteristic Value */
    [BLE_UART_IDX_TX_VAL]         =
    {{SSV_GATT_AUTO_RSP}, {SSV_UUID_LEN_128, (uint8_t *)&ble_uart_tx_uuid128, SSV_GATT_PERM_READ | SSV_GATT_PERM_WRITE,
      BLE_UART_TX_MAX_LEN, 4, (uint8_t *)ble_tx_data}},

    /* Characteristic Configuration Descriptor */
    [BLE_UART_IDX_TX_NOTIFY_CFG]  =
    {{SSV_GATT_AUTO_RSP}, {SSV_UUID_LEN_16, (uint8_t *)&character_client_config_uuid, SSV_GATT_PERM_READ | SSV_GATT_PERM_WRITE,
      sizeof(uint16_t), sizeof(ble_uart_ccc), (uint8_t *)ble_uart_ccc}},

    /* Characteristic Declaration */
    [BLE_UART_IDX_RX_CHAR]        =
    {{SSV_GATT_AUTO_RSP}, {SSV_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, SSV_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_write_write_nr}},

    /* Characteristic Value */
    [BLE_UART_IDX_RX_VAL]         =
    {{SSV_GATT_RSP_BY_APP}, {SSV_UUID_LEN_128, (uint8_t *)&ble_uart_rx_uuid128, SSV_GATT_PERM_READ | SSV_GATT_PERM_WRITE,
      BLE_UART_RX_MAX_LEN, 4, (uint8_t *)ble_rx_data}},
};

static void gatts_ble_uart_profile_event_handler(ssv_gatts_cb_event_t event,ssv_gatt_if_t gatts_if,
    ssv_ble_gatts_cb_param_t *param)
{
    switch (event) {
        case SSV_GATTS_REG_EVT:
        {
            printf("[%s] SSV_GATTS_REG_EVT: %d\n", __func__, gatts_if);
            ssv_err_t set_dev_name_ret = ssv_ble_gap_set_device_name(sg_ble_uart_device_name);
            if (set_dev_name_ret){
                printf("[%s] set device name failed, error code = %x", __func__, set_dev_name_ret);
            }

#ifdef CONFIG_SET_RAW_ADV_DATA
            ssv_err_t raw_adv_ret = ssv_ble_gap_config_adv_data_raw(raw_adv_data, sizeof(raw_adv_data));
            if (raw_adv_ret){
                printf("[%s] config adv data raw failed, error code = %x", __func__, raw_adv_ret);
            }
            adv_config_done |= ADV_CONFIG_FLAG;
            ssv_err_t raw_scan_ret = ssv_ble_gap_config_scan_rsp_data_raw(raw_scan_rsp_data, sizeof(raw_scan_rsp_data));
            if (raw_scan_ret){
                printf("[%s] config scan raw scan rsp data failed, error code = %x", __func__, raw_scan_ret);
            }
            adv_config_done |= SCAN_RSP_CONFIG_FLAG;
#else
            //config adv data
            ssv_err_t ret = ssv_ble_gap_config_adv_data(&adv_data);
            if (ret){
                printf("[%s] config adv data failed, error code = %x", __func__, ret);
            }
            adv_config_done |= ADV_CONFIG_FLAG;

            //config scan rssvonse data
            ret = ssv_ble_gap_config_adv_data(&scan_rsp_data);
            if (ret){
                printf("[%s] config scan raw scan rsp data failed, error code = %x", __func__, ret);
            }
            adv_config_done |= SCAN_RSP_CONFIG_FLAG;
#endif

            ssv_err_t create_attr_ret = ssv_ble_gatts_create_attr_tab(ble_uart_gatt_db, gatts_if, BLE_UART_IDX_NB, SVC_INST_ID);
            if (create_attr_ret){
                printf("[%s] create attr table failed, error code = %x", __func__, create_attr_ret);
            }
        }
            break;

        case SSV_GATTS_CONNECT_EVT:
            printf("[%s] SSV_GATTS_CONNECT_EVT: %d\n", __func__, gatts_if);
            sg_gatts_if = gatts_if;
            sg_conn_id = param->connect.conn_id;
            break;

        case SSV_GATTS_CREAT_ATTR_TAB_EVT:
            printf("[%s] SSV_GATTS_CREAT_ATTR_TAB_EVT, status %d, handles 0x%x\n", __func__,
                    param->add_attr_tab.status, param->add_attr_tab.handles[0]);

            if (param->add_attr_tab.status != SSV_GATT_OK){
                printf("[%s] create attribute table failed, error code=0x%x\n", __func__, param->add_attr_tab.status);
            }
            else if (param->add_attr_tab.num_handle != BLE_UART_IDX_NB){
                printf("[%s] create attribute table abnormally, num_handle (%d) doesn't equal to BLE_UART_IDX_NB(%d)\n", __func__, param->add_attr_tab.num_handle, BLE_UART_IDX_NB);
            }
            else {
                //printf("[%s] create attribute table successfully, the number handle = %d\n", __func__, param->add_attr_tab.num_handle);
                memcpy(ble_uart_handle_table, param->add_attr_tab.handles, sizeof(ble_uart_handle_table));
                ssv_ble_gatts_start_service(ble_uart_handle_table[BLE_UART_IDX_SVC]);
            }
            break;
        case SSV_GATTS_DISCONNECT_EVT:
			printf("[%s] SSV_GATTS_DISCONNECT_EVT, reason = 0x%x\n", __func__, param->disconnect.reason);
            ssv_ble_gap_start_advertising(&adv_params);
            break;
        case SSV_GATTS_READ_EVT:
            printf("[%s] SSV_GATTS_READ_EVT, conn_id %d, trans_id %d, handle %d\n", __func__,
                param->read.conn_id, param->read.trans_id, param->read.handle);
            ssv_gatt_rsp_t rsp;
            memset(&rsp, 0, sizeof(ssv_gatt_rsp_t));
            rsp.attr_value.handle = param->read.handle;
            rsp.attr_value.len = 4;/*ascii code "ABC"*/
            rsp.attr_value.value[0] = 0x41;
            rsp.attr_value.value[1] = 0x42;
            rsp.attr_value.value[2] = 0x43;
            rsp.attr_value.value[3] = 0x0;
            ssv_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id,
                                    SSV_GATT_OK, &rsp);
            break;

        case SSV_GATTS_WRITE_EVT:
			printf("[%s] SSV_GATTS_WRITE_EVT\n", __func__);
            if (!param->write.is_prep){
                // the data length of gattc write  must be less than GATTS_DEMO_CHAR_VAL_LEN_MAX.
                //printf("[%s] GATT_WRITE_EVT, handle = %d, value len = %d, value :\n", __func__, param->write.handle, param->write.len);
                //hexdump(param->write.value, param->write.len);
                if (ble_uart_handle_table[BLE_UART_IDX_RX_VAL] == param->write.handle){
                    printf("recv RX_Characteristic: %s\n", param->write.value);
                } else if (ble_uart_handle_table[BLE_UART_IDX_TX_NOTIFY_CFG] == param->write.handle && param->write.len == 2){
                    uint16_t descr_value = param->write.value[1]<<8 | param->write.value[0];
                    if (descr_value == 0x0001){
                        printf("notify enable");
                        uint8_t notify_data[15];
                        for (int i = 0; i < sizeof(notify_data); ++i)
                        {
                            notify_data[i] = i % 0xff;
                        }
                        //the size of notify_data[] need less than MTU size
                        ssv_ble_gatts_send_indicate(gatts_if, param->write.conn_id, ble_uart_handle_table[BLE_UART_IDX_TX_VAL], sizeof(notify_data), notify_data, false);
                    }else if (descr_value == 0x0002){
                        printf("indicate enable");
                        uint8_t indicate_data[15];
                        for (int i = 0; i < sizeof(indicate_data); ++i)
                        {
                            indicate_data[i] = i % 0xff;
                        }
                        //the size of indicate_data[] need less than MTU size
                        ssv_ble_gatts_send_indicate(gatts_if, param->write.conn_id, ble_uart_handle_table[BLE_UART_IDX_TX_VAL], sizeof(indicate_data), indicate_data, true);
                    }
                    else if (descr_value == 0x0000){
                        printf("notify/indicate disable ");
                    }else{
                        printf("unknown descr value");
                    }

                }
                /* send response when param->write.need_rsp is true*/
                if (param->write.need_rsp){
                    ssv_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, SSV_GATT_OK, NULL);
                }
            }else{
                /* handle prepare write */
                //example_prepare_write_event_env(gatts_if, &prepare_write_env, param);
                printf("[%s] else SSV_GATTS_WRITE_EVT\n", __func__);
            }
      	    break;
        case SSV_GATTS_EXEC_WRITE_EVT:
            // the length of gattc prepare write data must be less than GATTS_DEMO_CHAR_VAL_LEN_MAX.
            printf("SSV_GATTS_EXEC_WRITE_EVT");
            //example_exec_write_event_env(&prepare_write_env, param);
            break;
        case SSV_GATTS_MTU_EVT:
            printf("SSV_GATTS_MTU_EVT, MTU %d", param->mtu.mtu);
            break;
        case SSV_GATTS_CONF_EVT:
            printf("SSV_GATTS_CONF_EVT, status = %d, attr_handle %d", param->conf.status, param->conf.handle);
            break;
        case SSV_GATTS_START_EVT:
            printf("SERVICE_START_EVT, status %d, service_handle %d", param->start.status, param->start.service_handle);
            break;
        case SSV_GATTS_STOP_EVT:
        case SSV_GATTS_OPEN_EVT:
        case SSV_GATTS_CANCEL_OPEN_EVT:
        case SSV_GATTS_CLOSE_EVT:
        case SSV_GATTS_LISTEN_EVT:
        case SSV_GATTS_CONGEST_EVT:
        case SSV_GATTS_UNREG_EVT:
        case SSV_GATTS_DELETE_EVT:
        default:
            printf("[%s] event %d\n", __func__, event);
            break;
    }
}

static void gatts_event_handler(ssv_gatts_cb_event_t event, ssv_gatt_if_t gatts_if, ssv_ble_gatts_cb_param_t *param)
{
    /* If event is register event, store the gatts_if for each profile */
    if (event == SSV_GATTS_REG_EVT) {
        if (param->reg.status == SSV_GATT_OK) {
            if (param->reg.app_id != 0) {
                printf("[%s] register, app_id %04x, it should be 0\n", __func__, param->reg.app_id);
                while(1);// aMH todo remove this assert!!
            }
            sg_ble_uart_profile_table[param->reg.app_id].gatts_if = gatts_if;
        } else {
            printf("Reg app failed, app_id %04x, status %d\n",
                    param->reg.app_id,
                    param->reg.status);
            return;
        }
    }

    /* If the gatts_if equal to profile A, call profile A cb handler,
     * so here call each profile's callback */
    do {
        int idx;
        for (idx = 0; idx < BLE_UART_PROFILE_NUM; idx++) {
            if (gatts_if == SSV_GATT_IF_NONE || /* SSV_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
                    gatts_if == sg_ble_uart_profile_table[idx].gatts_if) {
                if (sg_ble_uart_profile_table[idx].gatts_cb) {
                    sg_ble_uart_profile_table[idx].gatts_cb(event, gatts_if, param);
                }
            }
        }
    } while (0);
}


void ssv_ble_uart_gap_event_cb(ssv_gap_ble_cb_event_t event, ssv_ble_gap_cb_param_t *param)
{
    uint8_t *adv_name = NULL;
    uint8_t adv_name_len = 0;

	printf("[%s] event %d\n", __func__, event);
    switch (event) {
    #ifdef CONFIG_SET_RAW_ADV_DATA
        case SSV_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:
            adv_config_done &= (~ADV_CONFIG_FLAG);
            if (adv_config_done == 0){
                ssv_ble_gap_start_advertising(&adv_params);
            }
            break;
        case SSV_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT:
            adv_config_done &= (~SCAN_RSP_CONFIG_FLAG);
            if (adv_config_done == 0){
                ssv_ble_gap_start_advertising(&adv_params);
            }
            break;
    #else
        case SSV_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
            adv_config_done &= (~ADV_CONFIG_FLAG);
            if (adv_config_done == 0){
                ssv_ble_gap_start_advertising(&adv_params);
            }
            break;
        case SSV_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
            adv_config_done &= (~SCAN_RSP_CONFIG_FLAG);
            if (adv_config_done == 0){
                ssv_ble_gap_start_advertising(&adv_params);
            }
            break;
    #endif
        case SSV_GAP_BLE_ADV_START_COMPLETE_EVT:
            printf("[%s] event SSV_GAP_BLE_ADV_START_COMPLETE_EVT\n", __func__);
            //adv_status = ADV_ON;
            break;

        case SSV_GAP_BLE_ADV_STOP_COMPLETE_EVT:
            printf("[%s] event SSV_GAP_BLE_ADV_STOP_COMPLETE_EVT\n", __func__);
            //adv_status = ADV_OFF;
            break;
        default:
            printf("[%s] event %d\n", __func__, event);
            break;
    }
}

int At_ble_uart_init(stParam *param)
{
    int ret = 0;
    if (param->argc == 1) {
        strncpy(sg_ble_uart_device_name, param->argv[0], MAX_DEVNAME_LEN);
    } else {
        strncpy(sg_ble_uart_device_name, BLE_UART_DEFAULT_DEVICE_NAME, MAX_DEVNAME_LEN);
    }
    ssv_ble_gap_register_callback(ssv_ble_uart_gap_event_cb);

    do {
        ret = ssv_hal_ble_common_init();
        if (ret) {
            printf("[%s] failed in line %d\n", __func__, __LINE__);
            break;
        }
        ret = ssv_ble_gatts_register_callback(gatts_event_handler);
        if (ret){
            printf("[%s] failed in line %d gatts register error, error code = %x\n", __func__, __LINE__, ret);
            break;
        }
        ret = ssv_ble_gatts_app_register(SSV_BLE_UART_APP_ID);
        if (ret){
            printf("[%s] failed in line %d gatts app register error, error code = %x\n", __func__, __LINE__, ret);
            break;
        }
    } while(0);
    if (ret) {
        return -1;
    }

    ssv_err_t ssv_ret = ssv_ble_gatt_set_local_mtu(BLE_UART_GATTC_MTU_SIZE);
    if (ssv_ret){
        printf("[%s] line %d, set local MTU failed, error code = %x", __func__, __LINE__, ssv_ret);
    }

    return 0;
}

int At_ble_uart_send(stParam *param)
{
    if (param->argc < 1) {
        printf("usage:\n");
        printf("AT+ble_uart_send=<string>\n");
        return ERROR_INVALID_PARAMETER;
    }
    int len = strlen(param->argv[0]);
    if (len > BLE_UART_TX_MAX_LEN) {
        len = BLE_UART_TX_MAX_LEN;
    }
    ssv_ble_gatts_send_indicate(sg_gatts_if, sg_conn_id, ble_uart_handle_table[BLE_UART_IDX_TX_VAL], len, (uint8_t *)param->argv[0], false);
    return 0;
}
