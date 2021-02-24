#ifndef _BLE_LL_H_
#define _BLE_LL_H_

/** ##############################################
 * define constant/structure and fx of link-layer
 *  - would be used by LL_FSM/LLCP
 * ############################################### */
#include "ble_config.h"
#include "ble/ble_lib_v2.h"
#include "ble/ctrl_v2/ble_ll_if.h"

/** ##############################################
 * global constant
 * ############################################### */
// # version
#define BLE_LL_LOCAL_VER_HCI_VER      0x06        // Core Specification 4.0
#define BLE_LL_LOCAL_VER_HCI_REV      0x0000
#define BLE_LL_LOCAL_VER_LMP_VER      0x09        // Core Specification 5.0
#define BLE_LL_LOCAL_VER_MANUFACTOR   0x039B
//
#ifdef FW_VER
#define BLE_LL_LOCAL_VER_LMP_REV      FW_VER
#else
#define BLE_LL_LOCAL_VER_LMP_REV      0x0008
#endif
extern const ble_ll_ver_st local_ver;

// # feature
#define BLE_LL_LOCAL_FEATURE    (0x0000006000000000)    // [38]: LE Supported (Controller), [37]BR/EDR not support
#define BLE_LL_LOCAL_LE_FEATURE (0x0000000000000021)    // support encryption
#define BLE_LL_LOCAL_SUPPORTED_COMMANDS  {0x20, 0x00, 0x80, 0x00, \
                                          0x00, 0x40, 0x00, 0x00, \
                                          0x00, 0x00, 0x00, 0x00, \
                                          0x00, 0x00, 0xA0, 0x22, \
                                          0x00, 0x00, 0x00, 0x00, \
                                          0x00, 0x00, 0x00, 0x00, \
                                          0x00, 0xf7, 0xff, 0xff, \
                                          0x7f, 0x00, 0x00, 0x00, \
                                          0x00, 0xC0, 0x01, 0x08, \
                                          0x00, 0x00, 0x80, 0x00, \
                                          0x00, 0x00, 0x00, 0x00, \
                                          0x00, 0x00, 0x00, 0x00, \
                                          0x00, 0x00, 0x00, 0x00, \
                                          0x00, 0x00, 0x00, 0x00, \
                                          0x00, 0x00, 0x00, 0x00, \
                                          0x00, 0x00, 0x00, 0x00, \
                                        } // Refer to spec Vol2, partE, 6.27 SUPPORTED COMMANDS
extern const u64 local_feature;
extern const u64 local_le_feature;
extern const u8  local_supported_commands[64];

#define BLE_LL_FEATURE_SET_IDX_LE_ENCRYPTION    0

// # state
#define BLE_LL_LOCAL_SUPPORT_STATES (0x00000000ffffff1f)
extern const u64 local_le_support_states;

// # role
typedef enum {
    BLE_LL_ROLE_SLAVE = 0x00,   // NOTE: different with HCI defintion.
    BLE_LL_ROLE_MASTER,
}   BLE_LL_ROLE_CONN;

typedef enum {
    BLE_LL_CH_ADV = 0,
    BLE_LL_CH_DATA,
}   BLE_LL_CH_TYPE;

typedef enum {
    BLE_LL_DIRECTION_TX = 0,
    BLE_LL_DIRECTION_RX,
}   BLE_LL_DIRECTION;

/** ##############################################
 * physical constants
 * ############################################### */
//extern const u8         ble_ll_map_ch_ll2rf[];
extern const u8         ble_ll_map_dwlfsr_seed[];
extern const BLE_LL_PPM ble_ll_map_sca[];

#define BLE_LL_ADVCH_ACCESS_ADDR    0x8E89BED6
#define BLE_LL_ADVCH_PHY_CRC_INIT   0x555555
/**
 * time
 *
 */
typedef s32 BLE_LL_US;
#define BLE_LL_IN128US(_US_) (((_US_) +127) >> 7)    // +127: do ceiling
#define BLE_LL_INUS(_US_) (_US_)    // +127: do ceiling

#define BLE_LL_BYTE_TIME(_BYTE_) ((_BYTE_) << 3)
#define BLE_LL_IFS ((BLE_LL_US)150)

/**
 * phy timing
 *
 */
#define BLE_PHY_TX_END_LATENCY  3       // in fact, 2.5~3us
#define BLE_PHY_RX_EARLY_ON     (2 +2)  // 2ns for communition uncertainty, 2us for implementation uncertainty
#define BLE_PHY_RX_LATE_ACCESS  (2 +2)  // 2ns for communition uncertainty, 2us for implementation uncertainty
#define BLE_PHY_RX_LATENCY      6

#define BLE_LL_CLOCK_TIME_BW 28
typedef struct {

    union {
        s32 w;
        s32 val:BLE_LL_CLOCK_TIME_BW;
    };

} ble_ll_clock_time_st;
#define BLE_LL_CLOCK_TIME_ALIGN_BW          (32  -BLE_LL_CLOCK_TIME_BW)
#define BLE_LL_CLOCK_TIME_ALIGNED(_TIME_)   ((_TIME_) << BLE_LL_CLOCK_TIME_ALIGN_BW)

#define BLE_LL_CLOCK_OFFSET_BW 20
typedef struct {

    union {
        s32 w;
        s32 val:BLE_LL_CLOCK_OFFSET_BW;
    };

} ble_ll_clock_offset_st;

#define BLE_LL_CLOCK_US(_US_) ((s32)((_US_) << 1)) // clock unit: 0.5us

#define BLE_LL_TOUT(_CLOCK_NOW_, _CLOCK_ORIG_, _PRD_) \
    (BLE_LL_CLOCK_TIME_ALIGNED((_CLOCK_NOW_).w -(_CLOCK_ORIG_).w -BLE_LL_CLOCK_US(_PRD_)) > 0)

#define BLE_LL_TEXPIRE(_CLOCK_NOW_, _CLOCK_TARGET_) \
    (BLE_LL_CLOCK_TIME_ALIGNED((_CLOCK_NOW_).w -(_CLOCK_TARGET_).w) >= 0)

#define BLE_LL_SLOT_EXPIRE(_CURRENT_SLOT_, _SLOT_) \
    (((_CURRENT_SLOT_) -(_SLOT_)) >= 0)

typedef s16 BLE_LL_INSTANT;

typedef struct ble_ll_rssi {

    u8  adc;
    s16 instant;

} ble_ll_rssi_st;

extern NV_DATA ble_ll_rssi_st   g_ble_ll_rssi_slave;

/**
 * a window description, referenced to specific instance in connection
 *
 */
typedef struct ble_ll_conn_window {

    BLE_LL_INSTANT          ref_instant;
    ble_ll_clock_time_st    ref_time;

    BLE_LL_US size;
    BLE_LL_US offset;

} ble_ll_conn_window_st;

typedef struct ble_ll_connection_timing_raw_parameter {

    u16 conn_interval;
    u16 conn_latency;
    u16 supervision_timeout;
    u8  master_clock_accuracy;

} ble_ll_connection_timing_raw_parameter_st;

typedef struct ble_ll_conn_timing_param {

    BLE_LL_US conn_intv;
    BLE_LL_US supervision_tout;

    u16 latency;

    ble_ll_connection_timing_raw_parameter_st raw;

} ble_ll_conn_timing_param_st;

typedef struct ble_ll_conn_update_param {

    union {
        ble_ll_conn_timing_param_st timing;
        ble_datach_map_st           ch_map;
    };
    u8  bandwidth_updated;

} ble_ll_conn_update_param_st;

/** ##############################################
 * timing offsets
 *
 * ############################################### */
typedef struct ble_ll_timing_offset {

    // # tbx
    s8  tbx_phy_rx_ref_time_offset;
    s16 tbx_window_widening_offset;
    // # air_prot
    s8  air_prot_rx_follower_offset;        // tracking rx
    s8  air_prot_tx_follower_offset;        // tracking tx
    s8  air_prot_tx_long_rf_cali_offset;    // alarm0_notify0; // tx long rx cali
    s8  air_prot_tx_rf_on_offset;           // alarm0_notify1; // tx on
    s8  air_prot_tx_pdu_req_offset;         // alarm0_notify2; // tx pdu_req
    s8  air_prot_rx_long_rf_cali_offset;    // alarm1_notify0; // rx long rx cali
    s8  air_prot_rx_rf_on_offset;           // alarm1_notify1; // rx on
    s8  air_prot_rx_access_tout_offset;     // alarm1_notify3; // rx access timeout

} ble_ll_timing_offset_st;

extern const ble_ll_timing_offset_st ble_ll_timing_offset;

/** ##############################################
 * configurables (40-byte)
 *  - bd_addr/random_addr
 *  - datach_class
 *  - tx_pwr
 * ############################################### */
typedef struct ble_ll_cfg {
    // + dev info
    ble_addr_st bd_addr;
    // + privacy
    ble_addr_st random_addr;
    // + data channel classification
    ble_datach_class datach_class;
    // + air event notify msk
    u8  air_event_notify_msk;
    u8  air_event_application_irq_msk;
    // + ssv version exchanged notify msk
    u8  ssv_version_exchanged_notify_msk;
    // + early notify time
    u16 early_notify_time_advch;
    u16 early_notify_time_datach;
    // + sca (ppm)
    BLE_LL_PPM fclk_sca;
    BLE_LL_PPM sclk_sca;
    // + anchor id (priority)
    u8  anchor_id_adv;
    u8  anchor_id_scan_inita;

    u16 data_pdu_suggest_txlen;
    u16 data_pdu_suggest_txtime;
} ble_ll_cfg_st;

extern NV_DATA ble_ll_cfg_st g_ble_ll_cfg;

/** ##############################################
 * HCI timing unit and constant
 * ############################################### */
#define BLE_LL_ADV_INTV_UNIT    ((BLE_LL_US)625)
#define BLE_LL_SCAN_INTV_UNIT   ((BLE_LL_US)625)
#define BLE_LL_SCAN_WINDOW_UNIT ((BLE_LL_US)625)
#define BLE_LL_CONN_INTV_UNIT   ((BLE_LL_US)1250)
#define BLE_LL_CONN_WINDOW_UNIT ((BLE_LL_US)1250)

#define BLE_LL_SUPERVISION_TOUT_UNIT    ((BLE_LL_US)10000)
#define BLE_LL_SUPERVISION_TOUT_MIN     ((BLE_LL_US)100000)
#define BLE_LL_SUPERVISION_TOUT_MAX     ((BLE_LL_US)32000000)

/** ##############################################
 * evt to host
 * ############################################### */
#define HCI_EVT_MSKB_DEFAULT    0x00001fffffffffff
#define HCI_LE_EVT_MSKB_DEFAULT 0x000000000000005f
extern NV_DATA u64  g_hci_evt_mskb;
extern NV_DATA u64  g_hci_le_evt_mskb;

s16 ble_ll_send_evt_hci(ble_ll_evt_hci_un evt);
#if (1 == BLE_AGGR_ADV_REPORT)
s16 ble_ll_send_evt_hci_aggr(ble_ll_evt_hci_aggr_adv_rtp aggr_evt, u8 aggr_num);
#endif

/** ##############################################
 * op
 * ############################################### */
// const ble_ll_op_un ble_ll_op_null = {0};

/** ##############################################
 * air event notify to host
 * ############################################### */
enum {
    BLE_LL_AIR_EVENT_NOTIFY_TYPE_EARLY = 1,
    BLE_LL_AIR_EVENT_NOTIFY_TYPE_END,
};
s16 ble_ll_air_event_notify2host(u8 type);

/** ##############################################
 * peer information
 * ############################################### */
typedef struct ble_ll_peer_info {

    ble_addr_st     addr;
    ble_addr_st     own_used_addr;
    ble_ll_ver_st   ver;
    u64             used_le_feature;

    struct {
        u8  ver_vld             :1;
        u8  used_le_feature_vld :1;
    };

} ble_ll_peer_info_st;

extern NV_DATA ble_ll_peer_info_st g_slave_peer_info;

/** ##############################################
 * pdu (56-byte)
 * ############################################### */
#define BLE_LL_PREAMBLE_SIZE    1
#define BLE_LL_ACCESS_CODE_SIZE 4
#define BLE_LL_PDU_HDR_SIZE     BLE_PDU_HDR_SIZE
#define BLE_LL_PDU_PLD_SIZE     BLE_PDU_PLD_SIZE
#define BLE_LL_MIC_SIZE         4
#define BLE_LL_CRC_SIZE         3
typedef struct ble_ll_pdu {

    struct ble_ll_pdu* next;

    // cfg
    u32 type            :12;
    u32 conn_id         :4;
    u32 flag            :8;
    u32 tx_pld_offset   :8;

    // log
    u32 rxlog_rssi          :8;
    u32 rxlog_access_time   :24;  // 4-bit reserved
    u32 rxlog_ch            :8;
    u32 rxlog_filter_result :8;
    u32 rxlog_instant       :16;

    // hdr
    u8  hdr0;
    union {
        u8  hdr1;
        u8  pld_len;
    };

    // pld
    u8  pld[BLE_LL_PDU_PLD_SIZE];

} ble_ll_pdu_st;

#define BLE_LL_CPDU_SLAVE_TX_PLD_SIZE 23 // LL_ENC_RSP, plain text
typedef struct ble_ll_cpdu_slave_tx {

    struct ble_ll_tx_cpdu_slave_stble_ll_pdu* next;

    // cfg
    u32 type            :12;
    u32 conn_id         :4;
    u32 flag            :8;
    u32 tx_pld_offset   :8;

    // log
    u32 rxlog_rssi          :8;
    u32 rxlog_access_time   :24;  // 4-bit reserved
    u32 rxlog_ch            :8;
    u32 rxlog_filter_result :8;
    u32 rxlog_instant       :16;

    // hdr
    u8  hdr0;
    union {
        u8  hdr1;
        u8  pld_len;
    };

    // pld
    u8  pld[BLE_LL_CPDU_SLAVE_TX_PLD_SIZE];

} ble_ll_cpdu_slave_tx_st;

#define BLE_LL_PLAIN_PDU_TIME(PLD_LEN)  \
    BLE_LL_BYTE_TIME(BLE_LL_PREAMBLE_SIZE +BLE_LL_ACCESS_CODE_SIZE +BLE_LL_PDU_HDR_SIZE +(PLD_LEN) \
        +BLE_LL_CRC_SIZE)

#define BLE_LL_ENCRYPTED_PDU_TIME(PLD_LEN)  \
    BLE_LL_BYTE_TIME(BLE_LL_PREAMBLE_SIZE +BLE_LL_ACCESS_CODE_SIZE +BLE_LL_PDU_HDR_SIZE +(PLD_LEN) \
        +BLE_LL_MIC_SIZE +BLE_LL_CRC_SIZE)

// # cfg macro
#define BLE_LL_TYPE_GET_CRCOK(_TYPE_)       (((_TYPE_) & 0x010) >> 4 )
#define BLE_LL_TYPE_GET_ASACK(_TYPE_)       (((_TYPE_) & 0x020) >> 5 )
#define BLE_LL_TYPE_GET_MIC_ERR(_TYPE_)     (((_TYPE_) & 0x080) >> 7 )
#define BLE_LL_TYPE_GET_LONG_PLD(_TYPE_)    (((_TYPE_) & 0x200) >> 9 )
#define BLE_LL_TYPE_GET_DIRECTION(_TYPE_)   (((_TYPE_) & 0x400) >> 10)
#define BLE_LL_TYPE_GET_CH_TYPE(_TYPE_)     (((_TYPE_) & 0x800) >> 11)

#define BLE_LL_TYPE_SET_CRCOK(_TYPE_, _VAL_)        _TYPE_ = (((_TYPE_) & 0xfef) | ((_VAL_) << 4 ))
#define BLE_LL_TYPE_SET_ASACK(_TYPE_, _VAL_)        _TYPE_ = (((_TYPE_) & 0xfdf) | ((_VAL_) << 5 ))
#define BLE_LL_TYPE_SET_MIC_ERR(_TYPE_, _VAL_)      _TYPE_ = (((_TYPE_) & 0xf7f) | ((_VAL_) << 7 ))
#define BLE_LL_TYPE_SET_LONG_PLD(_TYPE_, _VAL_)     _TYPE_ = (((_TYPE_) & 0xdff) | ((_VAL_) << 9 ))
#define BLE_LL_TYPE_SET_DIRECTION(_TYPE_, _VAL_)    _TYPE_ = (((_TYPE_) & 0xbff) | ((_VAL_) << 10))
#define BLE_LL_TYPE_SET_CH_TYPE(_TYPE_, _VAL_)      _TYPE_ = (((_TYPE_) & 0x7ff) | ((_VAL_) << 11))

// ## adv ch
#define BLE_LL_TYPE_GET_PDU_TYPE(_TYPE_)    (((_TYPE_) & 0x00f) >> 0 )
#define BLE_LL_TYPE_GET_TX_ADDR_HIT(_TYPE_) (((_TYPE_) & 0x040) >> 6 )
#define BLE_LL_TYPE_GET_RX_ADDR_HIT(_TYPE_) (((_TYPE_) & 0x080) >> 7 )

#define BLE_LL_TYPE_SET_PDU_TYPE(_TYPE_, _VAL_)     _TYPE_ = (((_TYPE_) & 0xff0) | ((_VAL_) << 0 ))
#define BLE_LL_TYPE_SET_TX_ADDR_HIT(_TYPE_, _VAL_)  _TYPE_ = (((_TYPE_) & 0xfbf) | ((_VAL_) << 6 ))
#define BLE_LL_TYPE_SET_RX_ADDR_HIT(_TYPE_, _VAL_)  _TYPE_ = (((_TYPE_) & 0xf7f) | ((_VAL_) << 7 ))

#define BLE_PDU_TX_PLD_OFFSET_INIT 14   // (type: 4-byte, rx_log: 8-byte, hdr: 2-byte)

/** ##############################################
 * acl2host
 * ############################################### */
s16 ble_ll_acl2host (const ble_ll_pdu_st* pdu);

/**
 * ADVCH pdu constant/structure/macro
 *
 */
// # header
#define BLE_LL_HDR_ADV_IND          0
#define BLE_LL_HDR_ADV_DIRECT_IND   1
#define BLE_LL_HDR_ADV_NONCONN_IND  2
#define BLE_LL_HDR_SCAN_REQ         3
#define BLE_LL_HDR_SCAN_RSP         4
#define BLE_LL_HDR_CONNECT_REQ      5
#define BLE_LL_HDR_ADV_SCAN_IND     6

#define BLE_LL_HDR_GET_PDU_TYPE(_HDR_)      (((_HDR_) & 0x0f) >> 0)
#define BLE_LL_HDR_GET_TX_ADDR_TYPE(_HDR_)  (((_HDR_) & 0x40) >> 6)
#define BLE_LL_HDR_GET_RX_ADDR_TYPE(_HDR_)  (((_HDR_) & 0x80) >> 7)

#define BLE_LL_HDR_SET_PDU_TYPE(_HDR_, _VAL_)       _HDR_ = (((_HDR_) & 0xf0) | ((_VAL_) << 0))
#define BLE_LL_HDR_SET_TX_ADDR_TYPE(_HDR_, _VAL_)   _HDR_ = (((_HDR_) & 0xbf) | ((_VAL_) << 6))
#define BLE_LL_HDR_SET_RX_ADDR_TYPE(_HDR_, _VAL_)   _HDR_ = (((_HDR_) & 0x7f) | ((_VAL_) << 7))

// # payload/adata
#define BLE_LL_APLD_IDX_TX_ADDR  0
#define BLE_LL_APLD_IDX_RX_ADDR  6

typedef struct ble_ll_adata_lldata {

    u8  access_addr [BLE_LL_ACCESS_CODE_SIZE];
    u8  crc_init    [BLE_LL_CRC_SIZE];
    u8  win_size;
    u8  win_offset  [2];
    u8  intv        [2];
    u8  latency     [2];
    u8  tout        [2];
    u8  ch_map      [BLE_DATACH_MAP_SIZE];
    u8  ch_hop      :5;
    u8  sca         :3;

} ble_ll_adata_lldata_st;

typedef struct ble_ll_apld_conn_req {

    u8  init_addr   [BLE_ADDR_SIZE];
    u8  adv_addr    [BLE_ADDR_SIZE];

    ble_ll_adata_lldata_st lldata;

} ble_ll_apld_conn_req_st;
#define BLE_LL_APLD_SIZE_CONN_REQ sizeof(ble_ll_apld_conn_req_st)

/**
 * DATACH pdu constant/structure/macro
 *
 */
// # header
#define BLE_LL_LLID_RESERVED            0x00
#define BLE_LL_LLID_CONTINUE_L2CAP_PDU  0x01
#define BLE_LL_LLID_EMPTY_PDU           0x01
#define BLE_LL_LLID_START_L2CAP_PDU     0x02
#define BLE_LL_LLID_CPDU                0x03

#define BLE_LL_HDR_GET_DATA_LLID(_HDR_)  (((_HDR_) & 0x03) >> 0)
#define BLE_LL_HDR_GET_DATA_NESN(_HDR_)  (((_HDR_) & 0x04) >> 2)
#define BLE_LL_HDR_GET_DATA_SN(_HDR_)    (((_HDR_) & 0x08) >> 3)
#define BLE_LL_HDR_GET_DATA_MD(_HDR_)    (((_HDR_) & 0x10) >> 4)

#define BLE_LL_HDR_SET_DATA_LLID(_HDR_, _VAL_) _HDR_ = (((_HDR_) & 0xfc) | ((_VAL_) << 0))
#define BLE_LL_HDR_SET_DATA_NESN(_HDR_, _VAL_) _HDR_ = (((_HDR_) & 0xfb) | ((_VAL_) << 2))
#define BLE_LL_HDR_SET_DATA_SN(_HDR_, _VAL_)   _HDR_ = (((_HDR_) & 0xf7) | ((_VAL_) << 3))
#define BLE_LL_HDR_SET_DATA_MD(_HDR_, _VAL_)   _HDR_ = (((_HDR_) & 0xef) | ((_VAL_) << 4))

// # payload
#define BLE_LL_DPLD_SIZE_DEFAULT    (27)
#define BLE_LL_DPDU_TIME_DEFAULT    BLE_LL_ENCRYPTED_PDU_TIME(BLE_LL_DPLD_SIZE_DEFAULT)
#if(CHIP_SUB_ID==2)
#define BLE_LL_DPLD_SIZE_MAX    (251)
#define BLE_LL_DPDU_TIME_MAX    17040 //Coded RHY
#else
#define BLE_LL_DPLD_SIZE_MAX    (27)
#define BLE_LL_DPDU_TIME_MAX    BLE_LL_ENCRYPTED_PDU_TIME(BLE_LL_DPLD_SIZE_MAX)
#endif

u16 ble_ll_check_data_length(u16 len);
u16 ble_ll_check_data_txtime(u16 time);
u8 ble_ll_update_used_data_length (ble_data_length_st *dataleninfo);

/**
 * constant null pdu
 */
extern const ble_ll_pdu_st ble_ll_tx_null_pdu;

/** ##############################################
 * apdu
 * ############################################### */
#define BLE_LL_ADV_PDU_DEFAULT {                                                            \
    .type = (BLE_LL_CH_ADV << 11) | (BLE_LL_DIRECTION_TX << 10) | BLE_APDU_TYPE_ADV_IND,    \
    .tx_pld_offset  = BLE_PDU_TX_PLD_OFFSET_INIT,                                           \
    .pld_len        = 0,                                                                    \
}
#define BLE_LL_SCAN_RSP_PDU_DEFAULT {                                                       \
    .type = (BLE_LL_CH_ADV << 11) | (BLE_LL_DIRECTION_TX << 10) | BLE_APDU_TYPE_SCAN_RSP,   \
    .tx_pld_offset  = BLE_PDU_TX_PLD_OFFSET_INIT,                                           \
    .pld_len        = 0,                                                                    \
}
#define BLE_LL_CREATE_CONN_PDU_DEFAULT {                                                    \
    .type = (BLE_LL_CH_ADV << 11) | (BLE_LL_DIRECTION_TX << 10) | BLE_APDU_TYPE_CONNECT_REQ,\
    .tx_pld_offset  = BLE_PDU_TX_PLD_OFFSET_INIT,                                           \
    .pld_len        = 0,                                                                    \
}
extern NV_DATA ble_ll_pdu_st g_ble_ll_adv_pdu;
extern NV_DATA ble_ll_pdu_st g_ble_ll_scan_rsp_pdu;
extern NV_DATA ble_ll_pdu_st g_ble_ll_create_conn_pdu;
extern u32 g_conn_ind_peer_addr[2];
extern u8 g_conn_ind_peer_addr_type;

/** ##############################################
 * whitelist
 * ############################################### */
#define BLE_WHITELIST_SIZE  8
extern NV_DATA ble_addr_st  g_ble_whitelist[];
extern NV_DATA u32          g_ble_whitelist_en;

/** ##############################################
 * cpdu pool
 * ############################################### */
extern NV_DATA ble_pdu_pool_st g_ble_tx_cpdu_pool;

/** ##############################################
 * link-layer utility
 * ############################################### */
/**
 * pduq manipulate
 *
 */
typedef struct ble_ll_pduq {

    ble_ll_pdu_st*  head;
    u32             depth;

} ble_ll_pduq_st;

ble_ll_pdu_st*  ble_ll_pdu_deq  (ble_ll_pduq_st* pduq);
u32             ble_ll_pdu_inq  (ble_ll_pduq_st* pduq, ble_ll_pdu_st* pdu);
u32             ble_ll_pduq_cat (ble_ll_pduq_st* dest, ble_ll_pduq_st* src);

#define BLE_APDU_TYPE_ADV_IND          0
#define BLE_APDU_TYPE_ADV_DIRECT_IND   1
#define BLE_APDU_TYPE_ADV_NONCONN_IND  2
#define BLE_APDU_TYPE_SCAN_REQ         3
#define BLE_APDU_TYPE_SCAN_RSP         4
#define BLE_APDU_TYPE_CONNECT_REQ      5
#define BLE_APDU_TYPE_ADV_SCAN_IND     6
u8*  ble_ll_tx_apdu_init(u8 type, ble_ll_pdu_st* pdu);

/**
 * status check
 *
 */
#define BLE_LL_TASK_FLAG_ADVCH  0x07
#define BLE_LL_TASK_FLAG_DATACH 0xf8
u8  ble_ll_task_busy(u16 task_flag);

/** ##############################################
 * predefined anchor_id
 * ############################################### */
#define BLE_LL_ANCHOR_ID_ADVCH_PRIORITY_HIGH    0x00
#define BLE_LL_ANCHOR_ID_ADVCH_PRIORITY_LOW     0x01
#define BLE_LL_ANCHOR_ID_SLAVE  0X02
#define BLE_LL_ANCHOR_ID_MASTER 0X03

/** ##############################################
 * conn_hdl/conn_id/master_id
 * ############################################### */
typedef u16 BLE_LL_CONN_HDL;
#define BLE_LL_CONN_HDL_INVLD ((BLE_LL_CONN_HDL)0x0fff)

typedef u8 BLE_LL_CONN_ID;
#define BLE_LL_CONN_ID_INVLD ((BLE_LL_CONN_ID)0xff)

#define BLE_LL_CONN_ID_ADV          ((BLE_LL_CONN_ID)0x00)
#define BLE_LL_CONN_ID_SCAN         ((BLE_LL_CONN_ID)0x01)
#define BLE_LL_CONN_ID_INITA         ((BLE_LL_CONN_ID)0x02)
#define BLE_LL_CONN_ID_SLAVE        ((BLE_LL_CONN_ID)0x03)
#define BLE_LL_CONN_ID_MASTER_BASE  ((BLE_LL_CONN_ID)0x04)

BLE_LL_CONN_ID  ble_ll_conn_id_query        (BLE_LL_CONN_HDL    conn_hdl);
BLE_LL_CONN_HDL ble_ll_conn_hdl_register    (BLE_LL_CONN_ID     conn_id);
void            ble_ll_conn_hdl_unregister  (BLE_LL_CONN_ID     conn_id);
bool            ble_ll_new_master_conn_available();

typedef u8 BLE_LL_MASTER_ID;
#define BLE_LL_MASTER2CONN_ID(_MASTER_ID_) \
    ((BLE_LL_CONN_ID)((_MASTER_ID_)  +BLE_LL_CONN_ID_MASTER_BASE))
#define BLE_LL_CONN2MASTER_ID(_CONN_ID_) \
    ((BLE_LL_MASTER_ID)((_CONN_ID_)    -BLE_LL_CONN_ID_MASTER_BASE))

/** ##############################################
 * anchor
 * ############################################### */
typedef struct {

    u8  priority;
    u8  early_notify_msk;           // # 1: turn-off early_notify_msk
    u16  pre_process_time_us;     // # trigger air_event_beg, to execute:
                                    // ## hwif_profile load
                                    // ## trx_ring load
                                    // ## 1*128 us ~ 8*128us
    u16  post_process_time_us;    // # the time reserved for FSM operations, including:
                                    // ## link-layer/host in protocol layer
    u16 rx_window_us;            // # if no rx accessed in this window, trigger hard_end
                                    // ## this may run-time depenedent
    u16 window_us;               // # real-time behavior window
    u16 early_notify_time_us;    // # a event to HOST, specified by HOST(advch/datach seperately)

    ble_ll_clock_time_st anchor;    // # main anchor
                                    // ## run-time dependent
                                    // ## scheduled next anchor

} ble_ll_anchor_profile_st;

#define BLE_LL_HWIF_ALARM_IRQ_EARLY_NOTIFY      BLE_LL_HWIF_ALARM_IRQ_NOTIFY0
#define BLE_LL_HWIF_ALARM_IRQ_AIR_EVENT_BEG     BLE_LL_HWIF_ALARM_IRQ_NOTIFY1

/** ##############################################
 * schedule
 * ############################################### */
typedef s32 BLE_LL_MASTER_SLOT;

typedef struct ble_ll_sche_info {

    BLE_LL_US   adv_intv_min;
    BLE_LL_US   scan_sub_window;
    BLE_LL_US   inita_sub_window; //leo only for build pass

    BLE_LL_US   slave_intv_min;
    BLE_LL_US   slave_window;   // slave air event timeout

    BLE_LL_US           master_slot_intv;
    BLE_LL_MASTER_SLOT  master_slot_inc_min;

} ble_ll_sche_info_st;

extern const ble_ll_sche_info_st g_ble_ll_sche_info;

/** ##############################################
 * wakelock
 * ############################################### */
void ble_ll_wakelock_task(u8 conn_id, u8 wakelock);
void ble_ll_wakelock_rt(u8 wakelock);

/** ##############################################
 * system constant
 * ############################################### */
#define MSG_IRQn IPC_1_IRQn

/** ##############################################
 * patchable macro
 * ############################################### */
#define BLE_LL_PATCHABLE_CONST  const __attribute__((section (".swgp_record")))

/** ##############################################
 * log
 * ############################################### */
#include "ilog.h"
#define BLE_LL_FXLOG_VERBOSE(...) \
    do { \
        LL_ILOG(LOG_VERBOSE, "# %s: ", __func__);  \
        LL_ILOG(LOG_VERBOSE, __VA_ARGS__);         \
    } while(0)

#define BLE_LL_LOG_VERBOSE(...) \
    LL_ILOG(LOG_VERBOSE, __VA_ARGS__)

#define BLE_LL_FXLOG_DBG(...) \
    do { \
        LL_ILOG(LOG_DBG, "# %s: ", __func__);  \
        LL_ILOG(LOG_DBG, __VA_ARGS__);         \
    } while(0)

#define BLE_LL_LOG_DBG(...) \
    LL_ILOG(LOG_DBG, __VA_ARGS__)

#define BLE_LL_LOG_INFO(...) \
    LL_ILOG(LOG_INFO, __VA_ARGS__)

#define BLE_LL_LOG_ERR(...) \
    LL_ILOG(LOG_ERR, __VA_ARGS__)

#define BLE_LL_LOG_HARDFAULT(...) \
    do { \
        LL_ILOG(LOG_CRIT, __VA_ARGS__); \
        asm("setgie.d\n"); \
        printf(__VA_ARGS__); \
        while(1); \
    } while(0)

/** ##############################################
 * lpram recovery
 * ############################################### */
s16 ble_ll_lpram_recovery();

/** ##############################################
 * link-layer timer
 * ############################################### */
#define BLE_LL_TMR_UNIT ((BLE_LL_US)1000000)

#endif // _BLE_LL_H_
