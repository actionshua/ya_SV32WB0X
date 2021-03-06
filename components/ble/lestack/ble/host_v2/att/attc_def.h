#ifndef _ATTC_DEF_H_
#define _ATTC_DEF_H_



#include "att_def.h"
#include "l2cap/l2cap_def.h"



/// ATT client related definition
#define ATTC_INVALID_CONNECTION_HANDLE              0xFFFF
#define ATTC_INVALID_ATTR_HANDLE                    0x0000



typedef enum
{
    ATTC_RESULT_SUCCESS = ERR_HOST_SUCCESS,
    ATTC_RESULT_FAIL = ERR_HOST_FAIL,
    ATTC_RESULT_INVALID_PARAM = ERR_HOST_INVALID_PARAM,
    ATTC_RESULT_INVALID_OPERATION = ERR_HOST_INVALID_OPERATION,
    ATTC_RESULT_INSUFF_RESOURCE = ERR_HOST_INSUFF_RESOURCE,
    ATTC_RESULT_INVALID_CONNECTION = ERR_HOST_INVALID_CONNECTION,

    ATTC_RESULT_MIN = ERR_HOST_ATTC,
    ATTC_RESULT_MAX,

} ATTC_RESULT;



#endif  /// end of _ATTC_DEF_H_
