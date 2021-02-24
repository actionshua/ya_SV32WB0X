#include <sys/backtrace.h>
#include <sys/xip.h>
#include <osal.h>
#include <wifinetstack.h>
#include <idmanage/pbuf.h>
#include <security/drv_security.h>
#include <phy/drv_phy.h>
#include <soc_defs.h>
#include <ieee80211_mgmt.h>
#include <ieee80211_mac.h>
#include <sta_func.h>
#include <wifi_api.h>
#include <netstack.h>
#include <netstack_def.h>
#include <uart/drv_uart.h>
#include <uart/drv_comport.h>
//#include <phy/rf_api.h>

#include <sysconf_api.h>
#include <toolbox.h>
#include <bsp.h>

void Cli_Task( void *args );


/**********************************************************/

void wifirspcbfunc(WIFI_RSP *msg)
{
    u8 dhcpen;
    u8 mac[6];
    u8 ipv4[4];

    uip_ipaddr_t ipaddr, submask, gateway, dnsserver;
    s8 ret;

    if(msg->wifistatus == 1)
    {
        printf("wifi connected\n");
        get_if_config(&dhcpen, (u32*)&ipaddr, (u32*)&submask, (u32*)&gateway, (u32*)&dnsserver);
        memcpy(mac, gwifistatus.local_mac, ETH_ALEN);
        printf("mac             - %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        printf("ip addr         - %d.%d.%d.%d\n", ipaddr.u8[0], ipaddr.u8[1], ipaddr.u8[2], ipaddr.u8[3]);
        printf("netmask         - %d.%d.%d.%d\n", submask.u8[0], submask.u8[1], submask.u8[2], submask.u8[3]);
        printf("default gateway - %d.%d.%d.%d\n", gateway.u8[0], gateway.u8[1], gateway.u8[2], gateway.u8[3]);
        printf("DNS server      - %d.%d.%d.%d\n", dnsserver.u8[0], dnsserver.u8[1], dnsserver.u8[2], dnsserver.u8[3]);
    }
}

void tcptask(void *args)
{
	while(1){
		if(1==get_wifi_status()) {
			break;
		} else {
			OS_MsDelay(500);
		}

	}

	OS_TaskDelete(NULL);
}

void wifi_auto_connect_task(void *pdata)
{  
    if( get_auto_connect_flag() == 1 )
    {
        printf("run wifi_auto_connect_task\n");
        OS_MsDelay(3*1000);
        printf("run wifi_auto_connect_task\n");
        DUT_wifi_start(DUT_STA);
        OS_MsDelay(1*1000);
        do_wifi_auto_connect();
    }
    
    OS_TaskDelete(NULL);
}

void ssvradio_init_task(void *pdata)
{
    RADIO_INIT(DEFAULT_COUNTRY_CODE, DEFAULT_RATE_MASK_VALUE,FALSE); 
#ifdef TCPIPSTACK_EN
    netstack_init(NULL);
#endif
    OS_TaskDelete(NULL);
}

void APP_Init(void)
{
    bsp_init();

    rf_table_init();

#if 1
    OS_TaskCreate(Cli_Task, "cli", 1024, NULL, OS_TASK_LOW_PRIO, NULL);
#endif

    OS_TaskCreate(ssvradio_init_task, "ssvradio_init", 512, NULL, OS_TASK_MIDDLE_PRIO, NULL);

    init_global_conf();
    OS_TaskCreate(wifi_auto_connect_task, "wifi_auto_connect", 1024, NULL, OS_TASK_MIDDLE_PRIO, NULL);

    printf("[%s %s][%s][%d] fota option: %d\n", __DATE__, __TIME__, __func__, __LINE__, (int)&__fota_option);
    OS_StartScheduler();
}

