#ifndef _DRV_ADC_H_
#define _DRV_ADC_H_
#include <stdint.h>

#include "hal_adc.h"

#include "custom_io_hal.h"
#include "custom_io_chk.h"


//# adc convert formula : -0.9792*code +1014
#define ADC_CONVERT_SLOPE   9792
#define ADC_CONVERT_OFFSET  10140000

/**
 * Initialize the ADC hardware.
 * @param  pin                      Initialize with that ADC pin.
 * @retval   0                      Initialize success.
 * @retval  -1                      The ADC pin is unavailable.
 */

int8_t drv_adc_init (ADC_EXT_VOLTAGE_GPIO pin);

/**
 * Deinitialize the ADC hardware.
 * @param  pin                      Deinitialize with that ADC pin.
 * @retval   0                      Deinitialize success.
 * @retval  -1                      The ADC pin is unavailable.
 */

int8_t drv_adc_deinit (ADC_EXT_VOLTAGE_GPIO pin);

/**
 * Read out the ADC value(10bit).
 * @param  value                    Pointer to the value to store the adc code from ADC pin.
 * @retval   0                      ADC read out success. 
 * @retval  -1                      The pointer to the value is unavailable. 
 */

int8_t drv_adc_read (uint16_t *value);
int8_t drv_adc_read_ex(uint8_t ch, uint16_t *value);

#if 1 //CHIP = 6020
int8_t drv_adc_read_temp(uint16_t *temp_code);
int8_t drv_adc_read_vdd(uint16_t *vdd_code);
int8_t drv_adc_enable_isr(void);
int8_t drv_adc_disable_isr(void);
void drv_adc_enable();
void drv_adc_disable();
int8_t drv_adc_set_vref(ADC_VREF_TYPE vref_type);
void drv_adc_ctrl_ext_ch(uint8_t ch_mask);
void drv_adc_fifo_ctrl(uint8_t threshold);
void drv_adc_fifo_rst();
#endif

//6020C
void drv_adc_ch_sel_pipe(uint8_t pipe, uint8_t ch);
void drv_adc_triggle_signal_sel(uint8_t pipe, uint8_t signal);
void drv_adc_latch(uint8_t pipe);
void drv_adc_trigger_event_en(uint8_t pipe, uint8_t event);
void drv_adc_decimate(uint8_t pipe, uint8_t decimate);
void drv_adc_delay(uint8_t pipe, uint8_t delay);
void drv_adc_forget_factor(uint8_t pipe, uint8_t factor);
void drv_adc_latch_threshold(uint8_t pipe, uint8_t geq, uint32_t threshold);
void drv_adc_pipe_irq(uint8_t pipe, uint8_t enable);
void drv_adc_fifo_src_switch(uint8_t pipe, uint8_t to_fifo);
uint32_t drv_adc_pipe_read(uint8_t pipe);

// support padmux checking feature.
#define DRV_ADC_INIT_HAL_ADC_0() \
    do { \
        drv_adc_init(HAL_ADC_0); \
        (void)PERI_IO_ADC0; \
    } while(0)
#define DRV_ADC_INIT_HAL_ADC_1() \
    do { \
        drv_adc_init(HAL_ADC_1); \
        (void)PERI_IO_ADC1; \
    } while(0)

#define DRV_ADC_INIT_HAL_ADC_2() \
    do { \
        drv_adc_init(HAL_ADC_2); \
        (void)PERI_IO_ADC2; \
    } while(0)

#define DRV_ADC_INIT_HAL_ADC_3() \
    do { \
        drv_adc_init(HAL_ADC_3); \
        (void)PERI_IO_ADC3; \
    } while(0)

#define DRV_ADC_INIT_HAL_ADC_4() \
    do { \
        drv_adc_init(HAL_ADC_4); \
        (void)PERI_IO_ADC4; \
    } while(0)

#define DRV_ADC_INIT_HAL_ADC_5() \
    do { \
        drv_adc_init(HAL_ADC_5); \
        (void)PERI_IO_ADC5; \
    } while(0)

#define DRV_ADC_INIT_HAL_ADC_6() \
    do { \
        drv_adc_init(HAL_ADC_6); \
        (void)PERI_IO_ADC6; \
    } while(0)

#define DRV_ADC_INIT_HAL_ADC_7() \
    do { \
        drv_adc_init(HAL_ADC_7); \
        (void)PERI_IO_ADC7; \
    } while(0)

#define DRV_ADC_INIT(ADC) \
    DRV_ADC_INIT_##ADC();


////// here is for adc audio test code

#define MAX_ADC_AUDIO_BUF_NUM 2

struct _adc_audio_buffer_st 
{
    uint16_t buffer_idx;                
    uint16_t buffer_len;               
    uint16_t* buffer;                  
    volatile uint8_t data_ready;        
};

typedef struct 
{
    uint8_t pingpong_idx;              
    struct _adc_audio_buffer_st ping_pong[MAX_ADC_AUDIO_BUF_NUM]; 
    uint32_t use_buf_num;
} adc_audio_buffer;

int drv_adc_audio_init(ADC_EXT_VOLTAGE_GPIO audio_ch, uint32_t offset);
int drv_adc_audio_set_buffer(adc_audio_buffer *adc_buffer);
int drv_adc_audio_start(uint32_t sample_rate);
int drv_adc_audio_stop();
int drv_adc_audio_deinit();

#endif
