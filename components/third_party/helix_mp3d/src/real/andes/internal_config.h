/***************************************************************************
 * internal_config.h                                                             *
 *                                                                         *
 * Copyright (C) 2012-2016 Andes Technology Corporation                    *
 * All rights reserved.                                                    *
 ***************************************************************************/

/**
 * @defgroup config header file
 */

/**
 * This header file will be included for each C file with -include
 * while compiling. So any configuration or common definition can be
 * written here.
 */

#ifndef __INTERNAL_CONFIG_H__
#define __INTERNAL_CONFIG_H__

#ifdef  __cplusplus
extern "C"
{
#endif

#ifdef __NDS32_EXT_DSP__
#if __NDS32_EXT_DSP__
#ifndef ENA_DSP_ISA
#define ENA_DSP_ISA
#endif
#endif
#endif

#include "nds32_intrinsic.h"

#if defined(__NDS32_EXT_ZOL__) && (__NDS32_EXT_ZOL__ == 1)

#define FUNC_ATTR_NO_HWLOOP     __attribute__ ((no_ext_zol))
#define LOOP_HINT_NO_HWLOOP()   __nds32__no_ext_zol()

#else

#define FUNC_ATTR_NO_HWLOOP
#define LOOP_HINT_NO_HWLOOP()

#endif

#include "nds32_math_types.h"

//Use nonsaturation alogrithm for n10
//If "size" less than ((2^8)-1), there is no risk for overflow.
#define ENA_HIGHER_PERFORMANCE_DPROD_U8XQ15

//Use less cycles to calc atan2_q31 (from 848 to 268 cycles)
//Otherwise calc more precicsion.
#define ENA_HIGHER_PERFORMANCE_ATAN2_Q31

//Use higher accuracy for atan2_f32 ifdef "NDS32_EXT_FPU_SP"
#define ENA_LUT_ATAN

//Use higher performance but bigger size compare with Keil"
#define ENA_HIGHER_PERFORMANCE_MAX_AND_MIN

//Using special function to process F32 calulation by usign integer ALU.
#ifndef __NDS32_EXT_FPU_SP__
#define ENA_HIGHER_PERFORMANCE_F32_HMT
#endif

//Using not checking inf, -inf, NAN for higher performance.
#define ENA_HIGHER_PERFORMANCE_CONVERT_F32

//For Changes of CMSIS 1.4.4 (Changed to use linear interpolation)
//For Cos/Sin q31 and q15 functions,
//libdsp still uses Hermite table but change the interpolation to linear instead of Hermite.
//This can help to reduce the cycles but still has better accuracy than CMSIS.
#define ENA_CS_Q_HMT_TBL_LNR_INTP

#define FUNC_RESTRICT       __restrict
#ifdef ENA_DBG_MSG

#include "stdio.h"
#define DBGMSG printf
void dump_data_q15(q15_t *src, int size, char *disp_string);

#else //ENA_DBG_MSG

#define DBGMSG(...)
#define dump_data_q15(...)

#endif  //ENA_DBG_MSG

#ifdef ENA_DSP_MSG

#include "stdio.h"

#define DSPMSG printf
void print16_2(q31_t x, q31_t y);
#define P16_2(X,Y) DSPMSG("[%s] :", __FUNCTION__);print16_2(  X,Y)

#else   //ENA_DSP_MSG

#define DSPMSG(...)
#define print16_2(...)
#define P16_2(...)

#endif  //ENA_DSP_MSG



#ifdef  __cplusplus
}
#endif


#endif      //__INTERNAL_CONFIG_H__
