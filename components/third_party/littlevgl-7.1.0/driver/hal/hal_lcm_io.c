#include <stdint.h>
#include "hal_lcm_io.h"
#include <bsp.h>


void LCD_IO_Init()
{
}

void LCD_IO_WriteData(uint16_t RegValue)
{
}

void LCD_IO_WriteReg(uint8_t Reg)
{
}

uint32_t LCD_IO_ReadData(uint16_t RegValue, uint8_t ReadSize)
{
}

void LCD_Delay(uint32_t delay)
{
    system_delay(system_us2delaytick(delay*1000));
}

