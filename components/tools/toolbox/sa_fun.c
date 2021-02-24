#include <stdint.h>
#include <flash.h>
#include "sa_cfg.h"
#include "osal.h"
#include <string.h>
#include <stdio.h>

#define CFG_ASSERT(cmp) \
    do { \
    } while(!(cmp))

extern const struct sa_cfg g_sa_cfg __attribute__((section(".sa_mp_data")));

void cfg_dump_sa_table(int len) {
    int i;
    volatile uint8_t *ptr = (volatile uint8_t *)&g_sa_cfg;
    for (i = 0; i < len; i++) {
        if ((i!=0) && (i%36 == 0)) {
            printf("\n");
        }
        printf("%02X-", ptr[i]);
    }
    printf("\n");
}

void cfg_sa_write_cfg(struct sa_cfg *new_cfg, uint16_t len) {
	OS_DeclareCritical();
    CFG_ASSERT(len <= FLASH_SECTOR_SIZE);
    flash_init();
    uint8_t *buf = OS_MemAlloc(FLASH_SECTOR_SIZE);
    memcpy(&(buf[0]), (uint8_t*)new_cfg, len);
    memcpy(&(buf[len]), (((uint8_t *)&g_sa_cfg)+len), FLASH_SECTOR_SIZE-len);
    uint32_t ptr = (uint32_t)((uint32_t)(&g_sa_cfg) & (0xFFFFFF));
    OS_EnterCritical();
    flash_sector_erase((unsigned int)ptr);
    int i;
    
    for (i = 0; i < FLASH_SECTOR_SIZE; i+=FLASH_PAGE_SIZE) {
        flash_page_program(ptr+i, FLASH_PAGE_SIZE, &(buf[i]));
    }
    OS_ExitCritical();
    OS_MemFree(buf);
}

