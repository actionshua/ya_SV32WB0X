#include "ble/ctrl_v2/ble_ll_hwif.h"

extern const ble_ll_hwif_policy_st ble_ll_jammer_policy;

#define BLE_LL_JAMMER_PRIORITY (3)
void ble_ll_jammer_irqh();

#define BLE_LL_SCAN_JAMMER_PRIORITY (3)
void ble_ll_scan_jammer();
