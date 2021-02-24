/*
 * FreeRTOS Kernel V10.1.1
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software. If you wish to use our Amazon
 * FreeRTOS name, please do so in a fair use way that does not cause confusion.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef ISR_SUPPORT_H
#define ISR_SUPPORT_H

#include "FreeRTOSConfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef configSUPPORT_FPU
    #if defined(__NDS32_EXT_FPU_DP__) || defined(__NDS32_EXT_FPU_SP__)
        #define configSUPPORT_FPU 1
    #else
        #define configSUPPORT_FPU 0
    #endif
#endif

#ifndef configSUPPORT_IFC
    #ifdef __NDS32_EXT_IFC__
        #define configSUPPORT_IFC 1
    #else
        #define configSUPPORT_IFC 0
    #endif
#endif

#ifndef configSUPPORT_ZOL
    #define configSUPPORT_ZOL 0
#endif

/*When the kernel update, TCB structure may be changed. So the offset need to be modified*/
#if (configHSP_ENABLE==1)
/*Set the bytes of stack's offset in TCB. Unit: 1 byte*/
#define StackOffset_TCB         48 /*The offset of pxCurrentTCB->pxStack in TCB structure*/

/*Set the offset of top address of stack in TCB. Unit: 1 byte*/
#define EndStackOffset_TCB      52 + configMAX_TASK_NAME_LEN /*The offset of pxCurrentTCB->pxEndOfStack in TCB structure*/
#endif

/* The used register numbers of FPU context */
#if ( configSUPPORT_FPU == 1 )
    #if defined(__NDS32_EXT_FPU_CONFIG_0__)
        #define portFPU_REGS    8
    #elif defined(__NDS32_EXT_FPU_CONFIG_1__)
        #define portFPU_REGS    16
    #elif defined(__NDS32_EXT_FPU_CONFIG_2__)
        #define portFPU_REGS    32
    #elif defined(__NDS32_EXT_FPU_CONFIG_3__)
        #define portFPU_REGS    64
    #endif
#endif

/*-----------------------------------------------------------*/

#ifdef __ASSEMBLER__

    /* align $sp to 8B boundary */
    .macro align8_sp R0="$r2", R1="$r3"
        move    \R0, $sp        /*!keep original $sp to be pushed */
#if !defined(__NDS32_ISA_V3M__) || 1 //could be optimized out
    #ifndef __NDS32_EXT_PERF__
        andi    \R1, $sp, #4    /*! R1 = $sp.bit2 // 0 or 4 */
        subri   \R1, \R1, #4    /*! R1 = 4 - R1   // 4 or 0 */
        sub     $sp, $sp, \R1   /*! $sp -= R1     //-4 or 0 */
        push    \R0
    #else
        addi    $sp, $sp, #-4   /*! $sp -= 4 */
        bclr    $sp, $sp, #2    /*! $sp.bit2 = 0 */
        swi     \R0, [$sp]
    #endif
#endif
    .endm

    /**
     *  Save d0d1, ifc_lp, zol
     */
    .macro save_misc
        /* save_d0d1 */
#if (configSUPPORT_D0D1)
        mfusr   $r1, $d1.lo
        mfusr   $r2, $d1.hi
        mfusr   $r3, $d0.lo
        mfusr   $r4, $d0.hi
        pushm   $r1, $r4
#endif

        /* save_ifc_lp */
#if (configSUPPORT_IFC)
        mfusr   $r0, $IFC_LP
        push    $r0
#endif

        /* save_zol */
#if (configSUPPORT_ZOL)
        mfusr   $r1, $LB
        mfusr   $r2, $LE
        mfusr   $r3, $LC
        pushm   $r1, $r3
#endif
    .endm

    /**
     *  Restore d0d1, ifc_lp, zol
     */
    .macro restore_misc
        /* restore_zol */
#if (configSUPPORT_ZOL)
        mfusr   $r1, $LB
        popm    $r1, $r3
        mtusr   $r1, $LB
        mtusr   $r2, $LE
        mtusr   $r3, $LC
#endif

        /* restore_ifc_lp */
#if (configSUPPORT_IFC)
        pop     $r0
        mtusr   $r0, $IFC_LP
#endif

        /* restore_d0d1 */
#if (configSUPPORT_D0D1)
        popm    $r1, $r4
        mtusr   $r1, $d1.lo
        mtusr   $r2, $d1.hi
        mtusr   $r3, $d0.lo
        mtusr   $r4, $d0.hi
#endif
    .endm
/**********************************/
    .macro portSAVE_FPU
#if ( configSUPPORT_FPU == 1 )
        addi    $sp, $sp, -8
    #if ( portFPU_REGS > 32 )
        fsdi.bi $fd31, [$sp], -8
        fsdi.bi $fd30, [$sp], -8
        fsdi.bi $fd29, [$sp], -8
        fsdi.bi $fd28, [$sp], -8
        fsdi.bi $fd27, [$sp], -8
        fsdi.bi $fd26, [$sp], -8
        fsdi.bi $fd25, [$sp], -8
        fsdi.bi $fd24, [$sp], -8
        fsdi.bi $fd23, [$sp], -8
        fsdi.bi $fd22, [$sp], -8
        fsdi.bi $fd21, [$sp], -8
        fsdi.bi $fd20, [$sp], -8
        fsdi.bi $fd19, [$sp], -8
        fsdi.bi $fd18, [$sp], -8
        fsdi.bi $fd17, [$sp], -8
        fsdi.bi $fd16, [$sp], -8
    #endif
    #if ( portFPU_REGS > 16 )
        fsdi.bi $fd15, [$sp], -8
        fsdi.bi $fd14, [$sp], -8
        fsdi.bi $fd13, [$sp], -8
        fsdi.bi $fd12, [$sp], -8
        fsdi.bi $fd11, [$sp], -8
        fsdi.bi $fd10, [$sp], -8
        fsdi.bi $fd9, [$sp], -8
        fsdi.bi $fd8, [$sp], -8
    #endif
    #if ( portFPU_REGS > 8 )
        fsdi.bi $fd7, [$sp], -8
        fsdi.bi $fd6, [$sp], -8
        fsdi.bi $fd5, [$sp], -8
        fsdi.bi $fd4, [$sp], -8
    #endif
        fsdi.bi $fd3, [$sp], -8
        fsdi.bi $fd2, [$sp], -8
        fsdi.bi $fd1, [$sp], -8
        fsdi    $fd0, [$sp+0]
#endif
    .endm

    .macro portRESTORE_FPU
#if ( configSUPPORT_FPU == 1 )
        fldi.bi $fd0, [$sp], 8
        fldi.bi $fd1, [$sp], 8
        fldi.bi $fd2, [$sp], 8
        fldi.bi $fd3, [$sp], 8
    #if ( portFPU_REGS > 8 )
        fldi.bi $fd4, [$sp], 8
        fldi.bi $fd5, [$sp], 8
        fldi.bi $fd6, [$sp], 8
        fldi.bi $fd7, [$sp], 8
    #endif
    #if ( portFPU_REGS > 16 )
        fldi.bi $fd8, [$sp], 8
        fldi.bi $fd9, [$sp], 8
        fldi.bi $fd10, [$sp], 8
        fldi.bi $fd11, [$sp], 8
        fldi.bi $fd12, [$sp], 8
        fldi.bi $fd13, [$sp], 8
        fldi.bi $fd14, [$sp], 8
        fldi.bi $fd15, [$sp], 8
    #endif
    #if ( portFPU_REGS > 32 )
        fldi.bi $fd16, [$sp], 8
        fldi.bi $fd17, [$sp], 8
        fldi.bi $fd18, [$sp], 8
        fldi.bi $fd19, [$sp], 8
        fldi.bi $fd20, [$sp], 8
        fldi.bi $fd21, [$sp], 8
        fldi.bi $fd22, [$sp], 8
        fldi.bi $fd23, [$sp], 8
        fldi.bi $fd24, [$sp], 8
        fldi.bi $fd25, [$sp], 8
        fldi.bi $fd26, [$sp], 8
        fldi.bi $fd27, [$sp], 8
        fldi.bi $fd28, [$sp], 8
        fldi.bi $fd29, [$sp], 8
        fldi.bi $fd30, [$sp], 8
        fldi.bi $fd31, [$sp], 8
    #endif
#endif
    .endm
/*-----------------------------------------------------------*/

    .macro portSAVE_FPU_CALLER
#if ( configSUPPORT_FPU == 1 )
        addi    $sp, $sp, -8
    #if ( portFPU_REGS > 32 )
        fsdi.bi $fd23, [$sp], -8
        fsdi.bi $fd22, [$sp], -8
        fsdi.bi $fd21, [$sp], -8
        fsdi.bi $fd20, [$sp], -8
        fsdi.bi $fd19, [$sp], -8
        fsdi.bi $fd18, [$sp], -8
        fsdi.bi $fd17, [$sp], -8
        fsdi.bi $fd16, [$sp], -8
    #endif
    #if ( portFPU_REGS > 16 )
        fsdi.bi $fd15, [$sp], -8
        fsdi.bi $fd14, [$sp], -8
        fsdi.bi $fd13, [$sp], -8
        fsdi.bi $fd12, [$sp], -8
        fsdi.bi $fd11, [$sp], -8
    #endif
        fsdi.bi $fd2, [$sp], -8
        fsdi.bi $fd1, [$sp], -8
        fsdi    $fd0, [$sp+0]
#endif
    .endm

    .macro portRESTORE_FPU_CALLER
#if ( configSUPPORT_FPU == 1 )
        fldi.bi $fd0, [$sp], 8
        fldi.bi $fd1, [$sp], 8
        fldi.bi $fd2, [$sp], 8
    #if ( portFPU_REGS > 16 )
        fldi.bi $fd11, [$sp], 8
        fldi.bi $fd12, [$sp], 8
        fldi.bi $fd13, [$sp], 8
        fldi.bi $fd14, [$sp], 8
        fldi.bi $fd15, [$sp], 8
    #endif
    #if ( portFPU_REGS > 32 )
        fldi.bi $fd16, [$sp], 8
        fldi.bi $fd17, [$sp], 8
        fldi.bi $fd18, [$sp], 8
        fldi.bi $fd19, [$sp], 8
        fldi.bi $fd20, [$sp], 8
        fldi.bi $fd21, [$sp], 8
        fldi.bi $fd22, [$sp], 8
        fldi.bi $fd23, [$sp], 8
    #endif
#endif
    .endm
/*-----------------------------------------------------------*/

    .macro portSAVE_CONTEXT
        pushm   $r2, $r30

        save_misc

        mfsr    $r0, $PSW
        mfsr    $r1, $IPC
        mfsr    $r2, $IPSW
        pushm   $r0, $r2

        align8_sp
        portSAVE_FPU
    .endm

    .macro portRESTORE_CONTEXT
        portRESTORE_FPU

        lwi     $sp, [$sp]
        popm    $r0, $r2    /* popm $r1 ~ $r2*/
        mtsr    $r1, $IPC
        mtsr    $r2, $IPSW

        restore_misc

        popm    $r2, $r30
    .endm
/*-----------------------------------------------------------*/

    .macro portSAVE_CALLER
        pushm   $r2, $r5
        pushm   $r15,$r30   /* full: 16 gpr, reduce: 6 gpr*/
        /* pushm   $r0, $r25 */

        save_misc

        mfsr    $r0, $PSW
        mfsr    $r1, $IPC
        mfsr    $r2, $IPSW
        pushm   $r0, $r2    /* 3 reg */

        align8_sp          /* already 8-byte align, needn't do again*/

        portSAVE_FPU_CALLER
   .endm

    .macro portRESTORE_CALLER
        portRESTORE_FPU_CALLER

        lwi     $sp, [$sp]
        popm    $r0, $r2    /* popm $r1 ~ $r2*/
        mtsr    $r1, $IPC
        mtsr    $r2, $IPSW

        restore_misc

        popm    $r15, $r30
        popm    $r2,  $r5
    .endm
/*-----------------------------------------------------------*/

#endif /* __ASSEMBLER__ */

#ifdef __cplusplus
}
#endif

#endif /* ISR_SUPPORT_H */
