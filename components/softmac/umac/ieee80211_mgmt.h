/*
 * Copyright (c) 2007, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         A MAC protocol implementation that does not do anything.
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

//#include "process.h"
#include "soc_types.h"
#include "ieee80211.h"
#include "wificonf.h"
#include "hwmac/drv_mac.h"

#ifndef __IEEE80211_MGMT_H__
#define __IEEE80211_MGMT_H__

/*---------------------------------------------------------------------------*/
#define MAX_STA_WSID_IDX (2)

typedef void (*mgmt_Handler)(struct sk_pbuff *skb);

typedef struct MGMT_MSG {
    u32 wsid:8;
    u32 action:8;
    u32 param1:8;
    u32 param2:8;
} MGMT_MSG;


typedef struct MGMT_WSIDTIMEREVENT {
    u32 wait_time[MAX_STA_WSID_IDX];
    u32 next_wsid;
} MGMT_NEXTTIMER;


s32 scan_func(AT_SCAN_CUSTOM_ARGS *cust, u8 txprob_time, u8 rssi_threshold);
void sta_conn_task(void *args);
void rx_process_mgmt(struct sk_pbuff *skb);
u8 getAvailableIndex(void);
TAG_AP_INFO *get_ap_info_by_ssid(char *ssid,u8 ssid_len);
int get_max_rssi_ap_info_by_ssid(char *ssid,TAG_AP_INFO *pAPInfo);
s32 tx_probe_req(u8 wsid);
s32 tx_authentication_req_seq1 (u8 wsid, u8 alg);
void softap_rx_assoc_req(struct sk_pbuff * skb);
void rx_association_rsp (struct sk_pbuff * skb);
void softap_rx_reassoc_req(struct sk_pbuff * skb);
void softap_rx_probe_request(struct sk_pbuff * skb);
void rx_probe_rsp (struct sk_pbuff * skb);
void rx_process_check_ap(struct sk_pbuff * skb);
void rx_mgmt_disassoc(struct sk_pbuff * skb);
void rx_authentication_rsp(struct sk_pbuff * skb);
void rx_mgmt_deauth(struct sk_pbuff * skb);
void rx_mgmt_action (struct sk_pbuff * skb);
void rx_probe_rsp_handler (struct sk_pbuff * skb);
void mgmt_msg_post(u8 wsid, u8 action, u8 reconnect);
int wifi_connect_start(u8 staid, u8 activeconn, void (*cbfn)(WIFI_RSP*));
int wifi_sta_reconnect(WIFI_DIS_REASON reason, u16 code, u8 bssid);
u32 check_chbandwidth(u32 ch);
void mgmt_register_cbfn(void (*mgmtcbfn)(packetinfo *));

#endif /* __IEEE80211_MGMT_H__ */
