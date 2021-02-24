#ifndef _ATCMD_H_
#define _ATCMD_H_

#include "Cabrio-conf.h"
#include <stdio.h>
//#include "console.h"
#include "logger.h"

////Customer AT Command
#define PRINT_ATCMD_TAG LOG_TAG_ATCMD
#define ATCMD_LOG_E(format, ...) log_e(PRINT_ATCMD_TAG, format, ##__VA_ARGS__)
#define ATCMD_LOG_W(format, ...) log_w(PRINT_ATCMD_TAG, format, ##__VA_ARGS__)
#define ATCMD_LOG_I(format, ...)\
	do{\
		log_i(PRINT_ATCMD_TAG, format, ##__VA_ARGS__);\
		at_cmd_log_write(format, ##__VA_ARGS__);\
	}while(0)
#define ATCMD_LOG_D(format, ...) log_d(PRINT_ATCMD_TAG, format, ##__VA_ARGS__)
#define ATCMD_LOG_V(format, ...) log_v(PRINT_ATCMD_TAG, format, ##__VA_ARGS__)

#define MAX_CMD_LEN (32)
#define MAX_ARGUMENT 64

typedef struct _stParam
{
	char*	argv[MAX_ARGUMENT];
	int	argc;
} stParam;

typedef int (*PF_handle) (stParam *param);
typedef struct _at_cmd_info
{
	char*		atCmd;
	PF_handle	pfHandle;
    uint8_t maxargu;
} at_cmd_info;


int get_atcmd_homekit_size();

int At_Parser (char *buff, int len);
void At_RespOK (char* pStr);
int At_CmdList (stParam *param);
int At_ShowRfCommand (stParam *param);

int At_MacHWQueue(stParam *param);
int At_MacHWMIB(stParam *param);
int At_RCINFO(stParam *param);
int At_RCMASK(stParam *param);

#if 1 //AT cmd log to buffer.
int at_cmd_log_enable(void);
int at_cmd_log_disable(void);
int at_cmd_log_buf_get(char **buf, unsigned int *buflen);
int at_cmd_log_print(void);
int at_cmd_log_write(const char* fmt, ...);
#endif
#endif
