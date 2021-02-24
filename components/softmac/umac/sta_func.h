#ifndef __STA_FUNC_H__
#define __STA_FUNC_H__

#include "soc_types.h"
#include "wificonf.h"

extern IEEE80211STATUS gwifistatus;;
void set_mrx_filter_sta();
void init_sta_conf();
void deinit_sta();

#endif

