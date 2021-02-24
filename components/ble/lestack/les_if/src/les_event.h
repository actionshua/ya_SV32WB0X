#ifndef _LES_EVENT_H_
#define _LES_EVENT_H_



#include <stdint.h>
#include "les_if/api/inc/les_api.h"
#include "lib/condor_ssv_lib.h"



#ifdef __SSV_LINUX_SIM__

#define LES_FX_ALLOC(SIZE)         malloc(SIZE)
#define LES_FX_FREE(PTR)           free(PTR)

#else

#include "condor.h"
#include "inc/bsp/intl_mem.h"

#define LES_FX_ALLOC(SIZE)          OS_MemAlloc(SIZE)
#define LES_FX_FREE(PTR)            OS_MemFree(PTR)

#endif



typedef enum
{
    LES_EVENT_STATUS_DEQUEUE = 0,
    LES_EVENT_STATUS_ENQUEUE,

} LES_EVENT_STATUS;



typedef struct les_event_lq_element
{
    struct les_event_lq_element     *next;
    les_event_st                    les_event;

} les_event_lq_element_st;



typedef struct les_event_lq_base
{
    les_event_lq_element_st *head;
    uint32_t                 depth;

} les_event_lq_base_st;



typedef struct
{
    uint8_t                 used;
    les_event_lq_element_st lq_element;
    sys_les_event_st        sys_les_event;

} les_event_lq_sys_element_st;



void les_event_init(void);
u8 les_event_queue_enqueue(les_event_st *les_event);
u8 les_event_queue_enqueue_with_cb(les_event_st *les_event, u32 info, les_event_status_cb_t cb);
u8 les_event_queue_dequeue(les_event_st *les_event);
u8 les_event_queue_peek_size(uint16_t *les_event_size);
u8 les_event_queue_peek_depth(uint32_t *les_event_queue_depth);



#endif  /// end of _LES_EVENT_H_
