#ifndef _FSAL_H_
#define _FSAL_H_

#include "soc_defs.h"

#ifdef CONFIG_OS_ALIOS
#else
#include "sys/flash.h"
#include "../third_party/spiffs/spiffs_interface.h"
#include "../third_party/spiffs/spiffs_config.h"
#include "../third_party/spiffs/spiffs_nucleus.h"
#include "../third_party/littlefs/lfs.h"
#include "fsal_evt.h"
#include "../third_party/FatFs/ff.h"

#ifdef SUPPORT_SDC
#define SDC_PATH_PREFIX "/sdcard/"
#endif

#define FSAL_PATH_MAX_LEN 256

#if(FFS_METHOD == 1)
#define SSV_SEEK_SET                   SPIFFS_SEEK_SET
#define SSV_SEEK_CUR                 SPIFFS_SEEK_CUR
#define SSV_SEEK_END                 SPIFFS_SEEK_END
#elif(FFS_METHOD == 2)
#define SSV_SEEK_SET                   LFS_SEEK_SET
#define SSV_SEEK_CUR                 LFS_SEEK_CUR
#define SSV_SEEK_END                 LFS_SEEK_END
#else
#endif

#if(FFS_METHOD == 1)
#define SSV_O_APPEND                 SPIFFS_APPEND
#define SSV_O_TRUNC                  SPIFFS_TRUNC
#define SSV_O_CREAT                  SPIFFS_CREAT
#define SSV_O_RDONLY                 SPIFFS_RDONLY
#define SSV_O_WRONLY                 SPIFFS_WRONLY
#define SSV_O_RDWR                   SPIFFS_RDWR
#define SSV_O_DIRECT                 SPIFFS_DIRECT
#define SSV_O_EXCL                   SPIFFS_EXCL
#elif(FFS_METHOD == 2)
#define SSV_O_APPEND                 LFS_O_APPEND
#define SSV_O_TRUNC                  LFS_O_TRUNC
#define SSV_O_CREAT                  LFS_O_CREAT
#define SSV_O_RDONLY                 LFS_O_RDONLY
#define SSV_O_WRONLY                 LFS_O_WRONLY
#define SSV_O_RDWR                   LFS_O_RDWR
#define SSV_O_DIRECT                 
#define SSV_O_EXCL                   LFS_O_EXCL
#else
#endif
    
#ifdef SUPPORT_SDC
#define	SSV_DISK_ERR		FR_DISK_ERR,			/* (1) A hard error occurred in the low level disk I/O layer */
#define	SSV_INT_ERR		FR_INT_ERR,			/* (2) Assertion failed */
#define	SSV_NOT_READY		FR_NOT_READY,			/* (3) The physical drive cannot work */
#define	SSV_NO_FILE		FR_NO_FILE,			/* (4) Could not find the file */
#define	SSV_NO_PATH		FR_NO_PATH,			/* (5) Could not find the path */
#define	SSV_INVALID_NAME	FR_INVALID_NAME,		/* (6) The path name format is invalid */
#define	SSV_DENIED		FR_DENIED,			/* (7) Access denied due to prohibited access or directory full */
#define	SSV_EXIST		FR_EXIST,			/* (8) Access denied due to prohibited access */
#define	SSV_INVALID_OBJECT	FR_INVALID_OBJECT,		/* (9) The file/directory object is invalid */
#define	SSV_WRITE_PROTECTED	FR_WRITE_PROTECTED,		/* (10) The physical drive is write protected */
#define	SSV_INVALID_DRIVE	FR_INVALID_DRIVE,		/* (11) The logical drive number is invalid */
#define	SSV_NOT_ENABLED		FR_NOT_ENABLED,			/* (12) The volume has no work area */
#define	SSV_NO_FILESYSTEM	FR_NO_FILESYSTEM,		/* (13) There is no valid FAT volume */
#define	SSV_MKFS_ABORTED	FR_MKFS_ABORTED,		/* (14) The f_mkfs() aborted due to any problem */
#define	SSV_TIMEOUT		FR_TIMEOUT,			/* (15) Could not get a grant to access the volume within defined period */
#define	SSV_LOCKED		FR_LOCKED,			/* (16) The operation is rejected according to the file sharing policy */
#define	SSV_NOT_ENOUGH_CORE 	FR_NOT_ENOUGH_CORE,		/* (17) LFN working buffer could not be allocated */
#define	SSV_TOO_MANY_OPEN_FILES FR_TOO_MANY_OPEN_FILES,		/* (18) Number of open files > FF_FS_LOCK */
#define	SSV_INVALID_PARAMETER	FR_INVALID_PARAMETER		/* (19) Given parameter is invalid */
#endif
#if(FFS_METHOD == 1)
#define SSV_OK				SPIFFS_OK			/* (0) Succeeded */
#define SSV_ERR_NOT_MOUNTED		SPIFFS_ERR_NOT_MOUNTED          /* -10000 */
#define SSV_ERR_FULL			SPIFFS_ERR_FULL                 /* -10001 */
#define SSV_ERR_NOT_FOUND		SPIFFS_ERR_NOT_FOUND            /* -10002 */
#define SSV_ERR_END_OF_OBJECT		SPIFFS_ERR_END_OF_OBJECT        /* -10003 */
#define SSV_ERR_DELETED			SPIFFS_ERR_DELETED              /* -10004 */
#define SSV_ERR_NOT_FINALIZED		SPIFFS_ERR_NOT_FINALIZED        /* -10005 */
#define SSV_ERR_NOT_INDEX		SPIFFS_ERR_NOT_INDEX            /* -10006 */
#define SSV_ERR_OUT_OF_FILE_DESCS	SPIFFS_ERR_OUT_OF_FILE_DESCS    /* -10007 */
#define SSV_ERR_FILE_CLOSED		SPIFFS_ERR_FILE_CLOSED          /* -10008 */
#define SSV_ERR_FILE_DELETED		SPIFFS_ERR_FILE_DELETED         /* -10009 */
#define SSV_ERR_BAD_DESCRIPTOR		SPIFFS_ERR_BAD_DESCRIPTOR       /* -10010 */
#define SSV_ERR_IS_INDEX		SPIFFS_ERR_IS_INDEX             /* -10011 */
#define SSV_ERR_IS_FREE			SPIFFS_ERR_IS_FREE              /* -10012 */
#define SSV_ERR_INDEX_SPAN_MISMATCH	SPIFFS_ERR_INDEX_SPAN_MISMATCH  /* -10013 */
#define SSV_ERR_DATA_SPAN_MISMATCH	SPIFFS_ERR_DATA_SPAN_MISMATCH   /* -10014 */
#define SSV_ERR_INDEX_REF_FREE		SPIFFS_ERR_INDEX_REF_FREE       /* -10015 */
#define SSV_ERR_INDEX_REF_LU		SPIFFS_ERR_INDEX_REF_LU         /* -10016 */
#define SSV_ERR_INDEX_REF_INVALID	SPIFFS_ERR_INDEX_REF_INVALID    /* -10017 */
#define SSV_ERR_INDEX_FREE		SPIFFS_ERR_INDEX_FREE           /* -10018 */
#define SSV_ERR_INDEX_LU		SPIFFS_ERR_INDEX_LU             /* -10019 */
#define SSV_ERR_INDEX_INVALID		SPIFFS_ERR_INDEX_INVALID        /* -10020 */
#define SSV_ERR_NOT_WRITABLE		SPIFFS_ERR_NOT_WRITABLE         /* -10021 */
#define SSV_ERR_NOT_READABLE		SPIFFS_ERR_NOT_READABLE         /* -10022 */
#define SSV_ERR_CONFLICTING_NAME	SPIFFS_ERR_CONFLICTING_NAME     /* -10023 */
#define SSV_ERR_NOT_CONFIGURED		SPIFFS_ERR_NOT_CONFIGURED       /* -10024 */
#define SSV_ERR_NOT_A_FS		SPIFFS_ERR_NOT_A_FS             /* -10025 */
#define SSV_ERR_MOUNTED			SPIFFS_ERR_MOUNTED              /* -10026 */
#define SSV_ERR_ERASE_FAIL		SPIFFS_ERR_ERASE_FAIL           /* -10027 */
#define SSV_ERR_MAGIC_NOT_POSSIBLE	SPIFFS_ERR_MAGIC_NOT_POSSIBLE   /* -10028 */
#define SSV_ERR_NO_DELETED_BLOCKS	SPIFFS_ERR_NO_DELETED_BLOCKS    /* -10029 */
#define SSV_ERR_FILE_EXISTS		SPIFFS_ERR_FILE_EXISTS          /* -10030 */
#define SSV_ERR_NOT_A_FILE		SPIFFS_ERR_NOT_A_FILE           /* -10031 */
#define SSV_ERR_RO_NOT_IMPL		SPIFFS_ERR_RO_NOT_IMPL          /* -10032 */
#define SSV_ERR_RO_ABORTED_OPERATION	SPIFFS_ERR_RO_ABORTED_OPERATION /* -10033 */
#define SSV_ERR_PROBE_TOO_FEW_BLOCKS	SPIFFS_ERR_PROBE_TOO_FEW_BLOCKS /* -10034 */
#define SSV_ERR_PROBE_NOT_A_FS		SPIFFS_ERR_PROBE_NOT_A_FS       /* -10035 */
#define SSV_ERR_NAME_TOO_LONG		SPIFFS_ERR_NAME_TOO_LONG        /* -10036 */
#define SSV_ERR_IX_MAP_UNMAPPED		SPIFFS_ERR_IX_MAP_UNMAPPED      /* -10037 */
#define SSV_ERR_IX_MAP_MAPPED		SPIFFS_ERR_IX_MAP_MAPPED        /* -10038 */
#define SSV_ERR_IX_MAP_BAD_RANGE	SPIFFS_ERR_IX_MAP_BAD_RANGE     /* -10039 */
#define SSV_ERR_INTERNAL		SPIFFS_ERR_INTERNAL             /* -10050 */
#define SSV_ERR_TEST			SPIFFS_ERR_TEST                 /* -10100 */
#elif(FFS_METHOD == 2)
#define SSV_OK				LFS_ERR_OK			/* (0) No error */
#define SSV_ERR_FILE_EXISTS		LFS_ERR_EXIST          /* (-17) Entry already exists */
#define SSV_ERR_FULL			LFS_ERR_NOSPC                 /* (-28) No space left on device */
#define SSV_ERR_NAME_TOO_LONG		LFS_ERR_NAMETOOLONG         /* (-36) File name too long */

#define SSV_ERR_IO				LFS_ERR_IO			/* (-5) Error during device operation */
#define SSV_ERR_CORRUPT				LFS_ERR_CORRUPT			/* (-84) Corrupted */
#define SSV_ERR_NOENT				LFS_ERR_NOENT			/* (-2) No directory entry */
#define SSV_ERR_NOTDIR				LFS_ERR_NOTDIR			/* (-20) Entry is not a dir */
#define SSV_ERR_ISDIR				LFS_ERR_ISDIR			/* (-21) Entry is a dir */
#define SSV_ERR_NOTEMPTY				LFS_ERR_NOTEMPTY			/* (-39) Dir is not empty */
#define SSV_ERR_BADF				LFS_ERR_BADF			/* (-9) Bad file number */
#define SSV_ERR_FBIG				LFS_ERR_FBIG			/* (-27) File too large */
#define SSV_ERR_INVAL				LFS_ERR_INVAL			/* (-22) Invalid parameter */
#define SSV_ERR_NOMEM				LFS_ERR_NOMEM			/* (-12) No more memory available */
#define SSV_ERR_NOATTR				LFS_ERR_NOATTR			/* (-61) No data/attr available */

#define SSV_ERR_INTERNAL		LFS_ERR_INVAL             /* (-22) Invalid parameter */
#else
#endif
    
typedef enum {
    SSV_FLASH_TYPE,
#ifdef SUPPORT_SDC
    SSV_SDC_TYPE,
#endif
} SSV_FILE_TYPE;

typedef struct {
    s32_t ferrno;
    SSV_FILE_TYPE ftype;
    union {
        spiffs_file file;
        lfs_file_t lfsfile;
        FIL sdfile;
    };
    char path[FSAL_PATH_MAX_LEN];
} _SSV_FILE, *SSV_FILE;

typedef struct {
    SSV_FILE_TYPE ftype;
    union {
        spiffs_stat fstat;
        struct lfs_info lfsstate;
        FILINFO sdfstat;
    };
    unsigned long long fsize;
} SSV_FILE_STAT;

typedef struct {
    s32_t derrno;
    SSV_FILE_TYPE dtype;
    union {
        spiffs_DIR dir;
        lfs_dir_t lfsdir;
        DIR sddir;
    };
    char path[FSAL_PATH_MAX_LEN];
} SSV_DIR;

typedef struct {
    SSV_FILE_TYPE type;
    union {
        struct spiffs_dirent dirent;
        struct lfs_info lfsdirent;
        FILINFO sddirent;
    };
    char *name;
    unsigned long long size;
} SSV_DIRENT;

#endif

typedef struct {
    void *fs;
    bool support_sdc;
} _SSV_FS, *SSV_FS;

void		FS_register_evthandler(void (*handler)(SSV_FS_EVENT));
void		FS_deregister_evthandler(void);
s32_t		FS_ferrno(SSV_FILE file);
s32_t		FS_derrno(SSV_DIR d);
SSV_FS		FS_init(void);
SSV_FS		FS_reset(void);
void		FS_list(SSV_FS fs);
void		FS_list_personal(SSV_FS fs);
void		FS_remove_prevota(SSV_FS fs);
SSV_FILE	FS_open(SSV_FS fs, const char* path, uint32_t flags, uint32_t mode);
int32_t 	FS_read(SSV_FS fs, SSV_FILE file, void* buf, uint32_t len);
int32_t 	FS_write(SSV_FS fs, SSV_FILE file, void* buf, uint32_t len);
int32_t		FS_lseek(SSV_FS fs, SSV_FILE file, int32_t offs, uint32_t whence);
int32_t		FS_remove(SSV_FS fs, const char* path);
int32_t 	FS_fremove(SSV_FS fs, SSV_FILE file);
int32_t		FS_stat(SSV_FS fs, const char* path, SSV_FILE_STAT* stat);
int32_t		FS_fstat(SSV_FS fs, SSV_FILE file, SSV_FILE_STAT* stat);
int32_t		FS_flush(SSV_FS fs, SSV_FILE file);
int32_t		FS_close(SSV_FS fs, SSV_FILE file);
int32_t		FS_rename(SSV_FS fs, const char* old, const char* new);
SSV_DIR*	FS_opendir(SSV_FS fs, const char* name, SSV_DIR* d);
int32_t		FS_closedir(SSV_DIR* d);
SSV_DIRENT*	FS_readdir(SSV_DIR* d, SSV_DIRENT* e);
int32_t		FS_feof(SSV_FS ff,  SSV_FILE file);
int32_t		FS_ftell(SSV_FS ff, SSV_FILE file);

#endif
