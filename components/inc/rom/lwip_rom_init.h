#ifndef LWIP_ROM_INIT_H
#define LWIP_ROM_INIT_H

#include "string.h"
#include "soc_types.h"
#include "osal.h"
#include "lwip/opt.h"
#include "lwip/tcp_impl.h"
#include "lwip/tcpip.h"
#include "lwip/ethip6.h"
#include "lwip/memp.h"
#include "lwip/raw.h"
#include "lwip/nd6.h"
#include "lwip/mld6.h"
#include "lwip/ip6_frag.h"
#include "lwip/dns.h"

typedef struct  {
    void* (*memset)    (void *str, int c, size_t n);
    void* (*memcpy)    (void *dst, const void *src, size_t n);
	int (*memcmp) ( const void * ptr1, const void * ptr2, size_t num );
    size_t (*strlen) (const char *str);
	int (*strcmp) ( const char * str1, const char * str2 );
    int (*printf)    (const char* format, ...);
    void* (*OS_MemAlloc)( u32 size );
    void (*OS_MemFree)( void *mem );
	u8  (*OS_TaskCreate)( OsTask task, const char *name, u16 stackSize, void *param, u32 pri, OsTaskHandle *taskHandle );
    OS_STATUS (*OS_MsgQCreate)( OsMsgQ *MsgQ, u32 QLen );
	void (*OS_MsgQDelete)( OsMsgQ MsgQ);
	OS_STATUS (*OS_MsgQEnqueue)( OsMsgQ MsgQ, OsMsgQEntry *MsgItem );
	OS_STATUS (*OS_MsgQDequeue)( OsMsgQ MsgQ, OsMsgQEntry *MsgItem, u32 TickToWait );
	u32 (*OS_MsgQWaitingSize)( OsMsgQ MsgQ );
	void (*OS_TickDelay)(u32 ticks);
	u32 (*OS_GetSysTick)(void);
	OS_STATUS (*OS_SemInit)( OsSemaphore* Sem , u32 maxcnt , u32 cnt);
	OS_STATUS (*OS_SemWait)( OsSemaphore Sem , u32 timeout);
	OS_STATUS (*OS_SemSignal)( OsSemaphore Sem);
	OS_STATUS (*OS_SemDelete)(OsSemaphore Sem);
	OS_STATUS (*OS_MutexInit)( OsMutex *mutex );
	OS_STATUS (*OS_MutexLock)( OsMutex mutex );
	OS_STATUS (*OS_MutexUnLock)( OsMutex mutex );
	OS_STATUS (*OS_MutexDelete)( OsMutex mutex );
	u32 (*OS_IntSave)(void);
	void (*OS_IntRestore)(u32);
	err_t (*ethip6_output)(struct netif *netif, struct pbuf *q, ip6_addr_t *ip6addr);
	const struct network_driver *ieee80211_net;
	const u16_t *memp_sizes;
	err_t (*ip6_input)(struct pbuf *p, struct netif *inp);
	void (*autoip_arp_reply)(struct netif *netif, struct etharp_hdr *hdr);
	void (*dhcp_arp_reply)(struct netif *netif, ip_addr_t *addr);
	struct netif **netif_list;
	struct netif **netif_default;
	struct igmp_group* (*igmp_lookfor_group)(struct netif *ifp, ip_addr_t *addr);
	u8_t (*raw_input)(struct pbuf *p, struct netif *inp);
	void (*igmp_input)(struct pbuf *p, struct netif *inp, ip_addr_t *dest);
	void (*icmp_input)(struct pbuf *p, struct netif *inp);
	err_t (*netif_loop_output)(struct netif *netif, struct pbuf *p);
	void (*lwip_init)(void);
	err_t (*ip6_output)(struct pbuf *p, struct ip6_addr *src, struct ip6_addr *dest, u8_t hl, u8_t tc, u8_t nexth);
	struct netif* (*ip6_route)(struct ip6_addr *src, struct ip6_addr *dest);
	u16_t (*nd6_get_destination_mtu)(ip6_addr_t * ip6addr, struct netif * netif);
	ip6_addr_t* (*ip6_select_source_address)(struct netif *netif, ip6_addr_t * dest);
	void (*nd6_reachability_hint)(ip6_addr_t * ip6addr);
	err_t (*ip6_output_if)(struct pbuf *p, ip6_addr_t *src, ip6_addr_t *dest, u8_t hl, u8_t tc, u8_t nexth, struct netif *netif);
	s8_t (*netif_matches_ip6_addr)(struct netif * netif, ip6_addr_t * ip6addr);
	void (*mld6_tmr)(void);
	void (*ip6_reass_tmr)(void);
	void (*nd6_tmr)(void);
	void (*dns_tmr)(void);
	void (*igmp_tmr)(void);
	void (*autoip_tmr)(void);
	void (*dhcp_fine_tmr)(void);
	void (*dhcp_coarse_tmr)(void);
	void (*netbuf_delete)(struct netbuf *buf);
	struct raw_pcb* (*raw_new)(u8_t proto);
	void (*raw_remove)(struct raw_pcb *pcb);
	err_t (*raw_bind)(struct raw_pcb *pcb, ip_addr_t *ipaddr);
	err_t (*raw_connect)(struct raw_pcb *pcb, ip_addr_t *ipaddr);
	void (*raw_recv)(struct raw_pcb *pcb, raw_recv_fn recv, void *recv_arg);
	err_t (*raw_sendto)(struct raw_pcb *pcb, struct pbuf *p, ip_addr_t *ipaddr);
	err_t (*raw_send)(struct raw_pcb *pcb, struct pbuf *p);
	err_t (*dns_gethostbyname)(const char *hostname, ip_addr_t *addr, dns_found_callback found, void *callback_arg);
	err_t (*mld6_joingroup)(ip6_addr_t *srcaddr, ip6_addr_t *groupaddr);
	err_t (*mld6_leavegroup)(ip6_addr_t *srcaddr, ip6_addr_t *groupaddr);
	err_t (*igmp_joingroup)(ip_addr_t *ifaddr, ip_addr_t *groupaddr);
	err_t (*igmp_leavegroup)(ip_addr_t *ifaddr, ip_addr_t *groupaddr);
	struct netif* (*netif_find)(char *name);
	void* (*netbuf_alloc)(struct netbuf *buf, u16_t size);
	void (*netbuf_free)(struct netbuf *buf);

	u16 tcp_wnd;
	u16 tcp_wnd_update_threshold;
	u16 tcp_snd_buf;
	u16 tcp_snd_queuelen;
    u8  num_sockets;
} tcpipstack_rom_protocol;

typedef struct {
    int (*netstack_output)(struct netif *netif, void *data, u32 len);
} rom_lwip_depend_t;

typedef struct {
    int32_t (*init)(void *data);
    int32_t (*resume)(void *data);
    int32_t (*suspend)(void *data);
    int32_t (*deinit)(void *data);
} rom_lwip_init_t;

void _rom_lwip_init(rom_lwip_depend_t dep);
void _rom_lwip_get_ptr(rom_lwip_init_t *ptr);
extern void tcpipstack_rom_init(void);

extern tcpipstack_rom_protocol *g_tcpipstack_rom_protocol;
extern rom_lwip_depend_t _rom_lwip_depend;

#endif /* end of include guard: LWIP_ROM_INIT_H */
