#include <stdint.h>
#include "gpio/hal_gpio.h"
#include "pinmux/hal_pinmux.h"

#include "ota_flash.h"
#include "tiny_printf.h"

#include <serial.h>

// this function will execute before boot system start.
void _boot_init() {
    tiny_printf_display(1);

    //set pinmux for uart fw upgrade
	uint32_t pin_mode = 0;
    uint32_t sel_func = 0;

#if (CHIP_ID == 6006)
#if 1    //use gpio3 and gpio4 for uart fw upgrade
    pin_mode |= (0x1 << UART0_RXD_II);	//set gpio3 manual
    pin_mode |= (0x1 << UART0_TXD_II);	//set gpio4 manual
    sel_func |= (0x1 << SEL_UART0_II);	//enable uart0 as gpio3 and gpio4
#else    //use gpio21 and gpio22 for uart fw upgrade
    pin_mode |= (0x1 << UART0_TXD_I);	//set gpio21 manual
    pin_mode |= (0x1 << UART0_RXD_I);	//set gpio22 manual
    sel_func |= (0x1 << SEL_UART0_I);	//enable uart0 as gpio21 and gpio22
#endif    
#elif (CHIP_ID == 6020)
#else
#error no this chip.
#endif

#if (CHIP_ID == 6006)
    serial_init(UART_BAUD_RATE);
    hal_pinmux_set_raw(pin_mode, sel_func);	
#elif (CHIP_ID == 6020)
#else
#error no this chip.
#endif
}

// define ota by filesystem.
// @return 1: ota by filesystem.
//         0: no ota.
int _ota_use_fs() {
    return 1;
}

