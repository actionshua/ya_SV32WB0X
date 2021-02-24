#ifndef _GATTC_PROC_H_
#define _GATTC_PROC_H_


#include "gattc_def.h"



/// procedure request
u8 gattc_proc_exchange_mtu_request(u16 conn_hdl, u16 mtu_size);
u8 gattc_proc_discover_primary_services_request(u16 conn_hdl, u16 start_attr_hdl);
u8 gattc_proc_discover_primary_services_by_uuid_request(u16 conn_hdl, u16 start_attr_hdl, uuid_st *service_uuid);
u8 gattc_proc_discover_characteristics_request(u16 conn_hdl, u16 start_attr_hdl, u16 end_attr_hdl);
u8 gattc_proc_discover_descriptors_request(u16 conn_hdl, u16 start_attr_hdl, u16 end_attr_hdl);
u8 gattc_proc_read_request(u16 conn_hdl, u16 attr_hdl, u16 offset);
u8 gattc_proc_write_request(u16 conn_hdl, u8 type, u16 attr_hdl_or_flags, attr_value_st *attr_value);

/// procedure handle value operation
u8 gattc_proc_handle_value_operation(u16 conn_hdl, u8 type, l2cap_sdu_st *sdu);

/// procedure response
u8 gattc_proc_exchange_mtu_response(u16 conn_hdl, l2cap_sdu_st *sdu);
u8 gattc_proc_discover_primary_services_response(u16 conn_hdl, l2cap_sdu_st *sdu);
u8 gattc_proc_discover_primary_services_by_uuid_response(u16 conn_hdl, l2cap_sdu_st *sdu);
u8 gattc_proc_discover_characteristics_response(u16 conn_hdl, l2cap_sdu_st *sdu);
u8 gattc_proc_discover_descriptors_response(u16 conn_hdl, l2cap_sdu_st *sdu);
u8 gattc_proc_read_response(u16 conn_hdl, l2cap_sdu_st *sdu);
u8 gattc_proc_write_response(u16 conn_hdl, l2cap_sdu_st *sdu);



#endif  /// end of _GATTC_PROC_H_
