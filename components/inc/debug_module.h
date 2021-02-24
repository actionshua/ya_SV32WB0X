#include "soc_types.h"
#include <stdio.h>

#define DEBUG_MODUE_EN          (0)

#define DEBUG_GROUP_MAC_REPTER  ((0x1) << 0)
#define DEBUG_GROUP_NET_REPTER  ((0x1) << 1)

#define DEBUG_LEVEL_BASIC       (0)
#define DEBUG_LEVEL_ERROR       (1)
#define DEBUG_LEVEL_WARM        (2)
#define DEBUG_LEVEL_INFO        (3)

extern u8 g_debug_level;
extern u32 g_debug_group_bitmap;

#if (DEBUG_MODUE_EN == 1)
#define DEBUG_LOG(group, level, format, args...) \
    {   \
        if ((DEBUG_GROUP_##group & g_debug_group_bitmap) != 0) { \
            if (DEBUG_LEVEL_##level <= g_debug_level) { \
                printf("[%s:%d] "format, __FILE__, __LINE__, ##args); \
            } \
        } \
    }
#else
#define DEBUG_LOG(group, level, format, args...)
#endif
