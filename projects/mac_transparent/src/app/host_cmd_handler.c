#include <stdio.h>
#include <string.h>
#include "soc_types.h"
#include "osal.h"
#include "wifi_api.h"

#include "wifi_app_common.h"
#include "soc/lowpower/lowpower.h"


OsBufQ  hstcmd_que = NULL;


typedef struct ipconf{
    u32 ipaddr;
    u32 gateway;
    u32 netmask;
    u32 dns;
}ipconf;

void send_wifi_atcmd_rsp_soc_event(u8 *data, u32 datalen)
{
    u32 evtlen = 0;
    ST_WIFI_APP_EVT *evt = NULL;

    if((NULL == data) || (0 == datalen))
    {
        return;
    }
    evtlen = WIFI_APP_EVT_HDR_LEN+datalen;
    evt = (ST_WIFI_APP_EVT *)OS_MemAlloc(evtlen);
    if(NULL == evt)
    {
        printf("[%s] malloc(%u) failed!!\n", __FUNCTION__, evtlen);
        return;
    }
    memset((void *)evt, 0, sizeof(ST_WIFI_APP_EVT));
    evt->evtid = E_WIFI_APP_EVT_TYPE_ATCMD_RSP;
    evt->datalen = datalen;
    memcpy((void *)evt->data, (const void *)data, datalen);
    wifi_send_custom_soc_event((u8 *)evt, evtlen);
    OS_MemFree(evt);
}

void send_wifi_test_rsp_soc_event(u8 *data, u32 datalen)
{
    u32 evtlen = 0;
    ST_WIFI_APP_EVT *evt = NULL;

    evtlen = WIFI_APP_EVT_HDR_LEN+datalen;
    evt = (ST_WIFI_APP_EVT *)OS_MemAlloc(evtlen);
    if(NULL == evt)
    {
        printf("[%s] malloc(%u) failed!!\n", __FUNCTION__, evtlen);
        return;
    }
    memset((void *)evt, 0, sizeof(ST_WIFI_APP_EVT));

    evt->evtid = E_WIFI_APP_EVT_TYPE_TEST_RSP;
    evt->datalen = datalen;
    memcpy((void *)evt->data, (const void *)data, datalen);

    wifi_send_custom_soc_event((u8 *)evt, evtlen);
    OS_MemFree(evt);
}

void send_wifi_lowpower_soc_event(bool exit)
{
    u16 evtlen = 0;
    ST_WIFI_APP_EVT *evt = NULL;

    evtlen = WIFI_APP_EVT_HDR_LEN;
    evt = (ST_WIFI_APP_EVT *)OS_MemAlloc(evtlen);
    if(NULL == evt)
    {
        printf("[%s] malloc(%u) failed!!\n", __FUNCTION__, evtlen);
        return;
    }
    memset((void *)evt, 0, sizeof(ST_WIFI_APP_EVT));
    
    if (exit)
        evt->evtid = E_WIFI_APP_EVT_TYPE_EXIT_LOWPOWER;
    else
        evt->evtid = E_WIFI_APP_EVT_TYPE_ENTER_LOWPOWER;

    evt->datalen = 0;

    wifi_send_custom_soc_event((u8 *)evt, evtlen);
    OS_MemFree(evt);
}

void send_wifi_disconnect_soc_event()
{
    u16 evtlen = 0;
    ST_WIFI_APP_EVT *evt = NULL;

    evtlen = WIFI_APP_EVT_HDR_LEN;
    evt = (ST_WIFI_APP_EVT *)OS_MemAlloc(evtlen);
    if(NULL == evt)
    {
        printf("[%s] malloc(%u) failed!!\n", __FUNCTION__, evtlen);
        return;
    }
    memset((void *)evt, 0, sizeof(ST_WIFI_APP_EVT));

    evt->evtid = E_WIFI_APP_EVT_TYPE_WIFI_DISCONNECT;
    evt->datalen = 0;

    wifi_send_custom_soc_event((u8 *)evt, evtlen);
    OS_MemFree(evt);
}

void send_wifi_connect_soc_event(ipconf *ip)
{
    u16 evtlen = 0;
    ST_WIFI_APP_EVT *evt = NULL;

    evtlen = sizeof(ipconf) + WIFI_APP_EVT_HDR_LEN;
    evt = (ST_WIFI_APP_EVT *)OS_MemAlloc(evtlen);
    if(NULL == evt)
    {
        printf("[%s] malloc(%u) failed!!\n", __FUNCTION__, evtlen);
        return;
    }
    memset((void *)evt, 0, sizeof(ST_WIFI_APP_EVT));

    evt->evtid = E_WIFI_APP_EVT_TYPE_WIFI_CONNECT;
    evt->datalen = sizeof(ipconf);
    memcpy(evt->data, ip, sizeof(ipconf));

    wifi_send_custom_soc_event((u8 *)evt, evtlen);
    OS_MemFree(evt);
}

void wifirspcbfunc(WIFI_RSP *msg)
{
    u8 dhcpen;
    u8 mac[6];
    u8 ipv4[4];

    uip_ip4addr_t ipaddr, submask, gateway, dnsserver;
    s8 ret;
    char ipstr[16];

    if(msg->wifistatus == 1)
    {
        printf("wifi connected:%d\n", msg->id);
        if(msg->id == 0)
        {
            get_if_config_2(IF0_NAME, &dhcpen, (u32 *)&ipaddr, (u32 *)&submask, (u32 *)&gateway, (u32 *)&dnsserver, mac, 6);
        }
        else
        {
            get_if_config_2(IF1_NAME, &dhcpen, (u32 *)&ipaddr, (u32 *)&submask, (u32 *)&gateway, (u32 *)&dnsserver, mac, 6);
        }
        printf("mac             - %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        printf("ip addr         - %d.%d.%d.%d\n", ipaddr.u8[0], ipaddr.u8[1], ipaddr.u8[2], ipaddr.u8[3]);
        printf("netmask         - %d.%d.%d.%d\n", submask.u8[0], submask.u8[1], submask.u8[2], submask.u8[3]);
        printf("default gateway - %d.%d.%d.%d\n", gateway.u8[0], gateway.u8[1], gateway.u8[2], gateway.u8[3]);
        printf("DNS server      - %d.%d.%d.%d\n", dnsserver.u8[0], dnsserver.u8[1], dnsserver.u8[2], dnsserver.u8[3]);
        
        ipconf ip;
        ip.ipaddr = ipaddr.u32;
        ip.gateway = gateway.u32;
        ip.netmask = submask.u32;
        ip.dns = dnsserver.u32;
        send_wifi_connect_soc_event(&ip);
    }
    else
    {
        printf("!!!!!!wifi disconnected:%d\n", msg->id);
        send_wifi_disconnect_soc_event();
    }
}

void send_aplist_soc_event(TAG_AP_INFO *ap_list, u8 apcnt)
{
    u16 evtlen = WIFI_APP_EVT_HDR_LEN;
    u8 *wp, i;
    ST_WIFI_APP_EVT *evt;

    for(i = 0; i < apcnt; i++)
        evtlen += (1 + 6 + ap_list[i].name_len);
    
    printf("evtlen:%d\n", evtlen);
    evt = (ST_WIFI_APP_EVT *)OS_MemAlloc(evtlen);
    if(NULL == evt)
    {
        printf("[%s] malloc(%u) failed!!\n", __FUNCTION__, evtlen);
        return;
    }

    evt->evtid = E_WIFI_APP_EVT_TYPE_APLIST;
    evt->datalen = evtlen-WIFI_APP_EVT_HDR_LEN;
    wp = evt->data;
    for(i = 0; i < apcnt; i++)
    {
        *wp = ap_list[i].name_len;
        wp++;
        memcpy(wp, ap_list[i].name, ap_list[i].name_len);
        wp += ap_list[i].name_len;
        memcpy(wp, ap_list[i].mac, 6);
        wp += 6;
    }
    wifi_send_custom_soc_event((u8 *)evt, evtlen);
    OS_MemFree(evt);
}

void scan_cb()
{
    u8 apcnt = get_ap_lsit_total_num();
    TAG_AP_INFO *ap_list = NULL;
    
    printf("\nCount:%d\n", apcnt);
    if(0 != apcnt)
    {
        ap_list = (TAG_AP_INFO *)OS_MemAlloc(apcnt * sizeof(TAG_AP_INFO));
         if(NULL == ap_list)
        {
            printf("[%s] malloc(%u) failed!!\n", __FUNCTION__, apcnt * sizeof(TAG_AP_INFO));
            return;
        }
        get_ap_list(ap_list, &apcnt);
    }
    
    send_aplist_soc_event(ap_list, apcnt);
    if(NULL != ap_list)
    {
        OS_MemFree(ap_list);
    }
}

extern int At_Parser (char *buff, int len);
static bool _host_cmd_atcmd_handler(u8 *data, u32 datalen)
{
    bool ret = FALSE; //Need to send response.

    //Here datalen-1 because this function will do len++ for null character.
    if(0 == At_Parser((char *)data, (int)(datalen-1)))
    {
        ret = TRUE;
    }

    return ret;
}

void host_custom_cmd_handler( void *args )
{
    OS_STATUS ret;
    ST_WIFI_APP_CMD *msg;
    u8 mode;
    //char param[256];
    u8 ssid[33], passphrase[65];
    u8 ssidlen, passlen, *dat;
    int i;

    wifi_register_custom_cmd_queue(&hstcmd_que);
    while(1)
    {
        ret = OS_BufQPop(hstcmd_que, (void *)&msg, portMAX_DELAY);
        printf("cmd:%d len:%d\n", msg->cmdid, msg->datalen);
        dat = msg->data;
        if(msg->cmdid == E_WIFI_APP_CMD_TYPE_SCAN)
        {
            scan_AP(scan_cb);
        }
        else if(msg->cmdid == E_WIFI_APP_CMD_TYPE_JOIN)
        {
            passlen = 0;
            ssidlen = 0;
            for(i = 0; i < msg->datalen; i++)
            {
                if(dat[i] == ',')
                {
                    ssidlen = i;
                    memcpy(ssid, dat, ssidlen);
                    ssid[ssidlen] = 0;
                    if(ssidlen != msg->datalen - 1)
                    {
                        passlen = msg->datalen - ssidlen - 1;
                        memcpy(passphrase, dat + i + 1, passlen);
                        passphrase[passlen] = 0;
                    }
                    break;
                }
            }

            if(i == msg->datalen)
            {
                ssidlen = msg->datalen;
                memcpy(ssid, dat, ssidlen);
                ssid[ssidlen] = 0;
            }

            printf("ssid:%s\n", ssid);
            if(passlen)
                printf("pswd:%s\n", passphrase);
            wifi_connect_active (ssid, ssidlen, passphrase, passlen, wifirspcbfunc);
        }
        else if(msg->cmdid == E_WIFI_APP_CMD_TYPE_LEAVE)
        {
            wifi_disconnect(NULL);
        }
        else if(msg->cmdid == E_WIFI_APP_CMD_TYPE_ENTER_LOWPOWER)
        {
            lowpower_mode(E_LOW_POWER_SLEEP);
            set_power_mode(1, DUT_STA);
            send_wifi_lowpower_soc_event(false);
        }
        else if(msg->cmdid == E_WIFI_APP_CMD_TYPE_EXIT_LOWPOWER)
        {
            lowpower_mode(E_LOW_POWER_ACTIVE);
            set_power_mode(0, DUT_STA);
            send_wifi_lowpower_soc_event(true);
        }
        else if(msg->cmdid == E_WIFI_APP_CMD_TYPE_TEST_REQ)
        {
            send_wifi_test_rsp_soc_event((u8 *)dat, (u32)msg->datalen);
        }
        else if(msg->cmdid == E_WIFI_APP_CMD_TYPE_ATCMD)
        {
            extern int at_cmd_log_init(void);
            extern int at_cmd_log_deinit(void);
            extern int at_cmd_log_enable(void);
            extern int at_cmd_log_disable(void);
            extern int at_cmd_log_buf_get(char **buf, unsigned int *buflen);
            extern int at_cmd_log_write(const char* fmt, ...);
            u8 *pu8CmdLogBuf = NULL;
            u32 u32CmdLogBufLen = 0;

            at_cmd_log_init();
            at_cmd_log_enable();
            _host_cmd_atcmd_handler((u8 *)dat, (u32)msg->datalen);
            at_cmd_log_disable();
            if(0 == at_cmd_log_buf_get((char **)&pu8CmdLogBuf, (unsigned int *)&u32CmdLogBufLen))
            {
                send_wifi_atcmd_rsp_soc_event(pu8CmdLogBuf, u32CmdLogBufLen);
            }
            at_cmd_log_deinit();
        }
        OS_MemFree(msg);
    }

    OS_BufQDelete(hstcmd_que);
    OS_TaskDelete(NULL);
}

int host_cmd_proc_start()
{
    if(OS_BufQCreate(&hstcmd_que, 4, ( unsigned portBASE_TYPE ) sizeof(void *)) != OS_SUCCESS)
        return -1;
    
    if(OS_TaskCreate(host_custom_cmd_handler, "host_cmd_handler", 512, NULL, OS_TASK_MIDDLE_PRIO, NULL) == false)
        return -1;

    return 0;
}

