#ifndef CUSTOM_IO_P40_TO_FULL_H
#define CUSTOM_IO_P40_TO_FULL_H

//For 6020C
//List the deleted pins for P40, and than map to GPIO(ALT7)
//The delete GPIO pins of P40 are GPIO 05, 07, 08, 09, 10, 11, 12, 14, 15, 16, 17, 18, 19, 20, 21, 22, 25, 26, 27, 28, 29, 32, 33, 34, 35, 36, 37.
//P40 FLASH is SIP. Flash pins defined on GPIO 07, 08, 09, 10, 11, 12.

//ALT0 : GPIO05		/ALT1 : NONE			/ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : SPIMAS0_CSN    	/ALT5 : SPISLV0_CSN    	    /ALT6 : NONE              /ALT7 : GPIO05
#define M_CUSTOM_P05_MODE       M_CUSTOM_ALT7                                                                                                       
 
//ALT0 : GPIO07		/ALT1 : FLASH_SPI_HOLD  /ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : NONE        	/ALT5 : NONE        	    /ALT6 : NONE              /ALT7 : GPIO07
#define M_CUSTOM_P07_MODE       M_CUSTOM_ALT1                                                                                                       

//ALT0 : GPIO08		/ALT1 : FLASH_SPI_SCLK  /ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : NONE        	/ALT5 : NONE        	    /ALT6 : NONE              /ALT7 : GPIO08
#define M_CUSTOM_P08_MODE       M_CUSTOM_ALT1                                                                                                       

//ALT0 : GPIO09		/ALT1 : FLASH_SPI_MOSI  /ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : NONE        	/ALT5 : NONE        	    /ALT6 : NONE              /ALT7 : GPIO09
#define M_CUSTOM_P09_MODE       M_CUSTOM_ALT1                                                                                                       

//ALT0 : GPIO10		/ALT1 : FLASH_SPI_CSN   /ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : NONE        	/ALT5 : NONE        	    /ALT6 : NONE              /ALT7 : GPIO10
#define M_CUSTOM_P10_MODE       M_CUSTOM_ALT1                                                                                                       

//ALT0 : GPIO11		/ALT1 : FLASH_SPI_MISO  /ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : NONE        	/ALT5 : NONE        	    /ALT6 : NONE              /ALT7 : GPIO11
#define M_CUSTOM_P11_MODE       M_CUSTOM_ALT1                                                                                                       

//ALT0 : GPIO12		/ALT1 : FLASH_SPI_WPN   /ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : NONE        	/ALT5 : NONE        	    /ALT6 : NONE              /ALT7 : GPIO12
#define M_CUSTOM_P12_MODE       M_CUSTOM_ALT1                                                                                                       

//ALT0 : GPIO14		/ALT1 : NONE			/ALT2 : NONE        	    /ALT3 : PDMTX0_DOUT0	/ALT4 : PDMRX0_CLK  	/ALT5 : I2S0_WS 		    /ALT6 : NONE              /ALT7 : GPIO14
#define M_CUSTOM_P14_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO15		/ALT1 : NONE			/ALT2 : NONE        	    /ALT3 : PDMTX0_DOUT1	/ALT4 : PDMRX0_DIN  	/ALT5 : I2S0_SDI		    /ALT6 : NONE              /ALT7 : GPIO15
#define M_CUSTOM_P15_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO16		/ALT1 : NONE        	/ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : PDMRX1_CLK  	/ALT5 : I2S0_SDO		    /ALT6 : NONE              /ALT7 : GPIO16
#define M_CUSTOM_P16_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO17		/ALT1 : SD_DATA2    	/ALT2 : UART2_NCTS		    /ALT3 : NONE        	/ALT4 : PDMRX1_DIN		/ALT5 : I2S0_SCK		    /ALT6 : NONE              /ALT7 : GPIO17
#define M_CUSTOM_P17_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO18		/ALT1 : SD_DATA3		/ALT2 : NONE			    /ALT3 : DATASPIS_CSN	/ALT4 : SPISLV1_CSN		/ALT5 : SPIMAS1_CSN		    /ALT6 : NONE              /ALT7 : GPIO18
#define M_CUSTOM_P18_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO19		/ALT1 : SD_CMD		    /ALT2 : NONE			    /ALT3 : DATASPIS_MOSI	/ALT4 : SPISLV1_MOSI	/ALT5 : SPIMAS1_MOSI	    /ALT6 : NONE              /ALT7 : GPIO19
#define M_CUSTOM_P19_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO20		/ALT1 : SD_CLK			/ALT2 : NONE			    /ALT3 : DATASPIS_SCLK	/ALT4 : SPISLV1_MISO	/ALT5 : SPIMAS1_MISO	    /ALT6 : NONE              /ALT7 : GPIO20
#define M_CUSTOM_P20_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO21		/ALT1 : SD_DATA0		/ALT2 : NONE			    /ALT3 : DATASPIS_MISO	/ALT4 : SPISLV1_SCLK	/ALT5 : SPIMAS1_SCLK	    /ALT6 : NONE              /ALT7 : GPIO21
#define M_CUSTOM_P21_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO22		/ALT1 : SD_DATA1		/ALT2 : UART2_NRTS		    /ALT3 : NONE			/ALT4 : I2S0_MCLK_iii	/ALT5 : NONE    		    /ALT6 : NONE              /ALT7 : GPIO22
#define M_CUSTOM_P22_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO25		/ALT1 : BTCX_WIFI_TX	/ALT2 : NONE                /ALT3 : NONE			/ALT4 : UART2_TXD_ii	/ALT5 : NONE			    /ALT6 : NONE              /ALT7 : GPIO25
#define M_CUSTOM_P25_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO26		/ALT1 : BTCX_BT_IN_PROC /ALT2 : NONE    		    /ALT3 : I2S0_MCLK_ii	/ALT4 : UART2_RXD_ii	/ALT5 : SPIMA2_CSN_ii	    /ALT6 : NONE              /ALT7 : GPIO26
#define M_CUSTOM_P26_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO27		/ALT1 : NONE    		/ALT2 : UART1_NCTS		    /ALT3 : PDMRX0_CLK_ii	/ALT4 : NONE			/ALT5 : I2S1_WS			    /ALT6 : NONE              /ALT7 : GPIO27
#define M_CUSTOM_P27_MODE       M_CUSTOM_ALT0                                                                                                       

//ALT0 : SIO28		/ALT1 : NONE			/ALT2 : NONE			    /ALT3 : NONE        	/ALT4 : NONE			/ALT5 : I2S0_MCLK		    /ALT6 : NONE              /ALT7 : SIO28
#define M_CUSTOM_P28_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO29		/ALT1 : ADC3			/ALT2 : UART1_NRTS		    /ALT3 : PDMRX0_DIN_ii	/ALT4 : UART1_RXD_ii	/ALT5 : I2S1_SDI		    /ALT6 : NONE              /ALT7 : GPIO29
#define M_CUSTOM_P29_MODE       M_CUSTOM_ALT0                                                                                                       

//ALT0 : GPIO32		/ALT1 : BTCX_BT_PTI3	/ALT2 : NONE    		    /ALT3 : SPIMAS2_SCLK	/ALT4 : NONE			/ALT5 : NONE        	    /ALT6 : NONE              /ALT7 : GPIO32
#define M_CUSTOM_P32_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO33		/ALT1 : NONE			/ALT2 : NONE        	    /ALT3 : SPIMAS2_MOSI	/ALT4 : UART1_TXD_ii	/ALT5 : BTCX_WIFI_TX_ii	    /ALT6 : NONE              /ALT7 : GPIO33
#define M_CUSTOM_P33_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : SIO34		/ALT1 : NONE        	/ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : NONE			/ALT5 : NONE			    /ALT6 : NONE              /ALT7 : SIO34
#define M_CUSTOM_P34_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO35		/ALT1 : NONE			/ALT2 : NONE        	    /ALT3 : SPIMAS2_MISO	/ALT4 : NONE			/ALT5 : NONE			    /ALT6 : NONE              /ALT7 : GPIO35
#define M_CUSTOM_P35_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO36		/ALT1 : ADC6			/ALT2 : I2C0_SCL_ii 	    /ALT3 : UART2_RXD_iii	/ALT4 : SPIMAS2_CSN		/ALT5 : BTCX_BT_IN_PROC_ii	/ALT6 : ANTSW_BT_SW       /ALT7 : GPIO36
#define M_CUSTOM_P36_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO37		/ALT1 : ADC7			/ALT2 : I2C0_SDA_ii 	    /ALT3 : UART2_TXD_iii	/ALT4 : NONE			/ALT5 : BTCX_BT_PTI3_ii		/ALT6 : ANTSW_WIFI_TX_SW  /ALT7 : GPIO37
#define M_CUSTOM_P37_MODE       M_CUSTOM_ALT7

#endif 
/* end of include guard: CUSTOM_IO_P40_TO_FULL_H */

