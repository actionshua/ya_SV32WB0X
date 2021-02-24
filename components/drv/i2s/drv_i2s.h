#ifndef _DRV_I2S_H_
#define _DRV_I2S_H_

#include "hal_i2s.h"

#include "custom_io_hal.h"
#include "custom_io_chk.h"

#define I2S_ISR_FUNC
#define MAX_BUF_NUM 36

typedef enum {
    DRV_I2S_STATUS_INVALID_PARAMETER  = -2, /**< parameter error */
    DRV_I2S_STATUS_ERROR = -1, /**< status error */
    DRV_I2S_STATUS_OK =  0 /**< status ok */
} drv_i2s_status_t;

typedef enum  {
    DRV_I2S_0 = 0x0,
    DRV_I2S_1 = 0x1,
    DRV_I2S_MAX = 0x2,
} drv_i2s_port;

typedef enum {
    DRV_SampleRate_mormal = 0,
    DRV_SampleRate_8000HZ = 8000,
    DRV_SampleRate_11025HZ = 11025,
    DRV_SampleRate_16000HZ = 16000,
    DRV_SampleRate_22050HZ = 22050,
    DRV_SampleRate_24000HZ = 24000,
    DRV_SampleRate_44100HZ = 44100,
    DRV_SampleRate_48000HZ = 48000,
} drv_sample_rate_t;

typedef enum {
    MCU_MODE = 0x0, /**< use mcu copy data */
    DMAC_MODE = 0x1, /**< use dmac copy data. */
    MAX_HANDLER = 0x2,
} i2s_data_handler;

struct _i2s_buffer_st {
    uint16_t buffer_idx;                /**< the driver is using data index of the buffer. */
    uint16_t buffer_len;                /**< the buffer total length. */
    int16_t* buffer;                    /**< point to the buffer. */
    volatile uint8_t data_ready;        /**< point to the buffer is data available, Rx: the driver set it, clean by application, Tx: the applcation set it, clean by driver. */
};

enum i2s_event {
    I2S_NO_DATA,                        /**< driver cannot get data (tx). */
    I2S_DISABLE_ISR,                    /**< driver disable isr. */
    I2S_BUFFER_FULL,                    /**< driver buffer full (rx). */
};

typedef struct {
    volatile uint16_t idle_cnt;         /**< driver counting how many time not get data, initial to 0 */
    uint8_t pingpong_idx;               /**< driver using in which pingpong, initial to 0 */
    uint8_t stereo;                     /**< stereo: 1, mono: 0 */
    uint8_t i2s_dup_sample_idx;         /**< driver using, initial to 0 */
    uint8_t dup_sample;                 /**< for mcu mode sample rate downgrade. 48K->24K, set to 1, 48K->16K, set to 2, 48K->8K, set to 5, 44100->22050, set to 1. 44100->11025, set to 3. */
                                                           /**< for dma mode sample rate downgrade. only origin sample rate*/
    struct _i2s_buffer_st ping_pong[MAX_BUF_NUM]; /**< ping/pong buffer */
    I2S_ISR_FUNC void *(*event)(enum i2s_event evt, void *reserved); /**< event callback(ISR) */
} i2s_buffer;

/**
 * @brief This function set the pingpong buffer for audio
 *
 * @param  buf - rx or tx ring buffer for i2s.
 *
 */
void drv_i2s_set_buffer(
    i2s_buffer *buf);

/**
 * @brief This function will initialize I2S config setting
 *
 * @param  mode - mode_master
 * @param  sample_rate - SampleRate_8000HZ, SampleRate_11025HZ, SampleRate_16000HZ, SampleRate_22050HZ, SampleRate_24000HZ, SampleRate_44100HZ, SampleRate_48000HZ
 * @param  resolution  - Resolution_16bit
 *
 * @return
 *     - DRV_I2S_STATUS_INVALID_PARAMETER
 *     - DRV_I2S_STATUS_OK
 */
drv_i2s_status_t drv_i2s_init(
    i2s_mode_t mode,
    sample_rate_t sample_rate,
    bit_resolution_t resolution);

 /**
 * @brief start output to ring buffer.
 *
 */
void drv_i2s_tx_start();

 /**
 * @brief stop output to ring buffer.
 *
 */
void drv_i2s_tx_stop();

 /**
 * @brief start input to ring buffer.
 *
 */
void drv_i2s_rx_start();

 /**
 * @brief stop input to ring buffer.
 *
 */
void drv_i2s_rx_stop();

 /**
 * @brief start loopback
 *
 */
void drv_i2s_loopback_start();

 /**
 * @brief stop loopback
 *
 */
void drv_i2s_loopback_stop();

/**
 * @brief This function set the pingpong buffer for audio
 *
 *  extend with drv_i2s_set_buffer
 *
 * @param  port - i2s interface port
 * @param  rx - rx ring buffer for i2s.
 * @param  rx_num rx ring buffer number for i2s.
 * @param  tx - tx ring buffer for i2s.
 * @param  tx_num - tx ring buffer number for i2s.
 *
 *     - DRV_I2S_STATUS_INVALID_PARAMETER
 *     - DRV_I2S_STATUS_OK
 */
drv_i2s_status_t drv_i2s_set_buffer_ex(
    drv_i2s_port port,
    i2s_buffer *rx,
    int rx_num,
    i2s_buffer *tx,
    int tx_num);

/**
 * @brief This function will initialize I2S config setting
 *
 *  extend with drv_i2s_init
 *
 * @param  module - i2s interface port
 * @param  mode - mode_master
 * @param  sample_rate - SampleRate_8000HZ, SampleRate_11025HZ, SampleRate_16000HZ, SampleRate_22050HZ, SampleRate_24000HZ, SampleRate_44100HZ, SampleRate_48000HZ
 * @param  resolution  - Resolution_16bit
 *
 * @return
 *     - DRV_I2S_STATUS_INVALID_PARAMETER
 *     - DRV_I2S_STATUS_OK
 */
drv_i2s_status_t drv_i2s_init_ex(
    drv_i2s_port port,
    i2s_mode_t mode,
    drv_sample_rate_t sample_rate,
    bit_resolution_t resolution);

 /**
 * @brief start output to ring buffer.
 *
 *  extend with drv_i2s_tx_start
 *  play ring buffer.
 *
 * @param port Specifies the i2s port.
 * @param handler - MCU_MODE: use mcu copy data, This mode can not run rx at same time.
 *                                      DMAC_MODE: use dmac copy data, only use dmac channel 1 or channel 9
 *
 * @return
 *     - DRV_I2S_STATUS_ERROR
 *     - DRV_I2S_STATUS_INVALID_PARAMETER
 *     - DRV_I2S_STATUS_OK
 */
drv_i2s_status_t drv_i2s_tx_start_ex(
    drv_i2s_port port,
    i2s_data_handler handler);

 /**
 * @brief stop output to ring buffer.
 *
 *  extend with drv_i2s_tx_stop
 *
 * @param port Specifies the i2s port.
 *
 * @return
 *     - DRV_I2S_STATUS_INVALID_PARAMETER
 *     - DRV_I2S_STATUS_OK
 */
drv_i2s_status_t drv_i2s_tx_stop_ex(
    drv_i2s_port port);

 /**
 * @brief start input to ring buffer.
 *
 *  extend with drv_i2s_rx_start
 *  record to pingpong buffer. origin 48K sample rate, if use mcu mode, down sample to 8K
 *
 * @param port Specifies the i2s port.
 * @param rate  rx rate, small or equal drv_i2s_init sample_rate rate 
 * @param handler - MCU_MODE: use mcu copy data, only have mono data, 
 *                                      drup another mono data. This mode can not run tx at same time.
 *                                      DMAC_MODE: use dmac copy data, only use dmac channel 0 or channel 8
 *
 * @return
 *     - DRV_I2S_STATUS_ERROR
 *     - DRV_I2S_STATUS_INVALID_PARAMETER
 *     - DRV_I2S_STATUS_OK
 */
drv_i2s_status_t drv_i2s_rx_start_ex(
    drv_i2s_port port,
    drv_sample_rate_t rate,
    i2s_data_handler handler);

 /**
 * @brief stop input to ring buffer.
 *
 *  extend with drv_i2s_rx_stop
 *
 * @param port Specifies the i2s port.
 *
 * @return
 *     - DRV_I2S_STATUS_INVALID_PARAMETER
 *     - DRV_I2S_STATUS_OK
 */
drv_i2s_status_t drv_i2s_rx_stop_ex(
    drv_i2s_port port);

 /**
 * @brief start loopback
 *
 *  extend with drv_i2s_loopback_start,only loopback mono data
 *
 * @param port Specifies the i2s port.
 * @param  handler - MCU_MODE: use mcu copy data DMAC_MODE: use dmac copy data, only use dmac channel 1 or channel 9
 *
 * @return
 *     - DRV_I2S_STATUS_ERROR
 *     - DRV_I2S_STATUS_INVALID_PARAMETER
 *     - DRV_I2S_STATUS_OK
 */
drv_i2s_status_t drv_i2s_loopback_start_ex(
    drv_i2s_port port,
    i2s_data_handler handler);

 /**
 * @brief stop loopback
 *
 *  extend with drv_i2s_loopback_stop
 *
 * @param port Specifies the i2s port.
 *
 * @return
 *     - DRV_I2S_STATUS_INVALID_PARAMETER
 *     - DRV_I2S_STATUS_OK
 */
drv_i2s_status_t drv_i2s_loopback_stop_ex(
    drv_i2s_port port);

// support padmux checking feature.
#define DRV_I2S_INIT_EX_HAL_I2S_0(mode, sample_rate, resolution) \
    do { \
        drv_i2s_init_ex(HAL_I2S_0, mode, sample_rate, resolution); \
        (void)PERI_IO_I2S0; \
    } while(0)

#define DRV_I2S_INIT_EX_HAL_I2S_1(mode, sample_rate, resolution) \
    do { \
        drv_i2s_init_ex(HAL_I2S_1, mode, sample_rate, resolution); \
        (void)PERI_IO_I2S1; \
    } while(0)

#define DRV_I2S_INIT_EX(I2S, mode, sample_rate, resolution) \
    DRV_I2S_INIT_EX_##I2S(mode, sample_rate, resolution);

#endif
