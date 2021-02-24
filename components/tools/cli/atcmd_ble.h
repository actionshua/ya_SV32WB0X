#ifndef _ATCMD_BLE_H_
#define _ATCMD_BLE_H_
#include "atcmd.h"
#include "error.h"

#if BLE_GAP_ATCMD_EN
#define ATCMD_CUSTOM_SEGMENT_SIZE 40

#if BLE_GATTC_ATCMD_EN
#include "ssv_gattc_api.h"

#define ATCMD_GATTC_PROFILE_NUM      1
#define ATCMD_GATTC_PROFILE_A_APP_ID 0


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


#endif//end BLE_GATTC_ATCMD_EN

int At_ble_init(stParam *param);
int At_ble_start_adv(stParam *param);
int At_ble_stop_adv(stParam *param);

int At_ble_set_scan_params(stParam *param);
int At_ble_start_scan(stParam *param);
int At_ble_gattc_open(stParam *param);

int At_ble_add_service(stParam *param);
int At_ble_send_indication(stParam *param);
int At_ble_gattc_write_char(stParam *param);
int At_ble_disconnect(stParam *param);
#endif//BLE_GAP_ATCMD_EN

#endif  //_ATCMD_BLE_H_
