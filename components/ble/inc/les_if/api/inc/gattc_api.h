#ifndef _GATTC_API_H_
#define _GATTC_API_H_


#include "les_if/api/inc/svc_def.h"
#include "les_if/api/inc/les_def.h"



#define GATTC_PROC_SERVICE_16_NUM_MAX               3
#define GATTC_PROC_SERVICE_16_NUM_MIN               1
#define GATTC_PROC_SERVICE_128_NUM_MAX              1
#define GATTC_PROC_SERVICE_128_NUM_MIN              1
#define GATTC_PROC_SERVICE_HDL_NUM_MAX              5
#define GATTC_PROC_SERVICE_HDL_NUM_MIN              1
#define GATTC_PROC_CHARACTERISTIC_16_NUM_MAX        3
#define GATTC_PROC_CHARACTERISTIC_16_NUM_MIN        1
#define GATTC_PROC_CHARACTERISTIC_128_NUM_MAX       1
#define GATTC_PROC_CHARACTERISTIC_128_NUM_MIN       1
#define GATTC_PROC_DESCRIPTOR_16_NUM_MAX            3
#define GATTC_PROC_DESCRIPTOR_16_NUM_MIN            1
#define GATTC_PROC_DESCRIPTOR_128_NUM_MAX           1
#define GATTC_PROC_DESCRIPTOR_128_NUM_MIN           1



typedef enum
{
    GATTC_SVCMD_EXCHANGE_MTU_REQUEST = GATTC_SVC_NUM_MIN,
    GATTC_SVCMD_DISCOVER_PRIMARY_SERVICES_REQUEST,
    GATTC_SVCMD_DISCOVER_PRIMARY_SERVICES_BY_UUID_REQUEST,
    GATTC_SVCMD_DISCOVER_RELATIONSHIPS_REQUEST,
    GATTC_SVCMD_DISCOVER_CHARACTERISTICS_REQUEST,
    GATTC_SVCMD_DISCOVER_DESCRIPTORS_REQUEST,
    GATTC_SVCMD_READ_REQUEST,
    GATTC_SVCMD_WRITE_REQUEST,
    GATTC_SVCMD_READ_CHARACTERISTICS_BY_UUID_REQUEST,
    GATTC_SVCMD_READ_MULTIPLE_CHARACTERISTICS_REQUEST,

} GATTC_SVCMD;



typedef enum
{
    GATTC_LES_EVENT_EXCHANGE_MTU_RESPONSE = GATTC_LES_EVENT_ID_MIN,
    GATTC_LES_EVENT_DISCOVER_PRIMARY_SERVICES_RESPONSE,
    GATTC_LES_EVENT_DISCOVER_PRIMARY_SERVICES_BY_UUID_RESPONSE,
    GATTC_LES_EVENT_DISCOVER_RELATIONSHIPS_RESPONSE,
    GATTC_LES_EVENT_DISCOVER_CHARACTERISTICS_RESPONSE,
    GATTC_LES_EVENT_DISCOVER_DESCRIPTORS_RESPONSE,
    GATTC_LES_EVENT_READ_RESPONSE,
    GATTC_LES_EVENT_WRITE_RESPONSE,
    GATTC_LES_EVENT_HANDLE_VALUE_OPERATION,
    GATTC_LES_EVENT_READ_CHARACTERISTICS_BY_UUID_RESPONSE,
    GATTC_LES_EVENT_READ_MULTIPLE_CHARACTERISTICS_RESPONSE,

} GATTC_LES_EVENT;



typedef enum
{
    GATTC_STATUS_END = 0,
    GATTC_STATUS_CONTINUE,
    GATTC_STATUS_ERROR,
    GATTC_STATUS_TIMEOUT,
    GATTC_STATUS_ERROR_SECURITY,
    GATTC_STATUS_DISCONNECTION_COMPLETE,

    GATTC_STATUS_SUCCESS = 0,
    GATTC_STATUS_ERROR_RESPONSE,

} GATTC_STATUS;



typedef enum
{
    GATTC_PROC_SERVICE_TYPE_16 = 0,
    GATTC_PROC_SERVICE_TYPE_128,
    GATTC_PROC_SERVICE_TYPE_HDL,

} GATTC_PROC_SERVICE_TYPE;



typedef enum
{
    GATTC_PROC_CHARACTERISTIC_TYPE_16 = 0,
    GATTC_PROC_CHARACTERISTIC_TYPE_128,

} GATTC_PROC_CHARACTERISTIC_TYPE;



typedef enum
{
    GATTC_PROC_DESCRIPTOR_TYPE_16 = 0,
    GATTC_PROC_DESCRIPTOR_TYPE_128,

} GATTC_PROC_DESCRIPTOR_TYPE;



typedef enum
{
    GATTC_WRITE_TYPE_WRITE_REQUEST = 0,
    GATTC_WRITE_TYPE_WRITE_COMMAND,
    GATTC_WRITE_TYPE_SIGNED_WRITE_COMMAND,
    GATTC_WRITE_TYPE_PREP_WRITE,
    GATTC_WRITE_TYPE_EXEC_WRITE,
    GATTC_WRITE_TYPE_MAX,
    GATTC_WRITE_TYPE_INVALID = GATTC_WRITE_TYPE_MAX,

} GATTC_WRITE_TYPE;



typedef enum
{
    GATTC_HANDLE_VALUE_OPERATION_TYPE_NONE = 0,
    GATTC_HANDLE_VALUE_OPERATION_TYPE_NOTIFICATION,
    GATTC_HANDLE_VALUE_OPERATION_TYPE_INDICATION,

} GATTC_HANDLE_VALUE_OPERATION_TYPE;



typedef struct
{
    uint8_t     type;
    uint16_t    start_attr_hdl;
    uint16_t    end_attr_hdl;
    uuid_16_st  uuid;

} gattc_service_16_st;



typedef struct
{
    uint8_t     type;
    uint16_t    start_attr_hdl;
    uint16_t    end_attr_hdl;
    uuid_128_st uuid;

} gattc_service_128_st;



typedef struct
{
    uint16_t    start_attr_hdl;
    uint16_t    end_attr_hdl;

} gattc_service_hdl_st;



typedef struct
{
    uint8_t     count;
    uint8_t     proc_type;

    union
    {
        gattc_service_16_st     services_16[GATTC_PROC_SERVICE_16_NUM_MAX];
        gattc_service_128_st    services_128[GATTC_PROC_SERVICE_128_NUM_MAX];
        gattc_service_hdl_st    services_hdl[GATTC_PROC_SERVICE_HDL_NUM_MAX];
    };

} gattc_services_list_st;



typedef struct
{
    uint8_t     prop;
    uint16_t    decl_attr_hdl;
    uint16_t    val_attr_hdl;
    uuid_16_st  uuid;

} gattc_characteristic_16_st;



typedef struct
{
    uint8_t     prop;
    uint16_t    decl_attr_hdl;
    uint16_t    val_attr_hdl;
    uuid_128_st uuid;

} gattc_characteristic_128_st;



typedef struct
{
    uint8_t     count;
    uint8_t     proc_type;

    union
    {
        gattc_characteristic_16_st  characteristics_16[GATTC_PROC_CHARACTERISTIC_16_NUM_MAX];
        gattc_characteristic_128_st characteristics_128[GATTC_PROC_CHARACTERISTIC_128_NUM_MAX];
    };

} gattc_characteristics_list_st;



typedef struct
{
    uint16_t    val_attr_hdl;
    uuid_16_st  uuid;

} gattc_descriptor_16_st;



typedef struct
{
    uint16_t    val_attr_hdl;
    uuid_128_st uuid;

} gattc_descriptor_128_st;



typedef struct
{
    uint8_t     count;
    uint8_t     proc_type;

    union
    {
        gattc_descriptor_16_st  descriptors_16[GATTC_PROC_DESCRIPTOR_16_NUM_MAX];
        gattc_descriptor_128_st descriptors_128[GATTC_PROC_DESCRIPTOR_128_NUM_MAX];
    };

} gattc_descriptors_list_st;



typedef struct
{
    uint8_t     count;
    uint8_t     pair_size;
    uint8_t     val[ATT_MTU];

} gattc_values_list_st;



typedef struct
{
    uint8_t     status;
    uint8_t     err_reason;
    uint16_t    mtu_size;

} gattc_exchange_mtu_response_st;



typedef struct
{
    uint8_t                     status;
    uint8_t                     err_reason;
    gattc_services_list_st      services_list;

} gattc_discover_primary_services_response_st;



typedef struct
{
    uint8_t                     status;
    uint8_t                     err_reason;
    gattc_services_list_st      services_list;

} gattc_discover_primary_services_by_uuid_response_st;



typedef struct
{
    uint8_t                     status;
    uint8_t                     err_reason;
    gattc_services_list_st      services_list;

} gattc_discover_relationships_response_st;



typedef struct
{
    uint8_t                         status;
    uint8_t                         err_reason;
    gattc_characteristics_list_st   characteristics_list;

} gattc_discover_characteristics_response_st;



typedef struct
{
    uint8_t                     status;
    uint8_t                     err_reason;
    gattc_descriptors_list_st   descriptors_list;

} gattc_discover_descriptors_response_st;



typedef struct
{
    uint8_t     status;
    uint8_t     err_reason;
    uint16_t    attr_hdl;
    uint16_t    offset;
    uint16_t    size;
    uint8_t     val[ATT_MTU];

} gattc_read_response_st;



typedef struct
{
    uint8_t                 status;
    uint8_t                 err_reason;
    gattc_values_list_st    values_list;

} gattc_read_characteristics_by_uuid_response_st;



typedef struct
{
    uint8_t                 status;
    uint8_t                 err_reason;
    gattc_values_list_st    values_list;

} gattc_read_multiple_characteristics_response_st;



typedef struct
{
    uint8_t     status;
    uint8_t     err_reason;
    uint8_t     type;
    uint16_t    attr_hdl_or_flags;
    uint16_t    offset;
    uint16_t    size;
    uint8_t     val[ATT_MTU];

} gattc_write_response_st;



typedef struct
{
    uint8_t     type;
    uint16_t    attr_hdl;
    uint16_t    size;
    uint8_t     val[ATT_MTU];

} gattc_handle_value_operation_st;



typedef struct 
{
    uint16_t conn_hdl;

    union
    {
        gattc_exchange_mtu_response_st                          exchange_mtu_response;                      /// GATTC_LES_EVENT_EXCHANGE_MTU_RESPONSE
        gattc_discover_primary_services_response_st             discover_primary_services_response;         /// GATTC_LES_EVENT_DISCOVER_PRIMARY_SERVICES_RESPONSE
        gattc_discover_primary_services_by_uuid_response_st     discover_primary_services_by_uuid_response; /// GATTC_LES_EVENT_DISCOVER_PRIMARY_SERVICES_BY_UUID_RESPONSE
        gattc_discover_relationships_response_st                discover_relationships_response;            /// GATTC_LES_EVENT_DISCOVER_RELATIONSHIPS_RESPONSE
        gattc_discover_characteristics_response_st              discover_characteristics_response;          /// GATTC_LES_EVENT_DISCOVER_CHARACTERISTICS_RESPONSE
        gattc_discover_descriptors_response_st                  discover_descriptors_response;              /// GATTC_LES_EVENT_DISCOVER_DESCRIPTORS_RESPONSE
        gattc_read_response_st                                  read_response;                              /// GATTC_LES_EVENT_READ_RESPONSE
        gattc_read_characteristics_by_uuid_response_st          read_characteristics_by_uuid_response;      /// GATTC_LES_EVENT_READ_CHARACTERISTICS_BY_UUID_RESPONSE
        gattc_read_multiple_characteristics_response_st         read_multiple_characteristics_response;     /// GATTC_LES_EVENT_READ_MULTIPLE_CHARACTERISTICS_RESPONSE
        gattc_write_response_st                                 write_response;                             /// GATTC_LES_EVENT_WRITE_RESPONSE
        gattc_handle_value_operation_st                         handle_value_operation;                     /// GATTC_LES_EVENT_HANDLE_VALUE_OPERATION

    } data;

} gattc_les_event_st;



DEF_SVC(GATTC_SVCMD_EXCHANGE_MTU_REQUEST,                       uint32_t,   les_gattc_exchange_mtu_request(uint16_t conn_hdl, uint16_t mtu_size));
DEF_SVC(GATTC_SVCMD_DISCOVER_PRIMARY_SERVICES_REQUEST,          uint32_t,   les_gattc_discover_primary_services_request(uint16_t conn_hdl, uint16_t start_attr_hdl));
DEF_SVC(GATTC_SVCMD_DISCOVER_PRIMARY_SERVICES_BY_UUID_REQUEST,  uint32_t,   les_gattc_discover_primary_services_by_uuid_request(uint16_t conn_hdl, uint16_t start_attr_hdl, uuid_st *service_uuid));
DEF_SVC(GATTC_SVCMD_DISCOVER_RELATIONSHIPS_REQUEST,             uint32_t,   les_gattc_discover_relationships_request(uint16_t conn_hdl, uint16_t start_attr_hdl, uint16_t end_attr_hdl));
DEF_SVC(GATTC_SVCMD_DISCOVER_CHARACTERISTICS_REQUEST,           uint32_t,   les_gattc_discover_characteristics_request(uint16_t conn_hdl, uint16_t start_attr_hdl, uint16_t end_attr_hdl));
DEF_SVC(GATTC_SVCMD_DISCOVER_DESCRIPTORS_REQUEST,               uint32_t,   les_gattc_discover_descriptors_request(uint16_t conn_hdl, uint16_t start_attr_hdl, uint16_t end_attr_hdl));
DEF_SVC(GATTC_SVCMD_READ_REQUEST,                               uint32_t,   les_gattc_read_request(uint16_t conn_hdl, uint16_t attr_hdl, uint16_t offset));
DEF_SVC(GATTC_SVCMD_WRITE_REQUEST,                              uint32_t,   les_gattc_write_request(uint16_t conn_hdl, uint8_t type, uint16_t attr_hdl_or_flags, attr_value_st *attr_value));
DEF_SVC(GATTC_SVCMD_READ_CHARACTERISTICS_BY_UUID_REQUEST,       uint32_t,   les_gattc_read_characteristics_by_uuid_request(uint16_t conn_hdl, uint16_t start_attr_hdl, uint16_t end_attr_hdl, uuid_st *characteristic_uuid));
DEF_SVC(GATTC_SVCMD_READ_MULTIPLE_CHARACTERISTICS_REQUEST,      uint32_t,   les_gattc_read_multiple_characteristics_request(uint16_t conn_hdl, uint16_t count, uint16_t *attr_hdl_tbl));



#endif  // end of _GATTC_API_H_