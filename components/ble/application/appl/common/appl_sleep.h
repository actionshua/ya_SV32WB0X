#ifndef _APPL_SLEEP_H_
#define _APPL_SLEEP_H_


#include "stdint.h"



void appl_sleep_init(void);
void appl_sleep_enable(void);
void appl_sleep_disable(void);
void appl_sleep_perform(void);
void appl_sleep_deinit(void);



#endif  /// end of _APPL_SLEEP_H_
