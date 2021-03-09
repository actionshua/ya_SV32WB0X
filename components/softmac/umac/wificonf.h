#ifndef __SYSTEMCONF_H__
#define __SYSTEMCONF_H__

#include "soc_types.h"
#include "osal.h"
#include "wpa.h"

#include "mac_common.h"
#include "ieee80211.h"
#include <rc/minstrel/core/rc_def.h>
#include <rc/rc.h>

#define MAX_APRECORD 	1
#define DEFAULT_AP_LIST_AMOUNT		(50)
#define MAX_CONN_RTYCNT	10
#define CFG_SOFTAP_SSID_LENGTH (32)
#define IF0_NAME       "et0"
#define IF1_NAME       "et1"

typedef enum {
    EN_DRATE_IDX_BMODE_LONG_10M = 0,       //LONG PREAMBLE, 1M
    EN_DRATE_IDX_BMODE_LONG_20M = 1,       //LONG PREAMBLE, 2M
    EN_DRATE_IDX_BMODE_LONG_55M = 2,       //LONG PREAMBLE, 5.5M 
    EN_DRATE_IDX_BMODE_LONG_110M= 3,       //LONG PREAMBLE, 11M
    EN_DRATE_IDX_BMODE_SHORT_20M= 4,       //SHORT PREAMBLE, 2M
    EN_DRATE_IDX_BMODE_SHORT_55M= 5,       //SHORT PREAMBLE, 5.5M	
    EN_DRATE_IDX_BMODE_SHORT_110M=6,       //SHORT PREAMBLE, 11M			
	
    EN_DRATE_IDX_GMODE_60M=7,              //6M		
    EN_DRATE_IDX_GMODE_90M=8, 		       //9M,	
    EN_DRATE_IDX_GMODE_120M=9,             //12M		
    EN_DRATE_IDX_GMODE_180M=10,            //18M			
    EN_DRATE_IDX_GMODE_240M=11,            //24M		
    EN_DRATE_IDX_GMODE_360M=12,            //36M			
    EN_DRATE_IDX_GMODE_480M=13,	           //48M	
    EN_DRATE_IDX_GMODE_540M=14,            //54M
    
    EN_DRATE_IDX_NMODE_LONG_GI_65=15,		//6.5M
    EN_DRATE_IDX_NMODE_LONG_GI_130=16,	    //13M		
    EN_DRATE_IDX_NMODE_LONG_GI_195=17,		//19.5M
    EN_DRATE_IDX_NMODE_LONG_GI_260=18,		//26M	
    EN_DRATE_IDX_NMODE_LONG_GI_390=19,		//39M
    EN_DRATE_IDX_NMODE_LONG_GI_520=20,		//52M	
    EN_DRATE_IDX_NMODE_LONG_GI_585=21,		//58.5M
    EN_DRATE_IDX_NMODE_LONG_GI_650=22,     //65M
		
    EN_DRATE_IDX_INVALID=0xFF,	
	
} EN_DATA_RATE_IDX;

typedef enum {
    
    //Repeater's SSID and Secure type is depend on Home AP. If the SSID of Home AP is ABCDE, the SSID of repeater is ABCDE-RA
    //If the Home AP's OPEN, the repeater is OPEN
    //If the Home AP's WEP, the repeater is WEP
    //If the Home AP's WPA/WPA2, the repeater is WPA2   
    REPT_CONF_AUTO=0, 

    //The default value of SSID is LAPSSID //#define LAPSSID "icomm1234567890"
    //The default secure type is WPA2, the password is LAPPASSPHRASE //#define LAPPASSPHRASE "1234567890"
    REPT_CONF_DEFAULT,

    //Depend on customer's configuration
    REPT_CONF_CUSTOM,        
} REPEATER_CONF_MODE;

typedef enum {
    WIFI_DISCONNECTION = 0,
    WIFI_CONNECTION,
} ieee80211_action;

typedef enum {
    IEEE80211_DISCONNECTED = 0,
    IEEE80211_PROBING_REQ,
    IEEE80211_AUTHENTICATING_SEQ1_PREPARE,
    IEEE80211_AUTHENTICATING_SEQ3_PREPARE,
    IEEE80211_AUTHENTICATING_SEQ1,
    IEEE80211_AUTHENTICATING_SEQ3,
    IEEE80211_ASSOCIATING_REQ,
    IEEE80211_REASSOCIATING_REQ,
    IEEE80211_EAPOL_HANDSHAKE1,
    IEEE80211_EAPOL_HANDSHAKE2,
    IEEE80211_EAPOL_HANDSHAKE3,
    IEEE80211_EAPOL_HANDSHAKE4,
    IEEE80211_GETIP,
    IEEE80211_CONNECTED,
    IEEE80211_DISASSOCIATING_SAQUERY,
    IEEE80211_ACTIVEPROBE,
    IEEE80211_ACTIVEPROBE_FOUND,
    IEEE80211_ACTIVETRANSITION,
    IEEE80211_WAITSCANDONE_RECONN,
    IEEE80211_WPS_REGISTRATION,
    IEEE80211_WPS_FINISH,
} ieee80211_state;

#define IEEE80211_UNAUTHENTICATED   ((0x0) << 0)
#define IEEE80211_AUTHENTICATED     ((0x1) << 0)

#define IEEE80211_UNASSOCIATED      ((0x0) << 1)
#define IEEE80211_ASSOCIATED        ((0x1) << 1)

#define IEEE80211_UN_RSN_PROTECT    ((0x0) << 2)
#define IEEE80211_RSN_PROTECT       ((0x1) << 3)

enum MLME_STATE {
    MLME_FSM_STATE_INIT         = (IEEE80211_UNAUTHENTICATED | IEEE80211_UNASSOCIATED | IEEE80211_UN_RSN_PROTECT),
    MLME_FSM_STATE_AUTH         = (IEEE80211_AUTHENTICATED | IEEE80211_UNASSOCIATED | IEEE80211_UN_RSN_PROTECT),        
    MLME_FSM_STATE_NON_PROTECT  = (IEEE80211_AUTHENTICATED | IEEE80211_ASSOCIATED | IEEE80211_UN_RSN_PROTECT),
    MLME_FSM_STATE_CONNECTED    = (IEEE80211_AUTHENTICATED | IEEE80211_ASSOCIATED | IEEE80211_RSN_PROTECT),
};

enum{
    STA_GO_DISCONNECT,
    STA_TRY_RECONNECT,
};

typedef enum {
    MGMT_CONN_PASSIVE = 0,
    MGMT_CONN_ACTIVE,
    MGMT_CONN_INIT,
    MGMT_GETIP,
    MGMT_CONNECTED,
    MGMT_DISCONNECTED,
    MGMT_RESETTIMER,
    MGMT_RECONNECT,
    MGMT_DELTASK,
} MGMT_ACTION;

typedef enum {
    DIS_TIMEOUT = 0,
    DIS_DEAUTH,
    DIS_DISASSOC,
    DIS_ASSOCERR,
    DIS_SELFDIS,
} DISCONN_TYPE;

/* 802.11 authentication and  association Status code, refer to the following URL
https://supportforums.cisco.com/document/141136/80211-association-status-80211-deauth-reason-codes*/
typedef enum {
	IEEE80211_RSP_SUCCESS = 0,
	IEEE80211_RSP_FAILURE = 1,
	IEEE80211_RSP_CAPAB_UNSUPP = 10,
	IEEE80211_RSP_REASSOC_INVALID = 11,
	IEEE80211_RSP_ASSOC_DENIED = 12,
	IEEE80211_RSP_AUTH_ALGO_UNSUPP = 13,
	IEEE80211_RSP_AUTH_SEQ_INVALID = 14,
	IEEE80211_RSP_AUTH_CHALL_INVALID = 15,
	IEEE80211_RSP_AUTH_TIMEOUT = 16,
	IEEE80211_RSP_ASSOC_NO_ROOM = 17,
	IEEE80211_RSP_ASSOC_NEED_RATE = 18,
	IEEE80211_RSP_ASSOC_NEED_SHORT_PMBL = 19,
	IEEE80211_RSP_ASSOC_NEED_PBCC = 20,
	IEEE80211_RSP_ASSOC_NEED_CHAN_AGILITY = 21,
	IEEE80211_RSP_ASSOC_NEED_SPECTRUM_MGMT = 22,
	IEEE80211_RSP_ASSOC_BAD_POWER = 23,
	IEEE80211_RSP_ASSOC_BAD_CHANNELS = 24,
	IEEE80211_RSP_ASSOC_NEED_SHORT_SLOT = 25,
	IEEE80211_RSP_ASSOC_NEED_DSSS_OFDM = 26,
	IEEE80211_RSP_QOS_FAILURE = 32,
	IEEE80211_RSP_QOS_NO_ROOM = 33,
	IEEE80211_RSP_LINK_IS_HORRIBLE = 34,
	IEEE80211_RSP_ASSOC_NEED_QOS = 35,
	IEEE80211_RSP_REQUEST_DECLINED = 37,
	IEEE80211_RSP_REQUEST_INVALID = 38,
	IEEE80211_RSP_TS_NOT_CREATED_AGAIN = 39,
	IEEE80211_RSP_INVALID_IE = 40,
	IEEE80211_RSP_GROUP_CIPHER_INVALID = 41,
	IEEE80211_RSP_PAIR_CIPHER_INVALID  = 42,
	IEEE80211_RSP_AKMP_INVALID = 43,
	IEEE80211_RSP_RSN_VERSION_UNSUPP = 44,
	IEEE80211_RSP_RSN_CAPAB_INVALID = 45,
	IEEE80211_RSP_CIPHER_REJECTED = 46,
	IEEE80211_RSP_TS_NOT_CREATED_WAIT = 47,
	IEEE80211_RSP_DIRECT_LINK_FORBIDDEN = 48,
	IEEE80211_RSP_DEST_NOT_PRESENT = 49,
	IEEE80211_RSP_DEST_NOT_QOS = 50,
	IEEE80211_RSP_ASSOC_LISTEN_TOO_HIGH = 51,
} ieee80211_rsp_state;

typedef enum _MP_ID
{
    MP_MAC_ADDR=0,
    MP_RF_TABLE,
    MP_HT_TABLE,
    MP_LT_TABLE,
    MP_TEMP_BOUNDARY,
    MP_SERIAL_NO,
    MP_NUM_MAX
} MP_ID;

typedef enum user_ie_type {
    USER_IE_BEACON = 0, 
    USER_IE_PROBE_REQ, 
    USER_IE_PROBE_RESP, 
    USER_IE_ASSOC_REQ,
    USER_IE_ASSOC_RESP, 
    USER_IE_MAX,
}user_ie_type;

typedef struct t_WIFI_STATUS
{
	ieee80211_state status;
	DISCONN_TYPE	type;
	u16		        reasoncode;
} WIFI_STATUS;

typedef struct t_TAG_AP_INFO
{
	u8 		name[32];
	u8		name_len;
	u8 		mac[6];
	u8		channel;
	u8		security_type;
	u8		security_subType;
	u8		rssi;
} TAG_AP_INFO;
extern TAG_AP_INFO *ap_list;


typedef enum t_TAG_SECURITY
{
	NONE = 0,
	WEP,
	WPA,
	WPA2,
	WPAWPA2,
    WPA3,
} TAG_SECURITY;

typedef enum t_TAG_SECURITY_TYPE
{
	NOSECTYPE = 0,
	TKIP,
	CCMP,
	TKIP_CCMP,
} TAG_SECURITY_TYPE;

typedef union uip_ip4addr_t {
  u8  u8[4];			
  u16 u16[2];
  u32 u32;
} uip_ip4addr_t;

typedef enum 
{
	STA_CONN = 0,
	STA_DISCONN,
} STA_STATE;

typedef struct packetinfo {
  u8 channel;
  u8  *data;			
  u16 len;
  s16 rssi;
  u32 ht_signal_23_0;
  u32 ht_signal_47_24;
} packetinfo;

typedef struct stainfo {
  STA_STATE  stastatus;           
  u8  mac[6];			
} STAINFO;

typedef struct t_IP_CONFIGURATION
{
	uip_ip4addr_t	local_ip_addr;
	uip_ip4addr_t	net_mask;
	uip_ip4addr_t	gateway_ip_addr;
	uip_ip4addr_t	dns_server;
	u32				dhcp_enable;		// 1: Enable 0: Fix IP
} IP_CONFIGURATION;

enum PHY_MODE
{
	PHY_11B = 0x1,
	PHY_11G = 0x2,
	PHY_11N = 0x4,
} PHY_MODE;

enum dhcp_status 
{
    DHCP_STOPPED, 
    DHCP_STARTED, 
};

enum STATION_STATUS
{
    STATION_IDLE,
    STATION_CONNECTING,
    STATION_WRONG_PASSWORD,
    STATION_NO_AP_FOUND,
    STATION_CONNECT_FAIL,
    STATION_GOT_IP,
}STATION_STATUS;

typedef enum System_Event_t {
    EVENT_STAMODE_SCAN_DONE = 0, 
    EVENT_STAMODE_CONNECTED, 
    EVENT_STAMODE_DISCONNECTED, 
    EVENT_STAMODE_AUTHMODE_CHANGE,
    EVENT_STAMODE_GOT_IP, 
    EVENT_STAMODE_DHCP_TIMEOUT, 
    EVENT_SOFTAPMODE_STACONNECTED, 
    EVENT_SOFTAPMODE_STADISCONNECTED,
    EVENT_SOFTAPMODE_PROBEREQRECVED, 
    EVENT_MAX 
}System_Event_t;

typedef struct wifi_event_t
{
    u8 interfaceid;
    System_Event_t event;
}wifi_event_t;


typedef enum {
   eSOFTAP_STA_ID0=0,      //client 0
   eSOFTAP_STA_ID1,        //client 1
   eSOFTAP_STA_ID2,        //client 2 
   eSOFTAP_STA_ID3,        //client 3 
   eSOFTAP_STA_MAX_ID        //client 1
} eSOFTAP_STA_ID;

typedef struct _STA_INFO    //0:use peermac0,1:use peermac1
{
    s32 idle_timer;
    s32 softap_tx_null_data_idle_time;
    u32 filteraddr;
    u16 sta_seqno;
    u8 ht_support;
    u8 wmm_support;
//    u8 ipaddr[4];
    u8 mac[6];    //only one sta available now!!
    u8 connected;    
    u8 host_ethpkt_offset;
    struct wpa_common_ctx wpa_ap;
} STA_INFO;

typedef enum WIFI_DIS_REASON{
    UNSUPPORT_ENCRYPT = 0,
    WRONG_PASSPHRASE,
    DEAUTHENTICATION,
    DISASSOCIATION,
    AP_MISSING,
    CANNOT_GET_IP,
    DISCONNECT,
    MSG_NONE,
} WIFI_DIS_REASON;

typedef struct _AT_SCAN_CUSTOM_ARGS {
    void (*callbackfn)(void *);
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
    char  ssid[32];
    u8 ssid_len;
    u8 max_apcnt;
    bool online_scan;       ///< Enable/Disable online scan mode.
} AT_SCAN_CUSTOM_ARGS;

typedef struct _WIFI_RSP {
    u8  wifistatus;
    u8  id;
    u16 reason;
    u16 code;
} WIFI_RSP;

typedef enum{
   EN_WPS_SUCCESS=0,
   EN_WPS_WAKE_TIME_TO,
   EN_WPS_PBC_OVERLAP,   
   EN_WPS_FAIL,
}EN_WPS_STATUS;

typedef struct _WIFI_WPS_RSP {
    EN_WPS_STATUS  status;
    u8 ssid[32];
    u8 ssid_len;
    u8 key[64];
    u8 key_len;
} WIFI_WPS_RSP;

typedef struct _STA_CUSTOM_CONFIG {
    u8 IF0_L2keepalive_en;
    u8 IF1_L2keepalive_en;
    u16 IF0_L2keepalive_sec;
    u16 IF1_L2keepalive_sec;
    u16 APlist_amount;
    u8 conn_tx_deauth_en;
}STA_CUSTOM_CONFIG;

typedef enum {
    RECV_BEACON             = 0x1,
    RECV_MGMT               = 0x2,
    RECV_BROADCAST_DATA     = 0x4,
    RECV_DATA               = 0x8,
} SNIFFER_RECVINDEX;

typedef enum {
    DUT_NONE = 0,
    DUT_STA,
    DUT_AP,
    DUT_CONCURRENT,
    DUT_TWOSTA,
    DUT_SNIFFER,
    DUT_REPEATER,
    DUT_TRANSPARENT,
    DUT_MAX,
} WIFI_OPMODE;

typedef enum {
    IF_0 = 0,
    IF_1,
    IF_MAX,
} IF_NUM;

typedef enum {
    DEF=0,
    TW,
    CN,
    HK,
    US,
    JP,
    COUNTRY_MAX,
}COUNTRY_CODE;

typedef enum {
	SCAN_END,
	SCAN_ONGOING,
    SCAN_TERMINATING,
}SCAN_STATE;

/*typedef enum {
    RADIO_BAND_2G=0,
    RADIO_BAND_5100=1,
    RADIO_BAND_5500=2,
    RADIO_BAND_5700=3,
    RADIO_BAND_5900=4,
}RADIO_BAND;  */ 

typedef enum {
    SOFTAP_MGM_ACT_TX_DEAUTH = 0,
    SOFTAP_MGM_ACT_NOTIFY_CONN,	
    SOFTAP_MGM_ACT_NOTIFY_DISCONN,
    SOFTAP_MGM_ACT_EAPOL_INITIAL,
    SOFTAP_MGM_ACT_EAPOL_STEP1,	// tx1_of_4
    SOFTAP_MGM_ACT_EAPOL_STEP3,	// tx3_of_4
    SOFTAP_MGM_ACT_EAPOL_DONE,
    SOFTAP_MGM_ACT_DELETE,
    SOFTAP_MGM_ACT_NOTHING,
    SOFTAP_MGM_ACT_MAX
} SOFTAP_MGMT_ACTION;


typedef struct 
{
    u8 act;
    u8 wsid;
    u8 macaddr[6];
} SOFTAP_MGMT_MSG;

typedef enum {
    SOFTAP_TXNULL_DELETE=0,
    SOFTAP_TXNULL_MAX
} SOFTAP_TXNULL_ACTION;

typedef struct 
{
	SOFTAP_TXNULL_ACTION act;
} SOFTAP_TXNULL_MSG;

typedef struct t_AP_DETAIL_INFO
{
    u8                    mac[6];
    u8                    channel;
    u8                    ssid_len;
    u8                    ssid[32];
    u8                    key[64];
    u8                    key_len;
    u8                    security_type;
    u8                    security_subType;
    u8                    rssi;
    u8                    txnullcnt;
    u8                    configen;
    u8                    beaconcnt;
    u8                    beaconmisscnt;
    u8                    hwbeaconmisscnt;
    u8                    pmk[32];

    IP_CONFIGURATION      ipconf;
    struct wpa_common_ctx wpactx;
    void                  (*wificbfun)(WIFI_RSP*);
    u32                   sta_txengflow;
    u16                   mgmtseq;
    u16                   dataseq;
    u16                   capability_info;
    u16                    ht_capab;
    u16                   beacon_interval;
    u16                   association_id;
    u16                   unicastseq;
    u8 	                  action;
    u8 	                  status;    
    u8 	                  l2keepalive_en;    
    u8 	                  l2keepalive_sec;    
    u8	                  wifi_security;
    u8	                  priority;
    u8                    idle_count;
    u8                    custom_crypt;
    u8                    ht_support;
    u8                    wmm_support;
    u8                    secondchinfo;
    u8                    is_uuid_valid; //for WPS    
    u8                    uuid[16]; //for WPS
    u8                    noreconnect;
    u8                    dtim_period;
    u8                    checkAPCnt;
    u8                    forcenmode;
    u8                    host_ethpkt_offset;
	struct netif          *pwlan;
} AP_DETAIL_INFO;

typedef struct ssv_reg_st {
    u32 address;
    u32 data;
} ssv_reg;

typedef struct t_IEEE80211STATUS
{
	u8  				local_mac[2][6];    /* TWO STA mode: 0: STA, 1: STA, Othercase: 0: STA, 1: AP */
    char 	            ifname[2][6];
    u8                  ifmode[2];
    u8                  mac0_en;
    u8                  mac1_en;
    u8                  available_index;    /* counter for AP_list */
    u16                 APlist_amount;
    u16                 available_2Gchannel;
    u32                 available_5Gchannel;
	AP_DETAIL_INFO		connAP[2];  /* represet the connnected Ap info: for sta use only */

    OsSemaphore sta_sem;
    OsSemaphore softap_sem;
    OsBufQ  *custom_que;
    
    WIFI_OPMODE opmode;

    u32 region_code;
    u8  build_aplist;      
    u8  countrycode;
    u8  powersave_enable;
    u8  powersave_user_dtime;
    u8  autoip_en;
    u8  rssi_threshold;
    u8  conn_tx_deauth_en;
    u8  force_24G_ht40;      
    u8  txpkt_pbuftype;      
    u8  check_morebit;      
    OsTaskHandle scantask;
    
    //softap status!!
    OsBufQ        dhcps_que;
    OsBufQ        softap_mgm_que;
    u8 softap_phymode;
    u8 softap_state;
    u8 softap_ready;
    u8 softap_hidden_ssid;
    u32 softap_start_ip;	//ex:172.31.254.240
    u32 softap_end_ip;	//ex:172.31.254.250
    u32 softap_gw;	    //ex:172.31.254.250
    u32 softap_subnet;	//ex:255.255.255.0
    u32 softap_dhcp_leasetimes;	
    u32 softap_dhcp_en;	
    u32 softap_dhcp_routerinfo_en;	

    u8 softap_hk_support;	//beacon will have special information for HOMEKIT
    const uint8_t *softap_hk_inIE;
    size_t softap_hk_inIELen;

    s16 softap_sta_connected_number;                //0 or 1 or 2
    u8 softap_sta_mac[6];    	//eapol 
    u8 softap_ht40info;
    u8 softap_dfsignore;

#if PMF_EN
    u8 softap_broad_txpn[6];
#endif
    STA_INFO softap_sta_info[SOFTAP_CLIENT_MAX];
    u8 softap_gtk_ccmp[16];

    u8 softap_key[64];
    u8 softap_keylen;
    u8 softap_pmk[32];
    u8 softap_max_sta_num;
    u8 softap_encryt_mode;  //0: open, 1:WPA2-tkip 2:WPA2:CCMP
    u8 softap_groupcast_pkt_offset;
    u8 softap_nmode_support;
    u8 softap_dhcpd_init;
    s32 softap_reset_cnt;

//<<config start
    s8 softap_ssid[CFG_SOFTAP_SSID_LENGTH+1];   //+1 to prevent printf core dump!!
    s8 softap_ssid_length;   //+1 to prevent printf core dump!!
    u8 run_channel;
    u32 softap_ack_timeout;
    u32 softap_data_timeout;
//>>config end
    
    u16 softap_seq_no;    //sequence number!!
    u16 softap_freg_no;   //fregment number!!
    u16 softap_seq_and_freg_no;
    u16 softap_group_seqno;
    s16 softap_beacon_interval;
    u8  softap_dump_enable;
    u8  softap_beaconpkt_en;
    u8  softap_dtim_period;
    u32 *softap_dtim_addr;
    u32 *softap_beacon_addr;
    u32 softap_pktbuf_tmp;
    s32 softap_mem_cnt;
    s32 softap_eapol_mcnt;
	
    u32	softap_txengflow;
    void (*sofatpnotifycbfn)(STAINFO *);

    //sniffer mode settings
    void (*mgmtcbfn)(packetinfo *);
    void (*sniffercb)(packetinfo *);
    u32 snifferfilter;     
    u32 sniffer_max_len;
    u32 sniffer_min_len;
    u8  sniffer_mac[6];
    //wps
#ifdef WPS_EN    
    void    *pWPSSM;
    u8      bWPSPBC;
    u8      bDoingWPS;
    u8      bWPSFindActivedSR;
    u8      bWPSPBCOverLapChecking;
    u8      bWPSPBCOverLap;    
    u8      bWPSSuccess;
    u32     WPSWalkTimeStart;
    void (*wpsCbfun)(WIFI_WPS_RSP*);
#endif

    //eap
#ifdef EAP_EN    
    void *pEAPSM;    
#endif

    /* reapter mode handler */
    REPEATER_CONF_MODE rept_conf_mode;

    bool mac_debug_en;
    void (*mac_send_debug_cb)(void *data);
    void (*radio_send_debug_cb)(void *data);

    /* mutex. protect the member of gwifistatus */
    OsMutex w_mutex;

    /*
        bit0:RADIO_BAND_2G,
        bit1:RADIO_BAND_5100,
        bit2:RADIO_BAND_5500,
        bit3:RADIO_BAND_5700,
        bit4:RADIO_BAND_5900,
    */
    u8 dpd_disable_mask;

    u8 *user_ie[5];
    void (*wifi_event_cb)(wifi_event_t*);
}IEEE80211STATUS;

/*int remove_sysconfig(void);
void reset_global_conf();
void init_global_conf();

S32 gconfig_set_softap_ssid(char *p_ssid);
S32 gconfig_set_enable_smart(SMARK_LINK_TYPE val, U8 change_now);
S32 gconfig_set_auto_connect(U8 val);
S32 gconfig_save_config();
void clear_ap_lists();*/

/************************************
    WPS related settings 
************************************/
/* Create by the MAC address */
#define WPS_UUID           ""

/* User: Change to your device name */
#define WPS_DEVICE_NAME    "ssv wifi"

/* User: Change to your name */
#define WPS_MANUFACTURER   "SSV"

/* User: Change to your model */
#define WPS_MODEL_NAME     "Model"

/* User: Change to your model number */
#define WPS_MODEL_NUMBER   "1234"

/* User: Change to your serial number */
#define WPS_SERIAL_NUMBER  "12345678"

/* 
   User: change to your device type, see WPS spec Primary Device Type table.
   First number is the category, 0050F204 is the Wi-Fi Alliance OUI 
   and last number is the Sub Category.
   
   Category/sub category:
   Computer/PC                                "1-0050F204-1"
   Computer/Server                            "1-0050F204-2"
   Computer/Media Center                      "1-0050F204-3"
   Computer/Mltra-mobile PC                   "1-0050F204-4"
   Computer/Notebook                          "1-0050F204-5"
   Computer/Desktop                           "1-0050F204-6"
   Computer/Mobile Internet Device            "1-0050F204-7"
   Computer/Netbook                           "1-0050F204-8"
   Input Device/Keyboard                      "2-0050F204-1"
   Input Device/Mouse                         "2-0050F204-2"
   Input Device/Joystick                      "2-0050F204-3"
   Input Device/Trackball                     "2-0050F204-4"
   Input Device/Gaming controller             "2-0050F204-5"
   Input Device/Remote                        "2-0050F204-6"
   Input Device/Touchscreen                   "2-0050F204-7"
   Input Device/Biometric reader              "2-0050F204-8"
   Input Device/Barcode reader                "2-0050F204-9"
   Printers, Scanners/Printer/Printer Server  "3-0050F204-1"
   Printers, Scanners/Scanner                 "3-0050F204-2"
   Printers, Scanners/Fax                     "3-0050F204-3"
   Printers, Scanners/Copier                  "3-0050F204-4"
   Printers, Scanners/All-in-one              "3-0050F204-5"
   Camera/Digital Still Camera                "4-0050F204-1"
   Camera/Video Camera                        "4-0050F204-2"
   Camera/Web Camera                          "4-0050F204-3"
   Camera/Security Camera                     "4-0050F204-4"
   Storage/NAS                                "5-0050F204-1"
   Network Infrastructure/AP                  "6-0050F204-1"
   Network Infrastructure/Router              "6-0050F204-2"
   Network Infrastructure/Switch              "6-0050F204-3"
   Network Infrastructure/Gateway             "6-0050F204-4"
   Displays/Television                        "7-0050F204-1"
   Displays/Electronic Picture Frame          "7-0050F204-2"
   Displays/Projector                         "7-0050F204-3"
   Displays/Monitor                           "7-0050F204-4"
   Multimedia Devices/DAR                     "8-0050F204-1"
   Multimedia Devices/PVR                     "8-0050F204-2"
   Multimedia Devices/MCX                     "8-0050F204-3"
   Multimedia Devices/Set-top box             "8-0050F204-4"
   Multimedia Devices/Media Server            "8-0050F204-5"
   Multimedia Devices/Portable Video Player   "8-0050F204-6"
   Gaming Devices/Xbos                        "9-0050F204-1"
   Gaming Devices/Xbos360                     "9-0050F204-2"
   Gaming Devices/Playstation                 "9-0050F204-3"
   Gaming Devices/Game Console                "9-0050F204-4"
   Gaming Devices/Portable Gaming Device      "9-0050F204-5"
   Telephone/Windows Mobile                   "10-0050F204-1"
   Telephone/Phone-Single Mode                "10-0050F204-2"
   Telephone/Phone-Dual Mode                  "10-0050F204-3"
   Telephone/Smartphone-Single Mode           "10-0050F204-4"
   Telephone/Smartphone-Dual Mode             "10-0050F204-5"
   Audio Devices/Audio Tuner/receiver         "11-0050F204-1"
   Audio Devices/Speaker                      "11-0050F204-2"
   Audio Devices/Portable Music Player        "11-0050F204-3"
   Audio Devices/Headset                      "11-0050F204-4"
   Audio Devices/Headphones                   "11-0050F204-5"
   Audio Devices/Microphone                   "11-0050F204-6"
*/


#define WPS_DEVICE_TYPE    "7-0050F204-1"

/* User: change to your version if you do not want to use smxWiFi version here */
#define WPS_OS_VERSION     0x1800

/* User: you can change display to lable if you do not want to create new PIN. 
         delete virtual_push_button if you do not want to use PBC
*/
#define WPS_CONFIG_METHODS "display virtual_push_button"

/* Should not change for normal case, smxWiFi will handle the received credentials */
#define WPS_CREDENTIAL_PROCESSING  0

/* Wait WPS Timeout */
#define WPS_TIMEOUT                60000


typedef void (*user_tx_cb) (u32 result, u32 user_priv);

#endif
