#ifndef _SSVRADIO_H_
#define _SSVRADIO_H_

#include "soc_types.h"
#include "radio.h"
#include "txrx/txtask.h"

#define SSV6200_MAX_PACKET_LEN     16
#define MAC_REG_WRITE(_r, _v)   hw_reg_write(_r, _v)
#define MAC_REG_READ(_r, _v)   hw_reg_read(_r, _v)

struct ssv_on3_reg {
    u32 address;
    u32 value;
};

u8 get_basedrate(void);
u8 get_basecrate(void);
int radio_rx_handler(struct ssv6006_rx_desc *rx_desc);
bool is_5g_band_support(void);
void sendto_txque(u8 wsid, void *payload);
int ssv6200_radio_send_socevent(u8 evtid, u8 *event, u16 evtlen);

#endif /* _SSVRADIO_H_ */
