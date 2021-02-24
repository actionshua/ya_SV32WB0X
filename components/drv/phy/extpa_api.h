#ifndef _EXTPA_API_H_
#define _EXTPA_API_H_

bool drv_phy_check_extpa(void);

void drv_phy_init_extpa_cfg(void);

void drv_phy_set_external_pa_pin(bool val);

void drv_phy_set_external_lna_pin(bool val);

void drv_phy_init_extpa(void);

void drv_phy_update_extpa(u8 *rssi);

void drv_phy_update_extpa_ctrl_pin(void);

void drv_phy_show_extpa_status(void);

void drv_phy_set_auto_lna(bool val);

void drv_phy_extpa_compen_rssi(u8 *rssi);

s8 drv_phy_get_rssi_offset();
#endif
