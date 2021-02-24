#ifndef _GAP_IF_H_
#define _GAP_IF_H_



#include "gap_def.h"



u8 GAP_reset(void);
u8 GAP_get_conn_num(void);
u8 GAP_set_adv_param(gap_adv_param_st *adv_param);
u8 GAP_set_adv_data(gap_adv_data_st *adv_data);
u8 GAP_set_scan_response_data(gap_adv_data_st *scan_response_data);
u8 GAP_start_adv(u32 timeout);
u8 GAP_stop_adv(void);
u8 GAP_set_scan_param(gap_scan_param_st *scan_param);
u8 GAP_start_scan(u32 timeout, u8 filter_duplicates);
u8 GAP_stop_scan(void);
u8 GAP_get_public_address(bd_addr_st *public_addr);
u8 GAP_set_public_address(bd_addr_st *public_addr);
u8 GAP_get_own_used_address(u16 conn_hdl, bd_addr_st *own_addr);
u8 GAP_get_peer_used_address(u16 conn_hdl, bd_addr_st *peer_addr);
u8 GAP_read_white_list_size(u8 *white_list_size);
u8 GAP_clear_white_list(void);
u8 GAP_add_dev_to_white_list(bd_addr_st *addr);
u8 GAP_remove_dev_from_white_list(bd_addr_st *addr);
u8 GAP_handle_conn_param_update_request(u16 conn_hdl, gap_conn_param_st *conn_param);
u8 GAP_set_tx_power(u8 type, s8 tx_power);
u8 GAP_get_rssi(u16 conn_hdl, u8 *rssi);
u8 GAP_start_rssi(u16 conn_hdl);
u8 GAP_stop_rssi(u16 conn_hdl);
u8 GAP_disconnect(u16 conn_hdl, u8 reason);
u8 GAP_update_security_level(u16 conn_hdl, GAP_SECURITY_LEVEL security_level, u8 enc_key_size);
u8 GAP_check_security_level(u16 conn_hdl, GAP_SECURITY_LEVEL security_level);
u8 GAP_generate_rand_addr(u8 addr_type, gap_irk_st *irk, bd_addr_st *rand_addr);
u8 GAP_set_rand_addr(bd_addr_st *rand_addr);
u8 GAP_read_local_version_info(gap_version_info_st *version_info);
u8 GAP_read_local_supported_features(gap_le_features_st *le_features);
u8 GAP_read_remote_version_info(u16 conn_hdl, gap_version_info_st *version_info);
u8 GAP_read_remote_used_features(u16 conn_hdl, gap_le_features_st *le_features);
u8 GAP_handle_connection_complete_event(gap_conn_complete_st *conn_complete);
u8 GAP_handle_disconnection_complete_event(gap_disconn_complete_st *disconn_complete);
u8 GAP_handle_conn_update_complete(u8 status, u16 conn_hdl, gap_conn_param_st *conn_param);
u8 GAP_handle_conn_param_update_response(u16 conn_hdl, u8 identifier, u16 len, u16 rsp_result);
u8 GAP_handle_unsupport_request(u16 conn_hdl, u8 identifier);
u8 GAP_handle_version_exchanged_notify(u8 status, u16 conn_hdl, u8 version, u16 subversion, u16 manufacturer_name);



#endif  // end of _GAP_IF_H_
