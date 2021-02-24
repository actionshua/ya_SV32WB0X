/*
 * Driver interface definition
 * Copyright (c) 2003-2010, Jouni Malinen <j@w1.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README and COPYING for more details.
 *
 * This file defines a driver interface used by both %wpa_supplicant and
 * hostapd. The first part of the file defines data structures used in various
 * driver operations. This is followed by the struct wpa_driver_ops that each
 * driver wrapper will beed to define with callback functions for requesting
 * driver operations. After this, there are definitions for driver event
 * reporting with wpa_supplicant_event() and some convenience helper functions
 * that can be used to report events.
 */

#ifndef _DRV_SECURITY_H_
#define _DRV_SECURITY_H_

#include "drv_security_def.h"
#include "mac_common.h"

/**
 * Define Constant vlaues for WSID:
 *
 */
#define WSID_0                          0
#define WSID_1                          1
#define WSID_GROUP_ADDR               0xe  
#define WSID_NOT_FOUND                0xf

/**
* SSV6006 HW Security Table: 2 BSSID entry + 8 WSID entry (in packet buffer):
*/
#define SSV6006_HW_SEC_TABLE_SIZE       632 //2*BSSID(140 bytes) + 8*WSID(44 bytes)
#define SSV6006_HW_KEY_SIZE              32  //one hw key size, refer to ssv6006_hw_key
#define SSV6006_PAIRWISE_KEY_OFFSET      12  //refer to ssv6006_hw_sta_key
#define SSV6006_GROUP_KEY_OFFSET         12  //refer to ssv6006_bss

/**
* struct ssv6006_hw_sec - ssv6006 hardware security engine data structure.
* This descriptor is shared with ssv6006 hardware and driver.
*/
#define SSV6006_SECURITY_KEY_LEN              (32)

struct ssv6006_hw_key {
    u8          key[SSV6006_SECURITY_KEY_LEN];
}__attribute__((packed));

/**
* Key index for each security
* - WEP security: key indexes 0~3 are all stored in pair_key_idx.
* - others security: pairwise key index is stored in pair_key_idx,
*                    group key indexes are stored in group_key_idx.
*/
struct ssv6006_hw_sta_key {
    u8         	pair_key_idx;       /* 0: pairwise key, 1-3: group key */
    u8         	pair_cipher_type;   //WEP,TKIP,CCMP
    u8          valid;              /* 0: invalid entry, 1: valid entry asic hw don't check this field*/
    u8          reserve[1];
    u32         tx_pn_l;
    u32         tx_pn_h;

    struct ssv6006_hw_key pair;
}__attribute__((packed));

struct ssv6006_bss {
    u8          group_key_idx;
    u8          group_cipher_type;  //WEP,TKIP,CCMP
    u8          reserve[2];
    u32         tx_pn_l;
    u32         tx_pn_h;

	struct ssv6006_hw_key group_key[4]; //mapping to protocol group key 1-3
}__attribute__((packed));

struct ssv6006_hw_sec {
    struct ssv6006_bss bss_group[2];       /* The maximal number of VIFs: 2 */
    struct ssv6006_hw_sta_key sta_key[WLAN_MAX_STA];  /* The maximal number of STAs: 8 */
}__attribute__((packed));

s32 drv_sec_init(void);
s32 drv_sec_reset_key_tbl(void);
int drv_sec_set_key(u8 vif_idx, enum SEC_ALG alg, u8 wsid, 
                          int key_idx, u8 key_type, const u8 *key, size_t key_len);
u8 drv_sec_get_cipher_type(u8 key_type, u8 wsid, u8 vif_idx);
void drv_sec_set_cipher_type(u8 key_type, u8 wsid, u8 vif_idx, u8 cipher);
void drv_sec_set_key_idx(u8 key_type, u8 wsid, u8 vif_idx, u8 key_idx);
void drv_sec_set_hw_key(enum SSV6XXX_WSID_SEC key_type, u8 wsid, u8 vif_idx, u8 key_idx, 
            u16 alg, u8 *key, size_t key_len);

void drv_buckup_hwkey(void) ATTRIBUTE_SECTION_FAST_L2STACK;
void drv_restore_hwkey(void) ATTRIBUTE_SECTION_FAST_L2STACK;

#endif /* _DRV_SECURITY_H_ */

