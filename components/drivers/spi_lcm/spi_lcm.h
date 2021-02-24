/**
 * @file spi_lcm.h
 */

#ifndef SPI_LCM
#define SPI_LCM

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdbool.h>
#include <spi_lcm_hw.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void spi_lcm_init(spi_lcm_hal_t *lcm);
void spi_lcm_flush(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t * color_map, void (*done_cb)(void *), void *param);
void spi_lcm_enable_backlight(int backlight);
int spi_lcm_is_busy();

extern spi_lcm_hal_t M_LCM_DRV;

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard */
