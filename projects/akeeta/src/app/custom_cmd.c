
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "soc_types.h"
#include "soc_defs.h"
#include "osal.h"

#include "cli.h"
#include "error.h"

#include "logger.h"
#include <attrs.h>
#include <drv_gpio.h>

#define CMD_TAG       LOG_TAG_CMD
#define CMD_LOG_E(format, ...) log_e(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_W(format, ...) log_w(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_I(format, ...) log_i(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_D(format, ...) log_d(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_V(format, ...) log_v(CMD_TAG, format, ##__VA_ARGS__)

int Cmd_meminfo(s32 argc, char *argv[])
{
    printf("\n");
    OS_MemInfo();
    return ERROR_SUCCESS;
}

int Cmd_sysinfo(s32 argc, char *argv[])
{
    printf("\n");
    OS_SysInfo();
    return ERROR_SUCCESS;
}

int Cmd_log(s32 argc, char *argv[])
{
    int i;

    char* tag_array[5] = {"app", "driver", "app_iperf", "lwip", "app_main"}; 

    for(i=0; i<5; i++)
    {
        printf("\n");
        CMD_LOG_E("(%s)this is ERROR message\n", tag_array[i]);
        CMD_LOG_W("(%s)this is WARN message\n", tag_array[i]);
        CMD_LOG_I("(%s)this is INFO message\n", tag_array[i]);
        CMD_LOG_D("(%s)this is DEBUG message\n", tag_array[i]);
        CMD_LOG_V("(%s)this is VERBOSE message\n", tag_array[i]);
    }

    return ERROR_SUCCESS;
}

int Cmd_tag(s32 argc, char *argv[])
{
    printf("Set Tag %s to debug leve %d\n", argv[1], atoi(argv[2]));
    set_tag_level(atoi(argv[1]), atoi(argv[2]) );

    return 0;
}

int Cmd_show(s32 argc, char *argv[])
{
    show_tag_level_list();
    return 0;
}

/* ---------------------- Registered CMDs to CMD Table ---------------------- */
const CLICmds gCustomCmdTable[] =
{
    { "meminfo",            Cmd_meminfo,        "meminfo"},
    { "sysinfo",            Cmd_sysinfo,        "sysinfo"},

    { "cmd_log",            Cmd_log,        "test command"},   
    { "cmd_tag",            Cmd_tag,        "test command"}, 
    { "cmd_show",            Cmd_show,        "test command"}, 
    
    { (const char *)NULL, (CliCmdFunc)NULL,   (const char *)NULL },
};


