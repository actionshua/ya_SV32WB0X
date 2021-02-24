#ifndef _BLE_LL_SLAVE_H_
#define _BLE_LL_SLAVE_H_

#include "ble/ctrl_v2/ble_ll_op.h"
#include "ble/ctrl_v2/ble_ll_security.h"

/**
 *
 */
u8  ble_ll_slave_busy();

/**
 *
 */
s16 ble_ll_slave_reset();

/**
 *
 */
void ble_ll_slave_read_chmap(ble_datach_map_st* ch_map);

/**
 * get stored anchor_profile of slave
 *
 */
void ble_ll_slave_read_anchor_profile(ble_ll_anchor_profile_st* anchor_profile);

void ble_ll_slave_read_data_length_info(ble_data_length_st *info);

/**
 * dump slave info
 *
 */
void ble_ll_slave_info_dump();
void ble_ll_slave_quality();

/**
 *
 */
s16 ble_ll_slave(ble_ll_op_un op);

/**
 *
 */
void ble_ll_slave_subrate(u8 enable, u8 minimum_tx_latency);

static inline s16 ble_ll_slave_cmd_task_connect(const ble_ll_pdu_st* conn_req, ble_ll_clock_time_st conn_req_tref) {

    ble_ll_op_un op = {
        .cmd.task.connect = {
            .type_w         = BLE_LL_CMD_TASK_TYPE(BLE_LL_CMD_TASK_CODE_CONNECT),
            .conn_req       = conn_req,
            .conn_req_tref  = conn_req_tref,
        },
    };
    return ble_ll_slave(op);
};

/** ##############################################
 * subrate lock: for llcp
 * ############################################### */
extern NV_DATA u8 g_ble_ll_slave_subrate_lock_llcp_own_proc;
extern NV_DATA u8 g_ble_ll_slave_subrate_lock_llcp_peer_proc;

/** ##############################################
 * security storage
 * ############################################### */
extern NV_DATA ble_ll_aes_ccm_sk_st g_ble_slave_aes_ccm_sk;

#endif // _BLE_LL_SLAVE_H_

