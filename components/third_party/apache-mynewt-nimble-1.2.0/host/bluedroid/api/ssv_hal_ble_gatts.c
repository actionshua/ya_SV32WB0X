#include <bsp.h>
#include <stdio.h>
#include "ssv_hal_ble_common.h"
#include "ssv_hal_ble_gatts.h"
#include "ssv_gap_ble_api.h"
#include "ssv_gatts_api.h"
#include "ssv_log.h"

#define SSV_HAL_GATTS "SSV_HAL_GATTS"
#define SVC_INST_ID 0

uint32_t g_gatts_value = 0;
EventGroupHandle_t g_gatts_eg = NULL;

ssv_hal_ble_gatts_profile_event_handler_callback_t ssv_ble_gatts_profile_event_handler_cb;

static ssv_gatt_char_prop_t a_property = 0;

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

static void gatts_event_handler(ssv_gatts_cb_event_t event, ssv_gatt_if_t gatts_if, ssv_ble_gatts_cb_param_t *param);
static void gatts_profile_a_event_handler(ssv_gatts_cb_event_t event,ssv_gatt_if_t gatts_if,
    ssv_ble_gatts_cb_param_t *param);

/* One gatt-based profile one app_id and one gatts_if, this array will store the gatts_if returned by SSV_GATTS_REG_EVT */
static struct gatts_profile_inst gl_gatts_profile_tab[GATTS_PROFILE_NUM] = {
    [GATTS_PROFILE_A_APP_ID] = {
        .gatts_cb = gatts_profile_a_event_handler,
        .gatts_if = SSV_GATT_IF_NONE,       /* Not get the gatt_if, so initial is SSV_GATT_IF_NONE */
    },
};

void ssv_api_gatts_event_set_by_evtntval(u32 event_val,u32 bit)
{
    BaseType_t val = 0;
    if(g_gatts_eg)
    {
        if(gOsFromISR)
            xEventGroupSetBitsFromISR(g_gatts_eg, bit, &val);
        else
            xEventGroupSetBits(g_gatts_eg, bit);

        SSV_API_SET_BIT(g_gatts_value, bit);
    }
}

void ssv_api_gatts_event_clear_bit(uint32_t bitval)
{
	SSV_API_CLEAR_BIT(g_gatts_value, bitval);
}

void ssv_api_gatts_event_set(uint32_t bit)
{
    ssv_api_gatts_event_set_by_evtntval(g_gatts_value, bit);
}

int ssv_api_gatts_wait_event(uint32_t bit, char *failmsg)
{
	int ret = 0;
    EventBits_t evtrlt;
	WAIT_API_EVENT(g_gatts_eg, bit, API_EVENT_WAIT_TIME,
            failmsg, SSV_HAL_GATTS);
	return ret;
}
uint16_t g_service_base_handle = 0;
uint16_t g_gatts_mtu = 0;
static void gatts_profile_a_event_handler(ssv_gatts_cb_event_t event,ssv_gatt_if_t gatts_if,
    ssv_ble_gatts_cb_param_t *param)
 {
    ssv_ble_conn_update_params_t conn_params;
    //SSV_LOGW(SSV_HAL_GATTS, "%s event %d\n", __FUNCTION__, event);
    switch (event) {
        case SSV_GATTS_REG_EVT:
            SSV_LOGI(SSV_HAL_GATTS, "REGISTER_APP_EVT, status %d, app_id %d\n", param->reg.status, param->reg.app_id);
            /*gl_gatts_profile_tab[PROFILE_A_APP_ID].service_id.is_primary = true;
            gl_gatts_profile_tab[PROFILE_A_APP_ID].service_id.id.inst_id = 0x00;
            gl_gatts_profile_tab[PROFILE_A_APP_ID].service_id.id.uuid.len = SSV_UUID_LEN_16;
            gl_gatts_profile_tab[PROFILE_A_APP_ID].service_id.id.uuid.uuid.uuid16 = GATTS_SERVICE_UUID_TEST_A;

            ssv_err_t set_dev_name_ret = ssv_ble_gap_set_device_name(TEST_DEVICE_NAME);
            if (set_dev_name_ret){
                SSV_LOGE(SSV_HAL_GATTS, "set device name failed, error code = %x", set_dev_name_ret);
            }*/

            //ssv_ble_gatts_create_service(gatts_if, &gl_profile_tab[PROFILE_A_APP_ID].service_id, GATTS_NUM_HANDLE_TEST_A);
            /* SSV_GATTS_CREATE_EVT for end of ssv_ble_gatts_create_service*/
            break;
        case SSV_GATTS_READ_EVT: {
            SSV_LOGW(SSV_HAL_GATTS, "GATT_READ_EVT, conn_id %d, trans_id %d, handle %d\n", param->read.conn_id, param->read.trans_id, param->read.handle);

            break;
        }
        case SSV_GATTS_WRITE_EVT: {
            //SSV_LOGW(SSV_HAL_GATTS, "GATT_WRITE_EVT, conn_id %d, trans_id %d, handle %d", param->write.conn_id, param->write.trans_id, param->write.handle);
            break;
        }
        case SSV_GATTS_EXEC_WRITE_EVT:
            SSV_LOGI(SSV_HAL_GATTS,"SSV_GATTS_EXEC_WRITE_EVT");
            break;
        case SSV_GATTS_MTU_EVT:
            //SSV_LOGI(SSV_HAL_GATTS, "SSV_GATTS_MTU_EVT, MTU %d", param->mtu.mtu);
            g_gatts_mtu = param->mtu.mtu;
            break;
        case SSV_GATTS_UNREG_EVT:
            break;
        case SSV_GATTS_CREATE_EVT:
            SSV_LOGI(SSV_HAL_GATTS, "CREATE_SERVICE_EVT, status %d,  service_handle %d\n", param->create.status, param->create.service_handle);
            break;
        case SSV_GATTS_ADD_INCL_SRVC_EVT:
            break;
        case SSV_GATTS_ADD_CHAR_EVT: {
            SSV_LOGI(SSV_HAL_GATTS, "ADD_CHAR_EVT, status %d,  attr_handle %d, service_handle %d\n",
                    param->add_char.status, param->add_char.attr_handle, param->add_char.service_handle);
            break;
        }
        case SSV_GATTS_ADD_CHAR_DESCR_EVT:
            gl_gatts_profile_tab[GATTS_PROFILE_A_APP_ID].descr_handle = param->add_char_descr.attr_handle;
            SSV_LOGI(SSV_HAL_GATTS, "ADD_DESCR_EVT, status %d, attr_handle %d, service_handle %d\n",
                    param->add_char_descr.status, param->add_char_descr.attr_handle, param->add_char_descr.service_handle);
            break;
        case SSV_GATTS_DELETE_EVT:
            break;
        case SSV_GATTS_START_EVT:
            SSV_LOGI(SSV_HAL_GATTS, "SERVICE_START_EVT, status %d, service_handle %d\n",
                    param->start.status, param->start.service_handle);
            break;
        case SSV_GATTS_STOP_EVT:
            break;
        case SSV_GATTS_CONNECT_EVT: {
            SSV_LOGI(SSV_HAL_GATTS, "SSV_GATTS_CONNECT_EVT, conn_id %d, remote %02x:%02x:%02x:%02x:%02x:%02x",
                    param->connect.conn_id,
                    param->connect.remote_bda[5], param->connect.remote_bda[4], param->connect.remote_bda[3],
                    param->connect.remote_bda[2], param->connect.remote_bda[1], param->connect.remote_bda[0]);
            gl_gatts_profile_tab[GATTS_PROFILE_A_APP_ID].conn_id = param->connect.conn_id;
            //start sent the update connection parameters to the peer device.
            //ssv_ble_gap_update_conn_params(&conn_params);
            break;
        }
        case SSV_GATTS_DISCONNECT_EVT:
            SSV_LOGI(SSV_HAL_GATTS, "SSV_GATTS_DISCONNECT_EVT, disconnect reason 0x%x", param->disconnect.reason);
            break;
        case SSV_GATTS_CONF_EVT:
            /*SSV_LOGI(SSV_HAL_GATTS, "SSV_GATTS_CONF_EVT, status %d attr_handle %d", param->conf.status, param->conf.handle);
            if (param->conf.status != SSV_GATT_OK){
                ssv_log_buffer_hex(SSV_HAL_GATTS, param->conf.value, param->conf.len);
            }*/

            ssv_api_gatts_event_set(SSV_API_GATTS_SEND_INDICATION);
            break;

        case SSV_GATTS_CREAT_ATTR_TAB_EVT:
			SSV_LOGI(SSV_HAL_GATTS, "SSV_GATTS_CREAT_ATTR_TAB_EVT, status %d, handles 0x%x ",
				param->add_attr_tab.status, *param->add_attr_tab.handles);

			if (param->add_attr_tab.handles)
				g_service_base_handle = (*param->add_attr_tab.handles);

            ssv_api_gatts_event_set(SSV_API_GATTS_CREATE_ATT_ATB);
            break;

        case SSV_GATTS_OPEN_EVT:
        case SSV_GATTS_CANCEL_OPEN_EVT:
        case SSV_GATTS_CLOSE_EVT:
        case SSV_GATTS_LISTEN_EVT:
        case SSV_GATTS_CONGEST_EVT:
        default:
            break;
        }

        if (ssv_ble_gatts_profile_event_handler_cb)
            ssv_ble_gatts_profile_event_handler_cb(event, gatts_if, param);

 }

static void gatts_event_handler(ssv_gatts_cb_event_t event, ssv_gatt_if_t gatts_if, ssv_ble_gatts_cb_param_t *param)
{
    //SSV_LOGW(SSV_HAL_GATTS, "%s event %d, gatts_if %d\n", __FUNCTION__, event, gatts_if);
    /* If event is register event, store the gatts_if for each profile */
    if (event == SSV_GATTS_REG_EVT) {
        if (param->reg.status == SSV_GATT_OK) {
            gl_gatts_profile_tab[param->reg.app_id].gatts_if = gatts_if;
        } else {
            SSV_LOGI(SSV_HAL_GATTS, "Reg app failed, app_id %04x, status %d\n",
                    param->reg.app_id,
                    param->reg.status);
            return;
        }
    }

    /* If the gatts_if equal to profile A, call profile A cb handler,
     * so here call each profile's callback */
    do {
        int idx;
        for (idx = 0; idx < GATTS_PROFILE_NUM; idx++) {
            if (gatts_if == SSV_GATT_IF_NONE || /* SSV_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
                    gatts_if == gl_gatts_profile_tab[idx].gatts_if) {
                if (gl_gatts_profile_tab[idx].gatts_cb) {
                    gl_gatts_profile_tab[idx].gatts_cb(event, gatts_if, param);
                }
            }
        }
    } while (0);
}

int ssv_hal_ble_gatts_init(void)
{
	int ret = 0;

    g_gatts_eg = xEventGroupCreate();

	if (g_gatts_eg == NULL)
        SSV_LOGE(SSV_HAL_GATTS, "%s create group event fail", __FUNCTION__);


    ret = ssv_ble_gatts_register_callback(gatts_event_handler);
    if (ret){
        SSV_LOGE(SSV_HAL_GATTS, "gatts register error, error code = %x", ret);
        return ret;
    }

    ret = ssv_ble_gatts_app_register(GATTS_PROFILE_A_APP_ID);
    if (ret){
        SSV_LOGE(SSV_HAL_GATTS, "gatts app register error, error code = %x", ret);
        return ret;
    }
	return ret;
}

int ssv_hal_ble_gatts_set_profile_cb(
    ssv_hal_ble_gatts_profile_event_handler_callback_t profile_cb)
{
	int ret = -1;

	if (profile_cb == NULL) {
        SSV_LOGE(SSV_HAL_GATTS, "%s profile_cb is NULL", __FUNCTION__);
		return ret;
    }

	ssv_ble_gatts_profile_event_handler_cb = profile_cb;
	return 0;

}

int ssv_hal_ble_gatts_create_service_by_db(
	ssv_gatts_attr_db_t *gatts_attr_db,	uint8_t max_nb_attr,
	uint16_t *out_handle)
{
    ssv_err_t api_ret = SSV_FAIL;

	if (gl_gatts_profile_tab[GATTS_PROFILE_A_APP_ID].gatts_if != SSV_GATT_IF_NONE) {
        ssv_api_gatts_event_clear_bit(SSV_API_GATTS_CREATE_ATT_ATB);
		api_ret = ssv_ble_gatts_create_attr_tab(
			gatts_attr_db, gl_gatts_profile_tab[GATTS_PROFILE_A_APP_ID].gatts_if,
			max_nb_attr, SVC_INST_ID);

        ssv_api_gatts_wait_event( SSV_API_GATTS_CREATE_ATT_ATB,
            "ssv_ble_gatts_create_attr_tab timeout\n");
        if(api_ret)
            printf("!!!ssv_api_gatts_eventg_clear_bit set fail %d\n", api_ret);

		if (out_handle)
			(*out_handle) = g_service_base_handle;
	} else
		printf("!!!ssv_ble_gatts_create_attr_tab gatts_if %d\n",
			gl_gatts_profile_tab[GATTS_PROFILE_A_APP_ID].gatts_if);

	return api_ret;
}

uint16_t ssv_hal_ble_gatts_get_mut(void)
{
    printf("%s %d\n", __FUNCTION__, g_gatts_mtu);
    return g_gatts_mtu;
}

uint16_t ssv_hal_ble_gatts_send_indication(uint16_t attrib_offset, uint8_t *data, uint16_t len, bool need_confirm)
{
    ssv_err_t ret = 0;
    printf("%s attrib_offset %d, len %d, need_confirm %d\n", __FUNCTION__, attrib_offset, len, need_confirm);

    ssv_ble_gatts_send_indicate(gl_gatts_profile_tab[GATTS_PROFILE_A_APP_ID].gatts_if,
        gl_gatts_profile_tab[GATTS_PROFILE_A_APP_ID].conn_id, attrib_offset, len, data, need_confirm);
    return ret;
}
