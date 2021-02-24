#ifndef _DRV_DBG_UART_H_
#define _DRV_DBG_UART_H_

#include "stdint.h"

void dbg_uart_putc(int8_t ch);
int8_t   dbg_uart_getc(void);
uint32_t  dbg_uart_kbhit(void);
void dbg_uart_prints(int8_t *s);
void dbg_uart_init(void);



#endif  /// end of _DRV_DBG_UART_H_

