#ifndef _HOST_TIMER_H_
#define _HOST_TIMER_H_



#include "ssv_types.h"
#include "ssv_hal.h"



#define HTMR_DRV_TIMER_ID_INVALID               0xFF
#define HTMR_DRV_TIMER_ID_0                     SW_MS_TIMER0
#define HTMR_DRV_TIMER_ID_1                     SW_MS_TIMER1
#define HTMR_DRV_TIMER_ID_2                     SW_MS_TIMER2
#define HTMR_DRV_TIMER_ID_3                     SW_MS_TIMER3
#define HTMR_DRV_TIMER_ID_4                     SW_MS_TIMER4



typedef void (*htmr_cb_t)(u8 htmr_id);



typedef enum
{
    HTMR_ID_0 = 0,
    HTMR_ID_1,
    HTMR_ID_2,
    HTMR_ID_3,
    HTMR_ID_4,
    HTMR_ID_MAX,
    HTMR_ID_INVALID = HTMR_ID_MAX,

} HTMR_ID;



typedef struct
{
    u8          drv_timer_id;
    u8          drv_timer_reload;
    htmr_cb_t   htmr_cb;
    
} htmr_ctrlblock_st;



void htmr_reset(void);
HTMR_ID htmr_start(u32 period, u8 reload, htmr_cb_t htmr_cb);
void htmr_stop(HTMR_ID id);
void htmr_msg_handle(u8 drv_timer_id);



#endif  /// end of _HOST_TIMER_H_
