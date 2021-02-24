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
 
#define SSV6020_TURISMOE_BLE_PHY_TABLE_VER "9.00"

ssv_cabrio_reg ssv6020_turismoE_ble_phy_setting[]={
// BLE enable
    {0xccb10000,0x8000000b}, // bit[31], RGW_BB_CLK_SEL     , 1'b1 40M DPLL clk 
                                                  // bit[19], RGW_RF_PWR_SAVE_OFF, 1'b0 clock gate on
                                                  // bit[18], RGW_RF_GATE_OFF    , 1'b0 clock gate on
                                                  // bit[17], RGW_RX_GATE_OFF    , 1'b0 clock gate on
                                                  // bit[16], RGW_TX_GATE_OFF    , 1'b0 clock gate on

    {0xCCB100B4,0x02002000}, // bit[7:4] rgw_addr_cor_det_max
    {0xCCB100F0,0x80140000}, // bit[0] rgw_acc_det_en

// BLE Tx baseband gain
    {0xccb10010,0x04030980}, // set tx baseband gain to manual mode
//    {0xccb10030,0x01002800}, // lower tx gain to 40/256=0.15625
    
// BLE AGC
    {0xccb10168,0x70046072},// 11b agc rssi threshold, bb iq power threshold, agc target, agc saturation
    {0xccb1016c,0x0F1F0000},// analog est delay, wait t final, rx agc done t(should be less than wait t final)
    {0xccb10170,0x630F36D0},
    {0xccb10174,0x100c0003},
    {0xccb10178,0x01100000},

// Rx Low-IF
    {0xccb10034,0x0000A666}, // bit[19:0] RGW_RX_DDC_RATE 2M Low IF
                             // round(1048576*1.625e6/40e6)
};
