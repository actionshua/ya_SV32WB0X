#ifndef INTL_PMU_H
#define INTL_PMU_H

#include <condor.h>
#include <stdint.h>

__STATIC_INLINE uint32_t pmu_get_sys_rtc_time() {
    return CONDOR_CSR_PMU->SYS_RTC_TIME << 1;
}


#endif /* end of include guard: INTL_PMU_H */
