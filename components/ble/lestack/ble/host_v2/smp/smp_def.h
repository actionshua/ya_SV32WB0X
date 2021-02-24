#ifndef _SMP_DEF_H_
#define _SMP_DEF_H_



#include "host_def.h"



#define SMP_MTU                                         23

#define SMP_OPCODE_PAIRING_REQUEST                      0x01
#define SMP_OPCODE_PAIRING_RESPONSE                     0x02
#define SMP_OPCODE_PAIRING_CONFIRM                      0x03
#define SMP_OPCODE_PAIRING_RANDOM                       0x04
#define SMP_OPCODE_PAIRING_FAILED                       0x05
#define SMP_OPCODE_ENCRYPTION_INFO                      0x06
#define SMP_OPCODE_MASTER_IDENTIFICATION                0x07
#define SMP_OPCODE_IDENTITY_INFO                        0x08
#define SMP_OPCODE_IDENTITY_ADDRESS_INFO                0x09
#define SMP_OPCODE_SIGNING_INFO                         0x0a
#define SMP_OPCODE_SECURITY_REQUEST                     0x0b
#define SMP_OPCODE_MAX                                  0x0b



typedef u8 (*send_l2cap_msg_func_t)(u16, u8, u8 *, u8);
typedef u8 (*send_hci_cmd_func_t)(u16, u32 *, u8);
typedef u8 (*send_app_event_func_t)(u16, u8, void *);



typedef enum
{
    SMP_RESULT_SUCCESS = ERR_HOST_SUCCESS,
    SMP_RESULT_FAIL = ERR_HOST_FAIL,
    SMP_RESULT_INSUFF_RESOURCE = ERR_HOST_INSUFF_RESOURCE,
    SMP_RESULT_INVALID_OPERATION = ERR_HOST_INVALID_OPERATION,
    SMP_RESULT_INVALID_PARAM = ERR_HOST_INVALID_PARAM,
    SMP_RESULT_CANCEL = ERR_HOST_CANCEL,
    SMP_RESULT_TIMEOUT = ERR_HOST_TIMEOUT,
    SMP_RESULT_DISCONNECT = ERR_HOST_DISCONNECT,
    SMP_RESULT_INVALID_CONNECTION = ERR_HOST_INVALID_CONNECTION,

    SMP_RESULT_MIN = ERR_HOST_SMP,
    SMP_RESULT_MAX,

} SMP_RESULT;



typedef enum
{
    SMP_HCI_CMD_ENCRYPT_DATA,
    SMP_HCI_CMD_START_ENCRYPTION,
    SMP_HCI_CMD_LTK_REQUEST_REPLY,
    SMP_HCI_CMD_LTK_REQUEST_NEGATIVE_REPLY,
    SMP_HCI_CMD_DISCONNECT,

} SMP_HCI_CMD;



typedef enum
{
    SMP_ACTION_RESULT_SUCCESS = SMP_RESULT_SUCCESS,
    SMP_ACTION_RESULT_FAIL = SMP_RESULT_FAIL,
    SMP_ACTION_RESULT_CANCEL = SMP_RESULT_CANCEL,
    SMP_ACTION_RESULT_TIMEOUT = SMP_RESULT_TIMEOUT,
    SMP_ACTION_RESULT_DISCONNECT = SMP_RESULT_DISCONNECT,

} SMP_ACTION_RESULT;



#endif  /// end of _SMP_DEF_H_
