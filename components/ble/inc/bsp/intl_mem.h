#ifndef INTL_MEM_H
#define INTL_MEM_H

#include "inc/mem.h"

#define DEBUG_HEAP  (0)
#define HEAP_CS     (1)

/* not support free function. */
// must aligned to 32 bites.
struct heap_u16_fixed_hdr
{
    u32         max_len;
    u8          *ptr;
};

void dump_mem_status();
void *bsp_heap_fixed_alloc(u16 size);
void *ble_alloc(u16 size);
void ble_free(void *ptr);
#if (DEBUG_HEAP == 1)
u16 ble_mem_len(void *ptr);
void memory_verify_init(u16 time);
#endif

#endif /* end of include guard: INTL_MEM_H */


