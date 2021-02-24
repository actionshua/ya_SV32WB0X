#ifndef _L2CAP_RM_H_
#define _L2CAP_RM_H_



#include "l2cap_def.h"



u8 l2cap_rm_send_sdu(L2CAP_ID id, u16 conn_hdl, u8 frame_type, u16 cid, l2cap_sdu_st *sdu);



#endif  /// end of _L2CAP_RM_H_
