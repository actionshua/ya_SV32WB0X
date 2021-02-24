
//#include "types.h"
#include "soc_types.h"
#include "atcmd.h"
#include "error.h"
#include "mdns.h"
#include "dns_sd.h"
#include "wificonf.h"
#include "lwip/def.h"

#include "lwip/autoip.h"
#include "wifinetstack.h"
#include "netstack.h"
#include "wifi_api.h"
#include <stdio.h>
#include <string.h>
#include "httpd.h" 
///#include "HTTPServer.h"
//#include "drv_spimst.h"

#define ServiceType "_testupdate._tcp."
#define ServiceDomain "local"
#define ServicePort 5123
#define NewServiceName "New - Bonjour Service Name"
#define ReServiceName "Re - Bonjour Service Name"
#define STATIC_IP "192.168.1.1"
#define STATIC_MASK "255.255.255.0"
#define STATIC_GW "192.168.1.1"

static DNSServiceRef client;
extern int adk_main();

static u8 SSID[33] = "BCT";
static u8 PASS[65] = "";
u8 auto_ip_get = 0;

/*Static IP ADDRESS*/
#define IP_ADDR0   0
#define IP_ADDR1   0
#define IP_ADDR2   0
#define IP_ADDR3   0

/*NETMASK*/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/*Gateway Address*/
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   1
#define GW_ADDR3   1

typedef enum 
{ 
    DHCP_START=0,
    DHCP_WAIT_ADDRESS,
    DHCP_ADDRESS_ASSIGNED,
    DHCP_RELEASE_IP,
    DHCP_STOP,
    DHCP_TIMEOUT
} DHCP_State_TypeDef;

int RemoveBonjourService()
{
    int err = -1;
    DNSServiceRefDeallocate(client);
    client = NULL;
    err = 0;
    return err;
}

int RegisterBonjourService(char* servicename, char* type, unsigned short port)
{
    DNSServiceErrorType err;
    
    ATCMD_LOG_I("Register Bonjour Service: %s type: %s port: %d\n", servicename, type, port);
    // Register Bonjour Service
    err = DNSServiceRegister(&client,                      // DNSServiceRef
            0,                                         // DNSServiceFlags
            kDNSServiceInterfaceIndexAny,                  // interface index
            servicename, type,                             // service name
            "local",                                 // domain
            NULL,                                          // host
            htons(port),                            // port
            0,                // txt record length
            NULL,              // txt record pointer
            NULL,                                          // callback
            NULL);                                         // context
    if (!err) {
        ATCMD_LOG_I("Register Bonjour Service successfully!\n");
    } else {
        ATCMD_LOG_I("Register Bonjour Service failed.\n");
    }
    
    return err;
}

int ReNameBonjourService(char* servicename, char* type, unsigned short port)
{
    int err = 0;
    err = RemoveBonjourService();
    if (err) {
        ATCMD_LOG_I("Remove Bonjour Service failed\n");
    } else {
        err = RegisterBonjourService(servicename, type, port);
        if (err) {
            ATCMD_LOG_I("Register Bonjour Service failed\n");
        }
    }
    return err;
}

void homekit_mdns_reg()
{
    RegisterBonjourService(NewServiceName, ServiceType, ServicePort);
    OS_TaskDelete(NULL);
}

void homekit_mdns_start()
{
    mdnsd_start();
    OS_TaskDelete(NULL);
}

extern int dnssd_main(void);

void homekit_mdns_sd()
{
    ATCMD_LOG_I("=====dnssd_main=====\n");
    dnssd_main();
    //OS_TaskDelete(NULL);
}

int cli_mdns_desd()
{
    dns_sd_stop();
    return 0;
}

int cli_mdns_sd()
{
    if (OS_TaskCreate(homekit_mdns_sd, "homekit_mdns_sd", 2048, NULL, OS_TASK_PRIO3, NULL ) != true)
    {
        //ATCMD_LOG_I("mdns start create fail\n");
        ATCMD_LOG_I("[%d] %s task create fail\n", __LINE__, __func__);
        return -1;
    }
    
    return 0;
}

void cli_mdns_reg(char* servicename, char* type, unsigned short port)
{
    //ATCMD_LOG_I("--- mdns_reg_cli task begin ---\n");
    if (OS_TaskCreate( homekit_mdns_reg, "mdns_reg", 2048, NULL, OS_TASK_PRIO3, NULL ) != 1)
    {
        ATCMD_LOG_I("mdns_reg task create fail\n");
    }
}

int cli_mdns_start()
{
    if (OS_TaskCreate(homekit_mdns_start, "mdns_start", 2048, NULL, OS_TASK_PRIO3, NULL ) != true)
    {
        //ATCMD_LOG_I("mdns start create fail\n");
        ATCMD_LOG_I("[%d] %s task create fail\n", __LINE__, __func__);
        return -1;
    }
    return 0;
}

void ip_addr_setting(uip_ip4addr_t *ip, char *para)
{
    //uint32_t ip[4];
    char *ptr, *head, *tail;
    int i;

    ptr = para;
    
    for(i = 0; i < 4; i ++) {
        head = ptr;
        while(*ptr && *ptr != '.') ptr ++;
        tail = ptr ++;
        *tail = 0;
        ip->u8[i] = atoi(head);
    }
    //IP4_ADDR(ip, ip[0], ip[1], ip[2], ip[3]);
}

void interface_get()
{
    u32 ip, gw, mask;
    netdev_getipv4info("et0", &ip, &gw, &mask);
    ATCMD_LOG_I("\nGet IP: %d.%d.%d.%d\n", (int)((ip >> 0) & 0xff), (int)((ip >> 8) & 0xff), (int)((ip >> 16) & 0xff), (int)((ip >> 24) & 0xff));
    ATCMD_LOG_I("GW: %d.%d.%d.%d\n", (int)((gw >> 0) & 0xff), (int)((gw >> 8) & 0xff), (int)((gw >> 16) & 0xff), (int)((gw >> 24) & 0xff));
    ATCMD_LOG_I("Mask: %d.%d.%d.%d\n", (int)((mask >> 0) & 0xff), (int)((mask >> 8) & 0xff), (int)((mask >> 16) & 0xff), (int)((mask >> 24) & 0xff));
}

void interface_setting(stParam *param)
{
    if((param->argc == 3) || (param->argc == 4)) {
        uip_ip4addr_t	local_ip_addr;
        uip_ip4addr_t	net_mask;
        uip_ip4addr_t	gateway_ip_addr;
        ip_addr_setting(&local_ip_addr, param->argv[1]);
        ip_addr_setting(&net_mask, param->argv[2]);
        if(param->argc == 4) {
            ip_addr_setting(&gateway_ip_addr, param->argv[3]);
        } else {
            //memset(gateway_ip_addr, 0, sizeof(uip_ip4addr_t));
        }
        netdev_setipv4info(NULL, *((u32 *)&local_ip_addr), *((u32 *)&net_mask), *((u32 *)&gateway_ip_addr));
        interface_get();
    } else {
        ATCMD_LOG_I("Usage: interface set IP NETMASK [GATEWAY]\n");
    }
}

void static_ip_setting()
{
    u32 ip, gw, mask;
    uip_ip4addr_t	local_ip_addr;
    uip_ip4addr_t	net_mask;
    uip_ip4addr_t	gateway_ip_addr;
    ip_addr_setting(&local_ip_addr, STATIC_IP);
    ip_addr_setting(&net_mask, STATIC_MASK);
    ip_addr_setting(&gateway_ip_addr, STATIC_GW);
    netdev_setipv4info(NULL, *((u32 *)&local_ip_addr), *((u32 *)&net_mask), *(u32 *)(&gateway_ip_addr));
    interface_get();
}
#if LWIP_AUTOIP
void lwip_autoip_set()
{
    struct netif * pnetif = NULL;
    pnetif = netif_find(IF0_NAME);
    if (!pnetif) {
        ATCMD_LOG_I("netif find err\n");
    }
    autoip_start(pnetif);
    while((pnetif->autoip->state == AUTOIP_STATE_PROBING) || 
               (pnetif->autoip->state == AUTOIP_STATE_ANNOUNCING)) {
        vTaskDelay(1000);
    }
    uint32_t ip =  pnetif->ip_addr.addr;
    if(ip == 0) {
        ATCMD_LOG_I("AUTOIP timeout\n");
        static_ip_setting();
    } else {
    ATCMD_LOG_I("\nLink-local address: %d.%d.%d.%d\n", (int)((ip >> 0) & 0xff), (int)((ip >> 8) & 0xff), (int)((ip >> 16) & 0xff), (int)((ip >> 24) & 0xff));
    }
}
#endif
void HomeKitNetworkConnection(void)
{
    static_ip_setting();
#if LWIP_AUTOIP
    lwip_autoip_set();
#endif
}

#define APSSID "xxxx"
#define APPASSPHRASE "xxxx"

void wifirspcbfuncTest(WIFI_RSP *msg)
{
    u8 dhcpen;
    u8 mac[6];
    u8 ipv4[4];

    uip_ipaddr_t ipaddr, submask, gateway, dnsserver;
    s8 ret;

    if(msg->wifistatus == 1)
    {
        ATCMD_LOG_I("wifi connected\n");
#ifdef TCPIPSTACK_EN
        get_if_config(&dhcpen, (u32 *)&ipaddr, (u32 *)&submask, (u32 *)&gateway, (u32 *)&dnsserver);
//        get_local_mac(mac, 6);
//        ATCMD_LOG_I("mac             - %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        ATCMD_LOG_I("ip addr         - %d.%d.%d.%d\n", ipaddr.u8[0], ipaddr.u8[1], ipaddr.u8[2], ipaddr.u8[3]);
        ATCMD_LOG_I("netmask         - %d.%d.%d.%d\n", submask.u8[0], submask.u8[1], submask.u8[2], submask.u8[3]);
        ATCMD_LOG_I("default gateway - %d.%d.%d.%d\n", gateway.u8[0], gateway.u8[1], gateway.u8[2], gateway.u8[3]);
        ATCMD_LOG_I("DNS server      - %d.%d.%d.%d\n", dnsserver.u8[0], dnsserver.u8[1], dnsserver.u8[2], dnsserver.u8[3]);
#endif
    }
}

void scanAPcbfuncTest()
{
    u8 i;
    
    ATCMD_LOG_I("\nCount:%d\n", get_ap_lsit_total_num());
    for(i = 0; i < get_ap_lsit_total_num(); i++)
    {
        ATCMD_LOG_I("%2d - name:%32s, rssi:%2d CH:%2d mac:%02x-%02x-%02x-%02x-%02x-%02x\n", i, ap_list[i].name, ap_list[i].rssi, ap_list[i].channel
            , ap_list[i].mac[0], ap_list[i].mac[1], ap_list[i].mac[2], ap_list[i].mac[3], ap_list[i].mac[4], ap_list[i].mac[5]);
    }
    ATCMD_LOG_I("end\n");
    
    if(set_wifi_config((u8 *)APSSID, (u8)strlen(APSSID), (u8 *)APPASSPHRASE, (u8)strlen(APPASSPHRASE), NULL, 0) == 0)
        wifi_connect(wifirspcbfuncTest);
    else
    {
        ATCMD_LOG_I("%s\n",APSSID);
    }
}

int At_Init (stParam *param)
{
#if 0
    PBUF_Init();
    NETSTACK_RADIO.init();    
    drv_sec_init();
    drv_phy_channel_change(2, NL80211_CHAN_HT20);
    netstack_init(NULL);
    ATCMD_LOG_I("init end 2\n");
#else
    //PBUF_Init();
    //NETSTACK_RADIO.init();    
    //drv_sec_init();
    //netstack_init(NULL);
    //ATCMD_LOG_I("init end 2\n");
    //DUT_wifi_start(DUT_NONE);
    //drv_spi_mst_init(10000000, 0, 0);
    return 0;
#endif
}

int At_Wifi (stParam *param)
{

    DUT_wifi_start(DUT_STA);
    //OS_MsDelay(500);
    if (get_DUT_wifi_mode() == DUT_STA          || 
        get_DUT_wifi_mode() == DUT_CONCURRENT   ||
        get_DUT_wifi_mode() == DUT_REPEATER)
    {
        scan_AP(scanAPcbfuncTest);
    }
    return ERROR_SUCCESS;
}
#if 0
void httpdrCallback( HTTPHeader_t *inHeader, bool stopped, void *callbackContext );

void httpdrCallback( HTTPHeader_t *inHeader, bool stopped, void *callbackContext )
{
    ATCMD_LOG_I("httpdrCallback\n");
}

int At_HTTPD (stParam *param)
{
    HTTPServer_t    *httpServer;
    httpServer = OS_MemAlloc( sizeof( HTTPServer_t ) );
    HTTPServerCreate( "WACPreConfigListener",     // Friendly name of server
                            httpdrCallback,  // Callback function
                            NULL,           // Reference to the WACContext_t
                            httpServer );    // Reference to alloc'd HTTPServer_t

    HTTPServerStart( httpServer );
    return ERROR_SUCCESS;
}

int At_MFi (stParam *param)
{
    uint8_t             i;
    uint8_t             digest[ 20 ];
    uint8_t *           signaturePtr = NULL;
    size_t              signatureLen;
    uint8_t *           certificatePtr = NULL;
    size_t              certificateLen;
    PlatformMFiAuthInitialize();
    ATCMD_LOG_I("OS_MsDelay before\n");
    OS_MsDelay(1);
    ATCMD_LOG_I("OS_MsDelay after\n");
    for(i = 0; i < 20; i++)
        digest[i] = i;
    ATCMD_LOG_I("PlatformMFiAuthCreateSignature\n");
    PlatformMFiAuthCreateSignature( digest, sizeof( digest ), &signaturePtr, &signatureLen );
    PlatformMFiAuthCopyCertificate( &certificatePtr, &certificateLen );
    return ERROR_SUCCESS;
}
#endif

void atwificbfunc_test(WIFI_RSP *msg)
{
#if 1
    u8 dhcpen;
    uip_ipaddr_t ipaddr, submask, gateway, dnsserver;

    if(msg->wifistatus == 1)
    {
        get_if_config(&dhcpen, (u32 *)&ipaddr, (u32 *)&submask, (u32 *)&gateway, (u32 *)&dnsserver);
        ATCMD_LOG_I("ip addr         - %d.%d.%d.%d\n", ipaddr.u8[0], ipaddr.u8[1], ipaddr.u8[2], ipaddr.u8[3]);
        ATCMD_LOG_I("netmask         - %d.%d.%d.%d\n", submask.u8[0], submask.u8[1], submask.u8[2], submask.u8[3]);
        ATCMD_LOG_I("default gateway - %d.%d.%d.%d\n", gateway.u8[0], gateway.u8[1], gateway.u8[2], gateway.u8[3]);
        ATCMD_LOG_I("DNS server      - %d.%d.%d.%d\n", dnsserver.u8[0], dnsserver.u8[1], dnsserver.u8[2], dnsserver.u8[3]);
        ATCMD_LOG_I("-- wifi_connect_ok = 0 --\n");

        if(auto_ip_get == 0) {
            auto_ip_get = 1;
            cli_mdns_start();
            OS_MsDelay(1000);
            cli_mdns_sd();
            httpd_init();
            httpd_start(NULL);
        }
    }
    else
    {
        ATCMD_LOG_I("disconnect OK\n");
    }
#endif
}

void scan_cbfunc_test()
{
    u8 i;

    //ATCMD_LOG_I("\nCount:%d\n", getAvailableIndex());
    for(i = 0; i < get_ap_lsit_total_num(); i++)
    {
        ATCMD_LOG_I("%2d - name:%32s, rssi:-%2d CH:%2d mac:%02x-%02x-%02x-%02x-%02x-%02x\n", i, ap_list[i].name, ap_list[i].rssi, ap_list[i].channel
            , ap_list[i].mac[0], ap_list[i].mac[1], ap_list[i].mac[2], ap_list[i].mac[3], ap_list[i].mac[4], ap_list[i].mac[5]);
    }
    ATCMD_LOG_I("end\n");
    set_wifi_config((u8 *)SSID, (u8)strlen((const char *)SSID), (u8 *)PASS, (u8)strlen((const char *)PASS), NULL, 0) ;
    wifi_connect(atwificbfunc_test);
    //OS_TaskCreate(dhcp_hk_test, "dhcp_test", 512, NULL, OS_TASK_LOW_PRIO, NULL);
}

void test_conn(void *pdata)
{
    DUT_wifi_start(DUT_STA);
    scan_AP(scan_cbfunc_test);
    OS_MsDelay(500);

    OS_TaskDelete(NULL);
}

int At_Soft (stParam *param)
{	
    DUT_wifi_start(DUT_AP);
    //softap_start();
    return ERROR_SUCCESS;
}


int At_Wac (stParam *param)
{	
#if 1
    if (OS_TaskCreate((OsTask)adk_main, "adk_main", 1600, NULL, OS_TASK_PRIO3, NULL ) != true)
    {
        //ATCMD_LOG_I("mdns start create fail\n");
        ATCMD_LOG_I("[%d] %s task create fail\n", __LINE__, __func__);
        return -1;
    }
#endif
    return ERROR_SUCCESS;
}

int At_Mdns (stParam *param)
{	
    //ATCMD_LOG_I("At_Mdns\n");
    if (param->argc < 1) {
        return ERROR_INVALID_PARAMETER;
    }
    
    if(strcmp(param->argv[0], "init") == 0) {
        cli_mdns_start();
    } else if(strcmp(param->argv[0], "deinit") == 0) {
        mdnsd_stop();
    } else if(strcmp(param->argv[0], "sd") == 0) {
        cli_mdns_sd();
    } else if(strcmp(param->argv[0], "desd") == 0) {
        cli_mdns_desd();
    } else if(strcmp(param->argv[0], "reg") == 0) {
        if (param->argc != 1 && param->argc != 4) {
            return ERROR_INVALID_PARAMETER;
        }
        if(param->argc == 1)
            cli_mdns_reg(NewServiceName, ServiceType, ServicePort);
        else
            cli_mdns_reg(param->argv[1], param->argv[2], atoi(param->argv[3]));
    } else if(strcmp(param->argv[0], "dereg") == 0) {
        RemoveBonjourService();
    } else if(strcmp(param->argv[0], "reflash") == 0) {
        mdns_update_interface();
    } else if(strcmp(param->argv[0], "rename") == 0) {
        if (param->argc != 1 &&  param->argc != 4) {
            return ERROR_INVALID_PARAMETER;
        }
        if(param->argc == 1)
            ReNameBonjourService(ReServiceName, ServiceType, ServicePort);
        else
            ReNameBonjourService(param->argv[1], param->argv[2], atoi(param->argv[3]));
    } 
    
    return ERROR_SUCCESS;
}

int At_Interface(stParam *param)
{	
    //ATCMD_LOG_I("At_Interface\n");
    if (param->argc < 1) {
        return ERROR_INVALID_PARAMETER;
    }
    
    dhcpc_wrapper_set(NULL, false);
    
    if(strcmp(param->argv[0], "set") == 0) {
        interface_setting(param);
    } else if(strcmp(param->argv[0], "info") == 0) {
        interface_get();
    } else if(strcmp(param->argv[0], "disconnect") == 0) {
        wifi_disconnect(NULL);
    } else if(strcmp(param->argv[0], "reconnect") == 0) {
        HomeKitNetworkConnection();
    } else {
        ATCMD_LOG_I("Usage: interface set|info|disconnect|reconnect\n");
    }
    
    return ERROR_SUCCESS;
}

int At_Bct(stParam *param)
{
    if (OS_TaskCreate((OsTask)test_conn, "test_conn", 512, NULL, OS_TASK_PRIO3, NULL ) != true)
    {
        ATCMD_LOG_I("[%d] %s task create fail\n", __LINE__, __func__);
        return -1;
    }
    return ERROR_SUCCESS;
}

const at_cmd_info atcmd_homekit_tbl[] =
{
/*-------------------
    ------for debug------ */
    {"init" , At_Init, 0},
    {"wifi" , At_Wifi, 0},
    //{"httpd" , At_HTTPD, 0},
    //{"mfi" , At_MFi, 0},
    {"softap" , At_Soft, 0},
/*-------------------*/
    {"wac" , At_Wac, 0},
    {"mdns" , At_Mdns, 0},
    {"interface" , At_Interface, 0},
    {"bct" , At_Bct, 0},
};

int get_atcmd_homekit_size()
{
    return sizeof(atcmd_homekit_tbl);
}
