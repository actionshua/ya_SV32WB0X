/*
 *  An implementation of the ARCFOUR algorithm
 *
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
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
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */
/*
 *  The ARCFOUR algorithm was publicly disclosed on 94/09.
 *
 *  http://groups.google.com/group/sci.crypt/msg/10a300c9d21afca0
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/arc4.h"
#include "mbedtls/platform_util.h"

#include <string.h>

#if defined(MBEDTLS_SELF_TEST)
#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#define mbedtls_printf printf
#endif /* MBEDTLS_PLATFORM_C */
#endif /* MBEDTLS_SELF_TEST */

#if !defined(MBEDTLS_ARC4_ALT)

void ssv_mbedtls_arc4_init( ssv_mbedtls_arc4_context *ctx )
{
    memset( ctx, 0, sizeof( ssv_mbedtls_arc4_context ) );
}

void ssv_mbedtls_arc4_free( ssv_mbedtls_arc4_context *ctx )
{
    if( ctx == NULL )
        return;

    ssv_mbedtls_platform_zeroize( ctx, sizeof( ssv_mbedtls_arc4_context ) );
}

/*
 * ARC4 key schedule
 */
void ssv_mbedtls_arc4_setup( ssv_mbedtls_arc4_context *ctx, const unsigned char *key,
                 unsigned int keylen )
{
    int i, j, a;
    unsigned int k;
    unsigned char *m;

    ctx->x = 0;
    ctx->y = 0;
    m = ctx->m;

    for( i = 0; i < 256; i++ )
        m[i] = (unsigned char) i;

    j = k = 0;

    for( i = 0; i < 256; i++, k++ )
    {
        if( k >= keylen ) k = 0;

        a = m[i];
        j = ( j + a + key[k] ) & 0xFF;
        m[i] = m[j];
        m[j] = (unsigned char) a;
    }
}

/*
 * ARC4 cipher function
 */
int ssv_mbedtls_arc4_crypt( ssv_mbedtls_arc4_context *ctx, size_t length, const unsigned char *input,
                unsigned char *output )
{
    int x, y, a, b;
    size_t i;
    unsigned char *m;

    x = ctx->x;
    y = ctx->y;
    m = ctx->m;

    for( i = 0; i < length; i++ )
    {
        x = ( x + 1 ) & 0xFF; a = m[x];
        y = ( y + a ) & 0xFF; b = m[y];

        m[x] = (unsigned char) b;
        m[y] = (unsigned char) a;

        if(input && output) {
            output[i] = (unsigned char)
                ( input[i] ^ m[(unsigned char)( a + b )] );
        }
    }

    ctx->x = x;
    ctx->y = y;

    return( 0 );
}

int ssv_mbedtls_arc4_skip ( const u8 *key, size_t keylen, size_t skip,
                 u8 *data, size_t data_len )
{
    ssv_mbedtls_arc4_context ctx;

    ssv_mbedtls_arc4_init(&ctx);
    ssv_mbedtls_arc4_setup(&ctx, key, keylen);

    ssv_mbedtls_arc4_crypt(&ctx, skip, NULL, NULL);
    ssv_mbedtls_arc4_crypt(&ctx, data_len, data, data);

    ssv_mbedtls_arc4_free(&ctx);

    return 0;
}

#endif /* !MBEDTLS_ARC4_ALT */

#if defined(MBEDTLS_SELF_TEST)
/*
 * ARC4 tests vectors as posted by Eric Rescorla in sep. 1994:
 *
 * http://groups.google.com/group/comp.security.misc/msg/10a300c9d21afca0
 */
static const unsigned char ssv_arc4_test_key[3][8] =
{
    { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF },
    { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

static const unsigned char ssv_arc4_test_pt[3][8] =
{
    { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

static const unsigned char ssv_arc4_test_ct[3][8] =
{
    { 0x75, 0xB7, 0x87, 0x80, 0x99, 0xE0, 0xC5, 0x96 },
    { 0x74, 0x94, 0xC2, 0xE7, 0x10, 0x4B, 0x08, 0x79 },
    { 0xDE, 0x18, 0x89, 0x41, 0xA3, 0x37, 0x5D, 0x3A }
};

/*
 * Checkup routine
 */
int ssv_mbedtls_arc4_self_test( int verbose )
{
    int i, ret = 0;
    unsigned char ibuf[8];
    unsigned char obuf[8];
    ssv_mbedtls_arc4_context ctx;

    ssv_mbedtls_arc4_init( &ctx );

    for( i = 0; i < 3; i++ )
    {
        if( verbose != 0 )
            mbedtls_printf( "  ARC4 test #%d: ", i + 1 );

        memcpy( ibuf, ssv_arc4_test_pt[i], 8 );

        ssv_mbedtls_arc4_setup( &ctx, ssv_arc4_test_key[i], 8 );
        ssv_mbedtls_arc4_crypt( &ctx, 8, ibuf, obuf );

        if( memcmp( obuf, ssv_arc4_test_ct[i], 8 ) != 0 )
        {
            if( verbose != 0 )
                mbedtls_printf( "failed\n" );

            ret = 1;
            goto exit;
        }

        if( verbose != 0 )
            mbedtls_printf( "passed\n" );
    }

    if( verbose != 0 )
        mbedtls_printf( "\n" );

exit:
    ssv_mbedtls_arc4_free( &ctx );

    return( ret );
}

#endif /* MBEDTLS_SELF_TEST */

