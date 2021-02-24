/**
 * @file gc9306.c
 *
 */

// Strange boars with shifted coords
#if !defined (GC9306_SHIFTED_COORDS)
#define GC9306_SHIFTED_COORDS FALSE
#endif

#if GC9306_SHIFTED_COORDS
#define GC9306_COL_SHIFT 2
#define GC9306_ROW_SHIFT 1
#else
#define GC9306_COL_SHIFT 0
#define GC9306_ROW_SHIFT 0
#endif


#include <stdio.h>
#include <soc_types.h>
#include <osal.h>
#include "gc9306.h"
#include "spi_lcm.h"
#include "spi_lcm_hw.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*The LCD needs a bunch of command/argument values to be initialized. They are stored in this struct. */

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
#define LCD_ACQUIRE_SPI_GC9306()
#define LCD_RELEASE_SPI_GC9306()
#define LCD_CtrlWrite_GC9306(x)	spi_lcm_hw_write_cmd(x)
#define LCD_DataWrite_GC9306(x) spi_lcm_hw_write_data_byte(x)
#define LCD_D16Write_GC9306(x)  spi_lcm_hw_write_data(x)
void gc9306_init(void)
{
    LCD_ACQUIRE_SPI_GC9306();
    LCD_CtrlWrite_GC9306(0xfe);
    LCD_CtrlWrite_GC9306(0xef);
    LCD_CtrlWrite_GC9306(0x36);

#if defined(M_LCM_LANDSCAPE) && (M_LCM_LANDSCAPE == 1)
    LCD_DataWrite_GC9306(0x28); // X-Y exchange 320x240
#else
    LCD_DataWrite_GC9306(0x48); // 240x320
#endif
    LCD_CtrlWrite_GC9306(0x3a);
    LCD_DataWrite_GC9306(0x05);
    //------end display control setting----//
    //------Power Control Registers Initial----//
    LCD_CtrlWrite_GC9306(0xa4);
    LCD_DataWrite_GC9306(0x44);
    LCD_DataWrite_GC9306(0x44);
    LCD_CtrlWrite_GC9306(0xa5);
    LCD_DataWrite_GC9306(0x42);
    LCD_DataWrite_GC9306(0x42);
    LCD_CtrlWrite_GC9306(0xaa);
    LCD_DataWrite_GC9306(0x88);
    LCD_DataWrite_GC9306(0x88);
    LCD_CtrlWrite_GC9306(0xe8);//
    LCD_DataWrite_GC9306(0x11);//11   12	13	15_40
    LCD_DataWrite_GC9306(0x40);// 68   58	48	 

    LCD_CtrlWrite_GC9306(0xe3);
    LCD_DataWrite_GC9306(0x01);
    LCD_DataWrite_GC9306(0x10);
    LCD_CtrlWrite_GC9306(0xff);
    LCD_DataWrite_GC9306(0x61);
    LCD_CtrlWrite_GC9306(0xAC);
    LCD_DataWrite_GC9306(0x00);

    LCD_CtrlWrite_GC9306(0xAe);
    LCD_DataWrite_GC9306(0x2b);//20161020

    LCD_CtrlWrite_GC9306(0xAd);
    LCD_DataWrite_GC9306(0x33);
    LCD_CtrlWrite_GC9306(0xAf);
    LCD_DataWrite_GC9306(0x55);
    LCD_CtrlWrite_GC9306(0xa6);
    LCD_DataWrite_GC9306(0x2a);
    LCD_DataWrite_GC9306(0x2a);
    LCD_CtrlWrite_GC9306(0xa7);
    LCD_DataWrite_GC9306(0x2b);
    LCD_DataWrite_GC9306(0x2b);
    LCD_CtrlWrite_GC9306(0xa8);
    LCD_DataWrite_GC9306(0x18);
    LCD_DataWrite_GC9306(0x18);
    LCD_CtrlWrite_GC9306(0xa9);
    LCD_DataWrite_GC9306(0x2a);
    LCD_DataWrite_GC9306(0x2a);
    //-----display window 240X320---------//
    LCD_CtrlWrite_GC9306(0x2a);
    LCD_DataWrite_GC9306(0x00);
    LCD_DataWrite_GC9306(0x00);
    LCD_DataWrite_GC9306(0x00);
    LCD_DataWrite_GC9306(0xef);
    LCD_CtrlWrite_GC9306(0x2b);
    LCD_DataWrite_GC9306(0x00);
    LCD_DataWrite_GC9306(0x00);
    LCD_DataWrite_GC9306(0x01);
    LCD_DataWrite_GC9306(0x3f);
    LCD_CtrlWrite_GC9306(0x2c);
    //--------end display window --------------//
    //------------gamma setting------------------//
#if 1
    LCD_CtrlWrite_GC9306(0xf0);
    LCD_DataWrite_GC9306(0x2);
    LCD_DataWrite_GC9306(0x0);
    LCD_DataWrite_GC9306(0x0);
    LCD_DataWrite_GC9306(0x5);
    LCD_DataWrite_GC9306(0x9);
    LCD_DataWrite_GC9306(0xf);

    LCD_CtrlWrite_GC9306(0xf1);
    LCD_DataWrite_GC9306(0x1);
    LCD_DataWrite_GC9306(0x2);
    LCD_DataWrite_GC9306(0x0);
    LCD_DataWrite_GC9306(0x20);
    LCD_DataWrite_GC9306(0x32);
    LCD_DataWrite_GC9306(0x12);

    LCD_CtrlWrite_GC9306(0xf2);
    LCD_DataWrite_GC9306(0x10);
    LCD_DataWrite_GC9306(0xb);
    LCD_DataWrite_GC9306(0x2e);
    LCD_DataWrite_GC9306(0x6);
    LCD_DataWrite_GC9306(0x6);
    LCD_DataWrite_GC9306(0x3d);

    LCD_CtrlWrite_GC9306(0xf3);
    LCD_DataWrite_GC9306(0x12);
    LCD_DataWrite_GC9306(0x9);
    LCD_DataWrite_GC9306(0x5a);
    LCD_DataWrite_GC9306(0x1);
    LCD_DataWrite_GC9306(0x1);
    LCD_DataWrite_GC9306(0x66);

    LCD_CtrlWrite_GC9306(0xf4);
    LCD_DataWrite_GC9306(0xf);
    LCD_DataWrite_GC9306(0x1b);
    LCD_DataWrite_GC9306(0x1a);
    LCD_DataWrite_GC9306(0xF);
    LCD_DataWrite_GC9306(0x11);
    LCD_DataWrite_GC9306(0xF);

    LCD_CtrlWrite_GC9306(0xf5);
    LCD_DataWrite_GC9306(0x4);
    LCD_DataWrite_GC9306(0x10);
    LCD_DataWrite_GC9306(0x10);
    LCD_DataWrite_GC9306(0x32);
    LCD_DataWrite_GC9306(0x31);
    LCD_DataWrite_GC9306(0xF);
#endif
    //-----------------end gamma setting----------------------//
    LCD_CtrlWrite_GC9306(0x11);
    OS_MsDelay(120);
    LCD_CtrlWrite_GC9306(0x29);
    LCD_CtrlWrite_GC9306(0x2c);
    LCD_RELEASE_SPI_GC9306();

}

void gc9306_backlight(uint32_t dim)
{
    (void) dim;
}


void gc9306_flush(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t * color_map, void (*done_cb)(void *), void *param)
{
    LCD_ACQUIRE_SPI_GC9306();

    LCD_CtrlWrite_GC9306 (GC9306_CASET);
    LCD_D16Write_GC9306 (x1+GC9306_COL_SHIFT); 
    LCD_D16Write_GC9306 (x2+GC9306_COL_SHIFT);
    LCD_CtrlWrite_GC9306 (GC9306_RASET);
    LCD_D16Write_GC9306 (y1+GC9306_ROW_SHIFT);
    LCD_D16Write_GC9306 (y2+GC9306_ROW_SHIFT);
    LCD_CtrlWrite_GC9306 (GC9306_RAMWR);

    uint32_t size = (x2-x1+1) * (y2-y1+1) * sizeof(uint16_t);

    spi_lcm_hw_write_buf((uint8_t *)color_map, size, done_cb, param);

    LCD_RELEASE_SPI_GC9306();
}

uint32_t gc9306_spi_clock()
{
    return 80*1000*1000;
}

void gc9306_reset()
{
    spi_lcm_hw_setpin_reset(GPIO_LOGIC_HIGH);
    OS_MsDelay(120);
    spi_lcm_hw_setpin_reset(GPIO_LOGIC_LOW);
    OS_MsDelay(120);
    spi_lcm_hw_setpin_reset(GPIO_LOGIC_HIGH);
    OS_MsDelay(140);
}

uint32_t gc9306_probe(void *param)
{
    (void) param;
    return 1;
}

/*
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
 */
spi_lcm_hal_t gc9306 = {
    .probe = gc9306_probe,
    .reset = gc9306_reset,
    .init = gc9306_init,
    .spi_clock = gc9306_spi_clock,
    .backlight = gc9306_backlight,
    .flush = gc9306_flush,
};

