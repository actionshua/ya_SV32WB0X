#ifndef _APPL_LINKED_QUEUE_H_
#define _APPL_LINKED_QUEUE_H_



#include "stdint.h"



typedef struct lq_element
{
    struct lq_element*  next;
    uint32_t            data;

} lq_element_st;



typedef struct lq_base
{
    lq_element_st*      head;
    uint32_t            depth;

} lq_base_st;



void appl_linked_queue_init(void);
lq_element_st* appl_linked_queue_peek(lq_base_st* queue);
lq_element_st* appl_linked_queue_deq(lq_base_st* queue);
uint32_t appl_linked_queue_enq(lq_base_st* queue, lq_element_st* element);
uint32_t appl_linked_queue_cat(lq_base_st* dest, lq_base_st* src);
uint32_t appl_linked_queue_size(lq_base_st* queue);
void appl_linked_queue_deinit(void);



#endif      /// end of _APPL_LINKED_QUEUE_H_
