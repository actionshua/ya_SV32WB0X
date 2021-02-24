#ifndef _APPL_LES_EVENT_QUEUE_H_
#define _APPL_LES_EVENT_QUEUE_H_



#include "stdint.h"
#include "stdlib.h"
#include "appl/common/appl_error.h"
#include "appl/common/appl_mem.h"
#include "les_if/api/inc/les_api.h"



#define LES_FX_ALLOC(SIZE)          appl_mem_malloc(SIZE)
#define LES_FX_FREE(PTR)            appl_mem_free(PTR)



typedef struct les_event_lq_element
{
    struct les_event_lq_element     *next;
    les_event_st                    *les_event;

} les_event_lq_element_st;



typedef struct les_event_lq_base
{
    les_event_lq_element_st     *head;
    uint32_t                    depth;

} les_event_lq_base_st;



void appl_les_event_queue_init(void);
les_event_st* appl_les_event_queue_alloc_event(uint16_t les_event_size);
void appl_les_event_queue_free_event(les_event_st *les_event);
les_event_lq_element_st* appl_les_event_queue_alloc_element(uint16_t les_event_size);
void appl_les_event_queue_free_element(les_event_lq_element_st *les_event_lq_element);
uint32_t appl_les_event_queue_enqueue(les_event_lq_element_st *les_event_lq_element);
les_event_lq_element_st* appl_les_event_queue_dequeue(void);
les_event_lq_element_st* appl_les_event_queue_peek(void);
uint32_t appl_les_event_queue_size(void);



#endif  /// end of _APPL_LES_EVENT_QUEUE_H_
