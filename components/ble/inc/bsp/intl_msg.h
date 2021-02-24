#ifndef INTL_MSG_H
#define INTL_MSG_H

#include "bsp/msg.h"

/* this must in critical section. */
msg_return intl_bsp_recv_msg(bsp_msg **msg, msg_handler src);
msg_return intl_bsp_send_msg(msg_handler src, msg_handler dst, u32 param0, u32 param1, u32 param2, u32 param3);
//msg_return intl_bsp_send_msg(bsp_msg *msg, msg_handler dst);

#endif /* end of include guard: INTL_MSG_H */
