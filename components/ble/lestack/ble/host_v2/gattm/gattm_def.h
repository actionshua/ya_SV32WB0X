#ifndef _GATTM_DEF_H_
#define _GATTM_DEF_H_


#include "host_def.h"



#define SERVICE_NUM_MAX                         16    /// total number of supported services
#define ATTR_NUM_MAX                            97    /// total number of supported attributes. No.0 is reserved.
#define ATTR_VALUE_LENGTH_MAX                   512
#define ATTR_VALUE_SIZE_MAX                     22
#define ATTR_DATABASE_SIZE_MAX                  2048



typedef enum
{
    GATTM_RESULT_SUCCESS = ERR_HOST_SUCCESS,
    GATTM_RESULT_FAIL = ERR_HOST_FAIL,
    GATTM_RESULT_INVALID_HANDLE = ERR_HOST_INVALID_HANDLE,
    GATTM_RESULT_INVALID_PARAM = ERR_HOST_INVALID_PARAM,
    GATTM_RESULT_INVALID_OPERATION = ERR_HOST_INVALID_OPERATION,
    GATTM_RESULT_INSUFF_RESOURCE = ERR_HOST_INSUFF_RESOURCE,

    GATTM_RESULT_MIN = ERR_HOST_GATTM,
    GATTM_RESULT_INVALID_HANDLE_UNDER_MAX = GATTM_RESULT_MIN,
    GATTM_RESULT_INVALID_HANDLE_OVER_MAX,
    GATTM_RESULT_SERVICE_OFF_ACCESS,
    GATTM_RESULT_MAX,
  
} GATTM_RESULT;



typedef struct
{
    u32 access_r : 1;
    u32 access_w : 1;
    u32 access_wcmd : 1;
    u32 access_wsigned : 1;
    u32 r_authen : 3;
    u32 w_authen : 3;
    u32 r_author : 1;
    u32 w_author : 1;

    u32 uuid_type : 2;
    u32 value_size : 10;
    u32 value_size_max : 10;
    u32 variable_value_len : 1;

    u8 *att;    /// attribute, including uuid/value

} gattm_attr_info_st;



#endif  /// end of _GATTM_DEF_H_
