#ifndef _HCI_UART_H_
#define _HCI_UART_H_

#include "ssv_types.h"

u32 hci_uart_read (u32 char_2read,          u8* dst);
u32 hci_uart_write(u32 char_2write, const   u8* src);
void hci_uart_init(void);
void hci_uart_deinit(void);
u32 hci_uart_rxbuf_empty();
void insert_cmd_to_rxbuf(u8 *cmd);

#endif // _HCI_UART_H_ 
