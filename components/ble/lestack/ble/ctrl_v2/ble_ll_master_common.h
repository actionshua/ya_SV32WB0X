#ifndef _BLE_LL_MASTER_COMMON_H_
#define _BLE_LL_MASTER_COMMON_H_

#include "ble/ctrl_v2/ble_ll.h"
#include "ble/ctrl_v2/ble_ll_hwif.h"
#include "ble/ctrl_v2/ble_ll_security.h"

/** ##############################################
 * master fsm
 * ############################################### */

typedef enum {
    BLE_LLCP_STATE_HARDFAULT = -1,
    //
    BLE_LLCP_STATE_IDLE,
    BLE_LLCP_STATE_CONNECTED,
}   BLE_LLCP_STATE;

typedef struct ble_llcp_info {
    BLE_LLCP_STATE state;
} ble_llcp_info_st;
    
#define BLE_LLCP_INFO_DEFAULT {     \
    .state  = BLE_LLCP_STATE_IDLE,  \
}

/**
 *  master encrypt:
 *
 */
enum {
    BLE_LLCP_MASTER_ENCRYPT_STATE_IDLE = 0,
    BLE_LLCP_MASTER_ENCRYPT_STATE_PAUSE_ENC_REQ,
    BLE_LLCP_MASTER_ENCRYPT_STATE_PAUSE_ENC_RSP,//send from slave
    //BLE_LLCP_MASTER_ENCRYPT_STATE_PAUSE_ENC_RSP_M,//send from master
    BLE_LLCP_MASTER_ENCRYPT_STATE_ENC_REQ,
    BLE_LLCP_MASTER_ENCRYPT_STATE_ENC_RSP,
    BLE_LLCP_MASTER_ENCRYPT_STATE_WAIT_START_ENC_REQ,
    BLE_LLCP_MASTER_ENCRYPT_STATE_START_ENC_REQ,
    BLE_LLCP_MASTER_ENCRYPT_STATE_START_ENC_RSP,//send from slave
    BLE_LLCP_MASTER_ENCRYPT_STATE_START_ENC_RSP_DONE,//send from master
    BLE_LLCP_MASTER_ENCRYPT_STATE_ERROR,
};
    
#define BLE_LLCP_MASTER_ENCRYPT_INFO_DEFAULT {               \
    .state          = BLE_LLCP_MASTER_ENCRYPT_STATE_IDLE,    \
}

typedef struct {
    s8  state;
    u8  ever_encrypted;
    u8  subrate_lock;
    u8  tmr_enabled;
    u8  own_proc_txq_msk;

    u8  skdm[BLE_LL_AES_CCM_SKDM_SIZE];
    u8  skds[BLE_LL_AES_CCM_SKDS_SIZE];
    u8  ivm [BLE_LL_AES_CCM_IVM_SIZE];
    u8  ivs [BLE_LL_AES_CCM_IVS_SIZE];
    ble_ll_cypher_key_un long_term_key;
    u32 rand_seed;
    
    ble_ll_pduq_st*         txq;
    ble_ll_clock_time_st    tmr_tstamp;

    u8 rand[BLE_LL_SECURITY_RAND_SIZE];
    u8 ediv[BLE_LL_SECURITY_EDIV_SIZE];
} ble_llcp_master_encrypt_info_st;

/**
 * llcp implementation constant
 *
 */
typedef struct ble_llcp_tx {
    
    // txq
    ble_ll_pduq_st own_proc_txq;    // txq: used for procedure initiated by own-site
    ble_ll_pduq_st peer_proc_txq;   // txq: used for procedure initiated by peer-site
    
    // txq grant/mask
    u8  own_proc_txq_locked;
    u8  own_proc_txq_lockby;
    u8  own_proc_txq_msk;
   
    u8  peer_proc_txq_locked;
    u8  peer_proc_txq_lockby;
    u8  peer_proc_txq_msk;

} ble_llcp_tx_st;
    
#define BLE_LLCP_TX_DEFAULT {           \
    .own_proc_txq_locked    = false,    \
    .own_proc_txq_lockby    = 0,        \
    .own_proc_txq_msk       = false,    \
    .peer_proc_txq_locked   = false,    \
    .peer_proc_txq_lockby   = 0,        \
    .peer_proc_txq_msk      = false,    \
}

/**
 * update timing
 *
 */
enum {
    BLE_LLCP_MASTER_UPDATE_TIMING_STATE_IDLE = 0,
    BLE_LLCP_MASTER_UPDATE_TIMING_STATE_WAIT_INSTANT,
    BLE_LLCP_MASTER_UPDATE_TIMING_STATE_ERROR,
};

typedef struct ble_llcp_master_update_timing_info {
    s8              state;
    ble_ll_pduq_st* txq;
} ble_llcp_master_update_timing_info_st;

#define BLE_LLCP_MASTER_UPDATE_TIMING_INFO_DEFAULT {     \
    .state  = BLE_LLCP_MASTER_UPDATE_TIMING_STATE_IDLE,  \
    .txq    = NULL,                                     \
}

/**
 * update ch
 *
 */
enum {
    BLE_LLCP_MASTER_UPDATE_CH_STATE_IDLE = 0,
    BLE_LLCP_MASTER_UPDATE_CH_STATE_WAIT_INSTANT,
    BLE_LLCP_MASTER_UPDATE_CH_STATE_ERROR,
};

typedef struct ble_llcp_master_update_ch_info {
    s8              state;
    ble_ll_pduq_st* txq;
} ble_llcp_master_update_ch_info_st;

#define BLE_LLCP_MASTER_UPDATE_CH_INFO_DEFAULT {     \
    .state  = BLE_LLCP_MASTER_UPDATE_CH_STATE_IDLE,  \
    .txq    = NULL,                                 \
}

/**
 * feature exchange
 *  - master part
 *
 */
enum {
    BLE_LLCP_MASTER_FEATURE_EXCHANGE_IDLE = 0,
    BLE_LLCP_MASTER_FEATURE_EXCHANGE_WAIT_RSP,
    BLE_LLCP_MASTER_FEATURE_EXCHANGE_DONE,
    BLE_LLCP_MASTER_FEATURE_EXCHANGE_ERROR,
};
    
typedef struct ble_llcp_master_feature_exchange_info {
    s8  state;
    ble_ll_pdu_st*          cpdu;
    ble_ll_clock_time_st    tmr_tstamp;
} ble_llcp_master_feature_exchange_info_st;

#define BLE_LLCP_MASTER_FEATURE_EXCHANGE_INFO_DEFAULT {  \
    .state  = BLE_LLCP_MASTER_FEATURE_EXCHANGE_IDLE,     \
}

/**
 * version exchange
 *
 */
enum {
    BLE_LLCP_VERSION_EXCHANGE_STATE_IDLE = 0,
    BLE_LLCP_VERSION_EXCHANGE_STATE_WAIT_IND,
    BLE_LLCP_VERSION_EXCHANGE_STATE_WAIT_IND_AUTONOMOUSLY,
    BLE_LLCP_VERSION_EXCHANGE_STATE_EXCHANGED,
    BLE_LLCP_VERSION_EXCHANGE_STATE_ERROR,
};
typedef struct ble_llcp_version_exchange_info {

    s8  state;
    u8  subrate_lock;

    ble_ll_pdu_st*          cpdu;
    ble_ll_clock_time_st    tmr_tstamp;

} ble_llcp_version_exchange_info_st;

#define BLE_LLCP_VERSION_EXCHANGE_INFO_DEFAULT {    \
    .state  = BLE_LLCP_VERSION_EXCHANGE_STATE_IDLE, \
    .cpdu   = NULL,                                 \
}

/**
 * data length change
 *  - master part
 *
 */
enum {
    BLE_LLCP_MASTER_DATA_LENGTH_CHANGE_IDLE = 0,
    BLE_LLCP_MASTER_DATA_LENGTH_CHANGE_WAIT_RSP,
};

typedef struct ble_llcp_data_length_change_info {
    s8  state;
    ble_ll_clock_time_st    tmr_tstamp;
} ble_llcp_data_length_change_info_st;

#define BLE_LLCP_DATA_LENGTH_CHANGE_INFO_DEFAULT {       \
    .state  = BLE_LLCP_MASTER_DATA_LENGTH_CHANGE_IDLE,  \
}

enum {
    BLE_LLCP_MASTER_TERMINATE_STATE_IDLE = 0,
    BLE_LLCP_MASTER_TERMINATE_STATE_2TERMINATE,
};

typedef struct ble_llcp_master_termination_info {
    s8  state;
    u8  txq_msk;
} ble_llcp_master_termination_info_st;

#define BLE_LLCP_MASTER_TERMINATION_INFO_DEFAULT {       \
    .state      = BLE_LLCP_MASTER_TERMINATE_STATE_IDLE,  \
    .txq_msk    = false,                                \
}

typedef struct ble_ll_master_info {

    // # parameters
    ble_ll_conn_timing_param_st timing_param;
    ble_datach_map_st           ch_map;

    // # parameters, fixed
    u8  ch_hop;
    u16 sca_over2exp20;

    // # air_event_mask
    u8  air_evt_msk;

    // # timing:
    // ## sync (handle by glue)
    BLE_LL_INSTANT          sync_instant;
    ble_ll_clock_time_st    sync_tstamp;    // to calculate anchor
    // ## valid (handle by glue)
    BLE_LL_INSTANT          valid_instant;
    ble_ll_clock_time_st    valid_tstamp;   // to calculate supervison_tout
    // ## timer (handle by glue)
    BLE_LL_INSTANT          tmr_instant;
    ble_ll_clock_time_st    tmr_tstamp;     // to calculate supervison_tout

    // # state
    s8                      state;
    u8                      unmap_ch;
    BLE_LL_INSTANT          instant;
    u8                      disconn_reason;

    // ## state accessaries
    ble_ll_clock_time_st    state_tstamp;

    // # subrate algorithm
    BLE_LL_INSTANT  idle_instant;
    u16             latency;

    // # schedule
    // ## type
    u8  sche_enabled;
    u8  sche_window_enabled;
    u8  wakelock;
    // ## profile
    ble_ll_conn_window_st       anchor_window;
    ble_ll_anchor_profile_st    anchor_profile;

    // # datapath
    u8  acl_tx_enabled;
    u8  acl_rx_enabled;
    // ## security
    u8  tx_is_encrypted;
    u8  rx_is_encrypted;
    //pdu length
    ble_data_length_st datalen_info;
    // ## log
    u32 acl_tx_cnt;
    u32 acl_tx_completed_cnt;
    u32 acl_rx_cnt;
    u32 not_synced_event_cnt;
    u32 not_valid_event_cnt;
    u32 active_event_cnt;
    u16 consecutive_not_sync_event_cnt;
    u16 consecutive_not_sync_event_cnt_max;
    u16 consecutive_not_valid_event_cnt;
    u16 consecutive_not_valid_event_cnt_max;
    s16 measured_ppm_max;

    // ## tx path buffering
    ble_ll_pduq_st  acl_txq;
    ble_ll_pduq_st  encrypted_txq;
    u8              tx_pdus_2send;
    struct buf_list acl_tx_buf;

    // ## rx path flow control
    u8  rx_pdu_cnt_max;

    // ## from pdu, latch under LLCP cmd
    BLE_LL_INSTANT              action_instant;
    ble_ll_conn_update_param_st update_param;

    // # notify2host
    u8  host_notification_msk;
    u8  host_notified;

    // # 
    u32 rx_crc_count;

    //related global variable
    u16 conn_id;
    ble_ll_hwif_cfg_st         *phwif_cfg;
    ble_ll_hwif_trx_ring_st    *ptrx_ring;
    ble_ll_hwif_data_flag_st   *pdata_flag;

    ble_ll_aes_ccm_sk_st       aes_ccm_sk;
    ble_ll_peer_info_st        peer_info;
    ble_ll_rssi_st             rssi_info;

    //llcp
    ble_llcp_info_st llcp_info;
//    ble_llcp_tx_st llcp_tx;
    ble_llcp_master_update_timing_info_st update_timing_info;
    ble_llcp_master_update_ch_info_st update_ch_info;
    ble_llcp_master_encrypt_info_st encrypt_info;
    ble_llcp_master_feature_exchange_info_st feature_exchange_info;
    ble_llcp_version_exchange_info_st version_exchange_info;
    ble_llcp_data_length_change_info_st data_length_change_info;
    ble_llcp_master_termination_info_st termination_info;
} ble_ll_master_info_st;

#endif // _BLE_LL_MASTER_COMMON_H_
