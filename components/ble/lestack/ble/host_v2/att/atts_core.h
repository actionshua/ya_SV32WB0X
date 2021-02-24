#ifndef _ATTS_CORE_H_
#define _ATTS_CORE_H_



#include "atts_def.h"



typedef enum
{
    ATTS_ID_0 = 0,
    ATTS_ID_MAX,
    ATTS_ID_INVALID = ATTS_ID_MAX,

} ATTS_ID;



typedef enum
{
    ATTS_STATE_IDLE = 0,
    ATTS_STATE_AUTHEN_PENDING,
    ATTS_STATE_AUTHOR_PENDING,
    ATTS_STATE_RETRY_PENDING,

} ATTS_STATE;



typedef enum
{
    ATTS_OPERATION_HANDLE_OP_REQUEST = 0,
    ATTS_OPERATION_AUTHEN_RESPONSE,
    ATTS_OPERATION_AUTHOR_RESPONSE,
    ATTS_OPERATION_AUTHEN_TIMEOUT,
    ATTS_OPERATION_AUTHOR_TIMEOUT,
    ATTS_OPERATION_RETRY_TIMEOUT,
    ATTS_OPERATION_RETRY_NUMBER_OF_COMPLETE,

} ATTS_OPERATION;



typedef enum
{
    ATTS_AUTHEN_STATE_NOT_AUTHENTICATED = 0,
    ATTS_AUTHEN_STATE_AUTHENTICATING,
    ATTS_AUTHEN_STATE_AUTHENTICATED,
    ATTS_AUTHEN_STATE_AUTHENTICATING_FAIL,

} ATTS_AUTHEN_STATE;



typedef enum
{
    ATTS_AUTHOR_STATE_NOT_AUTHORIZED = 0,
    ATTS_AUTHOR_STATE_AUTHORIZING,
    ATTS_AUTHOR_STATE_AUTHORIZED,
    ATTS_AUTHOR_STATE_AUTHORIZING_FAIL,

} ATTS_AUTHOR_STATE;



typedef struct
{
    u8              htmr_id;
    l2cap_sdu_st    *sdu;

} atts_pending_param_st;



typedef struct
{
    u8  state;
    u8  error_code;
    u8  security_level;

} atts_authen_state_st;



typedef struct
{
    u16             htmr_attr_hdl;
    attr_value_st   *response_attr_value;

} atts_author_param_st;



typedef struct
{
    u8  state : 2;
    u8  type : 2;
    u8  reserved : 4;
    u8  error_code;
    u16 attr_hdl;

} atts_author_state_st;



typedef struct
{
    ATTS_STATE              state;
    u16                     conn_hdl;
    atts_pending_param_st   pending_param;
    atts_authen_state_st    authen_state;
    atts_author_param_st    author_param;
    atts_author_state_st    author_state[ATTS_AUTHOR_ID_MAX];

} atts_ctrlblock_st;



typedef struct
{
    ATTS_OPERATION  op;
    u32             *param;
    u8              param_size;

} atts_operation_st;



u8 atts_core_reset(void);
u8 atts_core_obtain_resource(u16 conn_hdl);
u8 atts_core_release_resource(u16 conn_hdl);
ATTS_ID atts_core_get_valid_id(u16 conn_hdl);
ATTS_STATE atts_core_get_state(ATTS_ID id);
u8 atts_core_send_operation(ATTS_ID id, atts_operation_st *operation);
u8 atts_core_obtain_author_resource(ATTS_ID id, u16 attr_hdl);
void atts_core_release_author_resource(ATTS_ID id, u16 attr_hdl);
void atts_core_set_authen_security_level(ATTS_ID id, u8 security_level);
u8 atts_core_get_authen_security_level(ATTS_ID id);
void atts_core_set_authen_error_code(ATTS_ID id, u8 error_code);
u8 atts_core_get_authen_error_code(ATTS_ID id);
void atts_core_set_authen_state(ATTS_ID id, ATTS_AUTHEN_STATE state);
ATTS_AUTHEN_STATE atts_core_get_authen_state(ATTS_ID id);
void atts_core_set_author_state(ATTS_ID id, u8 author_id, ATTS_AUTHOR_STATE state);
ATTS_AUTHOR_STATE atts_core_get_author_state(ATTS_ID id, u8 author_id);
void atts_core_set_author_type(ATTS_ID id, u8 author_id, ATT_AUTHOR_TYPE type);
ATT_AUTHOR_TYPE atts_core_get_author_type(ATTS_ID id, u8 author_id);
void atts_core_set_author_error_code(ATTS_ID id, u8 author_id, u8 error_code);
u8 atts_core_get_author_error_code(ATTS_ID id, u8 author_id);
u8 atts_core_get_valid_author_id(ATTS_ID id, u16 attr_hdl);
void atts_core_set_author_htmr_attr_hdl(ATTS_ID id, u16 attr_hdl);
u16 atts_core_get_author_htmr_attr_hdl(ATTS_ID id);
void atts_core_set_author_response_attr_value(ATTS_ID id, attr_value_st *attr_value);
attr_value_st *atts_core_get_author_response_attr_value(ATTS_ID id);



#endif  /// end of _ATTS_CORE_H_

