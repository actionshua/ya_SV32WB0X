#ifndef RC_DEF_H
#define RC_DEF_H

#include <soc_types.h>
#include <phy/drv_phy_common.h>
//#include <mlme.h>

#define IEEE80211_HT_MCS_MASK_LEN       10
/**
 * struct ieee80211_mcs_info - MCS information
 * @rx_mask: RX mask
 * @rx_highest: highest supported RX rate. If set represents
 *	the highest supported RX data rate in units of 1 Mbps.
 *	If this field is 0 this value should not be used to
 *	consider the highest RX data rate supported.
 * @tx_params: TX parameters
 */
struct ieee80211_mcs_info {
	u8 rx_mask[IEEE80211_HT_MCS_MASK_LEN];
	u16 rx_highest;
	u8 tx_params;
	u8 reserved[3];
} __attribute__((packed));

/**
 * struct ieee80211_vht_mcs_info - VHT MCS information
 * @rx_mcs_map: RX MCS map 2 bits for each stream, total 8 streams
 * @rx_highest: Indicates highest long GI VHT PPDU data rate
 *	STA can receive. Rate expressed in units of 1 Mbps.
 *	If this field is 0 this value should not be used to
 *	consider the highest RX data rate supported.
 * @tx_mcs_map: TX MCS map 2 bits for each stream, total 8 streams
 * @tx_highest: Indicates highest long GI VHT PPDU data rate
 *	STA can transmit. Rate expressed in units of 1 Mbps.
 *	If this field is 0 this value should not be used to
 *	consider the highest TX data rate supported.
 */
struct ieee80211_vht_mcs_info {
	u16 rx_mcs_map;
	u16 rx_highest;
	u16 tx_mcs_map;
	u16 tx_highest;
} __attribute__((packed));


#define PHY_MODE_LONG_PREAMBLE		0
#define PHY_MODE_SHORT_PREAMBLE		1
#define PHY_MODE_LONG_GI			0
#define PHY_MODE_SHORT_GI			1
#define PHY_MODE_GREENFIELD			2
#define PHY_MODE_G_ONLY				3

#define PHY_SUPPORT_RATE_NUMBER			39
#define SSV6200_SUPPORT_RATE_NUMBER		12

#define MCS_GROUP_RATES	8
#define SAMPLE_COLUMNS	10
/* maximum number of rate stages */
#define IEEE80211_TX_MAX_RATES	5
#if 0
enum WLAN_RC_PHY_TYPE {
	WLAN_RC_PHY_CCK=0,
	WLAN_RC_PHY_OFDM,
	WLAN_RC_PHY_HT_MF,
	WLAN_RC_PHY_HT_GF
};
#endif

/* Spatial Multiplexing Power Save Modes (for capability) */
#define WLAN_HT_CAP_SM_PS_STATIC	0
#define WLAN_HT_CAP_SM_PS_DYNAMIC	1
#define WLAN_HT_CAP_SM_PS_INVALID	2
#define WLAN_HT_CAP_SM_PS_DISABLED	3

#define IEEE80211_TX_CTL_STBC_SHIFT		23

/* 802.11n HT capabilities masks (for cap_info) */
#define IEEE80211_HT_CAP_LDPC_CODING		0x0001
#define IEEE80211_HT_CAP_SUP_WIDTH_20_40	0x0002
#define IEEE80211_HT_CAP_SM_PS			0x000C
#define		IEEE80211_HT_CAP_SM_PS_SHIFT	2
#define IEEE80211_HT_CAP_GRN_FLD		0x0010
#define IEEE80211_HT_CAP_SGI_20			0x0020
#define IEEE80211_HT_CAP_SGI_40			0x0040
#define IEEE80211_HT_CAP_TX_STBC		0x0080
#define IEEE80211_HT_CAP_RX_STBC		0x0300
#define		IEEE80211_HT_CAP_RX_STBC_SHIFT	8
#define IEEE80211_HT_CAP_DELAY_BA		0x0400
#define IEEE80211_HT_CAP_MAX_AMSDU		0x0800
#define IEEE80211_HT_CAP_DSSSCCK40		0x1000
#define IEEE80211_HT_CAP_RESERVED		0x2000
#define IEEE80211_HT_CAP_40MHZ_INTOLERANT	0x4000
#define IEEE80211_HT_CAP_LSIG_TXOP_PROT		0x8000

/* 802.11n HT extended capabilities masks (for extended_ht_cap_info) */
#define IEEE80211_HT_EXT_CAP_PCO		0x0001
#define IEEE80211_HT_EXT_CAP_PCO_TIME		0x0006
#define		IEEE80211_HT_EXT_CAP_PCO_TIME_SHIFT	1
#define IEEE80211_HT_EXT_CAP_MCS_FB		0x0300
#define		IEEE80211_HT_EXT_CAP_MCS_FB_SHIFT	8
#define IEEE80211_HT_EXT_CAP_HTC_SUP		0x0400
#define IEEE80211_HT_EXT_CAP_RD_RESPONDER	0x0800

/* 802.11n HT capability AMPDU settings (for ampdu_params_info) */
#define IEEE80211_HT_AMPDU_PARM_FACTOR		0x03
#define IEEE80211_HT_AMPDU_PARM_DENSITY		0x1C
#define		IEEE80211_HT_AMPDU_PARM_DENSITY_SHIFT	2
/**
 * enum ieee80211_band - Frequency band
 * @IEEE80211_BAND_2GHZ: 2.4 GHz ISM band
 * @IEEE80211_BAND_5GHZ: around 5 GHz band (4.9 - 5.7 GHz)
 */

enum ieee80211_band {
	IEEE80211_BAND_2GHZ,
	IEEE80211_BAND_5GHZ,

	/* keep last */
	IEEE80211_NUM_BANDS
};

#if 0
// info for rate
struct phy_rate_info {
    u16 bitrate:7;      // values in IE
	u16 type:2;     // modulation
	u16 flag:1;     // for long/short preamble or long short GI
	u16 ackIndex:6; // ack rate hareware index
    u16 hkbps;          // Speed in hkbps, It is need to calculate perfect tx time
};
#endif

enum RC_PARA {
    RC_PARA_SET_RATE_MASK,
    RC_PARA_SET_HT_PROTECT,
    RC_PARA_SET_TX_SGI,
    RC_PARA_TEST
};

enum mac80211_tx_control_flags {
	IEEE80211_TX_CTL_REQ_TX_STATUS		= BIT(0),
	IEEE80211_TX_CTL_ASSIGN_SEQ		= BIT(1),
	IEEE80211_TX_CTL_NO_ACK			= BIT(2),
	IEEE80211_TX_CTL_CLEAR_PS_FILT		= BIT(3),
	IEEE80211_TX_CTL_FIRST_FRAGMENT		= BIT(4),
	IEEE80211_TX_CTL_SEND_AFTER_DTIM	= BIT(5),
	IEEE80211_TX_CTL_AMPDU			= BIT(6),
	IEEE80211_TX_CTL_INJECTED		= BIT(7),
	IEEE80211_TX_STAT_TX_FILTERED		= BIT(8),
	IEEE80211_TX_STAT_ACK			= BIT(9),
	IEEE80211_TX_STAT_AMPDU			= BIT(10),
	IEEE80211_TX_STAT_AMPDU_NO_BACK		= BIT(11),
	IEEE80211_TX_CTL_RATE_CTRL_PROBE	= BIT(12),
	IEEE80211_TX_INTFL_NEED_TXPROCESSING	= BIT(14),
	IEEE80211_TX_INTFL_RETRIED		= BIT(15),
	IEEE80211_TX_INTFL_DONT_ENCRYPT		= BIT(16),
	IEEE80211_TX_CTL_NO_PS_BUFFER		= BIT(17),
	IEEE80211_TX_CTL_MORE_FRAMES		= BIT(18),
	IEEE80211_TX_INTFL_RETRANSMISSION	= BIT(19),
	/* hole at 20, use later */
	IEEE80211_TX_INTFL_NL80211_FRAME_TX	= BIT(21),
	IEEE80211_TX_CTL_LDPC			= BIT(22),
	IEEE80211_TX_CTL_STBC			= BIT(23) | BIT(24),
	IEEE80211_TX_CTL_TX_OFFCHAN		= BIT(25),
	IEEE80211_TX_INTFL_TKIP_MIC_FAILURE	= BIT(26),
	IEEE80211_TX_CTL_NO_CCK_RATE		= BIT(27),
	IEEE80211_TX_STATUS_EOSP		= BIT(28),
	IEEE80211_TX_CTL_USE_MINRATE		= BIT(29),
	IEEE80211_TX_CTL_DONTFRAG		= BIT(30),
};

enum mac80211_rate_control_flags {
	IEEE80211_TX_RC_USE_RTS_CTS		= BIT(0),
	IEEE80211_TX_RC_USE_CTS_PROTECT		= BIT(1),
	IEEE80211_TX_RC_USE_SHORT_PREAMBLE	= BIT(2),

	/* rate index is an MCS rate number instead of an index */
	IEEE80211_TX_RC_MCS			= BIT(3),
	IEEE80211_TX_RC_GREEN_FIELD		= BIT(4),
	IEEE80211_TX_RC_40_MHZ_WIDTH		= BIT(5),
	IEEE80211_TX_RC_DUP_DATA		= BIT(6),
	IEEE80211_TX_RC_SHORT_GI		= BIT(7),
	/* tx report*/
	IEEE80211_TX_RC_SUCCESS		= BIT(8),
    IEEE80211_TX_RC_CCK         = BIT(9),
    
};

#ifndef max
#define max(x, y) ({				\
	typeof(x) _max1 = (x);			\
	typeof(y) _max2 = (y);			\
	(void) (&_max1 == &_max2);		\
	_max1 > _max2 ? _max1 : _max2; })
#endif

#ifndef min
#define min(x, y) ({				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(void) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; })
#endif
#if 0
/**
 * struct ieee80211_mcs_info - MCS information
 * @rx_mask: RX mask
 * @rx_highest: highest supported RX rate. If set represents
 *	the highest supported RX data rate in units of 1 Mbps.
 *	If this field is 0 this value should not be used to
 *	consider the highest RX data rate supported.
 * @tx_params: TX parameters
 */
struct ieee80211_mcs_info {
    u8 rx_mask[IEEE80211_HT_MCS_MASK_LEN];
    u16 rx_highest;
    u8 tx_params;
    u8 reserved[3];
} ;

/**
 * struct ieee80211_ht_cap - HT capabilities
 *
 
 */
struct ieee80211_ht_cap {
    u16 cap_info;
    u8 ampdu_params_info;

    /* 16 bytes MCS information */
    struct ieee80211_mcs_info mcs;

    u16 extended_ht_cap_info;
    u32 tx_BF_cap_info;
    u8 antenna_selection_info;
} ;

struct ieee80211_ht_info {
    u8 control_chan;
    u8 ht_param;
    u16 operation_mode;
    u16 stbc_param;
    u8 basic_set[16];
} ;
#endif

/**
 * enum ieee80211_rate_flags - rate flags
 *
 * Hardware/specification flags for rates. These are structured
 * in a way that allows using the same bitrate structure for
 * different bands/PHY modes.
 *
 * @IEEE80211_RATE_SHORT_PREAMBLE: Hardware can send with short
 *	preamble on this bitrate; only relevant in 2.4GHz band and
 *	with CCK rates.
 * @IEEE80211_RATE_MANDATORY_A: This bitrate is a mandatory rate
 *	when used with 802.11a (on the 5 GHz band); filled by the
 *	core code when registering the wiphy.
 * @IEEE80211_RATE_MANDATORY_B: This bitrate is a mandatory rate
 *	when used with 802.11b (on the 2.4 GHz band); filled by the
 *	core code when registering the wiphy.
 * @IEEE80211_RATE_MANDATORY_G: This bitrate is a mandatory rate
 *	when used with 802.11g (on the 2.4 GHz band); filled by the
 *	core code when registering the wiphy.
 * @IEEE80211_RATE_ERP_G: This is an ERP rate in 802.11g mode.
 */
enum ieee80211_rate_flags {
	IEEE80211_RATE_SHORT_PREAMBLE	= 1<<0,
	IEEE80211_RATE_MANDATORY_A	= 1<<1,
	IEEE80211_RATE_MANDATORY_B	= 1<<2,
	IEEE80211_RATE_MANDATORY_G	= 1<<3,
	IEEE80211_RATE_ERP_G		= 1<<4,
};

/**
 * struct ieee80211_channel - channel definition
 *
 * This structure describes a single channel for use
 * with cfg80211.
 *
 * @center_freq: center frequency in MHz
 * @hw_value: hardware-specific value for the channel
 * @flags: channel flags from &enum ieee80211_channel_flags.
 * @orig_flags: channel flags at registration time, used by regulatory
 *	code to support devices with additional restrictions
 * @band: band this channel belongs to.
 * @max_antenna_gain: maximum antenna gain in dBi
 * @max_power: maximum transmission power (in dBm)
 * @max_reg_power: maximum regulatory transmission power (in dBm)
 * @beacon_found: helper to regulatory code to indicate when a beacon
 *	has been found on this channel. Use regulatory_hint_found_beacon()
 *	to enable this, this is useful only on 5 GHz band.
 * @orig_mag: internal use
 * @orig_mpwr: internal use
 */
struct ieee80211_channel {
	enum ieee80211_band band;
	u16 center_freq;
	u16 hw_value;
	u32 flags;
	int max_antenna_gain;
	int max_power;
	int max_reg_power;
	bool beacon_found;
	u32 orig_flags;
	int orig_mag, orig_mpwr;
};

/**
 * struct ieee80211_rate - bitrate definition
 *
 * This structure describes a bitrate that an 802.11 PHY can
 * operate with. The two values @hw_value and @hw_value_short
 * are only for driver use when pointers to this structure are
 * passed around.
 *
 * @flags: rate-specific flags
 * @bitrate: bitrate in units of 100 Kbps
 * @hw_value: driver/hardware value for this rate
 * @hw_value_short: driver/hardware value for this rate when
 *	short preamble is used
 */
struct ieee80211_rate {
	u32 flags;
	u16 bitrate;
	u16 hw_value, hw_value_short;
};

/**
 * struct ieee80211_sta_ht_cap - STA's HT capabilities
 *
 * This structure describes most essential parameters needed
 * to describe 802.11n HT capabilities for an STA.
 *
 * @ht_supported: is HT supported by the STA
 * @cap: HT capabilities map as described in 802.11n spec
 * @ampdu_factor: Maximum A-MPDU length factor
 * @ampdu_density: Minimum A-MPDU spacing
 * @mcs: Supported MCS rates
 */
struct ieee80211_sta_ht_cap {
	u16 cap; /* use IEEE80211_HT_CAP_ */
	bool ht_supported;
	u8 ampdu_factor;
	u8 ampdu_density;
	struct ieee80211_mcs_info mcs;
};

/**
 * struct ieee80211_supported_band - frequency band definition
 *
 * This structure describes a frequency band a wiphy
 * is able to operate in.
 *
 * @channels: Array of channels the hardware can operate in
 *	in this band.
 * @band: the band this structure represents
 * @n_channels: Number of channels in @channels
 * @bitrates: Array of bitrates the hardware can operate with
 *	in this band. Must be sorted to give a valid "supported
 *	rates" IE, i.e. CCK rates first, then OFDM.
 * @n_bitrates: Number of bitrates in @bitrates
 * @ht_cap: HT capabilities in this band
 */
struct ieee80211_supported_band {
	struct ieee80211_channel *channels;
	struct ieee80211_rate *bitrates;
	enum ieee80211_band band;
	int n_channels;
	int n_bitrates;
	struct ieee80211_sta_ht_cap ht_cap;
};

struct rc_param_st
{
    //1st global setting
    u16 host_rate_mask_sta;
    u16 host_rate_mask_ap;
	
    u32 host_ht_protect_en:1;
    u32 host_tx_SGI_en:1;
    u32 FixRateEnable:1;
    u32 gf_enable:1;
    u32 erp_protect:1;
    u32 host_tx_s_preamble:1;
    u32 rsvd:26;

    //by sta
    union {
        u8 mcs_0;
        /* 16 bytes MCS information */
        struct ieee80211_mcs_info mcs;
    };
    struct ieee80211_supported_band* sband;
    enum nl80211_channel_type ch_type;
    u8      op_mode;    
    u16     ht_cap_info;
    u16     supp_rates;    
    u16     preamble:1;
    u16     networkMode:2;
    u16     ampdu_tx:1;
    u16     ht_protect:1;
    u16     rsvd1:11;
    
};

/**
 * struct ieee80211_tx_rate - rate selection/status
 *
 * @idx: rate index to attempt to send with
 * @flags: rate control flags (&enum mac80211_rate_control_flags)
 * @count: number of tries in this rate before going to the next rate
 *
 * A value of -1 for @idx indicates an invalid rate and, if used
 * in an array of retry rates, that no more rates should be tried.
 *
 * When used for transmit status reporting, the driver should
 * always report the rate along with the flags it used.
 *
 * &struct ieee80211_tx_info contains an array of these structs
 * in the control information, and it will be filled by the rate
 * control algorithm according to what should be sent. For example,
 * if this array contains, in the format { <idx>, <count> } the
 * information
 *    { 3, 2 }, { 2, 2 }, { 1, 4 }, { -1, 0 }, { -1, 0 }
 * then this means that the frame should be transmitted
 * up to twice at rate 3, up to twice at rate 2, and up to four
 * times at rate 1 if it doesn't get acknowledged. Say it gets
 * acknowledged by the peer after the fifth attempt, the status
 * information should then contain
 *   { 3, 2 }, { 2, 2 }, { 1, 1 }, { -1, 0 } ...
 * since it was transmitted twice at rate 3, twice at rate 2
 * and once at rate 1 after which we received an acknowledgement.
 */
struct ieee80211_tx_rate {
	s8 idx;
	u8 count;
	u16 flags;
}__attribute__((__packed__));

struct ieee80211_tx_info {
	/* common information */
	u32 flags;

	struct {
		u8 ampdu_ack_len;
		u8 ampdu_len;
		struct ieee80211_tx_rate rates[IEEE80211_TX_MAX_RATES];
		/* 15 bytes free */
	} status;
};

struct ieee80211_tx_rate_control {
	void *hw;
	struct ieee80211_supported_band *sband;
	//struct ieee80211_bss_conf *bss_conf;
	void *skb;
    struct ieee80211_tx_info *info;
    u8 ht_protect; //bit 8 & bit9 in ht operation it
	bool short_preamble;
	u8 max_rate_idx;
	u32 rate_idx_mask;
	u8 rate_idx_mcs_mask[IEEE80211_HT_MCS_MASK_LEN];
	bool bss;
};


typedef struct rom_rc_minstrel_thunk_st{
    int   (* printf)( const char * format, ... );
    u32   (* os_ms2tick)(u32 ms);
    void *(* os_malloc)( u32 size );
    void  (* os_mfree)( void *mem );
    u32   (* os_gettick)(void);
    void *(* os_memset)(void *ptr, int x, unsigned long n);
    void  (* get_random_bytes)(u8* rand_num, u32 byte_cnt);
    s8    (* rate_lowest_index)(struct ieee80211_supported_band *sband, u16 supp_rates);
    int   (* rate_supported)(u16 supp_rates, enum ieee80211_band band, int index);    
    
}rom_rc_minstrel_thunk_st;


typedef struct rc_sample_table{
    u8 sample_table[SAMPLE_COLUMNS][MCS_GROUP_RATES];
}rc_sample_table;

struct rate_control_ops {
	const char *name;
	void *(*alloc)(void* hw, u8 max_rates,u8 max_rate_tries, rom_rc_minstrel_thunk_st *thunk);
	void (*free)(void *priv, rom_rc_minstrel_thunk_st *thunk);

	void *(*alloc_sta)(void *priv, int max_rates, rom_rc_minstrel_thunk_st *thunk);
	void (*rate_init)(void *priv, void *priv_sta, struct rc_param_st* rc_para_p, rom_rc_minstrel_thunk_st *thunk);
	void (*rate_update)(void *priv, void *priv_sta, struct rc_param_st* rc_para_p, rom_rc_minstrel_thunk_st *thunk);
	void (*free_sta)(void *priv, void *priv_sta, rom_rc_minstrel_thunk_st *thunk);

	void (*tx_status)(void *priv, struct ieee80211_supported_band *sband,
                      void *priv_sta, struct ieee80211_tx_info *info, rom_rc_minstrel_thunk_st *thunk);
	void (*get_rate)(void *priv, void *priv_sta, struct ieee80211_tx_info *info, bool ht_protect, rom_rc_minstrel_thunk_st *thunk, rc_sample_table *sample_tbl);

};


#endif /* IEEE80211_RATE_H */
