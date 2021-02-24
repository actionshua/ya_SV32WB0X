
#include <stdio.h>
#include <soc_types.h>
#include <osal.h>
#include "ili9341.h"
#include <spi_lcm.h>
#include "spi_lcm_hw.h"

#define LCD_ACQUIRE_SPI_ILI9341()
#define LCD_RELEASE_SPI_ILI9341()
#define LCD_CtrlWrite_ILI9341(x)	spi_lcm_hw_write_cmd(x)
#define LCD_DataWrite_ILI9341(x)    spi_lcm_hw_write_data_byte(x)
#define LCD_D16Write_ILI9341(x)     spi_lcm_hw_write_data(x)
#define LCD_Delay(d)                OS_MsDelay(d)
void ili9341_init(void)
{
    LCD_CtrlWrite_ILI9341(0xCB);
    LCD_DataWrite_ILI9341(0x39);
    LCD_DataWrite_ILI9341(0x2C);
    LCD_DataWrite_ILI9341(0x00);
    LCD_DataWrite_ILI9341(0x34);
    LCD_DataWrite_ILI9341(0x02);

    LCD_CtrlWrite_ILI9341(0xCF);
    LCD_DataWrite_ILI9341(0x00);
    LCD_DataWrite_ILI9341(0XC1);
    LCD_DataWrite_ILI9341(0X30);

    LCD_CtrlWrite_ILI9341(0xE8);
    LCD_DataWrite_ILI9341(0x85);
    LCD_DataWrite_ILI9341(0x00);
    LCD_DataWrite_ILI9341(0x78);

    LCD_CtrlWrite_ILI9341(0xEA);
    LCD_DataWrite_ILI9341(0x00);
    LCD_DataWrite_ILI9341(0x00);

    LCD_CtrlWrite_ILI9341(0xED);
    LCD_DataWrite_ILI9341(0x64);
    LCD_DataWrite_ILI9341(0x03);
    LCD_DataWrite_ILI9341(0X12);
    LCD_DataWrite_ILI9341(0X81);

    LCD_CtrlWrite_ILI9341(0xF7);
    LCD_DataWrite_ILI9341(0x20);

    LCD_CtrlWrite_ILI9341(0xC0);    //Power control
    LCD_DataWrite_ILI9341(0x23);   //VRH[5:0]

    LCD_CtrlWrite_ILI9341(0xC1);    //Power control
    LCD_DataWrite_ILI9341(0x10);   //SAP[2:0];BT[3:0]

    LCD_CtrlWrite_ILI9341(0xC5);    //VCM control
    LCD_DataWrite_ILI9341(0x3e);   //Contrast
    LCD_DataWrite_ILI9341(0x28);

    LCD_CtrlWrite_ILI9341(0xC7);    //VCM control2
    LCD_DataWrite_ILI9341(0x86);   //--

    LCD_CtrlWrite_ILI9341(0x36);    // Memory Access Control
#if (M_LCM_LANDSCAPE == 1)
    LCD_DataWrite_ILI9341(0x28); // X-Y exchange 320x240
#else
    LCD_DataWrite_ILI9341(0x48); // 240x320
#endif

    LCD_CtrlWrite_ILI9341(0x3A);
    LCD_DataWrite_ILI9341(0x55);

    LCD_CtrlWrite_ILI9341(0xB1);
    LCD_DataWrite_ILI9341(0x00);
    LCD_DataWrite_ILI9341(0x18);

    LCD_CtrlWrite_ILI9341(0xB6);    // Display Function Control
    LCD_DataWrite_ILI9341(0x08);
    LCD_DataWrite_ILI9341(0x82);
    LCD_DataWrite_ILI9341(0x27);

    LCD_CtrlWrite_ILI9341(0x11);    //Exit Sleep
    LCD_Delay(120);

    LCD_CtrlWrite_ILI9341(0x29);    //Display on
    LCD_CtrlWrite_ILI9341(0x2c);
}

void ili9341_DisplayOn(void)
{
  LCD_CtrlWrite_ILI9341(LCD_DISPLAY_ON);
}

void ili9341_DisplayOff(void)
{
  LCD_CtrlWrite_ILI9341(LCD_DISPLAY_OFF);
}

void ili9341_backlight(uint32_t dim)
{
    (void) dim;
}

uint32_t ili9341_spi_clock()
{
    //return 27*1000*1000;
    return 20*1000*1000;
}

void ili9341_reset()
{
    spi_lcm_hw_setpin_reset(GPIO_LOGIC_HIGH);
    OS_MsDelay(120);
    spi_lcm_hw_setpin_reset(GPIO_LOGIC_LOW);
    OS_MsDelay(120);
    spi_lcm_hw_setpin_reset(GPIO_LOGIC_HIGH);
    OS_MsDelay(140);

}

uint32_t ili9341_probe(void *param)
{
    (void) param;
    return 1;
}


void ili9341_flush(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t * color_map, void (*done_cb)(void *), void *param)
{
    uint8_t data[4];

    /*Column addresses*/
    LCD_CtrlWrite_ILI9341(LCD_COLUMN_ADDR);
	LCD_D16Write_ILI9341(x1);
	LCD_D16Write_ILI9341(x2);

    /*Page addresses*/
    LCD_CtrlWrite_ILI9341(LCD_PAGE_ADDR);
	LCD_D16Write_ILI9341(y1);
	LCD_D16Write_ILI9341(y2);

    /*Memory write*/
    LCD_CtrlWrite_ILI9341(LCD_GRAM);
    uint32_t size = (x2-x1+1) * (y2-y1+1) * sizeof(uint16_t);
    spi_lcm_hw_write_buf((uint8_t *)color_map, size, done_cb, param);
}

spi_lcm_hal_t ili9341 = {
    .probe = ili9341_probe,
    .reset = ili9341_reset,
    .init = ili9341_init,
    .spi_clock = ili9341_spi_clock,
    .backlight = ili9341_backlight,
    .flush = ili9341_flush,
};

