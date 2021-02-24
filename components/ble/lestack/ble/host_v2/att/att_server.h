#ifndef _ATT_SERVER_H_
#define _ATT_SERVER_H_



#include "atts_def.h"



#define ATT_EXEC_WRITE_FLAG_CANCEL              0
#define ATT_EXEC_WRITE_FLAG_IMMEDIATELY_WRITE   1



typedef enum
{
    ATT_SERVER_AUTHEN_PASS,
    ATT_SERVER_AUTHEN_FAIL,                 

} ATT_SERVER_AUTHEN;



u32 att_server_write_req(u16 conn_hdl, u16 param_len, u8 *param);
u32 att_server_prep_write_req(u16 conn_hdl, u16 param_len, u8 *param);
u32 att_server_exec_write_req(u16 conn_hdl, u16 param_len, u8 *param);
u32 att_server_write_cmd(u16 conn_hdl, u16 param_len, u8 *param, l2cap_sdu_st *sdu);
u8 att_server_mtu_req(u16 conn_hdl, u16 param_len, u8 *param);
u8 att_server_read_blob_req(u16 conn_hdl, u16 param_len, u8 *param);
u8 att_server_read_by_type_req(u16 conn_hdl, u16 param_len, u8 *param);
u8 att_server_read_by_group_type_req(u16 conn_hdl, u16 param_len, u8 *param);
u8 att_server_find_by_type_value_req(u16 conn_hdl, u16 param_len, u8 *param);
u8 att_server_read_multiple_req(u16 conn_hdl, u16 param_len, u8 *param);
u8 att_server_find_info_req(u16 conn_hdl, u16 param_len, u8 *param);
u8 att_server_read_req(u16 conn_hdl, u16 param_len, u8 *param);
u8 att_server_handle_value_indication(u16 conn_hdl, u16 hdl, u16 val_len, u8 *val);
u8 att_server_handle_value_notification(u16 conn_hdl, u16 hdl, u16 val_len, u8 *val);
u8 att_server_dispatch(u16 conn_hdl, l2cap_sdu_st *sdu);



#endif  /// end of _ATT_SERVER_H_

