#ifndef _ATCMD_GPIO_H_
#define _ATCMD_GPIO_H_
#include "atcmd.h"
#include "error.h"

int At_SetGpioTriState (stParam *param);
int At_SetGpioDir (stParam *param);
int At_SetGpioLogic (stParam *param);
int At_SetGpioPull (stParam *param);
int At_ReadGpio (stParam *param);
int At_SetGpioInt (stParam *param);
int At_SetPWM (stParam *param);
int At_SetPWMDisable (stParam *param);
int At_SetPWMEnable (stParam *param);
int At_SetPWMReconfig (stParam *param);



#endif  //_ATCMD_GPIO_H_