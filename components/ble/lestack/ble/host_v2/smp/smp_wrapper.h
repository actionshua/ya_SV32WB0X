#ifndef _SMP_WRAPPER_H_
#define _SMP_WRAPPER_H_



#include "smp_def.h"
#include "l2cap/l2cap_if.h"
#include "ble/ctrl_v2/ble_ll_if.h"
#include "ble/hci_lib.h"



// Functions
void smp_wrapper_reset(void);
u32 smp_svcmd_handle(u32 cmd, u32 *svc_args);
void smp_handle_l2cap_data(u16 conn_hdl, l2cap_sdu_st *sdu);
void smp_wrapper_evt_hci_handler(ble_ll_evt_hci_general_st *hci_event);



#endif  /// end of _SMP_WRAPPER_H_
