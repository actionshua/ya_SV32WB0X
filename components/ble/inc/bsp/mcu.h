#ifndef MCU_H
#define MCU_H

#if (__ARM_ARCH_ISA_THUMB==1)
    #include "m0/intl_cs_m0.h"
#elif (__NDS32_ISA_V3M__==1)
    #include "n7/intl_cs_n7.h"
#else
#error please check your mcu ISA.
#endif



#endif /* end of include guard: MCU_H */
