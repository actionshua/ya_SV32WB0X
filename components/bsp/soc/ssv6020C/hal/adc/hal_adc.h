#ifndef _HAL_ADC_H_
#define _HAL_ADC_H_

#include "sys/intc.h"   // components/

typedef enum{
    ADC_EXT_VOLTAGE_GPIO_GPIO00 = 0,
    ADC_EXT_VOLTAGE_GPIO_GPIO01 = 1,
    ADC_EXT_VOLTAGE_GPIO_GPIO02 = 2,
    ADC_EXT_VOLTAGE_GPIO_GPIO30 = 3,
    ADC_EXT_VOLTAGE_GPIO_GPIO31 = 4,
    ADC_EXT_VOLTAGE_GPIO_GPIO32 = 5,
    ADC_EXT_VOLTAGE_GPIO_GPIO33 = 6,
    ADC_EXT_VOLTAGE_GPIO_GPIO34 = 7,
    HAL_ADC_0                   = 0,
    HAL_ADC_1                   = 1,
    HAL_ADC_2                   = 2,
    HAL_ADC_3                   = 3,
    HAL_ADC_4                   = 4,
    HAL_ADC_5                   = 5,
    HAL_ADC_6                   = 6,
    HAL_ADC_7                   = 7,
    HAL_ADC_MAX                 = HAL_ADC_7,
}ADC_EXT_VOLTAGE_GPIO;


typedef enum{
    ADC_VREF_1_8 = 0,
    ADC_VREF_3_6 = 1,
    ADC_VREF_BATTERY = 2
}ADC_VREF_TYPE;

typedef enum{
    ADC_FIFO_TH_1 = 0,  
    ADC_FIFO_TH_4 = 1,    
    ADC_FIFO_TH_8 = 2,
    ADC_FIFO_TH_16 = 3,
    ADC_FIFO_TH_28 = 4,   
} ADC_FIFO_TH;

typedef enum{
    ADC_SIGNAL_GPIO_0 = 0,
    ADC_SIGNAL_GPIO_1 = 1,
    ADC_SIGNAL_GPIO_2 = 2, 
    ADC_SIGNAL_GPIO_3 = 3,
    ADC_SIGNAL_GPIO_4 = 4,
    ADC_SIGNAL_GPIO_5 = 5,
    ADC_SIGNAL_GPIO_6 = 6, 
    
    ADC_SIGNAL_GPIO_13 = 13,
    ADC_SIGNAL_GPIO_14 = 14,
    ADC_SIGNAL_GPIO_15 = 15,
    ADC_SIGNAL_GPIO_16 = 16, 
    ADC_SIGNAL_GPIO_17 = 17,
    ADC_SIGNAL_GPIO_18 = 18,
    ADC_SIGNAL_GPIO_19 = 19,
    ADC_SIGNAL_GPIO_20 = 20, 
    ADC_SIGNAL_GPIO_21 = 21,
    ADC_SIGNAL_GPIO_22 = 22,
    ADC_SIGNAL_GPIO_23 = 23,
    ADC_SIGNAL_GPIO_24 = 24, 
    ADC_SIGNAL_GPIO_25 = 25,
    ADC_SIGNAL_GPIO_26 = 26,
    ADC_SIGNAL_GPIO_27 = 27,
    ADC_SIGNAL_GPIO_28 = 28, 
    ADC_SIGNAL_GPIO_29 = 29,
    ADC_SIGNAL_GPIO_30 = 30,
    ADC_SIGNAL_GPIO_31 = 31,
    ADC_SIGNAL_GPIO_32 = 32,
    ADC_SIGNAL_GPIO_33 = 33, 
    ADC_SIGNAL_GPIO_34 = 34,
    ADC_SIGNAL_GPIO_35 = 35,
    ADC_SIGNAL_GPIO_36 = 36,
    ADC_SIGNAL_GPIO_37 = 37, 
    
    ADC_SIGNAL_PWM_0 = 48,
    ADC_SIGNAL_PWM_1 = 49,
    ADC_SIGNAL_PWM_2 = 50,
    ADC_SIGNAL_PWM_3 = 51, 
    ADC_SIGNAL_PWM_4 = 52,
    ADC_SIGNAL_PWM_5 = 53,
    ADC_SIGNAL_PWM_6 = 54,
    ADC_SIGNAL_PWM_7 = 55
    
}ADC_SIGNAL_SOURCE;

typedef enum{
    ADC_TRIGGLE_RISING = 1<<0,
    ADC_TRIGGLE_FALLING = 1<<1,
    ADC_TRIGGLE_WRITE_KICK = 1<<2,
    ADC_TRIGGLE_AUTO = 1<<3,    
    ADC_TRIGGLE_MS_TIMER2 = 1<<4,
    ADC_TRIGGLE_MS_TIMER3 = 1<<5,
    ADC_TRIGGLE_US_TIMER2 = 1<<6,
    ADC_TRIGGLE_US_TIMER3 = 1<<7
}ADC_TRIGGLE_EVENT;

void hal_adc_init (uint8_t aio_source);
void hal_adc_deinit (uint8_t aio_source);
uint32_t hal_adc_fifo_read (void);

//6020B
void hal_adc_add_ch(uint8_t ch);
void hal_adc_ctrl_ext_ch(uint8_t ch_mask);
void hal_adc_enable_tmp(uint8_t enable);
void hal_adc_enable_vdd(uint8_t enable);
void hal_adc_enable();
void hal_adc_disable();
void hal_adc_ctrl_clk(uint8_t clk);
void hal_adc_fifo_ctrl(uint8_t threshold);
void hal_adc_fifo_rst();
void hal_adc_set_vref(ADC_VREF_TYPE vref_type);

//6020C
void hal_adc_ch_sel_pipe(uint8_t pipe, uint8_t ch);
void hal_adc_triggle_signal_sel(uint8_t pipe, ADC_SIGNAL_SOURCE signal);
void hal_adc_latch(uint8_t pipe);
void hal_adc_trigger_event_en(uint8_t pipe, ADC_TRIGGLE_EVENT event);
void hal_adc_decimate(uint8_t pipe, uint8_t decimate);
void hal_adc_delay(uint8_t pipe, uint8_t delay);
void hal_adc_forget_factor(uint8_t pipe, uint8_t factor);
void hal_adc_latch_threshold(uint8_t pipe, uint8_t geq, uint32_t threshold);
void hal_adc_pipe_irq(uint8_t pipe, uint8_t enable);
void hal_adc_fifo_src_switch(uint8_t pipe, uint8_t to_fifo);
uint32_t hal_adc_pipe_read(uint8_t pipe);



#endif  // #ifndef _HAL_ADC_H_
