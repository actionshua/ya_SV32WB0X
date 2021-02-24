#ifndef _EDCA_NAV_H_
#define _EDCA_NAV_H_

enum WLAN_RC_PHY_TYPE {
	WLAN_RC_PHY_CCK=0,
	WLAN_RC_PHY_OFDM,
	WLAN_RC_PHY_HT_MF,
	WLAN_RC_PHY_HT_GF
};

#define HT_SIGNAL_EXT				6		//For 2.4G
#define HT_SIFS_TIME        		10
#define ACK_LEN						(14)	//include fcs
#define BA_LEN						(34)	//include fcs
#define RTS_LEN						(20)	//include fcs
#define CTS_LEN						(14)	//include fcs

#define PHY_MODE_LONG_PREAMBLE		0
#define PHY_MODE_SHORT_PREAMBLE		1
#define PHY_MODE_LONG_GI			0
#define PHY_MODE_SHORT_GI			1
#define PHY_MODE_GREENFIELD			2
#define PHY_MODE_G_ONLY				3


#define PHY_SUPPORT_RATE_NUMBER 39

// info for rate
struct phy_rate_info {
    u16 bitrate:7;      // values in IE
	u16 type:2;     // modulation
	u16 flag:1;     // for long/short preamble or long short GI
	u16 ackIndex:6; // ack rate hareware index
    u16 hkbps;          // Speed in hkbps, It is need to calculate perfect tx time
};

extern const struct phy_rate_info ssv6200_phy_rate[PHY_SUPPORT_RATE_NUMBER];
extern u16 EDCA_Duration(enum WLAN_RC_PHY_TYPE phy, int kbps,
			   u32 frameLen, bool shortPreamble, u8 rateidx, bool bShortGI, u8 isht40);


#endif /* _EDCA_ROM_H_ */

