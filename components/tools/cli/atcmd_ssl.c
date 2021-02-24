#include <string.h>
#include <stdio.h>
#include <unistd.h>
//#include "sys_status_api.h"

#include "soc_types.h"
#include "atcmd.h"
//#include "atcmdlib.h"
#include "netstack_def.h"
#include "error.h"
#include "wifi_api.h"
#include "mbedtls_api.h"

#define SUPPORT_SSL_NUM 4
#ifdef MBEDTLS_EN
int At_SSLTest(stParam *param)
{
    char *pIp = 0, *pport = 0, *psec;
    s32 i = 0;
    u16 port;
    s8 status = 0;
    u8 test_type = 0;
    u8 max_argc = 0;
    u8 sec = 0;
    
    if (get_wifi_status() != 1)
        return ERROR_WIFI_CONNECTION;

    test_type = atoi(param->argv[0]);

    if(test_type == 0) {
        max_argc = 1;
    } else if(test_type == 1){
        max_argc = 4;
    } else {
        printf("unknown type: %d\n", test_type);
        return ERROR_INVALID_PARAMETER;
    }
    if (param->argc < max_argc) {
        printf("unknown argc: %d %d\n", param->argc, max_argc);
        return ERROR_INVALID_PARAMETER;
    }

    if(test_type == 0) {
        ssl_mbed_test();
    } else if(test_type == 1) {
        pIp = param->argv[1];
        pport = param->argv[2];
        port = atoi (pport);
        psec = param->argv[3];
        sec = atoi (psec);
        if (port == 0) {
            printf("unknown port: %d\n", port);
            return ERROR_INVALID_PARAMETER;
        }
        ssl_mbed_thoughtput_test(pIp, port, sec);
    }
    return ERROR_SUCCESS;
}

#endif

