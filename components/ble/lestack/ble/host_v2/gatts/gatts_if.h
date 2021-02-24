#ifndef _GATTS_IF_H_
#define _GATTS_IF_H_


#include "gatts_def.h"
#include "l2cap/l2cap_if.h"



u8 GATTS_reset(void);
u8 GATTS_handle_connection_complete_event(u16 conn_hdl, u8 status);
u8 GATTS_handle_disconnection_complete_event(u16 conn_hdl, u8 status);
u8 GATTS_handle_value_indication(u16 conn_hdl, u16 att_hdl);
u8 GATTS_handle_value_notification(u16 conn_hdl, u16 att_hdl);
u8 GATTS_handle_indication_confirm(u16 conn_hdl, l2cap_sdu_st *sdu);



#endif  /// end of _GATTS_IF_H_
