/*
 * crypto_gcm.h
 *
 *  Created on: Apr 25, 2019
 *      Author: Matt
 */

#ifndef INCLUDE_CRYPTO_CRYPTO_GCM_H_
#define INCLUDE_CRYPTO_CRYPTO_GCM_H_

#include "mbedtls/cipher.h"

/**
 * \brief          The GCM context structure.
 */
typedef struct crypto_gcm_context
{
    ssv_mbedtls_cipher_context_t cipher_ctx;  /*!< The cipher context used. */
    unsigned char h[16];                      /*!< Precalculated HTable high. */
    uint64_t len;                         /*!< The total length of the encrypted data. */
    uint64_t add_len;                     /*!< The total length of the additional data. */
    unsigned char base_ectr[16];          /*!< The first ECTR for tag. */
    unsigned char y[16];                  /*!< The Y working value. */
    unsigned char buf[16];                /*!< The buf working value. */
    int mode;                             /*!< The operation to perform:
                                               #MBEDTLS_GCM_ENCRYPT or
                                               #MBEDTLS_GCM_DECRYPT. */
    ssv_mbedtls_cipher_id_t cipher_id;
}
crypto_gcm_context;

#endif /* INCLUDE_CRYPTO_CRYPTO_GCM_H_ */
