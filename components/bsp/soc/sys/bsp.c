#include "osal.h"
#include "xip.h"
#if defined(SUPPORT_FFS)
#include <fsal.h>
#endif
#include "backtrace.h"
#include "uart/drv_uart.h"
#include "uart/drv_comport.h"
#include "pinmux/drv_pinmux.h"
#include "wifi_api.h"
#include "lowpower.h"
#if defined(ROM_MODE)
#include <rom_init.h>
#endif
#include "gpio/drv_gpio.h"
#include <stdio.h>
#include <sys_info.h>
#ifdef SUPPORT_SDC
#include "sd_diskio.h"
#endif
#include "sys/flash.h"
#if(CHIP_ID!=6006)
#ifdef SUPPORT_CRYPTO_ENGINE
#include "crypto_common.h"
#include "crypto_register_banks.h"
#endif
#endif
#include <cxx_init.h>

const int g_fsal_fds = 16;
const int g_fsal_cache_pages = 8;

#if (CHIP_ID == 6020) && (CHIP_SUB_ID == 2)
#define rom_init_bss()
#define rom_init_data()
#endif

#if defined(SUPPORT_LOW_POWER) && (SUPPORT_LOW_POWER == 1)
void bsp_rtc_startup (void *pdata) {
    #if !defined(FPGA) && !defined(FPGAv2)
    sys_rtc_cali();
    #endif
    OS_TaskDelete(NULL);
}
#endif

#if defined(SUPPORT_FFS)
SSV_FS fs_handle;
#endif
#if defined(SETTING_RTC_CALI_INTERVAL) && (SETTING_RTC_CALI_INTERVAL != 0)
//OsTimer g_rtc_cali_tmr;
#endif
void bsp_init() {

    //adjust priority, ble set 3, flash set 2, other set 1
    REG32(0xD0000000) = 1;
    REG32(0xD0000020) = 3;
    REG32(0xD0000024) = 2;

#if defined(SUPPORT_MCU_UNALIGNMENT) && (SUPPORT_MCU_UNALIGNMENT == 1)
    extern void mcu_unalignment();
    mcu_unalignment();
#endif

#if defined(SUPPORT_HOST_IF) && (SUPPORT_HOST_IF == 0)
    sys_hwif_power_off();
#endif

#if (UART_IO_NUM == 0)
    DRV_COMPORT_INIT(COMPORT_UART);
#elif (UART_IO_NUM == 1)
    DRV_COMPORT_INIT(COMPORT_HSUART1);
#elif (UART_IO_NUM == 2)
    DRV_COMPORT_INIT(COMPORT_HSUART2);
#else
    DRV_COMPORT_INIT(COMPORT_UART);
#endif

#if defined(UART_BAUD_RATE)
    drv_comport_set_format(UART_BAUD_RATE, COMPORT_WORD_LEN_8, COMPORT_STOP_BIT_1, COMPORT_PARITY_DISABLE);
#else
    drv_comport_set_format(115200, COMPORT_WORD_LEN_8, COMPORT_STOP_BIT_1, COMPORT_PARITY_DISABLE);
#endif
#if defined(SUPPORT_LOW_POWER) && (SUPPORT_LOW_POWER == 1)
    sys_lowpower_init();
#endif

#if defined(ROM_MODE)
    sys_rom_invaild(ROM_VERSION);
    rom_init_bss();
    rom_init_data();
#endif

#if defined(SUPPORT_CXX) && (SUPPORT_CXX==1)
    sys_cxx_init();
#endif

    OS_Init();
#if defined(OSAL_SYS_INFO_EN)
    OS_StatInit();
#endif
    OS_MemInit();
    OS_PsramInit();

#ifdef SUPPORT_SDC
    sd_spi_driver_init();
#endif

#if defined(SUPPORT_FFS)
    fs_handle = FS_init();
    if (fs_handle) {
#ifdef SUPPORT_SDC
        fs_handle->support_sdc = true;
#else
        fs_handle->support_sdc = false;
#endif
    }
#else
    if(!flash_init())
    {
        printf("invalid flash, please check\n");
    }

#endif
#if(CHIP_ID!=6006)
#ifdef SUPPORT_CRYPTO_ENGINE
    crypto_init();
#endif
#endif
#if defined(SUPPORT_LOW_POWER) && (SUPPORT_LOW_POWER == 1)
    OS_TaskCreate(bsp_rtc_startup, "rtc", 512, NULL, OS_TASK_HIGH_PRIO, NULL);
#endif

    flash_register_pmu();
}

extern int __sys_mcu_speed;

uint32_t system_us2delaytick(uint32_t us)
{
    return us*27 * ((((int)&__sys_mcu_speed)+159)/160);
}

// one tick is ~75nS.
void system_delay(uint32_t delaytick) ATTRIBUTE_SECTION_FBOOT;
void system_delay(uint32_t delaytick) {
    volatile int idx = delaytick;
    if (delaytick <= 0) return;
    while(idx--);
    //while(idx--) asm("nop");
}

void vAssertCalled( const char *func, int line )
{
	__nds32__gie_dis();
	printf("<!!!OS Assert!!!> func = %s, line=%d\n", func, line);
	print_callstack();
	while(1);
}

#define M_GPIO_DEFAULT          (0)
#define M_GPIO_USER_DEFINED     (1)

#define SDIO_PULLUP_MASK        (BIT(SDIOS_DAT2) | BIT(SDIOS_DAT1) | BIT(SDIOS_DAT0) | BIT(SDIOS_CMD) | BIT(SDIOS_DAT3))
#define SDIO_PULLDOWN_MASK      (BIT(SDIOS_CLK))
#define SDIO_MASK               (SDIO_PULLUP_MASK | SDIO_PULLDOWN_MASK)

// this will increase current.
int lowpower_sleep_gpio_hook() ATTRIBUTE_SECTION_FAST;
int lowpower_sleep_gpio_hook() {
#if defined(SUPPORT_HOST_IF) && (SUPPORT_HOST_IF == 0)
    // do your gpio setting
    //return M_GPIO_USER_DEFINED;
    // use default gpio setting.
    return M_GPIO_DEFAULT;
#else
    // host low power.
    hal_gpio_set_manual_pull_raw(SDIO_MASK, SDIO_PULLUP_MASK, SDIO_PULLDOWN_MASK, 0);
    hal_gpio_set_pull_raw(SDIO_MASK, SDIO_PULLUP_MASK, SDIO_PULLDOWN_MASK, 0);
    return M_GPIO_USER_DEFINED;
#endif
}

// this will increase current.
int lowpower_dormant_gpio_hook() {
#if defined(SUPPORT_HOST_IF) && (SUPPORT_HOST_IF == 0)
    // do your gpio setting
    //return M_GPIO_USER_DEFINED;
    // use default gpio setting.
    return M_GPIO_DEFAULT;
#else
    // host low power.
    hal_gpio_set_manual_pull_raw(SDIO_MASK, SDIO_PULLUP_MASK, SDIO_PULLDOWN_MASK, 0);
    hal_gpio_set_pull_raw(SDIO_MASK, SDIO_PULLUP_MASK, SDIO_PULLDOWN_MASK, 0);
    return M_GPIO_USER_DEFINED;
#endif
}

void lowpower_pre_sleep_hook() ATTRIBUTE_SECTION_FAST;
void lowpower_pre_sleep_hook() {
    // do nothing
}

void lowpower_post_sleep_hook() ATTRIBUTE_SECTION_FAST;
void lowpower_post_sleep_hook() {
    // do nothing
}

extern char __memory_option;
extern char __fence__;
int system_has_ilm(void)
{
    return (((int)&__memory_option) == 1);
}

int system_has_dlm(void)
{
    return (((int)&__memory_option) == 1) && ((((uint32_t)&__fence__) & 0xFFF00000) == 0x00100000);
}

