#ifndef SOC_PAD_CFG_H
#define SOC_PAD_CFG_H

#include <stdint.h>

struct _pad_struct {
    uint32_t pre_magic;
#if (CHIP_ID == 6020)
    uint32_t pin_alt[64];
#elif (CHIP_ID == 6006)
    uint32_t pin_alt[32];
#endif
    uint32_t pin_mode[4];
    uint32_t func_sel[4];
#if (CHIP_ID == 6020)
    uint32_t force_gpio[4];
    uint32_t pad_5v_force_3v;
    uint32_t push_pull[4];
#endif
    uint32_t gpio_startup_setting_enable_mask;
    uint32_t gpio_manual_pu[4];
    uint32_t gpio_manual_pd[4];
    uint32_t gpio_manual_ds[4];
    uint32_t gpio_output[4];
    uint32_t gpio_input_enable[4];
    uint32_t gpio_output_disable[4];
    uint32_t gpio_pue[4];
    uint32_t gpio_pde[4];
    uint32_t gpio_ds[4];
    uint32_t gpio_int[4];
    uint32_t post_magic;
};

#endif /* end of include guard: SOC_PAD_CFG_H */
;
