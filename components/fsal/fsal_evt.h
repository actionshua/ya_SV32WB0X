#ifndef _FSAL_EVT_H_
#define _FSAL_EVT_H_

typedef enum {
    SSV_FLASH_ERR,
#ifdef SUPPORT_SDC
    SSV_SDC_PLUGIN,
    SSV_SDC_UNPLUG,
#endif
} SSV_FS_EVENT;

#endif
