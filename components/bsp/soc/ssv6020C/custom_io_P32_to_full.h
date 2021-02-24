#ifndef CUSTOM_IO_P32_TO_FULL_H
#define CUSTOM_IO_P32_TO_FULL_H

//For 6020C
//List the deleted pins for P32, and than map to GPIO(ALT7)
//The delete GPIO pins of P32 are GPIO 02, 03, 04, 05, 06, 07, 08, 09, 10, 11, 12, 15, 16, 23, 24, 25, 26, 27, 28, 30, 31, 32, 34, 35.
//P32 FLASH is SIP. Flash pins defined on GPIO 07, 08, 09, 10, 11, 12.

//ALT0 : GPIO02		/ALT1 : ADC2			/ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : SPIS0_SCLK  	/ALT5 : SPIM0_SCLK  	    /ALT6 : NONE              /ALT7 : GPIO02
#define M_CUSTOM_P02_MODE       M_CUSTOM_ALT7                                                                                                     
   
//ALT0 : GPIO03	    /ALT1 : NONE			/ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : SPISLV0_CSN_ii 	/ALT5 : SPIMAS0_CSN_ii 	    /ALT6 : NONE              /ALT7 : GPIO05
#define M_CUSTOM_P03_MODE       M_CUSTOM_ALT7

//ALT0 : GPIO04		/ALT1 : I2C0_SCL		/ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : NONE        	/ALT5 : NONE        	    /ALT6 : NONE              /ALT7 : GPIO04
#define M_CUSTOM_P04_MODE       M_CUSTOM_ALT7                                                                                                   

//ALT0 : GPIO05		/ALT1 : NONE			/ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : SPIMAS0_CSN    	/ALT5 : SPISLV0_CSN    	    /ALT6 : NONE              /ALT7 : GPIO05
#define M_CUSTOM_P05_MODE       M_CUSTOM_ALT7
 
//ALT0 : GPIO06		/ALT1 : I2C0_SDA		/ALT2 : PSRAM_SPI_CSN  	    /ALT3 : NONE			/ALT4 : NONE        	/ALT5 : NONE        	    /ALT6 : NONE              /ALT7 : GPIO06
#define M_CUSTOM_P06_MODE       M_CUSTOM_ALT7

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

//ALT0 : GPIO15		/ALT1 : NONE			/ALT2 : NONE        	    /ALT3 : PDMTX0_DOUT1	/ALT4 : PDMRX0_DIN  	/ALT5 : I2S0_SDI		    /ALT6 : NONE              /ALT7 : GPIO15
#define M_CUSTOM_P15_MODE       M_CUSTOM_ALT7                                                                                                      

//ALT0 : GPIO16		/ALT1 : NONE        	/ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : PDMRX1_CLK  	/ALT5 : I2S0_SDO		    /ALT6 : NONE              /ALT7 : GPIO16
#define M_CUSTOM_P16_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO23		/ALT1 : NONE    		/ALT2 : UART2_TXD		    /ALT3 : I2C1_SCL		/ALT4 : NONE        	/ALT5 : NONE        	    /ALT6 : NONE              /ALT7 : GPIO23
#define M_CUSTOM_P23_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO24		/ALT1 : NONE    		/ALT2 : UART2_RXD		    /ALT3 : I2C1_SDA		/ALT4 : NONE			/ALT5 : NONE			    /ALT6 : NONE              /ALT7 : GPIO24
#define M_CUSTOM_P24_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO25		/ALT1 : BTCX_WIFI_TX	/ALT2 : RTC_RC32K_EXT	    /ALT3 : NONE			/ALT4 : UART2_TXD_ii	/ALT5 : NONE			    /ALT6 : NONE              /ALT7 : GPIO25
#define M_CUSTOM_P25_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO26		/ALT1 : BTCX_BT_IN_PROC /ALT2 : NONE    		    /ALT3 : I2S0_MCLK_ii	/ALT4 : UART2_RXD_ii	/ALT5 : SPIMA2_CSN_ii	    /ALT6 : NONE              /ALT7 : GPIO26
#define M_CUSTOM_P26_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO27		/ALT1 : NONE    		/ALT2 : UART1_NCTS		    /ALT3 : PDMRX0_CLK_ii	/ALT4 : NONE			/ALT5 : I2S1_WS			    /ALT6 : NONE              /ALT7 : GPIO27
#define M_CUSTOM_P27_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : SIO28		/ALT1 : NONE			/ALT2 : NONE			    /ALT3 : NONE        	/ALT4 : NONE			/ALT5 : I2S0_MCLK		    /ALT6 : NONE              /ALT7 : SIO28
#define M_CUSTOM_P28_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO30		/ALT1 : ADC4			/ALT2 : UART1_RXD		    /ALT3 : PDMRX1_CLK_ii	/ALT4 : PDMTX0_DOUT0_ii	/ALT5 : I2S1_SDO    	    /ALT6 : NONE              /ALT7 : GPIO30
#define M_CUSTOM_P30_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO31		/ALT1 : ADC5			/ALT2 : UART1_TXD		    /ALT3 : PDMRX1_DIN_ii	/ALT4 : PDMTX0_DOUT1_ii	/ALT5 : I2S1_SCK    	    /ALT6 : NONE              /ALT7 : GPIO31
#define M_CUSTOM_P31_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO32		/ALT1 : BTCX_BT_PTI3	/ALT2 : NONE    		    /ALT3 : SPIMAS2_SCLK	/ALT4 : NONE			/ALT5 : NONE        	    /ALT6 : NONE              /ALT7 : GPIO32
#define M_CUSTOM_P32_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : SIO34		/ALT1 : NONE        	/ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : NONE			/ALT5 : NONE			    /ALT6 : NONE              /ALT7 : SIO34
#define M_CUSTOM_P34_MODE       M_CUSTOM_ALT7                                                                                                       

//ALT0 : GPIO35		/ALT1 : NONE			/ALT2 : NONE        	    /ALT3 : SPIMAS2_MISO	/ALT4 : NONE			/ALT5 : NONE			    /ALT6 : NONE              /ALT7 : GPIO35
#define M_CUSTOM_P35_MODE       M_CUSTOM_ALT7                                                                                                       

#endif /* end of include guard: CUSTOM_IO_P32_TO_FULL_H */

