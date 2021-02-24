#ifndef _CLI_H_
#define _CLI_H_
//standard libary include
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLI_BUFFER_SIZE   (2048)
#define CLI_HISTORY_NUM (5)
//#define DEFAULT_CLI_BUF_SIZE   (128)
#define CLI_ARG_SIZE		(20)
#define CLI_PROMPT			("#")

inline int get_cli_buffer_len(void);

//typedef void (*CliCmdFunc) ( s32, char  ** );
typedef int (*CliCmdFunc) ( int32_t, char* argv[] );

typedef struct CLICmds_st
{
        const char           *Cmd;
        CliCmdFunc          CmdHandler;
        const char           *CmdUsage;

} CLICmds, *PCLICmds;

extern const CLICmds gCliCmdTable[];

void Cli_Init( void );
void Cli_Start( void );
void Cli_Task( void *args );
void drv_uart_tx_0(char ch);


#endif /* _CLI_H_ */

