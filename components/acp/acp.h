#ifndef _ACP_H
#define _ACP_H

#include "mbedtls/chacha20.h"

#define MAGIC_NONCE_SHIFT 8

#define MAGIC_KEY_SHIFT(k) do { \
                               int i; \
                               for (i = 1 ; i < 32 ; i++) \
                                   k[i] = ((k[i] ^ k[i-1]) << 2) + 58; \
                           } while (0)

typedef struct {
    uint8_t offset[4];
    u32     enable;
    u32     offset1;
    u32     size1;
    u32     offset2;
    u32     size2;
    uint8_t nonce[24];
} acp_header_t;

typedef struct {
    mbedtls_chacha20_context ctx1;
    mbedtls_chacha20_context ctx2;
} acp_int_info_t;

typedef struct {
    unsigned int enable;
    unsigned int offset1;//the acp1 start addr relative to the data head
    unsigned int size1;
    unsigned int offset2;//the acp2 start addr relative to the data head
    unsigned int size2;
    unsigned char nonce[24];
    unsigned int magic_pos;
    acp_int_info_t acp_int_info;
} acp_ext_info_t;

void acp_trng(unsigned int word_cnt, unsigned char *addr);
int acp_init(acp_int_info_t *acp_info, unsigned char *key, unsigned char *nonce);
void acp_deinit(acp_int_info_t *acp_info);
void acp_encrypt1(acp_int_info_t *acp_info, unsigned char *addr, size_t size);
void acp_encrypt2(acp_int_info_t *acp_info, unsigned char *addr, size_t size);
void acp_decrypt1(unsigned char *key, unsigned char *nonce, unsigned char *from, unsigned char *to, size_t size);
void acp_decrypt2(unsigned char *key, unsigned char *nonce, unsigned char *from, unsigned char *to, size_t size);

#endif // _ACP_H
