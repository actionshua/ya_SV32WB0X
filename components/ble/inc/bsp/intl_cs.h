#ifndef INTL_CS_H
#define INTL_CS_H

#if (__ARM_ARCH_ISA_THUMB==1)
    #include "m0/intl_cs_m0.h"
#elif (__NDS32_ISA_V3M__==1)
    #include "n7/intl_cs_n7.h"
#else
    #include "osal.h"
    #include "sys/intc.h"
#endif

#endif /* end of include guard: INTL_CS_H */

