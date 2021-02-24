#ifndef SPISLV
#define SPISLV


#include "hal_spislv.h"

#include "custom_io_hal.h"
#include "custom_io_chk.h"

typedef enum  {
    DRV_SPISLV_0 = 0x0,
    DRV_SPISLV_1 = 0x1,
    DRV_SPISLV_MAX = 0x2,
} drv_spislv_port;


#define DRV_SPISLV_INIT_HAL_SPISLV_0(clk, cpha, cpol) \
    do { \
        drv_spislv_init(HAL_SPISLV_0, clk, cpha, cpol); \
        (void)PERI_IO_SPIS0; \
    } while(0)

#define DRV_SPISLV_INIT_HAL_SPISLV_1(clk, cpha, cpol) \
    do { \
        drv_spislv_init(HAL_SPISLV_1, clk, cpha, cpol); \
        (void)PERI_IO_SPIS1; \
    } while(0)

#define DRV_SPISLV_INIT(SPIS, clk, cpha, cpol) \
    DRV_SPISLV_INIT_##SPIS(clk, cpha, cpol);
/**
 * Initilize SPI bus to enable SPI operations.
 *            
 * @param   CPHA       Serial Clock Phase. 
 *              0x00 - Serial clock toggles in middle of first data bit
 *              0x01 - Serial clock toggles at start of first data bit
 * @param   CPOL       Serial Clock Polarity. 
 *              0x00 - Inactive state of serial clock is low
 *              0x01 - Inactive state of serial clock is high, need pull up in the clock pin.
 */
int32_t drv_spislv_init(drv_spislv_port port, ENUM_SPI_SLV_CPHA_T CPHA, ENUM_SPI_SLV_CPOL_T CPOL);



/**
 * Deinitialize SPI bus to disable SPI operations
 * 
 */
void drv_spislv_deinit(drv_spislv_port port);


/**
 * Transmit and receive the spi data by dma.
 * 
 * @param   write_data      Pointer to the data buffer to be written by the master.
 * @param   read_data       Pointer to the data buffer to be read by the master.
 * @param   length          Size of the data buffer exposed to the SPI master - max dma length : 8190 bytes for even length, 4095 for odd length.
 * @param   csn             Chip select pin.
 *
 * @return  -1              The operation error.
 * @return   0              The operation completed successfully.
 */
int32_t drv_spislv_dma_trx(drv_spislv_port port, uint8_t *write_data, uint8_t *read_data, uint32_t length);


/**
 * Transmit and receive the spi data.
 * 
 * @param   write_data      Pointer to the data buffer to be written by the master.
 * @param   read_data       Pointer to the data buffer to be read by the master.
 * @param   length          Size of the data buffer exposed to the SPI master.
 * @param   csn             Chip select pin.
 *
 * @return  -1              The operation error.
 * @return   0              The operation completed successfully.
 */
int32_t drv_spislv_trx(drv_spislv_port port, uint8_t *write_data, uint8_t *read_data, uint32_t length);

//////////////////////////
#define MAX_SPI_BUF_NUM 16

struct _spi_buffer_st 
{
    uint16_t buffer_idx;                /**< the driver is using data index of the buffer. */
    uint16_t buffer_len;                /**< the buffer total length. */
    uint8_t* buffer;                    /**< point to the buffer. */
    volatile uint8_t data_ready;        /**< point to the buffer is data available, Rx: the driver set it, clean by application, Tx: the applcation set it, clean by driver. */
};

typedef struct 
{
    uint8_t pingpong_idx;               /**< driver using in which pingpong, initial to 0 */
    struct _spi_buffer_st ping_pong[MAX_SPI_BUF_NUM]; /**< ping/pong buffer */
    uint32_t use_buf_num;
    //I2S_ISR_FUNC void *(*event)(enum i2s_event evt, void *reserved); /**< event callback(ISR) */
} spi_buffer;

int32_t drv_spislv_dma_lli_trx(drv_spislv_port port, spi_buffer *write_data, spi_buffer *read_data, uint32_t length);
int32_t drv_spislv_dma_lli_trx_stop(drv_spislv_port port);
void drv_spislv_set_trx_mode(hal_spislv_port port, spislv_trx_mode_t trx_mode);


#endif


