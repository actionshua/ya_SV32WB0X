/*
 * aes_alt.h
 *
 *  Created on: Apr 25, 2019
 *      Author: Matt
 */

#ifndef INCLUDE_MBEDTLS_AES_ALT_H_
#define INCLUDE_MBEDTLS_AES_ALT_H_

#include "crypto_aes.h"

// Regular implementation
//

typedef struct crypto_aes_context mbedtls_aes_context;

#if defined(MBEDTLS_CIPHER_MODE_XTS)
typedef struct crypto_aes_xts_context mbedtls_aes_xts_context;
#endif /* MBEDTLS_CIPHER_MODE_XTS */

#define ssv_mbedtls_aes_context mbedtls_aes_context
#define ssv_mbedtls_aes_xts_context mbedtls_aes_xts_context

#endif /* INCLUDE_MBEDTLS_AES_ALT_H_ */
