#ifndef __HAL_GPIO_H__
#define __HAL_GPIO_H__
#include "sys/intc.h"   // components/

typedef enum
{
    PIN_MODE_GPIO     = 0,       /**< Gpio mode */
    PIN_MODE_ZSTATE   = 1
} pin_mode_t;


typedef enum
{
    PIN_NONE            = -1,
    SPI_M_CS            = 15,

    SDIOS_DAT2          = 17,
    SDIOS_DAT3          = 18,
    SDIOS_CMD           = 19,
    SDIOS_CLK           = 20,
    SDIOS_DAT0          = 21,
    SDIOS_DAT1          = 22,

    GPIO_00             = 0,
    GPIO_01             = 1,
    GPIO_02             = 2,
    GPIO_03             = 3,
    GPIO_04             = 4,
    GPIO_05             = 5,
    GPIO_06             = 6,
    GPIO_07             = 7,
    GPIO_08             = 8,
    GPIO_09             = 9,
    GPIO_10             = 10,
    GPIO_11             = 11,
    SIO_12              = 12,
    SIO_13              = 13,
    GPIO_14             = 14,
    GPIO_15             = 15,
    GPIO_16             = 16,
    GPIO_17             = 17,
    GPIO_18             = 18,
    GPIO_19             = 19,
    GPIO_20             = 20,
    GPIO_21             = 21,
    GPIO_22             = 22,
    GPIO_23             = 23,
    GPIO_24             = 24,
    GPIO_25             = 25,
    GPIO_26             = 26,
    GPIO_27             = 27,
    SIO_28              = 28,
    GPIO_29             = 29,
	GPIO_30             = 30,
	GPIO_31             = 31,
	GPIO_32             = 32,
	GPIO_33             = 33,
	SIO_34              = 34,
	GPIO_35             = 35,
	GPIO_36             = 36,
	GPIO_37             = 37,
	GPIO_MAX            = GPIO_37,
} gpio_pin_t;


typedef enum
{
    GPIO_DIR_IN         = 0,        /**< GPIO direction INPUT */
    GPIO_DIR_OUT        = 1,        /**< GPIO direction OUTPUT */
    GPIO_DIR_IN_OUT     = 2,        /**< GPIO direction INPUT and OUTPUT */
    GPIO_DIR_IN_OUT_OFF = 3         /**< GPIO direction INPUT and OUTPUT OFF*/
} gpio_dir_t;

typedef enum
{
    GPIO_PULL_DOWN      = 0,        /**< GPIO Pull Down */
    GPIO_PULL_UP        = 1,         /**< GPIO Pull Up */
    GPIO_PULL_NONE      = 2,
    GPIO_PULL_ERROR     = 3,
} gpio_pull_t;

typedef enum
{
    GPIO_DRIVING_WEAK       = 0,         /**< GPIO weak driving strenght */
    GPIO_DRIVING_STRONG     = 1          /**< GPIO strong driving streght */
} gpio_driving_strengh_t;


typedef enum
{
    GPIO_LOGIC_LOW    = 0,         /**< GPIO logic state LOW */
    GPIO_LOGIC_HIGH   = 1          /**< GPIO logic state HIGH */
} gpio_logic_t;


typedef enum
{
    GPIO_INTC_HIGH_LEVEL    = 2,
    GPIO_INTC_RISING_EDGE   = 3,
    GPIO_INTC_LOW_LEVEL     = 4,
    GPIO_INTC_FALLING_EDGE  = 5
} gpio_intc_trigger_mode_t;

typedef enum
{
    GPIO_00_TO_07   = 0,
    GPIO_08_TO_15   = 1,
    GPIO_16_TO_23   = 2,
    GPIO_24_TO_31   = 3,
    GPIO_32_TO_39   = 4,
} gpio_intc_group_t;


int8_t hal_gpio_set_mode(gpio_pin_t pin, pin_mode_t mode);
int8_t hal_gpio_set_dir(gpio_pin_t pin, gpio_dir_t dir);
gpio_dir_t hal_gpio_get_dir(gpio_pin_t pin);
int8_t hal_gpio_set_pull(gpio_pin_t pin, gpio_pull_t pull);
gpio_pull_t hal_gpio_get_pull(gpio_pin_t pin);
int8_t hal_gpio_set_logic(gpio_pin_t pin, gpio_logic_t logic);
int8_t hal_gpio_set_driving_strengh(gpio_pin_t pin, gpio_driving_strengh_t driving_streght);
int8_t hal_gpio_set_interrupt(gpio_pin_t pin);
gpio_logic_t hal_gpio_get_logic(gpio_pin_t pin);

int8_t hal_gpio_intc_trigger_mode(gpio_pin_t pin, gpio_intc_trigger_mode_t mode);
int8_t hal_gpio_register_isr(gpio_pin_t pin, isr_func handler);
int8_t hal_gpio_intc_clear_counter(gpio_pin_t pin);

int8_t hal_gpio_set_wakeup_enable(gpio_pin_t pin);
int8_t hal_gpio_set_wakeup_disable(gpio_pin_t pin);
int8_t hal_gpio_set_wakeup_detect(gpio_intc_trigger_mode_t int_mode);
int8_t hal_gpio_set_wakeup_enable_with_level(gpio_pin_t pin, int level);

void hal_gpio_set_manual_pull_raw(uint32_t enable_mask, uint32_t pue, uint32_t pde, uint32_t ds);
void hal_gpio_set_pull_raw(uint32_t enable_mask, uint32_t pue, uint32_t pde, uint32_t ds);
void hal_gpio_set_io_raw(uint32_t enable_mask, uint32_t output, uint32_t pie, uint32_t poen);
#endif  // __HAL_GPIO_H__

