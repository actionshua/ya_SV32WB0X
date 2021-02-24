#ifndef _DRV_IDMANAGE_H_
#define _DRV_IDMANAGE_H_

#include "attrs.h"
#include "ssv_pktdef.h"
#include "ssv_desc.h"
#ifndef PROJECT_SMAC
#include "ssv_common.h"
#endif

#define PBUF_ADDR_MAX               128
#if (CHIP_ID == 6020) && ((CHIP_SUB_ID==1) || (CHIP_SUB_ID==2))
// for 6020B
#define PBUF_BASE_ADDR              0xE0000000
#else
#define PBUF_BASE_ADDR              0x80000000
#endif
#define PBUF_ADDR_SHIFT	            16

#define PBUF_MapPkttoID(_pkt)		(((u32)_pkt&0x0FFF0000)>>PBUF_ADDR_SHIFT)
#define PBUF_MapIDtoPkt(_id)		(PBUF_BASE_ADDR|((_id)<<PBUF_ADDR_SHIFT))
#define PBUF_isPkt(addr)    (((u32)(addr) >= (u32)PBUF_BASE_ADDR) && \
                                ((u32)(addr) <= (u32)PBUF_MapIDtoPkt(PBUF_ADDR_MAX-1)) && \
                                ((((u32)(addr))&0xFFFF)==0))

typedef enum __PBuf_Type_E {
    NOTYPE_BUF  = 0,
    TX_BUF      = 1,
    RX_BUF      = 2
} PBuf_Type_E;

void *drv_id_mng_alloc(u32 packet_len, PBuf_Type_E buf_type) ATTRIBUTE_SECTION_FAST_L2STACK;
u32 drv_id_mng_rls(void *packet_address) ATTRIBUTE_SECTION_FAST_L2STACK;
u8 drv_id_mng_full(void);
void drv_id_set_trx_pagesize(u16 tx_page, u16 rx_page);
u8 drv_get_nontype_packet_freesize() ATTRIBUTE_SECTION_FAST_L2STACK;

#endif /* _DRV_PBUF_H_ */

