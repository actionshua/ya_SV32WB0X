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

#define SSV6020_TURISMOE_RF_TABLE_VER "3.00"  
  
ssv_cabrio_reg ssv6020_turismoE_rf_setting[]={
// Xtal settings
    {0xCCB0B000,0x24C09015}, //

// SX register

// calibration and loop
    {0xCCB0A460,0xFA8551D2}, // sx aac dis, PRM/SPLPF/IOSTHREF off

// RX register
    {0xCCB0A420,0x2C614C6F}, // TZ vcm 000 , sca load 000
    {0xCCB0A418,0x11C002AA}, // feabb ldo 11 ; lpf ldo 00
    {0xCCB0A428,0x1C50C0DF}, // TZ bst 01
    {0xCCB0A4C4,0x5AA00206}, // RX Filter VCM 000

//TX register
    {0xCCB0B010,0xAAAA003C}, //DLDO --> 111
    {0xCCB0A408,0x0003DE42}, //2GTX gain manual
    {0xCCB0A448,0x41072480}, //2GTXFE bias/capsw setting
    {0xCCB0A454,0x1F87E108}, //TXPGA setting    

// ADC DAC edge selection
    {0xCCB0A808,0x82000010},
    {0xCCB0A88C,0x00000010},

// PHY mode control
    {0xCCB0A88C,0x00000010}, // RG_MODE_BY_PHY, 1 for WiFi, 0 for BLE
};

//ssv_cabrio_reg ssv6020_turismoE_rf_hp_patch[]={
//    disable(PADPD},       // do not need learn PA curve
//    disable(GreenTx},     // RF gain manual mode is turned on
//    SET_RG_TX_GAIN(0x30}, // fix 2G Tx gain at -24dB level
//}
