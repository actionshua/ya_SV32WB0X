
#include <stdio.h>
#include <string.h>
#include "soc_types.h"
#include "soc_defs.h"
#include "osal.h"

#include "cli.h"
#include "error.h"

#include "logger.h"
#include <drv_gpio.h>

static void Cmd_set_gpio_logic_usage() {
    printf("Usage   : set_gpio_logic <id> <logic>\n");
    printf("<id>    : gpio id(0-22)\n");
    printf("<logic> : 0:low ; 1:high\n");
}
static void Cmd_set_gpio_direction_usage(const char *cmd) {
    printf("Usage   : %s <id> <input> <output>\n", cmd);
    printf("<id>    : gpio id(0-22)\n");
    printf("<input> : 0:disable ; 1:enable\n");
    printf("<output> : 0:disable ; 1:enable\n");
}

static void Cmd_set_gpio_high_low_usage() {
    printf("Usage   : set_gpio_high_low <id>\n");
    printf("<id>    : gpio id(0-22)\n");
}

static void Cmd_set_gpio_low_high_usage() {
    printf("Usage   : set_gpio_low_high <id>\n");
    printf("<id>    : gpio id(0-22)\n");
}
int Cmd_set_gpio_direction(int32_t argc, char *argv[]) {

    uint32_t gpio_id = 0;
    uint32_t gpio_input = 0;
    uint32_t gpio_output = 0;

    if (argc != 4) {
        Cmd_set_gpio_direction_usage(argv[0]);
        return -1;
    }

	gpio_id = strtoul(argv[1], NULL, 10);
    gpio_input = strtoul(argv[2], NULL, 10);
    gpio_output = strtoul(argv[3], NULL, 10);

    if ((gpio_id > 22) || (gpio_input > 1) || (gpio_output > 1)) {
        Cmd_set_gpio_direction_usage(argv[0]);
        return -1;
    }

    //drv_gpio_set_mode(gpio_id, PIN_MODE_GPIO);
    if (gpio_input) {
        if (gpio_output) {
            // in & out
            drv_gpio_set_dir(gpio_id, GPIO_DIR_IN_OUT);
        } else {
            // in
            drv_gpio_set_dir(gpio_id, GPIO_DIR_IN);
        }
    } else {
        if (gpio_output) {
            // out
            drv_gpio_set_dir(gpio_id, GPIO_DIR_OUT);
        } else {
            // none
            drv_gpio_set_dir(gpio_id, GPIO_DIR_IN_OUT_OFF);
        }
    }
    printf("gpio_id = %d, set input = %d, set output = %d\n", gpio_id, gpio_input, gpio_output);

    return 0;
}

int Cmd_set_gpio_logic(int32_t argc, char *argv[]) {

    int8_t ret = 0x0;
    uint32_t gpio_id = 0;
    uint32_t gpio_logic = 0;
	

    if (argc != 3) {
        Cmd_set_gpio_logic_usage();
        return -1;
    }

	gpio_id = strtoul(argv[1], NULL, 10);
    gpio_logic = strtoul(argv[2], NULL, 10);

    if ((gpio_id > 22) || (gpio_logic > 1)) {
        Cmd_set_gpio_logic_usage();
        return -1;
    }

    if ((drv_gpio_get_dir(gpio_id) != GPIO_DIR_OUT) && (drv_gpio_get_dir(gpio_id) != GPIO_DIR_IN_OUT)) {
        printf("gpio_id %d\n", gpio_id);
        printf("not set to direction output\n");
        return -1;
    }
    ret = drv_gpio_set_logic(gpio_id, gpio_logic);

    printf("gpio_id = %d\n", gpio_id);
    printf("set gpio_logic = %d\n", gpio_logic);

    return 0;
}

int Cmd_set_gpio_high_low(int32_t argc, char *argv[]) {

    int8_t ret = 0x0;
    uint32_t gpio_id = 0;
	

    if (argc != 2) {
        Cmd_set_gpio_high_low_usage();
        return -1;
    }

	gpio_id = strtoul(argv[1], NULL, 10);

    if (gpio_id > 22) {
        Cmd_set_gpio_high_low_usage();
        return -1;
    }

    if ((drv_gpio_get_dir(gpio_id) != GPIO_DIR_OUT) && (drv_gpio_get_dir(gpio_id) != GPIO_DIR_IN_OUT)) {
        drv_gpio_set_mode(gpio_id, 0);
        drv_gpio_set_dir(gpio_id, GPIO_DIR_OUT);
    }
    ret = drv_gpio_set_logic(gpio_id, 1);
    OS_MsDelay(10);
    ret = drv_gpio_set_logic(gpio_id, 0);
    printf("set gpio %d rising edge\n", gpio_id);

    return 0;
}

int Cmd_set_gpio_low_high(int32_t argc, char *argv[]) {

    int8_t ret = 0x0;
    uint32_t gpio_id = 0;
	

    if (argc != 2) {
        Cmd_set_gpio_low_high_usage();
        return -1;
    }

	gpio_id = strtoul(argv[1], NULL, 10);

    if (gpio_id > 22) {
        Cmd_set_gpio_low_high_usage();
        return -1;
    }

    if ((drv_gpio_get_dir(gpio_id) != GPIO_DIR_OUT) && (drv_gpio_get_dir(gpio_id) != GPIO_DIR_IN_OUT)) {
        printf("gpio_id %d\n", gpio_id);
        printf("not set to direction output\n");
        return -1;
    }
    
    ret = drv_gpio_set_logic(gpio_id, 0);

    ret = drv_gpio_set_logic(gpio_id, 1);
    printf("set gpio %d falling edge\n", gpio_id);

    return 0;

}
/* ---------------------- Registered CMDs to CMD Table ---------------------- */
const CLICmds gCustomCmdTable[] =
{
    { "set_gpio_direction",         Cmd_set_gpio_direction,		    "get_set_direction <id> <input> <output>"   },
    { "set_gpio_logic",             Cmd_set_gpio_logic,             "set_gpio_logic <id> <logic>"               },
    { "trigger",             Cmd_set_gpio_high_low,             "trigger <id>"               },
    //{ "set_gpio_low_high",             Cmd_set_gpio_low_high,             "set_gpio_low_high <id>"               },
    
    { (const char *)NULL, (CliCmdFunc)NULL,   (const char *)NULL },
};


