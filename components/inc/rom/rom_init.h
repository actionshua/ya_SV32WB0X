#ifndef _ROM_INIT_H_
#define _ROM_INIT_H_

#include "soc_types.h"
__attribute__((no_prologue))
void
rom_init_bss (
    void
    );

__attribute__((no_prologue))
void
rom_init_data (
    void
    );

typedef struct {
    int32_t (*init)(void *data);
    int32_t (*resume)(void *data);
    int32_t (*suspend)(void *data);
    int32_t (*deinit)(void *data);
} rom_init_t;

void _rom_get_ptr(rom_init_t *ptr);

#endif  // #ifndef _ROM_INIT_H_
