
#include <stdint.h>
#include "drv_wdt.h"
#include "hal_wdt.h"

int32_t drv_wdt_register_isr (WDT_ID_E wdt_id, uint8_t wdt_int_count_offset, WDT_ISR wdt_isr)
{
    return (hal_wdt_register_isr (wdt_id, wdt_int_count_offset, wdt_isr));
}

void drv_wdt_init (void)
{
    hal_wdt_init ();
}

void drv_wdt_deinit (void)
{
    hal_wdt_deinit ();
}

int32_t drv_wdt_enable (WDT_ID_E wdt_id, uint16_t wdt_init_count)
{
    return (hal_wdt_enable (wdt_id, wdt_init_count));
}

int32_t drv_wdt_disable (WDT_ID_E wdt_id)
{
    return (hal_wdt_disable (wdt_id));
}

int32_t drv_wdt_kick (WDT_ID_E wdt_id)
{
    int32_t wdt_status = 0;
    wdt_status = hal_wdt_get_enable(wdt_id);
    if (wdt_status == 1) {
        return (hal_wdt_kick (wdt_id));
    }
    if (wdt_status == 0) {
        return -1;
    }
    return wdt_status;
}

int32_t drv_wdt_set_init_count (WDT_ID_E wdt_id, uint16_t wdt_init_count)
{
    return (hal_wdt_set_time_cnt (wdt_id, wdt_init_count));
}

void drv_wdt_sw_rst (void)
{
    hal_wdt_sw_rst ();
}

int32_t drv_wdt_get_reset_info (WDT_ID_E wdt_id)
{
    return (hal_wdt_get_reset (wdt_id));
}
