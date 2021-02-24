#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "atcmd.h"
#include "osal.h"
#ifdef IPERF3_EN
#include "iperf.h"
#elif IPERF2_EN
#include "iperf2.h"
#endif

#ifdef IPERF3_EN
void iperf3(void *args)
{
    stParam param;
    memcpy(&param, args, sizeof(stParam));
    OS_MemFree(args);
    net_app_iperf3(param.argc, param.argv);

    OS_TaskDelete(NULL);
}
#endif

int At_IPERF(stParam *param)
{
    printf("<%s>%d\n",__func__,__LINE__);

    if(param->argc == 1)
    {
        int buflen, i;
        const char delimiters = ' ';
        char* bufCmd = param->argv[0];
        printf("\n[%s]\n", bufCmd);

        buflen = strlen (bufCmd);
        if (strlen (bufCmd) == 0) 
            return -1;

        param->argc = 1;
        param->argv[param->argc] = &bufCmd[0];

        param->argc++; 
        i = 0;
        while( i<80 )
        {
            for(; i < buflen ; i++)
            {
                if(bufCmd[i] == delimiters)
                {
                    bufCmd[i] = 0;
                    break;
                }
            }

            if(bufCmd[i + 1] != 0)
            {
                param->argv[param->argc] = &bufCmd[i + 1];
                param->argc ++;
            }
            else
                break;
        }

        param->argv[0] = "iperf";
        printf("argc=%d\n",param->argc);
        if (param->argv[0]) {
            printf("argv[0]=%s\n",param->argv[0]);
        }
        if (param->argv[1]) {
            printf("argv[1]=%s\n",param->argv[1]);
        }
        if (param->argv[2]) {
            printf("argv[2]=%s\n",param->argv[2]);
        }
        if (param->argv[3]) {
            printf("argv[3]=%s\n",param->argv[3]);
        }
        if (param->argv[4]) {
            printf("argv[4]=%s\n",param->argv[4]);
        }
    }
    else if(param->argc >= 2)   //old parser
    {
        printf("argc=%d\n",param->argc);
        if (param->argv[0]) {
            printf("argv[0]=%s\n",param->argv[0]);
        }
        if (param->argv[1]) {
            printf("argv[1]=%s\n",param->argv[1]);
        }
        if (param->argv[2]) {
            printf("argv[2]=%s\n",param->argv[2]);
        }
        if (param->argv[3]) {
            printf("argv[3]=%s\n",param->argv[3]);
        }
        if (param->argv[4]) {
            printf("argv[4]=%s\n",param->argv[4]);
        }
    }
    else
    {
        printf("erro iperf param\n");
    }
#ifdef TCPIPSTACK_EN
#ifdef IPERF3_EN
    //iperf3(param->argc, param->argv);
    void *param_ptr;
    param_ptr = OS_MemAlloc(sizeof(stParam));
    memcpy(param_ptr, param, sizeof(stParam));
    if (!OS_TaskCreate(iperf3, "iperf3 task", 512, param_ptr, OS_TASK_MIDDLE_PRIO, NULL)) {
        OS_MemFree(param_ptr);
    }
#elif IPERF2_EN
    iperf(param->argc, param->argv);
#endif
#endif

    return 0;
}

