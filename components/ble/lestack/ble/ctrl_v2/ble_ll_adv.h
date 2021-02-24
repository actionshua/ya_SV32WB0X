#ifndef _BLE_LL_ADV_H_
#define _BLE_LL_ADV_H_

#include "ble/ctrl_v2/ble_ll.h"
#include "ble/ctrl_v2/ble_ll_op.h"

/**
 * return true, if adv task is busy
 *
 */
u8  ble_ll_adv_busy();

/**
 * return true, if whitelist is adoped
 *
 */
u8  ble_ll_adv_whitelist_adopted();

/**
 * get stored anchor_profile of adv
 *
 */
void ble_ll_adv_read_anchor_profile(ble_ll_anchor_profile_st* anchor_profile);

/**
 * dump adv info
 *
 */
void ble_ll_adv_info_dump();

/**
 *
 *
 */
s16 ble_ll_adv_reset();

/**
 *
 *
 */
s16 ble_ll_adv(ble_ll_op_un op);

static inline s16 ble_ll_adv_cmd_hci_advertise_enable (u8 enable) {
//    printf("ble_ll_adv_cmd_hci_advertise_enable\n");
    ble_ll_op_un op = {
        .cmd.hci.le_set_advertise_enable = {
            .type_w = BLE_LL_CMD_HCI_TYPE(BLE_LL_CMD_HCI_CODE_LE_SET_ADVERTISE_ENABLE),
            .enable = enable,
        },
    };
    return ble_ll_adv(op);
}

#endif // _BLE_LL_ADV_H_
