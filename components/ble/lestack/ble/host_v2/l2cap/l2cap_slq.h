#ifndef _L2CAP_SLQ_H_
#define _L2CAP_SLQ_H_



#include "l2cap_def.h"



u8 l2cap_slq_reset(L2CAP_ID id);
u8 l2cap_slq_alloc_sdu_lq(L2CAP_ID id, L2CAP_SLQ_OWNER owner);
u8 l2cap_slq_free_sdu_lq(L2CAP_ID id, L2CAP_SLQ_OWNER owner);
L2CAP_SLQ_ID l2cap_slq_get_exist_slq_id(L2CAP_ID id, L2CAP_SLQ_OWNER owner);
L2CAP_SLQ_ID l2cap_slq_get_new_slq_id(L2CAP_ID id, L2CAP_SLQ_OWNER owner);
u8 l2cap_slq_enqueue(L2CAP_ID id, L2CAP_SLQ_OWNER owner, l2cap_sdu_st *sdu);
l2cap_sdu_st *l2cap_slq_dequeue(L2CAP_ID id, L2CAP_SLQ_OWNER owner);
l2cap_sdu_st *l2cap_slq_peek(L2CAP_ID id, L2CAP_SLQ_OWNER owner);



#endif  /// end of _L2CAP_SLQ_H_
