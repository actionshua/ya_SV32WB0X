

#ifndef _YA_LIGHT_EXAMPLE_H_
#define _YA_LIGHT_EXAMPLE_H_

#define LIGHT_CLOUD				 UNKNOWN_CLOUD_TYPE   

#define MCU_LIGHT_VERSION			""

//  0: C and W controled by one PWM   
//  1: C and W are controlled by PWM individually 
//  2: C and W are controlled by RGB
#define CW_PWM     		1

#define LIGHT_TYPE		0//0:5 PWM (R,G,B,C,W)   1:2 PWM (C,W)

#define FLOAT_SUPPORT	1//0:not support float  1:support float

#define MIN_BRIGHT_PERCENT		5

#define YA_LIGHT_FLASH_PARA_ADDR  (0x1e0000)

#define YA_LIGHT_DATA_ADDR 	  	  (YA_LIGHT_FLASH_PARA_ADDR + 0x1000)

#if (LIGHT_TYPE == 0) //5pwm
#define TEST_WIFI_LIGHT_VERSION	"bl.light.db5.001"
#else
#define TEST_WIFI_LIGHT_VERSION	"bl.light.db2.001"
#endif


#endif


