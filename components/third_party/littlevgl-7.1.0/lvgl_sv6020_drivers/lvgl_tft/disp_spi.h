/**
 * @file disp_spi.h
 *
 */

#ifndef DISP_SPI_H
#define DISP_SPI_H

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
#define RESET_PIN           M_LCM_RESET_PIN
#define DC_PIN              M_LCM_DC_PIN
#define BK_LIGHT_PIN        M_LCM_BK_LIGHT_PIN

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void disp_spi_init(void);
 void setpin_reset(bool state);
 void set_backlight( uint8_t percent);
 void acquire_bus(void);
 void release_bus(void);
 void write_index( uint16_t index);
 void write_data( uint16_t data);
 void setreadmode(void);
 void setwritemode(void);
 uint16_t read_data(void);
 void write_cmd( uint8_t cmd);
 void write_data_byte( uint8_t byte);
 void write_fill_area_rgb( uint16_t byte, uint32_t cnt);


/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*DISP_SPI_H*/
