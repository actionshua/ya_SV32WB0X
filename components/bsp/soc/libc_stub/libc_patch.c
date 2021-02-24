#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <sys/time.h>

#include "osal.h"
#if defined(SUPPORT_FFS)
#include "fsal.h"
#endif

//+++ stdlib override
#undef strdup
__attribute__((used))
char *strdup(const char *str)
{
    size_t len;
    char *copy;

    len = strlen(str) + 1;
    if (!(copy = malloc(len)))
        return (NULL);
    memcpy(copy, str, len);
    return (copy);
}

#undef calloc
__attribute__((used))
void *calloc( size_t count, size_t size )
{
    void* p;
    p = pvPortMalloc(count * size);
    memset(p, 0, count * size);
    return p;
}

#undef malloc
__attribute__((used))
void *malloc( size_t size )
{
	void* p;
	p = pvPortMalloc(size);
	return p;
}

#undef free
__attribute__((used))
void free( void *m )
{
	vPortFree(m);
}

#undef realloc
__attribute__((used))
void* realloc(void *mem, size_t newsize)
{
    if (newsize == 0)
    {
    	vPortFree(mem);
        return NULL;
    }

    void *p;
    p = pvPortMalloc(newsize);
    if (p)
    {
        if (mem != NULL)
        {
            memcpy(p, mem, newsize);
            vPortFree(mem);
        }
    }
    return p;
}

int _fflush_r(struct _reent *a, FILE *b) {
    return 0;
}
int _fclose_r(struct _reent *a, FILE *b) {
    return 0;
}
int  fflush(FILE *stream)
{
    if (stream == 0) {
        return (int)-1;
    }

    // todo
    return (int)1;
}

#define MAX_FS 5
static FILE *file[MAX_FS];
static int file_cnt = 0;
#if defined(SUPPORT_FFS)
extern SSV_FS fs_handle;
#endif

#undef fopen
__attribute__((used))
FILE* fopen (const char *filename, const char *mode)
{
#if defined(SUPPORT_FFS)
    SSV_FILE fs;
    uint32_t flag;
    if(file_cnt >= MAX_FS) {
        printf("==open cnt%d==\n", file_cnt);
        return NULL;
    }
    if(strcmp(mode,"r") == 0) {
        flag = SSV_O_RDONLY;
    } else if(strcmp(mode,"rb") == 0) {
        flag = SSV_O_RDONLY;
    } else if(strcmp(mode,"w") == 0) {
        flag = SSV_O_WRONLY | SSV_O_TRUNC |SSV_O_CREAT;
    } else if(strcmp(mode,"wb") == 0) {
        flag = SSV_O_WRONLY | SSV_O_TRUNC | SSV_O_CREAT;
    } else if(strcmp(mode,"wb+") == 0) {
        flag = SSV_O_RDWR | SSV_O_TRUNC | SSV_O_CREAT;
    } else if(strcmp(mode,"a") == 0) {
        flag = SSV_O_APPEND;
    } else {
        return NULL;
    }

    fs = FS_open(fs_handle, filename, flag ,0);
    if(FS_ferrno(fs) < 0) {
        printf("==return null: %d filename: %s flag: %d==\n", FS_ferrno(fs), filename, flag);
        return NULL;
    }
  
    file_cnt++;
    return (FILE *)fs;
#else
    return NULL;
#endif
}

#undef fread
__attribute__((used))
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
#if defined(SUPPORT_FFS)
    int ret;

    SSV_FILE fs = (SSV_FILE)stream;
    if(file_cnt > MAX_FS) {
        return -1;
    }
    if(size != 1) {
        return -2;
    }
    ret = FS_read(fs_handle, fs, ptr, nmemb);

    return ret;
#else
    return -1;
#endif
}

#undef fwrite
__attribute__((used))
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
#if defined(SUPPORT_FFS)
    int ret;
    SSV_FILE fs = (SSV_FILE)stream;
    if(file_cnt > MAX_FS) {
        return -1;
    }
    if(size != 1) {
        return -2;
    }
    ret = FS_write(fs_handle, fs, (void *)ptr, nmemb);
    //printf("fs: %d nmemb: %d ret: %d\n", fs, nmemb, ret);
    if(ret  < 0) {
        return -3;
    }
    if(ret  == 0) {
        return 0;
    }
    return ret;
#else
    return -1;
#endif
}

#undef ftell
__attribute__((used))
long ftell(FILE *stream)
{
#if defined(SUPPORT_FFS)
    int ret;
    SSV_FILE fs = (SSV_FILE)stream;
    if(file_cnt > MAX_FS) {
        return -1;
    }
    ret = FS_ftell(fs_handle, fs);
    return ret;
#else
    return -1;
#endif
}

#undef feof
__attribute__((used))
int feof(FILE *stream)
{
#if defined(SUPPORT_FFS)
    int ret;
    SSV_FILE fs = (SSV_FILE)stream;
    if(file_cnt > MAX_FS) {
        return -1;
    }
    ret = FS_feof(fs_handle, fs);
    return ret;
#else
    return -1;
#endif
}

#undef fseek
__attribute__((used))
int fseek(FILE *stream, long offset, int whence)
{
#if defined(SUPPORT_FFS)
    int ret;
    SSV_FILE fs = (SSV_FILE)stream;
    if(file_cnt > MAX_FS) {
        return -1;
    }

    if(whence == SEEK_SET) {
        whence = SSV_SEEK_SET;
    } else if(whence == SEEK_CUR) {
        whence = SSV_SEEK_CUR;
    } else if(whence == SEEK_END) {
        whence = SSV_SEEK_END;
    } else {
        return -1;
    }

    ret = FS_lseek(fs_handle, fs, offset, whence);
    return ret;
#else
    return -1;
#endif
}
#if 1
#undef fclose
__attribute__((used))
int fclose(FILE *stream)
{
#if defined(SUPPORT_FFS)
    int ret;
    SSV_FILE fs = (SSV_FILE)stream;
    if(file_cnt > MAX_FS) {
        return -1;
    }
    //printf("==close( id: %d)==\n", fs);
    ret = FS_close(fs_handle, fs);
    if(ret  < 0) {
        return -1;
    }
    file_cnt--;
    return 0;
#else
    return -1;
#endif
}
#endif

#undef fget
__attribute__((used))
char *fgets(char *s, int size, FILE *stream)
{
#if defined(SUPPORT_FFS)
    int ret;
    char *p = s;
    char tmp[2];
    int c, i =0;
    SSV_FILE fs = (SSV_FILE)stream;
    if(file_cnt > MAX_FS) {
        return 0;
    }
    
    for(;;) {
        ret = FS_read(fs_handle, fs, tmp, 1);
        if(ret  <= 0) {//eof
            break;
        } 
        c = tmp[0];
        s[i] = c;
        ++i;
        if(i >= (size - 1))//max 
            break;
        if(c == '\n')//new line
            break;
    }
    if(i == 0)
        return 0;
    s[i] = 0;
    return s;
#else
    return NULL;
#endif
}

void __assert_func() {
}

#undef ferror
__attribute__((used))
int ferror(FILE *stream)
{
#if defined(SUPPORT_FFS)
    int ret;
    SSV_FILE f = (SSV_FILE)stream;

    return FS_ferrno(f);
#else
    return -1;
#endif
}

#undef gettimeofday
__attribute__((used))
    int gettimeofday (struct timeval *tp, void *tz)
{
    if (tz)
    return -1;

    unsigned int update_tick = 0;
    long update_sec = 0, update_usec = 0;
#if TCPIPSTACK_EN
    extern void sntp_get_lasttime(long *sec, long *usec, unsigned int *tick);
    sntp_get_lasttime(&update_sec, &update_usec, &update_tick);
#endif

    if(update_tick) {
        long tick_diff_sec, tick_diff_ms, current_sec, current_usec;
        unsigned int current_tick = OS_GetSysTick();

        tick_diff_sec = (current_tick - update_tick) / OS_TICK_RATE_HZ;
        tick_diff_ms = (current_tick - update_tick) % OS_TICK_RATE_HZ / OS_TICK_RATE_MS;
        update_sec += tick_diff_sec;
        update_usec += (tick_diff_ms * 1000);
        current_sec = update_sec + update_usec / 1000000;
        current_usec = update_usec % 1000000;
    }   

    tp->tv_usec = update_usec;
    tp->tv_sec = update_sec;
    if(tp->tv_sec ==(time_t) -1 )
        return -1;
    return 0;
}
