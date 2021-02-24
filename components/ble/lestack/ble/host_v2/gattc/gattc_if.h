#ifndef _GATTC_IF_H_
#define _GATTC_IF_H_


#include "gattc_def.h"
#include "l2cap/l2cap_if.h"



u8 GATTC_reset(void);
u8 GATTC_exchange_mtu_request(u16 conn_hdl, u16 mtu_size);
u8 GATTC_discover_primary_services_request(u16 conn_hdl, u16 start_attr_hdl);
u8 GATTC_discover_primary_services_by_uuid_request(u16 conn_hdl, u16 start_attr_hdl, uuid_st *service_uuid);
u8 GATTC_discover_characteristics_request(u16 conn_hdl, u16 start_attr_hdl, u16 end_attr_hdl);
u8 GATTC_discover_descriptors_request(u16 conn_hdl, u16 start_attr_hdl, u16 end_attr_hdl);
u8 GATTC_read_request(u16 conn_hdl, u16 attr_hdl, u16 offset);
u8 GATTC_write_request(u16 conn_hdl, u8 type, u16 attr_hdl_or_flags, attr_value_st *attr_value);
u8 GATTC_handle_connection_complete_event(u16 conn_hdl, u8 status);
u8 GATTC_handle_disconnection_complete_event(u16 conn_hdl, u8 status);
u8 GATTC_handle_op_response(u16 conn_hdl, l2cap_sdu_st *sdu);
u8 GATTC_handle_value_notification(u16 conn_hdl, l2cap_sdu_st *sdu);
u8 GATTC_handle_value_indication(u16 conn_hdl, l2cap_sdu_st *sdu);



#endif  /// end of _GATTC_IF_H_
