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
 
#ifndef TU_COMMON_H
#define TU_COMMON_H
 
//For PADPD use, the following should define in sc
#define     PADPDBAND   5
#define     MAX_PADPD_TONE  26

struct ssv6006dpd{
    u32     am[MAX_PADPD_TONE/2];
    u32     pm[MAX_PADPD_TONE/2];
};
struct ssv6006_padpd{
    bool    dpd_done[PADPDBAND];
    bool    dpd_disable[PADPDBAND];
    bool    pwr_mode;           /* 0: normal mode, 1: Green_Tx_mode*/
    u8      current_band;
    struct  ssv6006dpd val[PADPDBAND];
    u8      spur_patched;
    u8      bbscale[PADPDBAND]; /* bbscale value from efuse table or phy table default value */ 
    u32     adr_mode_register;
    u8      am_enable;
};

struct ssv6006_cal_result{
    bool cal_done;
    bool cal_iq_done[PADPDBAND];
    u32 rxdc_2g[21];
    u8  rxrc_bw20;
    u8  rxrc_bw40;
    u8  txdc_i_2g;
    u8  txdc_q_2g;
    u32 rxdc_5g[21];
    u8  rxiq_alpha[PADPDBAND];
    u8  rxiq_theta[PADPDBAND];
    u8  rxiq_alpha_bw40[PADPDBAND];
    u8  rxiq_theta_bw40[PADPDBAND];
    u8  txdc_i_5g;
    u8  txdc_q_5g;
    u8  txiq_alpha[PADPDBAND];
    u8  txiq_theta[PADPDBAND];       
};
typedef void SSV_HW;      /* dummy def to compile with fw*/

struct ssv6006_patch{
    bool    dcdc;
    bool    need_rf_patch;
    u32     g_band_pa_bias0;
    u32     g_band_pa_bias1;
    u32     a_band_pa_bias0;
    u32     a_band_pa_bias1;        
    u16     xtal;
    u16     cpu_clk;
    u8      rxfe_level;
    u8      dldo_level;
    u8      buck_level;
};
#define NOT_PATCHED     0xff


#define CLK_32K     1
#define CLK_XTAL    2
#define CLK_40M     4
#define CLK_80M     8

/* define for xtal type*/

enum {   
    XTAL16M = 0,
    XTAL24M,
    XTAL26M,
    XTAL40M,
    XTAL12M,
    XTAL20M,
    XTAL25M,
    XTAL32M,
    XTAL19P2M,
    XTAL38P4M,
    XTAL52M,
    XTALMAX,
};

/* define for supported band */
enum{
    G_BAND_ONLY = 0,
    AG_BAND_BOTH = 1,
};

enum {
    CAL_IDX_NONE,           
    CAL_IDX_WIFI2P4G_RXDC,  
    CAL_IDX_BT_RXDC,        
    CAL_IDX_BW20_RXRC,      
    CAL_IDX_WIFI2P4G_TXLO,  
    CAL_IDX_WIFI2P4G_TXIQ, 
    CAL_IDX_WIFI2P4G_RXIQ,  
    CAL_IDX_WIFI2P4G_PADPD,
    CAL_IDX_5G_NONE,        
    CAL_IDX_WIFI5G_RXDC,    
    CAL_IDX_5G_NONE2,       
    CAL_IDX_BW40_RXRC,      
    CAL_IDX_WIFI5G_TXLO,    
    CAL_IDX_WIFI5G_TXIQ,   
    CAL_IDX_WIFI5G_RXIQ,    
    CAL_IDX_WIFI5G_PADPD,   
};
   
enum {
    MODE_STANDBY,
    MODE_CALIBRATION,
    MODE_WIFI2P4G_TX,
    MODE_WIFI2P4G_RX,
    MODE_BT_TX,
    MODE_BT_RX,
    MODE_WIFI5G_TX,
    MODE_WIFI5G_RX,
};  

enum {
    BAND_2G,
    BAND_5100,
    BAND_5500,
    BAND_5700,
    BAND_5900,
    MAX_BAND,
};   

#ifndef MAX_PADPD_TONE
#define     MAX_PADPD_TONE  26    
#endif
 
struct padpd_table{
    u32 addr;
    u32 mask0;
    u32 mask1;
};
  
extern const int cal_ch_5g[4];
extern const struct padpd_table padpd_am_table[];
extern const struct padpd_table padpd_pm_table[];
extern const u8 xtal_sx_cp_isel_wf[];
extern const char *xtal_type[];
extern const u32 am_mask[];
extern const u32 padpd_am_addr_table[][13];
extern const u32 pm_mask[];
extern const u32 padpd_pm_addr_table[][13];

extern int ssv6006_get_pa_band(int ch);
extern void turismo_pre_cal(SSV_HW *sh);
extern void turismo_post_cal(SSV_HW *sh);
extern void turismo_inter_cal(SSV_HW *sh);
                                

/**
*   The following code are common phy_RF routine over all platform.
*   To use these routine , it should define several macro in other header file first.
*   
*   // Macros for predefined register access.
*   #define REG32(_addr)    REG32_R(_addr)
*   #define REG32_R(_addr)   ({ u32 reg; SMAC_REG_READ(sh, _addr, &reg); reg;})
*   #define REG32_W(_addr, _value)   do { SMAC_REG_WRITE(sh, _addr, _value); } while (0)
*
*   // Macros for turismo common header
*   #define MSLEEP(_val)        msleep(_val)
*   #define MDELAY(_val)        mdelay(_val)
*   #define UDELAY(_val)        udelay(_val)
*   #define PRINT               printk    
*/
  

/* for tiramisu only*/
extern int printf_null(const char *fmt, ...); 
#define MSLEEP(_val)        drv_pmu_tu2(_val * 1000)
#define MDELAY              MSLEEP
#define UDELAY(_val)        drv_pmu_tu2(_val)
#define PRINT               printf_null

#define PRINT_ERR           printf
#define PRINT_INFO          printf


#define SET_HT20_G_RESP_RATE                                                                \
do{ /* bit0~ bit 7 ack/cts rate, bit8~bit15  BA rate, ignore BA rate */                     \
    SET_MTX_RESPFRM_RATE_80(0x9090);                                                     \
    SET_MTX_RESPFRM_RATE_81(0x9090);                                                     \
    SET_MTX_RESPFRM_RATE_82(0x9090);                                                     \
    SET_MTX_RESPFRM_RATE_83(0x9292);                                                     \
    SET_MTX_RESPFRM_RATE_84(0x9292);                                                     \
    SET_MTX_RESPFRM_RATE_85(0x9494);                                                     \
    SET_MTX_RESPFRM_RATE_86(0x9494);                                                     \
    SET_MTX_RESPFRM_RATE_87(0x9494);                                                     \
} while(0)


#define SET_HT40_G_RESP_RATE                                                                \
do {/* bit0~ bit 7 ack/cts rate, bit8~bit15  BA rate*/                                      \
    SET_MTX_RESPFRM_RATE_80(0xB0B0);                                                     \
    SET_MTX_RESPFRM_RATE_81(0xB0B0);                                                     \
    SET_MTX_RESPFRM_RATE_82(0xB0B0);                                                     \
    SET_MTX_RESPFRM_RATE_83(0xB2B2);                                                     \
    SET_MTX_RESPFRM_RATE_84(0xB2B2);                                                     \
    SET_MTX_RESPFRM_RATE_85(0xB4B4);                                                     \
    SET_MTX_RESPFRM_RATE_86(0xB4B4);                                                     \
    SET_MTX_RESPFRM_RATE_87(0xB4B4);                                                     \
} while (0)

#endif
