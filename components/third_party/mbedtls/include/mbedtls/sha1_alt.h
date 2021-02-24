/*
 * sha1_alt.h
 *
 *  Created on: Apr 24, 2019
 *      Author: Matt
 */

#ifndef INCLUDE_MBEDTLS_SHA1_ALT_H_
#define INCLUDE_MBEDTLS_SHA1_ALT_H_

#include "crypto_sha1.h"

// Regular implementation
//

/**
 * \brief          The SHA-1 context structure.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
typedef struct crypto_sha1_context mbedtls_sha1_context;
#define ssv_mbedtls_sha1_context mbedtls_sha1_context


#endif /* INCLUDE_MBEDTLS_SHA1_ALT_H_ */
