#ifndef _GAP_CORE_H_
#define _GAP_CORE_H_



#include "gap_def.h"



typedef enum
{
    GAP_ID_0 = 0,
    GAP_ID_MAX,
    GAP_ID_INVALID = GAP_ID_MAX,

} GAP_ID;



typedef enum
{
    GAP_STATE_IDLE = 0,
    GAP_STATE_PENDING,

} GAP_STATE;



typedef enum
{
    GAP_OPERATION_CONN_PARAM_UPDATE_REQUEST,
    GAP_OPERATION_CONN_PARAM_UPDATE_RESPONSE,
    GAP_OPERATION_CONN_PARAM_UPDATE_REQUEST_TIMEOUT,
    GAP_OPERATION_DISCONNECTION_COMPLETE,

} GAP_OPERATION;



typedef struct
{
    GAP_STATE           state;
    u16                 conn_hdl;
    GAP_SECURITY_LEVEL  security_level;
    GAP_ENC_KEY_SIZE    enc_key_size;
    GAP_ROLE            role;
    u8                  htmr_id;

} gap_conn_info_st;



typedef struct
{
    gap_conn_info_st    conn_info[GAP_ID_MAX];
    u8                  htmr_id_adv;
    u8                  htmr_id_scan;

} gap_ctrlblock_st;



typedef struct
{
    GAP_OPERATION   op;
    u32             *param;
    u8              param_size;

} gap_operation_st;



u8 gap_core_reset(void);
u8 gap_core_obtain_resource(u16 conn_hdl);
u8 gap_core_release_resource(u16 conn_hdl);
GAP_ID gap_core_get_valid_id(u16 conn_hdl);
u8 gap_core_get_conn_num(void);
u8 gap_core_set_adv_param(gap_adv_param_st *adv_param);
u8 gap_core_set_adv_data(gap_adv_data_st *adv_data);
u8 gap_core_set_scan_response_data(gap_adv_data_st *scan_response_data);
u8 gap_core_start_adv(u32 timeout);
u8 gap_core_stop_adv(void);
u8 gap_core_set_scan_param(gap_scan_param_st *scan_param);
u8 gap_core_start_scan(u32 timeout, u8 filter_duplicates);
u8 gap_core_stop_scan(void);
u8 gap_core_get_public_address(bd_addr_st *public_addr);
u8 gap_core_set_public_address(bd_addr_st *public_addr);
u8 gap_core_get_own_used_address(u16 conn_hdl, bd_addr_st *own_addr);
u8 gap_core_get_peer_used_address(u16 conn_hdl, bd_addr_st *peer_addr);
u8 gap_core_read_white_list_size(u8 *white_list_size);
u8 gap_core_clear_white_list(void);
u8 gap_core_add_dev_to_white_list(bd_addr_st *addr);
u8 gap_core_remove_dev_from_white_list(bd_addr_st *addr);
u8 gap_core_update_conn_param(u16 conn_hdl, gap_conn_param_st *conn_param);
u8 gap_core_set_tx_power(u8 type, s8 tx_power);
u8 gap_core_get_rssi(u16 conn_hdl, u8 *rssi);
u8 gap_core_start_rssi(u16 conn_hdl);
u8 gap_core_stop_rssi(u16 conn_hdl);
u8 gap_core_disconnect(u16 conn_hdl, u8 reason);
u8 gap_core_update_security_level(GAP_ID id, GAP_SECURITY_LEVEL security_level, u8 enc_key_size);
u8 gap_core_check_security_level(GAP_ID id, GAP_SECURITY_LEVEL security_level);
u8 gap_core_generate_rand_addr(u8 addr_type, gap_irk_st *irk, bd_addr_st *rand_addr);
u8 gap_core_set_rand_addr(bd_addr_st *rand_addr);
u8 gap_core_read_local_version_info(gap_version_info_st *version_info);
u8 gap_core_read_local_supported_features(gap_le_features_st *le_features);
u8 gap_core_read_remote_version_info(u16 conn_hdl, gap_version_info_st *version_info);
u8 gap_core_read_remote_used_features(u16 conn_hdl, gap_le_features_st *le_features);
u8 gap_core_handle_connection_complete_event(gap_conn_complete_st *conn_complete);
u8 gap_core_handle_disconnection_complete_event(gap_disconn_complete_st *disconn_complete);
u8 gap_core_handle_conn_update_complete(u8 status, u16 conn_hdl, gap_conn_param_st *conn_param);
u8 gap_core_handle_unsupport_request(GAP_ID id, u8 identifier);
u8 gap_core_handle_version_exchanged_notify(GAP_ID id, u8 status, u8 version, u16 subversion, u16 manufacturer_name);
u8 gap_core_send_operation(GAP_ID id, gap_operation_st *operation);



#endif  /// end of _GAP_CORE_H_

