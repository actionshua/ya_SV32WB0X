#ifndef __DRV_UART_H__
#define __DRV_UART_H__
#include "pcb_config.h"
#include "ssv_types.h"
#include "condor_ssv_lib.h"
#include "regs/chip_reg.h"
#include "condor.h"
#include "drv/base_peri.h"

#if (MAIN_CHIP != P7005)
#error please check your main chipid.
#endif 

typedef struct uart
{
    const base_peri_st module;
    //volatile uint32_t *int_status;
    uint8_t int_tx_offset; //means STS, MASK, RAW must the same.
    uint8_t int_rx_offset;
    uint8_t gpio_tx;
    uint8_t gpio_rx;
    CONDOR_UART_Type * const regs;
} uart_st;

extern const uart_st dbguart, uart0, uart1;

#define UART_PARITY_NONE	0
#define UART_PARITY_ODD		1
#define UART_PARITY_EVEN	2

// 1. turn on clk
// 2. do uart reg init
// 3. turn on UART-GPIO 
//
// data_bits	: 5|6|7|8
// stop_bits	: 1|2
bool	uart_init(const uart_st *uart, 
				  u32	baudrate, 
				  u8	data_bits,
				  u8	parity,
				  u8	stop_bits);
// 1. turn off clk
void	uart_deinit(const uart_st *uart);

void	uart_enable(const uart_st *uart);
bool	uart_set_baudrate(const uart_st *uart, u32 baudrate);

u8		uart_kbhit(const uart_st *uart);
s8		uart_getc(const uart_st *uart);

void	uart_putc(const uart_st *uart, s8 ch);
void	uart_prints(const uart_st *uart, s8 *s);

// TBD
void	uart_txrx_exchange(const uart_st *uart);

#endif		// __DRV_UART_H__
