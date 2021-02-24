#ifndef MINI_CLI_H
#define MINI_CLI_H

#include <stdint.h>
#define M_MINI_CLI_CMD_MAX_LEN      (20)

typedef void (*mini_cli_command)(s32 argc, s8 **argv);

typedef struct _mini_cli_cmd_st {
    const char *cmdname;
    const mini_cli_command handler;
    const char *desc;
    struct _mini_cli_cmd_st *next;
} mini_cli_cmd_st;

typedef struct _mini_cli_st {
    s8 idx;
    s8 cmd[M_MINI_CLI_CMD_MAX_LEN];
    //s8 *cmd;
    s8 max_arg_len;
    s8 max_argc;
    s8 argc;
    s8 is_arg_used;
    s8 *args;
    s8 **argv;
    mini_cli_cmd_st *cmd_list;
} mini_cli_st;

extern void mini_cli_init(mini_cli_st *cli, s8 max_argc, s8 max_arg_len, mini_cli_cmd_st *table);
extern void mini_cli_static_init(mini_cli_st *cli, s8 max_argc, s8 max_arg_len, s8 *args, s8 **argv, mini_cli_cmd_st *table);
extern void mini_cli_process(mini_cli_st *cli, u8 data);
extern void mini_cli_register_cmd(mini_cli_st *cli, mini_cli_cmd_st *c_list);


#endif /* end of include guard: MINI_CLI_H */
