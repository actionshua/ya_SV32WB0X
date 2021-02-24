#ifndef _GATT_CLIENT_API_H_
#define _GATT_CLIENT_API_H_



#include "stdint.h"
#include "gatt_client_def.h"



#define GATT_CLIENT_EVT_NTY_SIZE_MAX        23



typedef enum
{
    GATT_CLIENT_CMD_DISC_DB = 0x00,
    GATT_CLIENT_CMD_MAX,
    GATT_CLIENT_CMD_INVALID = GATT_CLIENT_CMD_MAX,

} GATT_CLIENT_CMD;



typedef enum
{
    GATT_CLIENT_EVT_CMD_COMP = 0x00,
    GATT_CLIENT_EVT_NTY,
    GATT_CLIENT_EVT_MAX,
    GATT_CLIENT_EVT_INVALID = GATT_CLIENT_EVT_MAX,

} GATT_CLIENT_EVT;



typedef struct
{
    uint8_t     cmd;
    uint8_t     status;
    uint8_t     err_reason;

} gatt_client_evt_cmd_comp_st;



typedef struct
{
    uint8_t     size;
    uint8_t     data[GATT_CLIENT_EVT_NTY_SIZE_MAX];

} gatt_client_evt_nty_st;



typedef struct 
{
    uint8_t     evt;
    uint16_t    conn_hdl;

    union
    {
        gatt_client_evt_cmd_comp_st     cmd_comp_evt;
        gatt_client_evt_nty_st          nty_evt;
    };

} gatt_client_evt_st;



uint8_t gatt_client_api_init(void);
uint8_t gatt_client_api_deinit(void);
uint8_t gatt_client_api_new_db(uint16_t conn_hdl, uint8_t *mem_ptr, uint16_t mem_size);
uint8_t gatt_client_api_free_db(uint16_t conn_hdl);
void *gatt_client_api_get_db_element(uint16_t conn_hdl, uint16_t idx);
uint8_t gatt_client_api_disc_db(uint16_t conn_hdl);



#endif  /// end of _GATT_CLIENT_API_H_
