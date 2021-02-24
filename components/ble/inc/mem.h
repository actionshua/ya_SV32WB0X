#ifndef MEM_H
#define MEM_H

#define M_ALIGN_32(val)     (((val+3)>>2)<<2)


SSV_API void bsp_heap_init();
SSV_API void* ap_alloc(u16);
SSV_API void ap_free(void*);


#endif /* end of include guard: MEM_H */

