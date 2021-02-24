#ifndef __SDC_PARAM_H__
#define __SDC_PARAM_H__

#include "drv_spimst.h"
#include "hal_spimst.h"

#if(CHIP_ID==6006)
#define SDC_CSN_PIN             11  //suggested for 6006
#define SDC_CD_PIN              9  //suggested for 6006
#elif(CHIP_ID==6020)
#define SDC_CSN_PIN             36  //suggested for 6020
#define SDC_CD_PIN              28  //suggested for 6020
#define SDC_WP_PIN              6  //optional
#else
#error "not support"
#endif


#define SDC_DEBOUNCE_CNT        500
#define SDC_DEBOUNCE_TIME       1

#define SDC_SPI_MST_CHOICE      DRV_SPIMST_2
#define SDC_SPI_MST_PHASE       SPI_MST_CPHA_0
#define SDC_SPI_MST_POLARITY    SPI_MST_CPOL_0

#endif
