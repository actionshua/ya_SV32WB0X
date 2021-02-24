/**
 * cmd_if: this file handle interface with external processor
 *
 */
#ifndef _CMD_IF_H_
#define _CMD_IF_H_

#include "ssv_types.h"

/**
 * cmd_if_async_evt_inq
 *  - used by les-evt handle, implemented by memcpy
 *
 */
u8 cmd_if_async_evt_inq(u8* evt, u8 evt_len, void* les_ptr);


/**
 *  select if when power-up
 *
 */
typedef u32 (*CMD_IF_RX)(u32 rx_len,        u8* rx);
typedef u32 (*CMD_IF_TX)(u32 tx_len, const  u8* tx);
void cmd_if_register(CMD_IF_TX tx, CMD_IF_RX rx);

/**
 * cmd_if status
 *  - return busy, if any tx/rx in progress
 *
 */
typedef enum {
    CMD_IF_STATUS_IDLE = 0,
    CMD_IF_STATUS_BUSY,
    CMD_IF_STATUS_HARDFAULT,
}   CMD_IF_STATUS;

CMD_IF_STATUS cmd_if();

/**
 * configurations
 *
 */
#define CMD_IF_RX_BUF_SIZE 256
#define CMD_IF_TX_BUF_SIZE 256

#define CMD_IF_ASYNC_EVT_BUF_DEPTH 8

#endif  // _CMD_IF_H_
