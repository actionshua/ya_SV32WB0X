/**
 * \file sha1.h
 *
 * \brief This file contains SHA-1 definitions and functions.
 *
 * The Secure Hash Algorithm 1 (SHA-1) cryptographic hash function is defined in
 * <em>FIPS 180-4: Secure Hash Standard (SHS)</em>.
 *
 * \warning   SHA-1 is considered a weak message digest and its use constitutes
 *            a security risk. We recommend considering stronger message
 *            digests instead.
 */
/*
 *  Copyright (C) 2006-2018, Arm Limited (or its affiliates), All Rights Reserved
 *  SPDX-License-Identifier: GPL-2.0
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  This file is part of Mbed TLS (https://tls.mbed.org)
 */
#ifndef MBEDTLS_SHA1_H
#define MBEDTLS_SHA1_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

/* MBEDTLS_ERR_SHA1_HW_ACCEL_FAILED is deprecated and should not be used. */
#define SSV_MBEDTLS_ERR_SHA1_HW_ACCEL_FAILED                  -0x0035  /**< SHA-1 hardware accelerator failed */
#define SSV_MBEDTLS_ERR_SHA1_BAD_INPUT_DATA                   -0x0073  /**< SHA-1 input data was malformed. */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_SHA1_ALT)
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
typedef struct ssv_mbedtls_sha1_context
{
    uint32_t total[2];          /*!< The number of Bytes processed.  */
    uint32_t state[5];          /*!< The intermediate digest state.  */
    unsigned char buffer[64];   /*!< The data block being processed. */
}
ssv_mbedtls_sha1_context;

#else  /* MBEDTLS_SHA1_ALT */
#include "sha1_alt.h"
#endif /* MBEDTLS_SHA1_ALT */

/**
 * \brief          This function initializes a SHA-1 context.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 * \param ctx      The SHA-1 context to initialize.
 *                 This must not be \c NULL.
 *
 */
void ssv_mbedtls_sha1_init( ssv_mbedtls_sha1_context *ctx );

/**
 * \brief          This function clears a SHA-1 context.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 * \param ctx      The SHA-1 context to clear. This may be \c NULL,
 *                 in which case this function does nothing. If it is
 *                 not \c NULL, it must point to an initialized
 *                 SHA-1 context.
 *
 */
void ssv_mbedtls_sha1_free( ssv_mbedtls_sha1_context *ctx );

/**
 * \brief          This function clones the state of a SHA-1 context.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 * \param dst      The SHA-1 context to clone to. This must be initialized.
 * \param src      The SHA-1 context to clone from. This must be initialized.
 *
 */
void ssv_mbedtls_sha1_clone( ssv_mbedtls_sha1_context *dst,
                         const ssv_mbedtls_sha1_context *src );

/**
 * \brief          This function starts a SHA-1 checksum calculation.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 * \param ctx      The SHA-1 context to initialize. This must be initialized.
 *
 * \return         \c 0 on success.
 * \return         A negative error code on failure.
 *
 */
int ssv_mbedtls_sha1_starts_ret( ssv_mbedtls_sha1_context *ctx );

/**
 * \brief          This function feeds an input buffer into an ongoing SHA-1
 *                 checksum calculation.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 * \param ctx      The SHA-1 context. This must be initialized
 *                 and have a hash operation started.
 * \param input    The buffer holding the input data.
 *                 This must be a readable buffer of length \p ilen Bytes.
 * \param ilen     The length of the input data \p input in Bytes.
 *
 * \return         \c 0 on success.
 * \return         A negative error code on failure.
 */
int ssv_mbedtls_sha1_update_ret( ssv_mbedtls_sha1_context *ctx,
                             const unsigned char *input,
                             size_t ilen );

/**
 * \brief          This function finishes the SHA-1 operation, and writes
 *                 the result to the output buffer.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 * \param ctx      The SHA-1 context to use. This must be initialized and
 *                 have a hash operation started.
 * \param output   The SHA-1 checksum result. This must be a writable
 *                 buffer of length \c 20 Bytes.
 *
 * \return         \c 0 on success.
 * \return         A negative error code on failure.
 */
int ssv_mbedtls_sha1_finish_ret( ssv_mbedtls_sha1_context *ctx,
                             unsigned char output[20] );

/**
 * \brief          SHA-1 process data block (internal use only).
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 * \param ctx      The SHA-1 context to use. This must be initialized.
 * \param data     The data block being processed. This must be a
 *                 readable buffer of length \c 64 Bytes.
 *
 * \return         \c 0 on success.
 * \return         A negative error code on failure.
 *
 */
int ssv_mbedtls_internal_sha1_process( ssv_mbedtls_sha1_context *ctx,
                                   const unsigned char data[64] );

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \brief          This function starts a SHA-1 checksum calculation.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 * \deprecated     Superseded by mbedtls_sha1_starts_ret() in 2.7.0.
 *
 * \param ctx      The SHA-1 context to initialize. This must be initialized.
 *
 */
MBEDTLS_DEPRECATED void ssv_mbedtls_sha1_starts( ssv_mbedtls_sha1_context *ctx );

/**
 * \brief          This function feeds an input buffer into an ongoing SHA-1
 *                 checksum calculation.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 * \deprecated     Superseded by mbedtls_sha1_update_ret() in 2.7.0.
 *
 * \param ctx      The SHA-1 context. This must be initialized and
 *                 have a hash operation started.
 * \param input    The buffer holding the input data.
 *                 This must be a readable buffer of length \p ilen Bytes.
 * \param ilen     The length of the input data \p input in Bytes.
 *
 */
MBEDTLS_DEPRECATED void ssv_mbedtls_sha1_update( ssv_mbedtls_sha1_context *ctx,
                                             const unsigned char *input,
                                             size_t ilen );

/**
 * \brief          This function finishes the SHA-1 operation, and writes
 *                 the result to the output buffer.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 * \deprecated     Superseded by mbedtls_sha1_finish_ret() in 2.7.0.
 *
 * \param ctx      The SHA-1 context. This must be initialized and
 *                 have a hash operation started.
 * \param output   The SHA-1 checksum result.
 *                 This must be a writable buffer of length \c 20 Bytes.
 */
MBEDTLS_DEPRECATED void ssv_mbedtls_sha1_finish( ssv_mbedtls_sha1_context *ctx,
                                             unsigned char output[20] );

/**
 * \brief          SHA-1 process data block (internal use only).
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 * \deprecated     Superseded by mbedtls_internal_sha1_process() in 2.7.0.
 *
 * \param ctx      The SHA-1 context. This must be initialized.
 * \param data     The data block being processed.
 *                 This must be a readable buffer of length \c 64 bytes.
 *
 */
MBEDTLS_DEPRECATED void ssv_mbedtls_sha1_process( ssv_mbedtls_sha1_context *ctx,
                                              const unsigned char data[64] );

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

/**
 * \brief          This function calculates the SHA-1 checksum of a buffer.
 *
 *                 The function allocates the context, performs the
 *                 calculation, and frees the context.
 *
 *                 The SHA-1 result is calculated as
 *                 output = SHA-1(input buffer).
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 * \param input    The buffer holding the input data.
 *                 This must be a readable buffer of length \p ilen Bytes.
 * \param ilen     The length of the input data \p input in Bytes.
 * \param output   The SHA-1 checksum result.
 *                 This must be a writable buffer of length \c 20 Bytes.
 *
 * \return         \c 0 on success.
 * \return         A negative error code on failure.
 *
 */
int ssv_mbedtls_sha1_ret( const unsigned char *input,
                      size_t ilen,
                      unsigned char output[20] );

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \brief          This function calculates the SHA-1 checksum of a buffer.
 *
 *                 The function allocates the context, performs the
 *                 calculation, and frees the context.
 *
 *                 The SHA-1 result is calculated as
 *                 output = SHA-1(input buffer).
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 * \deprecated     Superseded by mbedtls_sha1_ret() in 2.7.0
 *
 * \param input    The buffer holding the input data.
 *                 This must be a readable buffer of length \p ilen Bytes.
 * \param ilen     The length of the input data \p input in Bytes.
 * \param output   The SHA-1 checksum result. This must be a writable
 *                 buffer of size \c 20 Bytes.
 *
 */
MBEDTLS_DEPRECATED void ssv_mbedtls_sha1( const unsigned char *input,
                                      size_t ilen,
                                      unsigned char output[20] );

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

/**
 * \brief          The SHA-1 checkup routine.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 * \return         \c 0 on success.
 * \return         \c 1 on failure.
 *
 */
int ssv_mbedtls_sha1_self_test( int verbose );

#ifdef MBEDTLS_EN
#define MBEDTLS_ERR_SHA1_HW_ACCEL_FAILED SSV_MBEDTLS_ERR_SHA1_HW_ACCEL_FAILED
#define MBEDTLS_ERR_SHA1_BAD_INPUT_DATA SSV_MBEDTLS_ERR_SHA1_BAD_INPUT_DATA
#if !defined(MBEDTLS_SHA1_ALT)
#define mbedtls_sha1_context ssv_mbedtls_sha1_context
#endif
void mbedtls_sha1_init(mbedtls_sha1_context* ctx);
void mbedtls_sha1_free(mbedtls_sha1_context* ctx);
void mbedtls_sha1_clone(mbedtls_sha1_context *dst,
                         const mbedtls_sha1_context *src );
int mbedtls_sha1_starts_ret(mbedtls_sha1_context* ctx);
int mbedtls_sha1_update_ret(mbedtls_sha1_context *ctx,
                             const unsigned char *input,
                             size_t ilen);
int mbedtls_sha1_finish_ret(mbedtls_sha1_context *ctx,
                             unsigned char output[20] );
int mbedtls_internal_sha1_process(mbedtls_sha1_context *ctx,
                             const unsigned char data[64] );
#if !defined(MBEDTLS_DEPRECATED_REMOVED)
void mbedtls_sha1_starts(mbedtls_sha1_context *ctx);
void mbedtls_sha1_update(mbedtls_sha1_context *ctx,
                          const unsigned char *input,
                          size_t ilen );
void mbedtls_sha1_finish(mbedtls_sha1_context *ctx,
                          unsigned char output[20]);
void mbedtls_sha1_process(mbedtls_sha1_context *ctx,
                           const unsigned char data[64] );
#endif
int mbedtls_sha1_ret(const unsigned char *input,
                      size_t ilen,
                      unsigned char output[20]);
#if !defined(MBEDTLS_DEPRECATED_REMOVED)
void mbedtls_sha1(const unsigned char *input,
                   size_t ilen,
                   unsigned char output[20] );
#endif
int mbedtls_sha1_self_test(int verbose );
#endif

#ifdef __cplusplus
}
#endif

#endif /* mbedtls_sha1.h */
