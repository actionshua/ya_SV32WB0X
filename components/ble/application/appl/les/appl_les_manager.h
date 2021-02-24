#ifndef _APPL_LES_MANAGER_H_
#define _APPL_LES_MANAGER_H_



#include "stdint.h"
#include "string.h"
#include "les_if/api/inc/les_api.h"
#include "appl/common/appl_error.h"



typedef enum
{
    LOCAL_DEVICE_IOCAP                  = 0x00,
    LOCAL_DEVICE_OOB                    = 0x00,
    LOCAL_DEVICE_BONDING                = 0x01,
    LOCAL_DEVICE_MITM                   = 0x01,
    LOCAL_DEVICE_ENC_KEY_SIZE_MAX       = 0x10,
    LOCAL_DEVICE_ENC_KEY_SIZE_MIN       = 0x07,
    LOCAL_DEVICE_INIT_DIST_KEY          = 0x07,
    LOCAL_DEVICE_RSP_DIST_KEY           = 0x07,

} LOCAL_DEVICE;



typedef struct 
{
    bd_addr_st  local_addr;
    uint8_t     iocap;
    uint8_t     oob;
    uint8_t     bonding;
    uint8_t     mitm;
    uint8_t     max_enc_key_size;
    uint8_t     min_enc_key_size;
    uint8_t     init_key_dist;
    uint8_t     rsp_key_dist;    
    uint8_t     div[SMP_KEY_SIZE_2BYTE];
    uint32_t    target_count;
    bd_addr_st  target_addr;

} appl_les_manager_device_st;



void appl_les_manager_init(void);
void appl_les_manager_set_local_device_property(uint8_t iocap, uint8_t oob, uint8_t bonding, uint8_t mitm);
void appl_les_manager_set_target_bd_addr(bd_addr_st *target_addr);



#endif  /// end of _APPL_LES_MANAGER_H_
