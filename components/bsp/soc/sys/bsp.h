#ifndef BSP_H
#define BSP_H

#if defined(SUPPORT_FFS)
#include "fsal.h"
#endif
#include "osal.h"
#include <attrs.h>

extern OsTimer g_rtc_cali_tmr;
#if defined(SUPPORT_FFS)
extern SSV_FS fs_handle;
#endif
extern unsigned int __fota_option;
void bsp_init();

uint32_t system_us2delaytick(uint32_t us) ATTRIBUTE_SECTION_FBOOT;
void system_delay(uint32_t delaytick) ATTRIBUTE_SECTION_FBOOT;
int lowpower_dormant_gpio_hook() ATTRIBUTE_SECTION_FAST;
int lowpower_sleep_gpio_hook() ATTRIBUTE_SECTION_FAST;
void lowpower_pre_sleep_hook() ATTRIBUTE_SECTION_FAST;
void lowpower_post_sleep_hook() ATTRIBUTE_SECTION_FAST;

int system_has_ilm(void) ATTRIBUTE_SECTION_FAST;
int system_has_dlm(void) ATTRIBUTE_SECTION_FAST;
#endif /* end of include guard: BSP_H */
