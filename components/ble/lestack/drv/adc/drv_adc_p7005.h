#ifndef _DRV_ADC_H_
#define _DRV_ADC_H_

#include "ssv_types.h"
#include "pcb_config.h"


typedef enum {
    ADC_CONFIG_TYPE_TEMP = 0,
    ADC_CONFIG_TYPE_EXTERNAL_VOL_LEVEL0,
    ADC_CONFIG_TYPE_EXTERNAL_VOL_LEVEL1,
    ADC_CONFIG_TYPE_BATTERY_VOL,
}ADC_CONFIG_TYPE;


typedef enum{
    ADC_EXTV_LEVEL_0 = 0x0,
    ADC_EXTV_LEVEL_1 ,
}ADC_EXTV_LEVEL;

typedef enum{
    ADC_EXTV_AIO_PIN_INT1 = 0,
    ADC_EXTV_AIO_PIN_INT0 = 1,
    ADC_EXTV_AIO_PIN_CMIF0 = 2,
    ADC_EXTV_AIO_PIN_CMIF1 = 3,
}ADC_EXTV_PIN_IO;

typedef struct{
    u8 type;
    u8 io;
    u8 scaling;
}adc_param_st;


void drv_phy_adc_enable_lestack();
void drv_phy_adc_disable_lestack();
s8 drv_phy_adc_map_rssi(u8 adc_val);

s8 drv_adc_value_read(u8 * value , adc_param_st *param);

#endif
