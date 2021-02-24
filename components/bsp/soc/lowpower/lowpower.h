#ifndef LOW_POWER_H
#define LOW_POWER_H

#include "attrs.h"
#include <stdint.h>
#include <sys/time.h>

enum lowpower_option {
    E_LOW_POWER_ACTIVE      = 0,
    E_LOW_POWER_STANDBY     = 1,
    E_LOW_POWER_SLEEP       = 2,  //< Tick will not accuratcy
    //E_LOW_POWER_HIBERNATE   = 2,
};

typedef struct rtc_sleep_st{
    uint32_t passed_ms;
    uint32_t remain_us;
    uint32_t target_count;
}rtc_sleep_st;

extern enum lowpower_option g_lowpower_option;
void lowpower_mode(enum lowpower_option);
enum lowpower_option get_lowpower_mode();
int sys_lowpower_present() ATTRIBUTE_SECTION_FAST_TEXT;
void sys_wifi_power_off() ATTRIBUTE_SECTION_FAST_TEXT;
void sys_wifi_power_on() ATTRIBUTE_SECTION_FAST_TEXT;
void sys_hwif_power_off() ATTRIBUTE_SECTION_FAST_TEXT;
void sys_hwif_power_on() ATTRIBUTE_SECTION_FAST_TEXT;
int sys_sleep(uint32_t) ATTRIBUTE_SECTION_FAST_TEXT;
int sys_sleep_with_pmu(uint32_t) ATTRIBUTE_SECTION_FAST_TEXT;
void sys_lowpower_init();
void sys_hibernate(int, uint32_t) ATTRIBUTE_SECTION_FAST_TEXT;
void sys_save_timer() ATTRIBUTE_SECTION_FAST_TEXT;

uint32_t sys_rtc_tick() ATTRIBUTE_SECTION_FAST_TEXT;
uint32_t sys_rtc_ns_period();


void sys_rtc_cali() ATTRIBUTE_SECTION_FAST_TEXT;
uint32_t sys_stop_clk() ATTRIBUTE_SECTION_FAST_TEXT;
void sys_resume_clk(uint32_t clk) ATTRIBUTE_SECTION_FAST_TEXT;

int32_t sys_dormant(struct timeval *tv) ATTRIBUTE_SECTION_FAST_TEXT;
int sys_sleep_rtc_alarm(uint32_t) ATTRIBUTE_SECTION_FAST_TEXT;
uint32_t sys_timer_min_time() ATTRIBUTE_SECTION_FAST_TEXT;
void sys_timer_restore_time(uint32_t passed_us) ATTRIBUTE_SECTION_FAST_TEXT;
int sys_sleep_rtc(uint32_t) ATTRIBUTE_SECTION_FAST_TEXT;

void sys_rtc_fast(uint32_t step) ATTRIBUTE_SECTION_FAST_TEXT;
void sys_rtc_slow(uint32_t step) ATTRIBUTE_SECTION_FAST_TEXT;
void sys_adjust_dcdc_voltage();

#endif /* end of include guard */
