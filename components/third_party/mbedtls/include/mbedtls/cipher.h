/**
 * \file cipher.h
 *
 * \brief This file contains an abstraction interface for use with the cipher
 * primitives provided by the library. It provides a common interface to all of
 * the available cipher operations.
 *
 * \author Adriaan de Jong <dejong@fox-it.com>
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

#ifndef MBEDTLS_CIPHER_H
#define MBEDTLS_CIPHER_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include "mbedtls/platform_util.h"

#if defined(MBEDTLS_GCM_C) || defined(MBEDTLS_CCM_C) || defined(MBEDTLS_CHACHAPOLY_C)
#define SSV_MBEDTLS_CIPHER_MODE_AEAD
#endif

#if defined(MBEDTLS_CIPHER_MODE_CBC)
#define SSV_MBEDTLS_CIPHER_MODE_WITH_PADDING
#endif

#if defined(MBEDTLS_ARC4_C) || defined(MBEDTLS_CIPHER_NULL_CIPHER) || \
    defined(MBEDTLS_CHACHA20_C)
#define SSV_MBEDTLS_CIPHER_MODE_STREAM
#endif

#if ( defined(__ARMCC_VERSION) || defined(_MSC_VER) ) && \
    !defined(inline) && !defined(__cplusplus)
#define inline __inline
#endif

#define SSV_MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE  -0x6080  /**< The selected feature is not available. */
#define SSV_MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA       -0x6100  /**< Bad input parameters. */
#define SSV_MBEDTLS_ERR_CIPHER_ALLOC_FAILED         -0x6180  /**< Failed to allocate memory. */
#define SSV_MBEDTLS_ERR_CIPHER_INVALID_PADDING      -0x6200  /**< Input data contains invalid padding and is rejected. */
#define SSV_MBEDTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED  -0x6280  /**< Decryption of block requires a full block. */
#define SSV_MBEDTLS_ERR_CIPHER_AUTH_FAILED          -0x6300  /**< Authentication failed (for AEAD modes). */
#define SSV_MBEDTLS_ERR_CIPHER_INVALID_CONTEXT      -0x6380  /**< The context is invalid. For example, because it was freed. */

/* MBEDTLS_ERR_CIPHER_HW_ACCEL_FAILED is deprecated and should not be used. */
#define SSV_MBEDTLS_ERR_CIPHER_HW_ACCEL_FAILED      -0x6400  /**< Cipher hardware accelerator failed. */

#define SSV_MBEDTLS_CIPHER_VARIABLE_IV_LEN     0x01    /**< Cipher accepts IVs of variable length. */
#define SSV_MBEDTLS_CIPHER_VARIABLE_KEY_LEN    0x02    /**< Cipher accepts keys of variable length. */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief     Supported cipher types.
 *
 * \warning   RC4 and DES are considered weak ciphers and their use
 *            constitutes a security risk. Arm recommends considering stronger
 *            ciphers instead.
 */
typedef enum {
    SSV_MBEDTLS_CIPHER_ID_NONE = 0,  /**< Placeholder to mark the end of cipher ID lists. */
    SSV_MBEDTLS_CIPHER_ID_NULL,      /**< The identity cipher, treated as a stream cipher. */
    SSV_MBEDTLS_CIPHER_ID_AES,       /**< The AES cipher. */
    SSV_MBEDTLS_CIPHER_ID_DES,       /**< The DES cipher. */
    SSV_MBEDTLS_CIPHER_ID_3DES,      /**< The Triple DES cipher. */
    SSV_MBEDTLS_CIPHER_ID_CAMELLIA,  /**< The Camellia cipher. */
    SSV_MBEDTLS_CIPHER_ID_BLOWFISH,  /**< The Blowfish cipher. */
    SSV_MBEDTLS_CIPHER_ID_ARC4,      /**< The RC4 cipher. */
    SSV_MBEDTLS_CIPHER_ID_ARIA,      /**< The Aria cipher. */
    SSV_MBEDTLS_CIPHER_ID_CHACHA20,  /**< The ChaCha20 cipher. */
} ssv_mbedtls_cipher_id_t;

/**
 * \brief     Supported {cipher type, cipher mode} pairs.
 *
 * \warning   RC4 and DES are considered weak ciphers and their use
 *            constitutes a security risk. Arm recommends considering stronger
 *            ciphers instead.
 */
typedef enum {
    SSV_MBEDTLS_CIPHER_NONE = 0,             /**< Placeholder to mark the end of cipher-pair lists. */
    SSV_MBEDTLS_CIPHER_NULL,                 /**< The identity stream cipher. */
    SSV_MBEDTLS_CIPHER_AES_128_ECB,          /**< AES cipher with 128-bit ECB mode. */
    SSV_MBEDTLS_CIPHER_AES_192_ECB,          /**< AES cipher with 192-bit ECB mode. */
    SSV_MBEDTLS_CIPHER_AES_256_ECB,          /**< AES cipher with 256-bit ECB mode. */
    SSV_MBEDTLS_CIPHER_AES_128_CBC,          /**< AES cipher with 128-bit CBC mode. */
    SSV_MBEDTLS_CIPHER_AES_192_CBC,          /**< AES cipher with 192-bit CBC mode. */
    SSV_MBEDTLS_CIPHER_AES_256_CBC,          /**< AES cipher with 256-bit CBC mode. */
    SSV_MBEDTLS_CIPHER_AES_128_CFB128,       /**< AES cipher with 128-bit CFB128 mode. */
    SSV_MBEDTLS_CIPHER_AES_192_CFB128,       /**< AES cipher with 192-bit CFB128 mode. */
    SSV_MBEDTLS_CIPHER_AES_256_CFB128,       /**< AES cipher with 256-bit CFB128 mode. */
    SSV_MBEDTLS_CIPHER_AES_128_CTR,          /**< AES cipher with 128-bit CTR mode. */
    SSV_MBEDTLS_CIPHER_AES_192_CTR,          /**< AES cipher with 192-bit CTR mode. */
    SSV_MBEDTLS_CIPHER_AES_256_CTR,          /**< AES cipher with 256-bit CTR mode. */
    SSV_MBEDTLS_CIPHER_AES_128_GCM,          /**< AES cipher with 128-bit GCM mode. */
    SSV_MBEDTLS_CIPHER_AES_192_GCM,          /**< AES cipher with 192-bit GCM mode. */
    SSV_MBEDTLS_CIPHER_AES_256_GCM,          /**< AES cipher with 256-bit GCM mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_128_ECB,     /**< Camellia cipher with 128-bit ECB mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_192_ECB,     /**< Camellia cipher with 192-bit ECB mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_256_ECB,     /**< Camellia cipher with 256-bit ECB mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_128_CBC,     /**< Camellia cipher with 128-bit CBC mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_192_CBC,     /**< Camellia cipher with 192-bit CBC mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_256_CBC,     /**< Camellia cipher with 256-bit CBC mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_128_CFB128,  /**< Camellia cipher with 128-bit CFB128 mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_192_CFB128,  /**< Camellia cipher with 192-bit CFB128 mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_256_CFB128,  /**< Camellia cipher with 256-bit CFB128 mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_128_CTR,     /**< Camellia cipher with 128-bit CTR mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_192_CTR,     /**< Camellia cipher with 192-bit CTR mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_256_CTR,     /**< Camellia cipher with 256-bit CTR mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_128_GCM,     /**< Camellia cipher with 128-bit GCM mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_192_GCM,     /**< Camellia cipher with 192-bit GCM mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_256_GCM,     /**< Camellia cipher with 256-bit GCM mode. */
    SSV_MBEDTLS_CIPHER_DES_ECB,              /**< DES cipher with ECB mode. */
    SSV_MBEDTLS_CIPHER_DES_CBC,              /**< DES cipher with CBC mode. */
    SSV_MBEDTLS_CIPHER_DES_EDE_ECB,          /**< DES cipher with EDE ECB mode. */
    SSV_MBEDTLS_CIPHER_DES_EDE_CBC,          /**< DES cipher with EDE CBC mode. */
    SSV_MBEDTLS_CIPHER_DES_EDE3_ECB,         /**< DES cipher with EDE3 ECB mode. */
    SSV_MBEDTLS_CIPHER_DES_EDE3_CBC,         /**< DES cipher with EDE3 CBC mode. */
    SSV_MBEDTLS_CIPHER_BLOWFISH_ECB,         /**< Blowfish cipher with ECB mode. */
    SSV_MBEDTLS_CIPHER_BLOWFISH_CBC,         /**< Blowfish cipher with CBC mode. */
    SSV_MBEDTLS_CIPHER_BLOWFISH_CFB64,       /**< Blowfish cipher with CFB64 mode. */
    SSV_MBEDTLS_CIPHER_BLOWFISH_CTR,         /**< Blowfish cipher with CTR mode. */
    SSV_MBEDTLS_CIPHER_ARC4_128,             /**< RC4 cipher with 128-bit mode. */
    SSV_MBEDTLS_CIPHER_AES_128_CCM,          /**< AES cipher with 128-bit CCM mode. */
    SSV_MBEDTLS_CIPHER_AES_192_CCM,          /**< AES cipher with 192-bit CCM mode. */
    SSV_MBEDTLS_CIPHER_AES_256_CCM,          /**< AES cipher with 256-bit CCM mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_128_CCM,     /**< Camellia cipher with 128-bit CCM mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_192_CCM,     /**< Camellia cipher with 192-bit CCM mode. */
    SSV_MBEDTLS_CIPHER_CAMELLIA_256_CCM,     /**< Camellia cipher with 256-bit CCM mode. */
    SSV_MBEDTLS_CIPHER_ARIA_128_ECB,         /**< Aria cipher with 128-bit key and ECB mode. */
    SSV_MBEDTLS_CIPHER_ARIA_192_ECB,         /**< Aria cipher with 192-bit key and ECB mode. */
    SSV_MBEDTLS_CIPHER_ARIA_256_ECB,         /**< Aria cipher with 256-bit key and ECB mode. */
    SSV_MBEDTLS_CIPHER_ARIA_128_CBC,         /**< Aria cipher with 128-bit key and CBC mode. */
    SSV_MBEDTLS_CIPHER_ARIA_192_CBC,         /**< Aria cipher with 192-bit key and CBC mode. */
    SSV_MBEDTLS_CIPHER_ARIA_256_CBC,         /**< Aria cipher with 256-bit key and CBC mode. */
    SSV_MBEDTLS_CIPHER_ARIA_128_CFB128,      /**< Aria cipher with 128-bit key and CFB-128 mode. */
    SSV_MBEDTLS_CIPHER_ARIA_192_CFB128,      /**< Aria cipher with 192-bit key and CFB-128 mode. */
    SSV_MBEDTLS_CIPHER_ARIA_256_CFB128,      /**< Aria cipher with 256-bit key and CFB-128 mode. */
    SSV_MBEDTLS_CIPHER_ARIA_128_CTR,         /**< Aria cipher with 128-bit key and CTR mode. */
    SSV_MBEDTLS_CIPHER_ARIA_192_CTR,         /**< Aria cipher with 192-bit key and CTR mode. */
    SSV_MBEDTLS_CIPHER_ARIA_256_CTR,         /**< Aria cipher with 256-bit key and CTR mode. */
    SSV_MBEDTLS_CIPHER_ARIA_128_GCM,         /**< Aria cipher with 128-bit key and GCM mode. */
    SSV_MBEDTLS_CIPHER_ARIA_192_GCM,         /**< Aria cipher with 192-bit key and GCM mode. */
    SSV_MBEDTLS_CIPHER_ARIA_256_GCM,         /**< Aria cipher with 256-bit key and GCM mode. */
    SSV_MBEDTLS_CIPHER_ARIA_128_CCM,         /**< Aria cipher with 128-bit key and CCM mode. */
    SSV_MBEDTLS_CIPHER_ARIA_192_CCM,         /**< Aria cipher with 192-bit key and CCM mode. */
    SSV_MBEDTLS_CIPHER_ARIA_256_CCM,         /**< Aria cipher with 256-bit key and CCM mode. */
    SSV_MBEDTLS_CIPHER_AES_128_OFB,          /**< AES 128-bit cipher in OFB mode. */
    SSV_MBEDTLS_CIPHER_AES_192_OFB,          /**< AES 192-bit cipher in OFB mode. */
    SSV_MBEDTLS_CIPHER_AES_256_OFB,          /**< AES 256-bit cipher in OFB mode. */
    SSV_MBEDTLS_CIPHER_AES_128_XTS,          /**< AES 128-bit cipher in XTS block mode. */
    SSV_MBEDTLS_CIPHER_AES_256_XTS,          /**< AES 256-bit cipher in XTS block mode. */
    SSV_MBEDTLS_CIPHER_CHACHA20,             /**< ChaCha20 stream cipher. */
    SSV_MBEDTLS_CIPHER_CHACHA20_POLY1305,    /**< ChaCha20-Poly1305 AEAD cipher. */
} ssv_mbedtls_cipher_type_t;

/** Supported cipher modes. */
typedef enum {
    SSV_MBEDTLS_MODE_NONE = 0,               /**< None. */
    SSV_MBEDTLS_MODE_ECB,                    /**< The ECB cipher mode. */
    SSV_MBEDTLS_MODE_CBC,                    /**< The CBC cipher mode. */
    SSV_MBEDTLS_MODE_CFB,                    /**< The CFB cipher mode. */
    SSV_MBEDTLS_MODE_OFB,                    /**< The OFB cipher mode. */
    SSV_MBEDTLS_MODE_CTR,                    /**< The CTR cipher mode. */
    SSV_MBEDTLS_MODE_GCM,                    /**< The GCM cipher mode. */
    SSV_MBEDTLS_MODE_STREAM,                 /**< The stream cipher mode. */
    SSV_MBEDTLS_MODE_CCM,                    /**< The CCM cipher mode. */
    SSV_MBEDTLS_MODE_XTS,                    /**< The XTS cipher mode. */
    SSV_MBEDTLS_MODE_CHACHAPOLY,             /**< The ChaCha-Poly cipher mode. */
} ssv_mbedtls_cipher_mode_t;

/** Supported cipher padding types. */
typedef enum {
    SSV_MBEDTLS_PADDING_PKCS7 = 0,     /**< PKCS7 padding (default).        */
    SSV_MBEDTLS_PADDING_ONE_AND_ZEROS, /**< ISO/IEC 7816-4 padding.         */
    SSV_MBEDTLS_PADDING_ZEROS_AND_LEN, /**< ANSI X.923 padding.             */
    SSV_MBEDTLS_PADDING_ZEROS,         /**< Zero padding (not reversible). */
    SSV_MBEDTLS_PADDING_NONE,          /**< Never pad (full blocks only).   */
} ssv_mbedtls_cipher_padding_t;

/** Type of operation. */
typedef enum {
    SSV_MBEDTLS_OPERATION_NONE = -1,
    SSV_MBEDTLS_DECRYPT = 0,
    SSV_MBEDTLS_ENCRYPT,
} ssv_mbedtls_operation_t;

enum {
    /** Undefined key length. */
    SSV_MBEDTLS_KEY_LENGTH_NONE = 0,
    /** Key length, in bits (including parity), for DES keys. */
    SSV_MBEDTLS_KEY_LENGTH_DES  = 64,
    /** Key length in bits, including parity, for DES in two-key EDE. */
    SSV_MBEDTLS_KEY_LENGTH_DES_EDE = 128,
    /** Key length in bits, including parity, for DES in three-key EDE. */
    SSV_MBEDTLS_KEY_LENGTH_DES_EDE3 = 192,
};

/** Maximum length of any IV, in Bytes. */
#define SSV_MBEDTLS_MAX_IV_LENGTH      16
/** Maximum block size of any cipher, in Bytes. */
#define SSV_MBEDTLS_MAX_BLOCK_LENGTH   16

/**
 * Base cipher information (opaque struct).
 */
typedef struct ssv_mbedtls_cipher_base_t ssv_mbedtls_cipher_base_t;

/**
 * CMAC context (opaque struct).
 */
typedef struct ssv_mbedtls_cmac_context_t ssv_mbedtls_cmac_context_t;

/**
 * Cipher information. Allows calling cipher functions
 * in a generic way.
 */
typedef struct ssv_mbedtls_cipher_info_t
{
    /** Full cipher identifier. For example,
     * MBEDTLS_CIPHER_AES_256_CBC.
     */
    ssv_mbedtls_cipher_type_t type;

    /** The cipher mode. For example, MBEDTLS_MODE_CBC. */
    ssv_mbedtls_cipher_mode_t mode;

    /** The cipher key length, in bits. This is the
     * default length for variable sized ciphers.
     * Includes parity bits for ciphers like DES.
     */
    unsigned int key_bitlen;

    /** Name of the cipher. */
    const char * name;

    /** IV or nonce size, in Bytes.
     * For ciphers that accept variable IV sizes,
     * this is the recommended size.
     */
    unsigned int iv_size;

    /** Bitflag comprised of MBEDTLS_CIPHER_VARIABLE_IV_LEN and
     *  MBEDTLS_CIPHER_VARIABLE_KEY_LEN indicating whether the
     *  cipher supports variable IV or variable key sizes, respectively.
     */
    int flags;

    /** The block size, in Bytes. */
    unsigned int block_size;

    /** Struct for base cipher information and functions. */
    const ssv_mbedtls_cipher_base_t *base;

} ssv_mbedtls_cipher_info_t;

/**
 * Generic cipher context.
 */
typedef struct ssv_mbedtls_cipher_context_t
{
    /** Information about the associated cipher. */
    const ssv_mbedtls_cipher_info_t *cipher_info;

    /** Key length to use. */
    int key_bitlen;

    /** Operation that the key of the context has been
     * initialized for.
     */
    ssv_mbedtls_operation_t operation;

#if defined(SSV_MBEDTLS_CIPHER_MODE_WITH_PADDING)
    /** Padding functions to use, if relevant for
     * the specific cipher mode.
     */
    void (*add_padding)( unsigned char *output, size_t olen, size_t data_len );
    int (*get_padding)( unsigned char *input, size_t ilen, size_t *data_len );
#endif

    /** Buffer for input that has not been processed yet. */
    unsigned char unprocessed_data[SSV_MBEDTLS_MAX_BLOCK_LENGTH];

    /** Number of Bytes that have not been processed yet. */
    size_t unprocessed_len;

    /** Current IV or NONCE_COUNTER for CTR-mode, data unit (or sector) number
     * for XTS-mode. */
    unsigned char iv[SSV_MBEDTLS_MAX_IV_LENGTH];

    /** IV size in Bytes, for ciphers with variable-length IVs. */
    size_t iv_size;

    /** The cipher-specific context. */
    void *cipher_ctx;

#if defined(MBEDTLS_CMAC_C)
    /** CMAC-specific context. */
    ssv_mbedtls_cmac_context_t *cmac_ctx;
#endif
} ssv_mbedtls_cipher_context_t;

#if defined(ROM_MODE) || defined(BUILD_ROM)
#include "soc_types.h"

typedef struct _rom_mbed_protocol_st {
    void * (*memset)    (void *str, int c, size_t n);
    void * (*memcpy)    (void *str, const void *src, size_t n);
    size_t (*strlen) (const char *str);
    int (*printf)    (const char* format, ...);
    void *(*calloc)(u32 count, u32 size);
    void (*free)( void *mem );
    const mbedtls_cipher_info_t * (*mbedtls_cipher_info_from_values)( const mbedtls_cipher_id_t cipher_id, int key_bitlen, const mbedtls_cipher_mode_t mode );
    void (*mbedtls_cipher_free)( mbedtls_cipher_context_t *ctx );
    int (*mbedtls_cipher_setup)( mbedtls_cipher_context_t *ctx, const mbedtls_cipher_info_t *cipher_info );
    int (*mbedtls_cipher_setkey)( mbedtls_cipher_context_t *ctx, const unsigned char *key, int key_bitlen, const mbedtls_operation_t operation );                                                                  
    int (*mbedtls_cipher_update)( mbedtls_cipher_context_t *ctx, const unsigned char *input, size_t ilen, unsigned char *output, size_t *olen );
} rom_mbed_protocol_st;

extern rom_mbed_protocol_st *g_rom_mbed_protocol;
#endif

/**
 * \brief This function retrieves the list of ciphers supported by the generic
 * cipher module.
 *
 * \return      A statically-allocated array of ciphers. The last entry
 *              is zero.
 */
const int *ssv_mbedtls_cipher_list( void );

/**
 * \brief               This function retrieves the cipher-information
 *                      structure associated with the given cipher name.
 *
 * \param cipher_name   Name of the cipher to search for. This must not be
 *                      \c NULL.
 *
 * \return              The cipher information structure associated with the
 *                      given \p cipher_name.
 * \return              \c NULL if the associated cipher information is not found.
 */
const ssv_mbedtls_cipher_info_t *ssv_mbedtls_cipher_info_from_string( const char *cipher_name );

/**
 * \brief               This function retrieves the cipher-information
 *                      structure associated with the given cipher type.
 *
 * \param cipher_type   Type of the cipher to search for.
 *
 * \return              The cipher information structure associated with the
 *                      given \p cipher_type.
 * \return              \c NULL if the associated cipher information is not found.
 */
const ssv_mbedtls_cipher_info_t *ssv_mbedtls_cipher_info_from_type( const ssv_mbedtls_cipher_type_t cipher_type );

/**
 * \brief               This function retrieves the cipher-information
 *                      structure associated with the given cipher ID,
 *                      key size and mode.
 *
 * \param cipher_id     The ID of the cipher to search for. For example,
 *                      #MBEDTLS_CIPHER_ID_AES.
 * \param key_bitlen    The length of the key in bits.
 * \param mode          The cipher mode. For example, #MBEDTLS_MODE_CBC.
 *
 * \return              The cipher information structure associated with the
 *                      given \p cipher_id.
 * \return              \c NULL if the associated cipher information is not found.
 */
const ssv_mbedtls_cipher_info_t *ssv_mbedtls_cipher_info_from_values( const ssv_mbedtls_cipher_id_t cipher_id,
                                              int key_bitlen,
                                              const ssv_mbedtls_cipher_mode_t mode );

/**
 * \brief               This function initializes a \p cipher_context as NONE.
 *
 * \param ctx           The context to be initialized. This must not be \c NULL.
 */
void ssv_mbedtls_cipher_init( ssv_mbedtls_cipher_context_t *ctx );

/**
 * \brief               This function frees and clears the cipher-specific
 *                      context of \p ctx. Freeing \p ctx itself remains the
 *                      responsibility of the caller.
 *
 * \param ctx           The context to be freed. If this is \c NULL, the
 *                      function has no effect, otherwise this must point to an
 *                      initialized context.
 */
void ssv_mbedtls_cipher_free( ssv_mbedtls_cipher_context_t *ctx );


/**
 * \brief               This function initializes and fills the cipher-context
 *                      structure with the appropriate values. It also clears
 *                      the structure.
 *
 * \param ctx           The context to initialize. This must be initialized.
 * \param cipher_info   The cipher to use.
 *
 * \return              \c 0 on success.
 * \return              #MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                      parameter-verification failure.
 * \return              #MBEDTLS_ERR_CIPHER_ALLOC_FAILED if allocation of the
 *                      cipher-specific context fails.
 *
 * \internal Currently, the function also clears the structure.
 * In future versions, the caller will be required to call
 * mbedtls_cipher_init() on the structure first.
 */
int ssv_mbedtls_cipher_setup( ssv_mbedtls_cipher_context_t *ctx,
                          const ssv_mbedtls_cipher_info_t *cipher_info );

/**
 * \brief        This function returns the block size of the given cipher.
 *
 * \param ctx    The context of the cipher. This must be initialized.
 *
 * \return       The block size of the underlying cipher.
 * \return       \c 0 if \p ctx has not been initialized.
 */
static inline unsigned int ssv_mbedtls_cipher_get_block_size(
    const ssv_mbedtls_cipher_context_t *ctx )
{
    MBEDTLS_INTERNAL_VALIDATE_RET( ctx != NULL, 0 );
    if( ctx->cipher_info == NULL )
        return 0;

    return ctx->cipher_info->block_size;
}

/**
 * \brief        This function returns the mode of operation for
 *               the cipher. For example, MBEDTLS_MODE_CBC.
 *
 * \param ctx    The context of the cipher. This must be initialized.
 *
 * \return       The mode of operation.
 * \return       #MBEDTLS_MODE_NONE if \p ctx has not been initialized.
 */
static inline ssv_mbedtls_cipher_mode_t ssv_mbedtls_cipher_get_cipher_mode(
    const ssv_mbedtls_cipher_context_t *ctx )
{
    MBEDTLS_INTERNAL_VALIDATE_RET( ctx != NULL, SSV_MBEDTLS_MODE_NONE );
    if( ctx->cipher_info == NULL )
        return SSV_MBEDTLS_MODE_NONE;

    return ctx->cipher_info->mode;
}

/**
 * \brief       This function returns the size of the IV or nonce
 *              of the cipher, in Bytes.
 *
 * \param ctx   The context of the cipher. This must be initialized.
 *
 * \return      The recommended IV size if no IV has been set.
 * \return      \c 0 for ciphers not using an IV or a nonce.
 * \return      The actual size if an IV has been set.
 */
static inline int ssv_mbedtls_cipher_get_iv_size(
    const ssv_mbedtls_cipher_context_t *ctx )
{
    MBEDTLS_INTERNAL_VALIDATE_RET( ctx != NULL, 0 );
    if( ctx->cipher_info == NULL )
        return 0;

    if( ctx->iv_size != 0 )
        return (int) ctx->iv_size;

    return (int) ctx->cipher_info->iv_size;
}

/**
 * \brief               This function returns the type of the given cipher.
 *
 * \param ctx           The context of the cipher. This must be initialized.
 *
 * \return              The type of the cipher.
 * \return              #MBEDTLS_CIPHER_NONE if \p ctx has not been initialized.
 */
static inline ssv_mbedtls_cipher_type_t ssv_mbedtls_cipher_get_type(
    const ssv_mbedtls_cipher_context_t *ctx )
{
    MBEDTLS_INTERNAL_VALIDATE_RET(
        ctx != NULL, SSV_MBEDTLS_CIPHER_NONE );
    if( ctx->cipher_info == NULL )
        return SSV_MBEDTLS_CIPHER_NONE;

    return ctx->cipher_info->type;
}

/**
 * \brief               This function returns the name of the given cipher
 *                      as a string.
 *
 * \param ctx           The context of the cipher. This must be initialized.
 *
 * \return              The name of the cipher.
 * \return              NULL if \p ctx has not been not initialized.
 */
static inline const char *ssv_mbedtls_cipher_get_name(
    const ssv_mbedtls_cipher_context_t *ctx )
{
    MBEDTLS_INTERNAL_VALIDATE_RET( ctx != NULL, 0 );
    if( ctx->cipher_info == NULL )
        return 0;

    return ctx->cipher_info->name;
}

/**
 * \brief               This function returns the key length of the cipher.
 *
 * \param ctx           The context of the cipher. This must be initialized.
 *
 * \return              The key length of the cipher in bits.
 * \return              #MBEDTLS_KEY_LENGTH_NONE if ctx \p has not been
 *                      initialized.
 */
static inline int ssv_mbedtls_cipher_get_key_bitlen(
    const ssv_mbedtls_cipher_context_t *ctx )
{
    MBEDTLS_INTERNAL_VALIDATE_RET(
        ctx != NULL, SSV_MBEDTLS_KEY_LENGTH_NONE );
    if( ctx->cipher_info == NULL )
        return SSV_MBEDTLS_KEY_LENGTH_NONE;

    return (int) ctx->cipher_info->key_bitlen;
}

/**
 * \brief          This function returns the operation of the given cipher.
 *
 * \param ctx      The context of the cipher. This must be initialized.
 *
 * \return         The type of operation: #MBEDTLS_ENCRYPT or #MBEDTLS_DECRYPT.
 * \return         #MBEDTLS_OPERATION_NONE if \p ctx has not been initialized.
 */
static inline ssv_mbedtls_operation_t ssv_mbedtls_cipher_get_operation(
    const ssv_mbedtls_cipher_context_t *ctx )
{
    MBEDTLS_INTERNAL_VALIDATE_RET(
        ctx != NULL, SSV_MBEDTLS_OPERATION_NONE );
    if( ctx->cipher_info == NULL )
        return SSV_MBEDTLS_OPERATION_NONE;

    return ctx->operation;
}

/**
 * \brief               This function sets the key to use with the given context.
 *
 * \param ctx           The generic cipher context. This must be initialized and
 *                      bound to a cipher information structure.
 * \param key           The key to use. This must be a readable buffer of at
 *                      least \p key_bitlen Bits.
 * \param key_bitlen    The key length to use, in Bits.
 * \param operation     The operation that the key will be used for:
 *                      #MBEDTLS_ENCRYPT or #MBEDTLS_DECRYPT.
 *
 * \return              \c 0 on success.
 * \return              #MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                      parameter-verification failure.
 * \return              A cipher-specific error code on failure.
 */
int ssv_mbedtls_cipher_setkey( ssv_mbedtls_cipher_context_t *ctx,
                           const unsigned char *key,
                           int key_bitlen,
                           const ssv_mbedtls_operation_t operation );

#if defined(SSV_MBEDTLS_CIPHER_MODE_WITH_PADDING)
/**
 * \brief               This function sets the padding mode, for cipher modes
 *                      that use padding.
 *
 *                      The default passing mode is PKCS7 padding.
 *
 * \param ctx           The generic cipher context. This must be initialized and
 *                      bound to a cipher information structure.
 * \param mode          The padding mode.
 *
 * \return              \c 0 on success.
 * \return              #MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE
 *                      if the selected padding mode is not supported.
 * \return              #MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA if the cipher mode
 *                      does not support padding.
 */
int ssv_mbedtls_cipher_set_padding_mode( ssv_mbedtls_cipher_context_t *ctx,
                                     ssv_mbedtls_cipher_padding_t mode );
#endif /* MBEDTLS_CIPHER_MODE_WITH_PADDING */

/**
 * \brief           This function sets the initialization vector (IV)
 *                  or nonce.
 *
 * \note            Some ciphers do not use IVs nor nonce. For these
 *                  ciphers, this function has no effect.
 *
 * \param ctx       The generic cipher context. This must be initialized and
 *                  bound to a cipher information structure.
 * \param iv        The IV to use, or NONCE_COUNTER for CTR-mode ciphers. This
 *                  must be a readable buffer of at least \p iv_len Bytes.
 * \param iv_len    The IV length for ciphers with variable-size IV.
 *                  This parameter is discarded by ciphers with fixed-size IV.
 *
 * \return          \c 0 on success.
 * \return          #MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                  parameter-verification failure.
 */
int ssv_mbedtls_cipher_set_iv( ssv_mbedtls_cipher_context_t *ctx,
                           const unsigned char *iv,
                           size_t iv_len );

/**
 * \brief         This function resets the cipher state.
 *
 * \param ctx     The generic cipher context. This must be initialized.
 *
 * \return        \c 0 on success.
 * \return        #MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                parameter-verification failure.
 */
int ssv_mbedtls_cipher_reset( ssv_mbedtls_cipher_context_t *ctx );

#if defined(MBEDTLS_GCM_C) || defined(MBEDTLS_CHACHAPOLY_C)
/**
 * \brief               This function adds additional data for AEAD ciphers.
 *                      Currently supported with GCM and ChaCha20+Poly1305.
 *                      This must be called exactly once, after
 *                      mbedtls_cipher_reset().
 *
 * \param ctx           The generic cipher context. This must be initialized.
 * \param ad            The additional data to use. This must be a readable
 *                      buffer of at least \p ad_len Bytes.
 * \param ad_len        the Length of \p ad Bytes.
 *
 * \return              \c 0 on success.
 * \return              A specific error code on failure.
 */
int ssv_mbedtls_cipher_update_ad( ssv_mbedtls_cipher_context_t *ctx,
                      const unsigned char *ad, size_t ad_len );
#endif /* MBEDTLS_GCM_C || MBEDTLS_CHACHAPOLY_C */

/**
 * \brief               The generic cipher update function. It encrypts or
 *                      decrypts using the given cipher context. Writes as
 *                      many block-sized blocks of data as possible to output.
 *                      Any data that cannot be written immediately is either
 *                      added to the next block, or flushed when
 *                      mbedtls_cipher_finish() is called.
 *                      Exception: For MBEDTLS_MODE_ECB, expects a single block
 *                      in size. For example, 16 Bytes for AES.
 *
 * \note                If the underlying cipher is used in GCM mode, all calls
 *                      to this function, except for the last one before
 *                      mbedtls_cipher_finish(), must have \p ilen as a
 *                      multiple of the block size of the cipher.
 *
 * \param ctx           The generic cipher context. This must be initialized and
 *                      bound to a key.
 * \param input         The buffer holding the input data. This must be a
 *                      readable buffer of at least \p ilen Bytes.
 * \param ilen          The length of the input data.
 * \param output        The buffer for the output data. This must be able to
 *                      hold at least `ilen + block_size`. This must not be the
 *                      same buffer as \p input.
 * \param olen          The length of the output data, to be updated with the
 *                      actual number of Bytes written. This must not be
 *                      \c NULL.
 *
 * \return              \c 0 on success.
 * \return              #MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                      parameter-verification failure.
 * \return              #MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE on an
 *                      unsupported mode for a cipher.
 * \return              A cipher-specific error code on failure.
 */
int ssv_mbedtls_cipher_update( ssv_mbedtls_cipher_context_t *ctx, const unsigned char *input,
                   size_t ilen, unsigned char *output, size_t *olen );

/**
 * \brief               The generic cipher finalization function. If data still
 *                      needs to be flushed from an incomplete block, the data
 *                      contained in it is padded to the size of
 *                      the last block, and written to the \p output buffer.
 *
 * \param ctx           The generic cipher context. This must be initialized and
 *                      bound to a key.
 * \param output        The buffer to write data to. This needs to be a writable
 *                      buffer of at least \p block_size Bytes.
 * \param olen          The length of the data written to the \p output buffer.
 *                      This may not be \c NULL.
 *
 * \return              \c 0 on success.
 * \return              #MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                      parameter-verification failure.
 * \return              #MBEDTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED on decryption
 *                      expecting a full block but not receiving one.
 * \return              #MBEDTLS_ERR_CIPHER_INVALID_PADDING on invalid padding
 *                      while decrypting.
 * \return              A cipher-specific error code on failure.
 */
int ssv_mbedtls_cipher_finish( ssv_mbedtls_cipher_context_t *ctx,
                   unsigned char *output, size_t *olen );

#if defined(MBEDTLS_GCM_C) || defined(MBEDTLS_CHACHAPOLY_C)
/**
 * \brief               This function writes a tag for AEAD ciphers.
 *                      Currently supported with GCM and ChaCha20+Poly1305.
 *                      This must be called after mbedtls_cipher_finish().
 *
 * \param ctx           The generic cipher context. This must be initialized,
 *                      bound to a key, and have just completed a cipher
 *                      operation through mbedtls_cipher_finish() the tag for
 *                      which should be written.
 * \param tag           The buffer to write the tag to. This must be a writable
 *                      buffer of at least \p tag_len Bytes.
 * \param tag_len       The length of the tag to write.
 *
 * \return              \c 0 on success.
 * \return              A specific error code on failure.
 */
int ssv_mbedtls_cipher_write_tag( ssv_mbedtls_cipher_context_t *ctx,
                      unsigned char *tag, size_t tag_len );

/**
 * \brief               This function checks the tag for AEAD ciphers.
 *                      Currently supported with GCM and ChaCha20+Poly1305.
 *                      This must be called after mbedtls_cipher_finish().
 *
 * \param ctx           The generic cipher context. This must be initialized.
 * \param tag           The buffer holding the tag. This must be a readable
 *                      buffer of at least \p tag_len Bytes.
 * \param tag_len       The length of the tag to check.
 *
 * \return              \c 0 on success.
 * \return              A specific error code on failure.
 */
int ssv_mbedtls_cipher_check_tag( ssv_mbedtls_cipher_context_t *ctx,
                      const unsigned char *tag, size_t tag_len );
#endif /* MBEDTLS_GCM_C || MBEDTLS_CHACHAPOLY_C */

/**
 * \brief               The generic all-in-one encryption/decryption function,
 *                      for all ciphers except AEAD constructs.
 *
 * \param ctx           The generic cipher context. This must be initialized.
 * \param iv            The IV to use, or NONCE_COUNTER for CTR-mode ciphers.
 *                      This must be a readable buffer of at least \p iv_len
 *                      Bytes.
 * \param iv_len        The IV length for ciphers with variable-size IV.
 *                      This parameter is discarded by ciphers with fixed-size
 *                      IV.
 * \param input         The buffer holding the input data. This must be a
 *                      readable buffer of at least \p ilen Bytes.
 * \param ilen          The length of the input data in Bytes.
 * \param output        The buffer for the output data. This must be able to
 *                      hold at least `ilen + block_size`. This must not be the
 *                      same buffer as \p input.
 * \param olen          The length of the output data, to be updated with the
 *                      actual number of Bytes written. This must not be
 *                      \c NULL.
 *
 * \note                Some ciphers do not use IVs nor nonce. For these
 *                      ciphers, use \p iv = NULL and \p iv_len = 0.
 *
 * \return              \c 0 on success.
 * \return              #MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                      parameter-verification failure.
 * \return              #MBEDTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED on decryption
 *                      expecting a full block but not receiving one.
 * \return              #MBEDTLS_ERR_CIPHER_INVALID_PADDING on invalid padding
 *                      while decrypting.
 * \return              A cipher-specific error code on failure.
 */
int ssv_mbedtls_cipher_crypt( ssv_mbedtls_cipher_context_t *ctx,
                  const unsigned char *iv, size_t iv_len,
                  const unsigned char *input, size_t ilen,
                  unsigned char *output, size_t *olen );

#if defined(SSV_MBEDTLS_CIPHER_MODE_AEAD)
/**
 * \brief               The generic autenticated encryption (AEAD) function.
 *
 * \param ctx           The generic cipher context. This must be initialized and
 *                      bound to a key.
 * \param iv            The IV to use, or NONCE_COUNTER for CTR-mode ciphers.
 *                      This must be a readable buffer of at least \p iv_len
 *                      Bytes.
 * \param iv_len        The IV length for ciphers with variable-size IV.
 *                      This parameter is discarded by ciphers with fixed-size IV.
 * \param ad            The additional data to authenticate. This must be a
 *                      readable buffer of at least \p ad_len Bytes.
 * \param ad_len        The length of \p ad.
 * \param input         The buffer holding the input data. This must be a
 *                      readable buffer of at least \p ilen Bytes.
 * \param ilen          The length of the input data.
 * \param output        The buffer for the output data. This must be able to
 *                      hold at least \p ilen Bytes.
 * \param olen          The length of the output data, to be updated with the
 *                      actual number of Bytes written. This must not be
 *                      \c NULL.
 * \param tag           The buffer for the authentication tag. This must be a
 *                      writable buffer of at least \p tag_len Bytes.
 * \param tag_len       The desired length of the authentication tag.
 *
 * \return              \c 0 on success.
 * \return              #MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                      parameter-verification failure.
 * \return              A cipher-specific error code on failure.
 */
int ssv_mbedtls_cipher_auth_encrypt( ssv_mbedtls_cipher_context_t *ctx,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *ad, size_t ad_len,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t *olen,
                         unsigned char *tag, size_t tag_len );

/**
 * \brief               The generic autenticated decryption (AEAD) function.
 *
 * \note                If the data is not authentic, then the output buffer
 *                      is zeroed out to prevent the unauthentic plaintext being
 *                      used, making this interface safer.
 *
 * \param ctx           The generic cipher context. This must be initialized and
 *                      and bound to a key.
 * \param iv            The IV to use, or NONCE_COUNTER for CTR-mode ciphers.
 *                      This must be a readable buffer of at least \p iv_len
 *                      Bytes.
 * \param iv_len        The IV length for ciphers with variable-size IV.
 *                      This parameter is discarded by ciphers with fixed-size IV.
 * \param ad            The additional data to be authenticated. This must be a
 *                      readable buffer of at least \p ad_len Bytes.
 * \param ad_len        The length of \p ad.
 * \param input         The buffer holding the input data. This must be a
 *                      readable buffer of at least \p ilen Bytes.
 * \param ilen          The length of the input data.
 * \param output        The buffer for the output data.
 *                      This must be able to hold at least \p ilen Bytes.
 * \param olen          The length of the output data, to be updated with the
 *                      actual number of Bytes written. This must not be
 *                      \c NULL.
 * \param tag           The buffer holding the authentication tag. This must be
 *                      a readable buffer of at least \p tag_len Bytes.
 * \param tag_len       The length of the authentication tag.
 *
 * \return              \c 0 on success.
 * \return              #MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA on
 *                      parameter-verification failure.
 * \return              #MBEDTLS_ERR_CIPHER_AUTH_FAILED if data is not authentic.
 * \return              A cipher-specific error code on failure.
 */
int ssv_mbedtls_cipher_auth_decrypt( ssv_mbedtls_cipher_context_t *ctx,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *ad, size_t ad_len,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t *olen,
                         const unsigned char *tag, size_t tag_len );
#endif /* MBEDTLS_CIPHER_MODE_AEAD */

#ifdef MBEDTLS_EN
#if defined(MBEDTLS_GCM_C) || defined(MBEDTLS_CCM_C) || defined(MBEDTLS_CHACHAPOLY_C)
#define MBEDTLS_CIPHER_MODE_AEAD SSV_MBEDTLS_CIPHER_MODE_AEAD
#endif
#if defined(MBEDTLS_CIPHER_MODE_CBC)
#define MBEDTLS_CIPHER_MODE_WITH_PADDING SSV_MBEDTLS_CIPHER_MODE_WITH_PADDING
#endif
#if defined(MBEDTLS_ARC4_C) || defined(MBEDTLS_CIPHER_NULL_CIPHER) || \
    defined(MBEDTLS_CHACHA20_C)
#define MBEDTLS_CIPHER_MODE_STREAM SSV_MBEDTLS_CIPHER_MODE_STREAM
#endif
#define MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE SSV_MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE
#define MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA SSV_MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA
#define MBEDTLS_ERR_CIPHER_ALLOC_FAILED SSV_MBEDTLS_ERR_CIPHER_ALLOC_FAILED
#define MBEDTLS_ERR_CIPHER_INVALID_PADDING SSV_MBEDTLS_ERR_CIPHER_INVALID_PADDING
#define MBEDTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED SSV_MBEDTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED
#define MBEDTLS_ERR_CIPHER_AUTH_FAILED SSV_MBEDTLS_ERR_CIPHER_AUTH_FAILED
#define MBEDTLS_ERR_CIPHER_INVALID_CONTEXT SSV_MBEDTLS_ERR_CIPHER_INVALID_CONTEXT
#define MBEDTLS_ERR_CIPHER_HW_ACCEL_FAILED SSV_MBEDTLS_ERR_CIPHER_HW_ACCEL_FAILED
#define MBEDTLS_CIPHER_VARIABLE_IV_LEN SSV_MBEDTLS_CIPHER_VARIABLE_IV_LEN
#define MBEDTLS_CIPHER_VARIABLE_KEY_LEN SSV_MBEDTLS_CIPHER_VARIABLE_KEY_LEN
#define MBEDTLS_CIPHER_ID_NONE SSV_MBEDTLS_CIPHER_ID_NONE
#define MBEDTLS_CIPHER_ID_NULL SSV_MBEDTLS_CIPHER_ID_NULL
#define MBEDTLS_CIPHER_ID_AES SSV_MBEDTLS_CIPHER_ID_AES
#define MBEDTLS_CIPHER_ID_DES SSV_MBEDTLS_CIPHER_ID_DES
#define MBEDTLS_CIPHER_ID_3DES SSV_MBEDTLS_CIPHER_ID_3DES
#define MBEDTLS_CIPHER_ID_CAMELLIA SSV_MBEDTLS_CIPHER_ID_CAMELLIA
#define MBEDTLS_CIPHER_ID_BLOWFISH SSV_MBEDTLS_CIPHER_ID_BLOWFISH
#define MBEDTLS_CIPHER_ID_ARC4 SSV_MBEDTLS_CIPHER_ID_ARC4
#define MBEDTLS_CIPHER_ID_ARIA SSV_MBEDTLS_CIPHER_ID_ARIA
#define MBEDTLS_CIPHER_ID_CHACHA20 SSV_MBEDTLS_CIPHER_ID_CHACHA20
#define mbedtls_cipher_id_t ssv_mbedtls_cipher_id_t
#define MBEDTLS_CIPHER_NONE SSV_MBEDTLS_CIPHER_NONE
#define MBEDTLS_CIPHER_NULL SSV_MBEDTLS_CIPHER_NULL
#define MBEDTLS_CIPHER_AES_128_ECB SSV_MBEDTLS_CIPHER_AES_128_ECB
#define MBEDTLS_CIPHER_AES_192_ECB SSV_MBEDTLS_CIPHER_AES_192_ECB
#define MBEDTLS_CIPHER_AES_256_ECB SSV_MBEDTLS_CIPHER_AES_256_ECB
#define MBEDTLS_CIPHER_AES_128_CBC SSV_MBEDTLS_CIPHER_AES_128_CBC
#define MBEDTLS_CIPHER_AES_192_CBC SSV_MBEDTLS_CIPHER_AES_192_CBC
#define MBEDTLS_CIPHER_AES_256_CBC SSV_MBEDTLS_CIPHER_AES_256_CBC
#define MBEDTLS_CIPHER_AES_128_CFB128 SSV_MBEDTLS_CIPHER_AES_128_CFB128
#define MBEDTLS_CIPHER_AES_192_CFB128 SSV_MBEDTLS_CIPHER_AES_192_CFB128
#define MBEDTLS_CIPHER_AES_256_CFB128 SSV_MBEDTLS_CIPHER_AES_256_CFB128
#define MBEDTLS_CIPHER_AES_128_CTR SSV_MBEDTLS_CIPHER_AES_128_CTR
#define MBEDTLS_CIPHER_AES_192_CTR SSV_MBEDTLS_CIPHER_AES_192_CTR
#define MBEDTLS_CIPHER_AES_256_CTR SSV_MBEDTLS_CIPHER_AES_256_CTR
#define MBEDTLS_CIPHER_AES_128_GCM SSV_MBEDTLS_CIPHER_AES_128_GCM
#define MBEDTLS_CIPHER_AES_192_GCM SSV_MBEDTLS_CIPHER_AES_192_GCM
#define MBEDTLS_CIPHER_AES_256_GCM SSV_MBEDTLS_CIPHER_AES_256_GCM
#define MBEDTLS_CIPHER_CAMELLIA_128_ECB SSV_MBEDTLS_CIPHER_CAMELLIA_128_ECB
#define MBEDTLS_CIPHER_CAMELLIA_192_ECB SSV_MBEDTLS_CIPHER_CAMELLIA_192_ECB
#define MBEDTLS_CIPHER_CAMELLIA_256_ECB SSV_MBEDTLS_CIPHER_CAMELLIA_256_ECB
#define MBEDTLS_CIPHER_CAMELLIA_128_CBC SSV_MBEDTLS_CIPHER_CAMELLIA_128_CBC
#define MBEDTLS_CIPHER_CAMELLIA_192_CBC SSV_MBEDTLS_CIPHER_CAMELLIA_192_CBC
#define MBEDTLS_CIPHER_CAMELLIA_256_CBC SSV_MBEDTLS_CIPHER_CAMELLIA_256_CBC
#define MBEDTLS_CIPHER_CAMELLIA_128_CFB128 SSV_MBEDTLS_CIPHER_CAMELLIA_128_CFB128
#define MBEDTLS_CIPHER_CAMELLIA_192_CFB128 SSV_MBEDTLS_CIPHER_CAMELLIA_192_CFB128
#define MBEDTLS_CIPHER_CAMELLIA_256_CFB128 SSV_MBEDTLS_CIPHER_CAMELLIA_256_CFB128
#define MBEDTLS_CIPHER_CAMELLIA_128_CTR SSV_MBEDTLS_CIPHER_CAMELLIA_128_CTR
#define MBEDTLS_CIPHER_CAMELLIA_192_CTR SSV_MBEDTLS_CIPHER_CAMELLIA_192_CTR
#define MBEDTLS_CIPHER_CAMELLIA_256_CTR SSV_MBEDTLS_CIPHER_CAMELLIA_256_CTR
#define MBEDTLS_CIPHER_CAMELLIA_128_GCM SSV_MBEDTLS_CIPHER_CAMELLIA_128_GCM
#define MBEDTLS_CIPHER_CAMELLIA_192_GCM SSV_MBEDTLS_CIPHER_CAMELLIA_192_GCM
#define MBEDTLS_CIPHER_CAMELLIA_256_GCM SSV_MBEDTLS_CIPHER_CAMELLIA_256_GCM
#define MBEDTLS_CIPHER_DES_ECB SSV_MBEDTLS_CIPHER_DES_ECB
#define MBEDTLS_CIPHER_DES_CBC SSV_MBEDTLS_CIPHER_DES_CBC
#define MBEDTLS_CIPHER_DES_EDE_ECB SSV_MBEDTLS_CIPHER_DES_EDE_ECB
#define MBEDTLS_CIPHER_DES_EDE_CBC SSV_MBEDTLS_CIPHER_DES_EDE_CBC
#define MBEDTLS_CIPHER_DES_EDE3_ECB SSV_MBEDTLS_CIPHER_DES_EDE3_ECB
#define MBEDTLS_CIPHER_DES_EDE3_CBC SSV_MBEDTLS_CIPHER_DES_EDE3_CBC
#define MBEDTLS_CIPHER_BLOWFISH_ECB SSV_MBEDTLS_CIPHER_BLOWFISH_ECB
#define MBEDTLS_CIPHER_BLOWFISH_CBC SSV_MBEDTLS_CIPHER_BLOWFISH_CBC
#define MBEDTLS_CIPHER_BLOWFISH_CFB64 SSV_MBEDTLS_CIPHER_BLOWFISH_CFB64
#define MBEDTLS_CIPHER_BLOWFISH_CTR SSV_MBEDTLS_CIPHER_BLOWFISH_CTR
#define MBEDTLS_CIPHER_ARC4_128 SSV_MBEDTLS_CIPHER_ARC4_128
#define MBEDTLS_CIPHER_AES_128_CCM SSV_MBEDTLS_CIPHER_AES_128_CCM
#define MBEDTLS_CIPHER_AES_192_CCM SSV_MBEDTLS_CIPHER_AES_192_CCM
#define MBEDTLS_CIPHER_AES_256_CCM SSV_MBEDTLS_CIPHER_AES_256_CCM
#define MBEDTLS_CIPHER_CAMELLIA_128_CCM SSV_MBEDTLS_CIPHER_CAMELLIA_128_CCM
#define MBEDTLS_CIPHER_CAMELLIA_192_CCM SSV_MBEDTLS_CIPHER_CAMELLIA_192_CCM
#define MBEDTLS_CIPHER_CAMELLIA_256_CCM SSV_MBEDTLS_CIPHER_CAMELLIA_256_CCM
#define MBEDTLS_CIPHER_ARIA_128_ECB SSV_MBEDTLS_CIPHER_ARIA_128_ECB
#define MBEDTLS_CIPHER_ARIA_192_ECB SSV_MBEDTLS_CIPHER_ARIA_192_ECB
#define MBEDTLS_CIPHER_ARIA_256_ECB SSV_MBEDTLS_CIPHER_ARIA_256_ECB
#define MBEDTLS_CIPHER_ARIA_128_CBC SSV_MBEDTLS_CIPHER_ARIA_128_CBC
#define MBEDTLS_CIPHER_ARIA_192_CBC SSV_MBEDTLS_CIPHER_ARIA_192_CBC
#define MBEDTLS_CIPHER_ARIA_256_CBC SSV_MBEDTLS_CIPHER_ARIA_256_CBC
#define MBEDTLS_CIPHER_ARIA_128_CFB128 SSV_MBEDTLS_CIPHER_ARIA_128_CFB128
#define MBEDTLS_CIPHER_ARIA_192_CFB128 SSV_MBEDTLS_CIPHER_ARIA_192_CFB128
#define MBEDTLS_CIPHER_ARIA_256_CFB128 SSV_MBEDTLS_CIPHER_ARIA_256_CFB128
#define MBEDTLS_CIPHER_ARIA_128_CTR SSV_MBEDTLS_CIPHER_ARIA_128_CTR
#define MBEDTLS_CIPHER_ARIA_192_CTR SSV_MBEDTLS_CIPHER_ARIA_192_CTR
#define MBEDTLS_CIPHER_ARIA_256_CTR SSV_MBEDTLS_CIPHER_ARIA_256_CTR
#define MBEDTLS_CIPHER_ARIA_128_GCM SSV_MBEDTLS_CIPHER_ARIA_128_GCM
#define MBEDTLS_CIPHER_ARIA_192_GCM SSV_MBEDTLS_CIPHER_ARIA_192_GCM
#define MBEDTLS_CIPHER_ARIA_256_GCM SSV_MBEDTLS_CIPHER_ARIA_256_GCM
#define MBEDTLS_CIPHER_ARIA_128_CCM SSV_MBEDTLS_CIPHER_ARIA_128_CCM
#define MBEDTLS_CIPHER_ARIA_192_CCM SSV_MBEDTLS_CIPHER_ARIA_192_CCM
#define MBEDTLS_CIPHER_ARIA_256_CCM SSV_MBEDTLS_CIPHER_ARIA_256_CCM
#define MBEDTLS_CIPHER_AES_128_OFB SSV_MBEDTLS_CIPHER_AES_128_OFB
#define MBEDTLS_CIPHER_AES_192_OFB SSV_MBEDTLS_CIPHER_AES_192_OFB
#define MBEDTLS_CIPHER_AES_256_OFB SSV_MBEDTLS_CIPHER_AES_256_OFB
#define MBEDTLS_CIPHER_AES_128_XTS SSV_MBEDTLS_CIPHER_AES_128_XTS
#define MBEDTLS_CIPHER_AES_256_XTS SSV_MBEDTLS_CIPHER_AES_256_XTS
#define MBEDTLS_CIPHER_CHACHA20 SSV_MBEDTLS_CIPHER_CHACHA20
#define MBEDTLS_CIPHER_CHACHA20_POLY1305 SSV_MBEDTLS_CIPHER_CHACHA20_POLY1305
#define mbedtls_cipher_type_t ssv_mbedtls_cipher_type_t
#define MBEDTLS_MODE_NONE SSV_MBEDTLS_MODE_NONE
#define MBEDTLS_MODE_ECB SSV_MBEDTLS_MODE_ECB
#define MBEDTLS_MODE_CBC SSV_MBEDTLS_MODE_CBC
#define MBEDTLS_MODE_CFB SSV_MBEDTLS_MODE_CFB
#define MBEDTLS_MODE_OFB SSV_MBEDTLS_MODE_OFB
#define MBEDTLS_MODE_CTR SSV_MBEDTLS_MODE_CTR
#define MBEDTLS_MODE_GCM SSV_MBEDTLS_MODE_GCM
#define MBEDTLS_MODE_STREAM SSV_MBEDTLS_MODE_STREAM
#define MBEDTLS_MODE_CCM SSV_MBEDTLS_MODE_CCM
#define MBEDTLS_MODE_XTS SSV_MBEDTLS_MODE_XTS
#define MBEDTLS_MODE_CHACHAPOLY SSV_MBEDTLS_MODE_CHACHAPOLY
#define mbedtls_cipher_mode_t ssv_mbedtls_cipher_mode_t
#define MBEDTLS_PADDING_PKCS7 SSV_MBEDTLS_PADDING_PKCS7
#define MBEDTLS_PADDING_ONE_AND_ZEROS SSV_MBEDTLS_PADDING_ONE_AND_ZEROS
#define MBEDTLS_PADDING_ZEROS_AND_LEN SSV_MBEDTLS_PADDING_ZEROS_AND_LEN
#define MBEDTLS_PADDING_ZEROS SSV_MBEDTLS_PADDING_ZEROS
#define MBEDTLS_PADDING_NONE SSV_MBEDTLS_PADDING_NONE
#define mbedtls_cipher_padding_t ssv_mbedtls_cipher_padding_t
#define MBEDTLS_OPERATION_NONE SSV_MBEDTLS_OPERATION_NONE
#define MBEDTLS_DECRYPT SSV_MBEDTLS_DECRYPT
#define MBEDTLS_ENCRYPT SSV_MBEDTLS_ENCRYPT
#define mbedtls_operation_t ssv_mbedtls_operation_t
#define MBEDTLS_KEY_LENGTH_NONE SSV_MBEDTLS_KEY_LENGTH_NONE
#define MBEDTLS_KEY_LENGTH_DES SSV_MBEDTLS_KEY_LENGTH_DES
#define MBEDTLS_KEY_LENGTH_DES_EDE SSV_MBEDTLS_KEY_LENGTH_DES_EDE
#define MBEDTLS_KEY_LENGTH_DES_EDE3 SSV_MBEDTLS_KEY_LENGTH_DES_EDE3
#define MBEDTLS_MAX_IV_LENGTH SSV_MBEDTLS_MAX_IV_LENGTH
#define MBEDTLS_MAX_BLOCK_LENGTH SSV_MBEDTLS_MAX_BLOCK_LENGTH
#define mbedtls_cipher_base_t ssv_mbedtls_cipher_base_t
#define mbedtls_cmac_context_t ssv_mbedtls_cmac_context_t
#define mbedtls_cipher_info_t ssv_mbedtls_cipher_info_t
#define mbedtls_cipher_context_t ssv_mbedtls_cipher_context_t
const int *mbedtls_cipher_list();
const mbedtls_cipher_info_t *mbedtls_cipher_info_from_string( const char *cipher_name);
const mbedtls_cipher_info_t *mbedtls_cipher_info_from_type(const mbedtls_cipher_type_t cipher_type );
const mbedtls_cipher_info_t *mbedtls_cipher_info_from_values(const mbedtls_cipher_id_t cipher_id,
                                              int key_bitlen,
                                              const mbedtls_cipher_mode_t mode);
void mbedtls_cipher_init(mbedtls_cipher_context_t *ctx);
void mbedtls_cipher_free(mbedtls_cipher_context_t *ctx);
int mbedtls_cipher_setup(mbedtls_cipher_context_t *ctx, const mbedtls_cipher_info_t *cipher_info);
int mbedtls_cipher_get_block_size(const mbedtls_cipher_context_t *ctx);
int  mbedtls_cipher_get_cipher_mode(const mbedtls_cipher_context_t *ctx);
int mbedtls_cipher_get_iv_size(const mbedtls_cipher_context_t *ctx);
int mbedtls_cipher_get_type(const mbedtls_cipher_context_t *ctx);
const char *mbedtls_cipher_get_name(const mbedtls_cipher_context_t *ctx);
int mbedtls_cipher_get_key_bitlen(const mbedtls_cipher_context_t *ctx);
mbedtls_operation_t mbedtls_cipher_get_operation(const mbedtls_cipher_context_t *ctx);
int mbedtls_cipher_setkey(mbedtls_cipher_context_t *ctx,
                           const unsigned char *key,
                           int key_bitlen,
                           const mbedtls_operation_t operation);
#if defined(SSV_MBEDTLS_CIPHER_MODE_WITH_PADDING)
int mbedtls_cipher_set_padding_mode(mbedtls_cipher_context_t *ctx,
                                     mbedtls_cipher_padding_t mode);
#endif
int mbedtls_cipher_set_iv(mbedtls_cipher_context_t *ctx,
                           const unsigned char *iv,
                           size_t iv_len);
int mbedtls_cipher_reset(mbedtls_cipher_context_t *ctx);
#if defined(MBEDTLS_GCM_C) || defined(MBEDTLS_CHACHAPOLY_C)
int mbedtls_cipher_update_ad( mbedtls_cipher_context_t *ctx,
                      const unsigned char *ad, size_t ad_len);
#endif
int mbedtls_cipher_update(mbedtls_cipher_context_t *ctx, const unsigned char *input,
                   size_t ilen, unsigned char *output, size_t *olen);
int mbedtls_cipher_finish( mbedtls_cipher_context_t *ctx,
                   unsigned char *output, size_t *olen );
#if defined(MBEDTLS_GCM_C) || defined(MBEDTLS_CHACHAPOLY_C)
int mbedtls_cipher_write_tag(mbedtls_cipher_context_t *ctx,
                      unsigned char *tag, size_t tag_len );
int mbedtls_cipher_check_tag(mbedtls_cipher_context_t *ctx,
                      const unsigned char *tag, size_t tag_len );
#endif
int mbedtls_cipher_crypt(mbedtls_cipher_context_t *ctx,
                  const unsigned char *iv, size_t iv_len,
                  const unsigned char *input, size_t ilen,
                  unsigned char *output, size_t *olen  );
#if defined(SSV_MBEDTLS_CIPHER_MODE_AEAD)
int mbedtls_cipher_auth_encrypt(mbedtls_cipher_context_t *ctx,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *ad, size_t ad_len,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t *olen,
                         unsigned char *tag, size_t tag_len );
int mbedtls_cipher_auth_decrypt(mbedtls_cipher_context_t *ctx,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *ad, size_t ad_len,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t *olen,
                         unsigned char *tag, size_t tag_len );
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_CIPHER_H */
