#ifndef _SSV_TYPES_H_
#define _SSV_TYPES_H_

#include "soc_types.h"
#include "soc_defs.h"
#include "attrs.h"

typedef volatile u32 SSV_REG;
typedef void *handle_t;

#define ALIGNED_4BYTE __attribute__((aligned(4)))

#define FX_SUCCESS                  0
#define FX_FAIL                     -1

#define SSV_API
#define SIM_API

// # used to indicate non-volatile data
// ## may add some compile attribute
#define NV_DATA ATTRIBUTE_SECTION_BLE_RESTORE

#define LOSABLE
//#define NV_DATA


// used to defined the irq handler
#define IRQ

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

#ifndef OFFSET_OF
#define OFFSET_OF(s, m) ((size_t)(&((s *)0)->m))
#endif 

#define CT_FIELD_ALIGN(_t, _f, _n)	STATIC_ASSERT((OFFSET_OF(_t, _f) % (_n) == 0), m)

#endif /* _SSV_TYPES_H _*/
