#ifndef _HCI_CTRL_H_
#define _HCI_CTRL_H_

#include "ssv_types.h"

s16 hci_cmd(u32 cmd_len, const u8* cmd, u32* sync_evt_len, u8* sync_evt);

#endif // _HCI_CTRL_H_
