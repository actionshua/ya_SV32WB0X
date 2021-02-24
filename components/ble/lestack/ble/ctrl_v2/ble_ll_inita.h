#ifndef _BLE_LL_INITA_H_
#define _BLE_LL_INITA_H_

#include "ble_ll_op.h"

/**
 * return true, if inita task is busy
 */
u8  ble_ll_inita_busy();

/**
 * return true, if whitelist is adoped
 *
 */
u8  ble_ll_inita_whitelist_adopted();

/**
 * get stored anchor_profile of inita
 *
 */
void ble_ll_inita_read_anchor_profile(ble_ll_anchor_profile_st* anchor_profile);

/**
 * dump inita info
 *
 */
void ble_ll_inita_info_dump();

/**
 * reset
 */
s16 ble_ll_inita_reset();

/**
 * inita task
 */
s16 ble_ll_inita(ble_ll_op_un op);

#endif // _BLE_LL_INITA_H_
