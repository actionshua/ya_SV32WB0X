#ifndef __NDS32_CMSIS_TO_NDS_H__
#define __NDS32_CMSIS_TO_NDS_H__
/***************************************************************************
 * arm_math.h                                                              *
 *                                                                         *
 * Copyright (C) 2012-2019 Andes Technology Corporation                    *
 * All rights reserved.                                                    *
 ***************************************************************************/
#include "arm_to_nds_types.h"
#include "nds32_basic_math.h"
#include "nds32_complex_math.h"
#include "nds32_controller_math.h"
#include "nds32_filtering_math.h"
#include "nds32_math_types.h"
#include "nds32_matrix_math.h"
#include "nds32_statistics_math.h"
#include "nds32_transform_math.h"
#include "nds32_utils_math.h"
#include "stdio.h"

#include <string.h>
#include <math.h>
#include <float.h>
#include <limits.h>

// Note the arm_dct4 for using to inverse the buffer
// Can not map to nds_idct4 directly, please calling the nds_idct4 functions


// Rename ARM DSP functions to Andes functions.
#define arm_abs_f32 nds32_abs_f32
#define arm_negate_f32 nds32_neg_f32
#define arm_offset_f32 nds32_offset_f32
#define arm_scale_f32 nds32_scale_f32
#define arm_abs_q15 nds32_abs_q15
#define arm_negate_q15 nds32_neg_q15
#define arm_offset_q15 nds32_offset_q15
#define arm_scale_q15 nds32_scale_q15
#define arm_abs_q31 nds32_abs_q31
#define arm_negate_q31 nds32_neg_q31
#define arm_offset_q31 nds32_offset_q31
#define arm_scale_q31 nds32_scale_q31
#define arm_abs_q7 nds32_abs_q7
#define arm_negate_q7 nds32_neg_q7
#define arm_offset_q7 nds32_offset_q7
#define arm_scale_q7 nds32_scale_q7
#define arm_add_f32 nds32_add_f32
#define arm_mult_f32 nds32_mul_f32
#define arm_sub_f32 nds32_sub_f32
#define arm_add_q15 nds32_add_q15
#define arm_mult_q15 nds32_mul_q15
#define arm_sub_q15 nds32_sub_q15
#define arm_add_q31 nds32_add_q31
#define arm_mult_q31 nds32_mul_q31
#define arm_sub_q31 nds32_sub_q31
#define arm_add_q7 nds32_add_q7
#define arm_mult_q7 nds32_mul_q7
#define arm_sub_q7 nds32_sub_q7
#define arm_cmplx_conj_f32 nds32_clx_conj_f32
#define arm_cmplx_mag_f32 nds32_clx_mag_f32
#define arm_cmplx_mag_squared_f32 nds32_clx_mag_sqr_f32
#define arm_cmplx_mult_cmplx_f32 nds32_clx_mul_f32
#define arm_cmplx_mult_real_f32 nds32_clx_mul_real_f32
#define arm_cmplx_conj_q15 nds32_clx_conj_q15
#define arm_cmplx_mag_q15 nds32_clx_mag_q15
#define arm_cmplx_mag_squared_q15 nds32_clx_mag_sqr_q15
#define arm_cmplx_mult_cmplx_q15 nds32_clx_mul_q15
#define arm_cmplx_mult_real_q15 nds32_clx_mul_real_q15
#define arm_cmplx_conj_q31 nds32_clx_conj_q31
#define arm_cmplx_mag_q31 nds32_clx_mag_q31
#define arm_cmplx_mag_squared_q31 nds32_clx_mag_sqr_q31
#define arm_cmplx_mult_cmplx_q31 nds32_clx_mul_q31
#define arm_cmplx_mult_real_q31 nds32_clx_mul_real_q31
#define arm_cos_f32 nds32_cos_f32
#define arm_sin_f32 nds32_sin_f32
#define arm_conv_f32 nds32_conv_f32
#define arm_conv_q15 nds32_conv_q15
#define arm_conv_q31 nds32_conv_q31
#define arm_conv_q7 nds32_conv_q7
#define arm_correlate_f32 nds32_corr_f32
#define arm_correlate_q15 nds32_corr_q15
#define arm_correlate_q31 nds32_corr_q31
#define arm_correlate_q7 nds32_corr_q7
#define arm_fir_f32 nds32_fir_f32
//#define arm_fir_instance_f32 nds32_fir_f32_t
#define arm_fir_q15 nds32_fir_q15
//#define arm_fir_instance_q15 nds32_fir_q15_t
#define arm_fir_q31 nds32_fir_q31
//#define arm_fir_instance_q31 nds32_fir_q31_t
#undef arm_fir_q7
#define arm_fir_q7 nds32_fir_q7
#undef arm_fir_instance_q7
//#define arm_fir_instance_q7 nds32_fir_q7_t
#define arm_lms_f32 nds32_lms_f32
//#define arm_lms_instance_f32 nds32_lms_f32_t
#define arm_lms_q15 nds32_lms_q15
//#define arm_lms_instance_q15 nds32_lms_q15_t
#define arm_lms_q31 nds32_lms_q31
//#define arm_lms_instance_q31 nds32_lms_q31_t
#define arm_fir_lattice_f32 nds32_lfir_f32
//#define arm_fir_lattice_instance_f32 nds32_lfir_f32_t
#define arm_fir_lattice_q15 nds32_lfir_q15
//#define arm_fir_lattice_instance_q15 nds32_lfir_q15_t
#define arm_fir_lattice_q31 nds32_lfir_q31
//#define arm_fir_lattice_instance_q31 nds32_lfir_q31_t
#define arm_lms_norm_f32 nds32_nlms_f32
//#define arm_lms_norm_instance_f32 nds32_nlms_f32_t
#define arm_biquad_cascade_df1_f32 nds32_biquad_df1_f32
//#define arm_biquad_casd_df1_inst_f32 nds32_biquad_df1_f32_t
#define arm_biquad_cascade_df1_q15 nds32_biquad_df1_q15
//#define arm_biquad_casd_df1_inst_q15 nds32_biquad_df1_q15_t
#define arm_biquad_cascade_df1_q31 nds32_biquad_df1_q31
//#define arm_biquad_casd_df1_inst_q31 nds32_biquad_df1_q31_t
#define arm_iir_lattice_f32 nds32_liir_f32
//#define arm_iir_lattice_instance_f32 nds32_liir_f32_t
#define arm_iir_lattice_q15 nds32_liir_q15
//#define arm_iir_lattice_instance_q15 nds32_liir_q15_t
#define arm_iir_lattice_q31 nds32_liir_q31
//#define arm_iir_lattice_instance_q31 nds32_liir_q31_t
#define arm_fir_decimate_f32 nds32_dcmfir_f32
//#define arm_fir_decimate_instance_f32 nds32_dcmfir_f32_t
#define arm_fir_decimate_q15 nds32_dcmfir_q15
//#define arm_fir_decimate_instance_q15 nds32_dcmfir_q15_t
#define arm_fir_decimate_q31 nds32_dcmfir_q31
//#define arm_fir_decimate_instance_q31 nds32_dcmfir_q31_t
#define arm_fir_interpolate_f32 nds32_upsplfir_f32
//#define arm_fir_interpolate_instance_f32 nds32_upsplfir_f32_t
#define arm_fir_interpolate_q15 nds32_upsplfir_q15
//#define arm_fir_interpolate_instance_q15 nds32_upsplfir_q15_t
#define arm_fir_interpolate_q31 nds32_upsplfir_q31
//#define arm_fir_interpolate_instance_q31 nds32_upsplfir_q31_t
#define arm_fir_sparse_f32 nds32_spafir_f32
//#define arm_fir_sparse_instance_f32 nds32_spafir_f32_t
#define arm_fir_sparse_q15 nds32_spafir_q15
//#define arm_fir_sparse_instance_q15 nds32_spafir_q15_t
#define arm_fir_sparse_q31 nds32_spafir_q31
//#define arm_fir_sparse_instance_q31 nds32_spafir_q31_t
#define arm_fir_sparse_q7 nds32_spafir_q7
//#define arm_fir_sparse_instance_q7 nds32_spafir_q7_t
#define arm_copy_f32 nds32_dup_f32
//#define arm_copy_q15 nds32_dup_q15
#define arm_copy_q31 nds32_dup_q31
#define arm_copy_q7 nds32_dup_q7
#define arm_fill_f32 nds32_set_f32
#define arm_fill_q15 nds32_set_q15
#define arm_fill_q31 nds32_set_q31
#define arm_fill_q7 nds32_set_q7
#define arm_float_to_q15 nds32_convert_f32_q15
#define arm_float_to_q31 nds32_convert_f32_q31
#define arm_float_to_q7 nds32_convert_f32_q7
#define arm_q15_to_float nds32_convert_q15_f32
#define arm_q15_to_q31 nds32_convert_q15_q31
#define arm_q15_to_q7 nds32_convert_q15_q7
#define arm_q31_to_float nds32_convert_q31_f32
#define arm_q31_to_q15 nds32_convert_q31_q15
#define arm_q31_to_q7 nds32_convert_q31_q7
#define arm_q7_to_float nds32_convert_q7_f32
#define arm_q7_to_q15 nds32_convert_q7_q15
#define arm_q7_to_q31 nds32_convert_q7_q31
#define arm_shift_q31 nds32_shift_q31
#define arm_shift_q15 nds32_shift_q15
#define arm_shift_q7 nds32_shift_q7
#define arm_pid_f32 nds32_pid_f32
#define arm_pid_instance_f32 nds32_pid_f32_t
#define arm_pid_init_f32 nds32_init_pid_f32
#define arm_pid_q15 nds32_pid_q15
#define arm_pid_instance_q15 nds32_pid_q15_t
#define arm_pid_init_q15 nds32_init_pid_q15
#define arm_pid_q31 nds32_pid_q31
#define arm_pid_instance_q31 nds32_pid_q31_t
#define arm_pid_init_q31 nds32_init_pid_q31
#define arm_park_f32 nds32_park_f32
#define arm_park_q31 nds32_park_q31
#define arm_inv_park_f32 nds32_inv_park_f32
#define arm_inv_park_q31 nds32_inv_park_q31
#define arm_clarke_f32 nds32_clarke_f32
#define arm_clarke_q31 nds32_clarke_q31
#define arm_inv_clarke_f32 nds32_inv_clarke_f32
#define arm_inv_clarke_q31 nds32_inv_clarke_q31

// 2017_04_26
#define arm_cmplx_dot_prod_f32 nds32_cdprod_typ2_f32
#define arm_cmplx_dot_prod_q15 nds32_cdprod_typ2_q15
#define arm_cmplx_dot_prod_q31 nds32_cdprod_typ2_q31
#define arm_lms_norm_q15 nds32_nlms_q15
//#define arm_lms_norm_instance_q15 nds32_nlms_q15_t
#define arm_lms_norm_q31 nds32_nlms_q31
//#define arm_lms_norm_instance_q31 nds32_nlms_q31_t
#define arm_conv_partial_f32 nds32_conv_partial_f32
#define arm_conv_partial_q15 nds32_conv_partial_q15
#define arm_conv_partial_q31 nds32_conv_partial_q31
#define arm_conv_partial_q7 nds32_conv_partial_q7
#define arm_biquad_cascade_df2T_f32 nds32_bq_df2T_f32
//#define arm_biquad_cascade_df2T_instance_f32 nds32_bq_df2T_f32_t
#define arm_biquad_cascade_df2T_f64 nds32_bq_df2T_f64
//#define arm_biquad_cascade_df2T_instance_f64 nds32_bq_df2T_f64_t
#define arm_biquad_cascade_stereo_df2T_f32 nds32_bq_stereo_df2T_f32
//#define arm_biquad_cascade_stereo_df2T_instance_f32 nds32_bq_stereo_df2T_f32_t
//#define arm_biquad_cas_df1_32x64_q31 nds32_bq_df1_32x64_q31
//#define arm_biquad_cas_df1_32x64_ins_q31 nds32_bq_df1_32x64_q31_t

//2018
#define arm_fir_fast_q15 nds32_fir_fast_q15
#define arm_fir_fast_q31 nds32_fir_fast_q31

#define F64_MAX   ((float64_t)DBL_MAX)
#define F32_MAX   ((float32_t)FLT_MAX)
#define F64_MIN   (-DBL_MAX)
#define F32_MIN   (-FLT_MAX)
#define F64_ABSMAX   ((float64_t)DBL_MAX)
#define F32_ABSMAX   ((float32_t)FLT_MAX)
#define F64_ABSMIN   ((float64_t)0.0)
#define F32_ABSMIN   ((float32_t)0.0)
#define Q31_MAX   ((q31_t)(0x7FFFFFFFL))
#define Q15_MAX   ((q15_t)(0x7FFF))
#define Q7_MAX    ((q7_t)(0x7F))
#define Q31_MIN   ((q31_t)(0x80000000L))
#define Q15_MIN   ((q15_t)(0x8000))
#define Q7_MIN    ((q7_t)(0x80))
#define Q31_ABSMAX   ((q31_t)(0x7FFFFFFFL))
#define Q15_ABSMAX   ((q15_t)(0x7FFF))
#define Q7_ABSMAX    ((q7_t)(0x7F))
#define Q31_ABSMIN   ((q31_t)0)
#define Q15_ABSMIN   ((q15_t)0)
#define Q7_ABSMIN    ((q7_t)0)

/**
* @brief Macros required for reciprocal calculation in Normalized LMS
*/

#define DELTA_Q31          ((q31_t)(0x100))
#define DELTA_Q15          ((q15_t)0x5)
#define INDEX_MASK         0x0000003F
#ifndef PI
  #define PI               3.14159265358979f
#endif

/**
* @brief Macros required for SINE and COSINE Fast math approximations
*/

#define FAST_MATH_TABLE_SIZE  512
#define FAST_MATH_Q31_SHIFT   (32 - 10)
#define FAST_MATH_Q15_SHIFT   (16 - 10)
#define CONTROLLER_Q31_SHIFT  (32 - 9)
#define TABLE_SPACING_Q31     0x400000
#define TABLE_SPACING_Q15     0x80

/**
* @brief Macros required for SINE and COSINE Controller functions
*/
/* 1.31(q31) Fixed value of 2/360 */
/* -1 to +1 is divided into 360 values so total spacing is (2/360) */
#define INPUT_SPACING         0xB60B61

/**
* @brief Macros for complex numbers
*/

/* Dimension C vector space */
#define CMPLX_DIM 2

/**
* @brief Error status returned by some functions in the library.
*/
  
// Matrix instance and return status
typedef enum
{
    ARM_MATH_SUCCESS        =  0,        /**< No error */
    ARM_MATH_ARGUMENT_ERROR = -1,        /**< One or more arguments are incorrect */
    ARM_MATH_LENGTH_ERROR   = -2,        /**< Length of data buffer is incorrect */
    ARM_MATH_SIZE_MISMATCH  = -3,        /**< Size of matrices is not compatible with the operation */
    ARM_MATH_NANINF         = -4,        /**< Not-a-number (NaN) or infinity is generated */
    ARM_MATH_SINGULAR       = -5,        /**< Input matrix is singular and cannot be inverted */
    ARM_MATH_TEST_FAILURE   = -6         /**< Test Failed */
} arm_status;

/**
* @brief Struct for specifying sorting algorithm
*/
typedef enum
{
ARM_SORT_BITONIC   = 0,
         /**< Bitonic sort   */
ARM_SORT_BUBBLE    = 1,
         /**< Bubble sort    */
ARM_SORT_HEAP      = 2,
         /**< Heap sort      */
ARM_SORT_INSERTION = 3,
         /**< Insertion sort */
ARM_SORT_QUICK     = 4,
         /**< Quick sort     */
ARM_SORT_SELECTION = 5
         /**< Selection sort */
} arm_sort_alg;

/**
* @brief Struct for specifying sorting algorithm
*/
typedef enum
{
ARM_SORT_DESCENDING = 0,
         /**< Descending order (9 to 0) */
ARM_SORT_ASCENDING = 1
         /**< Ascending order (0 to 9) */
} arm_sort_dir;

/**
* @brief Struct for specifying cubic spline type
*/
typedef enum
{
ARM_SPLINE_NATURAL = 0,           /**< Natural spline */
ARM_SPLINE_PARABOLIC_RUNOUT = 1   /**< Parabolic runout spline */
} arm_spline_type;
  
#define __SIMD32_TYPE int32_t
  
#define __SIMD32(addr)        (*(__SIMD32_TYPE **) & (addr))
#define __SIMD32_CONST(addr)  ( (__SIMD32_TYPE * )   (addr))
#define _SIMD32_OFFSET(addr)  (*(__SIMD32_TYPE * )   (addr))
#define __SIMD64(addr)        (*(      int64_t **) & (addr))

#define STEP(x) (x) <= 0 ? 0 : 1
#define SQ(x) ((x) * (x))

typedef struct
{
    uint16_t numRows;    // number of rows of the matrix.
    uint16_t numCols;    // number of columns of the matrix.
    float32_t *pData;    // points to the data of the matrix.
} arm_matrix_instance_f32;

typedef struct
{
    uint16_t numRows;    // number of rows of the matrix.
    uint16_t numCols;    // number of columns of the matrix.
    q15_t *pData;        // points to the data of the matrix.
} arm_matrix_instance_q15;

typedef struct
{
    uint16_t numRows;    // number of rows of the matrix.
    uint16_t numCols;    // number of columns of the matrix.
    q31_t *pData;        // points to the data of the matrix.
} arm_matrix_instance_q31;

typedef struct
{
    uint16_t numRows;    // number of rows of the matrix.
    uint16_t numCols;    // number of columns of the matrix.
    float64_t *pData;    // points to the data of the matrix.
} arm_matrix_instance_f64;

typedef struct
{
    uint16_t fftLen;
    const float32_t *  pTwiddle;
    const uint16_t *  pBitRevTable;
    uint16_t bitRevLength;
} arm_cfft_instance_f32;
  
typedef struct
{
    uint16_t fftLen;
    const q15_t *  pTwiddle;
    const uint16_t *  pBitRevTable;
    uint16_t bitRevLength;
} arm_cfft_instance_q15;

typedef struct
{
    uint16_t fftLen;
    const q31_t *  pTwiddle;
    const uint16_t *  pBitRevTable;
    uint16_t bitRevLength;
} arm_cfft_instance_q31;

typedef struct
{
    uint16_t fftLen;
    uint8_t ifftFlag;
    uint8_t bitReverseFlag;
    const float32_t *pTwiddle;
    const uint16_t *pBitRevTable;
    uint16_t twidCoefModifier;
    uint16_t bitRevFactor;
    float32_t onebyfftLen;
} arm_cfft_radix2_instance_f32, arm_cfft_radix4_instance_f32;

typedef struct
{
    uint16_t fftLen;
    uint8_t ifftFlag;
    uint8_t bitReverseFlag;
    const q15_t *pTwiddle;
    const uint16_t *pBitRevTable;
    uint16_t twidCoefModifier;
    uint16_t bitRevFactor;
} arm_cfft_radix2_instance_q15, arm_cfft_radix4_instance_q15;

typedef struct
{
    uint16_t fftLen;
    uint8_t ifftFlag;
    uint8_t bitReverseFlag;
    const q31_t *pTwiddle;
    const uint16_t *pBitRevTable;
    uint16_t twidCoefModifier;
    uint16_t bitRevFactor;
} arm_cfft_radix2_instance_q31, arm_cfft_radix4_instance_q31;

typedef struct
{
    uint32_t fftLenReal;
    uint8_t ifftFlagR;
    uint8_t bitReverseFlagR;
    uint32_t twidCoefRModifier;
    const float32_t *pTwiddleAReal;
    const float32_t *pTwiddleBReal;
    const arm_cfft_radix4_instance_f32 *pCfft;
} arm_rfft_instance_f32;
#if 0
typedef struct
{
    uint32_t fftLenReal;
    uint8_t ifftFlagR;
    uint8_t bitReverseFlagR;
    uint32_t twidCoefRModifier;
    const q15_t *pTwiddleAReal;
    const q15_t *pTwiddleBReal;
    const arm_cfft_radix4_instance_q15 *pCfft;
} arm_rfft_instance_q15;

typedef struct
{
    uint32_t fftLenReal;
    uint8_t ifftFlagR;
    uint8_t bitReverseFlagR;
    uint32_t twidCoefRModifier;
    const q31_t *pTwiddleAReal;
    const q31_t *pTwiddleBReal;
    const arm_cfft_radix4_instance_q31 *pCfft;
} arm_rfft_instance_q31;
#else
  /**
   * @brief Instance structure for the Q15 RFFT/RIFFT function.
   */
  typedef struct
  {
          uint32_t fftLenReal;                      /**< length of the real FFT. */
          uint8_t ifftFlagR;                        /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
          uint8_t bitReverseFlagR;                  /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
          uint32_t twidCoefRModifier;               /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    const q15_t *pTwiddleAReal;                     /**< points to the real twiddle factor table. */
    const q15_t *pTwiddleBReal;                     /**< points to the imag twiddle factor table. */
    const arm_cfft_instance_q15 *pCfft;       /**< points to the complex FFT instance. */
  } arm_rfft_instance_q15;

  /**
   * @brief Instance structure for the Q31 RFFT/RIFFT function.
   */
  typedef struct
  {
          uint32_t fftLenReal;                        /**< length of the real FFT. */
          uint8_t ifftFlagR;                          /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
          uint8_t bitReverseFlagR;                    /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
          uint32_t twidCoefRModifier;                 /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    const q31_t *pTwiddleAReal;                       /**< points to the real twiddle factor table. */
    const q31_t *pTwiddleBReal;                       /**< points to the imag twiddle factor table. */
#if defined(ARM_MATH_MVEI)
    arm_cfft_instance_q31 cfftInst;
#else
    const arm_cfft_instance_q31 *pCfft;         /**< points to the complex FFT instance. */
#endif
  } arm_rfft_instance_q31;
#endif

typedef struct
{
    uint16_t N;
    uint16_t Nby2;
    float32_t normalize;
    float32_t *pTwiddle;
    float32_t *pCosFactor;
    arm_rfft_instance_f32 *pRfft;
    arm_cfft_radix4_instance_f32 *pCfft;
} arm_dct4_instance_f32;

typedef struct
{
    uint16_t N;
    uint16_t Nby2;
    q15_t normalize;
    q15_t *pTwiddle;
    q15_t *pCosFactor;
    arm_rfft_instance_q15 *pRfft;
    arm_cfft_radix4_instance_q15 *pCfft;
} arm_dct4_instance_q15;

typedef struct
{
    uint16_t N;
    uint16_t Nby2;
    q31_t normalize;
    q31_t *pTwiddle;
    q31_t *pCosFactor;
    arm_rfft_instance_q31 *pRfft;
    arm_cfft_radix4_instance_q31 *pCfft;
} arm_dct4_instance_q31;

/**
* @brief Instance structure for the Double Precision Floating-point CFFT/CIFFT function.
*/
typedef struct
{
      uint16_t fftLen;                   /**< length of the FFT. */
const float64_t *pTwiddle;         /**< points to the Twiddle factor table. */
const uint16_t *pBitRevTable;      /**< points to the bit reversal table. */
      uint16_t bitRevLength;             /**< bit reversal table length. */
} arm_cfft_instance_f64;


/**
* @brief Instance structure for the Double Precision Floating-point RFFT/RIFFT function.
*/
typedef struct
{
      arm_cfft_instance_f64 Sint;      /**< Internal CFFT structure. */
      uint16_t fftLenRFFT;             /**< length of the real sequence */
const float64_t * pTwiddleRFFT;        /**< Twiddle factors real stage  */
} arm_rfft_fast_instance_f64 ;

/**
* @brief Instance structure for the floating-point RFFT/RIFFT function.
*/
typedef struct
{
      arm_cfft_instance_f32 Sint;      /**< Internal CFFT structure. */
      uint16_t fftLenRFFT;             /**< length of the real sequence */
const float32_t * pTwiddleRFFT;        /**< Twiddle factors real stage  */
} arm_rfft_fast_instance_f32 ;

arm_status arm_rfft_fast_init_f32 (
         arm_rfft_fast_instance_f32 * S,
         uint16_t fftLen);

void arm_rfft_fast_f32(
    const arm_rfft_fast_instance_f32 * S,
    float32_t * p, float32_t * pOut,
    uint8_t ifftFlag);

/**
 * @brief Instance structure for Naive Gaussian Bayesian estimator.
 */
typedef struct
{
  uint32_t vectorDimension;  /**< Dimension of vector space */
  uint32_t numberOfClasses;  /**< Number of different classes  */
  const float32_t *theta;          /**< Mean values for the Gaussians */
  const float32_t *sigma;          /**< Variances for the Gaussians */
  const float32_t *classPriors;    /**< Class prior probabilities */
  float32_t epsilon;         /**< Additive value to variances */
} arm_gaussian_naive_bayes_instance_f32;


/**
 * @brief Instance structure for linear SVM prediction function.
 */
typedef struct
{
  uint32_t        nbOfSupportVectors;     /**< Number of support vectors */
  uint32_t        vectorDimension;        /**< Dimension of vector space */
  float32_t       intercept;              /**< Intercept */
  const float32_t *dualCoefficients;      /**< Dual coefficients */
  const float32_t *supportVectors;        /**< Support vectors */
  const int32_t   *classes;               /**< The two SVM classes */
} arm_svm_linear_instance_f32;

/**
 * @brief Instance structure for polynomial SVM prediction function.
 */
typedef struct
{
  uint32_t        nbOfSupportVectors;     /**< Number of support vectors */
  uint32_t        vectorDimension;        /**< Dimension of vector space */
  float32_t       intercept;              /**< Intercept */
  const float32_t *dualCoefficients;      /**< Dual coefficients */
  const float32_t *supportVectors;        /**< Support vectors */
  const int32_t   *classes;               /**< The two SVM classes */
  int32_t         degree;                 /**< Polynomial degree */
  float32_t       coef0;                  /**< Polynomial constant */
  float32_t       gamma;                  /**< Gamma factor */
} arm_svm_polynomial_instance_f32;

/**
 * @brief Instance structure for rbf SVM prediction function.
 */
typedef struct
{
  uint32_t        nbOfSupportVectors;     /**< Number of support vectors */
  uint32_t        vectorDimension;        /**< Dimension of vector space */
  float32_t       intercept;              /**< Intercept */
  const float32_t *dualCoefficients;      /**< Dual coefficients */
  const float32_t *supportVectors;        /**< Support vectors */
  const int32_t   *classes;               /**< The two SVM classes */
  float32_t       gamma;                  /**< Gamma factor */
} arm_svm_rbf_instance_f32;

/**
 * @brief Instance structure for sigmoid SVM prediction function.
 */
typedef struct
{
  uint32_t        nbOfSupportVectors;     /**< Number of support vectors */
  uint32_t        vectorDimension;        /**< Dimension of vector space */
  float32_t       intercept;              /**< Intercept */
  const float32_t *dualCoefficients;      /**< Dual coefficients */
  const float32_t *supportVectors;        /**< Support vectors */
  const int32_t   *classes;               /**< The two SVM classes */
  float32_t       coef0;                  /**< Independant constant */
  float32_t       gamma;                  /**< Gamma factor */
} arm_svm_sigmoid_instance_f32;

/**
* @brief Instance structure for the sorting algorithms.
*/
typedef struct            
{
arm_sort_alg alg;        /**< Sorting algorithm selected */
arm_sort_dir dir;        /**< Sorting order (direction)  */
} arm_sort_instance_f32;  

/**
* @brief Instance structure for the sorting algorithms.
*/
typedef struct            
{
arm_sort_dir dir;        /**< Sorting order (direction)  */
float32_t * buffer;      /**< Working buffer */
} arm_merge_sort_instance_f32;  


/**
* @brief Instance structure for the floating-point cubic spline interpolation.
*/
typedef struct
{
arm_spline_type type;      /**< Type (boundary conditions) */
const float32_t * x;       /**< x values */
const float32_t * y;       /**< y values */
uint32_t n_x;              /**< Number of known data points */
float32_t * coeffs;        /**< Coefficients buffer (b,c, and d) */
} arm_spline_instance_f32;

/**
* @brief Instance structure for the high precision Q31 Biquad cascade filter.
*/
typedef struct
{
      uint8_t numStages;       /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
      q63_t *pState;           /**< points to the array of state coefficients.  The array is of length 4*numStages. */
const q31_t *pCoeffs;          /**< points to the array of coefficients.  The array is of length 5*numStages. */
      uint8_t postShift;       /**< additional shift, in bits, applied to each output sample. */
} arm_biquad_cas_df1_32x64_ins_q31;

/**
* @brief Instance structure for the Q15 Biquad cascade filter.
*/
typedef struct
{
      int8_t numStages;        /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
      q15_t *pState;           /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
const q15_t *pCoeffs;          /**< Points to the array of coefficients.  The array is of length 5*numStages. */
      int8_t postShift;        /**< Additional shift, in bits, applied to each output sample. */
} arm_biquad_casd_df1_inst_q15;

/**
* @brief Instance structure for the Q31 Biquad cascade filter.
*/
typedef struct
{
      uint32_t numStages;      /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
      q31_t *pState;           /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
const q31_t *pCoeffs;          /**< Points to the array of coefficients.  The array is of length 5*numStages. */
      uint8_t postShift;       /**< Additional shift, in bits, applied to each output sample. */
} arm_biquad_casd_df1_inst_q31;

/**
* @brief Instance structure for the floating-point Biquad cascade filter.
*/
typedef struct
{
      uint32_t numStages;      /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
      float32_t *pState;       /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
const float32_t *pCoeffs;      /**< Points to the array of coefficients.  The array is of length 5*numStages. */
} arm_biquad_casd_df1_inst_f32;

/**
* @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
*/
typedef struct
{
      uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
      float32_t *pState;         /**< points to the array of state coefficients.  The array is of length 2*numStages. */
const float32_t *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
} arm_biquad_cascade_df2T_instance_f32;

/**
* @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
*/
typedef struct
{
      uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
      float64_t *pState;         /**< points to the array of state coefficients.  The array is of length 2*numStages. */
const float64_t *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
} arm_biquad_cascade_df2T_instance_f64;

/**
* @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
*/
typedef struct
{
      uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
      float32_t *pState;         /**< points to the array of state coefficients.  The array is of length 4*numStages. */
const float32_t *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
} arm_biquad_cascade_stereo_df2T_instance_f32;

/**
* @brief Instance structure for the Q15 FIR decimator.
*/
typedef struct
{
      uint8_t M;                  /**< decimation factor. */
      uint16_t numTaps;           /**< number of coefficients in the filter. */
const q15_t *pCoeffs;             /**< points to the coefficient array. The array is of length numTaps.*/
      q15_t *pState;              /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
} arm_fir_decimate_instance_q15;

/**
* @brief Instance structure for the Q31 FIR decimator.
*/
typedef struct
{
      uint8_t M;                  /**< decimation factor. */
      uint16_t numTaps;           /**< number of coefficients in the filter. */
const q31_t *pCoeffs;             /**< points to the coefficient array. The array is of length numTaps.*/
      q31_t *pState;              /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
} arm_fir_decimate_instance_q31;

/**
  @brief Instance structure for floating-point FIR decimator.
 */
typedef struct
  {
          uint8_t M;                  /**< decimation factor. */
          uint16_t numTaps;           /**< number of coefficients in the filter. */
    const float32_t *pCoeffs;         /**< points to the coefficient array. The array is of length numTaps.*/
          float32_t *pState;          /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
  } arm_fir_decimate_instance_f32;

  /**
   * @brief Instance structure for the floating-point FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;     /**< number of filter coefficients in the filter. */
          float32_t *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const float32_t *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
  } arm_fir_instance_f32;


/**
* @brief Instance structure for the Q15 FIR filter.
*/
typedef struct
{
      uint16_t numTaps;         /**< number of filter coefficients in the filter. */
      q15_t *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
const q15_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
} arm_fir_instance_q15;

/**
* @brief Instance structure for the Q31 FIR filter.
*/
typedef struct
{
      uint16_t numTaps;         /**< number of filter coefficients in the filter. */
      q31_t *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
const q31_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps. */
} arm_fir_instance_q31;


/**
* @brief Instance structure for the Q7 FIR filter.
*/
typedef struct
{
      uint16_t numTaps;        /**< number of filter coefficients in the filter. */
      q7_t *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
const q7_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
} arm_fir_instance_q7;

/**
* @brief Instance structure for the Q15 FIR interpolator.
*/
typedef struct
{
    uint8_t L;                      /**< upsample factor. */
    uint16_t phaseLength;           /**< length of each polyphase filter component. */
const q15_t *pCoeffs;                 /**< points to the coefficient array. The array is of length L*phaseLength. */
    q15_t *pState;                  /**< points to the state variable array. The array is of length blockSize+phaseLength-1. */
} arm_fir_interpolate_instance_q15;

/**
* @brief Instance structure for the Q31 FIR interpolator.
*/
typedef struct
{
    uint8_t L;                      /**< upsample factor. */
    uint16_t phaseLength;           /**< length of each polyphase filter component. */
const q31_t *pCoeffs;                 /**< points to the coefficient array. The array is of length L*phaseLength. */
    q31_t *pState;                  /**< points to the state variable array. The array is of length blockSize+phaseLength-1. */
} arm_fir_interpolate_instance_q31;

/**
* @brief Instance structure for the floating-point FIR interpolator.
*/
typedef struct
{
    uint8_t L;                     /**< upsample factor. */
    uint16_t phaseLength;          /**< length of each polyphase filter component. */
const float32_t *pCoeffs;            /**< points to the coefficient array. The array is of length L*phaseLength. */
    float32_t *pState;             /**< points to the state variable array. The array is of length phaseLength+numTaps-1. */
} arm_fir_interpolate_instance_f32;

/**
* @brief Instance structure for the Q15 FIR lattice filter.
*/
typedef struct
{
      uint16_t numStages;                  /**< number of filter stages. */
      q15_t *pState;                       /**< points to the state variable array. The array is of length numStages. */
const q15_t *pCoeffs;                      /**< points to the coefficient array. The array is of length numStages. */
} arm_fir_lattice_instance_q15;

/**
* @brief Instance structure for the Q31 FIR lattice filter.
*/
typedef struct
{
      uint16_t numStages;                  /**< number of filter stages. */
      q31_t *pState;                       /**< points to the state variable array. The array is of length numStages. */
const q31_t *pCoeffs;                      /**< points to the coefficient array. The array is of length numStages. */
} arm_fir_lattice_instance_q31;

/**
* @brief Instance structure for the floating-point FIR lattice filter.
*/
typedef struct
{
      uint16_t numStages;                  /**< number of filter stages. */
      float32_t *pState;                   /**< points to the state variable array. The array is of length numStages. */
const float32_t *pCoeffs;                  /**< points to the coefficient array. The array is of length numStages. */
} arm_fir_lattice_instance_f32;

  /**
   * @brief Instance structure for the floating-point sparse FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;             /**< number of coefficients in the filter. */
          uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
          float32_t *pState;            /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const float32_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
          uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
          int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } arm_fir_sparse_instance_f32;

  /**
   * @brief Instance structure for the Q31 sparse FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;             /**< number of coefficients in the filter. */
          uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
          q31_t *pState;                /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const q31_t *pCoeffs;               /**< points to the coefficient array. The array is of length numTaps.*/
          uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
          int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } arm_fir_sparse_instance_q31;

  /**
   * @brief Instance structure for the Q15 sparse FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;             /**< number of coefficients in the filter. */
          uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
          q15_t *pState;                /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const q15_t *pCoeffs;               /**< points to the coefficient array. The array is of length numTaps.*/
          uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
          int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } arm_fir_sparse_instance_q15;

  /**
   * @brief Instance structure for the Q7 sparse FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;             /**< number of coefficients in the filter. */
          uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
          q7_t *pState;                 /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const q7_t *pCoeffs;                /**< points to the coefficient array. The array is of length numTaps.*/
          uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
          int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } arm_fir_sparse_instance_q7;

  /**
   * @brief Instance structure for the Q15 IIR lattice filter.
   */
  typedef struct
  {
          uint16_t numStages;                  /**< number of stages in the filter. */
          q15_t *pState;                       /**< points to the state variable array. The array is of length numStages+blockSize. */
          q15_t *pkCoeffs;                     /**< points to the reflection coefficient array. The array is of length numStages. */
          q15_t *pvCoeffs;                     /**< points to the ladder coefficient array. The array is of length numStages+1. */
  } arm_iir_lattice_instance_q15;

  /**
   * @brief Instance structure for the Q31 IIR lattice filter.
   */
  typedef struct
  {
          uint16_t numStages;                  /**< number of stages in the filter. */
          q31_t *pState;                       /**< points to the state variable array. The array is of length numStages+blockSize. */
          q31_t *pkCoeffs;                     /**< points to the reflection coefficient array. The array is of length numStages. */
          q31_t *pvCoeffs;                     /**< points to the ladder coefficient array. The array is of length numStages+1. */
  } arm_iir_lattice_instance_q31;

  /**
   * @brief Instance structure for the floating-point IIR lattice filter.
   */
  typedef struct
  {
          uint16_t numStages;                  /**< number of stages in the filter. */
          float32_t *pState;                   /**< points to the state variable array. The array is of length numStages+blockSize. */
          float32_t *pkCoeffs;                 /**< points to the reflection coefficient array. The array is of length numStages. */
          float32_t *pvCoeffs;                 /**< points to the ladder coefficient array. The array is of length numStages+1. */
  } arm_iir_lattice_instance_f32;


  /**
   * @brief Instance structure for the floating-point LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;    /**< number of coefficients in the filter. */
          float32_t *pState;   /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          float32_t *pCoeffs;  /**< points to the coefficient array. The array is of length numTaps. */
          float32_t mu;        /**< step size that controls filter coefficient updates. */
  } arm_lms_instance_f32;

  /**
   * @brief Instance structure for the Q15 LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;    /**< number of coefficients in the filter. */
          q15_t *pState;       /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          q15_t *pCoeffs;      /**< points to the coefficient array. The array is of length numTaps. */
          q15_t mu;            /**< step size that controls filter coefficient updates. */
          uint32_t postShift;  /**< bit shift applied to coefficients. */
  } arm_lms_instance_q15;

  /**
   * @brief Instance structure for the Q31 LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;    /**< number of coefficients in the filter. */
          q31_t *pState;       /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          q31_t *pCoeffs;      /**< points to the coefficient array. The array is of length numTaps. */
          q31_t mu;            /**< step size that controls filter coefficient updates. */
          uint32_t postShift;  /**< bit shift applied to coefficients. */
  } arm_lms_instance_q31;

  /**
   * @brief Instance structure for the floating-point normalized LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;     /**< number of coefficients in the filter. */
          float32_t *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          float32_t *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
          float32_t mu;         /**< step size that control filter coefficient updates. */
          float32_t energy;     /**< saves previous frame energy. */
          float32_t x0;         /**< saves previous input sample. */
  } arm_lms_norm_instance_f32;

  /**
   * @brief Instance structure for the Q15 normalized LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;     /**< Number of coefficients in the filter. */
          q15_t *pState;        /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          q15_t *pCoeffs;       /**< points to the coefficient array. The array is of length numTaps. */
          q15_t mu;             /**< step size that controls filter coefficient updates. */
          uint8_t postShift;    /**< bit shift applied to coefficients. */
    const q15_t *recipTable;    /**< Points to the reciprocal initial value table. */
          q15_t energy;         /**< saves previous frame energy. */
          q15_t x0;             /**< saves previous input sample. */
  } arm_lms_norm_instance_q15;

 /**
   * @brief Instance structure for the Q31 normalized LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;     /**< number of coefficients in the filter. */
          q31_t *pState;        /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          q31_t *pCoeffs;       /**< points to the coefficient array. The array is of length numTaps. */
          q31_t mu;             /**< step size that controls filter coefficient updates. */
          uint8_t postShift;    /**< bit shift applied to coefficients. */
    const q31_t *recipTable;    /**< points to the reciprocal initial value table. */
          q31_t energy;         /**< saves previous frame energy. */
          q31_t x0;             /**< saves previous input sample. */
  } arm_lms_norm_instance_q31;
 
/* Change the different finction types for ARM DSP functions
 * to Andes functions.
 */

#define FUNC_PREFIX static inline

// Math Operations
FUNC_PREFIX void arm_copy_q15(const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize)
{
    nds32_dup_q15((q15_t *)pSrc, pDst, blockSize);
    return;
}

// Math Operations
FUNC_PREFIX void arm_dot_prod_f32(const float32_t *pSrcA,
        const float32_t *pSrcB,
        uint32_t    blockSize,
        float32_t *result)
{
    *result = nds32_dot_prod_f32((float32_t *)pSrcA, (float32_t *)pSrcB, blockSize);

    return;
}

FUNC_PREFIX void arm_dot_prod_q15(q15_t *pSrcA,
        q15_t *pSrcB,
        uint32_t    blockSize,
        q63_t *result)
{
    *result = nds32_dot_prod_q15(pSrcA, pSrcB, blockSize);

    return;
}

FUNC_PREFIX void arm_dot_prod_q31(q31_t *pSrcA,
        q31_t *pSrcB,
        uint32_t    blockSize,
        q63_t *result)
{
    *result = nds32_dot_prod_q31(pSrcA, pSrcB, blockSize);

    return;
}

FUNC_PREFIX void arm_dot_prod_q7(q7_t *pSrcA,
        q7_t *pSrcB,
        uint32_t     blockSize,
        q31_t *result)
{
    *result = nds32_dot_prod_q7(pSrcA, pSrcB, blockSize);

    return;
}

// Matrix Operations
// Mareix Addition/
FUNC_PREFIX void arm_mat_init_f32(arm_matrix_instance_f32 * S,
                                  uint16_t nRows,
                                  uint16_t nColumns,
                                  float32_t * pData)
{
    S->numRows = nRows;
    S->numCols = nColumns;
    S->pData = pData;
}

FUNC_PREFIX void arm_mat_init_f64(arm_matrix_instance_f64 * S,
                                  uint16_t nRows,
                                  uint16_t nColumns,
                                  float64_t * pData)
{
    S->numRows = nRows;
    S->numCols = nColumns;
    S->pData = pData;
}

FUNC_PREFIX void arm_mat_init_q15(arm_matrix_instance_q15 * S,
                                  uint16_t nRows,
                                  uint16_t nColumns,
                                  q15_t * pData)
{
    S->numRows = nRows;
    S->numCols = nColumns;
    S->pData = pData;
}

FUNC_PREFIX void arm_mat_init_q31(arm_matrix_instance_q31 * S,
                                  uint16_t nRows,
                                  uint16_t nColumns,
                                  q31_t * pData)
{
    S->numRows = nRows;
    S->numCols = nColumns;
    S->pData = pData;
}

FUNC_PREFIX arm_status arm_mat_add_f32(const arm_matrix_instance_f32    *pSrcA,
        const arm_matrix_instance_f32    *pSrcB,
        arm_matrix_instance_f32      *pDst)
{
    float32_t *src1 = pSrcA->pData;
    float32_t *src2 = pSrcB->pData;
    float32_t *dst = pDst->pData;
    uint32_t row = pSrcA->numRows;
    uint32_t col = pSrcA->numCols;

    nds32_mat_add_f32(src1, src2, dst, row, col);
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX arm_status arm_mat_add_q15(const arm_matrix_instance_q15    *pSrcA,
        const arm_matrix_instance_q15    *pSrcB,
        arm_matrix_instance_q15      *pDst)
{
    q15_t *src1 = pSrcA->pData;
    q15_t *src2 = pSrcB->pData;
    q15_t *dst = pDst->pData;
    uint32_t row = pSrcA->numRows;
    uint32_t col = pSrcA->numCols;

    nds32_mat_add_q15(src1, src2, dst, row, col);
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX arm_status arm_mat_add_q31(const arm_matrix_instance_q31    *pSrcA,
        const arm_matrix_instance_q31    *pSrcB,
        arm_matrix_instance_q31      *pDst)
{
    q31_t *src1 = pSrcA->pData;
    q31_t *src2 = pSrcB->pData;
    q31_t *dst = pDst->pData;
    uint32_t row = pSrcA->numRows;
    uint32_t col = pSrcA->numCols;

    nds32_mat_add_q31(src1, src2, dst, row, col);
    return ARM_MATH_SUCCESS;
}

/* Matrix Substraction */
FUNC_PREFIX arm_status arm_mat_sub_f32(const arm_matrix_instance_f32    *pSrcA,
        const arm_matrix_instance_f32    *pSrcB,
        arm_matrix_instance_f32      *pDst)
{
    float32_t *src1 = pSrcA->pData;
    float32_t *src2 = pSrcB->pData;
    float32_t *dst = pDst->pData;
    uint32_t row = pSrcA->numRows;
    uint32_t col = pSrcA->numCols;

    nds32_mat_sub_f32(src1, src2, dst, row, col);
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX arm_status arm_mat_sub_q15(const arm_matrix_instance_q15    *pSrcA,
        const arm_matrix_instance_q15    *pSrcB,
        arm_matrix_instance_q15      *pDst)
{
    q15_t *src1 = pSrcA->pData;
    q15_t *src2 = pSrcB->pData;
    q15_t *dst = pDst->pData;
    uint32_t row = pSrcA->numRows;
    uint32_t col = pSrcA->numCols;

    nds32_mat_sub_q15(src1, src2, dst, row, col);
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX arm_status arm_mat_sub_q31(const arm_matrix_instance_q31    *pSrcA,
        const arm_matrix_instance_q31    *pSrcB,
        arm_matrix_instance_q31      *pDst)
{
    q31_t *src1 = pSrcA->pData;
    q31_t *src2 = pSrcB->pData;
    q31_t *dst = pDst->pData;
    uint32_t row = pSrcA->numRows;
    uint32_t col = pSrcA->numCols;

    nds32_mat_sub_q31(src1, src2, dst, row, col);
    return ARM_MATH_SUCCESS;
}

/* Matrix Multiplication */
FUNC_PREFIX arm_status arm_mat_mult_f32(const arm_matrix_instance_f32   *pSrcA,
        const arm_matrix_instance_f32   *pSrcB,
        arm_matrix_instance_f32         *pDst)
{
    float32_t *src1 = pSrcA->pData;
    float32_t *src2 = pSrcB->pData;
    float32_t *dst = pDst->pData;
    uint32_t row = pSrcA->numRows;
    uint32_t col = pSrcA->numCols;
    uint32_t col2 = pSrcB->numCols;

    nds32_mat_mul_f32(src1, src2, dst, row, col, col2);
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX arm_status arm_mat_mult_q15(const arm_matrix_instance_q15   *pSrcA,
        const arm_matrix_instance_q15    *pSrcB,
        arm_matrix_instance_q15      *pDst,
        __attribute__((__unused__)) q15_t *pState)
{
    q15_t *src1 = pSrcA->pData;
    q15_t *src2 = pSrcB->pData;
    q15_t *dst = pDst->pData;
    uint32_t row = pSrcA->numRows;
    uint32_t col = pSrcA->numCols;
    uint32_t col2 = pSrcB->numCols;

    nds32_mat_mul_q15(src1, src2, dst, row, col, col2);
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX arm_status arm_mat_mult_q31(const arm_matrix_instance_q31   *pSrcA,
        const arm_matrix_instance_q31   *pSrcB,
        arm_matrix_instance_q31         *pDst)
{
    q31_t *src1 = pSrcA->pData;
    q31_t *src2 = pSrcB->pData;
    q31_t *dst = pDst->pData;
    uint32_t row = pSrcA->numRows;
    uint32_t col = pSrcA->numCols;
    uint32_t col2 = pSrcB->numCols;

    nds32_mat_mul_q31(src1, src2, dst, row, col, col2);
    return ARM_MATH_SUCCESS;
}

/* Matrix Scale */
FUNC_PREFIX arm_status arm_mat_scale_f32(const arm_matrix_instance_f32  *pSrc,
        float32_t scale,
        arm_matrix_instance_f32        *pDst)
{
    float32_t *src = pSrc->pData;
    float32_t *dst = pDst->pData;
    uint32_t row = pSrc->numRows;
    uint32_t col = pSrc->numCols;

    nds32_mat_scale_f32(src, scale, dst, row, col);
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX arm_status arm_mat_scale_q15(const arm_matrix_instance_q15  *pSrc,
        q15_t scaleFract,
        int32_t shift,
        arm_matrix_instance_q15        *pDst)
{
    q15_t *src = pSrc->pData;
    q15_t *dst = pDst->pData;
    uint32_t row = pSrc->numRows;
    uint32_t col = pSrc->numCols;

    nds32_mat_scale_q15(src, scaleFract, shift, dst, row, col);
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX arm_status arm_mat_scale_q31(const arm_matrix_instance_q31  *pSrc,
        q31_t scaleFract,
        int32_t shift,
        arm_matrix_instance_q31        *pDst)
{
    q31_t *src = pSrc->pData;
    q31_t *dst = pDst->pData;
    uint32_t row = pSrc->numRows;
    uint32_t col = pSrc->numCols;

    nds32_mat_scale_q31(src, scaleFract, shift, dst, row, col);
    return ARM_MATH_SUCCESS;
}

// Matrix Transform
FUNC_PREFIX arm_status arm_mat_trans_f32(const arm_matrix_instance_f32  *pSrc,
        arm_matrix_instance_f32        *pDst)
{
    float32_t *src = pSrc->pData;
    float32_t *dst = pDst->pData;
    uint32_t row = pSrc->numRows;
    uint32_t col = pSrc->numCols;

    nds32_mat_trans_f32(src, dst, row, col);
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX arm_status arm_mat_trans_q15(const arm_matrix_instance_q15  *pSrc,
        arm_matrix_instance_q15        *pDst)
{
    q15_t *src = pSrc->pData;
    q15_t *dst = pDst->pData;
    uint32_t row = pSrc->numRows;
    uint32_t col = pSrc->numCols;

    nds32_mat_trans_q15(src, dst, row, col);
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX arm_status arm_mat_trans_q31(const arm_matrix_instance_q31  *pSrc,
        arm_matrix_instance_q31        *pDst)
{
    q31_t *src = pSrc->pData;
    q31_t *dst = pDst->pData;
    uint32_t row = pSrc->numRows;
    uint32_t col = pSrc->numCols;

    nds32_mat_trans_q31(src, dst, row, col);
    return ARM_MATH_SUCCESS;
}

// Matrix Inverse
FUNC_PREFIX arm_status arm_mat_inverse_f32(const arm_matrix_instance_f32 *pSrc,
        arm_matrix_instance_f32        *pDst)
{
    float32_t *src = pSrc->pData;
    float32_t *dst = pDst->pData;
    uint32_t size = pSrc->numRows;
    int32_t st;

    st = nds32_mat_inv_f32(src, dst, size);

    return (arm_status)st;
}

FUNC_PREFIX arm_status arm_mat_inverse_f64(const arm_matrix_instance_f64 *pSrc,
        arm_matrix_instance_f64        *pDst)
{
    float64_t *src = pSrc->pData;
    float64_t *dst = pDst->pData;
    uint32_t size = pSrc->numRows;
    int32_t st;

    st = nds32_mat_inv_f64(src, dst, size);

    return (arm_status)st;
}

// Maximum
FUNC_PREFIX void arm_max_f32(float32_t *pSrcA,
        uint32_t    blockSize,
        float32_t *result,
        uint32_t   *pIndex)
{
    *result = nds32_max_f32(pSrcA, blockSize, pIndex);

    return;
}

FUNC_PREFIX void arm_max_q15(q15_t *pSrcA,
        uint32_t    blockSize,
        q15_t *result,
        uint32_t   *pIndex)
{
    *result = nds32_max_q15(pSrcA, blockSize, pIndex);

    return;
}

FUNC_PREFIX void arm_max_q31(q31_t *pSrcA,
        uint32_t    blockSize,
        q31_t *result,
        uint32_t   *pIndex)
{
    *result = nds32_max_q31(pSrcA, blockSize, pIndex);

    return;
}

FUNC_PREFIX void arm_max_q7(q7_t *pSrcA,
        uint32_t blockSize,
        q7_t *result,
        uint32_t    *pIndex)
{
    *result = nds32_max_q7(pSrcA, blockSize, pIndex);

    return;
}

// Minimum
FUNC_PREFIX void arm_min_f32(float32_t *pSrcA,
        uint32_t    blockSize,
        float32_t *result,
        uint32_t   *pIndex)
{
    *result = nds32_min_f32(pSrcA, blockSize, pIndex);

    return;
}

FUNC_PREFIX void arm_min_q15(q15_t *pSrcA,
        uint32_t    blockSize,
        q15_t *result,
        uint32_t   *pIndex)
{
    *result = nds32_min_q15(pSrcA, blockSize, pIndex);

    return;
}

FUNC_PREFIX void arm_min_q31(q31_t *pSrcA,
        uint32_t    blockSize,
        q31_t *result,
        uint32_t   *pIndex)
{
    *result = nds32_min_q31(pSrcA, blockSize, pIndex);

    return;
}

FUNC_PREFIX void arm_min_q7(q7_t *pSrcA,
        uint32_t blockSize,
        q7_t *result,
        uint32_t    *pIndex)
{
    *result = nds32_min_q7(pSrcA, blockSize, pIndex);

    return;
}

// Mean
FUNC_PREFIX void arm_mean_f32(float32_t *pSrc,
        uint32_t   blockSize,
        float32_t *result)
{
    *result = nds32_mean_f32(pSrc, blockSize);

    return;
}

FUNC_PREFIX void arm_mean_q15(q15_t *pSrc,
        uint32_t   blockSize,
        q15_t *result)
{
    *result = nds32_mean_q15(pSrc, blockSize);

    return;
}

FUNC_PREFIX void arm_mean_q31(q31_t *pSrc,
        uint32_t   blockSize,
        q31_t *result)
{
    *result = nds32_mean_q31(pSrc, blockSize);

    return;
}

FUNC_PREFIX void arm_mean_q7(q7_t *pSrc,
        uint32_t    blockSize,
        q7_t *result)
{
    *result = nds32_mean_q7(pSrc, blockSize);

    return;
}

// Sum of the Square (Power)
FUNC_PREFIX void arm_power_f32(const float32_t *pSrc,
        uint32_t  blockSize,
        float32_t *result)
{
    *result = nds32_sos_f32((float32_t *)pSrc, blockSize);

    return;
}

FUNC_PREFIX void arm_power_q15(q15_t *pSrc,
        uint32_t  blockSize,
        q63_t *result)
{
    *result = nds32_sos_q15(pSrc, blockSize);

    return;
}

FUNC_PREFIX void arm_power_q31(q31_t *pSrc,
        uint32_t  blockSize,
        q63_t *result)
{
    *result = nds32_sos_q31(pSrc, blockSize);

    return;
}

FUNC_PREFIX void arm_power_q7(q7_t *pSrc,
        uint32_t   blockSize,
        q31_t *result)
{
    *result = nds32_sos_q7(pSrc, blockSize);

    return;
}

// Variance
FUNC_PREFIX void arm_var_f32(float32_t *pSrc,
        uint32_t    blockSize,
        float32_t *result)
{
    *result = nds32_var_f32(pSrc, blockSize);

    return;
}

#ifdef CMSIS144
FUNC_PREFIX void arm_var_q15(q15_t *pSrc,
        uint32_t    blockSize,
        q15_t *result)
{
    *result = (q15_t) nds32_var_q15(pSrc, blockSize);

    return;
}

FUNC_PREFIX void arm_var_q31(q31_t *pSrc,
        uint32_t    blockSize,
        q31_t *result)
{
    *result = (q31_t) nds32_var_q31(pSrc, blockSize);

    return;
}
#else
FUNC_PREFIX void arm_var_q15(q15_t *pSrc,
        uint32_t    blockSize,
        q31_t *result)
{
    *result = nds32_var_q15(pSrc, blockSize);

    return;
}

FUNC_PREFIX void arm_var_q31(q31_t *pSrc,
        uint32_t    blockSize,
        q63_t *result)
{
    *result = nds32_var_q31(pSrc, blockSize);

    return;
}
#endif

// Root Mean square
FUNC_PREFIX void arm_rms_f32(float32_t *pSrc,
        uint32_t    blockSize,
        float32_t *result)
{
    *result = nds32_rms_f32(pSrc, blockSize);

    return;
}

FUNC_PREFIX void arm_rms_q15(q15_t *pSrc,
        uint32_t    blockSize,
        q15_t *result)
{
    *result = nds32_rms_q15(pSrc, blockSize);

    return;
}

FUNC_PREFIX void arm_rms_q31(q31_t *pSrc,
        uint32_t    blockSize,
        q31_t *result)
{
    *result = nds32_rms_q31(pSrc, blockSize);

    return;
}

// Standard Derivation
FUNC_PREFIX void arm_std_f32(float32_t *pSrc,
        uint32_t    blockSize,
        float32_t *result)
{
    *result = nds32_std_f32(pSrc, blockSize);

    return;
}

FUNC_PREFIX void arm_std_q15(q15_t *pSrc,
        uint32_t    blockSize,
        q15_t *result)
{
    *result = nds32_std_q15(pSrc, blockSize);

    return;
}

FUNC_PREFIX void arm_std_q31(q31_t *pSrc,
        uint32_t    blockSize,
        q31_t *result)
{
    *result = nds32_std_q31(pSrc, blockSize);

    return;
}

// Square Root
FUNC_PREFIX arm_status arm_sqrt_f32(float32_t in,
        float32_t *pOut)
{
    *pOut = nds32_sqrt_f32(in);
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX arm_status arm_sqrt_q15(q15_t in,
        q15_t *pOut)
{
    *pOut = nds32_sqrt_q15(in);
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX arm_status arm_sqrt_q31(q31_t in,
        q31_t *pOut)
{
    *pOut = nds32_sqrt_q31(in);
    return ARM_MATH_SUCCESS;
}

// transform
// CFFT_RADIX2
#include "math.h"
FUNC_PREFIX void arm_cfft_f32(const arm_cfft_instance_f32 *S, float32_t *p1, uint8_t ifftFlag, uint8_t bitReverseFlag)
{
    uint32_t m = S->fftLen;
    m = log(m);
    int inv = ifftFlag;
    if (inv == 0)
    {
        nds32_cfft_f32(p1, m);
    }
    else
    {
        nds32_cifft_f32(p1, m);
    }
}

FUNC_PREFIX void arm_cfft_q15(const arm_cfft_instance_q15 *S, q15_t *p1, uint8_t ifftFlag, uint8_t bitReverseFlag)
{
    uint32_t m = S->fftLen;
    m = log(m);
    int inv = ifftFlag;
    if (inv == 0)
    {
        nds32_cfft_q15(p1, m);
    }
    else
    {
        nds32_cifft_q15(p1, m);
    }
}

FUNC_PREFIX void arm_cfft_q31(const arm_cfft_instance_q31 *S, q31_t *p1, uint8_t ifftFlag, uint8_t bitReverseFlag)
{
    uint32_t m = S->fftLen;
    m = log(m);
    int inv = ifftFlag;
    if (inv == 0)
    {
        nds32_cfft_q31(p1, m);
    }
    else
    {
        nds32_cifft_q31(p1, m);
    }
}

FUNC_PREFIX arm_status arm_cfft_radix2_init_f32(arm_cfft_radix2_instance_f32 *S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag)
{
    S->fftLen = fftLen;
    S->ifftFlag = ifftFlag;
    S->bitReverseFlag = bitReverseFlag;
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX void arm_cfft_radix2_f32(const arm_cfft_radix2_instance_f32 *S,
        float32_t *pSrc)
{
    uint32_t m = S->fftLen;
    int32_t inv = S->ifftFlag;
    switch (m)
    {
        case 4096u:
            m = 12;
            break;
        case 2048u:
            m = 11;
            break;
        case 1024u:
            m = 10;
            break;
        case 512u:
            m = 9;
            break;
        case 256u:
            m = 8;
            break;
        case 128u:
            m = 7;
            break;
        case 64u:
            m = 6;
            break;
        case 32u:
            m = 5;
            break;
        case 16u:
            m = 4;
            break;
        default:
            printf("can not transform, direct use the nds32_cfft_radix2_f32 function\n");
            break;
    }
    if (inv == 0)
    {
#ifdef STATIC_VERSION
        nds32_cfft_radix2_f32(pSrc);
#else
        nds32_cfft_radix2_f32(pSrc, m);
#endif
    }
    else
    {
#ifdef STATIC_VERSION
        nds32_cifft_radix2_f32(pSrc);
#else
        nds32_cifft_radix2_f32(pSrc, m);
#endif
    }
}

FUNC_PREFIX arm_status arm_cfft_radix2_init_q15(arm_cfft_radix2_instance_q15 *S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag)
{
    S->fftLen = fftLen;
    S->ifftFlag = ifftFlag;
    S->bitReverseFlag = bitReverseFlag;
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX void arm_cfft_radix2_q15(const arm_cfft_radix2_instance_q15 *S,
        q15_t *pSrc)
{
    uint32_t n = S->fftLen, m;
    uint32_t i;
    int32_t inv = S->ifftFlag;
    switch (n)
    {
        case 4096u:
            m = 12;
            break;
        case 2048u:
            m = 11;
            break;
        case 1024u:
            m = 10;
            break;
        case 512u:
            m = 9;
            break;
        case 256u:
            m = 8;
            break;
        case 128u:
            m = 7;
            break;
        case 64u:
            m = 6;
            break;
        case 32u:
            m = 5;
            break;
        case 16u:
            m = 4;
            break;
        default:
            printf("can not transform, direct use the nds32_cfft_radix2_q15 function\n");
            break;
    }
    if (inv == 0)
    {
        nds32_cfft_radix2_q15(pSrc, m);
    }
    else
    {
        nds32_cifft_radix2_q15(pSrc, m);
    }
}

FUNC_PREFIX arm_status arm_cfft_radix2_init_q31(arm_cfft_radix2_instance_q31 *S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag)
{
    S->fftLen = fftLen;
    S->ifftFlag = ifftFlag;
    S->bitReverseFlag = bitReverseFlag;
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX void arm_cfft_radix2_q31(const arm_cfft_radix2_instance_q31 *S,
        q31_t *pSrc)
{
    uint32_t n = S->fftLen, m, i;
    int32_t inv = S->ifftFlag;
    switch (n)
    {
        case 4096u:
            m = 12;
            break;
        case 2048u:
            m = 11;
            break;
        case 1024u:
            m = 10;
            break;
        case 512u:
            m = 9;
            break;
        case 256u:
            m = 8;
            break;
        case 128u:
            m = 7;
            break;
        case 64u:
            m = 6;
            break;
        case 32u:
            m = 5;
            break;
        case 16u:
            m = 4;
            break;
        default:
            printf("can not transform, direct use the nds32_cfft_radix2_q31 function\n");
            break;
    }
    if (inv == 0)
    {
        nds32_cfft_radix2_q31(pSrc, m);
    }
    else
    {
        nds32_cifft_radix2_q31(pSrc, m);
    }
}

// CFFT_RADIX4
FUNC_PREFIX arm_status arm_cfft_radix4_init_f32(arm_cfft_radix4_instance_f32 *S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag)
{
    S->fftLen = fftLen;
    S->ifftFlag = ifftFlag;
    S->bitReverseFlag = bitReverseFlag;
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX void arm_cfft_radix4_f32(const arm_cfft_radix4_instance_f32 *S,
        float32_t *pSrc)
{
    uint32_t m = S->fftLen;
    int32_t inv = S->ifftFlag;
    switch (m)
    {
        case 4096u:
            m = 12;
            break;
        case 1024u:
            m = 10;
            break;
        case 256u:
            m = 8;
            break;
        case 64u:
            m = 6;
            break;
        case 16u:
            m = 4;
            break;
        default:
            printf("can not transform, direct use the nds32_cfft_radix4_f32 function\n");
            break;
    }
    if (inv != 0)
    {
        nds32_cifft_radix4_f32(pSrc, m);
    }
    else
    {
        nds32_cfft_radix4_f32(pSrc, m);
    }
}

FUNC_PREFIX arm_status arm_cfft_radix4_init_q15(arm_cfft_radix4_instance_q15 *S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag)
{
    S->fftLen = fftLen;
    S->ifftFlag = ifftFlag;
    S->bitReverseFlag = bitReverseFlag;
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX void arm_cfft_radix4_q15(const arm_cfft_radix4_instance_q15 *S,
        q15_t *pSrc)
{
    uint32_t n = S->fftLen, m, i;
    int32_t inv = S->ifftFlag;
    switch (n)
    {
        case 4096u:
            m = 12;
            break;
        case 1024u:
            m = 10;
            break;
        case 256u:
            m = 8;
            break;
        case 64u:
            m = 6;
            break;
        case 16u:
            m = 4;
            break;
        default:
            printf("can not transform, direct use the nds32_cfft_radix4_f32 function\n");
            break;
    }
    if (inv != 0)
    {
        nds32_cifft_radix4_q15(pSrc, m);
    }
    else
    {
        nds32_cfft_radix4_q15(pSrc, m);
    }

}

FUNC_PREFIX arm_status arm_cfft_radix4_init_q31(arm_cfft_radix4_instance_q31 *S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag)
{
    S->fftLen = fftLen;
    S->ifftFlag = ifftFlag;
    S->bitReverseFlag = bitReverseFlag;
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX void arm_cfft_radix4_q31(const arm_cfft_radix4_instance_q31 *S,
        q31_t *pSrc)
{
    uint32_t n = S->fftLen, m, i;
    int32_t inv = S->ifftFlag;
    switch (n)
    {
        case 4096u:
            m = 12;
            break;
        case 1024u:
            m = 10;
            break;
        case 256u:
            m = 8;
            break;
        case 64u:
            m = 6;
            break;
        case 16u:
            m = 4;
            break;
        default:
            printf("can not transform, direct use the nds32_cfft_radix4_q31 function\n");
            break;
    }
    if (inv == 0)
    {
        nds32_cfft_radix4_q31(pSrc, m);
    }
    else
    {
        nds32_cifft_radix4_q31(pSrc, m);
    }
}

// RFFT

FUNC_PREFIX arm_status arm_rfft_init_f32(arm_rfft_instance_f32 *S,
        __attribute__((__unused__))arm_cfft_radix4_instance_f32 *S_CFFT,
        uint32_t fftLenReal,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag)
{
    S->fftLenReal = fftLenReal;
    S->ifftFlagR = ifftFlagR;
    S->bitReverseFlagR = bitReverseFlag;
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX void arm_rfft_f32(const arm_rfft_instance_f32 *S,
        float32_t *pSrc,
        float32_t *pDst)
{
    uint32_t m = S->fftLenReal;
    uint32_t len = m;
    uint32_t i;
    int32_t inv = S->ifftFlagR;
    switch (m)
    {
        case 8192u:
            m = 13;
            break;
        case 2048u:
            m = 11;
            break;
        case 512u:
            m = 9;
            break;
        case 128u:
            m = 7;
            break;
        default:
            printf("can not transform, direct use the nds32_rfft_f32 function\n");
            break;
    }
    if (inv != 0)
    {
#ifdef STATIC_VERSION
        nds32_rifft_f32(pSrc);
#else
        nds32_rifft_f32(pSrc, m);
#endif
    }
    else
    {
#ifdef STATIC_VERSION
        nds32_rfft_f32(pSrc);
#else
        nds32_rfft_f32(pSrc, m);
#endif
    }
    for (i = 0; i < len; i++)
    {
        *pDst++ = *pSrc++;
    }
}

FUNC_PREFIX arm_status arm_rfft_init_q15(arm_rfft_instance_q15 *S,
        uint32_t fftLenReal,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag)
{
    S->fftLenReal = fftLenReal;
    S->ifftFlagR = ifftFlagR;
    S->bitReverseFlagR = bitReverseFlag;
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX void arm_rfft_q15(const arm_rfft_instance_q15 *S,
        q15_t *pSrc,
        q15_t *pDst)
{
    uint32_t m = S->fftLenReal;
    uint32_t len = m;
    uint32_t i;
    int32_t inv = S->ifftFlagR;
    switch (m)
    {
        case 8192u:
            m = 13;
            break;
        case 2048u:
            m = 11;
            break;
        case 512u:
            m = 9;
            break;
        case 128u:
            m = 7;
            break;
        default:
            printf("can not transform, direct use the nds32_rfft_q15 function\n");
            break;
    }
    if (inv != 0)
    {
#ifdef STATIC_VERSION
        nds32_rifft_q15(pSrc);
        for (i = 0; i < len; i++)
        {
            pSrc[i] = pSrc[i] >> m;
        }
#else
        nds32_rifft_q15(pSrc, m);
        for (i = 0; i < len; i++)
        {
            pSrc[i] = pSrc[i] >> m;
        }
#endif
    }
    else
    {
#ifdef STATIC_VERSION
        nds32_rfft_q15(pSrc);
#else
        nds32_rfft_q15(pSrc, m);
#endif
    }
    for (i = 0; i < len; i++)
    {
        *pDst++ = *pSrc++;
    }
}

FUNC_PREFIX arm_status arm_rfft_init_q31(arm_rfft_instance_q31 *S,
        uint32_t fftLenReal,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag)
{
    S->fftLenReal = fftLenReal;
    S->ifftFlagR = ifftFlagR;
    S->bitReverseFlagR = bitReverseFlag;
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX void arm_rfft_q31(const arm_rfft_instance_q31 *S,
        q31_t *pSrc,
        q31_t *pDst)
{
    uint32_t m = S->fftLenReal;
    uint32_t len = m;
    uint32_t i;
    int32_t inv = S->ifftFlagR;
    switch (m)
    {
        case 8192u:
            m = 13;
            break;
        case 2048u:
            m = 11;
            break;
        case 512u:
            m = 9;
            break;
        case 128u:
            m = 7;
            break;
        default:
            printf("can not transform, direct use the nds32_rfft_q31 function\n");
            break;
    }
    if (inv != 0)
    {
#ifdef STATIC_VERSION
        nds32_rifft_q31(pSrc);
        for (i = 0; i < len; i++)
        {
            pSrc[i] = pSrc[i] >> m;
        }
#else
        nds32_rifft_q31(pSrc, m);
        for (i = 0; i < len; i++)
        {
            pSrc[i] = pSrc[i] >> m;
        }
#endif
    }
    else
    {
#ifdef STATIC_VERSION
        nds32_rfft_q31(pSrc);
#else
        nds32_rfft_q31(pSrc, m);
#endif
    }
    for (i = 0; i < len; i++)
    {
        *pDst++ = *pSrc++;
    }
}

// DCT4
FUNC_PREFIX arm_status arm_dct4_init_f32(arm_dct4_instance_f32 *S,
        __attribute__((__unused__))arm_rfft_instance_f32 *S_RFFT,
        __attribute__((__unused__))arm_cfft_radix4_instance_f32 *S_CFFT,
        uint16_t N,
        __attribute__((__unused__))uint16_t Nby2,
        __attribute__((__unused__))float32_t normalize)
{
    S->N = N;
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX void arm_dct4_f32(const arm_dct4_instance_f32 *S,
        __attribute__((__unused__))float32_t *pState,
        float32_t *pInlineBuffer)
{
    uint32_t m = S->N;
    switch (m)
    {
        case 8192u:
            m = 13;
            break;
        case 2048u:
            m = 11;
            break;
        case 512u:
            m = 9;
            break;
        case 128u:
            m = 7;
            break;
        default:
            printf("can not transform, direct use the nds32_dct4_f32 function\n");
    }
#ifdef STATIC_VERSION
    nds32_dct4_f32(pInlineBuffer);  // if need inv dct4 need to call nds32_idct4_f32
#else
    nds32_dct4_f32(pInlineBuffer, m);  // if need inv dct4 need to call nds32_idct4_f32
#endif // STATIC_VERSION
}

FUNC_PREFIX arm_status arm_dct4_init_q15(arm_dct4_instance_q15 *S,
        __attribute__((__unused__))arm_rfft_instance_q15 *S_RFFT,
        __attribute__((__unused__))arm_cfft_radix4_instance_q15 *S_CFFT,
        uint16_t N,
        __attribute__((__unused__))uint16_t Nby2,
        __attribute__((__unused__))q15_t normalize)
{
    S->N = N;
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX void arm_dct4_q15(const arm_dct4_instance_q15 *S,
        __attribute__((__unused__))q15_t *pState,
        q15_t *pInlineBuffer)
{
    uint32_t m = S->N;
    switch (m)
    {
        case 8192u:
            m = 13;
            break;
        case 2048u:
            m = 11;
            break;
        case 512u:
            m = 9;
            break;
        case 128u:
            m = 7;
            break;
        default:
            printf("can not transform, direct use the nds32_dct4_q15 function\n");
    }
    nds32_dct4_q15(pInlineBuffer, m); // if need inv dct4 need to call nds32_idct4_q15
}

FUNC_PREFIX arm_status arm_dct4_init_q31(arm_dct4_instance_q31 *S,
        __attribute__((__unused__))arm_rfft_instance_q31 *S_RFFT,
        __attribute__((__unused__))arm_cfft_radix4_instance_q31 *S_CFFT,
        uint16_t N,
        __attribute__((__unused__))uint16_t Nby2,
        __attribute__((__unused__))q31_t normalize)
{
    S->N = N;
    return ARM_MATH_SUCCESS;
}

FUNC_PREFIX void arm_dct4_q31(const arm_dct4_instance_q31 *S,
        __attribute__((__unused__))q31_t *pState,
        q31_t *pInlineBuffer)
{
    uint32_t m = S->N;
    switch (m)
    {
        case 8192u:
            m = 13;
            break;
        case 2048u:
            m = 11;
            break;
        case 512u:
            m = 9;
            break;
        case 128u:
            m = 7;
            break;
        default:
            printf("can not transform, direct use the nds32_dct4_q31 function\n");
    }
#ifdef STATIC_VERSION
    nds32_dct4_q31(pInlineBuffer);  // if need inv dct4 need to call nds32_idct4_q31
#else
    nds32_dct4_q31(pInlineBuffer, m);  // if need inv dct4 need to call nds32_idct4_q31
#endif // STATIC_VERSION
}

FUNC_PREFIX q15_t arm_cos_q15(q15_t x)
{
    x = x << 1;
    return nds32_cos_q15(x);
}

FUNC_PREFIX q31_t arm_cos_q31(q31_t x)
{
    x = x << 1;
    return nds32_cos_q31(x);
}

FUNC_PREFIX q15_t arm_sin_q15(q15_t x)
{
    x = x << 1;
    return nds32_sin_q15(x);
}

FUNC_PREFIX q31_t arm_sin_q31(q31_t x)
{
    x = x << 1;
    return nds32_sin_q31(x);
}

#endif // end of __NDS32_CMSIS_TO_NDS_H__
