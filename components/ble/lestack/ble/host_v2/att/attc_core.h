#ifndef _ATTC_CORE_H_
#define _ATTC_CORE_H_



#include "attc_def.h"



typedef enum
{
    ATTC_ID_0 = 0,
    ATTC_ID_MAX,
    ATTC_ID_INVALID = ATTC_ID_MAX,

} ATTC_ID;



typedef enum
{
    ATTC_STATE_IDLE = 0,
    ATTC_STATE_PENDING,

} ATTC_STATE;



typedef enum
{
    ATTC_OPERATION_HANDLE_OP_REQUEST = 0,

} ATTC_OPERATION;



typedef struct
{
    ATTC_STATE              state;
    u16                     conn_hdl;

} attc_ctrlblock_st;



typedef struct
{
    ATTC_OPERATION  op;
    u32             *param;
    u8              param_size;

} attc_operation_st;



u8 attc_core_reset(void);
u8 attc_core_obtain_resource(u16 conn_hdl);
u8 attc_core_release_resource(u16 conn_hdl);
ATTC_ID attc_core_get_valid_id(u16 conn_hdl);
u8 attc_core_send_operation(ATTC_ID id, attc_operation_st *operation);



#endif  /// end of _ATTC_CORE_H_

