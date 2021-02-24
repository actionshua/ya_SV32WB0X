#ifndef _DRV_COMPORT_H_
#define _DRV_COMPORT_H_

#include "drv_uart.h"
#if defined(SUPPORT_PERIPHERAL_HSUART)
#include "hsuart/drv_hsuart.h"
#endif

#include "custom_io_hal.h"
#include "custom_io_chk.h"

typedef void (*COMPORT_ISR) (void);

typedef enum _COMPORT_IE_E {
    COMPORT_RX_DATA_READY_IE         = 0x0,  ///< Receiver Data Ready or Time out Interrupt Enable.
    COMPORT_THR_EMPTY_IE             = 0x1,  ///< Transmitter Holding Register Empty Interrupt Enable.
    COMPORT_RX_LINE_STATUS_IE        = 0x2,  ///< Receiver Line Status Interrupt Enable.
    COMPORT_MODEM_STATUS_IE          = 0x3   ///< Modem Status Interrupt Enable.
} COMPORT_IE_E;

typedef enum _COMPORT_INT_RXFIFO_TRGLVL_E {
    COMPORT_INT_RXFIFO_TRGLVL_1        = 0x0,  ///< Rx FIFO has  1 charcter trigger interrupt
    COMPORT_INT_RXFIFO_TRGLVL_4        = 0x1,  ///< Rx FIFO has  4 charcter trigger interrupt
    COMPORT_INT_RXFIFO_TRGLVL_8        = 0x2,  ///< Rx FIFO has  8 charcter trigger interrupt
    COMPORT_INT_RXFIFO_TRGLVL_14       = 0x3   ///< Rx FIFO has 14 charcter trigger interrupt
} COMPORT_INT_RXFIFO_TRGLVL_E;

typedef enum _COMPORT_WORD_LEN_E {
    COMPORT_WORD_LEN_5                 = 0x0,  ///< Character's Word Length 5 bits.
    COMPORT_WORD_LEN_6                 = 0x1,  ///< Character's Word Length 6 bits.
    COMPORT_WORD_LEN_7                 = 0x2,  ///< Character's Word Length 7 bits.
    COMPORT_WORD_LEN_8                 = 0x3   ///< Character's Word Length 8 bits.
} COMPORT_WORD_LEN_E;

typedef enum _COMPORT_STOP_BIT_E {
    COMPORT_STOP_BIT_1                 = 0x0,  ///< One stop bit will be transmitted.
    COMPORT_STOP_BIT_2                 = 0x1   ///< Two stop bits (1.5 with 5-bit data) will be transmitted.
} COMPORT_STOP_BIT_E;

typedef enum _COMPORT_PARITY_E {
    COMPORT_PARITY_DISABLE             = 0x0,  ///< No parity bit is transmitted nor expected.
    COMPORT_PARITY_ODD                 = 0x1,  ///< The number of bits including the parity bit must be odd.
    COMPORT_PARITY_EVEN                = 0x3,  ///< The number of bits including the parity bit must be even.
    COMPORT_PARITY_FORCED1             = 0x5,  ///< The parity bit is sent as/checked to be 1.
    COMPORT_PARITY_FORCED0             = 0x7   ///< The parity bit is sent as/checked to be 0.
} COMPORT_PARITY_E;

typedef enum _COMPORT_BLOCKING_MODE_E {
    COMPORT_NON_BLOCKING               = 0x0,  ///< Set the UART HAL driver to operate in non-blocking mode.
    COMPORT_BLOCKING                   = 0x1   ///< Set the UART HAL driver to operate in blocking mode.
} COMPORT_BLOCKING_MODE_E;

typedef enum _COMPORT_DRIVER
{
    COMPORT_UART     = 0,   // Use UART for I/O
    COMPORT_HSUART   = 1,   // Use HSUART for I/O
    COMPORT_HSUART1  = 1,   // Use HSUART1 for I/O
    COMPORT_HSUART2  = 2    // Use HSUART2 for I/O
} COMPORT_DRIVER;

//The structure of comport function 
struct st_comport {
    void (*COMPORT_REGISTER_ISR) (COMPORT_IE_E INT_ENABLE, COMPORT_ISR ISR);
    void (*COMPORT_INIT) (void);
    void (*COMPORT_DEINIT) (void);
    int32_t (*COMPORT_SET_FORMAT) (int32_t BaudRate, COMPORT_WORD_LEN_E DataBits, COMPORT_STOP_BIT_E StopBits, COMPORT_PARITY_E Parity);
    int32_t (*COMPORT_WRITE_FIFO) (uint8_t const *Buffer, int32_t NumberOfBytes, COMPORT_BLOCKING_MODE_E BlockingMode);
    int32_t (*COMPORT_READ_FIFO) (uint8_t *Buffer, int32_t NumberOfBytes, COMPORT_BLOCKING_MODE_E BlockingMode);
    void (*COMPORT_SW_RST) (void);
    uint32_t (*COMPORT_GET_LINE_STATUS) (void);
    uint32_t (*COMPORT_IS_RECEIVER_AVAILABLE) (void);
    uint32_t (*COMPORT_IS_TRANSMITTER_IDLE) (void);
    uint32_t (*COMPORT_DIRECT_READ_BYTE) (void);
};

#define DRV_COMPORT_INIT_COMPORT_UART() \
    do { \
        drv_comport_init(COMPORT_UART); \
        (void)PERI_IO_UART0; \
    } while(0)

#define DRV_COMPORT_INIT_COMPORT_HSUART1() \
    do { \
        drv_comport_init(COMPORT_HSUART1); \
        (void)PERI_IO_UART1; \
    } while(0)

#define DRV_COMPORT_INIT_COMPORT_HSUART2() \
    do { \
        drv_comport_init(COMPORT_HSUART2); \
        (void)PERI_IO_UART2; \
    } while(0)

#define DRV_COMPORT_INIT(UART) \
    DRV_COMPORT_INIT_##UART();

void drv_comport_register_isr (COMPORT_IE_E INT_ENABLE, COMPORT_ISR ISR);
void drv_comport_init (COMPORT_DRIVER drv_io);
void drv_comport_deinit (void);
int32_t drv_comport_set_format (int32_t BaudRate, COMPORT_WORD_LEN_E DataBits, COMPORT_STOP_BIT_E StopBits, COMPORT_PARITY_E Parity);
int32_t drv_comport_write_fifo (uint8_t const *Buffer, int32_t NumberOfBytes, COMPORT_BLOCKING_MODE_E BlockingMode);
int32_t drv_comport_read_fifo (uint8_t *Buffer, int32_t NumberOfBytes, COMPORT_BLOCKING_MODE_E BlockingMode);
void drv_comport_sw_rst (void);
uint32_t drv_comport_get_line_status (void);
uint32_t drv_comport_is_receiver_available (void);
uint32_t drv_comport_is_transmitter_idle (void);
uint32_t drv_comport_direct_read_byte(void);

#endif  // #ifndef _DRV_COMPORT_H_
