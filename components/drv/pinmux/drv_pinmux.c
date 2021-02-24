
#include <stdint.h>
#include "drv_pinmux.h"
#include "hal_pinmux.h"
#include "attrs.h"
#include "osal.h"
#include <stdio.h>

int8_t drv_pinmux_manual_function_select_enable(pinmux_fun_t function) {

    int8_t ret = 0;

    ret = hal_pinmux_manual_function_select_enable(function);

    return ret;
}

int8_t drv_pinmux_manual_function_select_disable(pinmux_fun_t function) {

    int8_t ret = 0;

    ret = hal_pinmux_manual_function_select_disable(function);

    return ret;
}

void drv_pinmux_pin_manual_io(uint32_t manual_gpio)
{
    hal_pinmux_pin_manual_io(manual_gpio);
}

void drv_pinmux_pin_manual_io_32(uint32_t manual_gpio32)
{
    hal_pinmux_pin_manual_io_32(manual_gpio32);
}

void drv_pinmux_pin_manual_force_gpio(uint32_t manual_gpio)
{
    hal_pinmux_pin_manual_force_gpio(manual_gpio);
}

void drv_pinmux_pin_manual_force_gpio_32(uint32_t manual_gpio32)
{
    hal_pinmux_pin_manual_force_gpio_32(manual_gpio32);
}

void drv_pinmux_pin_manual_restore_gpio(uint32_t manual_gpio)
{
    hal_pinmux_pin_manual_restore_gpio(manual_gpio);
}

void drv_pinmux_pin_manual_restore_gpio_32(uint32_t manual_gpio32)
{
    hal_pinmux_pin_manual_restore_gpio_32(manual_gpio32);
}

