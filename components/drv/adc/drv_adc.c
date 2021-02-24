#include <stdio.h>
#include "soc_defs.h"

#include "drv_adc.h"

#include "drv_pwm.h"

#define ADC_SAMPLE_CNT 16           ///< ADC code average count

static uint8_t drv_adc_initialized = 0;
int8_t drv_adc_init (ADC_EXT_VOLTAGE_GPIO pin) 
{
    if(drv_adc_initialized == 1)
        return -2;
        
    if(pin > ADC_EXT_VOLTAGE_GPIO_GPIO34)
    {
        return -1;
    }

    hal_adc_init(pin);
    drv_adc_initialized = 1;

    return 0;
}

int8_t drv_adc_deinit (ADC_EXT_VOLTAGE_GPIO pin)
{
    if(drv_adc_initialized == 0)
        return -2;
        
    if(pin > ADC_EXT_VOLTAGE_GPIO_GPIO34)
    {
        return -1;
    }    
    
    hal_adc_deinit(pin);
    drv_adc_initialized = 0;
    
    return 0;
}

int8_t drv_adc_read (uint16_t *value)
{
    if(value == 0)
    {
        return -1;
    }
        

    uint8_t i;
    uint32_t sarcode = 0;
    uint32_t reg_cfg = 0;

    uint32_t adc_raw[ADC_SAMPLE_CNT] = {0};
    //FIFO Reset
    hal_adc_fifo_rst();
    
    //IOTADC Enable
    //hal_adc_enable();
    
    for (i = 0 ; i < ADC_SAMPLE_CNT ; )
    {
        uint32_t value = hal_adc_fifo_read();
        if( (value&0xF000) != 0xF000  )
        {
            adc_raw[i] = value;
            i++;
        }
    }    

    sarcode = 0;
    for(i=0; i<ADC_SAMPLE_CNT; i++)
    {
        sarcode += (adc_raw[i]& 0xFFF);
    }
    
    *value = (sarcode/ADC_SAMPLE_CNT);
    

    return 0;
}

int8_t drv_adc_read_ex(uint8_t ch, uint16_t *value)
{
    uint32_t adc_value=0xF000;   
    if(value == 0)
    {
        return -1;
    }     
    //clear register
    hal_adc_pipe_read(ch);
  
    while( (adc_value & 0xF000) == 0xF000  )
    {
        adc_value = hal_adc_pipe_read(ch);
    }

    *value = adc_value&0xFFF;
    

    return 0;
}

#define ADC_FIFO_THRESHOLD (0x3)  
#define ADC_FIFO_THRESHOLD_SIZE (16)    

void drv_adc_isr (uint32_t irq_num)
{
    uint32_t sum = 0;
    uint16_t adc_raw[ADC_FIFO_THRESHOLD_SIZE] = {0};
    int i;
    
    for(i=0;i<ADC_FIFO_THRESHOLD_SIZE;i++)
    {
        adc_raw[i] = hal_adc_fifo_read();
    }

    hal_adc_disable();
    intc_irq_disable(IRQ_ADC);

     for(i=0;i<ADC_FIFO_THRESHOLD_SIZE;i++)
    {
        sum += (adc_raw[i]& 0xFFF);
        printf("%x\n", adc_raw[i]);
    }

    printf("adc value = %d\n", sum/ADC_FIFO_THRESHOLD_SIZE );
}

int8_t drv_adc_read_temp(uint16_t *temp_code)
{
    hal_adc_enable_tmp(1);
    drv_adc_read(temp_code);
    hal_adc_enable_tmp(0);

    return 0;
}

int8_t drv_adc_read_vdd(uint16_t *vdd_code)
{
    hal_adc_enable_vdd(1);
    drv_adc_read(vdd_code);
    hal_adc_enable_vdd(0);

    return 0;
}

int8_t drv_adc_enable_isr()
{
    hal_adc_fifo_ctrl(ADC_FIFO_THRESHOLD);    
    intc_irq_enable(IRQ_ADC);
    intc_register_isr (IRQ_ADC , drv_adc_isr);

    hal_adc_enable();   
    return 0;
    
}
int8_t drv_adc_disable_isr(void)
{
    intc_irq_disable(IRQ_ADC);
    intc_register_isr (IRQ_ADC , NULL);
    return 0;
}
void drv_adc_enable()
{
    return hal_adc_enable();
}
void drv_adc_disable()
{
    return hal_adc_disable();
}

int8_t drv_adc_set_vref(ADC_VREF_TYPE vref_type)
{
    hal_adc_set_vref(vref_type);
    return 0;
}
void drv_adc_ctrl_ext_ch(uint8_t ch_mask)
{
    return hal_adc_ctrl_ext_ch(ch_mask);
}

void drv_adc_fifo_ctrl(uint8_t threshold)
{
    return hal_adc_fifo_ctrl(threshold);
}
void drv_adc_fifo_rst()
{
    return hal_adc_fifo_rst();
}

//6020C
void drv_adc_ch_sel_pipe(uint8_t pipe, uint8_t ch)
{
    return hal_adc_ch_sel_pipe(pipe, ch);
}
void drv_adc_triggle_signal_sel(uint8_t pipe, uint8_t signal)
{
    return hal_adc_triggle_signal_sel(pipe, signal);
}
void drv_adc_latch(uint8_t pipe)
{
    return hal_adc_latch(pipe);
}
void drv_adc_trigger_event_en(uint8_t pipe, uint8_t event)
{
    return hal_adc_trigger_event_en(pipe, event);
}
void drv_adc_decimate(uint8_t pipe, uint8_t decimate)
{
    return hal_adc_decimate(pipe, decimate);
}
void drv_adc_delay(uint8_t pipe, uint8_t delay)
{
    return hal_adc_delay(pipe, delay);
}
void drv_adc_forget_factor(uint8_t pipe, uint8_t factor)
{
    return hal_adc_forget_factor(pipe, factor);
}
void drv_adc_latch_threshold(uint8_t pipe, uint8_t geq, uint32_t threshold)
{
    return hal_adc_latch_threshold(pipe, geq, threshold);
}
void drv_adc_pipe_irq(uint8_t pipe, uint8_t enable)
{
    return hal_adc_pipe_irq(pipe, enable);
}
void drv_adc_fifo_src_switch(uint8_t pipe, uint8_t to_fifo)
{
    return hal_adc_fifo_src_switch(pipe, to_fifo);
}
uint32_t drv_adc_pipe_read(uint8_t pipe)
{
    return hal_adc_pipe_read(pipe);
}


/////////////////here is for adc audio driver test code 
#define ADC_PWM HAL_PWM_6
static adc_audio_buffer *sg_adc_audio_buffer = NULL;
uint16_t g_sample_offset = 0;


void drv_adc_audio_isr(uint32_t irq_num)
{
    int i;
    
    int32_t buf_num = sg_adc_audio_buffer->use_buf_num;
    int32_t now = sg_adc_audio_buffer->pingpong_idx;
    int32_t next = (now + 1) % buf_num;
    struct _adc_audio_buffer_st* buff = &sg_adc_audio_buffer->ping_pong[now];
    
    if(sg_adc_audio_buffer->ping_pong[now].data_ready == 0) 
    {
        for(i=0; i<16; i++)
        {
            buff->buffer[buff->buffer_idx++] = (( (hal_adc_fifo_read()&0xfff) - g_sample_offset) << 4);
        }
    }
    if(buff->buffer_idx >= buff->buffer_len)
    {
        sg_adc_audio_buffer->ping_pong[now].data_ready = 1;
        sg_adc_audio_buffer->pingpong_idx = next;  
    }
    
}

int drv_adc_audio_init(ADC_EXT_VOLTAGE_GPIO audio_ch, uint32_t offset)
{
    g_sample_offset = offset;
   
    //set irq 
    intc_irq_enable(IRQ_ADC);
    intc_register_isr (IRQ_ADC , drv_adc_audio_isr);

    //set adc ctrl    
    drv_adc_init(audio_ch);

    drv_adc_fifo_ctrl(ADC_FIFO_TH_16);   
    drv_adc_set_vref(ADC_VREF_BATTERY);    

    drv_adc_triggle_signal_sel(audio_ch, ADC_SIGNAL_PWM_6); //use PWM 6 triggle 
    drv_adc_trigger_event_en(audio_ch, ADC_TRIGGLE_RISING); //trigger event set pwm rasing edge

    drv_adc_fifo_rst();

    drv_adc_enable();

    
    return 0;
}

int drv_adc_audio_set_buffer(adc_audio_buffer *adc_buffer)
{
    if(adc_buffer != NULL)
        sg_adc_audio_buffer = adc_buffer;
    else 
        return -1;
    
    return 0;
}

int drv_adc_audio_start(uint32_t sample_rate)
{
    uint32_t pwm_clk = sample_rate;  //16KHz
    drv_pwm_init(ADC_PWM);
    drv_pwm_config(ADC_PWM, pwm_clk, 2048, 0);
    drv_pwm_enable(ADC_PWM);
    return 0;
}

int drv_adc_audio_stop()
{
    drv_pwm_disable(0);

    return 0;
}
int drv_adc_audio_deinit()
{
    intc_irq_disable(IRQ_ADC);
    drv_adc_disable();

    return 0;
}
