
/*
 * 
 * Author: Tim Li
 *
 */

#ifndef __OTA_COMMON_H__
#define __OTA_COMMON_H__

#include "soc_types.h"
#include "logger.h"

#define PRINT_FOTA_TAG LOG_TAG_FOTA

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#define MAX_PATH        (256)
#define OTA_HDR_SIZE      (84)
#define OTA_MAJOR_VER (1)
#define OTA_MINOR_VER (0)

typedef enum {
    RETRY = -9,
    NO_SUPPORT = -8,
    FS_ERROR = -7,
    T_ERROR = -6,
    C_ERROR = -5,
    H_ERROR = -4,
    A_ERROR = -3,
    P_ERROR = -2,
    MORE = -1,
    SUCCESS = 0,
} OTA_COMM_TYPE;

typedef enum {
    OTA_NOT_SUPPORT =0,
    OTA_FS = 1,
    OTA_PING_PONG = 2,
    OTA_UNKNOWN
} OTA_METHOD_TYPE;

void (*verify_burn)(char *, int);

struct ota_burn {
  char *name;
  int (* init)(void);
  int (* owrite)(char*, int);
  int (*verify)(void (*verify_burn)(char *, int));
  int (* close)(void);
  int (* deinit)(void);
};

struct protocol {
  char *name;
  int (* init)(char *, unsigned int, unsigned char *,struct ota_burn *);
  int (* get_hdr)(void);
  int (* burn)(void);
  int (* verify)(void);
  int (* done)(void);
  int (* deinit)(void);
};

int ota_get_ota_type();
int ota_get_hdr(const char *hdr, const int hdr_len);
int ota_get_jump_size();
int ota_get_img_size();
int ota_get_md5(char *md5);
void ota_update_flag();

#ifdef __cplusplus
}
#endif

#endif /* __OTA_COMMON_H__ */
