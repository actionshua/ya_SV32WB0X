
#ifndef _YA_LIGHT_EXAMPLE_H_

#define _YA_LIGHT_EXAMPLE_H_

#define LIGHT_CLOUD				 UNKNOWN_CLOUD_TYPE   

#define MCU_LIGHT_VERSION			""

//  0: C and W controled by one PWM   
//  1: C and W are controlled by PWM individually 
//  2: C and W are controlled by RGB

#define CW_PWM     				1//0:C and W controled by one PWM   1:C and W are controlled by PWM individually
 
#define LIGHT_TYPE				0//0:5 PWM (R,G,B,C,W)   1:2 PWM (C,W)

#if (LIGHT_TYPE == 0)
#define TEST_WIFI_LIGHT_VERSION			"SV.light.ys5.018"
#else
#define TEST_WIFI_LIGHT_VERSION			"SV.light.ys2.018"
#endif

#define FLOAT_SUPPORT				1//0:not support float  1:support float

#define MIN_BRIGHT_PERCENT		5

#define YA_LIGHT_FLASH_PARA_ADDR  (0x25000 - 0x2000)//RAW User

#define YA_LIGHT_DATA_ADDR 	  	  (YA_LIGHT_FLASH_PARA_ADDR + 0x1000)

#endif


