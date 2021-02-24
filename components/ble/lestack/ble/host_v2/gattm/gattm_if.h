#ifndef _GATTM_IF_H_
#define _GATTM_IF_H_


#include "gattm_def.h"



u8 GATTM_reset(void);
u8 GATTM_db_reset(void);
u8 GATTM_add_service(u8 type);
u8 GATTM_add_attr(gattm_add_attr_st *attr, u16 *added_attr_hdl);
u8 GATTM_get_attr_value(u16 attr_hdl, attr_value_st *attr_value);
u8 GATTM_set_attr_value(u16 attr_hdl, attr_value_st *attr_value);
u8 GATTM_set_service_onoff(u16 start_hdl, u8 onoff);
u8 GATTM_get_service_info(u16 attr_hdl, gattm_service_info_st *service_info);
u8 GATTM_get_attr_info(u16 attr_hdl, gattm_attr_info_st* info);
u8 GATTM_get_prep_exec_write_support(void);
void GATTM_set_prep_exec_write_support(u8 onoff);



#endif  /// end of _GATTM_IF_H_
