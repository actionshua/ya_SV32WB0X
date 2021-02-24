#ifndef _OTA_SSV_SPIFFS_H
#define _OTA_SSV_SPIFFS_H

#include <stdint.h>
#include "ota_spiffs.h"
#include "ota_spiffs_config.h"
#include "ota_spiffs_nucleus.h"

spiffs* OTA_SPIFFS_init(uint32_t addr, uint32_t size);
uint32_t OTA_SPIFFS_find_and_check(void);
uint32_t OTA_SPIFFS_find_and_update(void);

#endif
