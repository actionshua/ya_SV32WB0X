#ifndef _BLE_LLCP_MASTER_H_
#define _BLE_LLCP_MASTER_H_

#include "ble/ctrl_v2/ble_ll_op.h"
#include "ble/ctrl_v2/ble_ll_master_common.h"

s16 ble_llcp_master(ble_ll_master_info_st *master_info, ble_ll_op_un op);
s16 ble_llcp_master_reset();

/**
 * latch information from cpdu
 *
 */
s16 ble_llcp_master_latch_update_timing_param (const ble_ll_pdu_st* cpdu,
    BLE_LL_INSTANT*                 action_instant,
    ble_ll_conn_window_st*          anchor_window,
    ble_ll_conn_timing_param_st*    param);

s16 ble_llcp_master_latch_update_ch_map_param (const ble_ll_pdu_st* cpdu,
    BLE_LL_INSTANT*     action_instant,
    ble_datach_map_st*  param);

s16 ble_llcp_master_latch_err_code_peer (const ble_ll_pdu_st* cpdu,
    u8* err_code);

void ble_llcp_master_check_data_length (u8 conn_id, ble_data_length_st *dataleninfo);
s16 ble_llcp_master_latch_data_length (u8 conn_id, const ble_ll_pdu_st* cpdu,
    ble_data_length_st *dataleninfo);
/**
 * constant: timing
 *  -timing is handled by fsm task
 *
 */
#define BLE_LLCP_TOUT   ((BLE_LL_US)40000000)

#endif  // _BLE_LLCP_MASTER_H_
