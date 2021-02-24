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

#define SSV6020_TURISMOE_RF_TABLE_VER "9.00"  
  
ssv_cabrio_reg ssv6020_turismoE_rf_setting[]={
    {0xCCB0A808,0x0a000000}, // bit[31] set to 0 for signed adc data input without edge: 0x0a000000
//    {0xCCB0A810,0x21000000}, // change DAC clock sampling edge default:0x1000000
// 2G/5G R2T ramping control
    {0xCCB0A540,0x001F1F01}, // set 2G R2T delay time
   
// Tx gain by band control
    {0xCCB0A408,0x0003DE30},

// RF mode control selection
    {0xCCB0A88C,0x00000010}, // rf_phy_mode controlled by PHY, bit[0] rg_oriona_sx_loop_sel

// Tx gain by band control
    {0xCCB0A408,0x0003DE80}, // 2G Tx gain to -8 steps for OrionA settings

// turn off flash clock
//    {0xC0000018,0x00000004},
};

//ssv_cabrio_reg ssv6020_turismoE_rf_hp_patch[]={
//    disable(PADPD},       // do not need learn PA curve
//    disable(GreenTx},     // RF gain manual mode is turned on
//    SET_RG_TX_GAIN(0x30}, // fix 2G Tx gain at -24dB level
//}
