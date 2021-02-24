#include <stdint.h>
#include "gpio/hal_gpio.h"
#include "pinmux/hal_pinmux.h"

#include "ota_flash.h"
#include "tiny_printf.h"
#include "bootsystem.h"

#include "serial.h"

#undef FLASH_TEST
#undef GPIO_TEST
#undef UART1_TEST

#if defined(FLASH_TEST)
char __flash_testing[]="123123123";
#define FLASH_TEST_CODE() \
    do { \
        long_wait=10000; \
        ota_flash_init(); \
        ota_flash_sector_erase(0xfa000); \
        ota_flash_page_program(0xfa000, 10, (unsigned char *)__flash_testing); \
        tiny_printf("test ='%s'\n", M_FLASH_START_ADDR+0xfa000); \
        while(long_wait--); \
    } while(0)
#else
#define FLASH_TEST_CODE()
#endif

#if defined(GPIO_TEST)
#define GPIO_TEST_CODE() \
    do {\
        long_wait=10000; \
        hal_gpio_set_mode(GPIO_13, PIN_MODE_GPIO); \
        hal_gpio_set_dir(GPIO_13, GPIO_DIR_IN); \
        while(long_wait--); \
        gpio_logic_t logic = hal_gpio_get_logic(GPIO_13); \
        tiny_printf_display(1); \
        if (logic == GPIO_LOGIC_HIGH) { \
            tiny_printf("gpio 13 is HIGH\n"); \
        } else { \
            tiny_printf("gpio 13 is LOW\n"); \
        } \
    } while(0)
#else
#define GPIO_TEST_CODE()
#endif

#if defined(UART1_TEST)
#define UART1_TEST_CODE() \
    do { \
        serial_uart1_init(921600); \
        serial_uart1_tx('u'); \
        serial_uart1_tx('a'); \
        serial_uart1_tx('r'); \
        serial_uart1_tx('t'); \
        serial_uart1_tx('1'); \
        serial_uart1_tx('_'); \
        serial_uart1_tx('t'); \
        serial_uart1_tx('e'); \
        serial_uart1_tx('s'); \
        serial_uart1_tx('t'); \
        serial_uart1_tx('\r'); \
        serial_uart1_tx('\n'); \
        while(!serial_uart1_rx_ready()); \
        int get_rx_data; \
        get_rx_data = serial_uart1_rx(); \
        serial_uart1_tx('\''); \
        serial_uart1_tx(get_rx_data); \
        serial_uart1_tx('\''); \
    } while(0)
#else
#define UART1_TEST_CODE()
#endif
// System will jump to the return address.
extern unsigned int __app_xip1;

#define BIT(n) (1<<n)

#if defined(BOOTLOADER_ENABLE_QE) && (BOOTLOADER_ENABLE_QE == 1)
void flash_write_enable(unsigned char *flash_tx, unsigned char *flash_rx) {
    flash_tx[0] = WRITE_ENABLE_CMD;
    flash_cmd(flash_tx, WRITE_ENABLE_TLEN, flash_rx, WRITE_ENABLE_RLEN);
}

void flash_wait_busy(unsigned char *flash_tx, unsigned char *flash_rx) {
    flash_tx[0] = READ_STATUS1_CMD;
    do {
        flash_cmd(flash_tx, READ_STATUS1_TLEN, flash_rx, READ_STATUS2_RLEN);
    } while(flash_rx[0] & BIT(0)); // check bit 0 is busy
}

void flash_set_qe_type0(unsigned char *flash_tx, unsigned char *flash_rx) {
    unsigned char status;
    flash_tx[0] = READ_STATUS1_CMD;
    flash_cmd(flash_tx, READ_STATUS1_TLEN, flash_rx, READ_STATUS1_RLEN);
    status = flash_rx[0];
    if (status & BIT(6)) {
        // enabled.
        return;
    }

    flash_write_enable(flash_tx, flash_rx);
    flash_wait_busy(flash_tx, flash_rx);

    flash_tx[0] = WRITE_STATUS1_CMD;
	flash_tx[1] = status | BIT(6);

    flash_cmd(flash_tx, WRITE_STATUS1_TLEN, flash_rx, WRITE_STATUS1_RLEN);
    flash_wait_busy(flash_tx, flash_rx);
}

void flash_set_qe_type1(unsigned char *flash_tx, unsigned char *flash_rx) {
    unsigned char status1, status2;
    flash_tx[0] = READ_STATUS2_CMD;
	flash_cmd(flash_tx, READ_STATUS2_TLEN, flash_rx, READ_STATUS2_RLEN);	//qe is S9, status2 bit1
    status2 = flash_rx[0];
    if (status2 & BIT(1)) {
        // enabled.
        return;
    }

    flash_tx[0] = READ_STATUS1_CMD;
    flash_cmd(flash_tx, READ_STATUS1_TLEN, flash_rx, READ_STATUS1_RLEN);
    status1 = flash_rx[0];

    flash_write_enable(flash_tx, flash_rx);
    flash_wait_busy(flash_tx, flash_rx);

    flash_tx[0] = WRITE_STATUS1_AND_2_CMD;
    flash_tx[1] = status1;
	flash_tx[2] = status2 | BIT(1);
    flash_cmd(flash_tx, WRITE_STATUS1_AND_2_TLEN, flash_rx, WRITE_STATUS1_AND_2_RLEN);
    flash_wait_busy(flash_tx, flash_rx);
}

void flash_set_qe_type2(unsigned char *flash_tx, unsigned char *flash_rx) {
    unsigned char status2;
    flash_tx[0] = READ_STATUS2_CMD;
	flash_cmd(flash_tx, READ_STATUS2_TLEN, flash_rx, READ_STATUS2_RLEN);	//qe is S9, status2 bit1
    status2 = flash_rx[0];
    if (status2 & BIT(1)) {
        // enabled.
        return;
    }

    flash_write_enable(flash_tx, flash_rx);
    flash_wait_busy(flash_tx, flash_rx);

    flash_tx[0] = WRITE_STATUS2_CMD;
	flash_tx[1] = status2 | BIT(1);
    flash_cmd(flash_tx, WRITE_STATUS2_TLEN, flash_rx, WRITE_STATUS2_RLEN);
    flash_wait_busy(flash_tx, flash_rx);
}
#endif

void custom_upgrade() {
#if defined(FOTA_OPTION) && (FOTA_OPTION == 1)
    fota_fs_upgrade();
#endif
#if defined(UART_UPGRADE_EN) && (UART_UPGRADE_EN == 1)
    uart_fw_upgrade(500);   // wait 500mS for uart fw upgrade
#endif

#if defined(BOOTLOADER_ENABLE_QE) && (BOOTLOADER_ENABLE_QE == 1)
    {
        // qe enable demo.
        unsigned int flash_tx_aligned[4];
        unsigned int flash_rx_aligned[4];
        unsigned char *flash_tx = (unsigned char *)flash_tx_aligned;
        unsigned char *flash_rx = (unsigned char *)flash_rx_aligned;
        // step 1. get flash jedid
        flash_tx[0] = JEDEC_ID_CMD_CMD;
        flash_cmd(flash_tx, JEDEC_ID_CMD_TLEN, flash_rx, JEDEC_ID_CMD_RLEN);

        // step 2. switch qe bit method.
        switch(flash_rx[0]) {
            case MANUFACTURER_ID_GIGADEVICE:
                if (flash_rx[2] == 0x17) { // GD25Q64C
                    flash_set_qe_type2(flash_tx, flash_rx);
                } else if (flash_rx[2] == 0x15) { //GD25Q16C
                    flash_set_qe_type1(flash_tx, flash_rx);
                } else { // GD others.
                    flash_set_qe_type1(flash_tx, flash_rx);
                }
                break;
            case MANUFACTURER_ID_WINBOND:
                if (flash_rx[2] == 0x17) { // W25Q64JV
                    flash_set_qe_type2(flash_tx, flash_rx);
                } else if (flash_rx[2] == 0x15) { //W25Q16JV
                    flash_set_qe_type1(flash_tx, flash_rx);
                } else { // Winbond others.
                    flash_set_qe_type1(flash_tx, flash_rx);
                }
                break;
            case MANUFACTURER_ID_MXIC:
                flash_set_qe_type0(flash_tx, flash_rx);
                break;
            case MANUFACTURER_ID_EON:
                break;
            case MANUFACTURER_ID_XTX:
            case MANUFACTURER_ID_ZETTA:
                flash_set_qe_type1(flash_tx, flash_rx);
                break;
            default:
                break;
        }
    }
#endif
}

void * custom_boot_addr() {

    // flash test example code.
    int long_wait;
    (void) long_wait;

    FLASH_TEST_CODE();
    GPIO_TEST_CODE();
    UART1_TEST_CODE();

    //return 1: use original FOTA
    //return jump adress, custom own FOTA.
    //return &__app_xip1;
    return (void *)1;
}

