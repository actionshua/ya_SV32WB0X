//#include <stdio.h>
//#include <string.h>
//#include <stdint.h>
//#include <stdlib.h>
//#include "ssv_lib.h"
//#include "attrs.h"

#include "atcmd_gpio.h"
#include "gpio/drv_gpio.h"

#if defined(SUPPORT_PERIPHERAL_PWM) && (SUPPORT_PERIPHERAL_PWM==1)
#include "pwm/drv_pwm.h"
#endif


int At_SetGpioTriState (stParam *param) {
	char *pid = 0;
    int8_t ret = 0;

	pid = param->argv[0];

	if ((param->argc < 1) || (atoi(pid) > 22)) {
        ATCMD_LOG_I("\n");
        ATCMD_LOG_I("Usage   : AT+SET_GPIO_TRI_STATE=<id>\n");
        ATCMD_LOG_I("<id>    : gpio id(0-22)\n");
		return ERROR_INVALID_PARAMETER;
	}
    
    ret = drv_gpio_set_mode(atoi(pid), 1);

    ATCMD_LOG_I("\n");
    ATCMD_LOG_I("gpio_id = %d\n", atoi(pid));
    
	return ERROR_SUCCESS;
}
int At_SetGpioDir (stParam *param) {
    char *pid = 0, *pdir = 0;
    int8_t ret = 0;
    
    pid = param->argv[0];
    pdir = param->argv[1];

    if ((param->argc < 2) || (atoi(pid) > 22) || (atoi(pdir) > 1)) {
        ATCMD_LOG_I("\n");
        ATCMD_LOG_I("Usage   : AT+SET_GPIO_DIR=<id>,<dir>\n");
        ATCMD_LOG_I("<id>    : gpio id(0-22)\n");
        ATCMD_LOG_I("<dir> : 0:input ; 1:output\n");
		return ERROR_INVALID_PARAMETER;
    }

    ret = drv_gpio_set_mode(atoi(pid), 0);
    ret = drv_gpio_set_dir(atoi(pid), atoi(pdir));

    ATCMD_LOG_I("\n");
    ATCMD_LOG_I("gpio_id = %d\n", atoi(pid));
    ATCMD_LOG_I("gpio_dir = %d\n", atoi(pdir));
    
    return ERROR_SUCCESS;    
}
int At_SetGpioLogic (stParam *param) {
	char *pid = 0, *logic = 0;
    int8_t ret = 0;
    
	pid = param->argv[0];
	logic = param->argv[1];

	if ((param->argc < 2) || (atoi(pid) > 22) || (atoi(logic) > 1)) {
        ATCMD_LOG_I("\n");
        ATCMD_LOG_I("Usage   : AT+SET_GPIO_LOGIC=<id>,<logic>\n");
        ATCMD_LOG_I("<id>    : gpio id(0-22)\n");
        ATCMD_LOG_I("<logic> : 0:low ; 1:high\n");
		return ERROR_INVALID_PARAMETER;
	}

    ret = drv_gpio_set_mode(atoi(pid), 0);
    ret = drv_gpio_set_dir(atoi(pid), 1);
    ret = drv_gpio_set_logic(atoi(pid), atoi(logic));

    ATCMD_LOG_I("\n");
    ATCMD_LOG_I("gpio_id = %d\n", atoi(pid));
    ATCMD_LOG_I("gpio_logic = %d\n", atoi(logic));
    
	return ERROR_SUCCESS;
}

int At_SetGpioPull (stParam *param) {
	char *pid = 0, *gpio_pull = 0;
    int8_t ret = 0;
    
	pid = param->argv[0];
	gpio_pull = param->argv[1];

	if ((param->argc < 2) || (atoi(pid) > 22) || (atoi(gpio_pull) > 2)) {
        ATCMD_LOG_I("\n");
        ATCMD_LOG_I("Usage   : AT+SET_GPIO_PULL=<id>,<pull>\n");
        ATCMD_LOG_I("<id>    : gpio id(0-22)\n");
        ATCMD_LOG_I("<pull>  : 0:down ; 1:up ; 2:none\n");
		return ERROR_INVALID_PARAMETER;
	}
    
    ret = drv_gpio_set_mode(atoi(pid), 0);
    ret = drv_gpio_set_dir(atoi(pid), 0);
    ret = drv_gpio_set_pull(atoi(pid), atoi(gpio_pull));

    ATCMD_LOG_I("\n");
    ATCMD_LOG_I("gpio_id = %d\n", atoi(pid));
    ATCMD_LOG_I("gpio_pull = %d\n", atoi(gpio_pull));
    ATCMD_LOG_I("gpio_input_get = %d\n", drv_gpio_get_logic(atoi(pid)));
    
	return ERROR_SUCCESS;
}

int At_ReadGpio (stParam *param) {
	char *pid = 0;
    int8_t ret = 0;

	pid = param->argv[0];

	if ((param->argc < 1) || (atoi(pid) > 22)) {
        ATCMD_LOG_I("\n");
        ATCMD_LOG_I("Usage   : AT+READ_GPIO=<id>\n");
        ATCMD_LOG_I("<id>    : gpio id(0-22)\n");
		return ERROR_INVALID_PARAMETER;
	}

    ret = drv_gpio_get_logic(atoi(pid));

    ATCMD_LOG_I("\n");
    ATCMD_LOG_I("gpio_id = %d\n", atoi(pid));
    ATCMD_LOG_I("gpio_logic = %d\n", ret);
    
	return ERROR_SUCCESS;
}


uint8_t gpio_intc_id = 0x0;
uint8_t gpio_intc_mode = 0x0;

void irq_test_gpio_ipc(uint32_t irq_num) {
    int8_t ret = 0x0;
    
    ret = drv_gpio_intc_clear(gpio_intc_id);
    
    if(2 == gpio_intc_mode) {
        ATCMD_LOG_I("\nLine = %d\nFunc = %s\nGPIO_INTC_HIGH_LEVEL\n", __LINE__, __FUNCTION__);
    }
    else if(3 == gpio_intc_mode) {
        ATCMD_LOG_I("\nLine = %d\nFunc = %s\nGPIO_INTC_RISING_EDGE\n", __LINE__, __FUNCTION__);
    }
    else if(4 == gpio_intc_mode) { 
        ATCMD_LOG_I("\nLine = %d\nFunc = %s\nGPIO_INTC_LOW_LEVEL\n", __LINE__, __FUNCTION__);
    }
    else {
        ATCMD_LOG_I("\nLine = %d\nFunc = %s\nGPIO_INTC_FALLING_EDGE\n", __LINE__, __FUNCTION__);
    }    
}

int At_SetGpioInt (stParam *param) {
	char *pid = 0, *int_mode = 0;
    int8_t ret = 0;
    
	pid = param->argv[0];
	int_mode = param->argv[1];

	if ((param->argc < 2) || (atoi(pid) > 22) || (atoi(int_mode) > 5) || (atoi(int_mode) < 2)) {
        ATCMD_LOG_I("\n");
        ATCMD_LOG_I("Usage   : AT+SET_GPIO_INT=<id>,<mode>\n");
        ATCMD_LOG_I("<id>    : gpio id(0-22)\n");
        ATCMD_LOG_I("<mode>  : 2:high_level ; 3:rising_edge ; 4:low_level ; 5:falling_edge\n");
		return ERROR_INVALID_PARAMETER;
	}

    gpio_intc_id = atoi(pid);
    gpio_intc_mode = atoi(int_mode);
    
    ret = drv_gpio_set_mode(gpio_intc_id, 0);
	ret = drv_gpio_set_dir(gpio_intc_id, 0);
    ret = drv_gpio_intc_trigger_mode(gpio_intc_id, gpio_intc_mode);
    ret = drv_gpio_register_isr(gpio_intc_id, irq_test_gpio_ipc);

    ATCMD_LOG_I("\n");
    ATCMD_LOG_I("gpio_id = %d\n", gpio_intc_id);
    ATCMD_LOG_I("gpio_interrupt_mode = %d\n", gpio_intc_mode);
    
	return ERROR_SUCCESS;
}

#if defined(SUPPORT_PERIPHERAL_PWM) && (SUPPORT_PERIPHERAL_PWM==1)
int At_SetPWM (stParam *param) {
	char *pwm_id = 0, *freq_hz = 0, *duty = 0, *is_invert = 0;
    int8_t ret = 0;
    
	pwm_id = param->argv[0];
	freq_hz = param->argv[1];
    duty = param->argv[2];
    is_invert = param->argv[3];

	if ((param->argc < 4) || (atoi(pwm_id) > 4) || (atoi(freq_hz) < 5) || (atoi(freq_hz) > 4000000) || (atoi(duty) > 100) || (atoi(is_invert) > 1)) {
        ATCMD_LOG_I("\n");
        ATCMD_LOG_I("Usage   : AT+SET_PWM=<id>,<freq>,<duty>,<inv>\n");
        ATCMD_LOG_I("<id>    : pwm id(0-4)\n");
        ATCMD_LOG_I("<freq>  : freq_hz(5-4M)\n");
        ATCMD_LOG_I("<duty>  : duty(0-100)\n");
        ATCMD_LOG_I("<inv>   : 0:none ; 1:invert the PWM polarity\n");
		return ERROR_INVALID_PARAMETER;
	}

    ret = drv_pwm_init(atoi(pwm_id));
    ret = drv_pwm_config(atoi(pwm_id), atoi(freq_hz), atoi(duty), atoi(is_invert));
    ret = drv_pwm_enable(atoi(pwm_id));
    
    
    ATCMD_LOG_I("\n");
    ATCMD_LOG_I("pwm_id      = %d\n", atoi(pwm_id));
    ATCMD_LOG_I("freq_hz     = %d\n", atoi(freq_hz));
    ATCMD_LOG_I("duty        = %d\n", atoi(duty));
    ATCMD_LOG_I("is_invert   = %d\n", atoi(is_invert));
    
	return ERROR_SUCCESS;
}

int At_SetPWMDisable (stParam *param) {
	char *pwm_id = 0;
    int8_t ret = 0;

	pwm_id = param->argv[0];

	if ((param->argc < 1) || (atoi(pwm_id) > 4)) {
        ATCMD_LOG_I("\n");
        ATCMD_LOG_I("Usage   : AT+SET_PWM_DISABLE=<id>\n");
        ATCMD_LOG_I("<id>    : pwm_id(0-4)\n");
		return ERROR_INVALID_PARAMETER;
	}

    ret = drv_pwm_disable(atoi(pwm_id));

    ATCMD_LOG_I("\n");
    ATCMD_LOG_I("pwm_id      = %d\n", atoi(pwm_id));
    
	return ERROR_SUCCESS;
}

int At_SetPWMEnable (stParam *param) {
	char *pwm_id = 0;
    int8_t ret = 0;

	pwm_id = param->argv[0];

	if ((param->argc < 1) || (atoi(pwm_id) > 4)) {
        ATCMD_LOG_I("\n");
        ATCMD_LOG_I("Usage   : AT+SET_PWM_ENABLE=<id>\n");
        ATCMD_LOG_I("<id>    : pwm_id(0-4)\n");
		return ERROR_INVALID_PARAMETER;
	}

    ret = drv_pwm_enable(atoi(pwm_id));

    ATCMD_LOG_I("\n");
    ATCMD_LOG_I("pwm_id      = %d\n", atoi(pwm_id));
    
	return ERROR_SUCCESS;
}

int At_SetPWMReconfig (stParam *param) {
	char *pwm_id = 0, *freq_hz = 0, *duty = 0, *is_invert = 0;
    int8_t ret = 0;
    
	pwm_id = param->argv[0];
	freq_hz = param->argv[1];
    duty = param->argv[2];
    is_invert = param->argv[3];

	if ((param->argc < 4) || (atoi(pwm_id) > 4) || (atoi(freq_hz) < 5) || (atoi(freq_hz) > 4000000) || (atoi(duty) > 100) || (atoi(is_invert) > 1)) {
        ATCMD_LOG_I("\n");
        ATCMD_LOG_I("Usage   : AT+SET_PWM_RECONFIG=<id>,<freq>,<duty>,<inv>\n");
        ATCMD_LOG_I("<id>    : pwm id(0-4)\n");
        ATCMD_LOG_I("<freq>  : freq_hz(5-4M)\n");
        ATCMD_LOG_I("<duty>  : duty(0-100)\n");
        ATCMD_LOG_I("<inv>   : 0:none ; 1:invert the PWM polarity\n");
		return ERROR_INVALID_PARAMETER;
	}
    
    ret = drv_pwm_config(atoi(pwm_id), atoi(freq_hz), atoi(duty), atoi(is_invert));
    
    ATCMD_LOG_I("\n");
    ATCMD_LOG_I("pwm_id      = %d\n", atoi(pwm_id));
    ATCMD_LOG_I("freq_hz     = %d\n", atoi(freq_hz));
    ATCMD_LOG_I("duty        = %d\n", atoi(duty));
    ATCMD_LOG_I("is_invert   = %d\n", atoi(is_invert));
    
	return ERROR_SUCCESS;
}
#endif
