#include "ble/ctrl_v2/ble_ll_hwif.h"

extern const ble_ll_hwif_policy_st ble_ll_scan_early_stopper_policy;

#define BLE_LL_SCAN_EARLY_STOPPER_PRIORITY (0)
void ble_ll_scan_early_stopper();
