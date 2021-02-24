#line 2 "suites/main_test.function"
/*
 * *** THIS FILE HAS BEEN MACHINE GENERATED ***
 *
 * This file has been machine generated using the script:
 * generate_test_code.py
 *
 * Test file      : ./test_suite_ecp.c
 *
 * The following files were used to create this file.
 *
 *      Main code file      : suites/main_test.function
 *      Platform code file  : suites/host_test.function
 *      Helper file         : suites/helpers.function
 *      Test suite file     : suites/test_suite_ecp.function
 *      Test suite data     : suites/test_suite_ecp.data
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

#if defined(MBEDTLS_ECP_C)
#line 2 "suites/test_suite_ecp.function"
#include "mbedtls/ecp.h"

#define ECP_PF_UNKNOWN     -1

#define ECP_PT_RESET( x )           \
    mbedtls_ecp_point_free( x );    \
    mbedtls_ecp_point_init( x );
#line 17 "suites/test_suite_ecp.function"
void test_ecp_valid_param( )
{
    TEST_VALID_PARAM( mbedtls_ecp_group_free( NULL ) );
    TEST_VALID_PARAM( mbedtls_ecp_keypair_free( NULL ) );
    TEST_VALID_PARAM( mbedtls_ecp_point_free( NULL ) );

#if defined(MBEDTLS_ECP_RESTARTABLE)
    TEST_VALID_PARAM( mbedtls_ecp_restart_free( NULL ) );
#endif /* MBEDTLS_ECP_RESTARTABLE */

exit:
    return;
}

void test_ecp_valid_param_wrapper( void ** params )
{
    (void)params;

    test_ecp_valid_param(  );
}
#if defined(MBEDTLS_CHECK_PARAMS)
#if !defined(MBEDTLS_PARAM_FAILED_ALT)
#line 33 "suites/test_suite_ecp.function"
void test_ecp_invalid_param( )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_keypair kp;
    mbedtls_ecp_point P;
    mbedtls_mpi m;
    const char *x = "deadbeef";
    int valid_fmt   = MBEDTLS_ECP_PF_UNCOMPRESSED;
    int invalid_fmt = 42;
    size_t olen;
    unsigned char buf[42] = { 0 };
    const unsigned char *null_buf = NULL;
    mbedtls_ecp_group_id valid_group = MBEDTLS_ECP_DP_SECP192R1;
    mbedtls_ecp_restart_ctx restart_ctx;

    TEST_INVALID_PARAM( mbedtls_ecp_point_init( NULL ) );
    TEST_INVALID_PARAM( mbedtls_ecp_keypair_init( NULL ) );
    TEST_INVALID_PARAM( mbedtls_ecp_group_init( NULL ) );

#if defined(MBEDTLS_ECP_RESTARTABLE)
    TEST_INVALID_PARAM( mbedtls_ecp_restart_init( NULL ) );
    TEST_INVALID_PARAM( mbedtls_ecp_check_budget( NULL, &restart_ctx, 42 ) );
#endif /* MBEDTLS_ECP_RESTARTABLE */

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_copy( NULL, &P ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_copy( &P, NULL ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_group_copy( NULL, &grp ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_group_copy( &grp, NULL ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_gen_privkey( NULL,
                                                     &m,
                                                     rnd_std_rand,
                                                     NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_gen_privkey( &grp,
                                                     NULL,
                                                     rnd_std_rand,
                                                     NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_gen_privkey( &grp,
                                                     &m,
                                                     NULL,
                                                     NULL ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_set_zero( NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_is_zero( NULL ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_point_cmp( NULL, &P ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_point_cmp( &P, NULL ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_point_read_string( NULL, 2,
                                                           x, x ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_point_read_string( &P, 2,
                                                           NULL, x ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_point_read_string( &P, 2,
                                                           x, NULL ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_point_write_binary( NULL, &P,
                                                      valid_fmt,
                                                      &olen,
                                                      buf, sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_point_write_binary( &grp, NULL,
                                                      valid_fmt,
                                                      &olen,
                                                      buf, sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_point_write_binary( &grp, &P,
                                                      invalid_fmt,
                                                      &olen,
                                                      buf, sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_point_write_binary( &grp, &P,
                                                      valid_fmt,
                                                      NULL,
                                                      buf, sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_point_write_binary( &grp, &P,
                                                      valid_fmt,
                                                      &olen,
                                                      NULL, sizeof( buf ) ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_point_read_binary( NULL, &P, buf,
                                                     sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_point_read_binary( &grp, NULL, buf,
                                                     sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_point_read_binary( &grp, &P, NULL,
                                                     sizeof( buf ) ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_read_point( NULL, &P,
                                                 (const unsigned char **) &buf,
                                                 sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_read_point( &grp, NULL,
                                                 (const unsigned char **) &buf,
                                                 sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_read_point( &grp, &P, &null_buf,
                                                        sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_read_point( &grp, &P, NULL,
                                                    sizeof( buf ) ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_write_point( NULL, &P,
                                                     valid_fmt,
                                                     &olen,
                                                     buf,
                                                     sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_write_point( &grp, NULL,
                                                     valid_fmt,
                                                     &olen,
                                                     buf,
                                                     sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_write_point( &grp, &P,
                                                     invalid_fmt,
                                                     &olen,
                                                     buf,
                                                     sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_write_point( &grp, &P,
                                                     valid_fmt,
                                                     NULL,
                                                     buf,
                                                     sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_write_point( &grp, &P,
                                                     valid_fmt,
                                                     &olen,
                                                     NULL,
                                                     sizeof( buf ) ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_group_load( NULL, valid_group ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_read_group( NULL,
                                                 (const unsigned char **) &buf,
                                                 sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_read_group( &grp, NULL,
                                                        sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_read_group( &grp, &null_buf,
                                                        sizeof( buf ) ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_read_group_id( NULL,
                                                 (const unsigned char **) &buf,
                                                 sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_read_group_id( &valid_group, NULL,
                                                        sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_read_group_id( &valid_group,
                                                           &null_buf,
                                                           sizeof( buf ) ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_write_group( NULL, &olen,
                                                       buf, sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_write_group( &grp, NULL,
                                                       buf, sizeof( buf ) ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_tls_write_group( &grp, &olen,
                                                       NULL, sizeof( buf ) ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_mul( NULL, &P, &m, &P,
                                             rnd_std_rand, NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_mul( &grp, NULL, &m, &P,
                                             rnd_std_rand, NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_mul( &grp, &P, NULL, &P,
                                             rnd_std_rand, NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_mul( &grp, &P, &m, NULL,
                                             rnd_std_rand, NULL ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_mul_restartable( NULL, &P, &m, &P,
                                                 rnd_std_rand, NULL , NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_mul_restartable( &grp, NULL, &m, &P,
                                                 rnd_std_rand, NULL , NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_mul_restartable( &grp, &P, NULL, &P,
                                                 rnd_std_rand, NULL , NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_mul_restartable( &grp, &P, &m, NULL,
                                                 rnd_std_rand, NULL , NULL ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_muladd( NULL, &P, &m, &P,
                                                &m, &P ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_muladd( &grp, NULL, &m, &P,
                                                &m, &P ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_muladd( &grp, &P, NULL, &P,
                                                &m, &P ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_muladd( &grp, &P, &m, NULL,
                                                &m, &P ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_muladd( &grp, &P, &m, &P,
                                                NULL, &P ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_muladd( &grp, &P, &m, &P,
                                                &m, NULL ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_muladd_restartable( NULL, &P, &m, &P,
                                                            &m, &P, NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_muladd_restartable( &grp, NULL, &m, &P,
                                                            &m, &P, NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_muladd_restartable( &grp, &P, NULL, &P,
                                                            &m, &P, NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_muladd_restartable( &grp, &P, &m, NULL,
                                                            &m, &P, NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_muladd_restartable( &grp, &P, &m, &P,
                                                            NULL, &P, NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_muladd_restartable( &grp, &P, &m, &P,
                                                            &m, NULL, NULL ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_check_pubkey( NULL, &P ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_check_pubkey( &grp, NULL ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_check_pub_priv( NULL, &kp ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_check_pub_priv( &kp, NULL ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_check_privkey( NULL, &m ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_check_privkey( &grp, NULL ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_gen_keypair_base( NULL, &P,
                                                          &m, &P,
                                                          rnd_std_rand,
                                                          NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_gen_keypair_base( &grp, NULL,
                                                          &m, &P,
                                                          rnd_std_rand,
                                                          NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_gen_keypair_base( &grp, &P,
                                                          NULL, &P,
                                                          rnd_std_rand,
                                                          NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_gen_keypair_base( &grp, &P,
                                                          &m, NULL,
                                                          rnd_std_rand,
                                                          NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_gen_keypair_base( &grp, &P,
                                                          &m, &P,
                                                          NULL,
                                                          NULL ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_gen_keypair( NULL,
                                                     &m, &P,
                                                     rnd_std_rand,
                                                     NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_gen_keypair( &grp,
                                                     NULL, &P,
                                                     rnd_std_rand,
                                                     NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_gen_keypair( &grp,
                                                     &m, NULL,
                                                     rnd_std_rand,
                                                     NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_gen_keypair( &grp,
                                                     &m, &P,
                                                     NULL,
                                                     NULL ) );

    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_gen_key( valid_group, NULL,
                                                 rnd_std_rand, NULL ) );
    TEST_INVALID_PARAM_RET( MBEDTLS_ERR_ECP_BAD_INPUT_DATA,
                            mbedtls_ecp_gen_key( valid_group, &kp,
                                                 NULL, NULL ) );

exit:
    return;
}

void test_ecp_invalid_param_wrapper( void ** params )
{
    (void)params;

    test_ecp_invalid_param(  );
}
#endif /* !MBEDTLS_PARAM_FAILED_ALT */
#endif /* MBEDTLS_CHECK_PARAMS */
#line 360 "suites/test_suite_ecp.function"
void test_mbedtls_ecp_curve_info( int id, int tls_id, int size, char * name )
{
    const mbedtls_ecp_curve_info *by_id, *by_tls, *by_name;

    by_id   = mbedtls_ecp_curve_info_from_grp_id( id     );
    by_tls  = mbedtls_ecp_curve_info_from_tls_id( tls_id );
    by_name = mbedtls_ecp_curve_info_from_name(   name   );
    TEST_ASSERT( by_id   != NULL );
    TEST_ASSERT( by_tls  != NULL );
    TEST_ASSERT( by_name != NULL );

    TEST_ASSERT( by_id == by_tls  );
    TEST_ASSERT( by_id == by_name );

    TEST_ASSERT( by_id->bit_size == size );
exit:
    ;
}

void test_mbedtls_ecp_curve_info_wrapper( void ** params )
{

    test_mbedtls_ecp_curve_info( *( (int *) params[0] ), *( (int *) params[1] ), *( (int *) params[2] ), (char *) params[3] );
}
#line 379 "suites/test_suite_ecp.function"
void test_ecp_check_pub( int grp_id, char * x_hex, char * y_hex, char * z_hex,
                    int ret )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point P;

    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &P );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, grp_id ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &P.X, 16, x_hex ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &P.Y, 16, y_hex ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &P.Z, 16, z_hex ) == 0 );

    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &P ) == ret );

exit:
    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &P );
}

void test_ecp_check_pub_wrapper( void ** params )
{

    test_ecp_check_pub( *( (int *) params[0] ), (char *) params[1], (char *) params[2], (char *) params[3], *( (int *) params[4] ) );
}
#if defined(MBEDTLS_ECP_RESTARTABLE)
#line 403 "suites/test_suite_ecp.function"
void test_ecp_test_vect_restart( int id,
                            char *dA_str, char *xA_str, char *yA_str,
                            char *dB_str,  char *xZ_str, char *yZ_str,
                            int max_ops, int min_restarts, int max_restarts )
{
    /*
     * Test for early restart. Based on test vectors like ecp_test_vect(),
     * but for the sake of simplicity only does half of each side. It's
     * important to test both base point and random point, though, as memory
     * management is different in each case.
     *
     * Don't try using too precise bounds for restarts as the exact number
     * will depend on settings such as MBEDTLS_ECP_FIXED_POINT_OPTIM and
     * MBEDTLS_ECP_WINDOW_SIZE, as well as implementation details that may
     * change in the future. A factor 2 is a minimum safety margin.
     *
     * For reference, with mbed TLS 2.4 and default settings, for P-256:
     * - Random point mult:     ~3250M
     * - Cold base point mult:  ~3300M
     * - Hot base point mult:   ~1100M
     * With MBEDTLS_ECP_WINDOW_SIZE set to 2 (minimum):
     * - Random point mult:     ~3850M
     */
    mbedtls_ecp_restart_ctx ctx;
    mbedtls_ecp_group grp;
    mbedtls_ecp_point R, P;
    mbedtls_mpi dA, xA, yA, dB, xZ, yZ;
    int cnt_restarts;
    int ret;

    mbedtls_ecp_restart_init( &ctx );
    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &R ); mbedtls_ecp_point_init( &P );
    mbedtls_mpi_init( &dA ); mbedtls_mpi_init( &xA ); mbedtls_mpi_init( &yA );
    mbedtls_mpi_init( &dB ); mbedtls_mpi_init( &xZ ); mbedtls_mpi_init( &yZ );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &dA, 16, dA_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &xA, 16, xA_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &yA, 16, yA_str ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &dB, 16, dB_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &xZ, 16, xZ_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &yZ, 16, yZ_str ) == 0 );

    mbedtls_ecp_set_max_ops( (unsigned) max_ops );

    /* Base point case */
    cnt_restarts = 0;
    do {
        ECP_PT_RESET( &R );
        ret = mbedtls_ecp_mul_restartable( &grp, &R, &dA, &grp.G, NULL, NULL, &ctx );
    } while( ret == MBEDTLS_ERR_ECP_IN_PROGRESS && ++cnt_restarts );

    TEST_ASSERT( ret == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xA ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.Y, &yA ) == 0 );

    TEST_ASSERT( cnt_restarts >= min_restarts );
    TEST_ASSERT( cnt_restarts <= max_restarts );

    /* Non-base point case */
    mbedtls_ecp_copy( &P, &R );
    cnt_restarts = 0;
    do {
        ECP_PT_RESET( &R );
        ret = mbedtls_ecp_mul_restartable( &grp, &R, &dB, &P, NULL, NULL, &ctx );
    } while( ret == MBEDTLS_ERR_ECP_IN_PROGRESS && ++cnt_restarts );

    TEST_ASSERT( ret == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xZ ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.Y, &yZ ) == 0 );

    TEST_ASSERT( cnt_restarts >= min_restarts );
    TEST_ASSERT( cnt_restarts <= max_restarts );

    /* Do we leak memory when aborting an operation?
     * This test only makes sense when we actually restart */
    if( min_restarts > 0 )
    {
        ret = mbedtls_ecp_mul_restartable( &grp, &R, &dB, &P, NULL, NULL, &ctx );
        TEST_ASSERT( ret == MBEDTLS_ERR_ECP_IN_PROGRESS );
    }

exit:
    mbedtls_ecp_restart_free( &ctx );
    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &R ); mbedtls_ecp_point_free( &P );
    mbedtls_mpi_free( &dA ); mbedtls_mpi_free( &xA ); mbedtls_mpi_free( &yA );
    mbedtls_mpi_free( &dB ); mbedtls_mpi_free( &xZ ); mbedtls_mpi_free( &yZ );
}

void test_ecp_test_vect_restart_wrapper( void ** params )
{

    test_ecp_test_vect_restart( *( (int *) params[0] ), (char *) params[1], (char *) params[2], (char *) params[3], (char *) params[4], (char *) params[5], (char *) params[6], *( (int *) params[7] ), *( (int *) params[8] ), *( (int *) params[9] ) );
}
#endif /* MBEDTLS_ECP_RESTARTABLE */
#if defined(MBEDTLS_ECP_RESTARTABLE)
#line 498 "suites/test_suite_ecp.function"
void test_ecp_muladd_restart( int id, char *xR_str, char *yR_str,
                         char *u1_str, char *u2_str,
                         char *xQ_str, char *yQ_str,
                         int max_ops, int min_restarts, int max_restarts )
{
    /*
     * Compute R = u1 * G + u2 * Q
     * (test vectors mostly taken from ECDSA intermediate results)
     *
     * See comments at the top of ecp_test_vect_restart()
     */
    mbedtls_ecp_restart_ctx ctx;
    mbedtls_ecp_group grp;
    mbedtls_ecp_point R, Q;
    mbedtls_mpi u1, u2, xR, yR;
    int cnt_restarts;
    int ret;

    mbedtls_ecp_restart_init( &ctx );
    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &R );
    mbedtls_ecp_point_init( &Q );
    mbedtls_mpi_init( &u1 ); mbedtls_mpi_init( &u2 );
    mbedtls_mpi_init( &xR ); mbedtls_mpi_init( &yR );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &u1, 16, u1_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &u2, 16, u2_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &xR, 16, xR_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &yR, 16, yR_str ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &Q.X, 16, xQ_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &Q.Y, 16, yQ_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_lset( &Q.Z, 1 ) == 0 );

    mbedtls_ecp_set_max_ops( (unsigned) max_ops );

    cnt_restarts = 0;
    do {
        ECP_PT_RESET( &R );
        ret = mbedtls_ecp_muladd_restartable( &grp, &R,
                                              &u1, &grp.G, &u2, &Q, &ctx );
    } while( ret == MBEDTLS_ERR_ECP_IN_PROGRESS && ++cnt_restarts );

    TEST_ASSERT( ret == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xR ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.Y, &yR ) == 0 );

    TEST_ASSERT( cnt_restarts >= min_restarts );
    TEST_ASSERT( cnt_restarts <= max_restarts );

    /* Do we leak memory when aborting an operation?
     * This test only makes sense when we actually restart */
    if( min_restarts > 0 )
    {
        ret = mbedtls_ecp_muladd_restartable( &grp, &R,
                                              &u1, &grp.G, &u2, &Q, &ctx );
        TEST_ASSERT( ret == MBEDTLS_ERR_ECP_IN_PROGRESS );
    }

exit:
    mbedtls_ecp_restart_free( &ctx );
    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &R );
    mbedtls_ecp_point_free( &Q );
    mbedtls_mpi_free( &u1 ); mbedtls_mpi_free( &u2 );
    mbedtls_mpi_free( &xR ); mbedtls_mpi_free( &yR );
}

void test_ecp_muladd_restart_wrapper( void ** params )
{

    test_ecp_muladd_restart( *( (int *) params[0] ), (char *) params[1], (char *) params[2], (char *) params[3], (char *) params[4], (char *) params[5], (char *) params[6], *( (int *) params[7] ), *( (int *) params[8] ), *( (int *) params[9] ) );
}
#endif /* MBEDTLS_ECP_RESTARTABLE */
#line 570 "suites/test_suite_ecp.function"
void test_ecp_test_vect( int id, char * dA_str, char * xA_str, char * yA_str,
                    char * dB_str, char * xB_str, char * yB_str,
                    char * xZ_str, char * yZ_str )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point R;
    mbedtls_mpi dA, xA, yA, dB, xB, yB, xZ, yZ;
    rnd_pseudo_info rnd_info;

    mbedtls_ecp_group_init( &grp ); mbedtls_ecp_point_init( &R );
    mbedtls_mpi_init( &dA ); mbedtls_mpi_init( &xA ); mbedtls_mpi_init( &yA ); mbedtls_mpi_init( &dB );
    mbedtls_mpi_init( &xB ); mbedtls_mpi_init( &yB ); mbedtls_mpi_init( &xZ ); mbedtls_mpi_init( &yZ );
    memset( &rnd_info, 0x00, sizeof( rnd_pseudo_info ) );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );

    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &grp.G ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &dA, 16, dA_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &xA, 16, xA_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &yA, 16, yA_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &dB, 16, dB_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &xB, 16, xB_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &yB, 16, yB_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &xZ, 16, xZ_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &yZ, 16, yZ_str ) == 0 );

    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dA, &grp.G,
                          &rnd_pseudo_rand, &rnd_info ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xA ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.Y, &yA ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );
    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dB, &R, NULL, NULL ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xZ ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.Y, &yZ ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );

    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dB, &grp.G, NULL, NULL ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xB ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.Y, &yB ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );
    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dA, &R,
                          &rnd_pseudo_rand, &rnd_info ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xZ ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.Y, &yZ ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );

exit:
    mbedtls_ecp_group_free( &grp ); mbedtls_ecp_point_free( &R );
    mbedtls_mpi_free( &dA ); mbedtls_mpi_free( &xA ); mbedtls_mpi_free( &yA ); mbedtls_mpi_free( &dB );
    mbedtls_mpi_free( &xB ); mbedtls_mpi_free( &yB ); mbedtls_mpi_free( &xZ ); mbedtls_mpi_free( &yZ );
}

void test_ecp_test_vect_wrapper( void ** params )
{

    test_ecp_test_vect( *( (int *) params[0] ), (char *) params[1], (char *) params[2], (char *) params[3], (char *) params[4], (char *) params[5], (char *) params[6], (char *) params[7], (char *) params[8] );
}
#line 625 "suites/test_suite_ecp.function"
void test_ecp_test_vec_x( int id, char * dA_hex, char * xA_hex, char * dB_hex,
                     char * xB_hex, char * xS_hex )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point R;
    mbedtls_mpi dA, xA, dB, xB, xS;
    rnd_pseudo_info rnd_info;

    mbedtls_ecp_group_init( &grp ); mbedtls_ecp_point_init( &R );
    mbedtls_mpi_init( &dA ); mbedtls_mpi_init( &xA );
    mbedtls_mpi_init( &dB ); mbedtls_mpi_init( &xB );
    mbedtls_mpi_init( &xS );
    memset( &rnd_info, 0x00, sizeof( rnd_pseudo_info ) );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );

    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &grp.G ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &dA, 16, dA_hex ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &dB, 16, dB_hex ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &xA, 16, xA_hex ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &xB, 16, xB_hex ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &xS, 16, xS_hex ) == 0 );

    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dA, &grp.G,
                          &rnd_pseudo_rand, &rnd_info ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xA ) == 0 );

    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dB, &R,
                          &rnd_pseudo_rand, &rnd_info ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xS ) == 0 );

    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dB, &grp.G, NULL, NULL ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xB ) == 0 );

    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dA, &R, NULL, NULL ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xS ) == 0 );

exit:
    mbedtls_ecp_group_free( &grp ); mbedtls_ecp_point_free( &R );
    mbedtls_mpi_free( &dA ); mbedtls_mpi_free( &xA );
    mbedtls_mpi_free( &dB ); mbedtls_mpi_free( &xB );
    mbedtls_mpi_free( &xS );
}

void test_ecp_test_vec_x_wrapper( void ** params )
{

    test_ecp_test_vec_x( *( (int *) params[0] ), (char *) params[1], (char *) params[2], (char *) params[3], (char *) params[4], (char *) params[5] );
}
#line 676 "suites/test_suite_ecp.function"
void test_ecp_fast_mod( int id, char * N_str )
{
    mbedtls_ecp_group grp;
    mbedtls_mpi N, R;

    mbedtls_mpi_init( &N ); mbedtls_mpi_init( &R );
    mbedtls_ecp_group_init( &grp );

    TEST_ASSERT( mbedtls_mpi_read_string( &N, 16, N_str ) == 0 );
    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );
    TEST_ASSERT( grp.modp != NULL );

    /*
     * Store correct result before we touch N
     */
    TEST_ASSERT( mbedtls_mpi_mod_mpi( &R, &N, &grp.P ) == 0 );

    TEST_ASSERT( grp.modp( &N ) == 0 );
    TEST_ASSERT( mbedtls_mpi_bitlen( &N ) <= grp.pbits + 3 );

    /*
     * Use mod rather than addition/subtraction in case previous test fails
     */
    TEST_ASSERT( mbedtls_mpi_mod_mpi( &N, &N, &grp.P ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &N, &R ) == 0 );

exit:
    mbedtls_mpi_free( &N ); mbedtls_mpi_free( &R );
    mbedtls_ecp_group_free( &grp );
}

void test_ecp_fast_mod_wrapper( void ** params )
{

    test_ecp_fast_mod( *( (int *) params[0] ), (char *) params[1] );
}
#line 709 "suites/test_suite_ecp.function"
void test_ecp_write_binary( int id, char * x, char * y, char * z, int format,
                       data_t * out, int blen, int ret )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point P;
    unsigned char buf[256];
    size_t olen;

    memset( buf, 0, sizeof( buf ) );

    mbedtls_ecp_group_init( &grp ); mbedtls_ecp_point_init( &P );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &P.X, 16, x ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &P.Y, 16, y ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &P.Z, 16, z ) == 0 );

    TEST_ASSERT( mbedtls_ecp_point_write_binary( &grp, &P, format,
                                   &olen, buf, blen ) == ret );

    if( ret == 0 )
    {
        TEST_ASSERT( hexcmp( buf, out->x, olen, out->len ) == 0 );
    }

exit:
    mbedtls_ecp_group_free( &grp ); mbedtls_ecp_point_free( &P );
}

void test_ecp_write_binary_wrapper( void ** params )
{
    data_t data5 = {(uint8_t *) params[5], *( (uint32_t *) params[6] )};

    test_ecp_write_binary( *( (int *) params[0] ), (char *) params[1], (char *) params[2], (char *) params[3], *( (int *) params[4] ), &data5, *( (int *) params[7] ), *( (int *) params[8] ) );
}
#line 741 "suites/test_suite_ecp.function"
void test_ecp_read_binary( int id, data_t * buf, char * x, char * y, char * z,
                      int ret )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point P;
    mbedtls_mpi X, Y, Z;


    mbedtls_ecp_group_init( &grp ); mbedtls_ecp_point_init( &P );
    mbedtls_mpi_init( &X ); mbedtls_mpi_init( &Y ); mbedtls_mpi_init( &Z );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &X, 16, x ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &Y, 16, y ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &Z, 16, z ) == 0 );

    TEST_ASSERT( mbedtls_ecp_point_read_binary( &grp, &P, buf->x, buf->len ) == ret );

    if( ret == 0 )
    {
        TEST_ASSERT( mbedtls_mpi_cmp_mpi( &P.X, &X ) == 0 );
        TEST_ASSERT( mbedtls_mpi_cmp_mpi( &P.Y, &Y ) == 0 );
        TEST_ASSERT( mbedtls_mpi_cmp_mpi( &P.Z, &Z ) == 0 );
    }

exit:
    mbedtls_ecp_group_free( &grp ); mbedtls_ecp_point_free( &P );
    mbedtls_mpi_free( &X ); mbedtls_mpi_free( &Y ); mbedtls_mpi_free( &Z );
}

void test_ecp_read_binary_wrapper( void ** params )
{
    data_t data1 = {(uint8_t *) params[1], *( (uint32_t *) params[2] )};

    test_ecp_read_binary( *( (int *) params[0] ), &data1, (char *) params[3], (char *) params[4], (char *) params[5], *( (int *) params[6] ) );
}
#line 774 "suites/test_suite_ecp.function"
void test_mbedtls_ecp_tls_read_point( int id, data_t * buf, char * x, char * y,
                                 char * z, int ret )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point P;
    mbedtls_mpi X, Y, Z;
    const unsigned char *vbuf = buf->x;


    mbedtls_ecp_group_init( &grp ); mbedtls_ecp_point_init( &P );
    mbedtls_mpi_init( &X ); mbedtls_mpi_init( &Y ); mbedtls_mpi_init( &Z );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &X, 16, x ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &Y, 16, y ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &Z, 16, z ) == 0 );

    TEST_ASSERT( mbedtls_ecp_tls_read_point( &grp, &P, &vbuf, buf->len ) == ret );

    if( ret == 0 )
    {
        TEST_ASSERT( mbedtls_mpi_cmp_mpi( &P.X, &X ) == 0 );
        TEST_ASSERT( mbedtls_mpi_cmp_mpi( &P.Y, &Y ) == 0 );
        TEST_ASSERT( mbedtls_mpi_cmp_mpi( &P.Z, &Z ) == 0 );
        TEST_ASSERT( (uint32_t)( vbuf - buf->x ) == buf->len );
    }

exit:
    mbedtls_ecp_group_free( &grp ); mbedtls_ecp_point_free( &P );
    mbedtls_mpi_free( &X ); mbedtls_mpi_free( &Y ); mbedtls_mpi_free( &Z );
}

void test_mbedtls_ecp_tls_read_point_wrapper( void ** params )
{
    data_t data1 = {(uint8_t *) params[1], *( (uint32_t *) params[2] )};

    test_mbedtls_ecp_tls_read_point( *( (int *) params[0] ), &data1, (char *) params[3], (char *) params[4], (char *) params[5], *( (int *) params[6] ) );
}
#line 809 "suites/test_suite_ecp.function"
void test_ecp_tls_write_read_point( int id )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point pt;
    unsigned char buf[256];
    const unsigned char *vbuf;
    size_t olen;

    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &pt );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );

    memset( buf, 0x00, sizeof( buf ) ); vbuf = buf;
    TEST_ASSERT( mbedtls_ecp_tls_write_point( &grp, &grp.G,
                    MBEDTLS_ECP_PF_COMPRESSED, &olen, buf, 256 ) == 0 );
    TEST_ASSERT( mbedtls_ecp_tls_read_point( &grp, &pt, &vbuf, olen )
                 == MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE );
    TEST_ASSERT( vbuf == buf + olen );

    memset( buf, 0x00, sizeof( buf ) ); vbuf = buf;
    TEST_ASSERT( mbedtls_ecp_tls_write_point( &grp, &grp.G,
                    MBEDTLS_ECP_PF_UNCOMPRESSED, &olen, buf, 256 ) == 0 );
    TEST_ASSERT( mbedtls_ecp_tls_read_point( &grp, &pt, &vbuf, olen ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &grp.G.X, &pt.X ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &grp.G.Y, &pt.Y ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &grp.G.Z, &pt.Z ) == 0 );
    TEST_ASSERT( vbuf == buf + olen );

    memset( buf, 0x00, sizeof( buf ) ); vbuf = buf;
    TEST_ASSERT( mbedtls_ecp_set_zero( &pt ) == 0 );
    TEST_ASSERT( mbedtls_ecp_tls_write_point( &grp, &pt,
                    MBEDTLS_ECP_PF_COMPRESSED, &olen, buf, 256 ) == 0 );
    TEST_ASSERT( mbedtls_ecp_tls_read_point( &grp, &pt, &vbuf, olen ) == 0 );
    TEST_ASSERT( mbedtls_ecp_is_zero( &pt ) );
    TEST_ASSERT( vbuf == buf + olen );

    memset( buf, 0x00, sizeof( buf ) ); vbuf = buf;
    TEST_ASSERT( mbedtls_ecp_set_zero( &pt ) == 0 );
    TEST_ASSERT( mbedtls_ecp_tls_write_point( &grp, &pt,
                    MBEDTLS_ECP_PF_UNCOMPRESSED, &olen, buf, 256 ) == 0 );
    TEST_ASSERT( mbedtls_ecp_tls_read_point( &grp, &pt, &vbuf, olen ) == 0 );
    TEST_ASSERT( mbedtls_ecp_is_zero( &pt ) );
    TEST_ASSERT( vbuf == buf + olen );

exit:
    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &pt );
}

void test_ecp_tls_write_read_point_wrapper( void ** params )
{

    test_ecp_tls_write_read_point( *( (int *) params[0] ) );
}
#line 861 "suites/test_suite_ecp.function"
void test_mbedtls_ecp_tls_read_group( data_t * buf, int result, int bits,
                                 int record_len )
{
    mbedtls_ecp_group grp;
    const unsigned char *vbuf = buf->x;
    int ret;

    mbedtls_ecp_group_init( &grp );

    ret = mbedtls_ecp_tls_read_group( &grp, &vbuf, buf->len );

    TEST_ASSERT( ret == result );
    if( ret == 0)
    {
        TEST_ASSERT( mbedtls_mpi_bitlen( &grp.P ) == (size_t) bits );
        TEST_ASSERT( vbuf - buf->x ==  record_len);
    }

exit:
    mbedtls_ecp_group_free( &grp );
}

void test_mbedtls_ecp_tls_read_group_wrapper( void ** params )
{
    data_t data0 = {(uint8_t *) params[0], *( (uint32_t *) params[1] )};

    test_mbedtls_ecp_tls_read_group( &data0, *( (int *) params[2] ), *( (int *) params[3] ), *( (int *) params[4] ) );
}
#line 885 "suites/test_suite_ecp.function"
void test_ecp_tls_write_read_group( int id )
{
    mbedtls_ecp_group grp1, grp2;
    unsigned char buf[10];
    const unsigned char *vbuf = buf;
    size_t len;
    int ret;

    mbedtls_ecp_group_init( &grp1 );
    mbedtls_ecp_group_init( &grp2 );
    memset( buf, 0x00, sizeof( buf ) );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp1, id ) == 0 );

    TEST_ASSERT( mbedtls_ecp_tls_write_group( &grp1, &len, buf, 10 ) == 0 );
    ret = mbedtls_ecp_tls_read_group( &grp2, &vbuf, len );
    TEST_ASSERT( ret == 0 );

    if( ret == 0 )
    {
        TEST_ASSERT( mbedtls_mpi_cmp_mpi( &grp1.N, &grp2.N ) == 0 );
        TEST_ASSERT( grp1.id == grp2.id );
    }

exit:
    mbedtls_ecp_group_free( &grp1 );
    mbedtls_ecp_group_free( &grp2 );
}

void test_ecp_tls_write_read_group_wrapper( void ** params )
{

    test_ecp_tls_write_read_group( *( (int *) params[0] ) );
}
#line 916 "suites/test_suite_ecp.function"
void test_mbedtls_ecp_check_privkey( int id, char * key_hex, int ret )
{
    mbedtls_ecp_group grp;
    mbedtls_mpi d;

    mbedtls_ecp_group_init( &grp );
    mbedtls_mpi_init( &d );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &d, 16, key_hex ) == 0 );

    TEST_ASSERT( mbedtls_ecp_check_privkey( &grp, &d ) == ret );

exit:
    mbedtls_ecp_group_free( &grp );
    mbedtls_mpi_free( &d );
}

void test_mbedtls_ecp_check_privkey_wrapper( void ** params )
{

    test_mbedtls_ecp_check_privkey( *( (int *) params[0] ), (char *) params[1], *( (int *) params[2] ) );
}
#line 936 "suites/test_suite_ecp.function"
void test_mbedtls_ecp_check_pub_priv( int id_pub, char * Qx_pub, char * Qy_pub,
                                 int id, char * d, char * Qx, char * Qy,
                                 int ret )
{
    mbedtls_ecp_keypair pub, prv;

    mbedtls_ecp_keypair_init( &pub );
    mbedtls_ecp_keypair_init( &prv );

    if( id_pub != MBEDTLS_ECP_DP_NONE )
        TEST_ASSERT( mbedtls_ecp_group_load( &pub.grp, id_pub ) == 0 );
    TEST_ASSERT( mbedtls_ecp_point_read_string( &pub.Q, 16, Qx_pub, Qy_pub ) == 0 );

    if( id != MBEDTLS_ECP_DP_NONE )
        TEST_ASSERT( mbedtls_ecp_group_load( &prv.grp, id ) == 0 );
    TEST_ASSERT( mbedtls_ecp_point_read_string( &prv.Q, 16, Qx, Qy ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &prv.d, 16, d ) == 0 );

    TEST_ASSERT( mbedtls_ecp_check_pub_priv( &pub, &prv ) == ret );

exit:
    mbedtls_ecp_keypair_free( &pub );
    mbedtls_ecp_keypair_free( &prv );
}

void test_mbedtls_ecp_check_pub_priv_wrapper( void ** params )
{

    test_mbedtls_ecp_check_pub_priv( *( (int *) params[0] ), (char *) params[1], (char *) params[2], *( (int *) params[3] ), (char *) params[4], (char *) params[5], (char *) params[6], *( (int *) params[7] ) );
}
#line 963 "suites/test_suite_ecp.function"
void test_mbedtls_ecp_gen_keypair( int id )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point Q;
    mbedtls_mpi d;
    rnd_pseudo_info rnd_info;

    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &Q );
    mbedtls_mpi_init( &d );
    memset( &rnd_info, 0x00, sizeof( rnd_pseudo_info ) );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );

    TEST_ASSERT( mbedtls_ecp_gen_keypair( &grp, &d, &Q, &rnd_pseudo_rand, &rnd_info )
                 == 0 );

    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &Q ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_privkey( &grp, &d ) == 0 );

exit:
    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &Q );
    mbedtls_mpi_free( &d );
}

void test_mbedtls_ecp_gen_keypair_wrapper( void ** params )
{

    test_mbedtls_ecp_gen_keypair( *( (int *) params[0] ) );
}
#line 991 "suites/test_suite_ecp.function"
void test_mbedtls_ecp_gen_key( int id )
{
    mbedtls_ecp_keypair key;
    rnd_pseudo_info rnd_info;

    mbedtls_ecp_keypair_init( &key );
    memset( &rnd_info, 0x00, sizeof( rnd_pseudo_info ) );

    TEST_ASSERT( mbedtls_ecp_gen_key( id, &key, &rnd_pseudo_rand, &rnd_info ) == 0 );

    TEST_ASSERT( mbedtls_ecp_check_pubkey( &key.grp, &key.Q ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_privkey( &key.grp, &key.d ) == 0 );

exit:
    mbedtls_ecp_keypair_free( &key );
}

void test_mbedtls_ecp_gen_key_wrapper( void ** params )
{

    test_mbedtls_ecp_gen_key( *( (int *) params[0] ) );
}
#if defined(MBEDTLS_SELF_TEST)
#line 1010 "suites/test_suite_ecp.function"
void test_ecp_selftest(  )
{
    TEST_ASSERT( mbedtls_ecp_self_test( 1 ) == 0 );
exit:
    ;
}

void test_ecp_selftest_wrapper( void ** params )
{
    (void)params;

    test_ecp_selftest(  );
}
#endif /* MBEDTLS_SELF_TEST */
#endif /* MBEDTLS_ECP_C */


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

#if defined(MBEDTLS_ECP_C)

        case 0:
            {
                *out_value = MBEDTLS_ECP_DP_BP512R1;
            }
            break;
        case 1:
            {
                *out_value = MBEDTLS_ECP_DP_BP384R1;
            }
            break;
        case 2:
            {
                *out_value = MBEDTLS_ECP_DP_BP256R1;
            }
            break;
        case 3:
            {
                *out_value = MBEDTLS_ECP_DP_SECP521R1;
            }
            break;
        case 4:
            {
                *out_value = MBEDTLS_ECP_DP_SECP384R1;
            }
            break;
        case 5:
            {
                *out_value = MBEDTLS_ECP_DP_SECP256R1;
            }
            break;
        case 6:
            {
                *out_value = MBEDTLS_ECP_DP_SECP224R1;
            }
            break;
        case 7:
            {
                *out_value = MBEDTLS_ECP_DP_SECP192R1;
            }
            break;
        case 8:
            {
                *out_value = MBEDTLS_ECP_DP_CURVE25519;
            }
            break;
        case 9:
            {
                *out_value = MBEDTLS_ERR_ECP_INVALID_KEY;
            }
            break;
        case 10:
            {
                *out_value = MBEDTLS_ECP_DP_SECP224K1;
            }
            break;
        case 11:
            {
                *out_value = MBEDTLS_ECP_PF_UNCOMPRESSED;
            }
            break;
        case 12:
            {
                *out_value = MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL;
            }
            break;
        case 13:
            {
                *out_value = MBEDTLS_ECP_PF_COMPRESSED;
            }
            break;
        case 14:
            {
                *out_value = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
            }
            break;
        case 15:
            {
                *out_value = MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;
            }
            break;
        case 16:
            {
                *out_value = MBEDTLS_ECP_DP_NONE;
            }
            break;
        case 17:
            {
                *out_value = MBEDTLS_ECP_DP_CURVE448;
            }
            break;
        case 18:
            {
                *out_value = MBEDTLS_ECP_DP_SECP192K1;
            }
            break;
        case 19:
            {
                *out_value = MBEDTLS_ECP_DP_SECP256K1;
            }
            break;
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

#if defined(MBEDTLS_ECP_C)

        case 0:
            {
#if defined(MBEDTLS_ECP_DP_BP512R1_ENABLED)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 1:
            {
#if defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 2:
            {
#if defined(MBEDTLS_ECP_DP_BP256R1_ENABLED)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 3:
            {
#if defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 4:
            {
#if defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 5:
            {
#if defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 6:
            {
#if defined(MBEDTLS_ECP_DP_SECP224R1_ENABLED)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 7:
            {
#if defined(MBEDTLS_ECP_DP_SECP192R1_ENABLED)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 8:
            {
#if defined(MBEDTLS_ECP_DP_CURVE25519_ENABLED)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 9:
            {
#if defined(MBEDTLS_ECP_DP_SECP224K1_ENABLED)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 10:
            {
#if defined(MBEDTLS_ECP_DP_CURVE448_ENABLED)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 11:
            {
#if defined(MBEDTLS_ECP_DP_SECP192K1_ENABLED)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 12:
            {
#if defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED)
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

#if defined(MBEDTLS_ECP_C)
    test_ecp_valid_param_wrapper,
#else
    NULL,
#endif
/* Function Id: 1 */

#if defined(MBEDTLS_ECP_C) && defined(MBEDTLS_CHECK_PARAMS) && !defined(MBEDTLS_PARAM_FAILED_ALT)
    test_ecp_invalid_param_wrapper,
#else
    NULL,
#endif
/* Function Id: 2 */

#if defined(MBEDTLS_ECP_C)
    test_mbedtls_ecp_curve_info_wrapper,
#else
    NULL,
#endif
/* Function Id: 3 */

#if defined(MBEDTLS_ECP_C)
    test_ecp_check_pub_wrapper,
#else
    NULL,
#endif
/* Function Id: 4 */

#if defined(MBEDTLS_ECP_C) && defined(MBEDTLS_ECP_RESTARTABLE)
    test_ecp_test_vect_restart_wrapper,
#else
    NULL,
#endif
/* Function Id: 5 */

#if defined(MBEDTLS_ECP_C) && defined(MBEDTLS_ECP_RESTARTABLE)
    test_ecp_muladd_restart_wrapper,
#else
    NULL,
#endif
/* Function Id: 6 */

#if defined(MBEDTLS_ECP_C)
    test_ecp_test_vect_wrapper,
#else
    NULL,
#endif
/* Function Id: 7 */

#if defined(MBEDTLS_ECP_C)
    test_ecp_test_vec_x_wrapper,
#else
    NULL,
#endif
/* Function Id: 8 */

#if defined(MBEDTLS_ECP_C)
    test_ecp_fast_mod_wrapper,
#else
    NULL,
#endif
/* Function Id: 9 */

#if defined(MBEDTLS_ECP_C)
    test_ecp_write_binary_wrapper,
#else
    NULL,
#endif
/* Function Id: 10 */

#if defined(MBEDTLS_ECP_C)
    test_ecp_read_binary_wrapper,
#else
    NULL,
#endif
/* Function Id: 11 */

#if defined(MBEDTLS_ECP_C)
    test_mbedtls_ecp_tls_read_point_wrapper,
#else
    NULL,
#endif
/* Function Id: 12 */

#if defined(MBEDTLS_ECP_C)
    test_ecp_tls_write_read_point_wrapper,
#else
    NULL,
#endif
/* Function Id: 13 */

#if defined(MBEDTLS_ECP_C)
    test_mbedtls_ecp_tls_read_group_wrapper,
#else
    NULL,
#endif
/* Function Id: 14 */

#if defined(MBEDTLS_ECP_C)
    test_ecp_tls_write_read_group_wrapper,
#else
    NULL,
#endif
/* Function Id: 15 */

#if defined(MBEDTLS_ECP_C)
    test_mbedtls_ecp_check_privkey_wrapper,
#else
    NULL,
#endif
/* Function Id: 16 */

#if defined(MBEDTLS_ECP_C)
    test_mbedtls_ecp_check_pub_priv_wrapper,
#else
    NULL,
#endif
/* Function Id: 17 */

#if defined(MBEDTLS_ECP_C)
    test_mbedtls_ecp_gen_keypair_wrapper,
#else
    NULL,
#endif
/* Function Id: 18 */

#if defined(MBEDTLS_ECP_C)
    test_mbedtls_ecp_gen_key_wrapper,
#else
    NULL,
#endif
/* Function Id: 19 */

#if defined(MBEDTLS_ECP_C) && defined(MBEDTLS_SELF_TEST)
    test_ecp_selftest_wrapper,
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
    const char *default_filename = "/ecp.datax";
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
int main_test_suite_ecp( int argc, const char *argv[] )
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
