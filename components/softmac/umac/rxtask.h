#ifndef _RXTASK_H_
#define _RXTASK_H_

//#include "soc_types.h"

void ampdu_set_rx_status(bool bEnable);
bool ampdu_get_rx_status(void);
void ampdu_rx_init();
int ampdu_rx_ctx_init(u8 wsid, u8 tid, u8 quesize, u16 seqnum);
int ampdu_rx_ctx_release(u8 wsid, u8 tid);
int rx_pkt_check_reorder_proc(struct ssv6006_rx_desc *rx_desc, u32 time);
int ampdu_get_expire_time(u32 *expiretime);
void ampdu_rx_proc_expire_event(u32 tick);
int ampdu_rx_ctx_release_wsid(u8 wsid);

#endif /* _RXTASK_H_ */
