#ifndef _L2CAP_DEF_H_
#define _L2CAP_DEF_H_



#include "host_def.h"
#include "ble/ble_lib_v2.h"



#define L2CAP_SDU_LOG_SIZE                          (BLE_PDU_LOG_SIZE - 4)
#define L2CAP_SDU_START_PAYLOAD_SIZE                (BLE_L2CAP_PDU_PLD_SIZE)
#define L2CAP_SDU_CONTINUE_PAYLOAD_SIZE             (BLE_PDU_PLD_SIZE)

#define L2CAP_DIRECTION_TX                          0x00
#define L2CAP_DIRECTION_RX                          0x01

#define L2CAP_PRIORITY_SDU_NUM_MAX                  0x01

#define L2CAP_START_FRAGMENT_SIZE_MAX               23
#define L2CAP_CONTINUE_FRAGMENT_SIZE_MAX            27

#define L2CAP_START_FRAGMENT                        0x02
#define L2CAP_CONTINUE_FRAGMENT                     0x01

#define L2CAP_MAX_ACL_DATA                          23
#define L2CAP_LEN_HEADER_SIZE                       2
#define L2CAP_CID_HEADER_SIZE                       2
#define L2CAP_HEADER_SIZE                           (L2CAP_LEN_HEADER_SIZE + L2CAP_CID_HEADER_SIZE)

#define L2CAP_CID_OFFSET                            2
#define L2CAP_DATA_OFFSET                           4

#define L2CAP_INVALID_CONNECTION_HANDLE             0xFFFF

/// L2CAP fixed-channel type
#define L2CAP_ATT_CHANNEL                           0x0004
#define L2CAP_SIGNAL_CHANNEL                        0x0005
#define L2CAP_SM_CHANNEL                            0x0006

/// Dynamically allocated CID range
#define L2CAP_NULL_CID                              0x0000
#define L2CAP_DYNAMIC_CID_MIN                       0x0040
#define L2CAP_DYNAMIC_CID_MAX                       0x0048
#define L2CAP_INVALID_DYNAMIC_CID                   L2CAP_NULL_CID



typedef ble_pdu_st* (*alloc_pdu_func_t)(u8, u8);
typedef u8 (*free_pdu_func_t)(u8, ble_pdu_st *);
typedef u8 (*send_tx_pdu_func_t)(u16, ble_pdu_st *);



typedef enum
{
    L2CAP_RESULT_SUCCESS = ERR_HOST_SUCCESS,
    L2CAP_RESULT_FAIL = ERR_HOST_FAIL,
    L2CAP_RESULT_INVALID_OPERATION = ERR_HOST_INVALID_OPERATION,
    L2CAP_RESULT_INVALID_PARAM = ERR_HOST_INVALID_PARAM,
    L2CAP_RESULT_INSUFF_RESOURCE = ERR_HOST_INSUFF_RESOURCE,
    L2CAP_RESULT_INVALID_CONNECTION = ERR_HOST_INVALID_CONNECTION,

    L2CAP_RESULT_MIN = ERR_HOST_L2CAP,
    L2CAP_RESULT_SLQ_EMPTY,
    L2CAP_RESULT_MAX,

} L2CAP_RESULT;



typedef enum
{
    L2CAP_FRAME_TYPE_B,
    L2CAP_FRAME_TYPE_LE,

} L2CAP_FRAME_TYPE;



typedef enum
{
    L2CAP_SDU_TYPE_NORMAL,
    L2CAP_SDU_TYPE_PRIORITY,

} L2CAP_SDU_TYPE;



typedef enum
{
    L2CAP_ID_0 = 0,
    L2CAP_ID_MAX,
    L2CAP_ID_INVALID = L2CAP_ID_MAX,

} L2CAP_ID;



typedef enum
{
    L2CAP_SLQ_ID_0 = 0,
    L2CAP_SLQ_ID_1,
    L2CAP_SLQ_ID_2,
    L2CAP_SLQ_ID_3,
    L2CAP_SLQ_ID_MAX,
    L2CAP_SLQ_ID_INVALID = L2CAP_SLQ_ID_MAX,

} L2CAP_SLQ_ID;



typedef enum
{
    L2CAP_SLQ_OWNER_RX_ATT = 0,
    L2CAP_SLQ_OWNER_RX_SIG,
    L2CAP_SLQ_OWNER_RX_SMP,
    L2CAP_SLQ_OWNER_RX_DYNAMIC_CID,
    L2CAP_SLQ_OWNER_MAX,
    L2CAP_SLQ_OWNER_INVALID = L2CAP_SLQ_OWNER_MAX,

} L2CAP_SLQ_OWNER;



typedef struct l2cap_sdu
{
    struct l2cap_sdu    *next;

    /// configuration. reserve for LL.
    u32                 cfg;

    /// pointer to next fragment location
    struct l2cap_sdu    *next_fragment;

    /// flags
    u32                 dir : 1;        /// TX/RX direction
    u32                 reserved : 31;

    /// LL header
    u8                  pb_flag;        /// owner l2cap, follow SIG defintion
    u8                  fragment_len;   /// fragment length

    /// fragment
    union
    {
        u8              continue_pld[L2CAP_SDU_CONTINUE_PAYLOAD_SIZE];

        struct
        {
            u16         frame_len;
            u16         cid;
            u8          start_pld[L2CAP_SDU_START_PAYLOAD_SIZE];
        };
    };

} l2cap_sdu_st;



#endif  /// end of _L2CAP_DEF_H_
