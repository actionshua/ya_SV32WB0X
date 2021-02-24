#ifndef _WIFI_API_H_
#define _WIFI_API_H_

#include "wificonf.h"
#include "logger.h"

#define WIFI_TAG       LOG_TAG_WIFI
#define WIFI_LOG_E(format, ...) log_e(WIFI_TAG, format, ##__VA_ARGS__)
#define WIFI_LOG_I(format, ...) log_i(WIFI_TAG, format, ##__VA_ARGS__)
#define RADIO_INIT(country, rcmask,ble) \
    ble_en(ble);    \
    set_country_code(country);\
    PBUF_Init();    \
    wifi_ampdu_rx_enable(AMPDU_RX_EN);\
    NETSTACK_RADIO.init();  \
    drv_sec_init(); \
    wifi_set_rate_mask(rcmask);\
    if(DEF==country) \
    {\
        WIFI_LOG_I("\33[35m ******************************************************************************\33[0m\r\n");\
        WIFI_LOG_I("\33[35m *                                                                            *\33[0m\r\n");\
        WIFI_LOG_I("\33[35m * The defalut country code is global. Please change it in feature.mk         *\33[0m\r\n");\
        WIFI_LOG_I("\33[35m * Global country code support the channel:                                   *\33[0m\r\n");\
        WIFI_LOG_I("\33[35m * 2.4G:1/2/3/4/5/6/7/8/9/10/11/12/13/14                                      *\33[0m\r\n");\
        WIFI_LOG_I("\33[35m * 5G  :36/40/44/48/52/56/60/64/100/104/108/112/116/120/124/128/132/136/140/  *\33[0m\r\n");\
        WIFI_LOG_I("\33[35m *      144/149/153/156/161                                                   *\33[0m\r\n");\
        WIFI_LOG_I("\33[35m *                                                                            *\33[0m\r\n");\
        WIFI_LOG_I("\33[35m ******************************************************************************\33[0m\r\n");\
    }
	
typedef struct CONNSTAINFO
{
    u8 mac[6];
    u8 ipaddr[4];
}CONNSTAINFO;

typedef struct CUS_SCAN_PARAM
{
    u32 channel5Gindex;
    u16 channel2Gindex;
    u8 *channel_seq;
    u8 channel_numbers;
    u16 scantime_in_ms;
    u16 staytime_in_ms;     ///< Stay time in ms after switch to home channel for online scan.
    u16 delaytime_in_ms;    ///< Delay time in ms before switch to scan channel for online scan.
    /*
     * Specific a SSID during scanning
     */
    char *ssid;
    u8 max_apcnt;
    void (*callbackfn)(void *);
}CUS_SCAN_PARAM;

typedef struct SCAN_PARAM
{
    u16 scantime_in_ms;
    u16 max_apcount;
    u8 *channel_seq;
    u8 channel_numbers;
    void (*callbackfn)(void *);
}SCAN_PARAM;

/// Structure for SSV NOW parameters
typedef struct _st_wifi_api_ssv_now_param
{
    u8 *pu8PeerMAC;       ///< [IN] Peer MAC address. (6 bytes)
    u8 *pu8Bssid;         ///< [IN] BSSID. (6 bytes)
    u8 *pu8OUI;           ///< [IN] The OUI value. (3 bytes)
    u8 *pu8Data;          ///< [IN] The vendor specific data.
    u32 u32DataLen;       ///< [IN] The length of the vendor specific data.
}__attribute__ ((packed)) ST_WIFI_API_SSV_NOW_PARAM;


/**
 * @brief Turn off RF & MAC & PHY to reduce power consumption. When start WIFI function the DUT will tuen on RF & MAC & PHY automatically.
 *        This API only work at WIFI_NONE mode.
 * @return the result. 0 : Successful, -1 : Failed.
 */
int DUT_wifi_OFF();

/**
 * @brief Get DUT current operation mode.
 * @return operation mode.
 */
WIFI_OPMODE get_DUT_wifi_mode();

/**
 * @brief Stop DUT activity and all connections will terminate.
 * @return none.
 */
void DUT_wifi_stop();

/**
 * @brief Active DUT functionality. DUT can run DUT_TWOSTA and DUT_CONCURRENT only when DUT has two different mac address.
 * @param mode   [IN] operation mode.
 * @return none.
 */
int DUT_wifi_start(WIFI_OPMODE mode);

#ifdef WPS_EN
int WPSStartPBC(bool bRegistrar, u8 *pPeerAddr, void (*wpsCbFun)(WIFI_WPS_RSP*), void (*connCbFun)(WIFI_RSP*));
int WPSStartPIN(bool bRegistrar, u32 pin, void (*wpsCbFun)(WIFI_WPS_RSP*), void (*connCbFun)(WIFI_RSP*));
int WPSGenPIN(u32 *pin);
#endif

#if (ENABLE_HK==1)
int homekit_softap_start(u8 *inIE, size_t inIELen);
int homekit_softap_stop();
#endif

/**
 * @brief Start scan task, only scan channel in 2.4G band. THe callback function will be excuted when scan task is ended.
 * @param callbackfn   [IN] callback function.
 * @return none.
 */
int scan_AP(void (*callbackfn)(void *));

/**
 * @brief Start scan task, only scan channel in 2.4G band. THe callback function will be excuted when scan task is ended.
 * @param ssid         [IN] Assign a specific ssid, the maximum length of ssid is 32, the maximum length doesn't include the terminal character 
 * @param callbackfn   [IN] callback function.
 * @return none.
 */
int scan_AP_2(char *ssid, void (*callbackfn)(void *));
#define scan_AP_ex scan_AP_2

/**
 * @brief Start scan task, only scan channel in 2.4G band. THe callback function will be excuted when scan task is ended.
 * @param ssid                      [IN] Assign a specific ssid, the maximum length of ssid is 32, the maximum length doesn't include the terminal character 
 * @param scantime_in_ms            [IN] how many time that stay in one channel
 * @param callbackfn                [IN] callback function.
 * @return none.
 */
int scan_AP_3(char *ssid, u16 scantime_in_ms, void (*callbackfn)(void *));

/**
 * @brief Start scan task. The callback function will be excuted when scan task is ended.
 * @param ssid                      [IN] Assign a specific ssid, the maximum length of ssid is 32, the maximum length doesn't include the terminal character
 * @param scantime_in_ms            [IN] how many time that stay in one channel.
 * @param staytime_in_ms            [IN] how many time that stay in home channel for online scan.
 * @param callbackfn                [IN] callback function.
 * @return none.
 */
int scan_AP_4(char *ssid, u16 scantime_in_ms, u16 staytime_in_ms, void (*callbackfn)(void *));

/**
 * @brief Start scan task. THe callback function will be excuted when scan task is ended.
 * @param ssid            [IN] Assign a specific ssid, the max length of ssid is 32 
 * @param callbackfn      [IN] callback function.
 * @param channelindex    [IN] Set the specific 2.4G channels to scan.
 * @param channel5Gindex  [IN] Set the specific 5G channels to scan.
 * @param scantime_in_ms  [IN] Scan time for each channel.
 * @param staytime_in_ms  [IN] Online scan: stay time after switch from scan channel to home channel.
 * @param delaytime_in_ms [IN] Online scan: delay time before switch from home channel to scan channel.
 * @return none.
 */
int scan_AP_custom(char *ssid, void (*callbackfn)(void *), u16 channel2Gindex, u32 channel5Gindex, u16 scantime_in_ms, u16 staytime_in_ms, u16 delaytime_in_ms);

/**
 * @brief Start connect to AP. This API is used for connect to the AP with hidden SSID.
 *        In TWOSTA mode, it's working when there's no any connection. 
 *        Otherwise, it will return -1.
 * @param pssid		        [IN] AP's SSID.
 * @param ssidlen	        [IN] Length of SSID.
 * @param pkey              [IN] AP's Passphrase.
 * @param keylen            [IN] Length of passphrase.
 * @param sectype           [IN] The encryption method. 0 : NONO. 1 : WEP. 2 : TKIP. 3 : CCMP.
                                                       4 : TKIP or CCMP. 5 : Allow all encryption method.
 * @param channel           [IN] Set the specific channel to do connection, channel set 0 means all channels are possible.
 * @param mac               [IN] AP's mac address. Input NULL if do not want to connect to specific AP.
 * @param noreconnecrt      [IN] 0:run reconnect after disconnection. 1: Don't run reconnect after disconnection
 * @param rssi_threshold    [IN] DUT will find a AP that SSSID is the same with pssid that the RSSI is stronger than rssi_threshold. If there is not a AP that SSID is the same with pssid that RSSI is stronger than rssi_threshold, DUT will choose a max rssi AP that SSID is the same with pssid.
 *                              0:don't check this condiction. 
 *                              > 0 
 * @param callbackfn        [IN] callback function.
 * @return the result. 0 : Successful, -1 : Failed.
 */

int wifi_connect_active_5 (u8 *pssid, u8 ssidlen, u8 *pkey, u8 keylen, u8 sectype, u8 channel, u8 *mac, u8 noreconnect, u8 rssi_threshold, void (*callbackfn)(WIFI_RSP*));

/**
 * @brief Start connect to AP. This API is used for connect to the AP with hidden SSID.
 *        In TWOSTA mode, it's working when there's no any connection. 
 *        Otherwise, it will return -1.
 * @param pssid		   [IN] AP's SSID.
 * @param ssidlen	   [IN] Length of SSID.
 * @param pkey         [IN] AP's Passphrase.
 * @param keylen       [IN] Length of passphrase.
 * @param sectype      [IN] The encryption method. 0 : NONO. 1 : WEP. 2 : TKIP. 3 : CCMP.
                                                   4 : TKIP or CCMP. 5 : Allow all encryption method.
 * @param channel      [IN] Set the specific channel to do connection, channel set 0 means all channels are possible.
 * @param mac          [IN] AP's mac address. Input NULL if do not want to connect to specific AP.
 * @param noreconnecrt [IN] 0:run reconnect after disconnection. 1: Don't run reconnect after disconnection
 * @param callbackfn   [IN] callback function.
 * @return the result. 0 : Successful, -1 : Failed.
 */

int wifi_connect_active_4 (u8 *pssid, u8 ssidlen, u8 *pkey, u8 keylen, u8 sectype, u8 channel, u8 *mac, u8 noreconnect, void (*callbackfn)(WIFI_RSP*));
/**
 * @brief Start connect to AP. This API is used for connect to the AP with hidden SSID.
 *        In TWOSTA mode, it's working when there's no any connection. 
 *        Otherwise, it will return -1.
 * @param pssid		   [IN] AP's SSID.
 * @param ssidlen	   [IN] Length of SSID.
 * @param pkey         [IN] AP's Passphrase.
 * @param keylen       [IN] Length of passphrase.
 * @param sectype      [IN] The encryption method. 0 : NONO. 1 : WEP. 2 : TKIP. 3 : CCMP.
                                                   4 : TKIP or CCMP. 5 : Allow all encryption method.
 * @param channel      [IN] Set the specific channel to do connection, channel set 0 means all channels are possible.
 * @param mac          [IN] AP's mac address. Input NULL if do not want to connect to specific AP.
 * @param callbackfn   [IN] callback function.
 * @return the result. 0 : Successful, -1 : Failed.
 */
int wifi_connect_active_3 (u8 *pssid, u8 ssidlen, u8 *pkey, u8 keylen, u8 sectype, u8 channel, u8 *mac, void (*callbackfn)(WIFI_RSP*));

/**
 * @brief Start connect to AP. This API is used for connect to the AP with hidden SSID.
 *        In TWOSTA mode, it's working when there's no any connection. 
 *        Otherwise, it will return -1.
 * @param pssid		   [IN] AP's SSID.
 * @param ssidlen	   [IN] Length of SSID.
 * @param pkey         [IN] AP's Passphrase.
 * @param keylen       [IN] Length of passphrase.
 * @param callbackfn   [IN] callback function.
 * @param sectype      [IN] The encryption method. 0 : NONO. 1 : WEP. 2 : TKIP. 3 : CCMP.
                                                   4 : TKIP or CCMP. 5 : Allow all encryption method.
 * @return the result. 0 : Successful, -1 : Failed.
 */
int wifi_connect_active_2 (u8 *pssid, u8 ssidlen, u8 *pkey, u8 keylen, void (*callbackfn)(WIFI_RSP*), u8 sectype);

/**
 * @brief Start connect to AP and allow all encryption method. This API is used for connect to the AP with hidden SSID.
 *        In TWOSTA mode, it's working when there's no any connection. 
 * @param pssid		   [IN] AP's SSID.
 * @param ssidlen	   [IN] Length of SSID.
 * @param pkey         [IN] AP's Passphrase.
 * @param keylen       [IN] Length of passphrase.
 * @param callbackfn   [IN] callback function.
 * @return the result. 0 : Successful, -1 : Failed.
 */
int wifi_connect_active (u8 *pssid, u8 ssidlen, u8 *pkey, u8 keylen, void (*callbackfn)(WIFI_RSP*));


/**
 * @brief Start connect to AP. THe callback function will be excuted when wifi status is changed.
 *        if the staid is illegal, it will return -1.
 *        If it's doesn't allos run this api in DUT operation mode. it will return -2.
 *        Channel of the second connection must same as the channel of exsited connection.
 *        Otherwise, it will return -3.
 *        Mac address of the second connection must different from the mac address of exsited connection.
 *        Otherwise, it will return -4.
 * @param staid        [IN] The sta index will like to start connection(0 or 1).
 * @param noreconnect  [IN] 0: reconnect after disconnection, 1: no reconnect after disconnection
 * @param callbackfn   [IN] callback function.
 * @return the result. 0 : Successful, others : Failed.
 */
int wifi_connect_3(u8 staid, u8 noreconnect, void (*callbackfn)(WIFI_RSP*));

/**
 * @brief Start connect to AP. THe callback function will be excuted when wifi status is changed.
 *        if the staid is illegal, it will return -1.
 *        If it's doesn't allos run this api in DUT operation mode. it will return -2.
 *        Channel of the second connection must same as the channel of exsited connection.
 *        Otherwise, it will return -3.
 *        Mac address of the second connection must different from the mac address of exsited connection.
 *        Otherwise, it will return -4.
 * @param staid        [IN] The sta index will like to start connection(0 or 1).
 * @param callbackfn   [IN] callback function.
 * @return the result. 0 : Successful, others : Failed.
 */
int wifi_connect_2(u8 staid, void (*callbackfn)(WIFI_RSP*));

/**
 * @brief Start connect to AP. THe callback function will be excuted when wifi status is changed.
 *        In TWOSTA mode, it's only can start connection process of STA0. 
 *        If it's doesn't allos run this api in DUT operation mode. it will return -2.
 * @param callbackfn   [IN] callback function.
 * @return the result. 0 : Successful, -2 : Failed.
 */
int wifi_connect (void (*callbackfn)(WIFI_RSP*));

/**
 * @brief Disconnect with the current AP. 
 * @return none.
 */
void wifi_disconnect_2(u8 staid, void (*callbackfn)(WIFI_RSP*));

/**
 * @brief Disconnect with the current AP. 
 *        In TWOSTA mode, it's only can terminate connection process of STA0. 
 * @return none.
 */
void wifi_disconnect (void (*callbackfn)(WIFI_RSP*));

/**
 * @brief Configures the wifi settings. 
 * @param pssid		   [IN] AP's SSID.
 * @param ssidlen	   [IN] Length of SSID.
 * @param pkey         [IN] AP's Passphrase. It can be NULL if AP dosen't need passphrase.
 * @param keylen       [IN] Length of passphrase.
 * @param pmac     	   [IN] AP's mac address. It only need to be filled when there are several AP with the same SSID.
                                          STA will connect to specific AP when input mac address. If input NULL, STA will  
                                          connect to the AP with the strongest signal.
 * @param maclen       [IN] Length of mac address.
 * @param sectype      [IN] The encryption method. 0 : NONO. 1 : WEP. 2 : TKIP. 3 : CCMP.
                                                   4 : TKIP or CCMP. 5 : Allow all encryption method.
 * @return the result. 0 : Successful, -1 : Failed.
 */
int set_wifi_config_3(u8 staid, u8 *pssid, u8 ssidlen, u8 *pkey, u8 keylen, u8 *pmac, u8 maclen, u8 sectype);
int set_wifi_config_2(u8 *pssid, u8 ssidlen, u8 *pkey, u8 keylen, u8 *pmac, u8 maclen, u8 sectype);

/**
 * @brief Configures the wifi settings and allow all encryption method. 
 * @param pssid		   [IN] AP's SSID.
 * @param ssidlen	   [IN] Length of SSID.
 * @param pkey         [IN] AP's Passphrase. It can be NULL if AP dosen't need passphrase.
 * @param keylen       [IN] Length of passphrase.
 * @param pmac     	   [IN] AP's mac address. It only need to be filled when there are several AP with the same SSID.
                                          STA will connect to specific AP when input mac address. If input NULL, STA will  
                                          connect to the AP with the strongest signal.
 * @param maclen       [IN] Length of mac address.
 * @return the result. 0 : Successful, -1 : Failed.
 */
int set_wifi_config(u8 *pssid, u8 ssidlen, u8 *pkey, u8 keylen, u8 *pmac, u8 maclen);

/**
 * @brief Get the configuration of  the wifi settings. 
 * @param pssid		   [OUT] AP's SSID.
 * @param ssidlen	   [INOUT] IN : The length of pssid. OUT : Length of SSID.
 * @param pkey         [OUT] AP's Passphrase.
 * @param pkeylen      [INOUT] IN : The length of pkey. OUT : Length of passphrase.
 * @param pmac     	   [OUT] AP's mac address.
 * @param maclen       [INOUT] IN : The length of pMac. OUT : Length of mac address.
 * @return the result. 0 : Successful, -1 : Failed.
 */
int get_wifi_config_2(u8 staid, u8 *pssid, u8 *pssidlen, u8 *pkey, u8 *pkeylen, u8 *pMac, u8 maclen);
int get_wifi_config(u8 *pssid, u8 *pssidlen, u8 *pkey, u8 *pkeylen, u8 *pMac, u8 maclen);

/**
 * @brief Setting tx data rate. 
 * @param rate     	   [IN] The index of rate table. If the value is out of rate table, rate control task will restart.
 * @return none.
 */
//void set_data_rate(u8 rate);

/**
 * @brief Get the amount of AP list. 
 * @return The amount of AP list.
 */
u8 get_ap_lsit_total_num(void);

/**
 * @brief Get the AP information. 
 * @param plist		[OUT] A pointer to a buffer that receives AP information.
 * @param avaliable	[INOUT] IN : The avalible element of plist.
                            OUT : The number of element received.
 * @return the result. 0 : Successful, -1 : Failed.
 */
int get_ap_list(TAG_AP_INFO *plist, u8 *avaliable);

/**
 * @brief get the AP information with maximum rssi.  
 * @param ssid		[IN] you can assign a specific ssid or not. 
 * @param pAPInfo   [OUT] the AP's information with max rssie
 * @return the result. 0 : Successful, -1 : Failed.
 */
int get_the_max_rssi_ap(char *ssid,TAG_AP_INFO *pAPInfo);

/**
 * @brief get station reconnect state.  
 * @param staid	[IN] interface id. 
 * @return the result. -1 : Failed. 0 : reconnect disable,  1 : reconnect enable.
 */
int wifi_station_get_reconnect_state(u8 staid);

/**
 * @brief Get the configuration of network interfaces. 
 * @param pdhcpen	     [OUT] DHCP functionally. 0 : disable DHCP, 1 : enable DHCP.
 * @param pipaddr		 [OUT] The IP address of this host.
 * @param psubmask       [OUT] The IP network mask for this interface.
 * @param pgateway	     [OUT] The default router's IP address.
 * @param pdnsserver	 [OUT] The DNS server IP address.
 * @return the result.   0 : Successful, -1 : Failed.
 */
int get_if_config_2(char *netifname, u8 *pdhcpen, u32 *pipaddr, u32 *psubmask, u32 *pgateway, u32 *pdnsserver, u8 *pmac, u8 len);
int get_if_config(u8 *pdhcpen, u32 *pipaddr, u32 *psubmask, u32 *pgateway, u32 *pdnsserver);

int set_if_config_2(u8 staid, u8 dhcpen, u32 ipaddr, u32 submask, u32 gateway, u32 dnsserver);
int set_if_config(u8 dhcpen, u32 ipaddr, u32 submask, u32 gateway, u32 dnsserver);

/**
 * @brief Get the wifi status. 
 * @return 0 : Disconnected. 1 : Connected. -1 : Failed
 */
int get_wifi_status_2(u8 staid);

/**
 * @brief Get the wifi status. 
 * @return 0 : Disconnected. 1 : Connected.
 */
u8 get_wifi_status(void);

/*
 * @param mode		[IN] 0 : STA, 1 : AP.
 * bit[0]=1M
 * bit[1]=2M
 * bit[2]=5.5M
 * bit[3]=11M
 * bit[4]=MCSO or 6M
 * bit[5]=MCS1 or 9M
 * bit[6]=MCS2 or 12M
 * bit[7]=MCS3 or 18M
 * bit[8]=MCS4 or 24M
 * bit[9]=MCS5 or 34M
 * bit[10]=MCS6 or 48M
 * bit[11]=MCS7 or 54M
 * If HT, rc_mask=0x2B1, it means that DUT only tx packets by MCS5, MCS3, MCS1, MCS0 and 1M
 * If Legacy, rc_mask=0x2B1, it means that DUT only tx packets by 34M, 18M, 9M, 6M and 1M
 * This function should be called before connect to AP or STA connect to SoftAP
 */
int wifi_set_rate_mask_2(u8 mode, u16 rc_mask);
int wifi_set_rate_mask(u16 rc_mask);

/**
 * @brief get the rate mask of DUT.  
 * @param mode		[IN] 0 : STA, 1 : AP.
 * @param mask      [OUT] rate mask.
 * @return the result. 0 : Successful, -1 : Failed.
 */
int wifi_get_rate_mask(u8 mode, u16 *mask);

/*
 * @In AP mode, user can get the STA index by MAC
 * @mac. input parameter
 * @return -1: fail.
*/
int wifi_softap_get_sta_idx_by_mac(u8 *mac);

/**
 * @brief register the callback function and it will be execute when STA connect or disconnect to softap.
 * @param callbackfn   [IN] callback function.
 * @return the result. 0 : Successful, -1 : Failed(Only can operation when softap is not working).
 */
int wifi_register_softap_cb(void (*callbackfn)(STAINFO*));

int get_connectap_info(u8 staid, u8 *pssid, u8 *pssidlen, u8 *pmac, u8 maclen, u8 *prssi, u8 *pch);
/**
 * @brief Configures the settings of sniffer mode. 
 * @param index	         [IN] set which kind of frame would like to receive.
 * @param sniffercb		 [IN] When receive the expect frame, it will call the callback function and offer the detail frame information.
                              The first parameter is pointer of the frame. The second parameter is the length of the frame.
 * @return none.
 */
void set_sniffer_config(SNIFFER_RECVINDEX index, void (*sniffercb)(packetinfo *));

/**
 * @brief Configures the settings of sniffer mode. 
 * @param index	         [IN] set which kind of frame would like to receive.
 * @param sniffercb		 [IN] When receive the expect frame, it will call the callback function and offer the detail frame information.
                              The first parameter is pointer of the frame. The second parameter is the length of the frame.
 * @param min_len        [IN] set the filter condiction. If the lenght of packet is larger than this value, driver will free this packet.                 
 * @param max_len        [IN] set the filter condiction. If the lenght of packet is smaller than this value, driver will free this packet.                            
 * @param target_mac     [IN] set the filter condiction. Only keep the packets that are from this mac address
 * @return none.
 */

void set_sniffer_config_2(SNIFFER_RECVINDEX index, void (*sniffercb)(packetinfo *), u32 max_len, u32 min_len, u8 *target_mac);
void clear_rxque_buffer();

/**
 * @brief Enable/Disable power save mode. 
 * @param enable	     [IN] enable/disable power save mode.
 * @param opmode		 [IN] reserved.
 * @return 0:success, -1:fail 
 */
int set_power_mode(u8 enable, u8 opmode);

/**
 * @brief Set user expect dtime period. If the value is not multiple of AP dtime period, 
          It will change to multiple of AP dtime period and the value is bigger and most close to the user expect value.  
 * @param enable	     [IN] enable/disable power save mode.
 * @param enable		 [IN] reserved.
 * @return 0:success, -1:fail 
 */
int set_user_dtim_period(u8 period);
int set_highprio_sta(u8 staid);
int register_wifi_ifname(u8 id, char *ifname);

/**
 * @brief Set local mac address. This API must be executed in or before WIFI_INIT().
 * @param staid	         [IN] interface id.
 * @param pmac  		 [IN] mac address buffer.
 * @param len   		 [IN] size of pmac.
 * @return 0:success, -1:fail 
 */
int set_local_mac(u8 staid, u8 *pmac, u8 len);

/**
 * @brief Get local mac address.  
 * @param staid	         [IN] interface id.
 * @param pmac  		 [OUT] mac address buffer.
 * @param len   		 [IN] size of pmac.
 * @return 0:success, -1:fail 
 */
int get_local_mac(u8 staid, u8 *pmac, u8 len);
u8 get_operation_mode();

/**
 * @brief Configures the channel settings of sniffer mode. 
 * @param ch	    [IN] cannel number. 
 *                  1,2,3,4,5,6,7,8,9,10,11,12,13 on 2.4G Band. 
 *                  36,40,44,48,52,56,60,64,100,104,108,112,116,120,124,128,132,136,140,144,149,153,157,161,and 165 on 5G Band
 * @param type      [IN] channel type
 *                  0: None HT
 *                  1: HT20
 *                  2: HT40 minus
 *                  3. HT40 plus
 * @return 0:success, -1:fail
 */
int wifi_set_channel(u32 ch, u32 type);
int set_country_code(COUNTRY_CODE code);


int wifi_debug_enable(bool en);
int wifi_register_mac_send_cb(void (*mac_send_debug_cb)(void *data));
int wifi_unregister_mac_send_cb(void (*mac_send_debug_cb)(void *data));
int wifi_register_radio_send_cb(void (*radio_send_debug_cb)(void *data));
int wifi_unregister_radio_send_cb(void (*radio_send_debug_cb)(void *data));

void wifi_ap_timperiod(u8 timperiod);

/**
 * @brief Enable/Disable softap hidden ssid.
 * @param staid	         [IN] 1 : enable. 0 : disable.
 * @return 0 : ok -1 : fail
 */
 int wifi_ap_set_hidden_ssid(u8 enable);

/**
 * @Config the AP attribute. The default secure type is WPA2 if the key_len is not zero
 * @If the ssid=NULL and ssid_len=0, it means use the default ssid
 * @If the key=NULL and key_len=0, it means that the secure type is open
 * @If the key!=NULL and key_len=!0, it means use the customer's password, and secure type is always WPA2
 * @return 0 : ok -1 : fail
 */
int wifi_ap_easy_conf(char *ssid, u32 ssid_len, char *key, u32 key_len, u8 channel);

/**
 * @brief Get the mac and ip address of connected STAs.
 * @param info		   [OUT] The array storage mac and ip address of connected STAs.
 * @param number	   [INOUT] IN : The amount of array - info. 
                               OUT : the avaiable number of sta information.
 * @return the result. 0 : Successful, -1 : Failed.
 */
int get_connectsta_info(CONNSTAINFO *info, u8 *number);

/**
 * @brief Disconnect the STA which is connected to softap.
 * @param mac		   [IN] mac address of the STA.
 * @return the result. 0 : Successful, -1 : Failed.
 */
int wifi_softap_disconnect_sta(u8 *mac);

/**
 * @Config the repeater's AP attribute. 
 * @If conf_mode=REPT_CONF_AUTO, wifi_repetater_easy_conf(REPT_CONF_AUTO,NULL,0,NULL,0)
    Repeater's SSID and Secure type is depend on Home AP. If the SSID of Home AP is ABCDE, the SSID of repeater is ABCDE-RA
    If the Home AP's OPEN, the repeater is OPEN
    If the Home AP's WEP, the repeater is WEP
    If the Home AP's WPA/WPA2, the repeater is WPA2  
 * @If conf_mode=REPT_CONF_DEFAULT, wifi_repetater_easy_conf(REPT_CONF_DEFAULT,NULL,0,NULL,0). 
    The secure type is always OPEN, ssid is always iComm1234567890
 * @If conf_mode=REPT_CONF_CUSTOM, wifi_repetater_easy_conf(REPT_CONF_CUSTOM,ssid,len,key,key_len).
    If the key=NULL and key_len=0, it means that the secure type is open
    If the key!=NULL and key_len=!0, it means use the customer's password, and secure type is always WPA2    
 * @return 0 : ok -1 : fail
 */
int wifi_repetater_easy_conf(REPEATER_CONF_MODE conf_mode, char *ssid, u32 ssid_len, char *key, u32 key_len);

/**
 *@Configure the amout of ap list. This setting will be apply when start STA mode after execute API.
 *@amount: input parameter
 *@return 0: success, -1:fail 
*/
int wifi_set_ap_list_amount(u32 amount);

/**
 * @brief Enable/disable transmit deauthentication frame before connection process.
 * @param enable	     [IN] 1 : enable, 0 disable.
 * @return none.
 */
void wifi_set_connect_tx_deauth(u8 en);

/**
 *@Configure L2 keep alive behavior. This setting will be apply when start STA mode after execute API.
 *@param keepalive_en	 [IN] 1 : enable L2 keep alive. 0 : disable L2 keep alive.
 *@param prriod_sec		 [IN] The period of L2 keep alive.
 *@return 0: success, -1:fail 
*/
int wifi_set_sta_l2keepalive(u8 id, u8 keepalive_en, u16 prriod_sec);

/**
 *@ send null data to AP, this function only works when a STA interface is working
 *@ pwmode=0: STA is active, pwmode=1: STA is in sleeping.
 *@ id: interface id, id=0, it means IF0, id=1, it means IF1
    id=0 or 1, if DUT works on DUT_TWOSTA
    id=0, if DUT works on DUT_STA, DUT_CONCURRENT    
*/
int wifi_send_null_data(int pwmode, u8 id);

/**
     use external pa. This function should be excuted before creating ssvradio_init_task
 */
int wifi_use_ext_pa(bool en);

/**
    setup the extra setting for external pa. This function should be excuted after DUT_wifi_start

    const ssv_reg customer_extra_table[]={
        //addrr      value
        {0xCCB0A424, 0x57444427},
        {0xCCB0A400, 0x39000300},
    };

    wifi_set_ext_pa(customer_extra_table, sizeof(customer_extra_table)/sizeof(ssv_reg));
};    
 */
int wifi_set_ext_pa(ssv_reg *reg_tbl,u32 size);

/**
 *@ send icmp with fix 1M or use auto rate
 *@ en=0, auto rate (default)
 *@ en=1, fix 1M   
*/
int wifi_set_icmp_1m(bool en);

/**
 *@ send low rate with rts/cts
 *@ en=0, without rts/cts (default)
 *@ en=1, with rts/cts
*/
int wifi_set_low_rate_rts_cts(bool en);

/**
 *@brief set fixed rate
 *@param enable_mask    [IN]. Now, only support ENALBE_MASK_ALL
 *@param rate           [IN]
 *@param try_cnt        [IN]. retry counter, 1<=try_cnt<=15
 *@return 0:success, -1:fail
 */
#define USE_FIXED_RATE_ENABLE_MASK_NONE 0
#define USE_FIXED_RATE_ENABLE_MASK_STA 0x01
#define USE_FIXED_RATE_ENABLE_MASK_AP 0x02
#define USE_FIXED_RATE_ENABLE_MASK_ALL 0x03

enum USER_FIXED_RATE{
    USER_FIXED_RATE_B_MODE_1M=0,
    USER_FIXED_RATE_B_MODE_2M=1,
    USER_FIXED_RATE_B_MODE_5P5M=2,
    USER_FIXED_RATE_B_MODE_11M=3,
    USER_FIXED_RATE_G_MODE_6M=7,
    USER_FIXED_RATE_G_MODE_9M=8,
    USER_FIXED_RATE_G_MODE_12M=9,
    USER_FIXED_RATE_G_MODE_18M=10,
    USER_FIXED_RATE_G_MODE_24M=11,
    USER_FIXED_RATE_G_MODE_36M=12,
    USER_FIXED_RATE_G_MODE_48M=13,
    USER_FIXED_RATE_G_MODE_54M=14,
    USER_FIXED_RATE_N_MODE_6P5M=15,
    USER_FIXED_RATE_N_MODE_13M=16,
    USER_FIXED_RATE_N_MODE_19P5M=17,
    USER_FIXED_RATE_N_MODE_26M=18,
    USER_FIXED_RATE_N_MODE_39M=19,
    USER_FIXED_RATE_N_MODE_52M=20,
    USER_FIXED_RATE_N_MODE_58P5M=21,
    USER_FIXED_RATE_N_MODE_65M=22
};
int wifi_set_user_fixed_rate(u8 enable_mask, u8 rate, u8 try_cnt);

/**
 *@brief set fixed rate
 *@param enable_mask    [OUT]
 *@param rate           [OUT]
 *@param try_cnt        [OUT]
 *@return 0:success, -1:fail
 */
int wifi_get_user_fixed_rate(u8 *enable_mask, u8 *rate, u8 *try_cnt);
/**
 *@brief send the 802.11 raw packets from APP
 *@param data           [IN]
 *@param len            [IN]
 *@param user_cb        [IN] Inform the users that this packet is tx done. This call back function has two parameters, first one is to tell user if tx down or not. The second one is user's private information. 
 *@param user_dat       [IN] user's private data
 *@param sys_seq        [IN] This parameter is just reserved now.
 *@return 0:success, -1:fail
 */

int wifi_send_packet_freedom(u8 *data, int len, user_tx_cb user_cb, u32 user_dat, bool sys_seq);

/**
 * @brief Create management prob frame for the vendor specific data.
 * == Prob Request Frame Format ==
 * ----------------------------------------------
 * | MAC Header | Vendor Specific Content | FCS |
 * ----------------------------------------------
 *    24 bytes           5~255 bytes
 * -> Vendor Specific Content
 * --------------------------------------------------------------
 * | Element ID | Length | Organization Identifier |    Body    |
 * --------------------------------------------------------------
 *     1 byte     1 byte            3 bytes          0~252 bytes
 * @param pu8PeerMAC      [IN] Peer MAC address. (6 bytes)
 * @param pu8OUI          [IN] The OUI value. (3 bytes)
 * @param pu8Data         [IN] The vendor specific data.
 * @param u32DataLen      [IN] The length of the vendor specific data.
 * @param *u32RealPktLen  [OUT] The length of the real packet length
 * @return the output frame memory address.
 */
u8* wifi_mgm_prob_create(u8 *pu8PeerMAC, u8 *pu8OUI, u8 *pu8Data, u32 u32DataLen, u32 *u32RealPktLen);

/**
 * @brief Create management prob frame for the vendor specific data.
 * @param pstParam        [IN] Pointer to parameters.
 * @param *u32RealPktLen  [OUT] The length of the real packet length
 * @return the output frame memory address.
 */
u8* wifi_mgm_prob_create_ex(ST_WIFI_API_SSV_NOW_PARAM *pstParam, u32 *u32RealPktLen);

/**
 * @brief Release the allocated management prob frame memory.
 * @param pu8Data         [IN] Memory address.
 * @return the result.   0 : Successful, -1 : Failed.
 */
int wifi_mgm_prob_release(u8 *pu8Data);

/**
 * @brief Create management action frame for the vendor specific data.
 * == Action Frame Format ==
 * ----------------------------------------------------------------------------------------
 * | MAC Header | Category Code | Organization Identifier | Vendor Specific Content | FCS |
 * ----------------------------------------------------------------------------------------
 *    24 bytes        1 byte              3 bytes                  5~255 bytes
 * -> Vendor Specific Content
 * --------------------------------------------------------------
 * | Element ID | Length | Organization Identifier |    Body    |
 * --------------------------------------------------------------
 *     1 byte     1 byte            3 bytes          0~252 bytes
 * @param pu8PeerMAC      [IN] Peer MAC address. (6 bytes)
 * @param pu8OUI          [IN] The OUI value. (3 bytes)
 * @param pu8Data         [IN] The vendor specific data.
 * @param u32DataLen      [IN] The length of the vendor specific data.
 * @param *u32RealPktLen  [OUT] The length of the real packet length
 * @return the output frame memory address.
 */
u8* wifi_mgm_action_create(u8 *pu8PeerMAC, u8 *pu8OUI, u8 *pu8Data, u32 u32DataLen, u32 *u32RealPktLen);

/**
 * @brief Create management action frame of the specific BSSID for the vendor specific data.
 * @param pstParam        [IN] Pointer to parameters.
 * @param *u32RealPktLen  [OUT] The length of the real packet length
 * @return the output frame memory address.
 */
u8* wifi_mgm_action_create_ex(ST_WIFI_API_SSV_NOW_PARAM *pstParam, u32 *u32RealPktLen);

/**
 * @brief Release the allocated management action frame memory.
 * @param pu8Data         [IN] Memory address.
 * @return the result.   0 : Successful, -1 : Failed.
 */
int wifi_mgm_action_release(u8 *pu8Data);

/**
 * @brief Create data frame for the vendor specific data.
 *        Before call this function, make sure the fixed rate has been set.
 *        Otherwise, please call wifi_set_user_fixed_rate() first.
 * == Frame Format ==
 * ----------------------------------------------
 * | MAC Header | Vendor Specific Content | FCS |
 * ----------------------------------------------
 *    24 bytes           0~7951 bytes
 * @param pu8PeerMAC      [IN] Peer MAC address. (6 bytes)
 * @param pu8Data         [IN] The vendor specific data. (0~7951 bytes)
 * @param u32DataLen      [IN] The length of the vendor specific data.
 * @return the output frame memory address.
 */
u8* wifi_data_create(u8 *pu8PeerMAC, u8 *pu8Data, u32 u32DataLen);

/**
 * @brief Create data frame of the specific BSSID for the vendor specific data.
 *        Before call this function, make sure the fixed rate has been set.
 *        Otherwise, please call wifi_set_user_fixed_rate() first.
 * @param pstParam        [IN] Pointer to parameters.
 * @return the output frame memory address.
 */
u8* wifi_data_create_ex(ST_WIFI_API_SSV_NOW_PARAM *pstParam);

/**
 * @brief Release the allocated data frame memory.
 * @param pu8Data         [IN] Memory address.
 * @return the result.   0 : Successful, -1 : Failed.
 */
int wifi_data_release(u8 *pu8Data);

/**
 * @brief Get current WiFi running channel.
 * @return the current channel.
 */
u8 wifi_get_current_channel(void);

/**
 * @brief watch mgmt frame on STA mode. 
 *  The APP should not modify the content of frame. If APP needs to modify it, APP should allocat a memory and backup it.
 * @param mgmtcbfn [IN] 
 */
void wifi_mgmt_watch_cbfn(void (*mgmtcbfn)(packetinfo *));

typedef enum _en_wifi_mod_cfg
{
    E_WIFI_MOD_CFG_TYPE_NONE = 0,
    E_WIFI_MOD_CFG_TYPE_TXQ_WAIT_NUM = 0x1000,
    E_WIFI_MOD_CFG_TYPE_TXQ_WAIT_TIME,
    E_WIFI_MOD_CFG_TYPE_AMPDU_TX_CHKTIME = 0x2000,
    E_WIFI_MOD_CFG_TYPE_MAX = 0xFFFFFFFF
}EN_WIFI_MOD_CFG_TYPE;

/**
 * @brief Set module config.
 * @param eType           [IN] Config type.
 * @param u32Val          [IN] Config value.
 * @return the result.    0 : Successful, -1 : Failed.
 */
int wifi_set_module_config(EN_WIFI_MOD_CFG_TYPE eType, u32 u32Val);

/**
 * @brief The user IE will be appended to the end of target packets of user_ie_type. 
 * @param enable    [IN] 1 : enable, 0 : disable. 
 * @param type      [IN] user_ie_type
 * @param user_ie   [IN] user defined information elements
 * @param len       [IN] length of user IE.
 * @return 0:success, -1:fail
 */
int wifi_set_user_ies (bool enable, user_ie_type type, u8 *user_ie, u8 len);

/**
 * @brief Register wifi event handler. 
 * @param callbackfn [IN] callback function. 
 * @return NULL
 */
void wifi_set_event_handler_cb(void (*callbackfn)(wifi_event_t *));

int wifi_register_user_ie_manufacturer_recv_cb (void *cb);
void wifi_unregister_user_ie_manufacturer_recv_cb (void);

/**
 * @brief Set lease time of dhcp server. 
 * @param time      [IN] lease time. 
 * @return 0:success, -1:fail
 */
int softap_set_lease_time(u32 time);

/**
 * @brief Get lease time of dhcp server.
 * @return lease time
 */
u32 softap_get_lease_time(void);

/**
 * @brief Enable/disable dhcp server.
 * @param enable    [IN] 1 : enable, 0 : disable.
 * @return 0:success, -1:fail
 */
int softap_set_dhcp_enable(u8 enable);

/**
 * @brief Enable/disable dhcp server.
 * @return enum dhcp_status
 */
int softap_get_dhcp_status(void);


/**
 * @brief Enable/disable dhcp router option.
 * @param enable    [IN] 1 : enable, 0 : disable.
 * @return 0:success, -1:fail
 */
int softap_set_dhcp_offer_option(u8 en);

/**
 * @brief set the support rate in IE.
 * @param min       [IN] minimum value of data rate.
 * @param max       [IN] maximum value of data rate.
 * @return 0:success, -1:fail
 */
int wifi_set_user_sup_rate (RATE_BG_TYPE min, RATE_BG_TYPE max);

/**
 * @brief Set softap phy mode setting.
 * @param phymode   [IN] physical mode. If want to enable B/G/N mode, please input  (PHY_11B | PHY_11G | PHY_11N)
 * @return 0:success, -1:fail
 */
int wifi_softap_set_phy_mode (u8 phymode);

/**
 * @brief Get softap phy mode setting.
 * @return phy mode setting(enum PHY_MODE).
 */
u8 wifi_softap_get_phy_mode ();

/**
 * @brief Get station connection status.
 * @param staid     [IN] interface id.
 * @return -1:fail, Others : enum STATION_STATUS
 */
int Get_connection_status(u8 staid);

#ifdef SUPPORT_WIFI_POSITIONING
int scan_AP_positioning(SCAN_PARAM *argv);
#endif

/**
 * @Set csi b mode configuration and enable function
 * @param addr1     [IN] mac80211 header address1
 * @param addr2     [IN] mac80211 header address2
 * @param addr3     [IN] mac80211 header address3
 * @param fc        [IN] mac80211 header frame control
 * @param fc_mask   [IN] mac80211 header frame control mask
 * @return -1:fail, 0:success
 */
int wifi_set_csi_config_b(u8 *addr1, u8 *addr2, u8 *addr3, u16 fc, u16 fc_mask);

/**
 * @Enable/Disable csi b mode function
 */
void wifi_enable_csi_b(bool en);

/**
 * @Set csi g/n mode configuration and enable function
 * @param addr1     [IN] mac80211 header address1
 * @param addr2     [IN] mac80211 header address2
 * @param addr3     [IN] mac80211 header address3
 * @param fc        [IN] mac80211 header frame control
 * @param fc_mask   [IN] mac80211 header frame control mask
 * @return -1:fail, 0:success
 */
int wifi_set_csi_config_gn(u8 *addr1, u8 *addr2, u8 *addr3, u16 fc, u16 fc_mask);

/**
 * @Enable/Disable csi g/n mode function
 */
void wifi_enable_csi_gn(bool en);

/**
 * @Unregister csi interrupt service routine
 */
void wifi_ungister_csi_isr(void);

/**
 * @Register csi interrupt service routine
 * @param isrfn     [IN] interrupt service routine
 * @param csi_result   [IN] csi result
 */
void wifi_register_csi_isr(void (*isrfn)(void *), void *csi_result);

/**
 * @Enable/Disable csi interrupt handler 
 */
void wifi_csi_irq_enable(bool val); 

void wifi_set_24G_ht40_enable(u8 enable);
void wifi_register_custom_cmd_queue(OsBufQ *que);
int wifi_send_custom_soc_event(u8 *evt, u16 evtlen);
int ble_en(bool en);

/**
 * @brief   Allow SDIO/SPI reset
 * @param   en              [IN] Enable/Disable
 * @return  None.
 */
void wifi_allow_sdio_spi_reset(bool en);

/**
 * @brief   Enable/Disable AMPDU RX.
 * @param   en              [IN] Enable/Disable
 * @return  None.
 */
void wifi_ampdu_rx_enable(bool en);

#endif /* __WIFI_API_H__ */
