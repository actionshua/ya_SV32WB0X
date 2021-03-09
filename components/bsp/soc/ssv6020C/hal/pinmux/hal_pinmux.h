#ifndef __HAL_PINMUX_H__
#define __HAL_PINMUX_H__

typedef enum
{ // Register table "IO_REG" for 0xC0000560
    FUNCTION_NONE   	= -1,
	SEL_ADC0			= 0,
	SEL_ADC1			= 1,
	SEL_ADC2			= 2,
	SEL_ADC3			= 3,
	SEL_ADC4			= 4,
	SEL_ADC5			= 5,
	SEL_ADC6			= 6,
	SEL_ADC7			= 7,
	SEL_ANTSW			= 8,
    SEL_ANTSW_II		= 9,
	SEL_BTCX			= 10,
	SEL_BTCX_II			= 11,
	SEL_UART0			= 12,
	SEL_UART0_II		= 13,
	SEL_UART1			= 14,
    SEL_UART1_II		= 15,
	SEL_UART2			= 16,
	SEL_UART2_II		= 17,
    SEL_UART2_III		= 18,
	SEL_UART2_RTSCTS	= 19,
	SEL_I2C0			= 20,
    SEL_I2C0_II			= 21,
    SEL_I2C1			= 22,
	SEL_PDMTX0			= 23,
	SEL_PDMTX0_II		= 24,
	SEL_PDMRX0			= 25,
	SEL_PDMRX0_II		= 26,
	SEL_PDMRX1			= 27,
	SEL_PDMRX1_II		= 28,
} pinmux_fun_t;

typedef enum
{ // Register table "IO_REG" for 0xC0000564
	SEL_I2S0				= 0,
	SEL_I2S1				= 1,
	SEL_I2S0_MCLK			= 2,
	SEL_I2S0_MCLK_II		= 3,
    SEL_I2S0_MCLK_III		= 4,
	SEL_SPIMAS0				= 5,
	SEL_SPIMAS0_CSN			= 6,
	SEL_SPIMAS0_CSN_II		= 7,
	SEL_SPIMAS1         	= 8,
	SEL_SPIMAS2 			= 9,
	SEL_SPIMAS2_CSN			= 10,
	SEL_SPIMAS2_CSN_II		= 11,
	SEL_SPISLV0				= 12,
	SEL_SPISLV0_CSN			= 13,
	SEL_SPISLV0_CSN_II		= 14,
	SEL_SPISLV1         	= 15,
	SEL_PSRAM_CSN			= 16,
	SEL_FLASH				= 17,
	SEL_SDIO_IOT			= 18,
	SEL_SPIDATA_IOT			= 19,
	SPI_RAW_DATA			= 20,
} pinmux_fun1_t;

enum specify_i2c_pin
{
    SPECIFY_I2C1_SCL    = 0,
    SPECIFY_I2C1_SDA    = 4,
};

enum specify_spi_pin
{
    SPECIFY_SPI1_CLK    = 0x0,
    SPECIFY_SPI1_MISO   = 0x4,
    SPECIFY_SPI1_MOSI   = 0x8,
    SPECIFY_SPI1_CSN    = 0xC,
    SPECIFY_SPI2_CLK    = 0x10,
    SPECIFY_SPI2_MISO   = 0x14,
    SPECIFY_SPI2_MOSI   = 0x18,
    SPECIFY_SPI2_CSN    = 0x1C,
};

int8_t hal_pinmux_manual_function_select_enable(pinmux_fun_t fun_sel);
int8_t hal_pinmux_manual_function_select_disable(pinmux_fun_t fun_sel);
//void hal_pinmux_set_raw(uint32_t io_sel, uint32_t fun_sel, uint32_t fun1_sel);
void hal_pinmux_set_raw_ex(uint32_t io_sel, uint32_t io_sel32, uint32_t fun_sel, uint32_t fun1_sel);
void hal_pinmux_set_force_gpio(uint32_t force_gpio);
void hal_pinmux_set_force_gpio_32(uint32_t force_gpio32);
void hal_pinmux_set_specify_pwm(uint32_t idx, uint32_t cfg);
void hal_pinmux_set_specify_pwm_32(uint32_t idx32, uint32_t cfg32);
//void hal_pinmux_set_specify_i2c(enum specify_i2c_pin pin, uint32_t cfg);
//void hal_pinmux_set_specify_spi(enum specify_spi_pin pin, uint32_t cfg);
void hal_pinmux_set_specify_io(uint32_t io_cfg);
void hal_pinmux_set_specify_io_32(uint32_t io_cfg32);
void hal_pinmux_set_5v_pad(uint32_t pad_5v_force_3v);
void hal_pinmux_pin_manual_io(uint32_t manual_gpio);
void hal_pinmux_pin_manual_io_32(uint32_t manual_gpio32);
void hal_pinmux_pin_manual_force_gpio(uint32_t manual_gpio);
void hal_pinmux_pin_manual_force_gpio_32(uint32_t manual_gpio32);
void hal_pinmux_pin_manual_restore_gpio(uint32_t manual_gpio);
void hal_pinmux_pin_manual_restore_gpio_32(uint32_t manual_gpio32);
void hal_pinmux_push_pull(uint32_t *push_pull);

#endif  // __HAL_PINMUX_H__
