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
//#define BK_LIGHT_PIN        M_LCM_BK_LIGHT_PIN

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void spi_lcm_init(void);
void set_backlight( uint8_t percent);
void spi_lcm_acquire_bus(void);
void spi_lcm_release_bus(void);
void spi_lcm_write_cmd( uint8_t cmd);
void spi_lcm_write_data_byte( uint8_t byte);


/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*DISP_SPI_H*/
