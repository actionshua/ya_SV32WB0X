#ifndef HEAP_Dlm
#define HEAP_Dlm

#include <stdlib.h>

void *pvDlmPortMalloc( size_t xWantedSize );
void vDlmPortFree( void *pv );
size_t xDlmPortGetFreeHeapSize( void );
size_t xDlmPortGetMinimumEverFreeHeapSize( void );
uint32_t ulDlmMemMaxFreeBlockSize( void );
size_t xDlmPortGetTotalHeapSize( void );
uint32_t isDlm(void *pv);
#endif /* end of include guard */
