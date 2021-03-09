#ifndef __HAL_TOUCH_H__
#define __HAL_TOUCH_H__

#include "soc_defs.h"
#include "sys/intc.h"   // components/

enum {
    g_CTMR_SRC_0_GPI_SEL = 0x0,
    g_CTMR_SRC_1_GPI_SEL = 0x1,
    g_CTMR_SRC_2_GPI_SEL = 0x2,
    g_CTMR_SRC_3_GPI_SEL = 0x3,
    g_CTMR_SRC_4_GPI_SEL = 0x4,
    g_CTMR_SRC_5_GPI_SEL = 0x5,
    g_CTMR_SRC_6_GPI_SEL = 0x6,
    g_CTMR_SRC_7_GPI_SEL = 0x7,
    g_CTMR_SRC_8_GPO_SEL = 0x8,
    g_CTMR_SRC_9_GPO_SEL = 0x9,
    g_PWM_6              = 0xA,
    g_PWM_7              = 0xB,
    g_CTMR_SRC_12_SW     = 0xC,
    g_CTMR_SRC_13_SW     = 0xD,
    g_CTMR_6_IRQ         = 0xE,
    g_CTMR_7_IRQ         = 0xF,
};



int8_t hal_touch_pulse_src_config(uint8_t pwm_id, uint32_t freq_hz, uint32_t input_duty, uint8_t is_invert);
int8_t hal_touch_0_config(uint8_t pin);
int8_t hal_touch_1_config(uint8_t pin);
int8_t hal_touch_2_config(uint8_t pin);
int8_t hal_touch_3_config(uint8_t pin);
int8_t hal_touch_4_config(uint8_t pin);
int8_t hal_touch_5_config(uint8_t pin);
int8_t hal_touch_6_config(uint8_t pin);
int8_t hal_touch_all_timer_reset(void);
int8_t hal_touch_pulse_src_counter_config(void);
int8_t hal_touch_pulse_src_counter_reset(void);
int16_t hal_touch_all_ctmr_enable(void);
int16_t hal_touch_all_ctmr_disable(void);
int16_t hal_touch_query_timer_0(void);
int16_t hal_touch_query_timer_1(void);
int16_t hal_touch_query_timer_2(void);
int16_t hal_touch_query_timer_3(void);
int16_t hal_touch_query_timer_4(void);
int16_t hal_touch_query_timer_5(void);
int16_t hal_touch_query_timer_6(void);


#endif

