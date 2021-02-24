#ifndef __RATE_CONTROL_H__
#define __RATE_CONTROL_H__

#include "soc_types.h"
#include <attrs.h>

#define MAX_UPRATECNT 6
#define MAX_DOWNRATECNT 2
#define SHIFTBITS 16
#define CCK_SIFS_TIME  10
#define OFDM_SIFS_TIME 16
#define HT_SIFS_TIME   10
#define HT_SIGNAL_EXT  6

#define ACKLEN			14
#define RTSLEN			20
#define CTSLEN			14
#define FCSLEN          4

typedef struct t_DURATION_TABLE
{
    u32 multiplevalue;
    u8  ctrl_rate_idx;
}DURATION_TABLE;

void n_rc_sta_init(u8 mode, u8 wsid, u8 run_channel, u8 htsupport, u8 ratenum, u8 *supportrate);
u8 get_current_rate(u8 wsid);
void n_rc_handler(struct ssv6006_tx_desc *tx_desc) ATTRIBUTE_SECTION_FAST_L2STACK;
int n_rc_get_rate(u8 id, u8 ifmode, struct ssv6006_tx_desc *pTxInfo) ATTRIBUTE_SECTION_FAST_L2STACK;
int n_rc_rate_update(u8 wsid, u8 type);
int n_rc_status(u8 wsid);

#endif
