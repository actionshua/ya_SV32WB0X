#include <stdint.h>
#include "ssv_private/ssv_timer_impl.h"
#include "mesh_types.h"
#include "osal.h"
#include "osi/allocator.h"

/* Timer is clocked from APB. To allow for integer scaling factor between ticks
 * and microseconds, divider 1 is used. 16 or 256 would not work for APB
 * frequencies such as 40 or 26 or 2 MHz.
 */
#define TIMER_DIV           1
#define TIMER_DIV_CFG       FRC_TIMER_PRESCALER_1

/* ALARM_OVERFLOW_VAL is used as timer alarm value when there are not timers
 * enabled which need to fire within the next timer overflow period. This alarm
 * is used to perform timekeeping (i.e. to track timer overflows).
 * Due to the 0xffffffff cannot recognize the real overflow or the scenario that
 * ISR happens follow set_alarm, so change the ALARM_OVERFLOW_VAL to resolve this problem.
 * Set it to 0xefffffffUL. The remain 0x10000000UL(about 3 second) is enough to handle ISR.
 */
#define DEFAULT_ALARM_OVERFLOW_VAL 0xefffffffUL

/* Provision to set lower overflow value for unit testing. Lowering the
 * overflow value helps check for race conditions which occur near overflow
 * moment.
 */
#ifndef SSV_TIMER_DYNAMIC_OVERFLOW_VAL
#define ALARM_OVERFLOW_VAL  DEFAULT_ALARM_OVERFLOW_VAL
#else
static uint32_t s_alarm_overflow_val = DEFAULT_ALARM_OVERFLOW_VAL;
#define ALARM_OVERFLOW_VAL (s_alarm_overflow_val)
#endif

static const char* TAG = "ssv_timer_impl";

// Interrupt handle returned by the interrupt allocator
//static intr_handle_t s_timer_interrupt_handle;

// Function from the upper layer to be called when the interrupt happens.
// Registered in ssv_timer_impl_init.
//static intr_handler_t s_alarm_handler;

// Time in microseconds from startup to the moment
// when timer counter was last equal to 0. This variable is updated each time
// when timer overflows, and when APB frequency switch is performed.
static uint64_t s_time_base_us;

// Number of timer ticks per microsecond. Calculated from APB frequency.
static uint32_t s_timer_ticks_per_us;

// Period between timer overflows, in microseconds.
// Equal to 2^32 / s_timer_ticks_per_us.
static uint32_t s_timer_us_per_overflow;

// When frequency switch happens, timer counter is reset to 0, s_time_base_us
// is updated, and alarm value is re-calculated based on the new APB frequency.
// However because the frequency switch can happen before the final
// interrupt handler is invoked, interrupt handler may see a different alarm
// value than the one which caused an interrupt. This can cause interrupt handler
// to consider that the interrupt has happened due to timer overflow, incrementing
// s_time_base_us. To avoid this, frequency switch hook sets this flag if
// it needs to set timer alarm value to ALARM_OVERFLOW_VAL. Interrupt handler
// will not increment s_time_base_us if this flag is set.
//static bool s_mask_overflow;

#ifdef CONFIG_PM_DFS_USE_RTC_TIMER_REF
// If DFS is enabled, upon the first frequency change this value is set to the
// difference between ssv_timer value and RTC timer value. On every subsequent
// frequency change, s_time_base_us is adjusted to maintain the same difference
// between ssv_timer and RTC timer. (All mentioned values are in microseconds.)
static uint64_t s_rtc_time_diff = 0;
#endif

// Spinlock used to protect access to static variables above and to the hardware
// registers.
//portMUX_TYPE s_time_update_lock = portMUX_INITIALIZER_UNLOCKED;

//Use FRC_TIMER_LOAD_VALUE(1) instead of UINT32_MAX, convenience to change FRC TIMER for future
#define TIMER_IS_AFTER_OVERFLOW(a) (ALARM_OVERFLOW_VAL < (a) && (a) <= FRC_TIMER_LOAD_VALUE(1))

// Check if timer overflow has happened (but was not handled by ISR yet)
static inline bool timer_overflow_happened()
{
    return 0;
}

static inline void timer_count_reload(void)
{

}

void ssv_timer_impl_lock()
{
    BM_EnterCritical();
}

void ssv_timer_impl_unlock()
{
    BM_ExitCritical();
}
#define SYSUSTICKMAX     0xF9FFFFFF //Unit is ms
uint64_t ssv_timer_impl_get_time()/* get us time*/
{
    static uint64_t total_time = 0;
    static uint32_t round_time = 0;
    static uint8_t around = 0;/*is time round overflow*/
    uint64_t value = 0;
    OS_TICKTYPE now = 0;
    //ssv_timer_impl_lock();
    now = OS_GetUsSysTick();//OS_TICKTYPE
    //printf("tr %u\n", now);
    if (round_time < now) {
        round_time = now;// 1 in 48day
        if (total_time) {
            //printf("tr 3s\n");
            value = ((total_time + now));// 3 after a round
        } else {
            //printf("tr 1s\n");
            value = (now);// 1 in 48day
        }
        
    } else if (round_time >= now) {
        around = 1;// 2 after 48day
        total_time += SYSUSTICKMAX;
        round_time = now;
        value = ((total_time + now));
        //printf("tr 2s\n");
    }

    //printf("te %llu\n", value);
    //ssv_timer_impl_unlock();
    return value;
    //return (xTaskGetTickCount()/OS_TICK_RATE_MS)*1000;
    //xTaskGetTickCount() * (1000 / configTICK_RATE_HZ) * 1000;
}

static void timer_alarm_isr(void *arg)
{
    // Call the upper layer handler
    //printf("ttb %llu\n", ssv_timer_impl_get_time());
    (*s_alarm_handler)(arg);    
}

void ssv_timer_handler(OsTimer t)
{
    //printf("tt\n");//werner dbg
    timer_alarm_isr(NULL);
}
OsTimer g_osTimer;
uint64_t g_meshtimestamp = 0;

OsTimer g_osTimer = 0;
#if 1
void ssv_timer_impl_set_alarm(uint64_t timestamp)
{
    uint64_t now = 0;
    uint64_t timer_time = 0;
    uint8_t stoped = 0;
    
    BM_EnterCritical();
    if (!g_osTimer) {
        OS_TimerCreate(&g_osTimer, 20, true, NULL, ssv_timer_handler);
        OS_TimerStart(g_osTimer);
    }
    BM_ExitCritical();
}
#else
uint64_t g_meshtimestamp = 0;
void ssv_timer_impl_set_alarm(uint64_t timestamp)
{
    uint64_t now = 0;
    uint64_t timer_time = 0;
    uint8_t stoped = 0;
    now = ssv_timer_impl_get_time();
    taskENTER_CRITICAL();
    //printf("%s %lld \n", __func__, timestamp);
    // Use calculated alarm value if it is less than ALARM_OVERFLOW_VAL.
    // Note that if by the time we update ALARM_REG, COUNT_REG value is higher,
    // interrupt will not happen for another ALARM_OVERFLOW_VAL timer ticks,
    // so need to check if alarm value is too close in the future (e.g. <2 us away).
    //printf("set timer\n");//werner dbg

    if (timestamp > now)
        timer_time = timestamp - now;
    else {
        //printf("<timestamp %llu %llu\n", timestamp, now);
        timer_alarm_isr(NULL);
        taskEXIT_CRITICAL();
        return;
    }

    if (g_meshtimestamp == (timestamp)) {
        //printf("e  timestamp %llu\n", timestamp);
        taskEXIT_CRITICAL();
        return;
    } else if (g_meshtimestamp) {
        //OS_TimerDelete(g_osTimer);
        if (g_osTimer) {
            OS_TimerStop(g_osTimer);
            stoped = 1;
        }
    }
    //printf("create timer %llu ms\n", timer_time/1000);//werner dbg
    if (g_osTimer) {
        if (!stoped)
            OS_TimerStop(g_osTimer);

        OS_TimerSet(g_osTimer, timer_time/1000, 0, NULL);
    } else
        OS_TimerCreate(&g_osTimer, timer_time/1000, 0, NULL, ssv_timer_handler);

    OS_TimerStart(g_osTimer);
    //printf("ts %llu\n", timestamp);
    g_meshtimestamp = timestamp;
    taskEXIT_CRITICAL();
}
#endif
void ssv_timer_impl_update_apb_freq(uint32_t apb_ticks_per_us)
{
    //printf("%s todo %d\n", __func__, apb_ticks_per_us);
}

void ssv_timer_impl_advance(int64_t time_us)
{
    //printf("%s todo %d\n", __func__, time_us);
}

ssv_err_t ssv_timer_impl_init(intr_handler_t alarm_handler)
{
    s_alarm_handler = alarm_handler;
    return SSV_BM_OK;
}

void ssv_timer_impl_deinit()
{
    //printf("%s \n", __func__);
    OS_TimerDelete(g_osTimer);
}

// FIXME: This value is safe for 80MHz APB frequency.
// Should be modified to depend on clock frequency.

uint64_t ssv_timer_impl_get_min_period_us()
{
    return 50;
}

#ifdef SSV_TIMER_DYNAMIC_OVERFLOW_VAL
uint32_t ssv_timer_impl_get_overflow_val()
{
    return s_alarm_overflow_val;
}

void ssv_timer_impl_set_overflow_val(uint32_t overflow_val)
{
    s_alarm_overflow_val = overflow_val;
    /* update alarm value */
    ssv_timer_impl_update_apb_freq(ssv_clk_apb_freq() / 1000000);
}
#endif // SSV_TIMER_DYNAMIC_OVERFLOW_VAL

