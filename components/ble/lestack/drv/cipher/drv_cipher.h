#ifndef _DRV_CIPHER_H_
#define _DRV_CIPHER_H_

#define DRV_CIPHER_KEY_WORDS    4
#define DRV_CIPHER_DATA_WORDS   4

#define DRV_CIPHER_KEY_SIZE     16
#define DRV_CIPHER_DATA_SIZE    16

enum {
    DRV_CIPHER_DATA_IS_LENDIAN = 0,
    DRV_CIPHER_DATA_IS_BENDIAN,
};

typedef struct drv_cipher_data_in {
    u8  data_len;
    u8* data;
} drv_cipher_data_in_st;

void drv_cipher_aes128(const u8* key, const u8* data_in, u8 big_endian, u8* data_out);

void drv_cipher_aes128_key  (const u32* key, u8 big_endian);

#include "regs/chip_reg.h"
#ifndef MAIN_CHIP
#error !MAIN_CHIP not defined
#endif

#define DRV_CIPHER_AES128_KEY_LENDIAN(_KEY_) \
do { \
    REG32(ADR_AES_KEY_0) = *(((volatile u32 *)(_KEY_)));     \
    REG32(ADR_AES_KEY_1) = *(((volatile u32 *)(_KEY_)) +1);  \
    REG32(ADR_AES_KEY_2) = *(((volatile u32 *)(_KEY_)) +2);  \
    REG32(ADR_AES_KEY_3) = *(((volatile u32 *)(_KEY_)) +3);  \
} while(0)
#define DRV_CIPHER_AES128_KEY_BENDIAN(_KEY_) drv_cipher_aes128_key((_KEY_), true)


#endif
