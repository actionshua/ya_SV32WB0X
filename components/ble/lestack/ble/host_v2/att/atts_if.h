#ifndef _ATTS_IF_H_
#define _ATTS_IF_H_



#include "atts_def.h"



u8 ATTS_reset(void);
u8 ATTS_handle_connection_complete_event(u16 conn_hdl, u8 status);
u8 ATTS_handle_disconnection_complete_event(u16 conn_hdl, u8 status);
u8 ATTS_handle_op_request(u16 conn_hdl, l2cap_sdu_st *sdu);
u8 ATTS_handle_authen_response(u16 conn_hdl, att_authen_response_st *response);
u8 ATTS_handle_author_response(u16 conn_hdl, att_author_response_st *response);
u8 ATTS_handle_author_response_with_value(u16 conn_hdl, att_author_response_st *response, attr_value_st *attr_value);
u8 ATTS_handle_retry_number_of_complete(u16 conn_hdl);



#endif  /// end of _ATTS_IF_H_
