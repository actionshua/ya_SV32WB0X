
/*
 * 
 * Author: Tim Li
 *
 */

#ifndef __FOTA_RAW_H__
#define __FTA_RAW_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fota_common.h"
#include "fota_md5.h"

typedef enum {
    RAW_FAIL = -3, ///< RAW data fail.
    RAW_FINISH = -2, ///< RAW data write finish.
    RAW_NOINIT = -1,///<RAW data need init firist
    RAW_SUCCESS = 0  ///< RAW data success.
} RAW_STATUS;

/**
 * write raw data function.
 * @param  data            raw data array point.
 * @param  len               raw data len.
 * @retval  -3.                raw data fail
 * @retval  -2.                raw data write already finish
 * @retval  -1.                raw data need init firist
 * @retval  0.                  raw data write success
  * @retval   > 0.            raw data already write size
 */
int input_raw_data(char *data, int len);

#ifdef __cplusplus
}
#endif

#endif  /* __OTA_FOTA_RAW_H__ */
