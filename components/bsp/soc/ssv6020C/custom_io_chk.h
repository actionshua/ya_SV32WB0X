#ifndef CUSTOM_IO_CHK_H
#define CUSTOM_IO_CHK_H

//#ifndef CUSTOM_IO_CHK_6020C_H
//#define CUSTOM_IO_CHK_6020C_H

#define M_CUSTOM_ALT0 (0)
#define M_CUSTOM_ALT1 (1)
#define M_CUSTOM_ALT2 (2)
#define M_CUSTOM_ALT3 (3)
#define M_CUSTOM_ALT4 (4)
#define M_CUSTOM_ALT5 (5)
#define M_CUSTOM_ALT6 (6)
#define M_CUSTOM_ALT7 (7)
#define M_CUSTOM_PWM0 (8)
#define M_CUSTOM_PWM1 (9)
#define M_CUSTOM_PWM2 (10)
#define M_CUSTOM_PWM3 (11)
#define M_CUSTOM_PWM4 (12)
#define M_CUSTOM_PWM5 (13)
#define M_CUSTOM_PWM6 (14)
#define M_CUSTOM_PWM7 (15)

#if (IC_PACKAGE == P32)
#include "custom_io_P32_to_full.h"
#elif (IC_PACKAGE == P40)
#include "custom_io_P40_to_full.h"
#elif (IC_PACKAGE == P60)
#include "custom_io_P60_to_full.h"
#endif

#if defined(BUILD_SDK)
#define PERI_IO_ADC0        (0)
#define PERI_IO_ADC1        (0)
#define PERI_IO_ADC2        (0)
#define PERI_IO_ADC3        (0)
#define PERI_IO_ADC4        (0)
#define PERI_IO_ADC5        (0)
#define PERI_IO_ADC6        (0)
#define PERI_IO_ADC7        (0)
#define PERI_IO_UART0       (0)
#define PERI_IO_UART1       (0)
#define PERI_IO_UART2       (0)
#define PERI_IO_SPIS0       (0)
#define PERI_IO_SPIS1       (0)
#define PERI_IO_SPIM0       (0)
#define PERI_IO_SPIM1       (0)
#define PERI_IO_SPIM2       (0)
#define PERI_IO_PWM0        (0)
#define PERI_IO_PWM1        (0)
#define PERI_IO_PWM2        (0)
#define PERI_IO_PWM3        (0)
#define PERI_IO_PWM4        (0)
#define PERI_IO_PWM5        (0)
#define PERI_IO_PWM6        (0)
#define PERI_IO_PWM7        (0)
#define PERI_IO_I2C0        (0)
#define PERI_IO_I2C1        (0)
#define PERI_IO_I2S0        (0)
#define PERI_IO_I2S1        (0)
#endif


#if ((M_CUSTOM_P00_MODE) == (M_CUSTOM_ALT0))		//AICE, Boot strapping mode
	#define _M_P00_MODE         (0x0 << GPIO_00)
	#define _M_P00_FUNC_SEL     (0)                 
	#define _M_P00_FUNC1_SEL    (0)
	#define _M_P00_GPIO_MODE    (0x0 << GPIO_00)
#elif ((M_CUSTOM_P00_MODE) == (M_CUSTOM_ALT1))
	#define _M_P00_MODE         (0x1 << GPIO_00)
	#define _M_P00_FUNC_SEL     (0x1 << SEL_ADC0)
	#define _M_P00_FUNC1_SEL    (0)
	#define _M_P00_GPIO_MODE    (0x0 << GPIO_00)
    #define PERI_IO_ADC0        (0)
#elif ((M_CUSTOM_P00_MODE) == (M_CUSTOM_ALT2))
	#define _M_P00_MODE         (0x1 << GPIO_00)
	#define _M_P00_FUNC_SEL     (0x1 << SEL_ANTSW_II)
	#define _M_P00_FUNC1_SEL    (0)
	#define _M_P00_GPIO_MODE    (0x0 << GPIO_00)
    #define PERI_IO_ANTSW
#elif ((M_CUSTOM_P00_MODE) == (M_CUSTOM_ALT3))
	#define _M_P00_MODE         (0x1 << GPIO_00)
	#define _M_P00_FUNC_SEL     (0x1 << SEL_UART0)
	#define _M_P00_FUNC1_SEL    (0)
	#define _M_P00_GPIO_MODE    (0x0 << GPIO_00)
    #define PERI_IO_UART0       (0)
#elif ((M_CUSTOM_P00_MODE) == (M_CUSTOM_ALT4))
	#define _M_P00_MODE         (0x1 << GPIO_00)
	#define _M_P00_FUNC_SEL     (0)
	#define _M_P00_FUNC1_SEL    (0x1 << SEL_SPISLV0)
	#define _M_P00_GPIO_MODE    (0x0 << GPIO_00)
    #define PERI_IO_SPIS0       (0)
#elif ((M_CUSTOM_P00_MODE) == (M_CUSTOM_ALT5))
	#define _M_P00_MODE         (0x1 << GPIO_00)
	#define _M_P00_FUNC_SEL     (0)
	#define _M_P00_FUNC1_SEL    (0x1 << SEL_SPIMAS0)
	#define _M_P00_GPIO_MODE    (0x0 << GPIO_00)
    #define PERI_IO_SPIM0       (0)
#elif ((M_CUSTOM_P00_MODE) == (M_CUSTOM_ALT6))
	#error M_CUSTOM_P00_MODE define NONE!
#elif ((M_CUSTOM_P00_MODE) == (M_CUSTOM_ALT7))
	#define _M_P00_MODE         (0x1 << GPIO_00)
	#define _M_P00_FUNC_SEL     (0)
	#define _M_P00_FUNC1_SEL    (0)
	#define _M_P00_GPIO_MODE    (0x1 << GPIO_00)
#else
    #define _M_P00_MODE         (0x0 << GPIO_00)
    #define _M_P00_FUNC_SEL     (0)
    #define _M_P00_FUNC1_SEL    (0)
    #define _M_P00_GPIO_MODE    (0x0 << GPIO_00)
    #if   ((M_CUSTOM_P00_MODE) == (M_CUSTOM_PWM0))
        #if defined(M_CUSTOM_PWM0_PIN)
            #error M_CUSTOM_P00_MODE define PWM0 collision to other pin.
        #endif
        #define M_CUSTOM_PWM0_PIN           (GPIO_00)
        #define PERI_IO_PWM0    (0)
    #elif   ((M_CUSTOM_P00_MODE) == (M_CUSTOM_PWM1))
        #if defined(M_CUSTOM_PWM1_PIN)
            #error M_CUSTOM_P00_MODE define PWM1 collision to other pin.
        #endif
        #define M_CUSTOM_PWM1_PIN           (GPIO_00)
        #define PERI_IO_PWM1    (0)
    #elif   ((M_CUSTOM_P00_MODE) == (M_CUSTOM_PWM2))
        #if defined(M_CUSTOM_PWM2_PIN)
            #error M_CUSTOM_P00_MODE define PWM2 collision to other pin.
        #endif
        #define M_CUSTOM_PWM2_PIN           (GPIO_00)
        #define PERI_IO_PWM2    (0)
    #elif   ((M_CUSTOM_P00_MODE) == (M_CUSTOM_PWM3))
        #if defined(M_CUSTOM_PWM3_PIN)
            #error M_CUSTOM_P00_MODE define PWM3 collision to other pin.
        #endif
        #define M_CUSTOM_PWM3_PIN           (GPIO_00)
        #define PERI_IO_PWM3    (0)
    #elif   ((M_CUSTOM_P00_MODE) == (M_CUSTOM_PWM4))
        #if defined(M_CUSTOM_PWM4_PIN)
            #error M_CUSTOM_P00_MODE define PWM4 collision to other pin.
        #endif
        #define M_CUSTOM_PWM4_PIN           (GPIO_00)
        #define PERI_IO_PWM4    (0)
    #elif   ((M_CUSTOM_P00_MODE) == (M_CUSTOM_PWM5))
        #if defined(M_CUSTOM_PWM5_PIN)
            #error M_CUSTOM_P00_MODE define PWM5 collision to other pin.
        #endif
        #define M_CUSTOM_PWM5_PIN           (GPIO_00)
        #define PERI_IO_PWM5    (0)
    #elif   ((M_CUSTOM_P00_MODE) == (M_CUSTOM_PWM6))
        #if defined(M_CUSTOM_PWM6_PIN)
            #error M_CUSTOM_P00_MODE define PWM6 collision to other pin.
        #endif
        #define M_CUSTOM_PWM6_PIN           (GPIO_00)
        #define PERI_IO_PWM6    (0)
    #elif   ((M_CUSTOM_P00_MODE) == (M_CUSTOM_PWM7))
        #if defined(M_CUSTOM_PWM7_PIN)
            #error M_CUSTOM_P00_MODE define PWM7 collision to other pin.
        #endif
        #define M_CUSTOM_PWM7_PIN           (GPIO_00)
        #define PERI_IO_PWM7    (0)
    #else
    #endif
#endif

#if ((M_CUSTOM_P01_MODE) == (M_CUSTOM_ALT0))		//AICE, Boot strapping mode
	#define _M_P01_MODE         (0x0 << GPIO_01)
	#define _M_P01_FUNC_SEL     (0)                 
	#define _M_P01_FUNC1_SEL    (0)
	#define _M_P01_GPIO_MODE    (0x0 << GPIO_01)
#elif ((M_CUSTOM_P01_MODE) == (M_CUSTOM_ALT1))
	#define _M_P01_MODE         (0x1 << GPIO_01)
	#define _M_P01_FUNC_SEL     (0x1 << SEL_ADC1)
	#define _M_P01_FUNC1_SEL    (0)
	#define _M_P01_GPIO_MODE    (0x0 << GPIO_01)
    #define PERI_IO_ADC1        (0)
#elif ((M_CUSTOM_P01_MODE) == (M_CUSTOM_ALT2))
	#define _M_P01_MODE         (0x1 << GPIO_01)
	#define _M_P01_FUNC_SEL     (0x1 << SEL_ANTSW_II)
	#define _M_P01_FUNC1_SEL    (0)
	#define _M_P01_GPIO_MODE    (0x0 << GPIO_01)
    #define PERI_IO_ANTSW
#elif ((M_CUSTOM_P01_MODE) == (M_CUSTOM_ALT3))
	#define _M_P01_MODE         (0x1 << GPIO_01)
	#define _M_P01_FUNC_SEL     (0x1 << SEL_UART0)
	#define _M_P01_FUNC1_SEL    (0)
	#define _M_P01_GPIO_MODE    (0x0 << GPIO_01)
    #define PERI_IO_UART0       (0)
#elif ((M_CUSTOM_P01_MODE) == (M_CUSTOM_ALT4))
	#define _M_P01_MODE         (0x1 << GPIO_01)
	#define _M_P01_FUNC_SEL     (0)
	#define _M_P01_FUNC1_SEL    (0x1 << SEL_SPISLV0)
	#define _M_P01_GPIO_MODE    (0x0 << GPIO_01)
    #define PERI_IO_SPIS0       (0)
#elif ((M_CUSTOM_P01_MODE) == (M_CUSTOM_ALT5))
	#define _M_P01_MODE         (0x1 << GPIO_01)
	#define _M_P01_FUNC_SEL     (0)
	#define _M_P01_FUNC1_SEL    (0x1 << SEL_SPIMAS0)
	#define _M_P01_GPIO_MODE    (0x0 << GPIO_01)
    #define PERI_IO_SPIM0       (0)
#elif ((M_CUSTOM_P01_MODE) == (M_CUSTOM_ALT6))
	#error M_CUSTOM_P01_MODE define NONE!
#elif ((M_CUSTOM_P01_MODE) == (M_CUSTOM_ALT7))
	#define _M_P01_MODE         (0x1 << GPIO_01)
	#define _M_P01_FUNC_SEL     (0)
	#define _M_P01_FUNC1_SEL    (0)
	#define _M_P01_GPIO_MODE    (0x1 << GPIO_01)
#else
    #define _M_P01_MODE         (0x0 << GPIO_01)
    #define _M_P01_FUNC_SEL     (0)
    #define _M_P01_FUNC1_SEL    (0)
    #define _M_P01_GPIO_MODE    (0x0 << GPIO_01)
    #if   ((M_CUSTOM_P01_MODE) == (M_CUSTOM_PWM0))
        #if defined(M_CUSTOM_PWM0_PIN)
            #error M_CUSTOM_P01_MODE define PWM0 collision to other pin.
        #endif
        #define M_CUSTOM_PWM0_PIN           (GPIO_01)
        #define PERI_IO_PWM0    (0)
    #elif   ((M_CUSTOM_P01_MODE) == (M_CUSTOM_PWM1))
        #if defined(M_CUSTOM_PWM1_PIN)
            #error M_CUSTOM_P01_MODE define PWM1 collision to other pin.
        #endif
        #define M_CUSTOM_PWM1_PIN           (GPIO_01)
        #define PERI_IO_PWM1    (0)
    #elif   ((M_CUSTOM_P01_MODE) == (M_CUSTOM_PWM2))
        #if defined(M_CUSTOM_PWM2_PIN)
            #error M_CUSTOM_P01_MODE define PWM2 collision to other pin.
        #endif
        #define M_CUSTOM_PWM2_PIN           (GPIO_01)
        #define PERI_IO_PWM2    (0)
    #elif   ((M_CUSTOM_P01_MODE) == (M_CUSTOM_PWM3))
        #if defined(M_CUSTOM_PWM3_PIN)
            #error M_CUSTOM_P01_MODE define PWM3 collision to other pin.
        #endif
        #define M_CUSTOM_PWM3_PIN           (GPIO_01)
        #define PERI_IO_PWM3    (0)
    #elif   ((M_CUSTOM_P01_MODE) == (M_CUSTOM_PWM4))
        #if defined(M_CUSTOM_PWM4_PIN)
            #error M_CUSTOM_P01_MODE define PWM4 collision to other pin.
        #endif
        #define M_CUSTOM_PWM4_PIN           (GPIO_01)
        #define PERI_IO_PWM4    (0)
    #elif   ((M_CUSTOM_P01_MODE) == (M_CUSTOM_PWM5))
        #if defined(M_CUSTOM_PWM5_PIN)
            #error M_CUSTOM_P01_MODE define PWM5 collision to other pin.
        #endif
        #define M_CUSTOM_PWM5_PIN           (GPIO_01)
        #define PERI_IO_PWM5    (0)
    #elif   ((M_CUSTOM_P01_MODE) == (M_CUSTOM_PWM6))
        #if defined(M_CUSTOM_PWM6_PIN)
            #error M_CUSTOM_P01_MODE define PWM6 collision to other pin.
        #endif
        #define M_CUSTOM_PWM6_PIN           (GPIO_01)
        #define PERI_IO_PWM6    (0)
    #elif   ((M_CUSTOM_P01_MODE) == (M_CUSTOM_PWM7))
        #if defined(M_CUSTOM_PWM7_PIN)
            #error M_CUSTOM_P01_MODE define PWM7 collision to other pin.
        #endif
        #define M_CUSTOM_PWM7_PIN           (GPIO_01)
        #define PERI_IO_PWM7    (0)
    #endif
#endif

#if ((M_CUSTOM_P02_MODE) == (M_CUSTOM_ALT0))
	#define _M_P02_MODE         (0x0 << GPIO_02)
	#define _M_P02_FUNC_SEL     (0)
	#define _M_P02_FUNC1_SEL    (0)
	#define _M_P02_GPIO_MODE    (0x0 << GPIO_02)
#elif ((M_CUSTOM_P02_MODE) == (M_CUSTOM_ALT1))
	#define _M_P02_MODE         (0x1 << GPIO_02)
	#define _M_P02_FUNC_SEL     (0x1 << SEL_ADC2)
	#define _M_P02_FUNC1_SEL    (0)
	#define _M_P02_GPIO_MODE    (0x0 << GPIO_02)
    #define PERI_IO_ADC2        (0)
#elif ((M_CUSTOM_P02_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P02_MODE define NONE!
#elif ((M_CUSTOM_P02_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P02_MODE define NONE!
#elif ((M_CUSTOM_P02_MODE) == (M_CUSTOM_ALT4))
	#define _M_P02_MODE         (0x1 << GPIO_02)
	#define _M_P02_FUNC_SEL     (0)
	#define _M_P02_FUNC1_SEL    (0x1 << SEL_SPISLV0)
	#define _M_P02_GPIO_MODE    (0x0 << GPIO_02)
    #define PERI_IO_SPIS0       (0)
#elif ((M_CUSTOM_P01_MODE) == (M_CUSTOM_ALT5))
	#define _M_P02_MODE         (0x1 << GPIO_02)
	#define _M_P02_FUNC_SEL     (0)
	#define _M_P02_FUNC1_SEL    (0x1 << SEL_SPIMAS0)
	#define _M_P02_GPIO_MODE    (0x0 << GPIO_02)
    #define PERI_IO_SPIM0       (0)
#elif ((M_CUSTOM_P02_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P02_MODE define NONE!
#elif ((M_CUSTOM_P02_MODE) == (M_CUSTOM_ALT7))
	#define _M_P02_MODE         (0x1 << GPIO_02)
	#define _M_P02_FUNC_SEL     (0)
	#define _M_P02_FUNC1_SEL    (0)
	#define _M_P02_GPIO_MODE    (0x1 << GPIO_02)
#else
	#define _M_P02_MODE         (0x0 << GPIO_02)
	#define _M_P02_FUNC_SEL     (0)
	#define _M_P02_FUNC1_SEL    (0)
	#define _M_P02_GPIO_MODE    (0x0 << GPIO_02)
	#if   ((M_CUSTOM_P02_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P02_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_02)
        #define PERI_IO_PWM0    (0)
	#elif   ((M_CUSTOM_P02_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P02_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_02)
        #define PERI_IO_PWM1    (0)
	#elif   ((M_CUSTOM_P02_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P02_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_02)
        #define PERI_IO_PWM2    (0)
	#elif   ((M_CUSTOM_P02_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P02_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_02)
        #define PERI_IO_PWM3    (0)
	#elif   ((M_CUSTOM_P02_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P02_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_02)
        #define PERI_IO_PWM4    (0)
	#elif   ((M_CUSTOM_P02_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P02_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_02)
        #define PERI_IO_PWM5    (0)
	#elif   ((M_CUSTOM_P02_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P02_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_02)
        #define PERI_IO_PWM6    (0)
	#elif   ((M_CUSTOM_P02_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P02_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_02)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P03_MODE) == (M_CUSTOM_ALT0))
	#define _M_P03_MODE         (0x0 << GPIO_03)
	#define _M_P03_FUNC_SEL     (0)
	#define _M_P03_FUNC1_SEL    (0)
	#define _M_P03_GPIO_MODE    (0x0 << GPIO_03)
#elif ((M_CUSTOM_P03_MODE) == (M_CUSTOM_ALT1))
    #error M_CUSTOM_P03_MODE define NONE!
#elif ((M_CUSTOM_P03_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P03_MODE define NONE!
#elif ((M_CUSTOM_P03_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P03_MODE define NONE!
#elif ((M_CUSTOM_P03_MODE) == (M_CUSTOM_ALT4))
	#define _M_P03_MODE         (0x1 << GPIO_03)
	#define _M_P03_FUNC_SEL     (0)
	#define _M_P03_FUNC1_SEL    (0x1 << SEL_SPISLV0_CSN_II)
	#define _M_P03_GPIO_MODE    (0x0 << GPIO_03)
    #define PERI_IO_SPIS0       (0)
#elif ((M_CUSTOM_P03_MODE) == (M_CUSTOM_ALT5))
	#define _M_P03_MODE         (0x1 << GPIO_03)
	#define _M_P03_FUNC_SEL     (0)
	#define _M_P03_FUNC1_SEL    (0x1 << SEL_SPIMAS0_CSN_II)
	#define _M_P03_GPIO_MODE    (0x0 << GPIO_03)
    #define PERI_IO_SPIM0       (0)
#elif ((M_CUSTOM_P03_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P03_MODE define NONE!
#elif ((M_CUSTOM_P03_MODE) == (M_CUSTOM_ALT7))
	#define _M_P03_MODE         (0x1 << GPIO_03)
	#define _M_P03_FUNC_SEL     (0)
	#define _M_P03_FUNC1_SEL    (0)
	#define _M_P03_GPIO_MODE    (0x1 << GPIO_03)
#else
	#define _M_P03_MODE         (0x0 << GPIO_03)
	#define _M_P03_FUNC_SEL     (0)
	#define _M_P03_FUNC1_SEL    (0)
	#define _M_P03_GPIO_MODE    (0x0 << GPIO_03)
	#if   ((M_CUSTOM_P03_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P03_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_03)
        #define PERI_IO_PWM0    (0)
	#elif   ((M_CUSTOM_P03_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P03_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_03)
        #define PERI_IO_PWM1    (0)
	#elif   ((M_CUSTOM_P03_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P03_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_03)
        #define PERI_IO_PWM2    (0)
	#elif   ((M_CUSTOM_P03_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P03_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_03)
        #define PERI_IO_PWM3    (0)
	#elif   ((M_CUSTOM_P03_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P03_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_03)
        #define PERI_IO_PWM4    (0)
	#elif   ((M_CUSTOM_P03_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P03_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_03)
        #define PERI_IO_PWM5    (0)
	#elif   ((M_CUSTOM_P03_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P03_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_03)
        #define PERI_IO_PWM6    (0)
	#elif   ((M_CUSTOM_P03_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P03_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_03)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P04_MODE) == (M_CUSTOM_ALT0))
	#define _M_P04_MODE         (0x0 << GPIO_04)
	#define _M_P04_FUNC_SEL     (0)
	#define _M_P04_FUNC1_SEL    (0)
	#define _M_P04_GPIO_MODE    (0x0 << GPIO_04)
#elif ((M_CUSTOM_P04_MODE) == (M_CUSTOM_ALT1))
	#define _M_P04_MODE         (0x1 << GPIO_04)
	#define _M_P04_FUNC_SEL     (0x1 << SEL_I2C0)
	#define _M_P04_FUNC1_SEL    (0)
	#define _M_P04_GPIO_MODE    (0x0 << GPIO_04)
    #define PERI_IO_I2C0        (0)
#elif ((M_CUSTOM_P04_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P04_MODE define NONE!
#elif ((M_CUSTOM_P04_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P04_MODE define NONE!
#elif ((M_CUSTOM_P04_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P04_MODE define NONE!
#elif ((M_CUSTOM_P04_MODE) == (M_CUSTOM_ALT5))
    #error M_CUSTOM_P04_MODE define NONE!
#elif ((M_CUSTOM_P04_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P04_MODE define NONE!
#elif ((M_CUSTOM_P04_MODE) == (M_CUSTOM_ALT7))
	#define _M_P04_MODE         (0x1 << GPIO_04)
	#define _M_P04_FUNC_SEL     (0)
	#define _M_P04_FUNC1_SEL    (0)
	#define _M_P04_GPIO_MODE    (0x1 << GPIO_04)
#else
	#define _M_P04_MODE         (0x0 << GPIO_04)
	#define _M_P04_FUNC_SEL     (0)
	#define _M_P04_FUNC1_SEL    (0)
	#define _M_P04_GPIO_MODE    (0x0 << GPIO_04)
	#if   ((M_CUSTOM_P04_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P04_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_04)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P04_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P04_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_04)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P04_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P04_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_04)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P04_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P04_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_04)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P04_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P04_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_04)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P04_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P04_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_04)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P04_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P04_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_04)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P04_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P04_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_04)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P05_MODE) == (M_CUSTOM_ALT0))
	#define _M_P05_MODE         (0x0 << GPIO_05)
	#define _M_P05_FUNC_SEL     (0)
	#define _M_P05_FUNC1_SEL    (0)
	#define _M_P05_GPIO_MODE    (0x0 << GPIO_05)
#elif ((M_CUSTOM_P05_MODE) == (M_CUSTOM_ALT1))
    #error M_CUSTOM_P05_MODE define NONE!
#elif ((M_CUSTOM_P05_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P05_MODE define NONE!
#elif ((M_CUSTOM_P05_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P05_MODE define NONE!
#elif ((M_CUSTOM_P05_MODE) == (M_CUSTOM_ALT4))
    #define _M_P05_MODE         (0x1 << GPIO_05)
    #define _M_P05_FUNC_SEL     (0)
    #define _M_P05_FUNC1_SEL    (0x1 << SEL_SPIMAS0_CSN)
    #define _M_P05_GPIO_MODE    (0x0 << GPIO_05)
    #define PERI_IO_SPIM0       (0)
#elif ((M_CUSTOM_P05_MODE) == (M_CUSTOM_ALT5))
    #define _M_P05_MODE         (0x1 << GPIO_05)
    #define _M_P05_FUNC_SEL     (0)
    #define _M_P05_FUNC1_SEL    (0x1 << SEL_SPISLV0_CSN)
    #define _M_P05_GPIO_MODE    (0x0 << GPIO_05)
    #define PERI_IO_SPIS0       (0)
#elif ((M_CUSTOM_P05_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P05_MODE define NONE!
#elif ((M_CUSTOM_P05_MODE) == (M_CUSTOM_ALT7))
	#define _M_P05_MODE         (0x1 << GPIO_05)
	#define _M_P05_FUNC_SEL     (0)
	#define _M_P05_FUNC1_SEL    (0)
	#define _M_P05_GPIO_MODE    (0x1 << GPIO_05)
#else
	#define _M_P05_MODE         (0x0 << GPIO_05)
	#define _M_P05_FUNC_SEL     (0)
	#define _M_P05_FUNC1_SEL    (0)
	#define _M_P05_GPIO_MODE    (0x0 << GPIO_05)
	#if   ((M_CUSTOM_P05_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P05_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_05)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P05_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P05_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_05)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P05_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P05_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_05)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P05_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P05_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_05)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P05_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P05_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_05)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P05_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P05_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_05)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P05_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P05_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_05)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P05_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P05_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_05)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P06_MODE) == (M_CUSTOM_ALT0))
	#define _M_P06_MODE         (0x0 << GPIO_06)
	#define _M_P06_FUNC_SEL     (0)
	#define _M_P06_FUNC1_SEL    (0)
	#define _M_P06_GPIO_MODE    (0x0 << GPIO_06)
#elif ((M_CUSTOM_P06_MODE) == (M_CUSTOM_ALT1))
	#define _M_P06_MODE         (0x1 << GPIO_06)
	#define _M_P06_FUNC_SEL     (0x1 << SEL_I2C0)
	#define _M_P06_FUNC1_SEL    (0)
	#define _M_P06_GPIO_MODE    (0x0 << GPIO_06)
    #define PERI_IO_I2C0        (0)
#elif ((M_CUSTOM_P06_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P06_MODE define NONE!
#elif ((M_CUSTOM_P06_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P06_MODE define NONE!
#elif ((M_CUSTOM_P06_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P06_MODE define NONE!
#elif ((M_CUSTOM_P06_MODE) == (M_CUSTOM_ALT5))
    #error M_CUSTOM_P06_MODE define NONE!
#elif ((M_CUSTOM_P06_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P06_MODE define NONE!
#elif ((M_CUSTOM_P06_MODE) == (M_CUSTOM_ALT7))
	#define _M_P06_MODE         (0x1 << GPIO_06)
	#define _M_P06_FUNC_SEL     (0)
	#define _M_P06_FUNC1_SEL    (0)
	#define _M_P06_GPIO_MODE    (0x1 << GPIO_06)
#else
	#define _M_P06_MODE         (0x0 << GPIO_06)
	#define _M_P06_FUNC_SEL     (0)
	#define _M_P06_FUNC1_SEL    (0)
	#define _M_P06_GPIO_MODE    (0x0 << GPIO_06)
	#if   ((M_CUSTOM_P06_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P06_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_06)
        #define PERI_IO_PWM0    (0)
	#elif   ((M_CUSTOM_P06_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P06_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_06)
        #define PERI_IO_PWM1    (0)
	#elif   ((M_CUSTOM_P06_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P06_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_06)
        #define PERI_IO_PWM2    (0)
	#elif   ((M_CUSTOM_P06_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P06_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_06)
        #define PERI_IO_PWM3    (0)
	#elif   ((M_CUSTOM_P06_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P06_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_06)
        #define PERI_IO_PWM4    (0)
	#elif   ((M_CUSTOM_P06_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P06_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_06)
        #define PERI_IO_PWM5    (0)
	#elif   ((M_CUSTOM_P06_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P06_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_06)
        #define PERI_IO_PWM6    (0)
	#elif   ((M_CUSTOM_P06_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P06_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_06)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P07_MODE) == (M_CUSTOM_ALT0))
	#error M_CUSTOM_P07_MODE define NONE!
#elif ((M_CUSTOM_P07_MODE) == (M_CUSTOM_ALT1))
	#define _M_P07_MODE         (0x1 << GPIO_07)
	#define _M_P07_FUNC_SEL     (0)
	#define _M_P07_FUNC1_SEL    (0x1 << SEL_FLASH)
	#define _M_P07_GPIO_MODE    (0x0 << GPIO_07)
    #define PERI_IO_FLASH
#elif ((M_CUSTOM_P07_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P07_MODE define NONE!
#elif ((M_CUSTOM_P07_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P07_MODE define NONE!
#elif ((M_CUSTOM_P07_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P07_MODE define NONE!
#elif ((M_CUSTOM_P07_MODE) == (M_CUSTOM_ALT5))
    #error M_CUSTOM_P07_MODE define NONE!
#elif ((M_CUSTOM_P07_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P07_MODE define NONE!
#elif ((M_CUSTOM_P07_MODE) == (M_CUSTOM_ALT7))
    #error M_CUSTOM_P07_MODE define NONE!
#endif

#if ((M_CUSTOM_P08_MODE) == (M_CUSTOM_ALT0))
	#error M_CUSTOM_P08_MODE define NONE!
#elif ((M_CUSTOM_P08_MODE) == (M_CUSTOM_ALT1))
	#define _M_P08_MODE         (0x1 << GPIO_08)
	#define _M_P08_FUNC_SEL     (0)
	#define _M_P08_FUNC1_SEL    (0x1 << SEL_FLASH)
	#define _M_P08_GPIO_MODE    (0x0 << GPIO_08)
    #define PERI_IO_FLASH
#elif ((M_CUSTOM_P08_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P08_MODE define NONE!
#elif ((M_CUSTOM_P08_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P08_MODE define NONE!
#elif ((M_CUSTOM_P08_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P08_MODE define NONE!
#elif ((M_CUSTOM_P08_MODE) == (M_CUSTOM_ALT5))
    #error M_CUSTOM_P08_MODE define NONE!
#elif ((M_CUSTOM_P08_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P08_MODE define NONE!
#elif ((M_CUSTOM_P08_MODE) == (M_CUSTOM_ALT7))
    #error M_CUSTOM_P08_MODE define NONE!
#endif

#if ((M_CUSTOM_P09_MODE) == (M_CUSTOM_ALT0))
	#error M_CUSTOM_P09_MODE define NONE!
#elif ((M_CUSTOM_P09_MODE) == (M_CUSTOM_ALT1))
	#define _M_P09_MODE         (0x1 << GPIO_09)
	#define _M_P09_FUNC_SEL     (0)
	#define _M_P09_FUNC1_SEL    (0x1 << SEL_FLASH)
	#define _M_P09_GPIO_MODE    (0x0 << GPIO_09)
    #define PERI_IO_FLASH
#elif ((M_CUSTOM_P09_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P09_MODE define NONE!
#elif ((M_CUSTOM_P09_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P09_MODE define NONE!
#elif ((M_CUSTOM_P09_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P09_MODE define NONE!
#elif ((M_CUSTOM_P09_MODE) == (M_CUSTOM_ALT5))
    #error M_CUSTOM_P09_MODE define NONE!
#elif ((M_CUSTOM_P09_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P09_MODE define NONE!
#elif ((M_CUSTOM_P09_MODE) == (M_CUSTOM_ALT7))
    #error M_CUSTOM_P09_MODE define NONE!
#endif

#if ((M_CUSTOM_P10_MODE) == (M_CUSTOM_ALT0))
	#error M_CUSTOM_P10_MODE define NONE!
#elif ((M_CUSTOM_P10_MODE) == (M_CUSTOM_ALT1))
	#define _M_P10_MODE         (0x1 << GPIO_10)
	#define _M_P10_FUNC_SEL     (0)
	#define _M_P10_FUNC1_SEL    (0x1 << SEL_FLASH)
	#define _M_P10_GPIO_MODE    (0x0 << GPIO_10)
    #define PERI_IO_FLASH
#elif ((M_CUSTOM_P10_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P10_MODE define NONE!
#elif ((M_CUSTOM_P10_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P10_MODE define NONE!
#elif ((M_CUSTOM_P10_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P10_MODE define NONE!
#elif ((M_CUSTOM_P10_MODE) == (M_CUSTOM_ALT5))
    #error M_CUSTOM_P10_MODE define NONE!
#elif ((M_CUSTOM_P10_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P10_MODE define NONE!
#elif ((M_CUSTOM_P10_MODE) == (M_CUSTOM_ALT7))
    #error M_CUSTOM_P10_MODE define NONE!
#endif

#if ((M_CUSTOM_P11_MODE) == (M_CUSTOM_ALT0))
	#error M_CUSTOM_P11_MODE define NONE!
#elif ((M_CUSTOM_P11_MODE) == (M_CUSTOM_ALT1))
	#define _M_P11_MODE         (0x1 << GPIO_11)
	#define _M_P11_FUNC_SEL     (0)
	#define _M_P11_FUNC1_SEL    (0x1 << SEL_FLASH)
	#define _M_P11_GPIO_MODE    (0x0 << GPIO_11)
    #define PERI_IO_FLASH
#elif ((M_CUSTOM_P11_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P11_MODE define NONE!
#elif ((M_CUSTOM_P11_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P11_MODE define NONE!
#elif ((M_CUSTOM_P11_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P11_MODE define NONE!
#elif ((M_CUSTOM_P11_MODE) == (M_CUSTOM_ALT5))
    #error M_CUSTOM_P11_MODE define NONE!
#elif ((M_CUSTOM_P11_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P11_MODE define NONE!
#elif ((M_CUSTOM_P11_MODE) == (M_CUSTOM_ALT7))
    #error M_CUSTOM_P11_MODE define NONE!
#endif

#if ((M_CUSTOM_P12_MODE) == (M_CUSTOM_ALT0))
	#error M_CUSTOM_P12_MODE define NONE!
#elif ((M_CUSTOM_P12_MODE) == (M_CUSTOM_ALT1))
	#define _M_P12_MODE         (0x1 << SIO_12)
	#define _M_P12_FUNC_SEL     (0)
	#define _M_P12_FUNC1_SEL    (0x1 << SEL_FLASH)
	#define _M_P12_GPIO_MODE    (0x0 << SIO_12)
    #define PERI_IO_FLASH
#elif ((M_CUSTOM_P12_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P12_MODE define NONE!
#elif ((M_CUSTOM_P12_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P12_MODE define NONE!
#elif ((M_CUSTOM_P12_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P12_MODE define NONE!
#elif ((M_CUSTOM_P12_MODE) == (M_CUSTOM_ALT5))
    #error M_CUSTOM_P12_MODE define NONE!
#elif ((M_CUSTOM_P12_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P12_MODE define NONE!
#elif ((M_CUSTOM_P12_MODE) == (M_CUSTOM_ALT7))
    #error M_CUSTOM_P12_MODE define NONE!
#endif

#if ((M_CUSTOM_P13_MODE) == (M_CUSTOM_ALT0))
	#define _M_P13_MODE         (0x0 << SIO_13)
	#define _M_P13_FUNC_SEL     (0)
	#define _M_P13_FUNC1_SEL    (0)
	#define _M_P13_GPIO_MODE    (0x0 << SIO_13)
#elif ((M_CUSTOM_P13_MODE) == (M_CUSTOM_ALT1))
    #error M_CUSTOM_P13_MODE define NONE!
#elif ((M_CUSTOM_P13_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P13_MODE define NONE!
#elif ((M_CUSTOM_P13_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P13_MODE define NONE!
#elif ((M_CUSTOM_P13_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P13_MODE define NONE!
#elif ((M_CUSTOM_P13_MODE) == (M_CUSTOM_ALT5))
    #error M_CUSTOM_P13_MODE define NONE!
#elif ((M_CUSTOM_P13_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P13_MODE define NONE!
#elif ((M_CUSTOM_P13_MODE) == (M_CUSTOM_ALT7))
	#define _M_P13_MODE         (0x1 << SIO_13)
	#define _M_P13_FUNC_SEL     (0)
	#define _M_P13_FUNC1_SEL    (0)
	#define _M_P13_GPIO_MODE    (0x1 << SIO_13)
#else
	#define _M_P13_MODE         (0x0 << SIO_13)
	#define _M_P13_FUNC_SEL     (0)
	#define _M_P13_FUNC1_SEL    (0)
	#define _M_P13_GPIO_MODE    (0x0 << SIO_13)
	#if   ((M_CUSTOM_P13_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P13_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (SIO_13)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P13_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P13_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (SIO_13)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P13_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P13_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (SIO_13)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P13_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P13_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (SIO_13)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P13_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P13_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (SIO_13)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P13_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P13_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (SIO_13)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P13_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P13_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (SIO_13)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P13_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P13_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (SIO_13)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P14_MODE) == (M_CUSTOM_ALT0))
	#define _M_P14_MODE         (0x0 << GPIO_14)
	#define _M_P14_FUNC_SEL     (0)
	#define _M_P14_FUNC1_SEL    (0)
	#define _M_P14_GPIO_MODE    (0x0 << GPIO_14)
#elif ((M_CUSTOM_P14_MODE) == (M_CUSTOM_ALT1))
    #error M_CUSTOM_P14_MODE define NONE!
#elif ((M_CUSTOM_P14_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P14_MODE define NONE!
#elif ((M_CUSTOM_P14_MODE) == (M_CUSTOM_ALT3))
    #define _M_P14_MODE         (0x1 << GPIO_14)
    #define _M_P14_FUNC_SEL     (0x1 << SEL_PDMTX0)
    #define _M_P14_FUNC1_SEL    (0)
    #define _M_P14_GPIO_MODE    (0x0 << GPIO_14)
    #define PERI_IO_PDMTX0
#elif ((M_CUSTOM_P14_MODE) == (M_CUSTOM_ALT4))
    #define _M_P14_MODE         (0x1 << GPIO_14)
    #define _M_P14_FUNC_SEL     (0x1 << SEL_PDMRX0)
    #define _M_P14_FUNC1_SEL    (0)
    #define _M_P14_GPIO_MODE    (0x0 << GPIO_14)
    #define PERI_IO_PDMRX0
#elif ((M_CUSTOM_P14_MODE) == (M_CUSTOM_ALT5))
    #define _M_P14_MODE         (0x1 << GPIO_14)
    #define _M_P14_FUNC_SEL     (0)
    #define _M_P14_FUNC1_SEL    (0x1 << SEL_I2S0)
    #define _M_P14_GPIO_MODE    (0x0 << GPIO_14)
    #define PERI_IO_I2S0        (0)
#elif ((M_CUSTOM_P14_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P14_MODE define NONE!
#elif ((M_CUSTOM_P14_MODE) == (M_CUSTOM_ALT7))
	#define _M_P14_MODE         (0x1 << GPIO_14)
	#define _M_P14_FUNC_SEL     (0)
	#define _M_P14_FUNC1_SEL    (0)
	#define _M_P14_GPIO_MODE    (0x1 << GPIO_14)
#else
	#define _M_P14_MODE         (0x0 << GPIO_14)
	#define _M_P14_FUNC_SEL     (0)
	#define _M_P14_FUNC1_SEL    (0)
	#define _M_P14_GPIO_MODE    (0x0 << GPIO_14)
	#if   ((M_CUSTOM_P14_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P14_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_14)
        #define PERI_IO_PWM0    (0)
	#elif   ((M_CUSTOM_P14_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P14_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_14)
        #define PERI_IO_PWM1    (0)
	#elif   ((M_CUSTOM_P14_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P14_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_14)
        #define PERI_IO_PWM2    (0)
	#elif   ((M_CUSTOM_P14_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P14_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_14)
        #define PERI_IO_PWM3    (0)
	#elif   ((M_CUSTOM_P14_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P14_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_14)
        #define PERI_IO_PWM4    (0)
	#elif   ((M_CUSTOM_P14_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P14_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_14)
        #define PERI_IO_PWM5    (0)
	#elif   ((M_CUSTOM_P14_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P14_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_14)
        #define PERI_IO_PWM6    (0)
	#elif   ((M_CUSTOM_P14_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P14_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_14)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P15_MODE) == (M_CUSTOM_ALT0))
	#define _M_P15_MODE         (0x0 << GPIO_15)
	#define _M_P15_FUNC_SEL     (0)
	#define _M_P15_FUNC1_SEL    (0)
	#define _M_P15_GPIO_MODE    (0x0 << GPIO_15)
#elif ((M_CUSTOM_P15_MODE) == (M_CUSTOM_ALT1))
    #error M_CUSTOM_P15_MODE define NONE!
#elif ((M_CUSTOM_P15_MODE) == (M_CUSTOM_ALT2))
	#error M_CUSTOM_P15_MODE define NONE!
#elif ((M_CUSTOM_P15_MODE) == (M_CUSTOM_ALT3))
    #define _M_P15_MODE         (0x1 << GPIO_15)
	#define _M_P15_FUNC_SEL     (0x1 << SEL_PDMTX0)
	#define _M_P15_FUNC1_SEL    (0)
	#define _M_P15_GPIO_MODE    (0x0 << GPIO_15)
    #define PERI_IO_PDMTX0
#elif ((M_CUSTOM_P15_MODE) == (M_CUSTOM_ALT4))
	#define _M_P15_MODE         (0x1 << GPIO_15)
	#define _M_P15_FUNC_SEL     (0x1 << SEL_PDMRX0)
	#define _M_P15_FUNC1_SEL    (0)
	#define _M_P15_GPIO_MODE    (0x0 << GPIO_15)
    #define PERI_IO_PDMRX0
#elif ((M_CUSTOM_P15_MODE) == (M_CUSTOM_ALT5))
	#define _M_P15_MODE         (0x1 << GPIO_15)
	#define _M_P15_FUNC_SEL     (0)
	#define _M_P15_FUNC1_SEL    (0x1 << SEL_I2S0)
	#define _M_P15_GPIO_MODE    (0x0 << GPIO_15)
    #define PERI_IO_I2S0        (0)
#elif ((M_CUSTOM_P15_MODE) == (M_CUSTOM_ALT6))
	#error M_CUSTOM_P15_MODE define NONE!
#elif ((M_CUSTOM_P15_MODE) == (M_CUSTOM_ALT7))
    #define _M_P15_MODE         (0x1 << GPIO_15)
	#define _M_P15_FUNC_SEL     (0)
	#define _M_P15_FUNC1_SEL    (0)
	#define _M_P15_GPIO_MODE    (0x1 << GPIO_15)
#else
	#define _M_P15_MODE         (0x0 << GPIO_15)
	#define _M_P15_FUNC_SEL     (0)
	#define _M_P15_FUNC1_SEL    (0)
	#define _M_P15_GPIO_MODE    (0x0 << GPIO_15)
	#if   ((M_CUSTOM_P15_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P15_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_15)
        #define PERI_IO_PWM0    (0)
	#elif   ((M_CUSTOM_P15_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P15_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_15)
        #define PERI_IO_PWM1    (0)
	#elif   ((M_CUSTOM_P15_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P15_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_15)
        #define PERI_IO_PWM2    (0)
	#elif   ((M_CUSTOM_P15_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P15_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_15)
        #define PERI_IO_PWM3    (0)
	#elif   ((M_CUSTOM_P15_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P15_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_15)
        #define PERI_IO_PWM4    (0)
	#elif   ((M_CUSTOM_P15_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P15_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_15)
        #define PERI_IO_PWM5    (0)
	#elif   ((M_CUSTOM_P15_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P15_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_15)
        #define PERI_IO_PWM6    (0)
	#elif   ((M_CUSTOM_P15_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P15_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_15)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P16_MODE) == (M_CUSTOM_ALT0))
	#define _M_P16_MODE         (0x0 << GPIO_16)
	#define _M_P16_FUNC_SEL     (0)
	#define _M_P16_FUNC1_SEL    (0)
	#define _M_P16_GPIO_MODE    (0x0 << GPIO_16)
#elif ((M_CUSTOM_P16_MODE) == (M_CUSTOM_ALT1))
	#error M_CUSTOM_P16_MODE define NONE!
#elif ((M_CUSTOM_P16_MODE) == (M_CUSTOM_ALT2))
	#error M_CUSTOM_P16_MODE define NONE!
#elif ((M_CUSTOM_P16_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P16_MODE define NONE!
#elif ((M_CUSTOM_P16_MODE) == (M_CUSTOM_ALT4))
	#define _M_P16_MODE         (0x1 << GPIO_16)
	#define _M_P16_FUNC_SEL     (0)
	#define _M_P16_FUNC1_SEL    (0x1 << SEL_PDMRX1)
	#define _M_P16_GPIO_MODE    (0x0 << GPIO_16)
    #define PERI_IO_PDMRX1      (0)
#elif ((M_CUSTOM_P16_MODE) == (M_CUSTOM_ALT5))
	#define _M_P16_MODE         (0x1 << GPIO_16)
	#define _M_P16_FUNC_SEL     (0)
	#define _M_P16_FUNC1_SEL    (0x1 << SEL_I2S0)
	#define _M_P16_GPIO_MODE    (0x0 << GPIO_16)
    #define PERI_IO_I2S0        (0)
#elif ((M_CUSTOM_P16_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P16_MODE define NONE!
#elif ((M_CUSTOM_P16_MODE) == (M_CUSTOM_ALT7))
	#define _M_P16_MODE         (0x1 << GPIO_16)
	#define _M_P16_FUNC_SEL     (0)
	#define _M_P16_FUNC1_SEL    (0)
	#define _M_P16_GPIO_MODE    (0x1 << GPIO_16)
#else
	#define _M_P16_MODE         (0x0 << GPIO_16)
	#define _M_P16_FUNC_SEL     (0)
	#define _M_P16_FUNC1_SEL    (0)
	#define _M_P16_GPIO_MODE    (0x0 << GPIO_16)
	#if   ((M_CUSTOM_P16_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P16_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_16)
        #define PERI_IO_PWM0    (0)
	#elif   ((M_CUSTOM_P16_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P16_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_16)
        #define PERI_IO_PWM1    (0)
	#elif   ((M_CUSTOM_P16_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P16_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_16)
        #define PERI_IO_PWM2    (0)
	#elif   ((M_CUSTOM_P16_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P16_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_16)
        #define PERI_IO_PWM3    (0)
	#elif   ((M_CUSTOM_P16_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P16_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_16)
        #define PERI_IO_PWM4    (0)
	#elif   ((M_CUSTOM_P16_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P16_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_16)
        #define PERI_IO_PWM5    (0)
	#elif   ((M_CUSTOM_P16_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P16_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_16)
        #define PERI_IO_PWM6    (0)
	#elif   ((M_CUSTOM_P16_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P16_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_16)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P17_MODE) == (M_CUSTOM_ALT0))
	#define _M_P17_MODE         (0x0 << GPIO_17)
	#define _M_P17_FUNC_SEL     (0)
	#define _M_P17_FUNC1_SEL    (0)
	#define _M_P17_GPIO_MODE    (0x0 << GPIO_17)
#elif ((M_CUSTOM_P17_MODE) == (M_CUSTOM_ALT1))
	#define _M_P17_MODE         (0x0 << GPIO_17)
	#define _M_P17_FUNC_SEL     (0)
	#define _M_P17_FUNC1_SEL    (0x1 << SEL_SDIO_IOT)
	#define _M_P17_GPIO_MODE    (0x0 << GPIO_17)
    #define PERI_IO_SDIO
#elif ((M_CUSTOM_P17_MODE) == (M_CUSTOM_ALT2))
    #define _M_P17_MODE         (0x1 << GPIO_17)
	#define _M_P17_FUNC_SEL     (0x1 << SEL_UART2_RTSCTS)
	#define _M_P17_FUNC1_SEL    (0)
	#define _M_P17_GPIO_MODE    (0x0 << GPIO_17)
    #define PERI_IO_UART2       (0)
#elif ((M_CUSTOM_P17_MODE) == (M_CUSTOM_ALT3))
	#error M_CUSTOM_P17_MODE define NONE!
#elif ((M_CUSTOM_P17_MODE) == (M_CUSTOM_ALT4))
    #define _M_P17_MODE         (0x1 << GPIO_17)
	#define _M_P17_FUNC_SEL     (0x1 << SEL_PDMRX1)
	#define _M_P17_FUNC1_SEL    (0)
	#define _M_P17_GPIO_MODE    (0x0 << GPIO_17)
    #define PERI_IO_PDMRX1      (0)
#elif ((M_CUSTOM_P17_MODE) == (M_CUSTOM_ALT5))
	#define _M_P17_MODE         (0x1 << GPIO_17)
	#define _M_P17_FUNC_SEL     (0)
	#define _M_P17_FUNC1_SEL    (0x1 << SEL_I2S0)
	#define _M_P17_GPIO_MODE    (0x0 << GPIO_17)
    #define PERI_IO_I2S0        (0)
#elif ((M_CUSTOM_P17_MODE) == (M_CUSTOM_ALT6))
	#error M_CUSTOM_P17_MODE define NONE!
#elif ((M_CUSTOM_P17_MODE) == (M_CUSTOM_ALT7))
    #define _M_P17_MODE         (0x1 << GPIO_17)
	#define _M_P17_FUNC_SEL     (0)
	#define _M_P17_FUNC1_SEL    (0)
	#define _M_P17_GPIO_MODE    (0x1 << GPIO_17)
#else
	#define _M_P17_MODE         (0x0 << GPIO_17)
	#define _M_P17_FUNC_SEL     (0)
	#define _M_P17_FUNC1_SEL    (0)
	#define _M_P17_GPIO_MODE    (0x0 << GPIO_17)
	#if   ((M_CUSTOM_P17_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P17_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_17)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P17_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P17_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_17)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P17_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P17_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_17)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P17_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P17_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_17)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P17_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P17_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_17)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P17_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P17_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_17)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P17_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P17_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_17)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P17_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P17_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_17)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P18_MODE) == (M_CUSTOM_ALT0))
	#define _M_P18_MODE         (0x0 << GPIO_18)
	#define _M_P18_FUNC_SEL     (0)
	#define _M_P18_FUNC1_SEL    (0)
	#define _M_P18_GPIO_MODE    (0x0 << GPIO_18)
#elif ((M_CUSTOM_P18_MODE) == (M_CUSTOM_ALT1))
	#define _M_P18_MODE         (0x0 << GPIO_18)
	#define _M_P18_FUNC_SEL     (0)
	#define _M_P18_FUNC1_SEL    (0x1 << SEL_SDIO_IOT)
	#define _M_P18_GPIO_MODE    (0x0 << GPIO_18)
    #define PERI_IO_SDIO
#elif ((M_CUSTOM_P18_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P18_MODE define NONE!
#elif ((M_CUSTOM_P18_MODE) == (M_CUSTOM_ALT3))
	#define _M_P18_MODE         (0x0 << GPIO_18)
	#define _M_P18_FUNC_SEL     (0)
	#define _M_P18_FUNC1_SEL    (0x1 << SEL_SPIDATA_IOT)
	#define _M_P18_GPIO_MODE    (0x0 << GPIO_18)
    #define PERI_IO_SPIDATA
#elif ((M_CUSTOM_P18_MODE) == (M_CUSTOM_ALT4))
    #define _M_P18_MODE         (0x1 << GPIO_18)
	#define _M_P18_FUNC_SEL     (0)
	#define _M_P18_FUNC1_SEL    (0x1 << SEL_SPISLV1)
	#define _M_P18_GPIO_MODE    (0x0 << GPIO_18)
    #define PERI_IO_SPIS1       (0)
#elif ((M_CUSTOM_P18_MODE) == (M_CUSTOM_ALT5))
	#define _M_P18_MODE         (0x1 << GPIO_18)
	#define _M_P18_FUNC_SEL     (0)
	#define _M_P18_FUNC1_SEL    (0x1 << SEL_SPIMAS1)
	#define _M_P18_GPIO_MODE    (0x0 << GPIO_18)
    #define PERI_IO_SPIM1       (0)
#elif ((M_CUSTOM_P18_MODE) == (M_CUSTOM_ALT6))
	#error M_CUSTOM_P18_MODE define NONE!
#elif ((M_CUSTOM_P18_MODE) == (M_CUSTOM_ALT7))
    #define _M_P18_MODE         (0x1 << GPIO_18)
	#define _M_P18_FUNC_SEL     (0)
	#define _M_P18_FUNC1_SEL    (0)
	#define _M_P18_GPIO_MODE    (0x1 << GPIO_18)
#else
	#define _M_P18_MODE         (0x0 << GPIO_18)
	#define _M_P18_FUNC_SEL     (0)
	#define _M_P18_FUNC1_SEL    (0)
	#define _M_P18_GPIO_MODE    (0x0 << GPIO_18)
	#if   ((M_CUSTOM_P18_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P18_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_18)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P18_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P18_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_18)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P18_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P18_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_18)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P18_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P18_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_18)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P18_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P18_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_18)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P18_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P18_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_18)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P18_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P18_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_18)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P18_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P18_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_18)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P19_MODE) == (M_CUSTOM_ALT0))
	#define _M_P19_MODE         (0x0 << GPIO_19)
	#define _M_P19_FUNC_SEL     (0)
	#define _M_P19_FUNC1_SEL    (0)
	#define _M_P19_GPIO_MODE    (0x0 << GPIO_19)
#elif ((M_CUSTOM_P19_MODE) == (M_CUSTOM_ALT1))
	#define _M_P19_MODE         (0x0 << GPIO_19)
	#define _M_P19_FUNC_SEL     (0)
	#define _M_P19_FUNC1_SEL    (0x1 << SEL_SDIO_IOT)
	#define _M_P19_GPIO_MODE    (0x0 << GPIO_19)
    #define PERI_IO_SDIO
#elif ((M_CUSTOM_P19_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P19_MODE define NONE!
#elif ((M_CUSTOM_P19_MODE) == (M_CUSTOM_ALT3))
    #define _M_P19_MODE         (0x0 << GPIO_19)
	#define _M_P19_FUNC_SEL     (0)
	#define _M_P19_FUNC1_SEL    (0x1 << SEL_SPIDATA_IOT)
	#define _M_P19_GPIO_MODE    (0x0 << GPIO_19)
    #define PERI_IO_SPIDATA
#elif ((M_CUSTOM_P19_MODE) == (M_CUSTOM_ALT4))
    #define _M_P19_MODE         (0x1 << GPIO_19)
	#define _M_P19_FUNC_SEL     (0)
	#define _M_P19_FUNC1_SEL    (0x1 << SEL_SPISLV1)
	#define _M_P19_GPIO_MODE    (0x0 << GPIO_19)
    #define PERI_IO_SPIS1       (0)
#elif ((M_CUSTOM_P19_MODE) == (M_CUSTOM_ALT5))
	#define _M_P19_MODE         (0x1 << GPIO_19)
	#define _M_P19_FUNC_SEL     (0)
	#define _M_P19_FUNC1_SEL    (0x1 << SEL_SPIMAS1)
	#define _M_P19_GPIO_MODE    (0x0 << GPIO_19)
    #define PERI_IO_SPIM1       (0)
#elif ((M_CUSTOM_P19_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P19_MODE define NONE!
#elif ((M_CUSTOM_P19_MODE) == (M_CUSTOM_ALT7))
    #define _M_P19_MODE         (0x1 << GPIO_19)
	#define _M_P19_FUNC_SEL     (0)
	#define _M_P19_FUNC1_SEL    (0)
	#define _M_P19_GPIO_MODE    (0x1 << GPIO_19)
#else
	#define _M_P19_MODE         (0x0 << GPIO_19)
	#define _M_P19_FUNC_SEL     (0)
	#define _M_P19_FUNC1_SEL    (0)
	#define _M_P19_GPIO_MODE    (0x0 << GPIO_19)
	#if   ((M_CUSTOM_P19_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P19_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_19)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P19_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P19_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_19)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P19_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P19_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_19)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P19_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P19_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_19)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P19_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P19_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_19)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P19_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P19_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_19)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P19_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P19_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_19)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P19_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P19_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_19)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P20_MODE) == (M_CUSTOM_ALT0))
	#define _M_P20_MODE         (0x0 << GPIO_20)
	#define _M_P20_FUNC_SEL     (0)
	#define _M_P20_FUNC1_SEL    (0)
	#define _M_P20_GPIO_MODE    (0x0 << GPIO_20)
#elif ((M_CUSTOM_P20_MODE) == (M_CUSTOM_ALT1))
	#define _M_P20_MODE         (0x0 << GPIO_20)
	#define _M_P20_FUNC_SEL     (0)
	#define _M_P20_FUNC1_SEL    (0x1 << SEL_SDIO_IOT)
	#define _M_P20_GPIO_MODE    (0x0 << GPIO_20)
    #define PERI_IO_SDIO
#elif ((M_CUSTOM_P20_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P20_MODE define NONE!
#elif ((M_CUSTOM_P20_MODE) == (M_CUSTOM_ALT3))
    #define _M_P20_MODE         (0x0 << GPIO_20)
	#define _M_P20_FUNC_SEL     (0)
	#define _M_P20_FUNC1_SEL    (0x1 << SEL_SPIDATA_IOT)
	#define _M_P20_GPIO_MODE    (0x0 << GPIO_20)
    #define PERI_IO_SPIDATA
#elif ((M_CUSTOM_P20_MODE) == (M_CUSTOM_ALT4))
    #define _M_P20_MODE         (0x1 << GPIO_20)
	#define _M_P20_FUNC_SEL     (0)
	#define _M_P20_FUNC1_SEL    (0x1 << SEL_SPISLV1)
	#define _M_P20_GPIO_MODE    (0x0 << GPIO_20)
    #define PERI_IO_SPIS1       (0)
#elif ((M_CUSTOM_P20_MODE) == (M_CUSTOM_ALT5))
	#define _M_P20_MODE         (0x1 << GPIO_20)
	#define _M_P20_FUNC_SEL     (0)
	#define _M_P20_FUNC1_SEL    (0x1 << SEL_SPIMAS1)
	#define _M_P20_GPIO_MODE    (0x0 << GPIO_20)
    #define PERI_IO_SPIM1       (0)
#elif ((M_CUSTOM_P20_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P20_MODE define NONE!
#elif ((M_CUSTOM_P20_MODE) == (M_CUSTOM_ALT7))
    #define _M_P20_MODE         (0x1 << GPIO_20)
	#define _M_P20_FUNC_SEL     (0)
	#define _M_P20_FUNC1_SEL    (0)
	#define _M_P20_GPIO_MODE    (0x1 << GPIO_20)
#else
	#define _M_P20_MODE         (0x0 << GPIO_20)
	#define _M_P20_FUNC_SEL     (0)
	#define _M_P20_FUNC1_SEL    (0)
	#define _M_P20_GPIO_MODE    (0x0 << GPIO_20)
	#if   ((M_CUSTOM_P20_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P20_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_20)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P20_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P20_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_20)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P20_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P20_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_20)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P20_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P20_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_20)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P20_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P20_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_20)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P20_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P20_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_20)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P20_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P20_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_20)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P20_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P20_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_20)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P21_MODE) == (M_CUSTOM_ALT0))
	#define _M_P21_MODE         (0x0 << GPIO_21)
	#define _M_P21_FUNC_SEL     (0)
	#define _M_P21_FUNC1_SEL    (0)
	#define _M_P21_GPIO_MODE    (0x0 << GPIO_21)
#elif ((M_CUSTOM_P21_MODE) == (M_CUSTOM_ALT1))
	#define _M_P21_MODE         (0x0 << GPIO_21)
	#define _M_P21_FUNC_SEL     (0)
	#define _M_P21_FUNC1_SEL    (0x1 << SEL_SDIO_IOT)
	#define _M_P21_GPIO_MODE    (0x0 << GPIO_21)
    #define PERI_IO_SDIO
#elif ((M_CUSTOM_P21_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P21_MODE define NONE!
#elif ((M_CUSTOM_P21_MODE) == (M_CUSTOM_ALT3))
    #define _M_P21_MODE         (0x0 << GPIO_21)
	#define _M_P21_FUNC_SEL     (0)
	#define _M_P21_FUNC1_SEL    (0x1 << SEL_SPIDATA_IOT)
	#define _M_P21_GPIO_MODE    (0x0 << GPIO_21)
    #define PERI_IO_SPIDATA
#elif ((M_CUSTOM_P21_MODE) == (M_CUSTOM_ALT4))
    #define _M_P21_MODE         (0x1 << GPIO_21)
	#define _M_P21_FUNC_SEL     (0)
	#define _M_P21_FUNC1_SEL    (0x1 << SEL_SPISLV1)
	#define _M_P21_GPIO_MODE    (0x0 << GPIO_21)
    #define PERI_IO_SPIS1       (0)
#elif ((M_CUSTOM_P21_MODE) == (M_CUSTOM_ALT5))
	#define _M_P21_MODE         (0x1 << GPIO_21)
	#define _M_P21_FUNC_SEL     (0)
	#define _M_P21_FUNC1_SEL    (0x1 << SEL_SPIMAS1)
	#define _M_P21_GPIO_MODE    (0x0 << GPIO_21)
    #define PERI_IO_SPIM1       (0)
#elif ((M_CUSTOM_P21_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P21_MODE define NONE!
#elif ((M_CUSTOM_P21_MODE) == (M_CUSTOM_ALT7))
    #define _M_P21_MODE         (0x1 << GPIO_21)
	#define _M_P21_FUNC_SEL     (0)
	#define _M_P21_FUNC1_SEL    (0)
	#define _M_P21_GPIO_MODE    (0x1 << GPIO_21)
#else
	#define _M_P21_MODE         (0x0 << GPIO_21)
	#define _M_P21_FUNC_SEL     (0)
	#define _M_P21_FUNC1_SEL    (0)
	#define _M_P21_GPIO_MODE    (0x0 << GPIO_21)
	#if   ((M_CUSTOM_P21_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P21_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_21)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P21_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P21_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_21)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P21_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P21_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_21)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P21_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P21_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_21)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P21_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P21_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_21)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P21_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P21_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_21)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P21_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P21_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_21)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P21_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P21_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_21)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P22_MODE) == (M_CUSTOM_ALT0))
	#define _M_P22_MODE         (0x0 << GPIO_22)
	#define _M_P22_FUNC_SEL     (0)
	#define _M_P22_FUNC1_SEL    (0)
	#define _M_P22_GPIO_MODE    (0x0 << GPIO_22)
#elif ((M_CUSTOM_P22_MODE) == (M_CUSTOM_ALT1))
	#define _M_P22_MODE         (0x0 << GPIO_22)
	#define _M_P22_FUNC_SEL     (0)
	#define _M_P22_FUNC1_SEL    (0x1 << SEL_SDIO_IOT)
	#define _M_P22_GPIO_MODE    (0x0 << GPIO_22)
    #define PERI_IO_SDIO
#elif ((M_CUSTOM_P22_MODE) == (M_CUSTOM_ALT2))
	#define _M_P22_MODE         (0x1 << GPIO_22)
	#define _M_P22_FUNC_SEL     (0x1 << SEL_UART2_RTSCTS)
	#define _M_P22_FUNC1_SEL    (0)
	#define _M_P22_GPIO_MODE    (0x0 << GPIO_22)
    #define PERI_IO_UART2       (0)
#elif ((M_CUSTOM_P22_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P22_MODE define NONE!
#elif ((M_CUSTOM_P22_MODE) == (M_CUSTOM_ALT4))
    #define _M_P22_MODE         (0x1 << GPIO_22)
	#define _M_P22_FUNC_SEL     (0)
	#define _M_P22_FUNC1_SEL    (0x1 << SEL_I2S0_MCLK_III)
	#define _M_P22_GPIO_MODE    (0x0 << GPIO_22)
    #define PERI_IO_I2S0        (0)
#elif ((M_CUSTOM_P22_MODE) == (M_CUSTOM_ALT5))
	#error M_CUSTOM_P22_MODE define NONE!
#elif ((M_CUSTOM_P22_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P22_MODE define NONE!
#elif ((M_CUSTOM_P22_MODE) == (M_CUSTOM_ALT7))
    #define _M_P22_MODE         (0x1 << GPIO_22)
	#define _M_P22_FUNC_SEL     (0)
	#define _M_P22_FUNC1_SEL    (0)
	#define _M_P22_GPIO_MODE    (0x1 << GPIO_22)
#else
	#define _M_P22_MODE         (0x0 << GPIO_22)
	#define _M_P22_FUNC_SEL     (0)
	#define _M_P22_FUNC1_SEL    (0)
	#define _M_P22_GPIO_MODE    (0x0 << GPIO_22)
	#if   ((M_CUSTOM_P22_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P22_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_22)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P22_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P22_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_22)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P22_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P22_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_22)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P22_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P22_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_22)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P22_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P22_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_22)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P22_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P22_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_22)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P22_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P22_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_22)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P22_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P22_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_22)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P23_MODE) == (M_CUSTOM_ALT0))
	#define _M_P23_MODE         (0x0 << GPIO_23)
	#define _M_P23_FUNC_SEL     (0)
	#define _M_P23_FUNC1_SEL    (0)
	#define _M_P23_GPIO_MODE    (0x0 << GPIO_23)
#elif ((M_CUSTOM_P23_MODE) == (M_CUSTOM_ALT1))
	#error M_CUSTOM_P23_MODE define NONE!
#elif ((M_CUSTOM_P23_MODE) == (M_CUSTOM_ALT2))
	#define _M_P23_MODE         (0x1 << GPIO_23)
	#define _M_P23_FUNC_SEL     (0x1 << SEL_UART2)
	#define _M_P23_FUNC1_SEL    (0)
	#define _M_P23_GPIO_MODE    (0x0 << GPIO_23)
    #define PERI_IO_UART2       (0)
#elif ((M_CUSTOM_P23_MODE) == (M_CUSTOM_ALT3))
	#define _M_P23_MODE         (0x1 << GPIO_23)
	#define _M_P23_FUNC_SEL     (0x1 << SEL_I2C1)
	#define _M_P23_FUNC1_SEL    (0)
	#define _M_P23_GPIO_MODE    (0x0 << GPIO_23)
    #define PERI_IO_I2C1        (0)
#elif ((M_CUSTOM_P23_MODE) == (M_CUSTOM_ALT4))
	#error M_CUSTOM_P23_MODE define NONE!
#elif ((M_CUSTOM_P23_MODE) == (M_CUSTOM_ALT5))
    #error M_CUSTOM_P23_MODE define NONE!
#elif ((M_CUSTOM_P23_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P23_MODE define NONE!
#elif ((M_CUSTOM_P23_MODE) == (M_CUSTOM_ALT7))
	#define _M_P23_MODE         (0x1 << GPIO_23)
	#define _M_P23_FUNC_SEL     (0)
	#define _M_P23_FUNC1_SEL    (0)
	#define _M_P23_GPIO_MODE    (0x1 << GPIO_23)
#else
	#define _M_P23_MODE         (0x0 << GPIO_23)
	#define _M_P23_FUNC_SEL     (0)
	#define _M_P23_FUNC1_SEL    (0)
	#define _M_P23_GPIO_MODE    (0x0 << GPIO_23)
	#if   ((M_CUSTOM_P23_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P23_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_23)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P23_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P23_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_23)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P23_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P23_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_23)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P23_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P23_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_23)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P23_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P23_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_23)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P23_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P23_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_23)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P23_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P23_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_23)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P23_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P23_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_23)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P24_MODE) == (M_CUSTOM_ALT0))
	#define _M_P24_MODE         (0x0 << GPIO_24)
	#define _M_P24_FUNC_SEL     (0)
	#define _M_P24_FUNC1_SEL    (0)
	#define _M_P24_GPIO_MODE    (0x0 << GPIO_24)
#elif ((M_CUSTOM_P24_MODE) == (M_CUSTOM_ALT1))
	#error M_CUSTOM_P24_MODE define NONE!
#elif ((M_CUSTOM_P24_MODE) == (M_CUSTOM_ALT2))
	#define _M_P24_MODE         (0x1 << GPIO_24)
	#define _M_P24_FUNC_SEL     (0x1 << SEL_UART2)
	#define _M_P24_FUNC1_SEL    (0)
	#define _M_P24_GPIO_MODE    (0x0 << GPIO_24)
    #define PERI_IO_UART2       (0)
#elif ((M_CUSTOM_P24_MODE) == (M_CUSTOM_ALT3))
    #define _M_P24_MODE         (0x1 << GPIO_24)
	#define _M_P24_FUNC_SEL     (0x1 << SEL_I2C1)
	#define _M_P24_FUNC1_SEL    (0)
	#define _M_P24_GPIO_MODE    (0x0 << GPIO_24)
    #define PERI_IO_I2C1        (0)
#elif ((M_CUSTOM_P24_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P24_MODE define NONE!
#elif ((M_CUSTOM_P24_MODE) == (M_CUSTOM_ALT5))
    #error M_CUSTOM_P24_MODE define NONE!
#elif ((M_CUSTOM_P24_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P24_MODE define NONE!
#elif ((M_CUSTOM_P24_MODE) == (M_CUSTOM_ALT7))
    #define _M_P24_MODE         (0x1 << GPIO_24)
	#define _M_P24_FUNC_SEL     (0)
	#define _M_P24_FUNC1_SEL    (0)
	#define _M_P24_GPIO_MODE    (0x1 << GPIO_24)
#else
	#define _M_P24_MODE         (0x0 << GPIO_24)
	#define _M_P24_FUNC_SEL     (0)
	#define _M_P24_FUNC1_SEL    (0)
	#define _M_P24_GPIO_MODE    (0x0 << GPIO_24)
	#if   ((M_CUSTOM_P24_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P24_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_24)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P24_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P24_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_24)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P24_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P24_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_24)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P24_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P24_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_24)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P24_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P24_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_24)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P24_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P24_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_24)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P24_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P24_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_24)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P24_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P24_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_24)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P25_MODE) == (M_CUSTOM_ALT0))
	#define _M_P25_MODE         (0x0 << GPIO_25)
	#define _M_P25_FUNC_SEL     (0)
	#define _M_P25_FUNC1_SEL    (0)
	#define _M_P25_GPIO_MODE    (0x0 << GPIO_25)
#elif ((M_CUSTOM_P25_MODE) == (M_CUSTOM_ALT1))
	#define _M_P25_MODE         (0x1 << GPIO_25)
	#define _M_P25_FUNC_SEL     (0x1 << SEL_BTCX)
	#define _M_P25_FUNC1_SEL    (0)
	#define _M_P25_GPIO_MODE    (0x0 << GPIO_25)
    #define PERI_IO_BTCX
#elif ((M_CUSTOM_P25_MODE) == (M_CUSTOM_ALT2))
	#error M_CUSTOM_P25_MODE define NONE!
#elif ((M_CUSTOM_P25_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P25_MODE define NONE!
#elif ((M_CUSTOM_P25_MODE) == (M_CUSTOM_ALT4))
    #define _M_P25_MODE         (0x1 << GPIO_25)
	#define _M_P25_FUNC_SEL     (0x1 << SEL_UART2_II)
	#define _M_P25_FUNC1_SEL    (0)
	#define _M_P25_GPIO_MODE    (0x0 << GPIO_25)
    #define PERI_IO_UART2       (0)
#elif ((M_CUSTOM_P25_MODE) == (M_CUSTOM_ALT5))
    #error M_CUSTOM_P25_MODE define NONE!
#elif ((M_CUSTOM_P25_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P25_MODE define NONE!
#elif ((M_CUSTOM_P25_MODE) == (M_CUSTOM_ALT7))
    #define _M_P25_MODE         (0x1 << GPIO_25)
	#define _M_P25_FUNC_SEL     (0)
	#define _M_P25_FUNC1_SEL    (0)
	#define _M_P25_GPIO_MODE    (0x1 << GPIO_25)
#else
	#define _M_P25_MODE         (0x0 << GPIO_25)
	#define _M_P25_FUNC_SEL     (0)
	#define _M_P25_FUNC1_SEL    (0)
	#define _M_P25_GPIO_MODE    (0x0 << GPIO_25)
	#if   ((M_CUSTOM_P25_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P25_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_25)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P25_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P25_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_25)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P25_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P25_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_25)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P25_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P25_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_25)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P25_MODE) == (M_CUSTOM_PWM4))
	#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P25_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_25)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P25_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P25_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_25)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P25_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P25_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_25)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P25_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P25_MODE define PWM7 collision to other pin.
		#endif
	#define M_CUSTOM_PWM7_PIN           (GPIO_25)
    #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P26_MODE) == (M_CUSTOM_ALT0))
	#define _M_P26_MODE         (0x0 << GPIO_26)
	#define _M_P26_FUNC_SEL     (0)
	#define _M_P26_FUNC1_SEL    (0)
	#define _M_P26_GPIO_MODE    (0x0 << GPIO_26)
#elif ((M_CUSTOM_P26_MODE) == (M_CUSTOM_ALT1))
    #define _M_P26_MODE         (0x1 << GPIO_26)
	#define _M_P26_FUNC_SEL     (0x1 << SEL_BTCX)
	#define _M_P26_FUNC1_SEL    (0)
	#define _M_P26_GPIO_MODE    (0x0 << GPIO_26)
    #define PERI_IO_BTCX
#elif ((M_CUSTOM_P26_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P26_MODE define NONE!
#elif ((M_CUSTOM_P26_MODE) == (M_CUSTOM_ALT3))
	#define _M_P26_MODE         (0x1 << GPIO_26)
	#define _M_P26_FUNC_SEL     (0)
	#define _M_P26_FUNC1_SEL    (0x1 << SEL_I2S0_MCLK_II)
	#define _M_P26_GPIO_MODE    (0x0 << GPIO_26)
    #define PERI_IO_I2S0        (0)
#elif ((M_CUSTOM_P26_MODE) == (M_CUSTOM_ALT4))
    #define _M_P26_MODE         (0x1 << GPIO_26)
	#define _M_P26_FUNC_SEL     (0x1 << SEL_UART2_II)
	#define _M_P26_FUNC1_SEL    (0)
	#define _M_P26_GPIO_MODE    (0x0 << GPIO_26)
    #define PERI_IO_UART2       (0)
#elif ((M_CUSTOM_P26_MODE) == (M_CUSTOM_ALT5))
    #define _M_P26_MODE         (0x1 << GPIO_26)
	#define _M_P26_FUNC_SEL     (0)
	#define _M_P26_FUNC1_SEL    (0x1 << SEL_SPIMAS2_CSN_II)
	#define _M_P26_GPIO_MODE    (0x0 << GPIO_26)
    #define PERI_IO_SPIM2       (0)
#elif ((M_CUSTOM_P26_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P26_MODE define NONE!
#elif ((M_CUSTOM_P26_MODE) == (M_CUSTOM_ALT7))
    #define _M_P26_MODE         (0x1 << GPIO_26)
	#define _M_P26_FUNC_SEL     (0)
	#define _M_P26_FUNC1_SEL    (0)
	#define _M_P26_GPIO_MODE    (0x1 << GPIO_26)
#else
	#define _M_P26_MODE         (0x0 << GPIO_26)
	#define _M_P26_FUNC_SEL     (0)
	#define _M_P26_FUNC1_SEL    (0)
	#define _M_P26_GPIO_MODE    (0x0 << GPIO_26)
	#if   ((M_CUSTOM_P26_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P26_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_26)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P26_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P26_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_26)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P26_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P26_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_26)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P26_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P26_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_26)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P26_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P26_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_26)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P26_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P26_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_26)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P26_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P26_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_26)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P26_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P26_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_26)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P27_MODE) == (M_CUSTOM_ALT0))
	#define _M_P27_MODE         (0x0 << GPIO_27)
	#define _M_P27_FUNC_SEL     (0)
	#define _M_P27_FUNC1_SEL    (0)
	#define _M_P27_GPIO_MODE    (0x0 << GPIO_27)
#elif ((M_CUSTOM_P27_MODE) == (M_CUSTOM_ALT1))
    #error M_CUSTOM_P27_MODE define NONE!
#elif ((M_CUSTOM_P27_MODE) == (M_CUSTOM_ALT2))
    #define _M_P27_MODE         (0x1 << GPIO_27)
	#define _M_P27_FUNC_SEL     (0x1 << SEL_UART1)
	#define _M_P27_FUNC1_SEL    (0)
	#define _M_P27_GPIO_MODE    (0x0 << GPIO_27)
    #define PERI_IO_UART1       (0)
#elif ((M_CUSTOM_P27_MODE) == (M_CUSTOM_ALT3))
	#define _M_P27_MODE         (0x1 << GPIO_27)
	#define _M_P27_FUNC_SEL     (0x1 << SEL_PDMRX0_II)
	#define _M_P27_FUNC1_SEL    (0)
	#define _M_P27_GPIO_MODE    (0x0 << GPIO_27)
    #define PERI_IO_PDMRX0
#elif ((M_CUSTOM_P27_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P27_MODE define NONE!
#elif ((M_CUSTOM_P27_MODE) == (M_CUSTOM_ALT5))
    #define _M_P27_MODE         (0x1 << GPIO_27)
	#define _M_P27_FUNC_SEL     (0)
	#define _M_P27_FUNC1_SEL    (0x1 << SEL_I2S1)
	#define _M_P27_GPIO_MODE    (0x0 << GPIO_27)
    #define PERI_IO_I2S1        (0)
#elif ((M_CUSTOM_P27_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P27_MODE define NONE!
#elif ((M_CUSTOM_P27_MODE) == (M_CUSTOM_ALT7))
    #define _M_P27_MODE         (0x1 << GPIO_27)
	#define _M_P27_FUNC_SEL     (0)
	#define _M_P27_FUNC1_SEL    (0)
	#define _M_P27_GPIO_MODE    (0x1 << GPIO_27)
#else
	#define _M_P27_MODE         (0x0 << GPIO_27)
	#define _M_P27_FUNC_SEL     (0)
	#define _M_P27_FUNC1_SEL    (0)
	#define _M_P27_GPIO_MODE    (0x0 << GPIO_27)
	#if   ((M_CUSTOM_P27_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P27_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_27)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P27_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P27_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_27)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P27_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P27_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_27)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P27_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P27_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_27)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P27_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P27_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_27)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P27_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P27_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_27)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P27_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P27_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_27)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P27_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P27_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_27)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P28_MODE) == (M_CUSTOM_ALT0))
	#define _M_P28_MODE         (0x0 << SIO_28)
	#define _M_P28_FUNC_SEL     (0)
	#define _M_P28_FUNC1_SEL    (0)
	#define _M_P28_GPIO_MODE    (0x0 << SIO_28)
#elif ((M_CUSTOM_P28_MODE) == (M_CUSTOM_ALT1))
    #error M_CUSTOM_P28_MODE define NONE!
#elif ((M_CUSTOM_P28_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P28_MODE define NONE!
#elif ((M_CUSTOM_P28_MODE) == (M_CUSTOM_ALT3))
    #error M_CUSTOM_P28_MODE define NONE!
#elif ((M_CUSTOM_P28_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P28_MODE define NONE!
#elif ((M_CUSTOM_P28_MODE) == (M_CUSTOM_ALT5))
    #define _M_P28_MODE         (0x1 << SIO_28)
	#define _M_P28_FUNC_SEL     (0)
	#define _M_P28_FUNC1_SEL    (0x1 << SEL_I2S0_MCLK)
	#define _M_P28_GPIO_MODE    (0x0 << SIO_28)
    #define PERI_IO_I2S0        (0)
#elif ((M_CUSTOM_P28_MODE) == (M_CUSTOM_ALT6))
	#error M_CUSTOM_P28_MODE define NONE!
#elif ((M_CUSTOM_P28_MODE) == (M_CUSTOM_ALT7))
    #define _M_P28_MODE         (0x1 << SIO_28)
	#define _M_P28_FUNC_SEL     (0)
	#define _M_P28_FUNC1_SEL    (0)
	#define _M_P28_GPIO_MODE    (0x1 << SIO_28)
#else
	#define _M_P28_MODE         (0x0 << SIO_28)
	#define _M_P28_FUNC_SEL     (0)
	#define _M_P28_FUNC1_SEL    (0)
	#define _M_P28_GPIO_MODE    (0x0 << SIO_28)
	#if   ((M_CUSTOM_P28_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P28_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (SIO_28)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P28_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P28_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (SIO_28)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P28_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P28_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (SIO_28)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P28_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P28_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (SIO_28)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P28_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P28_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (SIO_28)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P28_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P28_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (SIO_28)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P28_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P28_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (SIO_28)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P28_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P28_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (SIO_28)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P29_MODE) == (M_CUSTOM_ALT0))
	#define _M_P29_MODE         (0x0 << GPIO_29)
	#define _M_P29_FUNC_SEL     (0)
	#define _M_P29_FUNC1_SEL    (0)
	#define _M_P29_GPIO_MODE    (0x0 << GPIO_29)
#elif ((M_CUSTOM_P29_MODE) == (M_CUSTOM_ALT1))
	#define _M_P29_MODE         (0x1 << GPIO_29)
	#define _M_P29_FUNC_SEL     (0x1 << SEL_ADC3)
	#define _M_P29_FUNC1_SEL    (0)
	#define _M_P29_GPIO_MODE    (0x0 << GPIO_29)
    #define PERI_IO_ADC3        (0)
#elif ((M_CUSTOM_P29_MODE) == (M_CUSTOM_ALT2))
	#define _M_P29_MODE         (0x1 << GPIO_29)
	#define _M_P29_FUNC_SEL     (0x1 << SEL_UART1)
	#define _M_P29_FUNC1_SEL    (0)
	#define _M_P29_GPIO_MODE    (0x0 << GPIO_29)
    #define PERI_IO_UART1       (0)
#elif ((M_CUSTOM_P29_MODE) == (M_CUSTOM_ALT3))
	#define _M_P29_MODE         (0x1 << GPIO_29)
	#define _M_P29_FUNC_SEL     (0x1 << SEL_PDMRX0_II)
	#define _M_P29_FUNC1_SEL    (0)
	#define _M_P29_GPIO_MODE    (0x0 << GPIO_29)
    #define PERI_IO_PDMRX0
#elif ((M_CUSTOM_P29_MODE) == (M_CUSTOM_ALT4))
	#define _M_P29_MODE         (0x1 << GPIO_29)
	#define _M_P29_FUNC_SEL     (0x1 << SEL_UART1_II)
	#define _M_P29_FUNC1_SEL    (0)
	#define _M_P29_GPIO_MODE    (0x0 << GPIO_29)
    #define PERI_IO_UART1       (0)
#elif ((M_CUSTOM_P29_MODE) == (M_CUSTOM_ALT5))
	#define _M_P29_MODE         (0x1 << GPIO_29)
	#define _M_P29_FUNC_SEL     (0)
	#define _M_P29_FUNC1_SEL    (0x1 << SEL_I2S1)
	#define _M_P29_GPIO_MODE    (0x0 << GPIO_29)
    #define PERI_IO_I2S1        (0)
#elif ((M_CUSTOM_P29_MODE) == (M_CUSTOM_ALT6))
	#error M_CUSTOM_P28_MODE define NONE!
#elif ((M_CUSTOM_P29_MODE) == (M_CUSTOM_ALT7))
	#define _M_P29_MODE         (0x1 << GPIO_29)
	#define _M_P29_FUNC_SEL     (0)
	#define _M_P29_FUNC1_SEL    (0)
	#define _M_P29_GPIO_MODE    (0x1 << GPIO_29)
#else
	#define _M_P29_MODE         (0x0 << GPIO_29)
	#define _M_P29_FUNC_SEL     (0)
	#define _M_P29_FUNC1_SEL    (0)
	#define _M_P29_GPIO_MODE    (0x0 << GPIO_29)
	#if   ((M_CUSTOM_P29_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P29_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_29)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P29_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P29_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_29)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P29_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P29_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_29)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P29_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P29_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_29)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P29_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P29_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_29)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P29_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P29_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_29)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P29_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P29_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_29)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P29_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P29_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_29)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P30_MODE) == (M_CUSTOM_ALT0))
	#define _M_P30_MODE         (0x0 << GPIO_30)
	#define _M_P30_FUNC_SEL     (0)
	#define _M_P30_FUNC1_SEL    (0)
	#define _M_P30_GPIO_MODE    (0x0 << GPIO_30)
#elif ((M_CUSTOM_P30_MODE) == (M_CUSTOM_ALT1))
	#define _M_P30_MODE         (0x1 << GPIO_30)
	#define _M_P30_FUNC_SEL     (0x1 << SEL_ADC4)
	#define _M_P30_FUNC1_SEL    (0)
	#define _M_P30_GPIO_MODE    (0x0 << GPIO_30)
    #define PERI_IO_ADC4        (0)
#elif ((M_CUSTOM_P30_MODE) == (M_CUSTOM_ALT2))
	#define _M_P30_MODE         (0x1 << GPIO_30)
	#define _M_P30_FUNC_SEL     (0x1 << SEL_UART1)
	#define _M_P30_FUNC1_SEL    (0)
	#define _M_P30_GPIO_MODE    (0x0 << GPIO_30)
    #define PERI_IO_UART1       (0)
#elif ((M_CUSTOM_P30_MODE) == (M_CUSTOM_ALT3))
	#define _M_P30_MODE         (0x1 << GPIO_30)
	#define _M_P30_FUNC_SEL     (0x1 << SEL_PDMRX1_II)
	#define _M_P30_FUNC1_SEL    (0)
	#define _M_P30_GPIO_MODE    (0x0 << GPIO_30)
    #define PERI_IO_PDMRX1      (0)
#elif ((M_CUSTOM_P30_MODE) == (M_CUSTOM_ALT4))
	#define _M_P30_MODE         (0x1 << GPIO_30)
	#define _M_P30_FUNC_SEL     (0x1 << SEL_PDMTX0_II)
	#define _M_P30_FUNC1_SEL    (0)
	#define _M_P30_GPIO_MODE    (0x0 << GPIO_30)
    #define PERI_IO_PDMTX0
#elif ((M_CUSTOM_P30_MODE) == (M_CUSTOM_ALT5))
	#define _M_P30_MODE         (0x1 << GPIO_30)
	#define _M_P30_FUNC_SEL     (0)
	#define _M_P30_FUNC1_SEL    (0x1 << SEL_I2S1)
	#define _M_P30_GPIO_MODE    (0x0 << GPIO_30)
#elif ((M_CUSTOM_P30_MODE) == (M_CUSTOM_ALT6))
	#error M_CUSTOM_P31_MODE define NONE!
#elif ((M_CUSTOM_P30_MODE) == (M_CUSTOM_ALT7))
	#define _M_P30_MODE         (0x1 << GPIO_30)
	#define _M_P30_FUNC_SEL     (0)
	#define _M_P30_FUNC1_SEL    (0)
	#define _M_P30_GPIO_MODE    (0x1 << GPIO_30)
#else
	#define _M_P30_MODE         (0x0 << GPIO_30)
	#define _M_P30_FUNC_SEL     (0)
	#define _M_P30_FUNC1_SEL    (0)
	#define _M_P30_GPIO_MODE    (0x0 << GPIO_30)
	#if   ((M_CUSTOM_P30_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P30_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_30)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P30_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P30_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_30)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P30_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P30_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_30)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P30_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P30_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_30)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P30_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P30_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_30)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P30_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P30_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_30)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P30_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P30_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_30)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P30_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P30_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_30)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P31_MODE) == (M_CUSTOM_ALT0))
	#define _M_P31_MODE         (0x0 << GPIO_31)
	#define _M_P31_FUNC_SEL     (0)
	#define _M_P31_FUNC1_SEL    (0)
	#define _M_P31_GPIO_MODE    (0x0 << GPIO_31)
#elif ((M_CUSTOM_P31_MODE) == (M_CUSTOM_ALT1))
	#define _M_P31_MODE         (0x1 << GPIO_31)
	#define _M_P31_FUNC_SEL     (0x1 << SEL_ADC5)
	#define _M_P31_FUNC1_SEL    (0)
	#define _M_P31_GPIO_MODE    (0x0 << GPIO_31)
    #define PERI_IO_ADC5        (0)
#elif ((M_CUSTOM_P31_MODE) == (M_CUSTOM_ALT2))
	#define _M_P31_MODE         (0x1 << GPIO_31)
	#define _M_P31_FUNC_SEL     (0x1 << SEL_UART1)
	#define _M_P31_FUNC1_SEL    (0)
	#define _M_P31_GPIO_MODE    (0x0 << GPIO_31)
    #define PERI_IO_UART1       (0)
#elif ((M_CUSTOM_P31_MODE) == (M_CUSTOM_ALT3))
	#define _M_P31_MODE         (0x1 << GPIO_31)
	#define _M_P31_FUNC_SEL     (0x1 << SEL_PDMRX1_II)
	#define _M_P31_FUNC1_SEL    (0)
	#define _M_P31_GPIO_MODE    (0x0 << GPIO_31)
    #define PERI_IO_PDMRX1      (0)
#elif ((M_CUSTOM_P31_MODE) == (M_CUSTOM_ALT4))
    #define _M_P31_MODE         (0x1 << GPIO_31)
	#define _M_P31_FUNC_SEL     (0x1 << SEL_PDMTX0_II)
	#define _M_P31_FUNC1_SEL    (0)
	#define _M_P31_GPIO_MODE    (0x0 << GPIO_31)
    #define PERI_IO_PDMTX0
#elif ((M_CUSTOM_P31_MODE) == (M_CUSTOM_ALT5))
	#define _M_P31_MODE         (0x1 << GPIO_31)
	#define _M_P31_FUNC_SEL     (0)
	#define _M_P31_FUNC1_SEL    (0x1 << SEL_I2S1)
	#define _M_P31_GPIO_MODE    (0x0 << GPIO_31)
    #define PERI_IO_I2S1        (0)
#elif ((M_CUSTOM_P31_MODE) == (M_CUSTOM_ALT6))
	#error M_CUSTOM_P32_MODE define NONE!
#elif ((M_CUSTOM_P31_MODE) == (M_CUSTOM_ALT7))
	#define _M_P31_MODE         (0x1 << GPIO_31)
	#define _M_P31_FUNC_SEL     (0)
	#define _M_P31_FUNC1_SEL    (0)
	#define _M_P31_GPIO_MODE    (0x1 << GPIO_31)
#else
	#define _M_P31_MODE         (0x0 << GPIO_31)
	#define _M_P31_FUNC_SEL     (0)
	#define _M_P31_FUNC1_SEL    (0)
	#define _M_P31_GPIO_MODE    (0x0 << GPIO_31)
	#if   ((M_CUSTOM_P31_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P31_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_31)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P31_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P31_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_31)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P31_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P31_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_31)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P31_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P31_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_31)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P31_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P31_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_31)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P31_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P31_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_31)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P31_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P31_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_31)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P31_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P31_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_31)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#define GPIO_BIT_32			(GPIO_32-32) //////////////// Since over 32-bit, re-define GPIO 32 ~ 37 ////////////////
#define GPIO_BIT_33			(GPIO_33-32)
#define SIO_BIT_34			(SIO_34-32)
#define GPIO_BIT_35			(GPIO_35-32)
#define GPIO_BIT_36			(GPIO_36-32)
#define GPIO_BIT_37			(GPIO_37-32)

#if ((M_CUSTOM_P32_MODE) == (M_CUSTOM_ALT0))
	#define _M_P32_MODE         (0x0 << GPIO_BIT_32)
	#define _M_P32_FUNC_SEL     (0)
	#define _M_P32_FUNC1_SEL    (0)
	#define _M_P32_GPIO_MODE    (0x0 << GPIO_BIT_32)
#elif ((M_CUSTOM_P32_MODE) == (M_CUSTOM_ALT1))
	#define _M_P32_MODE         (0x1 << GPIO_BIT_32)
	#define _M_P32_FUNC_SEL     (0x1 << SEL_BTCX)
	#define _M_P32_FUNC1_SEL    (0)
	#define _M_P32_GPIO_MODE    (0x0 << GPIO_BIT_32)
    #define PERI_IO_BTCX
#elif ((M_CUSTOM_P32_MODE) == (M_CUSTOM_ALT2))
	#error M_CUSTOM_P32_MODE define NONE!
#elif ((M_CUSTOM_P32_MODE) == (M_CUSTOM_ALT3))
	#define _M_P32_MODE         (0x1 << GPIO_BIT_32)
	#define _M_P32_FUNC_SEL     (0)
	#define _M_P32_FUNC1_SEL    (0x1 << SEL_SPIMAS2)
	#define _M_P32_GPIO_MODE    (0x0 << GPIO_BIT_32)
    #define PERI_IO_SPIM2       (0)
#elif ((M_CUSTOM_P32_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P32_MODE define NONE!
#elif ((M_CUSTOM_P32_MODE) == (M_CUSTOM_ALT5))
	#error M_CUSTOM_P32_MODE define NONE!
#elif ((M_CUSTOM_P32_MODE) == (M_CUSTOM_ALT6))
	#error M_CUSTOM_P32_MODE define NONE!
#elif ((M_CUSTOM_P32_MODE) == (M_CUSTOM_ALT7))
	#define _M_P32_MODE         (0x1 << GPIO_BIT_32)
	#define _M_P32_FUNC_SEL     (0)
	#define _M_P32_FUNC1_SEL    (0)
	#define _M_P32_GPIO_MODE    (0x1 << GPIO_BIT_32)
#else
	#define _M_P32_MODE         (0x0 << GPIO_BIT_32)
	#define _M_P32_FUNC_SEL     (0)
	#define _M_P32_FUNC1_SEL    (0)
	#define _M_P32_GPIO_MODE    (0x0 << GPIO_BIT_32)
	#if   ((M_CUSTOM_P32_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P32_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_BIT_32)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P32_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P32_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_BIT_32)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P32_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P32_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_BIT_32)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P32_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P32_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_BIT_32)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P32_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P32_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_BIT_32)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P32_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P32_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_BIT_32)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P32_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P32_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_BIT_32)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P32_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P32_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_BIT_32)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P33_MODE) == (M_CUSTOM_ALT0))
	#define _M_P33_MODE         (0x0 << GPIO_BIT_33)
	#define _M_P33_FUNC_SEL     (0)
	#define _M_P33_FUNC1_SEL    (0)
	#define _M_P33_GPIO_MODE    (0x0 << GPIO_BIT_33)
#elif ((M_CUSTOM_P33_MODE) == (M_CUSTOM_ALT1))
	#error M_CUSTOM_P33_MODE define NONE!
#elif ((M_CUSTOM_P33_MODE) == (M_CUSTOM_ALT2))
	#error M_CUSTOM_P33_MODE define NONE!
#elif ((M_CUSTOM_P33_MODE) == (M_CUSTOM_ALT3))
	#define _M_P33_MODE         (0x1 << GPIO_BIT_33)
	#define _M_P33_FUNC_SEL     (0)
	#define _M_P33_FUNC1_SEL    (0x1 << SEL_SPIMAS2)
	#define _M_P33_GPIO_MODE    (0x0 << GPIO_BIT_33)
    #define PERI_IO_SPIM2       (0)
#elif ((M_CUSTOM_P33_MODE) == (M_CUSTOM_ALT4))
    #define _M_P33_MODE         (0x1 << GPIO_BIT_33)
	#define _M_P33_FUNC_SEL     (0x1 << SEL_UART1_II)
	#define _M_P33_FUNC1_SEL    (0)
	#define _M_P33_GPIO_MODE    (0x0 << GPIO_BIT_33)
    #define PERI_IO_UART1       (0)
#elif ((M_CUSTOM_P33_MODE) == (M_CUSTOM_ALT5))
    #define _M_P33_MODE         (0x1 << GPIO_BIT_33)
	#define _M_P33_FUNC_SEL     (0x1 << SEL_BTCX_II)
	#define _M_P33_FUNC1_SEL    (0)
	#define _M_P33_GPIO_MODE    (0x0 << GPIO_BIT_33)
    #define PERI_IO_BTCX
#elif ((M_CUSTOM_P33_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P33_MODE define NONE!
#elif ((M_CUSTOM_P33_MODE) == (M_CUSTOM_ALT7))
    #define _M_P33_MODE         (0x1 << GPIO_BIT_33)
	#define _M_P33_FUNC_SEL     (0)
	#define _M_P33_FUNC1_SEL    (0)
	#define _M_P33_GPIO_MODE    (0x1 << GPIO_BIT_33)
#else
	#define _M_P33_MODE         (0x0 << GPIO_BIT_33)
	#define _M_P33_FUNC_SEL     (0)
	#define _M_P33_FUNC1_SEL    (0)
	#define _M_P33_GPIO_MODE    (0x0 << GPIO_BIT_33)
	#if   ((M_CUSTOM_P33_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P33_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_BIT_33)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P33_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P33_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_BIT_33)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P33_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P33_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_BIT_33)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P33_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P33_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_BIT_33)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P33_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P33_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_BIT_33)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P33_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P33_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_BIT_33)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P33_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P33_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_BIT_33)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P33_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P33_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_BIT_33)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P34_MODE) == (M_CUSTOM_ALT0))
	#define _M_P34_MODE         (0x0 << SIO_BIT_34)
	#define _M_P34_FUNC_SEL     (0)
	#define _M_P34_FUNC1_SEL    (0)
	#define _M_P34_GPIO_MODE    (0x0 << SIO_BIT_34)
#elif ((M_CUSTOM_P34_MODE) == (M_CUSTOM_ALT1))
	#error M_CUSTOM_P34_MODE define NONE!
#elif ((M_CUSTOM_P34_MODE) == (M_CUSTOM_ALT2))
	#error M_CUSTOM_P34_MODE define NONE!
#elif ((M_CUSTOM_P34_MODE) == (M_CUSTOM_ALT3))
	#error M_CUSTOM_P34_MODE define NONE!
#elif ((M_CUSTOM_P34_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P34_MODE define NONE!
#elif ((M_CUSTOM_P34_MODE) == (M_CUSTOM_ALT5))
    #error M_CUSTOM_P34_MODE define NONE!
#elif ((M_CUSTOM_P34_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P34_MODE define NONE!
#elif ((M_CUSTOM_P34_MODE) == (M_CUSTOM_ALT7))
    #define _M_P34_MODE         (0x1 << SIO_BIT_34)
	#define _M_P34_FUNC_SEL     (0)
	#define _M_P34_FUNC1_SEL    (0)
	#define _M_P34_GPIO_MODE    (0x1 << SIO_BIT_34)
#else
	#define _M_P34_MODE         (0x0 << SIO_BIT_34)
	#define _M_P34_FUNC_SEL     (0)
	#define _M_P34_FUNC1_SEL    (0)
	#define _M_P34_GPIO_MODE    (0x0 << SIO_BIT_34)
	#if   ((M_CUSTOM_P34_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P34_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (SIO_BIT_34)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P34_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P34_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (SIO_BIT_34)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P34_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P34_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (SIO_BIT_34)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P34_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P34_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (SIO_BIT_34)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P34_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P34_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (SIO_BIT_34)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P34_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P34_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (SIO_BIT_34)
        #define PERI_IO_PWM5    (0)
	#elif ((M_CUSTOM_P34_MODE) == (M_CUSTOM_PWM6))
		#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P34_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (SIO_BIT_34)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P34_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P34_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (SIO_BIT_34)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P35_MODE) == (M_CUSTOM_ALT0))
	#define _M_P35_MODE         (0x0 << GPIO_BIT_35)
	#define _M_P35_FUNC_SEL     (0)
	#define _M_P35_FUNC1_SEL    (0)
	#define _M_P35_GPIO_MODE    (0x0 << GPIO_BIT_35)
#elif ((M_CUSTOM_P35_MODE) == (M_CUSTOM_ALT1))
    #error M_CUSTOM_P35_MODE define NONE!
#elif ((M_CUSTOM_P35_MODE) == (M_CUSTOM_ALT2))
    #error M_CUSTOM_P35_MODE define NONE!
#elif ((M_CUSTOM_P35_MODE) == (M_CUSTOM_ALT3))
    #define _M_P35_MODE         (0x1 << GPIO_BIT_35)
	#define _M_P35_FUNC_SEL     (0)
	#define _M_P35_FUNC1_SEL    (0x1 << SEL_SPIMAS2)
	#define _M_P35_GPIO_MODE    (0x0 << GPIO_BIT_35)
    #define PERI_IO_SPIM2       (0)
#elif ((M_CUSTOM_P35_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P35_MODE define NONE!
#elif ((M_CUSTOM_P35_MODE) == (M_CUSTOM_ALT5))
    #error M_CUSTOM_P35_MODE define NONE!
#elif ((M_CUSTOM_P35_MODE) == (M_CUSTOM_ALT6))
    #error M_CUSTOM_P35_MODE define NONE!
#elif ((M_CUSTOM_P35_MODE) == (M_CUSTOM_ALT7))
    #define _M_P35_MODE         (0x1 << GPIO_BIT_35)
	#define _M_P35_FUNC_SEL     (0)
	#define _M_P35_FUNC1_SEL    (0)
	#define _M_P35_GPIO_MODE    (0x1 << GPIO_BIT_35)
#else
	#define _M_P35_MODE         (0x0 << GPIO_BIT_35)
	#define _M_P35_FUNC_SEL     (0)
	#define _M_P35_FUNC1_SEL    (0)
	#define _M_P35_GPIO_MODE    (0x0 << GPIO_BIT_35)
	#if   ((M_CUSTOM_P35_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P35_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_BIT_35)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P35_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P35_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_BIT_35)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P35_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P35_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_BIT_35)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P35_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P35_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_BIT_35)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P35_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P35_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_BIT_35)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P35_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P35_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_BIT_35)
        #define PERI_IO_PWM5    (0)
		#elif ((M_CUSTOM_P35_MODE) == (M_CUSTOM_PWM6))
	#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P35_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_BIT_35)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P35_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P35_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_BIT_35)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P36_MODE) == (M_CUSTOM_ALT0))
	#define _M_P36_MODE         (0x0 << GPIO_BIT_36)
	#define _M_P36_FUNC_SEL     (0)
	#define _M_P36_FUNC1_SEL    (0)
	#define _M_P36_GPIO_MODE    (0x0 << GPIO_BIT_36)
#elif ((M_CUSTOM_P36_MODE) == (M_CUSTOM_ALT1))
    #define _M_P36_MODE         (0x1 << GPIO_BIT_36)
	#define _M_P36_FUNC_SEL     (0x1 << SEL_ADC6)
	#define _M_P36_FUNC1_SEL    (0)
	#define _M_P36_GPIO_MODE    (0x0 << GPIO_BIT_36)
    #define PERI_IO_ADC6        (0)
#elif ((M_CUSTOM_P36_MODE) == (M_CUSTOM_ALT2))
    #define _M_P36_MODE         (0x1 << GPIO_BIT_36)
	#define _M_P36_FUNC_SEL     (0x1 << SEL_I2C0_II)
	#define _M_P36_FUNC1_SEL    (0)
	#define _M_P36_GPIO_MODE    (0x0 << GPIO_BIT_36)
    #define PERI_IO_I2C0        (0)
#elif ((M_CUSTOM_P36_MODE) == (M_CUSTOM_ALT3))
    #define _M_P36_MODE         (0x1 << GPIO_BIT_36)
	#define _M_P36_FUNC_SEL     (0x1 << SEL_UART2_III)
	#define _M_P36_FUNC1_SEL    (0)
	#define _M_P36_GPIO_MODE    (0x0 << GPIO_BIT_36)
    #define PERI_IO_UART2       (0)
#elif ((M_CUSTOM_P36_MODE) == (M_CUSTOM_ALT4))
    #define _M_P36_MODE         (0x1 << GPIO_BIT_36)
	#define _M_P36_FUNC_SEL     (0)
	#define _M_P36_FUNC1_SEL    (0x1 << SEL_SPIMAS2_CSN)
	#define _M_P36_GPIO_MODE    (0x0 << GPIO_BIT_36)
    #define PERI_IO_SPIM2       (0)
#elif ((M_CUSTOM_P36_MODE) == (M_CUSTOM_ALT5))
    #define _M_P36_MODE         (0x1 << GPIO_BIT_36)
	#define _M_P36_FUNC_SEL     (0x1 << SEL_BTCX_II)
	#define _M_P36_FUNC1_SEL    (0)
	#define _M_P36_GPIO_MODE    (0x0 << GPIO_BIT_36)
    #define PERI_IO_BTCX
#elif ((M_CUSTOM_P36_MODE) == (M_CUSTOM_ALT6))
    #define _M_P36_MODE         (0x1 << GPIO_BIT_36)
	#define _M_P36_FUNC_SEL     (0x1 << SEL_ANTSW)
	#define _M_P36_FUNC1_SEL    (0)
	#define _M_P36_GPIO_MODE    (0x0 << GPIO_BIT_36)
    #define PERI_IO_ANTSW
#elif ((M_CUSTOM_P36_MODE) == (M_CUSTOM_ALT7))
    #define _M_P36_MODE         (0x1 << GPIO_BIT_36)
	#define _M_P36_FUNC_SEL     (0)
	#define _M_P36_FUNC1_SEL    (0)
	#define _M_P36_GPIO_MODE    (0x1 << GPIO_BIT_36)
#else
	#define _M_P36_MODE         (0x0 << GPIO_BIT_36)
	#define _M_P36_FUNC_SEL     (0)
	#define _M_P36_FUNC1_SEL    (0)
	#define _M_P36_GPIO_MODE    (0x0 << GPIO_BIT_36)
	#if   ((M_CUSTOM_P36_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P36_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_BIT_36)
        #define PERI_IO_PWM0    (0)
	#elif ((M_CUSTOM_P36_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P36_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_BIT_36)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P36_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P36_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_BIT_36)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P36_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P36_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_BIT_36)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P36_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P36_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_BIT_36)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P36_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P36_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_BIT_36)
        #define PERI_IO_PWM5    (0)
		#elif ((M_CUSTOM_P36_MODE) == (M_CUSTOM_PWM6))
	#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P36_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_BIT_36)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P36_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P36_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_BIT_36)
        #define PERI_IO_PWM7    (0)
	#endif
#endif

#if ((M_CUSTOM_P37_MODE) == (M_CUSTOM_ALT0))
	#define _M_P37_MODE         (0x0 << GPIO_BIT_37)
	#define _M_P37_FUNC_SEL     (0)
	#define _M_P37_FUNC1_SEL    (0)
	#define _M_P37_GPIO_MODE    (0x0 << GPIO_BIT_37)
#elif ((M_CUSTOM_P37_MODE) == (M_CUSTOM_ALT1))
    #define _M_P37_MODE         (0x1 << GPIO_BIT_37)
	#define _M_P37_FUNC_SEL     (0x1 << SEL_ADC7)
	#define _M_P37_FUNC1_SEL    (0)
	#define _M_P37_GPIO_MODE    (0x0 << GPIO_BIT_37)
    #define PERI_IO_ADC7        (0)
#elif ((M_CUSTOM_P37_MODE) == (M_CUSTOM_ALT2))
    #define _M_P37_MODE         (0x1 << GPIO_BIT_37)
	#define _M_P37_FUNC_SEL     (0x1 << SEL_I2C0_II)
	#define _M_P37_FUNC1_SEL    (0)
	#define _M_P37_GPIO_MODE    (0x0 << GPIO_BIT_37)
    #define PERI_IO_I2C0        (0)
#elif ((M_CUSTOM_P37_MODE) == (M_CUSTOM_ALT3))
    #define _M_P37_MODE         (0x1 << GPIO_BIT_37)
	#define _M_P37_FUNC_SEL     (0x1 << SEL_UART2_III)
	#define _M_P37_FUNC1_SEL    (0)
	#define _M_P37_GPIO_MODE    (0x0 << GPIO_BIT_37)
    #define PERI_IO_UART2       (0)
#elif ((M_CUSTOM_P37_MODE) == (M_CUSTOM_ALT4))
    #error M_CUSTOM_P35_MODE define NONE!
#elif ((M_CUSTOM_P37_MODE) == (M_CUSTOM_ALT5))
    #define _M_P37_MODE         (0x1 << GPIO_BIT_37)
	#define _M_P37_FUNC_SEL     (0x1 << SEL_BTCX_II)
	#define _M_P37_FUNC1_SEL    (0)
	#define _M_P37_GPIO_MODE    (0x0 << GPIO_BIT_37)
    #define PERI_IO_BTCX
#elif ((M_CUSTOM_P37_MODE) == (M_CUSTOM_ALT6))
    #define _M_P37_MODE         (0x1 << GPIO_BIT_37)
	#define _M_P37_FUNC_SEL     (0x1 << SEL_ANTSW)
	#define _M_P37_FUNC1_SEL    (0)
	#define _M_P37_GPIO_MODE    (0x0 << GPIO_BIT_37)
    #define PERI_IO_ANTSW
#elif ((M_CUSTOM_P37_MODE) == (M_CUSTOM_ALT7))
    #define _M_P37_MODE         (0x1 << GPIO_BIT_37)
	#define _M_P37_FUNC_SEL     (0)
	#define _M_P37_FUNC1_SEL    (0)
	#define _M_P37_GPIO_MODE    (0x1 << GPIO_BIT_37)
#else
	#define _M_P37_MODE         (0x0 << GPIO_BIT_37)
	#define _M_P37_FUNC_SEL     (0)
	#define _M_P37_FUNC1_SEL    (0)
	#define _M_P37_GPIO_MODE    (0x0 << GPIO_BIT_37)
	#if   ((M_CUSTOM_P37_MODE) == (M_CUSTOM_PWM0))
		#if defined(M_CUSTOM_PWM0_PIN)
			#error M_CUSTOM_P37_MODE define PWM0 collision to other pin.
		#endif
		#define M_CUSTOM_PWM0_PIN           (GPIO_BIT_37)
        #define PERI_IO_PWM0
	#elif ((M_CUSTOM_P37_MODE) == (M_CUSTOM_PWM1))
		#if defined(M_CUSTOM_PWM1_PIN)
			#error M_CUSTOM_P37_MODE define PWM1 collision to other pin.
		#endif
		#define M_CUSTOM_PWM1_PIN           (GPIO_BIT_37)
        #define PERI_IO_PWM1    (0)
	#elif ((M_CUSTOM_P37_MODE) == (M_CUSTOM_PWM2))
		#if defined(M_CUSTOM_PWM2_PIN)
			#error M_CUSTOM_P37_MODE define PWM2 collision to other pin.
		#endif
		#define M_CUSTOM_PWM2_PIN           (GPIO_BIT_37)
        #define PERI_IO_PWM2    (0)
	#elif ((M_CUSTOM_P37_MODE) == (M_CUSTOM_PWM3))
		#if defined(M_CUSTOM_PWM3_PIN)
			#error M_CUSTOM_P37_MODE define PWM3 collision to other pin.
		#endif
		#define M_CUSTOM_PWM3_PIN           (GPIO_BIT_37)
        #define PERI_IO_PWM3    (0)
	#elif ((M_CUSTOM_P37_MODE) == (M_CUSTOM_PWM4))
		#if defined(M_CUSTOM_PWM4_PIN)
			#error M_CUSTOM_P37_MODE define PWM4 collision to other pin.
		#endif
		#define M_CUSTOM_PWM4_PIN           (GPIO_BIT_37)
        #define PERI_IO_PWM4    (0)
	#elif ((M_CUSTOM_P37_MODE) == (M_CUSTOM_PWM5))
		#if defined(M_CUSTOM_PWM5_PIN)
			#error M_CUSTOM_P37_MODE define PWM5 collision to other pin.
		#endif
		#define M_CUSTOM_PWM5_PIN           (GPIO_BIT_37)
        #define PERI_IO_PWM5    (0)
		#elif ((M_CUSTOM_P37_MODE) == (M_CUSTOM_PWM6))
	#if defined(M_CUSTOM_PWM6_PIN)
			#error M_CUSTOM_P37_MODE define PWM6 collision to other pin.
		#endif
		#define M_CUSTOM_PWM6_PIN           (GPIO_BIT_37)
        #define PERI_IO_PWM6    (0)
	#elif ((M_CUSTOM_P37_MODE) == (M_CUSTOM_PWM7))
		#if defined(M_CUSTOM_PWM7_PIN)
			#error M_CUSTOM_P37_MODE define PWM7 collision to other pin.
		#endif
		#define M_CUSTOM_PWM7_PIN           (GPIO_BIT_37)
        #define PERI_IO_PWM7    (0)
	#endif
#endif


#ifndef _M_P00_MODE
    #error _M_P00_MODE define error!
#endif
#ifndef _M_P01_MODE
    #error _M_P01_MODE define error!
#endif
#ifndef _M_P02_MODE
    #error _M_P02_MODE define error!
#endif
#ifndef _M_P03_MODE
    #error _M_P03_MODE define error!
#endif
#ifndef _M_P04_MODE
    #error _M_P04_MODE define error!
#endif
#ifndef _M_P05_MODE
    #error _M_P05_MODE define error!
#endif
#ifndef _M_P06_MODE
    #error _M_P06_MODE define error!
#endif
#ifndef _M_P07_MODE
    #error _M_P07_MODE define error!
#endif
#ifndef _M_P08_MODE
    #error _M_P08_MODE define error!
#endif
#ifndef _M_P09_MODE
    #error _M_P09_MODE define error!
#endif
#ifndef _M_P10_MODE
    #error _M_P10_MODE define error!
#endif
#ifndef _M_P11_MODE
    #error _M_P11_MODE define error!
#endif
#ifndef _M_P12_MODE
    #error _M_P12_MODE define error!
#endif
#ifndef _M_P13_MODE
    #error _M_P13_MODE define error!
#endif
#ifndef _M_P14_MODE
    #error _M_P14_MODE define error!
#endif
#ifndef _M_P15_MODE
    #error _M_P15_MODE define error!
#endif
#ifndef _M_P16_MODE
    #error _M_P16_MODE define error!
#endif
#ifndef _M_P17_MODE
    #error _M_P17_MODE define error!
#endif
#ifndef _M_P18_MODE
    #error _M_P18_MODE define error!
#endif
#ifndef _M_P19_MODE
    #error _M_P19_MODE define error!
#endif
#ifndef _M_P20_MODE
    #error _M_P20_MODE define error!
#endif
#ifndef _M_P21_MODE
    #error _M_P21_MODE define error!
#endif
#ifndef _M_P22_MODE
    #error _M_P22_MODE define error!
#endif
#ifndef _M_P23_MODE
    #error _M_P23_MODE define error!
#endif
#ifndef _M_P24_MODE
    #error _M_P24_MODE define error!
#endif
#ifndef _M_P25_MODE
    #error _M_P25_MODE define error!
#endif
#ifndef _M_P26_MODE
    #error _M_P26_MODE define error!
#endif
#ifndef _M_P27_MODE
    #error _M_P27_MODE define error!
#endif
#ifndef _M_P28_MODE
    #error _M_P28_MODE define error!
#endif
#ifndef _M_P29_MODE
    #error _M_P29_MODE define error!
#endif
#ifndef _M_P30_MODE
    #error _M_P30_MODE define error!
#endif
#ifndef _M_P31_MODE
    #error _M_P31_MODE define error!
#endif
#ifndef _M_P32_MODE
    #error _M_P32_MODE define error!
#endif
#ifndef _M_P33_MODE
    #error _M_P33_MODE define error!
#endif
#ifndef _M_P34_MODE
    #error _M_P34_MODE define error!
#endif
#ifndef _M_P35_MODE
    #error _M_P35_MODE define error!
#endif
#ifndef _M_P36_MODE
    #error _M_P36_MODE define error!
#endif
#ifndef _M_P37_MODE
    #error _M_P37_MODE define error!
#endif


#if defined(_M_P00_MODE) && defined(_M_P01_MODE) && defined(_M_P02_MODE) && defined(_M_P03_MODE) && \
    defined(_M_P04_MODE) && defined(_M_P05_MODE) && defined(_M_P06_MODE) && defined(_M_P13_MODE) && \
    defined(_M_P14_MODE) && defined(_M_P15_MODE) && defined(_M_P16_MODE) && defined(_M_P17_MODE) && \
	defined(_M_P18_MODE) && defined(_M_P19_MODE) && defined(_M_P20_MODE) && defined(_M_P21_MODE) && \
    defined(_M_P22_MODE) && defined(_M_P23_MODE) && defined(_M_P24_MODE) && defined(_M_P25_MODE) && \
	defined(_M_P26_MODE) && defined(_M_P27_MODE) && defined(_M_P28_MODE) && defined(_M_P29_MODE) && \
	defined(_M_P30_MODE) && defined(_M_P31_MODE) && defined(_M_P32_MODE) && defined(_M_P33_MODE) && \
	defined(_M_P34_MODE) && defined(_M_P35_MODE) && defined(_M_P36_MODE) && defined(_M_P37_MODE)
    //#warning PIN CONFIG ALT SUCCESS!

#define _M_PIN_MODE ( \
                    _M_P00_MODE | _M_P01_MODE | _M_P02_MODE | _M_P03_MODE | \
                    _M_P04_MODE | _M_P05_MODE | _M_P06_MODE | _M_P13_MODE | \
                    _M_P07_MODE | _M_P08_MODE | _M_P09_MODE | _M_P10_MODE | \
                    _M_P11_MODE | _M_P12_MODE | \
                    _M_P14_MODE | _M_P15_MODE | _M_P16_MODE | _M_P17_MODE | \
                    _M_P18_MODE | _M_P19_MODE | _M_P20_MODE | _M_P21_MODE | \
                    _M_P22_MODE | _M_P23_MODE | _M_P24_MODE | _M_P25_MODE | \
                    _M_P26_MODE | _M_P27_MODE | _M_P28_MODE | _M_P29_MODE | \
                    _M_P30_MODE | _M_P31_MODE)
#define _M_PIN_MODE_32 ( \
                    _M_P32_MODE | _M_P33_MODE | _M_P34_MODE | _M_P35_MODE | \
                    _M_P36_MODE | _M_P37_MODE)
#define _M_FUNC_SEL ( \
                    _M_P00_FUNC_SEL | _M_P01_FUNC_SEL | _M_P02_FUNC_SEL | _M_P03_FUNC_SEL | \
                    _M_P04_FUNC_SEL | _M_P05_FUNC_SEL | _M_P06_FUNC_SEL | _M_P13_FUNC_SEL | \
                    _M_P07_FUNC_SEL | _M_P08_FUNC_SEL | _M_P09_FUNC_SEL | _M_P10_FUNC_SEL | \
                    _M_P11_FUNC_SEL | _M_P12_FUNC_SEL | \
                    _M_P14_FUNC_SEL | _M_P15_FUNC_SEL | _M_P16_FUNC_SEL | _M_P17_FUNC_SEL | \
                    _M_P18_FUNC_SEL | _M_P19_FUNC_SEL | _M_P20_FUNC_SEL | _M_P21_FUNC_SEL | \
                    _M_P22_FUNC_SEL | _M_P23_FUNC_SEL | _M_P24_FUNC_SEL | _M_P25_FUNC_SEL | \
                    _M_P26_FUNC_SEL | _M_P27_FUNC_SEL | _M_P28_FUNC_SEL | _M_P29_FUNC_SEL | \
                    _M_P30_FUNC_SEL | _M_P31_FUNC_SEL | _M_P32_FUNC_SEL | _M_P33_FUNC_SEL | \
                    _M_P34_FUNC_SEL | _M_P35_FUNC_SEL | _M_P36_FUNC_SEL | _M_P37_FUNC_SEL)
#define _M_FUNC1_SEL ( \
                    _M_P00_FUNC1_SEL | _M_P01_FUNC1_SEL | _M_P02_FUNC1_SEL | _M_P03_FUNC1_SEL | \
                    _M_P04_FUNC1_SEL | _M_P05_FUNC1_SEL | _M_P06_FUNC1_SEL | _M_P13_FUNC1_SEL | \
                    _M_P07_FUNC1_SEL | _M_P08_FUNC1_SEL | _M_P09_FUNC1_SEL | _M_P10_FUNC1_SEL | \
                    _M_P11_FUNC1_SEL | _M_P12_FUNC1_SEL | \
                    _M_P14_FUNC1_SEL | _M_P15_FUNC1_SEL | _M_P16_FUNC1_SEL | _M_P17_FUNC1_SEL | \
                    _M_P18_FUNC1_SEL | _M_P19_FUNC1_SEL | _M_P20_FUNC1_SEL | _M_P21_FUNC1_SEL | \
                    _M_P22_FUNC1_SEL | _M_P23_FUNC1_SEL | _M_P24_FUNC1_SEL | _M_P25_FUNC1_SEL | \
                    _M_P26_FUNC1_SEL | _M_P27_FUNC1_SEL | _M_P28_FUNC1_SEL | _M_P29_FUNC1_SEL | \
                    _M_P30_FUNC1_SEL | _M_P31_FUNC1_SEL | _M_P32_FUNC1_SEL | _M_P33_FUNC1_SEL | \
                    _M_P34_FUNC1_SEL | _M_P35_FUNC1_SEL | _M_P36_FUNC1_SEL | _M_P37_FUNC1_SEL)
#define _M_FORCE_GPIO ( \
                    _M_P00_GPIO_MODE | _M_P01_GPIO_MODE | _M_P02_GPIO_MODE | _M_P03_GPIO_MODE | \
                    _M_P04_GPIO_MODE | _M_P05_GPIO_MODE | _M_P06_GPIO_MODE | _M_P13_GPIO_MODE | \
                    _M_P14_GPIO_MODE | _M_P15_GPIO_MODE | _M_P16_GPIO_MODE | _M_P17_GPIO_MODE | \
                    _M_P18_GPIO_MODE | _M_P19_GPIO_MODE | _M_P20_GPIO_MODE | _M_P21_GPIO_MODE | \
                    _M_P22_GPIO_MODE | _M_P23_GPIO_MODE | _M_P24_GPIO_MODE | _M_P25_GPIO_MODE | \
                    _M_P26_GPIO_MODE | _M_P27_GPIO_MODE | _M_P28_GPIO_MODE | _M_P29_GPIO_MODE | \
                    _M_P30_GPIO_MODE | _M_P31_GPIO_MODE)
#define _M_FORCE_GPIO_32 ( \
                    _M_P32_GPIO_MODE | _M_P33_GPIO_MODE | _M_P34_GPIO_MODE | _M_P35_GPIO_MODE | \
                    _M_P36_GPIO_MODE | _M_P37_GPIO_MODE)
#else
    #error PIN CONFIG ALT ERROR!
#endif

#if defined(M_CUSTOM_PWM0_PIN)
#define _M_CUSTOM_PWM0_PIN (1<<M_CUSTOM_PWM0_PIN)
#else
#define _M_CUSTOM_PWM0_PIN (0)
#endif
#if defined(M_CUSTOM_PWM1_PIN)
#define _M_CUSTOM_PWM1_PIN (1<<M_CUSTOM_PWM1_PIN)
#else
#define _M_CUSTOM_PWM1_PIN (0)
#endif
#if defined(M_CUSTOM_PWM2_PIN)
#define _M_CUSTOM_PWM2_PIN (1<<M_CUSTOM_PWM2_PIN)
#else
#define _M_CUSTOM_PWM2_PIN (0)
#endif
#if defined(M_CUSTOM_PWM3_PIN)
#define _M_CUSTOM_PWM3_PIN (1<<M_CUSTOM_PWM3_PIN)
#else
#define _M_CUSTOM_PWM3_PIN (0)
#endif
#if defined(M_CUSTOM_PWM4_PIN)
#define _M_CUSTOM_PWM4_PIN (1<<M_CUSTOM_PWM4_PIN)
#else
#define _M_CUSTOM_PWM4_PIN (0)
#endif
#if defined(M_CUSTOM_PWM5_PIN)
#define _M_CUSTOM_PWM5_PIN (1<<M_CUSTOM_PWM5_PIN)
#else
#define _M_CUSTOM_PWM5_PIN (0)
#endif
#if defined(M_CUSTOM_PWM6_PIN)
#define _M_CUSTOM_PWM6_PIN (1<<M_CUSTOM_PWM6_PIN)
#else
#define _M_CUSTOM_PWM6_PIN (0)
#endif
#if defined(M_CUSTOM_PWM7_PIN)
#define _M_CUSTOM_PWM7_PIN (1<<M_CUSTOM_PWM7_PIN)
#else
#define _M_CUSTOM_PWM7_PIN (0)
#endif
//for gpio 32~37 pwm setting------------------------------------
#if defined(M_CUSTOM_PWM0_32_PIN)
#define _M_CUSTOM_PWM0_32_PIN (1<<M_CUSTOM_PWM0_32_PIN)
#else
#define _M_CUSTOM_PWM0_32_PIN (0)
#endif
#if defined(M_CUSTOM_PWM1_32_PIN)
#define _M_CUSTOM_PWM1_32_PIN (1<<M_CUSTOM_PWM1_32_PIN)
#else
#define _M_CUSTOM_PWM1_32_PIN (0)
#endif
#if defined(M_CUSTOM_PWM2_32_PIN)
#define _M_CUSTOM_PWM2_32_PIN (1<<M_CUSTOM_PWM2_32_PIN)
#else
#define _M_CUSTOM_PWM2_32_PIN (0)
#endif
#if defined(M_CUSTOM_PWM3_32_PIN)
#define _M_CUSTOM_PWM3_32_PIN (1<<M_CUSTOM_PWM3_32_PIN)
#else
#define _M_CUSTOM_PWM3_32_PIN (0)
#endif
#if defined(M_CUSTOM_PWM4_32_PIN)
#define _M_CUSTOM_PWM4_32_PIN (1<<M_CUSTOM_PWM4_32_PIN)
#else
#define _M_CUSTOM_PWM4_32_PIN (0)
#endif
#if defined(M_CUSTOM_PWM5_32_PIN)
#define _M_CUSTOM_PWM5_32_PIN (1<<M_CUSTOM_PWM5_32_PIN)
#else
#define _M_CUSTOM_PWM5_32_PIN (0)
#endif
#if defined(M_CUSTOM_PWM6_32_PIN)
#define _M_CUSTOM_PWM6_32_PIN (1<<M_CUSTOM_PWM6_32_PIN)
#else
#define _M_CUSTOM_PWM6_32_PIN (0)
#endif
#if defined(M_CUSTOM_PWM7_32_PIN)
#define _M_CUSTOM_PWM7_32_PIN (1<<M_CUSTOM_PWM7_32_PIN)
#else
#define _M_CUSTOM_PWM7_32_PIN (0)
#endif

#define _M_SPECIFY_IO       ( \
        (_M_CUSTOM_PWM0_PIN) | \
        (_M_CUSTOM_PWM1_PIN) | \
        (_M_CUSTOM_PWM2_PIN) | \
        (_M_CUSTOM_PWM3_PIN) | \
        (_M_CUSTOM_PWM4_PIN) | \
        (_M_CUSTOM_PWM5_PIN) | \
        (_M_CUSTOM_PWM6_PIN) | \
        (_M_CUSTOM_PWM7_PIN) \
	)

#define _M_SPECIFY_IO_32       ( \
        (_M_CUSTOM_PWM0_32_PIN) | \
        (_M_CUSTOM_PWM1_32_PIN) | \
        (_M_CUSTOM_PWM2_32_PIN) | \
        (_M_CUSTOM_PWM3_32_PIN) | \
        (_M_CUSTOM_PWM4_32_PIN) | \
        (_M_CUSTOM_PWM5_32_PIN) | \
        (_M_CUSTOM_PWM6_32_PIN) | \
        (_M_CUSTOM_PWM7_32_PIN) \
	)

#endif /* end of include guard: CUSTOM_IO_CHK_H */
