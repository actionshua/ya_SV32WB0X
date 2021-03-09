#include "soc_types.h"
#include "soc_defs.h"

#include "gpio/hal_gpio.h"
#include "pinmux/hal_pinmux.h"
#include "custom_io_hal.h"
#include "custom_io_chk.h"
#include "attrs.h"

#include "soc_pad_cfg.h"

#if defined(DEBUG)
#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)
#define VAR_NAME_VALUE(var) #var "="  VALUE(var)

#pragma message(VAR_NAME_VALUE(_M_PIN_MODE))
#pragma message(VAR_NAME_VALUE(_M_FUNC_SEL))
#endif

const struct _pad_struct _pad_setting ATTRIBUTE_CFG_PAD = {
    .pre_magic = 0x50414453,  /* PADS */
#if (CHIP_ID == 6006)
    .pin_alt = {
		[0] = M_CUSTOM_P00_MODE,
		[1] = M_CUSTOM_P01_MODE,
		[2] = M_CUSTOM_P02_MODE,
		[3] = M_CUSTOM_P03_MODE,
		[4] = M_CUSTOM_P04_MODE,
		[5] = M_CUSTOM_P05_MODE,
		[6] = M_CUSTOM_P06_MODE,
		[7] = M_CUSTOM_P07_MODE,
		[8] = M_CUSTOM_P08_MODE,
		[9] = M_CUSTOM_P09_MODE,
		[10] = M_CUSTOM_P10_MODE,
		[11] = M_CUSTOM_P11_MODE,
		[12] = M_CUSTOM_P12_MODE,
		[13] = M_CUSTOM_P13_MODE,
		[20] = M_CUSTOM_P20_MODE,
		[21] = M_CUSTOM_P21_MODE,
		[22] = M_CUSTOM_P22_MODE},
    .pin_mode = { [0] = _M_PIN_MODE},
    .func_sel = { [0] = _M_FUNC_SEL},
#elif (CHIP_ID == 6020)
#if (CHIP_SUB_ID == 2)
    // 6020C
    .pin_alt = {
        [0] = M_CUSTOM_P00_MODE,
        [1] = M_CUSTOM_P01_MODE,
        [2] = M_CUSTOM_P02_MODE,
        [3] = M_CUSTOM_P03_MODE,
        [4] = M_CUSTOM_P04_MODE,
        [5] = M_CUSTOM_P05_MODE,
        [6] = M_CUSTOM_P06_MODE,
        [7] = M_CUSTOM_P07_MODE,
        [8] = M_CUSTOM_P08_MODE,
        [9] = M_CUSTOM_P09_MODE,
        [10] = M_CUSTOM_P10_MODE,
        [11] = M_CUSTOM_P11_MODE,
        [12] = M_CUSTOM_P12_MODE,
        [13] = M_CUSTOM_P13_MODE,
        [14] = M_CUSTOM_P14_MODE,
        [15] = M_CUSTOM_P15_MODE,
        [16] = M_CUSTOM_P16_MODE,
        [17] = M_CUSTOM_P17_MODE,
        [18] = M_CUSTOM_P18_MODE,
        [19] = M_CUSTOM_P19_MODE,
        [20] = M_CUSTOM_P20_MODE,
        [21] = M_CUSTOM_P21_MODE,
        [22] = M_CUSTOM_P22_MODE,
        [23] = M_CUSTOM_P23_MODE,
        [24] = M_CUSTOM_P24_MODE,
        [25] = M_CUSTOM_P25_MODE,
        [26] = M_CUSTOM_P26_MODE,
        [27] = M_CUSTOM_P27_MODE,
        [28] = M_CUSTOM_P28_MODE,
        [29] = M_CUSTOM_P29_MODE,
		[30] = M_CUSTOM_P30_MODE,
		[31] = M_CUSTOM_P31_MODE,
		[32] = M_CUSTOM_P32_MODE,
		[33] = M_CUSTOM_P33_MODE,
		[34] = M_CUSTOM_P34_MODE,
		[35] = M_CUSTOM_P35_MODE,
		[36] = M_CUSTOM_P36_MODE,
		[37] = M_CUSTOM_P37_MODE},
    .pin_mode   = { [0] = _M_PIN_MODE,
					[1] = _M_PIN_MODE_32,},
    .func_sel   = { [0] = _M_FUNC_SEL,
                    [1] = _M_FUNC1_SEL, },
    .force_gpio = { [0] = _M_FORCE_GPIO,
					[1] = _M_FORCE_GPIO_32,},
#if !defined(IO_5V_PAD_LIMIT_TO_3V)
    .pad_5v_force_3v = 0,
#else
    .pad_5v_force_3v = IO_5V_PAD_LIMIT_TO_3V,
#endif
    .push_pull = {
        [0] = 0xFFFFFFFF,
        [1] = 0xFFFFFFFF,
        [2] = 0xFFFFFFFF,
        [3] = 0xFFFFFFFF,
    },
#elif (CHIP_SUB_ID == 1)
    // 6020B
    .pin_alt = {
        [0] = M_CUSTOM_P00_MODE,
        [1] = M_CUSTOM_P01_MODE,
		[2] = M_CUSTOM_P02_MODE,
		[3] = M_CUSTOM_P03_MODE,
		[4] = M_CUSTOM_P04_MODE,
		[5] = M_CUSTOM_P05_MODE,
        [6] = M_CUSTOM_P06_MODE,
        [7] = M_CUSTOM_P07_MODE,
        [8] = M_CUSTOM_P08_MODE,
        [9] = M_CUSTOM_P09_MODE,
        [10] = M_CUSTOM_P10_MODE,
        [11] = M_CUSTOM_P11_MODE,
        [12] = M_CUSTOM_P12_MODE,
        [13] = M_CUSTOM_P13_MODE,
        [14] = M_CUSTOM_P14_MODE,
        [15] = M_CUSTOM_P15_MODE,
        [16] = M_CUSTOM_P16_MODE,
        [17] = M_CUSTOM_P17_MODE,
        [18] = M_CUSTOM_P18_MODE,
        [19] = M_CUSTOM_P19_MODE,
        [20] = M_CUSTOM_P20_MODE,
        [21] = M_CUSTOM_P21_MODE,
        [22] = M_CUSTOM_P22_MODE,
        [23] = M_CUSTOM_P23_MODE,
        [24] = M_CUSTOM_P24_MODE,
        [25] = M_CUSTOM_P25_MODE,
        [26] = M_CUSTOM_P26_MODE,
        [27] = M_CUSTOM_P27_MODE,
        [28] = M_CUSTOM_P28_MODE,
        [29] = M_CUSTOM_P29_MODE,
		[30] = M_CUSTOM_P30_MODE,
		[31] = M_CUSTOM_P31_MODE,
		[32] = M_CUSTOM_P32_MODE,
		[33] = M_CUSTOM_P33_MODE,
		[34] = M_CUSTOM_P34_MODE,
		[35] = M_CUSTOM_P35_MODE},
    .pin_mode   = { [0] = _M_PIN_MODE,
					[1] = _M_PIN_MODE_32,},
    .func_sel   = { [0] = _M_FUNC_SEL,
                    [1] = _M_FUNC1_SEL, },
    .force_gpio = { [0] = _M_FORCE_GPIO,
					[1] = _M_FORCE_GPIO_32,},
#if !defined(IO_5V_PAD_LIMIT_TO_3V)
    .pad_5v_force_3v = 0,
#else
    .pad_5v_force_3v = IO_5V_PAD_LIMIT_TO_3V,
#endif
#else
    // 6020A5
    .pin_alt = {
        [6] = M_CUSTOM_P06_MODE,
        [7] = M_CUSTOM_P07_MODE,
        [8] = M_CUSTOM_P08_MODE,
        [9] = M_CUSTOM_P09_MODE,
        [10] = M_CUSTOM_P10_MODE,
        [11] = M_CUSTOM_P11_MODE,
        [12] = M_CUSTOM_P12_MODE,
        [13] = M_CUSTOM_P13_MODE,
        [14] = M_CUSTOM_P14_MODE,
        [15] = M_CUSTOM_P15_MODE,
        [16] = M_CUSTOM_P16_MODE,
        [17] = M_CUSTOM_P17_MODE,
        [18] = M_CUSTOM_P18_MODE,
        [19] = M_CUSTOM_P19_MODE,
        [20] = M_CUSTOM_P20_MODE,
        [21] = M_CUSTOM_P21_MODE,
        [22] = M_CUSTOM_P22_MODE,
        [23] = M_CUSTOM_P23_MODE,
        [24] = M_CUSTOM_P24_MODE,
        [25] = M_CUSTOM_P25_MODE,
        [26] = M_CUSTOM_P26_MODE,
        [27] = M_CUSTOM_P27_MODE,
        [28] = M_CUSTOM_P28_MODE,
        [29] = M_CUSTOM_P29_MODE},
    .pin_mode   = { [0] = _M_PIN_MODE   },
    .func_sel   = { [0] = _M_FUNC_SEL,
                    [1] = _M_FUNC1_SEL, },
    .force_gpio = { [0] = _M_FORCE_GPIO },
    .pad_5v_force_3v = 0,
#endif
#else
#error not support this CHIP_ID.
#endif
    .gpio_startup_setting_enable_mask = 0,
    .post_magic = 0x50414445, /* PADE */
};

