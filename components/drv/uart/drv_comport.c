#include "drv_comport.h"
#include <soc_types.h>
#include <osal.h>

static struct st_comport *comport_api = NULL;


//uart 
void comport_uart_register_isr (COMPORT_IE_E INT_ENABLE, COMPORT_ISR ISR)
{
    hal_uart_register_isr (INT_ENABLE, ISR);
}
void comport_uart_init (void)
{
    hal_uart_init ();
}
void comport_uart_deinit (void)
{
    hal_uart_deinit ();
}
int32_t comport_uart_set_format (int32_t BaudRate, COMPORT_WORD_LEN_E DataBits, COMPORT_STOP_BIT_E StopBits, COMPORT_PARITY_E Parity)
{
    return (hal_uart_set_format (BaudRate, DataBits, StopBits, Parity));
}
int32_t comport_uart_write_fifo (uint8_t const *Buffer, int32_t NumberOfBytes, COMPORT_BLOCKING_MODE_E BlockingMode)
{
    return (hal_uart_write_fifo (Buffer, NumberOfBytes, BlockingMode));
}
int32_t comport_uart_read_fifo (uint8_t *Buffer, int32_t NumberOfBytes, COMPORT_BLOCKING_MODE_E BlockingMode)
{
    return (hal_uart_read_fifo (Buffer, NumberOfBytes, BlockingMode));
}
void comport_uart_sw_rst (void)
{
    hal_uart_sw_rst ();
}
uint32_t comport_uart_get_line_status (void)
{
    UART_LSR LSR;
    LSR.Reg32 = hal_uart_get_line_status ();

    return (LSR.Reg32);
}
uint32_t comport_uart_is_receiver_available (void)
{
    UART_LSR LSR;
    LSR.Reg32 = hal_uart_get_line_status ();

    return (LSR.Bits.DR);
}
uint32_t comport_uart_is_transmitter_idle (void)
{
    UART_LSR LSR;
    LSR.Reg32 = hal_uart_get_line_status ();

    return (LSR.Bits.TSRE);
}
uint32_t comport_uart_direct_read_byte(void)
{
    return hal_uart_direct_read_byte();
}

#if defined(SUPPORT_PERIPHERAL_HSUART) && (SUPPORT_PERIPHERAL_HSUART==1)
#if ((CHIP_ID == 6020) && (CHIP_SUB_ID != 0))
static HSUART_HW_ID_E sg_select_hsuart;
#if defined(SUPPORT_LOG_RINGBUFFER) && (SUPPORT_LOG_RINGBUFFER == 1)
static uint8_t *sg_rx_buf;
static uint8_t *sg_tx_buf;
#endif
//hsuart
void comport_hsuart_register_isr (COMPORT_IE_E INT_ENABLE, COMPORT_ISR ISR)
{
    hal_hsuart_register_isr_ex (sg_select_hsuart, (HSUART_INTERRUPT_ENABLE_E)INT_ENABLE, (HSUART_ISR)ISR);
}
#if defined(SUPPORT_LOG_RINGBUFFER) && (SUPPORT_LOG_RINGBUFFER == 1)
uint32_t comport_hsuart_dma_direct_read_byte(void)
{
    uint8_t buf = 0;
    hal_hsuart_read_dma_ex(sg_select_hsuart, &buf, 1);
    return buf;
}
void comport_hsuart_dma_register_isr (COMPORT_IE_E INT_ENABLE, COMPORT_ISR ISR)
{
    if (INT_ENABLE == COMPORT_RX_DATA_READY_IE) {
        hal_hsuart_register_isr_ex (sg_select_hsuart, HSUART_INTERRUPT_ENABRXBUFF, (HSUART_ISR)ISR);
    } else {
        // TODO: to check another dma isr behavior.
        hal_hsuart_register_isr_ex (sg_select_hsuart, (HSUART_INTERRUPT_ENABLE_E)INT_ENABLE, (HSUART_ISR)ISR);
    }
}
uint32_t comport_hsuart_dma_get_line_status (void)
{
    HSUART_LSR LSR;
    LSR.Reg32 = hal_hsuart_get_line_status_ex (sg_select_hsuart) | (hal_hsuart_get_dma_rx_length_ex(sg_select_hsuart) > 0);

    return (LSR.Reg32);
}
int32_t comport_hsuart_dma_read_fifo (uint8_t *Buffer, int32_t NumberOfBytes, COMPORT_BLOCKING_MODE_E BlockingMode)
{
    return hal_hsuart_read_dma_ex(sg_select_hsuart, (uint8_t *)Buffer, NumberOfBytes);
}
int32_t comport_hsuart_dma_write_fifo (uint8_t const *Buffer, int32_t NumberOfBytes, COMPORT_BLOCKING_MODE_E BlockingMode)
{
    return hal_hsuart_write_dma_ex(sg_select_hsuart, (uint8_t *)Buffer, NumberOfBytes);
}
uint32_t comport_hsuart_dma_is_receiver_available (void)
{
    return hal_hsuart_get_dma_rx_length_ex(sg_select_hsuart);
}
void comport_hsuart_dma_init (void)
{
    hal_hsuart_init_ex (sg_select_hsuart);
    sg_rx_buf = (uint8_t *)MEM_NO_CACHE(OS_MemAlloc(SUPPORT_LOG_RX_BUF_SIZE));
    sg_tx_buf = (uint8_t *)MEM_NO_CACHE(OS_MemAlloc(SUPPORT_LOG_TX_BUF_SIZE));
    hal_hsuart_enable_dma_ring_buffer_ex(sg_select_hsuart, sg_tx_buf, (unsigned char*)(sg_tx_buf+SUPPORT_LOG_TX_BUF_SIZE-1), sg_rx_buf, (unsigned char*)(sg_rx_buf+SUPPORT_LOG_RX_BUF_SIZE-1));
}
//uint32_t comport_hsuart_dma_is_transmitter_idle (void)
//{
//}
void comport_hsuart_dma_deinit (void)
{
    hal_hsuart_deinit_ex (sg_select_hsuart);
    OS_MemFree(MEM_CACHED(sg_rx_buf));
    OS_MemFree(MEM_CACHED(sg_tx_buf));
    sg_rx_buf = NULL;
    sg_tx_buf = NULL;
}
#endif
void comport_hsuart_init (void)
{
    hal_hsuart_init_ex (sg_select_hsuart);
}
void comport_hsuart_deinit (void)
{
    hal_hsuart_deinit_ex (sg_select_hsuart);
}
int32_t comport_hsuart_set_format (int32_t BaudRate, COMPORT_WORD_LEN_E DataBits, COMPORT_STOP_BIT_E StopBits, COMPORT_PARITY_E Parity)
{
    return (hal_hsuart_set_format_ex (sg_select_hsuart, BaudRate, (HSUART_WLS_E)DataBits, (HSUART_STB_E)StopBits, (HSUART_PARITY_E)Parity));
}
int32_t comport_hsuart_write_fifo (uint8_t const *Buffer, int32_t NumberOfBytes, COMPORT_BLOCKING_MODE_E BlockingMode)
{
    return (hal_hsuart_write_fifo_ex (sg_select_hsuart, Buffer, NumberOfBytes, (HSUART_BLOCKING_MODE_E)BlockingMode));
}
int32_t comport_hsuart_read_fifo (uint8_t *Buffer, int32_t NumberOfBytes, COMPORT_BLOCKING_MODE_E BlockingMode)
{
    return (hal_hsuart_read_fifo_ex (sg_select_hsuart, Buffer, NumberOfBytes, (HSUART_BLOCKING_MODE_E)BlockingMode));
}
void comport_hsuart_sw_rst (void)
{
    hal_hsuart_sw_rst_ex (sg_select_hsuart);
}
uint32_t comport_hsuart_get_line_status (void)
{
    HSUART_LSR LSR;
    LSR.Reg32 = hal_hsuart_get_line_status_ex (sg_select_hsuart);

    return (LSR.Reg32);
}
uint32_t comport_hsuart_is_receiver_available (void)
{
    HSUART_LSR LSR;
    LSR.Reg32 = hal_hsuart_get_line_status_ex (sg_select_hsuart);

    return (LSR.Bits.DR);
}
uint32_t comport_hsuart_is_transmitter_idle (void)
{
    HSUART_LSR LSR;
    LSR.Reg32 = hal_hsuart_get_line_status_ex (sg_select_hsuart);

    return (LSR.Bits.TSRE);
}
uint32_t comport_hsuart_direct_read_byte(void)
{
    return hal_hsuart_direct_read_byte_ex(sg_select_hsuart);
}
#else
//hsuart
void comport_hsuart_register_isr (COMPORT_IE_E INT_ENABLE, COMPORT_ISR ISR)
{
    hal_hsuart_register_isr ((HSUART_INTERRUPT_ENABLE_E)INT_ENABLE, (HSUART_ISR)ISR);
}
void comport_hsuart_init (void)
{
    hal_hsuart_init ();
}
void comport_hsuart_deinit (void)
{
    hal_hsuart_deinit ();
}
int32_t comport_hsuart_set_format (int32_t BaudRate, COMPORT_WORD_LEN_E DataBits, COMPORT_STOP_BIT_E StopBits, COMPORT_PARITY_E Parity)
{
    return (hal_hsuart_set_format (BaudRate, (HSUART_WLS_E)DataBits, (HSUART_STB_E)StopBits, (HSUART_PARITY_E)Parity));
}
int32_t comport_hsuart_write_fifo (uint8_t const *Buffer, int32_t NumberOfBytes, COMPORT_BLOCKING_MODE_E BlockingMode)
{
    return (hal_hsuart_write_fifo (Buffer, NumberOfBytes, (HSUART_BLOCKING_MODE_E)BlockingMode));
}
int32_t comport_hsuart_read_fifo (uint8_t *Buffer, int32_t NumberOfBytes, COMPORT_BLOCKING_MODE_E BlockingMode)
{
    return (hal_hsuart_read_fifo (Buffer, NumberOfBytes, (HSUART_BLOCKING_MODE_E)BlockingMode));
}
void comport_hsuart_sw_rst (void)
{
    hal_hsuart_sw_rst ();
}
uint32_t comport_hsuart_get_line_status (void)
{
    HSUART_LSR LSR;
    LSR.Reg32 = hal_hsuart_get_line_status ();

    return (LSR.Reg32);
}
uint32_t comport_hsuart_is_receiver_available (void)
{
    HSUART_LSR LSR;
    LSR.Reg32 = hal_hsuart_get_line_status ();

    return (LSR.Bits.DR);
}
uint32_t comport_hsuart_is_transmitter_idle (void)
{
    HSUART_LSR LSR;
    LSR.Reg32 = hal_hsuart_get_line_status ();

    return (LSR.Bits.TSRE);
}
uint32_t comport_hsuart_direct_read_byte(void)
{
    return hal_hsuart_direct_read_byte();
}
#endif
#endif

struct st_comport uart_driver =
{
  comport_uart_register_isr,
  comport_uart_init,
  comport_uart_deinit,
  comport_uart_set_format,
  comport_uart_write_fifo,
  comport_uart_read_fifo,
  comport_uart_sw_rst,
  comport_uart_get_line_status,
  comport_uart_is_receiver_available,
  comport_uart_is_transmitter_idle,
  comport_uart_direct_read_byte,
};

#if defined(SUPPORT_PERIPHERAL_HSUART) && (SUPPORT_PERIPHERAL_HSUART==1)
struct st_comport hsuart_driver =
{
  comport_hsuart_register_isr,
  comport_hsuart_init,
  comport_hsuart_deinit,
  comport_hsuart_set_format,
  comport_hsuart_write_fifo,
  comport_hsuart_read_fifo,
  comport_hsuart_sw_rst,
  comport_hsuart_get_line_status,
  comport_hsuart_is_receiver_available,
  comport_hsuart_is_transmitter_idle,
  comport_hsuart_direct_read_byte,
};
#if defined(SUPPORT_LOG_RINGBUFFER) && (SUPPORT_LOG_RINGBUFFER == 1)
struct st_comport hsuart_dma_driver =
{
  comport_hsuart_dma_register_isr,
  comport_hsuart_dma_init,
  comport_hsuart_dma_deinit,
  comport_hsuart_set_format,
  comport_hsuart_dma_write_fifo,
  comport_hsuart_dma_read_fifo,
  comport_hsuart_sw_rst,
  comport_hsuart_dma_get_line_status,
  comport_hsuart_dma_is_receiver_available,
  comport_hsuart_is_transmitter_idle,
  comport_hsuart_dma_direct_read_byte,
};
#endif
#endif

void drv_comport_register_isr (COMPORT_IE_E INT_ENABLE, COMPORT_ISR ISR)
{   
    if( comport_api )
        comport_api->COMPORT_REGISTER_ISR( INT_ENABLE,  ISR);
}

void drv_comport_init (COMPORT_DRIVER drv_io)
{ 
    if( comport_api )
    {
        comport_api->COMPORT_DEINIT();
    }
    
    if( drv_io == COMPORT_UART )
        comport_api = &uart_driver;
#if defined(SUPPORT_PERIPHERAL_HSUART) && (SUPPORT_PERIPHERAL_HSUART==1)
#if ((CHIP_ID == 6020) && (CHIP_SUB_ID != 0))
#if defined(SUPPORT_LOG_RINGBUFFER) && (SUPPORT_LOG_RINGBUFFER == 1)
    else if( drv_io == COMPORT_HSUART ) {
        comport_api = &hsuart_dma_driver;
        sg_select_hsuart = HSUART_1;
    }
    else if( drv_io == COMPORT_HSUART2 ) {
        comport_api = &hsuart_dma_driver;
        sg_select_hsuart = HSUART_2;
    }
#else
    else if( drv_io == COMPORT_HSUART ) {
        comport_api = &hsuart_driver;
        sg_select_hsuart = HSUART_1;
    }
    else if( drv_io == COMPORT_HSUART2 ) {
        comport_api = &hsuart_driver;
        sg_select_hsuart = HSUART_2;
    }
#endif
#else
    else if( drv_io == COMPORT_HSUART )
        comport_api = &hsuart_driver;
#endif
#endif
    else
        comport_api = NULL;

    
    if( comport_api )
    {
        comport_api->COMPORT_SW_RST();
        comport_api->COMPORT_INIT();
    }
}

void drv_comport_deinit (void)
{
    if( comport_api )
        comport_api->COMPORT_DEINIT();
}

int32_t drv_comport_set_format (int32_t BaudRate, COMPORT_WORD_LEN_E DataBits, COMPORT_STOP_BIT_E StopBits, COMPORT_PARITY_E Parity)
{
    if( comport_api )
        return comport_api->COMPORT_SET_FORMAT(BaudRate, DataBits, StopBits, Parity);
    else
        return -1;
        
}

int32_t drv_comport_write_fifo (uint8_t const *Buffer, int32_t NumberOfBytes, COMPORT_BLOCKING_MODE_E BlockingMode)
{
    if( comport_api )
        return comport_api->COMPORT_WRITE_FIFO(Buffer, NumberOfBytes, BlockingMode);
    else
        return -1;
}

int32_t drv_comport_read_fifo (uint8_t *Buffer, int32_t NumberOfBytes, COMPORT_BLOCKING_MODE_E BlockingMode)
{
    if( comport_api )
        return comport_api->COMPORT_READ_FIFO(Buffer, NumberOfBytes, BlockingMode);
    else
        return -1;
    
}

void drv_comport_sw_rst (void)
{
    if( comport_api )
        comport_api->COMPORT_SW_RST();
}

uint32_t drv_comport_get_line_status (void)
{
    if( comport_api )
        return comport_api->COMPORT_GET_LINE_STATUS();
    else
        return -1;
    
}

uint32_t drv_comport_is_receiver_available (void)
{
    if( comport_api )
        return comport_api->COMPORT_IS_RECEIVER_AVAILABLE();
    else
        return -1;
}

uint32_t drv_comport_is_transmitter_idle (void)
{
    if( comport_api )
        return comport_api->COMPORT_IS_TRANSMITTER_IDLE();
    else
        return -1;
}

uint32_t drv_comport_direct_read_byte(void)
{
    if( comport_api )
        return comport_api->COMPORT_DIRECT_READ_BYTE();
    else
        return -1;
}
