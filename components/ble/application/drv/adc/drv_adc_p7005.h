#ifndef _DRV_ADC_H_
#define _DRV_ADC_H_

#include <stdint.h>

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

typedef enum {
    ADC_CONFIG_TYPE_TEMP = 0,
    ADC_CONFIG_TYPE_EXTERNAL_VOL_LEVEL0,
    ADC_CONFIG_TYPE_EXTERNAL_VOL_LEVEL1,
    ADC_CONFIG_TYPE_BATTERY_VOL,
}ADC_CONFIG_TYPE;

 
#define ADC_MEASURE_STATE    0x0000000f

typedef struct{
    u8 type;
    u8 io;
    u8 scaling;
}adc_param_st;

typedef void(*pf_user_adc)(uint8_t);
typedef void(*pf_drv_adc)(uint8_t);

extern pf_drv_adc g_drv_adc_cb ;
uint8_t adc_value_read(pf_drv_adc cb , uint8_t * value , adc_param_st * param);
int32_t adc_code2val(uint8_t type , uint8_t adc_code);

 
int8_t drv_phy_adc_map_rssi(uint8_t adc_val);
void drv_adc_enable_air_event_notify(uint8_t enable);
int8_t user_drv_adc_value_read(uint8_t * value, adc_param_st *param);


#endif
