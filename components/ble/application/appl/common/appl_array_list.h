#ifndef _APPL_ARRAY_LIST_H_
#define _APPL_ARRAY_LIST_H_



#include "stdint.h"



#define APPL_ARRAY_LIST_SIZE_MAX            (1024)
#define APPL_ARRAY_LIST_INVALID_IDX         (0xFFFF)



typedef struct
{
    void        **list;
    uint16_t    length;
    uint16_t    size;

} array_list_st;



array_list_st *appl_array_list_new(uint16_t size);
void appl_array_list_free(array_list_st *array_list);
void *appl_array_list_get(array_list_st *array_list, uint16_t idx);
uint16_t appl_array_list_add(array_list_st *array_list, void *data);



#endif      /// end of _APPL_ARRAY_LIST_H_
