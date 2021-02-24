#ifndef _EDCA_H_
#define _EDCA_H_

#include <nav/edca_nav.h>

void EDCA_Handler(struct ssv6006_tx_desc *pTxInfo);
void EDCA_FillRelatedDuration(struct ssv6006_tx_desc *pTxInfo, u16 fc);
int EDCA_set_icmp_1m(bool en);
int EDCA_set_low_rate_rts_cts(bool en);
void EDCA_set_txfrm_duration_period(u16 duration, u16 period);



#endif /* _EDCA_H_ */

