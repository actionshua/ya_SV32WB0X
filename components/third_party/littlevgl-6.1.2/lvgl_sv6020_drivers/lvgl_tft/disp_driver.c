/**
 * @file disp_driver.c
 */

#include "disp_driver.h"
#include <spi_lcm.h>

void disp_driver_init()
{
    spi_lcm_init(&M_LCM_DRV);
}

static lv_disp_drv_t *g_drv = NULL;

static void lcm_update_done_cb(void *param) {
    lv_disp_flush_ready(g_drv);
}

void disp_driver_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_map)
{
    g_drv = drv;
	spi_lcm_flush(area->x1, area->y1, area->x2, area->y2, (void *)color_map, lcm_update_done_cb, NULL);
}

