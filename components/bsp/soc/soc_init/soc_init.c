#include <nds32_intrinsic.h>
#include "soc_types.h"
#include "soc_defs.h"

#if defined(XIP_MODE)
#include "gpio/hal_gpio.h"
#include "pinmux/hal_pinmux.h"
#include "custom_io_hal.h"
#include "custom_io_chk.h"
#include "soc_pad_cfg.h"
#endif

#include "attrs.h"

extern struct _pad_struct _pad_setting;

#if defined(XIP_MODE)
uint32_t _soc_io_init(void)
{
    if ((_pad_setting.pre_magic == 0x50414453) && (_pad_setting.post_magic ==0x50414445)) {
        //printf("manual io = 0x%x, func sel = 0x%x, gpio enable mask = 0x%x\n", _pad_setting.pin_mode[0], _pad_setting.func_sel[0], _pad_setting.gpio_startup_setting_enable_mask);
#if (CHIP_ID == 6020)
        hal_pinmux_set_force_gpio(_pad_setting.force_gpio[0]);
		hal_pinmux_set_force_gpio_32(_pad_setting.force_gpio[1]);
#if (CHIP_SUB_ID == 0)
        hal_pinmux_set_raw(_pad_setting.pin_mode[0], _pad_setting.func_sel[0], _pad_setting.func_sel[1]);
#else
        hal_pinmux_set_raw_ex(_pad_setting.pin_mode[0], _pad_setting.pin_mode[1], _pad_setting.func_sel[0], _pad_setting.func_sel[1]);
        hal_pinmux_set_5v_pad(_pad_setting.pad_5v_force_3v);
#endif
#if (CHIP_SUB_ID == 2)
        hal_pinmux_push_pull(_pad_setting.push_pull);
#endif
#if defined(M_CUSTOM_PWM0_PIN)
        hal_pinmux_set_specify_pwm(0, _M_CUSTOM_PWM0_PIN);
#endif
#if defined(M_CUSTOM_PWM1_PIN)
        hal_pinmux_set_specify_pwm(1, _M_CUSTOM_PWM1_PIN);
#endif
#if defined(M_CUSTOM_PWM2_PIN)
        hal_pinmux_set_specify_pwm(2, _M_CUSTOM_PWM2_PIN);
#endif
#if defined(M_CUSTOM_PWM3_PIN)
        hal_pinmux_set_specify_pwm(3, _M_CUSTOM_PWM3_PIN);
#endif
#if defined(M_CUSTOM_PWM4_PIN)
        hal_pinmux_set_specify_pwm(4, _M_CUSTOM_PWM4_PIN);
#endif
#if defined(M_CUSTOM_PWM5_PIN)
        hal_pinmux_set_specify_pwm(5, _M_CUSTOM_PWM5_PIN);
#endif
#if defined(M_CUSTOM_PWM6_PIN)
        hal_pinmux_set_specify_pwm(6, _M_CUSTOM_PWM6_PIN);
#endif
#if defined(M_CUSTOM_PWM7_PIN)
        hal_pinmux_set_specify_pwm(7, _M_CUSTOM_PWM7_PIN);
#endif
#if defined(M_CUSTOM_I2CM1_SDA_PIN)
        hal_pinmux_set_specify_i2c(SPECIFY_I2C1_SDA, _M_CUSTOM_I2CM1_SDA_PIN);
#endif
#if defined(M_CUSTOM_I2CM1_SCL_PIN)
        hal_pinmux_set_specify_i2c(SPECIFY_I2C1_SCL, _M_CUSTOM_I2CM1_SCL_PIN);
#endif

#if defined(M_CUSTOM_SPIM1_CSN_PIN)
        hal_pinmux_set_specify_spi(SPECIFY_SPI1_CSN, _M_CUSTOM_SPIM1_CSN_PIN);
#endif
#if defined(M_CUSTOM_SPIM1_CLK_PIN)
        hal_pinmux_set_specify_spi(SPECIFY_SPI1_CLK, _M_CUSTOM_SPIM1_CLK_PIN);
#endif
#if defined(M_CUSTOM_SPIM1_MISO_PIN)
        hal_pinmux_set_specify_spi(SPECIFY_SPI1_MISO, _M_CUSTOM_SPIM1_MISO_PIN);
#endif
#if defined(M_CUSTOM_SPIM1_MOSI_PIN)
        hal_pinmux_set_specify_spi(SPECIFY_SPI1_MOSI, _M_CUSTOM_SPIM1_MOSI_PIN);
#endif
#if defined(M_CUSTOM_SPIM2_CSN_PIN)
        hal_pinmux_set_specify_spi(SPECIFY_SPI2_CSN, _M_CUSTOM_SPIM2_CSN_PIN);
#endif
#if defined(M_CUSTOM_SPIM2_CLK_PIN)
        hal_pinmux_set_specify_spi(SPECIFY_SPI2_CLK, _M_CUSTOM_SPIM2_CLK_PIN);
#endif
#if defined(M_CUSTOM_SPIM2_MISO_PIN)
        hal_pinmux_set_specify_spi(SPECIFY_SPI2_MISO, _M_CUSTOM_SPIM2_MISO_PIN);
#endif
#if defined(M_CUSTOM_SPIM2_MOSI_PIN)
        hal_pinmux_set_specify_spi(SPECIFY_SPI2_MOSI, _M_CUSTOM_SPIM2_MOSI_PIN);
#endif

#if (_M_SPECIFY_IO != 0)
        hal_pinmux_set_specify_io(_M_SPECIFY_IO);
#endif

//for gpio 32~37 pwm setting-------------------------------------
#if defined(M_CUSTOM_PWM0_32_PIN)
        hal_pinmux_set_specify_pwm_32(0, _M_CUSTOM_PWM0_32_PIN);
#endif
#if defined(M_CUSTOM_PWM1_32_PIN)
        hal_pinmux_set_specify_pwm_32(1, _M_CUSTOM_PWM1_32_PIN);
#endif
#if defined(M_CUSTOM_PWM2_32_PIN)
        hal_pinmux_set_specify_pwm_32(2, _M_CUSTOM_PWM2_32_PIN);
#endif
#if defined(M_CUSTOM_PWM3_32_PIN)
        hal_pinmux_set_specify_pwm_32(3, _M_CUSTOM_PWM3_32_PIN);
#endif
#if defined(M_CUSTOM_PWM4_32_PIN)
        hal_pinmux_set_specify_pwm_32(4, _M_CUSTOM_PWM4_32_PIN);
#endif
#if defined(M_CUSTOM_PWM5_32_PIN)
        hal_pinmux_set_specify_pwm_32(5, _M_CUSTOM_PWM5_32_PIN);
#endif
#if defined(M_CUSTOM_PWM6_32_PIN)
        hal_pinmux_set_specify_pwm_32(6, _M_CUSTOM_PWM6_32_PIN);
#endif
#if defined(M_CUSTOM_PWM7_32_PIN)
        hal_pinmux_set_specify_pwm_32(7, _M_CUSTOM_PWM7_32_PIN);
#endif

#if (_M_SPECIFY_IO_32 != 0)
        hal_pinmux_set_specify_io_32(_M_SPECIFY_IO_32);
#endif
#elif (CHIP_ID == 6006)
#if defined(SETTING_ROM_BOOT) && (SETTING_ROM_BOOT == 1)
        hal_pinmux_set_raw(_pad_setting.pin_mode[0] | 0xfc000, _pad_setting.func_sel[0] | 0x400);
#else
        hal_pinmux_set_raw(_pad_setting.pin_mode[0], _pad_setting.func_sel[0]);
#endif
#else
    #error not support CHIP_ID
#endif
        if (_pad_setting.gpio_startup_setting_enable_mask) {
            /// initial gpio
            hal_gpio_set_pull_raw(_pad_setting.gpio_startup_setting_enable_mask,
                    _pad_setting.gpio_pue[0],
                    _pad_setting.gpio_pde[0],
                    _pad_setting.gpio_ds[0]);
            hal_gpio_set_manual_pull_raw(_pad_setting.gpio_startup_setting_enable_mask,
                    _pad_setting.gpio_pue[0],
                    _pad_setting.gpio_pde[0],
                    _pad_setting.gpio_ds[0]);

            hal_gpio_set_io_raw(_pad_setting.gpio_startup_setting_enable_mask,
                    _pad_setting.gpio_output[0],
                    _pad_setting.gpio_input_enable[0],
                    _pad_setting.gpio_output_disable[0]);
        }
        return 1;
    } else {
        //printf("soc_io_init pinmux magic is wrong\n");
        return 0;
    }
}
#endif

