#ifndef __TXRX_UTILS_H__
#define __TXRX_UTILS_H__


/*******************************************************************************
 *         Include Files
 ******************************************************************************/


/*******************************************************************************
 *         Defines
 ******************************************************************************/
#define DEF_TXRX_STAT_NUM      (256)


/*******************************************************************************
 *         Enumerations
 ******************************************************************************/
typedef enum _en_txrx_stat_ctrl
{
    E_TXRX_STAT_CTRL_NONE = 0,
    E_TXRX_STAT_CTRL_MODE = 1,
    E_TXRX_STAT_CTRL_ENABLE = 2,
    E_TXRX_STAT_CTRL_DISABLE = 3,
    E_TXRX_STAT_CTRL_SHOW = 4,
    E_TXRX_STAT_CTRL_MAX = 0xFFFF,
} EN_TXRX_STAT_CTRL;

typedef enum _en_txrx_stat_mode
{
    E_TXRX_STAT_MODE_NONE = 0,
    E_TXRX_STAT_MODE_TX = 1,
    E_TXRX_STAT_MODE_RX = 2,
    E_TXRX_STAT_MODE_MAX = 0xFFFF,
} EN_TXRX_STAT_MODE;

typedef enum _en_txrx_stat
{
    E_TXRX_STAT_CFG_NONE = 0,
    E_TXRX_STAT_CFG_INFO_NUM = 1,
    E_TXRX_STAT_CFG_INFO_IDX = 2,
    E_TXRX_STAT_CFG_RX_LAST_SEQ = 3,
    E_TXRX_STAT_CFG_TX_LAST_SEQ = 4,
    E_TXRX_STAT_CFG_TX_LAST_AGGRNUM = 5,
    E_TXRX_STAT_CFG_MODE_SETTING = 6,
    E_TXRX_STAT_CFG_RX_BUFQ_ADDR = 7,
    E_TXRX_STAT_CFG_TX_LAST_TIMESTAMP = 8,
    E_TXRX_STAT_CFG_MAX = 0xFFFF,
} EN_TXRX_STAT_CFG;


/*******************************************************************************
 *         Structures
 ******************************************************************************/
typedef struct _st_txrx_stat_info
{
    u16 u16RxSeq;
    u16 u16TxSeq;
    u16 u16TxUsedPage;
    u8 u8RxMsgNum;
    u8 u8TxSwQNum;
    u8 u8TxHwQNum;
    u8 u8TxAggrNum;
    u32 u32TxTimeStamp;
}__attribute__ ((packed)) ST_TXRX_STAT_INFO;

typedef struct _st_txrx_stat_cfg
{
    EN_TXRX_STAT_MODE eTxRxStatMode;
    u32 u32InfoNum;
    u32 u32InfoSize;
    u32 u32InfoIdx;
    OsBufQ pRxBufQ;
    u16 u16RxLastSeq;
    u16 u16TxLastSeq;
    u8 u8TxLastAggrNum;
    u32 u32TxLastTimeStamp;
    bool bTxRxStatEn;
}__attribute__ ((packed)) ST_TXRX_STAT_CFG;


/*******************************************************************************
 *         Variables
 ******************************************************************************/


/*******************************************************************************
 *         Funcations
 ******************************************************************************/
bool txrx_stat_is_enable(void);
s32 txrx_stat_ctrl(EN_TXRX_STAT_CTRL eType, u32 u32Val);
s32 txrx_stat_store_info(EN_TXRX_STAT_MODE eMode);
u32 txrx_stat_get_val(EN_TXRX_STAT_CFG eType);
s32 txrx_stat_set_val(EN_TXRX_STAT_CFG eType, u32 u32Val);
#endif /* __AMPDU_H__ */
