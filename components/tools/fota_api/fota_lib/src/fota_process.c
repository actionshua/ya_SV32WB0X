
/*
 *
 * Author: Tim Li
 *
 */

#include <stdio.h>
#include <string.h>
#include "fota_process.h"
#include "fota_pp.h"
#include "fota_fs.h"
#include "fota_tftp.h"
#include "fota_http.h"
#include "osal.h"
#include "wdt/drv_wdt.h"
#ifdef TFTP_EN
extern struct protocol tftp;
#endif
#ifdef HTTPC_EN
extern struct protocol http;
#endif
extern struct protocol raw;
#if(FOTA_OPTION == 1)
#ifdef SUPPORT_FFS
#ifdef ANTI_CLONE_PROTECTION
extern struct ota_burn fs_acp;
#else
extern struct ota_burn fs;
#endif
#endif
#elif(FOTA_OPTION == 2)
#ifdef ANTI_CLONE_PROTECTION
extern struct ota_burn pp_acp;
#else
extern struct ota_burn pp;
#endif
#endif

#define MAX_RECNT (1)

typedef struct {
    //setting parameters
    ota_param_st ota_para;
    int ota_state;
    int retry_cnt;
    int stop;
} ota_process_st;
static ota_process_st ota_process;

static OTA_STATUS status = OTA_FAIL;
static struct protocol *proto;
static struct ota_burn *burn_img;
static int process_en = 0;

static inline void kick_watch_dog(void)
{
    drv_wdt_kick(MCU_WDT);
    drv_wdt_kick(SYS_WDT);
}

static void wdt_enable()
{
    //Reboot
    drv_wdt_init();
    drv_wdt_enable(SYS_WDT, 100);
    log_i(PRINT_FOTA_TAG, "\nOTA Reboot SUCCESS\n");
    while(1) {};
}

static void update_process_ptr(unsigned int totoal, unsigned int remin)
{
    if(ota_process.ota_para.ota_progress_ptr)
    {
        if(remin < 0)
            ota_process.ota_para.ota_progress_ptr(0);
        else
            ota_process.ota_para.ota_progress_ptr(((totoal -remin)*100)/totoal);
    }
}

static int ota_protocol_init()
{
    unsigned char file[512];
    int ret = SUCCESS;
    sprintf((char *)file, "%s%s", ota_process.ota_para.bin_filepath, ota_process.ota_para.bin_filename);
    if(burn_img != NULL && proto != NULL) 
    {
        ret = proto->init((char *)ota_process.ota_para.server_name,
            ota_process.ota_para.server_port, file, burn_img);
    }
    else
    {
        log_e(PRINT_FOTA_TAG, "[%d] %s(%x %x)\n",__LINE__, __func__,  (unsigned int)burn_img, (unsigned int)proto);
        ret = A_ERROR;
    }
    if (ret == SUCCESS)
    {
        ota_process.ota_state = OTA_STATE_GET_HDR;
    }
    else
    {
        ota_process.ota_state = OTA_STATE_FAIL;
    }
    return ret;
}

static int ota_protocol_get_hdr()
{
    int ret = SUCCESS;
    if(proto != NULL) 
    {
        ret = proto->get_hdr();
    }
    else
    {
        log_e(PRINT_FOTA_TAG, "[%d] %s(%x %x)\n",__LINE__, __func__,  (unsigned int)burn_img, (unsigned int)proto);
        ret = A_ERROR;
    }
    if(ret < MORE)
    {
        if(ret == NO_SUPPORT) 
        {
            ota_process.ota_state = OTA_STATE_FAIL;
        }
        else 
        {
            ota_process.ota_state = OTA_STATE_RETRY;
        }
    }
    else
    {
        //else return totoal burn size
        ota_process.ota_state = OTA_STATE_BURN;
    }
    return ret;
}

static int ota_protocol_burn()
{
    int ret = SUCCESS;
    if(proto != NULL) 
    {
        ret = proto->burn();
        //if ret > 0, it mean burn data size into flash
    }
    else
    {
        log_e(PRINT_FOTA_TAG, "[%d] %s(%x %x)\n",__LINE__, __func__,  (unsigned int)burn_img, (unsigned int)proto);
        ret = A_ERROR;
    }
    if(ret == SUCCESS)
    {
        ota_process.ota_state = OTA_STATE_VERIFY;
    }
    else
    {
        if(ret < MORE)
            ota_process.ota_state = OTA_STATE_RETRY;
    }
    //else more data
    return ret;
}

static int ota_protocol_verify()
{
    int ret = SUCCESS;
    if(proto != NULL) 
    {
        ret = proto->verify();
    }
    else
    {
        log_e(PRINT_FOTA_TAG, "[%d] %s(%x %x)\n",__LINE__, __func__,  (unsigned int)burn_img, (unsigned int)proto);
        ret = A_ERROR;
    }
    if(ret == SUCCESS)
    {
        ota_process.ota_state = OTA_STATE_DONE;
    }
    else
    {
        ota_process.ota_state = OTA_STATE_FAIL;
    }
    return ret;
}

static int ota_protocol_done()
{
    int ret = SUCCESS;
    if(proto != NULL) 
    {
        ret = proto->done();
    }
    else
    {
        log_e(PRINT_FOTA_TAG, "[%d] %s(%x %x)\n",__LINE__, __func__,  (unsigned int)burn_img, (unsigned int)proto);
        ret = A_ERROR;
    }
    if(ret == SUCCESS)
    {
        ota_process.ota_state = OTA_STATE_NONE;
        status = OTA_SUCCESS;
    }
    else
    {
        ota_process.ota_state = OTA_STATE_FAIL;
    }
    return ret;
}

static int ota_protocol_retry()
{
    int ret = SUCCESS;
    unsigned char file[512];
    ota_process.retry_cnt ++;
    if(ota_process.retry_cnt > MAX_RECNT)
    {
        ota_process.ota_state = OTA_STATE_FAIL;
        ret = A_ERROR;
    } 
    else
    {
        sprintf((char *)file, "%s%s", (char *)ota_process.ota_para.bin_filepath, (char *)ota_process.ota_para.bin_filename);
        if(proto != NULL) 
        {
            ret = proto->init((char *)ota_process.ota_para.bin_filename,
            ota_process.ota_para.server_port, file, burn_img);
        }
        else
        {
            log_e(PRINT_FOTA_TAG, "[%d] %s(%x %x)\n",__LINE__, __func__,  (unsigned int)burn_img, (unsigned int)proto);
            ret = A_ERROR;
        }
        if(ret == SUCCESS)
        {
            ota_process.ota_state = OTA_STATE_INIT;
        }
        else
        {
            ota_process.ota_state = OTA_STATE_FAIL;
        }
    }
    return ret;
}

static int ota_protocol_fail()
{
    int ret = SUCCESS;
    if(proto != NULL) 
    {
        ret = proto->done();
    }
    else
    {
        printf("[%d] %s(%x %x)\n",__LINE__, __func__,  (unsigned int)burn_img, (unsigned int)proto);
        ret = A_ERROR;
    }
    ota_process.ota_state = OTA_STATE_NONE;
    status = OTA_FAIL;
    return ret;
}

static int ota_resource_deinit()
{
    int ret = SUCCESS;
    if(burn_img != NULL) 
    {
        ret = burn_img->deinit();
    }
    else
    {
        log_e(PRINT_FOTA_TAG, "burn resource not init\n");
        ret = A_ERROR;
    }
    if(proto != NULL) 
    {
        ret = proto->deinit();
    }
    else
    {
        log_e(PRINT_FOTA_TAG, "protocol not init\n");
        ret = A_ERROR;
    }
    return ret;
}

static int ota_resource_init()
{
    int ota_type = ota_get_ota_type();
    int ret = SUCCESS;
    if(ota_type == OTA_NOT_SUPPORT) {
        log_e(PRINT_FOTA_TAG, "not support type: %d\n", ota_type);
        return A_ERROR;
    }
#if(FOTA_OPTION == 2)
    else if(ota_type == OTA_PING_PONG)
#ifdef ANTI_CLONE_PROTECTION
        burn_img = &pp_acp;
#else
        burn_img = &pp;
#endif
#endif
#if(FOTA_OPTION == 1)
#ifdef SUPPORT_FFS
    else if(ota_type == OTA_FS)
#ifdef ANTI_CLONE_PROTECTION
        burn_img = &fs_acp;
#else
        burn_img = &fs;
#endif
#endif
#endif
    else
    {
        log_e(PRINT_FOTA_TAG, "unknown type: %d\n", ota_type);
        return A_ERROR;
    }
    if(ota_process.ota_para.download_protocol== RAW)
        proto = &raw;
#ifdef HTTPC_EN
    else if(ota_process.ota_para.download_protocol== HTTP)
        proto = &http;
#endif
#ifdef TFTP_EN
    else if(ota_process.ota_para.download_protocol== TFTP)
        proto = &tftp;
#endif
    else
    {
        log_e(PRINT_FOTA_TAG, "unknown protocol type: %d\n", ota_process.ota_para.download_protocol);
        return A_ERROR;
    }
    ota_process.ota_state = OTA_STATE_INIT;
    burn_img->init();
    ota_process.retry_cnt = 1;
    ota_process.stop = 0;
    return ret;
}

static void ota_task(void *args)
{
    static int totoal = 0, remin = 0, state = -1;
    if(ota_resource_init() == SUCCESS) {
        while(ota_process.ota_state < OTA_STATE_NONE) 
        {
            //log_i(PRINT_FOTA_TAG, "ota_state: %d\n", ota_process.ota_state);
            kick_watch_dog();
            if(ota_process.stop == 1)
                ota_process.ota_state = OTA_STATE_FAIL;

            if(ota_process.ota_para.ota_state_ptr)
            {
                if(state != ota_process.ota_state)
                {
                    ota_process.ota_para.ota_state_ptr(ota_process.ota_state);
                    state = ota_process.ota_state;
                }
            }
            switch (ota_process.ota_state) 
            {
                case OTA_STATE_INIT:
                    ota_protocol_init();
                    break;
                case OTA_STATE_GET_HDR:
                    totoal = ota_protocol_get_hdr();
                    break;
                case OTA_STATE_BURN:
                    remin = ota_protocol_burn();
                    update_process_ptr(totoal, remin);
                    break;
                case OTA_STATE_VERIFY:
                    ota_protocol_verify();
                    break;
                case OTA_STATE_DONE:
                    ota_protocol_done();
                    break;
                case OTA_STATE_RETRY:
                    ota_protocol_retry();
                    break;
                case OTA_STATE_FAIL:
                    ota_protocol_fail();
                    break;
            }
        }
    }
    ota_resource_deinit();
    totoal = remin = 0;
    if(ota_process.ota_para.ota_status_ptr) 
    {
        ota_process.ota_para.ota_status_ptr(status);
    }
    process_en = 0;
    OS_TaskDelete(NULL);
}

OTA_RET_TYPE ota_process_stop()
{
    ota_process.stop = 1;
    if(ota_process.ota_para.download_protocol== RAW) {
        extern void stop_raw_mode();
        stop_raw_mode();
    }

    while(process_en != 0)
        OS_MsDelay(1);

    return O_SUCCESS;
}

OTA_RET_TYPE ota_process_run(ota_param_st *ota_param)
{
    if(ota_param == NULL)
    {
        log_e(PRINT_FOTA_TAG, "Error [%d] %s\n", __LINE__, __func__);
        return OP_ERROR;
    }
    if(process_en != 0)
    {
        log_e(PRINT_FOTA_TAG, "Error [%d] %s\n", __LINE__, __func__);
        return OP_ERROR;
    }
    memcpy(&ota_process.ota_para, ota_param, sizeof(ota_param_st));
    process_en = 1;
    if (OS_TaskCreate(ota_task, "OTA_Task", 2048, NULL, OS_TASK_MIDDLE_PRIO, NULL) != true)
    {
        log_e(PRINT_FOTA_TAG, "Error [%d] %s\n", __LINE__, __func__);
        return OP_ERROR;
    }
    return O_SUCCESS;
}

OTA_RET_TYPE process_reboot(void)
{
    if(ota_process.ota_state == OTA_STATE_NONE)
    {
        wdt_enable();
        return O_SUCCESS;
    }
    else
    {
        log_e(PRINT_FOTA_TAG, "fota not success, so can not reboot\n");
        return OP_ERROR;
    }
}

