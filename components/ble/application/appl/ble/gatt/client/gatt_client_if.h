#ifndef _GATT_CLIENT_IF_H_
#define _GATT_CLIENT_IF_H_



#include "gatt_client_def.h"



uint8_t gatt_client_init(void);
uint8_t gatt_client_deinit(void);
uint8_t gatt_client_handle_connection_complete_event(uint16_t conn_hdl, uint8_t status);
uint8_t gatt_client_handle_disconnection_complete_event(uint16_t conn_hdl, uint8_t status);
uint8_t gatt_client_new_db(uint16_t conn_hdl, uint8_t *mem_ptr, uint16_t mem_size);
uint8_t gatt_client_free_db(uint16_t conn_hdl);
void *gatt_client_get_db_element(uint16_t conn_hdl, uint16_t idx);
uint8_t gatt_client_disc_db(uint16_t conn_hdl);
uint8_t gatt_client_handle_discovered_services(uint16_t conn_hdl, gattc_discover_primary_services_response_st *response, gatt_client_evt_st *p_evt);
uint8_t gatt_client_handle_discovered_characteristics(uint16_t conn_hdl, gattc_discover_characteristics_response_st *response, gatt_client_evt_st *p_evt);
uint8_t gatt_client_handle_discovered_descriptors(uint16_t conn_hdl, gattc_discover_descriptors_response_st *response, gatt_client_evt_st *p_evt);



#endif  /// end of _GATT_CLIENT_IF_H_
