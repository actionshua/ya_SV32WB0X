#ifndef _GAP_DEF_H_
#define _GAP_DEF_H_



#include "host_def.h"



#define GAP_CONNECTION_TIMER_ID                     6
#define GAP_TIMER_UNIT_MS                           100
#define GAP_INVALID_CONNECTION_HANDLE               0xFFFF

#define GAP_TIMEOUT_CONN_PARAM_UPDATE_REQUEST_MS    30000

#define GAP_ENC_KEY_SIZE_SUPPORT_MIN                16

/// Signaling packet format
#define SIG_PKT_OP_COMMAND_REJECT                   0x01
#define SIG_PKT_OP_CONNECTION_REQ                   0x02
#define SIG_PKT_OP_CONNECTION_RSP                   0x03
#define SIG_PKT_OP_CONFIGURATION_REQ                0x04
#define SIG_PKT_OP_CONFIGURATION_RSP                0x05
#define SIG_PKT_OP_DISCONNECTION_REQ                0x06
#define SIG_PKT_OP_DISCONNECTION_RSP                0x07
#define SIG_PKT_OP_ECHO_REQ                         0x08
#define SIG_PKT_OP_ECHO_RSP                         0x09
#define SIG_PKT_OP_INFORMATION_REQ                  0x0A
#define SIG_PKT_OP_INFORMATION_RSP                  0x0B
#define SIG_PKT_OP_CREATE_CHANNEL_REQ               0x0C
#define SIG_PKT_OP_CREATE_CHANNEL_RSP               0x0D
#define SIG_PKT_OP_MOVE_CHANNEL_REQ                 0x0E
#define SIG_PKT_OP_MOVE_CHANNEL_RSP                 0x0F
#define SIG_PKT_OP_MOVE_CHANNEL_CFM_REQ             0x10
#define SIG_PKT_OP_MOVE_CHANNEL_CFM_RSP             0x11
#define SIG_PKT_OP_CONN_PARAM_UPDATE_REQ            0x12
#define SIG_PKT_OP_CONN_PARAM_UPDATE_RSP            0x13

#define SIG_PKT_PLD_LEN_COMMAND_REJECT              0x06
#define SIG_PKT_PLD_LEN_CONN_PARAM_UPDATE_REQ       0x0C



typedef enum
{
    GAP_RESULT_SUCCESS = ERR_HOST_SUCCESS,
    GAP_RESULT_FAIL = ERR_HOST_FAIL,
    GAP_RESULT_INVALID_PARAM = ERR_HOST_INVALID_PARAM,
    GAP_RESULT_INVALID_OPERATION = ERR_HOST_INVALID_OPERATION,
    GAP_RESULT_INSUFF_RESOURCE = ERR_HOST_INSUFF_RESOURCE,
    GAP_RESULT_INVALID_CONNECTION = ERR_HOST_INVALID_CONNECTION,

    GAP_RESULT_MIN = ERR_HOST_GAP,
    GAP_RESULT_STATUS_CONFLICT = GAP_RESULT_MIN,
    GAP_RESULT_INSUFFICIENT_SECURITY_LEVEL,
    GAP_RESULT_INSUFFICIENT_SECURITY_LEVEL_WITH_ENCRYPTION,
    GAP_RESULT_INSUFFICIENT_ENC_KEY_SIZE,
    GAP_RESULT_ERROR_OTHERS,
    GAP_RESULT_MAX,

} GAP_RESULT;



typedef enum
{
    GAP_ENC_KEY_SIZE_INSUFF = 0,
    GAP_ENC_KEY_SIZE_SUPPORT,

} GAP_ENC_KEY_SIZE;



#endif  /// end of _GAP_DEF_H_
