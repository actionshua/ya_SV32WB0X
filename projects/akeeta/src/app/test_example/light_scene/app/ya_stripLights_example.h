

#ifndef _YA_STRIPLIGHTS_EXAMPLE_H_
#define _YA_STRIPLIGHTS_EXAMPLE_H_


#define STRIPLIGHT_CLOUD				 UNKNOWN_CLOUD_TYPE   

#define TEST_WIFI_STRIPLIGHT_VERSION	"yg.light.001.001"

#define MCU_STRIPLIGHT_VERSION			""

//  0: C and W controled by one PWM   
//  1: C and W are controlled by PWM individually 
//  2: C and W are controlled by RGB
#define CW_PWM         1  

#define LIGHT_TYPE		0//0:5 PWM (R,G,B,C,W)   1:2 PWM (C,W)

#define FLOAT_SUPPORT	1//0:not support float  1:support float

#define MIN_BRIGHT_PERCENT	5

//flash
#define YA_LIGHT_FLASH_PARA_ADDR  (0x25000 - 0x2000)//RAW User
#define YA_STRILIGHTLIGHT_FLASH_PARA_ADDR 	  	  (YA_LIGHT_FLASH_PARA_ADDR + 0x1000)

#endif


