#ifndef _BLE_DTM_H_
#define _BLE_DTM_H_

u8 ble_dtm_tx(u8 rfch ,u16 pkt_cnt, u8 pkt_len ,u8 pld_tp);
u8 ble_dtm_rx(u8 rfch);
u8 ble_dtm_end(u16 * pkt_cnt, u16 * err_cnt);
u8 ble_dtm_reset();

#endif
