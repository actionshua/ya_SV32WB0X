#ifndef SYS_INFO_
#define SYS_INFO_

/**
 * @brief Reset reasons
 */
typedef enum {
    RST_UNKNOWN,    //!< Reset unknown
    RST_POWERON,    //!< Reset by power-on
    RST_MCU_WDT,    //!< Reset by mcu watchdog
    RST_SYS_WDT,    //!< Reset by sys watchdog
    RST_SDIO,       //!< Reset by SDIO
    RST_SPI,        //!< Reset by SPI
} reset_reason_t;

/**
 * @brief  Get reason of last reset
 * @return See description of reset_reason_t for explanation of each value.                                                                          
 */
reset_reason_t sys_reset_reason(void);
void sys_rom_invaild(int version);

char *sys_mcu_info(char *buf, int len);
#endif /* end of include guard */
