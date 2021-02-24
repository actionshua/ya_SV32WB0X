
/*
 * 
 * Author: Tim Li
 *
 */

#include "fota_tftp.h"

typedef struct {
    char strFile[MAX_PATH];
    unsigned int data_jump;
    int data_burn;
    PACKET tftp_buf;
    struct ota_burn *burn_st;
    MD5_CTX network_md5;
    MD5_CTX crypto_md5;
} ota_tftp_st;
static ota_tftp_st ota_tftp;

void tftp_burn_verify(char *buf, int len)
{
    MD5_Update(&ota_tftp.crypto_md5, buf, len);
}

static int ota_tftp_init(char *ip, unsigned int port, unsigned char *file, struct ota_burn *st)
{
    int ret = SUCCESS;
    memset(ota_tftp.strFile, 0, sizeof(ota_tftp.strFile));
    sprintf((char *)ota_tftp.strFile, "%s.bin", file); 
    if(st == NULL) 
    {        
        log_e(PRINT_FOTA_TAG, "Error [%d] %s\n", __LINE__, __func__);
        return A_ERROR;
    }
    ret = tftp_recv_req(ip, port, (char *)ota_tftp.strFile);
    if(ret < SUCCESS)
    {
        log_e(PRINT_FOTA_TAG, "[%d]%s fail: %d\n", __LINE__, __func__, ret);
        return T_ERROR;
    }
    ota_tftp.burn_st = st;
    MD5_Init(&ota_tftp.network_md5);
    MD5_Init(&ota_tftp.crypto_md5);

    return SUCCESS;   
}

static int ota_tftp_get_hdr()
{
    int ret = SUCCESS;
    char *addr;
    ret = tftp_recv(&ota_tftp.tftp_buf, (char *)ota_tftp.strFile);
    if (ret < SUCCESS)
    {
        log_e(PRINT_FOTA_TAG, "[%d]%s fail: %d\n", __LINE__, __func__, ret);
        return T_ERROR;
    }
    ret = ota_get_hdr(ota_tftp.tftp_buf.data.data, OTA_HDR_SIZE);
    if(ret < SUCCESS)
    {
        log_e(PRINT_FOTA_TAG, "[%d]%s fail: %d\n", __LINE__, __func__, ret);
        return T_ERROR;
    }
    ota_tftp.data_burn = ota_get_img_size();
    ota_tftp.data_jump = ota_get_jump_size();
    if(ota_tftp.data_jump > 0)
    {
        ota_tftp.data_jump -= (ota_tftp.tftp_buf.data.dataSize - OTA_HDR_SIZE);
    }
    else
    {
        if(ota_tftp.tftp_buf.data.dataSize > OTA_HDR_SIZE)
        {
            ota_tftp.tftp_buf.data.dataSize -= OTA_HDR_SIZE;
            addr = &ota_tftp.tftp_buf.data.data[OTA_HDR_SIZE];
            MD5_Update(&ota_tftp.network_md5, addr, ota_tftp.tftp_buf.data.dataSize);//chksum before encryption
            ota_tftp.burn_st->owrite(addr, ota_tftp.tftp_buf.data.dataSize);
            MD5_Update(&ota_tftp.crypto_md5, addr, ota_tftp.tftp_buf.data.dataSize);//chksum after encryption
            ota_tftp.data_burn -= ota_tftp.tftp_buf.data.dataSize;
        }
        else
        {
            log_e(PRINT_FOTA_TAG, "[%d] %s: %d\n", __LINE__, __func__, ota_tftp.tftp_buf.data.dataSize);
            return T_ERROR;
        }
    }
    return (ota_tftp.data_jump + ota_tftp.data_burn);
}

static int ota_tftp_burn()
{
    int ret, offset = 0, rlt = 0;
    char *addr;
    rlt = tftp_recv(&ota_tftp.tftp_buf, (char *)ota_tftp.strFile);
    if(rlt < SUCCESS)
    {
        log_e(PRINT_FOTA_TAG, "[%d]%s fail: %d\n", __LINE__, __func__, rlt);
        return T_ERROR;
    }
    if(ota_tftp.data_jump > 0) //if use b, then jump a size
    {
        if(ota_tftp.data_jump >= ota_tftp.tftp_buf.data.dataSize)
        {
            ota_tftp.data_jump -= ota_tftp.tftp_buf.data.dataSize;
            return ota_tftp.data_burn + ota_tftp.data_jump;
        }
        else
        {
            ota_tftp.tftp_buf.data.dataSize -= ota_tftp.data_jump;
            offset = ota_tftp.data_jump;
            ota_tftp.data_jump = 0;
        }
    }
    addr = &ota_tftp.tftp_buf.data.data[offset];
    if(ota_tftp.tftp_buf.data.dataSize > ota_tftp.data_burn)
       ota_tftp.tftp_buf.data.dataSize = ota_tftp.data_burn;

    MD5_Update(&ota_tftp.network_md5, addr, ota_tftp.tftp_buf.data.dataSize);//chksum before encryption

    ret = ota_tftp.burn_st->owrite(addr, ota_tftp.tftp_buf.data.dataSize);
    if(ret != SUCCESS) 
    {
        return H_ERROR;
    }
    MD5_Update(&ota_tftp.crypto_md5, addr, ota_tftp.tftp_buf.data.dataSize);//chksum after encryption
    ota_tftp.data_burn -= ota_tftp.tftp_buf.data.dataSize;
    if(ota_tftp.data_burn <= 0 || rlt == SUCCESS) 
    {
        return SUCCESS;
    }
    else
        return ota_tftp.data_burn + ota_tftp.data_jump;
}

static int ota_tftp_verify()
{
    int ret = SUCCESS;
    unsigned char result[16];
    unsigned char acp_answer[16];
    unsigned char ans[16];
    ota_get_md5((char *)ans);
    MD5_Final(result, &ota_tftp.network_md5);
    MD5_Final(acp_answer, &ota_tftp.crypto_md5);
    if(memcmp(ans, result, 16))
    {
        log_e(PRINT_FOTA_TAG, "\nOTA Verify FAIL\n");
        return C_ERROR;
    }
    MD5_Init(&ota_tftp.crypto_md5);
    ret = ota_tftp.burn_st->verify(tftp_burn_verify);
    MD5_Final(result, &ota_tftp.crypto_md5);
    if (memcmp(acp_answer, result, 16))
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

static int ota_tftp_done()
{
    int ret = SUCCESS;
    return ret;
}

static int ota_tftp_deinit()
{
    int ret = SUCCESS;
    memset(&ota_tftp, 0, sizeof(ota_tftp));
    return ret;
}

struct protocol tftp = 
{
    "tftp",
    ota_tftp_init,
    ota_tftp_get_hdr,
    ota_tftp_burn,
    ota_tftp_verify,
    ota_tftp_done,
    ota_tftp_deinit,
};
