/**
 * hw interfaces
 *
 */
#ifndef _BLE_LL_HWIF_H_
#define _BLE_LL_HWIF_H_

#include "lib/condor_ssv_lib.h"
#include "ble/ble_lib_v2.h"

#include "ble/ctrl_v2/ble_ll_ring.h"

/** ##############################################
 * link-layer interface define
 *  - sync with asic
 * ############################################### */

/**
 * hw buffer interface
 *  - identical to ble_ll_pdu_st, except next*
 *
 */
typedef volatile struct ble_ll_hwif_buf {

    // cfg
    union {
        u32 cfg_w;
        struct {
            u32 type            :12;
            u32 conn_id         :4;
            u32 flag            :8;
            u32 tx_pld_offset   :8;
        } cfg;
    };

    // log
    union {
        u32 rxlog_phy_w;
        struct {
            u32 rssi        :8;
            u32 access_time :24;
        } phylog;
    };

    union {
        u32 rxlog_w;
        struct {
            u32 ch              :8;
            u32 filter_result   :8;
            u32 instant         :16;
        } log;
    };

    union {
        u32 pdu0_w;
        struct {
           u32 hdr0:8;
           u32 hdr1:8;
           u32 pld0:8;
           u32 pld1:8;
        } pdu0;
    };

    u32 pdu1;
    u32 pdu2;
    u32 pdu3;
    u32 pdu4;
    u32 pdu5;
    u32 pdu6;
    u32 pdu7;
    u32 pdu8;
    u32 pdu9;

} ble_ll_hwif_buf_st;

typedef volatile struct ble_ll_hwifc_buf {

    // cfg
    u32 type            :12;
    u32 conn_id         :4;
    u32 flag            :8;
    u32 tx_pld_offset   :8;

    // log
    u32 rxlog_rssi          :8;
    u32 rxlog_access_time   :24;

    u32 rxlog_ch            :8;
    u32 rxlog_filter_result :8;
    u32 rxlog_instant       :16;

    // header
    u8  hdr[BLE_LL_PDU_HDR_SIZE];
    u8  pld[BLE_LL_PDU_PLD_SIZE];

} ble_ll_hwifc_buf_st;

/**
 * buf store/load operation
 *
 */
void ble_ll_hwif_buf_store(ble_ll_hwif_buf_st* hwif, ble_ll_pdu_st* pdu);
void ble_ll_hwif_buf_load (ble_ll_hwif_buf_st* hwif, ble_ll_pdu_st* pdu);

/**
 * pdu-to-buf
 *  - from a pdu pointer, to a hwif-buf pointer
 *  - scenario: when mount a pdu to the ring
 *
 */
/*#define BLE_LL_PDU2BUF(pdu) (ble_ll_hwif_buf_st*) \
    ((u8 *)pdu +(sizeof(ble_ll_pdu_st) -sizeof(ble_ll_hwif_buf_st)))*/
#define BLE_LL_PDU2BUF(pdu) (ble_ll_hwif_buf_st*) \
    ((u8 *)pdu + (4))

/**
 * buf-to-pdu
 *  - from a hwif-buf pointer, to a pdu pointer
 *  - scenario: when un-mount a pdu from the ring
 *
 */
/*#define BLE_LL_BUF2PDU(buf) (ble_ll_pdu_st*) \
    ((u8 *)(u32)buf -(sizeof(ble_ll_pdu_st) -sizeof(ble_ll_hwif_buf_st)))*/
#define BLE_LL_BUF2PDU(buf) (ble_ll_pdu_st*) \
    ((u8 *)(u32)buf -(4))


typedef volatile struct ble_ll_hwif_ring {

    // memory
    ble_ll_ring_element_st* elements;
    u32                     cfg_element_baddr;

    // interface
    union {
        u32 if_vptr_w;
        struct {
            u32 rd:8;
            u32 wr:8;
        } if_vptr;
    };

    // config
    u32 cfg_ptr_msk;

} ble_ll_hwif_ring_st;
#define HWIF_RING_IF_VPTR_W(_WR_VPTR_, _RD_VPTR_) (((_WR_VPTR_) << 8) | (_RD_VPTR_))

/**
 * from ring -> hwif
 *
 */
void ble_ll_hwif_ring_store(ble_ll_hwif_ring_st* hwif, ble_ll_ring_st* ring);

/**
 * from hwif -> ring
 *
 */
void ble_ll_hwif_ring_load(ble_ll_hwif_ring_st* hwif, ble_ll_ring_st* ring,
    u8 load_rd_vptr, u8 load_wr_vptr);

/**
 * policy, a decision rule
 *
 */
#define BLE_LL_HWIF_POLICY_S0SET_S1CLR      0x3333aaaa
#define BLE_LL_HWIF_POLICY_S0               0xaaaaaaaa
#define BLE_LL_HWIF_POLICY_LATH_S0          0xffffaaaa
#define BLE_LL_HWIF_POLICY_LATH_S1ORS0      0xffffeeee
#define BLE_LL_HWIF_POLICY_LATH_S1ANS0      0xffff8888
#define BLE_LL_HWIF_POLICY_LATH_S2AN_S1ORS0 0xffffe0e0
#define BLE_LL_HWIF_POLICY_S0CLR            0x55550000
#define BLE_LL_HWIF_POLICY_CLR              0x00000000
#define BLE_LL_HWIF_POLICY_HOLD             0xffff0000
#define BLE_LL_HWIF_POLICY_S1_SETATS0       0xcccc8888
#define BLE_LL_HWIF_POLICY_S1S0AND          0x88888888
#define BLE_LL_HWIF_POLICY_S0SET_S1ORS2CLR  0x0303aaaa
#define BLE_LL_HWIF_POLICY_REDGE            0x0000aaaa

typedef volatile struct ble_ll_hwif_policy {

    union {
        u32 cfg_w;
        struct {
            u32 sel0:(6+2);
            u32 sel1:(6+2);
            u32 sel2:(6+2);
            u32 sel3: 6;
            u32 manual_val  :1;
            u32 manual      :1;
        } cfg;
    };

    union {
        u32 if_w;
        struct {
            u32 set0:1;
            u32 set1:1;
            u32     :29;
            u32 val :1; // only in emulation
        } if_;
    };

    u32 cfg_policy;

} ble_ll_hwif_policy_st;
#define HWIF_POLICY_IF_CLEAR 0x00000001
#define HWIF_POLICY_IF_SET   0x00000002

/**
 * info, an information storage, 64-bit max
 *
 */
typedef volatile struct ble_ll_hwif_info {

    union {
        u32 if_w;
        struct {
            u32 invld           :1;
            u32 set             :1;
            u32 manual_ov       :1+1;
            u32 manual_ov_vld   :4;
            //
            u32 val:8;

            u32 ro_vld:8;
            u32 ro_val:8;
        } if_;
    };

} ble_ll_hwif_info_st;

typedef volatile struct ble_ll_hwif_info_long {

    union {
        u32 if_w;
        struct {
            u32 invld           :1;
            u32 set             :1;
            u32 manual_ov       :1+1;
            u32 manual_ov_vld   :4;
            u32                 :8;
            u32 ro_vld          :8+8;  // 8-bit val    in ble_ll_hwif_info_st
        } if_;
    };

    u32 if_val0;
    u32 if_val1;

    u32 ro_val0;
    u32 ro_val1;

} ble_ll_hwif_info_long_st;

/**
 * alarm
 *
 */
#define BLE_LL_HWIF_ALARM_OFFSET_BW 20
//
#define BLE_LL_HWIF_ALARM_IRQ_NOTIFY0   0
#define BLE_LL_HWIF_ALARM_IRQ_NOTIFY1   1
#define BLE_LL_HWIF_ALARM_IRQ_NOTIFY2   2
#define BLE_LL_HWIF_ALARM_IRQ_NOTIFY3   3
#define BLE_LL_HWIF_ALARM_IRQ_NOTIFY4   4
#define BLE_LL_HWIF_ALARM_IRQ_ANCHOR    5
#define BLE_LL_HWIF_ALARM_IRQ_COL       6
#define BLE_LL_HWIF_ALARM_IRQ_EXPIRE    7
#define BLE_LL_HWIF_ALARM_IRQ_REASONS   8

#define BLE_LL_HWIF_CLOCK_OFFSET_BW 20

#define ble_ll_hwif_clock_time_st   volatile ble_ll_clock_time_st
#define ble_ll_hwif_clock_offset_st volatile ble_ll_clock_offset_st

#define BLE_LL_HWIF_US(_US_)        BLE_LL_CLOCK_US((_US_))
#define BLE_LL_HWIF_128US(_128US_)  (BLE_LL_HWIF_US((_128US_) << 7))

typedef volatile struct ble_ll_hwif_alarm {

    u32 cfg_en;

    union {
        u32                         cfg_time_w;
        ble_ll_hwif_clock_time_st   cfg_time;
    };

    union {
        u32                         cfg_window_offset_early_w;
        ble_ll_hwif_clock_offset_st cfg_window_offset_early;
    };

    union {
        u32                         cfg_window_offset_late_w;
        ble_ll_hwif_clock_offset_st cfg_window_offset_late;
    };

    union {
        u32                         cfg_notify0_offset_w;
        ble_ll_hwif_clock_offset_st cfg_notify0_offset;
    };

    union {
        u32                         cfg_notify1_offset_w;
        ble_ll_hwif_clock_offset_st cfg_notify1_offset;
    };

    union {
        u32                         cfg_notify2_offset_w;
        ble_ll_hwif_clock_offset_st cfg_notify2_offset;
    };

    union {
        u32                         cfg_notify3_offset_w;
        ble_ll_hwif_clock_offset_st cfg_notify3_offset;
    };

    union {
        u32                         cfg_notify4_offset_w;
        ble_ll_hwif_clock_offset_st cfg_notify4_offset;
    };

    u32 cfg_irq_msk;
    u32 cfg_irq_clr;

    u32 irq;

} ble_ll_hwif_alarm_st;

typedef volatile struct {

    u32 cfg_en;

    union {
        u32                         cfg_time_w;
        ble_ll_hwif_clock_time_st   cfg_time;
    };

} ble_ll_hwif_clock_st;

typedef volatile struct ble_ll_hwif_cond {

    u32 cfg_minuend:8;
    u32 cfg_subtrahend_msk:8;
    u32 cfg_op:3;               // 3'bxx1: less
                                // 3'bx1x: equal
                                // 3'b1xx: large

} ble_ll_hwif_cond_st;

typedef volatile struct ble_ll_hwif_accum {

    u32 cfg_thd :8;
    u32 cfg_init:8;
    u32 cfg_sel :6;
    u32         :2;
    u32 cfg_en  :1;

} ble_ll_hwif_accum_st;

/**
 * link-layer global configuration
 *
 */

/**
 * Note:
 *      A sequence number used in HWIF, including:
 *  # if_engines_en
 *
 */
typedef enum {

    BLE_LL_HWIF_ANCHOR = 0,
    BLE_LL_HWIF_AIR_PROT,
    BLE_LL_HWIF_AIR_EVENT,
    BLE_LL_HWIF_ACK_MGR,
    BLE_LL_HWIF_PDU_ASM,
    BLE_LL_HWIF_PDU_DASM,
    BLE_LL_HWIF_TX_RING_RDMGR,
    BLE_LL_HWIF_RX_RING_WRMGR,
    BLE_LL_HWIF_DEVICE_FILTER,

} BLE_LL_HWIF_ENGINES;

typedef volatile struct ble_ll_hwif_addr {

    union {
        u64         addr_w;
        ble_addr_st addr;
    };

} ble_ll_hwif_addr_st;

/**
 * STATE/ROLE definition: (sync with asic designer)
 *
 */
typedef enum {
    BLE_LL_HWIF_STATE_ADV = 0,
    BLE_LL_HWIF_STATE_SCAN,
    BLE_LL_HWIF_STATE_INITA,
    BLE_LL_HWIF_STATE_CONN = 4, // (sync with asic designer)
}   BLE_LL_HWIF_STATE;

typedef enum {
    BLE_LL_HWIF_ROLE_SLAVE = 0x00,
    BLE_LL_HWIF_ROLE_MASTER,
}   BLE_LL_HWIF_ROLE_CONN;

typedef volatile struct ble_ll_hwif_cmn {

    u32 if_engines_en;

    union {
        u32 cfg_state_w;
        struct {
            u32 role:   4;
            u32 state:  4;
        } cfg_state;
    };

    union {
        u32 cfg_ch_w;
        struct {
            u32 ch_type :1;
            u32         :3;
            u32 conn_id :4;
            u32 ch      :6;
        } cfg_ch;
    };

    u32 cfg_long_pdu;

    ble_ll_hwif_addr_st cfg_addr;

    u32 cfg_access_addr;

    union {
        u32 cfg_phy_w;
        struct {
            u32 crc_init:   24;
            u32 dwlfsr_seed:7;
        } cfg_phy;
    };

} ble_ll_hwif_cmn_st;

/**
 * pdu_dasm
 *
 */
typedef struct ble_ll_hwif_rx_hash {

    union {
        u32 hash_w;
        struct {
            u32 key     :12;
            u32 state   :4;
            u32 action  :8;
        } hash;
    };
} ble_ll_hwif_rx_hash_st;

// advch:
// key[04]: crcok
// key[05]: asack
// key[06]: tx_addr_filter_hit
// key[07]: rx_addr_filter_hit

// datach:
// key[02]: non-null

// key[04]: crcok
// key[05]: asack
// key[06]: new data

// key[10]: direction   0: tx, 1: rx
// key[11]: ch-type:    0: adv_ch, 1: data_ch

// action[00]:  latch addr_peer
// action[01]:  latch data_x_peer flags
// action[02]:  trigger: rx_data_ack_peer (to ack_mgr)
// action[03]:  trigger: store_req
// action[04]:  trigger: rx_soft_end
// action[05]:  trigger: trigger_tx_notify
// action[06]:  trigger: trigger_rx_notify
// action[07]:  trigger: trigger_irq


#define BLE_LL_HWIF_RX_HASH_SIZE 8

#define BLE_LL_HWIF_RX_HASH_IDX_BAD_PDU 6
#define BLE_LL_HWIF_RX_HASH_IDX_DEF     7
enum {

    pdu_dasm_idxi_new_data = 0,             // IMPROVEMENT: should be removed, not adopted
    pdu_dasm_idxi_tx_addr_filter_decision,
    pdu_dasm_idxi_rx_addr_filter_decision,
    pdu_dasm_idxi_adv_asack,
    pdu_dasm_idxi_data_asack,
    pdu_dasm_idxi_non_null,
    pdu_dasm_idxi_tx_addr_filter_hit,
    pdu_dasm_idxi_rx_addr_filter_hit,
    pdu_dasm_idxi_tx_addr_filter_result,
    //
    pdu_dasm_info_size,
}; // InDeX of Info

enum {
    pdu_dasm_idxi_addr_peer = 0,
    pdu_dasm_info_long_size,
};

enum {
    pdu_dasm_idxp_rx_pdu_vld_notify = 0,
    pdu_dasm_idxp_rx_pdu_irq,
    pdu_dasm_idxp_dmy,
    //
    pdu_dasm_policy_size,
}; // InDeX of Policy

typedef enum {
    pdu_dasm_idxs_cfg_ch_type = 0,          // external: register (hwif_cmn)
    pdu_dasm_idxs_phy_rx_accessed_notify,   // external: phy_rx
    pdu_dasm_idxs_phy_rx_ip,
    pdu_dasm_idxs_phy_rx_hdr_vld,
    pdu_dasm_idxs_phy_rx_d_lastbit_vld,
    pdu_dasm_idxs_rx_store_end,             // external: rx_ring_wr_manager
    pdu_dasm_idxs_tx_addr_filter_end,       // external: device_filter
    pdu_dasm_idxs_rx_addr_filter_end,
    pdu_dasm_idxs_rx_pdu_buffered_notify,   // toolbox: phy_rx2buf
    pdu_dasm_idxs_rx_ahdr_interpret_req,    // toolbox: rx_interpret (rx_interpret)
    pdu_dasm_idxs_rx_dhdr_interpret_req,
    pdu_dasm_idxs_rx_apld_interpret_req,
    pdu_dasm_idxs_rx_pdu_log_req,
    pdu_dasm_idxs_rx_hash_lookup_notify,
    pdu_dasm_idxs_rx_interpret_end,
    pdu_dasm_idxs_rx_ahdr_interpret_end,    // toolbox: rx_ahdr_interpret
    pdu_dasm_idxs_rx_apld_interpret_end,    // toolbox: rx_apld_interpret
    pdu_dasm_idxs_tx_addr_filter_req,
    pdu_dasm_idxs_rx_addr_filter_req,
    pdu_dasm_idxs_rx_dhdr_interpret_end,    // toolbox: rx_dhdr_interpret
    pdu_dasm_idxs_rx_pdu_type_compose_end,  // toolbox: rx_pdu_type_compose
    pdu_dasm_idxs_rx_pdu_log_end,           // toolbox: rx_pdu_log
    pdu_dasm_idxs_rx_hash_notify0,          // toolbox: rx_hash
    pdu_dasm_idxs_rx_hash_notify1,
    pdu_dasm_idxs_rx_hash_notify2,
    pdu_dasm_idxs_rx_hash_notify3,
    pdu_dasm_idxs_rx_hash_notify4,
    pdu_dasm_idxs_rx_hash_notify5,
    pdu_dasm_idxs_rx_hash_notify6,
    pdu_dasm_idxs_rx_hash_notify7,
    pdu_dasm_idxs_asack,                    // info
    pdu_dasm_idxs_tx_addr_filter_hit,
    pdu_dasm_idxs_rx_addr_filter_hit,
    pdu_dasm_idxs_phy_rx2buf_req,           // policy
    pdu_dasm_idxs_rx_interpret_req,
    pdu_dasm_idxs_rx_pdu_vld_notify,
    pdu_dasm_idxs_rx_store_req,
    pdu_dasm_idxs_rx_soft_end,
    pdu_dasm_idxs_rx_pdu_irq,
    pdu_dasm_idxs_dmy,
    // emulation tick
    pdu_dasm_idxs_emufx_tick_notify = 63,

} ble_ll_hwif_pdu_dasm_idxs; // InDeX of Signals

#define pdu_dasm_idxs_latch_peer_addr_notify    pdu_dasm_idxs_rx_hash_notify0
#define pdu_dasm_idxs_latch_data_flag_notify    pdu_dasm_idxs_rx_hash_notify1
#define pdu_dasm_idxs_rx_data_ack_peer_notify   pdu_dasm_idxs_rx_hash_notify2
#define pdu_dasm_idxs_store_req_trigger         pdu_dasm_idxs_rx_hash_notify3
#define pdu_dasm_idxs_rx_soft_end_notify        pdu_dasm_idxs_rx_hash_notify4
#define pdu_dasm_idxs_trigger_tx_notify         pdu_dasm_idxs_rx_hash_notify5
#define pdu_dasm_idxs_trigger_rx_notify         pdu_dasm_idxs_rx_hash_notify6
#define pdu_dasm_idxs_rx_pdu_irq_trigger        pdu_dasm_idxs_rx_hash_notify7

#define pdu_dasm_idxs_rx_vld_latch              pdu_dasm_idxs_dmy

typedef volatile u64 ble_ll_hwif_signals;

typedef volatile struct ble_ll_hwif_pdu_dasm {

    // toolbox: phy_rx2buf
    union {
        u32 cfg_raw_mode_w;
        struct {
            u32 en  :8;
            u32 len :8;
        } cfg_raw_mode;
    };

    u32 cfg_1_bit_correct_en;

    // toolbox: rx_adv_header_interpret
    union {
        u64 cfg_filter_policy_w;
        struct {
            u16 adv :16;
            u16 scan:16;
            u16 init:16;
        } cfg_filter_policy;
    };

    // toolbox: rx_interpret
    u32 cfg_rx_interpret;

    // toolbox: pdu_type_compose
    union {
        u32 cfg_pdu_type_compose_w;
        struct {
            u32 en              :4;
            u32 constant_en     :12;
            u32 constant_val    :16;
        } cfg_pdu_type_compose;
    };

    // toolbox: rx_pdu_log
    u32 cfg_rx_pdu_log;

    // toolbox: rx_hash
    u32 cfg_rx_hash_entry_vld;

    union {
        u32 cfg_rx_hash_key_mask_w;
        struct {
            u32 data_ch :16;
            u32 adv_ch  :16;
        } cfg_rx_hash_key_mask;
    };

    ble_ll_hwif_rx_hash_st cfg_rx_hash[BLE_LL_HWIF_RX_HASH_SIZE];

    // toolbox: accumulate / condition
    union {
        u32 cfg_accumulate_tx_no_ack_cnt_w;
        struct {
            u32 en     :4;
            u32 clr_en :4;
            u32 init   :8;
        } cfg_accumulate_tx_no_ack_cnt;
    };

    union {
        u32                 cfg_cond_tx_no_ack_cnt_w;
        ble_ll_hwif_cond_st cfg_cond_tx_no_ack_cnt;
    };

    union {
        u32 cfg_accumulate_rx_crc_error_cnt_w;
        struct {
            u32 en     :4;
            u32 clr_en :4;
            u32 init   :8;
        } cfg_accumulate_rx_crc_error_cnt;
    };

    union {
        u32                 cfg_cond_rx_crc_error_cnt_w;
        ble_ll_hwif_cond_st cfg_cond_rx_crc_error_cnt;
    };

    // policy
    ble_ll_hwif_policy_st policy[pdu_dasm_policy_size];

    // info
    ble_ll_hwif_info_st         info        [pdu_dasm_info_size];
    ble_ll_hwif_info_long_st    info_long   [pdu_dasm_info_long_size];

    u32 ro_signals_w0;
    u32 ro_signals_w1;

} ble_ll_hwif_pdu_dasm_st;

/**
 * rx-ring-wr-manager
 *
 */
typedef enum {

    // external: pdu_dasm
    rx_ring_wrmgr_idxs_rx_store_req = 0,
    // external: air_prot
    rx_ring_wrmgr_idxs_alarm0,
    rx_ring_wrmgr_idxs_alarm0_notify0,
    rx_ring_wrmgr_idxs_alarm0_notify1,
    rx_ring_wrmgr_idxs_alarm0_notify2,
    rx_ring_wrmgr_idxs_alarm0_notify3,
    rx_ring_wrmgr_idxs_alarm1,
    rx_ring_wrmgr_idxs_alarm1_notify0,
    rx_ring_wrmgr_idxs_alarm1_notify1,
    rx_ring_wrmgr_idxs_alarm1_notify2,
    rx_ring_wrmgr_idxs_alarm1_notify3,
    // external: tx_ring_rdmgr
    rx_ring_wrmgr_idxs_tx_load_req,
    // external: tx_action
    rx_ring_wrmgr_idxs_tx_action,
    // toolbox: dma
    rx_ring_wrmgr_idxs_dma_end,
    // toolbox: ring
    rx_ring_wrmgr_idxs_ring_full,
    // toolbox: wr_ptr 
    rx_ring_wrmgr_idxs_wr_full_notify,
    // emulation tick
    rx_ring_wrmgr_idxs_emufx_tick_notify = 63,

} rx_ring_wrmgr_idxs;

typedef volatile struct ble_ll_hwif_rx_ring_wrmgr {

    // toolbox: ring
    ble_ll_hwif_ring_st ring;

    // glue
    u32 cfg_rx_long_pdu_addr;
    u32 cfg_rx_long_pdu_len_max;

} ble_ll_hwif_rx_ring_wrmgr_st;

/**
 * device filter
 *
 */
typedef enum {
    device_filter_idxs_tx_addr_filter_req = 0,
    device_filter_idxs_rx_addr_filter_req,

} device_filter_idxs;

#define BLE_LL_HWIF_DEVICE_FILTER_WHITELIST_SIZE 8
typedef volatile struct ble_ll_hwif_device_filter {

    ble_ll_hwif_addr_st cfg_whitelist[BLE_LL_HWIF_DEVICE_FILTER_WHITELIST_SIZE];

    u32 cfg_whitelist_en;

    // toolbox: tx_addr_filter
    union {
        u32 cfg_whitelist_value_msk_w;
        struct {
            u32 byte0:8;
            u32 byte5:8;
            u32 byte1:1;
            u32 byte2:1;
            u32 byte3:1;
            u32 byte4:1;
        } cfg_whitelist_value_msk;
    };

}ble_ll_hwif_device_filter_st;

/**
 * ack-manager
 *
 */
enum {

    ack_mgr_idxi_asack_ahdr_expand = 0,
    ack_mgr_idxi_asack_data_nesn_peer,
    ack_mgr_idxi_data_nesn_own,
    //
    ack_mgr_info_size,
};

enum {

    ack_mgr_idxp_data_md = 0,
    ack_mgr_idxp_dmy, 
    //
    ack_mgr_policy_size,
};

typedef enum {
    ack_mgr_idxs_cfg_ch_type = 0,       // external: register (hwif_cmn)
    ack_mgr_idxs_tx_pdu_sent_notify,    // external: pdu_asm
    ack_mgr_idxs_tx_ahdr_expand0,
    ack_mgr_idxs_tx_ahdr_expand1,
    ack_mgr_idxs_tx_ahdr_expand2,
    ack_mgr_idxs_tx_ahdr_expand3,
    ack_mgr_idxs_tx_ahdr_expand4,
    ack_mgr_idxs_tx_ahdr_expand5,
    ack_mgr_idxs_tx_ahdr_expand6,
    ack_mgr_idxs_tx_ahdr_expand7,
    ack_mgr_idxs_data_md_own,
    ack_mgr_idxs_data_sn_own,
    ack_mgr_idxs_rx_pdu_vld_notify,     // external: pdu_dasm
    ack_mgr_idxs_rx_ahdr_expand0,
    ack_mgr_idxs_rx_ahdr_expand1,
    ack_mgr_idxs_rx_ahdr_expand2,
    ack_mgr_idxs_rx_ahdr_expand3,
    ack_mgr_idxs_rx_ahdr_expand4,
    ack_mgr_idxs_rx_ahdr_expand5,
    ack_mgr_idxs_rx_ahdr_expand6,
    ack_mgr_idxs_rx_ahdr_expand7,
    ack_mgr_idxs_data_md_peer,
    ack_mgr_idxs_data_sn_peer,
    ack_mgr_idxs_data_nesn_peer,
    ack_mgr_idxs_rx_crcok,
    ack_mgr_idxs_rx_asack,
    ack_mgr_idxs_tx_addr_filter_hit,
    ack_mgr_idxs_rx_addr_filter_hit,
    ack_mgr_idxs_rx_new_data,
    ack_mgr_idxs_data_md_peer_clr,      // toolbox: glue
    ack_mgr_idxs_tx_trigger_tx_notify,
    ack_mgr_idxs_tx_trigger_rx_notify,
    ack_mgr_idxs_master_rx_process_end,
    ack_mgr_idxs_tbl_lookup_end,        // toolbox: tbl_by_ahdr
    ack_mgr_idxs_tbl_lookup_req,        // policy
    ack_mgr_idxs_data_md,
    ack_mgr_idxs_tx_acked_notify,
    ack_mgr_idxs_tx_notacked_notify,
    ack_mgr_idxs_data_nesn_own,
    ack_mgr_idxs_dmy,
    ack_mgr_idxs_asack_ahdr_expand0,    // info
    ack_mgr_idxs_asack_ahdr_expand1,
    ack_mgr_idxs_asack_ahdr_expand2,
    ack_mgr_idxs_asack_ahdr_expand3,
    ack_mgr_idxs_asack_ahdr_expand4,
    ack_mgr_idxs_asack_ahdr_expand5,
    ack_mgr_idxs_asack_ahdr_expand6,
    ack_mgr_idxs_asack_data_nesn_peer,
    ack_mgr_idxs_NOTUSED_data_nesn_own,

} ble_ll_hwif_ack_mgr_idxs;

#define BLE_LL_HWIF_ACK_MGR_TBL_SIZE    8
typedef volatile struct ble_ll_hwif_ack_mgr {

    u32 cfg_tbl_by_ahdr_vld;

    union {
        u32 cfg_tbl_by_ahdr01_w; 
        struct {
            u32 ahdr0:16;
            u32 ahdr1:16;
        } cfg_tbl_by_ahdr01;
    };
    union {
        u32 cfg_tbl_by_ahdr23_w; 
        struct {
            u32 ahdr2:16;
            u32 ahdr3:16;
        } cfg_tbl_by_ahdr23;
    };
    union {
        u32 cfg_tbl_by_ahdr45_w; 
        struct {
            u32 ahdr4:16;
            u32 ahdr5:16;
        } cfg_tbl_by_ahdr45;
    };
    union {
        u32 cfg_tbl_by_ahdr67_w; 
        struct {
            u32 ahdr6:16;
            u32 ahdr7:16;
        } cfg_tbl_by_ahdr67;
    };

    ble_ll_hwif_info_st     info  [ack_mgr_info_size];
    ble_ll_hwif_policy_st   policy[ack_mgr_policy_size];

    u32 ro_signals_w0;
    u32 ro_signals_w1;

} ble_ll_hwif_ack_mgr_st;

/**
 * pdu-assemble
 *
 */
enum {
    pdu_asm_idxi_tx_ahdr_build = 0,
    pdu_asm_idxi_tx_apld_tx_addr_build,
    pdu_asm_idxi_tx_apld_rx_addr_build,
    pdu_asm_idxi_tx_apld_rx_addr_src,
    pdu_asm_idxi_data_sn_own,
    pdu_asm_idxi_data_md_own,
    //
    pdu_asm_info_size,
};
enum {
    pdu_asm_tx_apld_rx_addr_src_addr_peer = 0,
    pdu_asm_tx_apld_rx_addr_src_whitelist,
};

enum {
    pdu_asm_idxp_dmy = 0,
    pdu_asm_idxp_tx_pdu_irq,
    //
    pdu_asm_policy_size,
};

typedef enum {
    pdu_asm_idxs_cfg_ch_type = 0,       // external: register (hwif_cmn)
    pdu_asm_idxs_phy_tx_ip,             // external: phy_tx
    pdu_asm_idxs_phy_tx_end,
    pdu_asm_idxs_tx_load_end,           // external: tx_ring_rdmgr
    pdu_asm_idxs_tx_pdu_req,            // external: air_protocol
    pdu_asm_idxs_data_nesn_own,         // external: ack_mgr
    pdu_asm_idxs_tx_tbl_lookup_end,     // toolbox: tx_tbl_by_ahdr
    pdu_asm_idxs_tx_hdr_build_req,      // toolbox: tx_build
    pdu_asm_idxs_tx_pld_build_req,
    pdu_asm_idxs_tx_build_end,
    pdu_asm_idxs_tx_ahdr_build_end,     // toolbox: tx_ahdr_build
    pdu_asm_idxs_tx_apld_build_end,     // toolbox: tx_apld_build
    pdu_asm_idxs_tx_dhdr_build_end,     // toolbox: tx_dhdr_build
    pdu_asm_idxs_cfg_long_pdu,          // toolbox: buf2phy_tx
    pdu_asm_idxs_buf2phy_tx_end,
    pdu_asm_idxs_tx_load_req,           // policy
    pdu_asm_idxs_tx_pdu_rdy,
    pdu_asm_idxs_tx_tbl_lookup_req,
    pdu_asm_idxs_tx_build_req,
    pdu_asm_idxs_buf2phy_tx_req,
    pdu_asm_idxs_tx_pdu_sent_notify,
    pdu_asm_idxs_dmy,
    pdu_asm_idxs_tx_ahdr_build,         // info
    pdu_asm_idxs_tx_apld_tx_addr_build,
    pdu_asm_idxs_tx_apld_rx_addr_build,
    pdu_asm_idxs_tx_apld_rx_addr_src,
    pdu_asm_idxs_data_sn_own,
    pdu_asm_idxs_data_md_own,
    pdu_asm_idxs_NOTUSED_ll_int0_clr,
    pdu_asm_idxs_tx_pdu_irq,
    pdu_asm_idxs_tx_tbl_notify4,
    pdu_asm_idxs_tx_tbl_notify5,
    pdu_asm_idxs_tx_tbl_notify7,
    pdu_asm_idxs_CONST0 = 63,
} ble_ll_hwif_pdu_asm_idxs;

#define pdu_asm_idxs_tx_tbl_tx_pdu_irq_trigger  pdu_asm_idxs_tx_tbl_notify7

#define BLE_LL_HWIF_PDU_ASM_TBL_SIZE 7
typedef volatile struct ble_ll_hwif_pdu_asm {

    // toolbox: buf2phy_tx
    union {
        u32 cfg_raw_mode_w;
        struct {
            u32 en  :8;
            u32 len :8;
        } cfg_raw_mode;
    };

    // toolbox: tbl_by_ahdr
    u32 cfg_tbl_by_ahdr_vld;

    union {
        u64 cfg_tbl_by_ahdr_w;
        u8  cfg_tbl_by_ahdr[BLE_LL_HWIF_PDU_ASM_TBL_SIZE];
    };

    // toolbox: tx_ahdr_build
    union {
        u32 cfg_ahdr_build_w;
        struct {
            u32 rx_addr :1;
            u32 tx_addr :1;
            u32 type    :1;
        } cfg_ahdr_build;
    };

    // toolbox: tx_apld_build
    union {
        u32 cfg_apld_build_w;
        struct {
            u32 rx_addr:1;
            u32 tx_addr:1;
        } cfg_apld_build;
    };

    // toolbox: tx_dhdr_build
    union {
        u32 cfg_dhdr_build_w; 
        struct {
            u32 md_val  :1;
            u32 md_ov   :1;
            u32 md      :1;
            u32 sn_val  :1;
            u32 sn_ov   :1;
            u32 sn      :1;
            u32 nesn_val:1;
            u32 nesn_ov :1;
            u32 nesn    :1;
            u32 llid    :1;
            u32         :6;
            u32 build   :1;
        } cfg_dhdr_build;
    };

    u32 asic_dbg0;              // TX_PDU_REQ_MANUAL

    ble_ll_hwif_info_st     info  [pdu_asm_info_size];
    ble_ll_hwif_policy_st   policy[pdu_asm_policy_size];

    u32 ro_signals_w0;
    u32 ro_signals_w1;

} ble_ll_hwif_pdu_asm_st;

/**
 * air-protocol
 *
 */
enum {
    air_prot_idxp_alarm0_by_follower0 = 0,
    air_prot_idxp_alarm1_by_follower1,
    air_prot_idxp_follower0_en,
    air_prot_idxp_follower1_en,
    air_prot_idxp_rf_tx_en,
    air_prot_idxp_phy_tx_en,
    air_prot_idxp_rf_rx_en,
    air_prot_idxp_phy_rx_en,
    air_prot_idxp_BUGGY_rx_access_tout, // note: asic bug: tie policy as constant
    air_prot_idxp_dmy0,
    air_prot_idxp_dmy1,
    air_prot_idxp_tx_pdu_req,
    //
    air_prot_policy_size,
} ;

typedef enum {

    air_prot_idxs_phy_tx_ip = 0,        // external: phy
    air_prot_idxs_phy_rx_ip,
    air_prot_idxs_NOTUSED_tx_rampoff_end,
    air_prot_idxs_phy_rx_end,
    air_prot_idxs_rf_tx_rdy,
    air_prot_idxs_rf_rx_rdy,
    air_prot_idxs_phy_rx_accessed,
    air_prot_idxs_pdu_rdy,              // external: pdu_asm
    air_prot_idxs_long_rf_cali,         // external: air_event_mgr
    air_prot_idxs_tx_action,
    air_prot_idxs_rx_action,
    air_prot_idxs_sync,
    air_prot_idxs_alarm0,               // toolbox: alarm0
    air_prot_idxs_alarm0_notify0,
    air_prot_idxs_alarm0_notify1,
    air_prot_idxs_alarm0_notify2,
    air_prot_idxs_alarm0_notify3,
    air_prot_idxs_alarm1,               // toolbox: alarm1
    air_prot_idxs_alarm1_notify0,
    air_prot_idxs_alarm1_notify1,
    air_prot_idxs_alarm1_notify2,
    air_prot_idxs_alarm1_notify3,
    air_prot_idxs_alarm0_active,        // toolbox: follwer
    air_prot_idxs_alarm1_active,
    air_prot_idxs_alarm0_by_follower0,  // policy
    air_prot_idxs_alarm1_by_follower1,
    air_prot_idxs_follower0_en,
    air_prot_idxs_follower1_en,
    air_prot_idxs_NOTUSED_rsv28,
    air_prot_idxs_rf_tx_en,
    air_prot_idxs_phy_tx_en,
    air_prot_idxs_NOTUSED_rsv31,
    air_prot_idxs_rf_rx_en,
    air_prot_idxs_phy_rx_en,
    air_prot_idxs_BUGGY_rx_access_tout,
    air_prot_idxs_pdu_req_tick,         // toolbox: tick_map
    air_prot_idxs_dmy0,
    air_prot_idxs_dmy1,
    air_prot_idxs_NOTUSED_gpi0,         // gpi
    air_prot_idxs_NOTUSED_gpi1,
    air_prot_idxs_NOTUSED_gpi2,
    air_prot_idxs_NOTUSED_gpi3,
    air_prot_idxs_alarm0_notify4,       // toolbox: alarm0
    air_prot_idxs_alarm1_notify4,       // toolbox: alarm1
    air_prot_idxs_rx_access_tout_tick,  // toolbox: tick_map
    air_prot_idxs_phy_rx_en_tick,
    air_prot_idxs_rf_rx_en_tick,
    air_prot_idxs_long_rx_rx_en_tick,
    air_prot_idxs_phy_tx_en_tick,
    air_prot_idxs_rf_tx_en_tick,
    air_prot_idxs_long_rf_tx_en_tick,
    air_prot_idxs_tx_pdu_req,           // policy
    air_prot_idxs_NOTUSED_tx_load_end,
    air_prot_idxs_air_event_ip,
    air_prot_idxs_phy_tx_end,
    air_prot_idxs_CONST0 = 63,

} ble_ll_hwif_air_prot_idxs;

#define air_prot_idxs_phy_trx_end   air_prot_idxs_dmy1

typedef volatile struct ble_ll_hwif_follower {

    u32 cfg_offset:16;
    u32 cfg_src:16;

} ble_ll_hwif_follower_st;

typedef volatile struct ble_ll_hwif_air_prot {

    // toolbox: tick_map
    union {
        u32 cfg_tsel_w;
        struct {
            u32 rx_access_tout:4;
            u32 phy_rx_en:4;
            u32 rf_rx_en:4;
            u32 long_rf_rx_en:4;
            u32 phy_tx_en:4;
            u32 rf_tx_en:4;
            u32 long_rf_tx_en:4;
            u32 pdu_req:4;
        } cfg_tsel;
    };

    union {
        u32 cfg_alarm_as_w;
        struct {
            u32 alarm1_asrx:1;
            u32 alarm1_astx:1;
            u32 alarm0_asrx:1;
            u32 alarm0_astx:1;
        } cfg_alarm_as;
    };

    // for policy gpi
    u32 cfg_policy_gpi:(4+(32-4));

    // toolbox: follower
    union {
        u32                     cfg_follower0_w;
        ble_ll_hwif_follower_st cfg_follower0;
    };

    union {
        u32                     cfg_follower1_w;
        ble_ll_hwif_follower_st cfg_follower1;
    };

    // toolbox: alarm, WRITE ONLY, for alarm bitwidth issue
    ble_ll_hwif_alarm_st cfg_wo_alarm0;
    ble_ll_hwif_alarm_st cfg_wo_alarm1;

    ble_ll_hwif_policy_st policy[air_prot_policy_size];

    u32 ro_signals_w0;
    u32 ro_signals_w1;

} ble_ll_hwif_air_prot_st;
#define BLE_LL_HWIF_TSEL_NOTIFY0    0
#define BLE_LL_HWIF_TSEL_NOTIFY1    1
#define BLE_LL_HWIF_TSEL_NOTIFY2    2
#define BLE_LL_HWIF_TSEL_NOTIFY3    3
#define BLE_LL_HWIF_TSEL_NOTIFY4    4
#define BLE_LL_HWIF_TSEL_ANCHOR     5

/**
 * tx_ring_rdmgr
 *
 */
enum {
    tx_ring_rdmgr_idxp_data_sn_own = 0,
    tx_ring_rdmgr_idxp_data_md_own,
    tx_ring_rdmgr_idxp_rd_vptr_inc,
    tx_ring_rdmgr_idxp_dma_src_null,
    tx_ring_rdmgr_idxp_BUGGY_dmy,
    tx_ring_rdmgr_idxp_pdu_waitack,
    tx_ring_rdmgr_idxp_null_waitack,
    //
    tx_ring_rdmgr_policy_size,
};

enum {
    tx_ring_rdmgr_idxs_cfg_ch_type = 0,     // external: register (hwif_cmn)
    tx_ring_rdmgr_idxs_tx_acked_notify,     // external: ack_mgr
    tx_ring_rdmgr_idxs_tx_load_req,         // external: pdu_asm
    tx_ring_rdmgr_idxs_rx_store_req,        // external: pdu_dasm
    tx_ring_rdmgr_idxs_alarm0,              // external: air_prot
    tx_ring_rdmgr_idxs_alarm0_notify0,
    tx_ring_rdmgr_idxs_alarm0_notify1,
    tx_ring_rdmgr_idxs_alarm0_notify2,
    tx_ring_rdmgr_idxs_alarm0_notify3,
    tx_ring_rdmgr_idxs_alarm1,
    tx_ring_rdmgr_idxs_alarm1_notify0,
    tx_ring_rdmgr_idxs_alarm1_notify1,
    tx_ring_rdmgr_idxs_alarm1_notify2,
    tx_ring_rdmgr_idxs_alarm1_notify3,
    tx_ring_rdmgr_idxs_ring_empty,          // toolbox: ring
    tx_ring_rdmgr_idxs_rd_last_pdu_notify,  // toolbox: rdmgr
    tx_ring_rdmgr_idxs_rd_empty_notify,
    tx_ring_rdmgr_idxs_NOTUSED_dma_en,      // toolbox: dma
    tx_ring_rdmgr_idxs_dma_ready,           // level
    tx_ring_rdmgr_idxs_rd_vptr_inc_notify,  // policy
    tx_ring_rdmgr_idxs_data_md_own,
    tx_ring_rdmgr_idxs_data_sn_own,
    tx_ring_rdmgr_idxs_dma_en,
    tx_ring_rdmgr_idxs_tx_load_end,
    tx_ring_rdmgr_idxs_pdu_waitack,
    tx_ring_rdmgr_idxs_null_waitack,
    tx_ring_rdmgr_idxs_BUGGY_dmy,
    tx_ring_rdmgr_idxs_NOTUSED_x,
    tx_ring_rdmgr_idxs_dma_src_null,
    tx_ring_rdmgr_idxs_dma_end,             // pulse
};
// workaround-0
// #define tx_ring_rdmgr_idxs_tx_acked_notify_redge    tx_ring_rdmgr_idxs_BUGGY_dmy

// workaround-1
#define tx_ring_rdmgr_idxp_data_sn_own_loaded       tx_ring_rdmgr_idxp_BUGGY_dmy
//
#define tx_ring_rdmgr_idxs_tx_acked_notify_redge    tx_ring_rdmgr_idxs_tx_acked_notify
#define tx_ring_rdmgr_idxs_data_sn_own_loaded       tx_ring_rdmgr_idxs_BUGGY_dmy

typedef volatile struct ble_ll_hwif_tx_ring_rdmgr {

    // toolbox: ring
    ble_ll_hwif_ring_st ring;

    // glue
    u32 cfg_tx_long_pdu_addr;
    u32 cfg_null_pdu_addr;

    ble_ll_hwif_policy_st policy[tx_ring_rdmgr_policy_size];

    u32 ro_signals_w0;
    u32 ro_signals_w1;

} ble_ll_hwif_tx_ring_rdmgr_st;

enum {
    air_event_idxp_sync = 0,
    air_event_idxp_rf_long_cali,
    air_event_idxp_tout,
    air_event_idxp_air_event_ip,
    air_event_idxp_hard_end,
    air_event_idxp_data_soft_end,
    air_event_idxp_tx_req,
    air_event_idxp_rx_req,
    air_event_idxp_air_event_irq0,
    air_event_idxp_air_event_irq1,
    air_event_idxp_dmy0,
    air_event_idxp_dmy1,
    //
    air_event_policy_size,
};

enum {
    air_event_idxs_NOTUSED_cfg_air_event_en = 0,    // external: register (hwif_cmn)
    air_event_idxs_cfg_ch_type,
    air_event_idxs_cfg_anchor_astx,
    air_event_idxs_anchor,                          // external: anchor
    air_event_idxs_anchor_notify0,
    air_event_idxs_anchor_notify1,
    air_event_idxs_anchor_notify2,
    air_event_idxs_anchor_notify3,
    air_event_idxs_anchor_notify4,
    air_event_idxs_tx_action_tick,                  // external: air_prot
    air_event_idxs_rx_action_tick,
    air_event_idxs_BUGGY_rx_access_tout,
    air_event_idxs_phy_tx_en,
    air_event_idxs_phy_rx_en,
    air_event_idxs_alarm0_notify3,
    air_event_idxs_alarm1_notify3,
    air_event_idxs_tx_soft_end_trigger,             // external: pdu_asm
    air_event_idxs_tx_trigger_tx_notify,            // external: ack_mgr
    air_event_idxs_tx_trigger_rx_notify,
    air_event_idxs_data_md,
    air_event_idxs_rx_trigger_tx_notify,            // external: pdu_dasm
    air_event_idxs_rx_trigger_rx_notify,
    air_event_idxs_rx_soft_end_notify,
    air_event_idxs_rx_pdu_vld_notify,
    air_event_idxs_phy_tx_end,                      // external: phy
    air_event_idxs_phy_rx_end,
    air_event_idxs_tx_ring_rd_empty_notify,         // external: tx_ring_rdmgr
    air_event_idxs_rx_ring_wr_full_notify,          // external: rx_ring_wrmgr
    air_event_idxs_soft_end,                        // glue
    air_event_idxs_pdu_trigger_tx_notify,
    air_event_idxs_pdu_trigger_rx_notify,
    air_event_idxs_quality_bad,
    air_event_idxs_tx_action,                       // toolbox: half_duplex
    air_event_idxs_tx_end,
    air_event_idxs_rx_action,
    air_event_idxs_rx_end,
    air_event_idxs_cond_rx_crc_error_cnt,           // (trigger directly from pdu_dasm)
    air_event_idxs_cond_tx_no_ack_cnt,              // (trigger directly from pdu_dasm)
    air_event_idxs_accum_tx_action,                 // toolbox: accum
    air_event_idxs_accum_rx_action,
    air_event_idxs_tx_req,                          // policy
    air_event_idxs_rx_req,
    air_event_idxs_sync,
    air_event_idxs_rf_long_cali,
    air_event_idxs_tout,
    air_event_idxs_hard_end,
    air_event_idxs_air_event_ip,
    air_event_idxs_adv_soft_end,
    air_event_idxs_data_soft_end,
    air_event_idxs_dmy0,
    air_event_idxs_dmy1,
    air_event_idxs_NOTUSED_irq2_clr,                // extra
    air_event_idxs_NOTUSED_irq3_clr,
    air_event_idxs_NOTUSED_irq4_clr,
    air_event_idxs_NOTUSED_irq5_clr,
    air_event_idxs_phy_tx_ip,
    air_event_idxs_phy_rx_accessed,
    air_event_idxs_master_rx_process_end,
    air_event_idxs_CONST0 = 63,
};

#define air_event_idxp_gp_irq               air_event_idxp_air_event_irq0
#define air_event_idxp_air_event_end        air_event_idxp_air_event_irq1

#define air_event_idxs_air_event_rx_tout    air_event_idxs_anchor_notify2
#define air_event_idxs_air_event_tout       air_event_idxs_anchor_notify4
#define air_event_idxs_rx_access_tout       air_event_idxs_dmy0
#define air_event_idxs_last_tx              air_event_idxs_dmy1

/**
 * air_event_manager
 *
 */
typedef volatile struct ble_ll_hwif_air_event {

    union {
        u32                     cfg_accum0_w;
        ble_ll_hwif_accum_st    cfg_accum0;
    };

    u32 cfg_anchor_astx;

    union {
        u32                     cfg_accum1_w;
        ble_ll_hwif_accum_st    cfg_accum1;
    };

    ble_ll_hwif_policy_st policy[air_event_policy_size];

    u32 ro_signals_w0;
    u32 ro_signals_w1;

    union {
        u32 ro_action_cnt_w;
        struct {
            u8  tx;
            u8  rx;
        } ro_action_cnt;
    };

} ble_ll_hwif_air_event_st;

#define ble_ll_do_air_event_direct_hard_end() \
    do { \
    BLE_LL_LOG_ERR("%s hard_end\n", __func__); \
    hwif_air_event->policy[air_event_idxp_hard_end].if_w = HWIF_POLICY_IF_SET;  \
    } while(0)

#define BLE_LL_AIR_EVENT_DIRECT_HARD_END_POLLING_CNT_MAX 10000

/**
 * anchor
 *
 */
#define BLE_LL_HWIF_ANCHOR_ALARM_NUM 5

#define BLE_LL_HWIF_ANCHOR_PRIORITY_HIGH    1
#define BLE_LL_HWIF_ANCHOR_PRIORITY_LOW     0

typedef volatile struct ble_ll_hwif_anchor {

    ble_ll_hwif_alarm_st cfg_alarm[BLE_LL_HWIF_ANCHOR_ALARM_NUM];

    ble_ll_hwif_clock_st cfg_clock;

    u32 cfg_arbi;

    union {
        u32 info_w;
        struct {
            u32 anchor_time :28;
            u32 id          :2;
            u32 vld         :1;
        } info;
    };

} ble_ll_hwif_anchor_st;

/**
 * first_rx_log (only in CondorC)
 *
 */
typedef volatile struct ble_ll_hwif_first_rx_log {

    union {
        u32 w;
        struct {
            u32 phy_rssi            :8;
            u32 phy_access_time     :20;
            u32                     :2;
            u32 rssi_vld            :1;
            u32 phy_access_time_vld :1;
        };
    };

} ble_ll_hwif_first_rx_log_st;

// common
extern ble_ll_hwif_cmn_st* const hwif_cmn;

// pdu_dasm
extern ble_ll_hwif_buf_st*      const hwif_rx_buf;
extern ble_ll_hwif_pdu_dasm_st* const hwif_pdu_dasm;

// rx_ring_wrmgr
extern ble_ll_hwif_rx_ring_wrmgr_st* const hwif_rx_ring_wrmgr;

// device filter
extern ble_ll_hwif_device_filter_st* const hwif_device_filter;

// ack_mgr
extern ble_ll_hwif_ack_mgr_st* const hwif_ack_mgr;

// pdu_asm
extern ble_ll_hwif_buf_st*      const hwif_tx_buf;
extern ble_ll_hwif_pdu_asm_st*  const hwif_pdu_asm;

// air_prot
extern ble_ll_hwif_air_prot_st* const hwif_air_prot;

// tx_ring_rdmgr
extern ble_ll_hwif_tx_ring_rdmgr_st* const hwif_tx_ring_rdmgr;

// air_event_manager
extern ble_ll_hwif_air_event_st* const hwif_air_event;

// anchor
extern ble_ll_hwif_anchor_st*       const hwif_anchor;
extern ble_ll_hwif_clock_time_st*   const hwif_now;

// first_rx_log (only in CondorC)
extern ble_ll_hwif_first_rx_log_st* const hwif_first_rx_log;

/** ##############################################
 * ble_ll_hwif_tbl_st
 *  - all link-layer hwif
 * ############################################### */
typedef struct ble_ll_hwif_tbl {

    ble_ll_hwif_cmn_st              cmn;
    ble_ll_hwif_air_prot_st         air_prot;
    ble_ll_hwif_air_event_st        air_event;
    ble_ll_hwif_ack_mgr_st          ack_mgr;
    ble_ll_hwif_pdu_asm_st          pdu_asm;
    ble_ll_hwif_pdu_dasm_st         pdu_dasm;
    ble_ll_hwif_tx_ring_rdmgr_st    tx_ring_rdmgr;
    ble_ll_hwif_rx_ring_wrmgr_st    rx_ring_wrmgr;
    ble_ll_hwif_device_filter_st    device_filter;

} ble_ll_hwif_tbl_st;

void ble_ll_hwif_tbl_store(const ble_ll_hwif_tbl_st* tbl);

/**
 * hwif_tbl default value, should be store when boot.
 *
 */
extern const ble_ll_hwif_tbl_st     hwif_tbl_init;

#define ble_ll_hwif_anchor_reset() \
do { \
    regset((void*)hwif_anchor, 0, sizeof(ble_ll_hwif_anchor_st)); \
} while(0)

/** ##############################################
 * hwif_profile (80-byte)
 *  - used to configure link-layer hw when air_event begin
 *  - fixed for specific state/role
 * ############################################### */
typedef void (*BLE_LL_AIR_EVENT_GPIRQ_CB)();
typedef void (*BLE_LL_PDU_DASM_IRQ_CB)();

typedef struct ble_ll_hwif_profile {

    // # cmn
    ble_ll_hwif_cmn_st cmn;

    // # air_event ({tx/rx}_action_cnt/soft-end/hard-end)
    u8  cfg_anchor_astx;

    // ## hard-end
    u8  cfg_tx_action_accum_thd;
    u8  cfg_rx_action_accum_thd;

} ble_ll_hwif_profile_st;

void ble_ll_hwif_profile_store(const ble_ll_hwif_profile_st* profile);

/** ##############################################
 * ble_ll_hwif_cfg_st (x-byte)
 *  - used to configure link-layer hw when air_event begin
 *  - variable under host instruction
 *  - variable between air_events
 * ############################################### */
#define BLE_LL_HWIF_CFG_RX_HASH_IRQ_TARGET_CNT_MAX  7

typedef struct ble_ll_hwif_cfg {

    // # ch
    u8  ch:6;
    // # addr
    u8  cfg_own_use_random_addr :1;
    // # features
    u8  cfg_long_pdu:1;

    // # end condition
    u8  cfg_tx_empty_direct_end     :1;
    u8  cfg_rx_full_direct_end      :1;
    u8  cfg_rx_mount_pdu            :1;
    s8  cfg_rx_hash_irq_target_cnt  :4;

    // # whitelist
    u8  whitelist_en;

    // # tx_pwr
    u8  tx_pwr; // RF_POWER in phy

    // # phy configuration
    u32 cfg_access_addr;

    union {
        u32 cfg_phy_w;
        struct {
            u32 crc_init:   24;
            u32 dwlfsr_seed:7;
        } cfg_phy;
    };

    // # rx_hash (vld)
    const ble_ll_hwif_rx_hash_st*   rx_hash;
    u16                             rx_hash_key_mask;
    u16                             rx_hash_entry_vld;

    // ## bad_pdu/default: if (hash != 0), enable the raw of hash.
    ble_ll_hwif_rx_hash_st  rx_hash_bad_pdu;
    ble_ll_hwif_rx_hash_st  rx_hash_def;

    ble_addr_st* whitelist;

    // # hardend src
    union {
        u32 cfg_hard_end_src_w;
        struct {
            u32 sel0:(6+2);
            u32 sel1:(6+2);
            u32 sel2:(6+2);
            u32 sel3: 6;
            u32 manual_val  :1;
            u32 manual      :1;
        } cfg_hard_end_src;
    };

    // # gpirq
    BLE_LL_AIR_EVENT_GPIRQ_CB   gpirq_cb;
    ble_ll_hwif_policy_st       gpirq_policy;
    u8                          gpirq_priority;
    u8                          gpirq_type;

    BLE_LL_PDU_DASM_IRQ_CB  pdu_dasm_irq_cb;
    u8                      pdu_dasm_irq_priorty;

} ble_ll_hwif_cfg_st;

void ble_ll_hwif_cfg_store(ble_ll_hwif_cfg_st* cfg);
static inline s8 ble_ll_hwif_cfg_hash_irq_target_cnt_limit(s32 target_cnt) {

    if(target_cnt > BLE_LL_HWIF_CFG_RX_HASH_IRQ_TARGET_CNT_MAX) {
        return BLE_LL_HWIF_CFG_RX_HASH_IRQ_TARGET_CNT_MAX;
    }
    return target_cnt;
}
/** ##############################################
 * trx_ring
 *  - data interface between fw/hw
 *  - in current configuration (ring depth 4), size (4 +1) *2 +1 = 11-words, or 44-byte.
 * ############################################### */
typedef struct ble_ll_hwif_trx_ring {

    ble_ll_ring_st  tx_ring;
    ble_ll_ring_st  rx_ring;

    u8  tx_const_pdu;   // in advch, we may have constant pdu

} ble_ll_hwif_trx_ring_st;

void ble_ll_hwif_trx_ring_store (ble_ll_hwif_trx_ring_st* trx_ring);
void ble_ll_hwif_trx_ring_load  (ble_ll_hwif_trx_ring_st* trx_ring);

/** ##############################################
 * data flags used in data-ch
 *  - data channel flag
 * ############################################### */
typedef struct ble_ll_hwif_data_flag {

    // # own-side info
    u8  sn_own:     1;  // (policy @tx_ring, + x_waitack -> asack_nesn_peer(info@ack_mgr))
    u8  nesn_own:   1;  // (info   @ack_mgr, related to rx "new" logic)

    u8  pdu_waitack:    1;  // (policy @tx_ring)
    u8  null_waitack:   1;  // (policy @tx_ring, if null_waitack, dma_src_null should be asserted)

} ble_ll_hwif_data_flag_st;
/**
 * data_flag operation:
 *  - in store, take-care of md_own
 *      # if (tx_pdu_cnt == 0), dma_src_null = 1.
 *
 */
void ble_ll_hwif_data_flag_store(const  ble_ll_hwif_data_flag_st* flag, u32 tx_pdu_cnt);
void ble_ll_hwif_data_flag_load (       ble_ll_hwif_data_flag_st* flag);

/** ##############################################
 * anchor timing related configuratios
 * ############################################### */
extern u8 g_anchor_lockup;

typedef u8 BLE_LL_ANCHOR_ID;
s16 ble_ll_hwif_anchor_store(u8 conn_id, u8 anchor_id, ble_ll_anchor_profile_st* profile);

/**
 * ble_ll_hwif_anchor_cancel()
 *  - used by fsm, when requested other modules (host cmd)
 *      + return anchor active or not. fsm MUST handle remaining notify, is "true" is return.
 *  - operate in critical section
 *
 */
u8 ble_ll_hwif_anchor_cancel(u8 anchor_id);

/**
 * ble_ll_hwif_anchor_off()
 *  - used by air_event_end handle
 *
 */
s16 ble_ll_hwif_anchor_off(u8 conn_id);

/**
 * ble_ll_hwif_anchor_enabled()
 *  - used to check if anchor is enabled(cfg_en) or not
 *
 */
#define ble_ll_hwif_anchor_enabled(anchor_id) \
    (hwif_anchor->cfg_alarm[anchor_id].cfg_en)

/**
 * ble_ll_hwif_anchor_free_window()
 *  - return anchor free window of specified priority, from tref
 *      >= 0: free window, in us
 *      <  0: no free window, until tref -(return);
 *  - offset
 *      offset of tref, for some early (< 0) action
 *  - priority:
 *      0: low priority
 *      1: high
 *
 * ble_ll_hwif_anchor_free_window_without_cs(): action without cs, caller should invoke this fx inside cs.
 * ble_ll_hwif_anchor_free_window():            action inside cs
 */
BLE_LL_US ble_ll_hwif_anchor_free_window_without_cs(ble_ll_hwif_clock_time_st tref, BLE_LL_US offset, u8 priority);

#include "bsp/cs.h"
#include "bsp/intl_cs.h"
__STATIC_INLINE BLE_LL_US ble_ll_hwif_anchor_free_window(ble_ll_hwif_clock_time_st tref, BLE_LL_US offset, u8 priority) {

    BLE_LL_US free_window;

    OS_EnterCritical();
    free_window = ble_ll_hwif_anchor_free_window_without_cs(tref, offset, priority);
    OS_ExitCritical();

    return free_window;
}


/**
 * g_anchor_id_map
 *  - mapping: from anchor_id to conn_id
 *      + set by fsm, when leave IDLE state
 *      + used by irqh, to select corresponding hwif_profile/trx_ring.
 *
 */
extern NV_DATA u8 g_anchor_id_map[];

/**
 * g_anchor_active
 *  - asserted, if air_event_begin has been triggered.
 *      + asserted by irqh
 *      + checked by fsm, when fsm want to "cancel" anchor
 *
 */
extern NV_DATA u8 g_anchor_active[];

#if 0
/** ##############################################
 * interface address
 * ############################################### */
#define ADDR_LL_HWIF_CMN            0x00c02000  //CSR_LL_REG_A2_BASE
// hwif address from yushan.chou@20150306
#define ADDR_LL_HWIF_PDU_DASM       0x00c02030  //LL_TRX_REG_BASE
#define ADDR_LL_HWIF_RX_RING_RWMGR  0x00c02190  //ADR_CSR_RX_RING_CTRL_0
#define ADDR_LL_HWIF_DEVICE_FILTER  0x00c021c0  //ADR_CSR_TX_WHITELIST_ADDR0_0
#define ADDR_LL_HWIF_PDU_ASM        0x00c02210  //ADR_LL_TX_PDU_RAW_MODE
#define ADDR_LL_HWIF_TX_RING_RDMGR  0x00c022c0  //ADR_CSR_TX_RING_CTRL_0
#define ADDR_LL_HWIF_ACK_MGR        0x00c02380  //LL_FUNC_REG_BASE
#define ADDR_LL_HWIF_AIR_EVENT      0x00c02460  //ADR_AEM_ACCUMULATOR_0
#define ADDR_LL_HWIF_AIR_PROT       0x00c02520  //ADR_AIRPRO_TICKMAP_0
#define ADDR_LL_HWIF_ANCHOR         0x00c02660  //ADR_CSR_ANCHOR_ALARM_0_EN
#define ADDR_LL_HWIF_NOW            0X00c02724  //ADR_ANCHOR_ACTIVE_TIME
#define ADDR_LL_HWIF_RX_BUF         0x00c02a00  //RX_PDU_BUF_REG_BASE
#define ADDR_LL_HWIF_TX_BUF         0x00c02b00  //TX_PDU_BUF_REG_BASE
#define ADDR_LL_HWIF_FIRST_RX_LOG   0x00c02028  //ADR_LL_RX_RSSI_INFO
#endif
/** ##############################################
 * signals
 * ############################################### */
#define HWIF_SIGNALS_GET(_HWIF_, _IDX_) U64_BIT_GET(U64_BUILD(_HWIF_->ro_signals_w1, _HWIF_->ro_signals_w0), _IDX_)

/** ##############################################
 * rx_hash instance
 *  - used to configure pdu_dasm rx_hash
 * ############################################### */
extern const ble_ll_hwif_rx_hash_st g_ble_ll_hwif_rx_hash_adv[];
extern const ble_ll_hwif_rx_hash_st g_ble_ll_hwif_rx_hash_scan_passive[];
extern const ble_ll_hwif_rx_hash_st g_ble_ll_hwif_rx_hash_scan_backoff[];
extern const ble_ll_hwif_rx_hash_st g_ble_ll_hwif_rx_hash_scan_active[];
extern const ble_ll_hwif_rx_hash_st g_ble_ll_hwif_rx_hash_inita[];
extern const ble_ll_hwif_rx_hash_st g_ble_ll_hwif_rx_hash_conn[];

#define BLE_LL_HWIF_RX_HASH_KEY_MASK_ADVCH  0xf000  // mask state
#define BLE_LL_HWIF_RX_HASH_KEY_MASK_DATACH 0xf023  // mask state, llid and asack

#define BLE_LL_HWIF_RX_HASH_ENTRY_VLD_ADV_FROM_ANY                  (((0x0005) << 3) | (0x0005))
#define BLE_LL_HWIF_RX_HASH_ENTRY_VLD_ADV_SCAN_REQ_FROM_WHITELIST   (((0x0005) << 3) | (0x0006))
#define BLE_LL_HWIF_RX_HASH_ENTRY_VLD_ADV_CONN_REQ_FROM_WHITELIST   (((0x0006) << 3) | (0x0005))
#define BLE_LL_HWIF_RX_HASH_ENTRY_VLD_ADV_ALL_FROM_WHITELIST        (((0x0006) << 3) | (0x0006))
#define BLE_LL_HWIF_RX_HASH_ENTRY_VLD_ADV_CONN_DIRECT               (((0x0006) << 3) | (0x0000))

#define BLE_LL_HWIF_RX_HASH_ENTRY_VLD_SCAN_PASSIVE  0x0f
#define BLE_LL_HWIF_RX_HASH_ENTRY_VLD_SCAN_ACTIVE   0x1f
#define BLE_LL_HWIF_RX_HASH_ENTRY_VLD_INITA         0x03
#define BLE_LL_HWIF_RX_HASH_ENTRY_VLD_CONN          0x0f

/** ##############################################
 * hwif_profile/hwif_cfg instance
 *  - index by conn_id
 * ############################################### */
extern const    ble_ll_hwif_profile_st    ble_ll_hwif_profile   [];
extern NV_DATA  ble_ll_hwif_cfg_st      g_ble_ll_hwif_cfg       [];

/** ##############################################
 * g_ble_ll_hwif_trx_ring instance
 *  - index by conn_id
 * ############################################### */
extern NV_DATA ble_ll_hwif_trx_ring_st  g_ble_ll_hwif_trx_ring[];

/** ##############################################
 * g_ble_ll_hwif_data_flag instance
 *  - index by conn_id
 * ############################################### */
extern NV_DATA ble_ll_hwif_data_flag_st g_ble_ll_hwif_data_flag[];

/** ##############################################
 * hwif reset
 *
 * ############################################### */
s16 ble_ll_hwif_reset();

/** ##############################################
 * hwif patch entry
 *
 * ############################################### */
void ble_ll_hwif_default_patch();
void ble_ll_hwif_patch(u8 conn_id);

#endif
