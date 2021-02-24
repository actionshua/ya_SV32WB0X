#ifndef _LINKED_QUEUE_H_
#define _LINKED_QUEUE_H_


#include "stdint.h"
#include "condor_ssv_lib.h"


typedef struct lq_element
{
    struct lq_element*  next;
    u32                 data;

} lq_element_st;



typedef struct lq_base
{
    lq_element_st*      head;
    u32                 depth;

} lq_base_st;



void linked_queue_init(void);
lq_element_st* linked_queue_peek(lq_base_st* queue);
lq_element_st* linked_queue_deq(lq_base_st* queue);
u32 linked_queue_enq(lq_base_st* queue, lq_element_st* element);
u32 linked_queue_cat(lq_base_st* dest, lq_base_st* src);
u32 linked_queue_dump(lq_base_st* queue);



#endif      /// end of _LINKED_QUEUE_H_
