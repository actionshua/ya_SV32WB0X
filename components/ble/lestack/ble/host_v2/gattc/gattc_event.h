#ifndef _GATTC_EVENT_H_
#define _GATTC_EVENT_H_


#include "gattc_def.h"



void gattc_event_send_exchange_mtu_response(u16 conn_hdl, u8 status, u8 err_reason, gattc_les_event_st *gattc_les_event);
void gattc_event_send_discover_primary_services_response(u16 conn_hdl, u8 status, u8 err_reason, gattc_les_event_st *gattc_les_event);
void gattc_event_send_discover_primary_services_by_uuid_response(u16 conn_hdl, u8 status, u8 err_reason, gattc_les_event_st *gattc_les_event);
void gattc_event_send_discover_characteristics_response(u16 conn_hdl, u8 status, u8 err_reason, gattc_les_event_st *gattc_les_event);
void gattc_event_send_discover_descriptors_response(u16 conn_hdl, u8 status, u8 err_reason, gattc_les_event_st *gattc_les_event);
void gattc_event_send_read_response(u16 conn_hdl, u8 status, u8 err_reason, gattc_les_event_st *gattc_les_event);
void gattc_event_send_write_response(u16 conn_hdl, u8 status, u8 err_reason, gattc_les_event_st *gattc_les_event);
void gattc_event_send_handle_value_operation(u16 conn_hdl, gattc_les_event_st *gattc_les_event, l2cap_sdu_st *sdu);



#endif  /// end of _GATTC_EVENT_H_
