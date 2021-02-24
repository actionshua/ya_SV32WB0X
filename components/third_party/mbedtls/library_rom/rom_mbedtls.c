
#include "../include/mbedtls/cipher.h"
#include "rom_mbedtls.h"

unsigned int g_rom_mbedtls_debug = 0;
rom_mbed_protocol_st*g_rom_mbed_protocol;

void rom_mbed_debug_enable()
{
    g_rom_mbedtls_debug = 1;
}


void rom_mbed_debug_disable()
{
    g_rom_mbedtls_debug = 0;
}

inline void rom_debug_print(const char *func, int line)
{
    if(g_rom_mbedtls_debug == 1) {
        g_rom_mbed_protocol->printf("[%d]rom %s\n", line, func);
    }
}
