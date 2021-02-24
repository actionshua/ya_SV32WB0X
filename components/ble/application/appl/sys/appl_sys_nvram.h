#ifndef _APPL_SYS_NVRAM_H_
#define _APPL_SYS_NVRAM_H_


#include "stdint.h"
#include "string.h"
#include "appl/common/appl_error.h"



#define APPL_SYS_NVRAM_HANDLER_MAX          2



typedef enum {

    APPL_SYS_NVRAM_MODE_NONE = 0,
    APPL_SYS_NVRAM_MODE_FLASH,
    APPL_SYS_NVRAM_MODE_RAM,

} APPL_SYS_NVRAM_MODE;



typedef struct 
{
    APPL_SYS_NVRAM_MODE mode;
    uint32_t base_addr;

} appl_sys_nvram_st;



APPL_RESULT appl_sys_nvram_register_handler(APPL_SYS_NVRAM_MODE mode, uint32_t base_addr, uint8_t *handler);
APPL_RESULT appl_sys_nvram_unregister_handler(uint8_t handler);
APPL_RESULT appl_sys_nvram_peek(uint8_t handler, uint8_t **dst, uint32_t offset);
APPL_RESULT appl_sys_nvram_read(uint8_t handler, uint8_t *dst, uint32_t offset, uint32_t size);
APPL_RESULT appl_sys_nvram_write(uint8_t handler, uint8_t *src, uint32_t offset, uint32_t size);



#endif  /// end of _APPL_SYS_NVRAM_H_
