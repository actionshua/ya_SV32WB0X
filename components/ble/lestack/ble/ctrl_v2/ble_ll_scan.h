#ifndef _BLE_LL_SCAN_H_
#define _BLE_LL_SCAN_H_

#include "ble_ll_op.h"

/**
 * return true, if scan task is busy
 */
u8  ble_ll_scan_busy();

/**
 * return true, if whitelist is adoped
 *
 */
u8  ble_ll_scan_whitelist_adopted();

/**
 * get stored anchor_profile of scan
 *
 */
void ble_ll_scan_read_anchor_profile(ble_ll_anchor_profile_st* anchor_profile);

/**
 * dump scan info
 *
 */
void ble_ll_scan_info_dump();

/**
 * reset
 */
s16 ble_ll_scan_reset();

/**
 * scan task
 */
s16 ble_ll_scan(ble_ll_op_un op);

#endif // _BLE_LL_SCAN_H_
