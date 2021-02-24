#ifndef _DRV_PHY_H_
#define _DRV_PHY_H_

// # for PHY_WRITE
#include "bsp/bsp.h"
#include "condor_ssv_lib.h"

#ifndef MAIN_CHIP
#error ! missing main chip-id define
#endif  // MAIN_CHIP

#if (MAIN_CHIP == P7003)
#include "inc/regs/p7003_reg.h"
#elif (MAIN_CHIP == P7005)
#include "soc_regs.h"
#else
#error ! drv_phy: not supported chip-id
#endif // MAIN_CHIP

#define DRV_PHY_RX_ACCESS_TIME_INIT(_US_) PHY_WRITE(ADR_PHY_RX_ACC_TIMER, ((u32)(_US_)))

typedef enum {
    RF_POWER_DBM_MINUS_45   = 0 ,
    RF_POWER_DBM_MINUS_7    = 1 ,
    RF_POWER_DBM_2          = 2 ,
    RF_POWER_DBM_8          = 3
} RF_POWER;

extern NV_DATA u32 g_phy_agc_enable ;

s32     drv_phy_init();
u32     drv_phy_set_rfch(u32 rfch);
void    drv_phy_agc_config();

static inline void drv_phy_set_tx_power(RF_POWER power_level){
//    SET_RF_PWR(power_level);
}

s8          drv_phy_tx_power_to_dbm     (RF_POWER   value);
RF_POWER    drv_phy_tx_power_to_value   (s8         dbm);
#endif
