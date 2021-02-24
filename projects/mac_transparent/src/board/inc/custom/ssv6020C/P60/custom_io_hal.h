#ifndef CUSTOM_IO_HAL_H
#define CUSTOM_IO_HAL_H

/*
#ifndef CUSTOM_IO_HAL_60P_6020C_H
#define CUSTOM_IO_HAL_60P_6020C_H
*
* +------+---------+---------+---------+---------+---------+---------+---------+---------+
* |  PIN |   ALT0  |   ALT1  |   ALT2  |   ALT3  |   ALT4  |   ALT5  |   ALT6  |   ALT7  |
* +------+---------+---------+---------+---------+---------+---------+---------+---------+
* |    0 |    AICE |    ADC0 |   ANTSW |   UART0 |   SPIS0 |   SPIM0 |         |  GPIO00 |
* |    1 |    AICE |    ADC1 |   ANTSW |   UART0 |   SPIS0 |   SPIM0 |         |  GPIO01 |
* |    2 |  GPIO02 |    ADC2 |         |         |   SPIS0 |   SPIM0 |         |  GPIO02 |
* |    4 |  GPIO04 |    I2C0 |         |         |         |         |         |  GPIO04 |
* |    5 |  GPIO05 |         |         |         |SPIM0_CSN|SPIS0_CSN|         |  GPIO05 |
* |    6 |  GPIO06 |    I2C0 |PSRAM_SPI|         |         |         |         |  GPIO06 |
* +------+---------+---------+---------+---------+---------+---------+---------+---------+
* |    7 |         |   FLASH |                                                           |
* |    8 |         |   FLASH |                                                           |
* |    9 |         |   FLASH |                                                           |
* |   10 |         |   FLASH |                                                           |
* |   11 |         |   FLASH |                                                           |
* |   12 |         |   FLASH |                                                           |
* +------+---------+---------+---------+---------+---------+---------+---------+---------+
* |   13 |   SIO13 |         |         |         |         |         |         |   SIO13 |
* |   14 |  GPIO14 |         |         |  PDMTX0 |  PDMRX0 |    I2S0 |         |  GPIO14 |
* |   15 |  GPIO15 |         |         |  PDMTX0 |  PDMRX0 |    I2S0 |         |  GPIO15 |
* |   16 |  GPIO16 |         |         |         |  PDMRX1 |    I2S0 |         |  GPIO16 |
* |   17 |  GPIO17 |    SDIO |   UART2 |         |  PDMRX1 |    I2S0 |         |  GPIO17 |
* |   18 |  GPIO18 |    SDIO |         | DATASPIS|SPIS1_CSN|SPIM1_CSN|         |  GPIO18 |
* |   19 |  GPIO19 |    SDIO |         | DATASPIS|    SPIS1|   SPIM1 |         |  GPIO19 |
* |   20 |  GPIO20 |    SDIO |         | DATASPIS|    SPIS1|   SPIM1 |         |  GPIO20 |
* |   21 |  GPIO21 |    SDIO |         | DATASPIS|    SPIS1|   SPIM1 |         |  GPIO21 |
* |   22 |  GPIO22 |    SDIO |   UART2 |         |I2S0_MCLK|         |         |  GPIO22 |
* |   23 |  GPIO23 |         |   UART2 |    I2C1 |         |         |         |  GPIO23 |
* |   24 |  GPIO24 |         |   UART2 |    I2C1 |         |         |         |  GPIO24 |
* |   25 |  GPIO25 |    BTCX |         |         |   UART2 |         |         |  GPIO25 |
* |   26 |  GPIO26 |    BTCX |         |I2S0_MCLK|   UART2 |SPIM2_CSN|         |  GPIO26 |
* |   27 |  GPIO27 |         |   UART1 |  PDMRX0 |         |    I2S1 |         |  GPIO27 |
* |   28 |   SIO28 |         |         |         |         |I2S0_MCLK|         |   SIO28 |
* |   29 |  GPIO29 |    ADC3 |   UART1 |  PDMRX0 |   UART1 |    I2S1 |         |  GPIO29 |
* |   30 |  GPIO30 |    ADC4 |   UART1 |  PDMRX1 |  PDMTX0 |    I2S1 |         |  GPIO30 |
* |   31 |  GPIO31 |    ADC5 |   UART1 |  PDMRX1 |  PDMTX0 |    I2S1 |         |  GPIO31 |
* |   32 |  GPIO32 |    BTCX |         |   SPIM2 |         |         |         |  GPIO32 |
* |   33 |  GPIO33 |         |         |   SPIM2 |   UART1 |    BTCX |         |  GPIO33 |
* |   35 |  GPIO35 |         |         |   SPIM2 |         |         |         |  GPIO35 |
* |   36 |  GPIO36 |    ADC6 |    I2C0 |   UART2 |SPIM2_CSN|    BTCX |   ANTSW |  GPIO36 |
* |   37 |  GPIO37 |    ADC7 |    I2C0 |   UART2 |         |    BTCX |   ANTSW |  GPIO37 |
* +------+---------+---------+---------+---------+---------+---------+---------+---------+
*/

//ALT0 : AICE_TMSC  /ALT1 : ADC0            /ALT2 : ANTSW_BT_SW_ii      /ALT3 : UART0_RXD       /ALT4 : SPIS0_MOSI      /ALT5 : SPIM0_MOSI          /ALT6 : NONE              /ALT7 : GPIO00
#define M_CUSTOM_P00_MODE       M_CUSTOM_ALT3

//ALT0 : AICE_TCKC  /ALT1 : ADC1            /ALT2 : ANTSW_WIFI_TX_SW_ii /ALT3 : UART0_TXD       /ALT4 : SPIS0_MISO      /ALT5 : SPIM0_MISO          /ALT6 : NONE              /ALT7 : GPIO01
#define M_CUSTOM_P01_MODE       M_CUSTOM_ALT3

//ALT0 : GPIO02     /ALT1 : ADC2            /ALT2 : NONE                /ALT3 : NONE            /ALT4 : SPIS0_SCLK      /ALT5 : SPIM0_SCLK          /ALT6 : NONE              /ALT7 : GPIO02
#define M_CUSTOM_P02_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO04     /ALT1 : I2C0_SCL        /ALT2 : NONE                /ALT3 : NONE            /ALT4 : NONE            /ALT5 : NONE                /ALT6 : NONE              /ALT7 : GPIO04
#define M_CUSTOM_P04_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO05     /ALT1 : NONE            /ALT2 : NONE                /ALT3 : NONE            /ALT4 : SPIMAS0_CSN     /ALT5 : SPISLV0_CSN         /ALT6 : NONE              /ALT7 : GPIO05
#define M_CUSTOM_P05_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO06     /ALT1 : I2C0_SDA        /ALT2 : PSRAM_SPI_CSN       /ALT3 : NONE            /ALT4 : NONE            /ALT5 : NONE                /ALT6 : NONE              /ALT7 : GPIO06
#define M_CUSTOM_P06_MODE       M_CUSTOM_ALT0

//ALT0 : SIO13      /ALT1 : NONE            /ALT2 : NONE                /ALT3 : NONE            /ALT4 : NONE            /ALT5 : NONE                /ALT6 : NONE              /ALT7 : SIO13
#define M_CUSTOM_P13_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO14     /ALT1 : NONE            /ALT2 : NONE                /ALT3 : PDMTX0_DOUT0    /ALT4 : PDMRX0_CLK      /ALT5 : I2S0_WS             /ALT6 : NONE              /ALT7 : GPIO14
#define M_CUSTOM_P14_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO15     /ALT1 : NONE            /ALT2 : NONE                /ALT3 : PDMTX0_DOUT1    /ALT4 : PDMRX0_DIN      /ALT5 : I2S0_SDI            /ALT6 : NONE              /ALT7 : GPIO15
#define M_CUSTOM_P15_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO16     /ALT1 : NONE            /ALT2 : NONE                /ALT3 : NONE            /ALT4 : PDMRX1_CLK      /ALT5 : I2S0_SDO            /ALT6 : NONE              /ALT7 : GPIO16
#define M_CUSTOM_P16_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO17     /ALT1 : SD_DATA2        /ALT2 : UART2_NCTS          /ALT3 : NONE            /ALT4 : PDMRX1_DIN      /ALT5 : I2S0_SCK            /ALT6 : NONE              /ALT7 : GPIO17
#define M_CUSTOM_P17_MODE       M_CUSTOM_ALT1

//ALT0 : GPIO18     /ALT1 : SD_DATA3        /ALT2 : NONE                /ALT3 : DATASPIS_CSN    /ALT4 : SPISLV1_CSN     /ALT5 : SPIMAS1_CSN         /ALT6 : NONE              /ALT7 : GPIO18
#define M_CUSTOM_P18_MODE       M_CUSTOM_ALT1

//ALT0 : GPIO19     /ALT1 : SD_CMD          /ALT2 : NONE                /ALT3 : DATASPIS_MOSI   /ALT4 : SPISLV1_MOSI    /ALT5 : SPIMAS1_MOSI        /ALT6 : NONE              /ALT7 : GPIO19
#define M_CUSTOM_P19_MODE       M_CUSTOM_ALT1

//ALT0 : GPIO20     /ALT1 : SD_CLK          /ALT2 : NONE                /ALT3 : DATASPIS_SCLK   /ALT4 : SPISLV1_MISO    /ALT5 : SPIMAS1_MISO        /ALT6 : NONE              /ALT7 : GPIO20
#define M_CUSTOM_P20_MODE       M_CUSTOM_ALT1

//ALT0 : GPIO21     /ALT1 : SD_DATA0        /ALT2 : NONE                /ALT3 : DATASPIS_MISO   /ALT4 : SPISLV1_SCLK    /ALT5 : SPIMAS1_SCLK        /ALT6 : NONE              /ALT7 : GPIO21
#define M_CUSTOM_P21_MODE       M_CUSTOM_ALT1

//ALT0 : GPIO22     /ALT1 : SD_DATA1        /ALT2 : UART2_NRTS          /ALT3 : NONE            /ALT4 : I2S0_MCLK_iii   /ALT5 : NONE                /ALT6 : NONE              /ALT7 : GPIO22
#define M_CUSTOM_P22_MODE       M_CUSTOM_ALT1

//ALT0 : GPIO23     /ALT1 : NONE            /ALT2 : UART2_TXD           /ALT3 : I2C1_SCL        /ALT4 : NONE            /ALT5 : NONE                /ALT6 : NONE              /ALT7 : GPIO23
#define M_CUSTOM_P23_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO24     /ALT1 : NONE            /ALT2 : UART2_RXD           /ALT3 : I2C1_SDA        /ALT4 : NONE            /ALT5 : NONE                /ALT6 : NONE              /ALT7 : GPIO24
#define M_CUSTOM_P24_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO25     /ALT1 : BTCX_WIFI_TX    /ALT2 : NONE                /ALT3 : NONE            /ALT4 : UART2_TXD_ii    /ALT5 : NONE                /ALT6 : NONE              /ALT7 : GPIO25
#define M_CUSTOM_P25_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO26     /ALT1 : BTCX_BT_IN_PROC /ALT2 : NONE                /ALT3 : I2S0_MCLK_ii    /ALT4 : UART2_RXD_ii    /ALT5 : SPIMA2_CSN_ii       /ALT6 : NONE              /ALT7 : GPIO26
#define M_CUSTOM_P26_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO27     /ALT1 : NONE            /ALT2 : UART1_NCTS          /ALT3 : PDMRX0_CLK_ii   /ALT4 : NONE            /ALT5 : I2S1_WS             /ALT6 : NONE              /ALT7 : GPIO27
#define M_CUSTOM_P27_MODE       M_CUSTOM_ALT0

//ALT0 : SIO28      /ALT1 : NONE            /ALT2 : NONE                /ALT3 : NONE            /ALT4 : NONE            /ALT5 : I2S0_MCLK           /ALT6 : NONE              /ALT7 : SIO28
#define M_CUSTOM_P28_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO29     /ALT1 : ADC3            /ALT2 : UART1_NRTS          /ALT3 : PDMRX0_DIN_ii   /ALT4 : UART1_RXD_ii    /ALT5 : I2S1_SDI            /ALT6 : NONE              /ALT7 : GPIO29
#define M_CUSTOM_P29_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO30     /ALT1 : ADC4            /ALT2 : UART1_RXD           /ALT3 : PDMRX1_CLK_ii   /ALT4 : PDMTX0_DOUT0_ii /ALT5 : I2S1_SDO            /ALT6 : NONE              /ALT7 : GPIO30
#define M_CUSTOM_P30_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO31     /ALT1 : ADC5            /ALT2 : UART1_TXD           /ALT3 : PDMRX1_DIN_ii   /ALT4 : PDMTX0_DOUT1_ii /ALT5 : I2S1_SCK            /ALT6 : NONE              /ALT7 : GPIO31
#define M_CUSTOM_P31_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO32     /ALT1 : BTCX_BT_PTI3    /ALT2 : NONE                /ALT3 : SPIMAS2_SCLK    /ALT4 : NONE            /ALT5 : NONE                /ALT6 : NONE              /ALT7 : GPIO32
#define M_CUSTOM_P32_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO33     /ALT1 : NONE            /ALT2 : NONE                /ALT3 : SPIMAS2_MOSI    /ALT4 : UART1_TXD_ii    /ALT5 : BTCX_WIFI_TX_ii     /ALT6 : NONE              /ALT7 : GPIO33
#define M_CUSTOM_P33_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO35     /ALT1 : NONE            /ALT2 : NONE                /ALT3 : SPIMAS2_MISO    /ALT4 : NONE            /ALT5 : NONE                /ALT6 : NONE              /ALT7 : GPIO35
#define M_CUSTOM_P35_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO36     /ALT1 : ADC6            /ALT2 : I2C0_SCL_ii         /ALT3 : UART2_RXD_iii   /ALT4 : SPIMAS2_CSN     /ALT5 : BTCX_BT_IN_PROC_ii  /ALT6 : ANTSW_BT_SW       /ALT7 : GPIO36
#define M_CUSTOM_P36_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO37     /ALT1 : ADC7            /ALT2 : I2C0_SDA_ii         /ALT3 : UART2_TXD_iii   /ALT4 : NONE            /ALT5 : BTCX_BT_PTI3_ii     /ALT6 : ANTSW_WIFI_TX_SW  /ALT7 : GPIO37
#define M_CUSTOM_P37_MODE       M_CUSTOM_ALT0

#endif /* end of include guard: CUSTOM_IO_HAL_H */

