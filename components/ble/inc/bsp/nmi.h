#ifndef NMI_H
#define NMI_H

typedef enum {
    WDT_DBG         = 0,                // to cli.
    WDT_MCU_RESET   = 1,          // only mcu reset.
    WDT_SYS_RESET   = 2,          // ic reset!!!
    WDT_MAX         = 2,
} SYS_WDT_DEFAULT_SEL;

extern int32_t nmi_set_behavior(SYS_WDT_DEFAULT_SEL act);

#endif /* end of include guard: NMI_H */

