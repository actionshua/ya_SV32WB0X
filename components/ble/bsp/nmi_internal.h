#ifndef NMI_INTERNAL_H
#define NMI_INTERNAL_H

#define M_NMI_MAGIC_NUMBER          (0x0EADBEEF)
//extern volatile s32 g_cs_nesting;

#define M_MCU_RESET_DISABLE() \
    do { CONDOR_MCU_WDT_REG->MCU_WDOG_ENABLE = 0; } while(0)
#define M_SYS_RESET_DISABLE() \
    do { CONDOR_SYS_WDT_REG->SYS_WDOG_ENABLE = 0; } while(0)

typedef struct {
    uint32_t sp, ipc, lp, oipc;
    SYS_WDT_DEFAULT_SEL wdt_behavior;
} nmi_status_st;

#define M_NMI_GET_MCU_STATUS() \
    do { \
    __asm__( \
            "move   %0, $lp\n" \
            "mfsr   %1, $ipc\n" \
            "mfsr   %2, $oipc\n" \
            "move   %3, $sp\n" \
            : "=r" (sg_nmi_status.lp), "=r" (sg_nmi_status.ipc), \
              "=r" (sg_nmi_status.oipc), "=r" (sg_nmi_status.sp)); \
    } while(0)

#define M_NMI_DUMP_MCU_STATUS() \
    do { \
        ILOG_INFO("sp: 0x%x\n", sg_nmi_status.sp); \
        ILOG_INFO("ipc: 0x%x\n", sg_nmi_status.ipc); \
        ILOG_INFO("oipc: 0x%x\n", sg_nmi_status.oipc); \
        ILOG_INFO("lp: 0x%x\n", sg_nmi_status.lp); \
    } while(0)

#endif /* end of include guard: NMI_INTERNAL_H */
