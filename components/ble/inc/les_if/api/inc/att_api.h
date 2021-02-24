#ifndef _ATT_API_H_
#define _ATT_API_H_


#include "les_if/api/inc/svc_def.h"
#include "les_if/api/inc/les_def.h"



#define ATTR_CHAR_PERM_SHIFT_RESERVED_0                     (0x0F)
#define ATTR_CHAR_PERM_SHIFT_RESERVED_1                     (0x0E)
#define ATTR_CHAR_PERM_SHIFT_READ                           (0x0D)
#define ATTR_CHAR_PERM_SHIFT_WRITE                          (0x0C)
#define ATTR_CHAR_PERM_SHIFT_WRITE_NO_RSP                   (0x0B)
#define ATTR_CHAR_PERM_SHIFT_WRITE_SIGNED                   (0x0A)
#define ATTR_CHAR_PERM_SHIFT_READ_AUTHEN                    (0x07)
#define ATTR_CHAR_PERM_SHIFT_WRITE_AUTHEN                   (0x04)
#define ATTR_CHAR_PERM_SHIFT_RESERVED_2                     (0x03)
#define ATTR_CHAR_PERM_SHIFT_READ_AUTHOR                    (0x02)
#define ATTR_CHAR_PERM_SHIFT_RESERVED_3                     (0x01)
#define ATTR_CHAR_PERM_SHIFT_WRITE_AUTHOR                   (0x00)


#define ATTR_CHAR_PERM_RESERVED_0                           (0x8000)
#define ATTR_CHAR_PERM_RESERVED_1                           (0x4000)
#define ATTR_CHAR_PERM_READ                                 (0x2000)
#define ATTR_CHAR_PERM_WRITE                                (0x1000)
#define ATTR_CHAR_PERM_WRITE_NO_RSP                         (0x0800)
#define ATTR_CHAR_PERM_WRITE_SIGNED                         (0x0400)
#define ATTR_CHAR_PERM_READ_AUTHEN_MODE_1_L1                (0x00 << ATTR_CHAR_PERM_SHIFT_READ_AUTHEN)
#define ATTR_CHAR_PERM_READ_AUTHEN_MODE_1_L2                (0x01 << ATTR_CHAR_PERM_SHIFT_READ_AUTHEN)
#define ATTR_CHAR_PERM_READ_AUTHEN_MODE_1_L3                (0x02 << ATTR_CHAR_PERM_SHIFT_READ_AUTHEN)
#define ATTR_CHAR_PERM_READ_AUTHEN_MODE_1_L4                (0x03 << ATTR_CHAR_PERM_SHIFT_READ_AUTHEN)
#define ATTR_CHAR_PERM_READ_AUTHEN_MODE_2_L1                (0x04 << ATTR_CHAR_PERM_SHIFT_READ_AUTHEN)
#define ATTR_CHAR_PERM_READ_AUTHEN_MODE_2_L2                (0x05 << ATTR_CHAR_PERM_SHIFT_READ_AUTHEN)
#define ATTR_CHAR_PERM_WRITE_AUTHEN_MODE_1_L1               (0x00 << ATTR_CHAR_PERM_SHIFT_WRITE_AUTHEN)
#define ATTR_CHAR_PERM_WRITE_AUTHEN_MODE_1_L2               (0x01 << ATTR_CHAR_PERM_SHIFT_WRITE_AUTHEN)
#define ATTR_CHAR_PERM_WRITE_AUTHEN_MODE_1_L3               (0x02 << ATTR_CHAR_PERM_SHIFT_WRITE_AUTHEN)
#define ATTR_CHAR_PERM_WRITE_AUTHEN_MODE_1_L4               (0x03 << ATTR_CHAR_PERM_SHIFT_WRITE_AUTHEN)
#define ATTR_CHAR_PERM_WRITE_AUTHEN_MODE_2_L1               (0x04 << ATTR_CHAR_PERM_SHIFT_WRITE_AUTHEN)
#define ATTR_CHAR_PERM_WRITE_AUTHEN_MODE_2_L2               (0x05 << ATTR_CHAR_PERM_SHIFT_WRITE_AUTHEN)
#define ATTR_CHAR_PERM_RESERVED_2                           (0x0008)
#define ATTR_CHAR_PERM_READ_AUTHOR                          (0x0004)
#define ATTR_CHAR_PERM_RESERVED_3                           (0x0002)
#define ATTR_CHAR_PERM_WRITE_AUTHOR                         (0x0001)



#define ATT_PREP_WR_BUF_SIZE                                (ATT_MTU - 5)
#define ATT_EXECUTE_WRITE_ATTR_HANDLE                       0xFFFC



typedef enum
{
    ATT_SVCMD_AUTHEN_RESPONSE = ATT_SVC_NUM_MIN,
    ATT_SVCMD_AUTHOR_RESPONSE,
    ATT_SVCMD_AUTHOR_RESPONSE_WITH_VALUE,

} ATT_SVCMD;



typedef enum
{
    ATT_LES_EVENT_AUTHEN_REQUEST = ATT_LES_EVENT_ID_MIN,
    ATT_LES_EVENT_AUTHOR_REQUEST,
    ATT_LES_EVENT_WRITE_SYNC,

} ATT_LES_EVENT;



typedef enum
{
    ATT_AUTHEN_RESULT_SUCCESS,
    ATT_AUTHEN_RESULT_FAIL,

} ATT_AUTHEN_RESULT;



typedef enum
{
    ATT_AUTHOR_RESULT_SUCCESS,
    ATT_AUTHOR_RESULT_FAIL,

} ATT_AUTHOR_RESULT;



typedef enum
{
    ATT_AUTHOR_TYPE_RD,
    ATT_AUTHOR_TYPE_WR,
    ATT_AUTHOR_TYPE_PREP_WR,
    ATT_AUTHOR_TYPE_EXEC_WR,

} ATT_AUTHOR_TYPE;



typedef struct
{
    uint16_t    reserved;

} att_authen_request_st;



typedef struct
{
    uint16_t    attr_hdl;
    uint16_t    value_offset;

} att_rd_author_request_st;



typedef struct
{
    uint16_t    attr_hdl;
    uint16_t    value_size;
    uint8_t     value[ATT_MTU];

} att_wr_author_request_st;



typedef struct
{
    uint16_t    attr_hdl;
    uint16_t    value_offset;
    uint16_t    value_size;
    uint8_t     value[ATT_PREP_WR_BUF_SIZE];

} att_prep_wr_author_request_st;



typedef struct
{
    uint16_t    attr_hdl;
    uint8_t     flags;

} att_exec_wr_author_request_st;



typedef struct
{
    uint8_t     author_type;
    
    union
    {
        att_rd_author_request_st         rd_author_request;
        att_wr_author_request_st         wr_author_request;
        att_prep_wr_author_request_st    prep_wr_author_request;
        att_exec_wr_author_request_st    exec_wr_author_request;

    } request;

} att_author_request_st;



typedef struct
{
    uint16_t    attr_hdl;
    uint16_t    value_size;
    uint8_t     value[ATT_MTU];

} att_write_sync_st;



typedef struct
{
    uint16_t    security_level;

} att_authen_response_st;



typedef struct
{
    uint16_t    result : 1;
    uint16_t    reserved : 5;
    uint16_t    error_code : 8;
    uint16_t    attr_hdl;

} att_author_response_st;



typedef struct 
{
    uint16_t    conn_hdl;

    union
    {
        att_authen_request_st   authen_request;     /// ATT_LES_EVENT_AUTHEN_REQUEST
        att_author_request_st   author_request;     /// ATT_LES_EVENT_AUTHOR_REQUEST
        att_write_sync_st       write_sync;         /// ATT_LES_EVENT_WRITE_SYNC

    } data;

} att_les_event_st;



DEF_SVC(ATT_SVCMD_AUTHEN_RESPONSE,              uint32_t, les_att_authen_response(uint16_t conn_hdl, att_authen_response_st *response));
DEF_SVC(ATT_SVCMD_AUTHOR_RESPONSE,              uint32_t, les_att_author_response(uint16_t conn_hdl, att_author_response_st *response));
DEF_SVC(ATT_SVCMD_AUTHOR_RESPONSE_WITH_VALUE,   uint32_t, les_att_author_response_with_value(uint16_t conn_hdl, att_author_response_st *response, attr_value_st *attr_value));



#endif  // end of _ATT_API_H_