/*
 * Copyright (c) 2015 iComm Semiconductor Ltd.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
 
#ifndef TURISMOE_COMMON_H
#define TURISMOE_COMMON_H

#include "turismoE_rf_reg.h"
#include "turismoE_wifi_phy_reg.h"
#include "turismoE_ble_phy_reg.h"

#define SSV6020_TURISMOE_COMMON_CODE_VER "0.02"

enum {
    MODUL_NONE,
    MODUL_WF_HT20,
    MODUL_WF_HT40,
    MODUL_WF_VHT80,
    MODUL_BT_CLASSIC,
    MODUL_BT_LE1M,
    MODUL_BT_LE2M,
    MODUL_NONE2,
};

enum{
    TE_CAL_IDX_NONE      ,
    TE_CAL_IDX_2G_RXDC   ,
    TE_CAL_IDX_BT_RXDC   ,
    TE_CAL_IDX_RXRC      ,
    TE_CAL_IDX_NONE2     ,
    TE_CAL_IDX_2G_TXDCIQ ,
    TE_CAL_IDX_BT_TXDCIQ ,
    TE_CAL_IDX_2G_RXIQ   ,
    TE_CAL_IDX_BT_RXIQ   ,
    TE_CAL_IDX_2G_PADPD  ,
    TE_CAL_IDX_5G_RXDC   ,
    TE_CAL_IDX_5G_TXDCIQ ,
    TE_CAL_IDX_5G_RXIQ   ,
    TE_CAL_IDX_5G_PADPD  ,
    TE_CAL_IDX_NONE3     ,
    TE_CAL_IDX_NONE4     ,
};

#define PAPDP_GAIN_SETTING      0x0
#define PAPDP_GAIN_SETTING_F2   0x0
#define PAPDP_GAIN_SETTING_2G   0x6

#define DEFAULT_DPD_BBSCALE_2500    0x72
#define DEFAULT_DPD_BBSCALE_5100    0x80
#define DEFAULT_DPD_BBSCALE_5500    0x6C    
#define DEFAULT_DPD_BBSCALE_5700    0x6C
#define DEFAULT_DPD_BBSCALE_5900    0x66

#define TURISMOE_EXT_LOAD_PLL_TABLE                                                         \
do{                                                                                         \
    u32 i = 0;                                                                              \
                                                                                            \
    for( i = 0; i < sizeof(ssv6020_turismoE_ext_dpll_setting)/sizeof(ssv_cabrio_reg); i++) {\
       REG32_W(ssv6020_turismoE_ext_dpll_setting[i].address,                                \
           ssv6020_turismoE_ext_dpll_setting[i].data );                                     \
       UDELAY(50); /* should delay a while when set external RF*/                           \
    }                                                                                       \
} while(0)

/* macro to set turismo pll and change clock*/
#define ORIONA_INIT_PLL                                                                     \
do{                                                                                         \
                                                                                            \
    MSLEEP(1);										                                        \
    /*for turismo, it just needs to set register once , pll is initialized by hw auto*/     \
    SET_RG_LOAD_RFTABLE_RDY(true);                                                          \
                                                                                            \
    MSLEEP(10);  /* wait for clock settled*/                                                \
    /* enable PHY clock*/                                                                   \
    REG32_W(ADR_WIFI_PHY_COMMON_SYS_REG, 0x80010000);                                       \
    UDELAY(50);                                                                             \
    /* do clock switch */                                                                   \
    REG32_W(ADR_CLOCK_SELECTION, 0x00000004);                                               \
    MSLEEP(1);  /* wait for clock settled*/                                                 \
}   while(0)

#define TU_SET_ORIONA_2G_CHANNEL(_ch)                                                       \
do{                                                                                         \
    int regval;                                                                             \
                                                                                            \
    SET_RG_RF_5G_BAND(0);                                                                   \
                                                                                            \
    /* set rf channel manual on*/                                                           \
    SET_RG_MODE_MANUAL(1);                                                                  \
                                                                                            \
    /* set rf channel mapping on*/                                                          \
    SET_RG_SX_RFCH_MAP_EN(1);                                                               \
                                                                                            \
    regval = GET_RG_2GWF_SX_CHANNEL;   /*GET_RG_2GWF_SX_CHANNEL*/ /*ADR_RF_DIG_ID*/         \
                                                                                            \
    if (regval == _ch){                                                                     \
        if (_ch != 1)                                                                       \
           SET_RG_2GWF_SX_CHANNEL(1);                                                       \
        else                                                                                \
           SET_RG_2GWF_SX_CHANNEL(11);                                                      \
        /*printk("co-channel, switch to another ch first!!\n");*/                           \
    }                                                                                       \
    UDELAY(100);                                                                            \
                                                                                            \
    /* set channel*/                                                                        \
    SET_RG_2GWF_SX_CHANNEL(_ch);                                                            \
                                                                                            \
    /* set RG_MODE to IDLE mode */                                                          \
    SET_RG_MODE(0);                                                                         \
    UDELAY(50);                                                                             \
                                                                                            \
    /* set RG_MODE to WIFI_RX */                                                            \
    SET_RG_MODE(3);                                                                         \
    UDELAY(150);                                                                            \
                                                                                            \
    /* set RG_MODE_MANUAL off */                                                            \
    SET_RG_MODE_MANUAL(0);                                                                  \
    UDELAY(50);                                                                             \
                                                                                            \
    /* turn on rx*/                                                                         \
    SET_RG_SOFT_RST_N_11B_RX(1);                                                            \
    SET_RG_SOFT_RST_N_11GN_RX(1);                                                           \
} while(0)

#define TU_SET_ORIONA_BW(_ch_type)                                                          \
do{                                                                                         \
    /* Set channel type*/                                                                   \
    switch (_ch_type){                                                                      \
      case 	NL80211_CHAN_HT20:                                                              \
      case  NL80211_CHAN_NO_HT:                                                             \
                                                                                            \
            SET_MTX_BLOCKTX_IGNORE_TOMAC_CCA_ED_SECONDARY(1);                               \
                                                                                            \
            SET_REG(ADR_WIFI_PHY_COMMON_SYS_REG,                                            \
                (0 << RG_PRIMARY_CH_SIDE_SFT) | (0 << RG_SYSTEM_BW_SFT), 0,                 \
                (RG_PRIMARY_CH_SIDE_I_MSK & RG_SYSTEM_BW_I_MSK));                           \
                                                                                            \
            SET_HT20_G_RESP_RATE;                                                           \
            SET_RG_MODUL_SCHEME(MODUL_WF_HT20);                                             \
            break;                                                                          \
                                                                                            \
	  case  NL80211_CHAN_HT40MINUS:                                                         \
                                                                                            \
            SET_MTX_BLOCKTX_IGNORE_TOMAC_CCA_ED_SECONDARY(0);                               \
                                                                                            \
            SET_REG(ADR_WIFI_PHY_COMMON_SYS_REG,                                            \
                (1 << RG_PRIMARY_CH_SIDE_SFT) | (1 << RG_SYSTEM_BW_SFT), 0,                 \
                (RG_PRIMARY_CH_SIDE_I_MSK & RG_SYSTEM_BW_I_MSK));                           \
                                                                                            \
            SET_HT40_G_RESP_RATE;                                                           \
            SET_RG_MODUL_SCHEME(MODUL_WF_HT40);                                             \
            break;                                                                          \
	  case  NL80211_CHAN_HT40PLUS:                                                          \
                                                                                            \
            SET_MTX_BLOCKTX_IGNORE_TOMAC_CCA_ED_SECONDARY(0);                               \
                                                                                            \
            SET_REG(ADR_WIFI_PHY_COMMON_SYS_REG,                                            \
                (0 << RG_PRIMARY_CH_SIDE_SFT) | (1 << RG_SYSTEM_BW_SFT), 0,                 \
                (RG_PRIMARY_CH_SIDE_I_MSK & RG_SYSTEM_BW_I_MSK));                           \
                                                                                            \
            SET_HT40_G_RESP_RATE;                                                           \
            SET_RG_MODUL_SCHEME(MODUL_WF_HT40);                                             \
            break;                                                                          \
      default:                                                                              \
            break;                                                                          \
    }                                                                                       \
}   while(0)

#define TU_CHANGE_ORIONA_CHANNEL(_ch, _ch_type)                                             \
do{                                                                                         \
    const char *chan_type[]={"NL80211_CHAN_NO_HT",                                          \
	    "NL80211_CHAN_HT20",                                                                \
	    "NL80211_CHAN_HT40MINUS",                                                           \
	    "NL80211_CHAN_HT40PLUS"};                                                           \
                                                                                            \
    PRINT("%s: ch %d, type %s\r\n", __func__, _ch, chan_type[_ch_type]);                    \
    SET_RG_SOFT_RST_N_11B_RX(0);                                                            \
    SET_RG_SOFT_RST_N_11GN_RX(0);                                                           \
                                                                                            \
    TU_SET_ORIONA_BW(_ch_type);                                                             \
                                                                                            \
    if (_ch_type == NL80211_CHAN_HT40PLUS)                                                  \
        _ch += 2;                                                                           \
    else if (_ch_type == NL80211_CHAN_HT40MINUS)                                            \
        _ch -= 2;                                                                           \
                                                                                            \
    if ( _ch <=14 && _ch >=1){                                                              \
        SET_SIFS(10);                                                                       \
    	SET_SIGEXT(6);                                                                      \
        TU_SET_ORIONA_2G_CHANNEL( _ch);                                                     \
    } else {                                                                                \
        PRINT("invalid channel %d\r\n", _ch);                                               \
    }                                                                                       \
}   while(0)

#define TU_INIT_ORIONA_TRX                                                                  \
do {                                                                                        \
	REG32_W(ADR_ORIONA_RF_D_MODE_CTRL, 0x7006);                                             \
	UDELAY(50);                                                                             \
} while (0)

#define TU_INIT_ORIONA_CALI                                                                 \
do {                                                                                        \
                                                                                            \
    int i = 0, regval;                                                                      \
    u32 wifi_dc_addr;                                                                       \
                                                                                            \
    /* set RG_MODE_MANUAL ON*/                                                              \
    SET_RG_ORIONA_MODE_MANUAL(1);                                                           \
    UDELAY(50); /* should delay a while when set external RF*/                              \
                                                                                            \
    /* set RG_MODE to IDLE mode*/                                                           \
    SET_RG_ORIONA_MODE(MODE_STANDBY);                                                       \
    UDELAY(50); /* should delay a while when set external RF*/                              \
                                                                                            \
    /* set RG_MODE to Calibration mode */                                                   \
    SET_RG_ORIONA_MODE(MODE_CALIBRATION);                                                   \
    UDELAY(50); /* should delay a while when set external RF*/                              \
                                                                                            \
    /* set RG_modulation MODE to WF_HT40 */                                                 \
    SET_RG_ORIONA_MODUL_SCHEME(MODUL_WF_HT40);                                              \
    UDELAY(50); /* should delay a while when set external RF*/                              \
                                                                                            \
    /* set RG_PMU modulation MODE to WF_HT40 */                                             \
    SET_RG_ORIONA_MODUL_SCHEME_PMU(MODUL_WF_HT40);                                          \
    UDELAY(50); /* should delay a while when set external RF*/                              \
                                                                                            \
    SET_RG_ORIONA_SX_RFCH_MAP_EN(1);                                                        \
    UDELAY(50); /* should delay a while when set external RF*/                              \
                                                                                            \
    /*set channel to ch 6*/                                                                 \
    SET_RG_ORIONA_2GWF_SX_CHANNEL(6);                                                       \
    UDELAY(50); /* should delay a while when set external RF*/                              \
                                                                                            \
    SET_RG_ORIONA_RX_DC_RESOLUTION(1);                                                      \
    UDELAY(50); /* should delay a while when set external RF*/                              \
                                                                                            \
    SET_RG_ORIONA_CAL_INDEX(TE_CAL_IDX_2G_RXDC);                                            \
                                                                                            \
    UDELAY(200); /* should delay a while when set external RF*/                             \
                                                                                            \
    while (GET_RO_ORIONA_WF2G_DCCAL_DONE == 0){                                             \
        i ++;                                                                               \
        if (i >1000) {                                                                      \
            PRINT_ERR("%s: 2.4G RXDC cal failed\r\n",__func__);                             \
            break;                                                                          \
        }                                                                                   \
        UDELAY(50); /* should delay a while when set external RF*/                          \
    }                                                                                       \
                                                                                            \
    PRINT("--------------------------------------------%d\r\n",i);                          \
    PRINT("--------2.4G Calibration result-------------\r\n");                              \
    for (i = 0; i < 8; i++) {                                                               \
       wifi_dc_addr = (ADR_ORIONA_WF_DCOC_IDAC_REGISTER1)+ (i << 2);                        \
       regval = REG32_R(wifi_dc_addr);                                                      \
       PRINT("addr %x : val 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\r\n", wifi_dc_addr,                \
           ((regval >> 24) & 0x3f), ((regval >> 18) & 0x3f), ((regval >> 12) & 0x3f),       \
           ((regval >> 6) & 0x3f), (regval & 0x3f));                                        \
    }                                                                                       \
                                                                                            \
    SET_RG_ORIONA_CAL_INDEX(TE_CAL_IDX_NONE);                                               \
    UDELAY(50); /* should delay a while when set external RF*/                              \
                                                                                            \
    /* set RG_MODE to IDLE mode*/                                                           \
    SET_RG_ORIONA_MODE(MODE_STANDBY);                                                       \
    UDELAY(50); /* should delay a while when set external RF*/                              \
                                                                                            \
    /* set RG_MODE_MANUAL OFF*/                                                             \
    SET_RG_ORIONA_MODE_MANUAL(0);                                                           \
    UDELAY(50); /* should delay a while when set external RF*/                              \
} while(0)
  
#define LOAD_ORIONA_RF_TABLE                                                                \
do{                                                                                         \
    u32 i = 0;                                                                              \
                                                                                            \
    for( i = 0; i < sizeof(ssv6020_turismoE_ext_rf_setting)/sizeof(ssv_cabrio_reg); i++) {  \
       REG32_W(ssv6020_turismoE_ext_rf_setting[i].address,                                  \
       ssv6020_turismoE_ext_rf_setting[i].data );                                           \
       UDELAY(50); /* should delay a while when set external RF*/                           \
    }                                                                                       \
    for( i = 0; i < sizeof(ssv6020_turismoE_rf_setting)/sizeof(ssv_cabrio_reg); i++) {      \
       REG32_W(ssv6020_turismoE_rf_setting[i].address,                                      \
       ssv6020_turismoE_rf_setting[i].data );                                               \
       UDELAY(50); /* should delay a while when set external RF*/                           \
    }                                                                                       \
} while(0)
 
#define LOAD_TURISMO_E_PHY_TABLE                                                            \
do{                                                                                         \
    u32 i = 0;                                                                              \
                                                                                            \
    for( i = 0; i < sizeof(ssv6020_turismoE_phy_setting)/sizeof(ssv_cabrio_reg); i++) {     \
       REG32_W(ssv6020_turismoE_phy_setting[i].address,                                     \
       ssv6020_turismoE_phy_setting[i].data );                                              \
       UDELAY(50); /* should delay a while when set external RF*/                           \
    }                                                                                       \
    for( i = 0; i < sizeof(ssv6020_turismoE_ble_phy_setting)/sizeof(ssv_cabrio_reg); i++) { \
       REG32_W(ssv6020_turismoE_ble_phy_setting[i].address,                                 \
       ssv6020_turismoE_ble_phy_setting[i].data );                                          \
       UDELAY(50); /* should delay a while when set external RF*/                           \
    }                                                                                       \
} while(0)

#define INIT_ORIONA_SYS                                                                     \
do {                                                                                        \
    PRINT_INFO("RF table ver %s PHY table ver %s, common code ver %s \n",                   \
        SSV6020_TURISMOE_RF_TABLE_VER, SSV6020_TURISMOE_PHY_TABLE_VER,                      \
        SSV6020_TURISMOE_COMMON_CODE_VER);                                                  \
    TURISMOE_EXT_LOAD_PLL_TABLE;                                                            \
    LOAD_ORIONA_RF_TABLE;                                                                   \
    LOAD_TURISMO_E_PHY_TABLE;                                                               \
    ORIONA_INIT_PLL;                                                                        \
    REG32_W(ADR_WIFI_PHY_COMMON_ENABLE_REG, 0);                                             \
    TU_INIT_ORIONA_CALI;                                                                    \
    TU_INIT_ORIONA_TRX;                                                                     \
} while(0)
#endif
