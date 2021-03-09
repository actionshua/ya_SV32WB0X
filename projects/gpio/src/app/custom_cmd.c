
#include <stdio.h>
#include <string.h>
#include "soc_types.h"
#include "soc_defs.h"
#include "osal.h"
#include "cli.h"
#include "error.h"

#include <hal_gpio.h>
                          
#include <hal_gpio.h>
#include <drv_gpio.h>
#include "hal_pinmux.h"
#include "drv_pinmux.h"

#if defined(SUPPORT_PERIPHERAL_TOUCH) && (SUPPORT_PERIPHERAL_TOUCH==1)
#include <drv_touch.h>
#endif

#include "logger.h"
#include <bsp.h>

#define CMD_TAG       LOG_TAG_CMD
#define CMD_LOG_E(format, ...) log_e(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_W(format, ...) log_w(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_I(format, ...) log_i(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_D(format, ...) log_d(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_V(format, ...) log_v(CMD_TAG, format, ##__VA_ARGS__)

uint8_t cmd_gpio_intc_id = 0x0;
uint8_t cmd_gpio_intc_mode = 0x0;
/*---------------------------------- CMDs -----------------------------------*/

static void Cmd_gpio_common_usage(const char *cmd) {
    printf("Usage   : %s <id>\n", cmd);
    printf("<id>    : gpio id(0-%d)\n", GPIO_MAX);
}

int Cmd_set_gpio_mode(int32_t argc, char *argv[]) {

    int8_t ret = 0x0;
    uint32_t gpio_id = 0;
    uint32_t gpio_logic = 0;

    if (argc != 2) {
        Cmd_gpio_common_usage(argv[0]);
        return -1;
    }

    gpio_id = strtoul(argv[1], NULL, 10);

    if (gpio_id > GPIO_MAX) {
        Cmd_gpio_common_usage(argv[0]);
        return -1;
    }

    ret = drv_gpio_set_mode(gpio_id, PIN_MODE_GPIO);

    CMD_LOG_I("gpio_id = %d, set to gpio with no input & not output\n", gpio_id);

    return 0;
}

static void Cmd_set_gpio_tri_state_usage() {
    printf("Usage   : set_gpio_tri_state <id>\n");
    printf("<id>    : gpio id(0-%d)\n", GPIO_MAX);
}

int Cmd_set_gpio_tri_state(int32_t argc, char *argv[]) {

    int8_t ret = 0x0;
    uint32_t gpio_id = 0;
    uint32_t gpio_logic = 0;
	
    if (argc != 2) {
        Cmd_set_gpio_tri_state_usage();
        return -1;
    }

    gpio_id = strtoul(argv[1], NULL, 10);

    if (gpio_id > GPIO_MAX) {
        Cmd_set_gpio_tri_state_usage();
        return -1;
    }

    ret = drv_gpio_set_mode(gpio_id, PIN_MODE_ZSTATE);

    CMD_LOG_I("gpio_id = %d, set zstate\n", gpio_id);

    return 0;
}

static void Cmd_set_gpio_direction_usage(const char *cmd) {
    printf("Usage   : %s <id> <input> <output>\n", cmd);
    printf("<id>    : gpio id(0-%d)\n", GPIO_MAX);
    printf("<input> : 0:disable ; 1:enable\n");
    printf("<output> : 0:disable ; 1:enable\n");
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

    if ((gpio_id > GPIO_MAX) || (gpio_input > 1) || (gpio_output > 1)) {
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
    CMD_LOG_I("gpio_id = %d, set input = %d, set output = %d\n", gpio_id, gpio_input, gpio_output);

    return 0;
}

static void Cmd_set_gpio_logic_usage() {
    printf("Usage   : set_gpio_logic <id> <logic>\n");
    printf("<id>    : gpio id(0-%d)\n", GPIO_MAX);
    printf("<logic> : 0:low ; 1:high\n");
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

    if ((gpio_id > GPIO_MAX) || (gpio_logic > 1)) {
        Cmd_set_gpio_logic_usage();
        return -1;
    }

    if ((drv_gpio_get_dir(gpio_id) != GPIO_DIR_OUT) && (drv_gpio_get_dir(gpio_id) != GPIO_DIR_IN_OUT)) {
        CMD_LOG_W("gpio_id %d\n", gpio_id);
        CMD_LOG_W("not set to direction output\n");
        return -1;
    }
    ret = drv_gpio_set_logic(gpio_id, gpio_logic);

    CMD_LOG_I("gpio_id = %d\n", gpio_id);
    CMD_LOG_I("set gpio_logic = %d\n", gpio_logic);

    return 0;
}

int Cmd_get_gpio_logic(int32_t argc, char *argv[]) {

    int8_t ret = 0x0;
    uint32_t gpio_id = 0;
    uint32_t gpio_logic = 0;
	
    if (argc != 2) {
        printf("Usage   : get_gpio_logic <id>\n");
        printf("<id>    : gpio id(0-%d)\n", GPIO_MAX);
        return -1;
    }

	gpio_id = strtoul(argv[1], NULL, 10);

    if ((gpio_id > GPIO_MAX)) {
    }

    if ((drv_gpio_get_dir(gpio_id) != GPIO_DIR_IN) && (drv_gpio_get_dir(gpio_id) != GPIO_DIR_IN_OUT)) {
        CMD_LOG_W("gpio_id %d\n", gpio_id);
        CMD_LOG_W("not set to direction input\n");
        return -1;
    }
    gpio_logic = drv_gpio_get_logic(gpio_id);

    printf("gpio_id = %d\n", gpio_id);
    printf("gpio_logic = %d\n", gpio_logic);

    return 0;
}

 static void Cmd_set_gpio_pull_usage(const char *cmd) {
    printf("Usage   : %s <id> <pull>\n", cmd);
    printf("<id>    : gpio id(0-%d)\n", GPIO_MAX);
    printf("<pull>  : 0:down ; 1:up ; 2:none\n");
}

int Cmd_set_gpio_pull(int32_t argc, char *argv[]) {
    
    uint32_t gpio_id = 0;
    uint32_t gpio_pull = 0;
	
    if (argc != 3) {
        Cmd_set_gpio_pull_usage(argv[0]);
        return -1;
    }

	gpio_id = strtoul(argv[1], NULL, 10);
    gpio_pull = strtoul(argv[2], NULL, 10);

    if ((gpio_id > GPIO_MAX) || (gpio_pull > 2)) {
        Cmd_set_gpio_pull_usage(argv[0]);
        return -1;
    }

    drv_gpio_set_pull(gpio_id, gpio_pull);

    CMD_LOG_I("gpio_id = %d\n", gpio_id);
    CMD_LOG_I("gpio_pull = %d\n", gpio_pull);
    return 0;
}

int Cmd_get_gpio_pull_logic(int32_t argc, char *argv[]) {

    int8_t ret = 0x0;
    uint32_t gpio_id = 0;
    gpio_pull_t gpio_pull_logic = GPIO_PULL_NONE;
	
    if (argc != 2) {
        Cmd_gpio_common_usage(argv[0]);
        return -1;
    }

    gpio_id = strtoul(argv[1], NULL, 10);

    if (gpio_id > GPIO_MAX) {
        Cmd_gpio_common_usage(argv[0]);
        return -1;
    }

    gpio_pull_logic = drv_gpio_get_pull(gpio_id);

    printf("gpio_id = %d\n", gpio_id);
	if (gpio_pull_logic == GPIO_PULL_DOWN)
		printf("gpio_pull_logic = pull down\n");
	else if (gpio_pull_logic == GPIO_PULL_UP)
		printf("gpio_pull_logic = pull up\n");
	else if (gpio_pull_logic == GPIO_PULL_NONE)
		printf("gpio_pull_logic = none\n");

    return 0;
}


int Cmd_get_gpio_direction(int32_t argc, char *argv[]) {

    int8_t ret = 0x0;
    uint32_t gpio_id = 0;
    gpio_dir_t gpio_direction = GPIO_DIR_IN_OUT_OFF;
	
    if (argc != 2) {
        Cmd_gpio_common_usage(argv[0]);
        return -1;
    }

    gpio_id = strtoul(argv[1], NULL, 10);

    if (gpio_id > GPIO_MAX) {
        Cmd_gpio_common_usage(argv[0]);
        return -1;
    }

    gpio_direction = drv_gpio_get_dir(gpio_id);

    printf("gpio_id = %d\n", gpio_id);
	if (gpio_direction == GPIO_DIR_IN)
		printf("gpio_dirction = input\n");
	else if (gpio_direction == GPIO_DIR_OUT)
		printf("gpio_dirction = output\n");
	else if (gpio_direction == GPIO_DIR_IN_OUT)
		printf("gpio_dirction = input and output\n");
	else if (gpio_direction == GPIO_DIR_IN_OUT_OFF)
		printf("gpio_dirction = input and output off\n");

    return 0;

}


void cmd_irq_test_gpio_ipc(uint32_t irq_num) {
    int8_t ret = 0x0;
    
    ret = drv_gpio_intc_clear(cmd_gpio_intc_id);
    
    if(GPIO_INTC_HIGH_LEVEL == cmd_gpio_intc_mode) {
        printf("\nLine = %d\nFunc = %s\nGPIO_INTC_HIGH_LEVEL\n", __LINE__, __FUNCTION__);
    }
    else if(GPIO_INTC_RISING_EDGE == cmd_gpio_intc_mode) {
        printf("\nLine = %d\nFunc = %s\nGPIO_INTC_RISING_EDGE\n", __LINE__, __FUNCTION__);
    }
    else if(GPIO_INTC_LOW_LEVEL == cmd_gpio_intc_mode) { 
        printf("\nLine = %d\nFunc = %s\nGPIO_INTC_LOW_LEVEL\n", __LINE__, __FUNCTION__);
    }
    else {
        printf("\nLine = %d\nFunc = %s\nGPIO_INTC_FALLING_EDGE\n", __LINE__, __FUNCTION__);
    }    
}

static void Cmd_set_gpio_int_usage(const char *cmd) {
    printf("Usage   : %s <id> <mode>\n", cmd);
    printf("<id>    : gpio id(0-%d)\n", GPIO_MAX);
    printf("<mode>  : 2:high_level ; 3:rising_edge ; 4:low_level ; 5:falling_edge\n");
}

int Cmd_set_gpio_int(int32_t argc, char *argv[]) {    

    uint32_t gpio_id = 0;
    uint32_t int_mode = 0;
	
    if (argc != 3) {
        Cmd_set_gpio_int_usage(argv[0]);
        return -1;
    }

	gpio_id = strtoul(argv[1], NULL, 10);
    int_mode = strtoul(argv[2], NULL, 10);

    if ((gpio_id > GPIO_MAX) || (int_mode > 5) || (int_mode < 2)) {
        Cmd_set_gpio_int_usage(argv[0]);
        return -1;
    }

    cmd_gpio_intc_id = gpio_id;
    cmd_gpio_intc_mode = int_mode;

    if (drv_gpio_get_dir(gpio_id) == GPIO_DIR_OUT) {
        drv_gpio_set_dir(gpio_id, GPIO_DIR_IN_OUT);
    } else {
        drv_gpio_set_dir(gpio_id, GPIO_DIR_IN);
    }
    drv_gpio_intc_trigger_mode(gpio_id, int_mode);
    drv_gpio_register_isr(gpio_id, cmd_irq_test_gpio_ipc);

    CMD_LOG_I("gpio_id = %d\n", gpio_id);
    CMD_LOG_I("gpio_interrupt_mode = %d\n", int_mode);

    return 0;
}

int Cmd_help (int32_t argc, char *argv[])
{
    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       set_gpio_logic  <id> <logic>\n");
    printf ("brief:\n");
    printf ("       This function sets the output logic of the target GPIO.\n");
    printf ("Options:\n");
    printf ("   <id>                       The GPIO target number(0-%d).\n", GPIO_MAX);
    printf ("   <logic>                    Output logic. 0:low ; 1:high.\n");

    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       get_gpio_logic  <id>\n");
    printf ("brief:\n");
    printf ("       This function gets the output logic of the target GPIO.\n");
    printf ("Options:\n");
    printf ("<id>                       The GPIO target number(0-%d).\n", GPIO_MAX);

    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       set_gpio_pull  <id> <pull>\n");
    printf ("brief:\n");
    printf ("       This function sets the target GPIO to the pull state.\n");
    printf ("Options:\n");
    printf ("   <id>                       The GPIO target number(0-%d).\n", GPIO_MAX);
    printf ("   <pull>                     Pull state. 0:down ; 1:up ; 2:none.\n");

    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       get_gpio_pull_logic  <id>\n");
    printf ("brief:\n");
    printf ("       This function gets the pull logic of the target GPIO.\n");
    printf ("Options:\n");
    printf ("<id>                       The GPIO target number(0-%d).\n", GPIO_MAX);

    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       set_gpio_tri_state  <id> \n");
    printf ("brief:\n");
    printf ("       This function sets the target GPIO to the tri-state.\n");
    printf ("Options:\n");
    printf ("   <id>                       The GPIO target number(0-%d).\n", GPIO_MAX);

    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       get_gpio_direction  <id>\n");
    printf ("brief:\n");
    printf ("       This function gets the direction of the target GPIO.\n");
    printf ("Options:\n");
    printf ("<id>                       The GPIO target number(0-%d).\n", GPIO_MAX);
    printf ("\n*************************************************************************\n");
    printf("Usage   : set_gpio_direction <id> <input> <output>\n");
    printf("<id>    : gpio id(0-%d)\n", GPIO_MAX);
    printf("<input> : 0:disable ; 1:enable\n");
    printf("<output> : 0:disable ; 1:enable\n");

    /*
    printf ("\n*************************************************************************\n");
    printf ("Usage: \n");
    printf ("       set_gpio_interrupt  <id> <mode>\n");
    printf ("brief:\n");
    printf ("       This function sets the target GPIO to the pull state.\n");
    printf ("Options:\n");
    printf (    "<id>                       The GPIO target number(0-%d).\n", GPIO_MAX);
    printf (    "<mode>                     Trigger mode. 2:high_level ; 3:rising_edge ; 4:low_level ; 5:falling_edge.\n");
    */

    return 0;
}

static void Cmd_set_gpio_isr_usage(const char *cmd) {
    printf("Usage   : %s <id> <mode>\n", cmd);
    printf("<id>    : gpio id(0-%d)\n", GPIO_MAX);
    printf("<mode>  : 2: high level\n");
    printf("        : 3: rising edge\n");
    printf("        : 4: low level\n");
    printf("        : 5: falling edge\n");
    printf("        : other: unregister\n");
}

void gpio_isr_handler(uint32_t gpio){
    //REG32(0xc0000c00) = 'G';
    CMD_LOG_I("isr %d\n", gpio);
    system_delay(system_us2delaytick(100000));
    drv_gpio_intc_clear(gpio);
}

int Cmd_set_gpio_isr(int32_t argc, char *argv[]) {
    
    uint32_t gpio_id = 0;
    uint32_t gpio_mode = 0;
	
    if (argc != 3) {
        Cmd_set_gpio_isr_usage(argv[0]);
        return -1;
    }

	gpio_id = strtoul(argv[1], NULL, 10);
    gpio_mode = strtoul(argv[2], NULL, 10);

    if (gpio_id > GPIO_MAX) {
        Cmd_set_gpio_isr_usage(argv[0]);
        return -1;
    }

    drv_gpio_intc_clear(gpio_id);
    drv_gpio_register_isr(gpio_id, gpio_isr_handler);
    drv_gpio_intc_trigger_mode(gpio_id, gpio_mode);

    CMD_LOG_I("gpio_id = %d\n", gpio_id);
    CMD_LOG_I("gpio_mode = %d\n", gpio_mode);
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

int Cmd_set_force_gpio(int32_t argc, char *argv[]) {

    uint32_t gpio_id = 0;
    	
    if (argc != 2) {
        printf("Usage   : set_force_gpio <id>\n");
        return -1;
    }

	gpio_id = strtoul(argv[1], NULL, 10);

    if (gpio_id > GPIO_MAX) {
        printf("Usage   : set_force_gpio <id>\n");
        printf("<id>    : gpio id(0-%d)\n", GPIO_MAX);
        return -1;

    }

    drv_pinmux_force_gpio(gpio_id, 1);

    CMD_LOG_I("gpio_id = %d\n", gpio_id);

    return 0;
}

int Cmd_set_remove_force_gpio(int32_t argc, char *argv[]) {
    
    uint32_t gpio_id = 0;
    	
    if (argc != 2) {
     
        printf("Usage   : set_restore_gpio <id>\n");

        return -1;
    }

	gpio_id = strtoul(argv[1], NULL, 10);

    if (gpio_id > GPIO_MAX) {
     
        printf("Usage   : set_restore_gpio <id>\n");
        printf("<id>    : gpio id(0-%d)\n", GPIO_MAX);

        return -1;
    }

    drv_pinmux_force_gpio(gpio_id, 0);

    CMD_LOG_I("gpio_id = %d\n", gpio_id);

    return 0;
}

/*---------------------Touch example code (START)-----------------------------*/
#if defined(SUPPORT_PERIPHERAL_TOUCH) && (SUPPORT_PERIPHERAL_TOUCH==1)

//#if defined(PERI_IO_PWM7)
//#else 
//    #error "Please check padmux for PWM7."
//#endif

//#if defined(PERI_IO_UART0)
//#else 
//    #error "Please check padmux for UART0."
//#endif

void Cmd_touch_task(void *pdata)    
{
    //Define the touchpad pin on which GPIO pin
    drv_touch_init(TOUCH_0,GPIO_29);
    drv_touch_init(TOUCH_1,GPIO_33);
    drv_touch_init(TOUCH_2,GPIO_36);
    drv_touch_init(TOUCH_3,GPIO_37);
    //drv_touch_init(TOUCH_4,GPIO_18);
    //drv_touch_init(TOUCH_5,GPIO_19);
    //drv_touch_init(TOUCH_6,GPIO_20);

    uint32_t touch_0_threshold = 1809;
    uint32_t touch_1_threshold = 1630;
    uint32_t touch_2_threshold = 1653;
    uint32_t touch_3_threshold = 1681;
    uint32_t touch_4_threshold = 2100;
    uint32_t touch_5_threshold = 2100;
    uint32_t touch_6_threshold = 2100;
    
    while (1)
    {
        drv_touch_src_config();
        drv_touch_enable();

        //PWM f=1kHz, min delay=50ms
        OS_MsDelay(60);

        //Query CTMR_0 timer value
        uint16_t touch_0_query = drv_touch_query_raw(TOUCH_0);
        //printf("CTMR_0 Timer=%d\n",touch_0_query);
        if (touch_0_query >= touch_0_threshold) { 
            printf("CTMR_0 Timer=%d PLAY\n",touch_0_query);
        }
                
        //Query CTMR_1 timer value
        uint16_t touch_1_query = drv_touch_query_raw(TOUCH_1);
        //printf("CTMR_1 Timer=%d\n",touch_1_query);
        if (touch_1_query >= touch_1_threshold) {
            printf("CTMR_1 Timer=%d SET\n",touch_1_query);      
        }

        //Query CTMR_2 timer value
        uint16_t touch_2_query = drv_touch_query_raw(TOUCH_2);
        //printf("CTMR_2 Timer=%d\n",touch_2_query);
        if (touch_2_query >= touch_2_threshold) { 
            printf("CTMR_2 Timer=%d VOL-\n",touch_2_query);
        }

        //Query CTMR_3 timer value
        uint16_t touch_3_query = drv_touch_query_raw(TOUCH_3);
        //printf("CTMR_3 Timer=%d\n",touch_3_query);
        if (touch_3_query >= touch_3_threshold) { 
            printf("CTMR_3 Timer=%d VOL+\n",touch_3_query);
        }

        //Query CTMR_4 timer value
        uint16_t touch_4_query = drv_touch_query_raw(TOUCH_4);
        if (touch_4_query >= touch_4_threshold) { 
            printf("CTMR_4 Timer=%d Pad4\n",touch_4_query);
        }  

        //Query CTMR_5 timer value
        uint16_t touch_5_query = drv_touch_query_raw(TOUCH_5);
        if (touch_5_query >= touch_5_threshold) { 
            printf("CTMR_5 Timer=%d Pad5\n",touch_5_query);
        }

        //Query CTMR_6 timer value
        uint16_t touch_6_query = drv_touch_query_raw(TOUCH_6);
        if (touch_6_query >= touch_6_threshold) { 
            printf("CTMR_6 Timer=%d Pad6\n",touch_6_query);
        }
        
        drv_touch_clear();
    }
    
    OS_TaskDelete(NULL);
    return;
}

int Cmd_touchpad (s32 argc, char *argv[])
{
    OS_TaskCreate(Cmd_touch_task, "Touch task", 512, NULL, OS_TASK_LOW_PRIO, NULL);
    return 0;
}

int Cmd_touch_cali(int32_t argc, char *argv[])    
{
    
    if (argc != 3)
    {
        printf("Usage     : touch_cali <touch_id> <gpio_pin>\n");
        printf("<touch_id>: 0 ~ 5\n");
        printf("<gpio_pin>: 0 ~ 37\n");
        return -1;
    }

	uint32_t touch_id = strtoul(argv[1], NULL, 10);
    uint32_t pin = strtoul(argv[2], NULL, 10);

    if ((touch_id < 0) && (touch_id > 5))
    {
        printf("Usage     : touch_cali <touch_id> <gpio_pin>\n");
        printf("<touch_id>: 0 ~ 5\n");
        printf("<gpio_pin>: 0 ~ 37\n");
        return -1;
    }
    
    if (pin > 37)
    {
        printf("Usage     : touch_cali <touch_id> <gpio_pin>\n");
        printf("<touch_id>: 0 ~ 5\n");
        printf("<gpio_pin>: 0 ~ 37\n");
        return -1;
    }
    
    drv_touch_clear();
    drv_touch_disable();
    drv_touch_init(touch_id,pin);
    
    
    uint32_t count = 51;

    //Cali. "no touch" threshold
    uint32_t no_touch_total = 0;
    uint32_t no_total_avg = 0;
    uint32_t no_touch[count];
        
    printf("Please do NOT touch for 3 seconds.\n");
    printf("... ... ...\n");
    
    for (int i=0;i<count;i++)
    {
        drv_touch_src_config();
        drv_touch_enable();

        OS_MsDelay(60);
        
        if (touch_id == TOUCH_0)
        {
            //Query CTMR_0 timer value
            uint16_t touch_0_query = drv_touch_query_raw(TOUCH_0);
            //printf("CTMR_0 Timer=%d\n",touch_0_query);
            //no_touch_total = no_touch_total + touch_0_query;
            no_touch[i] = touch_0_query;
        }
        else if (touch_id == TOUCH_1)
        {
            //Query CTMR_1 timer value
            uint16_t touch_1_query = drv_touch_query_raw(TOUCH_1);
            //printf("CTMR_1 Timer=%d\n",touch_1_query);
            //no_touch_total = no_touch_total + touch_1_query;
            no_touch[i] = touch_1_query;
        }
        else if (touch_id == TOUCH_2)
        {
            //Query CTMR_2 timer value
            uint16_t touch_2_query = drv_touch_query_raw(TOUCH_2);
            //printf("CTMR_2 Timer=%d\n",touch_2_query);
            //no_touch_total = no_touch_total + touch_2_query;
            no_touch[i] = touch_2_query;
        }
        else if (touch_id == TOUCH_3)
        {
            //Query CTMR_3 timer value
            uint16_t touch_3_query = drv_touch_query_raw(TOUCH_3);
            //printf("CTMR_3 Timer=%d\n",touch_3_query);
            //no_touch_total = no_touch_total + touch_3_query;
            no_touch[i] = touch_3_query;
        }
        else if (touch_id == TOUCH_4)
        {
            //Query CTMR_4 timer value
            uint16_t touch_4_query = drv_touch_query_raw(TOUCH_4);
            //printf("CTMR_4 Timer=%d\n",touch_4_query);
            //no_touch_total = no_touch_total + touch_4_query;
            no_touch[i] = touch_4_query;
        }
        else if (touch_id == TOUCH_5)
        {
            //Query CTMR_5 timer value
            uint16_t touch_5_query = drv_touch_query_raw(TOUCH_5);
            //printf("CTMR_5 Timer=%d\n",touch_5_query);
            //no_touch_total = no_touch_total + touch_5_query;
            no_touch[i] = touch_5_query;
        }
        else if (touch_id == TOUCH_6)
        {
            //Query CTMR_6 timer value
            uint16_t touch_6_query = drv_touch_query_raw(TOUCH_6);
            //printf("CTMR_6 Timer=%d\n",touch_6_query);
            //no_touch_total = no_touch_total + touch_6_query;
            no_touch[i] = touch_6_query;
        }
        
        drv_touch_clear();
        
    }

    //Sort the data from min to max.
    for (int i=0;i<count;i++)
    {
        uint32_t no_touch_min_index = i;
        for (int j=i+1;j<count;j++)
        {
                if (no_touch[j] < no_touch[no_touch_min_index])
                    no_touch_min_index = j;
        }
        uint32_t tmp = no_touch[i];
        no_touch[i] = no_touch[no_touch_min_index];
        no_touch[no_touch_min_index] = tmp;
        
    }

    printf("\n");

    printf("The 'no touch' calibration is completed.\n");
    
    printf("TOUCH_%d no touch value = %d\n",touch_id,no_touch[(count-1)/2]);

    //Cali. "touch" threshold 
    uint32_t touch_total = 0;
    uint32_t total_avg = 0;
    uint32_t touch[count];
    
    drv_touch_disable();

    printf("\n");
    printf("Please touch for 3 seconds.\n");
    printf("... ... ...\n");
    
    for (int i=0;i<count;i++)
    {
        drv_touch_src_config();
        drv_touch_enable();

        OS_MsDelay(60);
        
        if (touch_id == TOUCH_0)
        {
            //Query CTMR_0 timer value
            uint16_t touch_0_query = drv_touch_query_raw(TOUCH_0);
            //printf("CTMR_0 Timer=%d\n",touch_0_query);
            //touch_total = touch_total + touch_0_query;
            touch[i] = touch_0_query;
        }
        else if (touch_id == TOUCH_1)
        {
            //Query CTMR_1 timer value
            uint16_t touch_1_query = drv_touch_query_raw(TOUCH_1);
            //printf("CTMR_1 Timer=%d\n",touch_1_query);
            //touch_total = touch_total + touch_1_query;
            touch[i] = touch_1_query;
        }
        else if (touch_id == TOUCH_2)
        {
            //Query CTMR_2 timer value
            uint16_t touch_2_query = drv_touch_query_raw(TOUCH_2);
            //printf("CTMR_2 Timer=%d\n",touch_2_query);
            //touch_total = touch_total + touch_2_query;
            touch[i] = touch_2_query;
        }
        else if (touch_id == TOUCH_3)
        {
            //Query CTMR_3 timer value
            uint16_t touch_3_query = drv_touch_query_raw(TOUCH_3);
            //printf("CTMR_3 Timer=%d\n",touch_3_query);
            //touch_total = touch_total + touch_3_query;
            touch[i] = touch_3_query;
        }
        else if (touch_id == TOUCH_4)
        {
            //Query CTMR_4 timer value
            uint16_t touch_4_query = drv_touch_query_raw(TOUCH_4);
            //printf("CTMR_4 Timer=%d\n",touch_4_query);
            //touch_total = touch_total + touch_4_query;
            touch[i] = touch_4_query;
        }
        else if (touch_id == TOUCH_5)
        {
            //Query CTMR_5 timer value
            uint16_t touch_5_query = drv_touch_query_raw(TOUCH_5);
            //printf("CTMR_5 Timer=%d\n",touch_5_query);
            //touch_total = touch_total + touch_5_query;
            touch[i] = touch_5_query;
        }
        else if (touch_id == TOUCH_6)
        {
            //Query CTMR_6 timer value
            uint16_t touch_6_query = drv_touch_query_raw(TOUCH_6);
            //printf("CTMR_6 Timer=%d\n",touch_6_query);
            //touch_total = touch_total + touch_6_query;
            touch[i] = touch_6_query;
        }
        
        drv_touch_clear();
        
    }

    //Sort the data from min to max.
    for (int i=0;i<count;i++)
    {
        uint32_t touch_min_index = i;
        for (int j=i+1;j<count;j++)
        {
                if (touch[j] < touch[touch_min_index])
                    touch_min_index = j;
        }
        uint32_t tmp = touch[i];
        touch[i] = touch[touch_min_index];
        touch[touch_min_index] = tmp;
        
    }

    printf("\n");

    printf("The 'touch' calibration is completed.\n");
    printf("TOUCH_%d touch value = %d\n",touch_id,touch[(count-1)/2]);
    printf("Calibration done.\n");
    
    drv_touch_disable();
    
    return 0;
}

#endif
/*---------------------Touch example code (END)-----------------------------*/

/* ---------------------- Registered CMDs to CMD Table ---------------------- */
const CLICmds gCustomCmdTable[] =
{
    { "help",                       Cmd_help,                       "gpio test help"                            },
    { "set_gpio_logic",             Cmd_set_gpio_logic,             "set_gpio_logic <id> <logic>"               },
    { "get_gpio_logic",             Cmd_get_gpio_logic,             "get_gpio_logic <id>"                       },
    { "set_gpio_pull",              Cmd_set_gpio_pull,              "set_gpio_pull <id> <pull>"                 },
    { "get_gpio_pull_logic",        Cmd_get_gpio_pull_logic,        "get_gpio_pull_logic <id>"                  },
    { "set_gpio_tri_state",         Cmd_set_gpio_tri_state,         "set_gpio_tri_state <id>"                   },
    { "set_gpio_mode",              Cmd_set_gpio_mode,              "set_gpio_mode <id>"                        },
    { "get_gpio_direction",         Cmd_get_gpio_direction,		    "get_gpio_direction <id>"			        },
    { "set_gpio_direction",         Cmd_set_gpio_direction,		    "set_gpio_direction <id> <input> <output>"  },
    { "set_gpio_isr",               Cmd_set_gpio_isr,               "set_gpio_isr <id> <mode>"                  },
    { "regw",                       Cmd_WriteReg32,                 "regw"                                      },
    { "regr",                       Cmd_ReadReg32,                  "regr"                                      },
    { "force_gpio",                 Cmd_set_force_gpio,             "force_gpio <id>"                           },
    { "remove_force_gpio",          Cmd_set_remove_force_gpio,      "remove_force_gpio <id>"                    },    
    #if defined(SUPPORT_PERIPHERAL_TOUCH) && (SUPPORT_PERIPHERAL_TOUCH==1)
    { "touch",                      Cmd_touchpad,                   "Touchpad function enable."                 },
    { "touch_cali",                 Cmd_touch_cali,                 "Touchpad calibration."                     },    
    #endif
            
    { (const char *)NULL, (CliCmdFunc)NULL,   (const char *)NULL },
};


