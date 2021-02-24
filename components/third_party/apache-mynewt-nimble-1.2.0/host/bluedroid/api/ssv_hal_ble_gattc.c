#include <bsp.h>
#include "ssv_hal_ble_common.h"
#include "ssv_hal_ble_gattc.h"
#include "ssv_gattc_api.h"
#include "ssv_gatt_common_api.h"
#include "ssv_log.h"


#if BLE_GATTC_EN
#define SSV_HAL_GATTC "SSV_HAL_GATTC"

EventGroupHandle_t g_gattc_eg = NULL;/*eg is event group*/
uint32_t g_gattc_value = 0;

struct gattc_profile_inst {
    ssv_gattc_cb_t gattc_cb;
    uint16_t gattc_if;
    uint16_t app_id;
    uint16_t conn_id;
    uint16_t service_start_handle;
    uint16_t service_end_handle;
    uint16_t char_handle;
    ssv_bd_addr_t remote_bda;
};

ssv_hal_ble_gattc_profile_event_handler_callback_t hal_gattc_profile_event_cb = NULL;

void ssv_hal_ble_gattc_set_profile_cb(ssv_hal_ble_gattc_profile_event_handler_callback_t cb)
{
    hal_gattc_profile_event_cb = cb;
}

static void ssv_hal_gattc_profile_event_handler(ssv_gattc_cb_event_t event, ssv_gatt_if_t gattc_if, ssv_ble_gattc_cb_param_t *param)
{
    ssv_ble_gattc_cb_param_t *p_data = (ssv_ble_gattc_cb_param_t *)param;
    //SSV_LOGI(SSV_HAL_GATTC, "%s event %d, gattc_if %d", __FUNCTION__, event, gattc_if);
    switch (event) {
        case SSV_GATTC_OPEN_EVT:
            ssv_api_gattc_event_set(SSV_API_GATTC_OPEN_EVT);
            break;

        case SSV_GATTC_CONNECT_EVT:
            break;

        case SSV_GATTC_WRITE_CHAR_EVT:
            //printf("%s SSV_GATTC_WRITE_CHAR_EVT\n", __FUNCTION__);
            ssv_api_gattc_event_set(SSV_API_GATTC_WRITE_CHAR_EVT);
            break;

        case SSV_GATTC_NOTIFY_EVT:
            //SSV_LOGI(SSV_HAL_GATTC, "%s SSV_GATTC_NOTIFY_EVT", __FUNCTION__);
            break;

        default:
            break;
    }

    if (hal_gattc_profile_event_cb)
        hal_gattc_profile_event_cb(event, gattc_if, param);
    else
        SSV_LOGE(SSV_HAL_GATTC, "hal_gattc_profile_event_cb is NULL");

}

/* One gatt-based profile one app_id and one gattc_if, this array will store the gattc_if returned by SSV_GATTS_REG_EVT */
struct gattc_profile_inst ssv_hal_gattc_gl_profile_tab[SSV_HAL_GATTC_PROFILE_NUM] = {
    [SSV_HAL_GATTC_PROFILE_A_APP_ID] = {
        .gattc_cb = ssv_hal_gattc_profile_event_handler,
        .gattc_if = SSV_GATT_IF_NONE,       /* Not get the gatt_if, so initial is SSV_GATT_IF_NONE */
    },
};

static void ssv_gattc_cb(ssv_gattc_cb_event_t event, ssv_gatt_if_t gattc_if, ssv_ble_gattc_cb_param_t *param)
{
	/* If event is register event, store the gattc_if for each profile */
    if (event == SSV_GATTC_REG_EVT) {
        if (param->reg.status == SSV_GATT_OK) {
            ssv_hal_gattc_gl_profile_tab[param->reg.app_id].gattc_if = gattc_if;
        } else {
            SSV_LOGI(SSV_HAL_GATTC, "reg app failed, app_id %04x, status %d",
                    param->reg.app_id,
                    param->reg.status);
            return;
        }
    }

    /* If the gattc_if equal to profile A, call profile A cb handler,
     * so here call each profile's callback */
    do {
        int idx;
        for (idx = 0; idx < SSV_HAL_GATTC_PROFILE_NUM; idx++) {
            if (gattc_if == SSV_GATT_IF_NONE || /* SSV_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
                    gattc_if == ssv_hal_gattc_gl_profile_tab[idx].gattc_if) {
                if (ssv_hal_gattc_gl_profile_tab[idx].gattc_cb) {
                    ssv_hal_gattc_gl_profile_tab[idx].gattc_cb(event, gattc_if, param);
                }
            }
        }
    } while (0);
}

int ssv_hal_ble_gattc_init()
{
	ssv_err_t ret = 0;

	//register the callback function to the gattc module
    ret = ssv_ble_gattc_register_callback(ssv_gattc_cb);
    if(ret){
        SSV_LOGE(SSV_HAL_GATTC, "%s gattc register failed, error code = %x\n", __func__, ret);
        return ret;
    }

	ret = ssv_ble_gattc_app_register(SSV_HAL_GATTC_PROFILE_A_APP_ID);
    if (ret){
        SSV_LOGE(SSV_HAL_GATTC, "%s gattc app register failed, error code = %x\n", __func__, ret);
    }

    g_gattc_eg = xEventGroupCreate();

    if (g_gattc_eg == NULL)
        SSV_LOGE(SSV_HAL_GATTC, "%s create group event fail", __FUNCTION__);

	return ret;
}

void ssv_api_gattc_event_set_by_evtntval(u32 event_val,u32 bit)
{
    BaseType_t val = 0;
    if(g_gattc_eg)
    {
        if(gOsFromISR)
            xEventGroupSetBitsFromISR(g_gattc_eg, bit, &val);
        else
            xEventGroupSetBits(g_gattc_eg, bit);

        SSV_API_SET_BIT(g_gattc_value, bit);
    }
}

void ssv_api_gattc_event_set(uint32_t bit)
{
    ssv_api_gattc_event_set_by_evtntval(g_gattc_value, bit);
}

void ssv_api_gattc_event_clear_bit(uint32_t bitval)
{
    SSV_API_CLEAR_BIT(g_gattc_value, bitval);
}

int ssv_api_gattc_wait_event(uint32_t bit, char *failmsg)
{
    int ret = 0;
    EventBits_t evtrlt;
	WAIT_API_EVENT(g_gattc_eg, bit, API_EVENT_WAIT_TIME,
        failmsg, SSV_HAL_GATTC);
	return ret;
}

int ssv_hal_ble_gattc_open(ssv_gatt_if_t gattc_if, ssv_bd_addr_t remote_bda,
    ssv_ble_addr_type_t remote_addr_type, bool is_direct)
{
    ssv_err_t ret = 0;

    SSV_LOGE(SSV_HAL_GATTC, "%s ssv_hal_ble_gattc_open %02x%02x%02x%02x%02x%02x",
        __FUNCTION__, remote_bda[0], remote_bda[1], remote_bda[2],
        remote_bda[3], remote_bda[4], remote_bda[5]);

    do {
        ssv_api_gattc_event_clear_bit(SSV_API_GATTC_OPEN_EVT);
        ssv_err_t open_ret = ssv_ble_gattc_open(ssv_hal_gattc_gl_profile_tab[SSV_HAL_GATTC_PROFILE_A_APP_ID].gattc_if, remote_bda,
        remote_addr_type, is_direct);
        CHECK_RESULT(open_ret, "ssv_ble_gattc_open fail");
        open_ret = ssv_api_gattc_wait_event( SSV_API_GATTC_OPEN_EVT,
            "ssv_ble_gattc_open SSV_API_GATTC_OPEN_EVT timeout\n");
        CHECK_RESULT(open_ret, "");
    } while (0);

    return ret;
}

#endif