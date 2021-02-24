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

#define SSV6020_TURISMOE_EXT_RF_TABLE_VER "4.00"  
  
ssv_cabrio_reg ssv6020_turismoE_ext_rf_setting[]={
// 2G5G SX
    {0xCBD0A4AC,0x00000389}, ///// 52M Fref for both loopA/loopB
    {0xCBD0A4B8,0x1E6231CC}, ///// ICP 0110 , Kpdouble
    {0xCBD0A4BC,0x01B84667}, ///// default iost011 / pol=1 / pfddely=00
    {0xCBD0A4C4,0x00002AF3}, ///// C2 11111

// 2G5G RX
    {0xCBD0A458,0x0BF34AAC},   // RG_5GRX_SQDC[2:0]=001 -> 101 ; RG_5GTX_DPDGM_BIAS[3:0]=1011 -> 0111

//-----------------------------------------------------------------------------
//  2GTX high performance wifi mode
//-----------------------------------------------------------------------------
//DAC increase gain
    {0xCBD0A504,0x01FF002A}, //TX LPF gain increase 2dB
    {0xCBD0A508,0x00000001}, //TRX_IDAC 1dB
    {0xCBD0A510,0x00042340}, //TXDAC IBAIS full increase 1.5 dB

// WF mode PA/mod setting
    {0xCBD0A44C,0x00482410}, //MOD SET PGA/LOBIAS/GMBIAS
    {0xCBD0A450,0x18277787}, //PA SET # of cell 111 / GMBIAS / VCAS BIAS
//BT mode PA/mod setting , turn on when BTmode
//    {0xCBD0A44C,0x520811}, //MOD SET PGA/LOBIAS/GMBIAS & BTPA SET GMBIAS / VCAS BIAS
//    {0xCBD0A450,0x182333C6}, //BTPA SET # of cell 110

//-----------------------------------------------------------------------------
//  5GTX high performance wifi mode
//-----------------------------------------------------------------------------
    {0xCBD0A418,0xC66E66C0},  // 5G trx Divider LDO
    {0xCBD0A480,0x6E0001E7},  // 5g tx pga bias/gain
    {0xCBD0A408,0x03333335},  // 5g tx gain manual
    {0xCBD0A484,0xB6FA923B},  // pa bias
    {0xCBD0A5A8,0x00080801},  // 2G Tx ramping

//if( RF_5G_BAND == 1 ){
//        {0xCBD0A50C,0x12A31AAE},  //txlpf, common mode reduce for 5g mode. setting diff with 2gtx , will optimize further
//} else {
    {0xCBD0A50c,0x5AA31AAE},  //txlpf, common mode reduce for 5g mode. setting diff with 2gtx , will optimize further
//}

// baseband
    {0xCBD0A808,0x88800000}, // bit[31] rg_sign_swap, bit[27] rg_adc_edge, bit[23:20] rssi_adc_th
    {0xCBD0A8CC,0x141E157C}, // set 5G band threshold 5150, 5500
    {0xCBD0A8D0,0x00001644}, // set 5G band threshold 5700

// OrionA T40 RF_D
// Tx/Rx pad switch for External ADC/DAC use
// OrionA RF_D/PMU settings for FPGA mode
    {0xCBD0A820,0x00000002}, // bit[2:0] rg_rssi_samp_phase change to 0x2 for fast
                             // AGC loop delay in FPGA mode
    {0xCBD0A404,0x28000000}, // bit[29] RG_EN_TXLPF_IN_PADSW, bit[27] RG_EN_RX_PADSW
    {0xCBD0A88C,0x00000000}, // restore for the initial value for the sake
                             // of not being hardware reseted
    {0xCBD0A408,0x03333384}, // RF Tx gain manual set to -8 step for FPGA power EVM
};
