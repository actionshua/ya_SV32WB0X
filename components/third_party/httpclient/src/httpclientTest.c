/* Copyright (C) 2012 mbed.org, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "httpclient.h"

#define BUF_SIZE        (1024 * 1)
#define HTTP_GET_URL    "http://www.baidu.com/"
#define HTTPS_GET_URL    "https://www.baidu.com/"

static void httpclient_test_get(void)
{
    char *get_url = HTTP_GET_URL;
    char *get_urls = HTTPS_GET_URL;
    httpclient_t client = {0};
    httpclient_data_t client_data = {0};
    char *buf, *header;
    HTTPCLIENT_RESULT ret;
    int val_pos, val_len;

    OS_MsDelay(3000);
    buf = OS_MemAlloc(BUF_SIZE);    
    header = OS_MemAlloc(BUF_SIZE);
    if (buf == NULL || header == NULL) {        
        log_e(PRINT_HTTPC_TAG, "\nmemory malloc failed\n");
        return;
    }
    
    // Http "get"
    client_data.header_buf = header;    
    client_data.header_buf_len = BUF_SIZE;
    client_data.response_buf = buf;
    client_data.response_buf_len = BUF_SIZE;    
    client_data.response_buf[0] = '\0';
    ret = httpclient_get(&client, get_url, &client_data);
    if (ret < 0) {
        log_e(PRINT_HTTPC_TAG, "\nhttpclient_get fail, reason:%d.\n", ret);
        goto fail;
    }
    log_i(PRINT_HTTPC_TAG, "\ndata received: %s\n", client_data.response_buf);

    // get response header
    if(0 == httpclient_get_response_header_value(client_data.header_buf, "Content-length", &val_pos, &val_len))
        log_i(PRINT_HTTPC_TAG, "Content-length: %.*s", val_len, client_data.header_buf + val_pos);
    log_i(PRINT_HTTPC_TAG, "\x1B[31m");
    // Print final log
    if (ret >= 0)    
        log_i(PRINT_HTTPC_TAG, "\n===http test success.===\n");
    else        
        log_e(PRINT_HTTPC_TAG, "\n===http test fail, reason:%d.===\n", ret);
    log_i(PRINT_HTTPC_TAG, "\x1B[0m");
    ret = httpclient_get(&client, get_url, &client_data);
    if (ret < 0) {
        log_e(PRINT_HTTPC_TAG, "\nhttpclient_get fail, reason:%d.\n", ret);
        goto fail;
    }
    log_i(PRINT_HTTPC_TAG, "\ndata received: %s\n", client_data.response_buf);

    // get response header
    if(0 == httpclient_get_response_header_value(client_data.header_buf, "Content-length", &val_pos, &val_len))
        log_i(PRINT_HTTPC_TAG, "Content-length: %.*s", val_len, client_data.header_buf + val_pos);
    log_i(PRINT_HTTPC_TAG, "\x1B[31m");
    if (ret >= 0)    
        log_i(PRINT_HTTPC_TAG, "\n===https test success.===\n");
    else        
        log_e(PRINT_HTTPC_TAG, "\n===https test fail, reason:%d.===\n", ret);
    // Reset color.
    log_i(PRINT_HTTPC_TAG, "\x1B[0m");
fail:
    OS_MemFree(buf);
    OS_MemFree(header);
}

void httpclient_test()
{
    httpclient_test_get();
    OS_TaskDelete(NULL);
}


void easy_httpclient_test()
{
    if (OS_TaskCreate(httpclient_test, "test_task", 1024, NULL, OS_TASK_MIDDLE_PRIO, NULL) != 1)
    {
        printf("Failed to create test task\n");
    }
}
