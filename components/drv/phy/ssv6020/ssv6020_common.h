/*
 * Copyright (c) 2019 iComm-semi Ltd.
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
#ifndef SSV6020_COMMON_H
#define SSV6020_COMMON_H

#include <attrs.h>

enum {
    MODUL_NONE,
    MODUL_WF_HT20,
    MODUL_WF_HT40,
    MODUL_WF_VHT80,
    MODUL_BT_CLASSIC,
    MODUL_BT_LE1M,
    MODUL_BT_LE2M,
    MODUL_WF_LP11B,
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

void backup_ssv6020_rf_table(SSV_HW *sh) ATTRIBUTE_SECTION_FAST_L2STACK;
void load_ssv6020_rf_table(SSV_HW *sh) ATTRIBUTE_SECTION_FAST_L2STACK;
void backup_ssv6020_phy_table(SSV_HW *sh) ATTRIBUTE_SECTION_FAST_L2STACK;
void load_ssv6020_phy_table(SSV_HW *sh) ATTRIBUTE_SECTION_FAST_L2STACK;
void ssv6020_set_channel(SSV_HW *sh, int ch, int channel_type);
void ssv6020_restore_cal (SSV_HW *sh, struct ssv6006_cal_result *cal);
void ssv6020_init_turismoE_sys(SSV_HW *sh, struct ssv6006_patch *patch, struct ssv6006_cal_result *cal, struct ssv6006_padpd *dpd);
void init_ssv6020_pll(SSV_HW *sh);
void ssv6020_init_cali(SSV_HW *sh, struct ssv6006_cal_result *cal);
void ssv6020_turismoE_load_phy_table(ssv_cabrio_reg **phy_table);
u32 ssv6020_turismoE_get_phy_table_size(SSV_HW *sh);
void ssv6020_turismoE_load_rf_table(ssv_cabrio_reg **rf_table);
u32 ssv6020_turismoE_get_rf_table_size(void);
 #endif
