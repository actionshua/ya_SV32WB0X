
#include <stdio.h>
#include <string.h>
#include "soc_types.h"
#include "soc_defs.h"
#include "osal.h"
#include <attrs.h>

#include "cli.h"
#include "error.h"

#include "hsuart/drv_hsuart.h"

static OsTaskHandle sg_loop_task = NULL;

static void hsuart_isr ()
{
    uint8_t Buffer[32] = {0};
    int32_t retval;

    retval = drv_hsuart_read_fifo_ex (HSUART_1, Buffer, 32, HSUART_NON_BLOCKING);
    retval = drv_hsuart_write_fifo_ex (HSUART_1, Buffer, retval, HSUART_BLOCKING);
    printf ("received length: %ld\n", retval);
    printf ("\n");
}

int interrupt (int32_t argc, char *argv[])
{
    int32_t         BaudRate;
    HSUART_WLS_E    DataBits;
    HSUART_STB_E    StopBits;
    HSUART_PARITY_E Parity;

    int32_t         retval;

    if (argc == 5) {
        BaudRate    = strtol (argv[1], NULL, 10);
        DataBits    = strtol (argv[2], NULL, 10);
        StopBits    = strtol (argv[3], NULL, 10);
        Parity      = strtol (argv[4], NULL, 10);

    } else {
        printf ("\nUsage: int [BaudRate] [DataBits] [StopBits] [Parity]\n");
        printf ("Options:\n");
        printf ("BaudRate               The baud rate of the High Speed UART.\n");
        printf ("                       Contains at least the [1, 5000000] range\n");
        printf ("DataBits               The number of data bits in each character.\n");
        printf ("                       0: Character's Word Length 5 bits\n");
        printf ("                       1: Character's Word Length 6 bits\n");
        printf ("                       2: Character's Word Length 7 bits\n");
        printf ("                       3: Character's Word Length 8 bits\n");
        printf ("StopBits               The number of stop bits per character.\n");
        printf ("                       0: One stop bit will be transmitted\n");
        printf ("                       1: Two stop bits (1.5 with 5-bit data) will be transmitted\n");
        printf ("Parity                 That is computed or checked as each character is transmitted or received.\n");
        printf ("                       0: No parity bit is transmitted nor expected\n");
        printf ("                       1: The number of bits including the parity bit must be odd\n");
        printf ("                       3: The number of bits including the parity bit must be even\n");
        printf ("                       5: The parity bit is sent as/checked to be 1\n");
        printf ("                       7: The parity bit is sent as/checked to be 0\n");

        return -1;
    }

    if (((BaudRate < 1) || (BaudRate > 5000000)) ||
        ((DataBits < 0) || (DataBits > 3)) ||
        ((StopBits < 0) || (StopBits > 1)) ||
        ((Parity < 0) || (Parity == 2) || (Parity == 4) || (Parity == 6) || (Parity > 7))) {
        printf ("\nUsage: int [BaudRate] [DataBits] [StopBits] [Parity]\n");
        printf ("Options:\n");
        printf ("BaudRate               The baud rate of the High Speed UART.\n");
        printf ("                       Contains at least the [1, 5000000] range\n");
        printf ("DataBits               The number of data bits in each character.\n");
        printf ("                       0: Character's Word Length 5 bits\n");
        printf ("                       1: Character's Word Length 6 bits\n");
        printf ("                       2: Character's Word Length 7 bits\n");
        printf ("                       3: Character's Word Length 8 bits\n");
        printf ("StopBits               The number of stop bits per character.\n");
        printf ("                       0: One stop bit will be transmitted\n");
        printf ("                       1: Two stop bits (1.5 with 5-bit data) will be transmitted\n");
        printf ("Parity                 That is computed or checked as each character is transmitted or received.\n");
        printf ("                       0: No parity bit is transmitted nor expected\n");
        printf ("                       1: The number of bits including the parity bit must be odd\n");
        printf ("                       3: The number of bits including the parity bit must be even\n");
        printf ("                       5: The parity bit is sent as/checked to be 1\n");
        printf ("                       7: The parity bit is sent as/checked to be 0\n");

        return -1;
    }

    printf("hsuart receiver data ready interrupt test program (Build: %s %s)\n", __DATE__, __TIME__);

    drv_hsuart_sw_rst_ex (HSUART_1);
    drv_hsuart_init_ex (HSUART_1);
    drv_hsuart_set_fifo_ex (HSUART_1, HSUART_INT_RX_FIFO_TRIG_LV_16);

    // !!!! TODO: if hsuart CTS/RTS setup to GPIO, please not to setup hardware flow control. !!!!
    //drv_hsuart_set_hardware_flow_control (16, 24);
    retval = drv_hsuart_set_format_ex (HSUART_1, BaudRate, DataBits, StopBits, Parity);
    drv_hsuart_register_isr_ex (HSUART_1, HSUART_RX_DATA_READY_IE, hsuart_isr);

    printf ("hsuart wait for receiver data ready interrupt event...\n");

    return 0;
}

void loopback_task() {
    uint8_t         Buffer = 0;
    int retval;
    while (1) {
        if (drv_hsuart_read_fifo_ex (HSUART_1, &Buffer, 1, HSUART_NON_BLOCKING) <= 0) {
            OS_MsDelay(10);
        } else {
            retval = drv_hsuart_write_fifo_ex (HSUART_1, &Buffer, 1, HSUART_BLOCKING);
        }
    }
}

int loopback_exit (int32_t argc, char *argv[])
{
    if (sg_loop_task) {
        OS_TaskDelete(sg_loop_task);
        sg_loop_task = NULL;
    }
    return 0;
}

int loopback (int32_t argc, char *argv[])
{
    int32_t         BaudRate;
    HSUART_WLS_E    DataBits;
    HSUART_STB_E    StopBits;
    HSUART_PARITY_E Parity;

    int32_t         retval;
    uint8_t         Buffer = 0;

    if (argc == 5) {
        BaudRate    = strtol (argv[1], NULL, 10);
        DataBits    = strtol (argv[2], NULL, 10);
        StopBits    = strtol (argv[3], NULL, 10);
        Parity      = strtol (argv[4], NULL, 10);

    } else {
        printf ("\nUsage: loopback [BaudRate] [DataBits] [StopBits] [Parity]\n");
        printf ("Options:\n");
        printf ("BaudRate               The baud rate of the High Speed UART.\n");
        printf ("                       Contains at least the [1, 5000000] range\n");
        printf ("DataBits               The number of data bits in each character.\n");
        printf ("                       0: Character's Word Length 5 bits\n");
        printf ("                       1: Character's Word Length 6 bits\n");
        printf ("                       2: Character's Word Length 7 bits\n");
        printf ("                       3: Character's Word Length 8 bits\n");
        printf ("StopBits               The number of stop bits per character.\n");
        printf ("                       0: One stop bit will be transmitted\n");
        printf ("                       1: Two stop bits (1.5 with 5-bit data) will be transmitted\n");
        printf ("Parity                 That is computed or checked as each character is transmitted or received.\n");
        printf ("                       0: No parity bit is transmitted nor expected\n");
        printf ("                       1: The number of bits including the parity bit must be odd\n");
        printf ("                       3: The number of bits including the parity bit must be even\n");
        printf ("                       5: The parity bit is sent as/checked to be 1\n");
        printf ("                       7: The parity bit is sent as/checked to be 0\n");

        return -1;
    }

    if (((BaudRate < 1) || (BaudRate > 5000000)) ||
        ((DataBits < 0) || (DataBits > 3)) ||
        ((StopBits < 0) || (StopBits > 1)) ||
        ((Parity < 0) || (Parity == 2) || (Parity == 4) || (Parity == 6) || (Parity > 7))) {
        printf ("\nUsage: loopback [BaudRate] [DataBits] [StopBits] [Parity]\n");
        printf ("Options:\n");
        printf ("BaudRate               The baud rate of the High Speed UART.\n");
        printf ("                       Contains at least the [1, 5000000] range\n");
        printf ("DataBits               The number of data bits in each character.\n");
        printf ("                       0: Character's Word Length 5 bits\n");
        printf ("                       1: Character's Word Length 6 bits\n");
        printf ("                       2: Character's Word Length 7 bits\n");
        printf ("                       3: Character's Word Length 8 bits\n");
        printf ("StopBits               The number of stop bits per character.\n");
        printf ("                       0: One stop bit will be transmitted\n");
        printf ("                       1: Two stop bits (1.5 with 5-bit data) will be transmitted\n");
        printf ("Parity                 That is computed or checked as each character is transmitted or received.\n");
        printf ("                       0: No parity bit is transmitted nor expected\n");
        printf ("                       1: The number of bits including the parity bit must be odd\n");
        printf ("                       3: The number of bits including the parity bit must be even\n");
        printf ("                       5: The parity bit is sent as/checked to be 1\n");
        printf ("                       7: The parity bit is sent as/checked to be 0\n");

        return -1;
    }

    printf ("hsuart loopback test program (Build: %s %s)\n", __DATE__, __TIME__);

    drv_hsuart_sw_rst_ex (HSUART_1);
    drv_hsuart_init_ex (HSUART_1);
    drv_hsuart_set_fifo_ex (HSUART_1, HSUART_INT_RX_FIFO_TRIG_LV_16);

    // !!!! TODO: if hsuart CTS/RTS setup to GPIO, please not to setup hardware flow control. !!!!
    //drv_hsuart_set_hardware_flow_control (16, 24);
    retval = drv_hsuart_set_format_ex (HSUART_1, BaudRate, DataBits, StopBits, Parity);

    if (sg_loop_task) {
        return 0;
    } else {
        if (1 != OS_TaskCreate(loopback_task, "hsuart_loop", 128, NULL, OS_TASK_LOW_PRIO, &sg_loop_task)) {
            printf("task some error!!!\n");
            if (sg_loop_task) {
                OS_TaskDelete(sg_loop_task);
                sg_loop_task = NULL;
            }
        }
    }

    return 0;
}

// TX size can different to RX size.
#define HSUART_DMA_TX_SIZE         (256)
#define HSUART_DMA_RX_SIZE         (2048)

void hsuart_line_error() ATTRIBUTE_SECTION_HSUART_ISR;
void hsuart_line_error() {
    uint32_t line_status =  drv_hsuart_get_line_status_ex (HSUART_1);
    printf("[%s] !!! line status %x error\n", __func__, line_status);
}

void hsuart_modem_status() ATTRIBUTE_SECTION_HSUART_ISR;
void hsuart_modem_status() {
    printf("[%s] !!! model status\n", __func__);
}

void hsuart_tx_dma_done() ATTRIBUTE_SECTION_HSUART_ISR;
void hsuart_tx_dma_done() {
    printf("[%s] !!! tx dma done\n", __func__);
    drv_hsuart_register_isr_ex (HSUART_1, HSUART_ENABDMATXEND, NULL);
}

void hsuart_dma_data_ready_api() ATTRIBUTE_SECTION_HSUART_ISR;
void hsuart_dma_data_ready_api() {
    static uint8_t hsuart_buffer[HSUART_DMA_RX_SIZE];
    int rx_size = drv_hsuart_read_dma_ex(HSUART_1, (uint8_t *)hsuart_buffer, HSUART_DMA_RX_SIZE);

    int wrote = drv_hsuart_write_dma_ex(HSUART_1, (uint8_t *)hsuart_buffer, rx_size);
    if (rx_size != wrote) {
        printf("actually write to dma %d bytes\n", wrote);
    }

    // You can register a Tx empty the check the data send finish.
    // this is not necessary.
    drv_hsuart_register_isr_ex (HSUART_1, HSUART_ENABDMATXEND, hsuart_tx_dma_done);
}

int dma_isr (int32_t argc, char *argv[])
{
    int32_t         BaudRate;
    HSUART_WLS_E    DataBits;
    HSUART_STB_E    StopBits;
    HSUART_PARITY_E Parity;

    int32_t         retval;

    if (argc == 5) {
        BaudRate    = strtol (argv[1], NULL, 10);
        DataBits    = strtol (argv[2], NULL, 10);
        StopBits    = strtol (argv[3], NULL, 10);
        Parity      = strtol (argv[4], NULL, 10);

    } else {
        printf ("\nUsage: dma [BaudRate] [DataBits] [StopBits] [Parity]\n");
        printf ("Options:\n");
        printf ("BaudRate               The baud rate of the High Speed UART.\n");
        printf ("                       Contains at least the [1, 5000000] range\n");
        printf ("DataBits               The number of data bits in each character.\n");
        printf ("                       0: Character's Word Length 5 bits\n");
        printf ("                       1: Character's Word Length 6 bits\n");
        printf ("                       2: Character's Word Length 7 bits\n");
        printf ("                       3: Character's Word Length 8 bits\n");
        printf ("StopBits               The number of stop bits per character.\n");
        printf ("                       0: One stop bit will be transmitted\n");
        printf ("                       1: Two stop bits (1.5 with 5-bit data) will be transmitted\n");
        printf ("Parity                 That is computed or checked as each character is transmitted or received.\n");
        printf ("                       0: No parity bit is transmitted nor expected\n");
        printf ("                       1: The number of bits including the parity bit must be odd\n");
        printf ("                       3: The number of bits including the parity bit must be even\n");
        printf ("                       5: The parity bit is sent as/checked to be 1\n");
        printf ("                       7: The parity bit is sent as/checked to be 0\n");

        return -1;
    }

    if (((BaudRate < 1) || (BaudRate > 5000000)) ||
        ((DataBits < 0) || (DataBits > 3)) ||
        ((StopBits < 0) || (StopBits > 1)) ||
        ((Parity < 0) || (Parity == 2) || (Parity == 4) || (Parity == 6) || (Parity > 7))) {
        printf ("\nUsage: int [BaudRate] [DataBits] [StopBits] [Parity]\n");
        printf ("Options:\n");
        printf ("BaudRate               The baud rate of the High Speed UART.\n");
        printf ("                       Contains at least the [1, 5000000] range\n");
        printf ("DataBits               The number of data bits in each character.\n");
        printf ("                       0: Character's Word Length 5 bits\n");
        printf ("                       1: Character's Word Length 6 bits\n");
        printf ("                       2: Character's Word Length 7 bits\n");
        printf ("                       3: Character's Word Length 8 bits\n");
        printf ("StopBits               The number of stop bits per character.\n");
        printf ("                       0: One stop bit will be transmitted\n");
        printf ("                       1: Two stop bits (1.5 with 5-bit data) will be transmitted\n");
        printf ("Parity                 That is computed or checked as each character is transmitted or received.\n");
        printf ("                       0: No parity bit is transmitted nor expected\n");
        printf ("                       1: The number of bits including the parity bit must be odd\n");
        printf ("                       3: The number of bits including the parity bit must be even\n");
        printf ("                       5: The parity bit is sent as/checked to be 1\n");
        printf ("                       7: The parity bit is sent as/checked to be 0\n");

        return -1;
    }

    printf("hsuart receiver data ready interrupt test program (Build: %s %s)\n", __DATE__, __TIME__);

    drv_hsuart_sw_rst_ex (HSUART_1);
    drv_hsuart_init_ex (HSUART_1);
    retval = drv_hsuart_set_format_ex (HSUART_1, BaudRate, DataBits, StopBits, Parity);
    static uint8_t hsuart_dma_memory_rx[HSUART_DMA_RX_SIZE];
    static uint8_t hsuart_dma_memory_tx[HSUART_DMA_TX_SIZE];

    drv_hsuart_enable_dma_ring_buffer_ex(HSUART_1, hsuart_dma_memory_tx, hsuart_dma_memory_tx+HSUART_DMA_TX_SIZE-1, hsuart_dma_memory_rx, hsuart_dma_memory_rx+HSUART_DMA_RX_SIZE-1);
    drv_hsuart_register_isr_ex (HSUART_1, HSUART_INTERRUPT_ENABRXBUFF, hsuart_dma_data_ready_api);
    drv_hsuart_register_isr_ex (HSUART_1, HSUART_INTERRUPT_ENABLNSTAT, hsuart_line_error);
    drv_hsuart_register_isr_ex (HSUART_1, HSUART_INTERRUPT_ENABMDSTAT, hsuart_modem_status);

    printf ("hsuart dma wait for receiver data ready interrupt event...\n");

    return 0;
}


int help (int32_t argc, char *argv[])
{
    printf ("Usage: loopback [BaudRate] [DataBits] [StopBits] [Parity]\n");
    printf ("Options:\n");
    printf ("BaudRate               The baud rate of the High Speed UART.\n");
    printf ("                       Contains at least the [1, 5000000] range\n");
    printf ("DataBits               The number of data bits in each character.\n");
    printf ("                       0: Character's Word Length 5 bits\n");
    printf ("                       1: Character's Word Length 6 bits\n");
    printf ("                       2: Character's Word Length 7 bits\n");
    printf ("                       3: Character's Word Length 8 bits\n");
    printf ("StopBits               The number of stop bits per character.\n");
    printf ("                       0: One stop bit will be transmitted\n");
    printf ("                       1: Two stop bits (1.5 with 5-bit data) will be transmitted\n");
    printf ("Parity                 That is computed or checked as each character is transmitted or received.\n");
    printf ("                       0: No parity bit is transmitted nor expected\n");
    printf ("                       1: The number of bits including the parity bit must be odd\n");
    printf ("                       3: The number of bits including the parity bit must be even\n");
    printf ("                       5: The parity bit is sent as/checked to be 1\n");
    printf ("                       7: The parity bit is sent as/checked to be 0\n");
    printf ("\n");

    printf ("Usage: int [BaudRate] [DataBits] [StopBits] [Parity]\n");
    printf ("Options:\n");
    printf ("BaudRate               The baud rate of the High Speed UART.\n");
    printf ("                       Contains at least the [1, 5000000] range\n");
    printf ("DataBits               The number of data bits in each character.\n");
    printf ("                       0: Character's Word Length 5 bits\n");
    printf ("                       1: Character's Word Length 6 bits\n");
    printf ("                       2: Character's Word Length 7 bits\n");
    printf ("                       3: Character's Word Length 8 bits\n");
    printf ("StopBits               The number of stop bits per character.\n");
    printf ("                       0: One stop bit will be transmitted\n");
    printf ("                       1: Two stop bits (1.5 with 5-bit data) will be transmitted\n");
    printf ("Parity                 That is computed or checked as each character is transmitted or received.\n");
    printf ("                       0: No parity bit is transmitted nor expected\n");
    printf ("                       1: The number of bits including the parity bit must be odd\n");
    printf ("                       3: The number of bits including the parity bit must be even\n");
    printf ("                       5: The parity bit is sent as/checked to be 1\n");
    printf ("                       7: The parity bit is sent as/checked to be 0\n");
    printf ("\n");

    return 0;
}

/* ---------------------- Registered CMDs to CMD Table ---------------------- */
const CLICmds gCustomCmdTable[] =
{
    {"help",            help,               "hsuart help"},
    {"loopback",        loopback,           "hsuart loopback test"},
    {"loopback_exit",   loopback_exit,      "hsuart exit loopback test"},
    {"int",             interrupt,          "hsuart interrupt test"},
    {"dma",             dma_isr,            "hsuart dma test"},
    
    { (const char *)NULL, (CliCmdFunc)NULL,   (const char *)NULL },
};


