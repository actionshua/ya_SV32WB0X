#ifndef HAL_SPIMST
#define HAL_SPIMST

#include "soc_types.h"

typedef enum {
    HAL_SPIMST_0 = 0x0,
    HAL_SPIMST_1 = 0x1,
    HAL_SPIMST_2 = 0x2,
    HAL_SPIMST_MAX,
} hal_spimst_port;

typedef enum {
    SPI_MST_CPHA_0          = 0,
    SPI_MST_CPHA_1          = 1
} ENUM_SPI_MST_CPHA_T;

typedef enum {
    SPI_MST_CPOL_0          = 0,
    SPI_MST_CPOL_1          = 1
} ENUM_SPI_MST_CPOL_T;


typedef enum {
    SPI_MST_TRX_MODE = 0,
    SPI_MST_TX_MODE  = 1,
    SPI_MST_RX_MODE  = 2,
} spimst_trx_mode_t;


typedef enum {
    SPI_MST_TXE_INT         = 0,
    SPI_MST_TXO_INT         = 1,
    SPI_MST_RXU_INT         = 2,
    SPI_MST_RXO_INT         = 3,
    SPI_MST_RXF_INT         = 4
} ENUM_SPI_MST_INT_STATUS_T;

typedef enum {
    SPI_MST_TRX_BUSY        = 0,
    SPI_MST_TX_NOT_FULL     = 1,
    SPI_MST_TX_EMPTY        = 2,
    SPI_MST_RX_NOT_EMPTY    = 3,
    SPI_MST_RX_FULL         = 4,
    SPI_MST_TX_ERROR        = 5
} ENUM_SPI_MST_STATUS_T;


void hal_spimst_set_trx_mode(hal_spimst_port port, spimst_trx_mode_t trx_mode);
void hal_spimst_set_cpha_cpol(hal_spimst_port port, ENUM_SPI_MST_CPHA_T cpha, ENUM_SPI_MST_CPOL_T cpol);
void hal_spimst_set_clk(hal_spimst_port port, uint32_t clk_Hz);
void hal_spimst_enable(hal_spimst_port port);
void hal_spimst_disable(hal_spimst_port port);
void hal_spimst_init(hal_spimst_port port, uint32_t clk_Hz, ENUM_SPI_MST_CPHA_T cpha, ENUM_SPI_MST_CPOL_T cpol);
void hal_spimst_deinit(hal_spimst_port port);
int8_t hal_spimst_get_interrupt_status(hal_spimst_port port, uint8_t bit);
int8_t hal_spimst_get_status(hal_spimst_port port, uint8_t bit) __attribute__((section(".prog_in_sram")));
void hal_spimst_set_latch_latency(hal_spimst_port port, uint32_t latency);
uint32_t hal_spimst_read_data(hal_spimst_port port);
void hal_spimst_write_data(hal_spimst_port port, uint32_t data);
uint8_t hal_spimst_get_trx_mode(hal_spimst_port port);
void hal_spimst_set_txfifo_th(hal_spimst_port port, uint8_t threshold);
void hal_spimst_set_rxfifo_th(hal_spimst_port port, uint8_t threshold);

void hal_spimst_set_data_length(hal_spimst_port port, uint8_t data_length);
//uint32_t hal_spimst_is_busy(hal_spimst_port port);


#endif /* end of include guard */
