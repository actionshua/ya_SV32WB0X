#include <stdint.h>
#include "sa_cfg.h"
#include <string.h>
#include <stdio.h>

#define CFG_ASSERT(cmp) \
    do { \
    } while(!(cmp))

extern const struct sa_cfg g_sa_cfg __attribute__((section(".sa_mp_data")));
const struct sa_cfg g_sa_cfg __attribute__((section(".sa_mp_data"))) = {
    .buf_mp = { 8, 8, 8, 8, 8, 8, 8,0x97,0x97, 7, 9, 10, 7, 7, 7, 7, 7, 0,
                8, 8, 8, 8, 8, 8, 8,0x97,0x97, 7, 9, 10, 7, 7, 7, 7, 7, 0,
                8, 8, 8, 8, 8, 8, 8,0x97,0x97, 7, 9, 10, 7, 7, 7, 7, 7, 0,
                4, 
                2,
               13, 11, 9, 7,
               13, 11, 9, 7,
               13, 11, 9, 7,
               35, 90,
               0,0xFF,
               13, 10, 10, 9, 0x4A, 0x92, 0x64, 0x92, 0xCC, 0xB6, 0xDB, 0x96,
               13, 10, 10, 9, 0x4A, 0x92, 0x64, 0x92, 0xCC, 0xB6, 0xDB, 0x96,
               13, 10, 10, 9, 0x4A, 0x92, 0x64, 0x92, 0xCC, 0xB6, 0xDB, 0x96,
               0x1E,0x14,0x7C,0x15,0x44,0x16,
               0x53,0x53,0x56,0x00,
               0x01,0x00,0x00,0x00,
               0x01,0x00,0x00,0x00
}
};

