#ifndef MSG_H
#define MSG_H


#define LL_MSG_MAX      (10)
#define SVC_MSG_MAX     (1)
#define USER_MSG_MAX    (1)
#define HOST_MSG_MAX     (14)   // WARNING (CFI-80): msg size for link-layer and CFG_LL_CONN_PDUS are strongly co-related.

#include "ssv_types.h"

#define MSG_STATIC_METHOD       (1)
#define MSG_DYNAMIC_METHOD      (2)

#define MSG_PARAM_COUNT         (4)
#define MSG_PARAM_IDX_TYPE      (0)

#define MSG_METHOD          MSG_STATIC_METHOD

#if 0
#define E_LL            (0)
#define E_SVC           (1)
#define E_USER          (2)
#define E_HANDLER_END   (3)

typedef u8 msg_handler;
#else

typedef enum msg_handler_e{
    E_LL                = 0,
    E_SVC               = 1,
    E_USER              = 2,
    E_HOST              = 3,
    E_HANDLER_END       = 4,
    E_LL_RT             = 5,
    E_TIMER             = 6,
} msg_handler;
#endif

typedef enum msg_st_e{
    E_NEW,
    E_SEND,
    E_USED,
    E_PENDING_FREE,
    E_FREED,
} msg_st;

typedef enum msg_return_e{
    E_MSG_SUCCESS           = 0,
    E_MSG_QUEUE_FULL        = -1,
    E_MSG_QUEUE_EMPTY       = -2,
} msg_return;

typedef struct bsp_base_msg{
    msg_handler     src_handler;
    u32             param[MSG_PARAM_COUNT];
    //msg_st          status;
} bsp_msg;

#if (MSG_METHOD == MSG_STATIC_METHOD)

//struct fifo_st {
//    bsp_msg*     msg;
//};

/* i: wait for insert
 * h: head
 * t: tail
 * u: used */
struct msg_fifo_hdr {
    bsp_msg      *i, *h, *t, *u;
    //struct u8           size
    struct bsp_msg      *msg;
};

#elif (MSG_METHOD == MSG_DYNAMIC_METHOD)

struct msg_ll_hdr {
    bsp_msg      *t, *h;
    //struct u8           size
    struct bsp_msg      *msg;
};

#endif

void msg_init();
msg_return intl_bsp_send_msg(msg_handler src, msg_handler dst, u32 param0, u32 param1, u32 param2, u32 param3);

msg_return intl_bsp_recv_msg(bsp_msg **msg, msg_handler src);




#endif /* end of include guard: MSG_H */
