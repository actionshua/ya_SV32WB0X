
#include "ya_common.h"

#define YA_WITHOUT_HARDWARE_TIMER

#ifndef YA_WITHOUT_HARDWARE_TIMER
gtimer_t my_timer1;
#else
uint64_t  ya_start_timer = 0;
uint64_t  ya_end_timer = 0;
#endif

void ya_hal_hardware_timer_start(void)
{
#ifndef YA_WITHOUT_HARDWARE_TIMER
	gtimer_start(&my_timer1);
#endif
}

void ya_hal_hardware_timer_stop(void)
{
#ifndef YA_WITHOUT_HARDWARE_TIMER
	gtimer_stop(&my_timer1);
#endif
}

extern void sys_abstime_running(void);
void sys_start_abstime(void)
{	
	#ifndef YA_WITHOUT_HARDWARE_TIMER
    gtimer_init(&my_timer1, TIMER2);
    gtimer_start_periodical(&my_timer1, 1000000, (void*)sys_abstime_running, 0);
	#else
	ya_start_timer = ya_hal_os_ticks_to_msec();
	ya_end_timer = ya_hal_os_ticks_to_msec();
	#endif
}

extern void sys_update_cloud_time(uint8_t second_add);
void sys_run_abstime_1s(void)
{
#ifdef YA_WITHOUT_HARDWARE_TIMER
	ya_end_timer = ya_hal_os_ticks_to_msec();
	if(ya_timer_compare(ya_start_timer, ya_end_timer, 1000) == 0)
	{
		sys_update_cloud_time(1);		
		ya_start_timer += 1000;
	}
#endif

}


