
/*************************************

    Package: RTlink main
    Version: 1.0
    
    Copyright (C) 2018 RangerTek Inc. All Rights Reserved.
    
*************************************/

#include "rtlink_main.h"
#include "smart_config.h"

static RTResult result;
static u8 timeInterval = 150;
static OsTimer timer;
static int start = 0;
static int starTimer = 0, endTimer = 0;
#ifdef SUPPORT_AES
static uint8 secretKey[KEY_STR_MAX_LEN];    /**< security key storage*/
#endif
static void RTWifiCb(
    WIFI_RSP *msg)
{
    log_i(PRINT_RTLINK_TAG, "=========\n");
    log_i(PRINT_RTLINK_TAG, "rtlinkwificbfunc wifistatus = %d\n", msg->wifistatus);
    
    uint8_t dhcpen;
    u8 mac[6];
    uip_ipaddr_t ipaddr, submask, gateway, dnsserver;

    if(msg->wifistatus == 1)
    {
        if(msg->id == 0)
            get_if_config_2("et0", &dhcpen, (u32*)&ipaddr, (u32*)&submask, (u32*)&gateway, (u32*)&dnsserver, mac, 6);
        else
            get_if_config_2("et1", &dhcpen, (u32*)&ipaddr, (u32*)&submask, (u32*)&gateway, (u32*)&dnsserver, mac, 6);
        log_i(PRINT_RTLINK_TAG, "Wifi Connect\n");
        log_i(PRINT_RTLINK_TAG, "STA%d:\n", msg->id);
        log_i(PRINT_RTLINK_TAG, "mac addr        - %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        log_i(PRINT_RTLINK_TAG, "ip addr         - %d.%d.%d.%d\n", ipaddr.u8[0], ipaddr.u8[1], ipaddr.u8[2], ipaddr.u8[3]);
        log_i(PRINT_RTLINK_TAG, "netmask         - %d.%d.%d.%d\n", submask.u8[0], submask.u8[1], submask.u8[2], submask.u8[3]);
        log_i(PRINT_RTLINK_TAG, "default gateway - %d.%d.%d.%d\n", gateway.u8[0], gateway.u8[1], gateway.u8[2], gateway.u8[3]);
        log_i(PRINT_RTLINK_TAG, "DNS server      - %d.%d.%d.%d\n", dnsserver.u8[0], dnsserver.u8[1], dnsserver.u8[2], dnsserver.u8[3]);
    }
    else
    {
        log_e(PRINT_RTLINK_TAG, "Wifi Disconnect\n");
    }
}

static void RTScanCb(
    void *data)
{
    int ret = 0;

    ret = set_wifi_config(result.ssid, result.ssidLen, result.pwd, result.pwdLen, NULL, 0);

    if(ret == 0)
        ret = wifi_connect(RTWifiCb);
}

static void RTConnectAp(
    RTResult *pResult)
{
    int ret = 0;
    memset(&result, 0, sizeof(result));
    memcpy(&result, pResult, sizeof(result));
    DUT_wifi_start(DUT_STA);
    scan_AP(RTScanCb);
}

static void RTGetResult(
    RTResult result)
{
    int ret = 0;
    endTimer  = OS_GetSysTick();
    log_i(PRINT_RTLINK_TAG, "==============================\n");
    log_i(PRINT_RTLINK_TAG, "ssid %s, len %d\n", result.ssid, result.ssidLen);
    log_i(PRINT_RTLINK_TAG, "pswd %s, len %d\n", result.pwd, result.pwdLen);
    log_i(PRINT_RTLINK_TAG, "==============================\n");
    log_i(PRINT_RTLINK_TAG, "total time: %d ms\n", endTimer - starTimer);
    RTStop();
    #if 1//reslease customer, it can be enable
    RTConnectAp(&result);
    #else
    #include "wdt/drv_wdt.h"
    drv_wdt_init();
    drv_wdt_enable(SYS_WDT, 100);
    #endif
}
#ifdef SUPPORT_AES
static uint8 DecDataCallback(
    uint8 *In, uint8 in_len, uint8 *out)
{
    rtlink_aes_context ctx;
    uint8 paddingLen = 0;
    uint8 ssidOffset = 0;
    uint8 ssidLen = 0;
    int i = 0;
    int loop = in_len /16;
    rtlink_aes_setkey_dec( &ctx, secretKey, 128);
    for(i = 0; i < loop; i++)
        rtlink_aes_crypt_ecb( &ctx, RTLINK_AES_DECRYPT, In + (i * 16), out + (i * 16));
    
    if(out[0] <= PSW_MAX_LEN)
    {
        ssidOffset = out[0] + 1;
        ssidLen = out[ssidOffset];
        if(ssidLen <= SSID_MAX_LEN)
        {
            paddingLen = in_len - (ssidOffset +  ssidLen + 1);
            if(paddingLen <= 16)
            {
                return in_len - paddingLen;
            } else
            {
                log_i(PRINT_RTLINK_TAG, "aes dec fail: paddingLen:%d(%d = %d = %d)\n", paddingLen, in_len, ssidOffset, ssidLen);
                for(i = 0; i < in_len; i++)
                    log_i(PRINT_RTLINK_TAG, "%02d ", out[i]);
                return RTStatus_Params_Error;
            }
        } else
        {
            log_i(PRINT_RTLINK_TAG, "aes dec fail: ssidLen:%d\n", ssidLen);
            return RTStatus_Params_Error;
        }
    } else
    {
        log_i(PRINT_RTLINK_TAG, "aes dec fail: password len:%d\n", out[0]);
        return RTStatus_Params_Error;
    }
}
#endif
static void RTSwitchChCallback(
    u8 ch, u8 type)
{
    wifi_set_channel((u32)ch, (u32)type);
}

static void RTChangeHandler(
    void)
{
    RTSmntCycleCall();
    OS_TimerStart(timer);
}

static int RTInitTimer(
    void)
{
    if( OS_TimerCreate(&timer, timeInterval, (u8)FALSE, NULL, (OsTimerHandler)RTChangeHandler) == OS_FAILED)
        return OS_FAILED;

    OS_TimerStart(timer);
    return OS_SUCCESS;
}

static void RTSnifferCb(
    packetinfo *packet)
{
    Header80211 hdr = (Header80211)packet->data;
    RTSmntDatahandler(hdr, packet->len);
}

void RTInit(
    u8 *key)
{
    RTParams params;

    if (start)
        return;

    attach_sniffer_cb(RECV_DATA_BCN, &RTSnifferCb, 1024);
    //set_sniffer_config_2(RECV_DATA_BCN, &RTSnifferCb, 600, 65, NULL);
    start_sniffer_mode();

    RTInitTimer();
#ifdef SUPPORT_AES
    params.decCallback = &DecDataCallback;
    memcpy(secretKey, key, 16);
#else
    params.decCallback = NULL;
#endif
    params.switchChCallback = &RTSwitchChCallback;
    params.resultCallback = &RTGetResult;
    RTSmntInit(params);
    start = 1;
    starTimer = OS_GetSysTick();
}

void RTStop(
    void)
{
    if (start) 
    {
        if (timer) 
        {
            OS_TimerStop(timer);
            timer = NULL;
        }
        deattach_sniffer_cb();
        stop_sniffer_mode();
        RTSmntRelease();
        start = 0;
    }
}
