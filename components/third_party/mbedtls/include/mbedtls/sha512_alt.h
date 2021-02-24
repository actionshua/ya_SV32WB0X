/*
 * sha512_alt.h
 *
 *  Created on: Apr 23, 2019
 *      Author: Matt
 */

#ifndef INCLUDE_MBEDTLS_SHA512_ALT_H_
#define INCLUDE_MBEDTLS_SHA512_ALT_H_

#include "crypto_sha512.h"

#if !defined(MBEDTLS_CONFIG_FILE)
#include "config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

/* MBEDTLS_ERR_SHA512_HW_ACCEL_FAILED is deprecated and should not be used. */
#define MBEDTLS_ERR_SHA512_HW_ACCEL_FAILED                -0x0039  /**< SHA-512 hardware accelerator failed */
#define MBEDTLS_ERR_SHA512_BAD_INPUT_DATA                 -0x0075  /**< SHA-512 input data was malformed. */

#ifdef __cplusplus
extern "C" {
#endif

// Regular implementation
//

/**
 * \brief          The SHA-512 context structure.
 *
 *                 The structure is used both for SHA-384 and for SHA-512
 *                 checksum calculations. The choice between these two is
 *                 made in the call to mbedtls_sha512_starts_ret().
 */
typedef crypto_sha512_context mbedtls_sha512_context;
#ifdef __cplusplus
}
#endif


#endif /* INCLUDE_MBEDTLS_SHA512_ALT_H_ */
