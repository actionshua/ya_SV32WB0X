#ifndef MINSTREL_PORTING_H
#define MINSTREL_PORTING_H
#include <core/rc_def.h>
#include <attrs.h>
#include <soc_types.h>
#include <ieee80211.h>
#include <idmanage/pbuf.h>
#include <rc.h>

#define HW_MAX_RATE_TRIES   4
#define HW_MAX_RATES        4

#define RC_MINSTREL 0
#define RC_PIDE 1

#define RC_ALG RC_MINSTREL


#if 0
static inline struct ieee80211_tx_info *IEEE80211_SKB_CB(struct ssv6006_tx_desc *skb)
{
	return (struct ieee80211_tx_info *)(&(skb->dummy0)); //use txinfo ampdu_tx_bitmap_lw instead.
}
#endif
//extern struct phy_rate_info ssv6200_phy_rate[PHY_SUPPORT_RATE_NUMBER];

void m_rc_init(void* hwdev,u8 max_rates,u8 max_rate_tries);

int m_rc_get_rate(void *ref, DATARATE_INFO *sta, u8 run_channel, void *TxPkt) ATTRIBUTE_SECTION_FAST_L2STACK;

void rate_control_tx_status(void *ref, DATARATE_INFO *sta, u8 run_channel, struct ieee80211_tx_info *info) ATTRIBUTE_SECTION_FAST_L2STACK;

void m_rc_rate_init(u8 run_channel,enum nl80211_channel_type rctype, DATARATE_INFO *sta);

void m_rc_rate_update(struct ieee80211_supported_band *sband, DATARATE_INFO *sta, enum nl80211_channel_type oper_chan_type);

int m_rc_alloc_sta(void *ref,DATARATE_INFO *sta, struct cfg_set_sta *sta_info);

void m_rc_free_sta(void *ref,DATARATE_INFO *sta);
//void rate_control_set_erp_protect(bool param);
//bool rate_control_get_erp_protect(void);
void rate_control_parse_rate_report(void *TxPkt,struct ieee80211_tx_info *info) ATTRIBUTE_SECTION_FAST_L2STACK ;
s8 rate_lowest_index(struct ieee80211_supported_band *sband, u16 supp_rates);
int rate_supported(u16 supp_rates, enum ieee80211_band band, int index);
void rate_control_set_preamble(DATARATE_INFO *sta, u8 preamble);
void rate_control_fix_rate(u8 phymode ,s8 idx ,u8 shortlong, u8 ht40);
void m_rc_set_param (u32 mode, u8 opmode, u32 param);
bool rate_control_is_nmode_rate(u8 wsid);
void rate_control_set_gf(u8 gf_st);
void rate_control_set_erp_protect(bool param);
bool rate_control_get_erp_protect(void);


/* Rate control algorithms */
extern s32 rate_control_pid_init(void);

//extern void rc80211_minstrel_init(void);
//extern void rc80211_minstrel_exit(void);

extern void* rc80211_minstrel_ht_init(void* hwdev, u8 max_rates,u8 max_rate_tries, rom_rc_minstrel_thunk_st *thunk,rc_sample_table *sample_tbl);

extern void rc80211_minstrel_ht_exit(void);
extern bool rate_control_sta_exist(DATARATE_INFO *sta);
extern bool rate_control_sta_exist(DATARATE_INFO *sta);
extern void m_rc_rpt_handler(u8 *pbuf_addr, struct ieee80211_tx_info *info) ATTRIBUTE_SECTION_FAST_L2STACK;
void m_rc_statistics_in_sram(bool in_sram);

#endif /* MINSTREL_PORTING_H */
