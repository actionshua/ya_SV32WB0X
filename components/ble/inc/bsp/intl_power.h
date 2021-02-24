#ifndef INTL_POWER_H
#define INTL_POWER_H


#include "ssv_types.h"
#include <stdint.h>

union ble_wakelock{
    uint32_t wakelock;
    struct {
        union {
            uint8_t host;
            struct {
                uint8_t b0:1;
                uint8_t b1:1;
                uint8_t b2:1;
                uint8_t b3:1;
                uint8_t b4:1;
                uint8_t b5:1;
                uint8_t b6:1;
                uint8_t b7:1;
            } host_b;
        };
        union {
            uint8_t ll;
            struct {
                uint8_t b0:1;
                uint8_t b1:1;
                uint8_t b2:1;
                uint8_t b3:1;
                uint8_t b4:1;
                uint8_t b5:1;
                uint8_t b6:1;
                uint8_t b7:1;
            } ll_b;
        };
        union {
            uint8_t bsp;
            struct {
                uint8_t b0:1;
                uint8_t b1:1;
                uint8_t b2:1;
                uint8_t b3:1;
                uint8_t b4:1;
                uint8_t b5:1;
                uint8_t b6:1;
                uint8_t b7:1;
            } bsp_b;
        };
        union {
            uint8_t appl;
            struct {
                uint8_t b0:1;
                uint8_t b1:1;
                uint8_t b2:1;
                uint8_t b3:1;
                uint8_t b4:1;
                uint8_t b5:1;
                uint8_t b6:1;
                uint8_t b7:1;
            } appl_b;
        };
        //uint8_t host, ll, bsp, appl;
    } component;
};

struct ble_lp_param {
    // anchor_tick = rtc_tick*anchor_rtc_convert_mul/anchor_rtc_convert_div
    uint16_t    anchor_rtc_convert_mul;
    uint16_t    anchor_rtc_convert_div;
    uint32_t    long_sleep;
    uint32_t    hibernate_min;
    uint32_t    hibernate_gap;
    uint32_t    sleep_min;
    uint32_t    sleep_gap;
    uint8_t     timer_restore;
};

#define ONLY_SLEEP         (2)

extern const struct ble_lp_param g_pmu_lp_param;

extern union ble_wakelock g_pmu_ble_wakelock;

#endif /* end of include guard: INTL_POWER_H */
