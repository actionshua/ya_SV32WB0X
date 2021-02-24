#ifndef _BLE_LLCP_H_
#define _BLE_LLCP_H_

#include "ble/ctrl_v2/ble_ll_op.h"

/**
 * format (OP)
 *
 */
#define BLE_LLCP_OP_SIZE    1
#define BLE_LLCP_PLD_IDX_OP 0

#define BLE_LLCP_OP_CONN_UPDATE_REQ         0x00 /* LL_CONNECTION_UPDATE_IND */
#define BLE_LLCP_OP_CH_MAP_REQ              0x01 /* LL_CHANNEL_MAP_IND */
#define BLE_LLCP_OP_TERMINATE_IND           0x02
#define BLE_LLCP_OP_ENC_REQ                 0x03
#define BLE_LLCP_OP_ENC_RSP                 0x04
#define BLE_LLCP_OP_START_ENC_REQ           0x05
#define BLE_LLCP_OP_START_ENC_RSP           0x06
#define BLE_LLCP_OP_UNKNOWN_RSP             0x07
#define BLE_LLCP_OP_FEATURE_REQ             0x08
#define BLE_LLCP_OP_FEATURE_RSP             0x09
#define BLE_LLCP_OP_PAUSE_ENC_REQ           0x0a
#define BLE_LLCP_OP_PAUSE_ENC_RSP           0x0b
#define BLE_LLCP_OP_VERSION_IND             0x0c
#define BLE_LLCP_OP_REJECT_IND              0x0d
#define BLE_LLCP_OP_LENGTH_REQ              0x14
#define BLE_LLCP_OP_LENGTH_RSP              0x15
#define BLE_LLCP_OP_INVALID                 0xff

#define BLE_LLCP_OP_BITFIELD(OP)  ((1) << OP)

/**
 * funtion
 */
typedef enum {
    BLE_LLCP_ACTION_CPDU_ACCEPTED = 1,
}   BLE_LLCP_ACTION;

/*s16 ble_llcp_slave(ble_ll_op_un op);
s16 ble_llcp_slave_reset();*/

/**
 * latch information from cpdu
 *
 */
s16 ble_llcp_latch_update_timing_param (const ble_ll_pdu_st* cpdu,
    BLE_LL_INSTANT*                 action_instant,
    ble_ll_conn_window_st*          anchor_window,
    ble_ll_conn_timing_param_st*    param);

s16 ble_llcp_latch_update_ch_map_param (const ble_ll_pdu_st* cpdu,
    BLE_LL_INSTANT*     action_instant,
    ble_datach_map_st*  param);

s16 ble_llcp_latch_err_code_peer (const ble_ll_pdu_st* cpdu,
    u8* err_code);

/**
 * constant: timing
 *  -timing is handled by fsm task
 *
 */
#define BLE_LLCP_TOUT   ((BLE_LL_US)40000000)

/*static inline s16 ble_llcp_slave_cmd_task_disconnect() {

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
}*/
#endif  // _BLE_LLCP_H_
