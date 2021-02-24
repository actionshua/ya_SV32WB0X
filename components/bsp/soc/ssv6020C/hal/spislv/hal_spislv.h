#ifndef HAL_SPISLV
#define HAL_SPISLV

#include <soc_types.h>
//#include <hw_regs.h>
//#include <attrs.h>
//#include <soc_defs.h>

typedef void (*SPI_SLV_RX_ISR) (uint8_t *rx_data);

typedef enum  {
    HAL_SPISLV_0 = 0x0,
    HAL_SPISLV_1 = 0x1,
    HAL_SPISLV_MAX = 0x2,
} hal_spislv_port;

typedef enum {
    SPI_SLV_CPHA_0          = 0,
    SPI_SLV_CPHA_1          = 1
} ENUM_SPI_SLV_CPHA_T;

typedef enum {
    SPI_SLV_CPOL_0          = 0,
    SPI_SLV_CPOL_1          = 1
} ENUM_SPI_SLV_CPOL_T;


typedef enum {
    SPI_SLV_TRX_MODE = 0,
    SPI_SLV_TX_MODE  = 1,
    SPI_SLV_RX_MODE  = 2,
} spislv_trx_mode_t;


typedef enum {
    SPI_SLV_TXE_INT         = 0,
    SPI_SLV_TXO_INT         = 1,
    SPI_SLV_RXU_INT         = 2,
    SPI_SLV_RXO_INT         = 3,
    SPI_SLV_RXF_INT         = 4
} ENUM_SPI_SLV_INT_STATUS_T;

typedef enum {
    SPI_SLV_TRX_BUSY        = 0,
    SPI_SLV_TX_NOT_FULL     = 1,
    SPI_SLV_TX_EMPTY        = 2,
    SPI_SLV_RX_NOT_EMPTY    = 3,
    SPI_SLV_RX_FULL         = 4,
    SPI_SLV_TX_ERROR        = 5
} ENUM_SPI_SLV_STATUS_T;

//HW_SPI_PERISLV_REG_Type *hal_spislv_get_instance(hal_spislv_port port);
void hal_spislv_set_trx_mode(hal_spislv_port port, spislv_trx_mode_t trx_mode);
uint8_t hal_spislv_get_trx_mode(hal_spislv_port port);
void hal_spislv_set_cpha_cpol(hal_spislv_port port, ENUM_SPI_SLV_CPHA_T cpha, ENUM_SPI_SLV_CPOL_T cpol);
void hal_spislv_set_cfg_datalen(hal_spislv_port port, uint8_t data_length);
void hal_spislv_set_txfifo_th(hal_spislv_port port, uint8_t threshold);
void hal_spislv_set_rxfifo_th(hal_spislv_port port, uint8_t threshold);
void hal_spislv_enable(hal_spislv_port port);
void hal_spislv_disable(hal_spislv_port port);
void hal_spislv_init(hal_spislv_port port, ENUM_SPI_SLV_CPHA_T cpha, ENUM_SPI_SLV_CPOL_T cpol);
void hal_spislv_deinit(hal_spislv_port port);
int8_t hal_spislv_get_interrupt_status(hal_spislv_port port, uint8_t bit);
int8_t hal_spislv_get_status(hal_spislv_port port, uint8_t bit);
uint32_t hal_spislv_read_status(hal_spislv_port port);
//int32_t hal_spislv_transfer(hal_spislv_port port, uint8_t *tx_data, uint8_t *rx_data, uint32_t data_length);
void hal_spislv_set_latch_latency(uint32_t latency);
uint32_t hal_spislv_read_data(hal_spislv_port port);
void hal_spislv_write_data(hal_spislv_port port, uint32_t data);


#endif /* end of include guard */
