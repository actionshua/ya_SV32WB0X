#ifndef CUSTOM_IO_HAL_H
#define CUSTOM_IO_HAL_H

/*
#ifndef CUSTOM_IO_HAL_32P_6020C_H
#define CUSTOM_IO_HAL_32P_6020C_H
*
* +------+---------+---------+---------+---------+---------+---------+---------+---------+
* |  PIN |   ALT0  |   ALT1  |   ALT2  |   ALT3  |   ALT4  |   ALT5  |   ALT6  |   ALT7  |
* +------+---------+---------+---------+---------+---------+---------+---------+---------+
* |    0 |    AICE |    ADC0 |   ANTSW |   UART0 |         |         |         |  GPIO00 |
* |    1 |    AICE |    ADC1 |   ANTSW |   UART0 |         |         |         |  GPIO01 |
* |   13 |   SIO13 |         |         |         |         |         |         |   SIO13 |
* |   14 |  GPIO14 |         |         |  PDMTX0 |         |         |         |  GPIO14 |
* |   17 |  GPIO17 |    SDIO |   UART2 |         |         |         |         |  GPIO17 |
* |   18 |  GPIO18 |    SDIO |         |         |SPIS1_CSN|SPIM1_CSN|         |  GPIO18 |
* |   19 |  GPIO19 |    SDIO |         |         |    SPIS1|   SPIM1 |         |  GPIO19 |
* |   20 |  GPIO20 |    SDIO |         |         |    SPIS1|   SPIM1 |         |  GPIO20 |
* |   21 |  GPIO21 |    SDIO |         |         |    SPIS1|   SPIM1 |         |  GPIO21 |
* |   22 |  GPIO22 |    SDIO |   UART2 |         |         |         |         |  GPIO22 |
* |   29 |  GPIO29 |    ADC3 |         |         |   UART1 |         |         |  GPIO29 |
* |   33 |  GPIO33 |         |         |         |   UART1 |    BTCX |         |  GPIO33 |
* |   36 |  GPIO36 |    ADC6 |    I2C0 |   UART2 |         |    BTCX |   ANTSW |  GPIO36 |
* |   37 |  GPIO37 |    ADC7 |    I2C0 |   UART2 |         |    BTCX |   ANTSW |  GPIO37 |
* +------+---------+---------+---------+---------+---------+---------+---------+---------+
*/

//ALT0 : AICE_TMSC  /ALT1 : ADC0            /ALT2 : ANTSW_BT_SW_ii      /ALT3 : UART0_RXD       /ALT4 : NONE            /ALT5 : NONE                /ALT6 : NONE              /ALT7 : GPIO00
#define M_CUSTOM_P00_MODE       M_CUSTOM_ALT3

//ALT0 : AICE_TCKC  /ALT1 : ADC1            /ALT2 : ANTSW_WIFI_TX_SW_ii /ALT3 : UART0_TXD       /ALT4 : NONE            /ALT5 : NONE                /ALT6 : NONE              /ALT7 : GPIO01
#define M_CUSTOM_P01_MODE       M_CUSTOM_ALT3

//ALT0 : SIO13      /ALT1 : NONE            /ALT2 : NONE                /ALT3 : NONE            /ALT4 : NONE            /ALT5 : NONE                /ALT6 : NONE              /ALT7 : SIO13
#define M_CUSTOM_P13_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO14     /ALT1 : NONE            /ALT2 : NONE                /ALT3 : PDMTX0_DOUT0    /ALT4 : NONE            /ALT5 : NONE                /ALT6 : NONE              /ALT7 : GPIO14
#define M_CUSTOM_P14_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO17     /ALT1 : SD_DATA2        /ALT2 : UART2_NCTS          /ALT3 : NONE            /ALT4 : NONE            /ALT5 : NONE                /ALT6 : NONE              /ALT7 : GPIO17
#define M_CUSTOM_P17_MODE       M_CUSTOM_ALT2

//ALT0 : GPIO18     /ALT1 : SD_DATA3        /ALT2 : NONE                /ALT3 : NONE            /ALT4 : SPISLV1_CSN     /ALT5 : SPIMAS1_CSN         /ALT6 : NONE              /ALT7 : GPIO18
#define M_CUSTOM_P18_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO19     /ALT1 : SD_CMD          /ALT2 : NONE                /ALT3 : NONE            /ALT4 : SPISLV1_MOSI    /ALT5 : SPIMAS1_MOSI        /ALT6 : NONE              /ALT7 : GPIO19
#define M_CUSTOM_P19_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO20     /ALT1 : SD_CLK          /ALT2 : NONE                /ALT3 : NONE            /ALT4 : SPISLV1_MISO    /ALT5 : SPIMAS1_MISO        /ALT6 : NONE              /ALT7 : GPIO20
#define M_CUSTOM_P20_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO21     /ALT1 : SD_DATA0        /ALT2 : NONE                /ALT3 : NONE            /ALT4 : SPISLV1_SCLK    /ALT5 : SPIMAS1_SCLK        /ALT6 : NONE              /ALT7 : GPIO21
#define M_CUSTOM_P21_MODE       M_CUSTOM_ALT0

//ALT0 : GPIO22     /ALT1 : SD_DATA1        /ALT2 : UART2_NRTS          /ALT3 : NONE            /ALT4 : NONE            /ALT5 : NONE                /ALT6 : NONE              /ALT7 : GPIO22
#define M_CUSTOM_P22_MODE       M_CUSTOM_ALT2

//ALT0 : GPIO29     /ALT1 : ADC3            /ALT2 : NONE                /ALT3 : NONE            /ALT4 : UART1_RXD_ii    /ALT5 : NONE                /ALT6 : NONE              /ALT7 : GPIO29
#define M_CUSTOM_P29_MODE       M_CUSTOM_ALT4

//ALT0 : GPIO33     /ALT1 : NONE            /ALT2 : NONE                /ALT3 : NONE            /ALT4 : UART1_TXD_ii    /ALT5 : BTCX_WIFI_TX_ii     /ALT6 : NONE              /ALT7 : GPIO33
#define M_CUSTOM_P33_MODE       M_CUSTOM_ALT4

//ALT0 : GPIO36     /ALT1 : ADC6            /ALT2 : I2C0_SCL_ii         /ALT3 : UART2_RXD_iii   /ALT4 : NONE            /ALT5 : BTCX_BT_IN_PROC_ii  /ALT6 : ANTSW_BT_SW       /ALT7 : GPIO36
#define M_CUSTOM_P36_MODE       M_CUSTOM_ALT3

//ALT0 : GPIO37     /ALT1 : ADC7            /ALT2 : I2C0_SDA_ii         /ALT3 : UART2_TXD_iii   /ALT4 : NONE            /ALT5 : BTCX_BT_PTI3_ii     /ALT6 : ANTSW_WIFI_TX_SW  /ALT7 : GPIO37
#define M_CUSTOM_P37_MODE       M_CUSTOM_ALT3

#endif /* end of include guard: CUSTOM_IO_HAL_H */

