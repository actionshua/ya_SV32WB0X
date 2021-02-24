#ifndef _APPL_MEM_H_
#define _APPL_MEM_H_


#include "stdint.h"



void appl_mem_init(void);
void *appl_mem_malloc(uint32_t size);
void *appl_mem_realloc(void *ptr, uint32_t size);
void appl_mem_free(void *ptr);
void appl_mem_deinit(void);



#endif  /// end of _APPL_MEM_H_
