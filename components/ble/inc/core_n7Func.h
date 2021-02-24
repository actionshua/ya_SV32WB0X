/**************************************************************************//**
 * @file     core_cmFunc.h
 * @brief    CMSIS Cortex-M Core Function Access Header File
 * @version  V4.00
 * @date     28. August 2014
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2009 - 2014 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/


#ifndef __CORE_CMFUNC_H
#define __CORE_CMFUNC_H


/* ###########################  Core Function Access  ########################### */
/** \ingroup  CMSIS_Core_FunctionInterface
    \defgroup CMSIS_Core_RegAccFunctions CMSIS Core Register Access Functions
  @{
 */

#if   defined ( __CC_ARM ) /*------------------RealView Compiler -----------------*/
/* ARM armcc specific functions */

#if (__ARMCC_VERSION < 400677)
  #error "Please use ARM Compiler Toolchain V4.0.677 or later!"
#endif

/* intrinsic void __enable_irq();     */
/* intrinsic void __disable_irq();    */

/** \brief  Get Control Register

    This function returns the content of the Control Register.

    \return               Control Register value
 */
__STATIC_INLINE uint32_t __get_CONTROL(void)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Set Control Register

    This function writes the given value to the Control Register.

    \param [in]    control  Control Register value to set
 */
__STATIC_INLINE void __set_CONTROL(uint32_t control)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Get IPSR Register

    This function returns the content of the IPSR Register.

    \return               IPSR Register value
 */
__STATIC_INLINE uint32_t __get_IPSR(void)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Get APSR Register

    This function returns the content of the APSR Register.

    \return               APSR Register value
 */
__STATIC_INLINE uint32_t __get_APSR(void)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Get xPSR Register

    This function returns the content of the xPSR Register.

    \return               xPSR Register value
 */
__STATIC_INLINE uint32_t __get_xPSR(void)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Get Process Stack Pointer

    This function returns the current value of the Process Stack Pointer (PSP).

    \return               PSP Register value
 */
__STATIC_INLINE uint32_t __get_PSP(void)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Set Process Stack Pointer

    This function assigns the given value to the Process Stack Pointer (PSP).

    \param [in]    topOfProcStack  Process Stack Pointer value to set
 */
__STATIC_INLINE void __set_PSP(uint32_t topOfProcStack)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Get Main Stack Pointer

    This function returns the current value of the Main Stack Pointer (MSP).

    \return               MSP Register value
 */
__STATIC_INLINE uint32_t __get_MSP(void)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Set Main Stack Pointer

    This function assigns the given value to the Main Stack Pointer (MSP).

    \param [in]    topOfMainStack  Main Stack Pointer value to set
 */
__STATIC_INLINE void __set_MSP(uint32_t topOfMainStack)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Get Priority Mask

    This function returns the current state of the priority mask bit from the Priority Mask Register.

    \return               Priority Mask value
 */
__STATIC_INLINE uint32_t __get_PRIMASK(void)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Set Priority Mask

    This function assigns the given value to the Priority Mask Register.

    \param [in]    priMask  Priority Mask
 */
__STATIC_INLINE void __set_PRIMASK(uint32_t priMask)
{
    while(1); //aMH todo: new by N7.
}


#if       (__CORTEX_M >= 0x03) || (__CORTEX_SC >= 300)

/** \brief  Enable FIQ

    This function enables FIQ interrupts by clearing the F-bit in the CPSR.
    Can only be executed in Privileged modes.
 */
#define __enable_fault_irq                __enable_fiq


/** \brief  Disable FIQ

    This function disables FIQ interrupts by setting the F-bit in the CPSR.
    Can only be executed in Privileged modes.
 */
#define __disable_fault_irq               __disable_fiq


/** \brief  Get Base Priority

    This function returns the current value of the Base Priority register.

    \return               Base Priority register value
 */
__STATIC_INLINE uint32_t  __get_BASEPRI(void)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Set Base Priority

    This function assigns the given value to the Base Priority register.

    \param [in]    basePri  Base Priority value to set
 */
__STATIC_INLINE void __set_BASEPRI(uint32_t basePri)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Get Fault Mask

    This function returns the current value of the Fault Mask register.

    \return               Fault Mask register value
 */
__STATIC_INLINE uint32_t __get_FAULTMASK(void)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Set Fault Mask

    This function assigns the given value to the Fault Mask register.

    \param [in]    faultMask  Fault Mask value to set
 */
__STATIC_INLINE void __set_FAULTMASK(uint32_t faultMask)
{
    while(1); //aMH todo: new by N7.
}

#endif /* (__CORTEX_M >= 0x03) || (__CORTEX_SC >= 300) */


#if       (__CORTEX_M == 0x04) || (__CORTEX_M == 0x07)

/** \brief  Get FPSCR

    This function returns the current value of the Floating Point Status/Control register.

    \return               Floating Point Status/Control register value
 */
__STATIC_INLINE uint32_t __get_FPSCR(void)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Set FPSCR

    This function assigns the given value to the Floating Point Status/Control register.

    \param [in]    fpscr  Floating Point Status/Control value to set
 */
__STATIC_INLINE void __set_FPSCR(uint32_t fpscr)
{
    while(1); //aMH todo: new by N7.
}

#endif /* (__CORTEX_M == 0x04) || (__CORTEX_M == 0x07) */


#elif defined ( __GNUC__ ) /*------------------ GNU Compiler ---------------------*/
/* GNU gcc specific functions */

/** \brief  Enable IRQ Interrupts

  This function enables IRQ interrupts by clearing the I-bit in the CPSR.
  Can only be executed in Privileged modes.
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __enable_irq(void)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Disable IRQ Interrupts

  This function disables IRQ interrupts by setting the I-bit in the CPSR.
  Can only be executed in Privileged modes.
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __disable_irq(void)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Get Control Register

    This function returns the content of the Control Register.

    \return               Control Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_CONTROL(void)
{
    while(1); //aMH todo: new by N7.
    return 0;
}


/** \brief  Set Control Register

    This function writes the given value to the Control Register.

    \param [in]    control  Control Register value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_CONTROL(uint32_t control)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Get IPSR Register

    This function returns the content of the IPSR Register.

    \return               IPSR Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_IPSR(void)
{
    while(1); //aMH todo: new by N7.
    return 0;
}


/** \brief  Get APSR Register

    This function returns the content of the APSR Register.

    \return               APSR Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_APSR(void)
{
    while(1); //aMH todo: new by N7.
    return 0;
}


/** \brief  Get xPSR Register

    This function returns the content of the xPSR Register.

    \return               xPSR Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_xPSR(void)
{
    while(1); //aMH todo: new by N7.
    return 0;
}


/** \brief  Get Process Stack Pointer

    This function returns the current value of the Process Stack Pointer (PSP).

    \return               PSP Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_PSP(void)
{
    while(1); //aMH todo: new by N7.
    return 0;
}


/** \brief  Set Process Stack Pointer

    This function assigns the given value to the Process Stack Pointer (PSP).

    \param [in]    topOfProcStack  Process Stack Pointer value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_PSP(uint32_t topOfProcStack)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Get Main Stack Pointer

    This function returns the current value of the Main Stack Pointer (MSP).

    \return               MSP Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_MSP(void)
{
    while(1); //aMH todo: new by N7.
    return 0;
}


/** \brief  Set Main Stack Pointer

    This function assigns the given value to the Main Stack Pointer (MSP).

    \param [in]    topOfMainStack  Main Stack Pointer value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_MSP(uint32_t topOfMainStack)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Get Priority Mask

    This function returns the current state of the priority mask bit from the Priority Mask Register.

    \return               Priority Mask value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_PRIMASK(void)
{
    while(1); //aMH todo: new by N7.
    return 0;
}


/** \brief  Set Priority Mask

    This function assigns the given value to the Priority Mask Register.

    \param [in]    priMask  Priority Mask
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_PRIMASK(uint32_t priMask)
{
    while(1); //aMH todo: new by N7.
}


#if       (__CORTEX_M >= 0x03)

/** \brief  Enable FIQ

    This function enables FIQ interrupts by clearing the F-bit in the CPSR.
    Can only be executed in Privileged modes.
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __enable_fault_irq(void)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Disable FIQ

    This function disables FIQ interrupts by setting the F-bit in the CPSR.
    Can only be executed in Privileged modes.
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __disable_fault_irq(void)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Get Base Priority

    This function returns the current value of the Base Priority register.

    \return               Base Priority register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_BASEPRI(void)
{
    while(1); //aMH todo: new by N7.
    return 0;
}


/** \brief  Set Base Priority

    This function assigns the given value to the Base Priority register.

    \param [in]    basePri  Base Priority value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_BASEPRI(uint32_t value)
{
    while(1); //aMH todo: new by N7.
}


/** \brief  Get Fault Mask

    This function returns the current value of the Fault Mask register.

    \return               Fault Mask register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_FAULTMASK(void)
{
    while(1); //aMH todo: new by N7.
    return 0;
}


/** \brief  Set Fault Mask

    This function assigns the given value to the Fault Mask register.

    \param [in]    faultMask  Fault Mask value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_FAULTMASK(uint32_t faultMask)
{
    while(1); //aMH todo: new by N7.
}

#endif /* (__CORTEX_M >= 0x03) */


#if       (__CORTEX_M == 0x04) || (__CORTEX_M == 0x07)

/** \brief  Get FPSCR

    This function returns the current value of the Floating Point Status/Control register.

    \return               Floating Point Status/Control register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_FPSCR(void)
{
    while(1); //aMH todo: new by N7.
    return 0;
}


/** \brief  Set FPSCR

    This function assigns the given value to the Floating Point Status/Control register.

    \param [in]    fpscr  Floating Point Status/Control value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_FPSCR(uint32_t fpscr)
{
    while(1); //aMH todo: new by N7.
}

#endif /* (__CORTEX_M == 0x04) || (__CORTEX_M == 0x07) */


#elif defined ( __ICCARM__ ) /*------------------ ICC Compiler -------------------*/
/* IAR iccarm specific functions */
#include <cmsis_iar.h>


#elif defined ( __TMS470__ ) /*---------------- TI CCS Compiler ------------------*/
/* TI CCS specific functions */
#include <cmsis_ccs.h>


#elif defined ( __TASKING__ ) /*------------------ TASKING Compiler --------------*/
/* TASKING carm specific functions */
/*
 * The CMSIS functions have been implemented as intrinsics in the compiler.
 * Please use "carm -?i" to get an up to date list of all intrinsics,
 * Including the CMSIS ones.
 */


#elif defined ( __CSMC__ ) /*------------------ COSMIC Compiler -------------------*/
/* Cosmic specific functions */
#include <cmsis_csm.h>

#endif

/*@} end of CMSIS_Core_RegAccFunctions */

#endif /* __CORE_CMFUNC_H */
