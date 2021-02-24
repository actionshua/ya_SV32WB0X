#ifndef __CONDOR_CLI_H_
#define __CONDOR_CLI_H_

// 8K
//#define BSP_MEM_BIST_CMD    (1)
    #define BSP_MEM_BIST_SIZE               (8*1024/4)
    #define BSP_MEM_BIST_PATTERN_COUNT      (16)
    #define BSP_MEM_BIST_TIMES              (100)
    #define BSP_MEM_BIST_DBG                (0)
    #define BSP_MEM_BIST_RND_ACCESS         (1)

#define BSP_MEM_STATUS_CMD  (1)
#define BSP_TIMER_TEST      (1)

#define REG_CMD
//#define DTM_CMD

#if (BSP_TIMER_TEST != 1)
// add a msg test task.
    #if !defined(__SSV_LINUX_SIM__)
        #define BSP_MSG_CMD         (0)
    #endif
#endif

typedef void (*cli_cmd_handle)(s32, s8 **);


/**
* struct ssv_cli_cmd - The data structure to describe the cli user commands.
*
* @ cmd:
* @ cmd_hdle
* @ cmd_usage
*/
typedef struct ssv_cli_cmd {
    const char      *cmd;
    cli_cmd_handle  cmd_handle;
    const char      *cmd_usage;
} ssv_cli_cmd_st;

/**
* s32 ssv_cli_init() - API used to invoke CLI and register the user defined
*                                 command table.
*
 @ cmd_tbl
*/
SSV_API void ssv_cli_init(void);

/*
 *
 */
SSV_API void ssv_cli_task(void);


extern const ssv_cli_cmd_st g_cli_cmd_tbl[];


#endif /* __CONDOR_CLI_H_ */

