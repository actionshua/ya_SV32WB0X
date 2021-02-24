#ifndef _ATT_DEF_H_
#define _ATT_DEF_H_



#include "host_def.h"



/// ATT error code
#define  ATT_ERROR_NONE                                     0x00
#define  ATT_ERROR_INVALID_HANDLE                           0x01
#define  ATT_ERROR_READ_NOT_PERMIT                          0x02
#define  ATT_ERROR_WRITE_NOT_PERMIT                         0x03
#define  ATT_ERROR_INVALID_PDU                              0x04
#define  ATT_ERROR_INSUF_AUTHENTICATION                     0x05
#define  ATT_ERROR_REQ_NOT_SUPPORTED                        0x06
#define  ATT_ERROR_INVALID_OFFSET                           0x07
#define  ATT_ERROR_INSUF_AUTHORIZATION                      0x08
#define  ATT_ERROR_PREPARE_QUEUE_FULL                       0x09
#define  ATT_ERROR_ATTRIBUTE_NOT_FOUND                      0x0a
#define  ATT_ERROR_ATTRIBUTE_NOT_LONG                       0x0b
#define  ATT_ERROR_INSUF_ENCRYPTION_KEY_SIZE                0x0c
#define  ATT_ERROR_INVALID_ATTRIBUTE_VALUE_LEN              0x0d
#define  ATT_ERROR_UNLIKELY                                 0x0e
#define  ATT_ERROR_INSUF_ENCRYPTION                         0x0f
#define  ATT_ERROR_UNSUPPORT_GROUP_TYPE                     0x10
#define  ATT_ERROR_INSUF_RESOURCE                           0x11

#define  ATT_ERROR_APPLICATION_MIN                          0x80
#define  ATT_ERROR_APPLICATION_MAX                          0xFF

/// ATT opcode 
#define ATT_OP_ERROR_RSP                                    0x01
#define ATT_OP_MTU_REQ                                      0x02
#define ATT_OP_MTU_RSP                                      0x03
#define ATT_OP_FIND_INFO_REQ                                0x04
#define ATT_OP_FIND_INFO_RSP                                0x05
#define ATT_OP_FIND_BY_TYPE_VALUE_REQ                       0x06
#define ATT_OP_FIND_BY_TYPE_VALUE_RSP                       0x07
#define ATT_OP_READ_BY_TYPE_REQ                             0x08
#define ATT_OP_READ_BY_TYPE_RSP                             0x09
#define ATT_OP_READ_REQ                                     0x0A
#define ATT_OP_READ_RSP                                     0x0B
#define ATT_OP_READ_BY_GROUP_TYPE_REQ                       0x10
#define ATT_OP_READ_BY_GROUP_TYPE_RSP                       0x11
#define ATT_OP_READ_BLOB_REQ                                0x0C
#define ATT_OP_READ_BLOB_RSP                                0x0D
#define ATT_OP_READ_MULTIPLE_REQ                            0x0E
#define ATT_OP_READ_MULTIPLE_RSP                            0x0F
#define ATT_OP_WRITE_REQ                                    0x12
#define ATT_OP_WRITE_RSP                                    0x13
#define ATT_OP_WRITE_COMMAND                                0x52
#define ATT_OP_WRITE_SIGNED_COMMAND                         0xD2
#define ATT_OP_PREP_WRITE_REQ                               0x16
#define ATT_OP_PREP_WRITE_RSP                               0x17
#define ATT_OP_EXEC_WRITE_REQ                               0x18
#define ATT_OP_EXEC_WRITE_RSP                               0x19
#define ATT_OP_HANDLE_VALUE_NOTIFICATION                    0x1B
#define ATT_OP_HANDLE_VALUE_INDICATION                      0x1D
#define ATT_OP_HANDLE_VALUE_CONFIRMATION                    0x1E

/// Default MTU
#define ATT_UUID_LEN_MAX                                    16
#define ATT_ACCEPT_AUTHOR_NUM_MAX                           5
#define ATT_READ_MULTIPLE_NUM_MAX                           11
#define ATT_MTU_SIZE                                        2

/// ATT find information procedure:response format
#define ATT_HDL_UUID_PAIR_16                                0x01
#define ATT_HDL_UUID_PAIR_128                               0x02
#define ATT_TIMER_ID                                        5
#define ATT_TIME_OUT                                        30

/// Used to error response
#define ATT_ERSP_PLD_LEN                                    5
#define ATT_ERSP_REQ_OP_CODE_LEN                            1
#define ATT_ERSP_HDL_LEN                                    2
#define ATT_ERSP_REASON_LEN                                 1

/// Opcode length
#define ATT_OP_CDOE_LEN                                     1

/// Handle length
#define ATT_HDL_LEN                                         2
#define ATT_OFFSET_LEN                                      2

/// ATT response procedure offset
#define ATT_OP_CDOE_OFFSET                                  0

#define ATT_OP_EXCHANGE_MTU_RSP_MTU_SIZE_OFFSET             1

#define ATT_OP_READ_BY_GROUP_TYPE_RSP_ATTR_LEN_OFFSET       1
#define ATT_OP_READ_BY_GROUP_TYPE_RSP_START_HDL_OFFSET      2
#define ATT_OP_READ_BY_GROUP_TYPE_RSP_END_HDL_OFFSET        4
#define ATT_OP_READ_BY_GROUP_TYPE_RSP_UUID_OFFSET           6

#define ATT_OP_FIND_BY_TYPE_VALUE_FOUND_ATTR_HDL_LEN_OFFSET 1
#define ATT_OP_FIND_BY_TYPE_VALUE_GROUP_END_HDL_OFFSET      3

#define ATT_OP_READ_BY_TYPE_RSP_ATTR_LEN_OFFSET             1
#define ATT_OP_READ_BY_TYPE_RSP_DECL_HDL_OFFSET             2
#define ATT_OP_READ_BY_TYPE_RSP_PROP_OFFSET                 4
#define ATT_OP_READ_BY_TYPE_RSP_VAL_HDL_OFFSET              5
#define ATT_OP_READ_BY_TYPE_RSP_UUID_OFFSET                 7

#define ATT_OP_FIND_INFO_RSP_ATTR_LEN_OFFSET                1
#define ATT_OP_FIND_INFO_RSP_VAL_HDL_OFFSET                 2
#define ATT_OP_FIND_INFO_RSP_UUID_OFFSET                    4

#define ATT_OP_READ_RSP_VAL_OFFSET                          1

#define ATT_OP_HANDLE_VALUE_OPERATION_ATTR_HDL_OFFSET       1
#define ATT_OP_HANDLE_VALUE_OPERATION_VAL_OFFSET            3

#define ATT_OP_ERROR_RSP_REQUEST_OP_CODE_OFFSET             1
#define ATT_OP_ERROR_RSP_ATTR_HDL_OFFSET                    2
#define ATT_OP_ERROR_RSP_ERROR_CODE_OFFSET                  4

/// UUID length
#define UUID_LEN(_TYPE_)                                    (2 << (_TYPE_))

#define ATTR_CHAR_PERM_MASK_RESERVED_0                      (0x8000)
#define ATTR_CHAR_PERM_MASK_RESERVED_1                      (0x4000)
#define ATTR_CHAR_PERM_MASK_READ                            (0x2000)
#define ATTR_CHAR_PERM_MASK_WRITE                           (0x1000)
#define ATTR_CHAR_PERM_MASK_WRITE_NO_RSP                    (0x0800)
#define ATTR_CHAR_PERM_MASK_WRITE_SIGNED                    (0x0400)
#define ATTR_CHAR_PERM_MASK_READ_AUTHEN                     (0x0380)
#define ATTR_CHAR_PERM_MASK_WRITE_AUTHEN                    (0x0070)
#define ATTR_CHAR_PERM_MASK_RESERVED_2                      (0x0008)
#define ATTR_CHAR_PERM_MASK_READ_AUTHOR                     (0x0004)
#define ATTR_CHAR_PERM_MASK_RESERVED_3                      (0x0002)
#define ATTR_CHAR_PERM_MASK_WRITE_AUTHOR                    (0x0001)



enum
{
    ATT_SERVER_PROC_END = 0,
    ATT_SERVER_PROC_EXCEPTION,
    ATT_SERVER_PROC_AUTHEN_PENDING,
    ATT_SERVER_PROC_AUTHOR_PENDING,
    ATT_SERVER_PROC_RETRY_PENDING,
    ATT_SERVER_PROC_END_SDU_IN_USE,

    ATT_CLIENT_PROC_END,
    ATT_CLIENT_PROC_EXCEPTION,
    ATT_CLIENT_PROC_RETRY_PENDING,
};



#endif  /// end of _ATT_DEF_H_
