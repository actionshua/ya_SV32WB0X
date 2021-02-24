#ifndef _GATTM_API_H_
#define _GATTM_API_H_


#include "les_if/api/inc/svc_def.h"
#include "les_if/api/inc/les_def.h"



#define GATTM_UUID_LEN_MAX                  16



typedef enum
{
    GATTM_SVCMD_ADD_SERVICE = GATTM_SVC_NUM_MIN,
    GATTM_SVCMD_ADD_ATTR,
    GATTM_SVCMD_GET_ATTR_VALUE,
    GATTM_SVCMD_SET_ATTR_VALUE,
    GATTM_SVCMD_ENABLE_SERVICE,
    GATTM_SVCMD_GET_SERVICE_INFO,
    GATTM_SVCMD_RESET,

} GATTM_SVCMD;



typedef enum
{
    GATTM_LES_EVENT_NONE = GATTM_LES_EVENT_ID_MIN,

} GATTM_LES_EVENT;



typedef enum
{
    GATTM_SERVICE_TYPE_PRIMARY,
    GATTM_SERVICE_TYPE_SECONDARY,

} GATTM_SERVICE_TYPE;



/// GATTM_SVCMD_ADD_ATTR
typedef struct
{
    uint8_t     uuid_type;
    uint8_t     variable_value_len;
    uint16_t    perm;
    uint16_t    value_size;
    uint8_t     *value;
    uint8_t     *uuid;

} gattm_add_attr_st;



/// GATTM_SVCMD_GET_SERVICE_INFO
typedef struct
{
    uint16_t    start_hdl;
    uint16_t    end_hdl;
    uint8_t     onoff;                      /// 0: off, 1: on
    uint8_t     type;                       /// 0: primary, 1: secondary.
    uint16_t    uuid_type;
    uint8_t     uuid[GATTM_UUID_LEN_MAX];

} gattm_service_info_st;



DEF_SVC(GATTM_SVCMD_ADD_SERVICE,        uint32_t,   les_gattm_add_service(uint8_t type));
DEF_SVC(GATTM_SVCMD_ADD_ATTR,           uint32_t,   les_gattm_add_attr(gattm_add_attr_st *attr, uint16_t *added_attr_hdl));
DEF_SVC(GATTM_SVCMD_GET_ATTR_VALUE,     uint32_t,   les_gattm_get_attr_value(uint16_t attr_hdl, attr_value_st *attr_value));
DEF_SVC(GATTM_SVCMD_SET_ATTR_VALUE,     uint32_t,   les_gattm_set_attr_value(uint16_t attr_hdl, attr_value_st *attr_value));
DEF_SVC(GATTM_SVCMD_ENABLE_SERVICE,     uint32_t,   les_gattm_enable_service(uint16_t attr_hdl, uint8_t onoff));
DEF_SVC(GATTM_SVCMD_GET_SERVICE_INFO,   uint32_t,   les_gattm_get_service_info(uint16_t attr_hdl, gattm_service_info_st *service_info));
DEF_SVC(GATTM_SVCMD_RESET,              uint32_t,   les_gattm_reset(void));



#endif  // end of _GATTM_API_H_