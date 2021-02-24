#ifndef _GAP_API_H_
#define _GAP_API_H_


#include "les_if/api/inc/svc_def.h"
#include "les_if/api/inc/les_def.h"



#define GAP_ADV_DATA_MAX            31
#define GAP_IRK_LEN                 16
#define GAP_LE_FEATURES_LEN         8



typedef enum
{
    GAP_SVCMD_SET_ADV_PARAM = GAP_SVC_NUM_MIN,
    GAP_SVCMD_SET_ADV_DATA,
    GAP_SVCMD_SET_SCAN_RESPONSE_DATA,
    GAP_SVCMD_START_ADV,
    GAP_SVCMD_STOP_ADV,
    GAP_SVCMD_SET_SCAN_PARAM,
    GAP_SVCMD_START_SCAN,
    GAP_SVCMD_STOP_SCAN,

    GAP_SVCMD_GET_PUBLIC_ADDR,
    GAP_SVCMD_SET_PUBLIC_ADDR,
    GAP_SVCMD_READ_WHITE_LIST_SIZE,
    GAP_SVCMD_CLEAR_WHITE_LIST,
    GAP_SVCMD_ADD_DEV_TO_WHITE_LIST,
    GAP_SVCMD_REMOVE_DEV_FROM_WHITE_LIST,
    GAP_SVCMD_CONN_PARAM_UPDATE_REQUEST,
    GAP_SVCMD_SET_TX_POWER,
    GAP_SVCMD_GET_RSSI,
    GAP_SVCMD_START_RSSI,
    GAP_SVCMD_STOP_RSSI,
    GAP_SVCMD_DISCONNECT,
    GAP_SVCMD_RESET,
    GAP_SVCMD_GENERATE_RAND_ADDR,
    GAP_SVCMD_SET_RAND_ADDR,
    GAP_SVCMD_READ_LOCAL_VERSION_INFO,
    GAP_SVCMD_READ_LOCAL_SUPPORTED_FEATURES,
    GAP_SVCMD_READ_REMOTE_VERSION_INFO,
    GAP_SVCMD_READ_REMOTE_USED_FEATURES,

} GAP_SVCMD;



typedef enum
{
    GAP_LES_EVENT_ADV_TIMEOUT = GAP_LES_EVENT_ID_MIN,
    GAP_LES_EVENT_CONN_COMPLETE,
    GAP_LES_EVENT_DISCONN_COMPLETE,
    GAP_LES_EVENT_SCAN_TIMEOUT,
    GAP_LES_EVENT_CONN_UPDATE_COMPLETE,
    GAP_LES_EVENT_CONN_PARAM_UPDATE_RESPONSE,
    GAP_LES_EVENT_CONN_PARAM_UPDATE_REQUEST_TIMEOUT,
    GAP_LES_EVENT_CONN_PARAM_UPDATE_REQUEST_DISCONNECT_COMPLETE,
    GAP_LES_EVENT_RSSI_CHANGED,
    GAP_LES_EVENT_ADV_REPORT,

} GAP_LES_EVENT;



typedef enum
{
    GAP_ROLE_NONE,
    GAP_ROLE_PERIPHERAL_NON_SWITCHABLE,
    GAP_ROLE_CENTRAL_NON_SWITCHABLE,
    GAP_ROLE_PERIPHERAL_SWITCHABLE,
    GAP_ROLE_CENTRAL_SWITCHABLE,

} GAP_ROLE;



typedef enum
{
    GAP_RAND_ADDR_STATIC,
    GAP_RAND_ADDR_PRIVATE_NON_RESOLVABLE,
    GAP_RAND_ADDR_PRIVATE_RESOLVABLE,

} GAP_RAND_ADDR;



typedef enum
{
    GAP_TX_TYPE_ADV_CHANNEL,
    GAP_TX_TYPE_CONN_CHANNEL,

} GAP_TX_TYPE;



typedef enum
{
    GAP_SECURITY_LEVEL_MODE_1_L1 = 0,
    GAP_SECURITY_LEVEL_MODE_1_L2,
    GAP_SECURITY_LEVEL_MODE_1_L3,
    GAP_SECURITY_LEVEL_MODE_1_L4,
    GAP_SECURITY_LEVEL_MODE_2_L1,
    GAP_SECURITY_LEVEL_MODE_2_L2,

} GAP_SECURITY_LEVEL;



typedef struct
{
    uint8_t     adv_type;
    uint8_t     own_addr_type;
    uint8_t     adv_channel_map;
    uint8_t     adv_filter_policy;
    uint16_t    adv_interval_min;
    uint16_t    adv_interval_max;
    bd_addr_st  direct_addr;

} gap_adv_param_st;



typedef struct
{
    uint8_t     data_len;
    uint8_t     data[GAP_ADV_DATA_MAX];

} gap_adv_data_st;




typedef struct
{
    uint8_t     scan_type;
    uint8_t     own_addr_type;
    uint8_t     scan_filter_policy;
    uint16_t    scan_interval;
    uint16_t    scan_window;

} gap_scan_param_st;



typedef struct
{
    uint16_t    conn_interval_min;
    uint16_t    conn_interval_max;
    uint16_t    slave_latency;
    uint16_t    conn_sup_timeout;

} gap_conn_param_st;



typedef struct
{
    uint8_t     irk[GAP_IRK_LEN];

} gap_irk_st;



typedef struct
{
    uint8_t     hci_version;
    uint16_t    hci_revision;
    uint16_t    manufactor_name;
    uint8_t     lmp_version;
    uint16_t    lmp_subversion;

} gap_version_info_st;



typedef struct
{
    uint8_t    features[GAP_LE_FEATURES_LEN];

} gap_le_features_st;



typedef struct
{
    uint8_t     status;
    uint8_t     role;
    uint8_t     master_clock_accuracy;
    uint16_t    conn_hdl;
    uint16_t    conn_latency;
    uint16_t    conn_interval;
    uint16_t    supervision_timeout;
    bd_addr_st  peer_addr;

} gap_conn_complete_st;



typedef struct
{
    uint8_t     status;
    uint8_t     reason;
    uint16_t    conn_hdl;

} gap_disconn_complete_st;



typedef struct
{
    uint16_t            conn_hdl;
    uint8_t             status;
    gap_conn_param_st   conn_param;

} gap_conn_update_complete_st;



typedef struct
{
    uint8_t     event_type;
    uint8_t     rssi;
    uint8_t     data_len;
    uint8_t     data[GAP_ADV_DATA_MAX];
    bd_addr_st  peer_addr;

} gap_adv_report_st;



typedef struct
{
    uint16_t    conn_hdl;
    uint16_t    result;

} gap_conn_param_update_response_st;



typedef struct 
{
    union
    {
        gap_conn_complete_st                conn_complete;                  /// GAP_LES_EVENT_CONN_COMPLETE
        gap_disconn_complete_st             disconn_complete;               /// GAP_LES_EVENT_DISCONN_COMPLETE
        gap_conn_update_complete_st         conn_update_complete;           /// GAP_LES_EVENT_CONN_UPDATE_COMPLETE
        gap_conn_param_update_response_st   conn_param_update_response;     /// GAP_LES_EVENT_CONN_PARAM_UPDATE_RESPONSE
        gap_adv_report_st                   adv_report;                     /// GAP_LES_EVENT_ADV_REPORT

    } data;

} gap_les_event_st;



DEF_SVC(GAP_SVCMD_SET_ADV_PARAM,                    uint32_t,   les_gap_set_adv_param(gap_adv_param_st *adv_param));
DEF_SVC(GAP_SVCMD_SET_ADV_DATA,                     uint32_t,   les_gap_set_adv_data(gap_adv_data_st *adv_data));
DEF_SVC(GAP_SVCMD_SET_SCAN_RESPONSE_DATA,           uint32_t,   les_gap_set_scan_response_data(gap_adv_data_st *scan_response_data));
DEF_SVC(GAP_SVCMD_START_ADV,                        uint32_t,   les_gap_start_adv(uint32_t timeout));
DEF_SVC(GAP_SVCMD_STOP_ADV,                         uint32_t,   les_gap_stop_adv(void));
DEF_SVC(GAP_SVCMD_SET_SCAN_PARAM,                   uint32_t,   les_gap_set_scan_param(gap_scan_param_st *scan_param));
DEF_SVC(GAP_SVCMD_START_SCAN,                       uint32_t,   les_gap_start_scan(uint32_t timeout, uint8_t filter_duplicates));
DEF_SVC(GAP_SVCMD_STOP_SCAN,                        uint32_t,   les_gap_stop_scan(void));
DEF_SVC(GAP_SVCMD_GET_PUBLIC_ADDR,                  uint32_t,   les_gap_get_public_addr(bd_addr_st *public_addr));
DEF_SVC(GAP_SVCMD_SET_PUBLIC_ADDR,                  uint32_t,   les_gap_set_public_addr(bd_addr_st *public_addr));
DEF_SVC(GAP_SVCMD_READ_WHITE_LIST_SIZE,             uint32_t,   les_gap_read_white_list_size(uint8_t *white_list_size));
DEF_SVC(GAP_SVCMD_CLEAR_WHITE_LIST,                 uint32_t,   les_gap_clear_white_list(void));
DEF_SVC(GAP_SVCMD_ADD_DEV_TO_WHITE_LIST,            uint32_t,   les_gap_add_dev_to_white_list(bd_addr_st *addr));
DEF_SVC(GAP_SVCMD_REMOVE_DEV_FROM_WHITE_LIST,       uint32_t,   les_gap_remove_dev_from_white_list(bd_addr_st *addr));
DEF_SVC(GAP_SVCMD_CONN_PARAM_UPDATE_REQUEST,        uint32_t,   les_gap_conn_param_update_request(uint16_t conn_hdl, gap_conn_param_st *conn_param));
DEF_SVC(GAP_SVCMD_SET_TX_POWER,                     uint32_t,   les_gap_set_tx_power(uint8_t type, int8_t tx_power));
DEF_SVC(GAP_SVCMD_GET_RSSI,                         uint32_t,   les_gap_get_rssi(uint16_t conn_hdl, int8_t *rssi));
DEF_SVC(GAP_SVCMD_START_RSSI,                       uint32_t,   les_gap_start_rssi(uint16_t conn_hdl));
DEF_SVC(GAP_SVCMD_STOP_RSSI,                        uint32_t,   les_gap_stop_rssi(uint16_t conn_hdl));
DEF_SVC(GAP_SVCMD_DISCONNECT,                       uint32_t,   les_gap_disconnect(uint16_t conn_hdl, uint8_t reason));
DEF_SVC(GAP_SVCMD_RESET,                            uint32_t,   les_gap_reset(void));
DEF_SVC(GAP_SVCMD_GENERATE_RAND_ADDR,               uint32_t,   les_gap_generate_rand_addr(uint8_t addr_type, gap_irk_st *irk, bd_addr_st *rand_addr));
DEF_SVC(GAP_SVCMD_SET_RAND_ADDR,                    uint32_t,   les_gap_set_rand_addr(bd_addr_st *rand_addr));
DEF_SVC(GAP_SVCMD_READ_LOCAL_VERSION_INFO,          uint32_t,   les_gap_read_local_version_info(gap_version_info_st *version_info));
DEF_SVC(GAP_SVCMD_READ_LOCAL_SUPPORTED_FEATURES,    uint32_t,   les_gap_read_local_supported_features(gap_le_features_st *le_features));
DEF_SVC(GAP_SVCMD_READ_REMOTE_VERSION_INFO,         uint32_t,   les_gap_read_remote_version_info(uint16_t conn_hdl, gap_version_info_st *version_info));
DEF_SVC(GAP_SVCMD_READ_REMOTE_USED_FEATURES,        uint32_t,   les_gap_read_remote_used_features(uint16_t conn_hdl, gap_le_features_st *le_features));



#endif  // end of _GAP_API_H_
