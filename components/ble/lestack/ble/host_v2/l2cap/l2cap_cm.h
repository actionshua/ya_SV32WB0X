#ifndef _L2CAP_CM_H_
#define _L2CAP_CM_H_



#include "l2cap_def.h"



u8 l2cap_cm_register_dynamic_cid(L2CAP_ID id, u16 dynamic_cid);
u8 l2cap_cm_unregister_dynamic_cid(L2CAP_ID id);
u8 l2cap_cm_check_cid(L2CAP_ID id, u16 cid);
u8 l2cap_cm_send_upper_request(L2CAP_ID id, L2CAP_SLQ_OWNER owner);
u8 l2cap_cm_send_upper_response(L2CAP_ID id, L2CAP_SLQ_OWNER owner);
u8 l2cap_cm_send_upper_response_without_free_sdu(L2CAP_ID id, L2CAP_SLQ_OWNER owner);



#endif  /// end of _L2CAP_CM_H_
