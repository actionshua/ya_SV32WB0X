/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
//TODO: add SDTYPE & FLASHTYPE to common.h
#define SDTYPE 1
#define FLASHTYPE 2
#if CONFIG_STORAGE_TYPE == SDTYPE
#include "sd_diskio.h"
#elif CONFIG_STORAGE_TYPE == FLASHTYPE
#include "flash_diskio.h"
#endif
/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
#if CONFIG_STORAGE_TYPE == SDTYPE
	return (DSTATUS)sd_disk_status();
#elif CONFIG_STORAGE_TYPE == FLASHTYPE
	return 0;
#endif
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
#if CONFIG_STORAGE_TYPE == SDTYPE
	return (DSTATUS)sd_disk_initialize();
#elif CONFIG_STORAGE_TYPE == FLASHTYPE
	return 0;
#endif
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
#if CONFIG_STORAGE_TYPE == SDTYPE
	if(sd_disk_read(buff, sector, count))
		return RES_PARERR;
	else
		return RES_OK;
#elif CONFIG_STORAGE_TYPE == FLASHTYPE
	return 0;
#endif
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
#if CONFIG_STORAGE_TYPE == SDTYPE
	if(sd_disk_write((uint8_t *)buff, sector, count))
	        return RES_PARERR;
        else
                return RES_OK;
#elif CONFIG_STORAGE_TYPE == FLASHTYPE
	return 0;
#endif
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
#if CONFIG_STORAGE_TYPE == SDTYPE
	DRESULT res;

	switch (cmd) {
	case CTRL_SYNC:
		if(sd_disk_sync())
		{
			return RES_ERROR;
		}
		return RES_OK;
	case GET_SECTOR_COUNT:
		res = sd_disk_sectors();
		if(res > 0){
			*((DWORD*)buff) = res;
			return RES_OK;
		}
		else
		{
			return RES_ERROR;
		}
	case GET_SECTOR_SIZE:
		*(DWORD*)buff = 512;
		return RES_OK;
//		res = RES_OK;
		break;
	
	case GET_BLOCK_SIZE:
		*((DWORD*)buff) = 1;
		return RES_OK;
	}
	return RES_PARERR;
#elif CONFIG_STORAGE_TYPE == FLASHTYPE
	return 0;
#endif
}

