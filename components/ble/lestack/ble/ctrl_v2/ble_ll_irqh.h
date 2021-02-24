#ifndef _BLE_LL_IRQH_H_
#define _BLE_LL_IRQH_H_

#include "lib/condor_ssv_lib.h"
#include "ssv_types.h"

#include "ble/ctrl_v2/ble_ll_hwif.h"

/**
 * air_event_gp irqh: as a general purpose irq, could be used to latch "programmable" event.
 *  everytime irq trigger, do following procedure:
 *      ## turn off irq
        ## call the registered callback
 *
 */
typedef void (*BLE_LL_AIR_EVENT_GPIRQ_CB)();
typedef void (*BLE_LL_PDU_DASM_IRQ_CB)();

typedef enum {
    BLE_LL_AIR_EVENT_GPIRQ_CB_SINGLE = 1,
    BLE_LL_AIR_EVENT_GPIRQ_CB_ALWAYS,
}   BLE_LL_AIR_EVENT_GPIRQ_CB_TYPE;

void ble_ll_air_event_gpirq_cb_register(ble_ll_hwif_policy_st policy,
    BLE_LL_AIR_EVENT_GPIRQ_CB cb, BLE_LL_AIR_EVENT_GPIRQ_CB_TYPE type);

void ble_ll_pdu_dasm_irq_cb_register(BLE_LL_PDU_DASM_IRQ_CB cb);

void _wifi_block_switch_to_ble(void);
void _wifi_block_switch_to_wifi(void);

#endif  // _BLE_LL_IRQH_H_
