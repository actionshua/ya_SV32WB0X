#include <stdio.h>
#include <stdint.h>

#include "attrs.h"
#include "osal.h"
#include "soc_defs.h"
#include "soc_types.h"

#include "hal_touch.h"
#include "drv_touch.h"
#include "hal_pwm.h"
#include "drv_pwm.h"
#include "hal_gpio.h"
#include "drv_gpio.h"


uint32_t drv_touch_init(uint32_t touch_id,uint32_t pin) {

    if (touch_id < TOUCH_MAX)
    {
        if (touch_id == TOUCH_0)
        {
            hal_touch_0_config(pin);
                }
        else if (touch_id == TOUCH_1)
        {
            hal_touch_1_config(pin);
        }
        else if (touch_id == TOUCH_2)
        {
            hal_touch_2_config(pin);
        }
        else if (touch_id == TOUCH_3)
        {
            hal_touch_3_config(pin);
        }
        else if (touch_id == TOUCH_4)
        {
            hal_touch_4_config(pin);
        }
        else if (touch_id == TOUCH_5)
        {
            hal_touch_5_config(pin);
        }
        else if (touch_id == TOUCH_6)
        {
            hal_touch_6_config(pin);
        }  

        //All timer CTMR_0~6 reset, but no include CTMR_7
        hal_touch_all_timer_reset();

        //CTMR_7 counter reset
        hal_touch_pulse_src_counter_reset();
        
        return 0;
    }
    else
    {
        printf("ERROR! The <touch_id> is between TOUCH_0 ~ TOUCH_6.\n");
        return -1;
    }
}

uint32_t drv_touch_deinit(uint32_t touch_id,uint32_t pin) {

    return 0;

}

uint32_t drv_touch_clear(void) {

    //All timer CTMR_0~6 reset, but no include CTMR_7
    hal_touch_all_timer_reset();

    //CTMR_7 counter reset
    hal_touch_pulse_src_counter_reset();
    
    return 0;
}

uint32_t drv_touch_src_config(void) {

    //PWM7 config
    hal_touch_pulse_src_config(HAL_PWM_7,1000,2048,0);

    return 0; 
}

uint32_t drv_touch_enable(void) {

    //CTMR_0~7 timer/counter enable
    hal_touch_all_ctmr_enable();

    //PWM7 config
    //hal_touch_pulse_src_config(HAL_PWM_7,1000,2048,0);

    //PWM7 enable
    hal_pwm_enable(HAL_PWM_7);

    //CTMR_7 counter config
    hal_touch_pulse_src_counter_config();
        
    return 0; 
}

uint32_t drv_touch_disable(void) {

    //PWM7 disable
    hal_pwm_disable(HAL_PWM_7);

    //CTMR_0~7 timer/counter disable
    hal_touch_all_ctmr_disable();
        
    return 0; 
}

uint32_t drv_touch_query_raw(uint32_t touch_id) {

    if (touch_id < TOUCH_MAX)
    {
        if (touch_id == TOUCH_0)
        {
            uint16_t timer_0 = 0x0;
            
            //Query CTMR_0 timer
            timer_0 = hal_touch_query_timer_0();
        
            return timer_0;
        }
        else if (touch_id == TOUCH_1)
        {
            uint16_t timer_1 = 0x0;
        
            //Query CTMR_1 timer
            timer_1 = hal_touch_query_timer_1();
        
            return timer_1;
        }
        else if (touch_id == TOUCH_2)
        {
            uint16_t timer_2 = 0x0;
        
            //Query CTMR_2 timer
            timer_2 = hal_touch_query_timer_2();
        
            return timer_2;
        }
        else if (touch_id == TOUCH_3)
        {
            uint16_t timer_3 = 0x0;
        
            //Query CTMR_3 timer
            timer_3 = hal_touch_query_timer_3();
        
            return timer_3;
        }
        else if (touch_id == TOUCH_4)
        {
            uint16_t timer_4 = 0x0;
        
            //Query CTMR_4 timer
            timer_4 = hal_touch_query_timer_4();
        
            return timer_4;
        }
        else if (touch_id == TOUCH_5)
        {
            uint16_t timer_5 = 0x0;
        
            //Query CTMR_5 timer
            timer_5 = hal_touch_query_timer_5();
        
            return timer_5;
        }
        else if (touch_id == TOUCH_6)
        {
            uint16_t timer_6 = 0x0;
        
            //Query CTMR_6 timer
            timer_6 = hal_touch_query_timer_6();
        
            return timer_6;
        }
        return 0;
    }
    else
    {
        printf("ERROR! The <touch_id> is between TOUCH_0 ~ TOUCH_6.\n");
        return -1;
    }
}

/*---------------------------------------------------------*/
/*
uint32_t drv_touch_threshold (uint32_t touch_id, uint32_t threshold) {

    if (touch_id == TOUCH_0)
    {
        uint16_t timer_0 = 0x0;
    
        //Query CTMR_0 timer
        timer_0 = hal_touch_query_timer_0();
    
        if (timer_0 >= threshold)
        {
            return timer_0;
        }
            
        return 0;
    }
    return 0;
}

uint32_t drv_touch_pulse_src_config(void) {
    
    hal_touch_pulse_src_config(HAL_PWM_7,1000,2048,0);
        
    return 0; 
}

uint32_t drv_touch_pulse_src_disable(void) {
        
    hal_pwm_disable(HAL_PWM_7);
        
    return 0; 
}

uint32_t drv_touch_pulse_src_enable(void) {
        
    hal_pwm_enable(HAL_PWM_7);
        
    return 0; 
}

int8_t drv_touch_pulse_src_counter_reset(void) {
    
    //CTMR_7 counter reset
    hal_touch_pulse_src_counter_reset();
    
    return 0;
}

int8_t drv_touch_pulse_src_counter_config(void)
{
    //CTMR_7 counter config
    hal_touch_pulse_src_counter_config();
    
    return 0;
}

int16_t drv_touch_all_ctmr_ebable(void) {
       
    //CTMR_0~7 timer/counter enable
    hal_touch_all_ctmr_ebable();
    
    return 0;
}

int8_t drv_touch_all_timer_reset(void)
{

    //All timer CTMR_0~6 reset, but no include CTMR_7
    hal_touch_all_timer_reset();
    
    return 0;
}

int16_t drv_touch_query_timer_0(void) {

    uint16_t timer_0 = 0x0;
    
    //Query CTMR_0 timer
    timer_0 = hal_touch_query_timer_0();
    
    return timer_0;
}

int16_t drv_touch_query_timer_1(void) {

    uint16_t timer_1 = 0x0;
    
    //Query CTMR_1 timer
    timer_1 = hal_touch_query_timer_1();
    
    return timer_1;
}

int16_t drv_touch_query_timer_2(void) {

    uint16_t timer_2 = 0x0;
    
    //Query CTMR_2 timer
    timer_2 = hal_touch_query_timer_2();
    
    return timer_2;
}

int16_t drv_touch_query_timer_3(void) {

    uint16_t timer_3 = 0x0;
    
    //Query CTMR_3 timer
    timer_3 = hal_touch_query_timer_3();
    
    return timer_3;
}

int16_t drv_touch_query_timer_4(void) {

    uint16_t timer_4 = 0x0;
    
    //Query CTMR_4 timer
    timer_4 = hal_touch_query_timer_4();
    
    return timer_4;
}

int16_t drv_touch_query_timer_5(void) {

    uint16_t timer_5 = 0x0;
    
    //Query CTMR_5 timer
    timer_5 = hal_touch_query_timer_5();
    
    return timer_5;
}

int16_t drv_touch_query_timer_6(void) {

    uint16_t timer_6 = 0x0;
    
    //Query CTMR_6 timer
    timer_6 = hal_touch_query_timer_6();
    
    return timer_6;
}
*/
