#ifndef _DRV_AMPDU_H_
#define _DRV_AMPDU_H_

#include <idmanage/ssv_desc.h>

#define ENABLE_AMPDU_SW_MIB                 (0)
#define ENABLE_RESOURCES_TRACKING           (0)
#define AMPDU_SW_MAX_RETRY                  (7)

//In spec. every TID can own a ampdu sesstion, however, LWIP always pass the TID=0 to L2 driver,
//so this is just reserved for the future
#define MAX_TID_VALUE                       (1)
#define MAX_SUPPORT_STA                     (9)

enum AMPDU_TX_OPT
{
    AMPDU_TX_OPT_ENABLE, //0
    AMPDU_TX_OPT_SET_SW_MAX_RETRY,
};

enum AMPDU_TX_STATE
{
    AMPDU_TX_STATE_NOT_FINISH=0,
    AMPDU_TX_STATE_FINISH,
    AMPDU_TX_STATE_FAIL,
    AMPDU_TX_STATE_MAX,
};

struct ampdu_results {
    enum AMPDU_TX_STATE state;
    u8 ampdu_ack_len;
    u8 ampdu_len;
};

struct ampdu_tx_ops
{
    /**
     * return: 0: success, -1:fail
     */
    int (* rxmit)(void* retry_frame);
};

bool drv_ampdu_init(struct ampdu_tx_ops *ops);
s32 drv_ampdu_reform_mpdu_to_apmdu(struct ssv6006_tx_desc *pLeading,struct ssv6006_tx_desc *pPktInfo);
void drv_ampdu_tx_report_handler(void **pp_ampdu_tx_pkt, struct ampdu_results *ampdu_result);
void drv_ampdu_rx_ba_handler(void **pp_rx_data, struct ampdu_results *ampdu_result);
void drv_ampdu_tx_set_options(u16 mode, u16 value);
u32 drv_ampdu_get_options(u16 mode);
u32 drv_ampdu_last_tx_report(u8 wsid, u8 tid);
u32 drv_ampdu_last_ba(u8 wsid, u8 tid);
bool drv_ampdu_set_tx_session(u8 wsid, u8 tid, u8 ready);
bool drv_ampdu_get_tx_session(u8 wsid, u8 tid);

#if(ENABLE_AMPDU_SW_MIB==1)
void drv_ampdu_show_mib (u8 wsid, u8 tid);
void drv_ampdu_reset_mib (u8 wsid, u8 tid);
void drv_ampdu_mib_aggr_num(struct ssv6006_tx_desc *pLeading, u8 tx_sw_q_len, u8 tx_sw_total_len);
#endif
#endif /* _DRV_AMPDU_H_ */
