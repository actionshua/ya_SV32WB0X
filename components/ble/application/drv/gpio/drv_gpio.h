#include "pcb_config.h"

#if (MAIN_CHIP == P7003)
    #include "p7003/drv_gpio_internal.h"
#elif (MAIN_CHIP == P7005)
    #include "p7005/drv_gpio_internal.h"
#else
#error please check your main chipid.
#endif
