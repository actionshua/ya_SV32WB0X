/***************************************************************************
 * nds32_dsp_isa.h                                                         *
 *                                                                         *
 * Copyright (C) 2012-2016 Andes Technology Corporation                    *
 * All rights reserved.                                                    *
 ***************************************************************************/

/**
 * @defgroup dsp isa header file
 */

#ifndef __INTERNAL_DSP_ISA_H__
#define __INTERNAL_DSP_ISA_H__

#ifdef  __cplusplus
extern "C"
{
#endif

#if (defined(NDS32_EB) || defined(__NDS32_EB__))
#define ENA_DSP_BE          1
#else
#define ENA_DSP_BE          0
#endif

#ifdef ENA_DSP_ISA

/**
 * Enable SAT extension is default in DSP. This flag should be
 * put before internal_isa.h to enable using native SAT ext.
 * instructions. Otherwise the C functions for SAT ext. will be
 * called instead.
 */
#define ENA_EXT_SAT_INST

/**
 * Just for testing or debugging DSP ISA.
 *
 * Define this flag can force to use C functions to simulate DSP
 * ISA, no matter if it is presented.
 *
 * Note: The performance or code size will be affected if this
 * flag is defined.
 */
//#define SIM_DSP_ISA_WITH_C

#include "internal_math_types.h"        //for union types
#include "internal_isa.h"

/**
 * Define this flag to assume all buffers are 4-byte alignment.
 * If user can not guarantee of alignment, it is possible to get
 * segmentation fault!
 * Since the endian causes the different byte-order, the algorithm should
 * be changed according to the little/big endian. However, for convienent
 * implementation, in big endian, we reversed element-order to satisfy the
 * algorithms which are designed for little endian even enabled NDS_DSP_ASSUME_ALIGNED.
 * (This increases cycles to move data).
 * On the other hand, in little endian, Both disabling or enabling NDS_DSP_ASSUME_ALIGNED
 * are worked, but enabling has better performance than disable since no data movement needed.
 */
#define NDS_DSP_ASSUME_ALIGNED

#ifdef SIM_DSP_ISA_WITH_C
#define DSP_FUNC_PRFX
#else
#define DSP_FUNC_PRFX       static inline
#endif

//Rounding modes enumuration type.
typedef enum
{
    round_down = 0,
    round_up = 1,
    round_near = 2,
    round_zero = 3
} roundMode_t;

//#if !defined(NDS_DSP_ASSUME_ALIGNED) || (ENA_DSP_BE)
//Need 4 entries for Radix4.
#define MAX_SIMD_UNALGN_ENTRY   4
extern union32_t simd_unalign_val[];
//#endif

// static inline union32_t *simd_pack_byte_32(q7_t *src, const int idx)
// {
// #if !defined(NDS_DSP_ASSUME_ALIGNED) || (ENA_DSP_BE)
//     //unaligned address
//     union32_t *ret;
//     ret = (union32_t *)&simd_unalign_val[idx];
//     ret->b8.b0 = src[0];
//     ret->b8.b1 = src[1];
//     ret->b8.b2 = src[2];
//     ret->b8.b3 = src[3];
//     return ret;
// #else
//     //aligned address
//     (void) idx;     //avoid compiler warning.
//     return (union32_t *)src;
// #endif
// }

// static inline void simd_save_byte_32(q7_t *dst, union32_t *src)
// {
// #if !defined(NDS_DSP_ASSUME_ALIGNED) || (ENA_DSP_BE)
//     //unaligned address
//     dst[0] = src->b8.b0;
//     dst[1] = src->b8.b1;
//     dst[2] = src->b8.b2;
//     dst[3] = src->b8.b3;
// #else
//     //aligned address
//     //no need to copy memory.
//     (void) dst;
//     (void) src;
// #endif
// }

static inline union32_t simd_load_8(q7_t *src, const int idx)
{
    union32_t ret;
    (void)idx;      //avoid compiler warning.
#if !defined(NDS_DSP_ASSUME_ALIGNED) || (TEST_BE)
    //|| (ENA_DSP_BE)
    ret.b8.b0 = src[0];
    ret.b8.b1 = src[1];
    ret.b8.b2 = src[2];
    ret.b8.b3 = src[3];
#else
    ret.w0 = *(q31_t *)src;
#endif
    return ret;
}

//This is for if it should load memory into register:
//union32_t temp = simd_load_16(src, 0)
//unaligned:
//  load two times for two shorts into one register
//aligned:
//  load one time for one word into one register
static inline union32_t simd_load_16(q15_t *src, const int idx)
{
    union32_t ret;
    (void)idx;      //avoid compiler warning.
#if !defined(NDS_DSP_ASSUME_ALIGNED) || (TEST_BE)
    ret.b16.h0 = src[0];
    ret.b16.h1 = src[1];
#else
    ret.w0 = *(q31_t *)src;
#endif
    return ret;
}

// static inline union32_t *simd_pack_short_32(q15_t *src, const int idx)
// {
//     union32_t *ret;
//     ret = (union32_t *)&simd_unalign_val[idx];
// #if !defined(NDS_DSP_ASSUME_ALIGNED) || (ENA_DSP_BE)
//     //unaligned address
//     ret->b16.h0 = src[0];
//     ret->b16.h1 = src[1];
//     return ret;
// #else
//     //aligned address
//     ret->w0 = *(q31_t *)src;
//     return ret;
// #endif
// }

static inline void simd_save_8(q7_t *dst, q31_t val)
{
#if !defined(NDS_DSP_ASSUME_ALIGNED) || (TEST_BE)
    //unaligned address
    union32_t temp;
    temp.w0 = val;
    dst[0] = temp.b8.b0;
    dst[1] = temp.b8.b1;
    dst[2] = temp.b8.b2;
    dst[3] = temp.b8.b3;
#else
    //aligned address
    *(q31_t *)dst = val;
#endif
}

static inline void simd_save_16(q15_t *dst, q31_t val)
{
#if !defined(NDS_DSP_ASSUME_ALIGNED) || (TEST_BE)
    //unaligned address
    union32_t temp;
    temp.w0 = val;
    dst[0] = temp.b16.h0;
    dst[1] = temp.b16.h1;
#else
    //aligned address
    *(q31_t *)dst = val;
#endif
}

// static inline void simd_save_short_32(q15_t *dst, union32_t *src)
// {
// #if !defined(NDS_DSP_ASSUME_ALIGNED) || (ENA_DSP_BE)
//     //unaligned address
//     dst[0] = src->b16.h0;
//     dst[1] = src->b16.h1;
// #else
//     //aligned address
//     *(q31_t *)dst = src->w0;
// #endif
// }

#define NDS_DSP_CLZ             NDS_ISA_CLZ

//clips and clip instructions are base-line.
//Y: from bit 0 to bit 31
#define NDS_DSP_CLIPS           NDS_ISA_CLIPS
#define NDS_DSP_CLIP            NDS_ISA_CLIP

//Y: from 1 bit to 32 bits.
#define NDS_DSP_SATS            NDS_ISA_SATS
#define NDS_DSP_SAT             NDS_ISA_SAT

//Performance extension
#define NDS_DSP_ABS             NDS_ISA_ABS

//Performance extension V2
#define NDS_DSP_PBSADA          __nds32__pbsada
#define NDS_DSP_FFB             __nds32__ffb

//Baseline V1
#define NDS_DSP_SVA             __nds32__sva
#define NDS_DSP_SVS             __nds32__svs

//Baseline V2
#define NDS_DSP_MULR64          NDS_ISA_MULR64
#define NDS_DSP_MULSR64         NDS_ISA_MULSR64

#define NDS_DSP_RDOV            NDS_ISA_RDOV
#define NDS_DSP_CLOV            NDS_ISA_CLOV
#define NDS_DSP_KADDW           NDS_ISA_KADDW
#define NDS_DSP_KSUBW           NDS_ISA_KSUBW
#define NDS_DSP_KADDH           NDS_ISA_KADDH
#define NDS_DSP_KSUBH           NDS_ISA_KSUBH
#define NDS_DSP_KDMBB           NDS_ISA_KDMBB
#define NDS_DSP_KDMBT           NDS_ISA_KDMBT
#define NDS_DSP_KDMTB           NDS_ISA_KDMTB
#define NDS_DSP_KDMTT           NDS_ISA_KDMTT
#define NDS_DSP_KHMBB           NDS_ISA_KHMBB
#define NDS_DSP_KHMBT           NDS_ISA_KHMBT
#define NDS_DSP_KHMTB           NDS_ISA_KHMTB
#define NDS_DSP_KHMTT           NDS_ISA_KHMTT
#define NDS_DSP_KSLRAW          NDS_ISA_KSLRAW

#ifndef SIM_DSP_ISA_WITH_C

//DSP SIMD instructions
#define NDS_DSP_RADDW(X, Y)         (q31_t)     __nds32__raddw      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_URADDW(X, Y)        (uint32_t)  __nds32__uraddw     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_RSUBW(X, Y)         (q31_t)     __nds32__rsubw      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_URSUBW(X, Y)        (uint32_t)  __nds32__ursubw     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_RADD16(X, Y)        (q31_t)     __nds32__radd16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_KADD16(X, Y)        (q31_t)     __nds32__kadd16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_RSUB16(X, Y)        (q31_t)     __nds32__rsub16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_KSUB16(X, Y)        (q31_t)     __nds32__ksub16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_RCRAS16(X, Y)       (q31_t)     __nds32__rcras16    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_KCRAS16(X, Y)       (q31_t)     __nds32__kcras16    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_RCRSA16(X, Y)       (q31_t)     __nds32__rcrsa16    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_KCRSA16(X, Y)       (q31_t)     __nds32__kcrsa16    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_KADD8(X, Y)         (q31_t)     __nds32__kadd8      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_KSUB8(X, Y)         (q31_t)     __nds32__ksub8      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_ADD16(X, Y)         (q31_t)     __nds32__add16      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_URADD16(X, Y)       (uint32_t)  __nds32__uradd16    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UKADD16(X, Y)       (uint32_t)  __nds32__ukadd16    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SUB16(X, Y)         (q31_t)     __nds32__sub16      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_URSUB16(X, Y)       (uint32_t)  __nds32__ursub16    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UKSUB16(X, Y)       (uint32_t)  __nds32__uksub16    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_CRAS16(X, Y)        (q31_t)     __nds32__cras16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_URCRAS16(X, Y)      (uint32_t)  __nds32__urcras16   ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UKCRAS16(X, Y)      (uint32_t)  __nds32__ukcras16   ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_CRSA16(X, Y)        (q31_t)     __nds32__crsa16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_URCRSA16(X, Y)      (uint32_t)  __nds32__urcrsa16   ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UKCRSA16(X, Y)      (uint32_t)  __nds32__ukcrsa16   ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_ADD8(X, Y)          (q31_t)     __nds32__add8       ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_RADD8(X, Y)         (q31_t)     __nds32__radd8      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_URADD8(X, Y)        (uint32_t)  __nds32__uradd8     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UKADD8(X, Y)        (uint32_t)  __nds32__ukadd8     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SUB8(X, Y)          (q31_t)     __nds32__sub8       ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SRSUB8(X, Y)        (q31_t)     __nds32__srsub8     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_URSUB8(X, Y)        (uint32_t)  __nds32__ursub8     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UKSUB8(X, Y)        (uint32_t)  __nds32__uksub8     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMMUL(X, Y)         (q31_t)     __nds32__smmul      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMMUL_U(X, Y)       (q31_t)     __nds32__smmul_u    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_KMMAC(ACC, X, Y)    (q31_t)     __nds32__kmmac      ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KMMSB(ACC, X, Y)    (q31_t)     __nds32__kmmsb      ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KMMAC_U(ACC, X, Y)  (q31_t)     __nds32__kmmac_u    ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KMMSB_U(ACC, X, Y)  (q31_t)     __nds32__kmmsb_u    ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KWMMUL(X, Y)        (q31_t)     __nds32__kwmmul     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_KWMMUL_U(X, Y)      (q31_t)     __nds32__kwmmul_u   ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMBB(X, Y)          (q31_t)     __nds32__smbb       ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMBT(X, Y)          (q31_t)     __nds32__smbt       ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMTT(X, Y)          (q31_t)     __nds32__smtt       ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_KMABB(ACC, X, Y)    (q31_t)     __nds32__kmabb     ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KMABT(ACC, X, Y)    (q31_t)     __nds32__kmabt     ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KMATT(ACC, X, Y)    (q31_t)     __nds32__kmatt      ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KMDA(X, Y)          (q31_t)     __nds32__kmda       ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_KMXDA(X, Y)         (q31_t)     __nds32__kmxda      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMDS(X, Y)          (q31_t)     __nds32__smds       ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMDRS(X, Y)         (q31_t)     __nds32__smdrs      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMXDS(X, Y)         (q31_t)     __nds32__smxds      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_KMADA(ACC, X, Y)    (q31_t)     __nds32__kmada      ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KMSDA(ACC, X, Y)    (q31_t)     __nds32__kmsda      ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KMSXDA(ACC, X, Y)   (q31_t)     __nds32__kmsxda     ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KMAXDA(ACC, X, Y)   (q31_t)     __nds32__kmaxda     ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KMADS(ACC, X, Y)    (q31_t)     __nds32__kmads      ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KMADRS(ACC, X, Y)   (q31_t)     __nds32__kmadrs     ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KMAXDS(ACC, X, Y)   (q31_t)     __nds32__kmaxds     ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_SMMWB(X, Y)         (q31_t)     __nds32__smmwb      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMMWB_U(X, Y)       (q31_t)     __nds32__smmwb_u    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMMWT(X, Y)         (q31_t)     __nds32__smmwt      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMMWT_U(X, Y)       (q31_t)     __nds32__smmwt_u    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_KMMAWB(ACC, X, Y)   (q31_t)     __nds32__kmmawb     ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KMMAWB_U(ACC, X, Y) (q31_t)     __nds32__kmmawb_u   ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KMMAWT(ACC, X, Y)   (q31_t)     __nds32__kmmawt     ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_KMMAWT_U(ACC, X, Y) (q31_t)     __nds32__kmmawt_u   ((q31_t) ACC, (q31_t) X, (q31_t) Y)
#define NDS_DSP_SMALBB(ACC, X, Y)   (q63_t)     __nds32__smalbb     ((q63_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMALBT(ACC, X, Y)   (q63_t)     __nds32__smalbt     ((q63_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMALTT(ACC, X, Y)   (q63_t)     __nds32__smaltt     ((q63_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMALDA(ACC, X, Y)   (q63_t)     __nds32__smalda     ((q63_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMALXDA(ACC, X, Y)  (q63_t)     __nds32__smalxda    ((q63_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMALDS(ACC, X, Y)   (q63_t)     __nds32__smalds     ((q63_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMALDRS(ACC, X, Y)  (q63_t)     __nds32__smaldrs    ((q63_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMSLDA(ACC, X, Y)   (q63_t)     __nds32__smslda     ((q63_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMSLXDA(ACC, X, Y)  (q63_t)     __nds32__smslxda    ((q63_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMALXDS(ACC, X, Y)  (q63_t)     __nds32__smalxds    ((q63_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UMAR64(ACC, X, Y)   (uint64_t)  __nds32__umar64     ((uint64_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMAR64(ACC, X, Y)   (q63_t)     __nds32__smar64     ((q63_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UMSR64(ACC, X, Y)   (uint64_t)  __nds32__umsr64     ((uint64_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UMUL16(X, Y)        (uint64_t)  __nds32__umul16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMSR64(ACC, X, Y)   (q63_t)     __nds32__smsr64     ((q63_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SRL16(X, SH)        (q31_t)     __nds32__srl16      ((uint32_t) X, (uint32_t) SH)
#define NDS_DSP_SRLI16              NDS_DSP_SRL16
#define NDS_DSP_SRL16_U(X, SH)      (q31_t)     __nds32__sr16_u     ((uint32_t) X, (uint32_t) SH)
#define NDS_DSP_SRLI16_U            NDS_DSP_SRL16_U
#define NDS_DSP_SRA16(X, SH)        (q31_t)     __nds32__sra16      ((uint32_t) X, (uint32_t) SH)
#define NDS_DSP_SRAI16              NDS_DSP_SRA16
#define NDS_DSP_SLL16(X, SH)        (q31_t)     __nds32__sll16      ((uint32_t) X, (uint32_t) SH)
#define NDS_DSP_SLLI16              NDS_DSP_SLL16
#define NDS_DSP_PKTT16(X, Y)        (q31_t)     __nds32__pktt16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_PKBB16(X, Y)        (q31_t)     __nds32__pkbb16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_PKBT16(X, Y)        (q31_t)     __nds32__pkbt16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_PKTB16(X, Y)        (q31_t)     __nds32__pktb16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SUNPKD820(X)        (q31_t)     __nds32__sunpkd820   ((uint32_t) X)
#define NDS_DSP_SUNPKD831(X)        (q31_t)     __nds32__sunpkd831   ((uint32_t) X)
#define NDS_DSP_SUNPKD810(X)        (q31_t)     __nds32__sunpkd810   ((uint32_t) X)
#define NDS_DSP_SUNPKD830(X)        (q31_t)     __nds32__sunpkd830   ((uint32_t) X)
#define NDS_DSP_ZUNPKD820(X)        (uint32_t)  __nds32__zunpkd820   ((uint32_t) X)
#define NDS_DSP_ZUNPKD831(X)        (uint32_t)  __nds32__zunpkd831   ((uint32_t) X)
#define NDS_DSP_ZUNPKD810(X)        (uint32_t)  __nds32__zunpkd810   ((uint32_t) X)
#define NDS_DSP_ZUNPKD830(X)        (uint32_t)  __nds32__zunpkd830   ((uint32_t) X)
#define NDS_DSP_BITREV(X, BIT_SIZE) (uint32_t)  __nds32__bitrev     ((uint32_t) X, (uint32_t) BIT_SIZE)
#define NDS_DSP_BITREVI             NDS_DSP_BITREV
#define NDS_DSP_UCLIP32             __nds32__clip
#define NDS_DSP_SCLIP32             __nds32__clips
#define NDS_DSP_UCLIP16(X, BIT_IDX) (uint32_t)  __nds32__uclip16    ((uint32_t) X, (uint32_t) BIT_IDX)
#define NDS_DSP_SCLIP16(X, BIT_IDX) (uint32_t)  __nds32__sclip16    ((uint32_t) X, (uint32_t) BIT_IDX)
#define NDS_DSP_CMPEQ8(X, Y)        (q31_t)     __nds32__cmpeq8     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_CMPEQ16(X, Y)       (q31_t)     __nds32__cmpeq16    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SCMPLT8(X, Y)       (q31_t)     __nds32__scmplt8    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SCMPLT16(X, Y)      (q31_t)     __nds32__scmplt16   ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UCMPLT8(X, Y)       (uint32_t)  __nds32__ucmplt8    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UCMPLT16(X, Y)      (uint32_t)  __nds32__ucmplt16   ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SCMPLE8(X, Y)       (q31_t)     __nds32__scmple8    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SCMPLE16(X, Y)      (q31_t)     __nds32__scmple16   ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UCMPLE8(X, Y)       (uint32_t)  __nds32__ucmple8    ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UCMPLE16(X, Y)      (uint32_t)  __nds32__ucmple16   ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_BPICK(X,Y,SEL_CTL)  (uint32_t)  __nds32__bpick      ((uint32_t) X, (uint32_t) Y, (uint32_t) SEL_CTL)
#define NDS_DSP_INSB(X, Y, SEL)     (q31_t)     __nds32__insb       ((uint32_t) X, (uint32_t) Y, (uint32_t) SEL)
#define NDS_DSP_SMIN8(X, Y)         (q31_t)     __nds32__smin8      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UMIN8(X, Y)         (uint32_t)  __nds32__umin8      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMIN16(X, Y)        (q31_t)     __nds32__smin16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UMIN16(X, Y)        (uint32_t)  __nds32__umin16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMAX8(X, Y)         (q31_t)     __nds32__smax8      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UMAX8(X, Y)         (uint32_t)  __nds32__umax8      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMAX16(X, Y)        (q31_t)     __nds32__smax16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UMAX16(X, Y)        (uint32_t)  __nds32__umax16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_KSLL16(X, SH)       (q31_t)     __nds32__ksll16     ((uint32_t) X, (uint32_t) SH)
#define NDS_DSP_KSLLI16             NDS_DSP_KSLL16
#define NDS_DSP_KSLL(X, SH)         (q31_t)     __nds32__ksll       ((q31_t) X, (uint32_t) SH)
#define NDS_DSP_KSLLI               NDS_DSP_KSLL
#define NDS_DSP_SRA16_U(X, SH)      (q31_t)     __nds32__sra16_u    ((q31_t) X, (uint32_t) SH)
#define NDS_DSP_SRAI16_U            NDS_DSP_SRA16_U
#define NDS_DSP_SRA_U(X, SH)        (q31_t)     __nds32__sra_u      ((q31_t) X, (uint32_t) SH)
#define NDS_DSP_SRAI_U              NDS_DSP_SRA_U
#define NDS_DSP_KSLRA16(X, SH)      (q31_t)     __nds32__kslra16    ((uint32_t) X, (uint32_t) SH)
#define NDS_DSP_KSLRA16_U(X, SH)    (q31_t)     __nds32__kslra16_u  ((uint32_t) X, (uint32_t) SH)
#define NDS_DSP_KSLRAW_U(X, SH)     (q31_t)     __nds32__kslraw_u   ((uint32_t) X, (uint32_t) SH)
#define NDS_DSP_KABS                __nds32__abs
#define NDS_DSP_KABS16(X)           (q31_t)     __nds32__kabs16     ((uint32_t) X)
#define NDS_DSP_KABS8(X)            (q31_t)     __nds32__kabs8      ((uint32_t) X)
#define NDS_DSP_KHM16(X, Y)         (q31_t)     __nds32__khm16      ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_KHMX16(X, Y)        (q31_t)     __nds32__khmx16     ((uint32_t) X, (uint32_t) Y)
#define NDS_DSP_SMAL(ACC, X)        (q63_t)     __nds32__smal       ((q63_t) ACC, (q31_t) X)
#define NDS_DSP_WEXT(X, LSB_IDX)    (q31_t)     __nds32__wext       ((q63_t) X, (uint32_t) LSB_IDX)
#define NDS_DSP_WEXTI               NDS_DSP_WEXT
#define NDS_DSP_ADD64(X, Y)         (q63_t)     __nds32__add64      ((q63_t) X, (q63_t) Y)
#define NDS_DSP_SUB64(X, Y)         (q63_t)     __nds32__sub64      ((q63_t) X, (q63_t) Y)
#define NDS_DSP_RADD64(X, Y)        (q63_t)     __nds32__radd64     ((q63_t) X, (q63_t) Y)
#define NDS_DSP_RSUB64(X, Y)        (q63_t)     __nds32__rsub64     ((q63_t) X, (q63_t) Y)
#define NDS_DSP_URADD64(X, Y)       (uint64_t)  __nds32__uradd64    ((uint64_t) X, (uint64_t) Y)
#define NDS_DSP_URSUB64(X, Y)       (uint64_t)  __nds32__ursub64    ((uint64_t) X, (uint64_t) Y)
#define NDS_DSP_KADD64(X, Y)        (q63_t)     __nds32__kadd64      ((q63_t) X, (q63_t) Y)
#define NDS_DSP_KSUB64(X, Y)        (q63_t)     __nds32__ksub64      ((q63_t) X, (q63_t) Y)
#define NDS_DSP_UKADD64(X, Y)       (uint64_t)  __nds32__ukadd64    ((uint64_t) X, (uint64_t) Y)
#define NDS_DSP_UKSUB64(X, Y)       (uint64_t)  __nds32__uksub64    ((uint64_t) X, (uint64_t) Y)
#define NDS_DSP_KMAR64(ACC, X, Y)   (q63_t)     __nds32__kmar64     ((q63_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_KMSR64(ACC, X, Y)   (q63_t)     __nds32__kmsr64     ((q63_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UKMAR64(ACC, X, Y)  (uint64_t)  __nds32__ukmar64    ((uint64_t) ACC, (uint32_t) X, (uint32_t) Y)
#define NDS_DSP_UKMSR64(ACC, X, Y)  (uint64_t)  __nds32__ukmsr64    ((uint64_t) ACC, (uint32_t) X, (uint32_t) Y)

#else   //SIM_DSP_ISA_WITH_C

//Simulate DSP ISA with C functions.
DSP_FUNC_PRFX q31_t NDS_DSP_RADDW(q31_t x, q31_t y)                              ;
DSP_FUNC_PRFX uint32_t NDS_DSP_URADDW(uint32_t x, uint32_t y)                     ;
DSP_FUNC_PRFX q31_t NDS_DSP_RSUBW(q31_t x, q31_t y)                              ;
DSP_FUNC_PRFX uint32_t NDS_DSP_URSUBW(uint32_t x, uint32_t y)                     ;
DSP_FUNC_PRFX q31_t NDS_DSP_RADD16(q31_t x, q31_t y)                             ;
DSP_FUNC_PRFX q31_t NDS_DSP_KADD16(q31_t x, q31_t y)                              ;
DSP_FUNC_PRFX q31_t NDS_DSP_RSUB16(q31_t x, q31_t y)                             ;
DSP_FUNC_PRFX q31_t NDS_DSP_KSUB16(q31_t x, q31_t y)                              ;
DSP_FUNC_PRFX q31_t NDS_DSP_RCRAS16(q31_t x, q31_t y)                            ;
DSP_FUNC_PRFX q31_t NDS_DSP_KCRAS16(q31_t x, q31_t y)                             ;
DSP_FUNC_PRFX q31_t NDS_DSP_RCRSA16(q31_t x, q31_t y)                            ;
DSP_FUNC_PRFX q31_t NDS_DSP_KCRSA16(q31_t x, q31_t y)                             ;
DSP_FUNC_PRFX q31_t NDS_DSP_KADD8(q31_t x, q31_t y)                               ;
DSP_FUNC_PRFX q31_t NDS_DSP_KSUB8(q31_t x, q31_t y)                               ;
DSP_FUNC_PRFX q31_t NDS_DSP_ADD16(q31_t x, q31_t y)                              ;
// DSP_FUNC_PRFX uint32_t NDS_DSP_UADD16(uint32_t x, uint32_t y)                     ;
DSP_FUNC_PRFX uint32_t NDS_DSP_URADD16(uint32_t x, uint32_t y)                    ;
DSP_FUNC_PRFX uint32_t NDS_DSP_UKADD16(uint32_t x, uint32_t y)                    ;
DSP_FUNC_PRFX q31_t NDS_DSP_SUB16(q31_t x, q31_t y)                              ;
// DSP_FUNC_PRFX uint32_t NDS_DSP_USUB16(uint32_t x, uint32_t y)                     ;
DSP_FUNC_PRFX uint32_t NDS_DSP_URSUB16(uint32_t x, uint32_t y)                    ;
DSP_FUNC_PRFX uint32_t NDS_DSP_UKSUB16(uint32_t x, uint32_t y)                    ;
DSP_FUNC_PRFX q31_t NDS_DSP_CRAS16(q31_t x, q31_t y)                             ;
// DSP_FUNC_PRFX uint32_t NDS_DSP_UCRAS16(uint32_t x, uint32_t y)                    ;
DSP_FUNC_PRFX uint32_t NDS_DSP_URCRAS16(uint32_t x, uint32_t y)                   ;
DSP_FUNC_PRFX uint32_t NDS_DSP_UKCRAS16(uint32_t x, uint32_t y)                   ;
DSP_FUNC_PRFX q31_t NDS_DSP_CRSA16(q31_t x, q31_t y)                             ;
// DSP_FUNC_PRFX uint32_t NDS_DSP_UCRSA16(uint32_t x, uint32_t y)                    ;
DSP_FUNC_PRFX uint32_t NDS_DSP_URCRSA16(uint32_t x, uint32_t y)                   ;
DSP_FUNC_PRFX uint32_t NDS_DSP_UKCRSA16(uint32_t x, uint32_t y)                   ;
DSP_FUNC_PRFX q31_t NDS_DSP_ADD8(q31_t x, q31_t y)                               ;
DSP_FUNC_PRFX q31_t NDS_DSP_RADD8(q31_t x, q31_t y)                              ;
// DSP_FUNC_PRFX uint32_t NDS_DSP_UADD8(uint32_t x, uint32_t y)                      ;
DSP_FUNC_PRFX uint32_t NDS_DSP_URADD8(uint32_t x, uint32_t y)                     ;
DSP_FUNC_PRFX uint32_t NDS_DSP_UKADD8(uint32_t x, uint32_t y)                     ;
DSP_FUNC_PRFX q31_t NDS_DSP_SUB8(q31_t x, q31_t y)                               ;
DSP_FUNC_PRFX q31_t NDS_DSP_SRSUB8(q31_t x, q31_t y)                              ;
// DSP_FUNC_PRFX uint32_t NDS_DSP_USUB8(uint32_t x, uint32_t y)                      ;
DSP_FUNC_PRFX uint32_t NDS_DSP_URSUB8(uint32_t x, uint32_t y)                     ;
DSP_FUNC_PRFX uint32_t NDS_DSP_UKSUB8(uint32_t x, uint32_t y)                     ;
DSP_FUNC_PRFX q31_t NDS_DSP_SMMUL(q31_t x, q31_t y)                                ;
DSP_FUNC_PRFX q31_t NDS_DSP_SMMUL_U(q31_t x, q31_t y)                               ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMMAC(q31_t acc, q31_t x, q31_t y)                   ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMMSB(q31_t acc, q31_t x, q31_t y)                   ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMMAC_U(q31_t acc, q31_t x, q31_t y)                  ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMMSB_U(q31_t acc, q31_t x, q31_t y)                  ;
DSP_FUNC_PRFX q31_t NDS_DSP_KWMMUL(q31_t x, q31_t y)                              ;
DSP_FUNC_PRFX q31_t NDS_DSP_KWMMUL_U(q31_t x, q31_t y)                             ;
DSP_FUNC_PRFX q31_t NDS_DSP_SMBB(q31_t x, q31_t y)                                ;
DSP_FUNC_PRFX q31_t NDS_DSP_SMBT(q31_t x, q31_t y)                                ;
DSP_FUNC_PRFX q31_t NDS_DSP_SMTT(q31_t x, q31_t y)                                ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMABB(q31_t acc, q31_t x, q31_t y)                    ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMABT(q31_t acc, q31_t x, q31_t y)                    ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMATT(q31_t acc, q31_t x, q31_t y)                    ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMDA(q31_t x, q31_t y)                                ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMXDA(q31_t x, q31_t y)                               ;
DSP_FUNC_PRFX q31_t NDS_DSP_SMDS(q31_t x, q31_t y)                                ;
DSP_FUNC_PRFX q31_t NDS_DSP_SMDRS(q31_t x, q31_t y)                               ;
DSP_FUNC_PRFX q31_t NDS_DSP_SMXDS(q31_t x, q31_t y)                               ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMADA(q31_t acc, q31_t x, q31_t y)                    ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMSDA(q31_t acc, q31_t x, q31_t y)                    ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMSXDA(q31_t acc, q31_t x, q31_t y)                   ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMAXDA(q31_t acc, q31_t x, q31_t y)                   ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMADS(q31_t acc, q31_t x, q31_t y)                    ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMADRS(q31_t acc, q31_t x, q31_t y)                   ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMAXDS(q31_t acc, q31_t x, q31_t y)                   ;
DSP_FUNC_PRFX q31_t NDS_DSP_SMMWB(q31_t x, q31_t y)                                ;
DSP_FUNC_PRFX q31_t NDS_DSP_SMMWB_U(q31_t x, q31_t y)                                ;
DSP_FUNC_PRFX q31_t NDS_DSP_SMMWT(q31_t x, q31_t y)                                ;
DSP_FUNC_PRFX q31_t NDS_DSP_SMMWT_U(q31_t x, q31_t y)                                ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMMAWB(q31_t acc, q31_t x, q31_t y)                    ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMMAWB_U(q31_t acc, q31_t x, q31_t y)                    ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMMAWT(q31_t acc, q31_t x, q31_t y)                    ;
DSP_FUNC_PRFX q31_t NDS_DSP_KMMAWT_U(q31_t acc, q31_t x, q31_t y)                    ;
DSP_FUNC_PRFX q63_t NDS_DSP_SMALBB(q63_t acc, q31_t x, q31_t y)                   ;
DSP_FUNC_PRFX q63_t NDS_DSP_SMALBT(q63_t acc, q31_t x, q31_t y)                   ;
DSP_FUNC_PRFX q63_t NDS_DSP_SMALTT(q63_t acc, q31_t x, q31_t y)                   ;
DSP_FUNC_PRFX q63_t NDS_DSP_SMALDA(q63_t acc, q31_t x, q31_t y)                   ;
DSP_FUNC_PRFX q63_t NDS_DSP_SMALXDA(q63_t acc, q31_t x, q31_t y)                  ;
DSP_FUNC_PRFX q63_t NDS_DSP_SMALDS(q63_t acc, q31_t x, q31_t y)                   ;
DSP_FUNC_PRFX q63_t NDS_DSP_SMALDRS(q63_t acc, q31_t x, q31_t y)                  ;
DSP_FUNC_PRFX q63_t NDS_DSP_SMSLDA(q63_t acc, q31_t x, q31_t y)                   ;
DSP_FUNC_PRFX q63_t NDS_DSP_SMSLXDA(q63_t acc, q31_t x, q31_t y)                  ;
DSP_FUNC_PRFX q63_t NDS_DSP_SMALXDS(q63_t acc, q31_t x, q31_t y)                  ;
// DSP_FUNC_PRFX q63_t NDS_DSP_MDALU(q63_t acc, q31_t x, q31_t y)                    ;
DSP_FUNC_PRFX uint64_t NDS_DSP_UMAR64(uint64_t acc, uint32_t x, uint32_t y)      ;
DSP_FUNC_PRFX q63_t NDS_DSP_SMAR64(q63_t acc, q31_t x, q31_t y)                 ;
DSP_FUNC_PRFX uint64_t NDS_DSP_UMSR64(uint64_t acc, uint32_t x, uint32_t y)      ;
DSP_FUNC_PRFX q63_t NDS_DSP_SMSR64(q63_t acc, q31_t x, q31_t y)                 ;
DSP_FUNC_PRFX q31_t NDS_DSP_SRLI16(q31_t x, IMM uint8_t sh)                       ;
DSP_FUNC_PRFX q31_t NDS_DSP_SRLI16_U(q31_t x, IMM uint8_t sh);
DSP_FUNC_PRFX q31_t NDS_DSP_SRL16(q31_t x, uint8_t sh)                       ;
DSP_FUNC_PRFX q31_t NDS_DSP_SRL16_U(q31_t x, uint8_t sh);
DSP_FUNC_PRFX q31_t NDS_DSP_SRAI16(q31_t x, IMM uint8_t sh)                       ;
DSP_FUNC_PRFX q31_t NDS_DSP_SRA16(q31_t x, uint8_t sh)                       ;
DSP_FUNC_PRFX q31_t NDS_DSP_SLLI16(q31_t x, IMM uint8_t sh)                       ;
DSP_FUNC_PRFX q31_t NDS_DSP_SLL16(q31_t x, uint8_t sh)                       ;
// DSP_FUNC_PRFX q31_t NDS_DSP_SRLI8(q31_t x, IMM uint8_t sh)                        ;
// DSP_FUNC_PRFX q31_t NDS_DSP_SRAI8(q31_t x, IMM uint8_t sh)                        ;
// DSP_FUNC_PRFX q31_t NDS_DSP_SLLI8(q31_t x, IMM uint8_t sh)                        ;
DSP_FUNC_PRFX q31_t NDS_DSP_PKTT16(q31_t x, q31_t y)                              ;
DSP_FUNC_PRFX q31_t NDS_DSP_PKBB16(q31_t x, q31_t y)                              ;
DSP_FUNC_PRFX q31_t NDS_DSP_PKBT16(q31_t x, q31_t y)                              ;
DSP_FUNC_PRFX q31_t NDS_DSP_PKTB16(q31_t x, q31_t y)                              ;
// DSP_FUNC_PRFX q31_t NDS_DSP_SEB1(q31_t x)                                         ;
// DSP_FUNC_PRFX q31_t NDS_DSP_SEB2(q31_t x)                                         ;
// DSP_FUNC_PRFX q31_t NDS_DSP_SEB3(q31_t x)                                         ;
// DSP_FUNC_PRFX uint32_t NDS_DSP_ZEB1(uint32_t x)                                   ;
// DSP_FUNC_PRFX uint32_t NDS_DSP_ZEB2(uint32_t x)                                   ;
// DSP_FUNC_PRFX uint32_t NDS_DSP_ZEB3(uint32_t x)                                   ;
// DSP_FUNC_PRFX void NDS_DSP_SEDH(q31_t x, q31_t *v0, q31_t *v1)                    ;
// DSP_FUNC_PRFX void NDS_DSP_ZEDH(uint32_t x, uint32_t *v0, uint32_t *v1)           ;
DSP_FUNC_PRFX q31_t NDS_DSP_SUNPKD820(q31_t x)                                        ;
DSP_FUNC_PRFX q31_t NDS_DSP_SUNPKD831(q31_t x)                                        ;
DSP_FUNC_PRFX q31_t NDS_DSP_SUNPKD810(q31_t x)                                        ;
DSP_FUNC_PRFX q31_t NDS_DSP_SUNPKD830(q31_t x)                                        ;
// DSP_FUNC_PRFX q31_t NDS_DSP_SEDB2(q31_t x)                                        ;
// DSP_FUNC_PRFX q31_t NDS_DSP_SEDB3(q31_t x)                                        ;
DSP_FUNC_PRFX uint32_t NDS_DSP_ZUNPKD820(uint32_t x)                                  ;
DSP_FUNC_PRFX uint32_t NDS_DSP_ZUNPKD831(uint32_t x)                                  ;
DSP_FUNC_PRFX uint32_t NDS_DSP_ZUNPKD810(uint32_t x)                                  ;
DSP_FUNC_PRFX uint32_t NDS_DSP_ZUNPKD830(uint32_t x)                                  ;
// DSP_FUNC_PRFX uint32_t NDS_DSP_ZEDB2(uint32_t x)                                  ;
// DSP_FUNC_PRFX uint32_t NDS_DSP_ZEDB3(uint32_t x)                                  ;
DSP_FUNC_PRFX uint32_t NDS_DSP_BITREV(uint32_t x, uint8_t bit_size)               ;
DSP_FUNC_PRFX uint32_t NDS_DSP_BITREVI(uint32_t x, IMM uint8_t bit_size)          ;
// DSP_FUNC_PRFX q31_t NDS_DSP_RNDW(q31_t x, uint8_t rnd_bit, IMM roundMode_t rnd_mode)      ;
// DSP_FUNC_PRFX q31_t NDS_DSP_RNDWI(q31_t x, IMM uint8_t rnd_bit, IMM roundMode_t rnd_mode) ;
// DSP_FUNC_PRFX q63_t NDS_DSP_RNDDW(q63_t x, uint8_t rnd_bit, IMM roundMode_t rnd_mode)     ;
// DSP_FUNC_PRFX q63_t NDS_DSP_RNDDWI(q63_t x, IMM uint8_t rnd_bit, IMM roundMode_t rnd_mode);
DSP_FUNC_PRFX uint32_t NDS_DSP_UCLIP32(uint32_t x, IMM uint8_t bit_idx)              ;
DSP_FUNC_PRFX q31_t NDS_DSP_SCLIP32(q31_t x, IMM uint8_t bit_idx)                   ;
DSP_FUNC_PRFX uint32_t NDS_DSP_UCLIP16(uint32_t x, IMM uint8_t bit_idx)            ;
DSP_FUNC_PRFX q31_t NDS_DSP_SCLIP16(q31_t x, IMM uint8_t bit_idx)                 ;
DSP_FUNC_PRFX uint32_t NDS_DSP_CMPEQ8(q31_t x, q31_t y)                          ;
DSP_FUNC_PRFX uint32_t NDS_DSP_CMPEQ16(q31_t x, q31_t y)                         ;
// DSP_FUNC_PRFX uint32_t NDS_DSP_UCMPEQ8(uint32_t x, uint32_t y)                    ;
// DSP_FUNC_PRFX uint32_t NDS_DSP_UCMPEQ16(uint32_t x, uint32_t y)                   ;
DSP_FUNC_PRFX uint32_t NDS_DSP_SCMPLT8(q31_t x, q31_t y)                          ;
DSP_FUNC_PRFX uint32_t NDS_DSP_SCMPLT16(q31_t x, q31_t y)                         ;
DSP_FUNC_PRFX uint32_t NDS_DSP_UCMPLT8(uint32_t x, uint32_t y)                    ;
DSP_FUNC_PRFX uint32_t NDS_DSP_UCMPLT16(uint32_t x, uint32_t y)                   ;
DSP_FUNC_PRFX uint32_t NDS_DSP_SCMPLE8(q31_t x, q31_t y)                          ;
DSP_FUNC_PRFX uint32_t NDS_DSP_SCMPLE16(q31_t x, q31_t y)                         ;
DSP_FUNC_PRFX uint32_t NDS_DSP_UCMPLE8(uint32_t x, uint32_t y)                    ;
DSP_FUNC_PRFX uint32_t NDS_DSP_UCMPLE16(uint32_t x, uint32_t y)                   ;
// DSP_FUNC_PRFX uint32_t NDS_DSP_PICKT(q31_t x, uint32_t sel_ctl)                   ;
// DSP_FUNC_PRFX uint32_t NDS_DSP_PICKF(q31_t x, uint32_t sel_ctl)                   ;
DSP_FUNC_PRFX uint32_t NDS_DSP_BPICK(q31_t x, q31_t y, uint32_t sel_ctl)           ;
DSP_FUNC_PRFX q31_t NDS_DSP_INSB(q31_t x, q31_t y, int sel);
DSP_FUNC_PRFX q31_t NDS_DSP_SMIN8(q31_t x, q31_t y)                               ;
DSP_FUNC_PRFX uint32_t NDS_DSP_UMIN8(uint32_t x, uint32_t y)                      ;
DSP_FUNC_PRFX q31_t NDS_DSP_SMIN16(q31_t x, q31_t y)                              ;
DSP_FUNC_PRFX uint32_t NDS_DSP_UMIN16(uint32_t x, uint32_t y)                     ;
DSP_FUNC_PRFX q31_t NDS_DSP_SMAX8(q31_t x, q31_t y)                               ;
DSP_FUNC_PRFX uint32_t NDS_DSP_UMAX8(uint32_t x, uint32_t y)                      ;
DSP_FUNC_PRFX q31_t NDS_DSP_SMAX16(q31_t x, q31_t y)                              ;
DSP_FUNC_PRFX uint32_t NDS_DSP_UMAX16(uint32_t x, uint32_t y)                     ;
DSP_FUNC_PRFX q31_t NDS_DSP_KSLLI16(q31_t x, IMM uint8_t sh)                      ;
DSP_FUNC_PRFX q31_t NDS_DSP_KSLL16(q31_t x, uint8_t sh)                      ;
DSP_FUNC_PRFX q31_t NDS_DSP_KSLLI(q31_t x, IMM uint8_t sh)                        ;
DSP_FUNC_PRFX q31_t NDS_DSP_KSLL(q31_t x, uint8_t sh);
DSP_FUNC_PRFX q31_t NDS_DSP_SRAI16_U(q31_t x, IMM uint8_t sh)                      ;
DSP_FUNC_PRFX q31_t NDS_DSP_SRA16_U(q31_t x, uint8_t sh)                      ;
DSP_FUNC_PRFX q31_t NDS_DSP_SRAI_U(q31_t x, IMM uint8_t sh)                        ;
DSP_FUNC_PRFX q31_t NDS_DSP_SRA_U(q31_t x, uint8_t sh);
DSP_FUNC_PRFX q31_t NDS_DSP_KSLRA16(q31_t x, int sh)                              ;
DSP_FUNC_PRFX q31_t NDS_DSP_KSLRA16_U(q31_t x, int sh)                            ;
DSP_FUNC_PRFX q31_t NDS_DSP_KSLRAW_U(q31_t x, int sh)                             ;
// DSP_FUNC_PRFX q31_t NDS_DSP_KSLRA8(q31_t x, int sh)                               ;
// DSP_FUNC_PRFX q31_t NDS_DSP_KSLRAR8(q31_t x, int sh)                               ;
// Keep KABS for transparently migrate to BSP410 (BSP410 should generate abs instr automatically).
DSP_FUNC_PRFX q31_t NDS_DSP_KABS(q31_t x)                                         ;
DSP_FUNC_PRFX q31_t NDS_DSP_KABS16(q31_t x)                                       ;
DSP_FUNC_PRFX q31_t NDS_DSP_KABS8(q31_t x)                                        ;
DSP_FUNC_PRFX q31_t NDS_DSP_KHM16(q31_t x, q31_t y)                               ;
DSP_FUNC_PRFX q31_t NDS_DSP_KHMX16(q31_t x, q31_t y)                               ;
DSP_FUNC_PRFX q63_t NDS_DSP_SMAL(q63_t acc, q31_t x)                              ;
DSP_FUNC_PRFX q31_t NDS_DSP_WEXT(q63_t x, uint8_t lsb_idx)                        ;
DSP_FUNC_PRFX q31_t NDS_DSP_WEXTI(q63_t x, IMM uint8_t lsb_idx)                   ;

// 64-bit operation
DSP_FUNC_PRFX q63_t NDS_DSP_ADD64(q63_t x, q63_t y);
DSP_FUNC_PRFX q63_t NDS_DSP_SUB64(q63_t x, q63_t y);
DSP_FUNC_PRFX q63_t NDS_DSP_RADD64(q63_t x, q63_t y);
DSP_FUNC_PRFX q63_t NDS_DSP_RSUB64(q63_t x, q63_t y);
DSP_FUNC_PRFX uint64_t NDS_DSP_URADD64(uint64_t x, uint64_t y);
DSP_FUNC_PRFX uint64_t NDS_DSP_URSUB64(uint64_t x, uint64_t y);
DSP_FUNC_PRFX q63_t NDS_DSP_KADD64(q63_t x, q63_t y);
DSP_FUNC_PRFX q63_t NDS_DSP_KSUB64(q63_t x, q63_t y);
DSP_FUNC_PRFX uint64_t NDS_DSP_UKADD64(uint64_t x, uint64_t y);
DSP_FUNC_PRFX uint64_t NDS_DSP_UKSUB64(uint64_t x, uint64_t y);
DSP_FUNC_PRFX q63_t NDS_DSP_KMAR64(q63_t acc, q31_t x, q31_t y);
DSP_FUNC_PRFX q63_t NDS_DSP_KMSR64(q63_t acc, q31_t x, q31_t y);
DSP_FUNC_PRFX uint64_t NDS_DSP_UKMAR64(uint64_t acc, uint32_t x, uint32_t y);
DSP_FUNC_PRFX uint64_t NDS_DSP_UKMSR64(uint64_t acc, uint32_t x, uint32_t y);

#endif

#define NDS_DSP_SATS16(X, Y)        NDS_DSP_CLIPS16(X, (Y - 1))
#define NDS_DSP_SAT16(X, Y)         NDS_DSP_CLIP16(X, Y)

#ifdef  __cplusplus
}
#endif

#endif  //ENA_DSP_ISA

#endif  //__INTERNAL_DSP_ISA_H__
