#ifndef __DRV_UART_INTERNAL_H__
#define __DRV_UART_INTERNAL_H__
#include "condor.h"

#if (MAIN_CHIP != P7005)
#error please check your main chipid.
#endif 

// HW view:
//          (N-bytes)          (1-byte)
//		¢x   tx_fifo   ¢x --> ¢x  tx_thr   ¢x --> waveform
//		¢x   rx_fifo   ¢x <-- ¢x  rx_thr   ¢x <-- waveform
//
#define uart_get_data(p)					((p)->regs->DATA_b.DATA)
#define uart_set_data(p, v)					((p)->regs->DATA_b.DATA = (v))

#define uart_get_IER(p)						((p)->regs->IER)
#define uart_get_data_rdy_ie(p)				((p)->regs->IER_b.DATA_RDY_IE)
#define uart_get_tx_thr_empty_ie(p)			((p)->regs->IER_b.THR_EMPTY_IE)
#define uart_get_rx_line_sts_ie(p)			((p)->regs->IER_b.RX_LINESTS_IE)
#define uart_get_tx_high_thrd_ie(p)			((p)->regs->IER_b.TX_THRH_IE)
#define uart_get_tx_low_thrd_ie(p)			((p)->regs->IER_b.TX_THRL_IE)

#define uart_set_IER(p, v)					((p)->regs->IER					= (v))
#define uart_set_data_rdy_ie(p, v)			((p)->regs->IER_b.DATA_RDY_IE	= (v))
#define uart_set_tx_thr_empty_ie(p, v)		((p)->regs->IER_b.THR_EMPTY_IE	= (v))
#define uart_set_rx_line_sts_ie(p, v)		((p)->regs->IER_b.RX_LINESTS_IE	= (v))
#define uart_set_tx_high_thrd_ie(p, v)		((p)->regs->IER_b.TX_THRH_IE	= (v))
#define uart_set_tx_low_thrd_ie(p, v)		((p)->regs->IER_b.TX_THRL_IE	= (v))

#define RX_TRG_LVL_1_CHAR 		0
#define RX_TRG_LVL_4_CHAR 		1
#define RX_TRG_LVL_8_CHAR 		2
#define RX_TRG_LVL_14_CHAR 		3

#define RX_TRG_LVL_TO_CHARS(n)	(((n == 0) ? 1 : ((n == 1) ? 4 : ((n == 2) ? 8 : 14))))

#define uart_get_FCR(p)						((p)->regs->FCR)
#define uart_get_trx_fifo_en(p)				((p)->regs->FCR_b.FIFO_EN)
#define uart_get_rx_fifo_rst(p)				((p)->regs->FCR_b.RXFIFO_RST)
#define uart_get_tx_fifo_rst(p)				((p)->regs->FCR_b.TXFIFO_RST)
#define uart_get_dma_mode(p)				((p)->regs->FCR_b.DMA_MODE)
#define uart_get_rx_fifo_trg_lvl(p)			((p)->regs->FCR_b.RXFIFO_TRGLVL)

#define uart_set_FCR(p, v)					((p)->regs->FCR					= (v))
#define uart_set_trx_fifo_en(p, v)			((p)->regs->FCR_b.FIFO_EN		= (v))
#define uart_set_rx_fifo_rst(p, v)			((p)->regs->FCR_b.RXFIFO_RST	= (v))
#define uart_set_tx_fifo_rst(p, v)			((p)->regs->FCR_b.TXFIFO_RST	= (v))
#define uart_set_dma_mode(p, v)				((p)->regs->FCR_b.DMA_MODE		= (v))
#define uart_set_rx_fifo_trg_lvl(p, v)		((p)->regs->FCR_b.RXFIFO_TRGLVL	= (v))

#define uart_set_trx_fifo_en(p, v)			((p)->regs->FCR_b.FIFO_EN		= (v))
#define uart_clr_rx_fifo(p)					((p)->regs->FCR_b.RXFIFO_RST	= 1)
#define uart_clr_tx_fifo(p)					((p)->regs->FCR_b.TXFIFO_RST	= 1)

#define WORD_LEN_5b		0
#define WORD_LEN_6b		1
#define WORD_LEN_7b		2
#define WORD_LEN_8b		3
#define STOP_BIT_1b		0
#define STOP_BIT_2b		1

#define WORD_LEN_TO_BITS(n)		((n)+5)
#define WORD_LEN_FROM_BITS(n)	((n)-5)

#define STOP_BIT_TO_BITS(n)		((n)+1)
#define STOP_BIT_FROM_BITS(n)	((n)-1)

#define uart_get_LCR(p)						((p)->regs->LCR)
#define uart_get_word_len(p)				((p)->regs->LCR_b.WORD_LEN)
#define uart_get_stop_bit(p)				((p)->regs->LCR_b.STOP_BIT)
#define uart_get_parity_en(p)				((p)->regs->LCR_b.PARITY_EN)
#define uart_get_even_parity(p)				((p)->regs->LCR_b.EVEN_PARITY)
#define uart_get_force_parity(p)			((p)->regs->LCR_b.FORCE_PARITY)
#define uart_get_tx_break(p)				((p)->regs->LCR_b.SET_BREAK)
#define uart_get_DLAB(p)					((p)->regs->LCR_b.DLAB)

#define uart_set_LCR(p, v)					((p)->regs->LCR					= (v))
#define uart_set_word_len(p, v)				((p)->regs->LCR_b.WORD_LEN		= (v))
#define uart_set_stop_bit(p, v)				((p)->regs->LCR_b.STOP_BIT		= (v))
#define uart_set_parity_en(p, v)			((p)->regs->LCR_b.PARITY_EN		= (v))
#define uart_set_even_parity(p, v)			((p)->regs->LCR_b.EVEN_PARITY	= (v))
#define uart_set_force_parity(p, v)			((p)->regs->LCR_b.FORCE_PARITY	= (v))
#define uart_set_tx_break(p, v)				((p)->regs->LCR_b.SET_BREAK		= (v))		// if 1, tx will output "all 0"
#define uart_set_DLAB(p, v)					((p)->regs->LCR_b.DLAB			= (v))

#define uart_is_rx_data_rdy(p)				((p)->regs->LSR_b.DATA_RDY)
#define uart_is_rx_fifo_overrun(p)			((p)->regs->LSR_b.OVERRUN_ERR)
#define uart_is_rx_parity_err(p)			((p)->regs->LSR_b.PARITY_ERR)
#define uart_is_rx_framing_err(p)			((p)->regs->LSR_b.FRAMING_ERR)
#define uart_is_rx_break(p)					((p)->regs->LSR_b.BREAK_INT)		// if 1, mean rx data of "all 0" 
#define uart_is_tx_thr_empty(p)				((p)->regs->LSR_b.THR_EMPTY)		// ONLY tx_fifo is empty
#define uart_is_tx_empty(p)					((p)->regs->LSR_b.TX_EMPTY)			// BOTH tx_fifo+tx_stat are empty
#define uart_is_fifo_data_err(p)			((p)->regs->LSR_b.FIFODATA_ERR)

#define uart_is_rx_err(p)					(((p)->regs->LSR & 0x9E) > 0)

#define uart_get_SPR(p)						((p)->regs->SPR)

#define uart_get_rx_rcvd_int(p)				((p)->regs->INT_MAP_b.RX_RECIEVED)
#define uart_get_rx_fifo_to_int(p)			((p)->regs->INT_MAP_b.RX_FIFO_TO)
#define uart_get_tx_low_thrd_int(p)			((p)->regs->INT_MAP_b.TX_L)
#define uart_get_tx_high_thrd_int(p)		((p)->regs->INT_MAP_b.TX_H)
#define uart_get_tx_fifo_empty_int(p)		((p)->regs->INT_MAP_b.TX_EMPTY2)
#define uart_get_rx_fifo_overrun_int(p)		((p)->regs->INT_MAP_b.OVERRUN)
#define uart_get_rx_framing_err_int(p)		((p)->regs->INT_MAP_b.FRAMING)
#define uart_get_rx_break_int(p)			((p)->regs->INT_MAP_b.BREAK)
#define uart_get_rx_parity_err_int(p)		((p)->regs->INT_MAP_b.PARITY)

#define uart_get_rx_fifo_thrd_low(p)		((p)->regs->RTHR_b.RTHR_L)
#define uart_get_rx_fifo_thrd_high(p)		((p)->regs->RTHR_b.RTHR_H)
#define uart_set_rx_fifo_thrd_low(p, v)		((p)->regs->RTHR_b.RTHR_L	= (v))
#define uart_set_rx_fifo_thrd_high(p, v)	((p)->regs->RTHR_b.RTHR_H	= (v))

#define uart_get_tx_fifo_thrd_low(p)		((p)->regs->TTHR_b.TTHR_L)
#define uart_get_tx_fifo_thrd_high(p)		((p)->regs->TTHR_b.TTHR_H)
#define uart_set_tx_fifo_thrd_low(p, v)		((p)->regs->TTHR_b.TTHR_L	= (v))
#define uart_set_tx_fifo_thrd_high(p, v)	((p)->regs->TTHR_b.TTHR_H	= (v))

#define uart_set_tx_fifo_thrd(p, h, l) \
do { \
	uart_set_tx_fifo_thrd_low(p, l); \
	uart_set_tx_fifo_thrd_high(p, h); \
} while (0)

#define uart_set_rx_fifo_thrd(p, h, l) \
do { \
	uart_set_rx_fifo_thrd_low(p, l); \
	uart_set_rx_fifo_thrd_high(p, h); \
} while (0)

#endif	// __DRV_UART_INTERNAL_H__
