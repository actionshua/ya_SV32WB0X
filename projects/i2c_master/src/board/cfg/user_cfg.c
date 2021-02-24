#include <stdint.h>
#include "user_cfg.h"
#include <string.h>
#include <stdio.h>
//#include "atcmd.h"

#define USER_CFG_ASSERT(cmp) \
    do { \
    } while(!(cmp))

const struct user_cfg g_user_cfg __attribute__((section(".user_data")));



