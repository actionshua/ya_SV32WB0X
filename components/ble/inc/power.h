#ifndef POWER_H
#define POWER_H

#define LOW_POWER_DBG           (1)
#include "ssv_types.h"
#include "lestack/drv/anchor/drv_anchor.h"

#define M_BOOT_FROM_OFF         (0x00)
#define M_BOOT_FROM_SLEEP       (0x02)
#define M_BOOT_FROM_HIBERNATE   (0x03)
#define M_BOOT_FROM_DORMANT     (0x04)

#if defined(MAIN_CHIP) && (MAIN_CHIP == P7005)
#endif

#define DISABLE_SLEEP_FUNC 1
#define ENABLE_SLEEP_FUNC 0

enum E_WAKEUP_REASON{
//    E_WAKEUP_USER,
    E_WAKEUP_LL,
    E_WAKEUP_MAX,
};

typedef enum {
    E_LP_NO_SLEEP       = 0,
    E_LP_CLK_GATTING    = 1,

    // system will reboot
    E_LP_SLEEP          = 2,
    E_LP_HIBERNATE      = 3,
} SYS_LOW_POWER_SEL;

typedef enum {
    E_SLEEP_NO_TIME_MS1_FAILED          = -10,
    E_SLEEP_NO_TIME_MS0_FAILED          = -9,
    E_SLEEP_NO_TIME_US1_FAILED          = -8,
    E_SLEEP_NO_TIME_US0_FAILED          = -7,
    E_SLEEP_NO_SLEEP_LOCKED             = -6,
    E_SLEEP_NOT_ENTER_BY_CAN_SLEEP      = -5,
    E_SLEEP_NOT_ENTER_NO_SLEEP          = -4,
    E_SLEEP_DEEP_MODE_FAILED            = -3,
    E_SLEEP_NO_TIME_FAILED              = -2,
    E_SLEEP_FREE_TIME_FAILED            = -1,
    E_SLEEP_SUCCESS                     = 0,
} SYS_SLEEP;


#if defined(LOW_POWER_DBG) && (LOW_POWER_DBG == 1)
extern NV_DATA u32 g_lp_dbg_tbl[3];
#endif
//void power_restore_anchor();

void power_init();
//void set_wakeup_time(enum E_WAKEUP_REASON reason, sys_tick_st time);
//void set_wakeup_difftime(enum E_WAKEUP_REASON reason, sys_tick_st time);
bool is_cold_boot();

s32 do_sleep();
extern s32 pmu_setup_sleep(SYS_LOW_POWER_SEL new_opt);

typedef s32 (*pf_do_sleep)();
typedef bool (*pf_is_cold_boot)();

extern NV_DATA u32 g_can_sleep;
extern NV_DATA sys_tick_st g_bsp_power_sleep_offset, g_bsp_power_anchor_buffer;
extern NV_DATA u8 g_pmu_flash_low_power;
//extern NV_DATA u32 g_pmu_hw_timer[];

struct pmu_hw_timer_store{
    u32 cnt           : 24;
    u32 enable        : 1;
    u32 mask          : 1;
};
extern struct pmu_hw_timer_store g_pmu_hw_timer_cfg[4];
extern NV_DATA struct mcu_priority g_pmu_restore_mcu_priority;
extern NV_DATA u32 g_pmu_restore_intc;
extern NV_DATA uint32_t g_pmu_restore_mcu_irq;
//extern void pmu_restore();

#endif /* end of include guard: POWER_H */
