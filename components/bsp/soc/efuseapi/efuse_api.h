#ifndef EFUSE_API_H
#define EFUSE_API_H

int efuse_read_mac(uint8_t *mac_addr);
int efuse_read_mac_inc(uint8_t *mac_addr);

int rf_efuse_read_chip_id(uint32_t* p_chip_id);
int rf_efuse_read_mac(uint8_t* mac);
int rf_efuse_write_mac(uint8_t* mac);
int rf_efuse_write_tx_power1(uint8_t gain5200, uint8_t gain2000);
int rf_efuse_read_tx_power1(uint8_t* gain5200, uint8_t* gain2000);
int rf_efuse_write_xtal(uint8_t xtal);
int rf_efuse_read_xtal(uint8_t* xtal);
int rf_efuse_write_rate_gain_b_n40(uint8_t gain_b, uint8_t gain_n40);
int rf_efuse_read_rate_gain_b_n40(uint8_t* gain_b, uint8_t* gain_n40);
int rf_efuse_write_rate_gain_g_n20(uint8_t gain_g, uint8_t gain_n20);
int rf_efuse_read_rate_gain_g_n20(uint8_t* gain_g, uint8_t* gain_n20);
int rf_efuse_write_ble_power(uint8_t ble_power);
int rf_efuse_read_ble_power(uint8_t* ble_power);

int rf_efuse_check_item_free(uint8_t item);


#endif 
