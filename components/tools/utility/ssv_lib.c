#include <config.h>
#include <stdarg.h>
#include <stdio.h>
#include "ssv_lib.h"
#include "soc_types.h"

#define OS_APIs
#define H_APIs
#define LIB_APIs
#define DRV_APIs

LIB_APIs u32 ssv6xxx_atoi_base( const s8 *s, u32 base )
{
    u32  index, upbound=base-1;
    u32  value = 0, v;

    while( (v = (u8)*s) != 0 ) {
        index = v - '0';
        if ( index > 10 && base==16 ) {
            index = (v >= 'a') ? (v - 'a') : (v - 'A');
            index += 10;
        }
        if ( index > upbound )
            break;
        value = value * base + index;
        s++;
    }
    
    return value;
}


LIB_APIs s32 ssv6xxx_atoi( const s8 *s )
{
    u32 neg=0, value, base=10;

    if ( *s=='0' ) {
        switch (*++s) {
        case 'x':
        case 'X': base = 16; break;
        case 'b':
        case 'B': base = 2; break;
        default: return 0;
        }
        s++;
    }
    else if ( *s=='-' ) {
        neg = 1;
        s++;
    }

    value = ssv6xxx_atoi_base(s, base);
    
    if ( neg==1 )
        return -(s32)value;
    return (s32)value;

}

void dbg_dump_mac(char *msg,uint8_t *pmac){
    printf("%s:0x%lx-%lx-%lx-%lx-%lx-%lx\n",msg,(uint32_t)pmac[0],(uint32_t)pmac[1],(uint32_t)pmac[2],(uint32_t)pmac[3],(uint32_t)pmac[4],(uint32_t)pmac[5]);
}

void dbg_dump_ip(char *msg,uint8_t *p_ip){
    printf("%s:%d.%d.%d.%d\n",msg, p_ip[0], p_ip[1], p_ip[2], p_ip[3]);
}


#define PP_HTONL(x) ((((x) & 0xff) << 24) | \
                     (((x) & 0xff00) << 8) | \
                     (((x) & 0xff0000UL) >> 8) | \
                     (((x) & 0xff000000UL) >> 24))


#if (LWIP_IPV6==1) 
//fixed this function to allow unaligned address
void dbg_dump_ip6(char *msg,ip6_addr_t * target_addr) {
    uint32_t u32addr0;
	uint32_t u32addr1;
	uint32_t u32addr2;
	uint32_t u32addr3;

	memcpy(&u32addr0,&target_addr->addr[0],sizeof(uint32_t));
	memcpy(&u32addr1,&target_addr->addr[1],sizeof(uint32_t));
	memcpy(&u32addr2,&target_addr->addr[2],sizeof(uint32_t));
	memcpy(&u32addr3,&target_addr->addr[3],sizeof(uint32_t));

	printf("%s 0x%x:%x:%x:%x:%x:%x:%x:%x\n",msg,((PP_HTONL(u32addr0)>>16)&0xffff),
												  ((PP_HTONL(u32addr0)>>0)&0xffff),
												  ((PP_HTONL(u32addr1)>>16)&0xffff),
												  ((PP_HTONL(u32addr1)>>0)&0xffff),
												  ((PP_HTONL(u32addr2)>>16)&0xffff),
												  ((PP_HTONL(u32addr2)>>0)&0xffff),
												  ((PP_HTONL(u32addr3)>>16)&0xffff),
												  ((PP_HTONL(u32addr3)>>0)&0xffff));
}
#endif


LIB_APIs void halt(void)
{
    while (1) ;
} 
