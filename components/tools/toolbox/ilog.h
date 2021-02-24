#ifndef ILOG_H
#define ILOG_H

#include <stdint.h>
#include "logger.h"
#include "attrs.h"

// for 32bits buffer.
#define BUFFER_TYPE_32BITS      (1)

// for select baudrate 115200 or 230400
#define ILOG_SPEED              (115200)


#define M_SEVERITY_MASK         (0x7)
#define M_TASK_SRC_MASK         (0xFFC00000)
#define M_TASK_SRC_POS          (22)

#define M_TASK_DST_MASK         (0x003FF000)
#define M_TASK_DST_POS          (12)

#define M_LOG_TYPE_MASK             (0x00000F00)
#define M_LOG_TYPE_POS              (8)

#define M_LOG_TASK_ALWAYS_OUTPUT    (0)


#define M_ILOG_BUFFER_SIZE      (512)    /// Enlarge it temporally for debugging.
#define M_ILOG_INDICATOR        (0xB3)
#define M_ILOG_DUMP_INDICATOR   (0xB4)
#define M_ILOG_STATUS_INDICATOR (0xB6)

#define M_MAX_MEM_DUMP_SIZE     (64)

#define LEGACY_LOG      (1)

#define DIR_HOST_TO_CTRL   0x01
#define DIR_CTRL_TO_HOST   0x02

enum E_LOG_TYPE {
    LOG_TYPE_NORMAL,
    LOG_TYPE_MSG,

    LOG_T_NORMAL    = (LOG_TYPE_NORMAL << M_LOG_TYPE_POS),
    LOG_T_MSG       = (LOG_TYPE_MSG << M_LOG_TYPE_POS),
};

enum E_TASK {
    // max 10 types.
    TASK_HOST       = (0x01),
    TASK_LL         = (0x02),
    TASK_APP        = (0x04),
    TASK_L2CAP      = (0x08),
    TASK_SMP        = (0x10),
    TASK_ATT        = (0x20),
    TASK_GAP        = (0x40),

    TASK_DST_HOST   = (TASK_HOST << M_TASK_DST_POS),
    TASK_DST_LL     = (TASK_LL << M_TASK_DST_POS),
    TASK_DST_APP    = (TASK_APP << M_TASK_DST_POS),
    TASK_DST_L2CAP  = (TASK_L2CAP << M_TASK_DST_POS),
    TASK_DST_SMP    = (TASK_SMP << M_TASK_DST_POS),
    TASK_DST_ATT    = (TASK_ATT << M_TASK_DST_POS),
    TASK_DST_GAP    = (TASK_GAP << M_TASK_DST_POS),

    TASK_SRC_HOST   = (TASK_HOST << M_TASK_SRC_POS),
    TASK_SRC_LL     = (TASK_LL << M_TASK_SRC_POS),
    TASK_SRC_APP    = (TASK_APP << M_TASK_SRC_POS),
    TASK_SRC_L2CAP  = (TASK_L2CAP << M_TASK_SRC_POS),
    TASK_SRC_SMP    = (TASK_SMP << M_TASK_SRC_POS),
    TASK_SRC_ATT    = (TASK_ATT << M_TASK_SRC_POS),
    TASK_SRC_GAP    = (TASK_GAP << M_TASK_SRC_POS),
};

typedef uint16_t idx_t;

#define GET_SIZE(ring) \
    (ring.size)

#define GET_SIZE_U32(ring) \
        (ring.size >> 2)

#define POWER_TWO_CHECK(M) \
    STATIC_ASSERT((((M)-1)&(M)) == 0, #M " must power of 2")

#define M_INC_INDEX(idx) \
    ((idx+1) & (M_ILOG_BUFFER_SIZE-1))



typedef struct _log_st {
    struct _log_ring_st{
        idx_t start, end;
        uint8_t buffer[M_ILOG_BUFFER_SIZE];
        uint16_t size;
    } ring;
} log_st;
extern log_st g_log_data;

extern log_level_t g_log_sw;
extern enum E_TASK g_log_task_sw;

extern void ilog_hcilog_init();
extern int icomm_log(int param_count, ...) ATTRIBUTE_SECTION_FAST;
extern int icomm_blocking_log(int param_count, ...);
extern int icomm_memdump(uint8_t severity, uint8_t *ptr, int len);
extern int icomm_string(const uint8_t *ptr);
extern int icomm_stringln(const uint8_t *ptr);
extern int icomm_status(int status_id, int status);
extern void ilog_init();
extern void *ilog_get_cli();
extern void ilog_level(s32 argc, s8 **argv);
extern void ilog_task(s32 argc, s8 **argv);


typedef int (*pf_icomm_putc)(uint8_t c);

#define __MACRO_EXPAND(x) x 
#define __MACRO_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20 , N, ...) N 
#define __MACRO_NARG_PLUS_ONE(...) __MACRO_EXPAND(__MACRO_ARG_N(__VA_ARGS__, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))

#ifdef SUPPORT_ILOG
#define IDUMP(CRIT, p, l) \
    do { \
        if (g_log_sw >= (CRIT)) { \
                icomm_memdump((CRIT), (p), (l)); \
        } \
    } while(0)

#define ILOG(CRIT, ...) \
    do { \
        if ((g_log_sw) >= CRIT) { \
            icomm_log(__MACRO_NARG_PLUS_ONE(__VA_ARGS__), CRIT,  __VA_ARGS__); \
        } \
    } while(0)

#define ILOGB(CRIT, ...) \
    do { \
        if ((g_log_sw) >= CRIT) { \
            icomm_blocking_log(__MACRO_NARG_PLUS_ONE(__VA_ARGS__), CRIT,  __VA_ARGS__); \
        } \
    } while(0)
#define ILOGM(MODULE, CRIT, ...) \
        do { \
            if ((g_log_sw) >= (CRIT)) { \
                if (M_LOG_TASK_ALWAYS_OUTPUT | (g_log_task_sw & TASK_SRC_##MODULE)) { \
                    icomm_log(__MACRO_NARG_PLUS_ONE(__VA_ARGS__), (CRIT) | (TASK_SRC_##MODULE) | (LOG_T_NORMAL),  __VA_ARGS__); \
                } \
            } \
        } while(0)
#else
#define IDUMP(CRIT, p, l)
#define ILOG(CRIT, ...)
#define ILOGB(CRIT, ...)
#define ILOGM(MODULE, CRIT, ...)
#endif

#define ILOGB_INFO(...) ILOGB(LOG_INFO, __VA_ARGS__)

#define ILOG_INFO(...) ILOG(LOG_INFO, __VA_ARGS__)
#define ILOG_DBG(...)  ILOG(LOG_DBG, __VA_ARGS__)
#define ILOG_WARN(...) ILOG(LOG_WARN, __VA_ARGS__)



#define LL_ILOG(...) \
    ILOGM(LL, __VA_ARGS__)

#define HOST_ILOG(...) \
    ILOGM(HOST, __VA_ARGS__)

#define APP_ILOG(...) \
    ILOGM(APP, __VA_ARGS__)

#define SMP_ILOG(...) \
    ILOGM(SMP, __VA_ARGS__)

#define L2CAP_ILOG(...) \
    ILOGM(L2CAP, __VA_ARGS__)

#define ATT_ILOG(...) \
    ILOGM(ATT, __VA_ARGS__)

#define GAP_ILOG(...) \
    ILOGM(GAP, __VA_ARGS__)

#if (LEGACY_LOG == 1)
#define log_num(num) \
    ILOG_INFO("0x%X", num)

#define log_str(str) \
    ILOG_INFO("%s", str)

#define log_num_dec(num) \
    ILOG_INFO("%d", num)
#endif

extern void ouput_hcilog(u8 direct, u8 *cmd, u8 cmdlen);
extern void ouput_hcilog_2(u8 direct, u8 cmdtype, u8 *cmd, u8 cmdlen);
#ifdef SUPPORT_HCILOG
#define HCILOG(dir, cmd, cmdlen) ouput_hcilog(dir, cmd, cmdlen)
#define HCILOG_2(dir, cmdtype, cmd, cmdlen) ouput_hcilog_2(dir, cmdtype, cmd, cmdlen)
#else
#define HCILOG(dir, cmd, cmdlen)
#define HCILOG_2(dir, cmdtype, cmd, cmdlen)
#endif

#endif /* end of include guard: ILOG_H */
