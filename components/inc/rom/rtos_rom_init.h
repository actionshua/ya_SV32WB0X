#ifndef _ROM_INIT_H_
#define _ROM_INIT_H_

__attribute__((no_prologue))
void
rom_init_freertos_bss (
    void
    );

__attribute__((no_prologue))
void
rom_init_freertos_data (
    void
    );

#endif  // #ifndef _ROM_INIT_H_
