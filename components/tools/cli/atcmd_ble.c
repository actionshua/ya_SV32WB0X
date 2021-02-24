#if BLE_GAP_ATCMD_EN

#include <string.h>
#include <osal.h>
#include "atcmd.h"
#include "errora.h"
#include "atcmd_ble.h"
#include "ssv_err.h"

#if BLE_GAP_ATCMD_EN
#include "ssv_hal_ble_gap.h"
#include "ssv_hal_ble_gatts.h"
#include "ssv_hal_ble_common.h"
#include "ssv_gap_ble_api.h"
#endif

#if (BLE_GATTC_ATCMD_EN|BLE_GATTS_ATCMD_EN)
#include "ssv_gatt_common_api.h"
#endif

#if BLE_GATTC_ATCMD_EN
#include "ssv_hal_ble_gattc.h"
#include "ssv_gattc_api.h"
#endif

#if (BLE_GATTC_ATCMD_EN|BLE_GATTS_ATCMD_EN)
#define ATCMD_GATTC_MTU_SIZE 128
#endif

void ssv_atcmd_gap_event_handler(ssv_gap_ble_cb_event_t event, ssv_ble_gap_cb_param_t *param)
{
    uint8_t *adv_name = NULL;
    uint8_t adv_name_len = 0;

    switch (event) {
        case SSV_GAP_BLE_ADV_START_COMPLETE_EVT:
            //adv_status = ADV_ON;
            break;

        case SSV_GAP_BLE_ADV_STOP_COMPLETE_EVT:
            //adv_status = ADV_OFF;
            break;

        case SSV_GAP_BLE_SCAN_RESULT_EVT: {
            ssv_ble_gap_cb_param_t *scan_result = (ssv_ble_gap_cb_param_t *)param;
            char str[64] = {0};
            switch (scan_result->scan_rst.search_evt) {
                case SSV_GAP_SEARCH_INQ_RES_EVT:
                    ATCMD_LOG_I("Find:%02X:%02X:%02X:%02X:%02X:%02X\n",
                        scan_result->scan_rst.bda[5], scan_result->scan_rst.bda[4], scan_result->scan_rst.bda[3],
                        scan_result->scan_rst.bda[2], scan_result->scan_rst.bda[1], scan_result->scan_rst.bda[0]);

                    if (scan_result->scan_rst.dev_type == SSV_BT_DEVICE_TYPE_BLE ||
                        scan_result->scan_rst.dev_type == SSV_BT_DEVICE_TYPE_DUMO) {
                            ATCMD_LOG_I("Remote bd type:");

                            if (scan_result->scan_rst.ble_addr_type == BLE_ADDR_TYPE_PUBLIC)
                                ATCMD_LOG_I("PUBLIC\n");
                            else if (scan_result->scan_rst.ble_addr_type == BLE_ADDR_TYPE_RANDOM)
                                ATCMD_LOG_I("RANDOM\n");
                            else if (scan_result->scan_rst.ble_addr_type == BLE_ADDR_TYPE_RPA_PUBLIC)
                                ATCMD_LOG_I("RPA_PUBLIC\n");
                            else if (scan_result->scan_rst.ble_addr_type == BLE_ADDR_TYPE_RPA_RANDOM)
                                ATCMD_LOG_I("RPA_RANDOM\n");

                    }
                    //ATCMD_LOG_I("searched Adv Data Len %d, Scan Response Len %d\n",
                    //    scan_result->scan_rst.adv_data_len, scan_result->scan_rst.scan_rsp_len);
                    adv_name = ssv_ble_resolve_adv_data(scan_result->scan_rst.ble_adv,
                                                        SSV_BLE_AD_TYPE_NAME_CMPL, &adv_name_len);
                    if (adv_name_len && (adv_name_len < 30)) {
                        memcpy(str, adv_name, adv_name_len);
                        ATCMD_LOG_I("Name:%s\n", str);
                    }
                    ATCMD_LOG_I("\n");
                    break;

                default:
                    break;
            }
        }

        default:
            break;
    }
}

#if BLE_GATTC_ATCMD_EN
#define ATCMD_WRITE_AUTO_SEND_LEN 128
static void ssv_atcmd_gattc_profile_cb(ssv_gattc_cb_event_t event, ssv_gatt_if_t gattc_if, ssv_ble_gattc_cb_param_t *param)
{
    ssv_ble_gattc_cb_param_t *p_data = (ssv_ble_gattc_cb_param_t *)param;

    switch (event) {
        case SSV_GATTC_REG_EVT:
            ATCMD_LOG_I("%s SSV_GATTC_REG_EVT\n", __FUNCTION__);
            break;

        case SSV_GATTC_CONNECT_EVT:
            ATCMD_LOG_I("%s SSV_GATTC_CONNECT_EVT gattc_if %d, conn_id %d\n",
                __FUNCTION__, gattc_if, p_data->connect.conn_id);

            ssv_err_t mtu_ret = ssv_ble_gattc_send_mtu_req(gattc_if, p_data->connect.conn_id);
            if (mtu_ret)
                ATCMD_LOG_I("%s config MTU error, error code = %x", __FUNCTION__, mtu_ret);

            break;

        case SSV_GATTC_DISCONNECT_EVT:
            ATCMD_LOG_I("%s SSV_GATTC_DISCONNECT_EVT gattc_if %d, conn_id %d\n",
                __FUNCTION__, gattc_if, p_data->connect.conn_id);
            break;

        case SSV_GATTC_CFG_MTU_EVT:
            ATCMD_LOG_I("%s SSV_GATTC_CFG_MTU_EVT\n", __FUNCTION__);
            //write ccc enable notification
            uint8_t write_data[2] = {0x01, 0x00};
            ssv_ble_gattc_write_char(gattc_if, p_data->cfg_mtu.conn_id, 13, sizeof(write_data), write_data,
                SSV_GATT_WRITE_TYPE_RSP, SSV_GATT_AUTH_REQ_NONE);

            //if (p_data->cfg_mtu.status == 0)
            //    p_data->cfg_mtu.conn_id

            break;

        case SSV_GATTC_WRITE_CHAR_EVT:
            ATCMD_LOG_I("%s SSV_GATTC_WRITE_CHAR_EVT\n", __FUNCTION__);
            break;

        case SSV_GATTC_NOTIFY_EVT:
            ATCMD_LOG_I("%s SSV_GATTC_NOTIF_EVT conn_id %d len %d\n",
                __FUNCTION__, p_data->notify.conn_id, p_data->notify.value_len);
            if( !p_data->notify.is_notify) {
                ATCMD_LOG_I("%s SSV_GATTC_WRITE_CHAR_EVT conn_id %d, value_len %d\n", __FUNCTION__, p_data->notify.conn_id, p_data->notify.value_len);
                if (p_data->notify.value_len >= 125) {
                    uint8_t *send_data = NULL;
                    send_data = OS_MemZalloc(ATCMD_WRITE_AUTO_SEND_LEN);
                    for (int i = 0; i < ATCMD_WRITE_AUTO_SEND_LEN; i ++)
                        send_data[i] = i;

                    ATCMD_LOG_I("%s call ssv_ble_gattc_write_char gattc_if %d, conn_id %d\n", __FUNCTION__, gattc_if, p_data->notify.conn_id);
                    ssv_ble_gattc_write_char(gattc_if, p_data->notify.conn_id, 15, ATCMD_WRITE_AUTO_SEND_LEN, send_data,
                        SSV_GATT_WRITE_TYPE_RSP, SSV_GATT_AUTH_REQ_NONE);

                    OS_MemFree(send_data);
                }
                //ssv_atcmd_add_gattc_receive_indication_len(gattc_if, p_data->notify.conn_id, p_data->notify.value_len);
            }
            break;

        default:
            break;
    }
}

#endif


#if BLE_GATTS_ATCMD_EN
ssv_gatt_if_t g_gatts_if = 0;
void ssv_atcmd_gatts_profile_cb(ssv_gatts_cb_event_t event,ssv_gatt_if_t gatts_if,
    ssv_ble_gatts_cb_param_t *param)
{

    switch (event) {
        case SSV_GATTS_REG_EVT:
            g_gatts_if = gatts_if;
            break;

        case SSV_GATTS_CONNECT_EVT:

            break;

        default:
            break;
    }

}
#endif


int At_ble_init(stParam *param)
{
    int ret = 0;
#if BLE_GATTS_ATCMD_EN
    ssv_hal_ble_gatts_set_profile_cb(ssv_atcmd_gatts_profile_cb);
#endif
#if BLE_GATTC_ATCMD_EN
    ssv_hal_ble_gattc_set_profile_cb(ssv_atcmd_gattc_profile_cb);
#endif
    ssv_hal_ble_gap_set_event_cb(ssv_atcmd_gap_event_handler);

    do{
        ret = ssv_hal_ble_common_init();
        if (ret)
            break;

        ret = ssv_hal_ble_gap_init();
        if (ret)
            break;
#if BLE_GATTS_ATCMD_EN
        ret = ssv_hal_ble_gatts_init();
        if (ret)
            break;
#endif

#if BLE_GATTC_ATCMD_EN
        ret = ssv_hal_ble_gattc_init();
        if (ret)
            break;
#endif
    } while(0);

    if (ret)
        return ERROR_BLE_FAILED;

#if BLE_GATTC_ATCMD_EN
    ret = ssv_ble_gattc_app_register(ATCMD_GATTC_PROFILE_A_APP_ID);
    if (ret){
        ATCMD_LOG_E("%s gattc app register failed, error code = %x\n", __func__, ret);
    }
#endif

#if (BLE_GATTC_ATCMD_EN|BLE_GATTS_ATCMD_EN)
    ssv_err_t local_mtu_ret = ssv_ble_gatt_set_local_mtu(ATCMD_GATTC_MTU_SIZE);
    if (local_mtu_ret){
        ATCMD_LOG_E("set local  MTU failed, error code = %x", local_mtu_ret);
    }
#endif

    ATCMD_LOG_I("%s done\n", __FUNCTION__);
    return ERROR_SUCCESS;
}
#if BLE_GATTS_ATCMD_EN
/* Full Database Description - Used to add attributes into the database */
enum
{
    AT_IDX_SVC,
    AT_IDX_CHAR_A,
    AT_IDX_CHAR_VAL_A,

    AT_IDX_CHAR_B,
    AT_IDX_CHAR_VAL_B,

    AT_HRS_IDX_NB,
};

static const uint16_t AT_GATTS_SERVICE_UUID      = 0x00FF;
static const uint16_t AT_GATTS_CHAR_UUID_TEST_A       = 0xFF01;
static const uint16_t AT_GATTS_CHAR_UUID_TEST_B       = 0xFF02;

static const uint16_t at_primary_service_uuid         = SSV_GATT_UUID_PRI_SERVICE;
static const uint16_t at_character_declaration_uuid   = SSV_GATT_UUID_CHAR_DECLARE;
static const uint16_t at_character_client_config_uuid = SSV_GATT_UUID_CHAR_CLIENT_CONFIG;
static const uint8_t at_char_prop_read                =  SSV_GATT_CHAR_PROP_BIT_READ;
static const uint8_t at_char_prop_write               = SSV_GATT_CHAR_PROP_BIT_WRITE;
static const uint8_t at_char_prop_read_write_notify   = SSV_GATT_CHAR_PROP_BIT_WRITE | SSV_GATT_CHAR_PROP_BIT_READ | SSV_GATT_CHAR_PROP_BIT_NOTIFY;

static const uint8_t at_char_value[4]                 = {0x11, 0x22, 0x33, 0x44};
#define AT_CHAR_DECLARATION_SIZE       (sizeof(uint8_t))
#define AT_GATTS_CHAR_VAL_LEN_MAX 128
static ssv_gatts_attr_db_t gatt_db[AT_HRS_IDX_NB] =
{
    // Service Declaration
    [AT_IDX_SVC]        =
    {{SSV_GATT_AUTO_RSP}, {SSV_UUID_LEN_16, (uint8_t *)&at_primary_service_uuid, SSV_GATT_PERM_READ,
      sizeof(uint16_t), sizeof(AT_GATTS_SERVICE_UUID), (uint8_t *)&AT_GATTS_SERVICE_UUID}},

    /* Characteristic Declaration */
    [AT_IDX_CHAR_A]     =
    {{SSV_GATT_AUTO_RSP}, {SSV_UUID_LEN_16, (uint8_t *)&at_character_declaration_uuid, SSV_GATT_PERM_READ,
      AT_CHAR_DECLARATION_SIZE, AT_CHAR_DECLARATION_SIZE, (uint8_t *)&at_char_prop_read_write_notify}},

    /* Characteristic Value */
    [AT_IDX_CHAR_VAL_A] =
    {{SSV_GATT_AUTO_RSP}, {SSV_UUID_LEN_16, (uint8_t *)&AT_GATTS_CHAR_UUID_TEST_A, SSV_GATT_PERM_READ | SSV_GATT_PERM_WRITE,
      AT_GATTS_CHAR_VAL_LEN_MAX, sizeof(at_char_value), (uint8_t *)at_char_value}},

    /* Characteristic Declaration */
    [AT_IDX_CHAR_B]      =
    {{SSV_GATT_AUTO_RSP}, {SSV_UUID_LEN_16, (uint8_t *)&at_character_declaration_uuid, SSV_GATT_PERM_READ,
      AT_CHAR_DECLARATION_SIZE, AT_CHAR_DECLARATION_SIZE, (uint8_t *)&at_char_prop_read}},

    /* Characteristic Value */
    [AT_IDX_CHAR_VAL_B]  =
    {{SSV_GATT_AUTO_RSP}, {SSV_UUID_LEN_16, (uint8_t *)&AT_GATTS_CHAR_UUID_TEST_B, SSV_GATT_PERM_READ | SSV_GATT_PERM_WRITE,
      AT_GATTS_CHAR_VAL_LEN_MAX, sizeof(at_char_value), (uint8_t *)at_char_value}},
};

int At_ble_add_service(stParam *param)
{
    ssv_err_t api_ret = 0;
    uint16_t handle;

    api_ret = ssv_hal_ble_gatts_create_service_by_db(gatt_db, AT_HRS_IDX_NB, &handle);

    if (api_ret)
        ATCMD_LOG_E("ssv_hal_ble_gatts_create_service_by_db api_ret = %d", api_ret);

    return api_ret;
}

int At_ble_send_indication(stParam *param)
{
    ssv_err_t api_ret = 0;
    char *gatts_if = NULL, *conn_id = NULL;
    char *att_handle = NULL, *need_confirm = NULL;
    char *data_len = NULL;
    uint8_t  *data = NULL;


    gatts_if = param->argv[0];
    conn_id = param->argv[1];
    att_handle = param->argv[2];
    data_len = param->argv[3];
    data = (uint8_t*)param->argv[4];
    need_confirm = param->argv[5];

    unsigned char v_gatts_if = strtoul(gatts_if, NULL, 10);
    unsigned char v_conn_id = strtoul(conn_id, NULL, 10);
    unsigned char v_att_handle = strtoul(att_handle, NULL, 10);
    unsigned char v_need_confirm = strtoul(need_confirm, NULL, 10);
    unsigned char v_data_len = strtoul(data_len, NULL, 10);

    ATCMD_LOG_I("At_ble_send_indication v_data_len = %d\n", v_data_len);
    do {
        ssv_api_gatts_event_clear_bit(SSV_API_GATTS_SEND_INDICATION);
        api_ret = ssv_ble_gatts_send_indicate(v_gatts_if, v_conn_id,
            v_att_handle, v_data_len, data, v_need_confirm);
        CHECK_RESULT(api_ret, "ssv_ble_gatts_send_indicate fail");
        api_ret = ssv_api_gatts_wait_event(SSV_API_GATTS_SEND_INDICATION,
            "SSV_API_GATTS_SEND_INDICATION timeout\n");
        CHECK_RESULT(api_ret, "");
    } while (0);

    if (api_ret)
        ATCMD_LOG_E("ssv_ble_gatts_send_indicate api_ret = %d", api_ret);

    return api_ret;
}
#endif
static ssv_ble_scan_params_t ble_scan_params;

int At_ble_start_adv(stParam *param)
{
    ssv_ble_adv_params_t adv_params = {
        .adv_int_min        = 0x20,
        .adv_int_max        = 0x40,
        .adv_type           = ADV_TYPE_IND,
        .own_addr_type      = BLE_ADDR_TYPE_PUBLIC,
        .channel_map        = ADV_CHNL_ALL,
        .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
    };
    uint8_t raw_adv_data[] = {
            0x02, 0x01, 0x06,
            0x02, 0x0a, 0xeb, 0x03, 0x03, 0xab, 0xcd
    };

    uint8_t *p_raw_scan_rsp=NULL;
    uint8_t raw_scan_rsp_len=0;
    uint8_t bON=0;
    uint8_t err=0;
    ssv_err_t api_ret = 0;


    if ((param->argc > 2)||(param->argc==0)) {
		goto USAGE;

	}

    bON = atoi(param->argv[0]);

    if(param->argc==2)
    {
        raw_scan_rsp_len=strlen(param->argv[1])+2;
        p_raw_scan_rsp=OS_MemAlloc(raw_scan_rsp_len);
        if(NULL==p_raw_scan_rsp)
        {
            printf("malloc fail\r\n");
            err++;
            goto DONE;
        }
        p_raw_scan_rsp[0]=raw_scan_rsp_len-1;
        p_raw_scan_rsp[1]=0x09;
        memcpy(&p_raw_scan_rsp[2],param->argv[1],raw_scan_rsp_len-2);
    }
    else
    {
        //default scan rsp data
        raw_scan_rsp_len=16;
        p_raw_scan_rsp=OS_MemAlloc(raw_scan_rsp_len);
        if(NULL==p_raw_scan_rsp)
        {
            printf("malloc fail\r\n");
            err++;
            goto DONE;
        }
        /*
        uint8_t raw_scan_rsp_data[] = {
        0x0f, 0x09, 0x53, 0x53, 0x56, 0x5f, 0x47, 0x41, 0x54, 0x54, 0x53, 0x5f, 0x44,
        0x45, 0x4d, 0x4f
        */
        p_raw_scan_rsp[0]=0x0F;p_raw_scan_rsp[1]=0x09;p_raw_scan_rsp[2]=0x53;p_raw_scan_rsp[3]=0x53;p_raw_scan_rsp[4]=0x56;p_raw_scan_rsp[5]=0x5F;p_raw_scan_rsp[6]=0x47;p_raw_scan_rsp[7]=0x41;
        p_raw_scan_rsp[8]=0x54;p_raw_scan_rsp[9]=0x54;p_raw_scan_rsp[10]=0x53;p_raw_scan_rsp[11]=0x5F;p_raw_scan_rsp[12]=0x44;p_raw_scan_rsp[13]=0x45;p_raw_scan_rsp[14]=0x4D;p_raw_scan_rsp[15]=0x4F;
    };

    do {
        if(TRUE==bON)
        {
            //config adv data
            ssv_api_gap_event_clear_bit(SSV_API_GAP_CFG_ADV_DATA_RAW);
            api_ret = ssv_ble_gap_config_adv_data_raw(raw_adv_data, sizeof(raw_adv_data));
            CHECK_RESULT(api_ret, "ssv_ble_gap_config_adv_data_raw fail");
            api_ret = ssv_api_gap_wait_event(SSV_API_GAP_CFG_ADV_DATA_RAW,
                "ms_hal_ble_adv_start ssv_ble_gap_config_adv_data_raw timeout\n");
            CHECK_RESULT(api_ret, "");

            //config scan data
            ssv_api_gap_event_clear_bit(SSV_API_GAP_CFG_SCAN_RSP_DATA_RAW);
            api_ret = ssv_ble_gap_config_scan_rsp_data_raw(p_raw_scan_rsp, raw_scan_rsp_len);
            CHECK_RESULT(api_ret, "ssv_ble_gap_config_scan_rsp_data_raw fail");
            ssv_api_gap_wait_event( SSV_API_GAP_CFG_SCAN_RSP_DATA_RAW,
                "ms_hal_ble_adv_start ssv_ble_gap_config_scan_rsp_data_raw timeout\n");
            CHECK_RESULT(api_ret, "");

            //start adv
            ssv_api_gap_event_clear_bit(SSV_API_GAP_ADV_START_EVENT);
            api_ret = ssv_ble_gap_start_advertising(&adv_params);
            CHECK_RESULT(api_ret, "ssv_ble_gap_start_advertising fail");
            ssv_api_gap_wait_event(SSV_API_GAP_ADV_START_EVENT,
                "ms_hal_ble_adv_start ssv_ble_gap_start_advertising timeout\n");
        }
        else{
            ssv_ble_gap_stop_advertising();
        }

    } while(0);

DONE:
    if(NULL!=p_raw_scan_rsp)
    {
        OS_MemFree(p_raw_scan_rsp);
    }

    if(0==err)
    {
        return ERROR_SUCCESS;
    }
    else{
        return ERROR_BLE_FAILED;
    }

USAGE:
    printf("AT+bleADV=[on/off],[dev name]\r\n");
    printf("on=1\r\n");
    printf("off=0\r\n");
    return ERROR_INVALID_PARAMETER;
}

int At_ble_stop_adv(stParam *param)
{
    return ERROR_SUCCESS;
}

int At_ble_set_scan_params(stParam *param)
{
    char *scan_type = NULL, *own_addr_type = NULL, *scan_filter_policy = NULL;
    char *scan_interval = NULL, *scan_window = NULL, *scan_duplicate = NULL;

    if (param->argc < 6) {
        ATCMD_LOG_I("%s scan_type, own_addr_type, scan_filter_policy\n", __FUNCTION__);
        ATCMD_LOG_I("%s scan_interval 0xXX, scan_window  0xXX, scan_duplicate\n", __FUNCTION__);
        return ERROR_INVALID_PARAMETER;
    }

    scan_type = param->argv[0];
	own_addr_type = param->argv[1];
    scan_filter_policy = param->argv[2];
    scan_interval = param->argv[3];
    scan_window = param->argv[4];
    scan_duplicate = param->argv[5];

    ble_scan_params.scan_type              = strtoul(scan_type, NULL, 16);
    ble_scan_params.own_addr_type          = strtoul(own_addr_type, NULL, 16);
    ble_scan_params.scan_filter_policy     = strtoul(scan_filter_policy, NULL, 16);
    ble_scan_params.scan_interval          = strtoul(scan_interval, NULL, 16);
    ble_scan_params.scan_window            = strtoul(scan_window, NULL, 16);
    ble_scan_params.scan_duplicate         = strtoul(scan_duplicate, NULL, 16);

    ssv_api_gap_event_clear_bit(SSV_API_GAP_SCAN_PARAM_SET_COMPLETE_EVT);
    ssv_err_t scan_ret = ssv_ble_gap_set_scan_params(&ble_scan_params);
    if (scan_ret)
        ATCMD_LOG_I("ssv_ble_gap_set_scan_params fail = %d", scan_ret);

    scan_ret = ssv_api_gap_wait_event(SSV_API_GAP_SCAN_PARAM_SET_COMPLETE_EVT,
        "ssv_ble_gap_set_scan_params timeout\n");

    if (scan_ret) {
        ATCMD_LOG_I("ssv_ble_gap_set_scan_params fail = %d", scan_ret);
        return ERROR_BLE_FAILED;
    }

    return ERROR_SUCCESS;
}

int At_ble_start_scan(stParam *param)
{
    char *scan_duration = NULL;
    uint32_t duration = 0;

    if (param->argc < 1) {
        ATCMD_LOG_I("%s duration\n", __FUNCTION__);
        return ERROR_INVALID_PARAMETER;
    }

    scan_duration = param->argv[0];
    duration = strtoul(scan_duration, NULL, 16);

    do {
        ssv_api_gap_event_clear_bit(SSV_API_GAP_SCAN_START_COMPLETE_EVT);
        ssv_err_t scan_ret = ssv_ble_gap_start_scanning(duration);
        CHECK_RESULT(scan_ret, "ssv_ble_gap_start_scanning fail");
        scan_ret = ssv_api_gap_wait_event( SSV_API_GAP_SCAN_START_COMPLETE_EVT,
            "ssv_ble_gap_start_scanning SSV_API_GAP_SCAN_START_COMPLETE_EVT timeout\n");
        CHECK_RESULT(scan_ret, "");
    } while(0);

    return ERROR_SUCCESS;
}

int At_ble_disconnect(stParam *param)
{
    char *remote_bda = NULL;
    ssv_bd_addr_t st_remote_bda;

    if (param->argc < 1) {
        ATCMD_LOG_I("%s remote_bda\n", __FUNCTION__);
        return ERROR_INVALID_PARAMETER;
    }

    remote_bda = param->argv[0];

    for (int i = 0; i < SSV_BD_ADDR_LEN; i++)
        st_remote_bda[SSV_BD_ADDR_LEN - 1 - i] = strtoul(remote_bda + 3*i, NULL, 16);

    ssv_ble_gap_disconnect(st_remote_bda);

    return ERROR_SUCCESS;
}
#if BLE_GATTC_ATCMD_EN
int At_ble_gattc_open(stParam *param)
{
    char *gattc_if = NULL, *remote_bda = NULL, *remote_addr_type = NULL;
    char *is_direct = NULL;
    ssv_bd_addr_t st_remote_bda;

    uint8_t v_gattc_if = 0, v_remote_addr_type = 0, v_is_direct = 0;

    if (param->argc < 4) {
        ATCMD_LOG_I("%s gattc_if, remote_bda, remote_addr_type, is_direct\n", __FUNCTION__);
        return ERROR_INVALID_PARAMETER;
    }


    gattc_if = param->argv[0];
	remote_bda = param->argv[1];
    remote_addr_type = param->argv[2];
    is_direct = param->argv[3];

    v_gattc_if                 = strtoul(gattc_if, NULL, 16);
    v_remote_addr_type         = strtoul(remote_addr_type, NULL, 16);
    v_is_direct                = strtoul(is_direct, NULL, 16);

    ATCMD_LOG_I("%s remote_bda %s\n",
        __FUNCTION__, remote_bda);

    for (int i = 0; i < SSV_BD_ADDR_LEN; i++)
        st_remote_bda[SSV_BD_ADDR_LEN - 1 - i] = strtoul(remote_bda + 3*i, NULL, 16);

    ssv_hal_ble_gattc_open(v_gattc_if, st_remote_bda, v_remote_addr_type, v_is_direct);
    return ERROR_SUCCESS;
}


int At_ble_gattc_write_char(stParam *param)
{
    char *gattc_if = NULL, *conn_id = NULL, *handle = NULL;
    char *value_len = NULL, *value = NULL, *write_type = NULL;
    char *auth_req = NULL;

    uint8_t v_gattc_if = 0, v_conn_id = 0, v_handle = 0;
    uint8_t v_value_len = 0, v_write_type = 0, v_auth_req = 0;
    uint8_t *v_value = NULL;

    gattc_if = param->argv[0];
	conn_id = param->argv[1];
    handle = param->argv[2];
    value_len = param->argv[3];
    value = param->argv[4];
    write_type = param->argv[5];
    auth_req = param->argv[6];

    v_gattc_if              = strtoul(gattc_if, NULL, 10);
    v_conn_id               = strtoul(conn_id, NULL, 10);
    v_handle                = strtoul(handle, NULL, 10);
    v_value_len             = strtoul(value_len, NULL, 10);
    v_write_type            = strtoul(write_type, NULL, 10);
    v_auth_req              = strtoul(auth_req, NULL, 10);
    v_value =(uint8_t*) value;

    do {
        ssv_api_gattc_event_clear_bit(SSV_API_GATTC_WRITE_CHAR_EVT);
        ssv_err_t ret = ssv_ble_gattc_write_char(v_gattc_if, v_conn_id, v_handle, v_value_len, v_value,
            v_write_type, v_auth_req);
        CHECK_RESULT(ret, "ssv_ble_gattc_write_char fail");
        ret = ssv_api_gattc_wait_event( SSV_API_GATTC_WRITE_CHAR_EVT,
            "ssv_ble_gattc_write_char SSV_API_GATTC_WRITE_CHAR_EVT timeout\n");
        CHECK_RESULT(ret, "");
    } while(0);

    return ERROR_SUCCESS;
}
#endif




#endif //#if BLE_GAP_ATCMD_EN