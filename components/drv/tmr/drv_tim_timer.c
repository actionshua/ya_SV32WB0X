#include "drv_tim_timer.h"
#include <hal_tmr.h>
#include <sys_clock.h>
#include <sys/intc.h>
#include <soc_defs.h>
#include <attrs.h>

#define M_TIM_TIMER             (TM_TU3_US)
void drv_tim_timer_init() {
    hal_tm_init(M_TIM_TIMER);
}

void drv_tim_timer_register_irq_handler(isr_func local_tm_irq) {
    hal_tm_register_irq_handler(M_TIM_TIMER, local_tm_irq);
    intc_irq_set_priority(IRQ_UTIMER_0+M_TIM_TIMER, HIGH);
}

void drv_tim_timer_enable(int time) ATTRIBUTE_SECTION_FBOOT;
void drv_tim_timer_enable(int time) {
#if (CHIP_ID == 6006)
    if (time > 65535) {
        int prescale = 0;
        int bus = (sys_bus_clock()/1000000);
        prescale = (int)(((float)time)/65536 * bus) + 1;
        time = (time*bus)/prescale;
        hal_tm_prescale_enable(M_TIM_TIMER, prescale, time);
    } else {
        hal_tm_enable(M_TIM_TIMER, TM_MODE_ONE_SHOT, time);
    }
#else
    hal_tm_enable(M_TIM_TIMER, TM_MODE_ONE_SHOT, time);
#endif
}

void drv_tim_timer_disable() {
    hal_tm_disable(M_TIM_TIMER);
}

void drv_tim_timer_clear_isr() ATTRIBUTE_SECTION_FBOOT;
void drv_tim_timer_clear_isr() {
    hal_tm_clear_int_sts (M_TIM_TIMER);
}

