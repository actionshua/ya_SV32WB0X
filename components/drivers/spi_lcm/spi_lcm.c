#include <stdint.h>
#include "spi_lcm.h"
#include "spi_lcm_hw.h"
#include <stdio.h>

extern spi_lcm_hal_t *g_spi_lcm_hal;

void spi_lcm_init(spi_lcm_hal_t *lcm);
void spi_lcm_flush(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t * color_map, void (*done_cb)(void *), void *param);
void spi_lcm_enable_backlight(int backlight);

#define NON_RET
#define CHECK_SPI_LCM(FAILED_RET) \
    do { \
        if (!g_spi_lcm_hal) { \
            printf("[%s] lcm not selected. at %d\n", __func__, __LINE__); \
            return FAILED_RET; \
        } \
    } while(0)

void spi_lcm_init(spi_lcm_hal_t *lcm)
{
    g_spi_lcm_hal = lcm;
    CHECK_SPI_LCM(NON_RET);
    spi_lcm_hw_init();
    g_spi_lcm_hal->reset();
	g_spi_lcm_hal->init();
}

void spi_lcm_flush(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t * color_map, void (*done_cb)(void *), void *param)
{
	g_spi_lcm_hal->flush(x1, y1, x2, y2, color_map, done_cb, param);
}

