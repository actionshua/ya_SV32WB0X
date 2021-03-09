#ifndef __DRV_TOUCH_H__
#define __DRV_TOUCH_H__

#include <hal_touch.h>
#include <drv_touch.h>

typedef enum {
    TOUCH_0 = 0x0,
    TOUCH_1 = 0x1,
    TOUCH_2 = 0x2,
    TOUCH_3 = 0x3,
    TOUCH_4 = 0x4,
    TOUCH_5 = 0x5,
    TOUCH_6 = 0x6,
    TOUCH_MAX = 0x7,
} touch_id;
/*
typedef enum {
    touch_0_threshold = 1210,
    touch_1_threshold = 1109,
    touch_2_threshold = 1061,
    touch_3_threshold = 1157,
    touch_4_threshold = 2100,
    touch_5_threshold = 2100,
    touch_6_threshold = 2100,
} touch_threshold;
*/
uint32_t drv_touch_init(uint32_t touch_id,uint32_t pin);
uint32_t drv_touch_deinit(uint32_t touch_id,uint32_t pin);
uint32_t drv_touch_clear(void);
uint32_t drv_touch_src_config(void);
uint32_t drv_touch_enable(void);
uint32_t drv_touch_disable(void);
uint32_t drv_touch_query_raw(uint32_t touch_id);
/*
uint32_t drv_touch_threshold (uint32_t touch_id, uint32_t threshold);

uint32_t drv_touch_pulse_src_config(void);
uint32_t drv_touch_pulse_src_disable(void);
uint32_t drv_touch_pulse_src_enable(void);
int8_t drv_touch_0_config(uint8_t pin);
int8_t drv_touch_1_config(uint8_t pin);
int8_t drv_touch_2_config(uint8_t pin);
int8_t drv_touch_3_config(uint8_t pin);
int8_t drv_touch_4_config(uint8_t pin);
int8_t drv_touch_5_config(uint8_t pin);
int8_t drv_touch_6_config(uint8_t pin);
int8_t drv_touch_all_timer_reset(void);
int8_t drv_touch_pulse_src_counter_reset(void);
int8_t drv_touch_pulse_src_counter_config(void);
int16_t drv_touch_all_ctmr_ebable(void);
int16_t drv_touch_query_timer_0();
int16_t drv_touch_query_timer_1();
int16_t drv_touch_query_timer_2();
int16_t drv_touch_query_timer_3();
int16_t drv_touch_query_timer_4();
int16_t drv_touch_query_timer_5();
int16_t drv_touch_query_timer_6();
*/
#endif

