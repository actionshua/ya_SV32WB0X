#ifndef RC32_CALI_H
#define RC32_CALI_H

#define _NEW_CALI       (1)
#include <stdint.h>

#define M_TIMER_UNIT            (1024)
// for fine cali osf. > 297uS+33uS(start do sync when phy to 32K.)
#define M_TIMER_FAST            (256+128)
// for corase cali osf. > 33uS+33uS
#define M_TIMER_HURRY           (128)
#define M_TIMER_NORMAL           (1024)
typedef enum {
    SYS_32K_RC_1000MS_CALI      =   0x11,
    SYS_32K_RC_2000MS_CALI      =   0x12,
    SYS_32K_RC_4000MS_CALI      =   0x14,
    SYS_32K_RC_10000MS_CALI     =   0x18,
    SYS_32K_RC_16000MS_CALI     =   0x30,
} SYS_32K_SEL;

typedef struct {
    int16_t coarse_coffset;
    int16_t coarse_repeat_times;
    int16_t coarse_osf;
    int16_t coarse_waitl;
    int16_t coarse_avg;

    int16_t fine_roffset;
    int16_t fine_repeat_times;
    int16_t fine_osf;
    int16_t fine_waitl;
    int16_t fine_avg;
    int16_t rc_cnt;

    uint16_t sw1_low_threshold;
    uint16_t sw1_high_threshold;
    int8_t   sw2_plus_delta_by_sw1_overflow;
    int8_t   sw2_minus_delta_by_sw1_overflow;
    int8_t  sw1_jump_delta_when_overflow;
} RC32_CFG_ST;

extern const RC32_CFG_ST g_rc32_cfg;

extern void rc32_init();
extern int32_t rc32_setup_cali(SYS_32K_SEL);

#endif /* end of include guard: RC32_CALI_H */
