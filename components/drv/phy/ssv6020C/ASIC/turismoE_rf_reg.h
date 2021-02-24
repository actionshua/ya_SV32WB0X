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

#define SSV6020_TURISMOE_RF_TABLE_VER "36.00"

ssv_cabrio_reg ssv6020_turismoE_rf_setting[]={
// TRX dummy register settings
    {0xCCB0A560,0xAAAFAAA1}, // rx gm opt=2 / tx cim3 000 / tx gnd switch on 1, note:rx opt no use

// TRX B0 Copin settings
    {0xCCB0A414,0x000890F5}, // tr copin. rx b0 ctank=5/ tx ctank=1111
// TRX B1 Copin setting
//    {0xCCB0A414,0x00089080}, // tr copin. rx b1 ctank=0/ tx c2=1

// RX LDO_FEABB
    {0xCCB0A418,0x158002AA}, // LDO_FEABB from 01 to 10 , 1201
// RX TZ
    {0xCCB0A420,0x2C654D6F}, // TZ_VCM from 011 to 010 , 1208

// RX LNA
    {0xCCB0A428,0x9C40C2B7}, // LNA bias
    {0xCCB0A438,0x9C40C2B7}, // BT HG setting align WF

// RX LPF settings
    {0xCCB0A4A8,0x00000192}, // wifi rx lpf HT20 9.18M
    {0xCCB0A4AC,0x0000048C}, // wifi rx lpf HT40 17.2M
    {0xCCB0A4B4,0x000010E0}, // bt1m rx lpf 2.62M
    {0xCCB0A4B8,0x000010B0}, // bt2m rx lpf 3.5M

// SX settings
    {0xCCB0A460,0xFA8FD092}, // rp en/mx aac dis ; IOSThref/swc1 on ; PFD PRM ,0716MAN=1/1 ; 2nd dis ; 1124
    {0xCCB0A470,0x00000389}, // SX FDB M2 enable / BT IF to 1.600MHz
    {0xCCB0A49C,0x1FE6A700}, // SX sbcal diffmin on ; c0p5dis=1
    {0xCCB0A498,0x00001E01}, // SX div vdd for ref spur,xtal24M 1204    
    {0xCCB0A484,0x2AA228F2}, // LPF optimization , 0716
    {0xCCB0A4A4,0x0082A532}, // rep tar 0101 ; mix sca fix 20,1124
    {0xCCB0A45C,0x000AA91A}, // LDO_VCO level 01 to 00 for better PSRR at high temp ch13;LDOCP to 10 for HTmask,LDODIV10 for 11bmask,1204

// Tx settings
    {0xCCB0A408,0x8FC21E00}, //TX Gain = 0000/1011 for WF/BT_1.4dBm PHY CTRL, WF_MOD_GMCELL=1100, BT_MOD_GMCELL=1000 , 1112
    {0xCCB0A448,0x006B6D30}, //PGABIAS=000/LOBIAS=000/GM=0011/PACELL=110/PAVCAS=110/PAGM=0100
    {0xCCB0A44C,0x006B6D30}, //PGABIAS=000/LOBIAS=000/GM=0011/PACELL=110/PAVCAS=110/PAGM=0100
    {0xCCB0A450,0x7823FF82}, // BT PAcell001 ; CAPSW adjust for BT Pout flatness , 1211
//    {0xCCB0A454,0x108731FC}, //PGA/GMCELL=11111/1100; lowCurrent=11100/1100,DAC=+0.5 for 11b mask

// TX LPF setting
    {0xCCB0A4C4,0x5CFBDAAE}, //TXLPF_ICOURSE=10,TXLPD_ADDI=11,TXLPF_FILTER1ST=11 for 11b mask
    {0xCCB0A4BC,0x01FF017F}, //TXLPF_CTUNE max for 11b mask and 11n HT20, NOT for HT40

// Tx ramping
    {0xCCB0A540,0x00200101}, //RG_TXPA_R2T_DELAY[5:0]

// RSSI threshold settings
    {0xCCB0A808,0x82600000}, //bit[23:20] rssi threshold for BLE

// BLE IF frequency
    {0xCCB0A824,0x09600640}, //0x640 = 1600KHz

// PHY mode control
    {0xCCB0A88C,0x00000010}, // RG_MODE_BY_PHY, 1 for WiFi, 0 for BLE
};
