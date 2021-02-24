#ifndef _SVC_DEF_H_
#define _SVC_DEF_H_

#include "svc_def_n7.h"

#if 0
#if (__ARM_ARCH_ISA_THUMB==1)
#if defined(__SSV_LINUX_SIM__)

#define DEF_SVC(num, ret_type, func) ret_type func

#elif defined(__CC_ARM)

#define DEF_SVC(num, ret_type, func) ret_type __svc(num) func

#elif defined(__GNUC__)

#define DEF_SVC(num, ret_type, func) __attribute__((naked, noinline)) ret_type func

#elif defined(__ICCARM__)

#error not implement.

#else

#error not support.

#endif

    
#elif (__NDS32_ISA_V3M__==1)
    
#include "svc_def_n7.h"
#else
#error please check your mcu ISA.
#endif
#endif


#endif  /// end of _SVC_DEF_H_