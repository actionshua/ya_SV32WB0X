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
 
#define SSV6020_TURISMOE_PHY_TABLE_VER "3.00"

ssv_cabrio_reg ssv6020_turismoE_phy_setting[]={
// Tx packet generator
    {0xccb0e010,0x00000FFF},
    {0xccb0e014,0x00807f03},
    {0xccb0e018,0x0055003C},
    {0xccb0e01C,0x00000064},
    {0xccb0e020,0x00000000},

// AGC
    {0xccb0e02C,0x70046072},
    {0xccb0e030,0x70046072},
    {0xccb0e034,0x1F040400},
    {0xccb0e038,0x630F36D0},
    {0xccb0e03C,0x100c0003},

// DAGC 11b
    {0xccb0e040,0x11600400},
    {0xccb0e044,0x00080868},

// DAGC 11gn HT20
    {0xccb0e048,0xFF001160},
    {0xccb0e04C,0x00100040},

// agc bandwidth
    {0xccb0e060,0x11501150},

// MRxEN counter
    {0xccb0e088,0x80000000}, 

// DAGC 11gn HT40/HT20
    {0xccb0e12C,0x00001160},
    {0xccb0e130,0x00100040},
    {0xccb0e134,0x00100010},

// baseband power control
    {0xccb0e180,0x00010060},
    {0xccb0e184,0xB5A19080},
    {0xccb0e188,0xB5A19080},
    {0xccb0e18c,0xB5A19080},

// rf power control
    {0xccb0e190,0x00010006},
    {0xccb0e194,0x06060606},
    {0xccb0e198,0x06060606},
    {0xccb0e19c,0x06060606},
    
// RSSI
    {0xccb0e080,0x0110000F},

// Tx 11b setting
    {0xccb0e4b4,0x00002001},

// Tx 11gn setting
    {0xccb0ecA4,0x00009001},
    {0xccb0ecB8,0x000C50CC},

// RX 11gn setting
    {0xccb0f008,0x00004775},
    {0xccb0f00c,0x10000075},
    {0xccb0f010,0x3F304905},
    {0xccb0f014,0x40182000},
    {0xccb0f018,0x20600000},
    {0xccb0f01C,0x0c010080},
    {0xccb0f03C,0x0000005a},

    {0xccb0f020,0x20202020},
    {0xccb0f024,0x20000000},
    {0xccb0f028,0x50505050},
    {0xccb0f02c,0x20202020},
    {0xccb0f030,0x20000000},
    {0xccb0f034,0x00002424},

    {0xccb0f09c,0x000030A0},
    {0xccb0f0C0,0x0f0003c0},
    {0xccb0f0C4,0x30023003},

    {0xccb0f0CC,0x00100120},
    {0xccb0f0D0,0x00000020},

    {0xccb0f130,0x40000000},
    {0xccb0f164,0x000e0090},
    {0xccb0f188,0x82000000},
    {0xccb0f190,0x00000020},

// new pilot average
    {0xccb0f194,0x09360001},

    {0xccb0f3F8,0x00100001},
    {0xccb0f3FC,0x00010425},

// 11b Rx
    {0xccb0e804,0x00020000},
    {0xccb0e808,0x20280060},
    {0xccb0e80c,0x00003467},
    {0xccb0e810,0x00430000},
    {0xccb0e814,0x30000015},
    {0xccb0e818,0x00390005},
    {0xccb0e81C,0x05050005},
    {0xccb0e820,0x00570057},
    {0xccb0e824,0x00570057},
    {0xccb0e828,0x00236700},
    {0xccb0e82c,0x000d1746},
    {0xccb0e830,0x05051787},
    {0xccb0e834,0x07800000},

    {0xccb0e89c,0x009000B0},
    {0xccb0e8A0,0x00000000},
    {0xccb0ebF8,0x00100000},
    {0xccb0ebFC,0x00000001},

    {0xccb0e1a0,0x00000003}, // RF/PHY register table version number
                             // 0xCCB0E008, PHY SVN version
                             // 0xCCB0AFC0, RF_D version
};


