#ifndef _L2CAP_SPM_H_
#define _L2CAP_SPM_H_



#include "l2cap_def.h"



l2cap_sdu_st *l2cap_spm_alloc_tx_sdu(u8 type, u16 sdu_size);
void l2cap_spm_free_sdu(u8 dir, l2cap_sdu_st *sdu);
void l2cap_spm_cat_sdu(l2cap_sdu_st *dst_sdu, l2cap_sdu_st *src_sdu);
u32 l2cap_spm_get_sdu_overall_pld_size(l2cap_sdu_st *sdu);
u8 *l2cap_spm_get_sdu_pld_ptr(l2cap_sdu_st *sdu);
u16 l2cap_spm_get_sdu_pld_max_size(l2cap_sdu_st *sdu);
u16 l2cap_spm_get_sdu_pld_size(l2cap_sdu_st *sdu);



#endif  /// end of _L2CAP_SPM_H_
