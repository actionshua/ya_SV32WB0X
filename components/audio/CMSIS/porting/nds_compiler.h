
#ifndef __NDS_COMPILER_H
#define __NDS_COMPILER_H

#include <stdint.h>

#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE           static inline
#endif
#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE      __STATIC_INLINE
#endif
#ifndef   __RESTRICT
  #define __RESTRICT                             __restrict
#endif

#define  __ALIGNED(x) __attribute__((aligned(x)))

#endif /* __NDS_COMPILER_H */

