
#include "drv_hsuart.h"
#include <soc_types.h>

void drv_hsuart_register_isr (HSUART_IE_E INT_ENABLE, HSUART_ISR ISR)
{
    hal_hsuart_register_isr (INT_ENABLE, ISR);
}

void drv_hsuart_init (void)
{
    hal_hsuart_init ();
}
void drv_hsuart_deinit (void)
{
    hal_hsuart_deinit ();
}


int32_t drv_hsuart_set_format (int32_t BaudRate, HSUART_WLS_E DataBits, HSUART_STB_E StopBits, HSUART_PARITY_E Parity)
{
    return (hal_hsuart_set_format (BaudRate, DataBits, StopBits, Parity));
}

void drv_hsuart_set_fifo (HSUART_INT_RX_FIFO_TRIG_LV_E INT_RX_FIFO_TRIGGER_LEVEL)
{
    hal_hsuart_set_fifo (INT_RX_FIFO_TRIGGER_LEVEL);
}

void drv_hsuart_set_hardware_flow_control (uint8_t AutoRtsThresholdLow, uint8_t AutoRtsThresholdHigh)
{
    hal_hsuart_set_hardware_flow_control (AutoRtsThresholdLow, AutoRtsThresholdHigh);
}

int32_t drv_hsuart_write_fifo (uint8_t const *Buffer, int32_t NumberOfBytes, HSUART_BLOCKING_MODE_E BlockingMode)
{
    return (hal_hsuart_write_fifo (Buffer, NumberOfBytes, BlockingMode));
}

int32_t drv_hsuart_read_fifo (uint8_t *Buffer, int32_t NumberOfBytes, HSUART_BLOCKING_MODE_E BlockingMode)
{
    return (hal_hsuart_read_fifo (Buffer, NumberOfBytes, BlockingMode));
}

void drv_hsuart_sw_rst (void)
{
    hal_hsuart_sw_rst ();
}

uint32_t drv_hsuart_get_line_status (void)
{
    HSUART_LSR LSR;
    LSR.Reg32 = hal_hsuart_get_line_status ();

    return (LSR.Reg32);
}

uint32_t drv_hsuart_is_receiver_available (void)
{
    HSUART_LSR LSR;
    LSR.Reg32 = hal_hsuart_get_line_status ();

    return (LSR.Bits.DR);
}

uint32_t drv_hsuart_is_transmitter_idle (void)
{
    HSUART_LSR LSR;
    LSR.Reg32 = hal_hsuart_get_line_status ();

    return (LSR.Bits.TSRE);
}

uint32_t drv_hsuart_get_modem_status (void)
{
    HSUART_MSR MSR;
    MSR.Reg32 = hal_hsuart_get_modem_status ();

    return (MSR.Reg32);
}
/////////////////////////////////////////////////////////////
void drv_hsuart_set_fifo_ex (HSUART_HW_ID_E hw, HSUART_INT_RX_FIFO_TRIG_LV_E INT_RX_FIFO_TRIGGER_LEVEL)
{
    hal_hsuart_set_fifo_ex (hw, INT_RX_FIFO_TRIGGER_LEVEL);
}
int32_t drv_hsuart_set_format_ex (HSUART_HW_ID_E hw, int32_t BaudRate, HSUART_WLS_E DataBits, HSUART_STB_E StopBits, HSUART_PARITY_E Parity)
{
    return (hal_hsuart_set_format_ex (hw, BaudRate, DataBits, StopBits, Parity));
}
void drv_hsuart_deinit_ex (HSUART_HW_ID_E hw)
{
    hal_hsuart_deinit_ex (hw);
}

void drv_hsuart_init_ex (HSUART_HW_ID_E hw)
{
    hal_hsuart_init_ex (hw);
}
void drv_hsuart_register_isr_ex  (HSUART_HW_ID_E hw, HSUART_IE_E INT_ENABLE, HSUART_ISR ISR)
{
    hal_hsuart_register_isr_ex (hw, INT_ENABLE, ISR);
}
void drv_hsuart_set_hardware_flow_control_ex (HSUART_HW_ID_E hw, uint8_t AutoRtsThresholdLow, uint8_t AutoRtsThresholdHigh)
{
    hal_hsuart_set_hardware_flow_control_ex (hw, AutoRtsThresholdLow, AutoRtsThresholdHigh);
}

int32_t drv_hsuart_write_fifo_ex (HSUART_HW_ID_E hw, uint8_t const *Buffer, int32_t NumberOfBytes, HSUART_BLOCKING_MODE_E BlockingMode)
{
    return (hal_hsuart_write_fifo_ex (hw, Buffer, NumberOfBytes, BlockingMode));
}

int32_t drv_hsuart_read_fifo_ex (HSUART_HW_ID_E hw, uint8_t *Buffer, int32_t NumberOfBytes, HSUART_BLOCKING_MODE_E BlockingMode)
{
    return (hal_hsuart_read_fifo_ex (hw, Buffer, NumberOfBytes, BlockingMode));
}

void drv_hsuart_sw_rst_ex (HSUART_HW_ID_E hw)
{
    hal_hsuart_sw_rst_ex (hw);
}

uint32_t drv_hsuart_get_line_status_ex (HSUART_HW_ID_E hw)
{
    HSUART_LSR LSR;
    LSR.Reg32 = hal_hsuart_get_line_status_ex (hw);

    return (LSR.Reg32);
}

uint32_t drv_hsuart_is_receiver_available_ex (HSUART_HW_ID_E hw)
{
    HSUART_LSR LSR;
    LSR.Reg32 = hal_hsuart_get_line_status_ex (hw);

    return (LSR.Bits.DR);
}

uint32_t drv_hsuart_is_transmitter_idle_ex (HSUART_HW_ID_E hw)
{
    HSUART_LSR LSR;
    LSR.Reg32 = hal_hsuart_get_line_status_ex (hw);

    return (LSR.Bits.TSRE);
}

uint32_t drv_hsuart_get_modem_status_ex (HSUART_HW_ID_E hw)
{
    HSUART_MSR MSR;
    MSR.Reg32 = hal_hsuart_get_modem_status_ex (hw);

    return (MSR.Reg32);
}

int32_t drv_hsuart_write_dma_ex (HSUART_HW_ID_E hw, uint8_t *buf, int32_t buf_size)
{
    return hal_hsuart_write_dma_ex(hw, buf, buf_size);
}

int32_t drv_hsuart_read_dma_ex (HSUART_HW_ID_E hw, uint8_t *buf, int32_t buf_size)
{
    return hal_hsuart_read_dma_ex(hw, buf, buf_size);
}

void drv_hsuart_enable_dma_ring_buffer_ex (HSUART_HW_ID_E hw, uint8_t *DMA_TX_STR_ADDR, uint8_t *DMA_TX_END_ADDR, uint8_t *DMA_RX_STR_ADDR, uint8_t *DMA_RX_END_ADDR)
{
    // hardware buffer!!!!
    // should be non-cacheable.
    hal_hsuart_enable_dma_ring_buffer_ex (hw, MEM_NO_CACHE(DMA_TX_STR_ADDR), MEM_NO_CACHE(DMA_TX_END_ADDR), MEM_NO_CACHE(DMA_RX_STR_ADDR), MEM_NO_CACHE(DMA_RX_END_ADDR));
}

