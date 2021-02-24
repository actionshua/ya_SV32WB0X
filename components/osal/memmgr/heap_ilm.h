#ifndef HEAP_ILM
#define HEAP_ILM

#include <stdlib.h>

void *pvIlmPortMalloc( size_t xWantedSize );
void vIlmPortFree( void *pv );
size_t xIlmPortGetFreeHeapSize( void );
size_t xIlmPortGetMinimumEverFreeHeapSize( void );
uint32_t ulIlmMemMaxFreeBlockSize( void );
size_t xIlmPortGetTotalHeapSize( void );
uint32_t isIlm(void *pv);
#endif /* end of include guard */
