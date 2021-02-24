#include "ff.h"			/* Declarations of FatFs API */
#include "diskio.h"		/* Declarations of device I/O functions */

/*---------------------------------------------------------------------------

   Public Functions (FatFs API)

----------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------*/
/* Mount/Unmount a Logical Drive                                         */
/*-----------------------------------------------------------------------*/

FRESULT f_mount (
	FATFS* fs,			/* Pointer to the filesystem object (NULL:unmount)*/
	const TCHAR* path,	/* Logical drive number to be mounted/unmounted */
	BYTE opt			/* Mode option 0:Do not mount (delayed mount), 1:Mount immediately */
)
{
    return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Open or Create a File                                                 */
/*-----------------------------------------------------------------------*/

FRESULT f_open (
	FIL* fp,			/* Pointer to the blank file object */
	const TCHAR* path,	/* Pointer to the file name */
	BYTE mode			/* Access mode and file open mode flags */
)
{
    return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Read File                                                             */
/*-----------------------------------------------------------------------*/

FRESULT f_read (
	FIL* fp, 	/* Pointer to the file object */
	void* buff,	/* Pointer to data buffer */
	UINT btr,	/* Number of bytes to read */
	UINT* br	/* Pointer to number of bytes read */
)
{
    return FR_OK;
}




#if !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Write File                                                            */
/*-----------------------------------------------------------------------*/

FRESULT f_write (
	FIL* fp,			/* Pointer to the file object */
	const void* buff,	/* Pointer to the data to be written */
	UINT btw,			/* Number of bytes to write */
	UINT* bw			/* Pointer to number of bytes written */
)
{
    return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Synchronize the File                                                  */
/*-----------------------------------------------------------------------*/

FRESULT f_sync (
	FIL* fp		/* Pointer to the file object */
)
{
    return FR_OK;
}

#endif /* !FF_FS_READONLY */




/*-----------------------------------------------------------------------*/
/* Close File                                                            */
/*-----------------------------------------------------------------------*/

FRESULT f_close (
	FIL* fp		/* Pointer to the file object to be closed */
)
{
    return FR_OK;
}




#if FF_FS_RPATH >= 1
/*-----------------------------------------------------------------------*/
/* Change Current Directory or Current Drive, Get Current Directory      */
/*-----------------------------------------------------------------------*/

FRESULT f_chdrive (
	const TCHAR* path		/* Drive number to set */
)
{
	return FR_OK;
}



FRESULT f_chdir (
	const TCHAR* path	/* Pointer to the directory path */
)
{
	return FR_OK;
}


#if FF_FS_RPATH >= 2
FRESULT f_getcwd (
	TCHAR* buff,	/* Pointer to the directory path */
	UINT len		/* Size of buff in unit of TCHAR */
)
{
	return FR_OK;
}

#endif /* FF_FS_RPATH >= 2 */
#endif /* FF_FS_RPATH >= 1 */



#if FF_FS_MINIMIZE <= 2
/*-----------------------------------------------------------------------*/
/* Seek File Read/Write Pointer                                          */
/*-----------------------------------------------------------------------*/

FRESULT f_lseek (
	FIL* fp,		/* Pointer to the file object */
	FSIZE_t ofs		/* File pointer from top of file */
)
{
	return FR_OK;
}



#if FF_FS_MINIMIZE <= 1
/*-----------------------------------------------------------------------*/
/* Create a Directory Object                                             */
/*-----------------------------------------------------------------------*/

FRESULT f_opendir (
	DIR* dp,			/* Pointer to directory object to create */
	const TCHAR* path	/* Pointer to the directory path */
)
{
	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Close Directory                                                       */
/*-----------------------------------------------------------------------*/

FRESULT f_closedir (
	DIR *dp		/* Pointer to the directory object to be closed */
)
{
	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Read Directory Entries in Sequence                                    */
/*-----------------------------------------------------------------------*/

FRESULT f_readdir (
	DIR* dp,			/* Pointer to the open directory object */
	FILINFO* fno		/* Pointer to file information to return */
)
{
	return FR_OK;
}



#if FF_USE_FIND
/*-----------------------------------------------------------------------*/
/* Find Next File                                                        */
/*-----------------------------------------------------------------------*/

FRESULT f_findnext (
	DIR* dp,		/* Pointer to the open directory object */
	FILINFO* fno	/* Pointer to the file information structure */
)
{
	return FR_OK;
}



/*-----------------------------------------------------------------------*/
/* Find First File                                                       */
/*-----------------------------------------------------------------------*/

FRESULT f_findfirst (
	DIR* dp,				/* Pointer to the blank directory object */
	FILINFO* fno,			/* Pointer to the file information structure */
	const TCHAR* path,		/* Pointer to the directory to open */
	const TCHAR* pattern	/* Pointer to the matching pattern */
)
{
	return FR_OK;
}

#endif	/* FF_USE_FIND */



#if FF_FS_MINIMIZE == 0
/*-----------------------------------------------------------------------*/
/* Get File Status                                                       */
/*-----------------------------------------------------------------------*/

FRESULT f_stat (
	const TCHAR* path,	/* Pointer to the file path */
	FILINFO* fno		/* Pointer to file information to return */
)
{
	return FR_OK;
}



#if !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Get Number of Free Clusters                                           */
/*-----------------------------------------------------------------------*/

FRESULT f_getfree (
	const TCHAR* path,	/* Logical drive number */
	DWORD* nclst,		/* Pointer to a variable to return number of free clusters */
	FATFS** fatfs		/* Pointer to return pointer to corresponding filesystem object */
)
{
	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Truncate File                                                         */
/*-----------------------------------------------------------------------*/

FRESULT f_truncate (
	FIL* fp		/* Pointer to the file object */
)
{
	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Delete a File/Directory                                               */
/*-----------------------------------------------------------------------*/

FRESULT f_unlink (
	const TCHAR* path		/* Pointer to the file or directory path */
)
{
	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Create a Directory                                                    */
/*-----------------------------------------------------------------------*/

FRESULT f_mkdir (
	const TCHAR* path		/* Pointer to the directory path */
)
{
	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Rename a File/Directory                                               */
/*-----------------------------------------------------------------------*/

FRESULT f_rename (
	const TCHAR* path_old,	/* Pointer to the object name to be renamed */
	const TCHAR* path_new	/* Pointer to the new name */
)
{
	return FR_OK;
}

#endif /* !FF_FS_READONLY */
#endif /* FF_FS_MINIMIZE == 0 */
#endif /* FF_FS_MINIMIZE <= 1 */
#endif /* FF_FS_MINIMIZE <= 2 */



#if FF_USE_CHMOD && !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Change Attribute                                                      */
/*-----------------------------------------------------------------------*/

FRESULT f_chmod (
	const TCHAR* path,	/* Pointer to the file path */
	BYTE attr,			/* Attribute bits */
	BYTE mask			/* Attribute mask to change */
)
{
	return FR_OK;
}




/*-----------------------------------------------------------------------*/
/* Change Timestamp                                                      */
/*-----------------------------------------------------------------------*/

FRESULT f_utime (
	const TCHAR* path,	/* Pointer to the file/directory name */
	const FILINFO* fno	/* Pointer to the timestamp to be set */
)
{
	return FR_OK;
}

#endif	/* FF_USE_CHMOD && !FF_FS_READONLY */



#if FF_USE_LABEL
/*-----------------------------------------------------------------------*/
/* Get Volume Label                                                      */
/*-----------------------------------------------------------------------*/

FRESULT f_getlabel (
	const TCHAR* path,	/* Logical drive number */
	TCHAR* label,		/* Buffer to store the volume label */
	DWORD* vsn			/* Variable to store the volume serial number */
)
{
	return FR_OK;
}



#if !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Set Volume Label                                                      */
/*-----------------------------------------------------------------------*/

FRESULT f_setlabel (
	const TCHAR* label	/* Volume label to set with heading logical drive number */
)
{
	return FR_OK;
}

#endif /* !FF_FS_READONLY */
#endif /* FF_USE_LABEL */



#if FF_USE_EXPAND && !FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Allocate a Contiguous Blocks to the File                              */
/*-----------------------------------------------------------------------*/

FRESULT f_expand (
	FIL* fp,		/* Pointer to the file object */
	FSIZE_t fsz,	/* File size to be expanded to */
	BYTE opt		/* Operation mode 0:Find and prepare or 1:Find and allocate */
)
{
	return FR_OK;
}

#endif /* FF_USE_EXPAND && !FF_FS_READONLY */



#if FF_USE_FORWARD
/*-----------------------------------------------------------------------*/
/* Forward Data to the Stream Directly                                   */
/*-----------------------------------------------------------------------*/

FRESULT f_forward (
	FIL* fp, 						/* Pointer to the file object */
	UINT (*func)(const BYTE*,UINT),	/* Pointer to the streaming function */
	UINT btf,						/* Number of bytes to forward */
	UINT* bf						/* Pointer to number of bytes forwarded */
)
{
	return FR_OK;
}
#endif /* FF_USE_FORWARD */



#if !FF_FS_READONLY && FF_USE_MKFS
/*-----------------------------------------------------------------------*/
/* Create an FAT/exFAT volume                                            */
/*-----------------------------------------------------------------------*/

#define N_SEC_TRACK 63			/* Sectors per track for determination of drive CHS */
#define	GPT_ALIGN	0x100000	/* Alignment of partitions in GPT [byte] (>=128KB) */
#define GPT_ITEMS	128			/* Number of GPT table size (>=128, sector aligned) */


/* Create partitions on the physical drive */

static FRESULT create_partition (
	BYTE drv,			/* Physical drive number */
	const LBA_t plst[],	/* Partition list */
	UINT sys,			/* System ID (for only MBR, temp setting) and bit8:GPT */
	BYTE* buf			/* Working buffer for a sector */
)
{
	return FR_OK;
}



FRESULT f_mkfs (
	const TCHAR* path,		/* Logical drive number */
	const MKFS_PARM* opt,	/* Format options */
	void* work,				/* Pointer to working buffer (null: use heap memory) */
	UINT len				/* Size of working buffer [byte] */
)
{
	return FR_OK;
}




#if FF_MULTI_PARTITION
/*-----------------------------------------------------------------------*/
/* Create Partition Table on the Physical Drive                          */
/*-----------------------------------------------------------------------*/

FRESULT f_fdisk (
	BYTE pdrv,			/* Physical drive number */
	const LBA_t ptbl[],	/* Pointer to the size table for each partitions */
	void* work			/* Pointer to the working buffer (null: use heap memory) */
)
{
	return FR_OK;
}

#endif /* FF_MULTI_PARTITION */
#endif /* !FF_FS_READONLY && FF_USE_MKFS */




#if FF_USE_STRFUNC
#if FF_USE_LFN && FF_LFN_UNICODE && (FF_STRF_ENCODE < 0 || FF_STRF_ENCODE > 3)
#error Wrong FF_STRF_ENCODE setting
#endif
/*-----------------------------------------------------------------------*/
/* Get a String from the File                                            */
/*-----------------------------------------------------------------------*/

TCHAR* f_gets (
	TCHAR* buff,	/* Pointer to the buffer to store read string */
	int len,		/* Size of string buffer (items) */
	FIL* fp			/* Pointer to the file object */
)
{
	return 0;	/* When no data read due to EOF or error, return with error. */
}




#if !FF_FS_READONLY
#include <stdarg.h>
/*-----------------------------------------------------------------------*/
/* Put a Character to the File (sub-functions)                           */
/*-----------------------------------------------------------------------*/

/* Putchar output buffer and work area */

typedef struct {
	FIL *fp;		/* Ptr to the writing file */
	int idx, nchr;	/* Write index of buf[] (-1:error), number of encoding units written */
#if FF_USE_LFN && FF_LFN_UNICODE == 1
	WCHAR hs;
#elif FF_USE_LFN && FF_LFN_UNICODE == 2
	BYTE bs[4];
	UINT wi, ct;
#endif
	BYTE buf[64];	/* Write buffer */
} putbuff;

int f_putc (
	TCHAR c,	/* A character to be output */
	FIL* fp		/* Pointer to the file object */
)
{
	return 0;
}




/*-----------------------------------------------------------------------*/
/* Put a String to the File                                              */
/*-----------------------------------------------------------------------*/

int f_puts (
	const TCHAR* str,	/* Pointer to the string to be output */
	FIL* fp				/* Pointer to the file object */
)
{
	return 0;
}




/*-----------------------------------------------------------------------*/
/* Put a Formatted String to the File                                    */
/*-----------------------------------------------------------------------*/

int f_printf (
	FIL* fp,			/* Pointer to the file object */
	const TCHAR* fmt,	/* Pointer to the format string */
	...					/* Optional arguments... */
)
{
	return 0;
}

#endif /* !FF_FS_READONLY */
#endif /* FF_USE_STRFUNC */



#if FF_CODE_PAGE == 0
/*-----------------------------------------------------------------------*/
/* Set Active Codepage for the Path Name                                 */
/*-----------------------------------------------------------------------*/

FRESULT f_setcp (
	WORD cp		/* Value to be set as active code page */
)
{
	return FR_OK;
}
#endif	/* FF_CODE_PAGE == 0 */
