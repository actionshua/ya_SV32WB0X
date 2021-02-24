
/*
 * 
 * Author: Tim Li
 *
 */

#ifndef __OTA_UTIL_H__
#define __OTA_UTIL_H__

#include "fota_common.h"

#ifdef __cplusplus
extern "C" {
#endif

void get_trng(unsigned int word_cnt, unsigned char *addr);
void const_string_to_integer(char *a, unsigned char max,unsigned char *value);

#ifdef __cplusplus
}
#endif

#endif  /* __OTA_UTIL_H__ */
