
/*
 * 
 * Author: Tim Li
 *
 */

#ifndef __FOTA_FS_H__
#define __FOTA_FS_H__
#include "fota_flashdrv.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "fota_common.h"
#include "fsal.h"

#define OTA_FS_FW "ota.bin"
#define OTA_FS_MD5 "ota_info.bin"

typedef enum {
    NONE = -1,
    BURN_FS_OK =1
} OTA_FS_FLAG;

#ifdef __cplusplus
}
#endif

#endif  /* __FOTA_FS_H__ */
