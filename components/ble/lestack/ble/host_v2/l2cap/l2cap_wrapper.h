#ifndef _L2CAP_WRAPPER_H_
#define _L2CAP_WRAPPER_H_



#include "l2cap_def.h"
#include "ble/ctrl_v2/ble_ll_if.h"
#include "ble/hci_lib.h"



void l2cap_wrapper_reset(void);
u32 l2cap_svcmd_handle(u32 svc_number, u32 *svc_args);
void l2cap_wrapper_evt_hci_handler(ble_ll_evt_hci_general_st *hci_event);
u8 l2cap_wrapper_host_event_handler(u32 host_event, u32 param0, u32 param1, u32 param2);



#endif  /// end of _L2CAP_WRAPPER_H_
