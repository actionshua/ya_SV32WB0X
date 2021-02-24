
/*
 * 
 * Author: Tim Li
 *
 */
#include <string.h>
#include <stdio.h>
#include "fota_raw.h"
#include "osal.h"

#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))

typedef struct {
    unsigned int state;
    unsigned int init;
    unsigned int total_size;
    unsigned int data_jump;
    int data_burn;
    struct ota_burn *burn_st;
    MD5_CTX mem;
} ota_raw_st;
static ota_raw_st ota_raw;

void stop_raw_mode()
{
    ota_raw.state = 2;
}

static int raw_state0(char *data, int len)
{
    int ret = 0;
    char *addr;
    if(len <= OTA_HDR_SIZE) {
        log_e(PRINT_FOTA_TAG, "input data %d < %d\n", len, OTA_HDR_SIZE);
        return -1;
    }
    ret = ota_get_hdr(data, OTA_HDR_SIZE);
    if(ret < 0)
    {
        log_e(PRINT_FOTA_TAG, "[%d]%s fail: %d\n", __LINE__, __func__, ret);
        return -1;
    }
    ota_raw.data_burn = ota_get_img_size();
    ota_raw.data_jump = ota_get_jump_size();
    if(ota_raw.data_jump > 0)
    {
        ota_raw.data_jump -= (len - OTA_HDR_SIZE);
    }
    else
    {
        if(len > OTA_HDR_SIZE)
        {
            len -= OTA_HDR_SIZE;
            addr = &data[OTA_HDR_SIZE];
            ota_raw.burn_st->owrite(addr, len);
            MD5_Update(&ota_raw.mem, addr, len);
            ota_raw.data_burn -= len;
        }
        else
        {
            log_e(PRINT_FOTA_TAG, "[%d] %s: %d\n", __LINE__, __func__, len);
            return -1;
        }
    }
    ota_raw.total_size = ota_raw.data_jump + ota_raw.data_burn;
    return 0;
}

static int raw_state1(char *data, int len)
{
    int ret = 0;
    int offset = 0;
    char *addr;
    if(ota_raw.data_jump > 0) //if use b, then jump a size
    {
        if(ota_raw.data_jump >= len)
        {
            ota_raw.data_jump -= len;
            return ota_raw.data_burn + ota_raw.data_jump;
        }
        else
        {
            len -= ota_raw.data_jump;
            offset = ota_raw.data_jump;
            ota_raw.data_jump = 0;
        }
    }
    addr = &data[offset];
    if(len > ota_raw.data_burn)
       len = ota_raw.data_burn;
    ret = ota_raw.burn_st->owrite(addr, len);
    if(ret != 0) 
    {
        log_e(PRINT_FOTA_TAG, "write flash fail\n");
        return -1;
    }
    MD5_Update(&ota_raw.mem, addr,len);
    ota_raw.data_burn -= len;
    if(ota_raw.data_burn <= 0) 
    {
        log_i(PRINT_FOTA_TAG, "all image write ready\n");
        return 0;
    }

    return ota_raw.data_burn + ota_raw.data_jump;
}

int input_raw_data(char *data, int len)
{
    int status = RAW_SUCCESS;
    if(ota_raw.state == 2) {
        log_i(PRINT_FOTA_TAG, "raw data already write finish\n");
        return RAW_FINISH;
    }

    if(ota_raw.init == 0) {
        log_i(PRINT_FOTA_TAG, "need init\n");
        return RAW_NOINIT;
    }

    if(ota_raw.state == 0) {
        //write first data, and get header info
        status = raw_state0(data, len);
        if(status == 0) {
            ota_raw.state = 1;
        } else {
            log_e(PRINT_FOTA_TAG, "raw state0 error: %d\n", status);
            status = RAW_FAIL;
        }
    } else if(ota_raw.state == 1) {
        status = raw_state1(data, len);
        if(status == 0) {
            ota_raw.state = 2;
        } else if(status == -1) {
            log_e(PRINT_FOTA_TAG, "raw state1 error: %d\n", status);
            status = RAW_FAIL;
        } else {
            //have data need write to flash
        }
    } else {
        log_e(PRINT_FOTA_TAG, "unknown state: %d\n", ota_raw.state);
    }
    return status;
}

void raw_burn_verify(char *buf, int len)
{
    MD5_Update(&ota_raw.mem, buf, len);
}

static int ota_raw_init(char *UNUSED(ip), unsigned int UNUSED(port), unsigned char *UNUSED(file), struct ota_burn *st)
{
    int ret = SUCCESS;
    ota_raw.burn_st = st;
    MD5_Init(&ota_raw.mem);
    ota_raw.init= 1;
    ota_raw.state = 0;
    return SUCCESS;   
}

static int ota_raw_get_hdr()
{
    int ret = SUCCESS;
    while(ota_raw.state == 0) {
        //wait input_raw_data get header data
        OS_MsDelay(1);
    }
    return ota_raw.total_size;
}

static int ota_raw_burn()
{
    //wait input_raw_data write data finish, and return remain size
    OS_MsDelay(10);
    if(ota_raw.data_burn <= 0)
        return 0;
    else
        return ota_raw.data_burn + ota_raw.data_jump;
}

static int ota_raw_verify()
{
    int ret = SUCCESS;
    unsigned char result[16];
    unsigned char md5[16];
    ota_get_md5((char *)md5);
    MD5_Final(result, &ota_raw.mem);
    if(memcmp(md5, result, 16))
    {
        log_e(PRINT_FOTA_TAG, "\nOTA Verify FAIL\n");
        return C_ERROR;
    }
    MD5_Init(&ota_raw.mem);
    ret = ota_raw.burn_st->verify(raw_burn_verify);
    MD5_Final(result, &ota_raw.mem);
    if (memcmp(md5, result, 16))
    {
        log_e(PRINT_FOTA_TAG, "\nOTA Verify FAIL 2\n");
        return C_ERROR;
    }
    else 
    {
        log_i(PRINT_FOTA_TAG, "\nOTA Verify SUCCES\n");
        ota_update_flag();
        return SUCCESS;
    }
}

static int ota_raw_done()
{
    int ret = SUCCESS;
    memset(&ota_raw, 0, sizeof(ota_raw));
    return ret;
}

static int ota_raw_deinit()
{
    int ret = SUCCESS;
    memset(&ota_raw, 0, sizeof(ota_raw));
    return ret;
}

struct protocol raw = 
{
    "raw",
    ota_raw_init,
    ota_raw_get_hdr,
    ota_raw_burn,
    ota_raw_verify,
    ota_raw_done,
    ota_raw_deinit,
};
