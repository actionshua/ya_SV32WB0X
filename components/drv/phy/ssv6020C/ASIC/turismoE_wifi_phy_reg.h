/*
 * Copyright (c) 2020 iComm Semiconductor Ltd.
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
 
#define SSV6020_TURISMOE_PHY_TABLE_VER "36.00"

ssv_cabrio_reg ssv6020_turismoE_phy_setting[]={
// set clock to 80M and 11b fitler to lower BW
    {0xccb0e000,0x80010004}, // ht20
    
// Tx packet generator
    {0xccb0e010,0x00000FFF},

    {0xccb0e014,0x00807f03},
    {0xccb0e018,0x0055003C},
    {0xccb0e01C,0x00000064},
    {0xccb0e020,0x00000000},

// AGC
    {0xccb0e02C,0x6004606C},// 11b agc rssi threshold, bb iq power threshold, agc target, agc saturation
    {0xccb0e030,0x6004606C},// 11gn rssi threshold, bb iq power threshold, agc target, agc saturation
    {0xccb0e034,0x23230000},// analog est delay, wait t final, rx agc done t(should be less than wait t final)
    {0xccb0e038,0x630F36D0},
    {0xccb0e03C,0x100c0003},
    {0xCCB0E248,0x00000FC1},
    {0xCCB0E268,0x120C1200},

// DAGC 11b
    {0xccb0e040,0x11600400},
    {0xccb0e044,0x00080860},

// DAGC 11gn HT20
    {0xccb0e048,0xFF001160},
    {0xccb0e04C,0x00100040},

// agc bandwidth
    {0xccb0e060,0x11501150}, // 

// MRxEN counter
    {0xccb0e088,0x80000000}, 

// DAGC 11gn HT40
    {0xccb0e12C,0x00001160},
    {0xccb0e130,0x00100040},

// RF/baseband gian control manual
    {0xCCB0E16C,0x00010000},
    {0xCCB0E170,0x72727272},//1M, 2M, 5.5M, 11M
    {0xCCB0E178,0xB5B5A1A1},// 6M,  9M, 12M, 18M
    {0xCCB0E17C,0x90908080},//24M, 36M, 48M, 54M
    {0xCCB0E180,0xB5A1A190},//HT20 MCS0, MCS1, MCS2, MCS3
    {0xCCB0E184,0x90808080},//HT20 MCS4, MCS5, MCS6, MCS7
    {0xCCB0E188,0xB5A1A190},//HT40 MCS0, MCS1, MCS2, MCS3
    {0xCCB0E18C,0x90808080},//HT40 MCS4, MCS5, MCS6, MCS7

// RSSI
    {0xccb0e080,0x0110000F},

// Tx 11b setting
    {0xccb0e4b4,0x00002001},

// Tx 11gn setting
    {0xccb0ecA4,0x00009001},
    {0xccb0ecB8,0x000C50CC},

// RX 11gn setting
    {0xCCB0F1A0,0x00110770},
    {0xCCB0F1B4,0x0000ff00},
    {0xccb0f3F8,0x00100001},
    {0xccb0f3FC,0x00010425},
    {0xCCB0F198,0xFF0CFC8C},
    {0xCCB0F19C,0xFF0CF9FC},

// Rx 11b setting
    {0xCCB0E808,0x20280050},
    {0xCCB0E810,0x43435454},
    {0xCCB0E830,0x06061888},
    {0xCCB0E83C,0x00300011},
    {0xccb0ebF8,0x00100000},
    {0xccb0ebFC,0x00000001},

    {0xccb0e1a0,0x00000024}, // RF/PHY register table version number
                             // 0xCCB0E008, PHY SVN version
                             // 0xCCB0AFC0, RF_D version
};
