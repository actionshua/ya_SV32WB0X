/*
*  (C) Copyright 2014-2016 Shenzhen South Silicon Valley microelectronics co.,limited
*
*  All Rights Reserved
*/
#include <string.h>
#include "osal.h"
#include "netstack.h"
#ifdef TCPIPSTACK_EN
#ifdef CONFIG_OS_RHINO
#include "../trunk/components/net/tcpip/lwip-1.4.0/src/include/netif/ethernetif.h"
#else
//#ifdef ROM_MODE
//#include "rom/lwip_rom_init.h"
//#endif
#include "netif/ethernetif.h"
#endif


#define LLH_LEN 14
#define MEMSET memset
#define INIT_BF_THREAD_RUN 1
#define UDHCP_ON

extern IEEE80211STATUS gwifistatus;
extern void mgmt_msg_post(u8 wsid, u8 action, u8 reconnect);

static struct netif *_netif_find(char *name)
{    
    if(name == NULL)
    {
        return NULL;
    }
    else
        return netif_find(name);
}

void netdev_status_change_cb(struct netif *netif)
{
    u8 id;
    
#ifdef CONFIG_OS_RHINO
    id = netif->num;
#else
    if(strcmp(netif->name, IF0_NAME) == 0)
    {
        id = 0;
    }
    else
    {
        id = 1;
    }
#endif
    
    if (netif->flags & NETIF_FLAG_UP)
    {
#ifdef CONFIG_OS_RHINO
        if(gwifistatus.connAP[id].status == IEEE80211_GETIP)
#endif
        {
            mgmt_msg_post(id, MGMT_CONNECTED, 0);
        }
    }
    else
    {
        printf("netif is down : %s\n", netif->name);
    }
}

/* Transfer L2 packet to netstack
 * [in] data: pointer of incoming data
 * [in] len: length of real 802.3 packet
 * Transfer incoming wifi data to be processed by netstack 
 */
int netstack_input(char *ifname, void *data, u32 len)
{
    struct netif *pif;

    pif = _netif_find(ifname);
    ethernetif_input(pif, data, len);

    return NS_OK;
}

/* Transfer netstack packet to L2
 * [in] data: pointer of output data
 * [in] len: length of real 802.3 packet
 * Transfer output data to be sent 
 */
int netstack_output(char *name, void *data, u32 len)
{  
    if(0 != (NETSTACK_MAC.send)(name, data, len))
    {
        return NS_ERR_MEM;
    }

    return NS_OK;
}

/* Init netstack
 * [in] config: pointer of config
 * Init netstack with specific config
 * You may 
 * 1)init netstack
 * 2)add default net interface
 * 3)connect io of netstack and 
 */
int netstack_init(NETSTACK_CONFIG *config)
{
    struct netdev netdev;

//#ifdef ROM_MODE
//    tcpipstack_rom_init();
//#endif
#if LWIP_AUTOIP == 1
    gwifistatus.autoip_en = 1;
#else
    gwifistatus.autoip_en = 0;
#endif
    memset(&netdev, 0, sizeof(netdev));
    memcpy(&netdev.name, IF0_NAME, sizeof(IF0_NAME));
    memcpy(&netdev.hwmac, gwifistatus.local_mac[0], 6);
    //netdev_init(&netdev, true, false);

    if(config==NULL)
    {
        netdev_init(&netdev, true, false);
    }
    else
    {
        printf("netstack init: if0:%s\n",config->hostname_if0);
        netdev_init_ex(&netdev, true, false,config->hostname_if0);
    }
    
    memcpy(gwifistatus.ifname[0], IF0_NAME, sizeof(IF0_NAME));
    
    memset(&netdev, 0, sizeof(netdev));
    memcpy(&netdev.name, IF1_NAME, sizeof(IF1_NAME));
    memcpy(&netdev.hwmac, gwifistatus.local_mac[1], 6);
    if(config==NULL)
    {
        netdev_init(&netdev, false, false);
    }
    else
    {
        printf("netstack init: if1:%s\n",config->hostname_if0);
        netdev_init_ex(&netdev, false, false,config->hostname_if1);
    }
        
    memcpy(gwifistatus.ifname[1], IF1_NAME, sizeof(IF1_NAME));
    
    tcpip_init(NULL, NULL); 

    return NS_OK; 
}

/* get dns server
 * [in] dnsserver: point of dns server array
 * [in] nmudnssvr: the number of dns server you want to get
 * Default number of dns server is defined as DNS_MAX_SERVERS
 * You can get all dns servers with a array.
 */ 
int netstack_get_ipv4dnsaddr(u32 *dnsserver, u32 numdnssvr)
{
    u8 numdns = (numdnssvr > DNS_MAX_SERVERS)? DNS_MAX_SERVERS : numdnssvr, i = 0;
#if defined(CONFIG_OS_RHINO) || defined(CONFIG_LWIP_VER2_x_x)
    const ip_addr_t *tmpdnsaddr;
#else
    ip_addr_t tmpaddr;
#endif

    while (i < numdns)
    {        
#if defined(CONFIG_OS_RHINO) || defined(CONFIG_LWIP_VER2_x_x)
        tmpdnsaddr = dns_getserver(i);
        *dnsserver = tmpdnsaddr->addr;
#else
        tmpaddr = dns_getserver(i);
        *dnsserver = tmpaddr.addr;
#endif
        dnsserver ++; 
        i++;
    }
        
    return NS_OK;
}

/* set dns server
 * [in] dnsserver: point of dns server array
 * [in] nmudnssvr: the number of dns server you want to get
 * Default number of dns server is defined as DNS_MAX_SERVERS
 * You can set all dns servers with a array.
 */ 
int netstack_set_ipv4dnsaddr(const u32 *dnsserver, u32 numdnssvr)
{
    u8 numdns = (numdnssvr > DNS_MAX_SERVERS)? DNS_MAX_SERVERS : numdnssvr, i = 0;
    
    while (i < numdns)
    {
        dns_setserver(i, (ip_addr_t *)&dnsserver[i]);
        i++;
    }
    return NS_OK;
}

#if 0
static void _netstack_remove_cb(struct netif *netif)
{
    if(netif->hostname!=NULL)
    {
        OS_MemFree(netif->hostname);
        netif->hostname = NULL;
    }
    return;
}
#endif

static int _netdev_init(struct netdev *pdev, bool dft_dev, bool init_up, char *hostName)
{
    struct ip4_addr ipaddr, netmask, gw;
    struct netif *pwlan = NULL;
#if INIT_BF_THREAD_RUN
    struct netif *tmp = NULL;
#endif
//    int ret = ERR_OK;

    /* net if init */
    pwlan = netif_find(pdev->name);
    if (pwlan != NULL)
    {
#if INIT_BF_THREAD_RUN
        netif_remove(pwlan);
#else
        netifapi_netif_remove(pwlan);
#endif
        MEMSET((void *)pwlan, 0, sizeof(struct netif));
    }
    else
        pwlan = MALLOC(sizeof(struct netif));
    
    
    MEMCPY((void *)(pwlan->hwaddr), pdev->hwmac, 6);
#ifdef CONFIG_OS_RHINO
    MEMCPY((void *)(pwlan->name),pdev->name, 2);
#else
    MEMCPY((void *)(pwlan->name),pdev->name, 6);
#endif
    if(hostName!=NULL)
    {
        pwlan->hostname=OS_MemAlloc(strlen(hostName)+1);
        memcpy(pwlan->hostname,hostName,strlen(hostName)+1);        
    }
    else
    {
        pwlan->hostname=NULL;
    }

    ipaddr.addr = pdev->ipaddr;
    netmask.addr = pdev->netmask;
    gw.addr =  pdev->gw;

#if INIT_BF_THREAD_RUN
    tmp = netif_add(pwlan, &ipaddr, &netmask, &gw, NULL, ethernetif_init, tcpip_input);
    if (tmp != pwlan)
    {
        LOG_PRINTF("netif_add err, return netif is %p\r\n", tmp);
    }
#else
    ret = netifapi_netif_add(pwlan, &ipaddr, &netmask, &gw, NULL, ethernetif_init, tcpip_input);
    if (ret != ERR_OK)
    {
        LOG_PRINTF("netifapi_netif_add err = %d\r\n", ret);
    }
#endif

     /* 
        Mark "netif_set_remove_callback." 
        This function must enable LWIP_NETIF_REMOVE_CALLBACK of LWIP, and not all projects apply our L3 stack, 
        if customer insisit to use their L3 stack, and they disable LWIP_NETIF_REMOVE_CALLBACK, it will cause the compile error.

        Althouth we mark this linke, the infterfaces always exist, we don't need to worried about the memory leack
     */
     //netif_set_remove_callback(pwlan,_netstack_remove_cb);

#if LWIP_IPV6
	//add ipv6 link global interface!!
  	netif_create_ip6_linklocal_address(pwlan,1);	
	//dbg_dump_ip6("ipv6",&pwlan->ip6_addr[0]);
#endif


    if(dft_dev == TRUE)
    {
#if INIT_BF_THREAD_RUN        
        netif_set_default(pwlan);
#else
        ret = netifapi_netif_set_default(pwlan);
        if (ret != ERR_OK)
        {
            LOG_PRINTF("netifapi_netif_set_default err = %d\r\n", ret);
        }
#endif
    }    

#if INIT_BF_THREAD_RUN
    netif_set_link_down(pwlan);
#else    
    //netifapi_netif_set_link_down(pwlan);
    netifapi_netif_common(pwlan, netif_set_link_down, NULL);
#endif

    /* if ap mode and dhcpd enable, set ip is default ip and set netif up */
    if (init_up == true)
    {
#if INIT_BF_THREAD_RUN
        netif_set_link_up(pwlan);
        netif_set_up(pwlan);        
#else        
        //netifapi_netif_set_link_up(pwlan);
        netifapi_netif_common(pwlan, netif_set_link_up, NULL);
        netifapi_netif_set_up(pwlan);        
#endif
    }

    /* Register link change callback function */
    netif_set_status_callback(pwlan, netdev_status_change_cb);
    //netif_set_link_callback(pwlan, net);

    printf("MAC[%02x:%02x:%02x:%02x:%02x:%02x]\r\n",
        pwlan->hwaddr[0], pwlan->hwaddr[1], pwlan->hwaddr[2],
        pwlan->hwaddr[3], pwlan->hwaddr[4], pwlan->hwaddr[5]);

    return NS_OK;
}
/*Init device with setting
 * [in] pdev: pointer of config
 * Init netstack with specific config
 * You may 
 * init netdev
 */
int netdev_init(struct netdev *pdev, bool dft_dev, bool init_up)
{
    _netdev_init(pdev,dft_dev,init_up,NULL);    
    return NS_OK;
}


/*Init device with setting
 * [in] pdev: pointer of config
 * [in] hostName: pointer of a host name 
 * Init netstack with specific config
 * You may 
 * init netdev
 */
int netdev_init_ex(struct netdev *pdev, bool dft_dev, bool init_up, char *hostName)
{
    _netdev_init(pdev,dft_dev,init_up,hostName);    
    return NS_OK;
}

//get hw mac
int netdev_getmacaddr(const char *ifname, u8 *macaddr)
{
    struct netif * pwlan = NULL;
    pwlan = _netif_find((char *)ifname);
    if (pwlan)
        MEMCPY((void *)macaddr,(void *)(pwlan->hwaddr), 6);
    else
        return NS_ERR_ARG;
    return NS_OK;
}

//get ipinfo
int netdev_getipv4info(const char *ifname, u32 *ip, u32 *gw, u32 *netmask)
{
    struct netif * pwlan = NULL;
    pwlan = _netif_find((char *)ifname);
    if (NULL == pwlan)        
        return NS_ERR_ARG;
    
    if (NULL != ip)
        *ip = pwlan->ip_addr.addr;
    if (NULL != gw)
        *gw = pwlan->gw.addr;
    if (NULL != netmask)
        *netmask = pwlan->netmask.addr;
    
    return NS_OK;
}

//set ipinfo
int netdev_setipv4info(const char *ifname, u32 ip, u32 gw, u32 netmask)
{
    struct netif * pwlan = NULL;
    struct ip4_addr ipaddr, maskaddr, gwaddr;
    int err = ERR_OK;
    pwlan = _netif_find((char *)ifname);
    if (NULL == pwlan)        
        return NS_ERR_ARG;
    
    ipaddr.addr = ip;
    maskaddr.addr = netmask;
    gwaddr.addr = gw;
    err = netifapi_netif_set_addr(pwlan, &ipaddr, &maskaddr, &gwaddr);
        
    if(err != ERR_OK)
    {
        LOG_PRINTF("netifapi_netif_set_addr err=%d\r\n", err);
        return NS_ERR_ARG;
    }
    return NS_OK;
}

//get dns server
//int netdev_get_ipv4dnsaddr(const char *ifname, u32 *dnsserver);
//set dns server
//int netdev_set_ipv4dnsaddr(const char *ifname, const u32 *dnsserver);

//get interface status
int netdev_getifstatus(const char *ifname, u32 *flags)
{
    struct netif * pwlan = NULL;
    pwlan = _netif_find((char *)ifname);
    if (NULL == pwlan)        
        return NS_ERR_ARG;

    *flags = pwlan->flags;
    return NS_OK;
}

//set interface up
int netdev_ifup(const char *ifname)
{
    struct netif *pwlan = NULL;
    pwlan = _netif_find((char *)ifname);
    if (NULL == pwlan)        
        return NS_ERR_ARG;
    
    netifapi_netif_set_up(pwlan);
    return NS_OK;
}

//set interface down
int netdev_ifdown(const char *ifname)
{
    struct netif *pwlan = NULL;
    pwlan = _netif_find((char *)ifname);
    if (NULL == pwlan)        
        return NS_ERR_ARG;
    
    netifapi_netif_set_down(pwlan);
    return NS_OK;
}

//interface link up cb
void netdev_link_up_cb(void *ifname)
{   
    struct netif *pwlan = NULL;
    pwlan = _netif_find((char *)ifname);
    if (NULL == pwlan)        
        return ;
    
    //netifapi_netif_set_link_up(pwlan);
    netifapi_netif_common(pwlan, netif_set_link_up, NULL);
    //return NS_OK;
}

//interface link down cb
void netdev_link_down_cb(void *ifname)
{   
    struct netif *pwlan = NULL;
    pwlan = _netif_find((char *)ifname);
    if (NULL == pwlan)        
        return ;

    //netifapi_netif_set_link_down(pwlan);
    netifapi_netif_common(pwlan, netif_set_link_down, NULL);
    //return NS_OK;
}

//set dhcp client on dev
int dhcpc_wrapper_set(const char *ifname, const bool enable)
{
    struct netif *pwlan = NULL;    
    
    pwlan = _netif_find((char *)ifname);
    if (NULL == pwlan)        
        return NS_ERR_ARG;

    if(TRUE == enable)
        netifapi_dhcp_start(pwlan);
    else
        netifapi_dhcp_stop(pwlan);
    
    return NS_OK;        
}

u32 netdev_getallnetdev(struct netdev *pdev, u32 num_of_pdev)
{
    extern struct netif *netif_list;
    struct netif *netif;
    u32 num = 0;
    if ((pdev == NULL) ||(num_of_pdev == 0))
        return 0;
        
    for(netif=netif_list; ((num < num_of_pdev) && (netif!=NULL)); netif=netif->next)        
    {
        MEMCPY((void *)&pdev[num].name, (void *)&netif->name, sizeof(netif->name));
        MEMCPY((void *)&pdev[num].hwmac, (void *)&netif->hwaddr, sizeof(netif->hwaddr));
        pdev[num].flags = netif->flags;
        pdev[num].ipaddr = netif->ip_addr.addr;
        pdev[num].gw = netif->gw.addr;
        pdev[num].netmask = netif->netmask.addr;
        pdev[num].mtu = netif->mtu;
        num++;
    }
    return num;
}

void netstack_arp_table_showall()
{
//    etharp_show_all_entry();
}
#ifdef UDHCP_ON
extern void dhcpd_lease_show();
#endif
void netstack_dhcpd_lease_showall()
{
#ifdef UDHCP_ON    
    dhcpd_lease_show();
#endif
}
#else
int netstack_input(char *ifname, void *data, u32 len)
{
    return NS_OK;
}

int netstack_output(char *name, void *data, u32 len)
{
    return NS_OK;
}

int netstack_init(NETSTACK_CONFIG *config)
{
    return NS_OK; 
}
#endif

const struct network_driver ieee80211_net = {
	"ieee80211_net",
	netstack_init,
	netstack_input,
    netstack_output
};
