#ifndef _RF_API_H_
#define _RF_API_H_

#include "rf_table.h"

enum{
    EN_NORMAL_TEMPERATURE_STATE=0,
    EN_HIGH_TEMPERATURE_STATE=1,
    EN_LOW_TEMPERATURE_STATE=2,
}EN_TEMPERATURE_STATE;

enum{
    EN_BLE_HOST = 0,
    EN_BLE_DTM = 1,
    EN_BLE_UART = 2,
}EN_BLE_MODE;

int dump_rf_value();
int dump_rf_table();
int build_default_rf_table(struct st_rf_table *pTable);
void stop_temepature_compensation_timer(void);
void start_temepature_compensation_timer(void);
int load_rf_table_to_mac(struct st_rf_table *pTable);
int rf_table_get_rate_gain_idx_by_value(u32 value);
int rf_table_get_band_gain_idx_by_value(u32 value);
int get_current_temperature(int *pvalue);
int get_current_tempe_state(int *pTempState, int *pTempValue);
int check_rate_gain_value(struct st_rate_gain rate_gain, uint8_t flag);
uint32_t flag_to_mask(uint8_t flag);
int write_reg_band_gain(uint8_t gain_index);
int write_reg_freq_xi_xo(uint8_t xi, uint8_t xo, uint8_t mask);
int write_reg_rxfe(uint8_t rxafe);
int write_reg_dcdc(uint8_t dcdc);
int write_reg_xoldo(uint8_t xoldo);
int write_reg_rxpad_ch13(uint8_t bflag);
int write_reg_wfble(uint8_t wfble);
int write_reg_ldo(uint8_t dcdcv, uint8_t dldov, uint32_t mask);
int write_reg_2gpa(uint8_t vcas1, uint8_t vcas2, uint8_t vcas3, uint8_t bias, uint32_t mask);
int write_reg_2gpa_cap(uint8_t pa_cap);
int write_reg_2gpa_cell(uint8_t pa_cell);
int write_reg_padpd_cali(uint8_t padpd_cali);
int write_reg_tempe_table(struct st_tempe_table config);
void rf_ble_enable(uint8_t enable);
void write_ble_power_dec(uint8_t power_dec);
void SetBlePower(u8 ch, int target_state, u8 showmsg);
u8 GetBleChannelVariable(void);
void SetBleChannelVariable(u8 blech);
u8 convert_ble_channel_to_freq(u8 ble_ch);
int write_reg_rf_gain(uint8_t gain_index);
int write_reg_rate_gain_b(uint8_t gain_b);
int write_reg_rate_gain_g(struct st_rate_gain rate_g, uint8_t wrk_flag);
int write_reg_rate_gain_20n(struct st_rate_gain rate_20n, uint8_t wrk_flag);
int write_reg_rate_gain_40n(struct st_rate_gain rate_40n, uint8_t wrk_flag);
int write_reg_rf_table_ex(struct st_rf_table *p_table);
int write_reg_rate_gain_from_rf_table(void);
int write_reg_rf_table();
int set_temper_value(uint8_t low, uint8_t high);
int rf_tx_start(int count, int interval);
int rf_set_ch(int32_t ch, uint8_t withRFDisable , uint32_t ch_type);
int rf_set_rate(int rate_id);
int rf_set_packet_len(uint32_t len);
int rf_tx_stop();
int rf_rx_reset();
int rf_rx_reset_ex(int rx_mode);
int rf_bmode_count(uint32_t *total_count, uint32_t *err_count);
int rf_gmode_count(uint32_t *total_count, uint32_t *err_count);
int rf_get_rssi(uint8_t *rssi);
int rf_freqoffset_readxo(uint32_t *xo_value);
int rf_freqoffset_readxi(uint32_t *xi_value);
int rf_manu_padpd_cali();
int rf_enable_tcsr(uint8_t enable);
int rf_set_ch_ht40(int32_t ch_ht40);
#if 1
int write_reg_5g_bbscale_5100(uint8_t scale);
int write_reg_5g_bbscale_5500(uint8_t scale);
int write_reg_5g_bbscale_5700(uint8_t scale);
int write_reg_5g_bbscale_5900(uint8_t scale);
int write_reg_5g_bias1(uint32_t reg_value);
int write_reg_5g_bias2(uint32_t reg_value);
int write_reg_5g_band_threshold(uint16_t thr_f0, uint16_t thr_f1, uint16_t thr_f2);
int write_reg_tempe_5g_table(struct st_tempe_5g_table config);
int write_reg_extpadpd(void);
int read_reg_extpadpd(void);
#endif

int rf_tone_gen(uint8_t bStart);

int read_reg_band_gain_config(u8 *value);
int read_reg_5g_bbscale_5100_config(u8 *value);
int read_reg_5g_bbscale_5500_config(u8 *value);
int read_reg_5g_bbscale_5700_config(u8 *value);
int read_reg_5g_bbscale_5900_config(u8 *value);
int read_reg_freq_offset_config(u8 *freq_xi, u8 *freq_xo);

int write_reg_5g_bias1(uint32_t reg_value);
int write_reg_5g_bias2(uint32_t reg_value);    
int write_reg_5g_three_bias(uint32_t rt_bias1, uint32_t ht_bias1, uint32_t lt_bias1);
int write_reg_5g_band_threshold(uint16_t thr_f0, uint16_t thr_f1, uint16_t thr_f2);
int write_reg_tempe_5g_table(struct st_tempe_5g_table config);
int rf_tone_gen(uint8_t bStart);

u8 rf_get_dcdc_flag(void);
u8 rf_get_padpd_flag(void);
u8 rf_get_tx_lowpower_flag(void);

bool rf_get_extpa_flag(void);
void rf_get_extlna_trigger(bool *tri_5G, bool *tri_2G);
void rf_get_extpa_2G_rssi_offset(s8 *p_offset, s8 *n_offset);
void rf_get_extpa_5G_rssi_offset(s8 *p_offset, s8 *n_offset);
uint8_t get_ble_dtm_enable();
u8 rf_get_extpadpd_flag(void);

#if defined(FEATURE_RTC32K_XTAL_SUPPORT) && (FEATURE_RTC32K_XTAL_SUPPORT == 1)
uint8_t rf_get_rtc32k_xtal();
#endif
#endif
