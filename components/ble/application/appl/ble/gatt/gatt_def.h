#ifndef _GATT_DEF_H_
#define _GATT_DEF_H_



#include "stdint.h"
#include "les_if/api/inc/les_api.h"



/// GATT log operation
#define GATT_DEBUG

#ifdef GATT_DEBUG
#include "ilog.h"
#define GATT_LOG_VERBOSE(...)                   \
    do {                                        \
        ILOG(LOG_VERBOSE, __VA_ARGS__);         \
    } while(0)

#define GATT_LOG_DBG(...)                       \
    do {                                        \
        ILOG(LOG_DBG, __VA_ARGS__);             \
    } while(0)

#define GATT_LOG_INFO(...)                      \
    do {                                        \
        ILOG(LOG_INFO, __VA_ARGS__);            \
    } while(0)

#define GATT_LOG_ERR(...)                       \
    do {                                        \
        ILOG(LOG_ERR, __VA_ARGS__);             \
    } while(0)

#define GATT_LOG_HARDFAULT(...)                 \
    do {                                        \
        ILOG(LOG_CRIT, __VA_ARGS__);            \
    } while(0)

#define GATT_LOG_ARRAY(array, len)              \
    do {                                        \
        IDUMP(LOG_INFO, array, len);            \
    } while(0)

#else

#define GATT_LOG_VERBOSE(...)
#define GATT_LOG_DBG(...)
#define GATT_LOG_INFO(...)
#define GATT_LOG_ERR(...)
#define GATT_LOG_HARDFAULT(...)
#define GATT_LOG_ARRAY(array, len)

#endif  /// #ifdef PROFILE_DEBUG



typedef enum
{
    ERR_GATT_SUCCESS = ERR_SUCCESS,
    ERR_GATT_MIN = ERR_GATT,

    ERR_GATT_FAIL = ERR_GATT_MIN,
    ERR_GATT_INVALID_PARAM,
    ERR_GATT_INVALID_OPERATION,
    ERR_GATT_INSUFF_RESOURCE,
    ERR_GATT_TIMEOUT,
    ERR_GATT_DISCONNECT,

    ERR_GATT_MAX,

} ERR_GATT_ENUM;



typedef enum
{
    GATT_ELEMENT_NONE = 0,
    GATT_ELEMENT_SERVICE,
    GATT_ELEMENT_CHARACTERISTIC,
    GATT_ELEMENT_DESCRIPTOR,

} GATT_ELEMENT;



typedef struct
{
    uint8_t                         element;
    uint16_t                        val_attr_hdl;
    uint8_t                         uuid_type;
    uint8_t                         *uuid;

} gatt_descriptor_st;



typedef struct
{
    uint8_t                         element;
    uint8_t                         prop;
    uint16_t                        decl_attr_hdl;
    uint16_t                        val_attr_hdl;
    uint16_t                        service_idx;
    uint8_t                         uuid_type;
    uint8_t                         *uuid;

} gatt_characteristic_st;



typedef struct
{
    uint8_t                         element;
    uint8_t                         type;
    uint16_t                        start_attr_hdl;
    uint16_t                        end_attr_hdl;
    uint8_t                         uuid_type;
    uint8_t                         *uuid;

} gatt_service_st;



typedef struct
{
    void                            **list;
    uint16_t                        length;
    uint16_t                        size;

} gatt_element_list_st;



typedef struct
{
    gatt_element_list_st            *elements;

} gatt_db_st;



#endif  /// end of _GATT_DEF_H_
