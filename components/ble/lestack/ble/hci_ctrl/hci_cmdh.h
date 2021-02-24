#ifndef _HCI_CMDH_H_
#define _HCI_CMDH_H_

#include "ssv_types.h"
#include "lib/condor_ssv_lib.h"

#include "ble/hci_lib.h"
#include "ble/hci_ctrl/hci_config.h"

#ifdef _HCI_SUPPORT_CMD_NOP_
s32 hci_cmdh_nop(const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
#endif

#ifdef _HCI_SUPPORT_CMD_LINK_CONTROL_
s32 hci_cmdh_disconnect                         (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_read_remote_version_information    (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
#endif

#ifdef _HCI_SUPPORT_CMD_CONTROL_BASEBAND_
s32 hci_cmdh_set_event_mask                         (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_reset                                  (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_read_transmit_power_level              (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
// s32 hci_cmdh_set_controller_to_host_flow_control    (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
// s32 hci_cmdh_host_buffer_size                       (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
// s32 hci_cmdh_host_number_of_completed_packets       (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
// s32 hci_cmdh_read_le_host_support                   (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
// s32 hci_cmdh_write_le_host_support                  (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
#endif

#ifdef _HCI_SUPPORT_CMD_INFORMATION_PARAMETERS_
s32 hci_cmdh_read_local_version_information (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_read_local_supported_features  (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_read_local_supported_commands  (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
// s32 hci_cmdh_read_buffer_size               (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_read_bd_addr                   (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
#endif

#ifdef _HCI_SUPPORT_CMD_STATUS_PARAMETERS_
s32 hci_cmdh_read_rssi(const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
#endif

#ifdef _HCI_SUPPORT_CMD_LE_CONTROLLER_
s32 hci_cmdh_le_set_event_mask                          (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_read_buffer_size                        (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_read_local_supported_features           (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_set_random_address                      (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_set_advertising_parameters              (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_read_advertising_channel_tx_power       (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_set_advertising_data                    (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_set_scan_response_data                  (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_set_advertise_enable                    (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_set_scan_parameters                     (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_set_scan_enable                         (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_create_connection                       (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_create_connection_cancel                (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_read_white_list_size                    (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_clear_white_list                        (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_add_device_to_white_list                (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_remove_device_from_white_list           (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_connection_update                       (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_set_host_channel_classification         (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_read_channel_map                        (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_read_remote_used_features               (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_encrypt                                 (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_rand                                    (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_start_encryption                        (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_long_term_key_request_reply             (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_long_term_key_request_negative_reply    (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_read_supported_states                   (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_receiver_test                           (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_transmitter_test                        (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_test_end                                (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_set_data_length(const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_read_suggested_default_data_length(const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_write_suggested_default_data_length(const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_read_maximum_data_length(const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_le_read_transmit_power(const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
#endif

#ifdef _HCI_SUPPORT_CMD_SSV_CMD_
s32 hci_cmdh_ssv_slave_subrate                      (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_ssv_set_advertising_channel_priority   (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_ssv_acl_evt_to_external_host           (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_ssv_set_bd_addr(const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
s32 hci_cmdh_ssv_le_transmitter_test                (const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);
#endif

#endif // _HCI_CMDH_H_
