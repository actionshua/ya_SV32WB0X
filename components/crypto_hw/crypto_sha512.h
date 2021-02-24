/*
 * crypto_sha512.h
 *
 *  Created on: Apr 23, 2019
 *      Author: Matt
 */

#ifndef INCLUDE_CRYPTO_CRYPTO_SHA512_H_
#define INCLUDE_CRYPTO_CRYPTO_SHA512_H_

#include <stdint.h>
#include <stddef.h>

typedef struct crypto_sha512_context
{
    uint64_t total[2];          /*!< The number of Bytes processed. */
    uint64_t state[8];          /*!< The intermediate digest state. */
    unsigned char buffer[128];  /*!< The data block being processed. */
    int is384;                  /*!< Determines which function to use:
                                     0: Use SHA-512, or 1: Use SHA-384. */
}
crypto_sha512_context;

int crypto_sha512_coef_restore(crypto_sha512_context *ctx);
int crypto_sha512_coef_load(crypto_sha512_context *ctx);
int crypto_sha512_process( crypto_sha512_context *ctx, const unsigned char data[128] );
inline void crypto_sha512_to_le(crypto_sha512_context *ctx, unsigned char output[64]);

int mbedtls_sha512_ret_c( const unsigned char *input,
                        size_t ilen,
                        unsigned char output[64],
                        int is384 );
int mbedtls_sha512_update_ret_c( crypto_sha512_context *ctx,
                               const unsigned char *input,
                               size_t ilen );
int mbedtls_sha512_finish_ret_c( crypto_sha512_context *ctx,
                               unsigned char output[64] );

#endif /* INCLUDE_CRYPTO_CRYPTO_SHA512_H_ */
