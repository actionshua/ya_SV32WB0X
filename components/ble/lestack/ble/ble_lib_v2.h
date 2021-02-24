#ifndef _BLE_LIB_V2_H_
#define _BLE_LIB_V2_H_

#include "ssv_types.h"

#define ACL_TX_TYPE 1
/**
 * addr
 *
 */
#define BLE_ADDR_TYPE_PUBLIC    0
#define BLE_ADDR_TYPE_RANDOM    1

#define BLE_ADDR_SIZE 6
typedef struct ble_addr {

    union {
        u8  val     [BLE_ADDR_SIZE];
        u16 val_u16 [BLE_ADDR_SIZE >> 1];
    };
    u8  type;

} ble_addr_st;

#define ble_addr_equal(x, y) (\
    ((x).val_u16[0] == (y).val_u16[0]) && \
    ((x).val_u16[1] == (y).val_u16[1]) && \
    ((x).val_u16[2] == (y).val_u16[2]) && \
    ((x).type       == (y).type))

/**
 * channel
 *
 */
#define BLE_DATACH_MAP_SIZE  5
typedef union ble_datach_map {

    struct {
        u8  used[BLE_DATACH_MAP_SIZE];
        u8  used_num;
    };
    u64 used_u64    :(BLE_DATACH_MAP_SIZE *8);

} ble_datach_map_st;

#define BLE_DATACH_CLASS_IS_BAD     0
#define BLE_DATACH_CLASS_IS_UNKNOWN 1
typedef u64 ble_datach_class;

//#define BLE_ADVCH_CH_MIN    37
//#define BLE_ADVCH_CH_MAX    39
u8 g_ble_adv_ch_min;
u8 g_ble_adv_ch_max;
#define BLE_ADVCH_CH_NUM    (g_ble_adv_ch_max - g_ble_adv_ch_min + 1)

#define BLE_DATACH_CH_MIN    0
#define BLE_DATACH_CH_MAX    36
#define BLE_DATACH_CH_NUM   (BLE_DATACH_CH_MAX -BLE_DATACH_CH_MIN +1)

void ble_datach_map_init(ble_datach_map_st *ch_map);

/**
 * cypher
 *
 */
#define BLE_CYPHER_DATA_WORDS   4
#define BLE_CYPHER_DATA_SIZE    (BLE_CYPHER_DATA_WORDS << 2)
#define BLE_CYPHER_KEY_WORDS    BLE_CYPHER_DATA_WORDS
#define BLE_CYPHER_KEY_SIZE     BLE_CYPHER_DATA_SIZE

typedef union ble_ll_cypher_data {

    u32 val_w[BLE_CYPHER_DATA_WORDS];
    u8  val  [BLE_CYPHER_DATA_SIZE ];

} ble_ll_cypher_data_un;

typedef struct ble_data_length {
    u16 data_pdu_max_txlen;
    u16 data_pdu_max_txtime;
    u16 data_pdu_max_rxlen;
    u16 data_pdu_max_rxtime;
    u16 data_own_pdu_trxlen;
    u16 data_own_pdu_trxtime;
    u16 data_peer_pdu_rxlen;
    u16 data_peer_pdu_rxtime;
    u16 data_peer_pdu_txlen;
    u16 data_peer_pdu_txtime;
} ble_data_length_st;


typedef ble_ll_cypher_data_un ble_ll_cypher_key_un;

/**
 * unit
 *  - time
 *  - power
 *
 */
typedef u16 BLE_LL_PPM;
#define BLE_LL_PPM(_PPM_)   ((BLE_LL_PPM)(_PPM_))

typedef u8 BLE_PWR_DBM;
#define BLE_PWR_DBM(_PWR_)  ((BLE_PWR_DBM)(_PWR_))

/**
 * pdu structure
 *
 */
#define BLE_PDU_HDR_SIZE    2
#define BLE_PDU_LOG_SIZE    8
#if ((CHIP_ID==6020) && (CHIP_SUB_ID==2))
#define BLE_HCI_ACL_SIZE    251
#define BLE_PDU_PLD_SIZE    255
#else
#define BLE_HCI_ACL_SIZE    27
#define BLE_PDU_PLD_SIZE    37
#endif
typedef struct ble_pdu {

    struct ble_pdu* next;

    // configuration
    u32 cfg;

    // log
    u8  log[BLE_PDU_LOG_SIZE]; // this log may be defined differently on different layer

    // header
    u8  hdr0;
    union {
        u8  pld_len;
        u8  hdr1;
    };

    // pld
    u8  pld[BLE_PDU_PLD_SIZE];
    u8  reserved[3]; //used for four byte alignment
} ble_pdu_st;

/**
 * l2cap pdu structure
 *
 */
#define BLE_L2CAP_PDU_PLD_SIZE (BLE_PDU_PLD_SIZE -4)
typedef struct ble_l2cap_pdu {

    struct ble_pdu* next;

    // configuration, may not used in l2cap
    u32 cfg;

    // log, may not used in l2cap
    u8 log[BLE_PDU_LOG_SIZE];

    // hci(ll) header
    u8  pb_flag;        // owner l2cap, follow SIG defintion
    u8  hci_pld_len;    // pld_len + 4 (l2cap hdr)
                        // tx: owner l2cap
                        // rx: owner (hci/ll)

    // l2cap header
    u16 pld_len;        // valid pld size
                        // tx: owner att/l2cap/profile
                        // rx: owner l2cap
    u16 l2cap_ch;       // owner l2cap

    // l2cap pld
    u8  pld[BLE_L2CAP_PDU_PLD_SIZE];

} ble_l2cap_pdu_st;


/**
 * ble pdu_pool, operation within critical section
 *
 */
typedef struct ble_pdu_pool {

    void*   head;
    u32     pdu_size;
    u32     size;
    u32     alloced;
} ble_pdu_pool_st;

#define HCL_ACL_BUFFER_SIZE 8
struct buf_list_hdr
{
    /// Pointer to the next element in the list
    struct buf_list_hdr *next;
};

struct buf_list
{
    /// pointer to first element of the list
    struct buf_list_hdr *first;
    /// pointer to the last element
    struct buf_list_hdr *last;
    
    u8 bufnum;
};

typedef struct ble_hci_acl_buf {
    struct buf_list_hdr hdr;
    u8 procidx;
    u8 acllen;
    u8 pb_flag;
    u8 acldata[BLE_HCI_ACL_SIZE];
} ble_hci_acl_buf_st;

ble_pdu_st* ble_pdu_alloc   (ble_pdu_pool_st* pool);
u8          ble_pdu_free    (ble_pdu_pool_st* pool, ble_pdu_st* pdu);

#define BLE_DPDU_PB_FLAG_FIRST_NON_FLUSHABLE    0x00
#define BLE_DPDU_PB_FLAG_CONTINUE_NON_FLUSHABLE 0x01
ble_pdu_st* ble_tx_dpdu_alloc(u8 pb_flag, ble_pdu_pool_st* pool);
void buf_list_push_back(struct buf_list *list,
                       struct buf_list_hdr *list_hdr);
struct buf_list_hdr *buf_list_pop_front(struct buf_list *list);
struct buf_list_hdr *buf_list_pick(const struct buf_list *const list);

/**
 * ble hardfault trigger
 *
 */
void ble_hardfault(u8 code, u32 description);

/**
 * conn_hdl
 *
 */
typedef u16 ble_conn_hdl;
#define BLE_CONN_HDL_INVLD ((ble_conn_hdl)0x0fff)

/**
 * ble msg enum and encoding marco
 */
typedef enum{
    BLE_MSG_SRC_LL_RT = 1,
    BLE_MSG_SRC_LL,
    BLE_MSG_SRC_HOST,
}   BLE_MSG_SRC;

#define BLE_MSG_TYPE(_SRC_, _CODE_) ((((_SRC_) & 0x000000ff) << 24) | ((_CODE_) & 0x00ffffff))

/**
 * lpram variable declaration
 *
 */
typedef struct lpram_var {
    void*   lma;
    u16     size;
} lpram_var_st;

#define LPRAM_VAR_DECLARE(VAR)      {.lma = (void*)(&VAR),  .size = sizeof(VAR)}
#define LPRAM_ARRAY_DECLARE(ARRAY)  {.lma = (void*)(ARRAY), .size = sizeof(ARRAY)}

s16 lpram_recovery(const lpram_var_st tbl[], u32 tbl_size);
#endif
