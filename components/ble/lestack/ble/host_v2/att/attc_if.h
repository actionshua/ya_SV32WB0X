#ifndef _ATTC_IF_H_
#define _ATTC_IF_H_



#include "attc_def.h"



u8 ATTC_reset(void);
u8 ATTC_find_by_type_value_req(u16 conn_hdl, u16 start_attr_hdl, u16 end_attr_hdl, u8 uuid_len, u8 *uuid, u8 val_len, u8 *val);
u8 ATTC_find_info_req(u16 conn_hdl, u16 start_attr_hdl, u16 end_attr_hdl);
u8 ATTC_read_req(u16 conn_hdl, u16 attr_hdl);
u8 ATTC_read_blob_req(u16 conn_hdl, u16 attr_hdl, u16 offset);
u8 ATTC_read_by_group_type_req(u16 conn_hdl, u16 start_attr_hdl, u16 end_attr_hdl, u8 group_uuid_len, u8 *group_uuid);
u8 ATTC_read_by_type_req(u16 conn_hdl, u16 start_attr_hdl, u16 end_attr_hdl, u8 uuid_len, u8 *uuid);
u8 ATTC_write_req(u16 conn_hdl, u16 attr_hdl, u16 val_len, u8 *val);
u8 ATTC_prepare_write_req(u16 conn_hdl, u16 attr_hdl, u16 offset, u16 val_len, u8 *val);
u8 ATTC_execute_write_req(u16 conn_hdl, u8 execute_flag);
u8 ATTC_handle_value_confirm(u16 conn_hdl);
u8 ATTC_handle_connection_complete_event(u16 conn_hdl, u8 status);
u8 ATTC_handle_disconnection_complete_event(u16 conn_hdl, u8 status);
u8 ATTC_handle_op_request(u16 conn_hdl, l2cap_sdu_st *sdu);



#endif  /// end of _ATTS_IF_H_
