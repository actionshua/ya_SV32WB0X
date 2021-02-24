
/*
 * 
 * Author: Tim Li
 *
 */

#ifndef __OTA_PROCESS_H__
#define __OTA_PROCESS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fota_api.h"
#include "fota_common.h"

typedef struct {
    //setting parameters
    unsigned char server_name[MAX_PATH];
    unsigned char bin_filename[MAX_PATH];
    unsigned char bin_filepath[MAX_PATH];
    unsigned int download_protocol;
    unsigned int server_port;
    //Status Callback
    void (*ota_status_ptr)(OTA_STATUS);
    //State Callback
    void (*ota_state_ptr)(OTA_STATE_TYPE);
    //Progress Callback
    void (*ota_progress_ptr)(int);
} ota_param_st;

OTA_RET_TYPE ota_process_stop(void);
OTA_RET_TYPE ota_process_run(ota_param_st *ota_param);
OTA_RET_TYPE process_reboot(void);

#ifdef __cplusplus
}
#endif

#endif  /* __OTA_PROCESS_H__ */

