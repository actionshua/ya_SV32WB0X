#ifndef __RC_H__
#define __RC_H__
#include <attrs.h>
#include "idmanage/drv_idmanage.h"
#include "mac_common.h"
#include <ieee80211.h>

typedef enum _ssv_rc_rate_type {
    RC_TYPE_B_ONLY = 0,
    RC_TYPE_LEGACY_GB,
    RC_TYPE_HT_LGI_20,
    RC_TYPE_HT_SGI_20,
    RC_TYPE_LEGACY_A,
    RC_TYPE_HT_LGI_20_5G,
    RC_TYPE_HT_SGI_20_5G,
    RC_TYPE_HT_GF,
    RC_TYPE_CUSTOM,
    RC_TYPE_MAX,
} ssv_rc_rate_type;

typedef struct t_DATARATE_INFO
{
    /*native rc*/
    ssv_rc_rate_type ratetype;
    u8 datarate;
    u8 m1datarate;
    u8 m2datarate;
    u8 index;
    u8 succfulcnt;
    u8 failcnt;
    u8 tryup;
    u8 ht40en;
    /* minstrel */
    u8                  preamble;
    u8                  wsid;
    u8                  bssid_idx;
    u8                  op_mode;
    u8                  ht_protect;
    u8                  current_rate0;
    u16                 supp_rates;
    u16                 networkMode;  
    u16                 non_ht_rates;
    union {
        u8              mcs_0;
        /* 16 bytes MCS information */
        struct ieee80211_mcs_info mcs;
    };
    u16                 ht_cap_info;    
    void *msp; //struct minstrel_ht_sta_priv
    /* common */
    u8 ratetbl[12];
    u8 ratetblnum;
    u8 mcs0_7;

}DATARATE_INFO;

typedef struct t_RATE_CONTROL_INFO
{
    struct ieee80211_supported_band sbands[IEEE80211_NUM_BANDS];
    void* mp;           //struct minstrel_priv
    void* rc_ops;
    u8    cts2self;
    DATARATE_INFO		  rateinfo[WLAN_MAX_STA];
    u16 rc_mask_sta;
    u16 rc_mask_ap;
    /**
     * USE_FIXED_RATE_ENABLE_MASK_NONE 0
     * USE_FIXED_RATE_ENABLE_MASK_STA 0x01
     * USE_FIXED_RATE_ENABLE_MASK_AP 0x02
     * USE_FIXED_RATE_ENABLE_MASK_ALL 0x03
     */
    u8 user_fixed_rate_enable_mask;
    u8 user_fixed_rate_try_cnt;
    u8 user_fixed_rate;
    u8 user_fixed_rate_ht40en;
    u16 user_bg_supprate;
    u8                    ifmode[2];
    u8 run_channel;
    OsMutex               r_mutex;
}RC_INFO;

typedef enum RATE_BG_TYPE 
{
	RATE_1M = 0,
	RATE_2M,
	RATE_5M,
	RATE_11M,
	RATE_6M,
	RATE_9M,
	RATE_12M,
	RATE_18M,
	RATE_24M,
	RATE_36M,
	RATE_48M,
	RATE_54M,
} RATE_BG_TYPE;

struct cfg_ht_capabilities {
	le16 ht_capabilities_info;
	u8 supported_mcs_set[16];
};

struct cfg_set_sta {
    u16 non_ht_supp_rates;
    bool short_preamble;
    struct cfg_ht_capabilities ht_capabilities;
};

extern RC_INFO rc;
extern int rc_init(void);
//extern int rc_sta_init(u8 wsid,struct ieee80211_hdr_3addr *mgmt, u32 mgmt_len,u8 htsupport, u8 ratenum, u8 *supportrate, enum nl80211_channel_type rctype, u8 run_channel);
extern int rc_sta_init(u8 mode, u8 wsid, struct cfg_set_sta *sta_info, u8 htsupport, u8 ratenum, u8 *supportrate,enum nl80211_channel_type rctype, u8 run_channel);
extern int rc_sta_deinit(u8 wsid);
extern int rc_rpt_handler(u8 *pbuf_addr, struct ieee80211_tx_info *info) ATTRIBUTE_SECTION_FAST_L2STACK;
extern int rc_get_rate(u8 id, struct ssv6006_tx_desc *pTxInfo) ATTRIBUTE_SECTION_FAST_L2STACK;
extern u8 rc_get_current_rate(u8 wsid);
extern int rc_rate_update(u8 wsid, u8 type, u8 run_channel);
extern void rc_update_rate_table(u8 wsid, u8 *pos, u16 tag_len, u16 bgratemask);
void rc_update_rate_table_v2(u8 wsid, struct ieee802_11_elems *elems, u16 bgratemask);
int rc_check_rate_table(u8 wsid, struct ieee802_11_elems *elems, u16 bgratemask);
extern u8 rc_get_rate_mask(u8 mode);
extern int rc_set_rate_mask(u8 mode, u16 rc_mask);
extern int rc_get_rc_info(u8 wsid);
extern int rc_set_fix_rate(struct ssv6006_tx_desc *pTxInfo, u8 phy_rate_idx, u8 try_cnt);
extern void rc_parse_rate_report(u8 wsid, void *TxPkt ,struct ieee80211_tx_info *info) ATTRIBUTE_SECTION_FAST_L2STACK;
extern void rc_tx_status(u8 wsid, u8 run_channel, struct ieee80211_tx_info *info) ATTRIBUTE_SECTION_FAST_L2STACK;
extern void rc_statistics_in_sram(bool in_sram);
extern u8 get_basedrate(void);
extern u8 get_basecrate(void);

#endif //#ifndef __RC_H__
