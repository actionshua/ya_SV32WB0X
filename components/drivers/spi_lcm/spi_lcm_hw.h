#ifndef SPI_LCM_HW_H
#define SPI_LCM_HW_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdbool.h>
#include "gpio/drv_gpio.h"
#include "spimst/drv_spimst.h"
#include "lcm_param.h"

#define M_LCM_SPI_ASYNC     (1)
//#define BK_LIGHT_PIN        M_LCM_BK_LIGHT_PIN

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    // check lcm exist?
    uint32_t (*probe)(void *param);
    // reset lcm
    void (*reset)();
    // do lcm init
    void (*init)();
    // check spi clock.
    uint32_t (*spi_clock)();
    // setup backlight
    void (*backlight)(uint32_t dim);
    // flush screen
    void (*flush)(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t * color_map, void (*done_cb)(void *), void *param);
} spi_lcm_hal_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/
void set_backlight( uint8_t percent);
void spi_lcm_acquire_bus(void);
void spi_lcm_release_bus(void);

void spi_lcm_hw_init(void);
void spi_lcm_hw_write_cmd( uint8_t cmd);
void spi_lcm_hw_write_data_byte(uint8_t byte);
void spi_lcm_hw_write_data(uint16_t byte);
void spi_lcm_hw_write_buf(uint8_t *buf, uint32_t cnt, void (*done_cb)(void *), void *param);
void spi_lcm_hw_setpin_reset(gpio_logic_t logic);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
