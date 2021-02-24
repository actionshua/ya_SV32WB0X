#include <stdio.h>
#include "drv_spislv.h"
#include "attrs.h"
#include "osal.h"
#include "soc_defs.h"
#include "soc_types.h"
//#include "hw_regs.h"
#include "hal_gpio.h"
#include "hal_dmac.h"
#include "logger.h"


#define SPISLV_TAG  LOG_TAG_DRV_SPISLV
#define SPISLV_LOG_E(format, ...) log_e(SPISLV_TAG, format, ##__VA_ARGS__)
#define SPISLV_LOG_W(format, ...) log_w(SPISLV_TAG, format, ##__VA_ARGS__)
#define SPISLV_LOG_I(format, ...) log_i(SPISLV_TAG, format, ##__VA_ARGS__)
#define SPISLV_LOG_D(format, ...) log_d(SPISLV_TAG, format, ##__VA_ARGS__)
#define SPISLV_LOG_V(format, ...) log_v(SPISLV_TAG, format, ##__VA_ARGS__)

#define M_SPISLV_TIMEOUT    (5000)

static DMAC_CH_E spislv_dma_rx_ch[HAL_SPISLV_MAX] = { DMAC_CH_2, DMAC_CH_10 };
static DMAC_CH_E spislv_dma_tx_ch[HAL_SPISLV_MAX] = { DMAC_CH_3, DMAC_CH_11 };
static DMAC_PER_E spislv_dma_rx_per[HAL_SPISLV_MAX] = { DMAC_HW_HS_IF_SPI_S_RX, DMAC_HW_HS_IF_SPI1_S_RX };
static DMAC_PER_E spislv_dma_tx_per[HAL_SPISLV_MAX] = { DMAC_HW_HS_IF_SPI_S_TX, DMAC_HW_HS_IF_SPI1_S_TX };

static OsEvent g_spislv_done_event = NULL;
static uint8_t *p_tx_buff = NULL;
static uint8_t *p_rx_buff = NULL;

extern uint32_t SPISLV_TRX_ADDR[HAL_SPISLV_MAX];

int32_t drv_spislv_init(drv_spislv_port port, ENUM_SPI_SLV_CPHA_T CPHA, ENUM_SPI_SLV_CPOL_T CPOL)
{
    hal_spislv_init(port, CPHA, CPOL);
    if (OS_FAILED == OS_EventCreate(&g_spislv_done_event)) {
        SPISLV_LOG_E("[%s] System Resource not enough!!\n", __func__);
        return -1;
    }
    hal_dmac_init();

    return 0;
}

void drv_spislv_deinit(drv_spislv_port port)
{
    if( g_spislv_done_event )
    {
        OS_EventDelete(g_spislv_done_event);
        g_spislv_done_event = NULL;
    }
    hal_spislv_deinit(port);
}

static void drv_spislv_rx_isr(DMAC_CH_E CH, DMAC_INT_TYPE_E INT_TYPE) 
{
    hal_dmac_clear_int_status(CH, INT_TYPE);
    OS_EventSet(g_spislv_done_event);  
}

static int32_t drv_spislv_dma_trx_run(hal_spislv_port port, uint8_t *tx_data, uint8_t *rx_data, uint32_t data_length) 
{

    int8_t ret = 0x0;
    uint8_t dma_width = 0;
    uint32_t dma_data_length = 0;
    
    uint32_t localPtr;

    (void) localPtr;

    p_tx_buff = tx_data;
    p_rx_buff = rx_data;

    dma_data_length = data_length;
    dma_width = DMAC_TR_WIDTH_8;

    hal_spislv_disable(port);
    hal_spislv_set_cfg_datalen(port, 0x7);
    hal_spislv_set_txfifo_th(port, 0);
    hal_spislv_set_rxfifo_th(port, 0);
  
    hal_spislv_enable(port);
    
    hal_dmac_clear_int_status(spislv_dma_rx_ch[port], DMAC_INT_TYPE_Tfr);
    hal_dmac_register_isr(spislv_dma_rx_ch[port], DMAC_INT_TYPE_Tfr, drv_spislv_rx_isr);
    
   if (SPI_SLV_TRX_MODE == hal_spislv_get_trx_mode(port) ) {
        //RX - Used Channel 0
        hal_dmac_start(
                (void *) p_rx_buff,	// uint8_t				*DAR,
                (void *) SPISLV_TRX_ADDR[port],	// uint8_t const		*SAR,
                dma_data_length,	        // uint32_t				BLOCK_TS,
                spislv_dma_rx_ch[port],				// DMAC_CH_E			CH
                dma_width,		// DMAC_TR_WIDTH_E		DST_TR_WIDTH
                dma_width,		// DMAC_TR_WIDTH_E		SRC_TR_WIDTH
                DMAC_ADDR_INCREMENT,	// DMAC_ADDR_INC_E		DINC
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E		SINC
                DMAC_MSIZE_1,			    // DMAC_MSIZE_Es			DST_MSIZE
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E			SRC_MSIZE
                DMAC_TT_FC_P2M_Dma,		// DMAC_TT_FC_E			TT_FC
                DMAC_CH_PRIOR_1,		// DMAC_CH_PRIOR_E		CH_PRIOR
                DMAC_HS_SEL_SOFTWARE, // HS_SEL_DST, Reset: 0x1 (Software handshaking interface)
                0, // DEST_PER  , Reset: 0x0 (if the CFGx.HS_SEL_SRC field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                DMAC_HS_SEL_HARDWARE, // HS_SEL_SRC, Reset: 0x1 (Software handshaking interface)
                spislv_dma_rx_per[port]  // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                );


        //TX - Used Channel 1
        hal_dmac_start(
                (void *) SPISLV_TRX_ADDR[port],	// uint8_t			*DAR,
                (void *) p_tx_buff,	// uint8_t const	    *SAR,
                dma_data_length,            // uint32_t			BLOCK_TS,
                spislv_dma_tx_ch[port],				// DMAC_CH_E		    CH,
                dma_width,		// DMAC_TR_WIDTH_E	DST_TR_WIDTH,
                dma_width,		// DMAC_TR_WIDTH_E	SRC_TR_WIDTH,
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E	DINC,
                DMAC_ADDR_INCREMENT,	// DMAC_ADDR_INC_E	SINC,
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E		SRC_MSIZE,
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E		DST_MSIZE,
                DMAC_TT_FC_M2P_Dma,		// DMAC_TT_FC_E		TT_FC,
                DMAC_CH_PRIOR_1,		// DMAC_CH_PRIOR_E	CH_PRIOR,
                DMAC_HS_SEL_HARDWARE, // HS_SEL_DST, Reset: 0x1 (Software handshaking interface)
                spislv_dma_tx_per[port], // DEST_PER  , Reset: 0x0 (if the CFGx.HS_SEL_SRC field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                DMAC_HS_SEL_SOFTWARE, // HS_SEL_SRC, Reset: 0x1 (Software handshaking interface)
                0 // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                );
    }
    else if (SPI_SLV_TX_MODE == hal_spislv_get_trx_mode(port) ) 
    {
        //RX - Used Channel 0
        hal_dmac_start(
                (void *) &localPtr,	// uint8_t				*DAR,
                (void *) SPISLV_TRX_ADDR[port],	// uint8_t const		*SAR,
                dma_data_length,	        // uint32_t				BLOCK_TS,
                spislv_dma_rx_ch[port], //DMAC_CH_10,				// DMAC_CH_E			CH
                DMAC_TR_WIDTH_32,		// DMAC_TR_WIDTH_E		DST_TR_WIDTH
                DMAC_TR_WIDTH_32,		// DMAC_TR_WIDTH_E		SRC_TR_WIDTH
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E		DINC
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E		SINC
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E			DST_MSIZE
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E			SRC_MSIZE
                DMAC_TT_FC_P2M_Dma,		// DMAC_TT_FC_E			TT_FC
                DMAC_CH_PRIOR_1,		// DMAC_CH_PRIOR_E		CH_PRIOR
                DMAC_HS_SEL_SOFTWARE, // HS_SEL_DST, Reset: 0x1 (Software handshaking interface)
                0, // DEST_PER  , Reset: 0x0 (if the CFGx.HS_SEL_SRC field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                DMAC_HS_SEL_HARDWARE, // HS_SEL_SRC, Reset: 0x1 (Software handshaking interface)
                spislv_dma_rx_per[port] //DMAC_HW_HS_IF_SPI1_S_RX  // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                );


        //TX - Used Channel 1
        hal_dmac_start(
                (void *) SPISLV_TRX_ADDR[port],	// uint8_t			*DAR,
                (void *) p_tx_buff,	// uint8_t const	    *SAR,
                dma_data_length,            // uint32_t			BLOCK_TS,
                spislv_dma_tx_ch[port], //DMAC_CH_11,				// DMAC_CH_E		    CH,
                DMAC_TR_WIDTH_32,		// DMAC_TR_WIDTH_E	DST_TR_WIDTH,
                DMAC_TR_WIDTH_32,		// DMAC_TR_WIDTH_E	SRC_TR_WIDTH,
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E	DINC,
                DMAC_ADDR_INCREMENT,	// DMAC_ADDR_INC_E	SINC,
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E		SRC_MSIZE,
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E		DST_MSIZE,
                DMAC_TT_FC_M2P_Dma,		// DMAC_TT_FC_E		TT_FC,
                DMAC_CH_PRIOR_1,		// DMAC_CH_PRIOR_E	CH_PRIOR,
                DMAC_HS_SEL_HARDWARE, // HS_SEL_DST, Reset: 0x1 (Software handshaking interface)
                spislv_dma_tx_per[port], //DMAC_HW_HS_IF_SPI1_S_TX, // DEST_PER  , Reset: 0x0 (if the CFGx.HS_SEL_SRC field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                DMAC_HS_SEL_SOFTWARE, // HS_SEL_SRC, Reset: 0x1 (Software handshaking interface)
                0 // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                );
    }
    else 
    { // SPI_MST_RX_MODE 
        //RX - Used Channel 0
        hal_dmac_start(
                (void *) p_rx_buff,	// uint8_t				*DAR,
                (void *) SPISLV_TRX_ADDR[port],	// uint8_t const		*SAR,
                dma_data_length,	        // uint32_t				BLOCK_TS,
                spislv_dma_rx_ch[port], //DMAC_CH_10,				// DMAC_CH_E			CH
                DMAC_TR_WIDTH_32,		// DMAC_TR_WIDTH_E		DST_TR_WIDTH
                DMAC_TR_WIDTH_32,		// DMAC_TR_WIDTH_E		SRC_TR_WIDTH
                DMAC_ADDR_INCREMENT,	// DMAC_ADDR_INC_E		DINC
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E		SINC
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E			DST_MSIZE
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E			SRC_MSIZE
                DMAC_TT_FC_P2M_Dma,		// DMAC_TT_FC_E			TT_FC
                DMAC_CH_PRIOR_1,		// DMAC_CH_PRIOR_E		CH_PRIOR
                DMAC_HS_SEL_SOFTWARE, // HS_SEL_DST, Reset: 0x1 (Software handshaking interface)
                0, // DEST_PER  , Reset: 0x0 (if the CFGx.HS_SEL_SRC field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                DMAC_HS_SEL_HARDWARE, // HS_SEL_SRC, Reset: 0x1 (Software handshaking interface)
                spislv_dma_rx_per[port] //DMAC_HW_HS_IF_SPI1_S_RX  // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                );


        //TX - Used Channel 1
        hal_dmac_start(
                (void *) SPISLV_TRX_ADDR[port],	// uint8_t			*DAR,
                (void *) &localPtr,	// uint8_t const	    *SAR,
                dma_data_length,            // uint32_t			BLOCK_TS,
                spislv_dma_tx_ch[port], //DMAC_CH_11,				// DMAC_CH_E		    CH,
                DMAC_TR_WIDTH_32,		// DMAC_TR_WIDTH_E	DST_TR_WIDTH,
                DMAC_TR_WIDTH_32,		// DMAC_TR_WIDTH_E	SRC_TR_WIDTH,
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E	DINC,
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E	SINC,
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E		SRC_MSIZE,
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E		DST_MSIZE,
                DMAC_TT_FC_M2P_Dma,		// DMAC_TT_FC_E		TT_FC,
                DMAC_CH_PRIOR_1,		// DMAC_CH_PRIOR_E	CH_PRIOR,
                DMAC_HS_SEL_HARDWARE, // HS_SEL_DST, Reset: 0x1 (Software handshaking interface)
                spislv_dma_tx_per[port], //DMAC_HW_HS_IF_SPI1_TX, // DEST_PER  , Reset: 0x0 (if the CFGx.HS_SEL_SRC field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                DMAC_HS_SEL_SOFTWARE, // HS_SEL_SRC, Reset: 0x1 (Software handshaking interface)
                0 // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                );
    }

    return 0;
}

int32_t drv_spislv_dma_trx(drv_spislv_port port, uint8_t *write_data, uint8_t *read_data, uint32_t length) 
{

    int32_t ret = 0;

    if (length <= 0) 
    {
        ret = -1;
        SPISLV_LOG_E("[%s]:%d data length ERROR, %d\n", __FUNCTION__, __LINE__, length);
	 goto FUN_FAIL;
    }

    if (length >= 4096 ) 
    {
        ret = -2;
        SPISLV_LOG_E("[%s]:%d dma data length ERROR, %d\n", __FUNCTION__, __LINE__, length);
	 goto FUN_FAIL;
    }

    ret = drv_spislv_dma_trx_run(port, write_data, read_data, length);
    OS_EventWait(g_spislv_done_event, portMAX_DELAY);
    
    return ret;
    
    FUN_FAIL:
    return ret;   
}

int32_t drv_spislv_transfer(hal_spislv_port port, uint8_t *tx_data, uint8_t *rx_data, uint32_t data_length) ATTRIBUTE_SECTION_FAST;
int32_t drv_spislv_transfer(hal_spislv_port port, uint8_t *tx_data, uint8_t *rx_data, uint32_t data_length) 
{

    uint32_t i = 0x0;
    int tx_cnt = 0;
    int rx_cnt = 0;
    uint32_t time_out_cnt = 0;
    uint8_t b_active = 0;


    uint8_t trx_mode;
    
    if (data_length == 0) {
        return -1;
    }

    hal_spislv_enable(port);

#if 0

    for (i = 0; i < data_length; i++) 
    {
        while (0 == hal_spislv_get_status(port, SPI_SLV_TX_NOT_FULL)) 
        {
        }

        hal_spislv_write_data(port, tx_data[tx_cnt++]);

        if (hal_spislv_get_status(port, SPI_SLV_RX_NOT_EMPTY)) {
            rx_data[rx_cnt++] = hal_spislv_read_data(port);
            b_active = true;
        }
        
        if( b_active && (hal_spislv_get_status(port, SPI_SLV_TRX_BUSY) == 0) )
        {
            printf("spi idle\n");
            break; 
        }
    }

    time_out_cnt = M_SPISLV_TIMEOUT;
printf("r=%d, t=%d\n", rx_cnt, tx_cnt);   

    while (rx_cnt != data_length) 
    {
        while (1 == hal_spislv_get_status(port, SPI_SLV_TRX_BUSY)) 
        {
            if (hal_spislv_get_status(port, SPI_SLV_RX_NOT_EMPTY)) 
            {
                rx_data[rx_cnt++] = hal_spislv_read_data(port);
            
            }
        }
        time_out_cnt--;
        if (0 == time_out_cnt) {
            printf("r %d, t %d\n", rx_cnt, tx_cnt);
            return rx_cnt;

        }
    }

    printf("R=%d, T=%d\n", rx_cnt, tx_cnt);

#else
    
    //if tx mode enable
    //if( trx_mode != SPI_SLV_RX_MODE  )
    {
        while ( hal_spislv_get_status(port, SPI_SLV_TX_NOT_FULL)) 
        {
            hal_spislv_write_data(port, tx_data[tx_cnt++]);
            if( tx_cnt == data_length )
                break;
            
        }
    }

    //when spi master start tx, busy bit be sent , we check  SPI_SLV_TRX_BUSY
    while( hal_spislv_get_status(port, SPI_SLV_TRX_BUSY)==0 );
    //spi master start tx ...    
  
    do
    {   
        uint32_t spi_status = hal_spislv_read_status(port);
        if ( (rx_cnt < data_length) && ((spi_status&(1<<SPI_SLV_RX_NOT_EMPTY))>>SPI_SLV_RX_NOT_EMPTY ))
        {
            rx_data[rx_cnt++] = hal_spislv_read_data(port);  //Read Data
        } 

        if( (tx_cnt < data_length) && ( (spi_status&(1<<SPI_SLV_TX_NOT_FULL))>>SPI_SLV_TX_NOT_FULL ))
        {
            hal_spislv_write_data(port, tx_data[tx_cnt++]); //write Data
        }

        if( ((spi_status&(1<<SPI_SLV_TRX_BUSY))>>SPI_SLV_TRX_BUSY) == 0  )
        {
            break;
        }
    }  while(( rx_cnt < data_length ) );

#endif  

    return rx_cnt;
}
int32_t drv_spislv_trx(drv_spislv_port port, uint8_t *write_data, uint8_t *read_data, uint32_t length) 
{

    uint32_t ret = 0;

    if (length <= 0) 
    {
        ret = -1;
        SPISLV_LOG_E("[%s]:%d data_length ERROR\n", __FUNCTION__, __LINE__);
        goto FUN_FAIL;
    }
    ret = drv_spislv_transfer(port, write_data, read_data, length);

    return ret;
    
    FUN_FAIL:
    return ret;
}


/////////////////////////////////////////////////////////////////
///////////dma for lli method
/////////////////////////////////////////////////////////////////////

//static spi_buffer sg_spi_mcu_buffer[DRV_SPISLV_MAX];

static spi_buffer *sg_spi_rx_buffer[DRV_SPISLV_MAX];
static spi_buffer *sg_spi_tx_buffer[DRV_SPISLV_MAX];

static lli dma_rx[DRV_SPISLV_MAX][MAX_SPI_BUF_NUM];
static lli dma_tx[DRV_SPISLV_MAX][MAX_SPI_BUF_NUM];

//ISR
void drv_spislv_dma_rx_isr(DMAC_CH_E ch, DMAC_INT_TYPE_E int_type) ATTRIBUTE_SECTION_FAST_TEXT;
void drv_spislv_dma_rx_isr(DMAC_CH_E ch, DMAC_INT_TYPE_E int_type) 
{ 
    
    drv_spislv_port port = DRV_SPISLV_0;

    if(ch == DMAC_CH_2) 
    {
        port = DRV_SPISLV_0;
    } 
    else if(ch == DMAC_CH_10) 
    {
        port = DRV_SPISLV_1;
    } 

    
    int32_t buf_num = sg_spi_rx_buffer[port]->use_buf_num;
    int32_t now = sg_spi_rx_buffer[port]->pingpong_idx;
    int32_t next = (now + 1) % buf_num;   
    
    if(sg_spi_rx_buffer[port]->ping_pong[now].data_ready == 0) 
    {
        sg_spi_rx_buffer[port]->ping_pong[now].data_ready = 1;            
        //dma_rx[port][now].ctl2 &= 0x0fff;
        sg_spi_rx_buffer[port]->pingpong_idx = next;               
    }


    hal_dmac_clear_int_status(ch, int_type);
       
}
#if 0
void drv_spislv_dma_rx_isr(DMAC_CH_E ch, DMAC_INT_TYPE_E int_type) 
{
hal_gpio_set_logic(22, 0);     
    int i = 0;
    drv_spislv_port port = DRV_SPISLV_MAX;
    if(ch == DMAC_CH_2) 
    {
        port = DRV_SPISLV_0;
    } 
    else if(ch == DMAC_CH_10) 
    {
        port = DRV_SPISLV_1;
    } 
    else 
    {
        printf("spislv dma rx channel(%d) not use, please check\n", port);
        return;
    }
    
    int32_t buf_num = sg_spi_rx_buffer[port]->use_buf_num;
    int32_t now = sg_spi_rx_buffer[port]->pingpong_idx;
    int32_t next = (now + 1) % buf_num;   
    
#if 0
    for(i = 0; i < buf_num; i++) {
        printf("[%d]now:sar:%x dar:%x llp: %x ctl1: %x ctl2: %x\n",i, dma_rx.ll[port][i].sar, dma_rx.ll[port][i].dar, dma_rx.ll[port][i].llp, dma_rx.ll[port][i].ctl1, dma_rx.ll[port][i].ctl2);
    }
#endif

                if(sg_spi_rx_buffer[port]->ping_pong[now].data_ready == 0) 
                {
                    sg_spi_rx_buffer[port]->ping_pong[now].data_ready = 1;            
                    dma_rx[port][now].ctl2 &= 0x0fff;
                    sg_spi_rx_buffer[port]->pingpong_idx = next;
#if 0                    
                    //check next buf is free
                    if(sg_spi_rx_buffer[port]->ping_pong[next].data_ready == 1) 
                    {
                printf("rx fifo will full\n");
                    }
#endif                    
                } 
                else 
                {
        ;//printf("data overflow");
        }
      
    hal_dmac_clear_int_status(ch, int_type);
    
hal_gpio_set_logic(22, 1);         
}
#endif
void drv_spislv_dma_tx_isr(DMAC_CH_E ch, DMAC_INT_TYPE_E int_type) ATTRIBUTE_SECTION_FAST_TEXT;
void drv_spislv_dma_tx_isr(DMAC_CH_E ch, DMAC_INT_TYPE_E int_type) 
{
    int i = 0;
    drv_spislv_port port = DRV_SPISLV_0;
    if(ch == DMAC_CH_3) 
    {
        port = DRV_SPISLV_0;
    } 
    else if(ch == DMAC_CH_11) 
    {
        port = DRV_SPISLV_1;
    } 
    else 
    {
        printf("spislv dma rx channel(%d) not use, please check\n", port);
        return;
    }
    
    int32_t buf_num = sg_spi_tx_buffer[port]->use_buf_num;
    int32_t now = sg_spi_tx_buffer[port]->pingpong_idx;
    int32_t next = (now + 1) % buf_num;   
  
#if 0
    for(i = 0; i < buf_num; i++) {
        printf("[%d]now:sar:%x dar:%x llp: %x ctl1: %x ctl2: %x\n",i, dma_rx.ll[port][i].sar, dma_rx.ll[port][i].dar, dma_rx.ll[port][i].llp, dma_rx.ll[port][i].ctl1, dma_rx.ll[port][i].ctl2);
    }
#endif



    if(sg_spi_tx_buffer[port]->ping_pong[now].data_ready == 1) 
    {
  
        sg_spi_tx_buffer[port]->ping_pong[now].data_ready = 0;
        //dma_tx[port][now].ctl2 &= 0x0fff;
        sg_spi_tx_buffer[port]->pingpong_idx = next;
#if 0
        //check next
        if(sg_spi_tx_buffer[port]->ping_pong[next].data_ready == 0) 
        {
            printf("tx fifo will empty ");          
        }
#endif
    }
    else 
    {
        ;//printf("data empty");
    }   
    hal_dmac_clear_int_status(ch, int_type);
}
int check_and_set_dma_rx_buf(drv_spislv_port port, int32_t *buf_num)
{
    //HW_SPI_PERISLV_REG_Type *spi_slv = hal_spislv_get_instance(port);

    uint32_t dma_buf_num = sg_spi_rx_buffer[port]->use_buf_num, cnt = 0, check_len = 0;
    uint32_t dma_rx_addr = SPISLV_TRX_ADDR[port];

    for(cnt = 0; cnt < dma_buf_num; cnt++) 
    {
        check_len = (uint32_t)sg_spi_rx_buffer[port]->ping_pong[0].buffer_len;
        if(sg_spi_rx_buffer[port]->ping_pong[cnt].buffer == NULL) 
        {
            printf("number: %d buffer is null, please alloc address\n", cnt);
            return -2;
        }
    }

    for(cnt = 0; cnt < dma_buf_num; cnt++) 
    {
        dma_rx[port][cnt].sar = dma_rx_addr;
        dma_rx[port][cnt].dar = (uint32_t)sg_spi_rx_buffer[port]->ping_pong[cnt].buffer;
        if(cnt == (dma_buf_num -1)) //last link node point to first node
        {
            dma_rx[port][cnt].llp = (uint32_t)&dma_rx[port][0];
        } 
        else    //other link node point to nex node
        {
            dma_rx[port][cnt].llp = (uint32_t)&dma_rx[port][cnt+1];
        }
     
        dma_rx[port][cnt].ctl2=  check_len;
    }

    *buf_num = dma_buf_num;
    return (int)check_len;
}

void drv_spislv_dma_rx_run(drv_spislv_port port, uint8_t *rx_data, uint32_t byte_size, DMAC_ISR rx_done_isr, lli *lli_addr, int lli_num) 
{
    //HW_SPI_PERISLV_REG_Type *spi_slv = hal_spislv_get_instance(port);

    DMAC_CH_E ch_rx =HAL_DMAC_CH_NOT_FOUND;
    DMAC_PER_E per_rx = DMAC_HW_HS_IF_SPI_S_RX;
    DMAC_TR_WIDTH_E dma_width = DMAC_TR_WIDTH_8;
    uint8_t dma_size = 0x0;
    uint32_t cnt = 0;
    uint32_t dma_data_length = byte_size;
    uint32_t dma_buf_num = sg_spi_rx_buffer[port]->use_buf_num;

    dma_size = DMAC_MSIZE_1;
    
    for(cnt = 0; cnt < dma_buf_num; cnt++) {
        dma_rx[port][cnt].ctl2=  dma_data_length;
    }

    if(port == DRV_SPISLV_0) {
        ch_rx = DMAC_CH_2;
        per_rx = DMAC_HW_HS_IF_SPI_S_RX;
    } else if(port == DRV_SPISLV_1) {
        ch_rx = DMAC_CH_10;
        per_rx = DMAC_HW_HS_IF_SPI1_S_RX;
    }
    
    hal_dmac_register_isr(ch_rx, DMAC_INT_TYPE_Block, rx_done_isr);
    hal_dmac_dst_llp_enable(ch_rx);
                
        hal_dmac_start_lli(
                (void *) rx_data,	// uint8_t				*DAR,
                (void *) SPISLV_TRX_ADDR[port],	// uint8_t const		*SAR,
                dma_data_length,	        // uint32_t				BLOCK_TS,
                ch_rx, //DMAC_CH_10,				// DMAC_CH_E			CH
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
                per_rx, //DMAC_HW_HS_IF_SPI1_S_RX  // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                lli_addr,
                lli_num
                );
                
}

int32_t drv_spislv_dma_rx_start(drv_spislv_port port)
{
    int32_t buf_len = 0, buf_num = 0;

    buf_len = check_and_set_dma_rx_buf(port, &buf_num);
    //printf("buf_len = %d, buf_num = %d\n", buf_len, buf_num);

    if(buf_len > 0)
    {
        drv_spislv_dma_rx_run(port, (uint8_t*)dma_rx, buf_len, drv_spislv_dma_rx_isr, (lli*)(dma_rx[port]), buf_num);
    }
    else
        return -1;
    
    return 0;
}

static int check_and_set_dma_tx_buf(drv_spislv_port port, int32_t *buf_num)
{
    //HW_SPI_PERISLV_REG_Type *spi_slv = hal_spislv_get_instance(port);

    uint32_t dma_buf_num = sg_spi_tx_buffer[port]->use_buf_num, cnt = 0, check_len = 0;
    uint32_t dma_tx_addr = SPISLV_TRX_ADDR[port];

    for(cnt = 0; cnt < dma_buf_num; cnt++) 
    {
        check_len = (uint32_t)sg_spi_tx_buffer[port]->ping_pong[0].buffer_len;
        if(sg_spi_tx_buffer[port]->ping_pong[cnt].buffer == NULL) 
        {
            printf("number: %d buffer is null, please alloc address\n", cnt);
            return -2;
        }
    }

    for(cnt = 0; cnt < dma_buf_num; cnt++) 
    {
        dma_tx[port][cnt].sar = (uint32_t)sg_spi_tx_buffer[port]->ping_pong[cnt].buffer;
        dma_tx[port][cnt].dar = dma_tx_addr;
        if(cnt == (dma_buf_num -1)) //last link node point to first node
        {
            dma_tx[port][cnt].llp = (uint32_t)&dma_tx[port][0];
        } 
        else    //other link node point to nex node
        {
            dma_tx[port][cnt].llp = (uint32_t)&dma_tx[port][cnt+1];
        }
     
        dma_tx[port][cnt].ctl2=  check_len;
    }

    *buf_num = dma_buf_num;
    return (int)check_len;
}

static void drv_spislv_dma_tx_run(drv_spislv_port port, uint8_t *tx_data, uint32_t byte_size, DMAC_ISR tx_done_isr, lli *lli_addr, int lli_num) 
{
    //HW_SPI_PERISLV_REG_Type *spi_slv = hal_spislv_get_instance(port);

    DMAC_CH_E ch_tx =HAL_DMAC_CH_NOT_FOUND;
    DMAC_PER_E per_tx = DMAC_HW_HS_IF_SPI_S_TX;
    DMAC_TR_WIDTH_E dma_width = DMAC_TR_WIDTH_8;
    uint8_t dma_size = 0x0;
    uint32_t cnt = 0;
    uint32_t dma_data_length = byte_size;
    uint32_t dma_buf_num = sg_spi_tx_buffer[port]->use_buf_num;

    dma_size = DMAC_MSIZE_1;
    
    for(cnt = 0; cnt < dma_buf_num; cnt++) {
        dma_rx[port][cnt].ctl2=  dma_data_length;
    }

    if(port == DRV_SPISLV_0) {
        ch_tx = DMAC_CH_3;
        per_tx = DMAC_HW_HS_IF_SPI_S_TX;
    } else if(port == DRV_SPISLV_1) {
        ch_tx = DMAC_CH_11;
        per_tx = DMAC_HW_HS_IF_SPI1_S_TX;
    }
    
    hal_dmac_register_isr(ch_tx, DMAC_INT_TYPE_Block, tx_done_isr);
    hal_dmac_src_llp_enable(ch_tx);
                  
        hal_dmac_start_lli(
                (void *) SPISLV_TRX_ADDR[port],	// uint8_t				*DAR,
                (void *) tx_data,	// uint8_t const		*SAR,
                dma_data_length,	        // uint32_t				BLOCK_TS,
                ch_tx, //DMAC_CH_10,				// DMAC_CH_E			CH
                dma_width,		// DMAC_TR_WIDTH_E		DST_TR_WIDTH
                dma_width,		// DMAC_TR_WIDTH_E		SRC_TR_WIDTH
                DMAC_ADDR_NO_CHANGE,	// DMAC_ADDR_INC_E		DINC
                DMAC_ADDR_INCREMENT,	// DMAC_ADDR_INC_E		SINC
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E			DST_MSIZE
                DMAC_MSIZE_1,			    // DMAC_MSIZE_E			SRC_MSIZE
                DMAC_TT_FC_M2P_Dma,		// DMAC_TT_FC_E			TT_FC
                DMAC_CH_PRIOR_1,		// DMAC_CH_PRIOR_E		CH_PRIOR
                DMAC_HS_SEL_HARDWARE, // HS_SEL_DST, Reset: 0x1 (Software handshaking interface)
                per_tx, // DEST_PER  , Reset: 0x0 (if the CFGx.HS_SEL_SRC field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                DMAC_HS_SEL_SOFTWARE, // HS_SEL_SRC, Reset: 0x1 (Software handshaking interface)
                0, //DMAC_HW_HS_IF_SPI1_S_RX  // SRC_PER   , Reset: 0x0 (if the CFGx.HS_SEL_DST field is DMAC_HS_SEL_HARDWARE; otherwise, this field is ignored.)
                lli_addr,
                lli_num
                );
    return;
}


int32_t drv_spislv_dma_tx_start(drv_spislv_port port)
{
    int32_t buf_len = 0, buf_num = 0;

    buf_len = check_and_set_dma_tx_buf(port, &buf_num);
    //printf("buf_len = %d, buf_num = %d\n", buf_len, buf_num);

    if(buf_len > 0)
    {
        drv_spislv_dma_tx_run(port, (uint8_t*)dma_tx, buf_len, drv_spislv_dma_tx_isr, (lli*)(dma_tx[port]), buf_num);
    }
    
    return 0;
}

int32_t drv_spislv_set_dma_buffer(drv_spislv_port port, spi_buffer *write_data, spi_buffer *read_data)
{
    if(write_data != NULL)
        sg_spi_tx_buffer[port] = write_data;
    if(read_data != NULL)
        sg_spi_rx_buffer[port] = read_data;

      
    return 0;
}

int32_t drv_spislv_dma_lli_trx(drv_spislv_port port, spi_buffer *write_data, spi_buffer *read_data, uint32_t length) 
{
    //0:trx, 1:tx only, 2:rx only
    uint8_t trx_mode = hal_spislv_get_trx_mode(port);
    
    //check tx and rx buff length
    
    drv_spislv_set_dma_buffer(port, write_data, read_data);

    hal_spislv_disable(port);
    hal_spislv_set_cfg_datalen(port, 0x7);
    hal_spislv_set_txfifo_th(port, 0);
    hal_spislv_set_rxfifo_th(port, 0);
    
    if( (trx_mode & 0x2) == 0 ) //TX mode support
    {
        //printf("tx dma run\n");
        drv_spislv_dma_tx_start(port);
    }

    if( (trx_mode & 0x1) == 0) //RX mode support
    {
        //printf("rx dma run\n");
        drv_spislv_dma_rx_start(port);
    }
    hal_spislv_enable(port);

    return 0;
}

int32_t drv_spislv_dma_rx_stop(drv_spislv_port port)
{
    int timeout_cnt = 100;
    while(timeout_cnt)
    {
        hal_dmac_stop(spislv_dma_rx_ch[port]);
        int32_t ch_status= hal_dmac_get_channel_status(spislv_dma_rx_ch[port]);
        if(ch_status == HAL_DMAC_STATUS_OK)
            break;

        timeout_cnt--;
        OS_MsDelay(10);
    }
    
    if(timeout_cnt == 0)
        return -1;
    else
        return 0;

}

int32_t drv_spislv_dma_tx_stop(drv_spislv_port port)
{
    int timeout_cnt = 100;
    while(timeout_cnt)
    {
        hal_dmac_stop(spislv_dma_tx_ch[port]);
        int32_t ch_status= hal_dmac_get_channel_status(spislv_dma_tx_ch[port]);
        if(ch_status == HAL_DMAC_STATUS_OK)
            break;

        timeout_cnt--;
        OS_MsDelay(10);
    }
    
    if(timeout_cnt == 0)
        return -1;
    else
        return 0;

}

int32_t drv_spislv_dma_lli_trx_stop(drv_spislv_port port)
{
    //0:trx, 1:tx only, 2:rx only
    int32_t ret = 0;
    uint8_t trx_mode = hal_spislv_get_trx_mode(port);

    if( (trx_mode & 0x2) == 0 ) //TX mode support
    {
        //printf("tx dma run\n");
        ret = drv_spislv_dma_tx_stop(port);
    }

    if( (trx_mode & 0x1) == 0) //RX mode support
    {
        //printf("rx dma run\n");
        ret = drv_spislv_dma_rx_stop(port);
    }
    hal_spislv_disable(port);    
    
    return 0;
}

void drv_spislv_set_trx_mode(hal_spislv_port port, spislv_trx_mode_t trx_mode)
{
    return hal_spislv_set_trx_mode(port, trx_mode);
}


