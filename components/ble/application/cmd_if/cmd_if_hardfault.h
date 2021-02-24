#ifndef _CMD_IF_HARDFAULT_H_
#define _CMD_IF_HARDFAULT_H_

// TODO: CMD_IF_HARDFAULT isn't define yet
typedef enum {
    CMD_IF_HARDFAULT_EVT_BUF_OVERFLOW = 0x40,
    CMD_IF_HARDFAULT_UNKNOWN_INDICATOR,
    CMD_IF_HARDFAULT_HCI_ENABLE_FAIL,
    CMD_IF_HARDFAULT_PROGRAM_EXCEPTION,
}   CMD_IF_HARDFAULT;

/**
 * hardfault
 *
 */
typedef struct cmd_if_hardfault {

    u8  code;
    u32 description;

} cmd_if_hardfault_st;

extern cmd_if_hardfault_st g_cmd_if_hardfault;

#define cmd_if_hardfault_assert(_CODE_, _DESCRIPTION_) do { \
    g_cmd_if_hardfault.code         = (_CODE_);             \
    g_cmd_if_hardfault.description  = (_DESCRIPTION_);      \
} while(0)

#define cmd_if_hardfault_clear() do {       \
    g_cmd_if_hardfault.code         = (0);  \
    g_cmd_if_hardfault.description  = (0);  \
} while(0)

#endif // _CMD_IF_HARDFAULT_H_
