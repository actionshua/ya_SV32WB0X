#ifndef _SVC_IMPL_H_
#define _SVC_IMPL_H_

#include "soc_types.h"
extern u32 SVC_Handler_main(u32 svc_args1, u32 svc_args2, u32 svc_args3, u32 svc_args4, u32 svc_number);

#if 0
#if (__ARM_ARCH_ISA_THUMB==1)

#if defined(__SSV_LINUX_SIM__)

#define SVC(num, ret_type, func) \
    ret_type func { \
        return 0; \
    } \

#elif defined(__CC_ARM)

#define SVC(num, ret_type, func) ret_type __svc(num) func

#elif defined(__GNUC__)
#include "condor.h"

#define SVC(num, ret_type, func) \
_Pragma("GCC diagnostic push") \
_Pragma("GCC diagnostic ignored \"-Wreturn-type\"") \
_Pragma("GCC diagnostic ignored \"-Wunused-function\"") \
__attribute__((naked, noinline)) ret_type func \
{ \
    __ASM( \
            "svc %0\n\t" \
            "bx lr" \
            : \
            : "I" (num) \
            : "r0" \
         ); \
} \
_Pragma("GCC diagnostic pop")

#elif defined(__ICCARM__)

#error not implement.

#else

#error not support.

#endif

    
#elif (__NDS32_ISA_V3M__==1)
#include "svc_impl_n7.h"
    
#else
#error please check your mcu ISA.
#endif


#include "svc_impl_n7.h"
#endif

#endif  /// end of _SVC_IMPL_H_
