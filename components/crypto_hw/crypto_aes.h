/*
 * crypto_aes.h
 *
 *  Created on: Apr 25, 2019
 *      Author: Matt
 */

#ifndef INCLUDE_CRYPTO_CRYPTO_AES_H_
#define INCLUDE_CRYPTO_CRYPTO_AES_H_
#include <stdint.h>

/**
 * \brief The AES context-type definition.
 */
typedef struct crypto_aes_context
{
    int nr;             /*!< The number of rounds. */
    uint32_t *rk;       /*!< AES round keys. */
    union {
        uint32_t buf[68];   /*!< Unaligned data buffer. This buffer can
                             hold 32 extra Bytes, which can be used for
                             one of the following purposes:
                             <ul><li>Alignment if VIA padlock is
                                     used.</li>
                             <li>Simplifying key expansion in the 256-bit
                                 case by generating an extra round key.
                                 </li></ul> */
        struct {
            unsigned int keybits;
            unsigned int encryption;
            unsigned char key[32];
            unsigned int useid;
               
        } cop_buf;
	};
}
crypto_aes_context;

#if defined(MBEDTLS_CIPHER_MODE_XTS)
/**
 * \brief The AES XTS context-type definition.
 */
typedef struct crypto_aes_xts_context
{
    crypto_aes_context crypt; /*!< The AES context to use for AES block
                                        encryption or decryption. */
    crypto_aes_context tweak; /*!< The AES context used for tweak
                                        computation. */
} crypto_aes_xts_context;
#endif /* MBEDTLS_CIPHER_MODE_XTS */

int crypto_aes_encrypt( crypto_aes_context *ctx,
                                  const unsigned char input[16],
                                  unsigned char output[16] );
int crypto_aes_decrypt( crypto_aes_context *ctx,
                                  const unsigned char input[16],
                                  unsigned char output[16] );
int mbedtls_aes_setkey_enc_c( crypto_aes_context *ctx, const unsigned char *key,
                    unsigned int keybits );
int mbedtls_aes_setkey_dec_c( crypto_aes_context *ctx, const unsigned char *key,
                    unsigned int keybits );
int mbedtls_internal_aes_decrypt_c( crypto_aes_context *ctx,
                                  const unsigned char input[16],
                                  unsigned char output[16] );
int mbedtls_internal_aes_encrypt_c( crypto_aes_context *ctx,
                                  const unsigned char input[16],
                                  unsigned char output[16] );
int mbedtls_aes_crypt_ecb_c( crypto_aes_context *ctx,
                           int mode,
                           const unsigned char input[16],
                           unsigned char output[16] );
#endif /* INCLUDE_CRYPTO_CRYPTO_AES_H_ */
