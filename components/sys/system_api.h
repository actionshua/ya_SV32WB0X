#ifndef _SYSTEM_API_H
#define _SYSTEM_API_H

#include <stdio.h>
#include <string.h>
#include "soc_defs.h"
#include "soc_types.h"
#include "osal.h"
#include "flash.h"

typedef enum {
    OTA_NOT_SUPPORT =0,
    OTA_FS = 1,
    OTA_PING_PONG = 2,
    OTA_UNKNOWN
} OTA_METHOD_TYPE;

/**
  * @brief  Write data into flash with protection.
  *
  *         Flash read/write has to be 4-bytes aligned.
  *
  * @param  uint16_t offset : offset of data saved in user raw partition
  * @param  void *param : pointer of the data to be written
  * @param  uint16_t len : write data length
  * @param  bool backup_en :  backup_en =1, then SETTING_PARTITION_USER_RAW_SIZE cat to 3 sectors
  *             (sector 0 and sector 1 size is (SETTING_PARTITION_USER_RAW_SIZE - 4KB)/2, sector 2 size is 4KB) ,
  *              sector 0 and sector 1 are data sectors, back up each other, save data alternately, sector 2 is flag sector, 
  *              point out which sector is keeping the latest data, sector 0 or sector 1.  backup_en = 0, then only sector 0
  *             (sector 0 size is SETTING_PARTITION_USER_RAW_SIZE)
  *
  * @return true  : 0
  * @return false : -1
  */
int32_t system_save_raw_with_protect(uint16_t offset, void *param, uint16_t len, bool backup_en);

/**
  * @brief  Read the data saved into flash with the read/write protection.
  *
  *         Flash read/write has to be 4-bytes aligned.
  *
  * @param  uint16_t offset : offset of data load in user raw partition
  * @param  void *param : pointer of the data to be read
  * @param  uint16_t len :  read data length
  * @param  bool backup_en :  backup_en =1, then SETTING_PARTITION_USER_RAW_SIZE cat to 3 sectors
  *             (sector 0 and sector 1 size is (SETTING_PARTITION_USER_RAW_SIZE - 4KB)/2, sector 2 size is 4KB) ,
  *              sector 0 and sector 1 are data sectors, back up each other, save data alternately, sector 2 is flag sector, 
  *              point out which sector is keeping the latest data, sector 0 or sector 1.  backup_en = 0, then only sector 0
  *             (sector 0 size is SETTING_PARTITION_USER_RAW_SIZE)
  *
  * @return true  : 0
  * @return false : -1
  */
int32_t system_road_raw_with_protect(uint16_t offset, void *param, uint16_t len, bool backup_en);

/**
  * @brief     Get information of the boot version.
  *
  * @param     null
  *
  * @return    Information of the boot version.
  */
const char *system_get_boot_version(void);

/**
  * @brief  Get the current Flash size.
  *
  * @param  null
  *
  * @return total flash size (KB)
  */
uint32_t  system_get_flash_size();

/**
  * @brief  Get the current main partition size.
  *
  * @param  null
  *
  * @return main partition size (KB)
  */
uint32_t  system_get_main_size();

/**
  * @brief  Get the current fota method
  *
  * @param  null
  *
  * @return enum OTA_METHOD_TYPE
  */
OTA_METHOD_TYPE  system_get_fota_method();

/**
  * @brief  Get the address of the current running user bin.
  *
  * @param  null
  *
  * @return The address of the current running  bin.
  */
uint32_t system_get_userbin_addr( );

#endif // _FLASH_H
