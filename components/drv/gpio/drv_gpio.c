
#include <stdint.h>
#include "drv_gpio.h"
#include "hal_gpio.h"
#include "attrs.h"
#include "osal.h"
#include <stdio.h>

int8_t drv_gpio_set_mode(gpio_pin_t pin, pin_mode_t mode){
    int8_t ret = 0;

    ret = hal_gpio_set_mode(pin, mode);

    return ret;
}


int8_t drv_gpio_set_dir(gpio_pin_t pin, gpio_dir_t dir) {

    int8_t ret = 0;

    ret = hal_gpio_set_dir(pin, dir);

    return ret;
}

gpio_dir_t drv_gpio_get_dir(gpio_pin_t pin) {

    gpio_dir_t ret = 0;

    ret = hal_gpio_get_dir(pin);

    return ret;
}

int8_t drv_gpio_set_pull(gpio_pin_t pin, gpio_pull_t pull) {
    
    int8_t ret = 0;

    ret = hal_gpio_set_pull(pin, pull);

    return ret;
}

gpio_pull_t drv_gpio_get_pull(gpio_pin_t pin) {
    
    gpio_pull_t ret = 0;

    ret = hal_gpio_get_pull(pin);

    return ret;
}


int8_t drv_gpio_set_logic(gpio_pin_t pin, gpio_logic_t logic) {
    
    int8_t ret = 0;

    ret = hal_gpio_set_logic(pin, logic);

    return ret;
}

int8_t drv_gpio_set_driving_strengh(gpio_pin_t pin, gpio_driving_strengh_t driving_streght) {
    
    int8_t ret = 0;

    ret = hal_gpio_set_driving_strengh(pin, driving_streght);

    return ret;
}

gpio_logic_t drv_gpio_get_logic(gpio_pin_t pin) {
    
    gpio_logic_t ret = 0;

    ret = hal_gpio_get_logic(pin);

    return ret;
}

int8_t drv_gpio_intc_trigger_mode(gpio_pin_t pin, gpio_intc_trigger_mode_t mode) {
    
    int8_t ret = 0;

    ret = hal_gpio_intc_trigger_mode(pin, mode);

    return ret;
}

int8_t drv_gpio_register_isr(gpio_pin_t pin, isr_func handler) {
    
    int8_t ret = 0;

    ret = hal_gpio_register_isr(pin, handler);

    return ret;
}

int8_t drv_gpio_intc_clear(gpio_pin_t pin) {
    
    int8_t ret = 0;

    ret = hal_gpio_intc_clear_counter(pin);

    return ret;
}


int8_t drv_gpio_set_wakeup_enable(gpio_pin_t pin) {

    int8_t ret = 0;

    ret = hal_gpio_set_wakeup_enable(pin);

    return ret;
}

int8_t drv_gpio_set_wakeup_disable(gpio_pin_t pin) {

    int8_t ret = 0;

    ret = hal_gpio_set_wakeup_disable(pin);

    return ret;
}

int8_t drv_gpio_set_wakeup_detect(gpio_intc_trigger_mode_t int_mode) {

    int8_t ret = 0;

    ret = hal_gpio_set_wakeup_detect(int_mode);

    return ret;
}

