#include <stdio.h>
#include "bsp.h"
#ifdef SUPPORT_SDC
#include "ff.h"
#endif
#include "fsal.h"

#if 0
#define SDC_MAX_SCAN_DEPTH 5

static void sdc_scan_files (char* path, int max_path_len)
{
    DIR *dir[SDC_MAX_SCAN_DEPTH];
    UINT i, j;
    static UINT k = 0;
    static FILINFO fno;

    if (!strcmp(path, "/")) {//1st level file.
        k = 0;
    } else {
        k++;
    }

    dir[k] = OS_MemAlloc(sizeof(DIR));
    printf("malloc dir[%u]=0x%p\n", k, dir[k]);

    if (f_opendir(dir[k], path) == FR_OK) {
        for (;;) {
            if (f_readdir(dir[k], &fno) != FR_OK || fno.fname[0] == 0) break;

            if (!strcmp(path, "/")) {//1st level file.
                printf("%u: /sdcard/%s, size:%lld\n", k, fno.fname, fno.fsize);
            } else {
                printf("%u: /sdcard%s/%s, size:%lld\n", k, path, fno.fname, fno.fsize);
            }

            if (fno.fattrib & AM_DIR) {
                i = strlen(path);
                j = strlen(fno.fname);
                if (j < (max_path_len - 2) && (i+j) < (max_path_len - 2)) {
                    if (!strcmp(path, "/")) {//1st level folder.
		        if (k == (SDC_MAX_SCAN_DEPTH -1)) {
                            printf("%s%s exceeds %d layers", path, fno.fname, SDC_MAX_SCAN_DEPTH);
                            continue;
                        }
                        sprintf(&path[i], "%s", fno.fname);
                    } else {
		        if (k == (SDC_MAX_SCAN_DEPTH -1)) {
                            printf("%s/%s exceeds %d layers", path, fno.fname, SDC_MAX_SCAN_DEPTH);
                            continue;
                        }
                        sprintf(&path[i], "/%s", fno.fname);
                    }
                    sdc_scan_files(path, max_path_len);
                } else {
                    printf("%s/%s is too long!", path, fno.fname);
                }
                path[i] = 0;
            }
        }
        f_closedir(dir[k]);
    }

    printf("free dir[%u]=0x%p\n", k, dir[k]);
    OS_MemFree(dir[k]);
    k--;

    return;
}
#else
static FRESULT sdc_scan_files (char* path, int max_path_len)
{
    FRESULT res = 0;
#ifdef SUPPORT_SDC
    DIR dir;
    UINT i, j;
    static FILINFO fno;
    //static UINT k;

    //if (!strcmp(path, "/")) {//1st level folder.
    //    k = 1;
    //} else {
    //    k++;
    //}

    res = f_opendir(&dir, path);
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno);
            if (res != FR_OK || fno.fname[0] == 0) break;
            if (fno.fattrib & AM_DIR) {
                if (!strcmp(path, "/")) {//1st level file.
                    //printf("%u: /sdcard/%s, size:%lu\n", k, fno.fname, fno.fsize);
                    printf("/sdcard/%s, size:%llu\n", fno.fname, fno.fsize);
                } else {
                    //printf("%u: /sdcard%s/%s, size:%lu\n", k, path, fno.fname, fno.fsize);
                    printf("/sdcard%s/%s, size:%llu\n", path, fno.fname, fno.fsize);
                }
                i = strlen(path);
                j = strlen(fno.fname);
                if (j < (max_path_len - 2) && (i+j) < (max_path_len - 2)) {
                    if (!strcmp(path, "/")) {//1st level folder.
                        sprintf(&path[i], "%s", fno.fname);
                    } else {
                        sprintf(&path[i], "/%s", fno.fname);
                    }
                    res = sdc_scan_files(path, max_path_len);
                    if ((res != FR_OK) && (res != FR_INVALID_NAME)) {
                        printf("path=%s break: %d\n", path, res);
                        break;
                    }
                } else {
                    printf("%s/%s is too long!\n", path, fno.fname);
                }
                path[i] = 0;
            } else {
                if (!strcmp(path, "/")) {//1st level file.
                    //printf("%u: /sdcard/%s, size:%lu\n", k, fno.fname, fno.fsize);
                    printf("/sdcard/%s, size:%llu\n", fno.fname, fno.fsize);
                } else {
                    //printf("%u: /sdcard%s/%s, size:%lu\n", k, path, fno.fname, fno.fsize);
                    printf("/sdcard%s/%s, size:%llu\n", path, fno.fname, fno.fsize);
                }
            }
        }
        f_closedir(&dir);
    }
#endif
    //k--;

    return res;
}
#endif

void _SDC_list(void) {
#ifdef SUPPORT_SDC
    FRESULT res;
    FATFS *fsp;
    DWORD free_clust;
    char path[FSAL_PATH_MAX_LEN];

    //fsp = &fs;
    res = f_getfree("", &free_clust, &fsp);
    if (res == FR_OK) {
        printf("sd card total: %d MB, used: %d MB \n",
                ((fsp->n_fatent - 2) * fsp->csize) / 2048, ((fsp->n_fatent - 2) * fsp->csize - free_clust * fsp->csize) / 2048);

        strcpy(path,"/");
        sdc_scan_files(path, FSAL_PATH_MAX_LEN);
    } else {
        printf("%s(): Failed to get free space. res=%d\n", __func__, res);
    }
#endif
}

SSV_FILE _SDC_open(const char* path, uint32_t mode) {
#ifdef SUPPORT_SDC
    FRESULT res;
    BYTE fatfs_mode = 0;
    SSV_FILE file = OS_MemAlloc(sizeof(_SSV_FILE));

    if (file == NULL) {
        return NULL;
    }

    strncpy(file->path, path, FSAL_PATH_MAX_LEN);
    file->path[FSAL_PATH_MAX_LEN-1] = '\0';

    /* Any write to the filehandle is appended to end of the file */
    if (mode & SSV_O_APPEND) {
        fatfs_mode |= FA_OPEN_APPEND;
    }
    /* If the opened file exists, it will be truncated to zero length before opened */
    if (mode & SSV_O_TRUNC) {
        fatfs_mode |= FA_CREATE_ALWAYS;
    }
    /* If the opened file does not exist, it will be created before opened */
    if (mode & SSV_O_CREAT) {
        /* If SPIFFS_O_CREAT and SPIFFS_O_EXCL are set, SPIFFS_open() shall fail if the file exists */
        if (mode & SSV_O_EXCL) {
            fatfs_mode |= FA_CREATE_NEW;
        } else {
            fatfs_mode |= FA_OPEN_ALWAYS;
        }
    }
    /* The opened file may only be read */
    if (mode & SSV_O_RDONLY) {
        fatfs_mode |= FA_READ;
        fatfs_mode &= ~FA_WRITE;
    }
    /* The opened file may only be written */
    if (mode & SSV_O_WRONLY) {
        fatfs_mode &= ~FA_READ;
        fatfs_mode |= FA_WRITE;
    }
    /* The opened file may be both read and written */
    if (mode & SSV_O_RDWR) {
        fatfs_mode |= FA_READ;
        fatfs_mode |= FA_WRITE;
    }

    res = f_open(&file->sdfile, path, fatfs_mode);
    if (res == FR_OK) {
        file->ftype = SSV_SDC_TYPE;
        file->ferrno = (s32_t)res;
        return file;
    } else {
        OS_MemFree(file);
    }
#endif
    return NULL;
}

int32_t _SDC_read(SSV_FILE file, void* buf, uint32_t len) {
#ifdef SUPPORT_SDC
    FRESULT res;
    UINT read;

    if (file == NULL) {
        return FR_INVALID_PARAMETER;
    }

    res = f_read(&file->sdfile, buf, len, &read);
    file->ferrno = (s32_t)res;

    return (int32_t)read;
#else
    return 0;
#endif
}

int32_t _SDC_write(SSV_FILE file, void* buf, uint32_t len) {
#ifdef SUPPORT_SDC
    FRESULT res;
    UINT ret;

    if (file == NULL) {
        return FR_INVALID_PARAMETER;
    }

    res = f_write(&file->sdfile, buf, len, &ret);
    file->ferrno = (s32_t)res;

    if (res == FR_OK) {
        res = f_sync(&file->sdfile);
        file->ferrno = (s32_t)res;
    }

    return (int32_t)ret;
#else
    return 0;
#endif
}

int32_t	_SDC_stat(const char* path, SSV_FILE_STAT* stat) {
#ifdef SUPPORT_SDC
    FRESULT res;

    if (stat == NULL) {
        return FR_INVALID_PARAMETER;
    }

    res = f_stat(path, &stat->sdfstat);

    stat->ftype = SSV_SDC_TYPE;
    stat->fsize = (unsigned long long)stat->sdfstat.fsize;

    return (int32_t)res;
#else
    return 0;
#endif
}

int32_t	_SDC_lseek(SSV_FILE file, int32_t offs, uint32_t whence) {
#ifdef SUPPORT_SDC
    FRESULT res;

    if (file == NULL) {
        return FR_INVALID_PARAMETER;
    }

    if (whence) {
        file->ferrno = (s32_t)FR_INVALID_PARAMETER;
        return FR_INVALID_PARAMETER; 
    }

    res = f_lseek(&file->sdfile, offs);
    file->ferrno = (s32_t)res;
    if(res ==FR_OK) {
        return (int32_t)f_tell(&file->sdfile);
    }
    return (int32_t)res;
#else
    return 0;
#endif
}

int32_t	_SDC_flush(SSV_FILE file) {
#ifdef SUPPORT_SDC
    FRESULT res;

    if (file == NULL) {
        return FR_INVALID_PARAMETER;
    }

    res = f_sync(&file->sdfile);
    if (res == FR_OK) {
        OS_MemFree(file);
    } else {
        file->ferrno = (s32_t)res;
        printf("%s(): Failed to close file. res=%d\n", __func__, res);
    }
    return (int32_t)res;
#else
    return 0;
#endif
}

int32_t	_SDC_close(SSV_FILE file) {
#ifdef SUPPORT_SDC
    FRESULT res;

    if (file == NULL) {
        return FR_INVALID_PARAMETER;
    }

    res = f_close(&file->sdfile);
    if (res == FR_OK) {
        OS_MemFree(file);
    } else {
        file->ferrno = (s32_t)res;
        printf("%s(): Failed to close file. res=%d\n", __func__, res);
    }
    return (int32_t)res;
#else
    return 0;
#endif
}

int32_t	_SDC_remove(const char* path) {
#ifdef SUPPORT_SDC
    return (int32_t)f_unlink(path);
#else
    return 0;
#endif
}

SSV_DIR* _SDC_opendir(const char* name, SSV_DIR* d) {
#ifdef SUPPORT_SDC
    FRESULT res;

    if (d == NULL) {
        return NULL;
    }

    d->dtype = SSV_SDC_TYPE;
    res = f_opendir(&d->sddir, name);
    if (res == FR_OK) {
        strncpy(d->path, name, FSAL_PATH_MAX_LEN);
        d->path[FSAL_PATH_MAX_LEN-1] = '\0';

        d->derrno = (s32_t)FR_OK;
        return d;
    }
    d->derrno = (s32_t)res;

    return NULL;
#else
    return 0;
#endif
}

int32_t	_SDC_closedir(SSV_DIR* d) {
#ifdef SUPPORT_SDC
    FRESULT res;

    if (d == NULL) {
        return FR_INVALID_PARAMETER;
    }

    res = f_closedir(&d->sddir);
    d->derrno = (s32_t)res;

    return (int32_t)res;
#else
    return 0;
#endif
}

SSV_DIRENT* _SDC_readdir(SSV_DIR* d, SSV_DIRENT* e) {
#ifdef SUPPORT_SDC
    FRESULT res;

    if (d == NULL) {
        return NULL;
    }

    res = f_readdir(&d->sddir, &e->sddirent);
    e->type = SSV_SDC_TYPE;
    if ((res == FR_OK) && (e->sddirent.fname[0] != '\0')) {
        d->derrno = (s32_t)FR_OK;
        e->name = (char *)e->sddirent.fname;
        e->size = (unsigned long long)e->sddirent.fsize;
        return e;
    }
    d->derrno = (s32_t)res;

    return NULL;
#else
    return 0;
#endif
}

void _SDC_init(void) {
    return;
}

void _SDC_reset(void) {
    return;
}

int32_t	_SDC_rename(const char* old, const char* new) {
#ifdef SUPPORT_SDC
    return (int32_t)f_rename(old, new);
#else
    return 0;
#endif
}

int32_t	_SDC_ftell(SSV_FILE file) {
#ifdef SUPPORT_SDC
    return (int32_t)f_tell(&file->sdfile);
#else
    return 0;
#endif
}

int32_t	_SDC_feof(SSV_FILE file) {
#ifdef SUPPORT_SDC
    return (int32_t)f_eof(&file->sdfile);
#else
    return 0;
#endif
}
