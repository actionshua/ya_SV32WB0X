#ifndef _DRV_PHY_COMMON_H_
#define _DRV_PHY_COMMON_H_


typedef enum {
    RADIO_BAND_2G=0,
    RADIO_BAND_5100=1,
    RADIO_BAND_5500=2,
    RADIO_BAND_5700=3,
    RADIO_BAND_5900=4,
}RADIO_BAND;   

enum nl80211_channel_type{   
    NL80211_CHAN_NO_HT = 0,
    NL80211_CHAN_HT20,
    NL80211_CHAN_HT40MINUS,
    NL80211_CHAN_HT40PLUS,
    NL80211_CHAN_AUTO,
};

#endif /* _DRV_PHY_COMMON_H_ */

