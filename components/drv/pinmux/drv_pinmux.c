
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

void drv_pinmux_force_gpio(uint32_t pin, int isForceGPIO)
{
    OS_DeclareCritical();
    OS_EnterCritical();
    if (isForceGPIO) {
        if (pin < 32) {
            hal_pinmux_pin_manual_force_gpio(pin);
        } else {
            hal_pinmux_pin_manual_force_gpio_32(pin - 32);
        }
    } else {
        if (pin < 32) {
            hal_pinmux_pin_manual_restore_gpio(pin);
        } else {
            hal_pinmux_pin_manual_restore_gpio_32(pin - 32);
        }
    }
    OS_ExitCritical();
}

