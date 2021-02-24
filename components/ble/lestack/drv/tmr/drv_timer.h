#ifndef _DRV_TIMER_H_
#define _DRV_TIMER_H_

#include <ssv_hal.h>



/**
* Define flags for software timer (see below data structure):
*
* @ TMR_FLAG_ACTIVE:
*/
#define TMR_FLAG_ACTIVE                 0x0001
#define TMR_FLAG_RELOAD                 0x0002
#define TMR_FLAG_PREPARE                0X0004


#define TMR_IRQ_MASK                    (0xF)

/**
* struct sw_tmr_entry - software timer data structure.
*
* @ tmrid:
*/
typedef struct sw_tmr_entry  {
    s32         tmrid;      /* software timer ID, start from 0 */
    u16         flags;      /* timer flags, see TMR_FLAG_XXX */
    s32         cur_ticks;  /* current ticks left to time expire */
    s32         ticks;      /* total ticks to count */

    msg_handler handler;    /* call back handler once timeout */
    void        *data;      /* argument passed to call back handler */
    
} SW_TIMER;



s32 drv_tmr_init_c(void);
s32 drv_tmr_pause(void);
s32 drv_tmr_resume(s32 loss_rtc_ticks);



#endif /* _DRV_TIMER_H_ */

