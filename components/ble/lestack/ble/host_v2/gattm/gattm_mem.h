#ifndef _GATTM_MEM_H_
#define _GATTM_MEM_H_



#include "gattm_def.h"



#define GATTM_MEM_SIZE_MAX         1024



typedef struct
{
    u8  *base_ptr;
    u8  *next_ptr;

} gattm_mem_ctrlblock_st;



u8 gattm_mem_reset(void);
void *gattm_mem_alloc(u16 size);



#endif  /// end of _GATTM_MEM_H_
