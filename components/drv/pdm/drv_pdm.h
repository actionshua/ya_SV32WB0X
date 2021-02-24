
#ifndef _DRV_PDM_H_
#define _DRV_PDM_H_

#include <stdio.h>
#include <stdbool.h>
#include "soc_defs.h"

#if (CHIP_SUB_ID !=0)
typedef enum {
    DRV_PDM_TX_01KTONE = 1, 
    DRV_PDM_TX_02KTONE = 2,
    DRV_PDM_TX_03KTONE = 3,
    DRV_PDM_TX_04KTONE = 4, 
    DRV_PDM_TX_05KTONE = 5,
    DRV_PDM_TX_06KTONE = 6,
    DRV_PDM_TX_07KTONE = 7, 
    DRV_PDM_TX_08KTONE = 8,
    DRV_PDM_TX_09KTONE = 9,
    DRV_PDM_TX_10KTONE = 10, 
    DRV_PDM_TX_11KTONE = 11,
    DRV_PDM_TX_12KTONE = 12,
    DRV_PDM_TX_13KTONE = 13, 
    DRV_PDM_TX_14KTONE = 14,
    DRV_PDM_TX_15KTONE = 15,
    //DRV_PDM_TX_16KTONE = 16,  not support
} drv_pdm_tone_t;
#endif

typedef enum{
    PDM_RX_STEREO = 0,
    PDM_RX_MONO_ONLY_R = 1,
    PDM_RX_MONO_ONLY_L = 2,
    PDM_RX_MONO_L_AND_COPYTO_R = 3,
    PDM_RX_MONO_R_AND_COPYTO_L = 4,
} pdm_rx_mode_t;

typedef enum{
    PDM_TX_STEREO = 0,
    PDM_TX_MONO_ONLY_R = 1,
    PDM_TX_MONO_ONLY_L = 2,
    PDM_TX_MONO_L_AND_COPYTO_R = 3,
    PDM_TX_MONO_R_AND_COPYTO_L = 4,
} pdm_tx_mode_t;

typedef enum {
    DRV_PDM_STATUS_INVALID_PARAMETER = -2, /**< parameter error */
    DRV_PDM_STATUS_ERROR = -1, /**< status error */
    DRV_PDM_STATUS_OK = 0 /**< status ok */
} drv_pdm_status_t;

typedef enum {
    DRV_PDM_1 = 0x0,
    DRV_PDM_2 = 0x1,
    DRV_PDM_MAX = 0x2,
} drv_pdm_port;

typedef enum {
    PDM_Rx_SampleRate_8000HZ = 8000,
    PDM_Rx_SampleRate_16000HZ = 16000,
    PDM_Rx_SampleRate_22050HZ = 22050,
    PDM_Rx_SampleRate_44100HZ = 44100,
    PDM_Rx_SampleRate_48000HZ = 48000,
} pdm_rx_sample_rate_t;

typedef enum{
    PDM_TX_Bit_Depth_8 = 0,
    PDM_TX_Bit_Depth_16 = 1,
    PDM_TX_Bit_Depth_24 = 2,
} pdm_tx_bit_depth_t;

#if(CHIP_ID == 6020)

#if (CHIP_SUB_ID !=0)
#define I2S_SUPPORT_DS
#ifdef I2S_SUPPORT_DS
void pdm_downsampler_disable(
    drv_pdm_port port);

void pdm_downsampler_enable(
    drv_pdm_port port, 
    int src_sample, 
    int dest_sample);
#endif

/**
 * @brief pdm tx module tone generator enable,
 *
 * @param port Specifies the pdm module number, share i2s with the same port.
 * @param tone generator need k tone 
 * 
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
drv_pdm_status_t drv_pdm_tx_tonegen_enable(
    drv_pdm_port port,
    drv_pdm_tone_t tone);

/**
 * @brief pdm tx module tone generator disable,
 *
 * @param port Specifies the pdm module number, share i2s with the same port.
 * 
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
drv_pdm_status_t drv_pdm_tx_tonegen_disable(
    drv_pdm_port port);
#endif

/**
 * @brief pdm tx vol set
 * 
 * @param port Specifies the pdm module number, share i2s with the same port.
 * @param vol Specifies the volume [0, 64]
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
drv_pdm_status_t drv_pdm_tx_vol(
    drv_pdm_port port,
    int vol);
    
/**
 * @brief pdm module init
 *
 *  before use pdm, need call drv_i2s_init_ex
 * 
 * @param port Specifies the pdm module number, share i2s with the same port.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
drv_pdm_status_t drv_pdm_init(
    drv_pdm_port port);

/**
 * @brief pdm tx module enable, , only support i2s1 port
 *
 *  before use pdm, need call drv_i2s_init_ex
 * 
 * @param port Specifies the pdm module number, share i2s with the same port.
 * @param rate Specifies the sample rate KHZ, ex 44.1KHZ, then setting 44.1 value, [1KHZ, 51KHZ] range
 * @param depth Specifies the bit depth
 * @param mode Specifies the stereo or mono type
 * @param swapLR  1: swap L & R data 0: normal, only work at mode(PDM_TX_STEREO)
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
drv_pdm_status_t drv_pdm_tx_enable(
    drv_pdm_port port,
    float rate,
    pdm_tx_bit_depth_t depth,
    pdm_tx_mode_t mode,
    bool swapLR);

/**
 * @brief pdm tx module disable, only support i2s1 port
 *
 *  before use pdm, need call drv_i2s_init_ex
 * 
 * @param port Specifies the pdm module number, share i2s with the same port.
 * 
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
drv_pdm_status_t drv_pdm_tx_disable(
    drv_pdm_port port);

/**
 * @brief pdm rx module enable,
 *
 *  before use pdm, need call drv_i2s_init_ex
 * 
 * @param port Specifies the pdm module number, share i2s with the same port.
 * @param rate Specifies the sample rate
 * @param mode Specifies the stereo or mono type
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
drv_pdm_status_t drv_pdm_rx_enable(
    drv_pdm_port port,
    pdm_rx_sample_rate_t rate,
    pdm_rx_mode_t mode);

/**
 * @brief pdm rx module disable,
 *
 *  before use pdm, need call drv_i2s_init_ex
 * 
 * @param port Specifies the pdm module number, share i2s with the same port.
 * 
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
drv_pdm_status_t drv_pdm_rx_disable(
    drv_pdm_port port);
#endif

#endif
