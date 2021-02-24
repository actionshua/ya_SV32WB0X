#ifndef _RSSI_API_H_
#define _RSSI_API_H_

#define NORMAL_PWR      0
#define GREEN_PWR       1

void drv_phy_compensation_reset();
void drv_phy_compensation_by_rssi(bool enable);
void drv_phy_rssi_reset(u8 wsid);
u8 drv_phy_rssi_aver_compen(u8 wsid, u8 rssi);
u8 drv_phy_get_ccigate();
u8 drv_phy_set_ccigate(u8 gate);
void drv_phy_rssi_compensation_function_enable(bool enable);
u8 drv_phy_get_rssi_aver(u8 wsid);
u8 drv_phy_get_lna_ctl(void);
u8 drv_phy_get_compensation_status();
u8 drv_phy_set_cci_en(u8 en);

#endif
