#ifndef _GAP_WRAPPER_H_
#define _GAP_WRAPPER_H_


#include "gap_def.h"
#include "l2cap/l2cap_if.h"
#include "ble/hci_lib.h"
#include "ble/ctrl_v2/ble_ll_if.h"



u32 gap_svcmd_handle(u32 svc_number, u32 *svc_args);
void gap_wrapper_evt_hci_handler(ble_ll_evt_hci_general_st *hci_event);
void gap_handle_l2cap_data(u16 conn_hdl, l2cap_sdu_st *sdu);



#endif  // end of _GAP_WRAPPER_H_

