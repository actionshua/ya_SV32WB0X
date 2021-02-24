#ifndef _BLE_API_H_
#define _BLE_API_H_

#include "hci_ssv_common.h"

int ble_register_hcievent_callback(void (*callback_func)(u8 *evt, u16 evtlen));
int ble_enable(u8 mode);
uint32_t les_hci_cmd(uint32_t    cmd_len, const uint8_t* cmd, uint32_t  sync_evt_len_max, uint8_t* sync_evt);

#endif
