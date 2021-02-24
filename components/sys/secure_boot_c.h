#ifndef __SECURE_BOOT_C_H__
#define __SECURE_BOOT_C_H__

#include "soc_types.h"

#define FLASH_START_ADDR 0x30000000
#define HASH_BUFF_SIZE 512

/****************************************************************************************************/
/* XXX:1. Don't use __attribute__((__packed__)), or compiler will do stupid thing to degrade perf.  */
/* XXX:2. Because of 1, please keep every fields aligned!!!                                         */
/****************************************************************************************************/
//typedef struct __attribute__((__packed__)) bl_sec_header {
typedef struct bl_sec_header {
    uint8_t bl_sign_r[32];
    uint8_t bl_sign_s[32];
    uint8_t reserved[36];
    u32     xip1_addr;
    u32     xip2_addr;
    u32     magic;
    u32     bl_size;
    u32     xtal_freq;
    u32     flash_bit_mode;
    u32     flash_freq;
    uint8_t *bl;
} bl_sec_header_t;

typedef struct bl_nonsec_header {
    uint8_t reserved[36];
    u32     xip1_addr;
    u32     xip2_addr;
    u32     magic;
    u32     bl_size;
    u32     xtal_freq;
    u32     flash_bit_mode;
    u32     flash_freq;
    uint8_t *bl;
} bl_nonsec_header_t;

#endif
