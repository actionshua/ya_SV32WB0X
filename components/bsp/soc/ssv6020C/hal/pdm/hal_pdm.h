
#ifndef _HAL_PDM_H_
#define _HAL_PDM_H_

#include "soc_defs.h"
#include "soc_types.h"

typedef enum {
    HAL_PDM_STATUS_INVALID_PARAMETER = -2, /**< parameter error */
    HAL_PDM_STATUS_ERROR = -1, /**< status error */
    HAL_PDM_STATUS_OK = 0 /**< status ok */
} hal_pdm_status_t;

typedef enum {
    HAL_PDM_RX_1 = 0x0,
    HAL_PDM_RX_2 = 0x1,
    HAL_PDM_RX_MAX
} hal_pdm_rx_port;

typedef enum {
    HAL_PDM_ONLY_L = 0,
    HAL_PDM_ONLY_R = 1,
    HAL_PDM_L_COPY_TO_R = 2,
    HAL_PDM_R_COPY_TO_L = 3
} hal_pdm_mono_ctl_t;

typedef enum{
    PDM_TX_40D00M = 0,
    PDM_TX_20D00M = 1,
    PDM_TX_13D33M = 2,
    PDM_TX_10D00M = 3,//default
    PDM_TX_08D00M = 4,
    PDM_TX_06D67M = 5,
    PDM_TX_05D71M = 6,
    PDM_TX_05D00M = 7,
    PDM_TX_04D44M = 8,
    PDM_TX_04D00M = 9,
    PDM_TX_03D64M = 10,
    PDM_TX_03D33M = 11,
    PDM_TX_03D08M = 12,
    PDM_TX_02D86M = 13,
    PDM_TX_02D67M = 14,
    PDM_TX_02D50M = 15,
    PDM_TX_02D35M = 16,
    PDM_TX_02D22M = 17,
    PDM_TX_02D11M = 18,
    PDM_TX_02D00M = 19,
    PDM_TX_01D90M = 20,
    PDM_TX_01D82M = 21,
    PDM_TX_01D74M = 22,
    PDM_TX_01D67M = 23,
    PDM_TX_01D60M = 24,
    PDM_TX_01D54M = 25,
    PDM_TX_01D48M = 26,
    PDM_TX_01D43M = 27,
    PDM_TX_01D38M = 28,
    PDM_TX_01D33M = 29,
    PDM_TX_01D29M = 30,
    PDM_TX_01D25M = 31,
} hal_pdm_tx_out_bw;

typedef enum{
    PDM_TX_VOL_BW_400K = 0,
    PDM_TX_VOL_BW_200K = 1,
    PDM_TX_VOL_BW_100K = 2,
    PDM_TX_VOL_BW_50K = 3,//default
    PDM_TX_VOL_BW_25K = 4,
    PDM_TX_VOL_BW_12D5K = 5,
    PDM_TX_VOL_BW_6D25K = 6,
    PDM_TX_VOL_BW_3D125K = 7,
} hal_pdm_tx_slf;

typedef enum{
    PDM_RX_4D00M = 40,
    PDM_RX_3D20M = 50,//default
    PDM_RX_2D50M = 64,
    PDM_RX_2D00M = 80,
    PDM_RX_1D60M = 100,
    PDM_RX_1D25M = 128,
    PDM_RX_0D80M = 200,
} hal_rx_clk;


typedef enum {
    HAL_PDM_OFFSET_0_NSEC = 0,
    HAL_PDM_OFFSET_6_NSEC = 1,
    HAL_PDM_OFFSET_12_NSEC = 2,
    HAL_PDM_OFFSET_18_NSEC =3
} hal_pdm_rx_phase_offset_t;

/**
 * @brief pdm tx mask enable.
 *
 */
void hal_pdm_tx_mask_enable(void);

/**
 * @brief pdm tx module enable.
 *
 */
void hal_pdm_tx_ch_enable(void);

/**
 * @brief pdm tx module disable.
 *
 */
void hal_pdm_tx_ch_disable(void);

/**
 * @brief pdm tx module msb inv enable, ex: pcm value is unsigned.
 *
 */
void hal_pdm_tx_msb_inv_enable(void);

/**
 * @brief pdm tx module msb inv disable, ex: pcm value is unsigned.
 *
 */
void hal_pdm_tx_msb_inv_disable(void);

/**
 * @brief pdm tx module stereo enable.
 *
 */
void hal_pdm_tx_stereo_enable(void);

/**
 * @brief pdm tx module stereo disable.
 *
 */
void hal_pdm_tx_stereo_disable(void);

/**
 * @brief setting pdm tx module bit resoultion.
 *
 * @param bit Specifies the pdm bit resoultion.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_tx_bit_res_set(
    uint32_t bit);

/**
 * @brief setting pdm tx module mono crtl.
 *
 * @param ctl  mono data, have four mode, only L, only R, L and copy to R, R and copy to L
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_tx_mono_crtl(
    hal_pdm_mono_ctl_t ctl);

/**
 * @brief setting pdm tx module bandwidth.
 *
 * @param bw Specifies the pdm bandwidth.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_tx_out_bw_set(
    hal_pdm_tx_out_bw bw);

/**
 * @brief pdm tx module swap L&R enable, only use in stereo data.
 *
 */
void hal_pdm_tx_swapLR_enable(void);

/**
 * @brief pdm tx module swap L&R disable, only use in stereo data.
 *
 */
void hal_pdm_tx_swapLR_disable(void);

/**
 * @brief setting pdm tx module k value.
 *
 * @param k Specifies the pdm k value.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_tx_resamp_k_set(
    uint32_t k);

/**
 * @brief setting pdm tx module n value.
 *
 * @param n Specifies the pdm n value.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_tx_resamp_n_set(
    uint32_t n);

/**
 * @brief setting pdm tx module m value.
 *
 * @param m Specifies the pdm m value.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_tx_resamp_m_set(
    uint32_t m);

/**
 * @brief setting pdm tx module inv_m_mant value.
 *
 * @param inv_m_mant Specifies the pdm inv_m_mant value.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_tx_resamp_inv_m_mant_set(
    uint32_t inv_m_mant);

/**
 * @brief setting pdm tx module inv_m_exp value.
 *
 * @param inv_m_exp Specifies the pdm inv_m_exp value.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_tx_resamp_inv_m_exp_set(
    uint32_t inv_m_exp);

/**
 * @brief setting pdm tx module out_scaling value.
 *
 * @param out_scaling Specifies the pdm out_scaling value, equal volume +/-.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_tx_amp_out_scaling_set(
    uint32_t out_scaling);

/**
 * @brief setting pdm tx module smooth value.
 *
 * @param smooth Specifies the pdm smooth value.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_tx_scaling_leaky_factor_set(
    hal_pdm_tx_slf smooth);

/**
 * @brief pdm rx mask enable.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_mask_enable(
    hal_pdm_rx_port port);

/**
 * @brief pdm rx module enable.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_ch_enable(
    hal_pdm_rx_port port);

/**
 * @brief pdm rx module disable.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_ch_disable(
    hal_pdm_rx_port port);

/**
 * @brief pdm rx low power enable.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_lpow_enable(
    hal_pdm_rx_port port);

/**
 * @brief pdm rx low power disable.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_lpow_disable(
    hal_pdm_rx_port port);

/**
 * @brief pdm rx module stereo enable.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_stereo_enable(
    hal_pdm_rx_port port);

/**
 * @brief pdm rx module stereo disable.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_stereo_disable(
    hal_pdm_rx_port port);

/**
 * @brief pdm rx module loopback enable.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_loopback_enable(
    hal_pdm_rx_port port);

/**
 * @brief pdm rx module loopback disable.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_loopback_disable(
    hal_pdm_rx_port port);

/**
 * @brief pdm rx module echo enable.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_echo_enable(
    hal_pdm_rx_port port);

/**
 * @brief pdm rx module echo disable.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_echo_disable(
    hal_pdm_rx_port port);

/**
 * @brief setting pdm rx module data align.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 * @param msb_en: 1 MSB aligned. 0: LSB aligned,   
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_data_bit_align(
    hal_pdm_rx_port port,
    bool msb_en);

/**
 * @brief setting pdm rx module manual phase offset.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 * @param clk Specifies the pdm rx clock, ex: PDM_RX_2D50M equal 2.5MHZ.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_phase_cycle_set(
    hal_pdm_rx_port port,
    hal_rx_clk clk);

/**
 * @brief setting pdm rx module k value.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 * @param k Specifies the k vaule.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_resamp_k_set(
    hal_pdm_rx_port port,
    uint32_t k);

/**
 * @brief setting pdm rx module n value.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 * @param n Specifies the n vaule.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_resamp_n_set(
    hal_pdm_rx_port port,
    uint32_t n);

/**
 * @brief setting pdm rx module m value.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 * @param m Specifies the m vaule.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_resamp_m_set(
    hal_pdm_rx_port port,
    uint32_t m);

/**
 * @brief setting pdm rx module inverter m mant value.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 * @param inv_m_mant Specifies the inv_m_mant vaule.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_resamp_inv_m_mant_set(
    hal_pdm_rx_port port,
    uint32_t inv_m_mant);

/**
 * @brief setting pdm rx module inverter m exp value.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 * @param inv_m_exp Specifies the inv_m_exp vaule.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_resamp_inv_m_exp_set(
    hal_pdm_rx_port port,
    uint32_t inv_m_exp);

/**
 * @brief setting pdm rx module scale value.
 *
 * @param port Specifies the pdm module number, share i2s with the same port.
 * @param scale Specifies the scale vaule.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_rx_fir_lpf_ds4x_scale_set(
    hal_pdm_rx_port port,
    uint32_t scale);

/**
 * @brief pdm tone generator enable.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 * @param rate  fs * rate/65536 =  need tone
 * @param fs 0: 32K, 1: 44.1K, 2: 48K, 3: 96K.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_ctl_tonegen_enable(
    hal_pdm_rx_port port,
    uint16_t rate,
    uint16_t fs);

/**
 * @brief pdm tone generator disable.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_ctl_tonegen_disable(
    hal_pdm_rx_port port);

/**
 * @brief pdm rx phase offset.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 * @param offset before offset time, fetch data
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_ctl_phase_offset(
    hal_pdm_rx_port port,
    hal_pdm_rx_phase_offset_t offset);

/**
 * @brief pdm tx mono control.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 * @param ctl  mono data, have four mode, only L, only R, L and copy to R, R and copy to L
 *
 * @return
 *     - HAL_PDM_STATUS_INVALID_PARAMETER
 *     - HAL_PDM_STATUS_OK
 */
int32_t hal_pdm_ctl_rx_mono_ctl(
    hal_pdm_rx_port port,
    hal_pdm_mono_ctl_t ctl);

/**
 * @brief pdm tx module downsample path enable
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 *
 */
hal_pdm_status_t hal_pdm_ctl_rx_ds_enable(
    hal_pdm_rx_port port);

/**
 * @brief pdm tx module downsample path disable.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 *
 */
hal_pdm_status_t hal_pdm_ctl_rx_ds_disable(
    hal_pdm_rx_port port);

#endif  // #ifndef _HAL_ADC_H_

