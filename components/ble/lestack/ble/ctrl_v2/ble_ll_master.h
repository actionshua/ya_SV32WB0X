#ifndef _BLE_LL_MASTER_H_
#define _BLE_LL_MASTER_H_

#include "ble/ctrl_v2/ble_ll_op.h"
#include "ble/ctrl_v2/ble_ll_security.h"
#include "ble/ctrl_v2/ble_ll_master_common.h"


/**
 *
 */
u8  ble_ll_master_busy(u8 conn_id);

s16 ble_llcp_master_id(u8 conn_id, ble_ll_op_un op);
/**
 *
 */
s16 ble_ll_master_reset();

/**
 *
 */
//void ble_ll_master_read_chmap(ble_datach_map_st* ch_map);
void ble_ll_master_read_chmap(u8 conn_id, ble_datach_map_st* chmap);

/**
 * get stored anchor_profile of master
 *
 */
void ble_ll_master_read_anchor_profile(u8 conn_id, ble_ll_anchor_profile_st* anchor_profile);

/**
 * dump master info
 *
 */
void ble_ll_master_info_dump();
void ble_ll_master_quality();

/**
 *
 */
//s16 ble_ll_master(ble_ll_op_un op);
s16 ble_ll_master(u8 conn_id, ble_ll_op_un op);

u8  ble_ll_master_get_idle_master_id();
void ble_ll_init_master_info();
u8 ble_ll_master_read_rssi(u8 conn_id);
ble_ll_peer_info_st* ble_ll_master_read_peer_info(u8 conn_id);

static inline s16 ble_ll_master_cmd_task_connect(u8 conn_id, const ble_ll_pdu_st* conn_req, ble_ll_clock_time_st conn_req_tref) {

    ble_ll_op_un op = {
        .cmd.task.connect = {
            .type_w         = BLE_LL_CMD_TASK_TYPE(BLE_LL_CMD_TASK_CODE_CONNECT),
            .conn_req       = conn_req,
            .conn_req_tref  = conn_req_tref,
        },
    };
    return ble_ll_master(conn_id, op);
};

void ble_ll_master_read_data_length_info(u8 conn_id, ble_data_length_st *info);
void ble_ll_master_write_encrypt_data(u8 conn_id, u8* random_number, u16 encrypted_diversifier);

#endif // _BLE_LL_MASTER_H_

