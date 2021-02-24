#ifndef DRV_ANCHOR_H
#define DRV_ANCHOR_H

#include "condor.h"
#include "condor_ssv_lib.h"
#include "pcb_config.h"
#include "regs/chip_reg.h"

#define M_RTC_WAIT_TWO_TICK     (1)
#define BLE_LL_HWIF_CLOCK_TIME_BW       (28)

#define M_SYS_TICK_MAX  ((1<<(BLE_LL_HWIF_CLOCK_TIME_BW-1))-1)
#define USE_INLINE (1)

// +150994943~-150994944
typedef union {
    volatile u32 data;
    volatile struct {
        s32 val:BLE_LL_HWIF_CLOCK_TIME_BW;
        u32 rsv:(32-BLE_LL_HWIF_CLOCK_TIME_BW);
    } time;
} sys_tick_st;

#if (USE_INLINE == 1)
// static inline reduce code size.
//extern sys_tick_st bsp_anchor_get_tick();
__STATIC_INLINE sys_tick_st bsp_anchor_get_tick()
{
#if 1
    sys_tick_st ret;
    ret.data = CONDOR_LL_FUNC_REG->ANCHOR_ACTIVE_TIME;
    return (sys_tick_st)ret;
#endif
//    sys_tick_st ret;
//    return (sys_tick_st)ret;
}
__STATIC_INLINE void bsp_anchor_set_tick(sys_tick_st tick)
{
#if 1
    CONDOR_LL_FUNC_REG->ANCHOR_ACTIVE_TIME = tick.data;
#endif
}

__STATIC_INLINE void bsp_anchor_start_tick()
{
#if 1
    CONDOR_LL_FUNC_REG->ANCHOR_CONTROL = 1;
#endif
}

__STATIC_INLINE void bsp_anchor_stop_tick()
{
#if 1
    CONDOR_LL_FUNC_REG->ANCHOR_CONTROL = 0;
#endif
}

#ifndef MAIN_CHIP
#error ! MAIN_CHIP not defined
#endif
__STATIC_INLINE void bsp_anchor_init()
{
#if 1
#if (MAIN_CHIP == P7003)
    SET_PRESCALER_LLTIMER(0x20);    // (32M)
#elif (MAIN_CHIP == P7005)
    SET_PRESCALER_LLTIMER(0x08);    // (8M)

    SET_LL_CLK_ASYNC_EN(1);
//    SET_ON1_SYS_CK_SEL(2);
#endif
    CONDOR_CSR_LL_REG_A2->LL_ENGINE_EN_b.ANCHOR_EN = 1;
#endif
}

__STATIC_INLINE sys_tick_st bsp_anchor_after(sys_tick_st base, sys_tick_st tick)
{
#if 1
    return (sys_tick_st){.time.val = base.time.val + tick.time.val};
#endif
//    sys_tick_st ret;
//    return (sys_tick_st)ret;
}


__STATIC_INLINE sys_tick_st bsp_anchor_get_tick_sync_rtc()
{
#if 0
#if (MAIN_CHIP == P7003)
    sys_tick_st ret;
    CONDOR_CSR_PMU->SYS_RTC_CLR = 1;
    do {
    } while(CONDOR_CSR_PMU->SYS_RTC_TIME != 0);
#if (M_RTC_WAIT_TWO_TICK == 1)
    do {
    } while(CONDOR_CSR_PMU->SYS_RTC_TIME != 1);
#endif
    ret.data = CONDOR_LL_FUNC_REG->ANCHOR_ACTIVE_TIME;
    return (sys_tick_st)ret;
#elif (MAIN_CHIP == P7005)
    sys_tick_st ret;
    CONDOR_CSR_PMU->SYS_RTC_CLR = 1;
    do {
    } while((CONDOR_CSR_PMU->SYS_RTC_TIME>>1) != 0);
#if (M_RTC_WAIT_TWO_TICK == 1)
    do {
    } while((CONDOR_CSR_PMU->SYS_RTC_TIME>>1) != 1);
#endif
    ret.data = CONDOR_LL_FUNC_REG->ANCHOR_ACTIVE_TIME;
    return (sys_tick_st)ret;
#else
#error please check your chipid.
#endif
#endif
    sys_tick_st ret;
    return (sys_tick_st)ret;
}

#else

sys_tick_st bsp_anchor_get_tick();
void bsp_anchor_set_tick(sys_tick_st *tick);
void bsp_anchor_start_tick();
void bsp_anchor_stop_tick();
void bsp_anchor_init();
sys_tick_st bsp_anchor_get_tick_sync_rtc();

#endif

#endif /* end of include guard: DRV_ANCHOR_H */
