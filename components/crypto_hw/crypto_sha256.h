/*
 * crypto_sha256.h
 *
 *  Created on: Apr 23, 2019
 *      Author: Matt
 */

#ifndef INCLUDE_CRYPTO_CRYPTO_SHA256_H_
#define INCLUDE_CRYPTO_CRYPTO_SHA256_H_
#include <stdint.h>
#include <stddef.h>

typedef struct crypto_sha256_context
{
    uint32_t total[2];          /*!< The number of Bytes processed.  */
    uint32_t state[8];          /*!< The intermediate digest state.  */
    unsigned char buffer[64];   /*!< The data block being processed. */
    int is224;                  /*!< Determines which function to use:
                                     0: Use SHA-256, or 1: Use SHA-224. */
}
crypto_sha256_context;

inline int crypto_sha256_coef_restore(crypto_sha256_context *ctx);
inline int crypto_sha256_coef_load(crypto_sha256_context *ctx);
int crypto_sha256_process( crypto_sha256_context *ctx, const unsigned char data[64] );
inline void crypto_sha256_to_le(crypto_sha256_context *ctx, unsigned char output[32]);

int mbedtls_sha256_ret_c( const unsigned char *input,
                        size_t ilen,
                        unsigned char output[32],
                        int is224 );
int mbedtls_sha256_update_ret_c( crypto_sha256_context *ctx,
                               const unsigned char *input,
                               size_t ilen );
int mbedtls_sha256_finish_ret_c( crypto_sha256_context *ctx,
                               unsigned char output[32] );

#endif /* INCLUDE_CRYPTO_CRYPTO_SHA256_H_ */
