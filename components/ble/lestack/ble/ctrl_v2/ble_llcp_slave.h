#ifndef _BLE_LLCP_SLAVE_H_
#define _BLE_LLCP_SLAVE_H_

#include "ble/ctrl_v2/ble_llcp.h"
#include "ble/ctrl_v2/ble_llcp_slave.h"

s16 ble_llcp_slave(ble_ll_op_un op);
s16 ble_llcp_slave_reset();
void ble_llcp_slave_check_data_length (ble_data_length_st *dataleninfo);
s16 ble_llcp_slave_latch_data_length (const ble_ll_pdu_st* cpdu,
    ble_data_length_st *dataleninfo);

static inline s16 ble_llcp_slave_cmd_task_disconnect() {

    ble_ll_op_un op = {
        .cmd.task.disconnect = {
            .type_w = BLE_LL_CMD_TASK_TYPE(BLE_LL_CMD_TASK_CODE_DISCONNECT),
        },
    };
    return ble_llcp_slave(op);
};

static inline s16 ble_llcp_slave_cmd_task_cpdu_received (const ble_ll_pdu_st* cpdu) {

    ble_ll_op_un op = {
        .cmd.task.cpdu_received = {
            .type_w     = BLE_LL_CMD_TASK_TYPE(BLE_LL_CMD_TASK_CODE_CPDU_RECEIVED),
            .cpdu_op    = cpdu->pld[BLE_LLCP_PLD_IDX_OP],
            .cpdu       = cpdu,
        },
    };
    return ble_llcp_slave(op);
};

static inline s16 ble_llcp_slave_cmd_task_update_timing_complete() {

    ble_ll_op_un op = {
        .cmd.task.update_timing_complete = {
            .type_w     = BLE_LL_CMD_TASK_TYPE(BLE_LL_CMD_TASK_CODE_UPDATE_TIMING_COMPLETE),
        },
    };
    return ble_llcp_slave(op);
}

static inline s16 ble_llcp_slave_cmd_task_update_ch_map_complete() {

    ble_ll_op_un op = {
        .cmd.task.update_ch_map_complete = {
            .type_w     = BLE_LL_CMD_TASK_TYPE(BLE_LL_CMD_TASK_CODE_UPDATE_CH_MAP_COMPLETE),
        },
    };
    return ble_llcp_slave(op);
}


#endif
