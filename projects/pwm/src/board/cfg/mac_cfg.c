#include <stdint.h>
#include <string.h>
struct wifi_cfg {
    char mac_string[4096];
};

#define M_MAC_ADDR_SIZE      (36)

const struct wifi_cfg g_wifi_cfg __attribute__((section(".cfg_mac_data"))) = {
    .mac_string = 
    {
#include "mac_raw.h"
        , 0x00
    }
};
