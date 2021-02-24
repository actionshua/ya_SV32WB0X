#ifndef _ATT_CLIENT_H_
#define _ATT_CLIENT_H_



#include "attc_def.h"



u8 att_client_exchange_mtu_req(u16 conn_hdl, u16 mtu_size);
u8 att_client_find_by_type_value_req(u16 conn_hdl, u16 s_hdl, u16 e_hdl, u8 uuid_len, u8 *uuid, u8 val_len, u8 *val);
u8 att_client_find_info_req(u16 conn_hdl, u16 s_hdl, u16 e_hdl);
u8 att_client_read_req(u16 conn_hdl, u16 hdl);
u8 att_client_read_blob_req(u16 conn_hdl, u16 hdl, u16 offset);
u8 att_client_read_by_group_type_req(u16 conn_hdl, u16 s_hdl, u16 e_hdl, u8 group_uuid_len, u8 *group_uuid);
u8 att_client_read_by_type_req(u16 conn_hdl, u16 s_hdl, u16 e_hdl, u8 uuid_len, u8 *uuid);
u8 att_client_write_req(u16 conn_hdl, u16 hdl, u16 val_len, u8 *val);
u8 att_client_write_cmd(u16 conn_hdl, u16 hdl, u16 val_len, u8 *val);
u8 att_client_prepare_write_req(u16 conn_hdl, u16 hdl, u16 offset, u16 val_len, u8 *val);
u8 att_client_execute_write_req(u16 conn_hdl, u8 execute_flag);
u8 att_client_handle_value_confirm(u16 conn_hdl);



#endif  /// end of _ATT_CLIENT_H_

