#ifndef _HAL_I2S_H_
#define _HAL_I2S_H_

#include "soc_types.h"

typedef enum {
    I2S_NORMAL = 0,
    I2S_LEFT = 1,
    I2S_MAX
} i2s_format;

typedef enum {
    HAL_I2S_0 = 0x0,
    HAL_I2S_1 = 0x1,
    HAL_I2S_MAX,
} hal_i2s_port;

typedef enum{
    SampleRate_8000HZ = 8000,
    SampleRate_11025HZ = 11025,
    SampleRate_16000HZ = 16000,
    SampleRate_22050HZ = 22050,
    SampleRate_24000HZ = 24000,
    SampleRate_44100HZ = 44100,
    SampleRate_48000HZ = 48000,
} sample_rate_t;

typedef enum{
    lr_cnt_16 = 0,
    lr_cnt_24 = 1,
    lr_cnt_32 = 2
} lr_cnt_t;

typedef enum{
    Resolution_nobit = 0,
    Resolution_12bit = 1,
    Resolution_16bit = 2,
    Resolution_20bit = 3,
    Resolution_24bit = 4,
    Resolution_32bit = 5,
} bit_resolution_t;

typedef enum{
    mode_master = 0,
    mode_slave = 1
} i2s_mode_t;

enum i2s_mclk_option {
    mclk_80MHz  = 2,
    mclk_32MHz  = 5,
    mclk_16MHz  = 10,
    mclk_11MHz  = 14, //real mclk is 11.428571MHZ
    mclk_8MHz  = 20,
};

enum i2s_int {
    I2S_RX_FIFO_AVAILABLE = 0x1,
    I2S_RX_FIFO_OVERFLOW = 0x2,
    I2S_TX_FIFO_LOW = 0x10,
    I2S_TX_FIFO_OVERFLOW = 0x20,
};

/**
 * @brief get pdm rx module enable status.
 *
 * @param port Specifies the rx pdm port, share i2s with the same port.
 *
 * @return
 *     - true
 *     - false
 */
bool hal_get_pdm_rx_ch_enable_status(
    hal_i2s_port port);

/**
 * @brief enable i2s interface with specifies port
 *
 * @param port Specifies the i2s port
 *
 */
void hal_i2s_enable(
    hal_i2s_port port);

/**
 * @brief enable i2s rx interface with specifies port
 *
 *  before use hal_i2s_rx_enable, need call hal_i2s_enable
 * 
 * @param port Specifies the i2s port
 *
 */
void hal_i2s_rx_enable(
    hal_i2s_port port);

/**
 * @brief enable i2s tx interface with specifies port
 *
 *  before use hal_i2s_tx_enable, need call hal_i2s_enable
 * 
 * @param port Specifies the i2s port
 *
 */
void hal_i2s_tx_enable(
    hal_i2s_port port);

/**
 * @brief disable i2s interface with specifies port
 * 
 * @param port Specifies the i2s port
 *
 */
void hal_i2s_disable(
    hal_i2s_port port);

/**
 * @brief disable i2s rx interface with specifies port
 * 
 * @param port Specifies the i2s port
 *
 */
void hal_i2s_rx_disable(
    hal_i2s_port port);

/**
 * @brief disable i2s tx interface with specifies port
 * 
 * @param port Specifies the i2s port
 *
 */
void hal_i2s_tx_disable(
    hal_i2s_port port);

/**
 * @brief setting and enable i2s MCLK & bit clock
 * 
 * @param port Specifies the i2s port
 * @param clk_divider Specifies the bit clock, bit clock = MCLK / clk_divider
 * @param tx mclk_opt Specifies the MCLK, MCLK = 160MHZ/ mclk_pot
 *
 */
void hal_i2s_clk_enable(
    hal_i2s_port port,
    uint16_t clk_divider,
    enum i2s_mclk_option mclk_opt);

/**
 * @brief setting and enable i2s MCLK & bit clock
 * 
 * @param port Specifies the i2s port
 * @param fmt Specifies the i2s format,  normal mode or left justified
 * @param i2s_bclk_intg Specifies the bit clock, bit clock = MCLK /(i2s_bclk_intg + i2s_bclk_frac_real)
 * @param i2s_bclk_frac (i2s_bclk_frac_real * 2^ 16) = i2s_bclk_frac
 * @param mclk_opt Specifies the MCLK, MCLK = 160MHZ/ mclk_pot
 *
 */
void hal_i2s_exclk_enable(
    hal_i2s_port port,
    i2s_format fmt,
    uint16_t i2s_bclk_intg,
    uint16_t i2s_bclk_frac,
    enum i2s_mclk_option mclk_opt);

/**
 * @brief disable i2s MCLK & bit clock
 * 
 * @param port Specifies the i2s port
 *
 */
void hal_i2s_clk_disable(
    hal_i2s_port port);

/**
 * @brief setting specifies i2s interrupt type
 * 
 * @param port Specifies the i2s port
 * @param i2s_int Specifies the interrupt type
 *
 */
void hal_i2s_set_intr_mask(
    hal_i2s_port port,
    enum i2s_int);

/**
 * @brief clear specifies i2s interrupt type
 * 
 * @param port Specifies the i2s port
 * @param i2s_int Specifies the interrupt type
 *
 */
void hal_i2s_clr_intr_mask(
    hal_i2s_port port,
    enum i2s_int);

/**
 * @brief setting specifies i2s word select width
 * 
 * @param port Specifies the i2s port
 * @param lr_cnt Specifies word select width
 * @param tx Specifies bit resolution with tx
 * @param rx Specifies bit resolution with rx
 *
 */
void hal_i2s_set_word_select_width(
    hal_i2s_port port,
    lr_cnt_t lr_cnt,
    bit_resolution_t tx,
    bit_resolution_t rx);

/**
 * @brief setting i2s rx fifo threshold
 * 
 * @param port Specifies the i2s port
 * @param rx_threshold Specifies the rx threshold
 *
 */
void hal_i2s_set_rx_fifo_threshold(
    hal_i2s_port port,
    uint8_t rx_threshold);

/**
 * @brief setting i2s tx fifo threshold
 * 
 * @param port Specifies the i2s port
 * @param rx_threshold Specifies the tx threshold
 *
 */
void hal_i2s_set_tx_fifo_threshold(
    hal_i2s_port port,
    uint8_t tx_threshold);

/**
 * @brief cpu manual mode, i2s tx data
 * 
 * @param port Specifies the i2s port
 * @param tx Specifies the tx data
 *
 */
extern uint32_t I2S_TX_ADDR[HAL_I2S_MAX];
static inline void hal_i2s_tx(hal_i2s_port port, uint32_t tx) __attribute__((always_inline));
static inline void hal_i2s_tx(hal_i2s_port port, uint32_t tx) {
    (*((volatile uint32_t *)I2S_TX_ADDR[port])) = tx;
}

/**
 * @brief cpu manual mode, i2s rx data
 * 
 * @param port Specifies the i2s port
 *
 */
extern uint32_t I2S_RX_ADDR[HAL_I2S_MAX];
static inline volatile uint32_t hal_i2s_rx(hal_i2s_port port) __attribute__((always_inline));
static inline volatile uint32_t hal_i2s_rx(hal_i2s_port port) {
    return (*((volatile uint32_t *)I2S_RX_ADDR[port]));
}

/**
* @brief before use any i2s&pdm api, need call enable clock
*
*/
void hal_i2s_enable_clock();

/**
* @brief after not use any i2s&pdm api, user can call disable clock
*
*/
void hal_i2s_disable_clock();

#endif  // #ifndef _HAL_ADC_H_

