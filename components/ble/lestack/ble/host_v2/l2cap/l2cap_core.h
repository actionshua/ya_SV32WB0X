#ifndef _L2CAP_CORE_H_
#define _L2CAP_CORE_H_



#include "l2cap_def.h"



typedef enum
{
    L2CAP_STATE_IDLE = 0,
    L2CAP_STATE_SEND_UPPER,

} L2CAP_STATE;



typedef enum
{
    L2CAP_OPERATION_SEND_UPPER_REQUEST,
    L2CAP_OPERATION_SEND_UPPER_RESPONSE,

} L2CAP_OPERATION;



typedef struct
{
    L2CAP_OPERATION     op;
    u32                 *param;
    u8                  param_size;

} l2cap_operation_st;



typedef struct l2cap_slq
{
    l2cap_sdu_st        *head;
    u32                 depth;
    u32                 owner;

} l2cap_slq_st;



typedef struct
{
    L2CAP_STATE         state[L2CAP_SLQ_ID_MAX];
    u16                 conn_hdl;
    u16                 dynamic_cid;
    l2cap_sdu_st        *recombine_sdu;
    l2cap_slq_st        slq_pool[L2CAP_SLQ_ID_MAX];

} l2cap_ctrlblock_st;



typedef struct
{
    u16                 segment_size;
    u8                  segment_num_normal;
    u8                  segment_num_normal_max;
    u8                  segment_num_priority;
    u8                  segment_num_priority_max;
    alloc_pdu_func_t    alloc_pdu_func;
    free_pdu_func_t     free_pdu_func;
    send_tx_pdu_func_t  send_tx_pdu_func;

} l2cap_common_st;



u8 l2cap_core_reset(void);
u8 l2cap_core_obtain_resource(u16 conn_hdl);
u8 l2cap_core_release_resource(u16 conn_hdl);
L2CAP_ID l2cap_core_get_valid_id(u16 conn_hdl);
u16 l2cap_core_get_conn_hdl(L2CAP_ID id);
void l2cap_core_set_conn_hdl(L2CAP_ID id, u16 conn_hdl);
u16 l2cap_core_get_dynamic_cid(L2CAP_ID id);
void l2cap_core_set_dynamic_cid(L2CAP_ID id, u16 dynamic_cid);
l2cap_sdu_st *l2cap_core_get_recombine_sdu(L2CAP_ID id);
void l2cap_core_set_recombine_sdu(L2CAP_ID id, l2cap_sdu_st *sdu);
l2cap_slq_st *l2cap_core_get_slq(L2CAP_ID id, L2CAP_SLQ_ID slq_id);
u8 l2cap_core_register_alloc_pdu_func(alloc_pdu_func_t alloc_pdu_func);
u8 l2cap_core_register_free_pdu_func(free_pdu_func_t free_pdu_func);
u8 l2cap_core_register_send_tx_pdu_func(send_tx_pdu_func_t send_tx_pdu_func);
ble_pdu_st *l2cap_core_alloc_pdu(u8 type, u8 dir, u8 pb_flag);
u8 l2cap_core_free_pdu(u8 dir, ble_pdu_st *pdu);
u8 l2cap_core_send_tx_pdu(u16 conn_hdl, ble_pdu_st *tx_pdu);
u16 l2cap_core_get_segment_size(void);
u8 l2cap_core_get_segment_num(u8 type);
u8 l2cap_core_send_operation(L2CAP_ID id, l2cap_operation_st *operation);
u8 l2cap_core_send_upper_request(L2CAP_ID id, L2CAP_SLQ_OWNER owner);
u8 l2cap_core_handle_number_of_completed_packets_event(L2CAP_ID id, u8 packets);



#endif  /// end of _L2CAP_CORE_H_
