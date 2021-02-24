#ifndef _GATTM_CORE_H_
#define _GATTM_CORE_H_


#include "gattm_def.h"



typedef struct
{
    u32 uuid_type : 2;
    u32 value_size : 10;
    u32 value_size_max : 10;
    u32 variable_value_len : 1;
    u32 reserved : 9;

    u16 perm;

#ifndef __SSV_LINUX_SIM__
    u16 p_uuid_value;
#else
    u32 p_uuid_value;
#endif

} gattm_attr_ctrlblock_st;



typedef struct
{
    u8  s_hdl;
    u8  attr_num;
    u16 onoff : 1;
    u16 type : 1;
    u16 reserved : 14;

} gattm_service_ctrlblock_st;



typedef struct
{
    u8  service_num;
    u8  prep_exec_write_support : 1;
    u8  reserved : 7;
    u16 attr_db_size_used;

} gattm_ctrlblock_st;



u8 gattm_core_reset(void);
u8 gattm_core_db_reset(void);
u8 gattm_core_add_service(u8 type);
u8 gattm_core_add_attr(gattm_add_attr_st *attr, u16 *added_attr_hdl);
u8 gattm_core_get_attr_value(u16 attr_hdl, attr_value_st *attr_value);
u8 gattm_core_set_attr_value(u16 attr_hdl, attr_value_st *attr_value);
u8 gattm_core_set_service_onoff(u16 start_hdl, u8 onoff);
u8 gattm_core_get_service_info(u16 attr_hdl, gattm_service_info_st *service_info);
u8 gattm_core_get_attr_info(u16 attr_hdl, gattm_attr_info_st* info);
u8 gattm_core_get_prep_exec_write_support(void);
void gattm_core_set_prep_exec_write_support(u8 onoff);



#endif  /// end of _GATTM_CORE_H_
