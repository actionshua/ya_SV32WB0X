#ifndef _GATTC_CORE_H_
#define _GATTC_CORE_H_


#include "gattc_def.h"



typedef enum
{
    GATTC_ID_0 = 0,
    GATTC_ID_MAX,
    GATTC_ID_INVALID = GATTC_ID_MAX,

} GATTC_ID;



typedef enum
{
    GATTC_STATE_IDLE = 0,
    GATTC_STATE_WAIT_EXCHANGE_MTU_RESPONSE,
    GATTC_STATE_WAIT_DISCOVER_PRIMARY_SERVICES_RESPONSE,
    GATTC_STATE_WAIT_DISCOVER_PRIMARY_SERVICES_BY_UUID_RESPONSE,
    GATTC_STATE_WAIT_DISCOVER_RELATIONSHIPS_RESPONSE,
    GATTC_STATE_WAIT_DISCOVER_CHARACTERISTICS_RESPONSE,
    GATTC_STATE_WAIT_DISCOVER_DESCRIPTORS_RESPONSE,
    GATTC_STATE_WAIT_READ_RESPONSE,
    GATTC_STATE_WAIT_WRITE_RESPONSE,

} GATTC_STATE;



typedef enum
{
    GATTC_OPERATION_EXCHANGE_MTU_REQUEST = 0,
    GATTC_OPERATION_DISCOVER_PRIMARY_SERVICES_REQUEST,
    GATTC_OPERATION_DISCOVER_PRIMARY_SERVICES_BY_UUID_REQUEST,
    GATTC_OPERATION_DISCOVER_RELATIONSHIPS_REQUEST,
    GATTC_OPERATION_DISCOVER_CHARACTERISTICS_REQUEST,
    GATTC_OPERATION_DISCOVER_DESCRIPTORS_REQUEST,
    GATTC_OPERATION_READ_REQUEST,
    GATTC_OPERATION_WRITE_REQUEST,

    GATTC_OPERATION_HANDLE_OP_RESPONSE,

    GATTC_OPERATION_HANDLE_VALUE_NOTIFICATION,
    GATTC_OPERATION_HANDLE_VALUE_INDICATION,

    GATTC_OPERATION_TIMEOUT,
    GATTC_OPERATION_DISCONNECTION_COMPLETE,
    
} GATTC_OPERATION;



typedef struct
{
    u16     attr_hdl;
    u16     offset;

} gattc_proc_param_read_req_st;



typedef struct
{
    u8      type;
    u16     attr_hdl_or_flags;

} gattc_proc_param_write_req_st;



typedef struct
{
    GATTC_STATE     state;
    u16             conn_hdl;
    u8              htmr_id;

    union
    {
        gattc_proc_param_read_req_st    read_req;
        gattc_proc_param_write_req_st   write_req;

    } proc_param;

} gattc_ctrlblock_st;



typedef struct gattc_operation
{
    GATTC_OPERATION op;
    u32             *param;
    u8              param_size;

} gattc_operation_st;



u8 gattc_core_reset(void);
u8 gattc_core_obtain_resource(u16 conn_hdl);
u8 gattc_core_release_resource(u16 conn_hdl);
GATTC_ID gattc_core_get_valid_id(u16 conn_hdl);
u8 gattc_core_handle_value_notification(GATTC_ID id, l2cap_sdu_st *sdu);
u8 gattc_core_handle_value_indication(GATTC_ID id, l2cap_sdu_st *sdu);
void *gattc_core_get_proc_param(u16 conn_hdl);
u8 gattc_core_send_operation(GATTC_ID id, gattc_operation_st *operation);



#endif  /// end of _GATTC_CORE_H_
