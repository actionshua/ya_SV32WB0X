#ifndef DRV_RAND_H
#define DRV_RAND_H

#include "pcb_config.h"
#if (MAIN_CHIP == P7003)
#include "inc/regs/p7003_reg.h"
#elif (MAIN_CHIP == P7005)
#include "soc_regs.h"
#else
#error please check your main chipid.
#endif
#include "condor.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "ssv_lib.h" // for REG32()

#define DEFAULT_SEED        (20150108)
#define CLR_BIT(value, bit) (value & ~(1UL<<bit))

__STATIC_INLINE void set_rand_seed(u32 seed)
{
//    REG32(ADR_LFSR_SEED) = seed;
//    REG32(ADR_LFSR_RAND);           
}
__STATIC_INLINE void rand_init(void)
{
//    set_rand_seed(DEFAULT_SEED);
}
__STATIC_INLINE void set_rand_poly(u32 poly)
{
//    REG32(ADR_LFSR_POLYNOMIO) = poly;
}
__STATIC_INLINE u32 get_rand_seed(void)
{
#if 1
//    return REG32(ADR_LFSR_SEED);
    return 0;
#else
    return GET_SEED;
#endif
}
__STATIC_INLINE u32 get_rand_poly(void)
{
//    return GET_POLY;
    return 0;
}
__STATIC_INLINE u32 get_rand(void)
{
#if 1
    return OS_Random();
#else
    return GET_RAND_32;
#endif
}

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: DRV_RAND_H */

