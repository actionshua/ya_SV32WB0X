#ifndef _SMP_IF_H_
#define _SMP_IF_H_



#include "smp_def.h"



u8 SMP_reset(send_l2cap_msg_func_t l2cap_func, send_hci_cmd_func_t hci_func, send_app_event_func_t app_func);

/// For SVC operation
u8 SMP_pairing_start(u16 conn_hdl, smp_security_property_st *security_property);
u8 SMP_pairing_cancel(u16 conn_hdl);
u8 SMP_security_grant_response(u16 conn_hdl, smp_security_grant_response_st *security_grant);
u8 SMP_tk_response(u16 conn_hdl, smp_tk_response_st *tk_response);
u8 SMP_security_info_response(u16 conn_hdl, smp_security_info_st *security_info);
u8 SMP_recover_ltk_response(u16 conn_hdl, smp_encryption_info_st *encryption_info, smp_security_info_st *security_info);
u8 SMP_encrypt_data(smp_encryption_data_st *encryption_data);

/// For debug
u8 SMP_dump_info(u16 conn_hdl);

/// For HCI operation
u8 SMP_handle_encryption_change_event(u16 conn_hdl, u8 status, u8 encryption_enabled);
u8 SMP_handle_encryption_key_refresh_complete_event(u16 conn_hdl, u8 status);
u8 SMP_handle_ltk_request_event(u16 conn_hdl, u8 *rand64, u8 *ediv);
u8 SMP_handle_connection_complete_event(u16 conn_hdl, u8 status);
u8 SMP_handle_disconnection_complete_event(u16 conn_hdl, u8 status);

/// For other events
u8 smp_pairing_timeout(u16 conn_hdl);

/// For L2CAP operation
u8 SMP_pairing_operation(u16 conn_handle, u8 *data, u8 data_len);



#endif  /// _SMP_IF_H_
