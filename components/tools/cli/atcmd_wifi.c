#include <string.h>

#include "atcmd_wifi.h"
#include "hdr80211.h"
#include "ieee80211_mgmt.h"
#include "wifi_api.h"
#include "sysconf_api.h"
#include "softap_func.h"
#include "country_cfg.h"
#include "txrx/txtask.h"
#include "txrx/txrx_utils.h"
#include "idmanage/pbuf.h"
#include "txrx/ampdu.h"
#include "hwmac/drv_mac.h"
#include "phy/drv_phy.h"
#include "phy/extpa_api.h"
#if defined(BLE_EN) && (BLE_EN == 1)
#include "ble_api.h"
#endif

#if LWIP_MEMP_DEBUG_EN
#include "lwip/memp.h"
#endif

typedef struct _st_atcmd_wifi_sniffer_config
{
    u16 u16FltFrameType;
    u8 au8FltAddr1[MAC_ADDR_LEN];
    u8 au8FltAddr2[MAC_ADDR_LEN];
    bool bFltAddr1En;
    bool bFltAddr2En;
    bool bFltFrmTypEn;
}__attribute__ ((packed)) ST_ATCMD_WIFI_SNIFFER_CONFIG;

#if CSI_EN
typedef struct _st_atcmd_wifi_csi_config
{
    u16 u16FltFrameType;
    u16 u16FltFrameFcmask;
    u8 au8FltAddr1[MAC_ADDR_LEN];
    u8 au8FltAddr2[MAC_ADDR_LEN];
    u8 au8FltAddr3[MAC_ADDR_LEN];
}__attribute__ ((packed)) ST_ATCMD_WIFI_CSI_CONFIG;
#endif

extern IEEE80211STATUS gwifistatus;

//local function
const uint8_t hk_value_56byte_bin[] = {
  0xDD, 0x36, 0x00, 0xA0, 0x40,
  0x00, 0x07, 0x06, 0x90, 0x77, 0x97, 0x49, 0x5b, 0x29, 0x00, 0x03, 0x60,
  0x02, 0x40, 0x01, 0x14, 0x69, 0x55, 0x39, 0x2d, 0x53, 0x6d, 0x61, 0x72,
  0x74, 0x2d, 0x4f, 0x75, 0x74, 0x6c, 0x65, 0x74, 0x30, 0x32, 0x36, 0x44,
  0x03, 0x06, 0x46, 0x48, 0x48, 0x31, 0x30, 0x37, 0x02, 0x05, 0x4f, 0x70,
  0x72, 0x6f, 0x39
};

static ST_ATCMD_WIFI_SNIFFER_CONFIG _gstSnifferCfg = {0};
static ST_ATCMD_WIFI_SNIFFER_CONFIG _gstPhySnifferCfg = {0};
#if CSI_EN
static ST_ATCMD_WIFI_CSI_CONFIG _gstCsibCfg = {0};
static ST_ATCMD_WIFI_CSI_CONFIG _gstCsignCfg = {0};
#endif
static u32 _gu32MimoPktCnt = 0;
static u32 _gu32NonMimoPktCnt = 0;


extern s32 ssv6xxx_atoi(const s8 *s);
extern void dbg_dump_ip(char *msg,uint8_t *p_ip);
extern void showSWTxQueue(void);
extern int rc_get_rc_info(u8 wsid);


static void _copy_mac_addr(u8 *pu8Dst, u8 *pu8Src, const u8 *pu8Delimiter)
{
    u8 *pu8Mac = pu8Src;
    u8 *pu8Temp = (u8 *)strtok((char *)pu8Mac, (const char *)pu8Delimiter);
    u32 u32ToulVal = 0;
    u32 u32iCount = 0;

    for(u32iCount = 0; u32iCount < MAC_ADDR_LEN; u32iCount++)
    {
        u32ToulVal = (u32)strtoul((const char *)pu8Temp, NULL, 16);
        *(pu8Dst+u32iCount) = (u8)u32ToulVal;
        pu8Temp = (u8 *)strtok(NULL, (const char *)pu8Delimiter);
    }
}

static void _At_Sniffer_Show_Filter_Setting(void)
{
    ATCMD_LOG_I("Sniffer filter setting:\r\n");
    ATCMD_LOG_I("- MAC Address 1(%s) = 0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x\r\n", (_gstSnifferCfg.bFltAddr1En==true)?"Enable":"Disable",
        _gstSnifferCfg.au8FltAddr1[0], _gstSnifferCfg.au8FltAddr1[1], _gstSnifferCfg.au8FltAddr1[2], _gstSnifferCfg.au8FltAddr1[3], _gstSnifferCfg.au8FltAddr1[4], _gstSnifferCfg.au8FltAddr1[5]);
    ATCMD_LOG_I("- MAC Address 2(%s) = 0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x\r\n", (_gstSnifferCfg.bFltAddr2En==true)?"Enable":"Disable",
        _gstSnifferCfg.au8FltAddr2[0], _gstSnifferCfg.au8FltAddr2[1], _gstSnifferCfg.au8FltAddr2[2], _gstSnifferCfg.au8FltAddr2[3], _gstSnifferCfg.au8FltAddr2[4], _gstSnifferCfg.au8FltAddr2[5]);
    ATCMD_LOG_I("- Frame type(%s) = 0x%04x\r\n", (_gstSnifferCfg.bFltFrmTypEn==true)?"Enable":"Disable", _gstSnifferCfg.u16FltFrameType);
}

static void _At_Sniffer_Show_Usage(void)
{
    ATCMD_LOG_I("sniffer=enable\r\n");
    ATCMD_LOG_I("sniffer=disable\r\n");
    ATCMD_LOG_I("sniffer=show\r\n");
    ATCMD_LOG_I("sniffer=filter,addr1,XX:XX:XX:XX:XX:XX\r\n");
    ATCMD_LOG_I("sniffer=filter,addr2,XX:XX:XX:XX:XX:XX\r\n");
    ATCMD_LOG_I("sniffer=filter,type,0xXX\r\n");
    ATCMD_LOG_I("- type: 0x00~0xFC\r\n");
    ATCMD_LOG_I("        Probe request:  0x40\r\n");
    ATCMD_LOG_I("        Probe response: 0x50\r\n");
    ATCMD_LOG_I("        Beacon:         0x80\r\n");
}

static void _At_Sniffer_Callback(packetinfo *p)
{
    OS_EnterCritical();
    if(NULL != p->data)
    {
        u8 *data = (u8 *)p->data;
        struct ieee80211_hdr_3addr *mgmt = (struct ieee80211_hdr_3addr *)data;

        if(true == _gstSnifferCfg.bFltAddr1En)
        {
            if(0 != memcmp((const void *)&(_gstSnifferCfg.au8FltAddr1[0]), (const void *)&(mgmt->addr1[0]), MAC_ADDR_LEN))
            {
                goto EXIT;
            }
        }
        if(true == _gstSnifferCfg.bFltAddr2En)
        {
            if(0 != memcmp((const void *)&(_gstSnifferCfg.au8FltAddr2[0]), (const void *)&(mgmt->addr2[0]), MAC_ADDR_LEN))
            {
                goto EXIT;
            }
        }
        if(true == _gstSnifferCfg.bFltFrmTypEn)
        {
            if(!IS_EQUAL(FC_TYPE(_gstSnifferCfg.u16FltFrameType), FC_TYPE(mgmt->frame_control)))
            {
                //ATCMD_LOG_I("[%s] type = 0x%04x\n", __func__, FC_TYPE(mgmt->frame_control));
                goto EXIT;
            }
        }
        _gu32NonMimoPktCnt++;
        ATCMD_LOG_I("ch=%d, addr2 %02x:%02x:%02x:%02x:%02x:%02x, seq=%d, len=%d, rssi=%d, count=%d\r\n",
            p->channel,
            mgmt->addr2[0], mgmt->addr2[1], mgmt->addr2[2], mgmt->addr2[3], mgmt->addr2[4], mgmt->addr2[5],
            mgmt->seq_ctrl>>4, p->len, p->rssi, _gu32NonMimoPktCnt);
    }
    else
    {
        u32 ht_signal_23_0 = p->ht_signal_23_0;
        u32 ht_signal_47_24 = p->ht_signal_47_24;

        _gu32MimoPktCnt++;
        ATCMD_LOG_I("ch=%d, ht_mcs=%d, ht_len=%d, rssi = %d, count=%d\n", p->channel, ht_signal_23_0&0x7F, p->len, p->rssi, _gu32MimoPktCnt);
    }
EXIT:
    OS_ExitCritical();
}

static int _At_Sniffer_Handler(stParam *param)
{
    if(1 > param->argc)
    {
        goto USAGE;
    }
    if(0 == strcmp(param->argv[0], "enable"))
    {
        _gu32NonMimoPktCnt = 0;
        _gu32MimoPktCnt = 0;
        set_sniffer_config(0xF, _At_Sniffer_Callback);
        DUT_wifi_start(DUT_SNIFFER);
    }
    else if(0 == strcmp(param->argv[0], "disable"))
    {
        set_sniffer_config(0x0, NULL);
        DUT_wifi_stop();
        _gu32NonMimoPktCnt = 0;
        _gu32MimoPktCnt = 0;
        memset((void *)&(_gstSnifferCfg.au8FltAddr1[0]), 0, MAC_ADDR_LEN);
        memset((void *)&(_gstSnifferCfg.au8FltAddr2[0]), 0, MAC_ADDR_LEN);
        _gstSnifferCfg.u16FltFrameType = 0xffff;
        _gstSnifferCfg.bFltAddr1En = false;
        _gstSnifferCfg.bFltAddr2En = false;
        _gstSnifferCfg.bFltFrmTypEn = false;
    }
    else if(0 == strcmp(param->argv[0], "show"))
    {
        _At_Sniffer_Show_Filter_Setting();
    }
    else if(0 == strcmp(param->argv[0], "filter"))
    {
        if(3 > param->argc)
        {
            goto USAGE;
        }
        if(0 == strcmp(param->argv[1], "addr1"))
        {
            _copy_mac_addr(&(_gstSnifferCfg.au8FltAddr1[0]), (u8 *)param->argv[2], (const u8 *)":");
            _gstSnifferCfg.bFltAddr1En = true;
        }
        else if(0 == strcmp(param->argv[1], "addr2"))
        {
            _copy_mac_addr(&(_gstSnifferCfg.au8FltAddr2[0]), (u8 *)param->argv[2], (const u8 *)":");
            _gstSnifferCfg.bFltAddr2En = true;
        }
        else if(0 == strcmp(param->argv[1], "type"))
        {
            _gstSnifferCfg.u16FltFrameType = (u16)strtoul((const char *)param->argv[2], NULL, 16);
            _gstSnifferCfg.bFltFrmTypEn = true;
        }
        else
        {
            goto USAGE;
        }
    }
    else
    {
        goto USAGE;
    }

    return ERROR_SUCCESS;

USAGE:
    _At_Sniffer_Show_Usage();
    return ERROR_SUCCESS;
}

static void _At_Phy_Sniffer_Show_Filter_Setting(void)
{
    ATCMD_LOG_I("Phy Sniffer filter setting:\r\n");
    ATCMD_LOG_I("- MAC Address 1(%s) = 0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x\r\n", (_gstPhySnifferCfg.bFltAddr1En==true)?"Enable":"Disable",
        _gstPhySnifferCfg.au8FltAddr1[0], _gstPhySnifferCfg.au8FltAddr1[1], _gstPhySnifferCfg.au8FltAddr1[2], _gstPhySnifferCfg.au8FltAddr1[3], _gstPhySnifferCfg.au8FltAddr1[4], _gstPhySnifferCfg.au8FltAddr1[5]);
    ATCMD_LOG_I("- MAC Address 2(%s) = 0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x\r\n", (_gstPhySnifferCfg.bFltAddr2En==true)?"Enable":"Disable",
        _gstPhySnifferCfg.au8FltAddr2[0], _gstPhySnifferCfg.au8FltAddr2[1], _gstPhySnifferCfg.au8FltAddr2[2], _gstPhySnifferCfg.au8FltAddr2[3], _gstPhySnifferCfg.au8FltAddr2[4], _gstPhySnifferCfg.au8FltAddr2[5]);
    ATCMD_LOG_I("- Frame type(%s) = 0x%04x\r\n", (_gstPhySnifferCfg.bFltFrmTypEn==true)?"Enable":"Disable", _gstPhySnifferCfg.u16FltFrameType);
}

static void _At_Phy_Sniffer_Show_Usage(void)
{
    ATCMD_LOG_I("phy=sniffer,enable\r\n");
    ATCMD_LOG_I("phy=sniffer,disable\r\n");
    ATCMD_LOG_I("phy=sniffer,get\r\n");
    ATCMD_LOG_I("phy=sniffer,reset\r\n");
    ATCMD_LOG_I("phy=sniffer,show\r\n");
    ATCMD_LOG_I("phy=sniffer,filter,addr1,XX:XX:XX:XX:XX:XX\r\n");
    ATCMD_LOG_I("phy=sniffer,filter,addr2,XX:XX:XX:XX:XX:XX\r\n");
    ATCMD_LOG_I("phy=sniffer,filter,type,0xXXXX\r\n");
    ATCMD_LOG_I("- type: 0x0000~0xFFFF\r\n");
    ATCMD_LOG_I("        Probe request:  0x0040\r\n");
    ATCMD_LOG_I("        Probe response: 0x0050\r\n");
    ATCMD_LOG_I("        Beacon:         0x0080\r\n");
    ATCMD_LOG_I("        Data:           0x0008\r\n");
    ATCMD_LOG_I("- other flags: \r\n");
    ATCMD_LOG_I("        QoS:            0x0080\r\n");
    ATCMD_LOG_I("        ToDS:           0x0100\r\n");
    ATCMD_LOG_I("        FromDS:         0x0200\r\n");
    ATCMD_LOG_I("        Retry:          0x0800\r\n");
    ATCMD_LOG_I("        Private:        0x4000\r\n");
}

static int _At_Phy_Sniffer_Handler(stParam *param)
{
    if(2 > param->argc)
    {
        goto EXIT_FAIL;
    }

    ST_DRV_PHY_SNIFFER_PARAM stPhyParam;
    memset((void *)&stPhyParam, 0, sizeof(ST_DRV_PHY_SNIFFER_PARAM));

    if(0 == strcmp(param->argv[1], "enable"))
    {
        drv_phy_set_sniffer_action(E_DRV_PHY_SNIFFER_ACT_TYPE_ENABLE);
    }
    else if(0 == strcmp(param->argv[1], "disable"))
    {
        drv_phy_set_sniffer_action(E_DRV_PHY_SNIFFER_ACT_TYPE_DISABLE);
        memset((void *)&(_gstPhySnifferCfg.au8FltAddr1[0]), 0, MAC_ADDR_LEN);
        memset((void *)&(_gstPhySnifferCfg.au8FltAddr2[0]), 0, MAC_ADDR_LEN);
        _gstPhySnifferCfg.u16FltFrameType = 0x0000;
        _gstPhySnifferCfg.bFltAddr1En = false;
        _gstPhySnifferCfg.bFltAddr2En = false;
        _gstPhySnifferCfg.bFltFrmTypEn = false;
    }
    else if(0 == strcmp(param->argv[1], "get"))
    {
        drv_phy_set_sniffer_action(E_DRV_PHY_SNIFFER_ACT_TYPE_GET);
    }
    else if(0 == strcmp(param->argv[1], "reset"))
    {
        drv_phy_set_sniffer_action(E_DRV_PHY_SNIFFER_ACT_TYPE_RESET);
    }
    else if(0 == strcmp(param->argv[1], "show"))
    {
        _At_Phy_Sniffer_Show_Filter_Setting();
    }
    else if(0 == strcmp(param->argv[1], "filter"))
    {
        if(3 > param->argc)
        {
            goto EXIT_FAIL;
        }
        u8 au8Addr[MAC_ADDR_LEN] = {0};
        if(0 == strcmp(param->argv[2], "addr1"))
        {
            _copy_mac_addr(&au8Addr[0], (u8 *)param->argv[3], (const u8 *)":");
            stPhyParam.enType = E_DRV_PHY_SNIFFER_PARAM_TYPE_ADDR1;
            stPhyParam.uData.pData = (void *)&au8Addr[0];
            memcpy((void *)&(_gstPhySnifferCfg.au8FltAddr1[0]), (const void *)&au8Addr[0], MAC_ADDR_LEN);
            _gstPhySnifferCfg.bFltAddr1En = true;
        }
        else if(0 == strcmp(param->argv[2], "addr2"))
        {
            _copy_mac_addr(&au8Addr[0], (u8 *)param->argv[3], (const u8 *)":");
            stPhyParam.enType = E_DRV_PHY_SNIFFER_PARAM_TYPE_ADDR2;
            stPhyParam.uData.pData = (void *)&au8Addr[0];
            memcpy((void *)&(_gstPhySnifferCfg.au8FltAddr2[0]), (const void *)&au8Addr[0], MAC_ADDR_LEN);
            _gstPhySnifferCfg.bFltAddr2En = true;
        }
        else if(0 == strcmp(param->argv[2], "type"))
        {
            stPhyParam.enType = E_DRV_PHY_SNIFFER_PARAM_TYPE_FRAMETYPE;
            stPhyParam.uData.u16Data = (u16)strtoul((const char *)param->argv[3], NULL, 16);
            _gstPhySnifferCfg.u16FltFrameType = stPhyParam.uData.u16Data;
            _gstPhySnifferCfg.bFltFrmTypEn = true;
        }
        else
        {
            goto EXIT_FAIL;
        }
        drv_phy_set_sniffer_config(&stPhyParam);
    }
    else
    {
        goto EXIT_FAIL;
    }

    return ERROR_SUCCESS;
EXIT_FAIL:
    return ERROR_INVALID_PARAMETER;
}

int ip2int (char *pStr, uip_ip4addr_t *ipaddr)
{	
	const char delimiters[] = " .";	
	char cp[16]={0};	
	char *pIp1=0, *pIp2=0, *pIp3=0, *pIp4=0;	
		
	strcpy (cp, pStr);	pIp1 = strtok (cp, delimiters);	
	pIp2 = strtok (NULL, delimiters);  	
	pIp3 = strtok (NULL, delimiters);	
	pIp4 = strtok (NULL, delimiters);	
	if (pIp1==0 || pIp2==0 || pIp3==0 ||pIp4==0)	
		return ERROR_INVALID_PARAMETER;
	
	ipaddr->u8[0] = atoi (pIp1);	
	ipaddr->u8[1] = atoi (pIp2);	
	ipaddr->u8[2] = atoi (pIp3);	
	ipaddr->u8[3] = atoi (pIp4);
	
	return ERROR_SUCCESS;
}
uint32_t htonlx(uint32_t x)
{
    uint8_t *s = (uint8_t *)&x;
    return (uint32_t)((s[0] << 24) | (s[1] << 16) | (s[2] << 8) | (s[3]));
}
const char *securityString(u8 ver)
{
    switch(ver) {
    case NONE:
        return "OPEN";
        break;
    case WEP:
        return "WEP";
        break;
    case WPA:
        return "WPA";
        break;
    case WPA2:
        return "WPA2";
        break;
    case WPAWPA2:
        return "WPAWPA2";
        break;
    case WPA3:
        return "WPA3";
        break;		
    default:
        return "unknown security type";
    }
    return NULL;
}
const char *securitySubString(u8 ver)
{
    switch(ver) {
    case NOSECTYPE:
        return "NONE";
        break;
    case TKIP:
        return "TKIP";
        break;
    case CCMP:
        return "AES";
        break;
    case TKIP_CCMP:
        return "TKIP_CCMP";
        break;
    default:
        return "unknown security type";
    }
    return NULL;
}
void scan_cbfunc()
{
    u8 i;
	
	char ap_ssid[33];

    ATCMD_LOG_I("\nCount:%d\n", getAvailableIndex());
    for(i = 0; i < getAvailableIndex(); i++)
    {
		memset(ap_ssid, 0, 33);
		memcpy(ap_ssid, ap_list[i].name, ap_list[i].name_len>32?32:ap_list[i].name_len);

        ATCMD_LOG_I("%2d - name:%32s, rssi:-%2d CH:%2d mac:%02x-%02x-%02x-%02x-%02x-%02x\n", i, ap_ssid, ap_list[i].rssi, ap_list[i].channel
            , ap_list[i].mac[0], ap_list[i].mac[1], ap_list[i].mac[2], ap_list[i].mac[3], ap_list[i].mac[4], ap_list[i].mac[5]);
    }
    ATCMD_LOG_I("end\n");
}

void atwificbfunc(WIFI_RSP *msg)
{
    uint8_t dhcpen;
    u8 mac[6];
    uip_ipaddr_t ipaddr, submask, gateway, dnsserver;

    if(msg->wifistatus == 1)
    {
        ATCMD_LOG_I("%s OK\n", ATCMD_CONNECT);
#ifdef TCPIPSTACK_EN
        if(msg->id == 0)
            get_if_config_2("et0", &dhcpen, (u32*)&ipaddr, (u32*)&submask, (u32*)&gateway, (u32*)&dnsserver, mac, 6);
        else
            get_if_config_2("et1", &dhcpen, (u32*)&ipaddr, (u32*)&submask, (u32*)&gateway, (u32*)&dnsserver, mac, 6);
#endif
        ATCMD_LOG_I("STA%d:\n", msg->id);
        ATCMD_LOG_I("mac addr        - %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
#ifdef TCPIPSTACK_EN
        ATCMD_LOG_I("ip addr         - %d.%d.%d.%d\n", ipaddr.u8[0], ipaddr.u8[1], ipaddr.u8[2], ipaddr.u8[3]);
        ATCMD_LOG_I("netmask         - %d.%d.%d.%d\n", submask.u8[0], submask.u8[1], submask.u8[2], submask.u8[3]);
        ATCMD_LOG_I("default gateway - %d.%d.%d.%d\n", gateway.u8[0], gateway.u8[1], gateway.u8[2], gateway.u8[3]);
        ATCMD_LOG_I("DNS server      - %d.%d.%d.%d\n", dnsserver.u8[0], dnsserver.u8[1], dnsserver.u8[2], dnsserver.u8[3]);
#endif

        recordAP();

    }
    else
    {
        ATCMD_LOG_I("%s OK\n", ATCMD_DISCONNECT);
    }
}

//AT Command Function
int At_DUTSTART (stParam *param)
{
    u8 mode, *pmode;
    ATCMD_LOG_I("\r\n");

    if(param->argc < 1)
    {
        return ERROR_INVALID_PARAMETER;
    }
    
    pmode = (u8*)param->argv[0];
    mode = *pmode - 0x30;
    if(mode >= DUT_MAX)
    {
        return ERROR_INVALID_PARAMETER;
    }

    DUT_wifi_start(mode);	
    return ERROR_SUCCESS;
}

int At_NetScan (stParam *param)
{
    int scan_interval=0;

#if EXTPA_EN
    drv_phy_set_external_lna_pin(true);
#endif    
	
	if((get_DUT_wifi_mode() == DUT_NONE) || (get_DUT_wifi_mode() == DUT_SNIFFER))
        ATCMD_LOG_I("\nPlease run AT+DUT_START=1 first\n");

    if(NULL==param->argv[0])
    {    
        if(scan_AP(scan_cbfunc))
            return ERROR_INVALID_PARAMETER;
    }
    else
    {
        scan_interval=atoi(param->argv[0]);
        if(scan_AP_3(NULL,scan_interval,scan_cbfunc))
            return ERROR_INVALID_PARAMETER;
    }    

    return ERROR_SUCCESS_NO_RSP;
}
int At_SetWifiConfig (stParam *param)
{
        const char delimiters[] = ":";
	char *pMode= 0, *pSsid = 0, *pWebkey = 0, *pMac = 0, *ptmp;
	int ssid_len, keylen = 0;
	int ret;
	int8_t loop_i = 0;
	uint8_t mac[6];
	unsigned long int toul_val;
        int i = 0;
       
	if (param->argc < 2) {
		return ERROR_INVALID_PARAMETER;
	}

	pMode = param->argv[0];
	pSsid = param->argv[1];
	pWebkey = param->argv[2];
	pMac = param->argv[3];
	ssid_len = strlen (pSsid);

    if(pWebkey)
        keylen = strlen(pWebkey);

	if(pMac != NULL) {
        ptmp = strtok (pMac, delimiters);
		for(loop_i=0;loop_i<=5;loop_i++) {
            toul_val =  strtoul(ptmp, NULL, 16);
			mac[loop_i] = toul_val;
			ptmp = strtok (NULL, delimiters);
		}
	}
#if 0    
    for(i = 0; i < getAvailableIndex(); i++)
    {
        if( strcmp( ap_list[i].name, pSsid) == 0 )
        {
            if(ap_list[i].security_type == 0 && keylen==0)
            {
                memcpy(mac, ap_list[i].mac, 6);
                pMac = mac;
                break;
            }
            else if(ap_list[i].security_type =! 0 && keylen > 0)
            {
                memcpy(mac, ap_list[i].mac, 6);
                pMac = mac;
                break;
            }
            
        }
    }  
 #endif
 
    if(pMac)
    {
        ret = set_wifi_config((u8*)pSsid, ssid_len, (u8*)pWebkey, keylen, mac, 6);
    }
    else
    {
        ret = set_wifi_config((u8*)pSsid, ssid_len, (u8*)pWebkey, keylen, NULL, 0);
    }
        
    if(ret != 0)	
        return ERROR_INVALID_PARAMETER;

	return ERROR_SUCCESS;
}
int At_SetIfConfigure (stParam *param)
{

    char *pdhcp = NULL, *pIp = NULL, *pSubmask = NULL, *pGateway = NULL;
    u8 dhcpen;
    uip_ip4addr_t ipaddr, submask, gateway, dnsserver;

    if (param->argc < 1) 
    {
        return ERROR_INVALID_PARAMETER;
    }

    pdhcp = param->argv[0];
    pIp = param->argv[1];
    pSubmask = param->argv[2];
    pGateway = param->argv[3];

    dhcpen = *pdhcp - 0x30;
    if( dhcpen == 0 && param->argc < 4)
    {
        return ERROR_INVALID_PARAMETER;
    }

    memset(&dnsserver, 0, sizeof(uip_ipaddr_t));
    if (dhcpen == 0) 
    {
        if (ERROR_SUCCESS != ip2int (pIp, &ipaddr)) 
        {
            return ERROR_INVALID_PARAMETER;
        }
	 
        if (ERROR_SUCCESS != ip2int (pSubmask, &submask)) 
        {
            return ERROR_INVALID_PARAMETER;
        }
		
        if (ERROR_SUCCESS != ip2int (pGateway, &gateway)) 
        {
            return ERROR_INVALID_PARAMETER;
        }
    }
    else
    {
        memset(&ipaddr, 0, sizeof(uip_ipaddr_t));
        memset(&submask, 0, sizeof(uip_ipaddr_t));
        memset(&gateway, 0, sizeof(uip_ipaddr_t));
    }

#ifdef TCPIPSTACK_EN
    set_if_config(dhcpen, ipaddr.u32, submask.u32, gateway.u32, dnsserver.u32);
#endif

    return ERROR_SUCCESS;
}
int At_Connect (stParam *param)
{
    if((get_DUT_wifi_mode() == DUT_NONE) || (get_DUT_wifi_mode() == DUT_AP) || (get_DUT_wifi_mode() == DUT_SNIFFER))
    {
        ATCMD_LOG_I("\nPlease run AT+DUT_START=1 first\n");
        return ERROR_NOT_IMPLEMENT;
    }

    //if AP is open but user set password, we will return fail
    if( (gwifistatus.connAP[0].security_type == 0 ) && gwifistatus.connAP[0].key_len != 0 )
	{
		printf("WIFI Disconnect\n");
        return ERROR_WIFI_CONNECTION;
    }
    wifi_connect(atwificbfunc);
    return ERROR_SUCCESS_NO_RSP;
}
int At_Disconnect (stParam *param)
{
    wifi_disconnect(atwificbfunc);
    return ERROR_SUCCESS_NO_RSP;
}
int At_GetConfigure (stParam *param)
{   
    uint8_t ssid[33], ssidlen = 32, key[65], keylen = 64, mac[6], dhcpen;
    uip_ipaddr_t ipaddr, submask, gateway, dnsserver;

    if(get_wifi_config(ssid, &ssidlen, key, &keylen, mac, 6) == 0)
    {
        ssid[ssidlen] = 0;
        key[keylen] = 0;
    }
    
#ifdef TCPIPSTACK_EN
    get_if_config(&dhcpen, (u32*)&ipaddr, (u32*)&submask, (u32*)&gateway, (u32*)&dnsserver);
    ATCMD_LOG_I("\r\n");
	ATCMD_LOG_I (ATRSP_CONFIGURE, 0, ssid, key, keylen, dhcpen, 
		ipaddr.u8[0], ipaddr.u8[1], ipaddr.u8[2], ipaddr.u8[3],
		submask.u8[0], submask.u8[1], submask.u8[2], submask.u8[3],
		gateway.u8[0], gateway.u8[1], gateway.u8[2], gateway.u8[3]);
#endif

	return ERROR_SUCCESS;
}
int At_GetNetStatus (stParam *param)
{
    ATCMD_LOG_I("\r\n");
    ATCMD_LOG_I (ATRSP_NETSTATUS, get_wifi_status());	
    return ERROR_SUCCESS;
}
int At_ShowAllAP (stParam *param)
{	
    int i;
    uint8_t apcnt;
	uint8_t ap_ssid[33];
    TAG_AP_INFO *aplist;

    apcnt = get_ap_lsit_total_num();
    if (apcnt > 0) 
    {
        aplist = malloc(apcnt * sizeof(TAG_AP_INFO));
        if(aplist)
        {
            get_ap_list(aplist, &apcnt);
            for (i=0; i<apcnt; i++) 
            {
				memset(ap_ssid, 0, 33);
                memcpy(ap_ssid, ap_list[i].name, ap_list[i].name_len>32?32:ap_list[i].name_len);

                ATCMD_LOG_I("[%d]%s\n",i, ap_ssid);
                ATCMD_LOG_I("        ch: %2d", aplist[i].channel);
                ATCMD_LOG_I(", rssi: -%3d dBm", aplist[i].rssi);
                ATCMD_LOG_I(", mac:  %02x:%02x:%02x:%02x:%02x:%02x", aplist[i].mac[0],aplist[i].mac[1],aplist[i].mac[2],
                                                     aplist[i].mac[3],aplist[i].mac[4],aplist[i].mac[5]);
                ATCMD_LOG_I(", security_type = %s", securityString(aplist[i].security_type));
                ATCMD_LOG_I("/%s\r\n", securitySubString(aplist[i].security_subType));
            }
            free(aplist);
        }
    }
    else {
        ATCMD_LOG_I("please scan ap then you can show all ap info\r\n");
    }
    return ERROR_SUCCESS;
}
int At_ShowConnectAP (stParam *param)
{	
    ATCMD_LOG_I("\r\n");
    if (get_wifi_status() == 1) 
    {
        const int ssid_max_len = 32+1;
        u8 ap_ssid[ssid_max_len];
        memset(ap_ssid, 0, ssid_max_len);
        memcpy(ap_ssid, gwifistatus.connAP[0].ssid, gwifistatus.connAP[0].ssid_len>ssid_max_len?ssid_max_len:gwifistatus.connAP[0].ssid_len);
        ATCMD_LOG_I("%s", ap_ssid);
        ATCMD_LOG_I(", ch: %d", gwifistatus.connAP[0].channel);
        ATCMD_LOG_I(", rssi: -%d dBm", gwifistatus.connAP[0].rssi);
        ATCMD_LOG_I(", mac: %02x:%02x:%02x:%02x:%02x:%02x", gwifistatus.connAP[0].mac[0],gwifistatus.connAP[0].mac[1],gwifistatus.connAP[0].mac[2],
                                         gwifistatus.connAP[0].mac[3],gwifistatus.connAP[0].mac[4],gwifistatus.connAP[0].mac[5]);
        ATCMD_LOG_I(", security_type = %s", securityString(gwifistatus.connAP[0].security_type));
        ATCMD_LOG_I("/%s ", securitySubString(gwifistatus.connAP[0].security_subType));
    } else {
        ATCMD_LOG_I("please connect STA0 to ap\r\n");
    }

    if (gwifistatus.opmode == DUT_TWOSTA) 
    {
        if(get_wifi_status_2(1) == 1)
        {
            const int ssid_max_len =32+1;
            u8 ap_ssid[ssid_max_len];
            memset(ap_ssid, 0, ssid_max_len);
            memcpy(ap_ssid, gwifistatus.connAP[1].ssid, gwifistatus.connAP[1].ssid_len>ssid_max_len?ssid_max_len:gwifistatus.connAP[1].ssid_len);
            ATCMD_LOG_I("%s", ap_ssid);
            ATCMD_LOG_I(", ch: %d", gwifistatus.connAP[1].channel);
            ATCMD_LOG_I(", rssi: -%d dBm", gwifistatus.connAP[1].rssi);
            ATCMD_LOG_I(", mac: %x:%x:%x:%x:%x:%x", gwifistatus.connAP[1].mac[0],gwifistatus.connAP[1].mac[1],gwifistatus.connAP[1].mac[2],
                                             gwifistatus.connAP[1].mac[3],gwifistatus.connAP[1].mac[4],gwifistatus.connAP[1].mac[5]);
            ATCMD_LOG_I(", security_type = %s", securityString(gwifistatus.connAP[1].security_type));
            ATCMD_LOG_I("/%s ", securitySubString(gwifistatus.connAP[1].security_subType));
        }
        else
        {
            ATCMD_LOG_I("please connect STA1 to ap\r\n");
        }
    }
    
    return ERROR_SUCCESS;
}

int At_ConnectActive (stParam *param)
{
    const char delimiters[] = ":";
    char *pSsid = NULL, *pWebkey = NULL, *ptmp=NULL;
    int ssid_len, keylen = 0;
    int ret;
    int8_t loop_i = 0;	
    unsigned long int toul_val;
    int i = 0;
    u8 rssi_threshold=0;
    u8 noreconnect=0;
    TAG_AP_INFO apInfo;
    memset(&apInfo,0,sizeof(TAG_AP_INFO));

    if((get_DUT_wifi_mode() == DUT_NONE) || (get_DUT_wifi_mode() == DUT_AP) || (get_DUT_wifi_mode() == DUT_CONCURRENT) || (get_DUT_wifi_mode() == DUT_SNIFFER))
    {
        ATCMD_LOG_I("\nPlease run AT+DUT_START=1 first\n");
        return ERROR_NOT_IMPLEMENT;
    }
    
    if (param->argc < 1) {
        ATCMD_LOG_I("\r\nUsage:\r\n");
        ATCMD_LOG_I("AT+ACTIVECONNECT=[ssid],[key],[rssi threshold],[reconnect]\r\n");
        ATCMD_LOG_I("                :[rssi threshold] 0: don't check rssi. >0 check rssi\r\n");
        ATCMD_LOG_I("                :[reconnect] 1:reconnect, 0:no reconnect\r\n");
        return ERROR_SUCCESS;
    }

    
    pSsid  = param->argv[0];
    ssid_len = strlen (pSsid);
    
    if(NULL!=param->argv[1])
    {
        pWebkey = param->argv[1];
    }

    if(NULL!=param->argv[2])
    {
        rssi_threshold=atoi(param->argv[2]);
    }

    if(NULL!=param->argv[3])
    {
        noreconnect=(atoi(param->argv[3])==0)?1:0;

    }

    if(pWebkey)
        keylen = strlen(pWebkey);
    
    ATCMD_LOG_I("\nssid=%s,key=%s,rssi_threshold=%d reconnect=%d\n",pSsid,(pWebkey==NULL)?"":pWebkey, rssi_threshold, noreconnect^1);
    if(0==get_the_max_rssi_ap(pSsid,&apInfo))
    {
        ret=wifi_connect_active_5((u8 *)pSsid,ssid_len, (u8 *)pWebkey, keylen, NET80211_CRYPT_UNKNOWN, apInfo.channel, NULL, noreconnect, rssi_threshold,atwificbfunc);
    }
    else
    {
        ret=wifi_connect_active_5((u8 *)pSsid,ssid_len, (u8 *)pWebkey, keylen, NET80211_CRYPT_UNKNOWN, 0, NULL, noreconnect, rssi_threshold,atwificbfunc);
    }
    return ret;
}
int At_SetAutoConnect(stParam *param)
{
    if (param->argc < 1)  {
        return ERROR_INVALID_PARAMETER;
    }    
    set_auto_connect_flag(atoi(param->argv[0]));
    return ERROR_SUCCESS;
}

int At_AP (stParam *param)
{
    if((get_DUT_wifi_mode() == DUT_AP ) || (get_DUT_wifi_mode() == DUT_CONCURRENT) ||  (get_DUT_wifi_mode() == DUT_SNIFFER))
    {
        ATCMD_LOG_I("\nPlease run AT+DUT_START=0 to exit ap mode first\n");
        return ERROR_NOT_IMPLEMENT;
    }
       
    DUT_wifi_start(DUT_AP);
    return ERROR_SUCCESS_NO_RSP;
}
int At_AP_EXIT (stParam *param)
{
    int ret = ERROR_SUCCESS;
    if( (get_DUT_wifi_mode() != DUT_AP  ) )
    {
        ATCMD_LOG_I("\nPlease run AT+DUT_START=2 to enter ap mode first\n");
        return ERROR_NOT_IMPLEMENT;
    }
    
    //softap_exit();

    ret = DUT_wifi_start(DUT_STA);
    return ret;
}
#if(WIFI_REPEATER_EN==1)
int At_SET_REPTCONFIG (stParam *param)
{
    u8 conf_mode;
    char *p_ssid=NULL;
    u32 ssid_len;

    char *p_key=NULL;
    u32 key_len;

    printf("\r\n");

        if (param->argc != 5) {
        goto USAGE;
    }
    conf_mode=atoi(param->argv[0]);
    ssid_len=atoi(param->argv[2]);
    key_len=atoi(param->argv[4]);

    p_ssid=(ssid_len!=0)?param->argv[1]:NULL;
    p_key=(key_len!=0)?param->argv[3]:NULL;

    printf("conf_mode=%d\n",conf_mode);

    if(NULL!=p_ssid)
    {
        printf("ssid=%s\n",p_ssid);
    }

    if(NULL!=p_key)
    {
        printf("key=%s\n",p_key);
    }

    return wifi_repetater_easy_conf( conf_mode,p_ssid,ssid_len, p_key, key_len);

USAGE:
    printf("AT+SET_REPTCONFIG=[mode], [ssid],[ssid_len],[key],[key_len]\n");
    printf("mode=0, Depend on the Home AP's setting\n");
    printf("mode=1, Use default setiing\n");
    printf("mode=2, Follow customer's setting\n");
    return 0;
}
#endif
#if(SOFTAP_EN==1)
int At_SET_AP_HIDDENID(stParam *param)
{
    u32 val=0;
    if (param->argc == 1)
    {
        val = strtoul(param->argv[0], NULL, 10);
        if(val < 0xFF)
        {
            return wifi_ap_set_hidden_ssid((u8)val);
        }
        else
            return ERROR_INVALID_PARAMETER;
    }
    else
        return ERROR_INVALID_PARAMETER;
}

int At_SET_APCONFIG (stParam *param)
{
    int32_t rlt = ERROR_INVALID_PARAMETER;
	SOFTAP_CUSTOM_CONFIG isoftap_custom_config;
	int loop_i;
	uint32_t tmp_ip0=0;
	uint32_t tmp_ip1=0;
	uint32_t tmp_ip2=0;
	uint32_t tmp_ip3=0;
	   
	ATCMD_LOG_I("\n[%s] : +++\n",__func__);

    if (param->argc < 9) {
        return ERROR_INVALID_PARAMETER;
    }

    memset(&isoftap_custom_config, 0, sizeof(SOFTAP_CUSTOM_CONFIG));
	isoftap_custom_config.start_ip = strtoul(param->argv[0], NULL, 16);
	isoftap_custom_config.end_ip = strtoul(param->argv[1], NULL, 16);
	isoftap_custom_config.gw = strtoul(param->argv[2], NULL, 16);
	isoftap_custom_config.subnet = strtoul(param->argv[3], NULL, 16);

    
    isoftap_custom_config.max_sta_num = strtoul(param->argv[4], NULL, 10);

	if(isoftap_custom_config.max_sta_num > SOFTAP_CLIENT_MAX){
		isoftap_custom_config.max_sta_num = SOFTAP_CLIENT_MAX;
	}

	if(isoftap_custom_config.max_sta_num < 1){
		isoftap_custom_config.max_sta_num = 1;
	}

	if(isoftap_custom_config.end_ip >  (isoftap_custom_config.start_ip + isoftap_custom_config.max_sta_num)){
		tmp_ip0 = isoftap_custom_config.end_ip;
		isoftap_custom_config.end_ip = isoftap_custom_config.start_ip + isoftap_custom_config.max_sta_num;
		tmp_ip1 = isoftap_custom_config.end_ip;
		ATCMD_LOG_I("\n<Error> end_ip = %d.%d.%d.%d  over start_ip+max_stanum -----> new end_ip=%d.%d.%d.%d\n\n",(tmp_ip0>>24)&0xff,(tmp_ip0>>16)&0xff,(tmp_ip0>>8)&0xff,(tmp_ip0>>0)&0xff,(tmp_ip1>>24)&0xff,(tmp_ip1>>16)&0xff,(tmp_ip1>>8)&0xff,(tmp_ip1>>0)&0xff);
	}
	
    isoftap_custom_config.encryt_mode = strtoul(param->argv[5], NULL, 10);
    isoftap_custom_config.keylen = strtoul(param->argv[6], NULL, 10);
	
    if(isoftap_custom_config.keylen != strlen(param->argv[7])){
        rlt = -1;
        goto error_exit;
    }

    memset(isoftap_custom_config.key,0x0,sizeof(isoftap_custom_config.key));            
    memcpy(isoftap_custom_config.key,param->argv[7],isoftap_custom_config.keylen);
	
	isoftap_custom_config.channel = strtoul(param->argv[8], NULL, 10);
	isoftap_custom_config.ssid_length= strtoul(param->argv[9], NULL, 10);
	if(isoftap_custom_config.ssid_length != strlen(param->argv[10])){
		rlt = -2;
		goto error_exit;
	}

	memset(isoftap_custom_config.ssid,0x0,sizeof(isoftap_custom_config.ssid));			  
	memcpy(isoftap_custom_config.ssid,param->argv[10],isoftap_custom_config.ssid_length);

	tmp_ip0 = htonlx(isoftap_custom_config.start_ip);
	tmp_ip1 = htonlx(isoftap_custom_config.end_ip);
	tmp_ip2 = htonlx(isoftap_custom_config.gw);
	tmp_ip3 = htonlx(isoftap_custom_config.subnet);
	
	dbg_dump_ip("start_ip", (uint8_t*)&tmp_ip0);
	dbg_dump_ip("end_ip", (uint8_t*)&tmp_ip1);
	dbg_dump_ip("gateway", (uint8_t*)&tmp_ip2);
	dbg_dump_ip("netmask", (uint8_t*)&tmp_ip3);
	
    ATCMD_LOG_I("(max_sta_num,encryt_mode,channel)=(%d,%d,%d)\n",isoftap_custom_config.max_sta_num,isoftap_custom_config.encryt_mode,isoftap_custom_config.channel);
	ATCMD_LOG_I("(keylen,key)=(%d,%s)\n",isoftap_custom_config.keylen,isoftap_custom_config.key);
	ATCMD_LOG_I("(ssid_length,ssid)=(%d,%s)\n",isoftap_custom_config.ssid_length,isoftap_custom_config.ssid);

	isoftap_custom_config.beacon_interval = 50;
	
	rlt = softap_set_custom_conf(&isoftap_custom_config);

        if(rlt == -4)
            ATCMD_LOG_I("Don't configure SoftAP when SoftAP is running. Please execute AT+AP_EXIT first\n");
	
    return rlt;
error_exit:
	for(loop_i=0;loop_i<param->argc;loop_i++){
		ATCMD_LOG_I("argv[%d]=%s\n",loop_i,param->argv[loop_i]);
	}
    ATCMD_LOG_I("<Error>At_SET_APCONFIG rlt = %d\n", rlt);
    return rlt;
}


int At_GET_APCONFIG (stParam *param)
{
    int ret = ERROR_INVALID_PARAMETER;
    SOFTAP_CUSTOM_CONFIG ap_conf;
    memset(&ap_conf, 0, sizeof(SOFTAP_CUSTOM_CONFIG));
    ret = softap_get_custom_conf(&ap_conf); 
    ATCMD_LOG_I("\r\n");

    if(ret == 0)
        ATCMD_LOG_I("AT+GET_APCONFIG=0x%x,0x%x,0x%x,0x%x,%d,%d,%d,%s,%d,%d,%s\n", 
        ap_conf.start_ip, ap_conf.end_ip, ap_conf.gw, ap_conf.subnet, ap_conf.max_sta_num, ap_conf.encryt_mode, ap_conf.keylen, ap_conf.key, ap_conf.channel,ap_conf.ssid_length, ap_conf.ssid );
    
    return ret;
}
#endif //#if(SOFTAP_EN==1)
int At_GET_APMODE (stParam *param)
{
    WIFI_OPMODE mode = get_DUT_wifi_mode();
    ATCMD_LOG_I("\r\n");
    ATCMD_LOG_I("AT+GET_APMODE=%s\n", mode == DUT_AP?"AP Mode":"NO AP Mode");	
    return 0;
}
int At_CmdSetCountryCode(stParam *param) 
{
    int ret = ERROR_SUCCESS;	
    if( param->argc < 1 )
    {
        return ERROR_INVALID_PARAMETER;
    }
 
    ret = config_channel(atoi(param->argv[0]));
    return ret;
}

#if(SOFTAP_EN==1)
int At_ListStation (stParam *param)
{
    int ret = ERROR_SUCCESS;
    CONNSTAINFO connected_sta[SOFTAP_CLIENT_MAX] ;
    u8 number_sta = SOFTAP_CLIENT_MAX;
    int i=0;

    if(gwifistatus.ifmode[1] != IF_AP)
    {
        ATCMD_LOG_I("\nPlease Enter AP Mode First\n");
        return -1;
    }
    
    if( get_connectsta_info( (CONNSTAINFO*)&connected_sta, &number_sta) == 0 )
    {
        ATCMD_LOG_I("\nConnected Station Number = %d\n", number_sta);
        for(i=0; i<number_sta; i++)
        {
            ATCMD_LOG_I("STA%d MAC:%02x:%02x:%02x:%02x:%02x:%02x, IP:%d.%d.%d.%d\n", i+1, connected_sta[i].mac[0], connected_sta[i].mac[1], connected_sta[i].mac[2], connected_sta[i].mac[3], connected_sta[i].mac[4], connected_sta[i].mac[5], connected_sta[i].ipaddr[0], connected_sta[i].ipaddr[1], connected_sta[i].ipaddr[2], connected_sta[i].ipaddr[3]);
        }
    }
    else
    {
        ret = -1;
    }
    
    return ret;
}
int At_KickStation (stParam *param)
{
    int ret = ERROR_SUCCESS;
    int i = 0;
    const char delimiters[] = ":";
    char *pMac = 0, *ptmp;
    unsigned long int toul_val;
    uint8_t kick_mac[6] = {0};

    ATCMD_LOG_I("\n");
    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
        
    if(get_DUT_wifi_mode() != DUT_AP )
    {
        ATCMD_LOG_I("Please Enter AP Mode First\n");
        return -1;
    }
    
    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    if( strlen(param->argv[0]) != 17 )
    {
        ATCMD_LOG_I("EX:%s=00:23:45:67:89:AB\n", ATCMD_KICK_STA);
        return ERROR_INVALID_PARAMETER;
    }

    pMac = param->argv[0];

    if(pMac != NULL) 
    {
        ptmp = strtok (pMac, delimiters);
        for(i=0; i<=5; i++) 
        {
            toul_val =  strtoul(ptmp, NULL, 16);
            kick_mac[i] = toul_val;
            ptmp = strtok (NULL, delimiters);
        }
    }
    
    wifi_softap_disconnect_sta(kick_mac);   
    
    return ret;
}
#endif

int At_NetScanHidden (stParam *param)
{   
#if EXTPA_EN    
	drv_phy_set_external_lna_pin(true);
#endif	
	if((get_DUT_wifi_mode() == DUT_NONE) || (get_DUT_wifi_mode() == DUT_SNIFFER))
    {
        ATCMD_LOG_I("\nPlease run AT+DUT_START=1 first\n");
        return ERROR_NOT_IMPLEMENT;
    }

    if (param->argc < 1) {
        return ERROR_INVALID_PARAMETER;
    }
        
    if(scan_AP_2( param->argv[0], scan_cbfunc))
        return ERROR_INVALID_PARAMETER;
    
    return ERROR_SUCCESS_NO_RSP;
}

int At_SetWifiConfig2 (stParam *param)
{
    const char delimiters[] = ":";
	char *pid, *pMode= 0, *pSsid = 0, *pWebkey = 0, *pMac = 0, *ptmp;
	int ssid_len, keylen = 0;
	int ret;
	int8_t loop_i = 0;
	uint8_t mac[6];
    u8 id;
	unsigned long int toul_val;
       
	if (param->argc < 3) {
		return ERROR_INVALID_PARAMETER;
	}

	pid = param->argv[0];
	pMode = param->argv[1];
	pSsid = param->argv[2];
	pWebkey = param->argv[3];
	pMac = param->argv[4];
	ssid_len = strlen (pSsid);

    id = *pid - 0x30;
	if (id != 0 && id != 1) {
		return ERROR_INVALID_PARAMETER;
	}

    if(pWebkey)
        keylen = strlen(pWebkey);

	if(pMac != NULL) {
        ptmp = strtok (pMac, delimiters);
		for(loop_i=0;loop_i<=5;loop_i++) {
            toul_val =  strtoul(ptmp, NULL, 16);
			mac[loop_i] = toul_val;
			ptmp = strtok (NULL, delimiters);
		}
	}

    if(pMac)
    {
        ret = set_wifi_config_3(id, (u8*)pSsid, ssid_len, (u8*)pWebkey, keylen, mac, 6, 5);
    }
    else
    {
        ret = set_wifi_config_3(id, (u8*)pSsid, ssid_len, (u8*)pWebkey, keylen, NULL, 0, 5);
    }
        
    if(ret != 0)	
        return ERROR_INVALID_PARAMETER;

	return ERROR_SUCCESS;
}

int At_SetIfConfigure2 (stParam *param)
{

    char *pid, *pdhcp = NULL, *pIp = NULL, *pSubmask = NULL, *pGateway = NULL;
    u8 dhcpen, id;
    uip_ip4addr_t ipaddr, submask, gateway, dnsserver;
    int ret;

    if (param->argc < 2) 
    {
        return ERROR_INVALID_PARAMETER;
    }

    pid = param->argv[0];
    pdhcp = param->argv[1];
    pIp = param->argv[2];
    pSubmask = param->argv[3];
    pGateway = param->argv[4];

    id = *pid - 0x30;
    dhcpen = *pdhcp - 0x30;
    if( (dhcpen == 0 && param->argc < 5) || (id != 0 && id != 1))
    {
        return ERROR_INVALID_PARAMETER;
    }

    memset(&dnsserver, 0, sizeof(uip_ipaddr_t));
    if (dhcpen == 0) 
    {
        if (ERROR_SUCCESS != ip2int (pIp, &ipaddr)) 
        {
            return ERROR_INVALID_PARAMETER;
        }
	 
        if (ERROR_SUCCESS != ip2int (pSubmask, &submask)) 
        {
            return ERROR_INVALID_PARAMETER;
        }
		
        if (ERROR_SUCCESS != ip2int (pGateway, &gateway)) 
        {
            return ERROR_INVALID_PARAMETER;
        }
    }
    else
    {
        memset(&ipaddr, 0, sizeof(uip_ipaddr_t));
        memset(&submask, 0, sizeof(uip_ipaddr_t));
        memset(&gateway, 0, sizeof(uip_ipaddr_t));
    }

#ifdef TCPIPSTACK_EN
    ret = set_if_config_2(id, dhcpen, ipaddr.u32, submask.u32, gateway.u32, dnsserver.u32);
    
    if(ret != 0)
    {
        return ERROR_INVALID_PARAMETER;
    }
#endif

    return ERROR_SUCCESS;
}

int At_Connect2 (stParam *param)
{
    u8 id, *pid;
    int ret;
    ATCMD_LOG_I("\r\n");

    pid = (u8*)param->argv[0];
    id = *pid - 0x30;
    if((param->argc < 1) || (id != 0 && id != 1))
    {
        return ERROR_INVALID_PARAMETER;
    }

    ret = wifi_connect_2(id, atwificbfunc);
    if(ret != 0)
    {
        return ERROR_INVALID_PARAMETER;
    }

    return ERROR_SUCCESS_NO_RSP;
}
int At_Disconnect2 (stParam *param)
{
    u8 id, *pid;
    ATCMD_LOG_I("\r\n");

    pid = (u8*)param->argv[0];
    id = *pid - 0x30;
    if((param->argc < 1) || (id != 0 && id != 1))
    {
        return ERROR_INVALID_PARAMETER;
    }

    wifi_disconnect_2(id, atwificbfunc);
    return ERROR_SUCCESS_NO_RSP;
}
int At_GetNetStatus2 (stParam *param)
{
    u8 id, *pid;
    ATCMD_LOG_I("\r\n");

    pid = (u8*)param->argv[0];
    id = *pid - 0x30;
    if((param->argc < 1) || (id != 0 && id != 1))
    {
        return ERROR_INVALID_PARAMETER;
    }

    ATCMD_LOG_I (ATRSP_NETSTATUS2, id, get_wifi_status_2(id));	
    return ERROR_SUCCESS;
}
#if(ENABLE_HK==1)
int At_HKAP(stParam *param)
{
    //softap_start();
	SOFTAP_CUSTOM_CONFIG isoftap_custom_config;

#if 0
	isoftap_custom_config.a_gw_digit[0] = 192;
	isoftap_custom_config.a_gw_digit[1] = 168;
	isoftap_custom_config.a_gw_digit[2] = 0;
#endif

	isoftap_custom_config.start_ip = 0xc0a80002;	//192.168.10.2
	isoftap_custom_config.end_ip = 0xc0a80005; 	//192.168.10.5
	isoftap_custom_config.gw = 0xc0a80001; 		//192.168.10.254
	isoftap_custom_config.subnet = 0xffffff00; 	//255.255.255.0

	isoftap_custom_config.max_sta_num = 1;
	isoftap_custom_config.encryt_mode = 0;

	isoftap_custom_config.beacon_interval = 50;

	isoftap_custom_config.keylen = strlen("1234567890");
	memcpy(&isoftap_custom_config.key[0],"1234567890",isoftap_custom_config.keylen);
	
	isoftap_custom_config.channel= 1;

	isoftap_custom_config.ssid_length = strlen("iU9-Smart-Outlet026D");
	memcpy(&isoftap_custom_config.ssid[0],"iU9-Smart-Outlet026D",isoftap_custom_config.ssid_length);
	
	softap_set_custom_conf(&isoftap_custom_config);

	homekit_softap_start( (uint8_t*)&hk_value_56byte_bin[0], sizeof(hk_value_56byte_bin));

    return ERROR_SUCCESS_NO_RSP;
}
#endif
int At_Sniffer(stParam *param)
{
    ATCMD_LOG_I("\r\n");
    return _At_Sniffer_Handler(param);
}

static void mgm_watch_cb(packetinfo *p)
{
    OS_EnterCritical();
    struct ieee80211_hdr_3addr *mgmt = NULL;
    u8 *data=NULL;
    data=(u8 *)p->data;
    mgmt=(struct ieee80211_hdr_3addr *)data;
    ATCMD_LOG_I("addr2 %x:%x:%x:%x:%x:%x,frame ctrl=0x%x, seq=%d, len=%d\r\n",
            mgmt->addr2[0],mgmt->addr2[1],mgmt->addr2[2],mgmt->addr2[3],mgmt->addr2[4],mgmt->addr2[5],
            mgmt->frame_control,
            mgmt->seq_ctrl>>4,
            p->len);
    OS_ExitCritical();
}


int At_mgmt_watch(stParam *param) 
{
    wifi_mgmt_watch_cbfn(mgm_watch_cb);
    return ERROR_SUCCESS;
}


static void _fixed_rate_usage(void)
{
    ATCMD_LOG_I("fixrate [enable mask], [phy rate idx], [try cnt]\n");
    ATCMD_LOG_I("enable mask: (now only support ALL)\n");
    ATCMD_LOG_I("           0:NONE\n");
    ATCMD_LOG_I("           1:STA\n");
    ATCMD_LOG_I("           2:AP\n");
    ATCMD_LOG_I("           3:ALL\n");
    
    ATCMD_LOG_I("phy rate idx:\n");
    ATCMD_LOG_I("             0= B Mode 1M\n");
    ATCMD_LOG_I("             1= B Mode 2M\n");
    ATCMD_LOG_I("             2= B Mode 5.5M\n");
    ATCMD_LOG_I("             3= B Mode 11M\n");
    ATCMD_LOG_I("             7= G Mode 6M\n");
    ATCMD_LOG_I("             8= G Mode 9M\n");
    ATCMD_LOG_I("             9= G Mode 12M\n");
    ATCMD_LOG_I("            10= G Mode 18M\n");
    ATCMD_LOG_I("            11= G Mode 24M\n");
    ATCMD_LOG_I("            12= G Mode 36M\n");
    ATCMD_LOG_I("            13= G Mode 48M\n");
    ATCMD_LOG_I("            14= G Mode 54M\n");
    ATCMD_LOG_I("            15= N Mode 6.5M\n");
    ATCMD_LOG_I("            16= N Mode 13M\n");
    ATCMD_LOG_I("            17= N Mode 19.5M\n");
    ATCMD_LOG_I("            18= N Mode 26M\n");
    ATCMD_LOG_I("            19= N Mode 39M\n");
    ATCMD_LOG_I("            20= N Mode 52M\n");
    ATCMD_LOG_I("            21= N Mode 58.5M\n");
    ATCMD_LOG_I("            22= N Mode 65M\n");
    
    ATCMD_LOG_I("try cnt: 1<=try cnt<=15\n");
    return;
}
int At_fixrate(stParam *param) 
{
    u8 enable_mask;
    u8 fixed_rate;
    u8 try_cnt;
    if(param->argc < 3)
    {
         _fixed_rate_usage();
        return ERROR_INVALID_PARAMETER;
    }
    
    enable_mask = atoi(param->argv[0]);
    fixed_rate = atoi(param->argv[1]);
    try_cnt = atoi(param->argv[2]);
    ATCMD_LOG_I("\nenable mask=0x%x, fixed rate=%d, try cnt=%d\n",enable_mask,fixed_rate,try_cnt);
    if(0==wifi_set_user_fixed_rate(enable_mask,fixed_rate,try_cnt))
    {
        return ERROR_SUCCESS;
    }
    else
    {
         _fixed_rate_usage();
        return ERROR_INVALID_PARAMETER;
    }
   
}

bool _gbWaitNowSend = FALSE;
static void _At_TestNow_Callback(u32 result, u32 user_priv)
{
    ATCMD_LOG_I("[%s][%d] Test now send finish... Result(%u): Private data = %u\n", __FUNCTION__, __LINE__, result, user_priv);
    _gbWaitNowSend = FALSE;
}
int At_TestNow(stParam *param)
{
    u32 u32UserData = 1234;
    u8 u8TargetMAC[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    u8 au8OUI[] = {0x00, 0x00, 0x00};
    u8 u8Data[] = {0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f};
    u8 u8DataLen = sizeof(u8Data)/sizeof(u8);
    u8 *pu8Data = NULL;
    u32 u32PktLen = 0;

    /* Management Probe request frame */
    pu8Data = wifi_mgm_prob_create(u8TargetMAC, au8OUI, u8Data, u8DataLen, &u32PktLen);
    _gbWaitNowSend = TRUE;
    wifi_send_packet_freedom(pu8Data, u32PktLen, _At_TestNow_Callback, u32UserData, FALSE);
    while(TRUE == _gbWaitNowSend)
    {
        OS_MsDelay(100);
    }
    wifi_mgm_prob_release(pu8Data);
    pu8Data = NULL;

    OS_MsDelay(100);
    /* Management Action frame */
    pu8Data = wifi_mgm_action_create(u8TargetMAC, au8OUI, u8Data, u8DataLen, &u32PktLen);
    _gbWaitNowSend = TRUE;
    wifi_send_packet_freedom(pu8Data, u32PktLen, _At_TestNow_Callback, u32UserData+1234, FALSE);
    while(TRUE == _gbWaitNowSend)
    {
        OS_MsDelay(100);
    }
    wifi_mgm_action_release(pu8Data);
    pu8Data = NULL;

    OS_MsDelay(100);
    /* Data frame */
    bool bSetRate = FALSE;
    u8 u8EnMask = 0;
    u8 u8Channel = wifi_get_current_channel();
    u8 u8Rate = (u8Channel<=14)?USER_FIXED_RATE_B_MODE_1M:USER_FIXED_RATE_G_MODE_6M; //For better quality, to set 2.4G(1Mbps)/5G(6Mbps) fix rate.
    u8 u8TryCnt = 5;
    u8 u8PrvRate = 0;
    u8 u8PrvTryCnt = 0;
    pu8Data = wifi_data_create(u8TargetMAC, u8Data, (u32)u8DataLen);
    u32PktLen = IEEE80211_LEN+u8DataLen; //MAC header length(24 bytes)+The specific data length
    wifi_get_user_fixed_rate(&u8EnMask, &u8PrvRate, &u8PrvTryCnt);
    if(0 == u8EnMask)
    {
        u8EnMask = 1;
        wifi_set_user_fixed_rate(u8EnMask, u8Rate, u8TryCnt);
        bSetRate = TRUE;
    }
    _gbWaitNowSend = TRUE;
    wifi_send_packet_freedom(pu8Data, u32PktLen, _At_TestNow_Callback, u32UserData+2468, FALSE);
    while(TRUE == _gbWaitNowSend)
    {
        OS_MsDelay(100);
    }
    if(TRUE == bSetRate)
    {
        u8EnMask = 0;
        wifi_set_user_fixed_rate(u8EnMask, u8PrvRate, u8PrvTryCnt);
    }
    wifi_data_release(pu8Data);
    pu8Data = NULL;

    return ERROR_SUCCESS;
}

int At_SetTxQConfig(stParam *param)
{
    if(2 != param->argc)
    {
        goto USAGE;
    }

    ATCMD_LOG_I("\r\n");

    if(0 == strcmp(param->argv[0], "num"))
    {
        wifi_set_module_config(E_WIFI_MOD_CFG_TYPE_TXQ_WAIT_NUM, (u32)ssv6xxx_atoi((const s8 *)param->argv[1]));
    }
    else if(0 == strcmp(param->argv[0], "time"))
    {
        wifi_set_module_config(E_WIFI_MOD_CFG_TYPE_TXQ_WAIT_TIME, (u32)ssv6xxx_atoi((const s8 *)param->argv[1]));
    }
    else if(0 == strcmp(param->argv[0], "chkqnum"))
    {
        wifi_set_module_config(E_TXQUE_CFG_TYPE_CHECK_HWQ_NUM, (u32)ssv6xxx_atoi((const s8 *)param->argv[1]));
    }
    else
    {
        goto USAGE;
    }

    return ERROR_SUCCESS;

USAGE:
    ATCMD_LOG_I("settxqcfg=num,<number>\r\n");
    ATCMD_LOG_I("settxqcfg=time,<time>\r\n");
    return ERROR_SUCCESS;
}

int At_SetAmpduConfig(stParam *param)
{
    if(3 != param->argc)
    {
        goto USAGE;
    }

    ATCMD_LOG_I("\r\n");

    if(0 == strcmp(param->argv[0], "tx"))
    {
        if(0 == strcmp(param->argv[1], "chktime"))
        {
            wifi_set_module_config(E_WIFI_MOD_CFG_TYPE_AMPDU_TX_CHKTIME, (u32)ssv6xxx_atoi((const s8 *)param->argv[2]));
        }
        else
        {
            goto USAGE;
        }
    }
    else
    {
        goto USAGE;
    }

    return ERROR_SUCCESS;

USAGE:
    ATCMD_LOG_I("setampducfg=tx,chktime,<time in ms>\r\n");
    return ERROR_SUCCESS;
}

#if CSI_EN
struct drv_phy_csi_report phy_csi_result;
static void _phy_csi_isr(void *result)
{
    int i = 0;
    struct drv_phy_csi_report *csi = (struct drv_phy_csi_report *)result;
    
    if (false == csi->done) {
        printf("Cannot get csi report\n");
        return;
    }

    printf("tstamp %llu\n", csi->timestamp);
    printf("snr %d, rssi %d\n", csi->snr, csi->rssi);
    printf("frame control 0x%04x\n", csi->frame_ctl);
    printf("addr1: %02x:%02x:%02x:%02x:%02x:%02x\n", 
        csi->addr1[0], csi->addr1[1], csi->addr1[2], csi->addr1[3], csi->addr1[4], csi->addr1[5]);
    printf("addr2: %02x:%02x:%02x:%02x:%02x:%02x\n", 
        csi->addr2[0], csi->addr2[1], csi->addr2[2], csi->addr2[3], csi->addr2[4], csi->addr2[5]);
    printf("addr1: %02x:%02x:%02x:%02x:%02x:%02x\n", 
        csi->addr3[0], csi->addr3[1], csi->addr3[2], csi->addr3[3], csi->addr3[4], csi->addr3[5]);
    
    for (i = 0; i < csi->len; i++) {
        printf("index %d    real part %d    imag part %d\n", 
                csi->stat[i].idx, csi->stat[i].csi_i, csi->stat[i].csi_q);
    }

    csi->done = false;
}

static void At_CsiConfigB_Show_Usage(void)
{
    ATCMD_LOG_I("AT+CSI_B=enable\r\n");
    ATCMD_LOG_I("AT+CSI_B=latch\r\n");
    ATCMD_LOG_I("AT+CSI_B=disable\r\n");
    ATCMD_LOG_I("AT+CSI_B=show\r\n");
    ATCMD_LOG_I("AT+CSI_B=filter,addr1,XX:XX:XX:XX:XX:XX\r\n");
    ATCMD_LOG_I("AT+CSI_B=filter,addr2,XX:XX:XX:XX:XX:XX\r\n");
    ATCMD_LOG_I("AT+CSI_B=filter,addr3,XX:XX:XX:XX:XX:XX\r\n");
    ATCMD_LOG_I("AT+CSI_B=filter,type,0xXXXX\r\n");
    ATCMD_LOG_I("AT+CSI_B=filter,fcmask,0xXXXX\r\n");
}

int At_CsiConfigB(stParam *param)
{
    if (param->argc < 1) {
        goto EXIT_FAIL;
    }

    ATCMD_LOG_I("\r\n");
    
    if(0 == strcmp(param->argv[0], "enable"))
    {
        wifi_csi_irq_enable(FALSE);
        wifi_csi_irq_enable(TRUE);
        wifi_register_csi_isr(_phy_csi_isr, &phy_csi_result);
        wifi_set_csi_config_b(_gstCsibCfg.au8FltAddr1, 
                              _gstCsibCfg.au8FltAddr2, 
                              _gstCsibCfg.au8FltAddr3, 
                              _gstCsibCfg.u16FltFrameType,
                              _gstCsibCfg.u16FltFrameFcmask);
        wifi_enable_csi_b(TRUE);
    }
    else if(0 == strcmp(param->argv[0], "latch"))
    {
        wifi_enable_csi_b(TRUE);
    }
    else if(0 == strcmp(param->argv[0], "disable"))
    {
        wifi_enable_csi_b(FALSE);
        memset((void *)&(_gstCsibCfg.au8FltAddr1[0]), 0, MAC_ADDR_LEN);
        memset((void *)&(_gstCsibCfg.au8FltAddr2[0]), 0, MAC_ADDR_LEN);
        memset((void *)&(_gstCsibCfg.au8FltAddr3[0]), 0, MAC_ADDR_LEN);
        _gstCsibCfg.u16FltFrameType = 0x0000;
        _gstCsibCfg.u16FltFrameFcmask = 0x0000;
    }
    else if(0 == strcmp(param->argv[0], "show"))
    {
        ATCMD_LOG_I("CSI[B]: frame control = 0x%x, maks 0x%04x\n", 
             _gstCsibCfg.u16FltFrameType, _gstCsibCfg.u16FltFrameFcmask);
        ATCMD_LOG_I("add1[%02x:%02x:%02x:%02x:%02x:%02x]\n", 
            _gstCsibCfg.au8FltAddr1[0], _gstCsibCfg.au8FltAddr1[1], _gstCsibCfg.au8FltAddr1[2], 
            _gstCsibCfg.au8FltAddr1[3], _gstCsibCfg.au8FltAddr1[4], _gstCsibCfg.au8FltAddr1[5]);
        ATCMD_LOG_I("add2[%02x:%02x:%02x:%02x:%02x:%02x]\n", 
            _gstCsibCfg.au8FltAddr2[0], _gstCsibCfg.au8FltAddr2[1], _gstCsibCfg.au8FltAddr2[2], 
            _gstCsibCfg.au8FltAddr2[3], _gstCsibCfg.au8FltAddr2[4], _gstCsibCfg.au8FltAddr2[5]);
        ATCMD_LOG_I("add3[%02x:%02x:%02x:%02x:%02x:%02x]\n", 
            _gstCsibCfg.au8FltAddr3[0], _gstCsibCfg.au8FltAddr3[1], _gstCsibCfg.au8FltAddr3[2], 
            _gstCsibCfg.au8FltAddr3[3], _gstCsibCfg.au8FltAddr3[4], _gstCsibCfg.au8FltAddr3[5]);
    }
    else if(0 == strcmp(param->argv[0], "filter"))
    {
        if(3 != param->argc)
        {
            goto EXIT_FAIL;
        }
        
        u8 au8Addr[MAC_ADDR_LEN] = {0};
        if(0 == strcmp(param->argv[1], "addr1"))
        {
            _copy_mac_addr(&au8Addr[0], (u8 *)param->argv[2], (const u8 *)":");
            memcpy((void *)&(_gstCsibCfg.au8FltAddr1[0]), (const void *)&au8Addr[0], MAC_ADDR_LEN);
        }
        else if(0 == strcmp(param->argv[1], "addr2"))
        {
            _copy_mac_addr(&au8Addr[0], (u8 *)param->argv[2], (const u8 *)":");
            memcpy((void *)&(_gstCsibCfg.au8FltAddr2[0]), (const void *)&au8Addr[0], MAC_ADDR_LEN);
        }
        else if(0 == strcmp(param->argv[1], "addr3"))
        {
            _copy_mac_addr(&au8Addr[0], (u8 *)param->argv[2], (const u8 *)":");
            memcpy((void *)&(_gstCsibCfg.au8FltAddr3[0]), (const void *)&au8Addr[0], MAC_ADDR_LEN);
        }
        else if(0 == strcmp(param->argv[1], "type"))
        {
            _gstCsibCfg.u16FltFrameType = (u16)strtoul((const char *)param->argv[2], NULL, 16);
        }
        else if(0 == strcmp(param->argv[1], "fcmask"))
        {
            _gstCsibCfg.u16FltFrameFcmask = (u16)strtoul((const char *)param->argv[2], NULL, 16);
        }
        else
        {
            goto EXIT_FAIL;
        }
    }
    else
    {
        goto EXIT_FAIL;
    }
    return ERROR_SUCCESS;

EXIT_FAIL:
    At_CsiConfigB_Show_Usage();
    return ERROR_INVALID_PARAMETER;
}

static void At_CsiConfigGN_Show_Usage(void)
{
    ATCMD_LOG_I("AT+CSI_GN=enable\r\n");
    ATCMD_LOG_I("AT+CSI_GN=latch\r\n");
    ATCMD_LOG_I("AT+CSI_GN=disable\r\n");
    ATCMD_LOG_I("AT+CSI_GN=show\r\n");
    ATCMD_LOG_I("AT+CSI_GN=filter,addr1,XX:XX:XX:XX:XX:XX\r\n");
    ATCMD_LOG_I("AT+CSI_GN=filter,addr2,XX:XX:XX:XX:XX:XX\r\n");
    ATCMD_LOG_I("AT+CSI_GN=filter,addr3,XX:XX:XX:XX:XX:XX\r\n");
    ATCMD_LOG_I("AT+CSI_GN=filter,type,0xXXXX\r\n");
    ATCMD_LOG_I("AT+CSI_GN=filter,fcmask,0xXXXX\r\n");
}

int At_CsiConfigGN(stParam *param)
{
    if (param->argc < 1) {
        goto EXIT_FAIL;
    }

    ATCMD_LOG_I("\r\n");
    
    if(0 == strcmp(param->argv[0], "enable"))
    {
        wifi_csi_irq_enable(FALSE);
        wifi_csi_irq_enable(TRUE);
        wifi_register_csi_isr(_phy_csi_isr, &phy_csi_result);
        wifi_set_csi_config_gn(_gstCsignCfg.au8FltAddr1, 
                               _gstCsignCfg.au8FltAddr2, 
                               _gstCsignCfg.au8FltAddr3,
                               _gstCsignCfg.u16FltFrameType,
                               _gstCsignCfg.u16FltFrameFcmask);
        wifi_enable_csi_gn(TRUE);
    }
    else if(0 == strcmp(param->argv[0], "latch"))
    {
        wifi_enable_csi_gn(TRUE);
    }
    else if(0 == strcmp(param->argv[0], "disable"))
    {
        wifi_enable_csi_gn(FALSE);
        memset((void *)&(_gstCsignCfg.au8FltAddr1[0]), 0, MAC_ADDR_LEN);
        memset((void *)&(_gstCsignCfg.au8FltAddr2[0]), 0, MAC_ADDR_LEN);
        memset((void *)&(_gstCsignCfg.au8FltAddr3[0]), 0, MAC_ADDR_LEN);
        _gstCsignCfg.u16FltFrameType = 0x0000;
        _gstCsignCfg.u16FltFrameFcmask = 0x0000;
    }
    else if(0 == strcmp(param->argv[0], "show"))
    {
        ATCMD_LOG_I("CSI[GN]: frame control = 0x%x, mask = 0x%04x\n", 
            _gstCsignCfg.u16FltFrameType, _gstCsignCfg.u16FltFrameFcmask);
        ATCMD_LOG_I("add1[%02x:%02x:%02x:%02x:%02x:%02x]\n", 
            _gstCsignCfg.au8FltAddr1[0], _gstCsignCfg.au8FltAddr1[1], _gstCsignCfg.au8FltAddr1[2], 
            _gstCsignCfg.au8FltAddr1[3], _gstCsignCfg.au8FltAddr1[4], _gstCsignCfg.au8FltAddr1[5]);
        ATCMD_LOG_I("add2[%02x:%02x:%02x:%02x:%02x:%02x]\n", 
            _gstCsignCfg.au8FltAddr2[0], _gstCsignCfg.au8FltAddr2[1], _gstCsignCfg.au8FltAddr2[2], 
            _gstCsignCfg.au8FltAddr2[3], _gstCsignCfg.au8FltAddr2[4], _gstCsignCfg.au8FltAddr2[5]);
        ATCMD_LOG_I("add3[%02x:%02x:%02x:%02x:%02x:%02x]\n", 
            _gstCsignCfg.au8FltAddr3[0], _gstCsignCfg.au8FltAddr3[1], _gstCsignCfg.au8FltAddr3[2], 
            _gstCsignCfg.au8FltAddr3[3], _gstCsignCfg.au8FltAddr3[4], _gstCsignCfg.au8FltAddr3[5]);
    }
    else if(0 == strcmp(param->argv[0], "filter"))
    {
        if(3 != param->argc)
        {
            goto EXIT_FAIL;
        }
        
        u8 au8Addr[MAC_ADDR_LEN] = {0};
        if(0 == strcmp(param->argv[1], "addr1"))
        {
            _copy_mac_addr(&au8Addr[0], (u8 *)param->argv[2], (const u8 *)":");
            memcpy((void *)&(_gstCsignCfg.au8FltAddr1[0]), (const void *)&au8Addr[0], MAC_ADDR_LEN);
        }
        else if(0 == strcmp(param->argv[1], "addr2"))
        {
            _copy_mac_addr(&au8Addr[0], (u8 *)param->argv[2], (const u8 *)":");
            memcpy((void *)&(_gstCsignCfg.au8FltAddr2[0]), (const void *)&au8Addr[0], MAC_ADDR_LEN);
        }
        else if(0 == strcmp(param->argv[1], "addr3"))
        {
            _copy_mac_addr(&au8Addr[0], (u8 *)param->argv[2], (const u8 *)":");
            memcpy((void *)&(_gstCsignCfg.au8FltAddr3[0]), (const void *)&au8Addr[0], MAC_ADDR_LEN);
        }
        else if(0 == strcmp(param->argv[1], "type"))
        {
            _gstCsignCfg.u16FltFrameType = (u16)strtoul((const char *)param->argv[2], NULL, 16);
        }
        else if(0 == strcmp(param->argv[1], "fcmask"))
        {
            _gstCsignCfg.u16FltFrameFcmask = (u16)strtoul((const char *)param->argv[2], NULL, 16);
        }
        else
        {
            goto EXIT_FAIL;
        }
    }
    else
    {
        goto EXIT_FAIL;
    }
    return ERROR_SUCCESS;

EXIT_FAIL:
    At_CsiConfigGN_Show_Usage();
    return ERROR_INVALID_PARAMETER;

}
#endif // CSI_EN

int At_MacHWQueue(stParam *param)
{
    drv_mac_hw_queue_status();
    showSWTxQueue();
    return ERROR_SUCCESS;
}

int At_PhyHWInfo(stParam *param)
{
    ATCMD_LOG_I("\r\n");
    if(0==strcmp(param->argv[0],"pmu"))
    {
        drv_phy_pmu();
    }
    else if(0==strcmp(param->argv[0],"xtal"))
    {
        drv_phy_xtal();
    }
    else if(0==strcmp(param->argv[0],"sx"))
    {
        drv_phy_sx();
    }
    else if(0==strcmp(param->argv[0],"cali"))
    {
        drv_phy_cali_result();
    }
    else if(0==strcmp(param->argv[0],"txband"))
    {
        drv_phy_txband();
    }
    else if(0==strcmp(param->argv[0],"txgain"))
    {
        drv_phy_txgain();
    }
    else if(0==strcmp(param->argv[0],"dpd"))
    {
        drv_phy_dpd_show();
    }
    else if(0 == strcmp(param->argv[0],"sniffer"))
    {
        if(ERROR_SUCCESS != _At_Phy_Sniffer_Handler(param))
        {
            goto USAGE;
        }
    }
    else
    {
        goto USAGE;
    }

    return ERROR_SUCCESS;

USAGE:
    ATCMD_LOG_I("phy=pmu\r\n");
    ATCMD_LOG_I("phy=xtal\r\n");
    ATCMD_LOG_I("phy=sx\r\n");
    ATCMD_LOG_I("phy=cali\r\n");
    ATCMD_LOG_I("phy=txband\r\n");
    ATCMD_LOG_I("phy=txgain\r\n");
    ATCMD_LOG_I("phy=dpd\r\n");
    _At_Phy_Sniffer_Show_Usage(); //for Phy sniffer
    return ERROR_SUCCESS;
}

int At_MacHWMIB(stParam *param)
{
    ATCMD_LOG_I("\r\n");
    if(param->argc!=1)
    {
        goto USAGE;
    }

    if(0==strcmp(param->argv[0],"on"))
    {
        drv_mac_mib_on();
    }
    else if(0==strcmp(param->argv[0],"off"))
    {
        drv_mac_mib_off();
    }
    else if(0==strcmp(param->argv[0],"reset"))
    {
        drv_mac_mib_reset();
    }
    else if(0==strcmp(param->argv[0],"tx"))
    {
        drv_mac_mib_tx();
    }
    else if(0==strcmp(param->argv[0],"rx"))
    {
        drv_mac_mib_rx();
    }
    else if(0==strcmp(param->argv[0],"txrx"))
    {
        drv_mac_mib_tx();
        drv_mac_mib_rx();
    }
    else
    {
        goto USAGE;
    }

    return ERROR_SUCCESS;

USAGE:
    ATCMD_LOG_I("mib=on\r\n");
    ATCMD_LOG_I("mib=off\r\n");
    ATCMD_LOG_I("mib=reset\r\n");
    ATCMD_LOG_I("mib=tx\r\n");
    ATCMD_LOG_I("mib=rx\r\n");
    ATCMD_LOG_I("mib=txrx\r\n");
    return ERROR_SUCCESS;
}
int At_RCMASK(stParam *param)
{
    u32 rc_mask=0;
    ATCMD_LOG_I("\r\n");
    if (param->argc == 1)
    {
        rc_mask = strtoul(param->argv[0], NULL, 16);
        wifi_set_rate_mask(rc_mask);
    }

    return ERROR_SUCCESS;
}

int At_RCINFO(stParam *param)
{
    u8 wsid;

    ATCMD_LOG_I("\r\n");
    if(param->argc == 1)
    {
        wsid = (u8) ssv6xxx_atoi ((s8*)param->argv[0]);
        rc_get_rc_info(wsid);
    }
    else
    {
         ATCMD_LOG_I("Error !!need wsid\r\n");
    }

    return ERROR_SUCCESS;
}

int At_AMPDUMIB(stParam *param)
{
    ATCMD_LOG_I("\r\n");
#if(ENABLE_AMPDU_SW_MIB==1)
    u8 wsid;
    u8 tid;

    if(3 == param->argc)
    {
        wsid = (u8)ssv6xxx_atoi((s8*)param->argv[1]);
        tid = (u8)ssv6xxx_atoi((s8*)param->argv[2]);
        if(0 == strcmp("reset", (const char*)param->argv[0]))
        {
            printf("\n");
            printf("reset mib\n");
            ampdu_reset_mib(wsid,tid);
            return ERROR_SUCCESS;

        }
        
        if(0 == strcmp("show", (const char*)param->argv[0]))
        {
            printf("\n");
            printf("show mib\n");
            ampdu_show_mib(wsid,tid);
    return ERROR_SUCCESS;
}
        
    }

    ATCMD_LOG_I("Usage:\r\n");
    ATCMD_LOG_I("      ampdu_mib=show,[wsid],[tid]\r\n");
    ATCMD_LOG_I("      ampdu_mib=reset,[wsid],[tid]\r\n");

    return ERROR_SUCCESS;
#else
    return ERROR_NOT_IMPLEMENT;
#endif
}

#if LWIP_MEMP_DEBUG_EN
extern void stats_display(void);
extern void stats_p(void);
extern void stats_m(void);
extern void dump_mem_pool(memp_t type);
extern void dump_mem_pool_pbuf();
extern void dump_active_tcp_pcb(void);
int At_TcpipStatus(stParam *param)
{
    ATCMD_LOG_I("\r\n");
    if(1 > param->argc)
    {
        goto USAGE;
    }
    else if (0 == strcmp(param->argv[0], "p"))
    {
        stats_p();
    }
    else if (0 == strcmp(param->argv[0], "m"))
    {
        stats_m();
    }
    else if(0 == strcmp(param->argv[0], "mp"))
    {
        if((2 > param->argc) || ((MEMP_MAX-1) < atoi(param->argv[1])))
        {
            goto USAGE;
        }
        dump_mem_pool(atoi(param->argv[1]));
    }
    else if(0 == strcmp(param->argv[0], "mpp"))
    {
        dump_mem_pool_pbuf();
    }
    else if(0 == strcmp(param->argv[0],"pcb"))
    {
        dump_active_tcp_pcb();
    }
    else
    {
        goto USAGE;
    }
    return ERROR_SUCCESS;

USAGE:
    ATCMD_LOG_I("tcpstat=p\r\n");
    ATCMD_LOG_I(" - Protocol status\r\n");
    ATCMD_LOG_I("tcpstat=m\r\n");
    ATCMD_LOG_I(" - Memory status\r\n");
    ATCMD_LOG_I("tcpstat=mp,<0~%lu>\r\n", (u32)(MEMP_MAX-1));
    ATCMD_LOG_I(" - Memory pool status\r\n");
    ATCMD_LOG_I("tcpstat=mpp\r\n");
    ATCMD_LOG_I(" - Memory pool pbuf status\r\n");
    ATCMD_LOG_I("tcpstat=pcb\r\n");
    ATCMD_LOG_I(" - PCB status\r\n");
    return ERROR_SUCCESS;
}
#endif

int At_DbgQueueStat(stParam *param)
{
    ATCMD_LOG_I("\r\n");
    if(1 > param->argc)
    {
        goto USAGE;
    }

    if(0 == strcmp(param->argv[0], "mode"))
    {
        if(2 == param->argc)
        {
            return txrx_stat_ctrl(E_TXRX_STAT_CTRL_MODE,
                (0 == (u32)atoi(param->argv[1]))?E_TXRX_STAT_MODE_TX:E_TXRX_STAT_MODE_RX);
        }
        else
        {
            goto USAGE;
        }
    }
    else if(0 == strcmp(param->argv[0], "enable"))
    {
        return txrx_stat_ctrl(E_TXRX_STAT_CTRL_ENABLE, 0);
    }
    else if(0 == strcmp(param->argv[0], "disable"))
    {
        return txrx_stat_ctrl(E_TXRX_STAT_CTRL_DISABLE, 0);
    }
    else if(0 == strcmp(param->argv[0], "show"))
    {
        return txrx_stat_ctrl(E_TXRX_STAT_CTRL_SHOW, 0);
    }
    else
    {
        goto USAGE;
    }

    return 0;

USAGE:
    ATCMD_LOG_I("usage:\n");
    ATCMD_LOG_I("\tdq [mode|enable|show|disable]\n");
    ATCMD_LOG_I("\t- dq mode,<val>\n");
    ATCMD_LOG_I("\t-- <val> -> 0: TX(default), others: RX\n");
    return 0;
}

#if defined(BLE_EN) && (BLE_EN == 1)
extern int ble_enable(u8 mode) ATTRIBUTE_WEAK;
int At_BLEMode(stParam *param)
{
    u32 mode = 0;
    int ret = ERROR_INVALID_PARAMETER;

    if((ble_enable == NULL) || (param->argc != 1))
        goto exit;

    if (param->argc == 1)
    {
        mode = strtoul(param->argv[0], NULL, 10);
        if(mode <= HCI_RAM_MODE && ble_enable)
            ret = ble_enable(mode);
    }

exit:
    return ret;
}
#endif

int At_icmp_baserate(stParam *param)
{
    u32 en=0;
    if (param->argc == 1)
    {
        en = strtoul(param->argv[0], NULL, 16);
        if(en > 0)
            en = 1;
        wifi_set_icmp_1m(en);
    }

    return ERROR_SUCCESS;
}

int At_24g_HT40(stParam *param)
{
    u32 en=0;
    if (param->argc == 1)
    {
        en = strtoul(param->argv[0], NULL, 16);
        if(en > 0)
            en = 1;
        wifi_set_24G_ht40_enable(en);
    }

    return ERROR_SUCCESS;
}

int At_cci_enable(stParam *param)
{
    u32 en=0;
    if (param->argc == 1)
    {
        en = strtoul(param->argv[0], NULL, 16);
        if(en > 0)
            en = 1;
        drv_phy_set_cci_en(en);
    }

    return ERROR_SUCCESS;
}


