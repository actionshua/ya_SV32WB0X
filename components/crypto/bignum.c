/*
 *  Multi-precision integer library
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
 *  The following sources were referenced in the design of this Multi-precision
 *  Integer library:
 *
 *  [1] Handbook of Applied Cryptography - 1997
 *      Menezes, van Oorschot and Vanstone
 *
 *  [2] Multi-Precision Math
 *      Tom St Denis
 *      https://github.com/libtom/libtommath/blob/develop/tommath.pdf
 *
 *  [3] GNU Multi-Precision Arithmetic Library
 *      https://gmplib.org/manual/index.html
 *
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/bignum.h"
#include "mbedtls/bn_mul.h"
#include "mbedtls/platform_util.h"

#include <string.h>

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#include <stdlib.h>
#define mbedtls_printf     printf
#define mbedtls_calloc    calloc
#define mbedtls_free       free
#endif

#define MPI_VALIDATE_RET( cond )                                       \
    MBEDTLS_INTERNAL_VALIDATE_RET( cond, SSV_MBEDTLS_ERR_MPI_BAD_INPUT_DATA )
#define MPI_VALIDATE( cond )                                           \
    MBEDTLS_INTERNAL_VALIDATE( cond )

#define ciL    (sizeof(ssv_mbedtls_mpi_uint))         /* chars in limb  */
#define biL    (ciL << 3)               /* bits  in limb  */
#define biH    (ciL << 2)               /* half limb size */

#define MPI_SIZE_T_MAX  ( (size_t) -1 ) /* SIZE_T_MAX is not standard */

/*
 * Convert between bits/chars and number of limbs
 * Divide first in order to avoid potential overflows
 */
#define BITS_TO_LIMBS(i)  ( (i) / biL + ( (i) % biL != 0 ) )
#define CHARS_TO_LIMBS(i) ( (i) / ciL + ( (i) % ciL != 0 ) )

/* Implementation that should never be optimized out by the compiler */
static void ssv_mbedtls_mpi_zeroize( ssv_mbedtls_mpi_uint *v, size_t n )
{
    ssv_mbedtls_platform_zeroize( v, ciL * n );
}

/*
 * Initialize one MPI
 */
void ssv_mbedtls_mpi_init( ssv_mbedtls_mpi *X )
{
    MPI_VALIDATE( X != NULL );

    X->s = 1;
    X->n = 0;
    X->p = NULL;
}

/*
 * Unallocate one MPI
 */
void ssv_mbedtls_mpi_free( ssv_mbedtls_mpi *X )
{
    if( X == NULL )
        return;

    if( X->p != NULL )
    {
        ssv_mbedtls_mpi_zeroize( X->p, X->n );
        mbedtls_free( X->p );
    }

    X->s = 1;
    X->n = 0;
    X->p = NULL;
}

/*
 * Enlarge to the specified number of limbs
 */
int ssv_mbedtls_mpi_grow( ssv_mbedtls_mpi *X, size_t nblimbs )
{
    ssv_mbedtls_mpi_uint *p;
    MPI_VALIDATE_RET( X != NULL );

    if( nblimbs > SSV_MBEDTLS_MPI_MAX_LIMBS )
        return( SSV_MBEDTLS_ERR_MPI_ALLOC_FAILED );

    if( X->n < nblimbs )
    {
        if( ( p = (ssv_mbedtls_mpi_uint*)mbedtls_calloc( nblimbs, ciL ) ) == NULL )
            return( SSV_MBEDTLS_ERR_MPI_ALLOC_FAILED );

        if( X->p != NULL )
        {
            memcpy( p, X->p, X->n * ciL );
            ssv_mbedtls_mpi_zeroize( X->p, X->n );
            mbedtls_free( X->p );
        }

        X->n = nblimbs;
        X->p = p;
    }

    return( 0 );
}

/*
 * Resize down as much as possible,
 * while keeping at least the specified number of limbs
 */
int ssv_mbedtls_mpi_shrink( ssv_mbedtls_mpi *X, size_t nblimbs )
{
    ssv_mbedtls_mpi_uint *p;
    size_t i;
    MPI_VALIDATE_RET( X != NULL );

    if( nblimbs > SSV_MBEDTLS_MPI_MAX_LIMBS )
        return( SSV_MBEDTLS_ERR_MPI_ALLOC_FAILED );

    /* Actually resize up in this case */
    if( X->n <= nblimbs )
        return( ssv_mbedtls_mpi_grow( X, nblimbs ) );

    for( i = X->n - 1; i > 0; i-- )
        if( X->p[i] != 0 )
            break;
    i++;

    if( i < nblimbs )
        i = nblimbs;

    if( ( p = (ssv_mbedtls_mpi_uint*)mbedtls_calloc( i, ciL ) ) == NULL )
        return( SSV_MBEDTLS_ERR_MPI_ALLOC_FAILED );

    if( X->p != NULL )
    {
        memcpy( p, X->p, i * ciL );
        ssv_mbedtls_mpi_zeroize( X->p, X->n );
        mbedtls_free( X->p );
    }

    X->n = i;
    X->p = p;

    return( 0 );
}

/*
 * Copy the contents of Y into X
 */
int ssv_mbedtls_mpi_copy( ssv_mbedtls_mpi *X, const ssv_mbedtls_mpi *Y )
{
    int ret = 0;
    size_t i;
    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( Y != NULL );

    if( X == Y )
        return( 0 );

    if( Y->p == NULL )
    {
        ssv_mbedtls_mpi_free( X );
        return( 0 );
    }

    for( i = Y->n - 1; i > 0; i-- )
        if( Y->p[i] != 0 )
            break;
    i++;

    X->s = Y->s;

    if( X->n < i )
    {
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( X, i ) );
    }
    else
    {
        memset( X->p + i, 0, ( X->n - i ) * ciL );
    }

    memcpy( X->p, Y->p, i * ciL );

cleanup:

    return( ret );
}

/*
 * Swap the contents of X and Y
 */
void ssv_mbedtls_mpi_swap( ssv_mbedtls_mpi *X, ssv_mbedtls_mpi *Y )
{
    ssv_mbedtls_mpi T;
    MPI_VALIDATE( X != NULL );
    MPI_VALIDATE( Y != NULL );

    memcpy( &T,  X, sizeof( ssv_mbedtls_mpi ) );
    memcpy(  X,  Y, sizeof( ssv_mbedtls_mpi ) );
    memcpy(  Y, &T, sizeof( ssv_mbedtls_mpi ) );
}

/*
 * Conditionally assign X = Y, without leaking information
 * about whether the assignment was made or not.
 * (Leaking information about the respective sizes of X and Y is ok however.)
 */
int ssv_mbedtls_mpi_safe_cond_assign( ssv_mbedtls_mpi *X, const ssv_mbedtls_mpi *Y, unsigned char assign )
{
    int ret = 0;
    size_t i;
    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( Y != NULL );

    /* make sure assign is 0 or 1 in a time-constant manner */
    assign = (assign | (unsigned char)-assign) >> 7;

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( X, Y->n ) );

    X->s = X->s * ( 1 - assign ) + Y->s * assign;

    for( i = 0; i < Y->n; i++ )
        X->p[i] = X->p[i] * ( 1 - assign ) + Y->p[i] * assign;

    for( ; i < X->n; i++ )
        X->p[i] *= ( 1 - assign );

cleanup:
    return( ret );
}

/*
 * Conditionally swap X and Y, without leaking information
 * about whether the swap was made or not.
 * Here it is not ok to simply swap the pointers, which whould lead to
 * different memory access patterns when X and Y are used afterwards.
 */
int ssv_mbedtls_mpi_safe_cond_swap( ssv_mbedtls_mpi *X, ssv_mbedtls_mpi *Y, unsigned char swap )
{
    int ret, s;
    size_t i;
    ssv_mbedtls_mpi_uint tmp;
    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( Y != NULL );

    if( X == Y )
        return( 0 );

    /* make sure swap is 0 or 1 in a time-constant manner */
    swap = (swap | (unsigned char)-swap) >> 7;

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( X, Y->n ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( Y, X->n ) );

    s = X->s;
    X->s = X->s * ( 1 - swap ) + Y->s * swap;
    Y->s = Y->s * ( 1 - swap ) +    s * swap;


    for( i = 0; i < X->n; i++ )
    {
        tmp = X->p[i];
        X->p[i] = X->p[i] * ( 1 - swap ) + Y->p[i] * swap;
        Y->p[i] = Y->p[i] * ( 1 - swap ) +     tmp * swap;
    }

cleanup:
    return( ret );
}

/*
 * Set value from integer
 */
int ssv_mbedtls_mpi_lset( ssv_mbedtls_mpi *X, ssv_mbedtls_mpi_sint z )
{
    int ret;
    MPI_VALIDATE_RET( X != NULL );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( X, 1 ) );
    memset( X->p, 0, X->n * ciL );

    X->p[0] = ( z < 0 ) ? -z : z;
    X->s    = ( z < 0 ) ? -1 : 1;

cleanup:

    return( ret );
}

/*
 * Get a specific bit
 */
int ssv_mbedtls_mpi_get_bit( const ssv_mbedtls_mpi *X, size_t pos )
{
    MPI_VALIDATE_RET( X != NULL );

    if( X->n * biL <= pos )
        return( 0 );

    return( ( X->p[pos / biL] >> ( pos % biL ) ) & 0x01 );
}

/* Get a specific byte, without range checks. */
#define GET_BYTE( X, i )                                \
    ( ( ( X )->p[( i ) / ciL] >> ( ( ( i ) % ciL ) * 8 ) ) & 0xff )

/*
 * Set a bit to a specific value of 0 or 1
 */
int ssv_mbedtls_mpi_set_bit( ssv_mbedtls_mpi *X, size_t pos, unsigned char val )
{
    int ret = 0;
    size_t off = pos / biL;
    size_t idx = pos % biL;
    MPI_VALIDATE_RET( X != NULL );

    if( val != 0 && val != 1 )
        return( SSV_MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    if( X->n * biL <= pos )
    {
        if( val == 0 )
            return( 0 );

        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( X, off + 1 ) );
    }

    X->p[off] &= ~( (ssv_mbedtls_mpi_uint) 0x01 << idx );
    X->p[off] |= (ssv_mbedtls_mpi_uint) val << idx;

cleanup:

    return( ret );
}

/*
 * Return the number of less significant zero-bits
 */
size_t ssv_mbedtls_mpi_lsb( const ssv_mbedtls_mpi *X )
{
    size_t i, j, count = 0;
    MBEDTLS_INTERNAL_VALIDATE_RET( X != NULL, 0 );

    for( i = 0; i < X->n; i++ )
        for( j = 0; j < biL; j++, count++ )
            if( ( ( X->p[i] >> j ) & 1 ) != 0 )
                return( count );

    return( 0 );
}

/*
 * Count leading zero bits in a given integer
 */
static size_t ssv_mbedtls_clz( const ssv_mbedtls_mpi_uint x )
{
    size_t j;
    ssv_mbedtls_mpi_uint mask = (ssv_mbedtls_mpi_uint) 1 << (biL - 1);

    for( j = 0; j < biL; j++ )
    {
        if( x & mask ) break;

        mask >>= 1;
    }

    return j;
}

/*
 * Return the number of bits
 */
size_t ssv_mbedtls_mpi_bitlen( const ssv_mbedtls_mpi *X )
{
    size_t i, j;

    if( X->n == 0 )
        return( 0 );

    for( i = X->n - 1; i > 0; i-- )
        if( X->p[i] != 0 )
            break;

    j = biL - ssv_mbedtls_clz( X->p[i] );

    return( ( i * biL ) + j );
}

/*
 * Return the total size in bytes
 */
size_t ssv_mbedtls_mpi_size( const ssv_mbedtls_mpi *X )
{
    return( ( ssv_mbedtls_mpi_bitlen( X ) + 7 ) >> 3 );
}

/*
 * Convert an ASCII character to digit value
 */
static int mpi_get_digit( ssv_mbedtls_mpi_uint *d, int radix, char c )
{
    *d = 255;

    if( c >= 0x30 && c <= 0x39 ) *d = c - 0x30;
    if( c >= 0x41 && c <= 0x46 ) *d = c - 0x37;
    if( c >= 0x61 && c <= 0x66 ) *d = c - 0x57;

    if( *d >= (ssv_mbedtls_mpi_uint) radix )
        return( SSV_MBEDTLS_ERR_MPI_INVALID_CHARACTER );

    return( 0 );
}

/*
 * Import from an ASCII string
 */
int ssv_mbedtls_mpi_read_string( ssv_mbedtls_mpi *X, int radix, const char *s )
{
    int ret;
    size_t i, j, slen, n;
    ssv_mbedtls_mpi_uint d;
    ssv_mbedtls_mpi T;
    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( s != NULL );

    if( radix < 2 || radix > 16 )
        return( SSV_MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    ssv_mbedtls_mpi_init( &T );

    slen = strlen( s );

    if( radix == 16 )
    {
        if( slen > MPI_SIZE_T_MAX >> 2 )
            return( SSV_MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

        n = BITS_TO_LIMBS( slen << 2 );

        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( X, n ) );
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_lset( X, 0 ) );

        for( i = slen, j = 0; i > 0; i--, j++ )
        {
            if( i == 1 && s[i - 1] == '-' )
            {
                X->s = -1;
                break;
            }

            SSV_MBEDTLS_MPI_CHK( mpi_get_digit( &d, radix, s[i - 1] ) );
            X->p[j / ( 2 * ciL )] |= d << ( ( j % ( 2 * ciL ) ) << 2 );
        }
    }
    else
    {
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_lset( X, 0 ) );

        for( i = 0; i < slen; i++ )
        {
            if( i == 0 && s[i] == '-' )
            {
                X->s = -1;
                continue;
            }

            SSV_MBEDTLS_MPI_CHK( mpi_get_digit( &d, radix, s[i] ) );
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_mul_int( &T, X, radix ) );

            if( X->s == 1 )
            {
                SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_add_int( X, &T, d ) );
            }
            else
            {
                SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_int( X, &T, d ) );
            }
        }
    }

cleanup:

    ssv_mbedtls_mpi_free( &T );

    return( ret );
}

/*
 * Helper to write the digits high-order first
 */
static int mpi_write_hlp( ssv_mbedtls_mpi *X, int radix, char **p )
{
    int ret;
    ssv_mbedtls_mpi_uint r;

    if( radix < 2 || radix > 16 )
        return( SSV_MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_mod_int( &r, X, radix ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_div_int( X, NULL, X, radix ) );

    if( ssv_mbedtls_mpi_cmp_int( X, 0 ) != 0 )
        SSV_MBEDTLS_MPI_CHK( mpi_write_hlp( X, radix, p ) );

    if( r < 10 )
        *(*p)++ = (char)( r + 0x30 );
    else
        *(*p)++ = (char)( r + 0x37 );

cleanup:

    return( ret );
}

/*
 * Export into an ASCII string
 */
int ssv_mbedtls_mpi_write_string( const ssv_mbedtls_mpi *X, int radix,
                              char *buf, size_t buflen, size_t *olen )
{
    int ret = 0;
    size_t n;
    char *p;
    ssv_mbedtls_mpi T;
    MPI_VALIDATE_RET( X    != NULL );
    MPI_VALIDATE_RET( olen != NULL );
    MPI_VALIDATE_RET( buflen == 0 || buf != NULL );

    if( radix < 2 || radix > 16 )
        return( SSV_MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    n = ssv_mbedtls_mpi_bitlen( X );
    if( radix >=  4 ) n >>= 1;
    if( radix >= 16 ) n >>= 1;
    /*
     * Round up the buffer length to an even value to ensure that there is
     * enough room for hexadecimal values that can be represented in an odd
     * number of digits.
     */
    n += 3 + ( ( n + 1 ) & 1 );

    if( buflen < n )
    {
        *olen = n;
        return( SSV_MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL );
    }

    p = buf;
    ssv_mbedtls_mpi_init( &T );

    if( X->s == -1 )
        *p++ = '-';

    if( radix == 16 )
    {
        int c;
        size_t i, j, k;

        for( i = X->n, k = 0; i > 0; i-- )
        {
            for( j = ciL; j > 0; j-- )
            {
                c = ( X->p[i - 1] >> ( ( j - 1 ) << 3) ) & 0xFF;

                if( c == 0 && k == 0 && ( i + j ) != 2 )
                    continue;

                *(p++) = "0123456789ABCDEF" [c / 16];
                *(p++) = "0123456789ABCDEF" [c % 16];
                k = 1;
            }
        }
    }
    else
    {
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &T, X ) );

        if( T.s == -1 )
            T.s = 1;

        SSV_MBEDTLS_MPI_CHK( mpi_write_hlp( &T, radix, &p ) );
    }

    *p++ = '\0';
    *olen = p - buf;

cleanup:

    ssv_mbedtls_mpi_free( &T );

    return( ret );
}

#if defined(MBEDTLS_FS_IO)
/*
 * Read X from an opened file
 */
int ssv_mbedtls_mpi_read_file( ssv_mbedtls_mpi *X, int radix, FILE *fin )
{
    ssv_mbedtls_mpi_uint d;
    size_t slen;
    char *p;
    /*
     * Buffer should have space for (short) label and decimal formatted MPI,
     * newline characters and '\0'
     */
    char s[ SSV_MBEDTLS_MPI_RW_BUFFER_SIZE ];

    MPI_VALIDATE_RET( X   != NULL );
    MPI_VALIDATE_RET( fin != NULL );

    if( radix < 2 || radix > 16 )
        return( SSV_MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    memset( s, 0, sizeof( s ) );
    if( fgets( s, sizeof( s ) - 1, fin ) == NULL )
        return( SSV_MBEDTLS_ERR_MPI_FILE_IO_ERROR );

    slen = strlen( s );
    if( slen == sizeof( s ) - 2 )
        return( SSV_MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL );

    if( slen > 0 && s[slen - 1] == '\n' ) { slen--; s[slen] = '\0'; }
    if( slen > 0 && s[slen - 1] == '\r' ) { slen--; s[slen] = '\0'; }

    p = s + slen;
    while( p-- > s )
        if( mpi_get_digit( &d, radix, *p ) != 0 )
            break;

    return( ssv_mbedtls_mpi_read_string( X, radix, p + 1 ) );
}

/*
 * Write X into an opened file (or stdout if fout == NULL)
 */
int ssv_mbedtls_mpi_write_file( const char *p, const ssv_mbedtls_mpi *X, int radix, FILE *fout )
{
    int ret;
    size_t n, slen, plen;
    /*
     * Buffer should have space for (short) label and decimal formatted MPI,
     * newline characters and '\0'
     */
    char s[ SSV_MBEDTLS_MPI_RW_BUFFER_SIZE ];
    MPI_VALIDATE_RET( X != NULL );

    if( radix < 2 || radix > 16 )
        return( SSV_MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    memset( s, 0, sizeof( s ) );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_write_string( X, radix, s, sizeof( s ) - 2, &n ) );

    if( p == NULL ) p = "";

    plen = strlen( p );
    slen = strlen( s );
    s[slen++] = '\r';
    s[slen++] = '\n';

    if( fout != NULL )
    {
        if( fwrite( p, 1, plen, fout ) != plen ||
            fwrite( s, 1, slen, fout ) != slen )
            return( SSV_MBEDTLS_ERR_MPI_FILE_IO_ERROR );
    }
    else
        mbedtls_printf( "%s%s", p, s );

cleanup:

    return( ret );
}
#endif /* MBEDTLS_FS_IO */

/*
 * Import X from unsigned binary data, big endian
 */
int ssv_mbedtls_mpi_read_binary( ssv_mbedtls_mpi *X, const unsigned char *buf, size_t buflen )
{
    int ret;
    size_t i, j;
    size_t const limbs = CHARS_TO_LIMBS( buflen );

    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( buflen == 0 || buf != NULL );

    /* Ensure that target MPI has exactly the necessary number of limbs */
    if( X->n != limbs )
    {
        ssv_mbedtls_mpi_free( X );
        ssv_mbedtls_mpi_init( X );
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( X, limbs ) );
    }

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_lset( X, 0 ) );

    for( i = buflen, j = 0; i > 0; i--, j++ )
        X->p[j / ciL] |= ((ssv_mbedtls_mpi_uint) buf[i - 1]) << ((j % ciL) << 3);

cleanup:

    return( ret );
}

/*
 * Export X into unsigned binary data, big endian
 */
int ssv_mbedtls_mpi_write_binary( const ssv_mbedtls_mpi *X,
                              unsigned char *buf, size_t buflen )
{
    size_t stored_bytes;
    size_t bytes_to_copy;
    unsigned char *p;
    size_t i;

    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( buflen == 0 || buf != NULL );

    stored_bytes = X->n * ciL;

    if( stored_bytes < buflen )
    {
        /* There is enough space in the output buffer. Write initial
         * null bytes and record the position at which to start
         * writing the significant bytes. In this case, the execution
         * trace of this function does not depend on the value of the
         * number. */
        bytes_to_copy = stored_bytes;
        p = buf + buflen - stored_bytes;
        memset( buf, 0, buflen - stored_bytes );
    }
    else
    {
        /* The output buffer is smaller than the allocated size of X.
         * However X may fit if its leading bytes are zero. */
        bytes_to_copy = buflen;
        p = buf;
        for( i = bytes_to_copy; i < stored_bytes; i++ )
        {
            if( GET_BYTE( X, i ) != 0 )
                return( SSV_MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL );
        }
    }

    for( i = 0; i < bytes_to_copy; i++ )
        p[bytes_to_copy - i - 1] = GET_BYTE( X, i );

    return( 0 );
}

/*
 * Left-shift: X <<= count
 */
int ssv_mbedtls_mpi_shift_l( ssv_mbedtls_mpi *X, size_t count )
{
    int ret;
    size_t i, v0, t1;
    ssv_mbedtls_mpi_uint r0 = 0, r1;
    MPI_VALIDATE_RET( X != NULL );

    v0 = count / (biL    );
    t1 = count & (biL - 1);

    i = ssv_mbedtls_mpi_bitlen( X ) + count;

    if( X->n * biL < i )
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( X, BITS_TO_LIMBS( i ) ) );

    ret = 0;

    /*
     * shift by count / limb_size
     */
    if( v0 > 0 )
    {
        for( i = X->n; i > v0; i-- )
            X->p[i - 1] = X->p[i - v0 - 1];

        for( ; i > 0; i-- )
            X->p[i - 1] = 0;
    }

    /*
     * shift by count % limb_size
     */
    if( t1 > 0 )
    {
        for( i = v0; i < X->n; i++ )
        {
            r1 = X->p[i] >> (biL - t1);
            X->p[i] <<= t1;
            X->p[i] |= r0;
            r0 = r1;
        }
    }

cleanup:

    return( ret );
}

/*
 * Right-shift: X >>= count
 */
int ssv_mbedtls_mpi_shift_r( ssv_mbedtls_mpi *X, size_t count )
{
    size_t i, v0, v1;
    ssv_mbedtls_mpi_uint r0 = 0, r1;
    MPI_VALIDATE_RET( X != NULL );

    v0 = count /  biL;
    v1 = count & (biL - 1);

    if( v0 > X->n || ( v0 == X->n && v1 > 0 ) )
        return ssv_mbedtls_mpi_lset( X, 0 );

    /*
     * shift by count / limb_size
     */
    if( v0 > 0 )
    {
        for( i = 0; i < X->n - v0; i++ )
            X->p[i] = X->p[i + v0];

        for( ; i < X->n; i++ )
            X->p[i] = 0;
    }

    /*
     * shift by count % limb_size
     */
    if( v1 > 0 )
    {
        for( i = X->n; i > 0; i-- )
        {
            r1 = X->p[i - 1] << (biL - v1);
            X->p[i - 1] >>= v1;
            X->p[i - 1] |= r0;
            r0 = r1;
        }
    }

    return( 0 );
}

/*
 * Compare unsigned values
 */
int ssv_mbedtls_mpi_cmp_abs( const ssv_mbedtls_mpi *X, const ssv_mbedtls_mpi *Y )
{
    size_t i, j;
    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( Y != NULL );

    for( i = X->n; i > 0; i-- )
        if( X->p[i - 1] != 0 )
            break;

    for( j = Y->n; j > 0; j-- )
        if( Y->p[j - 1] != 0 )
            break;

    if( i == 0 && j == 0 )
        return( 0 );

    if( i > j ) return(  1 );
    if( j > i ) return( -1 );

    for( ; i > 0; i-- )
    {
        if( X->p[i - 1] > Y->p[i - 1] ) return(  1 );
        if( X->p[i - 1] < Y->p[i - 1] ) return( -1 );
    }

    return( 0 );
}

/*
 * Compare signed values
 */
int ssv_mbedtls_mpi_cmp_mpi( const ssv_mbedtls_mpi *X, const ssv_mbedtls_mpi *Y )
{
    size_t i, j;
    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( Y != NULL );

    for( i = X->n; i > 0; i-- )
        if( X->p[i - 1] != 0 )
            break;

    for( j = Y->n; j > 0; j-- )
        if( Y->p[j - 1] != 0 )
            break;

    if( i == 0 && j == 0 )
        return( 0 );

    if( i > j ) return(  X->s );
    if( j > i ) return( -Y->s );

    if( X->s > 0 && Y->s < 0 ) return(  1 );
    if( Y->s > 0 && X->s < 0 ) return( -1 );

    for( ; i > 0; i-- )
    {
        if( X->p[i - 1] > Y->p[i - 1] ) return(  X->s );
        if( X->p[i - 1] < Y->p[i - 1] ) return( -X->s );
    }

    return( 0 );
}

/*
 * Compare signed values
 */
int ssv_mbedtls_mpi_cmp_int( const ssv_mbedtls_mpi *X, ssv_mbedtls_mpi_sint z )
{
    ssv_mbedtls_mpi Y;
    ssv_mbedtls_mpi_uint p[1];
    MPI_VALIDATE_RET( X != NULL );

    *p  = ( z < 0 ) ? -z : z;
    Y.s = ( z < 0 ) ? -1 : 1;
    Y.n = 1;
    Y.p = p;

    return( ssv_mbedtls_mpi_cmp_mpi( X, &Y ) );
}

/*
 * Unsigned addition: X = |A| + |B|  (HAC 14.7)
 */
int ssv_mbedtls_mpi_add_abs( ssv_mbedtls_mpi *X, const ssv_mbedtls_mpi *A, const ssv_mbedtls_mpi *B )
{
    int ret;
    size_t i, j;
    ssv_mbedtls_mpi_uint *o, *p, c, tmp;
    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( A != NULL );
    MPI_VALIDATE_RET( B != NULL );

    if( X == B )
    {
        const ssv_mbedtls_mpi *T = A; A = X; B = T;
    }

    if( X != A )
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( X, A ) );

    /*
     * X should always be positive as a result of unsigned additions.
     */
    X->s = 1;

    for( j = B->n; j > 0; j-- )
        if( B->p[j - 1] != 0 )
            break;

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( X, j ) );

    o = B->p; p = X->p; c = 0;

    /*
     * tmp is used because it might happen that p == o
     */
    for( i = 0; i < j; i++, o++, p++ )
    {
        tmp= *o;
        *p +=  c; c  = ( *p <  c );
        *p += tmp; c += ( *p < tmp );
    }

    while( c != 0 )
    {
        if( i >= X->n )
        {
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( X, i + 1 ) );
            p = X->p + i;
        }

        *p += c; c = ( *p < c ); i++; p++;
    }

cleanup:

    return( ret );
}

/*
 * Helper for mbedtls_mpi subtraction
 */
static void mpi_sub_hlp( size_t n, ssv_mbedtls_mpi_uint *s, ssv_mbedtls_mpi_uint *d )
{
    size_t i;
    ssv_mbedtls_mpi_uint c, z;

    for( i = c = 0; i < n; i++, s++, d++ )
    {
        z = ( *d <  c );     *d -=  c;
        c = ( *d < *s ) + z; *d -= *s;
    }

    while( c != 0 )
    {
        z = ( *d < c ); *d -= c;
        c = z; d++;
    }
}

/*
 * Unsigned subtraction: X = |A| - |B|  (HAC 14.9)
 */
int ssv_mbedtls_mpi_sub_abs( ssv_mbedtls_mpi *X, const ssv_mbedtls_mpi *A, const ssv_mbedtls_mpi *B )
{
    ssv_mbedtls_mpi TB;
    int ret;
    size_t n;
    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( A != NULL );
    MPI_VALIDATE_RET( B != NULL );

    if( ssv_mbedtls_mpi_cmp_abs( A, B ) < 0 )
        return( SSV_MBEDTLS_ERR_MPI_NEGATIVE_VALUE );

    ssv_mbedtls_mpi_init( &TB );

    if( X == B )
    {
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &TB, B ) );
        B = &TB;
    }

    if( X != A )
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( X, A ) );

    /*
     * X should always be positive as a result of unsigned subtractions.
     */
    X->s = 1;

    ret = 0;

    for( n = B->n; n > 0; n-- )
        if( B->p[n - 1] != 0 )
            break;

    mpi_sub_hlp( n, B->p, X->p );

cleanup:

    ssv_mbedtls_mpi_free( &TB );

    return( ret );
}

/*
 * Signed addition: X = A + B
 */
int ssv_mbedtls_mpi_add_mpi( ssv_mbedtls_mpi *X, const ssv_mbedtls_mpi *A, const ssv_mbedtls_mpi *B )
{
    int ret, s;
    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( A != NULL );
    MPI_VALIDATE_RET( B != NULL );

    s = A->s;
    if( A->s * B->s < 0 )
    {
        if( ssv_mbedtls_mpi_cmp_abs( A, B ) >= 0 )
        {
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_abs( X, A, B ) );
            X->s =  s;
        }
        else
        {
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_abs( X, B, A ) );
            X->s = -s;
        }
    }
    else
    {
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_add_abs( X, A, B ) );
        X->s = s;
    }

cleanup:

    return( ret );
}

/*
 * Signed subtraction: X = A - B
 */
int ssv_mbedtls_mpi_sub_mpi( ssv_mbedtls_mpi *X, const ssv_mbedtls_mpi *A, const ssv_mbedtls_mpi *B )
{
    int ret, s;
    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( A != NULL );
    MPI_VALIDATE_RET( B != NULL );

    s = A->s;
    if( A->s * B->s > 0 )
    {
        if( ssv_mbedtls_mpi_cmp_abs( A, B ) >= 0 )
        {
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_abs( X, A, B ) );
            X->s =  s;
        }
        else
        {
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_abs( X, B, A ) );
            X->s = -s;
        }
    }
    else
    {
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_add_abs( X, A, B ) );
        X->s = s;
    }

cleanup:

    return( ret );
}

/*
 * Signed addition: X = A + b
 */
int ssv_mbedtls_mpi_add_int( ssv_mbedtls_mpi *X, const ssv_mbedtls_mpi *A, ssv_mbedtls_mpi_sint b )
{
    ssv_mbedtls_mpi _B;
    ssv_mbedtls_mpi_uint p[1];
    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( A != NULL );

    p[0] = ( b < 0 ) ? -b : b;
    _B.s = ( b < 0 ) ? -1 : 1;
    _B.n = 1;
    _B.p = p;

    return( ssv_mbedtls_mpi_add_mpi( X, A, &_B ) );
}

/*
 * Signed subtraction: X = A - b
 */
int ssv_mbedtls_mpi_sub_int( ssv_mbedtls_mpi *X, const ssv_mbedtls_mpi *A, ssv_mbedtls_mpi_sint b )
{
    ssv_mbedtls_mpi _B;
    ssv_mbedtls_mpi_uint p[1];
    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( A != NULL );

    p[0] = ( b < 0 ) ? -b : b;
    _B.s = ( b < 0 ) ? -1 : 1;
    _B.n = 1;
    _B.p = p;

    return( ssv_mbedtls_mpi_sub_mpi( X, A, &_B ) );
}

/*
 * Helper for mbedtls_mpi multiplication
 */
static
#if defined(__APPLE__) && defined(__arm__)
/*
 * Apple LLVM version 4.2 (clang-425.0.24) (based on LLVM 3.2svn)
 * appears to need this to prevent bad ARM code generation at -O3.
 */
__attribute__ ((noinline))
#endif
void mpi_mul_hlp( size_t i, ssv_mbedtls_mpi_uint *s, ssv_mbedtls_mpi_uint *d, ssv_mbedtls_mpi_uint b )
{
    ssv_mbedtls_mpi_uint c = 0, t = 0;

#if defined(MULADDC_HUIT)
    for( ; i >= 8; i -= 8 )
    {
        MULADDC_INIT
        MULADDC_HUIT
        MULADDC_STOP
    }

    for( ; i > 0; i-- )
    {
        MULADDC_INIT
        MULADDC_CORE
        MULADDC_STOP
    }
#else /* MULADDC_HUIT */
    for( ; i >= 16; i -= 16 )
    {
        MULADDC_INIT
        MULADDC_CORE   MULADDC_CORE
        MULADDC_CORE   MULADDC_CORE
        MULADDC_CORE   MULADDC_CORE
        MULADDC_CORE   MULADDC_CORE

        MULADDC_CORE   MULADDC_CORE
        MULADDC_CORE   MULADDC_CORE
        MULADDC_CORE   MULADDC_CORE
        MULADDC_CORE   MULADDC_CORE
        MULADDC_STOP
    }

    for( ; i >= 8; i -= 8 )
    {
        MULADDC_INIT
        MULADDC_CORE   MULADDC_CORE
        MULADDC_CORE   MULADDC_CORE

        MULADDC_CORE   MULADDC_CORE
        MULADDC_CORE   MULADDC_CORE
        MULADDC_STOP
    }

    for( ; i > 0; i-- )
    {
        MULADDC_INIT
        MULADDC_CORE
        MULADDC_STOP
    }
#endif /* MULADDC_HUIT */

    t++;

    do {
        *d += c; c = ( *d < c ); d++;
    }
    while( c != 0 );
}

/*
 * Baseline multiplication: X = A * B  (HAC 14.12)
 */
int ssv_mbedtls_mpi_mul_mpi( ssv_mbedtls_mpi *X, const ssv_mbedtls_mpi *A, const ssv_mbedtls_mpi *B )
{
    int ret;
    size_t i, j;
    ssv_mbedtls_mpi TA, TB;
    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( A != NULL );
    MPI_VALIDATE_RET( B != NULL );

    ssv_mbedtls_mpi_init( &TA ); ssv_mbedtls_mpi_init( &TB );

    if( X == A ) { SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &TA, A ) ); A = &TA; }
    if( X == B ) { SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &TB, B ) ); B = &TB; }

    for( i = A->n; i > 0; i-- )
        if( A->p[i - 1] != 0 )
            break;

    for( j = B->n; j > 0; j-- )
        if( B->p[j - 1] != 0 )
            break;

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( X, i + j ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_lset( X, 0 ) );

    for( ; j > 0; j-- )
        mpi_mul_hlp( i, A->p, X->p + j - 1, B->p[j - 1] );

    X->s = A->s * B->s;

cleanup:

    ssv_mbedtls_mpi_free( &TB ); ssv_mbedtls_mpi_free( &TA );

    return( ret );
}

/*
 * Baseline multiplication: X = A * b
 */
int ssv_mbedtls_mpi_mul_int( ssv_mbedtls_mpi *X, const ssv_mbedtls_mpi *A, ssv_mbedtls_mpi_uint b )
{
    ssv_mbedtls_mpi _B;
    ssv_mbedtls_mpi_uint p[1];
    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( A != NULL );

    _B.s = 1;
    _B.n = 1;
    _B.p = p;
    p[0] = b;

    return( ssv_mbedtls_mpi_mul_mpi( X, A, &_B ) );
}

/*
 * Unsigned integer divide - double mbedtls_mpi_uint dividend, u1/u0, and
 * mbedtls_mpi_uint divisor, d
 */
static ssv_mbedtls_mpi_uint ssv_mbedtls_int_div_int( ssv_mbedtls_mpi_uint u1,
            ssv_mbedtls_mpi_uint u0, ssv_mbedtls_mpi_uint d, ssv_mbedtls_mpi_uint *r )
{
#if defined(MBEDTLS_HAVE_UDBL)
    ssv_mbedtls_t_udbl dividend, quotient;
#else
    const ssv_mbedtls_mpi_uint radix = (ssv_mbedtls_mpi_uint) 1 << biH;
    const ssv_mbedtls_mpi_uint uint_halfword_mask = ( (ssv_mbedtls_mpi_uint) 1 << biH ) - 1;
    ssv_mbedtls_mpi_uint d0, d1, q0, q1, rAX, r0, quotient;
    ssv_mbedtls_mpi_uint u0_msw, u0_lsw;
    size_t s;
#endif

    /*
     * Check for overflow
     */
    if( 0 == d || u1 >= d )
    {
        if (r != NULL) *r = ~0;

        return ( ~0 );
    }

#if defined(MBEDTLS_HAVE_UDBL)
    dividend  = (ssv_mbedtls_t_udbl) u1 << biL;
    dividend |= (ssv_mbedtls_t_udbl) u0;
    quotient = dividend / d;
    if( quotient > ( (ssv_mbedtls_t_udbl) 1 << biL ) - 1 )
        quotient = ( (ssv_mbedtls_t_udbl) 1 << biL ) - 1;

    if( r != NULL )
        *r = (ssv_mbedtls_mpi_uint)( dividend - (quotient * d ) );

    return (ssv_mbedtls_mpi_uint) quotient;
#else

    /*
     * Algorithm D, Section 4.3.1 - The Art of Computer Programming
     *   Vol. 2 - Seminumerical Algorithms, Knuth
     */

    /*
     * Normalize the divisor, d, and dividend, u0, u1
     */
    s = ssv_mbedtls_clz( d );
    d = d << s;

    u1 = u1 << s;
    u1 |= ( u0 >> ( biL - s ) ) & ( -(ssv_mbedtls_mpi_sint)s >> ( biL - 1 ) );
    u0 =  u0 << s;

    d1 = d >> biH;
    d0 = d & uint_halfword_mask;

    u0_msw = u0 >> biH;
    u0_lsw = u0 & uint_halfword_mask;

    /*
     * Find the first quotient and remainder
     */
    q1 = u1 / d1;
    r0 = u1 - d1 * q1;

    while( q1 >= radix || ( q1 * d0 > radix * r0 + u0_msw ) )
    {
        q1 -= 1;
        r0 += d1;

        if ( r0 >= radix ) break;
    }

    rAX = ( u1 * radix ) + ( u0_msw - q1 * d );
    q0 = rAX / d1;
    r0 = rAX - q0 * d1;

    while( q0 >= radix || ( q0 * d0 > radix * r0 + u0_lsw ) )
    {
        q0 -= 1;
        r0 += d1;

        if ( r0 >= radix ) break;
    }

    if (r != NULL)
        *r = ( rAX * radix + u0_lsw - q0 * d ) >> s;

    quotient = q1 * radix + q0;

    return quotient;
#endif
}

/*
 * Division by mbedtls_mpi: A = Q * B + R  (HAC 14.20)
 */
int ssv_mbedtls_mpi_div_mpi( ssv_mbedtls_mpi *Q, ssv_mbedtls_mpi *R, const ssv_mbedtls_mpi *A,
                         const ssv_mbedtls_mpi *B )
{
    int ret;
    size_t i, n, t, k;
    ssv_mbedtls_mpi X, Y, Z, T1, T2;
    MPI_VALIDATE_RET( A != NULL );
    MPI_VALIDATE_RET( B != NULL );

    if( ssv_mbedtls_mpi_cmp_int( B, 0 ) == 0 )
        return( SSV_MBEDTLS_ERR_MPI_DIVISION_BY_ZERO );

    ssv_mbedtls_mpi_init( &X ); ssv_mbedtls_mpi_init( &Y ); ssv_mbedtls_mpi_init( &Z );
    ssv_mbedtls_mpi_init( &T1 ); ssv_mbedtls_mpi_init( &T2 );

    if( ssv_mbedtls_mpi_cmp_abs( A, B ) < 0 )
    {
        if( Q != NULL ) SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_lset( Q, 0 ) );
        if( R != NULL ) SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( R, A ) );
        return( 0 );
    }

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &X, A ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &Y, B ) );
    X.s = Y.s = 1;

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( &Z, A->n + 2 ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_lset( &Z,  0 ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( &T1, 2 ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( &T2, 3 ) );

    k = ssv_mbedtls_mpi_bitlen( &Y ) % biL;
    if( k < biL - 1 )
    {
        k = biL - 1 - k;
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_l( &X, k ) );
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_l( &Y, k ) );
    }
    else k = 0;

    n = X.n - 1;
    t = Y.n - 1;
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_l( &Y, biL * ( n - t ) ) );

    while( ssv_mbedtls_mpi_cmp_mpi( &X, &Y ) >= 0 )
    {
        Z.p[n - t]++;
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_mpi( &X, &X, &Y ) );
    }
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &Y, biL * ( n - t ) ) );

    for( i = n; i > t ; i-- )
    {
        if( X.p[i] >= Y.p[t] )
            Z.p[i - t - 1] = ~0;
        else
        {
            Z.p[i - t - 1] = ssv_mbedtls_int_div_int( X.p[i], X.p[i - 1],
                                                            Y.p[t], NULL);
        }

        Z.p[i - t - 1]++;
        do
        {
            Z.p[i - t - 1]--;

            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_lset( &T1, 0 ) );
            T1.p[0] = ( t < 1 ) ? 0 : Y.p[t - 1];
            T1.p[1] = Y.p[t];
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_mul_int( &T1, &T1, Z.p[i - t - 1] ) );

            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_lset( &T2, 0 ) );
            T2.p[0] = ( i < 2 ) ? 0 : X.p[i - 2];
            T2.p[1] = ( i < 1 ) ? 0 : X.p[i - 1];
            T2.p[2] = X.p[i];
        }
        while( ssv_mbedtls_mpi_cmp_mpi( &T1, &T2 ) > 0 );

        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_mul_int( &T1, &Y, Z.p[i - t - 1] ) );
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_l( &T1,  biL * ( i - t - 1 ) ) );
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_mpi( &X, &X, &T1 ) );

        if( ssv_mbedtls_mpi_cmp_int( &X, 0 ) < 0 )
        {
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &T1, &Y ) );
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_l( &T1, biL * ( i - t - 1 ) ) );
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_add_mpi( &X, &X, &T1 ) );
            Z.p[i - t - 1]--;
        }
    }

    if( Q != NULL )
    {
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( Q, &Z ) );
        Q->s = A->s * B->s;
    }

    if( R != NULL )
    {
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &X, k ) );
        X.s = A->s;
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( R, &X ) );

        if( ssv_mbedtls_mpi_cmp_int( R, 0 ) == 0 )
            R->s = 1;
    }

cleanup:

    ssv_mbedtls_mpi_free( &X ); ssv_mbedtls_mpi_free( &Y ); ssv_mbedtls_mpi_free( &Z );
    ssv_mbedtls_mpi_free( &T1 ); ssv_mbedtls_mpi_free( &T2 );

    return( ret );
}

/*
 * Division by int: A = Q * b + R
 */
int ssv_mbedtls_mpi_div_int( ssv_mbedtls_mpi *Q, ssv_mbedtls_mpi *R,
                         const ssv_mbedtls_mpi *A,
                         ssv_mbedtls_mpi_sint b )
{
    ssv_mbedtls_mpi _B;
    ssv_mbedtls_mpi_uint p[1];
    MPI_VALIDATE_RET( A != NULL );

    p[0] = ( b < 0 ) ? -b : b;
    _B.s = ( b < 0 ) ? -1 : 1;
    _B.n = 1;
    _B.p = p;

    return( ssv_mbedtls_mpi_div_mpi( Q, R, A, &_B ) );
}

/*
 * Modulo: R = A mod B
 */
int ssv_mbedtls_mpi_mod_mpi( ssv_mbedtls_mpi *R, const ssv_mbedtls_mpi *A, const ssv_mbedtls_mpi *B )
{
    int ret;
    MPI_VALIDATE_RET( R != NULL );
    MPI_VALIDATE_RET( A != NULL );
    MPI_VALIDATE_RET( B != NULL );

    if( ssv_mbedtls_mpi_cmp_int( B, 0 ) < 0 )
        return( SSV_MBEDTLS_ERR_MPI_NEGATIVE_VALUE );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_div_mpi( NULL, R, A, B ) );

    while( ssv_mbedtls_mpi_cmp_int( R, 0 ) < 0 )
      SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_add_mpi( R, R, B ) );

    while( ssv_mbedtls_mpi_cmp_mpi( R, B ) >= 0 )
      SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_mpi( R, R, B ) );

cleanup:

    return( ret );
}

/*
 * Modulo: r = A mod b
 */
int ssv_mbedtls_mpi_mod_int( ssv_mbedtls_mpi_uint *r, const ssv_mbedtls_mpi *A, ssv_mbedtls_mpi_sint b )
{
    size_t i;
    ssv_mbedtls_mpi_uint x, y, z;
    MPI_VALIDATE_RET( r != NULL );
    MPI_VALIDATE_RET( A != NULL );

    if( b == 0 )
        return( SSV_MBEDTLS_ERR_MPI_DIVISION_BY_ZERO );

    if( b < 0 )
        return( SSV_MBEDTLS_ERR_MPI_NEGATIVE_VALUE );

    /*
     * handle trivial cases
     */
    if( b == 1 )
    {
        *r = 0;
        return( 0 );
    }

    if( b == 2 )
    {
        *r = A->p[0] & 1;
        return( 0 );
    }

    /*
     * general case
     */
    for( i = A->n, y = 0; i > 0; i-- )
    {
        x  = A->p[i - 1];
        y  = ( y << biH ) | ( x >> biH );
        z  = y / b;
        y -= z * b;

        x <<= biH;
        y  = ( y << biH ) | ( x >> biH );
        z  = y / b;
        y -= z * b;
    }

    /*
     * If A is negative, then the current y represents a negative value.
     * Flipping it to the positive side.
     */
    if( A->s < 0 && y != 0 )
        y = b - y;

    *r = y;

    return( 0 );
}

/*
 * Fast Montgomery initialization (thanks to Tom St Denis)
 */
static void mpi_montg_init( ssv_mbedtls_mpi_uint *mm, const ssv_mbedtls_mpi *N )
{
    ssv_mbedtls_mpi_uint x, m0 = N->p[0];
    unsigned int i;

    x  = m0;
    x += ( ( m0 + 2 ) & 4 ) << 1;

    for( i = biL; i >= 8; i /= 2 )
        x *= ( 2 - ( m0 * x ) );

    *mm = ~x + 1;
}

/*
 * Montgomery multiplication: A = A * B * R^-1 mod N  (HAC 14.36)
 */
static int mpi_montmul( ssv_mbedtls_mpi *A, const ssv_mbedtls_mpi *B, const ssv_mbedtls_mpi *N, ssv_mbedtls_mpi_uint mm,
                         const ssv_mbedtls_mpi *T )
{
    size_t i, n, m;
    ssv_mbedtls_mpi_uint u0, u1, *d;

    if( T->n < N->n + 1 || T->p == NULL )
        return( SSV_MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    memset( T->p, 0, T->n * ciL );

    d = T->p;
    n = N->n;
    m = ( B->n < n ) ? B->n : n;

    for( i = 0; i < n; i++ )
    {
        /*
         * T = (T + u0*B + u1*N) / 2^biL
         */
        u0 = A->p[i];
        u1 = ( d[0] + u0 * B->p[0] ) * mm;

        mpi_mul_hlp( m, B->p, d, u0 );
        mpi_mul_hlp( n, N->p, d, u1 );

        *d++ = u0; d[n + 1] = 0;
    }

    memcpy( A->p, d, ( n + 1 ) * ciL );

    if( ssv_mbedtls_mpi_cmp_abs( A, N ) >= 0 )
        mpi_sub_hlp( n, N->p, A->p );
    else
        /* prevent timing attacks */
        mpi_sub_hlp( n, A->p, T->p );

    return( 0 );
}

/*
 * Montgomery reduction: A = A * R^-1 mod N
 */
static int mpi_montred( ssv_mbedtls_mpi *A, const ssv_mbedtls_mpi *N,
                        ssv_mbedtls_mpi_uint mm, const ssv_mbedtls_mpi *T )
{
    ssv_mbedtls_mpi_uint z = 1;
    ssv_mbedtls_mpi U;

    U.n = U.s = (int) z;
    U.p = &z;

    return( mpi_montmul( A, &U, N, mm, T ) );
}

/*
 * Sliding-window exponentiation: X = A^E mod N  (HAC 14.85)
 */
int ssv_mbedtls_mpi_exp_mod( ssv_mbedtls_mpi *X, const ssv_mbedtls_mpi *A,
                         const ssv_mbedtls_mpi *E, const ssv_mbedtls_mpi *N,
                         ssv_mbedtls_mpi *_RR )
{
    int ret;
    size_t wbits, wsize, one = 1;
    size_t i, j, nblimbs;
    size_t bufsize, nbits;
    ssv_mbedtls_mpi_uint ei, mm, state;
    ssv_mbedtls_mpi RR, T, W[ 2 << SSV_MBEDTLS_MPI_WINDOW_SIZE ], Apos;
    int neg;

    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( A != NULL );
    MPI_VALIDATE_RET( E != NULL );
    MPI_VALIDATE_RET( N != NULL );

    if( ssv_mbedtls_mpi_cmp_int( N, 0 ) <= 0 || ( N->p[0] & 1 ) == 0 )
        return( SSV_MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    if( ssv_mbedtls_mpi_cmp_int( E, 0 ) < 0 )
        return( SSV_MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    /*
     * Init temps and window size
     */
    mpi_montg_init( &mm, N );
    ssv_mbedtls_mpi_init( &RR ); ssv_mbedtls_mpi_init( &T );
    ssv_mbedtls_mpi_init( &Apos );
    memset( W, 0, sizeof( W ) );

    i = ssv_mbedtls_mpi_bitlen( E );

    wsize = ( i > 671 ) ? 6 : ( i > 239 ) ? 5 :
            ( i >  79 ) ? 4 : ( i >  23 ) ? 3 : 1;

    if( wsize > SSV_MBEDTLS_MPI_WINDOW_SIZE )
        wsize = SSV_MBEDTLS_MPI_WINDOW_SIZE;

    j = N->n + 1;
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( X, j ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( &W[1],  j ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( &T, j * 2 ) );

    /*
     * Compensate for negative A (and correct at the end)
     */
    neg = ( A->s == -1 );
    if( neg )
    {
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &Apos, A ) );
        Apos.s = 1;
        A = &Apos;
    }

    /*
     * If 1st call, pre-compute R^2 mod N
     */
    if( _RR == NULL || _RR->p == NULL )
    {
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_lset( &RR, 1 ) );
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_l( &RR, N->n * 2 * biL ) );
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_mod_mpi( &RR, &RR, N ) );

        if( _RR != NULL )
            memcpy( _RR, &RR, sizeof( ssv_mbedtls_mpi ) );
    }
    else
        memcpy( &RR, _RR, sizeof( ssv_mbedtls_mpi ) );

    /*
     * W[1] = A * R^2 * R^-1 mod N = A * R mod N
     */
    if( ssv_mbedtls_mpi_cmp_mpi( A, N ) >= 0 )
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_mod_mpi( &W[1], A, N ) );
    else
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &W[1], A ) );

    SSV_MBEDTLS_MPI_CHK( mpi_montmul( &W[1], &RR, N, mm, &T ) );

    /*
     * X = R^2 * R^-1 mod N = R mod N
     */
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( X, &RR ) );
    SSV_MBEDTLS_MPI_CHK( mpi_montred( X, N, mm, &T ) );

    if( wsize > 1 )
    {
        /*
         * W[1 << (wsize - 1)] = W[1] ^ (wsize - 1)
         */
        j =  one << ( wsize - 1 );

        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( &W[j], N->n + 1 ) );
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &W[j], &W[1]    ) );

        for( i = 0; i < wsize - 1; i++ )
            SSV_MBEDTLS_MPI_CHK( mpi_montmul( &W[j], &W[j], N, mm, &T ) );

        /*
         * W[i] = W[i - 1] * W[1]
         */
        for( i = j + 1; i < ( one << wsize ); i++ )
        {
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_grow( &W[i], N->n + 1 ) );
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &W[i], &W[i - 1] ) );

            SSV_MBEDTLS_MPI_CHK( mpi_montmul( &W[i], &W[1], N, mm, &T ) );
        }
    }

    nblimbs = E->n;
    bufsize = 0;
    nbits   = 0;
    wbits   = 0;
    state   = 0;

    while( 1 )
    {
        if( bufsize == 0 )
        {
            if( nblimbs == 0 )
                break;

            nblimbs--;

            bufsize = sizeof( ssv_mbedtls_mpi_uint ) << 3;
        }

        bufsize--;

        ei = (E->p[nblimbs] >> bufsize) & 1;

        /*
         * skip leading 0s
         */
        if( ei == 0 && state == 0 )
            continue;

        if( ei == 0 && state == 1 )
        {
            /*
             * out of window, square X
             */
            SSV_MBEDTLS_MPI_CHK( mpi_montmul( X, X, N, mm, &T ) );
            continue;
        }

        /*
         * add ei to current window
         */
        state = 2;

        nbits++;
        wbits |= ( ei << ( wsize - nbits ) );

        if( nbits == wsize )
        {
            /*
             * X = X^wsize R^-1 mod N
             */
            for( i = 0; i < wsize; i++ )
                SSV_MBEDTLS_MPI_CHK( mpi_montmul( X, X, N, mm, &T ) );

            /*
             * X = X * W[wbits] R^-1 mod N
             */
            SSV_MBEDTLS_MPI_CHK( mpi_montmul( X, &W[wbits], N, mm, &T ) );

            state--;
            nbits = 0;
            wbits = 0;
        }
    }

    /*
     * process the remaining bits
     */
    for( i = 0; i < nbits; i++ )
    {
        SSV_MBEDTLS_MPI_CHK( mpi_montmul( X, X, N, mm, &T ) );

        wbits <<= 1;

        if( ( wbits & ( one << wsize ) ) != 0 )
            SSV_MBEDTLS_MPI_CHK( mpi_montmul( X, &W[1], N, mm, &T ) );
    }

    /*
     * X = A^E * R * R^-1 mod N = A^E mod N
     */
    SSV_MBEDTLS_MPI_CHK( mpi_montred( X, N, mm, &T ) );

    if( neg && E->n != 0 && ( E->p[0] & 1 ) != 0 )
    {
        X->s = -1;
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_add_mpi( X, N, X ) );
    }

cleanup:

    for( i = ( one << ( wsize - 1 ) ); i < ( one << wsize ); i++ )
        ssv_mbedtls_mpi_free( &W[i] );

    ssv_mbedtls_mpi_free( &W[1] ); ssv_mbedtls_mpi_free( &T ); ssv_mbedtls_mpi_free( &Apos );

    if( _RR == NULL || _RR->p == NULL )
        ssv_mbedtls_mpi_free( &RR );

    return( ret );
}

/*
 * Greatest common divisor: G = gcd(A, B)  (HAC 14.54)
 */
int ssv_mbedtls_mpi_gcd( ssv_mbedtls_mpi *G, const ssv_mbedtls_mpi *A, const ssv_mbedtls_mpi *B )
{
    int ret;
    size_t lz, lzt;
    ssv_mbedtls_mpi TG, TA, TB;

    MPI_VALIDATE_RET( G != NULL );
    MPI_VALIDATE_RET( A != NULL );
    MPI_VALIDATE_RET( B != NULL );

    ssv_mbedtls_mpi_init( &TG ); ssv_mbedtls_mpi_init( &TA ); ssv_mbedtls_mpi_init( &TB );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &TA, A ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &TB, B ) );

    lz = ssv_mbedtls_mpi_lsb( &TA );
    lzt = ssv_mbedtls_mpi_lsb( &TB );

    if( lzt < lz )
        lz = lzt;

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &TA, lz ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &TB, lz ) );

    TA.s = TB.s = 1;

    while( ssv_mbedtls_mpi_cmp_int( &TA, 0 ) != 0 )
    {
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &TA, ssv_mbedtls_mpi_lsb( &TA ) ) );
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &TB, ssv_mbedtls_mpi_lsb( &TB ) ) );

        if( ssv_mbedtls_mpi_cmp_mpi( &TA, &TB ) >= 0 )
        {
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_abs( &TA, &TA, &TB ) );
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &TA, 1 ) );
        }
        else
        {
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_abs( &TB, &TB, &TA ) );
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &TB, 1 ) );
        }
    }

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_l( &TB, lz ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( G, &TB ) );

cleanup:

    ssv_mbedtls_mpi_free( &TG ); ssv_mbedtls_mpi_free( &TA ); ssv_mbedtls_mpi_free( &TB );

    return( ret );
}

/*
 * Fill X with size bytes of random.
 *
 * Use a temporary bytes representation to make sure the result is the same
 * regardless of the platform endianness (useful when f_rng is actually
 * deterministic, eg for tests).
 */
int ssv_mbedtls_mpi_fill_random( ssv_mbedtls_mpi *X, size_t size,
                     int (*f_rng)(void *, unsigned char *, size_t),
                     void *p_rng )
{
    int ret;
    unsigned char buf[SSV_MBEDTLS_MPI_MAX_SIZE];
    MPI_VALIDATE_RET( X     != NULL );
    MPI_VALIDATE_RET( f_rng != NULL );

    if( size > SSV_MBEDTLS_MPI_MAX_SIZE )
        return( SSV_MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    SSV_MBEDTLS_MPI_CHK( f_rng( p_rng, buf, size ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_read_binary( X, buf, size ) );

cleanup:
    ssv_mbedtls_platform_zeroize( buf, sizeof( buf ) );
    return( ret );
}

/*
 * Modular inverse: X = A^-1 mod N  (HAC 14.61 / 14.64)
 */
int ssv_mbedtls_mpi_inv_mod( ssv_mbedtls_mpi *X, const ssv_mbedtls_mpi *A, const ssv_mbedtls_mpi *N )
{
    int ret;
    ssv_mbedtls_mpi G, TA, TU, U1, U2, TB, TV, V1, V2;
    MPI_VALIDATE_RET( X != NULL );
    MPI_VALIDATE_RET( A != NULL );
    MPI_VALIDATE_RET( N != NULL );

    if( ssv_mbedtls_mpi_cmp_int( N, 1 ) <= 0 )
        return( SSV_MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    ssv_mbedtls_mpi_init( &TA ); ssv_mbedtls_mpi_init( &TU ); ssv_mbedtls_mpi_init( &U1 ); ssv_mbedtls_mpi_init( &U2 );
    ssv_mbedtls_mpi_init( &G ); ssv_mbedtls_mpi_init( &TB ); ssv_mbedtls_mpi_init( &TV );
    ssv_mbedtls_mpi_init( &V1 ); ssv_mbedtls_mpi_init( &V2 );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_gcd( &G, A, N ) );

    if( ssv_mbedtls_mpi_cmp_int( &G, 1 ) != 0 )
    {
        ret = SSV_MBEDTLS_ERR_MPI_NOT_ACCEPTABLE;
        goto cleanup;
    }

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_mod_mpi( &TA, A, N ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &TU, &TA ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &TB, N ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &TV, N ) );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_lset( &U1, 1 ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_lset( &U2, 0 ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_lset( &V1, 0 ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_lset( &V2, 1 ) );

    do
    {
        while( ( TU.p[0] & 1 ) == 0 )
        {
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &TU, 1 ) );

            if( ( U1.p[0] & 1 ) != 0 || ( U2.p[0] & 1 ) != 0 )
            {
                SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_add_mpi( &U1, &U1, &TB ) );
                SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_mpi( &U2, &U2, &TA ) );
            }

            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &U1, 1 ) );
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &U2, 1 ) );
        }

        while( ( TV.p[0] & 1 ) == 0 )
        {
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &TV, 1 ) );

            if( ( V1.p[0] & 1 ) != 0 || ( V2.p[0] & 1 ) != 0 )
            {
                SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_add_mpi( &V1, &V1, &TB ) );
                SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_mpi( &V2, &V2, &TA ) );
            }

            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &V1, 1 ) );
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &V2, 1 ) );
        }

        if( ssv_mbedtls_mpi_cmp_mpi( &TU, &TV ) >= 0 )
        {
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_mpi( &TU, &TU, &TV ) );
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_mpi( &U1, &U1, &V1 ) );
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_mpi( &U2, &U2, &V2 ) );
        }
        else
        {
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_mpi( &TV, &TV, &TU ) );
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_mpi( &V1, &V1, &U1 ) );
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_mpi( &V2, &V2, &U2 ) );
        }
    }
    while( ssv_mbedtls_mpi_cmp_int( &TU, 0 ) != 0 );

    while( ssv_mbedtls_mpi_cmp_int( &V1, 0 ) < 0 )
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_add_mpi( &V1, &V1, N ) );

    while( ssv_mbedtls_mpi_cmp_mpi( &V1, N ) >= 0 )
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_mpi( &V1, &V1, N ) );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( X, &V1 ) );

cleanup:

    ssv_mbedtls_mpi_free( &TA ); ssv_mbedtls_mpi_free( &TU ); ssv_mbedtls_mpi_free( &U1 ); ssv_mbedtls_mpi_free( &U2 );
    ssv_mbedtls_mpi_free( &G ); ssv_mbedtls_mpi_free( &TB ); ssv_mbedtls_mpi_free( &TV );
    ssv_mbedtls_mpi_free( &V1 ); ssv_mbedtls_mpi_free( &V2 );

    return( ret );
}

#if defined(MBEDTLS_GENPRIME)

static const int small_prime[] =
{
        3,    5,    7,   11,   13,   17,   19,   23,
       29,   31,   37,   41,   43,   47,   53,   59,
       61,   67,   71,   73,   79,   83,   89,   97,
      101,  103,  107,  109,  113,  127,  131,  137,
      139,  149,  151,  157,  163,  167,  173,  179,
      181,  191,  193,  197,  199,  211,  223,  227,
      229,  233,  239,  241,  251,  257,  263,  269,
      271,  277,  281,  283,  293,  307,  311,  313,
      317,  331,  337,  347,  349,  353,  359,  367,
      373,  379,  383,  389,  397,  401,  409,  419,
      421,  431,  433,  439,  443,  449,  457,  461,
      463,  467,  479,  487,  491,  499,  503,  509,
      521,  523,  541,  547,  557,  563,  569,  571,
      577,  587,  593,  599,  601,  607,  613,  617,
      619,  631,  641,  643,  647,  653,  659,  661,
      673,  677,  683,  691,  701,  709,  719,  727,
      733,  739,  743,  751,  757,  761,  769,  773,
      787,  797,  809,  811,  821,  823,  827,  829,
      839,  853,  857,  859,  863,  877,  881,  883,
      887,  907,  911,  919,  929,  937,  941,  947,
      953,  967,  971,  977,  983,  991,  997, -103
};

/*
 * Small divisors test (X must be positive)
 *
 * Return values:
 * 0: no small factor (possible prime, more tests needed)
 * 1: certain prime
 * MBEDTLS_ERR_MPI_NOT_ACCEPTABLE: certain non-prime
 * other negative: error
 */
static int mpi_check_small_factors( const ssv_mbedtls_mpi *X )
{
    int ret = 0;
    size_t i;
    ssv_mbedtls_mpi_uint r;

    if( ( X->p[0] & 1 ) == 0 )
        return( SSV_MBEDTLS_ERR_MPI_NOT_ACCEPTABLE );

    for( i = 0; small_prime[i] > 0; i++ )
    {
        if( ssv_mbedtls_mpi_cmp_int( X, small_prime[i] ) <= 0 )
            return( 1 );

        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_mod_int( &r, X, small_prime[i] ) );

        if( r == 0 )
            return( SSV_MBEDTLS_ERR_MPI_NOT_ACCEPTABLE );
    }

cleanup:
    return( ret );
}

/*
 * Miller-Rabin pseudo-primality test  (HAC 4.24)
 */
static int mpi_miller_rabin( const ssv_mbedtls_mpi *X, size_t rounds,
                             int (*f_rng)(void *, unsigned char *, size_t),
                             void *p_rng )
{
    int ret, count;
    size_t i, j, k, s;
    ssv_mbedtls_mpi W, R, T, A, RR;

    MPI_VALIDATE_RET( X     != NULL );
    MPI_VALIDATE_RET( f_rng != NULL );

    ssv_mbedtls_mpi_init( &W ); ssv_mbedtls_mpi_init( &R );
    ssv_mbedtls_mpi_init( &T ); ssv_mbedtls_mpi_init( &A );
    ssv_mbedtls_mpi_init( &RR );

    /*
     * W = |X| - 1
     * R = W >> lsb( W )
     */
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_sub_int( &W, X, 1 ) );
    s = ssv_mbedtls_mpi_lsb( &W );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &R, &W ) );
    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &R, s ) );

    i = ssv_mbedtls_mpi_bitlen( X );

    for( i = 0; i < rounds; i++ )
    {
        /*
         * pick a random A, 1 < A < |X| - 1
         */
        count = 0;
        do {
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_fill_random( &A, X->n * ciL, f_rng, p_rng ) );

            j = ssv_mbedtls_mpi_bitlen( &A );
            k = ssv_mbedtls_mpi_bitlen( &W );
            if (j > k) {
                A.p[A.n - 1] &= ( (ssv_mbedtls_mpi_uint) 1 << ( k - ( A.n - 1 ) * biL - 1 ) ) - 1;
            }

            if (count++ > 30) {
                return SSV_MBEDTLS_ERR_MPI_NOT_ACCEPTABLE;
            }

        } while ( ssv_mbedtls_mpi_cmp_mpi( &A, &W ) >= 0 ||
                  ssv_mbedtls_mpi_cmp_int( &A, 1 )  <= 0    );

        /*
         * A = A^R mod |X|
         */
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_exp_mod( &A, &A, &R, X, &RR ) );

        if( ssv_mbedtls_mpi_cmp_mpi( &A, &W ) == 0 ||
            ssv_mbedtls_mpi_cmp_int( &A,  1 ) == 0 )
            continue;

        j = 1;
        while( j < s && ssv_mbedtls_mpi_cmp_mpi( &A, &W ) != 0 )
        {
            /*
             * A = A * A mod |X|
             */
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_mul_mpi( &T, &A, &A ) );
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_mod_mpi( &A, &T, X  ) );

            if( ssv_mbedtls_mpi_cmp_int( &A, 1 ) == 0 )
                break;

            j++;
        }

        /*
         * not prime if A != |X| - 1 or A == 1
         */
        if( ssv_mbedtls_mpi_cmp_mpi( &A, &W ) != 0 ||
            ssv_mbedtls_mpi_cmp_int( &A,  1 ) == 0 )
        {
            ret = SSV_MBEDTLS_ERR_MPI_NOT_ACCEPTABLE;
            break;
        }
    }

cleanup:
    ssv_mbedtls_mpi_free( &W ); ssv_mbedtls_mpi_free( &R );
    ssv_mbedtls_mpi_free( &T ); ssv_mbedtls_mpi_free( &A );
    ssv_mbedtls_mpi_free( &RR );

    return( ret );
}

/*
 * Pseudo-primality test: small factors, then Miller-Rabin
 */
int ssv_mbedtls_mpi_is_prime_ext( const ssv_mbedtls_mpi *X, int rounds,
                              int (*f_rng)(void *, unsigned char *, size_t),
                              void *p_rng )
{
    int ret;
    ssv_mbedtls_mpi XX;
    MPI_VALIDATE_RET( X     != NULL );
    MPI_VALIDATE_RET( f_rng != NULL );

    XX.s = 1;
    XX.n = X->n;
    XX.p = X->p;

    if( ssv_mbedtls_mpi_cmp_int( &XX, 0 ) == 0 ||
        ssv_mbedtls_mpi_cmp_int( &XX, 1 ) == 0 )
        return( SSV_MBEDTLS_ERR_MPI_NOT_ACCEPTABLE );

    if( ssv_mbedtls_mpi_cmp_int( &XX, 2 ) == 0 )
        return( 0 );

    if( ( ret = mpi_check_small_factors( &XX ) ) != 0 )
    {
        if( ret == 1 )
            return( 0 );

        return( ret );
    }

    return( mpi_miller_rabin( &XX, rounds, f_rng, p_rng ) );
}

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
/*
 * Pseudo-primality test, error probability 2^-80
 */
int ssv_mbedtls_mpi_is_prime( const ssv_mbedtls_mpi *X,
                  int (*f_rng)(void *, unsigned char *, size_t),
                  void *p_rng )
{
    MPI_VALIDATE_RET( X     != NULL );
    MPI_VALIDATE_RET( f_rng != NULL );

    /*
     * In the past our key generation aimed for an error rate of at most
     * 2^-80. Since this function is deprecated, aim for the same certainty
     * here as well.
     */
    return( ssv_mbedtls_mpi_is_prime_ext( X, 40, f_rng, p_rng ) );
}
#endif

/*
 * Prime number generation
 *
 * To generate an RSA key in a way recommended by FIPS 186-4, both primes must
 * be either 1024 bits or 1536 bits long, and flags must contain
 * MBEDTLS_MPI_GEN_PRIME_FLAG_LOW_ERR.
 */
int ssv_mbedtls_mpi_gen_prime( ssv_mbedtls_mpi *X, size_t nbits, int flags,
                   int (*f_rng)(void *, unsigned char *, size_t),
                   void *p_rng )
{
#ifdef MBEDTLS_HAVE_INT64
// ceil(2^63.5)
#define CEIL_MAXUINT_DIV_SQRT2 0xb504f333f9de6485ULL
#else
// ceil(2^31.5)
#define CEIL_MAXUINT_DIV_SQRT2 0xb504f334U
#endif
    int ret = SSV_MBEDTLS_ERR_MPI_NOT_ACCEPTABLE;
    size_t k, n;
    int rounds;
    ssv_mbedtls_mpi_uint r;
    ssv_mbedtls_mpi Y;

    MPI_VALIDATE_RET( X     != NULL );
    MPI_VALIDATE_RET( f_rng != NULL );

    if( nbits < 3 || nbits > SSV_MBEDTLS_MPI_MAX_BITS )
        return( SSV_MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    ssv_mbedtls_mpi_init( &Y );

    n = BITS_TO_LIMBS( nbits );

    if( ( flags & SSV_MBEDTLS_MPI_GEN_PRIME_FLAG_LOW_ERR ) == 0 )
    {
        /*
         * 2^-80 error probability, number of rounds chosen per HAC, table 4.4
         */
        rounds = ( ( nbits >= 1300 ) ?  2 : ( nbits >=  850 ) ?  3 :
                   ( nbits >=  650 ) ?  4 : ( nbits >=  350 ) ?  8 :
                   ( nbits >=  250 ) ? 12 : ( nbits >=  150 ) ? 18 : 27 );
    }
    else
    {
        /*
         * 2^-100 error probability, number of rounds computed based on HAC,
         * fact 4.48
         */
        rounds = ( ( nbits >= 1450 ) ?  4 : ( nbits >=  1150 ) ?  5 :
                   ( nbits >= 1000 ) ?  6 : ( nbits >=   850 ) ?  7 :
                   ( nbits >=  750 ) ?  8 : ( nbits >=   500 ) ? 13 :
                   ( nbits >=  250 ) ? 28 : ( nbits >=   150 ) ? 40 : 51 );
    }

    while( 1 )
    {
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_fill_random( X, n * ciL, f_rng, p_rng ) );
        /* make sure generated number is at least (nbits-1)+0.5 bits (FIPS 186-4 §B.3.3 steps 4.4, 5.5) */
        if( X->p[n-1] < CEIL_MAXUINT_DIV_SQRT2 ) continue;

        k = n * biL;
        if( k > nbits ) SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( X, k - nbits ) );
        X->p[0] |= 1;

        if( ( flags & SSV_MBEDTLS_MPI_GEN_PRIME_FLAG_DH ) == 0 )
        {
            ret = ssv_mbedtls_mpi_is_prime_ext( X, rounds, f_rng, p_rng );

            if( ret != SSV_MBEDTLS_ERR_MPI_NOT_ACCEPTABLE )
                goto cleanup;
        }
        else
        {
            /*
             * An necessary condition for Y and X = 2Y + 1 to be prime
             * is X = 2 mod 3 (which is equivalent to Y = 2 mod 3).
             * Make sure it is satisfied, while keeping X = 3 mod 4
             */

            X->p[0] |= 2;

            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_mod_int( &r, X, 3 ) );
            if( r == 0 )
                SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_add_int( X, X, 8 ) );
            else if( r == 1 )
                SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_add_int( X, X, 4 ) );

            /* Set Y = (X-1) / 2, which is X / 2 because X is odd */
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_copy( &Y, X ) );
            SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_shift_r( &Y, 1 ) );

            while( 1 )
            {
                /*
                 * First, check small factors for X and Y
                 * before doing Miller-Rabin on any of them
                 */
                if( ( ret = mpi_check_small_factors(  X         ) ) == 0 &&
                    ( ret = mpi_check_small_factors( &Y         ) ) == 0 &&
                    ( ret = mpi_miller_rabin(  X, rounds, f_rng, p_rng  ) )
                                                                    == 0 &&
                    ( ret = mpi_miller_rabin( &Y, rounds, f_rng, p_rng  ) )
                                                                    == 0 )
                    goto cleanup;

                if( ret != SSV_MBEDTLS_ERR_MPI_NOT_ACCEPTABLE )
                    goto cleanup;

                /*
                 * Next candidates. We want to preserve Y = (X-1) / 2 and
                 * Y = 1 mod 2 and Y = 2 mod 3 (eq X = 3 mod 4 and X = 2 mod 3)
                 * so up Y by 6 and X by 12.
                 */
                SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_add_int(  X,  X, 12 ) );
                SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_add_int( &Y, &Y, 6  ) );
            }
        }
    }

cleanup:

    ssv_mbedtls_mpi_free( &Y );

    return( ret );
}

#endif /* MBEDTLS_GENPRIME */

#if defined(MBEDTLS_SELF_TEST)

#define GCD_PAIR_COUNT  3

static const int gcd_pairs[GCD_PAIR_COUNT][3] =
{
    { 693, 609, 21 },
    { 1764, 868, 28 },
    { 768454923, 542167814, 1 }
};

/*
 * Checkup routine
 */
int ssv_mbedtls_mpi_self_test( int verbose )
{
    int ret, i;
    ssv_mbedtls_mpi A, E, N, X, Y, U, V;

    ssv_mbedtls_mpi_init( &A ); ssv_mbedtls_mpi_init( &E ); ssv_mbedtls_mpi_init( &N ); ssv_mbedtls_mpi_init( &X );
    ssv_mbedtls_mpi_init( &Y ); ssv_mbedtls_mpi_init( &U ); ssv_mbedtls_mpi_init( &V );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_read_string( &A, 16,
        "EFE021C2645FD1DC586E69184AF4A31E" \
        "D5F53E93B5F123FA41680867BA110131" \
        "944FE7952E2517337780CB0DB80E61AA" \
        "E7C8DDC6C5C6AADEB34EB38A2F40D5E6" ) );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_read_string( &E, 16,
        "B2E7EFD37075B9F03FF989C7C5051C20" \
        "34D2A323810251127E7BF8625A4F49A5" \
        "F3E27F4DA8BD59C47D6DAABA4C8127BD" \
        "5B5C25763222FEFCCFC38B832366C29E" ) );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_read_string( &N, 16,
        "0066A198186C18C10B2F5ED9B522752A" \
        "9830B69916E535C8F047518A889A43A5" \
        "94B6BED27A168D31D4A52F88925AA8F5" ) );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_mul_mpi( &X, &A, &N ) );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_read_string( &U, 16,
        "602AB7ECA597A3D6B56FF9829A5E8B85" \
        "9E857EA95A03512E2BAE7391688D264A" \
        "A5663B0341DB9CCFD2C4C5F421FEC814" \
        "8001B72E848A38CAE1C65F78E56ABDEF" \
        "E12D3C039B8A02D6BE593F0BBBDA56F1" \
        "ECF677152EF804370C1A305CAF3B5BF1" \
        "30879B56C61DE584A0F53A2447A51E" ) );

    if( verbose != 0 )
        mbedtls_printf( "  MPI test #1 (mul_mpi): " );

    if( ssv_mbedtls_mpi_cmp_mpi( &X, &U ) != 0 )
    {
        if( verbose != 0 )
            mbedtls_printf( "failed\n" );

        ret = 1;
        goto cleanup;
    }

    if( verbose != 0 )
        mbedtls_printf( "passed\n" );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_div_mpi( &X, &Y, &A, &N ) );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_read_string( &U, 16,
        "256567336059E52CAE22925474705F39A94" ) );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_read_string( &V, 16,
        "6613F26162223DF488E9CD48CC132C7A" \
        "0AC93C701B001B092E4E5B9F73BCD27B" \
        "9EE50D0657C77F374E903CDFA4C642" ) );

    if( verbose != 0 )
        mbedtls_printf( "  MPI test #2 (div_mpi): " );

    if( ssv_mbedtls_mpi_cmp_mpi( &X, &U ) != 0 ||
        ssv_mbedtls_mpi_cmp_mpi( &Y, &V ) != 0 )
    {
        if( verbose != 0 )
            mbedtls_printf( "failed\n" );

        ret = 1;
        goto cleanup;
    }

    if( verbose != 0 )
        mbedtls_printf( "passed\n" );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_exp_mod( &X, &A, &E, &N, NULL ) );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_read_string( &U, 16,
        "36E139AEA55215609D2816998ED020BB" \
        "BD96C37890F65171D948E9BC7CBAA4D9" \
        "325D24D6A3C12710F10A09FA08AB87" ) );

    if( verbose != 0 )
        mbedtls_printf( "  MPI test #3 (exp_mod): " );

    if( ssv_mbedtls_mpi_cmp_mpi( &X, &U ) != 0 )
    {
        if( verbose != 0 )
            mbedtls_printf( "failed\n" );

        ret = 1;
        goto cleanup;
    }

    if( verbose != 0 )
        mbedtls_printf( "passed\n" );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_inv_mod( &X, &A, &N ) );

    SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_read_string( &U, 16,
        "003A0AAEDD7E784FC07D8F9EC6E3BFD5" \
        "C3DBA76456363A10869622EAC2DD84EC" \
        "C5B8A74DAC4D09E03B5E0BE779F2DF61" ) );

    if( verbose != 0 )
        mbedtls_printf( "  MPI test #4 (inv_mod): " );

    if( ssv_mbedtls_mpi_cmp_mpi( &X, &U ) != 0 )
    {
        if( verbose != 0 )
            mbedtls_printf( "failed\n" );

        ret = 1;
        goto cleanup;
    }

    if( verbose != 0 )
        mbedtls_printf( "passed\n" );

    if( verbose != 0 )
        mbedtls_printf( "  MPI test #5 (simple gcd): " );

    for( i = 0; i < GCD_PAIR_COUNT; i++ )
    {
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_lset( &X, gcd_pairs[i][0] ) );
        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_lset( &Y, gcd_pairs[i][1] ) );

        SSV_MBEDTLS_MPI_CHK( ssv_mbedtls_mpi_gcd( &A, &X, &Y ) );

        if( ssv_mbedtls_mpi_cmp_int( &A, gcd_pairs[i][2] ) != 0 )
        {
            if( verbose != 0 )
                mbedtls_printf( "failed at %d\n", i );

            ret = 1;
            goto cleanup;
        }
    }

    if( verbose != 0 )
        mbedtls_printf( "passed\n" );

cleanup:

    if( ret != 0 && verbose != 0 )
        mbedtls_printf( "Unexpected error, return code = %08X\n", ret );

    ssv_mbedtls_mpi_free( &A ); ssv_mbedtls_mpi_free( &E ); ssv_mbedtls_mpi_free( &N ); ssv_mbedtls_mpi_free( &X );
    ssv_mbedtls_mpi_free( &Y ); ssv_mbedtls_mpi_free( &U ); ssv_mbedtls_mpi_free( &V );

    if( verbose != 0 )
        mbedtls_printf( "\n" );

    return( ret );
}

#endif /* MBEDTLS_SELF_TEST */

