#ifndef _MSTICK_H_
#define _MSTICK_H_

#include "soc_defs.h"

void mstick_set_period(uint32_t ms);
uint32_t mstick_remain_count(void);
void mstick_stop(void);
void mstick_mdelay(uint32_t ms);

#endif
