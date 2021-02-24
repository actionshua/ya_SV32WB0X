
#include "drv_tmr.h"

int32_t drv_tmr_register_irq_handler (TM_ID_E tmr_id, isr_func tmr_irq_handler)
{
    if ((tmr_id == TM_TU0_US) || (tmr_id == TM_TM0_MS)) {
        //
        // TM_TU0_US and TM_TM0_MS unsupported
        //
        return -3;
    }

    return (hal_tm_register_irq_handler (tmr_id, tmr_irq_handler));
}

int32_t drv_tmr_clear_interrupt_status (TM_ID_E tmr_id)
{
    if ((tmr_id == TM_TU0_US) || (tmr_id == TM_TM0_MS)) {
        //
        // TM_TU0_US and TM_TM0_MS unsupported
        //
        return -3;
    }

    return (hal_tm_clear_int_sts (tmr_id));
}

int32_t drv_tmr_init (TM_ID_E tmr_id)
{
    if ((tmr_id == TM_TU0_US) || (tmr_id == TM_TM0_MS)) {
        //
        // TM_TU0_US and TM_TM0_MS unsupported
        //
        return -3;
    }

    return (hal_tm_init (tmr_id));
}

int32_t drv_tmr_deinit (TM_ID_E tmr_id)
{
    if ((tmr_id == TM_TU0_US) || (tmr_id == TM_TM0_MS)) {
        //
        // TM_TU0_US and TM_TM0_MS unsupported
        //
        return -3;
    }

    return (hal_tm_deinit (tmr_id));
}

int32_t drv_tmr_enable (TM_ID_E tmr_id, TM_MODE_E tmr_mode, uint32_t tmr_init_count)
{
    if ((tmr_id == TM_TU0_US) || (tmr_id == TM_TM0_MS)) {
        //
        // TM_TU0_US and TM_TM0_MS unsupported
        //
        return -3;
    }

#if(CHIP_ID==6006)
    tmr_init_count = tmr_init_count &0xffff;
#endif
    return (hal_tm_enable (tmr_id, tmr_mode, tmr_init_count));
}

int32_t drv_tmr_disable (TM_ID_E tmr_id)
{
    if ((tmr_id == TM_TU0_US) || (tmr_id == TM_TM0_MS)) {
        //
        // TM_TU0_US and TM_TM0_MS unsupported
        //
        return -3;
    }

    return (hal_tm_disable (tmr_id));
}

int32_t drv_tmr_sw_rst (TM_ID_E tmr_id)
{
    if ((tmr_id == TM_TU0_US) || (tmr_id == TM_TM0_MS)) {
        //
        // TM_TU0_US and TM_TM0_MS unsupported
        //
        return -3;
    }

    return (hal_tm_sw_rst (tmr_id));
}

int32_t drv_tmr_get_init_count (TM_ID_E tmr_id)
{
    return (hal_tm_get_init_value (tmr_id));
}

int32_t drv_tmr_get_mode (TM_ID_E tmr_id)
{
    return (hal_tm_get_mode (tmr_id));
}

int32_t drv_tmr_get_interrupt_status (TM_ID_E tmr_id)
{
    return (hal_tm_get_int_sts (tmr_id));
}

uint32_t drv_tmr_get_current_count (TM_ID_E tmr_id)
{
    return (hal_tm_get_cur_value (tmr_id));
}
#if(CHIP_ID==6020)
int32_t drv_tmr_set_current_count (TM_ID_E tmr_id, uint32_t tmr_init_count)
{
    return (hal_tm_set_cur_value (tmr_id, tmr_init_count));
}
#endif
