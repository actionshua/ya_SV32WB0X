#ifndef _APPL_LQ_COMBO_H_
#define _APPL_LQ_COMBO_H_


#include "stdint.h"
#include "appl_linked_queue.h"



typedef enum
{
    APPL_LQ_COMBO_TYPE_PERMANENT = 0,
    APPL_LQ_COMBO_TYPE_VOLATILE,
    APPL_LQ_COMBO_TYPE_MAX,

} APPL_LQ_COMBO_TYPE;



typedef struct
{
    uint8_t     type;

} appl_lq_combo_ctrlblock_st;



void appl_lq_combo_init(uint8_t type);
lq_element_st *appl_lq_combo_peek(lq_base_st* queue);
lq_element_st *appl_lq_combo_deq(lq_base_st* queue);
uint32_t appl_lq_combo_enq(lq_base_st* queue, lq_element_st* element);
uint32_t appl_lq_combo_cat(lq_base_st* dest, lq_base_st* src);
uint32_t appl_lq_combo_size(lq_base_st* queue);



#endif      /// end of _APPL_LQ_COMBO_H_
