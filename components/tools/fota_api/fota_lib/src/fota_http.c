
/*
 * 
 * Author: Tim Li
 *
 */

#include "fota_http.h"

#define BUF_SIZE        (1024 * 1)

typedef struct {    
    char strFile[MAX_PATH];
    httpclient_t client;
    httpclient_data_t client_data;
    char *httpc_buf;
    char *httpc_header;
    struct ota_burn *burn_st;
    MD5_CTX network_md5;
    MD5_CTX crypto_md5;
} ota_http_st;
static ota_http_st ota_http;
static int prv_len = -1;

static void http_burn_verify(char *buf, int len)
{
    MD5_Update(&ota_http.crypto_md5, buf, len);
}

static int ota_http_get_img()
{
    char header[256] = {0};
    int offset = OTA_HDR_SIZE + ota_get_jump_size();
    unsigned int img_size = ota_get_img_size();
    if (ota_http.httpc_buf == NULL || ota_http.httpc_header == NULL) 
    {        
        log_e(PRINT_FOTA_TAG, "Error [%d] %s\n", __LINE__, __func__);
        return  A_ERROR;
    }
    memset(&ota_http.client_data, 0, sizeof(ota_http.client_data));
    memset(&ota_http.client, 0, sizeof(ota_http.client));
    ota_http.client_data.header_buf = ota_http.httpc_header;    
    ota_http.client_data.header_buf_len = BUF_SIZE;
    ota_http.client_data.response_buf = ota_http.httpc_buf;
    ota_http.client_data.response_buf_len = BUF_SIZE;    
    ota_http.client_data.response_buf[0] = '\0';
    if (httpclient_connect(&ota_http.client, ota_http.strFile) != HTTPCLIENT_OK)
    {
        log_e(PRINT_FOTA_TAG, "\n[%d] %s!\n", __LINE__, __func__);
        return H_ERROR;
    }
    //Write User Header
    snprintf(header, sizeof(header), "Range: %s=%u-%u\r\n", "bytes",
                     offset, offset + img_size - 1); /* Write request */
    httpclient_set_custom_header(&ota_http.client, header);
    if (httpclient_send_request(&ota_http.client, ota_http.strFile, 
          HTTPCLIENT_GET, &ota_http.client_data) != HTTPCLIENT_OK)
    {
        log_e(PRINT_FOTA_TAG, "\n[%d] %s\n", __LINE__, __func__);
        return H_ERROR;
    }
    return SUCCESS;
}

static int ota_http_get_header()
{
    char header[256] = {0};
    int val_pos, val_len, ret;
   //Write User Header
    snprintf(header, sizeof(header), "Range: %s=%d-%d\r\n", "bytes", 0, OTA_HDR_SIZE - 1); /* Write request */
    httpclient_set_custom_header(&ota_http.client, header);
    if (httpclient_send_request(&ota_http.client, ota_http.strFile, 
            HTTPCLIENT_GET, &ota_http.client_data) != HTTPCLIENT_OK)
    {
        log_e(PRINT_FOTA_TAG, "\n[%d] %s\n", __LINE__, __func__);
        return H_ERROR;
    }
    ret = httpclient_recv_response(&ota_http.client, &ota_http.client_data);   
    if (ret < HTTPCLIENT_OK) 
    {
        log_e(PRINT_FOTA_TAG, "\n[%d] %s: %d!\n", __LINE__, __func__, ret);
        return H_ERROR;
    }
    if ((httpclient_get_response_code(&ota_http.client) < HTTP_OK) || 
        (httpclient_get_response_code(&ota_http.client) >= HTTP_BAD_REQUEST)) 
    {
        log_e(PRINT_FOTA_TAG, "\n[%d] %s error code: %d\n", __LINE__, __func__, httpclient_get_response_code(&ota_http.client));
        return H_ERROR;
    }
    // get response header
    if(0 == httpclient_get_response_header_value(ota_http.client_data.header_buf, "Accept-Ranges", &val_pos, &val_len)) 
    {
        if(!strncmp("none", ota_http.client_data.header_buf + val_pos, val_len)) 
        {
                log_e(PRINT_FOTA_TAG, "OTA not support range request\n");
                return NO_SUPPORT; //don't download image
        }
    }
    if(0 == httpclient_get_response_header_value(ota_http.client_data.header_buf, "Content-length", &val_pos, &val_len))
    httpclient_close(&ota_http.client);
    return SUCCESS;
}

static int ota_http_init(char *ip, unsigned int port, unsigned char *file, struct ota_burn *st)
{
    memset(ota_http.strFile, 0, sizeof(ota_http.strFile));
    sprintf((char *)ota_http.strFile, "http://%s:%d/%s.bin", 
                  ip, port, file);
    ota_http.httpc_buf = OS_MemAlloc(BUF_SIZE);    
    ota_http.httpc_header = OS_MemAlloc(BUF_SIZE);
    if (ota_http.httpc_buf == NULL || ota_http.httpc_header == NULL || st == NULL) 
    {        
        log_e(PRINT_FOTA_TAG, "Error [%d] %s\n", __LINE__, __func__);
        return A_ERROR;
    }
    memset(&ota_http.client_data, 0, sizeof(ota_http.client_data));
    memset(&ota_http.client, 0, sizeof(ota_http.client));
    ota_http.client_data.header_buf = ota_http.httpc_header;
    ota_http.client_data.header_buf_len = BUF_SIZE;
    ota_http.client_data.response_buf = ota_http.httpc_buf;
    ota_http.client_data.response_buf_len = BUF_SIZE;
    ota_http.client_data.response_buf[0] = '\0';
    ota_http.burn_st = st;
    prv_len = -1;
    MD5_Init(&ota_http.network_md5);
    MD5_Init(&ota_http.crypto_md5);

    return SUCCESS;
}

static int ota_http_get_hdr()
{
    int len = 0;
    int  ret = 0;
    char header[256] = {0};
    ota_http.client_data.response_buf[0] = '\0';
    if (httpclient_connect(&ota_http.client, ota_http.strFile) != HTTPCLIENT_OK)
    {
        log_e(PRINT_FOTA_TAG, "\n[%d] %s\n", __LINE__, __func__);
        return H_ERROR;
    }
    ret = ota_http_get_header();
    if(ret < SUCCESS)
    {
        printf("\n[%d] %s: %d!\n", __LINE__, __func__, ret);
        return H_ERROR;
    }
    len = (ota_http.client_data.response_content_len - ota_http.client_data.retrieve_len);
    ret = ota_get_hdr(ota_http.client_data.response_buf, len);
    if(ret < SUCCESS)
    {
        log_e(PRINT_FOTA_TAG, "\n[%d] %s: %d!\n", __LINE__, __func__, ret);
        return H_ERROR;
    }
    ret = ota_http_get_img();
    if(ret < SUCCESS)
    {
        log_e(PRINT_FOTA_TAG, "\n[%d] %s: %d!\n", __LINE__, __func__, ret);
        return H_ERROR;
    }
    return ota_get_img_size();
}

static int ota_http_burn()
{
    char *addr;
    int len = 0;
    int ret = 0;
    HTTPCLIENT_RESULT rlt = 0;
    rlt = httpclient_recv_response(&ota_http.client, &ota_http.client_data);
    if(rlt < HTTPCLIENT_OK) 
    {
        log_e(PRINT_FOTA_TAG, "\n[%d]HTTP recv Response Error: %d!\n", __LINE__, rlt);
        return H_ERROR;
    }
    if((httpclient_get_response_code(&ota_http.client) < HTTP_OK) || 
        (httpclient_get_response_code(&ota_http.client) >= HTTP_BAD_REQUEST)) 
    {
        log_e(PRINT_FOTA_TAG, "\nHTTP Response Error code: %d\n", httpclient_get_response_code(&ota_http.client));
        return H_ERROR;
    }
    if(prv_len == -1)
    {
        prv_len = ota_http.client_data.response_content_len;
    }
    addr = ota_http.client_data.response_buf;
    len = (prv_len - ota_http.client_data.retrieve_len);

    MD5_Update(&ota_http.network_md5, addr, len);

    ret = ota_http.burn_st->owrite(addr, len);
    if(ret != SUCCESS) 
    {
        return H_ERROR;
    }
    MD5_Update(&ota_http.crypto_md5, addr, len);
    prv_len = ota_http.client_data.retrieve_len;
    if(rlt == HTTPCLIENT_OK)
    {
        return SUCCESS; // download img finish
    }
    return ota_http.client_data.retrieve_len;
}

static int ota_http_verify()
{
    int ret = SUCCESS;
    unsigned char result[16];
    unsigned char acp_answer[16];
    unsigned char ans[16];
    ota_get_md5((char *)ans);
    MD5_Final(result, &ota_http.network_md5);
    MD5_Final(acp_answer, &ota_http.crypto_md5);
    if (memcmp(ans, result, 16))
    {
        log_e(PRINT_FOTA_TAG, "\nOTA Verify FAIL\n");
        return C_ERROR;
    }
    MD5_Init(&ota_http.crypto_md5);
    ret = ota_http.burn_st->verify(http_burn_verify);
    MD5_Final(result, &ota_http.crypto_md5);
    if (memcmp(acp_answer, result, 16) || ret != SUCCESS)
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

static int ota_http_done()
{
    int ret = SUCCESS;
    httpclient_close(&ota_http.client);
    OS_MemFree(ota_http.httpc_buf);
    ota_http.httpc_buf = NULL;
    OS_MemFree(ota_http.httpc_header);
    ota_http.httpc_header = NULL;
    return ret;
}

static int ota_http_deinit()
{
    int ret = SUCCESS;
    memset(&ota_http, 0, sizeof(ota_http));
    return ret;
}

struct protocol http = 
{
    "http",
    ota_http_init,
    ota_http_get_hdr,
    ota_http_burn,
    ota_http_verify,
    ota_http_done,
    ota_http_deinit,
};

