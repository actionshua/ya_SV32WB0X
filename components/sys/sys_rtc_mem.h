#ifndef _SYS_RTC_MEM
#define _SYS_RTC_MEM

#include <stdint.h>
enum sys_rtc_mem_result{
    SYS_RTC_MEM_FAILED      = 0,
    SYS_RTC_MEM_SUCCESS     = 1,
};

enum sys_rtc_mem_result sys_rtc_mem_read(uint32_t src, void *dst, uint32_t n);
enum sys_rtc_mem_result sys_rtc_mem_write(uint32_t dst, void *src, uint32_t n);

#endif /* end of include guard */
