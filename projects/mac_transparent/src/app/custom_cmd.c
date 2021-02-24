
#include <stdio.h>
#include <string.h>
#include "soc_types.h"
#include "soc_defs.h"
#include "osal.h"

#include "cli.h"
#include "error.h"

#include <lowpower.h>
#include <logger.h>
#include <drv_tim_timer.h>

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

int Cmd_WriteReg32 (s32 argc, char *argv[])
{ 
    char *pkey = 0, *pvalue = 0;

    if (argc < 3) {
        return ERROR_INVALID_PARAMETER;
    }
  
    pkey = argv[1];
    pvalue = argv[2];
    
    if( pkey == 0 || pvalue == 0)
        return ERROR_INVALID_PARAMETER;
    
    unsigned int address = strtoul(pkey, NULL, 16);
    unsigned int data = strtoul(pvalue, NULL, 16);

    printf("reg : write 0x%x  0x%x \n", address, data);

    REG32(address)  = data;

    return ERROR_SUCCESS;
}

int Cmd_ReadReg32 (s32 argc, char *argv[])
{
    char *pkey = 0;
    unsigned int address;
    if (argc < 2) {
        return ERROR_INVALID_PARAMETER;
    }

    pkey = argv[1];

    address = strtoul(pkey, NULL, 16);

    printf("reg : read 0x%08x  0x%08x \n", address, (unsigned int)REG32(address));
    return ERROR_SUCCESS;
}

/* ---------------------- Registered CMDs to CMD Table ---------------------- */
const CLICmds gCustomCmdTable[] =
{
    { "regw",               Cmd_WriteReg32,     "regw"},
    { "regr",               Cmd_ReadReg32,      "regr"},

    { "meminfo",            Cmd_meminfo,        "meminfo"},
    { "sysinfo",            Cmd_sysinfo,        "sysinfo"},

    { (const char *)NULL, (CliCmdFunc)NULL,   (const char *)NULL },
};


