#ifndef CUSTOM_IO_HAL_H
#define CUSTOM_IO_HAL_H

/*
#ifndef CUSTOM_IO_HAL_40P_6020C_H
#define CUSTOM_IO_HAL_40P_6020C_H
*
* +------+---------+---------+---------+---------+---------+---------+---------+
* |  PIN |   ALT0  |   ALT1  |   ALT2  |   ALT3  |   ALT4  |   ALT5  |   ALT7  |
* +------+---------+---------+---------+---------+---------+---------+---------+
* |    0 |    AICE |    ADC0 |         |   UART0 |   SPIS0 |   SPIM0 |  GPIO00 |
* |    1 |    AICE |    ADC1 |         |   UART0 |   SPIS0 |   SPIM0 |  GPIO01 |
* |    2 |  GPIO02 |    ADC2 |         |         |   SPIS0 |   SPIM0 |  GPIO02 |
* |    3 |  GPIO03 |         |         |         |SPIS0_CSN|SPIM0_CSN|  GPIO03 |
* |    4 |  GPIO04 |    I2C0 |         |         |         |         |  GPIO04 |
* |    6 |  GPIO06 |    I2C0 |         |         |         |         |  GPIO06 |
* |   13 |   SIO13 |         |         |         |         |         |   SIO13 |
* |   23 |  GPIO23 |         |   UART2 |    I2C1 |         |         |  GPIO23 |
* |   24 |  GPIO24 |         |   UART2 |    I2C1 |         |         |  GPIO24 |
* |   30 |  GPIO30 |    ADC4 |   UART1 |  PDMRX1 |  PDMTX0 |         |  GPIO30 |
* |   31 |  GPIO31 |    ADC5 |   UART1 |  PDMRX1 |  PDMTX0 |         |  GPIO31 |
* +------+---------+---------+---------+---------+---------+---------+---------+
*/

//ALT0 : AICE_TMSC  /ALT1 : ADC0            /ALT2 : NONE            /ALT3 : UART0_RXD       /ALT4 : SPIS0_MOSI      /ALT5 : SPIM0_MOSI   /ALT7 : GPIO00
#define M_CUSTOM_P00_MODE       M_CUSTOM_ALT0

//ALT0 : AICE_TCKC  /ALT1 : ADC1            /ALT2 : NONE            /ALT3 : UART0_TXD       /ALT4 : SPIS0_MISO      /ALT5 : SPIM0_MISO   /ALT7 : GPIO01
#define M_CUSTOM_P01_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO02     /ALT1 : ADC2            /ALT2 : NONE            /ALT3 : NONE            /ALT4 : SPIS0_SCLK      /ALT5 : SPIM0_SCLK   /ALT7 : GPIO02
#define M_CUSTOM_P02_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO03     /ALT1 : NONE            /ALT2 : NONE            /ALT3 : NONE            /ALT4 : SPIS0_CSN       /ALT5 : SPIM0_CSN    /ALT7 : GPIO03
#define M_CUSTOM_P03_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO04     /ALT1 : I2C0_SCL        /ALT2 : NONE            /ALT3 : NONE            /ALT4 : NONE            /ALT5 : NONE         /ALT7 : GPIO04
#define M_CUSTOM_P04_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO06     /ALT1 : I2C0_SDA        /ALT2 : NONE            /ALT3 : NONE            /ALT4 : NONE            /ALT5 : NONE         /ALT7 : GPIO06
#define M_CUSTOM_P06_MODE       M_CUSTOM_ALT0

//ALT0 : SIO13      /ALT1 : NONE            /ALT2 : NONE            /ALT3 : NONE            /ALT4 : NONE            /ALT5 : NONE         /ALT7 : SIO13
#define M_CUSTOM_P13_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO23     /ALT1 : NONE            /ALT2 : UART2_TXD       /ALT3 : I2C1_SCL        /ALT4 : NONE            /ALT5 : NONE         /ALT7 : GPIO23
#define M_CUSTOM_P23_MODE       M_CUSTOM_ALT2

//ALT0 : GPIO24     /ALT1 : NONE            /ALT2 : UART2_RXD       /ALT3 : I2C1_SDA        /ALT4 : NONE            /ALT5 : NONE         /ALT7 : GPIO24
#define M_CUSTOM_P24_MODE       M_CUSTOM_ALT2

//ALT0 : GPIO30     /ALT1 : ADC4            /ALT2 : UART1_RXD       /ALT3 : PDMRX1_CLK_ii   /ALT4 : PDMTX0_DOUT0_ii /ALT5 : NONE         /ALT7 : GPIO30
#define M_CUSTOM_P30_MODE       M_CUSTOM_ALT2

//ALT0 : GPIO31     /ALT1 : ADC5            /ALT2 : UART1_TXD       /ALT3 : PDMRX1_DIN_ii   /ALT4 : PDMTX0_DOUT1_ii /ALT5 : NONE         /ALT7 : GPIO31
#define M_CUSTOM_P31_MODE       M_CUSTOM_ALT2

#endif /* end of include guard: CUSTOM_IO_HAL_H */

