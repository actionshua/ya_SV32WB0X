#ifndef _OTA_SSV_LITTEFS_H
#define _OTA_SSV_LITTEFS_H

#include <stdint.h>
#include "ota_lfs.h"
#include "ota_lfs_util.h"

int OTA_LITTLEFS_init(uint32_t addr, uint32_t size);
uint32_t OTA_LITTLEFS_find_and_check();
uint32_t OTA_LIEELEFS_find_and_update();

#endif
