/*
 * crypto_sha1.h
 *
 *  Created on: Apr 24, 2019
 *      Author: Matt
 */

#ifndef INCLUDE_CRYPTO_CRYPTO_SHA1_H_
#define INCLUDE_CRYPTO_CRYPTO_SHA1_H_
#include <stdint.h>
#include <stddef.h>

/**
 * \brief          The SHA-1 context structure.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
typedef struct crypto_sha1_context
{
    uint32_t total[2];          /*!< The number of Bytes processed.  */
    uint32_t state[5];          /*!< The intermediate digest state.  */
    unsigned char buffer[64];   /*!< The data block being processed. */
}
crypto_sha1_context;


int crypto_sha1_coef_restore(crypto_sha1_context *ctx);
int crypto_sha1_coef_load(crypto_sha1_context *ctx);
int crypto_sha1_process( crypto_sha1_context *ctx, const unsigned char data[64] );
inline void crypto_sha1_to_le(crypto_sha1_context *ctx, unsigned char output[20]);

int mbedtls_sha1_ret_c( const unsigned char *input,
                        size_t ilen,
                        unsigned char output[20]);
int mbedtls_sha1_update_ret_c( crypto_sha1_context *ctx,
                               const unsigned char *input,
                               size_t ilen );
int mbedtls_sha1_finish_ret_c( crypto_sha1_context *ctx,
                               unsigned char output[20] );

#endif /* INCLUDE_CRYPTO_CRYPTO_SHA1_H_ */
