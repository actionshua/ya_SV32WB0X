#line 2 "suites/main_test.function"
/*
 * *** THIS FILE HAS BEEN MACHINE GENERATED ***
 *
 * This file has been machine generated using the script:
 * generate_test_code.py
 *
 * Test file      : ./test_suite_aes.ofb.c
 *
 * The following files were used to create this file.
 *
 *      Main code file      : suites/main_test.function
 *      Platform code file  : suites/host_test.function
 *      Helper file         : suites/helpers.function
 *      Test suite file     : suites/test_suite_aes.function
 *      Test suite data     : suites/test_suite_aes.ofb.data
 *
 *
 *  This file is part of Mbed TLS (https://tls.mbed.org)
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include <mbedtls/config.h>
#else
#include MBEDTLS_CONFIG_FILE
#endif


/*----------------------------------------------------------------------------*/
/* Common helper code */

#line 2 "suites/helpers.function"
/*----------------------------------------------------------------------------*/
/* Headers */

#include <stdlib.h>

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#define mbedtls_fprintf    fprintf
#define mbedtls_snprintf   snprintf
#define mbedtls_calloc     calloc
#define mbedtls_free       free
#define mbedtls_exit       exit
#define mbedtls_time       time
#define mbedtls_time_t     time_t
#define MBEDTLS_EXIT_SUCCESS EXIT_SUCCESS
#define MBEDTLS_EXIT_FAILURE EXIT_FAILURE
#endif

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
#include "mbedtls/memory_buffer_alloc.h"
#endif

#if defined(MBEDTLS_CHECK_PARAMS)
#include "mbedtls/platform_util.h"
#include <setjmp.h>
#endif

#ifdef _MSC_VER
#include <basetsd.h>
typedef UINT8 uint8_t;
typedef INT32 int32_t;
typedef UINT32 uint32_t;
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#else
#include <stdint.h>
#endif

#include <string.h>
#undef __unix__
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h>
#include <strings.h>
#endif

/* Type for Hex parameters */
typedef struct data_tag
{
    uint8_t *   x;
    uint32_t    len;
} data_t;

/*----------------------------------------------------------------------------*/
/* Status and error constants */

#define DEPENDENCY_SUPPORTED            0   /* Dependency supported by build */
#define KEY_VALUE_MAPPING_FOUND         0   /* Integer expression found */
#define DISPATCH_TEST_SUCCESS           0   /* Test dispatch successful */

#define KEY_VALUE_MAPPING_NOT_FOUND     -1  /* Integer expression not found */
#define DEPENDENCY_NOT_SUPPORTED        -2  /* Dependency not supported */
#define DISPATCH_TEST_FN_NOT_FOUND      -3  /* Test function not found */
#define DISPATCH_INVALID_TEST_DATA      -4  /* Invalid test parameter type.
                                               Only int, string, binary data
                                               and integer expressions are
                                               allowed */
#define DISPATCH_UNSUPPORTED_SUITE      -5  /* Test suite not supported by the
                                               build */

typedef enum
{
    PARAMFAIL_TESTSTATE_IDLE = 0,           /* No parameter failure call test */
    PARAMFAIL_TESTSTATE_PENDING,            /* Test call to the parameter failure
                                             * is pending */
    PARAMFAIL_TESTSTATE_CALLED              /* The test call to the parameter
                                             * failure function has been made */
} paramfail_test_state_t;


/*----------------------------------------------------------------------------*/
/* Macros */

/**
 * \brief   This macro tests the expression passed to it as a test step or
 *          individual test in a test case.
 *
 *          It allows a library function to return a value and return an error
 *          code that can be tested.
 *
 *          When MBEDTLS_CHECK_PARAMS is enabled, calls to the parameter failure
 *          callback, MBEDTLS_PARAM_FAILED(), will be assumed to be a test
 *          failure.
 *
 *          This macro is not suitable for negative parameter validation tests,
 *          as it assumes the test step will not create an error.
 *
 * \param   TEST    The test expression to be tested.
 */
#define TEST_ASSERT( TEST )                                 \
    do {                                                    \
       if( ! (TEST) )                                       \
       {                                                    \
          test_fail( #TEST, __LINE__, __FILE__ );           \
          goto exit;                                        \
       }                                                    \
    } while( 0 )

#if defined(MBEDTLS_CHECK_PARAMS) && !defined(MBEDTLS_PARAM_FAILED_ALT)
/**
 * \brief   This macro tests the statement passed to it as a test step or
 *          individual test in a test case. The macro assumes the test will fail
 *          and will generate an error.
 *
 *          It allows a library function to return a value and tests the return
 *          code on return to confirm the given error code was returned.
 *
 *          When MBEDTLS_CHECK_PARAMS is enabled, calls to the parameter failure
 *          callback, MBEDTLS_PARAM_FAILED(), are assumed to indicate the
 *          expected failure, and the test will pass.
 *
 *          This macro is intended for negative parameter validation tests,
 *          where the failing function may return an error value or call
 *          MBEDTLS_PARAM_FAILED() to indicate the error.
 *
 * \param   PARAM_ERROR_VALUE   The expected error code.
 *
 * \param   TEST                The test expression to be tested.
 */
#define TEST_INVALID_PARAM_RET( PARAM_ERR_VALUE, TEST )                     \
    do {                                                                    \
        test_info.paramfail_test_state = PARAMFAIL_TESTSTATE_PENDING;       \
        if( (TEST) != (PARAM_ERR_VALUE) ||                                  \
            test_info.paramfail_test_state != PARAMFAIL_TESTSTATE_CALLED )  \
        {                                                                   \
            test_fail( #TEST, __LINE__, __FILE__ );                         \
            goto exit;                                                      \
        }                                                                   \
   } while( 0 )

/**
 * \brief   This macro tests the statement passed to it as a test step or
 *          individual test in a test case. The macro assumes the test will fail
 *          and will generate an error.
 *
 *          It assumes the library function under test cannot return a value and
 *          assumes errors can only be indicated byt calls to
 *          MBEDTLS_PARAM_FAILED().
 *
 *          When MBEDTLS_CHECK_PARAMS is enabled, calls to the parameter failure
 *          callback, MBEDTLS_PARAM_FAILED(), are assumed to indicate the
 *          expected failure. If MBEDTLS_CHECK_PARAMS is not enabled, no test
 *          can be made.
 *
 *          This macro is intended for negative parameter validation tests,
 *          where the failing function can only return an error by calling
 *          MBEDTLS_PARAM_FAILED() to indicate the error.
 *
 * \param   TEST                The test expression to be tested.
 */
#define TEST_INVALID_PARAM( TEST )                                          \
    do {                                                                    \
        memcpy(jmp_tmp, param_fail_jmp, sizeof(jmp_buf));                   \
        if( setjmp( param_fail_jmp ) == 0 )                                 \
        {                                                                   \
            TEST;                                                           \
            test_fail( #TEST, __LINE__, __FILE__ );                         \
            goto exit;                                                      \
        }                                                                   \
        memcpy(param_fail_jmp, jmp_tmp, sizeof(jmp_buf));                   \
    } while( 0 )
#endif /* MBEDTLS_CHECK_PARAMS && !MBEDTLS_PARAM_FAILED_ALT */

/**
 * \brief   This macro tests the statement passed to it as a test step or
 *          individual test in a test case. The macro assumes the test will not fail.
 *
 *          It assumes the library function under test cannot return a value and
 *          assumes errors can only be indicated by calls to
 *          MBEDTLS_PARAM_FAILED().
 *
 *          When MBEDTLS_CHECK_PARAMS is enabled, calls to the parameter failure
 *          callback, MBEDTLS_PARAM_FAILED(), are assumed to indicate the
 *          expected failure. If MBEDTLS_CHECK_PARAMS is not enabled, no test
 *          can be made.
 *
 *          This macro is intended to test that functions returning void
 *          accept all of the parameter values they're supposed to accept - eg
 *          that they don't call MBEDTLS_PARAM_FAILED() when a parameter
 *          that's allowed to be NULL happens to be NULL.
 *
 *          Note: for functions that return something other that void,
 *          checking that they accept all the parameters they're supposed to
 *          accept is best done by using TEST_ASSERT() and checking the return
 *          value as well.
 *
 *          Note: this macro is available even when #MBEDTLS_CHECK_PARAMS is
 *          disabled, as it makes sense to check that the functions accept all
 *          legal values even if this option is disabled - only in that case,
 *          the test is more about whether the function segfaults than about
 *          whether it invokes MBEDTLS_PARAM_FAILED().
 *
 * \param   TEST                The test expression to be tested.
 */
#define TEST_VALID_PARAM( TEST )                                    \
    TEST_ASSERT( ( TEST, 1 ) );

#define assert(a) if( !( a ) )                                      \
{                                                                   \
    mbedtls_fprintf( stderr, "Assertion Failed at %s:%d - %s\n",   \
                             __FILE__, __LINE__, #a );              \
    mbedtls_exit( 1 );                                             \
}

/*
 * 32-bit integer manipulation macros (big endian)
 */
#ifndef GET_UINT32_BE
#define GET_UINT32_BE(n,b,i)                            \
{                                                       \
    (n) = ( (uint32_t) (b)[(i)    ] << 24 )             \
        | ( (uint32_t) (b)[(i) + 1] << 16 )             \
        | ( (uint32_t) (b)[(i) + 2] <<  8 )             \
        | ( (uint32_t) (b)[(i) + 3]       );            \
}
#endif

#ifndef PUT_UINT32_BE
#define PUT_UINT32_BE(n,b,i)                            \
{                                                       \
    (b)[(i)    ] = (unsigned char) ( (n) >> 24 );       \
    (b)[(i) + 1] = (unsigned char) ( (n) >> 16 );       \
    (b)[(i) + 2] = (unsigned char) ( (n) >>  8 );       \
    (b)[(i) + 3] = (unsigned char) ( (n)       );       \
}
#endif


/*----------------------------------------------------------------------------*/
/* Global variables */

static struct
{
    paramfail_test_state_t paramfail_test_state;
    int failed;
    const char *test;
    const char *filename;
    int line_no;
}
test_info;

#if defined(MBEDTLS_PLATFORM_C)
mbedtls_platform_context platform_ctx;
#endif

#if defined(MBEDTLS_CHECK_PARAMS)
jmp_buf param_fail_jmp;
jmp_buf jmp_tmp;
#endif

/*----------------------------------------------------------------------------*/
/* Helper flags for complex dependencies */

/* Indicates whether we expect mbedtls_entropy_init
 * to initialize some strong entropy source. */
#if defined(MBEDTLS_TEST_NULL_ENTROPY) ||             \
    ( !defined(MBEDTLS_NO_DEFAULT_ENTROPY_SOURCES) && \
      ( !defined(MBEDTLS_NO_PLATFORM_ENTROPY)  ||     \
         defined(MBEDTLS_HAVEGE_C)             ||     \
         defined(MBEDTLS_ENTROPY_HARDWARE_ALT) ||     \
         defined(ENTROPY_NV_SEED) ) )
#define ENTROPY_HAVE_STRONG
#endif


/*----------------------------------------------------------------------------*/
/* Helper Functions */

static void test_fail( const char *test, int line_no, const char* filename )
{
    test_info.failed = 1;
    test_info.test = test;
    test_info.line_no = line_no;
    test_info.filename = filename;
}

static int platform_setup()
{
    int ret = 0;
#if defined(MBEDTLS_PLATFORM_C)
    ret = mbedtls_platform_setup( &platform_ctx );
#endif /* MBEDTLS_PLATFORM_C */
    return( ret );
}

static void platform_teardown()
{
#if defined(MBEDTLS_PLATFORM_C)
    mbedtls_platform_teardown( &platform_ctx );
#endif /* MBEDTLS_PLATFORM_C */
}

#if defined(MBEDTLS_CHECK_PARAMS)
void mbedtls_param_failed( const char *failure_condition,
                           const char *file,
                           int line )
{
    /* If we are testing the callback function...  */
    if( test_info.paramfail_test_state == PARAMFAIL_TESTSTATE_PENDING )
    {
        test_info.paramfail_test_state = PARAMFAIL_TESTSTATE_CALLED;
    }
    else
    {
        /* ...else we treat this as an error */

        /* Record the location of the failure, but not as a failure yet, in case
         * it was part of the test */
        test_fail( failure_condition, line, file );
        test_info.failed = 0;

        longjmp( param_fail_jmp, 1 );
    }
}
#endif

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
static int redirect_output( FILE** out_stream, const char* path )
{
    int stdout_fd = dup( fileno( *out_stream ) );

    if( stdout_fd == -1 )
    {
        return -1;
    }

    fflush( *out_stream );
    fclose( *out_stream );
    *out_stream = fopen( path, "w" );

    if( *out_stream == NULL )
    {
        return -1;
    }

    return stdout_fd;
}

static int restore_output( FILE** out_stream, int old_fd )
{
    fflush( *out_stream );
    fclose( *out_stream );

    *out_stream = fdopen( old_fd, "w" );
    if( *out_stream == NULL )
    {
        return -1;
    }

    return 0;
}

static void close_output( FILE* out_stream )
{
    fclose( out_stream );
}
#endif /* __unix__ || __APPLE__ __MACH__ */

static int unhexify( unsigned char *obuf, const char *ibuf )
{
    unsigned char c, c2;
    int len = strlen( ibuf ) / 2;
    assert( strlen( ibuf ) % 2 == 0 ); /* must be even number of bytes */

    while( *ibuf != 0 )
    {
        c = *ibuf++;
        if( c >= '0' && c <= '9' )
            c -= '0';
        else if( c >= 'a' && c <= 'f' )
            c -= 'a' - 10;
        else if( c >= 'A' && c <= 'F' )
            c -= 'A' - 10;
        else
            assert( 0 );

        c2 = *ibuf++;
        if( c2 >= '0' && c2 <= '9' )
            c2 -= '0';
        else if( c2 >= 'a' && c2 <= 'f' )
            c2 -= 'a' - 10;
        else if( c2 >= 'A' && c2 <= 'F' )
            c2 -= 'A' - 10;
        else
            assert( 0 );

        *obuf++ = ( c << 4 ) | c2;
    }

    return len;
}

static void hexify( unsigned char *obuf, const unsigned char *ibuf, int len )
{
    unsigned char l, h;

    while( len != 0 )
    {
        h = *ibuf / 16;
        l = *ibuf % 16;

        if( h < 10 )
            *obuf++ = '0' + h;
        else
            *obuf++ = 'a' + h - 10;

        if( l < 10 )
            *obuf++ = '0' + l;
        else
            *obuf++ = 'a' + l - 10;

        ++ibuf;
        len--;
    }
}

/**
 * Allocate and zeroize a buffer.
 *
 * If the size if zero, a pointer to a zeroized 1-byte buffer is returned.
 *
 * For convenience, dies if allocation fails.
 */
static unsigned char *zero_alloc( size_t len )
{
    void *p;
    size_t actual_len = ( len != 0 ) ? len : 1;

    p = mbedtls_calloc( 1, actual_len );
    assert( p != NULL );

    memset( p, 0x00, actual_len );

    return( p );
}

/**
 * Allocate and fill a buffer from hex data.
 *
 * The buffer is sized exactly as needed. This allows to detect buffer
 * overruns (including overreads) when running the test suite under valgrind.
 *
 * If the size if zero, a pointer to a zeroized 1-byte buffer is returned.
 *
 * For convenience, dies if allocation fails.
 */
static unsigned char *unhexify_alloc( const char *ibuf, size_t *olen )
{
    unsigned char *obuf;

    *olen = strlen( ibuf ) / 2;

    if( *olen == 0 )
        return( zero_alloc( *olen ) );

    obuf = mbedtls_calloc( 1, *olen );
    assert( obuf != NULL );

    (void) unhexify( obuf, ibuf );

    return( obuf );
}

/**
 * This function just returns data from rand().
 * Although predictable and often similar on multiple
 * runs, this does not result in identical random on
 * each run. So do not use this if the results of a
 * test depend on the random data that is generated.
 *
 * rng_state shall be NULL.
 */
static int rnd_std_rand( void *rng_state, unsigned char *output, size_t len )
{
#if !defined(__OpenBSD__)
    size_t i;

    if( rng_state != NULL )
        rng_state  = NULL;

    for( i = 0; i < len; ++i )
        output[i] = rand();
#else
    if( rng_state != NULL )
        rng_state = NULL;

    arc4random_buf( output, len );
#endif /* !OpenBSD */

    return( 0 );
}

/**
 * This function only returns zeros
 *
 * rng_state shall be NULL.
 */
static int rnd_zero_rand( void *rng_state, unsigned char *output, size_t len )
{
    if( rng_state != NULL )
        rng_state  = NULL;

    memset( output, 0, len );

    return( 0 );
}

typedef struct
{
    unsigned char *buf;
    size_t length;
} rnd_buf_info;

/**
 * This function returns random based on a buffer it receives.
 *
 * rng_state shall be a pointer to a rnd_buf_info structure.
 *
 * The number of bytes released from the buffer on each call to
 * the random function is specified by per_call. (Can be between
 * 1 and 4)
 *
 * After the buffer is empty it will return rand();
 */
static int rnd_buffer_rand( void *rng_state, unsigned char *output, size_t len )
{
    rnd_buf_info *info = (rnd_buf_info *) rng_state;
    size_t use_len;

    if( rng_state == NULL )
        return( rnd_std_rand( NULL, output, len ) );

    use_len = len;
    if( len > info->length )
        use_len = info->length;

    if( use_len )
    {
        memcpy( output, info->buf, use_len );
        info->buf += use_len;
        info->length -= use_len;
    }

    if( len - use_len > 0 )
        return( rnd_std_rand( NULL, output + use_len, len - use_len ) );

    return( 0 );
}

/**
 * Info structure for the pseudo random function
 *
 * Key should be set at the start to a test-unique value.
 * Do not forget endianness!
 * State( v0, v1 ) should be set to zero.
 */
typedef struct
{
    uint32_t key[16];
    uint32_t v0, v1;
} rnd_pseudo_info;

/**
 * This function returns random based on a pseudo random function.
 * This means the results should be identical on all systems.
 * Pseudo random is based on the XTEA encryption algorithm to
 * generate pseudorandom.
 *
 * rng_state shall be a pointer to a rnd_pseudo_info structure.
 */
static int rnd_pseudo_rand( void *rng_state, unsigned char *output, size_t len )
{
    rnd_pseudo_info *info = (rnd_pseudo_info *) rng_state;
    uint32_t i, *k, sum, delta=0x9E3779B9;
    unsigned char result[4], *out = output;

    if( rng_state == NULL )
        return( rnd_std_rand( NULL, output, len ) );

    k = info->key;

    while( len > 0 )
    {
        size_t use_len = ( len > 4 ) ? 4 : len;
        sum = 0;

        for( i = 0; i < 32; i++ )
        {
            info->v0 += ( ( ( info->v1 << 4 ) ^ ( info->v1 >> 5 ) )
                            + info->v1 ) ^ ( sum + k[sum & 3] );
            sum += delta;
            info->v1 += ( ( ( info->v0 << 4 ) ^ ( info->v0 >> 5 ) )
                            + info->v0 ) ^ ( sum + k[( sum>>11 ) & 3] );
        }

        PUT_UINT32_BE( info->v0, result, 0 );
        memcpy( out, result, use_len );
        len -= use_len;
        out += 4;
    }

    return( 0 );
}

static int hexcmp( uint8_t * a, uint8_t * b, uint32_t a_len, uint32_t b_len )
{
    int ret = 0;
    uint32_t i = 0;

    if( a_len != b_len )
        return( -1 );

    for( i = 0; i < a_len; i++ )
    {
        if( a[i] != b[i] )
        {
            ret = -1;
            break;
        }
    }
    return ret;
}


#line 35 "suites/main_test.function"


/*----------------------------------------------------------------------------*/
/* Test Suite Code */


#define TEST_SUITE_ACTIVE

#if defined(MBEDTLS_AES_C)
#line 2 "suites/test_suite_aes.function"
#include "mbedtls/aes.h"
#line 11 "suites/test_suite_aes.function"
static void test_aes_encrypt_ecb( data_t * key_str, data_t * src_str,
                      data_t * hex_dst_string, int setkey_result )
{
    unsigned char output[100];
    mbedtls_aes_context ctx;

    memset(output, 0x00, 100);

    mbedtls_aes_init( &ctx );

    TEST_ASSERT( mbedtls_aes_setkey_enc( &ctx, key_str->x, key_str->len * 8 ) == setkey_result );
    if( setkey_result == 0 )
    {
        TEST_ASSERT( mbedtls_aes_crypt_ecb( &ctx, MBEDTLS_AES_ENCRYPT, src_str->x, output ) == 0 );

        TEST_ASSERT( hexcmp( output, hex_dst_string->x, 16, hex_dst_string->len ) == 0 );
    }

exit:
    mbedtls_aes_free( &ctx );
}

static void test_aes_encrypt_ecb_wrapper( void ** params )
{
    data_t data0 = {(uint8_t *) params[0], *( (uint32_t *) params[1] )};
    data_t data2 = {(uint8_t *) params[2], *( (uint32_t *) params[3] )};
    data_t data4 = {(uint8_t *) params[4], *( (uint32_t *) params[5] )};

    test_aes_encrypt_ecb( &data0, &data2, &data4, *( (int *) params[6] ) );
}
#line 35 "suites/test_suite_aes.function"
static void test_aes_decrypt_ecb( data_t * key_str, data_t * src_str,
                      data_t * hex_dst_string, int setkey_result )
{
    unsigned char output[100];
    mbedtls_aes_context ctx;

    memset(output, 0x00, 100);

    mbedtls_aes_init( &ctx );

    TEST_ASSERT( mbedtls_aes_setkey_dec( &ctx, key_str->x, key_str->len * 8 ) == setkey_result );
    if( setkey_result == 0 )
    {
        TEST_ASSERT( mbedtls_aes_crypt_ecb( &ctx, MBEDTLS_AES_DECRYPT, src_str->x, output ) == 0 );

        TEST_ASSERT( hexcmp( output, hex_dst_string->x, 16, hex_dst_string->len ) == 0 );
    }

exit:
    mbedtls_aes_free( &ctx );
}

static void test_aes_decrypt_ecb_wrapper( void ** params )
{
    data_t data0 = {(uint8_t *) params[0], *( (uint32_t *) params[1] )};
    data_t data2 = {(uint8_t *) params[2], *( (uint32_t *) params[3] )};
    data_t data4 = {(uint8_t *) params[4], *( (uint32_t *) params[5] )};

    test_aes_decrypt_ecb( &data0, &data2, &data4, *( (int *) params[6] ) );
}
#if defined(MBEDTLS_CIPHER_MODE_CBC)
#line 59 "suites/test_suite_aes.function"
static void test_aes_encrypt_cbc( data_t * key_str, data_t * iv_str,
                      data_t * src_str, data_t * hex_dst_string,
                      int cbc_result )
{
    unsigned char output[100];
    mbedtls_aes_context ctx;

    memset(output, 0x00, 100);

    mbedtls_aes_init( &ctx );

    mbedtls_aes_setkey_enc( &ctx, key_str->x, key_str->len * 8 );
    TEST_ASSERT( mbedtls_aes_crypt_cbc( &ctx, MBEDTLS_AES_ENCRYPT, src_str->len, iv_str->x, src_str->x, output ) == cbc_result );
    if( cbc_result == 0 )
    {

        TEST_ASSERT( hexcmp( output, hex_dst_string->x, src_str->len, hex_dst_string->len ) == 0 );
    }

exit:
    mbedtls_aes_free( &ctx );
}

static void test_aes_encrypt_cbc_wrapper( void ** params )
{
    data_t data0 = {(uint8_t *) params[0], *( (uint32_t *) params[1] )};
    data_t data2 = {(uint8_t *) params[2], *( (uint32_t *) params[3] )};
    data_t data4 = {(uint8_t *) params[4], *( (uint32_t *) params[5] )};
    data_t data6 = {(uint8_t *) params[6], *( (uint32_t *) params[7] )};

    test_aes_encrypt_cbc( &data0, &data2, &data4, &data6, *( (int *) params[8] ) );
}
#endif /* MBEDTLS_CIPHER_MODE_CBC */
#if defined(MBEDTLS_CIPHER_MODE_CBC)
#line 84 "suites/test_suite_aes.function"
static void test_aes_decrypt_cbc( data_t * key_str, data_t * iv_str,
                      data_t * src_str, data_t * hex_dst_string,
                      int cbc_result )
{
    unsigned char output[100];
    mbedtls_aes_context ctx;

    memset(output, 0x00, 100);
    mbedtls_aes_init( &ctx );

    mbedtls_aes_setkey_dec( &ctx, key_str->x, key_str->len * 8 );
    TEST_ASSERT( mbedtls_aes_crypt_cbc( &ctx, MBEDTLS_AES_DECRYPT, src_str->len, iv_str->x, src_str->x, output ) == cbc_result );
    if( cbc_result == 0)
    {

        TEST_ASSERT( hexcmp( output, hex_dst_string->x, src_str->len, hex_dst_string->len ) == 0 );
    }

exit:
    mbedtls_aes_free( &ctx );
}

static void test_aes_decrypt_cbc_wrapper( void ** params )
{
    data_t data0 = {(uint8_t *) params[0], *( (uint32_t *) params[1] )};
    data_t data2 = {(uint8_t *) params[2], *( (uint32_t *) params[3] )};
    data_t data4 = {(uint8_t *) params[4], *( (uint32_t *) params[5] )};
    data_t data6 = {(uint8_t *) params[6], *( (uint32_t *) params[7] )};

    test_aes_decrypt_cbc( &data0, &data2, &data4, &data6, *( (int *) params[8] ) );
}
#endif /* MBEDTLS_CIPHER_MODE_CBC */
#if defined(MBEDTLS_CIPHER_MODE_XTS)
#line 108 "suites/test_suite_aes.function"
static void test_aes_encrypt_xts( char *hex_key_string, char *hex_data_unit_string,
                      char *hex_src_string, char *hex_dst_string )
{
    enum { AES_BLOCK_SIZE = 16 };
    unsigned char *data_unit = NULL;
    unsigned char *key = NULL;
    unsigned char *src = NULL;
    unsigned char *dst = NULL;
    unsigned char *output = NULL;
    mbedtls_aes_xts_context ctx;
    size_t key_len, src_len, dst_len, data_unit_len;

    mbedtls_aes_xts_init( &ctx );

    data_unit = unhexify_alloc( hex_data_unit_string, &data_unit_len );
    TEST_ASSERT( data_unit_len == AES_BLOCK_SIZE );

    key = unhexify_alloc( hex_key_string, &key_len );
    TEST_ASSERT( key_len % 2 == 0 );

    src = unhexify_alloc( hex_src_string, &src_len );
    dst = unhexify_alloc( hex_dst_string, &dst_len );
    TEST_ASSERT( src_len == dst_len );

    output = zero_alloc( dst_len );

    TEST_ASSERT( mbedtls_aes_xts_setkey_enc( &ctx, key, key_len * 8 ) == 0 );
    TEST_ASSERT( mbedtls_aes_crypt_xts( &ctx, MBEDTLS_AES_ENCRYPT, src_len,
                                        data_unit, src, output ) == 0 );

    TEST_ASSERT( memcmp( output, dst, dst_len ) == 0 );

exit:
    mbedtls_aes_xts_free( &ctx );
    mbedtls_free( data_unit );
    mbedtls_free( key );
    mbedtls_free( src );
    mbedtls_free( dst );
    mbedtls_free( output );
}

static void test_aes_encrypt_xts_wrapper( void ** params )
{

    test_aes_encrypt_xts( (char *) params[0], (char *) params[1], (char *) params[2], (char *) params[3] );
}
#endif /* MBEDTLS_CIPHER_MODE_XTS */
#if defined(MBEDTLS_CIPHER_MODE_XTS)
#line 151 "suites/test_suite_aes.function"
static void test_aes_decrypt_xts( char *hex_key_string, char *hex_data_unit_string,
                      char *hex_dst_string, char *hex_src_string )
{
    enum { AES_BLOCK_SIZE = 16 };
    unsigned char *data_unit = NULL;
    unsigned char *key = NULL;
    unsigned char *src = NULL;
    unsigned char *dst = NULL;
    unsigned char *output = NULL;
    mbedtls_aes_xts_context ctx;
    size_t key_len, src_len, dst_len, data_unit_len;

    mbedtls_aes_xts_init( &ctx );

    data_unit = unhexify_alloc( hex_data_unit_string, &data_unit_len );
    TEST_ASSERT( data_unit_len == AES_BLOCK_SIZE );

    key = unhexify_alloc( hex_key_string, &key_len );
    TEST_ASSERT( key_len % 2 == 0 );

    src = unhexify_alloc( hex_src_string, &src_len );
    dst = unhexify_alloc( hex_dst_string, &dst_len );
    TEST_ASSERT( src_len == dst_len );

    output = zero_alloc( dst_len );

    TEST_ASSERT( mbedtls_aes_xts_setkey_dec( &ctx, key, key_len * 8 ) == 0 );
    TEST_ASSERT( mbedtls_aes_crypt_xts( &ctx, MBEDTLS_AES_DECRYPT, src_len,
                                        data_unit, src, output ) == 0 );

    TEST_ASSERT( memcmp( output, dst, dst_len ) == 0 );

exit:
    mbedtls_aes_xts_free( &ctx );
    mbedtls_free( data_unit );
    mbedtls_free( key );
    mbedtls_free( src );
    mbedtls_free( dst );
    mbedtls_free( output );
}

static void test_aes_decrypt_xts_wrapper( void ** params )
{

    test_aes_decrypt_xts( (char *) params[0], (char *) params[1], (char *) params[2], (char *) params[3] );
}
#endif /* MBEDTLS_CIPHER_MODE_XTS */
#if defined(MBEDTLS_CIPHER_MODE_XTS)
#line 194 "suites/test_suite_aes.function"
static void test_aes_crypt_xts_size( int size, int retval )
{
    mbedtls_aes_xts_context ctx;
    const unsigned char src[16] = { 0 };
    unsigned char output[16];
    unsigned char data_unit[16];
    size_t length = size;

    mbedtls_aes_xts_init( &ctx );
    memset( data_unit, 0x00, sizeof( data_unit ) );


    /* Valid pointers are passed for builds with MBEDTLS_CHECK_PARAMS, as
     * otherwise we wouldn't get to the size check we're interested in. */
    TEST_ASSERT( mbedtls_aes_crypt_xts( &ctx, MBEDTLS_AES_ENCRYPT, length, data_unit, src, output ) == retval );
exit:
    ;
}

static void test_aes_crypt_xts_size_wrapper( void ** params )
{

    test_aes_crypt_xts_size( *( (int *) params[0] ), *( (int *) params[1] ) );
}
#endif /* MBEDTLS_CIPHER_MODE_XTS */
#if defined(MBEDTLS_CIPHER_MODE_XTS)
#line 213 "suites/test_suite_aes.function"
void test_aes_crypt_xts_keysize( int size, int retval )
{
    mbedtls_aes_xts_context ctx;
    const unsigned char key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    size_t key_len = size;

    mbedtls_aes_xts_init( &ctx );

    TEST_ASSERT( mbedtls_aes_xts_setkey_enc( &ctx, key, key_len * 8 ) == retval );
    TEST_ASSERT( mbedtls_aes_xts_setkey_dec( &ctx, key, key_len * 8 ) == retval );
exit:
    mbedtls_aes_xts_free( &ctx );
}

static void test_aes_crypt_xts_keysize_wrapper( void ** params )
{

    test_aes_crypt_xts_keysize( *( (int *) params[0] ), *( (int *) params[1] ) );
}
#endif /* MBEDTLS_CIPHER_MODE_XTS */
#if defined(MBEDTLS_CIPHER_MODE_CFB)
#line 230 "suites/test_suite_aes.function"
static void test_aes_encrypt_cfb128( data_t * key_str, data_t * iv_str,
                         data_t * src_str, data_t * hex_dst_string )
{
    unsigned char output[100];
    mbedtls_aes_context ctx;
    size_t iv_offset = 0;

    memset(output, 0x00, 100);
    mbedtls_aes_init( &ctx );


    mbedtls_aes_setkey_enc( &ctx, key_str->x, key_str->len * 8 );
    TEST_ASSERT( mbedtls_aes_crypt_cfb128( &ctx, MBEDTLS_AES_ENCRYPT, 16, &iv_offset, iv_str->x, src_str->x, output ) == 0 );

    TEST_ASSERT( hexcmp( output, hex_dst_string->x, 16, hex_dst_string->len ) == 0 );

exit:
    mbedtls_aes_free( &ctx );
}

static void test_aes_encrypt_cfb128_wrapper( void ** params )
{
    data_t data0 = {(uint8_t *) params[0], *( (uint32_t *) params[1] )};
    data_t data2 = {(uint8_t *) params[2], *( (uint32_t *) params[3] )};
    data_t data4 = {(uint8_t *) params[4], *( (uint32_t *) params[5] )};
    data_t data6 = {(uint8_t *) params[6], *( (uint32_t *) params[7] )};

    test_aes_encrypt_cfb128( &data0, &data2, &data4, &data6 );
}
#endif /* MBEDTLS_CIPHER_MODE_CFB */
#if defined(MBEDTLS_CIPHER_MODE_CFB)
#line 252 "suites/test_suite_aes.function"
static void test_aes_decrypt_cfb128( data_t * key_str, data_t * iv_str,
                         data_t * src_str, data_t * hex_dst_string )
{
    unsigned char output[100];
    mbedtls_aes_context ctx;
    size_t iv_offset = 0;

    memset(output, 0x00, 100);
    mbedtls_aes_init( &ctx );


    mbedtls_aes_setkey_enc( &ctx, key_str->x, key_str->len * 8 );
    TEST_ASSERT( mbedtls_aes_crypt_cfb128( &ctx, MBEDTLS_AES_DECRYPT, 16, &iv_offset, iv_str->x, src_str->x, output ) == 0 );

    TEST_ASSERT( hexcmp( output, hex_dst_string->x, 16, hex_dst_string->len ) == 0 );

exit:
    mbedtls_aes_free( &ctx );
}

static void test_aes_decrypt_cfb128_wrapper( void ** params )
{
    data_t data0 = {(uint8_t *) params[0], *( (uint32_t *) params[1] )};
    data_t data2 = {(uint8_t *) params[2], *( (uint32_t *) params[3] )};
    data_t data4 = {(uint8_t *) params[4], *( (uint32_t *) params[5] )};
    data_t data6 = {(uint8_t *) params[6], *( (uint32_t *) params[7] )};

    test_aes_decrypt_cfb128( &data0, &data2, &data4, &data6 );
}
#endif /* MBEDTLS_CIPHER_MODE_CFB */
#if defined(MBEDTLS_CIPHER_MODE_CFB)
#line 274 "suites/test_suite_aes.function"
static void test_aes_encrypt_cfb8( data_t * key_str, data_t * iv_str,
                       data_t * src_str, data_t * hex_dst_string )
{
    unsigned char output[100];
    mbedtls_aes_context ctx;

    memset(output, 0x00, 100);
    mbedtls_aes_init( &ctx );


    mbedtls_aes_setkey_enc( &ctx, key_str->x, key_str->len * 8 );
    TEST_ASSERT( mbedtls_aes_crypt_cfb8( &ctx, MBEDTLS_AES_ENCRYPT, src_str->len, iv_str->x, src_str->x, output ) == 0 );

    TEST_ASSERT( hexcmp( output, hex_dst_string->x, src_str->len, hex_dst_string->len ) == 0 );

exit:
    mbedtls_aes_free( &ctx );
}

static void test_aes_encrypt_cfb8_wrapper( void ** params )
{
    data_t data0 = {(uint8_t *) params[0], *( (uint32_t *) params[1] )};
    data_t data2 = {(uint8_t *) params[2], *( (uint32_t *) params[3] )};
    data_t data4 = {(uint8_t *) params[4], *( (uint32_t *) params[5] )};
    data_t data6 = {(uint8_t *) params[6], *( (uint32_t *) params[7] )};

    test_aes_encrypt_cfb8( &data0, &data2, &data4, &data6 );
}
#endif /* MBEDTLS_CIPHER_MODE_CFB */
#if defined(MBEDTLS_CIPHER_MODE_CFB)
#line 295 "suites/test_suite_aes.function"
static void test_aes_decrypt_cfb8( data_t * key_str, data_t * iv_str,
                       data_t * src_str, data_t * hex_dst_string )
{
    unsigned char output[100];
    mbedtls_aes_context ctx;

    memset(output, 0x00, 100);
    mbedtls_aes_init( &ctx );


    mbedtls_aes_setkey_enc( &ctx, key_str->x, key_str->len * 8 );
    TEST_ASSERT( mbedtls_aes_crypt_cfb8( &ctx, MBEDTLS_AES_DECRYPT, src_str->len, iv_str->x, src_str->x, output ) == 0 );

    TEST_ASSERT( hexcmp( output, hex_dst_string->x, src_str->len, hex_dst_string->len ) == 0 );

exit:
    mbedtls_aes_free( &ctx );
}

static void test_aes_decrypt_cfb8_wrapper( void ** params )
{
    data_t data0 = {(uint8_t *) params[0], *( (uint32_t *) params[1] )};
    data_t data2 = {(uint8_t *) params[2], *( (uint32_t *) params[3] )};
    data_t data4 = {(uint8_t *) params[4], *( (uint32_t *) params[5] )};
    data_t data6 = {(uint8_t *) params[6], *( (uint32_t *) params[7] )};

    test_aes_decrypt_cfb8( &data0, &data2, &data4, &data6 );
}
#endif /* MBEDTLS_CIPHER_MODE_CFB */
#if defined(MBEDTLS_CIPHER_MODE_OFB)
#line 316 "suites/test_suite_aes.function"
static void test_aes_encrypt_ofb( int fragment_size, char *hex_key_string,
                      char *hex_iv_string, char *hex_src_string,
                      char *hex_dst_string )
{
    unsigned char key_str[32];
    unsigned char iv_str[16];
    unsigned char src_str[64];
    unsigned char dst_str[64];
    unsigned char output[32];
    mbedtls_aes_context ctx;
    size_t iv_offset = 0;
    int in_buffer_len;
    unsigned char* src_str_next;
    int key_len;

    memset( key_str, 0x00, sizeof( key_str ) );
    memset( iv_str, 0x00, sizeof( iv_str ) );
    memset( src_str, 0x00, sizeof( src_str ) );
    memset( dst_str, 0x00, sizeof( dst_str ) );
    memset( output, 0x00, sizeof( output ) );
    mbedtls_aes_init( &ctx );

    TEST_ASSERT( strlen( hex_key_string ) <= ( 32 * 2 ) );
    TEST_ASSERT( strlen( hex_iv_string ) <= ( 16 * 2 ) );
    TEST_ASSERT( strlen( hex_src_string ) <= ( 64 * 2 ) );
    TEST_ASSERT( strlen( hex_dst_string ) <= ( 64 * 2 ) );

    key_len = unhexify( key_str, hex_key_string );
    unhexify( iv_str, hex_iv_string );
    in_buffer_len = unhexify( src_str, hex_src_string );

    TEST_ASSERT( mbedtls_aes_setkey_enc( &ctx, key_str, key_len * 8 ) == 0 );
    src_str_next = src_str;

    while( in_buffer_len > 0 )
    {
        TEST_ASSERT( mbedtls_aes_crypt_ofb( &ctx, fragment_size, &iv_offset,
                                            iv_str, src_str_next, output ) == 0 );

        hexify( dst_str, output, fragment_size );
        TEST_ASSERT( strncmp( (char *) dst_str, hex_dst_string,
                              ( 2 * fragment_size ) ) == 0 );

        in_buffer_len -= fragment_size;
        hex_dst_string += ( fragment_size * 2 );
        src_str_next += fragment_size;

        if( in_buffer_len < fragment_size )
            fragment_size = in_buffer_len;
    }

exit:
    mbedtls_aes_free( &ctx );
}

static void test_aes_encrypt_ofb_wrapper( void ** params )
{

    test_aes_encrypt_ofb( *( (int *) params[0] ), (char *) params[1], (char *) params[2], (char *) params[3], (char *) params[4] );
}
#endif /* MBEDTLS_CIPHER_MODE_OFB */
#if defined(MBEDTLS_CHECK_PARAMS)
#if !defined(MBEDTLS_PARAM_FAILED_ALT)
#line 373 "suites/test_suite_aes.function"
void test_aes_check_params( )
{
    mbedtls_aes_context aes_ctx;
#if defined(MBEDTLS_CIPHER_MODE_XTS)
    mbedtls_aes_xts_context xts_ctx;
#endif
    const unsigned char key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    const unsigned char in[16] = { 0 };
    unsigned char out[16];
    size_t size;
    const int valid_mode = MBEDTLS_AES_ENCRYPT;
    const int invalid_mode = 42;

    TEST_INVALID_PARAM( mbedtls_aes_init( NULL ) );
#if defined(MBEDTLS_CIPHER_MODE_XTS)
    TEST_INVALID_PARAM( mbedtls_aes_xts_init( NULL ) );
#endif

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_setkey_enc( NULL, key, 128 ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_setkey_enc( &aes_ctx, NULL, 128 ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_setkey_dec( NULL, key, 128 ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_setkey_dec( &aes_ctx, NULL, 128 ) );

#if defined(MBEDTLS_CIPHER_MODE_XTS)
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_xts_setkey_enc( NULL, key, 128 ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_xts_setkey_enc( &xts_ctx, NULL, 128 ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_xts_setkey_dec( NULL, key, 128 ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_xts_setkey_dec( &xts_ctx, NULL, 128 ) );
#endif


    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_ecb( NULL,
                                                   valid_mode, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_ecb( &aes_ctx,
                                                   invalid_mode, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_ecb( &aes_ctx,
                                                   valid_mode, NULL, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_ecb( &aes_ctx,
                                                   valid_mode, in, NULL ) );

#if defined(MBEDTLS_CIPHER_MODE_CBC)
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cbc( NULL,
                                                   valid_mode, 16,
                                                   out, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cbc( &aes_ctx,
                                                   invalid_mode, 16,
                                                   out, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cbc( &aes_ctx,
                                                   valid_mode, 16,
                                                   NULL, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cbc( &aes_ctx,
                                                   valid_mode, 16,
                                                   out, NULL, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cbc( &aes_ctx,
                                                   valid_mode, 16,
                                                   out, in, NULL ) );
#endif /* MBEDTLS_CIPHER_MODE_CBC */

#if defined(MBEDTLS_CIPHER_MODE_XTS)
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_xts( NULL,
                                                   valid_mode, 16,
                                                   in, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_xts( &xts_ctx,
                                                   invalid_mode, 16,
                                                   in, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_xts( &xts_ctx,
                                                   valid_mode, 16,
                                                   NULL, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_xts( &xts_ctx,
                                                   valid_mode, 16,
                                                   in, NULL, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_xts( &xts_ctx,
                                                   valid_mode, 16,
                                                   in, in, NULL ) );
#endif /* MBEDTLS_CIPHER_MODE_XTS */

#if defined(MBEDTLS_CIPHER_MODE_CFB)
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cfb128( NULL,
                                                      valid_mode, 16,
                                                      &size, out, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cfb128( &aes_ctx,
                                                      invalid_mode, 16,
                                                      &size, out, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cfb128( &aes_ctx,
                                                      valid_mode, 16,
                                                      NULL, out, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cfb128( &aes_ctx,
                                                      valid_mode, 16,
                                                      &size, NULL, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cfb128( &aes_ctx,
                                                      valid_mode, 16,
                                                      &size, out, NULL, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cfb128( &aes_ctx,
                                                      valid_mode, 16,
                                                      &size, out, in, NULL ) );


    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cfb8( NULL,
                                                    valid_mode, 16,
                                                    out, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cfb8( &aes_ctx,
                                                    invalid_mode, 16,
                                                    out, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cfb8( &aes_ctx,
                                                    valid_mode, 16,
                                                    NULL, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cfb8( &aes_ctx,
                                                    valid_mode, 16,
                                                    out, NULL, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_cfb8( &aes_ctx,
                                                    valid_mode, 16,
                                                    out, in, NULL ) );
#endif /* MBEDTLS_CIPHER_MODE_CFB */

#if defined(MBEDTLS_CIPHER_MODE_OFB)
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_ofb( NULL, 16,
                                                   &size, out, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_ofb( &aes_ctx, 16,
                                                   NULL, out, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_ofb( &aes_ctx, 16,
                                                   &size, NULL, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_ofb( &aes_ctx, 16,
                                                   &size, out, NULL, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_ofb( &aes_ctx, 16,
                                                   &size, out, in, NULL ) );
#endif /* MBEDTLS_CIPHER_MODE_OFB */

#if defined(MBEDTLS_CIPHER_MODE_CTR)
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_ctr( NULL, 16, &size, out,
                                                   out, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_ctr( &aes_ctx, 16, NULL, out,
                                                   out, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_ctr( &aes_ctx, 16, &size, NULL,
                                                   out, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_ctr( &aes_ctx, 16, &size, out,
                                                   NULL, in, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_ctr( &aes_ctx, 16, &size, out,
                                                   out, NULL, out ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_AES_BAD_INPUT_DATA,
                            mbedtls_aes_crypt_ctr( &aes_ctx, 16, &size, out,
                                                   out, in, NULL ) );
#endif /* MBEDTLS_CIPHER_MODE_CTR */
exit:
    ;
}

static void test_aes_check_params_wrapper( void ** params )
{
    (void)params;

    test_aes_check_params(  );
}
#endif /* !MBEDTLS_PARAM_FAILED_ALT */
#endif /* MBEDTLS_CHECK_PARAMS */
#line 564 "suites/test_suite_aes.function"
static void test_aes_misc_params( )
{
#if defined(MBEDTLS_CIPHER_MODE_CBC) || \
    defined(MBEDTLS_CIPHER_MODE_XTS) || \
    defined(MBEDTLS_CIPHER_MODE_CFB) || \
    defined(MBEDTLS_CIPHER_MODE_OFB)
    mbedtls_aes_context aes_ctx;
    const unsigned char in[16] = { 0 };
    unsigned char out[16];
#endif
#if defined(MBEDTLS_CIPHER_MODE_XTS)
    mbedtls_aes_xts_context xts_ctx;
#endif
#if defined(MBEDTLS_CIPHER_MODE_CFB) || \
    defined(MBEDTLS_CIPHER_MODE_OFB)
    size_t size;
#endif

    /* These calls accept NULL */
    TEST_VALID_PARAM( mbedtls_aes_free( NULL ) );
#if defined(MBEDTLS_CIPHER_MODE_XTS)
    TEST_VALID_PARAM( mbedtls_aes_xts_free( NULL ) );
#endif

#if defined(MBEDTLS_CIPHER_MODE_CBC)
    TEST_ASSERT( mbedtls_aes_crypt_cbc( &aes_ctx, MBEDTLS_AES_ENCRYPT,
                                        15,
                                        out, in, out )
                 == MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH );
    TEST_ASSERT( mbedtls_aes_crypt_cbc( &aes_ctx, MBEDTLS_AES_ENCRYPT,
                                        17,
                                        out, in, out )
                 == MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH );
#endif

#if defined(MBEDTLS_CIPHER_MODE_XTS)
    TEST_ASSERT( mbedtls_aes_crypt_xts( &xts_ctx, MBEDTLS_AES_ENCRYPT,
                                        15,
                                        in, in, out )
                 == MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH );
    TEST_ASSERT( mbedtls_aes_crypt_xts( &xts_ctx, MBEDTLS_AES_ENCRYPT,
                                        (1 << 24) + 1,
                                        in, in, out )
                 == MBEDTLS_ERR_AES_INVALID_INPUT_LENGTH );
#endif

#if defined(MBEDTLS_CIPHER_MODE_CFB)
    size = 16;
    TEST_ASSERT( mbedtls_aes_crypt_cfb128( &aes_ctx, MBEDTLS_AES_ENCRYPT, 16,
                                           &size, out, in, out )
                 == MBEDTLS_ERR_AES_BAD_INPUT_DATA );
#endif

#if defined(MBEDTLS_CIPHER_MODE_OFB)
    size = 16;
    TEST_ASSERT( mbedtls_aes_crypt_ofb( &aes_ctx, 16, &size, out, in, out )
                 == MBEDTLS_ERR_AES_BAD_INPUT_DATA );
#endif
exit:
    ;
}

static void test_aes_misc_params_wrapper( void ** params )
{
    (void)params;

    test_aes_misc_params(  );
}
#if defined(MBEDTLS_SELF_TEST)
#line 626 "suites/test_suite_aes.function"
static void test_aes_selftest(  )
{
    TEST_ASSERT( mbedtls_aes_self_test( 1 ) == 0 );
exit:
    ;
}

static void test_aes_selftest_wrapper( void ** params )
{
    (void)params;

    test_aes_selftest(  );
}
#endif /* MBEDTLS_SELF_TEST */
#endif /* MBEDTLS_AES_C */


#line 46 "suites/main_test.function"


/*----------------------------------------------------------------------------*/
/* Test dispatch code */


/**
 * \brief       Evaluates an expression/macro into its literal integer value.
 *              For optimizing space for embedded targets each expression/macro
 *              is identified by a unique identifier instead of string literals.
 *              Identifiers and evaluation code is generated by script:
 *              generate_test_code.py
 *
 * \param exp_id    Expression identifier.
 * \param out_value Pointer to int to hold the integer.
 *
 * \return       0 if exp_id is found. 1 otherwise.
 */
static int get_expression( int32_t exp_id, int32_t * out_value )
{
    int ret = KEY_VALUE_MAPPING_FOUND;

    (void) exp_id;
    (void) out_value;

    switch( exp_id )
    {

#if defined(MBEDTLS_AES_C)

#endif

#line 75 "suites/main_test.function"
        default:
           {
                ret = KEY_VALUE_MAPPING_NOT_FOUND;
           }
           break;
    }
    return( ret );
}


/**
 * \brief       Checks if the dependency i.e. the compile flag is set.
 *              For optimizing space for embedded targets each dependency
 *              is identified by a unique identifier instead of string literals.
 *              Identifiers and check code is generated by script:
 *              generate_test_code.py
 *
 * \param exp_id    Dependency identifier.
 *
 * \return       DEPENDENCY_SUPPORTED if set else DEPENDENCY_NOT_SUPPORTED
 */
static int dep_check( int dep_id )
{
    int ret = DEPENDENCY_NOT_SUPPORTED;

    (void) dep_id;

    switch( dep_id )
    {

#if defined(MBEDTLS_AES_C)

        case 0:
            {
#if defined(MBEDTLS_CIPHER_MODE_OFB)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
#endif

#line 106 "suites/main_test.function"
        default:
            break;
    }
    return( ret );
}


/**
 * \brief       Function pointer type for test function wrappers.
 *
 *
 * \param void **   Pointer to void pointers. Represents an array of test
 *                  function parameters.
 *
 * \return       void
 */
typedef void (*TestWrapper_t)( void ** );


/**
 * \brief       Table of test function wrappers. Used by dispatch_test().
 *              This table is populated by script:
 *              generate_test_code.py
 *
 */
static TestWrapper_t test_funcs[] =
{
/* Function Id: 0 */

#if defined(MBEDTLS_AES_C)
    test_aes_encrypt_ecb_wrapper,
#else
    NULL,
#endif
/* Function Id: 1 */

#if defined(MBEDTLS_AES_C)
    test_aes_decrypt_ecb_wrapper,
#else
    NULL,
#endif
/* Function Id: 2 */

#if defined(MBEDTLS_AES_C) && defined(MBEDTLS_CIPHER_MODE_CBC)
    test_aes_encrypt_cbc_wrapper,
#else
    NULL,
#endif
/* Function Id: 3 */

#if defined(MBEDTLS_AES_C) && defined(MBEDTLS_CIPHER_MODE_CBC)
    test_aes_decrypt_cbc_wrapper,
#else
    NULL,
#endif
/* Function Id: 4 */

#if defined(MBEDTLS_AES_C) && defined(MBEDTLS_CIPHER_MODE_XTS)
    test_aes_encrypt_xts_wrapper,
#else
    NULL,
#endif
/* Function Id: 5 */

#if defined(MBEDTLS_AES_C) && defined(MBEDTLS_CIPHER_MODE_XTS)
    test_aes_decrypt_xts_wrapper,
#else
    NULL,
#endif
/* Function Id: 6 */

#if defined(MBEDTLS_AES_C) && defined(MBEDTLS_CIPHER_MODE_XTS)
    test_aes_crypt_xts_size_wrapper,
#else
    NULL,
#endif
/* Function Id: 7 */

#if defined(MBEDTLS_AES_C) && defined(MBEDTLS_CIPHER_MODE_XTS)
    test_aes_crypt_xts_keysize_wrapper,
#else
    NULL,
#endif
/* Function Id: 8 */

#if defined(MBEDTLS_AES_C) && defined(MBEDTLS_CIPHER_MODE_CFB)
    test_aes_encrypt_cfb128_wrapper,
#else
    NULL,
#endif
/* Function Id: 9 */

#if defined(MBEDTLS_AES_C) && defined(MBEDTLS_CIPHER_MODE_CFB)
    test_aes_decrypt_cfb128_wrapper,
#else
    NULL,
#endif
/* Function Id: 10 */

#if defined(MBEDTLS_AES_C) && defined(MBEDTLS_CIPHER_MODE_CFB)
    test_aes_encrypt_cfb8_wrapper,
#else
    NULL,
#endif
/* Function Id: 11 */

#if defined(MBEDTLS_AES_C) && defined(MBEDTLS_CIPHER_MODE_CFB)
    test_aes_decrypt_cfb8_wrapper,
#else
    NULL,
#endif
/* Function Id: 12 */

#if defined(MBEDTLS_AES_C) && defined(MBEDTLS_CIPHER_MODE_OFB)
    test_aes_encrypt_ofb_wrapper,
#else
    NULL,
#endif
/* Function Id: 13 */

#if defined(MBEDTLS_AES_C) && defined(MBEDTLS_CHECK_PARAMS) && !defined(MBEDTLS_PARAM_FAILED_ALT)
    test_aes_check_params_wrapper,
#else
    NULL,
#endif
/* Function Id: 14 */

#if defined(MBEDTLS_AES_C)
    test_aes_misc_params_wrapper,
#else
    NULL,
#endif
/* Function Id: 15 */

#if defined(MBEDTLS_AES_C) && defined(MBEDTLS_SELF_TEST)
    test_aes_selftest_wrapper,
#else
    NULL,
#endif

#line 135 "suites/main_test.function"
};

/**
 * \brief        Execute the test function.
 *
 *               This is a wrapper function around the test function execution
 *               to allow the setjmp() call used to catch any calls to the
 *               parameter failure callback, to be used. Calls to setjmp()
 *               can invalidate the state of any local auto variables.
 *
 * \param fp     Function pointer to the test function
 * \param params Parameters to pass
 *
 */
static void execute_function_ptr(TestWrapper_t fp, void **params)
{
#if defined(MBEDTLS_CHECK_PARAMS)
    if ( setjmp( param_fail_jmp ) == 0 )
    {
        fp( params );
    }
    else
    {
        /* Unexpected parameter validation error */
        test_info.failed = 1;
    }

    memset( param_fail_jmp, 0, sizeof(jmp_buf) );
#else
    fp( params );
#endif
}

/**
 * \brief        Dispatches test functions based on function index.
 *
 * \param exp_id    Test function index.
 *
 * \return       DISPATCH_TEST_SUCCESS if found
 *               DISPATCH_TEST_FN_NOT_FOUND if not found
 *               DISPATCH_UNSUPPORTED_SUITE if not compile time enabled.
 */
static int dispatch_test( int func_idx, void ** params )
{
    int ret = DISPATCH_TEST_SUCCESS;
    TestWrapper_t fp = NULL;

    if ( func_idx < (int)( sizeof( test_funcs ) / sizeof( TestWrapper_t ) ) )
    {
        fp = test_funcs[func_idx];
        if ( fp )
            execute_function_ptr(fp, params);
        else
            ret = DISPATCH_UNSUPPORTED_SUITE;
    }
    else
    {
        ret = DISPATCH_TEST_FN_NOT_FOUND;
    }

    return( ret );
}


/**
 * \brief       Checks if test function is supported
 *
 * \param exp_id    Test function index.
 *
 * \return       DISPATCH_TEST_SUCCESS if found
 *               DISPATCH_TEST_FN_NOT_FOUND if not found
 *               DISPATCH_UNSUPPORTED_SUITE if not compile time enabled.
 */
static int check_test( int func_idx )
{
    int ret = DISPATCH_TEST_SUCCESS;
    TestWrapper_t fp = NULL;

    if ( func_idx < (int)( sizeof(test_funcs)/sizeof( TestWrapper_t ) ) )
    {
        fp = test_funcs[func_idx];
        if ( fp == NULL )
            ret = DISPATCH_UNSUPPORTED_SUITE;
    }
    else
    {
        ret = DISPATCH_TEST_FN_NOT_FOUND;
    }

    return( ret );
}


#line 2 "suites/host_test.function"

/**
 * \brief       Verifies that string is in string parameter format i.e. "<str>"
 *              It also strips enclosing '"' from the input string.
 *
 * \param str   String parameter.
 *
 * \return      0 if success else 1
 */
static int verify_string( char **str )
{
    if( ( *str )[0] != '"' ||
        ( *str )[strlen( *str ) - 1] != '"' )
    {
        mbedtls_fprintf( stderr,
            "Expected string (with \"\") for parameter and got: %s\n", *str );
        return( -1 );
    }

    ( *str )++;
    ( *str )[strlen( *str ) - 1] = '\0';

    return( 0 );
}

/**
 * \brief       Verifies that string is an integer. Also gives the converted
 *              integer value.
 *
 * \param str   Input string.
 * \param value Pointer to int for output value.
 *
 * \return      0 if success else 1
 */
static int verify_int( char *str, int *value )
{
    size_t i;
    int minus = 0;
    int digits = 1;
    int hex = 0;

    for( i = 0; i < strlen( str ); i++ )
    {
        if( i == 0 && str[i] == '-' )
        {
            minus = 1;
            continue;
        }

        if( ( ( minus && i == 2 ) || ( !minus && i == 1 ) ) &&
            str[i - 1] == '0' && ( str[i] == 'x' || str[i] == 'X' ) )
        {
            hex = 1;
            continue;
        }

        if( ! ( ( str[i] >= '0' && str[i] <= '9' ) ||
                ( hex && ( ( str[i] >= 'a' && str[i] <= 'f' ) ||
                           ( str[i] >= 'A' && str[i] <= 'F' ) ) ) ) )
        {
            digits = 0;
            break;
        }
    }

    if( digits )
    {
        if( hex )
            *value = strtol( str, NULL, 16 );
        else
            *value = strtol( str, NULL, 10 );

        return( 0 );
    }

    mbedtls_fprintf( stderr,
                    "Expected integer for parameter and got: %s\n", str );
    return( KEY_VALUE_MAPPING_NOT_FOUND );
}


/**
 * \brief       Usage string.
 *
 */
#define USAGE \
    "Usage: %s [OPTIONS] files...\n\n" \
    "   Command line arguments:\n" \
    "     files...          One or more test data files. If no file is\n" \
    "                       specified the following default test case\n" \
    "                       file is used:\n" \
    "                           %s\n\n" \
    "   Options:\n" \
    "     -v | --verbose    Display full information about each test\n" \
    "     -h | --help       Display this information\n\n", \
    argv[0], \
    "TESTCASE_FILENAME"


/**
 * \brief       Read a line from the passed file pointer.
 *
 * \param f     FILE pointer
 * \param buf   Pointer to memory to hold read line.
 * \param len   Length of the buf.
 *
 * \return      0 if success else -1
 */
static int get_line( FILE *f, char *buf, size_t len )
{
    char *ret;
    int i = 0, str_len = 0, has_string = 0;

    /* Read until we get a valid line */
    do
    {
        ret = fgets( buf, len, f );
        if( ret == NULL )
            return( -1 );

        str_len = strlen( buf );

        /* Skip empty line and comment */
        if ( str_len == 0 || buf[0] == '#' )
            continue;
        has_string = 0;
        for ( i = 0; i < str_len; i++ )
        {
            char c = buf[i];
            if ( c != ' ' && c != '\t' && c != '\n' &&
                 c != '\v' && c != '\f' && c != '\r' )
            {
                has_string = 1;
                break;
            }
        }
    } while( !has_string );

    /* Strip new line and carriage return */
    ret = buf + strlen( buf );
    if( ret-- > buf && *ret == '\n' )
        *ret = '\0';
    if( ret-- > buf && *ret == '\r' )
        *ret = '\0';

    return( 0 );
}

/**
 * \brief       Splits string delimited by ':'. Ignores '\:'.
 *
 * \param buf           Input string
 * \param len           Input string length
 * \param params        Out params found
 * \param params_len    Out params array len
 *
 * \return      Count of strings found.
 */
static int parse_arguments( char *buf, size_t len, char **params,
                            size_t params_len )
{
    size_t cnt = 0, i;
    char *cur = buf;
    char *p = buf, *q;

    params[cnt++] = cur;

    while( *p != '\0' && p < ( buf + len ) )
    {
        if( *p == '\\' )
        {
            p++;
            p++;
            continue;
        }
        if( *p == ':' )
        {
            if( p + 1 < buf + len )
            {
                cur = p + 1;
                assert( cnt < params_len );
                params[cnt++] = cur;
            }
            *p = '\0';
        }

        p++;
    }

    /* Replace newlines, question marks and colons in strings */
    for( i = 0; i < cnt; i++ )
    {
        p = params[i];
        q = params[i];

        while( *p != '\0' )
        {
            if( *p == '\\' && *( p + 1 ) == 'n' )
            {
                p += 2;
                *( q++ ) = '\n';
            }
            else if( *p == '\\' && *( p + 1 ) == ':' )
            {
                p += 2;
                *( q++ ) = ':';
            }
            else if( *p == '\\' && *( p + 1 ) == '?' )
            {
                p += 2;
                *( q++ ) = '?';
            }
            else
                *( q++ ) = *( p++ );
        }
        *q = '\0';
    }

    return( cnt );
}

/**
 * \brief       Converts parameters into test function consumable parameters.
 *              Example: Input:  {"int", "0", "char*", "Hello",
 *                                "hex", "abef", "exp", "1"}
 *                      Output:  {
 *                                0,                // Verified int
 *                                "Hello",          // Verified string
 *                                2, { 0xab, 0xef },// Converted len,hex pair
 *                                9600              // Evaluated expression
 *                               }
 *
 *
 * \param cnt               Parameter array count.
 * \param params            Out array of found parameters.
 * \param int_params_store  Memory for storing processed integer parameters.
 *
 * \return      0 for success else 1
 */
static int convert_params( size_t cnt , char ** params , int * int_params_store )
{
    char ** cur = params;
    char ** out = params;
    int ret = DISPATCH_TEST_SUCCESS;

    while ( cur < params + cnt )
    {
        char * type = *cur++;
        char * val = *cur++;

        if ( strcmp( type, "char*" ) == 0 )
        {
            if ( verify_string( &val ) == 0 )
            {
              *out++ = val;
            }
            else
            {
                ret = ( DISPATCH_INVALID_TEST_DATA );
                break;
            }
        }
        else if ( strcmp( type, "int" ) == 0 )
        {
            if ( verify_int( val, int_params_store ) == 0 )
            {
              *out++ = (char *) int_params_store++;
            }
            else
            {
                ret = ( DISPATCH_INVALID_TEST_DATA );
                break;
            }
        }
        else if ( strcmp( type, "hex" ) == 0 )
        {
            if ( verify_string( &val ) == 0 )
            {
                *int_params_store = unhexify( (unsigned char *) val, val );
                *out++ = val;
                *out++ = (char *)(int_params_store++);
            }
            else
            {
                ret = ( DISPATCH_INVALID_TEST_DATA );
                break;
            }
        }
        else if ( strcmp( type, "exp" ) == 0 )
        {
            int exp_id = strtol( val, NULL, 10 );
            if ( get_expression ( (int32_t)exp_id, (int32_t *)int_params_store ) == 0 )
            {
              *out++ = (char *)int_params_store++;
            }
            else
            {
              ret = ( DISPATCH_INVALID_TEST_DATA );
              break;
            }
        }
        else
        {
          ret = ( DISPATCH_INVALID_TEST_DATA );
          break;
        }
    }
    return( ret );
}

/**
 * \brief       Tests snprintf implementation with test input.
 *
 * \note
 * At high optimization levels (e.g. gcc -O3), this function may be
 * inlined in run_test_snprintf. This can trigger a spurious warning about
 * potential misuse of snprintf from gcc -Wformat-truncation (observed with
 * gcc 7.2). This warning makes tests in run_test_snprintf redundant on gcc
 * only. They are still valid for other compilers. Avoid this warning by
 * forbidding inlining of this function by gcc.
 *
 * \param n         Buffer test length.
 * \param ref_buf   Expected buffer.
 * \param ref_ret   Expected snprintf return value.
 *
 * \return      0 for success else 1
 */
#if defined(__GNUC__)
__attribute__((__noinline__))
#endif
static int test_snprintf( size_t n, const char ref_buf[10], int ref_ret )
{
    int ret;
    char buf[10] = "xxxxxxxxx";
    const char ref[10] = "xxxxxxxxx";

    if( n >= sizeof( buf ) )
        return( -1 );
    ret = mbedtls_snprintf( buf, n, "%s", "123" );
    if( ret < 0 || (size_t) ret >= n )
        ret = -1;

    if( strncmp( ref_buf, buf, sizeof( buf ) ) != 0 ||
        ref_ret != ret ||
        memcmp( buf + n, ref + n, sizeof( buf ) - n ) != 0 )
    {
        return( 1 );
    }

    return( 0 );
}

/**
 * \brief       Tests snprintf implementation.
 *
 * \param none
 *
 * \return      0 for success else 1
 */
static int run_test_snprintf( void )
{
    return( test_snprintf( 0, "xxxxxxxxx",  -1 ) != 0 ||
            test_snprintf( 1, "",           -1 ) != 0 ||
            test_snprintf( 2, "1",          -1 ) != 0 ||
            test_snprintf( 3, "12",         -1 ) != 0 ||
            test_snprintf( 4, "123",         3 ) != 0 ||
            test_snprintf( 5, "123",         3 ) != 0 );
}


/**
 * \brief       Desktop implementation of execute_tests().
 *              Parses command line and executes tests from
 *              supplied or default data file.
 *
 * \param argc  Command line argument count.
 * \param argv  Argument array.
 *
 * \return      Program exit status.
 */
static int execute_tests( int argc , const char ** argv )
{
    /* Local Configurations and options */
    const char *default_filename = "/aes.ofb.datax";
    const char *test_filename = NULL;
    const char **test_files = NULL;
    int testfile_count = 0;
    int option_verbose = 0;
    int function_id = 0;

    /* Other Local variables */
    int arg_index = 1;
    const char *next_arg;
    int testfile_index, ret, i, cnt;
    int total_errors = 0, total_tests = 0, total_skipped = 0;
    FILE *file;
    char buf[5000];
    char *params[50];
    /* Store for proccessed integer params. */
    int int_params[50];
    void *pointer;
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
    int stdout_fd = -1;
#endif /* __unix__ || __APPLE__ __MACH__ */

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C) && \
    !defined(TEST_SUITE_MEMORY_BUFFER_ALLOC)
    unsigned char alloc_buf[1000000];
    mbedtls_memory_buffer_alloc_init( alloc_buf, sizeof( alloc_buf ) );
#endif

    /*
     * The C standard doesn't guarantee that all-bits-0 is the representation
     * of a NULL pointer. We do however use that in our code for initializing
     * structures, which should work on every modern platform. Let's be sure.
     */
    memset( &pointer, 0, sizeof( void * ) );
    if( pointer != NULL )
    {
        mbedtls_fprintf( stderr, "all-bits-zero is not a NULL pointer\n" );
        return( 1 );
    }

    /*
     * Make sure we have a snprintf that correctly zero-terminates
     */
    if( run_test_snprintf() != 0 )
    {
        mbedtls_fprintf( stderr, "the snprintf implementation is broken\n" );
        return( 1 );
    }

    while( arg_index < argc )
    {
        next_arg = argv[arg_index];

        if( strcmp( next_arg, "--verbose" ) == 0 ||
                 strcmp( next_arg, "-v" ) == 0 )
        {
            option_verbose = 1;
        }
        else if( strcmp(next_arg, "--help" ) == 0 ||
                 strcmp(next_arg, "-h" ) == 0 )
        {
            mbedtls_fprintf( stdout, USAGE );
            mbedtls_exit( EXIT_SUCCESS );
        }
        else
        {
            /* Not an option, therefore treat all further arguments as the file
             * list.
             */
            test_files = &argv[ arg_index ];
            testfile_count = argc - arg_index;
        }

        arg_index++;
    }

    /* If no files were specified, assume a default */
    if ( test_files == NULL || testfile_count == 0 )
    {
        test_files = &default_filename;
        testfile_count = 1;
    }

    /* Initialize the struct that holds information about the last test */
    memset( &test_info, 0, sizeof( test_info ) );

    /* Now begin to execute the tests in the testfiles */
    for ( testfile_index = 0;
          testfile_index < testfile_count;
          testfile_index++ )
    {
        int unmet_dep_count = 0;
        char *unmet_dependencies[20];

        test_filename = test_files[ testfile_index ];

        file = fopen( test_filename, "r" );
        if( file == NULL )
        {
            mbedtls_fprintf( stderr, "Failed to open test file: %s\n",
                             test_filename );
            return( 1 );
        }

        while( !feof( file ) )
        {
            if( unmet_dep_count > 0 )
            {
                mbedtls_fprintf( stderr,
                    "FATAL: Dep count larger than zero at start of loop\n" );
                mbedtls_exit( MBEDTLS_EXIT_FAILURE );
            }
            unmet_dep_count = 0;

            if( ( ret = get_line( file, buf, sizeof(buf) ) ) != 0 )
                break;
            mbedtls_fprintf( stdout, "%s%.66s", test_info.failed ? "\n" : "", buf );
            mbedtls_fprintf( stdout, " " );
            for( i = strlen( buf ) + 1; i < 67; i++ )
                mbedtls_fprintf( stdout, "." );
            mbedtls_fprintf( stdout, " " );
            fflush( stdout );

            total_tests++;

            if( ( ret = get_line( file, buf, sizeof( buf ) ) ) != 0 )
                break;
            cnt = parse_arguments( buf, strlen( buf ), params,
                                   sizeof( params ) / sizeof( params[0] ) );

            if( strcmp( params[0], "depends_on" ) == 0 )
            {
                for( i = 1; i < cnt; i++ )
                {
                    int dep_id = strtol( params[i], NULL, 10 );
                    if( dep_check( dep_id ) != DEPENDENCY_SUPPORTED )
                    {
                        if( 0 == option_verbose )
                        {
                            /* Only one count is needed if not verbose */
                            unmet_dep_count++;
                            break;
                        }

                        unmet_dependencies[ unmet_dep_count ] = strdup( params[i] );
                        if(  unmet_dependencies[ unmet_dep_count ] == NULL )
                        {
                            mbedtls_fprintf( stderr, "FATAL: Out of memory\n" );
                            mbedtls_exit( MBEDTLS_EXIT_FAILURE );
                        }
                        unmet_dep_count++;
                    }
                }

                if( ( ret = get_line( file, buf, sizeof( buf ) ) ) != 0 )
                    break;
                cnt = parse_arguments( buf, strlen( buf ), params,
                                       sizeof( params ) / sizeof( params[0] ) );
            }

            // If there are no unmet dependencies execute the test
            if( unmet_dep_count == 0 )
            {
                test_info.failed = 0;
                test_info.paramfail_test_state = PARAMFAIL_TESTSTATE_IDLE;

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
                /* Suppress all output from the library unless we're verbose
                 * mode
                 */
                if( !option_verbose )
                {
                    stdout_fd = redirect_output( &stdout, "/dev/null" );
                    if( stdout_fd == -1 )
                    {
                        /* Redirection has failed with no stdout so exit */
                        exit( 1 );
                    }
                }
#endif /* __unix__ || __APPLE__ __MACH__ */

                function_id = strtol( params[0], NULL, 10 );
                if ( (ret = check_test( function_id )) == DISPATCH_TEST_SUCCESS )
                {
                    ret = convert_params( cnt - 1, params + 1, int_params );
                    if ( DISPATCH_TEST_SUCCESS == ret )
                    {
                        ret = dispatch_test( function_id, (void **)( params + 1 ) );
                    }
                }

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
                if( !option_verbose && restore_output( &stdout, stdout_fd ) )
                {
                        /* Redirection has failed with no stdout so exit */
                        exit( 1 );
                }
#endif /* __unix__ || __APPLE__ __MACH__ */

            }

            if( unmet_dep_count > 0 || ret == DISPATCH_UNSUPPORTED_SUITE )
            {
                total_skipped++;
                mbedtls_fprintf( stdout, "----" );

                if( 1 == option_verbose && ret == DISPATCH_UNSUPPORTED_SUITE )
                {
                    mbedtls_fprintf( stdout, "\n   Test Suite not enabled" );
                }

                if( 1 == option_verbose && unmet_dep_count > 0 )
                {
                    mbedtls_fprintf( stdout, "\n   Unmet dependencies: " );
                    for( i = 0; i < unmet_dep_count; i++ )
                    {
                        mbedtls_fprintf( stdout, "%s  ",
                                        unmet_dependencies[i] );
                        free( unmet_dependencies[i] );
                    }
                }
                mbedtls_fprintf( stdout, "\n" );
                fflush( stdout );

                unmet_dep_count = 0;
            }
            else if( ret == DISPATCH_TEST_SUCCESS )
            {
                if( test_info.failed == 0 )
                {
                    mbedtls_fprintf( stdout, "PASS\n" );
                }
                else
                {
                    total_errors++;
                    mbedtls_fprintf( stdout, "FAILED\n" );
                    mbedtls_fprintf( stdout, "  %s\n  at line %d, %s\n",
                                     test_info.test, test_info.line_no,
                                     test_info.filename );
                }
                fflush( stdout );
            }
            else if( ret == DISPATCH_INVALID_TEST_DATA )
            {
                mbedtls_fprintf( stderr, "FAILED: FATAL PARSE ERROR\n" );
                fclose( file );
                mbedtls_exit( 2 );
            }
            else if( ret == DISPATCH_TEST_FN_NOT_FOUND )
            {
                mbedtls_fprintf( stderr, "FAILED: FATAL TEST FUNCTION NOT FUND\n" );
                fclose( file );
                mbedtls_exit( 2 );
            }
            else
                total_errors++;
        }
        fclose( file );

        /* In case we encounter early end of file */
        for( i = 0; i < unmet_dep_count; i++ )
            free( unmet_dependencies[i] );
    }

    mbedtls_fprintf( stdout, "\n----------------------------------------------------------------------------\n\n");
    if( total_errors == 0 )
        mbedtls_fprintf( stdout, "PASSED" );
    else
        mbedtls_fprintf( stdout, "FAILED" );

    mbedtls_fprintf( stdout, " (%d / %d tests (%d skipped))\n",
             total_tests - total_errors, total_tests, total_skipped );

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C) && \
    !defined(TEST_SUITE_MEMORY_BUFFER_ALLOC)
#if defined(MBEDTLS_MEMORY_DEBUG)
    mbedtls_memory_buffer_alloc_status();
#endif
    mbedtls_memory_buffer_alloc_free();
#endif

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
    if( stdout_fd != -1 )
        close_output( stdout );
#endif /* __unix__ || __APPLE__ __MACH__ */

    return( total_errors != 0 );
}


#line 231 "suites/main_test.function"

/*----------------------------------------------------------------------------*/
/* Main Test code */


/**
 * \brief       Program main. Invokes platform specific execute_tests().
 *
 * \param argc      Command line arguments count.
 * \param argv      Array of command line arguments.
 *
 * \return       Exit code.
 */
int test_suite_aes_ofb( int argc, const char *argv[] )
{
    int ret = platform_setup();
    if( ret != 0 )
    {
        mbedtls_fprintf( stderr,
                         "FATAL: Failed to initialize platform - error %d\n",
                         ret );
        return( -1 );
    }
    ret = execute_tests( argc, argv );
    platform_teardown();
    return( ret );
}

