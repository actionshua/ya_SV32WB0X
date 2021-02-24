#include <stdio.h>
#include <stdint.h>
#include "hal_pwm.h"
#include "drv_pwm.h"
#include "attrs.h"
#include "osal.h"
#include "soc_defs.h"
#include "soc_types.h"

int8_t drv_pwm_init(uint8_t pwm_id) {

    int8_t ret = 0;
    
#if defined(CONFIG_OS_RHINO)
    ret = _hal_pwm_init(pwm_id);
#else
    ret = hal_pwm_init(pwm_id);
#endif
    
    return ret; 
}


int8_t drv_pwm_deinit(void) {

    int8_t ret = 0;
    
    ret = hal_pwm_deinit();
    
    return ret; 
}

int8_t drv_pwm_config(uint8_t pwm_id, uint32_t freq_hz, uint32_t duty, uint8_t is_invert) {

    int8_t ret = 0;
    
    ret = hal_pwm_config(pwm_id, freq_hz, duty, is_invert);
    
    return ret; 
}

int8_t drv_pwm_enable_all(void) {

    int8_t ret = 0;
    
    ret = hal_pwm_enable_all();
    
    return ret; 
}


int8_t drv_pwm_enable(uint8_t pwm_id) {

    int8_t ret = 0;
    
    ret = hal_pwm_enable(pwm_id);
    
    return ret; 
}

int8_t drv_pwm_disable(uint8_t pwm_id) {

    int8_t ret = 0;
    
    ret = hal_pwm_disable(pwm_id);
    
    return ret; 
}


void drv_pwm_set_logic(uint8_t pwm_id, uint8_t logic)
{
    drv_pwm_config(pwm_id, 20000, 4096, !logic);
    drv_pwm_enable(pwm_id);
}
