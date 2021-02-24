#ifndef _BLE_LL_IF_H_
#define _BLE_LL_IF_H_

#include "ssv_types.h"
#include "ble/ble_lib_v2.h"

// ########################################
// # link control command
// ########################################
s8  ble_ll_cmd2status_disconnect (
    u16 connection_handle,
    u8  reason
    );

s8  ble_ll_cmd2status_read_remote_version_information (
    u16 connection_handle
    );

// ########################################
// # control baseband command
// ########################################
s8  ble_ll_cmd2complete_set_event_mask (
    u64 event_mask
    );

s8  ble_ll_cmd2complete_reset();

#define BLE_LL_TRANSMIT_POWER_TYPE_CURRENT 0
#define BLE_LL_TRANSMIT_POWER_TYPE_MAX     1
s8  ble_ll_cmd2complete_read_transmit_power_level (
    u16 connection_handle,
    u8  type,
    // return param
    u8* transmit_power_level
    );

s8  ble_ll_cmd2complete_set_controller_to_host_flow_control();   // not supported
s8  ble_ll_cmd2complete_host_buffer_size();                      // not supported
s8  ble_ll_cmd2complete_host_number_of_completed_packets();      // not supported
s8  ble_ll_cmd2complete_read_le_host_support();                  // not supported
s8  ble_ll_cmd2complete_write_le_host_support();                 // not supported

// ########################################
// # information parameters command
// ########################################
typedef struct ble_ll_ver {

    u8  hci_ver;
    u8  lmp_ver;
    u16 hci_rev;/*sub version*/
    u16 lmp_rev;/*link layer version*/
    u16 manufactor;/*company id*/

} ble_ll_ver_st;

s8  ble_ll_cmd2complete_read_local_version_information (
    // return param
    ble_ll_ver_st* ll_ver
    );

typedef struct ble_ll_patch_version {
    u16 value;
    u16 valid;
} ble_ll_patch_version_st;

extern NV_DATA ble_ll_patch_version_st g_ble_ll_patch_version;

s8  ble_ll_cmd2complete_read_local_supported_features (
    // return param
    u8* lmp_features
    );

s8  ble_ll_cmd2complete_read_local_supported_commands (
    // return param
    u8* support_commands
    );
s8  ble_ll_cmd2complete_read_buffer_size(); // not support

s8  ble_ll_cmd2complete_read_bd_addr (
    // return param
    ble_addr_st* addr
    );

// ########################################
// # status parameters command
// ########################################
s8  ble_ll_cmd2complete_read_rssi (
    u16 handle,
    // return param
    u8* rssi
    );

// ########################################
// # LE controller command
// ########################################
s8  ble_ll_cmd2complete_le_set_event_mask (
    u64 le_event_mask
    );

s8  ble_ll_cmd2complete_le_read_buffer_size (
    // return param
    u16* le_data_packet_length,
    u8*  total_num_le_data_packets
    );

s8  ble_ll_cmd2complete_le_read_local_supported_features (
    // return param
    u8* le_features
    );

s8  ble_ll_cmd2complete_le_set_random_address (
    ble_addr_st*    random_addr
    );

#define BLE_LL_ADVERTISING_TYPE_ADV_IND         0x00
#define BLE_LL_ADVERTISING_TYPE_ADV_DIRECT_IND  0x01
#define BLE_LL_ADVERTISING_TYPE_ADV_SCAN_IND    0x02
#define BLE_LL_ADVERTISING_TYPE_ADV_NONCONN_IND 0x03
#define BLE_LL_ADVERTISING_TYPE_ADV_SCAN_RSP    0x04
//
#define BLE_LL_ADVERTISING_FILTER_POLICY_FROM_ANY                   0x00
#define BLE_LL_ADVERTISING_FILTER_POLICY_SCAN_REQ_FROM_WHITELIST    0x01
#define BLE_LL_ADVERTISING_FILTER_POLICY_CONN_REQ_FROM_WHITELIST    0x02
#define BLE_LL_ADVERTISING_FILTER_POLICY_ALL_FROM_WHITELIST         0x03

typedef struct ble_ll_advertising_parameters {

    ble_addr_st direct_address;
    u16         advertising_interval_min;
    u16         advertising_interval_max;
    u8          advertising_type;
    u8          own_address_type;
    u8          advertising_channel_map;
    u8          advertising_filter_policy;
    //
    u8  apdu_type;  // for link-layer implementation easy
    u8          low_duty;  // for link-layer implementation easy

} ble_ll_advertising_parameters_st;

extern NV_DATA ble_ll_advertising_parameters_st g_ble_ll_advertising_parameters;

s8  ble_ll_cmd2complete_le_set_advertising_parameters (
    u16                 advertising_interval_min,
    u16                 advertising_interval_max,
    u8                  advertising_type,
    u8                  own_address_type,
    const ble_addr_st*  direct_address,
    u8                  advertising_channel_map,
    u8                  advertising_filter_policy
    );

s8  ble_ll_cmd2complete_le_get_advertising_type (
    u8* advertising_type
    );

s8  ble_ll_cmd2complete_le_read_advertising_channel_tx_power (
    // return param
    u8* transmit_power_level
    );

#define BLE_LL_ADATA_LEN_MAX (31)
extern NV_DATA u8 g_ble_ll_advertising_data[];
extern NV_DATA u8 g_ble_ll_advertising_data_length;

s8  ble_ll_cmd2complete_le_set_advertising_data (
    u8          advertising_data_length,
    const u8*   advertising_data
    );

s8  ble_ll_cmd2complete_le_set_scan_response_data (
    u8          scan_response_data_length,
    const u8*   scan_response_data
    );

s8  ble_ll_cmd2complete_le_set_advertise_enable (
    u8  enable
    );

#define BLE_LL_LE_SCAN_TYPE_PASSIVE 0x00
#define BLE_LL_LE_SCAN_TYPE_ACTIVE  0x01
//
#define BLE_LL_SCANNING_FILTER_POLICY_FROM_ANY          0x00
#define BLE_LL_SCANNING_FILTER_POLICY_FROM_WHITELIST    0x01

typedef struct ble_ll_scan_parameters {

    u16 le_scan_interval;
    u16 le_scan_window;
    u8  le_scan_type;
    u8  own_address_type;
    u8  scanning_filter_policy;

} ble_ll_scan_parameters_st;

extern ble_ll_scan_parameters_st g_ble_ll_scan_parameters;

s8  ble_ll_cmd2complete_le_set_scan_parameters (
    u8  le_scan_type,
    u16 le_scan_interval,
    u16 le_scan_window,
    u8  own_address_type,
    u8  scanning_filter_policy
    );

s8  ble_ll_cmd2complete_le_set_scan_enable (
    u8  le_scan_enable,
    u8  filter_duplicates
    );

s8  ble_ll_cmd2complete_le_read_white_list_size (
    u8* white_list_size
    );

s8  ble_ll_cmd2complete_le_clear_white_list();

s8  ble_ll_cmd2complete_le_add_device_to_white_list (
    const ble_addr_st* address
    );

s8  ble_ll_cmd2complete_le_remove_device_from_white_list (
    const ble_addr_st* address
    );

s8  ble_ll_cmd2complete_le_read_channel_map (
    u16 connection_handle,
    // return param
    ble_datach_map_st* le_channel_map
    );

typedef ble_ll_cypher_data_un ble_ll_cypher_key_un;

s8  ble_ll_cmd2complete_le_encrypt (
    const u8*   key,
    const u8*   plaintext_data,
    // return param
    u8* encrypted_data
    );

s8  ble_ll_cmd2complete_le_rand (
    // return param
    u64* random_number
    );

s8  ble_ll_cmd2complete_le_long_term_key_request_reply (
    u16         connection_handle,
    const u8*   long_term_key
    );

s8  ble_ll_cmd2complete_le_long_term_key_request_negative_reply (
    u16 connection_handle
    );

s8  ble_ll_cmd2complete_le_read_supported_states (
    // return param
    u64* le_states
    );

s8  ble_ll_cmd2complete_le_receiver_test (
    u8  rx_frequency
    );

s8  ble_ll_cmd2complete_le_transmitter_test (
    u8  tx_frequency,
    u16 number_of_packets,
    u8  length_of_test_data,
    u8  packet_payload
    );

s8  ble_ll_cmd2complete_le_test_end (
    u16* number_of_packets
    );

typedef struct ble_ll_set_host_data_length {
    u16 MaxTxOxts;
    u16 MaxTxTime;
} ble_ll_set_host_data_length_st;

s8  ble_ll_cmd2complete_le_set_data_length (
    u16 connection_handle, u16 maxtxoctets, u16 maxtxtime
    );

s8  ble_ll_cmd2complete_le_read_suggested_data_length (
    u16 *datalen_buf
    );

s8  ble_ll_cmd2complete_le_write_suggested_data_length (
    u16 maxtxoctets, u16 maxtxtime
    );

// ########################################
// # LE controller command (master only)
// ########################################
typedef struct ble_ll_create_connection {

    u16         le_scan_interval;
    u16         le_scan_window;
    u8          initiator_filter_policy;
    ble_addr_st peer_address;
    u8          own_address_type;
    u16         conn_interval_min;
    u16         conn_interval_max;
    u16         conn_latency;
    u16         supervision_timeout;
    u16         minimum_ce_length;
    u16         maximum_ce_length;

} ble_ll_create_connection_st;

extern NV_DATA ble_ll_create_connection_st g_ble_ll_create_connection;

s8  ble_ll_cmd2status_le_create_connection                   (
    u16         le_scan_interval,
    u16         le_scan_window,
    u8          initiator_filter_policy,
    ble_addr_st* p_peer_address,
    u8          own_address_type,
    u16         conn_interval_min,
    u16         conn_interval_max,
    u16         conn_latency,
    u16         supervision_timeout,
    u16         minimum_ce_length,
    u16         maximum_ce_length
    );
s8  ble_ll_cmd2complete_le_create_connection_cancel          ();
typedef struct ble_ll_conn_update {
    u8          conn_handle;
    u16         conn_interval_min;
    u16         conn_interval_max;
    u16         conn_latency;
    u16         supervision_timeout;
    u16         minimum_ce_length;
    u16         maximum_ce_length;
} ble_ll_conn_update_st;

extern NV_DATA ble_ll_conn_update_st g_ble_ll_conn_update;
s8  ble_ll_cmd2status_le_connection_update                   (
    u16         conn_handle,
    u16         conn_interval_min,
    u16         conn_interval_max,
    u16         conn_latency,
    u16         supervision_timeout,
    u16         minimum_ce_length,
    u16         maximum_ce_length
);

typedef struct ble_ll_set_host_ch_classification {
    u8          ch_map[BLE_DATACH_MAP_SIZE];
} ble_ll_set_host_ch_classification_st;
extern NV_DATA ble_ll_set_host_ch_classification_st g_ble_ll_set_host_ch_classification;
s8  ble_ll_cmd2complete_le_set_host_channel_classification   (u8 ch_map[BLE_DATACH_MAP_SIZE]);

s8  ble_ll_cmd2status_le_read_remote_used_features           (u16 connection_handle);
s8  ble_ll_cmd2status_le_start_encryption(
    u16 connection_handle,
    u8* random_number,
    u16 encrypted_diversifier,
    u8* long_term_key);

// ########################################
// # SSV-VS command
// ########################################
s8  ble_ll_cmd2complete_read_latched_remote_version_information (
    u16 connection_handle,
    // return param
    ble_ll_ver_st* ll_ver
    );

s8  ble_ll_cmd2complete_le_read_latched_remote_used_features (
    u16 connection_handle,
    // return param
    u8* le_features
    );

s8  ble_ll_cmd2complete_le_read_latched_own_used_device_address (
    u16 connection_handle,
    // return param
    ble_addr_st* address
    );

s8  ble_ll_cmd2complete_le_read_latched_peer_used_device_address (
    u16 connection_handle,
    // return param
    ble_addr_st* address
    );

s8  ble_ll_cmd2complete_le_set_advertising_channel_tx_power (
    u8  transmit_power_level
    );

s8  ble_ll_cmd2complete_le_set_transmit_power_level (
    u8  transmit_power_level
    );

s8  ble_ll_cmd2complete_le_set_bd_addr (
    const ble_addr_st* addr
    );

s8  ble_ll_cmd2complete_set_air_event_notify_mask (
    u8  mask
    );

s8  ble_ll_cmd2complete_set_protocol_enable (
    u8 enable
    );

s8  ble_ll_cmd2complete_set_protocol_resume(
    );

s8  ble_ll_cmd2complete_slave_subrate(
    u8  enable,
    u8  minimum_tx_latency
    );

typedef enum {
    ADVERTISING_CHANNEL_FAVOR_ADVERTISER = 0,
    ADVERTISING_CHANNEL_FAVOR_SCANNER_INITIATOR,
}   ADVERTISING_CHANNEL_PRIORITY;

s8  ble_ll_cmd2complete_set_advertising_channel_priority(
    ADVERTISING_CHANNEL_PRIORITY priority
    );

s8  ble_ll_cmd2complete_set_jammer_enable(
    u8 enable
    );

s8  ble_ll_cmd2complete_set_scan_early_stopper_enable(
    u8 enable
    );

s8  ble_ll_cmd2complete_set_phy_agc_enable(
    u8 enable
    );

s8  ble_ll_cmd2complete_set_air_event_application_irq_enable(
    u8 enable
    );

s8  ble_ll_cmd2complete_set_air_event_early_notify_time(
    u8 time
    );


s8  ble_ll_cmd2complete_acl_evt_to_external_host();
s8  ble_ll_cmd2complete_ssv_set_bd_addr (ble_addr_st* set_address);
s8  ble_ll_cmd2complete_set_default_public_address_low  (const u8* address_low);
s8  ble_ll_cmd2complete_set_default_public_address_high (const u8* address_high);

extern NV_DATA u8 g_ble_ll_acl_evt_to_external_host;

// ########################################
// # send acl
// ########################################
#if (ACL_TX_TYPE == 1)
s8 ble_ll_send_acl(u16     connection_handle, u16 pb_flag, const u8 *acl, u16 acllen);
#else
s8  ble_ll_send_acl (
    u16         connection_handle,
    ble_pdu_st* pdu
    );
#endif
// ########################################
// PDU pools
// ########################################
extern NV_DATA ble_pdu_pool_st g_ble_tx_pdu_pool;
extern NV_DATA ble_pdu_pool_st g_ble_rx_pdu_pool;
extern struct buf_list g_hciacl_pool;

// ########################################
// # to external host:
//   if true, would send ll evt/acl as les_evt
// ########################################
extern NV_DATA u8 g_ble_ll_2external_host;

// ########################################
// SSV VS SUBEVT code (used with evt EVT_CODE 0xff)
// ########################################
#define BLE_LL_EVT_CODE_SSV 0xff
typedef enum {
    BLE_LL_SSV_SUBEVT_AIR_EVT_EARLY_NOTIFY =  1,
    BLE_LL_SSV_SUBEVT_AIR_EVT_END_NOTIFY,
}   BLE_LL_SSV_SUBEVT_CODE;

// ########################################
// report HCI-event through message
// ########################################
#define BLE_LL_EVT_CODE(EVT_CODE, SUBEVT_CODE) (((EVT_CODE) << 8) | (SUBEVT_CODE))
typedef struct ble_ll_evt_hci_general {

    union {
        u32 param0;
        u32 type_w;
        struct {
            u32 code:16;
            u32 ind_:16;    // fixed constant: 0x0400 (0x04: ind, 0x00: op_space, constant 0)
        };
    };
    u32 param1;
    u32 param2;
    u32 param3;

} ble_ll_evt_hci_general_st;

/**
 * disconnection_complete
 */
typedef struct ble_ll_evt_hci_disconnection_complete {

    union {
        u32 param0;
        u32 type_w;
    };

    union {
        u32 param1;
        struct {
            u32 status              :8;
            u32 reason              :8;
            u32 connection_handle   :16;
        };
    };

    u32 param2; // reserved
    u32 param3; // reserved

} ble_ll_evt_hci_disconnection_complete_st;

/**
 * encryption_change
 */
typedef struct ble_ll_evt_hci_encryption_change {

    union {
        u32 param0;
        u32 type_w;
    };

    union {
        u32 param1;
        struct {
            u32 status              :8;
            u32 encryption_enabled  :8;
            u32 connection_handle   :16;
        };
    };

    u32 param2; // reserved
    u32 param3; // reserved

} ble_ll_evt_hci_encryption_change_st;

/**
 * read_remote_version_information_complete
 */
typedef struct ble_ll_evt_hci_read_remote_version_information_complete {

    union {
        u32 param0;
        u32 type_w;
    };

    union {
        u32 param1;
        struct {
            u32 status              :8;
            u32                     :8;
            u32 connection_handle   :16;
        };
    };

    union {
        u32 param2;
        struct {
            u32 version     :8;
            u32             :8;
            u32 subversion  :16;
        };
    };

    union {
        u32 param3;
        struct {
            u32 manufacturer_name   :16;
            u32                     :16;
        };
    };

} ble_ll_evt_hci_read_remote_version_information_complete_st;

/**
 * number_of_completed_packets
 */
typedef struct ble_ll_evt_hci_number_of_completed_packets {

    union {
        u32 param0;
        u32 type_w;
    };

    union {
        u32 param1;
        struct {
            u32 connection_handle               :16;
            u32 host_num_of_completed_packets   :16;
        };
    };

    u32 param2; // reserved
    u32 param3; // reserved

} ble_ll_evt_hci_number_of_completed_packets_st;

/**
 * data_buffer_overflow
 */
typedef struct ble_ll_evt_hci_data_buffer_overflow {

    union {
        u32 param0;
        u32 type_w;
    };

    union {
        u32 param1;
        struct {
            u32 link_type   :8;     // fixed constant: (0x01: ACL)
            u32             :24;
        };
    };

    u32 param2; // reserved
    u32 param3; // reserved

} ble_ll_evt_hci_data_buffer_overflow_st;

/**
 * encryption_key_refresh_complete
 */
typedef struct ble_ll_evt_hci_encryption_key_refresh_complete {

    union {
        u32 param0;
        u32 type_w;
    };

    union {
        u32 param1;
        struct {
            u32 status              :8;
            u32                     :8;
            u32 connection_handle   :16;
        };
    };

    u32 param2; // reserved
    u32 param3; // reserved

} ble_ll_evt_hci_encryption_key_refresh_complete_st;

/**
 * le_connection_complete
 *
 */
s8  ble_ll_evt_hci_le_connection_complete_pdu_parser (
    const ble_pdu_st* pdu,
    // return param
    u16*    conn_interval,
    u16*    conn_latency,
    u16*    supervision_timeout,
    u8*     master_clock_accuracy,
    u8*     peer_addr_type,
    u8      peer_addr_value[BLE_ADDR_SIZE]
    );
s8  ble_ll_evt_hci_le_connection_complete_pdu_master_parser (
    const ble_pdu_st* pdu,
    // return param
    u16*    conn_interval,
    u16*    conn_latency,
    u16*    supervision_timeout,
    u8*     master_clock_accuracy,
    u8*     peer_addr_type,
    u8      peer_addr_value[BLE_ADDR_SIZE]
    );
typedef struct ble_ll_evt_hci_le_connection_complete {

    union {
        u32 param0;
        u32 type_w;
    };

    union {
        u32 param1;
        struct {
            u32 status              :8;
            u32 role                :8;
            u32 connection_handle   :16;
        };
    };

    union {
        u32 param2;
        //
        const ble_pdu_st* pdu;
    };

    u32 param3; // reserved

} ble_ll_evt_hci_le_connection_complete_st;

/**
 * le_advertising_report
 */
s8  ble_ll_evt_hci_le_advertising_report_pdu_parser(
    const ble_pdu_st*   pdu,
    // return param
    u8*     peer_addr_type,
    u8      peer_addr_value[BLE_ADDR_SIZE],
    u8**    data,
    u8*     length
    );
typedef struct ble_ll_evt_hci_le_advertising_report {

    union {
        u32 param0;
        u32 type_w;
    };

    union {
        u32 param1;
        //
        struct {
            u8  event_type;
            u8  rssi;
        };
    };

    union {
        u32 param2;
        //
        ble_pdu_st* pdu;
    };

    u32 param3;

} ble_ll_evt_hci_le_advertising_report_st;

/**
 * le_connection_update_complete
 */
typedef struct ble_ll_evt_hci_le_connection_update_complete {

    union {
        u32 param0;
        u32 type_w;
    };

    union {
        u32 param1;
        struct {
            u32 status              :8;
            u32                     :8;
            u32 connection_handle   :16;
        };
    };

    union {
        u32 param2;
        struct {
            u16 conn_interval;
            u16 conn_latency;
        };
    };

    union {
        u32 param3;
        struct {
            u16 supervision_timeout;
        };
    };

} ble_ll_evt_hci_le_connection_update_complete_st;

/**
 * le_read_remote_used_features_complete
 */
typedef struct ble_ll_evt_hci_le_read_remote_used_features_complete {

    union {
        u32 param0;
        u32 type_w;
    };

    union {
        u32 param1;
        struct {
            u32 status              :8;
            u32                     :8;
            u32 connection_handle   :16;
        };
    };

    union {
        u32 param2[2]; // param[3:2]
        //
        u8 le_features[8];
    };

} ble_ll_evt_hci_le_read_remote_used_features_complete_st;

/**
 * le_long_term_key_request
 */
typedef struct ble_ll_evt_hci_le_long_term_key_request {

    union {
        u32 param0;
        u32 type_w;
    };

    union {
        u32 param1;
        struct {
            u16 connection_handle;
            u8  encrypted_diversifier[2];
        };
    };

    union {
        u32 param2[2]; // param[3:2]
        //
        u8 random_number[8];
    };

} ble_ll_evt_hci_le_long_term_key_request_st;

/**
 * le_data_length_change
 */
typedef struct ble_ll_evt_hci_le_data_length_change {

    union {
        u32 param0;
        u32 type_w;
    };

    union {
        u32 param1;
        struct {
            u16 connection_handle;
            u16 MaxTxOctets;
        };
    };

    union {
        u32 param2;
        struct {
            u16 MaxTxTime;
            u16 MaxRxOctets;
        };
    };

    union {
        u32 param3;
        struct {
            u16 MaxRxTime;
            u16 reserved;
        };
    };
} ble_ll_evt_hci_le_data_length_change_st;

/**
 * ssv_version_exchanged_notify
 */
typedef struct ble_ll_evt_hci_ssv_version_exchanged_notify {

    union {
        u32 param0;
        u32 type_w;
    };

    union {
        u32 param1;
        struct {
            u32 status              :8;
            u32                     :8;
            u32 connection_handle   :16;
        };
    };

    union {
        u32 param2;
        struct {
            u32 version     :8;
            u32             :8;
            u32 subversion  :16;
        };
    };

    union {
        u32 param3;
        struct {
            u32 manufacturer_name   :16;
            u32                     :16;
        };
    };

} ble_ll_evt_hci_ssv_version_exchanged_notify_st;

typedef union ble_ll_evt_hci {

    ble_ll_evt_hci_general_st                                   general;
    ble_ll_evt_hci_disconnection_complete_st                    disconnection_complete;
    ble_ll_evt_hci_encryption_change_st                         encryption_change;
    ble_ll_evt_hci_read_remote_version_information_complete_st  read_remote_version_information_complete;
    ble_ll_evt_hci_number_of_completed_packets_st               number_of_completed_packets;
    ble_ll_evt_hci_data_buffer_overflow_st                      data_buffer_overflow;
    ble_ll_evt_hci_encryption_key_refresh_complete_st           encryption_key_refresh_complete;
    ble_ll_evt_hci_le_connection_complete_st                    le_connection_complete;
    ble_ll_evt_hci_le_advertising_report_st                     le_advertising_report;
    ble_ll_evt_hci_le_connection_update_complete_st             le_connection_update_complete;
    ble_ll_evt_hci_le_read_remote_used_features_complete_st     le_read_remote_used_features_complete;
    ble_ll_evt_hci_le_long_term_key_request_st                  le_long_term_key_request;
    ble_ll_evt_hci_le_data_length_change_st                     le_data_length_change;
    ble_ll_evt_hci_ssv_version_exchanged_notify_st              ssv_version_exchanged_notify;

} ble_ll_evt_hci_un;

#if (1 == BLE_AGGR_ADV_REPORT)
#define AGGR_ADV_RPT_NUM_MAX    6 //ADV report len=2+41*num < HCI_ASYNC_EVT_LEN_MAX   255
typedef struct ble_ll_evt_hci_aggr_adv_rpt_st {
    ble_ll_evt_hci_un                     le_advertising_report_aggr[AGGR_ADV_RPT_NUM_MAX];
} ble_ll_evt_hci_aggr_adv_rtp;

#endif

typedef struct ble_ll_acl {

    union {
        u32 param0;
        u32 type_w;
        struct {
            u32 connection_handle   :16;
            u32 ind_                :16; // fixed, 0x0200
        };
    };
    union {
        u32         param1;
        ble_pdu_st* pdu;
        ble_hci_acl_buf_st* aclbuf;
    };
    u32 param2;
    u32 param3;

} ble_ll_acl_st;
void ble_hal_aclbuf_init();
void ble_hal_aclbuf_init();

#endif  // _BLE_LL_IF_H_
