#include <stdio.h>
#include "hal_spimst.h"
#include "hal_gpio.h"
#include "drv_spimst.h"
#include "hal_dmac.h"
#include "attrs.h"
#include "osal.h"
//#include "soc_defs.h"
//#include "soc_types.h"

#include "logger.h"
#include <soc_assert.h>
//#include "hw_regs.h"


#define SPIMST_TAG       LOG_TAG_DRV_SPIMST
#define SPIMST_LOG_E(format, ...) log_e(SPIMST_TAG, format, ##__VA_ARGS__)
#define SPIMST_LOG_W(format, ...) log_w(SPIMST_TAG, format, ##__VA_ARGS__)
#define SPIMST_LOG_I(format, ...) log_i(SPIMST_TAG, format, ##__VA_ARGS__)
#define SPIMST_LOG_D(format, ...) log_d(SPIMST_TAG, format, ##__VA_ARGS__)
#define SPIMST_LOG_V(format, ...) log_v(SPIMST_TAG, format, ##__VA_ARGS__)

#define DRV_SPIMST_DEFAULT DRV_SPIMST_0

#define M_SPIMST_TIMEOUT    (5000)

// local alloc.
// maxlen = 4095*38 = for 320*240*2
static lli *sg_local_llp[HAL_SPIMST_MAX];
static int16_t sg_llp_size[HAL_SPIMST_MAX];

static DMAC_CH_E spimst_dma_rx_ch[HAL_SPIMST_MAX] = { DMAC_CH_0, DMAC_CH_10, DMAC_CH_14 };
static DMAC_CH_E spimst_dma_tx_ch[HAL_SPIMST_MAX] = { DMAC_CH_1, DMAC_CH_11, DMAC_CH_15 };
static DMAC_PER_E spimst_dma_rx_per[HAL_SPIMST_MAX] = { DMAC_HW_HS_IF_SPI_RX,  DMAC_HW_HS_IF_SPI1_RX, DMAC_HW_HS_IF_SPI2_RX};
static DMAC_PER_E spimst_dma_tx_per[HAL_SPIMST_MAX] = { DMAC_HW_HS_IF_SPI_TX, DMAC_HW_HS_IF_SPI1_TX,  DMAC_HW_HS_IF_SPI2_TX};


static OsEvent g_spimst_done_event;
static uint8_t *p_tx_data = NULL;
static uint8_t *p_rx_data = NULL;

extern uint32_t SPIMST_TRX_ADDR[HAL_SPIMST_MAX];

int32_t drv_spimst_init(uint32_t clk_Hz, ENUM_SPI_MST_CPHA_T CPHA, ENUM_SPI_MST_CPOL_T CPOL) {
    return drv_spimst_init_ex(DRV_SPIMST_DEFAULT, clk_Hz, CPHA, CPOL);
}

void drv_spimst_deinit(void) {
    return drv_spimst_deinit_ex(DRV_SPIMST_DEFAULT);
}


static void drv_spi_rx_isr(uint8_t *rx_data) {
    OS_EventSet(g_spimst_done_event);
}

uint8_t *drv_spimst_alloc_dma_buffer(uint32_t max_length) {
    return drv_spimst_alloc_dma_buffer_ex(DRV_SPIMST_DEFAULT, max_length);
}

uint8_t *drv_spimst_alloc_dma_limited_buffer(uint32_t max_length) {
    return drv_spimst_alloc_dma_limited_buffer_ex(DRV_SPIMST_DEFAULT, max_length);
}

/*! \brief Release the DMA SPI transfer buffer
 *
 *  Release the DMA SPI transfer buffer
 *
 * \param buffer the buffer alloc from drv_spimst_alloc_dma_buffer
 */
void drv_spimst_free_dma_buffer(uint8_t *buffer) {
    return drv_spimst_free_dma_buffer_ex(DRV_SPIMST_DEFAULT, buffer);
}

void drv_spimst_set_dma_buffer(uint32_t max_length, uint8_t *tx_buf, uint8_t *rx_buf) {
    return drv_spimst_set_dma_buffer_ex(DRV_SPIMST_DEFAULT, max_length, tx_buf, rx_buf);
}

int8_t drv_spimst_dma_trx(uint8_t *write_data, uint8_t *read_data, uint32_t length, uint32_t csn) {
    return drv_spimst_dma_trx_ex(DRV_SPIMST_DEFAULT, write_data, read_data, length, csn);
}


int8_t drv_spimst_trx(uint8_t *write_data, uint8_t *read_data, uint32_t length, uint32_t csn) {
    return drv_spimst_trx_ex(DRV_SPIMST_DEFAULT, write_data, read_data, length, csn);
}



/////////////////EXPAND API
int8_t drv_spimst_dma_transfer(hal_spimst_port port, uint8_t *tx_data, uint8_t *rx_data, uint32_t data_length) ATTRIBUTE_SECTION_FAST;

int32_t drv_spimst_init_ex(drv_spimst_port port, uint32_t clk_Hz, ENUM_SPI_MST_CPHA_T CPHA, ENUM_SPI_MST_CPOL_T CPOL) 
{
    hal_spimst_init(port, clk_Hz, CPHA, CPOL);
    if (OS_FAILED == OS_EventCreate(&g_spimst_done_event)) {
        SPIMST_LOG_E("[%s] System Resource not enough!!\n", __func__);
        return -1;
    }
    hal_dmac_init();
    return 0;
}

void drv_spimst_deinit_ex(drv_spimst_port port) 
{
    if (sg_llp_size[port]) {
        OS_MemFree(sg_local_llp[port]);
        sg_llp_size[port] = 0;
    }
    OS_EventDelete(g_spimst_done_event);   
    hal_spimst_deinit(port);
}

uint8_t *drv_spimst_alloc_dma_buffer_ex(drv_spimst_port port, uint32_t max_length) 
{
    return OS_MemAlloc(max_length); 
}

uint8_t *drv_spimst_alloc_dma_limited_buffer_ex(drv_spimst_port port, uint32_t max_length) 
{ 
    return OS_MemAlloc(max_length); 
}

/*! \brief Release the DMA SPI transfer buffer
 *
 *  Release the DMA SPI transfer buffer
 *
 * \param buffer the buffer alloc from drv_spimst_alloc_dma_buffer
 */
void drv_spimst_free_dma_buffer_ex(drv_spimst_port port, uint8_t *buffer) 
{
    OS_MemFree(buffer);
}

void drv_spimst_set_dma_buffer_ex(drv_spimst_port port, uint32_t max_length, uint8_t *tx_buf, uint8_t *rx_buf) 
{
    return;
}

int8_t drv_spimst_dma_trx_ex(drv_spimst_port port, uint8_t *write_data, uint8_t *read_data, uint32_t length, uint32_t csn) 
{

    int8_t ret = 0;

    if (length <= 0) {
        ret = -1;
        SPIMST_LOG_E("[%s]:%d data_length ERROR\n", __FUNCTION__, __LINE__);
	    goto FUN_FAIL;
    }

    //dma limitation
    if ( length > 4095 ) {
        ret = -1;
        SPIMST_LOG_E("[%s]:%d dma length ERROR\n", __FUNCTION__, __LINE__);
	    goto FUN_FAIL;
    }

    if (csn != SPI_M_CS) {
        hal_gpio_set_logic(csn, GPIO_LOGIC_HIGH);
        hal_gpio_set_dir(csn, GPIO_DIR_OUT);    
        hal_gpio_set_logic(csn, GPIO_LOGIC_LOW);
    }   
    ret = drv_spimst_dma_transfer(port, write_data, read_data, length);

    OS_EventWait(g_spimst_done_event, portMAX_DELAY);
    if (csn != SPI_M_CS) {
        hal_gpio_set_logic(csn, GPIO_LOGIC_HIGH);
    }
    
    return ret;
    
    FUN_FAIL:
    return ret;
}


int8_t drv_spimst_trx_ex(drv_spimst_port port, uint8_t *write_data, uint8_t *read_data, uint32_t length, uint32_t csn) {

    int8_t ret = 0;

    if (length <= 0) {
        ret = -1;
        SPIMST_LOG_E("[%s]:%d data_length ERROR\n", __FUNCTION__, __LINE__);
	    goto FUN_FAIL;
    }

    if (csn != SPI_M_CS) {
        hal_gpio_set_logic(csn, GPIO_LOGIC_HIGH);
        //hal_gpio_set_pull(csn, GPIO_PULL_NONE);
        hal_gpio_set_dir(csn, GPIO_DIR_OUT);    
        hal_gpio_set_logic(csn, GPIO_LOGIC_LOW);
    }
 
    ret = drv_spimst_transfer(port, write_data, read_data, length);

    if (csn != SPI_M_CS) {
        hal_gpio_set_logic(csn, GPIO_LOGIC_HIGH);
    } else {
        // add a delay to release auto csn.
        OS_MsDelay(2);
    }
    
    
    return ret;
    
    FUN_FAIL:
    return ret;
}

static void drv_spimst_rx_isr(DMAC_CH_E CH, DMAC_INT_TYPE_E INT_TYPE)
{

    hal_dmac_clear_int_status(CH, INT_TYPE);   
    OS_EventSet(g_spimst_done_event);
}

int8_t drv_spimst_transfer(hal_spimst_port port, uint8_t *tx_data, uint8_t *rx_data, uint32_t data_length) ATTRIBUTE_SECTION_FAST;
int8_t drv_spimst_dma_transfer(hal_spimst_port port, uint8_t *tx_data, uint8_t *rx_data, uint32_t data_length) {

    int8_t ret = 0x0;
    uint8_t dma_width = 0x0;
    uint32_t dma_data_length = 0;

    uint32_t temp_value = 0x0;
    uint32_t tx_value = 0x0;
    uint32_t rx_value = 0x0;
    uint32_t localPtr;

    (void) localPtr;

    if (data_length == 0) {
#if defined(SPIMST_ERROR_PRINTF) && (SPIMST_ERROR_PRINTF == 1)
        printf("[%s]:%d data_length ERROR\n", __FUNCTION__, __LINE__);
#endif
        return -1;
    }

    p_rx_data = rx_data;
    p_tx_data = tx_data;

    dma_data_length = data_length;
    dma_width = DMAC_TR_WIDTH_8;
    
    hal_spimst_disable(port);
    hal_spimst_set_txfifo_th(port, 0);
    hal_spimst_set_rxfifo_th(port, 0);

  
    if( data_length > 4095 )
    {
        printf("No Support DMA length:%d\n", data_length);
        return -3;
    }

    hal_spimst_enable(port);

    hal_dmac_clear_int_status(spimst_dma_rx_ch[port], spimst_dma_rx_ch[port]);
    hal_dmac_register_isr(spimst_dma_rx_ch[port], DMAC_INT_TYPE_Tfr, drv_spimst_rx_isr);
  
    if (SPI_MST_TRX_MODE == hal_spimst_get_trx_mode(port)) {
        //RX - Used Channel 0
        hal_dmac_start(
                (void *) p_rx_data,	// uint8_t				*DAR,
                (void *) SPIMST_TRX_ADDR[port],	// uint8_t const		*SAR,
                dma_data_length,	        // uint32_t				BLOCK_TS,
                spimst_dma_rx_ch[port],				// DMAC_CH_E			CH
                dma_width,		// DMAC_TR_WIDTH_E		DST_TR_WIDTH
                dma_width,		// DMAC_TR_WIDTH_E		SRC_TR_WIDTH
                DMAC_ADDR_INCREMENT,	// DMAC_ADDR_INC_E		DINC
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E		SINC
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E			DST_MSIZE
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E			SRC_MSIZE
                DMAC_TT_FC_P2M_Dma,		// DMAC_TT_FC_E			TT_FC
                DMAC_CH_PRIOR_1,		// DMAC_CH_PRIOR_E		CH_PRIOR
                DMAC_HS_SEL_SOFTWARE, // HS_SEL_DST, Reset: 0x1 (Software handshaking interface)
                0, // DEST_PER  , Reset: 0x0 (if the CFGx.HS_SEL_SRC field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                DMAC_HS_SEL_HARDWARE, // HS_SEL_SRC, Reset: 0x1 (Software handshaking interface)
                spimst_dma_rx_per[port]  // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                );


        //TX - Used Channel 1
        hal_dmac_start(
                (void *) SPIMST_TRX_ADDR[port],	// uint8_t			*DAR,
                (void *) p_tx_data,	// uint8_t const	    *SAR,
                dma_data_length,            // uint32_t			BLOCK_TS,
                spimst_dma_tx_ch[port],				// DMAC_CH_E		    CH,
                dma_width,		// DMAC_TR_WIDTH_E	DST_TR_WIDTH,
                dma_width,		// DMAC_TR_WIDTH_E	SRC_TR_WIDTH,
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E	DINC,
                DMAC_ADDR_INCREMENT,	// DMAC_ADDR_INC_E	SINC,
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E		SRC_MSIZE,
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E		DST_MSIZE,
                DMAC_TT_FC_M2P_Dma,		// DMAC_TT_FC_E		TT_FC,
                DMAC_CH_PRIOR_1,		// DMAC_CH_PRIOR_E	CH_PRIOR,
                DMAC_HS_SEL_HARDWARE, // HS_SEL_DST, Reset: 0x1 (Software handshaking interface)
                spimst_dma_tx_per[port], // DEST_PER  , Reset: 0x0 (if the CFGx.HS_SEL_SRC field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                DMAC_HS_SEL_SOFTWARE, // HS_SEL_SRC, Reset: 0x1 (Software handshaking interface)
                0 // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                );
    }
    else if (SPI_MST_TX_MODE == hal_spimst_get_trx_mode(port)) 
    {
        //RX - Used Channel 0
        hal_dmac_start(
                //(void *) 0x00201000,	// uint8_t				*DAR,
                (void *) &localPtr,	// uint8_t				*DAR,
                (void *) SPIMST_TRX_ADDR[port],	// uint8_t const		*SAR,
                dma_data_length,	        // uint32_t				BLOCK_TS,
                spimst_dma_rx_ch[port],				// DMAC_CH_E			CH
                dma_width,		// DMAC_TR_WIDTH_E		DST_TR_WIDTH
                dma_width,		// DMAC_TR_WIDTH_E		SRC_TR_WIDTH
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E		DINC
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E		SINC
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E			DST_MSIZE
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E			SRC_MSIZE
                DMAC_TT_FC_P2M_Dma,		// DMAC_TT_FC_E			TT_FC
                DMAC_CH_PRIOR_1,		// DMAC_CH_PRIOR_E		CH_PRIOR
                DMAC_HS_SEL_SOFTWARE, // HS_SEL_DST, Reset: 0x1 (Software handshaking interface)
                0, // DEST_PER  , Reset: 0x0 (if the CFGx.HS_SEL_SRC field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                DMAC_HS_SEL_HARDWARE, // HS_SEL_SRC, Reset: 0x1 (Software handshaking interface)
                spimst_dma_rx_per[port]  // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                );


        //TX - Used Channel 1
        hal_dmac_start(
                (void *) SPIMST_TRX_ADDR[port],	// uint8_t			*DAR,
                (void *) p_tx_data,	// uint8_t const	    *SAR,
                dma_data_length,            // uint32_t			BLOCK_TS,
                spimst_dma_tx_ch[port],				// DMAC_CH_E		    CH,
                dma_width,		// DMAC_TR_WIDTH_E	DST_TR_WIDTH,
                dma_width,		// DMAC_TR_WIDTH_E	SRC_TR_WIDTH,
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E	DINC,
                DMAC_ADDR_INCREMENT,	// DMAC_ADDR_INC_E	SINC,
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E		SRC_MSIZE,
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E		DST_MSIZE,
                DMAC_TT_FC_M2P_Dma,		// DMAC_TT_FC_E		TT_FC,
                DMAC_CH_PRIOR_1,		// DMAC_CH_PRIOR_E	CH_PRIOR,
                DMAC_HS_SEL_HARDWARE, // HS_SEL_DST, Reset: 0x1 (Software handshaking interface)
                spimst_dma_tx_per[port], // DEST_PER  , Reset: 0x0 (if the CFGx.HS_SEL_SRC field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                DMAC_HS_SEL_SOFTWARE, // HS_SEL_SRC, Reset: 0x1 (Software handshaking interface)
                0 // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                );
    }
    else 
    { /* SPI_MST_RX_MODE */
        //RX - Used Channel 0
        hal_dmac_start(
                (void *) p_rx_data,	// uint8_t				*DAR,
                (void *) SPIMST_TRX_ADDR[port],	// uint8_t const		*SAR,
                dma_data_length,	        // uint32_t				BLOCK_TS,
                spimst_dma_rx_ch[port],				// DMAC_CH_E			CH
                dma_width,		// DMAC_TR_WIDTH_E		DST_TR_WIDTH
                dma_width,		// DMAC_TR_WIDTH_E		SRC_TR_WIDTH
                DMAC_ADDR_INCREMENT,	// DMAC_ADDR_INC_E		DINC
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E		SINC
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E			DST_MSIZE
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E			SRC_MSIZE
                DMAC_TT_FC_P2M_Dma,		// DMAC_TT_FC_E			TT_FC
                DMAC_CH_PRIOR_1,		// DMAC_CH_PRIOR_E		CH_PRIOR
                DMAC_HS_SEL_SOFTWARE, // HS_SEL_DST, Reset: 0x1 (Software handshaking interface)
                0, // DEST_PER  , Reset: 0x0 (if the CFGx.HS_SEL_SRC field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                DMAC_HS_SEL_HARDWARE, // HS_SEL_SRC, Reset: 0x1 (Software handshaking interface)
                spimst_dma_rx_per[port]  // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                );


        //TX - Used Channel 1
        hal_dmac_start(
                (void *) SPIMST_TRX_ADDR[port],	// uint8_t			*DAR,
                (void *) &localPtr,	// uint8_t const	    *SAR,
                dma_data_length,            // uint32_t			BLOCK_TS,
                spimst_dma_tx_ch[port],				// DMAC_CH_E		    CH,
                dma_width,		// DMAC_TR_WIDTH_E	DST_TR_WIDTH,
                dma_width,		// DMAC_TR_WIDTH_E	SRC_TR_WIDTH,
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E	DINC,
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E	SINC,
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E		SRC_MSIZE,
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E		DST_MSIZE,
                DMAC_TT_FC_M2P_Dma,		// DMAC_TT_FC_E		TT_FC,
                DMAC_CH_PRIOR_1,		// DMAC_CH_PRIOR_E	CH_PRIOR,
                DMAC_HS_SEL_HARDWARE, // HS_SEL_DST, Reset: 0x1 (Software handshaking interface)
                spimst_dma_tx_per[port], // DEST_PER  , Reset: 0x0 (if the CFGx.HS_SEL_SRC field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                DMAC_HS_SEL_SOFTWARE, // HS_SEL_SRC, Reset: 0x1 (Software handshaking interface)
                0 // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                );
    }

    return 0;
}

/******************************************************************************
 * FunctionName : hal_spimst_transfer
 * Description  : start SPI bus to transfer data
 * Parameters   : uint8_t *tx_data, data output to MOSI
 * Parameters   : uint8_t *rx_data, data input from MISO
 * Returns      : int8_t ret
 *                          -1 ¨C- The operation error.
 *                          00 ¨C- The operation completed successfully.
*******************************************************************************/
int8_t drv_spimst_transfer(hal_spimst_port port, uint8_t *tx_data, uint8_t *rx_data, uint32_t data_length) ATTRIBUTE_SECTION_FAST;
int8_t drv_spimst_transfer(hal_spimst_port port, uint8_t *tx_data, uint8_t *rx_data, uint32_t data_length) {

    
    uint32_t i = 0x0;
    int tx_cnt = 0;
    int rx_cnt = 0;
    uint32_t time_out_cnt = 0;

    if (data_length == 0) {
#if defined(SPIMST_ERROR_PRINTF) && (SPIMST_ERROR_PRINTF == 1)
        printf("[%s]:%d data_length ERROR\n", __FUNCTION__, __LINE__);
#endif
        return -1;
    }

    //loop = data_length / 16;
/*
    if ((sg_spi_mst[port]->CFG0 & HW_SPIMST_REG_CFG0_DATA_LEN_Msk) != 7) {
        hal_spimst_disable(port);
        sg_spi_mst[port]->CFG0 = ((sg_spi_mst[port]->CFG0) & (~(HW_SPIMST_REG_CFG0_DATA_LEN_Msk)))
            | ((0x7) << HW_SPIMST_REG_CFG0_DATA_LEN_Pos)
            ;
    }
*/
    hal_spimst_enable(port);


    for (i = 0; i < data_length; i++) {
        while (0 == hal_spimst_get_status(port, SPI_MST_TX_NOT_FULL)) {
        }

        hal_spimst_write_data(port, tx_data[tx_cnt++]);

        do 
        {
            if (hal_spimst_get_status(port, SPI_MST_RX_NOT_EMPTY)) {
                rx_data[rx_cnt++] = hal_spimst_read_data(port);  //Read Data
            }

        } while(tx_cnt - rx_cnt >= 16);
    }

    time_out_cnt = M_SPIMST_TIMEOUT;
    while (rx_cnt != data_length) {
        while (1 == hal_spimst_get_status(port, SPI_MST_TRX_BUSY)) {
            if (hal_spimst_get_status(port, SPI_MST_RX_NOT_EMPTY)) {
                rx_data[rx_cnt++] = hal_spimst_read_data(port);  //Read Data
                time_out_cnt = M_SPIMST_TIMEOUT;
            }
        }
        if (hal_spimst_get_status(port, SPI_MST_RX_NOT_EMPTY)) {
            rx_data[rx_cnt++] = hal_spimst_read_data(port);  //Read Data
            time_out_cnt = M_SPIMST_TIMEOUT;
        }
        time_out_cnt--;
        if (0 == time_out_cnt) {
#if defined(SPIMST_ERROR_PRINTF) && (SPIMST_ERROR_PRINTF == 1)
            printf("[ERROR][%s]:%d spi master error!\n", __FUNCTION__, __LINE__);
#endif
            return -1;
        }
    }
//    while (1 == hal_spimst_get_status(SPI_MST_RX_NOT_EMPTY)) {
//        rx_data[rx_cnt++] = HW_SPIMST_REG->SPIMST_TRX_DATA;  //Read Data
//#if defined(SPIMST_ERROR_PRINTF) && (SPIMST_ERROR_PRINTF == 1)
//        printf("[ERROR][%s]:%d later coming!!!!!\n", __FUNCTION__, __LINE__);
//#endif
//    }

    return 0;
}

int8_t drv_spimst_dma_tx(hal_spimst_port port, uint8_t *tx_data, uint32_t data_length, DMAC_ISR tx_dma_done_isr) ATTRIBUTE_SECTION_FAST;
int8_t drv_spimst_dma_tx(hal_spimst_port port, uint8_t *tx_data, uint32_t data_length, DMAC_ISR tx_dma_done_isr) {

    int8_t ret = 0x0;
    uint32_t i = 0x0;
    uint32_t align_4_byte = 0x0;
    uint8_t dma_size = 0x0;
    uint32_t dma_data_length = 0;
    uint32_t temp_value = 0x0;
    uint32_t tx_value = 0x0;
    uint32_t rx_value = 0x0;
    uint8_t dma_width = DMAC_TR_WIDTH_8;

    if (data_length == 0) {
#if defined(SPIMST_ERROR_PRINTF) && (SPIMST_ERROR_PRINTF == 1)
        printf("[%s]:%d data_length ERROR\n", __FUNCTION__, __LINE__);
#endif
        return -1;
    }

    hal_spimst_disable(port);

    hal_spimst_set_txfifo_th(port, 0x8);
    hal_spimst_set_rxfifo_th(port, 0x0);
    
    if( data_length <= 4095)
    {
        dma_data_length = data_length;
        dma_size = DMAC_MSIZE_1;
        dma_width = DMAC_TR_WIDTH_8;
        hal_spimst_set_data_length(port, 8);
    }
#if 0
    else if( (data_length <= 8190) && (data_length%2 == 0) )
    {
        dma_data_length = data_length/2;
        dma_size = DMAC_MSIZE_1;
        dma_width = DMAC_TR_WIDTH_16;
        sg_spi_mst[port]->CFG0 = ((sg_spi_mst[port]->CFG0) & (~(HW_SPIMST_REG_CFG0_DATA_LEN_Msk)))
            | ((0xf) << HW_SPIMST_REG_CFG0_DATA_LEN_Pos)
            ;        
    }
#endif    
    else
    {
        printf("No Support DMA length:%d\n", data_length);
        return -3;
    }

    hal_spimst_enable(port);

    hal_dmac_clear_int_status(spimst_dma_tx_ch[port], DMAC_INT_TYPE_Tfr);

    if (tx_dma_done_isr == NULL) {
        //hal_dmac_register_isr(spimst_dma_tx_ch[port], DMAC_INT_TYPE_Tfr, drv_spimst_dma_tx_isr);
    }
    else {
        //spi_data.tx_isr = tx_done_isr;
        hal_dmac_register_isr(spimst_dma_tx_ch[port], DMAC_INT_TYPE_Tfr, tx_dma_done_isr);
    }

#if 0
    if( dma_width == DMAC_TR_WIDTH_16 &&  tx_data != NULL)
    {
        endian_swap_buf( (uint16_t*)spi_data.tx_data, spi_data.length);
    }
#endif    


    //TX - Used Channel SPIMST_TRX_ADDR[port]
    hal_dmac_start(
            (void *) SPIMST_TRX_ADDR[port],	// uint8_t			*DAR,
            (void *) tx_data,	// uint8_t const	    *SAR,
            dma_data_length,            // uint32_t			BLOCK_TS,
            spimst_dma_tx_ch[port],				// DMAC_CH_E		    CH,
            dma_width,		// DMAC_TR_WIDTH_E	DST_TR_WIDTH,
            dma_width,		// DMAC_TR_WIDTH_E	SRC_TR_WIDTH,
            DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E	DINC,
            DMAC_ADDR_INCREMENT,	// DMAC_ADDR_INC_E	SINC,
            dma_size,			    // DMAC_MSIZE_E		SRC_MSIZE,
            dma_size,			    // DMAC_MSIZE_E		DST_MSIZE,
            DMAC_TT_FC_M2P_Dma,		// DMAC_TT_FC_E		TT_FC,
            DMAC_CH_PRIOR_1,		// DMAC_CH_PRIOR_E	CH_PRIOR,
            DMAC_HS_SEL_HARDWARE, // HS_SEL_DST, Reset: 0x1 (Software handshaking interface)
            spimst_dma_tx_per[port], // DEST_PER  , Reset: 0x0 (if the CFGx.HS_SEL_SRC field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
            DMAC_HS_SEL_SOFTWARE, // HS_SEL_SRC, Reset: 0x1 (Software handshaking interface)
            0 // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
            );

#if 1
    if (NULL == tx_dma_done_isr) {
        while(hal_dmac_get_int_raw_status(spimst_dma_tx_ch[port], DMAC_INT_TYPE_Tfr) == 0) {
            OS_MsDelay(1);
        }
        while (hal_spimst_get_status(port, SPI_MST_TRX_BUSY)) {
            OS_MsDelay(1);
        };
    }
#endif

    return 0;
}



int8_t drv_spimst_dma_long_tx(hal_spimst_port port, uint8_t *tx_data, uint32_t data_length, DMAC_ISR tx_dma_done_isr) ATTRIBUTE_SECTION_FAST;
int8_t drv_spimst_dma_long_tx(hal_spimst_port port, uint8_t *tx_data, uint32_t data_length, DMAC_ISR tx_dma_done_isr) {

    int8_t ret = 0x0;
    uint32_t i = 0x0;
    uint32_t align_4_byte = 0x0;
    uint8_t dma_size = 0x0;
    uint32_t dma_data_length = 0;
    uint32_t temp_value = 0x0;
    uint32_t tx_value = 0x0;
    uint32_t rx_value = 0x0;
    uint8_t dma_width = DMAC_TR_WIDTH_8;
    
    if (data_length == 0) {
#if defined(SPIMST_ERROR_PRINTF) && (SPIMST_ERROR_PRINTF == 1)
        printf("[%s]:%d data_length ERROR\n", __FUNCTION__, __LINE__);
#endif
        return -1;
    }

    if (data_length > 4095*sg_llp_size[port]) {
        int s = (data_length+4095)/4095;
        if (sg_llp_size[port]) {
            OS_MemFree(sg_local_llp[port]);
            sg_llp_size[port] = 0;
        }
        sg_local_llp[port] = OS_MemAlloc(sizeof(lli)*s);
        if (sg_local_llp[port]) {
            sg_llp_size[port] = s;
        } else {
            ASSERT(FALSE);
        }
    }

    hal_spimst_disable(port);

    hal_spimst_set_txfifo_th(port, 0x8);
    hal_spimst_set_rxfifo_th(port, 0x0);
    
    dma_data_length = data_length;
    dma_size = DMAC_MSIZE_4;
    dma_width = DMAC_TR_WIDTH_8;
    hal_spimst_set_data_length(port, 8);
        
    hal_spimst_enable(port);

    if (tx_dma_done_isr == NULL) {
    }
    else {
        hal_dmac_register_isr(spimst_dma_tx_ch[port], DMAC_INT_TYPE_Tfr, tx_dma_done_isr);
    }

    //TX - Used Channel 1
    hal_dmac_start_long_data(
            MEM_NO_CACHE(sg_local_llp[port]),
            sg_llp_size[port],
            (void *) SPIMST_TRX_ADDR[port],	// uint8_t			*DAR,
            (void *) tx_data,	// uint8_t const	    *SAR,
            dma_data_length,            // uint32_t			BLOCK_TS,
            DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E	DINC,
            DMAC_ADDR_INCREMENT,	// DMAC_ADDR_INC_E	SINC,
            dma_size,			    // DMAC_MSIZE_E		SRC_MSIZE,
            dma_size,			    // DMAC_MSIZE_E		DST_MSIZE,
            DMAC_TT_FC_M2P_Dma,		// DMAC_TT_FC_E		TT_FC,

            spimst_dma_tx_ch[port],				// DMAC_CH_E		    CH,
            DMAC_CH_PRIOR_1,		// DMAC_CH_PRIOR_E	CH_PRIOR,
            DMAC_HS_SEL_HARDWARE, // HS_SEL_DST, Reset: 0x1 (Software handshaking interface)
            spimst_dma_tx_per[port], // DEST_PER  , Reset: 0x0 (if the CFGx.HS_SEL_SRC field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
            DMAC_HS_SEL_SOFTWARE, // HS_SEL_SRC, Reset: 0x1 (Software handshaking interface)
            0 // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
            );
#if 1
    if (NULL == tx_dma_done_isr) {
        while(hal_dmac_get_int_raw_status(spimst_dma_tx_ch[port], DMAC_INT_TYPE_Tfr) == 0) {
            OS_MsDelay(1);
        }
        while(hal_spimst_get_status(port, SPI_MST_TRX_BUSY)) {
            OS_MsDelay(1);
        }
        //while(!hal_spimst_get_status(port, SPI_MST_TX_EMPTY));
        //REG32(0xc0000c00) = 'I';
    }
#endif

    return 0;
}
