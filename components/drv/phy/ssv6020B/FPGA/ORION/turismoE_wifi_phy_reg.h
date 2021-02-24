/*
 * Copyright (c) 2019 iComm Semiconductor Ltd.
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
 
#define SSV6020_TURISMOE_PHY_TABLE_VER "8.00"

ssv_cabrio_reg ssv6020_turismoE_phy_setting[]={
// Tx packet generator
    {0xccb0e010,0x00000FFF},
    {0xccb0e014,0x00807f03},
    {0xccb0e018,0x0055003C},
    {0xccb0e01C,0x00000064},
    {0xccb0e020,0x00000000},

// AGC
    {0xccb0e02C,0x70046072},// 11b agc rssi threshold, bb iq power threshold, agc target, agc saturation
    {0xccb0e030,0x70046072},// 11gn rssi threshold, bb iq power threshold, agc target, agc saturation
    {0xccb0e034,0x1F1F0000},// analog est delay, wait t final, rx agc done t(should be less than wait t final)
    {0xccb0e038,0x630F36D0},
    {0xccb0e03C,0x100c0003},

// DAGC 11b
    {0xccb0e040,0x11600400},
    {0xccb0e044,0x00080868},

// DAGC 11gn HT20
    {0xccb0e048,0xFF001160},
    {0xccb0e04C,0x00100040},

// agc bandwidth
    {0xccb0e060,0x11401140}, // 555 for 2.4G, 000 for 5G high CFO (degrade sensitivity 0.3db)

// DAGC 11gn HT40
    {0xccb0e12C,0x00001160},
    {0xccb0e130,0x00100040},
    {0xccb0e134,0x00100010}, // DAGC 11gn init gain

// RF, baseband power control
    {0xCCB0E16C,0x00010100},// bit[16] baseband pwr manual, bit[8] rf pwr manual
    {0xCCB0E170,0x60606060},// 1M, 2M, 5.5M, 11M baseband pwr
    {0xCCB0E174,0x06060606},// 1M, 2M, 5.5M, 11M RF pwr
    {0xCCB0E178,0xB5B59090},// 6M, 9M, 12M, 18M baseband pwr
    {0xCCB0E17C,0xA1A18080},// 24M, 36M, 48M, 54M baseband pwr
    {0xCCB0E180,0xB59090A1},// HT20 MCS0~3 basebnad pwr
    {0xCCB0E184,0xA1808080},// HT20 MCS4~7 baseband pwr
    {0xCCB0E188,0xB59090A1},// HT40 MCS0~3 baseband pwr
    {0xCCB0E18C,0xA1808080},// HT40 MCS4~7 baseband pwr
    {0xCCB0E194,0x06060606},// 6M/9M, 12M/18M, 24M/36M, 48M/54M RF pwr
    {0xCCB0E198,0x06060606},// HT20 MCS0, MCS1-2, MCS3-4, MCS5-7 RF pwr
    {0xCCB0E19C,0x06060606},// HT40 MCS0, MCS1-2, MCS3-4, MCS5-7 RF pwr

//// baseband power control
//    {0xccb0e180,0x00010060},//barker_cck
//    {0xccb0e184,0xB5A19080},//Legacy bpsk,qpsk,16qam,64qam
//    {0xccb0e188,0xB5A19080},//ht20 bpsk,qpsk,16qam,64qam
//    {0xccb0e18c,0xB5A19080},//ht40 bpsk,qpsk,16qam,64qam
//
//// rf power control
//    {0xccb0e190,0x00010006},//barker_cck
//    {0xccb0e194,0x06060606},//Legacy bpsk,qpsk,16qam,64qam
//    {0xccb0e198,0x06060606},//ht20 bpsk,qpsk,16qam,64qam
//    {0xccb0e19c,0x06060606},//ht40 bpsk,qpsk,16qam,64qam

// RSSI
    {0xccb0e080,0x0110000F},
// b[   24] rg_rssi_inv
// b[23:16] rg_rssi_offset
// b[ 3: 0] rg_tbus_sel

// Tx 11b setting
    {0xccb0e4b4,0x00002001},

// Tx 11gn setting
    {0xccb0ecA4,0x00009001},
    {0xccb0ecB8,0x000C50CC},

// RX 11gn setting
    {0xccb0f3F8,0x00100001},
    {0xccb0f3FC,0x00010425},

// 11b Rx
    {0xccb0ebF8,0x00100000},
    {0xccb0ebFC,0x00000001},

    {0xccb0e1a0,0x00000008}, // RF/PHY register table version number
                             // 0xCCB0E008, PHY SVN version
                             // 0xCCB0AFC0, RF_D version
};
