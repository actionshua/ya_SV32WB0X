/**
 * @file GC9306.h
 */

#ifndef GC9306_H
#define GC9306_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"

#define DISP_BUF_SIZE   (LV_HOR_RES_MAX * 40)
#define GC9306_NOP     0x00		//nop
#define GC9306_SWRESET 0x01		//nop
#define GC9306_RDDID   0x04		
#define GC9306_RDDST   0x09		

#define GC9306_SLPIN   0x10
#define GC9306_SLPOUT  0x11
#define GC9306_PTLON   0x12
#define GC9306_NORON   0x13

#define GC9306_INVOFF  0x20
#define GC9306_INVON   0x21
#define GC9306_DISPOFF 0x28
#define GC9306_DISPON  0x29
#define GC9306_CASET   0x2A
#define GC9306_RASET   0x2B
#define GC9306_RAMWR   0x2C
#define GC9306_RAMRD   0x2E		//nop

#define GC9306_PTLAR   0x30
#define GC9306_PFS  0x3A		//PFSET?
#define GC9306_MADCTL  0x36

#define GC9306_FRMCTR1 0xB1		//nop
#define GC9306_FRMCTR2 0xB2		//nop
#define GC9306_FRMCTR3 0xB3		//nop
#define GC9306_INVCTR  0xB4		//nop
#define GC9306_DISSET5 0xB6

#define GC9306_PWCTR1  0xC0		////nop
#define GC9306_PWCTR2  0xC1
#define GC9306_PWCTR3  0xC2
#define GC9306_PWCTR4  0xC3	
#define GC9306_PWCTR5  0xC4
#define GC9306_VMCTR1  0xC5

#define GC9306_RDID1   0xDA
#define GC9306_RDID2   0xDB
#define GC9306_RDID3   0xDC
#define GC9306_RDID4   0xDD		//nop

#define GC9306_PWCTR6  0xFC		//nop

#define GC9306_GMCTRP1 0xE0		//nop
#define GC9306_GMCTRN1 0xE1		//nop

#define GC9306_IRE1		0xFE
#define GC9306_IRE2		0xEF

#define GC9306_FRARATE	0xE8

void gc9306_init(void);
void gc9306_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map);
void gc9306_enable_backlight(bool backlight);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* GC9306_H  */
