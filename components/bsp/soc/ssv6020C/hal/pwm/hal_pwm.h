#ifndef __HAL_PWM_H__
#define __HAL_PWM_H__

#include "soc_defs.h"

#define M_PWM_DUTY_IN_FREQ_LOW_PRECISE      (80)
#define M_PWM_DUTY_IN_FREQ_HIGH_PRECISE     (20)
#define M_PWM_DUTY_STEP                                     (1 << 12) 

typedef enum {
    HAL_PWM_0 = 0x0,
    HAL_PWM_1 = 0x1,
    HAL_PWM_2 = 0x2,
    HAL_PWM_3 = 0x3,
    HAL_PWM_4 = 0x4,
    HAL_PWM_5 = 0x5,
    HAL_PWM_6 = 0x6,
    HAL_PWM_7 = 0x7,
} hal_pwm_port;

#if defined(CONFIG_OS_RHINO)
int8_t _hal_pwm_init(uint8_t pwm_id);
#else
int8_t hal_pwm_init(uint8_t pwm_id);
#endif
int8_t hal_pwm_deinit(void);
int8_t hal_pwm_config(uint8_t pwm_id, uint32_t freq_hz, uint32_t duty, uint8_t is_invert);
int8_t hal_pwm_enable(uint8_t pwm_id);
int8_t hal_pwm_disable(uint8_t pwm_id);
int8_t hal_pwm_enable_all(void);

void hal_pwm_set_pscaler(uint8_t pwm_id, uint32_t pscaler);
void hal_pwm_set_period(uint8_t pwm_id, uint32_t period);
void hal_pwm_set_high_duty(uint8_t pwm_id, uint32_t period);

uint32_t hal_pwm_get_pscaler(uint8_t pwm_id);
uint32_t hal_pwm_get_period(uint8_t pwm_id);
uint32_t hal_pwm_get_high_duty(uint8_t pwm_id);
#endif
