#ifndef _LCM_PARAM_ 
#define _LCM_PARAM_

//#define M_LCM_DRV           (ili9341)
#define M_LCM_DRV           (gc9306)
#define M_LCM_SPI_MASTER    (HAL_SPIMST_1)

#define M_LCM_LANDSCAPE     (0)

#if (M_LCM_LANDSCAPE == 1)
#define M_LCM_WIDTH         (320)
#define M_LCM_HEIGHT        (240)
#else
#define M_LCM_WIDTH         (240)
#define M_LCM_HEIGHT        (320)
#endif

// for 60Pin
#define M_LCM_RESET_PIN     (25)
#define M_LCM_DC_PIN        (5)
#define M_LCM_BK_LIGHT_PIN  (20)

// for 32Pin
//#define M_LCM_RESET_PIN     (20)
//#define M_LCM_DC_PIN        (22)
//#define M_LCM_BK_LIGHT_PIN  (24)

#define M_LCM_COLOR_16_SWAP (1)

#endif /* end of include guard */

