
#include <stdio.h>
#include <string.h>
#include "soc_types.h"
#include "soc_defs.h"
#include "osal.h"

#include "cli.h"
#include "error.h"

#include <drv_gpio.h>
#include <drv_pwm.h>

#include "logger.h"

#define CMD_TAG       LOG_TAG_CMD
#define CMD_LOG_E(format, ...) log_e(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_W(format, ...) log_w(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_I(format, ...) log_i(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_D(format, ...) log_d(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_V(format, ...) log_v(CMD_TAG, format, ##__VA_ARGS__)

//uint32_t pwm_gpio_int_pin = 5;

/*---------------------------------- CMDs -----------------------------------*/

int Cmd_test_pwm(int32_t argc, char *argv[]) {    

    int8_t ret = 0x0;
    uint32_t pwm_id = 0;
    uint32_t freq_hz = 0;
    uint32_t duty = 0;
    uint32_t is_invert = 0;

    pwm_id = strtoul(argv[1], NULL, 10);
    freq_hz = strtoul(argv[2], NULL, 10);
    duty = strtoul(argv[3], NULL, 10);
    is_invert = strtoul(argv[4], NULL, 10);

    if ((argc != 5) || (pwm_id < 0) || (pwm_id > 7) || (freq_hz < 10) || (freq_hz > 80000000) || (duty < 0) || (duty > M_PWM_DUTY_STEP) || (is_invert < 0) || (is_invert > 1))
    {
        printf("Usage	: test_pwm <id> <freq> <duty> <inv>\n");
        printf("<id>	: pwm id(0-7)\n");
        printf("<freq>	: freq_hz(10-80000000)\n");
        printf("<duty>	: duty(0-4095)\n");
        printf("<inv>	: 0:none ; 1:invert the PWM polarity\n");
        return -1;
    }

    double min_input_duty = 0.0;
    uint32_t bus_clk = 160000000;   //160MHz
    //double bus_clk_period = 1/160000000;
    double final_min_input_duty = 0.0;
    
    min_input_duty = 1 * 4096 / (bus_clk/freq_hz);
        
    /*If the input frequency is greater than 39062Hz and the duty value is too small, the minimum duty value will be given.*/    
    if (freq_hz > 39062)   //160MHz/4096=390625Hz
    {
        if ((min_input_duty == 64) || (min_input_duty == 128) || (min_input_duty == 256) || (min_input_duty == 512) || (min_input_duty == 1024) || (min_input_duty == 2048) || (min_input_duty == 3072) || (min_input_duty == 4096))
        {
            final_min_input_duty = min_input_duty;
            printf("The minimum duty is %.lf\n",final_min_input_duty);
        }
        else
        {
            final_min_input_duty = min_input_duty + 1;
            printf("The minimum duty is %.lf\n",final_min_input_duty);
        }
        
    }
    drv_pwm_init(pwm_id);
    ret = drv_pwm_config(pwm_id, freq_hz, duty, is_invert);
    drv_pwm_enable(pwm_id);
    
    printf("pwm_id      = %d\n", pwm_id);
    printf("freq_hz     = %d\n", freq_hz);
    printf("duty        = %d\n", duty);
    printf("is_invert   = %d\n", is_invert);
    
    
    return 0;
}


int Cmd_test_pwm_reconfig(int32_t argc, char *argv[]) {    

    int8_t ret = 0x0;
    uint32_t pwm_id = 0;
    uint32_t freq_hz = 0;
    uint32_t duty = 0;
    uint32_t is_invert = 0;

    pwm_id = strtoul(argv[1], NULL, 10);
    freq_hz = strtoul(argv[2], NULL, 10);
    duty = strtoul(argv[3], NULL, 10);
    is_invert = strtoul(argv[4], NULL, 10);

    if ((argc != 5) || (pwm_id < 0) || (pwm_id > 7) || (freq_hz < 10) || (freq_hz > 80000000) || (duty < 0) || (duty > M_PWM_DUTY_STEP) || (is_invert < 0) || (is_invert > 1)) {
        printf("Usage   : test_pwm_reconfig <id> <freq> <duty> <inv>\n");
        printf("<id>    : pwm id(0-7)\n");
        printf("<freq>  : freq_hz(10-80000000)\n");
        printf("<duty>  : duty(0-4095)\n");
        printf("<inv>   : 0:none ; 1:invert the PWM polarity\n");
        return -1;
    }

    double min_input_duty = 0.0;
    uint32_t bus_clk = 160000000;   //160MHz
    //double bus_clk_period = 1/160000000;
    double final_min_input_duty = 0.0;
    
    min_input_duty = 1 * 4096 / (bus_clk/freq_hz);
        
    /*If the input frequency is greater than 39062Hz and the duty value is too small, the minimum duty value will be given.*/    
    if (freq_hz > 39062)   //160MHz/4096=390625Hz
    {
        if ((min_input_duty == 64) || (min_input_duty == 128) || (min_input_duty == 256) || (min_input_duty == 512) || (min_input_duty == 1024) || (min_input_duty == 2048) || (min_input_duty == 3072) || (min_input_duty == 4096))
        {
            final_min_input_duty = min_input_duty;
            printf("The minimum duty is %.lf\n",final_min_input_duty);
        }
        else
        {
            final_min_input_duty = min_input_duty + 1;
            printf("The minimum duty is %.lf\n",final_min_input_duty);
        }  
        
    }
    ret = drv_pwm_config(pwm_id, freq_hz, duty, is_invert);    
        
    printf("pwm_id      = %d\n", pwm_id);
    printf("freq_hz     = %d\n", freq_hz);
    printf("duty        = %d\n", duty);
    printf("is_invert   = %d\n", is_invert);
    
    return 0;
    
}

int Cmd_test_pwm_disable(int32_t argc, char *argv[]) {    

    int8_t ret = 0x0;
    uint32_t pwm_id = 0;
    
    pwm_id = strtoul(argv[1], NULL, 10);    

    if ((argc != 2) || (pwm_id < 0) || (pwm_id > 7)) {
        printf("Usage   : test_pwm_disable <id>\n");
        printf("<id>    : pwm id(0-7)\n");
        return -1;
    }
    
    ret = drv_pwm_disable(pwm_id);

    //ret = drv_gpio_set_mode(pwm_gpio_int_pin, PIN_MODE_GPIO);
    //ret = drv_gpio_set_dir(pwm_gpio_int_pin, GPIO_DIR_OUT);
    //ret = drv_gpio_set_logic(pwm_gpio_int_pin, GPIO_LOGIC_HIGH);
    
    printf("pwm_id      = %d\n", pwm_id);

    //ret = drv_gpio_set_logic(pwm_gpio_int_pin, GPIO_LOGIC_LOW);

    return 0;
}

int Cmd_test_pwm_enable(int32_t argc, char *argv[]) {    

    int8_t ret = 0x0;
    uint32_t pwm_id = 0;
    
    pwm_id = strtoul(argv[1], NULL, 10);    

    if ((argc != 2) || (pwm_id < 0) || (pwm_id > 7)) {
        printf("Usage   : test_pwm_enable <id>\n");
        printf("<id>    : pwm id(0-7)\n");
        return -1;
    }

    ret = drv_pwm_init(pwm_id);
    ret = drv_pwm_enable(pwm_id);

    //ret = drv_gpio_set_mode(pwm_gpio_int_pin, PIN_MODE_GPIO);
    //ret = drv_gpio_set_dir(pwm_gpio_int_pin, GPIO_DIR_OUT);
    //ret = drv_gpio_set_logic(pwm_gpio_int_pin, GPIO_LOGIC_HIGH);
    
    printf("pwm_id      = %d\n", pwm_id);
    
    //ret = drv_gpio_set_logic(pwm_gpio_int_pin, GPIO_LOGIC_LOW);

    return 0;
}

int Cmd_test_pwm_enable_all(int32_t argc, char *argv[]) {

    int8_t ret = 0x0;

    ret = drv_pwm_enable_all();

    return 0;
}


int Cmd_help (int32_t argc, char *argv[])
{
    //printf ("\n*************************************************************************\n");
    //printf ("Test PWM Target : \n");
    //printf ("                   GPIO_00 : PWM_id: 0\n");
    //printf ("                   GPIO_01 : PWM_id: 1\n");
    //printf ("                   GPIO_02 : PWM_id: 2\n");
    //printf ("                   GPIO_03 : PWM_id: 3\n");
    //printf ("                   GPIO_04 : PWM_id: 4\n");
    //printf ("                   GPIO_05 : PWM_id: 5\n");
    //printf ("                   GPIO_06 : PWM_id: 6\n");
    //printf ("                   GPIO_07 : PWM_id: 7\n");
    
    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       set_pwm_config  <id> <freq> <duty> <inv>\n");
    printf ("brief:\n");
    printf ("       This function initializes the PWM setting.\n");
    printf ("Options:\n");
    printf ("<id>                       The PWM target number(0-7).\n");
    printf ("<freq>                     Freq_hz(10-80000000).\n");
    printf ("<duty>                     Duty cycle(0-4095).\n");
    printf ("<inv>                      PWM polarity. 0:none ; 1:invert\n");
    printf ("Note:\n");
    printf ("Regarding <duty>, if the <freq> is greater than 39062Hz and the duty value\n");
    printf ("is too small, the minimum duty value will be given.\n");

    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       set_pwm_reconfig  <id> <freq> <duty> <inv>\n");
    printf ("brief:\n");
    printf ("       This function will reconfig the PWM setting.\n");
    printf ("Options:\n");
    printf ("<id>                       The PWM target number(0-7).\n");
    printf ("<freq>                     Freq_hz(10-80000000).\n");
    printf ("<duty>                     Duty cycle(0-4095).\n");
    printf ("<inv>                      PWM polarity. 0:none ; 1:invert\n");
    printf ("Note:\n");
    printf ("Regarding <duty>, if the <freq> is greater than 39062Hz and the duty value\n");
    printf ("is too small, the minimum duty value will be given.\n");

    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       pwm_disable  <id>\n");
    printf ("brief:\n");
    printf ("       This function stops the PWM execution.\n");
    printf ("Options:\n");
    printf ("<id>                       The PWM target number(0-7).\n");

    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       pwm_enable  <id>\n");
    printf ("brief:\n");
    printf ("       This function starts the PWM execution.\n");
    printf ("Options:\n");
    printf ("<id>                       The PWM target number(0-7).\n");

    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       pwm_enable_all\n");
    printf ("brief:\n");
    printf ("       This function starts the all PWM execution.\n");

    return 0;   
}

int Cmd_WriteReg32 (s32 argc, char *argv[])
{ 
    char *pkey = 0, *pvalue = 0;

    if (argc < 3) {
        return ERROR_INVALID_PARAMETER;
    }
  
    pkey = argv[1];
    pvalue = argv[2];
    
    if( pkey == 0 || pvalue == 0)
        return ERROR_INVALID_PARAMETER;
    
    unsigned int address = strtoul(pkey, NULL, 16);
    unsigned int data = strtoul(pvalue, NULL, 16);

    printf("reg : write 0x%x  0x%x \n", address, data);

    REG32(address)  = data;

    return ERROR_SUCCESS;
}

int Cmd_ReadReg32 (s32 argc, char *argv[])
{
    char *pkey = 0;
    unsigned int address;
    if (argc < 2) {
        return ERROR_INVALID_PARAMETER;
    }

    pkey = argv[1];

    address = strtoul(pkey, NULL, 16);

    printf("reg : read 0x%08x  0x%08x \n", address, (unsigned int)REG32(address));
    return ERROR_SUCCESS;
}

/* ---------------------- Registered CMDs to CMD Table ---------------------- */
const CLICmds gCustomCmdTable[] =
{
    { "help",               Cmd_help,               "pwm test help"},
    { "set_pwm_config",     Cmd_test_pwm,           "set_pwm_config <id> <freq> <duty> <inv>"},
    { "set_pwm_reconfig",   Cmd_test_pwm_reconfig,  "set_pwm_reconfig <id> <freq> <duty> <inv>"},
    { "pwm_disable",        Cmd_test_pwm_disable,   "pwm_disable <id>"},
    { "pwm_enable",         Cmd_test_pwm_enable,    "pwm_enable <id>"},
    { "pwm_enable_all",     Cmd_test_pwm_enable_all,"pwm_enable_all"},
    { "regw",               Cmd_WriteReg32,         "regw"},
    { "regr",               Cmd_ReadReg32,          "regr"},    
    
    { (const char *)NULL, (CliCmdFunc)NULL,   (const char *)NULL },
};


