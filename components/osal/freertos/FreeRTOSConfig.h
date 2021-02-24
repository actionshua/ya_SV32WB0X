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

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

/*
 * The FreeRTOS Quark port implements a full interrupt nesting model.
 *
 * Interrupts that are assigned a priority at or below
 * configMAX_API_CALL_INTERRUPT_PRIORITY can call interrupt safe API functions
 * and will nest.
 *
 * Interrupts that are assigned a priority above
 * configMAX_API_CALL_INTERRUPT_PRIORITY cannot call any FreeRTOS API functions,
 * will nest, and will not be masked by FreeRTOS critical sections (although all
 * interrupts are briefly masked by the hardware itself on interrupt entry).
 *
 * FreeRTOS functions that can be called from an interrupt are those that end in
 * "FromISR".  FreeRTOS maintains a separate interrupt safe API to enable
 * interrupt entry to be shorter, faster, simpler and smaller.
 *
 * The NDS32 port implements 4 unique interrupt priorities.  For the purpose of
 * setting configMAX_API_CALL_INTERRUPT_PRIORITY 3 represents the lowest
 * priority (higher priorities are lower numeric values).
 *
 * User definable interrupt priorities range from 0 (the highest) to 3 (the
 * lowest).
 */
#define configMAX_API_CALL_INTERRUPT_PRIORITY   0

/* The NDS32 port utilizes a software interrupt to perform context switch, then
 * define configIRQ_SWI_VECTOR in FreeRTOSConfig.h to specify the platform software
 * interrupt number. */
#define configIRQ_SWI_VECTOR                    IRQ_SWI_VECTOR

//Unit(ms)
#define OS_CONTEXT_SWITCHING_INTERVAL           1
#define OS_TICK_MAGIC_NUMBER                    ( 1000 / OS_CONTEXT_SWITCHING_INTERVAL )

// #define configCPU_CLOCK_HZ                      ( CPUFREQ )
// #define configPERIPHERAL_CLOCK_HZ               ( PCLKFREQ )

/* Tickless idle/low power functionality support. */
#if defined(SUPPORT_LOW_POWER) && (SUPPORT_LOW_POWER == 1)
#define configUSE_TICKLESS_IDLE                 1
#else
#define configUSE_TICKLESS_IDLE                 0
#endif

#define configTICK_RATE_HZ                      ( ( portTickType ) OS_TICK_MAGIC_NUMBER )
#define configUSE_PREEMPTION                    1
#define configMAX_PRIORITIES                    ( 8 )
#define configMINIMAL_STACK_SIZE                ( (unsigned short)MINIMAL_STACK_SIZE )
#define configMAX_TASK_NAME_LEN                 ( 16 )
#define configUSE_16_BIT_TICKS                  0
#define configIDLE_SHOULD_YIELD                 1
#define configUSE_TASK_NOTIFICATIONS            1
#define configUSE_MUTEXES                       1
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_COUNTING_SEMAPHORES           1
#define configQUEUE_REGISTRY_SIZE               10
#define configUSE_QUEUE_SETS                    0

/* Memory allocation definitions. */
#define configSUPPORT_STATIC_ALLOCATION         1
#define configSUPPORT_DYNAMIC_ALLOCATION        1
// #define configTOTAL_HEAP_SIZE                   ( ( size_t ) ( 128 * 1024 ) )

/* Hook function definitions. */
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configCHECK_FOR_STACK_OVERFLOW          0
#define configUSE_MALLOC_FAILED_HOOK            0
#define configUSE_DAEMON_TASK_STARTUP_HOOK      0

/* Run time and task stats gathering definitions. */
#define configGENERATE_RUN_TIME_STATS           0
#define configUSE_TRACE_FACILITY                1       // Awareness debugging used
#define configUSE_STATS_FORMATTING_FUNCTIONS    0

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES                   0
#define configMAX_CO_ROUTINE_PRIORITIES         ( 2 )

/* Software timer definitions. */
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               ( 7 )
#define configTIMER_QUEUE_LENGTH                5
#define configTIMER_TASK_STACK_DEPTH            ( configMINIMAL_STACK_SIZE * 4 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskCleanUpResources           0
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_xTimerPendFunctionCall          1
#define INCLUDE_eTaskGetState                   0
#define INCLUDE_xTaskAbortDelay                 1
#define INCLUDE_xTaskGetHandle                  1
#define INCLUDE_xSemaphoreGetMutexHolder        1

/* The size of the global output buffer that is available for use when there
are multiple command interpreters running at once (for example, one on a UART
and one on TCP/IP).  This is done to prevent an output buffer being defined by
each implementation - which would waste RAM.  In this case, there is only one
command interpreter running. */
/* The buffer into which output generated by FreeRTOS+CLI is placed.  This must
be at least big enough to contain the output of the task-stats command, as the
example implementation does not include buffer overlow checking. */
#define configCOMMAND_INT_MAX_OUTPUT_SIZE       2096
#define configINCLUDE_QUERY_HEAP_COMMAND        1

/* This file is included from assembler files - make sure C code is not included
in assembler files. */
#ifndef __ASSEMBLER__
    void vAssertCalled( const char *func, int line );
    // void vConfigureTickInterrupt( void );
    // void vClearTickInterrupt( void );
    // void vEnableTickInterrupt( long xEnable );
    // void vSetTickReload( uint32_t ulReload );
    // uint32_t ulGetTickCounter( void );

    // void vPreSleepProcessing( unsigned long uxExpectedIdleTime );
    // void vPostSleepProcessing( unsigned long uxExpectedIdleTime );
#endif /* __ASSEMBLER__ */



/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __func__, __LINE__ );



/****** Hardware/compiler specific settings. *******************************************/

/**
 *  Support 'inline function call'
 */
#define configSUPPORT_IFC                       0

#ifdef __NDS32_EXT_IFC__
#ifndef CONFIG_NO_NDS32_EXT_IFC
#undef configSUPPORT_IFC
#define configSUPPORT_IFC                       1
#endif
#endif

/**
 * Support d0/d1 handle
 */
#define configSUPPORT_D0D1                      0

#if (defined(__NDS32_ISA_V2__) && defined(__NDS32_DX_REGS__)) || \
    (!defined(__NDS32_ISA_V2__) && (defined(__NDS32_DIV__) || defined(__NDS32_MAC__)))
    #define configSUPPORT_D0D1                  1
#endif

/*
 * Support zero-overhead loop mechanism or not.
 * If configSUPPORT_ZOL is set to 1 then tasks can optionally have a ZOL system
 * registers context (the ZOL system registers will be saved as part of the task
 * context).
 *
 * If configSUPPORT_ZOL is set to 0 then ZOL system registers must never be used.
 */
#ifdef CONFIG_HWZOL
    #define configSUPPORT_ZOL                   1
#else
    #define configSUPPORT_ZOL                   0
#endif

/*
 * The application must provide a function that configures a peripheral to
 * create the FreeRTOS tick interrupt, then define configSETUP_TICK_INTERRUPT()
 * in FreeRTOSConfig.h to call the function.  This file contains a function
 * that is suitable for use on the Andes AE210P.  FreeRTOS_Tick_Handler() must
 * be installed as the peripheral's interrupt handler.
 */
#ifndef __ASSEMBLER__
    extern void OS_ConfigureTickInterrupt(void);
    extern void OS_ClearTickInterrupt(void);
    #define configSETUP_TICK_INTERRUPT()     OS_ConfigureTickInterrupt()
    #define configCLEAR_TICK_INTERRUPT()     OS_ClearTickInterrupt()
    // #define configENABLE_TICK_INTERRUPT( x ) vEnableTickInterrupt( x )
    // #define configSET_TICK_RELOAD( x )       vSetTickReload( x )
    // #define configGET_TICK_COUNTER()         ulGetTickCounter()
#endif

/* The configPRE_SLEEP_PROCESSING() and configPOST_SLEEP_PROCESSING() macros
allow the application writer to add additional code before and after the MCU is
placed into the low power state respectively.  The empty implementations
provided in this demo can be extended to save even more power. */
// #define configPRE_SLEEP_PROCESSING( uxExpectedIdleTime ) vPreSleepProcessing( uxExpectedIdleTime );
// #define configPOST_SLEEP_PROCESSING( uxExpectedIdleTime ) vPostSleepProcessing( uxExpectedIdleTime );

/* Compiler specifics. */
#define fabs( x ) __builtin_fabs( x )

/* Enable Hardware Stack Protection and Recording mechanism. */
#define configHSP_ENABLE                0

#if defined(CONFIG_SUPPORT_HSP) && (CONFIG_SUPPORT_HSP)
#undef configHSP_ENABLE
#define configHSP_ENABLE                1
#endif

/* Record the highest address of stack. */
#if (configHSP_ENABLE == 1 && configRECORD_STACK_HIGH_ADDRESS != 1 )
    #define configRECORD_STACK_HIGH_ADDRESS     0
#endif

/**
 *  extend definitions
 */
#define configLIST_VOLATILE                 volatile
#define configUSE_APPLICATION_TASK_TAG          1

#if defined(BUILD_DEBUG)
    #define INCLUDE_uxTaskGetStackHighWaterMark     1
#else
    #define INCLUDE_uxTaskGetStackHighWaterMark     0
#endif

#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetIdleTaskHandle          1


#if !defined(__ASSEMBLER__) &&  defined(OSAL_SYS_INFO_EN)
    extern void OS_TaskSwitchIn_trace(void);
    #define traceTASK_SWITCHED_IN()     OS_TaskSwitchIn_trace()

    extern void OS_TaskSwitchOut_trace(void);
    #define traceTASK_SWITCHED_OUT()    OS_TaskSwitchOut_trace()

    extern void OS_TaskCreate_trace(void *taskHandle, unsigned int stackDepth);
    #define traceTASK_CREATE(pxNewTCB, usStackDepth)    OS_TaskCreate_trace((pxNewTCB), (usStackDepth))

    extern void OS_TaskDelete_trace(void *taskHandle);
    #define traceTASK_DELETE(pxTaskToDelete)            OS_TaskDelete_trace((pxTaskToDelete))
#endif

/**
 * Create task with static stack pool
 */
#if defined(configSUPPORT_STATIC_ALLOCATION) && (configSUPPORT_STATIC_ALLOCATION)
    #define vApplicationGetIdleTaskMemory    OS_GetIdleTaskMemory
    #define vApplicationGetTimerTaskMemory   OS_GetTimerTaskMemory
#endif

#define CONFIG_STACK_CHECKING_PRECISION     256
#define CONFIG_STACK_CHECKING_PATTERN       0x5AA5AA00

#endif /* FREERTOS_CONFIG_H */
