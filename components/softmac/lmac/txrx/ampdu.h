#ifndef __AMPDU_H__
#define __AMPDU_H__


/*******************************************************************************
 *         Include Files
 ******************************************************************************/
#include "ampdu/drv_ampdu.h"


/*******************************************************************************
 *         Defines
 ******************************************************************************/


/*******************************************************************************
 *         Enumerations
 ******************************************************************************/


/*******************************************************************************
 *         Structures
 ******************************************************************************/


/*******************************************************************************
 *         Variables
 ******************************************************************************/


/*******************************************************************************
 *         Funcations
 ******************************************************************************/
extern inline bool ampdu_get_drv_status(void);

bool ampdu_init(struct ampdu_tx_ops *ops);
s32 ampdu_reform_mpdu_to_apmdu(struct ssv6006_tx_desc *pLeading, struct ssv6006_tx_desc *pPktInfo);
void ampdu_tx_report_handler(void **pp_ampdu_tx_pkt, struct ampdu_results *ampdu_result);
void ampdu_rx_ba_handler(void **pp_rx_data, struct ampdu_results *ampdu_result);
void ampdu_tx_set_options(u16 mode, u16 value);
u32 ampdu_get_options(u16 mode);
u32 ampdu_last_tx_report(u8 wsid, u8 tid);
u32 ampdu_last_ba(u8 wsid, u8 tid);
bool ampdu_set_tx_session(u8 wsid, u8 tid, u8 ready);
bool ampdu_get_tx_session(u8 wsid, u8 tid);
#if(ENABLE_AMPDU_SW_MIB==1)
void ampdu_show_mib(u8 wsid, u8 tid);
void ampdu_reset_mib(u8 wsid, u8 tid);
void ampdu_mib_aggr_num(struct ssv6006_tx_desc *pLeading, u8 tx_sw_q_len, u8 tx_sw_total_len);
#endif
#endif /* __AMPDU_H__ */
