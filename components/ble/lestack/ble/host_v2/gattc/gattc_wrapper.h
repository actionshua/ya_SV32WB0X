#ifndef _GATTC_WRAPPER_H_
#define _GATTC_WRAPPER_H_



#include "gattc_def.h"
#include "ble/ctrl_v2/ble_ll_if.h"
#include "ble/hci_lib.h"



u32 gattc_svcmd_handle(u32 cmd, u32 *svc_args);
void gattc_wrapper_evt_hci_handler(ble_ll_evt_hci_general_st *hci_event);



#endif  /// end of _GATTC_WRAPPER_H_
