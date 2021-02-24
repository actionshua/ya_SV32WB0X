#ifndef CS_H
#define CS_H

#include "ssv_types.h"
#include "condor.h"


struct bsp_ap_cs_locker
{
    uint32_t stat;
};

SSV_API void app_cs_init(struct bsp_ap_cs_locker*);
SSV_API void app_cs_enter(struct bsp_ap_cs_locker*);
SSV_API void app_cs_leave(struct bsp_ap_cs_locker*);
SSV_API void app_cs_deinit(struct bsp_ap_cs_locker*);

#endif /* end of include guard: CS_H */
