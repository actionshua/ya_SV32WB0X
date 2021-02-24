#ifndef _L2CAP_IF_H_
#define _L2CAP_IF_H_


#include "l2cap_def.h"



u8 L2CAP_reset(alloc_pdu_func_t alloc_pdu_func, free_pdu_func_t free_pdu_func, send_tx_pdu_func_t send_tx_pdu_func);
u8 L2CAP_register_dynamic_cid(u16 conn_hdl, u16 cid);
u8 L2CAP_unregister_dynamic_cid(u16 conn_hdl);
l2cap_sdu_st *L2CAP_alloc_tx_normal_sdu(u16 sdu_size);
l2cap_sdu_st *L2CAP_alloc_tx_priority_sdu(u16 sdu_size);
void L2CAP_free_tx_sdu(l2cap_sdu_st *sdu);
void L2CAP_free_rx_sdu(l2cap_sdu_st *sdu);
u8 *L2CAP_get_sdu_pld_ptr(l2cap_sdu_st *sdu);
u16 L2CAP_get_sdu_pld_value(l2cap_sdu_st *sdu, u16 value_offset, u16 value_size, u8 *value);
u16 L2CAP_set_sdu_pld_value(l2cap_sdu_st *sdu, u16 value_offset, u16 value_size, u8 *value);
u8 L2CAP_send_att_sdu(u16 conn_hdl, l2cap_sdu_st *sdu);
u8 L2CAP_send_sig_sdu(u16 conn_hdl, l2cap_sdu_st *sdu);
u8 L2CAP_send_smp_sdu(u16 conn_hdl, l2cap_sdu_st *sdu);
u8 L2CAP_send_dynamic_cid_data(u16 conn_hdl, l2cap_dynamic_cid_data_st *dyncmic_cid_data);
u8 L2CAP_send_att_upper_response(u16 conn_hdl);
u8 L2CAP_send_sig_upper_response(u16 conn_hdl);
u8 L2CAP_send_smp_upper_response(u16 conn_hdl);
u8 L2CAP_send_att_upper_response_without_free_sdu(u16 conn_hdl);
u8 L2CAP_send_sig_upper_response_without_free_sdu(u16 conn_hdl);
u8 L2CAP_send_smp_upper_response_without_free_sdu(u16 conn_hdl);
u8 L2CAP_handle_connection_complete_event(u16 conn_hdl, u8 status);
u8 L2CAP_handle_disconnection_complete_event(u16 conn_hdl, u8 status);
u8 L2CAP_handle_number_of_completed_packets_event(u16 conn_hdl, u8 packets);
u8 L2CAP_handle_acl_data_received(u16 conn_hdl, l2cap_sdu_st *sdu);
u8 L2CAP_handle_send_upper_request_event(u16 conn_hdl, u16 owner);



#endif  /// end of _L2CAP_IF_H_


