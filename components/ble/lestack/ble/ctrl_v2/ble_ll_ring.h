#ifndef _BLE_LL_RING_H_
#define _BLE_LL_RING_H_

#include "ssv_types.h"
#include "condor_ssv_lib.h"

#include "ble/ctrl_v2/ble_ll.h"

/**
 * # a ring element description.
 * ## if ptr = 0, means the element is move to upper-layer
 *
 */
typedef struct ble_ll_ring_element {

    ptr_u16 ptr;
    u16     is_long :1;
    u16     rsv     :15;

} ble_ll_ring_element_st;

#define BLE_LL_RING_DEPTH CFG_LL_CONN_PDUS
typedef struct ble_ll_ring {

    // interface
    u32 rd_vptr:8;
    u32 wr_vptr:8;

    // config
    u32 ptr_msk:8;

    // memory
    ble_ll_ring_element_st elements[BLE_LL_RING_DEPTH];

} ble_ll_ring_st;

#define BLE_LL_RING_VPTR(vptr, vptr_msk)   (vptr & vptr_msk)
#define BLE_LL_RING_2PTR(vptr, vptr_msk)   (vptr & (vptr_msk >> 1))

/**
 * move pdus form ring to queue, until ring-empty
 *  - mount pdus into ring
 *
 */
s32 ble_ll_ring2q(ble_ll_ring_st* ring, ble_ll_pduq_st* pduq, u32 max_pdu_cnt, ble_pdu_pool_st* free_pdus);

/**
 * move pdus from queue to buf(s)(in fact, a ring), until ring-full
 *  - always write from vptr 0
 *
 */
u32 ble_ll_q2bufs(ble_ll_ring_st* ring, ble_ll_pduq_st* pduq, u32 cnt);


/**
 * move pdus from queue to ring, until ring-full
 *  - write from wr_vptr
 *
 */
u32 ble_ll_q2ring(ble_ll_ring_st* ring, ble_ll_pduq_st* pduq, u32 cnt);

/**
 *  pdu -> queue
 *
 */
u32 ble_ll_pdu2ring(ble_ll_ring_st* ring, ble_ll_pdu_st*    pdu);
u32 ble_ll_ring2pdu(ble_ll_ring_st* ring, ble_ll_pdu_st**   pdu);

/**
 * element cnt in a ring
 *
 */
u32 ble_ll_ring_element_cnt(ble_ll_ring_st* ring);

/**
 * reset ring
 *  - set *_vptr to 0
 *  - free all pdus in ring, if any
 *
 */
s16 ble_ll_ring_reset(ble_ll_ring_st* ring, ble_pdu_pool_st* free_pdus);

/**
 * mount pdus to "read, not reload" position
 *  - scenario: alloc pdu for rx_ring
 */
u32 ble_ll_ring_mount_pdu(ble_ll_ring_st* ring, ble_pdu_pool_st* free_pduq, u32 max_pdu_cnt);

/**
 * unmount pdus, until (rd_vptr -1)
 *
 */
u32 ble_ll_ring_unmount_pdu(ble_ll_ring_st* ring, ble_ll_pduq_st* free_pduq);

#define BLE_LL_RING_IS_FULL(_RING_) \
    (((_RING_)->wr_vptr ^ (_RING_)->rd_vptr) == ((_RING_)->ptr_msk +1))

#define BLE_LL_RING_IS_EMPTY(_RING_) \
    ((_RING_)->wr_vptr == (_RING_)->rd_vptr)

#endif // _BLE_LL_RING_H_
