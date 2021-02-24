#ifndef _TXTASK_H_
#define _TXTASK_H_


#include "soc_types.h"
#include "attrs.h"

#define MAX_WSID            (9)

/*
 * SW TX Queue
 */
typedef enum txque_stat {
    que_unlock = 0,
    que_lock,
    que_cond_unlock_uni,
    que_cond_unlock_broad,
} txque_stat;

typedef enum _en_txque_config
{
    E_TXQUE_CFG_TYPE_NONE,
    E_TXQUE_CFG_TYPE_WAITING_NUMBER,    ///< Waiting number
    E_TXQUE_CFG_TYPE_WAITING_TIME,      ///< Waiting time
    E_TXQUE_CFG_TYPE_WAITING_TIME_HT40, ///< Waiting time for HT40
    E_TXQUE_CFG_TYPE_CHECK_HWQ_NUM,     ///< Check HW queuen number
    E_TXQUE_CFG_TYPE_MAX,
}EN_TXQUE_CFG_TYPE;

typedef enum _en_txque_event
{
    E_TXQUE_EVENT_TYPE_NONE,
    E_TXQUE_EVENT_TYPE_FIRST_SEND,      ///< For 1st packet
    E_TXQUE_EVENT_TYPE_NORMAL_SEND,     ///< After 1st packet
    E_TXQUE_EVENT_TYPE_MAX,
}EN_TXQUE_EVENT_TYPE;


struct tx_queue_element
{
    u32 *pkt_addr;
    struct tx_queue_element *next;
};

typedef struct txque_pkyinfo {
    u32 *pkt_addr;
    u8 bssid;
    u8 wsid;
} txque_pkyinfo;

struct tx_queue
{
    struct tx_queue_element *head;
    struct tx_queue_element *last;
    txque_stat que_stat;
    u32 number;
    u32 max_number;
    u32 count;
    u32 last_time;
    u32 last_status_change_time;
};

typedef struct _st_txque_config
{
    u32 u32WaitNum;
    u32 u32WaitTime;
    u32 u32WaitTimeHt40;
    u32 u32ChkHwqNum;
}ST_TXQUE_CONFIG;


void txque_init();
void txque_status_changing(u8 wsid, u8 powerstat) ATTRIBUTE_SECTION_FAST_L2STACK;
u32 get_txque_last_status_change_time(u8 wsid);
txque_stat get_txque_status(u8 wsid);
u16 get_txque_len(u8 wsid);
void txque_pushevent(EN_TXQUE_EVENT_TYPE eType);
void txque_release(u8 wsid);
struct tx_queue * getque_bywsid(u8 wsid);
void txque_set_status(struct tx_queue *que, txque_stat stat);
void txque_set_status_by_wsid(u8 wsid, txque_stat stat);
u8 check_trigger_broadcastque(void);
bool txque_setconfig(EN_TXQUE_CFG_TYPE eType, u32 u32Val);
#endif /* _TXTASK_H_ */
