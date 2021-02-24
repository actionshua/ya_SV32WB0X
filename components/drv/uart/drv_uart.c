#include "drv_uart.h"

void drv_uart_register_isr (UART_IE_E INT_ENABLE, UART_ISR ISR)
{
    hal_uart_register_isr (INT_ENABLE, ISR);
}

void drv_uart_init (void)
{
    hal_uart_init ();
}

void drv_uart_deinit (void)
{
    hal_uart_deinit ();
}

int32_t drv_uart_set_format (int32_t BaudRate, UART_WORD_LEN_E DataBits, UART_STOP_BIT_E StopBits, UART_PARITY_E Parity)
{
    return (hal_uart_set_format (BaudRate, DataBits, StopBits, Parity));
}

void drv_uart_set_fifo (UART_INT_RXFIFO_TRGLVL_E INT_RXFIFO_TRIGGER_LEVEL, uint8_t INT_TXFIFO_THRESHOLD_LOW)
{
    hal_uart_set_fifo (INT_RXFIFO_TRIGGER_LEVEL, INT_TXFIFO_THRESHOLD_LOW, 0xC);
}

int32_t drv_uart_write_fifo (uint8_t const *Buffer, int32_t NumberOfBytes, UART_BLOCKING_MODE_E BlockingMode)
{
    return (hal_uart_write_fifo (Buffer, NumberOfBytes, BlockingMode));
}

int32_t drv_uart_read_fifo (uint8_t *Buffer, int32_t NumberOfBytes, UART_BLOCKING_MODE_E BlockingMode)
{
    return (hal_uart_read_fifo (Buffer, NumberOfBytes, BlockingMode));
}

void drv_uart_sw_rst (void)
{
    hal_uart_sw_rst ();
}

uint32_t drv_uart_get_line_status (void)
{
    UART_LSR LSR;
    LSR.Reg32 = hal_uart_get_line_status ();

    return (LSR.Reg32);
}

uint32_t drv_uart_is_receiver_available (void)
{
    UART_LSR LSR;
    LSR.Reg32 = hal_uart_get_line_status ();

    return (LSR.Bits.DR);
}

uint32_t drv_uart_is_transmitter_idle (void)
{
    UART_LSR LSR;
    LSR.Reg32 = hal_uart_get_line_status ();

    return (LSR.Bits.TSRE);
}
