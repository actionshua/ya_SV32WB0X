#ifndef SYS_ASSERT_H
#define SYS_ASSERT_H

#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
/* These can't be used after statements in c89. */
#ifdef __COUNTER__
  #define STATIC_ASSERT(e,m) \
        ;enum { ASSERT_CONCAT(static_assert_, __COUNTER__) = 1/(!!(e)) }
#else
  /* This can't be used twice on the same line so ensure if using in headers
   * that the headers are not included twice (by wrapping in #ifndef...#endif)
   * Note it doesn't cause an issue when used on same line of separate modules
   * compiled with gcc -combine -fwhole-program.  */
  #define STATIC_ASSERT(e,m) \
        ;enum { ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!(e)) }
#endif

#define POWER_TWO_CHECK(M) \
    STATIC_ASSERT((((M)-1)&(M)) == 0, #M " must power of 2")


extern void vAssertCalled( const char *func, int line );
#define runtime_ASSERT( x ) \
    do { \
      if ( /*lint -save -e731 */ ( x ) == 0 /*lint -restore */) \
        vAssertCalled( __func__, __LINE__ ); \
    } while (0)

#endif /* end of include guard */
