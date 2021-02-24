#ifndef CUSTOM_IO_P60_TO_FULL_H
#define CUSTOM_IO_P60_TO_FULL_H

//For 6020C
//List the deleted pins for P60, and than map to GPIO(ALT7)
//The delete GPIO pins of P60 are GPIO 03, and 34.
//Flash pins 07~12 also list in this file.

//ALT0 : GPIO03	    /ALT1 : NONE			/ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : SPISLV0_CSN_ii 	/ALT5 : SPIMAS0_CSN_ii 	    /ALT6 : NONE              /ALT7 : GPIO05
#define M_CUSTOM_P03_MODE       M_CUSTOM_ALT7

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

//ALT0 : SIO34		/ALT1 : NONE        	/ALT2 : NONE        	    /ALT3 : NONE			/ALT4 : NONE			/ALT5 : NONE			    /ALT6 : NONE              /ALT7 : SIO34
#define M_CUSTOM_P34_MODE       M_CUSTOM_ALT7                                                                                                       

#endif /* end of include guard: CUSTOM_IO_P60_TO_FULL_H */

