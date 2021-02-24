/*
 * crypto_common.h
 *
 *  Created on: May 21, 2019
 *      Author: Matt
 */


#ifndef CRYPTO_H_
#define CRYPTO_H_

#include "osal.h"

#define AES_BLOCK_SIZE 16

int ssv_mbedtls_arc4_skip ( const u8 *key, size_t keylen, size_t skip,
                 u8 *data, size_t data_len );

int aes_wrap(const u8 *kek, size_t kek_len, int n, const u8 *plain,
                      u8 *cipher);
int aes_unwrap(const u8 *kek, size_t kek_len, int n,
                        const u8 *cipher, u8 *plain);
int omac1_aes_128_vector(const u8 *key, size_t num_elem,                                                                                                                                                           
                              const u8 *addr[], const size_t *len,
                                                    u8 *mac);
int omac1_aes_128(const u8 *key, const u8 *data, size_t data_len,
                           u8 *mac);

int sha1_prf(const u8 *key, size_t key_len, const char *label,                                                                                                                                                     
                 const u8 *data, size_t data_len, u8 *buf, size_t buf_len);

int sha256_prf_bits(const u8 *key, size_t key_len, const char *label,                                                                                                                                              
                    const u8 *data, size_t data_len, u8 *buf,
                                size_t buf_len_bits);
int sha256_prf(const u8 *key, size_t key_len, const char *label,
                  const u8 *data, size_t data_len, u8 *buf, size_t buf_len);

#endif /* CRYPTO_H_ */
