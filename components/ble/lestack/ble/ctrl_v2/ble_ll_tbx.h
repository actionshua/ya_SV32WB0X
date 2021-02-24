#ifndef _BLE_LL_TBX_
#define _BLE_LL_TBX_

#include "ssv_types.h"

#include "ble/ble_lib_v2.h"
#include "ble/ctrl_v2/ble_ll.h"

/** ##############################################
 * about ch
 * ############################################### */
u32 ble_ll_tbx_advch_hop(u8 ch, u32 ch_map, u8* ch_nxt, u8 adv_start);

#define DATACH_CH_WRAP(_X_) \
do {                        \
if(_X_ > BLE_DATACH_CH_MAX) {   \
    _X_ -= BLE_DATACH_CH_NUM;   \
}                           \
} while(0)
u32 ble_ll_tbx_datach_map(u8 unmap_ch, ble_datach_map_st ch_map);


/** ##############################################
 * about timing
 * ############################################### */
/**
 * minimum x in table, where x /2^20 >= ppm /10^6.
 *
 */
u16 ble_ll_tbx_ppm_over2exp20(u16 ppm);

BLE_LL_US ble_ll_tbx_advdelay();
BLE_LL_US ble_ll_tbx_window_widening(u16 sca, BLE_LL_US duration);
s16 ble_ll_tbx_estimate_ppm   (BLE_LL_US conn_intv,
    BLE_LL_INSTANT ref_instant,     ble_ll_clock_time_st ref_tstamp,
    BLE_LL_INSTANT sync_instant,    ble_ll_clock_time_st sync_tstamp);

/**
 * algorithm to calculate slavelatency limit, with raw_conn_interval/raw_supervision_timeout
 */
u16 ble_ll_tbx_slavelatency_limit(u16 latency, u16 raw_conn_interval, u16 raw_supervision_timeout);

/**
 * algorithm to calculate next active instance under slavelatency
 *  - input
 *      + latency:          current latency
 *      + instant:          current instant
 *      + idle_instant:     the instant without traffic
 *      + latency_limit:    latency upper limit
 *  - output
 *      + latency
 */
u16 ble_ll_tbx_slavelatency(u16 latency, u16 latency_limit, BLE_LL_INSTANT instant, BLE_LL_INSTANT idle_instant);
/**
 * algorithm to calculate slave anchor
 *  - update anchor/rx_window_128us in anchor profile
 *  - return "rx_window_sat", if rx_tout > tout
 */
u8 ble_ll_tbx_slave_anchor(ble_ll_anchor_profile_st* anchor_profile,
    BLE_LL_US conn_intv, u16 sca_over2exp20,
    BLE_LL_INSTANT sync_instant, ble_ll_clock_time_st sync_tstamp,
    u16 data_pdu_max_txtme,
    BLE_LL_INSTANT trgt_instant);

u8 ble_ll_tbx_master_anchor(ble_ll_anchor_profile_st* anchor_profile,
    BLE_LL_US conn_intv, u16 sca_over2exp20,
    BLE_LL_INSTANT sync_instant, ble_ll_clock_time_st sync_tstamp, u16 data_pdu_max_txtme,
    BLE_LL_INSTANT trgt_instant);
// algorithm to calculate slave anchor, window based
u8 ble_ll_tbx_slave_anchor_window(ble_ll_anchor_profile_st* anchor_profile,
    BLE_LL_US conn_intv, u16 sca_over2exp20,
    ble_ll_conn_window_st window, ble_ll_clock_time_st sync_tstamp,
    BLE_LL_INSTANT trgt_instant);

u8 ble_ll_tbx_master_anchor_window(ble_ll_anchor_profile_st* anchor_profile,
    BLE_LL_US conn_intv, u16 sca_over2exp20,
    ble_ll_conn_window_st window, ble_ll_clock_time_st sync_tstamp,
    BLE_LL_INSTANT trgt_instant);
/** ##############################################
 * for init
 * ############################################### */
u32 ble_ll_tbx_access_addr_gen();
u32 ble_ll_tbx_crc_init_gen();

/** ##############################################
 * for scan
 * ############################################### */
// algorithm to generate backoff_cnt after the air_event sending scan_req.
typedef struct ble_ll_scan_backoff_info {

    s8 upper_limit_2exp;

    u8 success_cnt;
    u8 fail_cnt;

} ble_ll_scan_backoff_info_st;

s16 ble_ll_tbx_scan_backoff_cnt_gen(ble_ll_scan_backoff_info_st* info, u32 success);

/** ##############################################
 * for initiator
 * ############################################### */
//TODO if ble_ll_tbx_inita_backoff_cnt_gen is required to seperate with ble_ll_tbx_scan_backoff_cnt_gen which is for scan_rsp
#if 1 //temp for build pass
typedef struct ble_ll_inita_backoff_info {

    s8 upper_limit_2exp;

    u8 success_cnt;
    u8 fail_cnt;

} ble_ll_inita_backoff_info_st;

s16 ble_ll_tbx_inita_backoff_cnt_gen(ble_ll_inita_backoff_info_st* info, u32 success);
#endif

/** ##############################################
 * for phy
 * ############################################### */
ble_ll_clock_time_st drv_phy_rx_ref_time(ble_ll_clock_time_st init_time, u32 rxlog_access_time, BLE_LL_US offset);

#endif // _BLE_LL_TBX_
