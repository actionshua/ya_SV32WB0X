#ifndef __ADCBAT_PARAM_H__
#define __ADCBAT_PARAM_H__

#include "drv_adcbat.h"
#include "hal_adc.h"

#define V_RFE_ADC               3.6 //unit: V
#define V_BAT_MAX               4.2 //unit: V
#define V_BAT_MIN               3.2 //unit: V
#define R_TOP                   220 //R_TOP and R_BOTTOM must be same unit. (note: 7.5k ohm by SZ circuit)
#define R_BOTTOM                680 //R_TOP and R_BOTTOM must be same unit. (note: 24k ohm by SZ circuit)

#endif
