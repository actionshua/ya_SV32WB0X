#ifndef HEAP_Bus
#define HEAP_Bus

#include <stdlib.h>

void *pvBusPortMalloc( size_t xWantedSize );
void vBusPortFree( void *pv );
size_t xBusPortGetFreeHeapSize( void );
size_t xBusPortGetMinimumEverFreeHeapSize( void );
uint32_t ulBusMemMaxFreeBlockSize( void );
size_t xBusPortGetTotalHeapSize( void );
#endif /* end of include guard */
