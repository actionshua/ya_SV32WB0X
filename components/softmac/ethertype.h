#ifndef _ETHERTYPE_H_
#define _ETHERTYPE_H_


/*
 * Ethernet types.
 *
 * We wrap the declarations with #ifdef, so that if a file includes
 * <netinet/if_ether.h>, which may declare some of these, we don't
 * get a bunch of complaints from the C compiler about redefinitions
 * of these values.
 *
 * We declare all of them here so that no file has to include
 * <netinet/if_ether.h> if all it needs are ETHERTYPE_ values.
 */

#ifndef ETHERTYPE_LEN
#define ETHERTYPE_LEN           2
#endif

#ifndef ETHERTYPE_GRE_ISO
#define ETHERTYPE_GRE_ISO       0x00FE  /* not really an ethertype only used in GRE */
#endif
#ifndef ETHERTYPE_PUP
#define	ETHERTYPE_PUP		0x0200	/* PUP protocol */
#endif
#ifndef ETHERTYPE_IP
#define	ETHERTYPE_IP		0x0800	/* IP protocol */
#endif
#ifndef ETHERTYPE_ARP
#define ETHERTYPE_ARP		0x0806	/* Addr. resolution protocol */
#endif
#ifndef ETHERTYPE_REVARP
#define ETHERTYPE_REVARP	0x8035	/* reverse Addr. resolution protocol */
#endif
#ifndef ETHERTYPE_NS
#define ETHERTYPE_NS		0x0600
#endif
#ifndef	ETHERTYPE_SPRITE
#define	ETHERTYPE_SPRITE	0x0500
#endif
#ifndef ETHERTYPE_TRAIL
#define ETHERTYPE_TRAIL		0x1000
#endif
#ifndef	ETHERTYPE_MOPDL
#define	ETHERTYPE_MOPDL		0x6001
#endif
#ifndef	ETHERTYPE_MOPRC
#define	ETHERTYPE_MOPRC		0x6002
#endif
#ifndef	ETHERTYPE_DN
#define	ETHERTYPE_DN		0x6003
#endif
#ifndef	ETHERTYPE_LAT
#define	ETHERTYPE_LAT		0x6004
#endif
#ifndef ETHERTYPE_SCA
#define ETHERTYPE_SCA		0x6007
#endif
#ifndef	ETHERTYPE_LANBRIDGE
#define	ETHERTYPE_LANBRIDGE	0x8038
#endif
#ifndef	ETHERTYPE_DECDNS
#define	ETHERTYPE_DECDNS	0x803c
#endif
#ifndef	ETHERTYPE_DECDTS
#define	ETHERTYPE_DECDTS	0x803e
#endif
#ifndef	ETHERTYPE_VEXP
#define	ETHERTYPE_VEXP		0x805b
#endif
#ifndef	ETHERTYPE_VPROD
#define	ETHERTYPE_VPROD		0x805c
#endif
#ifndef ETHERTYPE_ATALK
#define ETHERTYPE_ATALK		0x809b
#endif
#ifndef ETHERTYPE_AARP
#define ETHERTYPE_AARP		0x80f3
#endif
#ifndef	ETHERTYPE_8021Q
#define	ETHERTYPE_8021Q		0x8100
#endif
#ifndef ETHERTYPE_IPX
#define ETHERTYPE_IPX		0x8137
#endif
#ifndef ETHERTYPE_IPV6
#define ETHERTYPE_IPV6		0x86dd
#endif
#ifndef ETHERTYPE_PPP
#define	ETHERTYPE_PPP		0x880b
#endif
#ifndef ETHERTYPE_SLOW
#define	ETHERTYPE_SLOW		0x8809
#endif
#ifndef	ETHERTYPE_MPLS
#define	ETHERTYPE_MPLS		0x8847
#endif
#ifndef	ETHERTYPE_MPLS_MULTI
#define	ETHERTYPE_MPLS_MULTI	0x8848
#endif
#ifndef ETHERTYPE_PPPOED
#define ETHERTYPE_PPPOED	0x8863
#endif
#ifndef ETHERTYPE_PPPOES
#define ETHERTYPE_PPPOES	0x8864
#endif
#ifndef ETHERTYPE_PPPOED2
#define ETHERTYPE_PPPOED2	0x3c12
#endif
#ifndef ETHERTYPE_PPPOES2
#define ETHERTYPE_PPPOES2	0x3c13
#endif
#ifndef ETHERTYPE_JUMBO
#define ETHERTYPE_JUMBO         0x8870
#endif
#ifndef ETHERTYPE_EAPOL
#define ETHERTYPE_EAPOL  	0x888e
#endif
#ifndef	ETHERTYPE_LOOPBACK
#define	ETHERTYPE_LOOPBACK	0x9000
#endif
#ifndef	ETHERTYPE_VMAN
#define	ETHERTYPE_VMAN	        0x9100 /* Extreme VMAN Protocol */ 
#endif
#ifndef	ETHERTYPE_ISO
#define	ETHERTYPE_ISO           0xfefe  /* nonstandard - used in Cisco HDLC encapsulation */
#endif
#ifndef	IPPROTO_UDP
#define	IPPROTO_UDP             17  /* UDP */
#endif

#ifdef htons
#undef htons
#endif
#ifdef htonl
#undef htonl
#endif
#ifdef ntohs
#undef ntohs
#endif
#ifdef ntohl
#undef ntohl
#endif

#define htons(x)    (((x & 0xff) << 8) | ((x & 0xff00) >> 8))
#define ntohs(x)    (((x & 0xff) << 8) | ((x & 0xff00) >> 8))
#define htonl(x)    (((x & 0xff) << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000UL) >> 8) | ((x & 0xff000000UL) >> 24))
#define ntohl(x)    (((x & 0xff) << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000UL) >> 8) | ((x & 0xff000000UL) >> 24))

#define DHCP_MSG_TYPE_DISCOVER          (1)
#define DHCP_MSG_TYPE_OFFER             (2)
#define DHCP_MSG_TYPE_REQUEST           (3)
#define DHCP_MSG_TYPE_DECLINE           (4)
#define DHCP_MSG_TYPE_ACK               (5)
#define DHCP_MSG_TYPE_NACK              (6)
#define DHCP_MSG_TYPE_RELEASE           (7)
#define GET_DHCP_MSG_TYPE(m)            ((m)->options[6])

#define IS_DISCOVER_MSG(m)              (GET_DHCP_MSG_TYPE(m) == DHCP_MSG_TYPE_DISCOVER)
#define IS_OFFER_MSG(m)                 (GET_DHCP_MSG_TYPE(m) == DHCP_MSG_TYPE_OFFER)
#define IS_REQUEST_MSG(m)               (GET_DHCP_MSG_TYPE(m) == DHCP_MSG_TYPE_REQUEST)
#define IS_DECLINE_MSG(m)               (GET_DHCP_MSG_TYPE(m) == DHCP_MSG_TYPE_DECLINE)
#define IS_ACK_MSG(m)                   (GET_DHCP_MSG_TYPE(m) == DHCP_MSG_TYPE_ACK)
#define IS_NACK_MSG(m)                  (GET_DHCP_MSG_TYPE(m) == DHCP_MSG_TYPE_NACK)
#define IS_RELEASE_MSG(m)               (GET_DHCP_MSG_TYPE(m) == DHCP_MSG_TYPE_RELEASE)

#define GET_IP_HDR_LEN(ver)             ((ver & 0x0F) << 2)
#define IP_ADDR_LEN                     (4)

/*  be sure the offer msg is not sned to R-S itself 
 *  ip_hdr->da_ip => gateway ip(i.e R-S)
 *  m->yiaddr     => the client of R-A(i.e phone) or R-S itself
 */
#define IS_DEST_TO_RS(ip_hdr, m)        ((memcmp(ip_hdr->da_ip, m->yiaddr, IP_ADDR_LEN) == 0) ? TRUE : FALSE)

#define DHCP_CLIENT_PORT  68
#define DHCP_SERVER_PORT  67


#define BROADCAST_FLAG 0x8000 /* "I need broadcast replies" */

struct snap_hdr {
    u8 dsap;
    u8 ssap;
    u8 ctrl;
    u8 org[3];
    u16 ethertype;
};

struct transpt_udp_hdr {
    u16 src_port;
    u16 dest_port;
    u16 len;
    u16 check_sum;
    u8  payload[0];
};

struct net_ethernet_hdr {
    u8 dest[6];
    u8 src[6];
    u16 type;
    u8 payload[0];
};

struct net_ip_hdr {
    u8 ver;
    u8 tos;
    u16 len;
    u16 id;
    u16 frag_ofset;
    u8 ttl;
    u8 proto;
    u16 h_chk_sum;
    u8 sa_ip[4];
    u8 da_ip[4];
    u8 payload[0];
};

struct net_ip6_hdr {
  /* version / traffic class / flow label */
  u32 v_tc_fl;
  /* payload length */
  u16 plen;
  /* next header */
  u8 nexth;
  /* hop limit */
  u8 hoplim;
  /* source and destination IP addresses */
  u32 src[4];
  u32 dest[4];
} PACK_STRUCT_STRUCT;

struct net_arp_hdr {
	u16 htype;              /* hardware type (must be ARPHRD_ETHER)      */
	u16 ptype;              /* protocol type (must be ETH_P_IP)          */
	u8 hlen;                /* hardware address length (must be 6)       */
	u8 plen;                /* protocol address length (must be 4)       */
	u16 operation;          /* ARP opcode                                */
	u8 sHaddr[6];           /* sender's hardware address                 */
	u8 sInaddr[4];          /* sender's IP address                       */
	u8 tHaddr[6];           /* target's hardware address                 */
	u8 tInaddr[4];          /* target's IP address                       */
	u8 payload[0];          /* ethernet payload (60 bytes)               */
};

/* Reference by RFC 2131 */
struct app_dhcp_msg {
	u8 op; 		            /* Message op code/message type. 
	                           1 = BOOTREQUEST, 2 = BOOTREPLY */
	u8 htype;		        /* Hardware address type */
	u8 hlen;		        /* Hardware address length */
	u8 hops;		        /* Client sets to zero, optionally used by relay 
	                           agents when booting via a relay agent */
	u8 xid[4];		        /* Transaction ID, a random number chosen by the client, 
	                           used by the client and server to associate messages and 
				               responses between a client and a server */
	u16 secs;		        /* Filled in by client, seconds elapsed since client 
	                           began address acquisition or renewal process.*/
	u16 flags;		        /* bit 0: Broadcast flag, bit 1~15:MBZ must 0*/
	u8 ciaddr[4];	        /* Client IP address; only filled in if client is in 
	                           BOUND, RENEW or REBINDING state and can respond to ARP requests. */
	u8 yiaddr[4];	        /* 'your' (client) IP address */
	u8 siaddr[4];	        /* IP address of next server to use in bootstrap; 
	                           returned in DHCPOFFER, DHCPACK by server. */
	u8 giaddr[4];	        /* Relay agent IP address, used in booting via a relay agent.*/
	u8 chaddr[16];	        /* Client hardware address */
	u8 sname[64];	        /* Optional server host name, null terminated string.*/
	u8 file[128];	        /* Boot file name, null terminated string; 
	                           "generic" name or null in DHCPDISCOVER, 
	                           fully qualified directory-path name in DHCPOFFER.*/
	u8 options[312];        /* Optional parameters field. reference the RFC 2132 */
};
#endif//_ETHERTYPE_H_
