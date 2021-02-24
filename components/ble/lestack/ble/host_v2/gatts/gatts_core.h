#ifndef _GATTS_CORE_H_
#define _GATTS_CORE_H_


#include "gatts_def.h"



#define GATTS_INDICATION_TIME_OUT               30000
#define GATTS_INDICATION_CONFIRM_CMD_LEN        1



typedef enum
{
    GATTS_ID_0 = 0,
    GATTS_ID_MAX,
    GATTS_ID_INVALID = GATTS_ID_MAX,

} GATTS_ID;



typedef enum
{
    GATTS_STATE_IDLE = 0,
    GATTS_STATE_WAIT_CONFIRM,
    GATTS_STATE_EXCEPTION,

} GATTS_STATE;



typedef enum
{
    GATTS_OPERATION_HANDLE_VALUE_INDICATION = 0,
    GATTS_OPERATION_INDICATION_CONFIRM,
    GATTS_OPERATION_TIMEOUT,
    GATTS_OPERATION_DISCONNECTION_COMPLETE,
    
} GATTS_OPERATION;



typedef struct
{
    GATTS_STATE state;
    u8          indication_htmr_id;
    u16         indication_attr_hdl;
    u16         conn_hdl;
    
} gatts_ctrlblock_st;



typedef struct gatts_operation
{
    GATTS_OPERATION op;
    u32             *param;
    u8              param_size;

} gatts_operation_st;



u8 gatts_core_reset(void);
u8 gatts_core_obtain_resource(u16 conn_hdl);
u8 gatts_core_release_resource(u16 conn_hdl);
GATTS_ID gatts_core_get_valid_id(u16 conn_hdl);
u8 gatts_core_handle_value_indication(u16 conn_hdl, u16 attr_hdl);
u8 gatts_core_handle_value_notification(u16 conn_hdl, u16 attr_hdl);
u8 gatts_core_send_operation(GATTS_ID id, gatts_operation_st *operation);



#endif  /// end of _GATTS_CORE_H_
