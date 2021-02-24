
#include <stdio.h>
#include <string.h>
#include "soc_types.h"
#include "soc_defs.h"
#include "osal.h"

#include "cli.h"
#include "error.h"

#include "spislv/drv_spislv.h"


#define SPI_RAW_DATA_GOIO_INT       (8)

/*---------------------------------- CMDs -----------------------------------*/
#define S_SPI_MAX_SIZE          (1024)
static uint8_t write_buf[S_SPI_MAX_SIZE];
static uint8_t read_buf[S_SPI_MAX_SIZE];
OsEvent g_spi_raw_rx_sem;

void irq_hal_spi_raw_handler (uint32_t irq_num) {
    drv_spi_slv_error_reduce();
    OS_EventSet(g_spi_raw_rx_sem);
}

void spi_raw_data_task(void *param) {

    while(1) {
        if (OS_EventWait(g_spi_raw_rx_sem, portMAX_DELAY) == OS_SUCCESS) {
            int ret;

            ret = drv_spi_slv_read_data(S_SPI_MAX_SIZE, read_buf);
            memcpy(write_buf, read_buf, S_SPI_MAX_SIZE);

            // places write data into the buffer for next transmission.
            ret = drv_spi_slv_write_data(S_SPI_MAX_SIZE, write_buf);
            ret = drv_spi_slv_set_data_ready();
        }
    }
}

int test_spi_raw_slave(int32_t argc, char *argv[]) {    
    uint8_t ret = 0x0; 
    
    uint8_t i = 0;
    uint32_t data_length = S_SPI_MAX_SIZE;
	uint32_t slave_inturrupt = 0;
	
	slave_inturrupt = strtoul(argv[0], NULL, 10);
	printf("<%s>%d gpio_inturrupt = %d\n",__func__,__LINE__, slave_inturrupt);
	printf("<%s>%d test_spi_slave start!!\n");
    for(i = 0; i < data_length; i ++) {
        write_buf[i] = (i % 0x100);
        read_buf[i] = 0;
    }
    
    // enable spi slave.
    ret = drv_spi_slv_enable();
    // set gpio_08 to be slave interrupt.    
    // when host trx done will execute irq_hal_spi_slv_handler function.
    ret = drv_spi_slv_init(0x08, 1, irq_hal_spi_raw_handler);
    // places write data into the buffer for transmission.
    ret = drv_spi_slv_write_data(S_SPI_MAX_SIZE, write_buf);
    // set spi slave ready for transmission status.
    ret = drv_spi_slv_set_data_ready();

    OsTaskHandle spi_task_handler;
    
    OS_EventCreate(&g_spi_raw_rx_sem);
    
    if (!OS_TaskCreate(spi_raw_data_task, "spi_raw", 128, NULL, 3, &spi_task_handler)) {
        printf("[%s] create spi raw task failed.\n", __func__);
        return -1;
    }

    if(1 == slave_inturrupt) {
        ret = drv_spi_slv_interrupt(1);
    }
    else {
        ret = drv_spi_slv_interrupt(0);
    }
    
    return ret;
}


/* ---------------------- Registered CMDs to CMD Table ---------------------- */
const CLICmds gCustomCmdTable[] =
{
    { "spi_slave",			test_spi_raw_slave,	    "SPI RAW Data Test"         },
    
    { (const char *)NULL, (CliCmdFunc)NULL,   (const char *)NULL },
};


