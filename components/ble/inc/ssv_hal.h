#ifndef _SSV_HAL_H_
#define _SSV_HAL_H_

#include "bsp/msg.h"
#include "ble_config.h"

/**
* Define Hardware Abstration Layer (HAL) error number:
*
* @ HAL_ERR_SUCCESS: 
* @
*/
#define HAL_ERR_SUCCESS                 0




/**
* Define system interrupt number. The system interrupt number
* assignment shall be according to the hardware interrupt pin 
* assignment.
*/
#define IRQ_US_TIMER0                   0
#define IRQ_US_TIMER1                   1
#define IRQ_MS_TIMER0                   2
#define IRQ_MS_TIMER1                   3
#define IRQ_MS_TIMER2                   4
#define IRQ_MS_TIMER3                   5
#define IRQ_PDU_RX                      10
#define IRQ_RX_RUNOUT                   11
#define IRQ_RX_TIMEOUT                  12
#define IRQ_TX_COMPLETE                 13
#define IRQ_TX_RUNOUT                   14

#define IRQ_UART_RX                     20
#define IRQ_EVENT_START                 25
#define IRQ_EVENT_CLOSE                 26
#define MAX_IRQ_NO                      32


typedef void (*IRQ_HANDLER)(void);

/* Hardware interrupt API definitions: */
SSV_API s32 hal_irq_request(s32 irqno, IRQ_HANDLER handler);
SSV_API s32 hal_irq_release(s32 irqno);















/* Define software timer handler: */
//typedef msg_handler TMR_HANDLER;
//typedef void (*TMR_HANDLER)(void *);

#define M_MTIMER_BIT        (12)

/* Hardware us timer ID definitions: */
//#define HW_US_TIMER0                (IRQ_US_TIMER0|0x1000)
//#define HW_US_TIMER1                (IRQ_US_TIMER1|0x1000)

/* Hardware ms timer ID definitions: */
//#define HW_MS_TIMER0                (IRQ_MS_TIMER0| (1<<M_MTIMER_BIT))
//#define HW_MS_TIMER1                (IRQ_MS_TIMER1| (1<<M_MTIMER_BIT))
//#define HW_MS_TIMER2                (IRQ_MS_TIMER2| (1<<M_MTIMER_BIT))
//#define HW_MS_TIMER3                (IRQ_MS_TIMER3| (1<<M_MTIMER_BIT))

enum E_TIMER_ID
{
    SW_MS_TIMER0,
    SW_MS_TIMER1,
    SW_MS_TIMER2,
    SW_MS_TIMER3,
    SW_MS_TIMER4,
    SW_MS_TIMER5,
    SW_MS_TIMER6,
    SW_MS_TIMER7,
    SW_MS_TIMER8,
    SW_MS_TIMER9,
    SW_MS_TIMER10,
    SW_MS_TIMER11,
    SW_MS_TIMER12,
    SW_MS_TIMER13,
    SW_MS_TIMER14,
    SW_MS_TIMER15,
    MAX_SW_TIMER_ID = MAX_SW_TIMER,
    HW_US_TIMER0 = MAX_SW_TIMER,
    HW_US_TIMER1,
    HW_MS_TIMER0,
    HW_MS_TIMER1,
    HW_MS_TIMER2,
    HW_MS_TIMER3,
    HW_SWTIMER = HW_MS_TIMER2,
    HW_MAX_TIMER = HW_SWTIMER,  // force assign to last, for software timer.  
};

/* Define interrupt handler prototype: */
typedef void (*TMR_IRQ_HANDLER)(enum E_TIMER_ID tmrid);



/* Timer API definitions: */
#if (M_TIMER_DYNAMIC_IRQ == 1)
SSV_API s32 drv_tmr_start_hw_timer(enum E_TIMER_ID tmrid, u32 time, u8 reload,
            TMR_IRQ_HANDLER handler);
#else
SSV_API s32 drv_tmr_start_hw_timer(enum E_TIMER_ID tmrid, u32 time, u8 reload);
#endif
//SSV_API s32 drv_tmr_start_hw_timer(s32 tmrid, u32 time, u8 reload,
//            IRQ_HANDLER handler);
SSV_API s32 drv_tmr_start_sw_timer(enum E_TIMER_ID tmrid, u32 ms, u8 reload,
            msg_handler src, void *data);
SSV_API s32 drv_tmr_stop_timer(enum E_TIMER_ID tmrid);
SSV_API s32 drv_tmr_clk_compensate();
SSV_API s32 drv_tmr_get_hwtimer_us(enum E_TIMER_ID e);
SSV_API void drv_tmr_restore_hwtimer_us(enum E_TIMER_ID e, s32 time_unit_us);






#endif /* _SSV_HAL_H_ */

