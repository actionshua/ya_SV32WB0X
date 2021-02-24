#ifndef _BLE_LL_OP_H_
#define _BLE_LL_OP_H_

#include "ssv_types.h"
#include "ble/hci_lib.h"
#include "ble/ctrl_v2/ble_ll.h"
#include "ble/ctrl_v2/ble_ll_if.h"

typedef struct ble_ll_op_general {

    union {
        u32 param0;
        //
        u32 type_w;
        u8  type[4];
        // cmd input
        struct {
            u32 code        :16;
            u32 code_space  :8;
            u32 ind         :8;
        } cmd_type;

        // evt input
        struct {
            u32 code        :16;
            u32 code_space  :8;
            u32 ind         :8;
        } evt_type;

        // acl
        struct {
            u32 conn_hdl    :16;
            u32 ind_        :16;
        } acl_type;
    };
    u32 param1;
    u32 param2;
    u32 param3;

} ble_ll_op_general_st;

#define BLE_LL_CMD_IND  0x01
#define BLE_LL_ACL_IND  0x02
#define BLE_LL_EVT_IND  0x04

/* ########################################
 * cmd/evt op space define
 * ######################################## */
typedef enum {
    BLE_LL_CMD_CODE_SPACE_HCI = 0,
    BLE_LL_CMD_CODE_SPACE_TASK,
}   BLE_LL_CMD_CODE_SPACE;
#define BLE_LL_CMD_IND_(_CODE_SPACE_) ((BLE_LL_CMD_IND << 8) | (_CODE_SPACE_))

typedef enum {
    BLE_LL_EVT_CODE_SPACE_HCI = 0,
    BLE_LL_EVT_CODE_SPACE_RT,
    BLE_LL_EVT_CODE_SPACE_LLCP,
}   BLE_LL_EVT_CODE_SPACE;
#define BLE_LL_EVT_IND_(_CODE_SPACE_) ((BLE_LL_EVT_IND << 8) | (_CODE_SPACE_))

/* ########################################
 * cmd code define
 * ######################################## */
/**
 * task(hci) cmd code
 *  - cmd without param:
 *      + read_remote_version_information
 *      + reset
 *
 */
#define BLE_LL_CMD_HCI_CODE_DISCONNECT BT_HCI_CMD_OPCODE(BT_HCI_CMD_OGF_LINK_CONTROL, \
             BT_HCI_CMD_OCF_DISCONNECT)
#define BLE_LL_CMD_HCI_CODE_READ_REMOTE_VERSION_INFORMATION BT_HCI_CMD_OPCODE(BT_HCI_CMD_OGF_LINK_CONTROL, \
             BT_HCI_CMD_OCF_READ_REMOTE_VERSION_INFORMATION)

#define BLE_LL_CMD_HCI_CODE_RESET BT_HCI_CMD_OPCODE(BT_HCI_CMD_OGF_CONTROL_BASEBAND, \
             BT_HCI_CMD_OCF_RESET)

#define BLE_LL_CMD_HCI_CODE_LE_SET_ADVERTISE_ENABLE BT_HCI_CMD_OPCODE(BT_HCI_CMD_OGF_LE_CONTROLLER, \
             BT_HCI_CMD_OCF_LE_SET_ADVERTISE_ENABLE)
#define BLE_LL_CMD_HCI_CODE_LE_SET_SCAN_ENABLE      BT_HCI_CMD_OPCODE(BT_HCI_CMD_OGF_LE_CONTROLLER, \
             BT_HCI_CMD_OCF_LE_SET_SCAN_ENABLE)
#define BLE_LL_CMD_HCI_CODE_LE_LONG_TERM_KEY_REQUEST_REPLY BT_HCI_CMD_OPCODE(BT_HCI_CMD_OGF_LE_CONTROLLER, \
             BT_HCI_CMD_OCF_LE_LONG_TERM_KEY_REQUEST_REPLY)
#define BLE_LL_CMD_HCI_CODE_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY BT_HCI_CMD_OPCODE(BT_HCI_CMD_OGF_LE_CONTROLLER, \
             BT_HCI_CMD_OCF_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY)

#define BLE_LL_CMD_HCI_CODE_LE_CREATE_CONNECTION    BT_HCI_CMD_OPCODE(BT_HCI_CMD_OGF_LE_CONTROLLER, \
             BT_HCI_CMD_OCF_LE_CREATE_CONNECTION)
#define BLE_LL_CMD_HCI_CODE_LE_CONNECTION_UPDATE    BT_HCI_CMD_OPCODE(BT_HCI_CMD_OGF_LE_CONTROLLER, \
             BT_HCI_CMD_OCF_LE_CONNECTION_UPDATE)

#define BLE_LL_CMD_HCI_CODE_LE_READ_REMOTE_USED_FEATURES BT_HCI_CMD_OPCODE(BT_HCI_CMD_OGF_LE_CONTROLLER, \
             BT_HCI_CMD_OCF_LE_READ_REMOTE_USED_FEATURES)

#define BLE_LL_CMD_HCI_CODE_LE_SET_HOST_CHANNEL_CLASSIFICATION BT_HCI_CMD_OPCODE(BT_HCI_CMD_OGF_LE_CONTROLLER, \
             BT_HCI_CMD_OCF_LE_SET_HOST_CHANNEL_CLASSIFICATION)

#define BLE_LL_CMD_HCI_CODE_LE_START_ENCRYPTION    BT_HCI_CMD_OPCODE(BT_HCI_CMD_OGF_LE_CONTROLLER, \
             BT_HCI_CMD_OCF_LE_START_ENCRYPTION)

#define BLE_LL_CMD_HCI_CODE_LE_CREATE_CONNECTION_CANCEL    BT_HCI_CMD_OPCODE(BT_HCI_CMD_OGF_LE_CONTROLLER, \
             BT_HCI_CMD_OCF_LE_CREATE_CONNECTION_CANCEL)
             
#define BLE_LL_CMD_HCI_CODE_LE_SET_DATA_LENGTH    BT_HCI_CMD_OPCODE(BT_HCI_CMD_OGF_LE_CONTROLLER, \
             BT_HCI_CMD_OCF_LE_SET_DATA_LENGTH)
             
#define BLE_LL_CMD_HCI_TYPE(CODE) (((BLE_LL_CMD_IND) << 24) | ((BLE_LL_CMD_CODE_SPACE_HCI) << 16) | (CODE)) 

typedef struct ble_ll_cmd_hci_general {

    union {
        u32 param0;
        u32 type_w;
        struct {
            u32 code:16;    // cmd opcode
            u32 ind_:16;    // fixed const: {BLE_LL_CMD_IND, BLE_LL_CMD_CODE_SPACE_HCI}
        } type;
    };
    u32 param1;
    u32 param2;
    u32 param3;

} ble_ll_cmd_hci_general_st;

typedef struct ble_ll_cmd_hci_disconnect {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32 param1;
        u32 reason: 8;
    };
    u32 param2;
    u32 param3;

} ble_ll_cmd_hci_disconnect_st;

typedef struct ble_ll_cmd_hci_le_set_advertise_enable {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32 param1;
        u32 enable;
    };
    u32 param2;
    u32 param3;

} ble_ll_cmd_hci_le_set_advertise_enable_st;

typedef struct ble_ll_cmd_hci_le_set_scan_enable {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32 param1;
        u32 le_scan_enable;
    };
    union {
        u32 param2;
        u32 filter_duplicates;
    };
    u32 param3;

} ble_ll_cmd_hci_le_set_scan_enable_st;

typedef struct ble_ll_cmd_hci_le_long_term_key_reply {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32                         param1;
        const ble_ll_cypher_key_un* long_term_key;
    };
    u32 param2;
    u32 param3;

} ble_ll_cmd_hci_le_long_term_key_reply_st;

typedef struct ble_ll_cmd_hci_le_long_term_key_negative_reply {

    union {
        u32 param0;
        u32 type_w;
    };
    u32 param1;
    u32 param2;
    u32 param3;

} ble_ll_cmd_hci_le_long_term_key_negative_reply_st;
typedef struct ble_ll_cmd_hci_le_create_connection {

    union {
        u32 param0;
        u32 type_w;
    };
    u32 param1;
    u32 param2;
    u32 param3;

} ble_ll_cmd_hci_le_create_connection_st;

typedef struct ble_ll_cmd_hci_le_start_encryption {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32                         param1;
        const ble_ll_cypher_key_un* long_term_key;
    };
    u32 param2;
    u32 param3;

} ble_ll_cmd_hci_le_start_encryption_st;


typedef struct ble_ll_cmd_hci_le_connection_update {

    union {
        u32 param0;
        u32 type_w;
    };
    u32 param1;
    u32 param2;
    u32 param3;

} ble_ll_cmd_hci_le_connection_update_st;

typedef struct ble_ll_cmd_hci_le_set_host_ch_classification {

    union {
        u32 param0;
        u32 type_w;
    };
    u32 param1;
    u32 param2;
    u32 param3;

} ble_ll_cmd_hci_le_set_host_ch_classification_st;
typedef struct ble_ll_cmd_hci_le_connection_cancel {

    union {
        u32 param0;
        u32 type_w;
    };
    u32 param1;
    u32 param2;
    u32 param3;

} ble_ll_cmd_hci_le_create_connection_cancel_st;

typedef struct ble_ll_cmd_hci_set_data_length {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32 param1;
        u32 txocts:16;
        u32 txtime:16;
    };
    u32 param2;
    u32 param3;

} ble_ll_cmd_hci_set_data_length_st;

typedef union ble_ll_cmd_hci {

    ble_ll_cmd_hci_general_st       general;
    ble_ll_cmd_hci_disconnect_st    disconnect;
    //
    ble_ll_cmd_hci_le_set_advertise_enable_st           le_set_advertise_enable;
    ble_ll_cmd_hci_le_set_scan_enable_st                le_set_scan_enable;
    ble_ll_cmd_hci_le_long_term_key_reply_st            le_long_term_key_reply;
    ble_ll_cmd_hci_le_long_term_key_negative_reply_st   le_long_term_key_negative_reply;
    //master
    ble_ll_cmd_hci_le_create_connection_st              le_create_connection;
    ble_ll_cmd_hci_le_start_encryption_st               le_start_encryption;
    ble_ll_cmd_hci_le_connection_update_st              le_connection_update;
    ble_ll_cmd_hci_le_set_host_ch_classification_st     le_set_host_ch_classification;
    ble_ll_cmd_hci_le_create_connection_cancel_st       le_create_connection_cancel;
    
    ble_ll_cmd_hci_set_data_length_st                   le_set_data_length;
} ble_ll_cmd_hci_un;

/**
 * task(fsm) cmd code
 *
 */
typedef enum {
    BLE_LL_CMD_TASK_CODE_CONNECT = 1,               // expect issued by ADV/INIT fsm
    BLE_LL_CMD_TASK_CODE_DISCONNECT,                // expect issued by slave/master fsm
    BLE_LL_CMD_TASK_CODE_CPDU_RECEIVED,
    BLE_LL_CMD_TASK_CODE_UPDATE_TIMING_COMPLETE,
    BLE_LL_CMD_TASK_CODE_UPDATE_CH_MAP_COMPLETE,
    BLE_LL_CMD_TASK_CODE_AUTONOMOUS_VERSION_EXCHANGE,
    BLE_LL_CMD_TASK_CODE_DATA_LENGTH_CHANGE,
    BLE_LL_CMD_TASK_CODE_NOW,
    BLE_LL_CMD_TASK_CODE_DO_TERMINATE,
}   BLE_LL_CMD_TASK_CODE;

#define BLE_LL_CMD_TASK_TYPE(CODE) (((BLE_LL_CMD_IND) << 24) | ((BLE_LL_CMD_CODE_SPACE_TASK) << 16) | (CODE))

typedef struct ble_ll_cmd_task_general {

    union {
        u32 param0;
        u32 type_w;
        struct {
            u32 code:16;    // cmd opcode
            u32 ind_:16;    // fixed const: {BLE_LL_CMD_IND, BLE_LL_CMD_CODE_SPACE_TASK}
        } cmd_type;
    };
    u32 param1;
    u32 param2;
    u32 param3;

} ble_ll_cmd_task_general_st;

typedef struct ble_ll_cmd_task_connect {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32 param1;
        const ble_ll_pdu_st* conn_req;
    };
    union {
        u32 param2;
        ble_ll_clock_time_st conn_req_tref;
    };

    u32 param3;

} ble_ll_cmd_task_connect_st;

typedef struct ble_ll_cmd_task_disconnect {

    union {
        u32 param0;
        u32 type_w;
    };
    u32 param1;
    u32 param2;
    u32 param3;

} ble_ll_cmd_task_disconnect_st;

typedef struct ble_ll_cmd_task_cpdu_received {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32 param1;
        struct {
            u8  cpdu_op;
        };
    };
    union {
        u32                     param2;
        const ble_ll_pdu_st*    cpdu;
    };
    u32 param3;

} ble_ll_cmd_task_cpdu_received_st;

typedef struct ble_ll_cmd_task_update_timing_complete {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32 param1;
        //
        const ble_ll_connection_timing_raw_parameter_st* raw_param;
    };
    u32 param2;
    u32 param3;

} ble_ll_cmd_task_update_timing_complete_st;

typedef struct ble_ll_cmd_task_update_ch_map_complete {

    union {
        u32 param0;
        u32 type_w;
    };
    u32 param1;
    u32 param2;
    u32 param3;

} ble_ll_cmd_task_update_ch_map_complete_st;

typedef struct ble_ll_cmd_task_data_length_change {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32 param1;
        u32 txocts:16;
        u32 txtime:16;
    };
    u32 param2;
    u32 param3;

} ble_ll_cmd_task_data_length_change_st;

typedef struct ble_ll_cmd_task_autonomous_version_exchange {

    union {
        u32 param0;
        u32 type_w;
    };
    u32 param1;
    u32 param2;
    u32 param3;

} ble_ll_cmd_task_autonomous_version_exchange_st;

typedef struct ble_ll_cmd_task_now {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32                     param1;
        ble_ll_clock_time_st    now;
    };
    u32 param2;
    u32 param3;

} ble_ll_cmd_task_now_st;

typedef struct ble_ll_cmd_task_do_terminate {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32 param1;
        struct {
            u8  reason;
        };
    };
    u32 param2;
    u32 param3;

} ble_ll_cmd_task_do_terminate_st;

typedef union ble_ll_cmd_task {

    ble_ll_cmd_task_general_st                  general;
    ble_ll_cmd_task_connect_st                  connect;
    ble_ll_cmd_task_disconnect_st               disconnect;
    ble_ll_cmd_task_cpdu_received_st            cpdu_received;
    ble_ll_cmd_task_update_timing_complete_st   update_timing_complete;
    ble_ll_cmd_task_update_ch_map_complete_st   update_ch_map_complete;
    ble_ll_cmd_task_data_length_change_st       data_length_change;
    ble_ll_cmd_task_now_st                      now;
    ble_ll_cmd_task_do_terminate_st             do_terminate;

} ble_ll_cmd_task_un;

typedef union ble_ll_cmd {

    ble_ll_cmd_hci_un   hci;
    ble_ll_cmd_task_un  task;

} ble_ll_cmd_un;

/* ########################################
 * evt: hci
 * ######################################## */
#define BLE_LL_EVT_HCI_TYPE(EVT_CODE, SUBEVT_CODE) \
    (((BLE_LL_EVT_IND) << 24) | ((BLE_LL_EVT_CODE_SPACE_HCI) << 16) | (BLE_LL_EVT_CODE(EVT_CODE, SUBEVT_CODE))) 

/* ########################################
 * evt code define
 * ######################################## */
/**
 * rt evt code [1:0]
 *  - code[1]: conn_id
 *  - code[0]: op0
 *
 */
#define BLE_LL_EVT_RT_CODE(CONN_ID, CODE0) (((CONN_ID) << 8) | (CODE0))
typedef enum {
    BLE_LL_EVT_RT_CODE0_AIR_EVT_EARLY_NOTIFY = 1,   // from LL_4_IRQHandler
    BLE_LL_EVT_RT_CODE0_AIR_EVT_END,                // from LL_3_IRQHandler
    BLE_LL_EVT_RT_CODE0_AIR_EVT_SKIP,               // from LL_4_IRQHandler
}   BLE_LL_EVT_RT_CODE0;

#define BLE_LL_EVT_RT_TYPE(CONN_ID, CODE0) \
    U32_BUILD((CODE0), (CONN_ID), (BLE_LL_EVT_CODE_SPACE_RT), (BLE_LL_EVT_IND))

/**
 * llcp evt code[1:0]
 *  - code[1]: conn_id
 *  - code[0]: op0
 *
 */
#define BLE_LL_EVT_CODE_LLCP(CONN_ID, CODE0) (((CONN_ID) << 8) | (CODE0))
typedef enum {
    BLE_LL_EVT_LLCP_CODE0_CPDU_2SEND = 1,
    BLE_LL_EVT_LLCP_CODE0_TOUT,
}   BLE_LL_EVT_LLCP_CODE0;

#define BLE_LL_EVT_LLCP_TYPE(CONN_ID, CODE0) \
    U32_BUILD((CODE0), (CONN_ID), (BLE_LL_EVT_CODE_SPACE_LLCP), (BLE_LL_EVT_IND))

/* ########################################
 * evt: rt
 * ######################################## */
/**
 * evt_rt: air_evt_end
 *
 */
typedef enum {
    BLE_LL_EVT_RT_AIR_EVT_END_HARD = 1,
    BLE_LL_EVT_RT_AIR_EVT_END_ADV_SOFT,
    BLE_LL_EVT_RT_AIR_EVT_END_DATA_SOFT,
}   BLE_LL_EVT_RT_AIR_EVT_END_REASON;

typedef struct ble_ll_evt_rt_general {

    union {
        u32 param0;
        u32 type_w;
        struct {
            u32 code:16;    // {conn_id, BLE_LL_EVT_OP0_RT_AIR_EVT_END}
            u32 ind_:16;    // fixed const: {BLE_LL_EVT_IND, BLE_LL_EVT_CODE_SPACE_RT}
        } type;
    };
    u32 param1;
    u32 param2;
    u32 param3;

} ble_ll_evt_rt_general_st;

/**
 * evt_rt: air_evt_early_notify
 *
 */
typedef struct ble_ll_evt_rt_air_evt_early_notify {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32                     param1;
        ble_ll_clock_time_st    anchor;
    };
    u32 param2;
    u32 param3;

} ble_ll_evt_rt_air_evt_early_notify_st;

typedef struct ble_ll_evt_rt_air_evt_end {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32 param1;
        struct {
            ble_ll_clock_time_st end_time;
        };
    };
    union {
        u32 param2;
        struct {
            u8  reason;
            struct {
                u8  tx_action_cnt;
                u8  rx_action_cnt;
                ///
                u8  rx_vld_latch:1;
                u8  data_md_own :1;
                u8  data_md     :1;
                u8  tx_scheduled:1;
                u8  rx_scheduled:1;
                u8  rx_crc_error:1; // for master to indicate valid_instant
            } log;
        };
    };
    union {
        u32 param3;
        struct {
            u32 phy_rssi            :8;
            u32 phy_access_time     :20;
            u32                     :2;
            u32 rssi_vld            :1;
            u32 phy_access_time_vld :1;
        } first_rx_log;
    };

} ble_ll_evt_rt_air_evt_end_st;

typedef enum {
    BLE_LL_EVT_RT_AIR_EVT_SKIP_COL = 1,
    BLE_LL_EVT_RT_AIR_EVT_SKIP_EXPIRE,
}   BLE_LL_EVT_RT_AIR_EVT_SKIP_REASON;

typedef struct ble_ll_evt_rt_air_evt_skip {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32 param1;
        struct {
            u8  reason;
        };
    };
    u32 param2;
    union {
        u32                     param3;
        ble_ll_clock_time_st    anchor;
    };

} ble_ll_evt_rt_air_evt_skip_st;

typedef union ble_ll_evt_rt {

    ble_ll_evt_rt_general_st                general;
    ble_ll_evt_rt_air_evt_end_st            air_evt_end;
    ble_ll_evt_rt_air_evt_early_notify_st   air_evt_early_notify;
    ble_ll_evt_rt_air_evt_skip_st           air_evt_skip;

} ble_ll_evt_rt_un;

/* ########################################
 * evt: llcp
 * ######################################## */
typedef struct ble_ll_evt_llcp_cpdu_2send {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32 param1;
        struct {
            u8  cpdu_op;
        };
    };
    union {
        u32             param2;
        ble_ll_pdu_st*  cpdu;
    };
    u32 param3;

} ble_ll_evt_llcp_cpdu_2send_st;

typedef struct ble_ll_evt_llcp_tout {

    union {
        u32 param0;
        u32 type_w;
    };
    union {
        u32 param1;
        struct {
            u8  proc_id;
        };
    };
    u32 param2;
    u32 param3;

} ble_ll_evt_llcp_tout_st;

typedef union {

    ble_ll_evt_llcp_cpdu_2send_st   cpdu_2send;
    ble_ll_evt_llcp_tout_st         tout;

} ble_ll_evt_llcp_un;

/**
 * evt:
 *
 */
typedef union ble_ll_evt {

    ble_ll_evt_hci_un   hci;
    ble_ll_evt_rt_un    rt;
    ble_ll_evt_llcp_un  llcp;

} ble_ll_evt_un;

/**
 * op
 */
typedef union ble_ll_op {

    ble_ll_op_general_st    general;
    ble_ll_cmd_un           cmd;
    ble_ll_evt_un           evt;
    ble_ll_acl_st           acl;

} ble_ll_op_un ;

extern const ble_ll_op_un ble_ll_op_null;   // reside in ble_ll.c


/* ########################################
 * acl
 * ######################################## */
#define BLE_LL_ACL_TYPE(CONN_HDL) (((BLE_LL_ACL_IND) << 24) | (CONN_HDL))

#endif // _BLE_LL_OP_H_
