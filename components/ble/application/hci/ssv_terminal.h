/**
 * terminal libraries:
 *  - printf()/getchar()/putchar()/kbhit()
 *
 */
#ifndef _SSV_TERMINAL_H_
#define _SSV_TERMINAL_H_

#include "ssv_types.h"
#include "stdio.h"

//s32     printf  (const s8 *format, ...);
//s8      getchar (void);
//void    putchar (s8);
s32     kbhit   (void);

#define PRINTF_FX(...) {printf("[fx:%s] ", __FUNCTION__); printf(__VA_ARGS__);}
#define PRINT_U64(_VAL_) printf("[0x%08x 0x%08x]\n", \
            ((u32)(_VAL_ >> 32)), \
            ((u32)(_VAL_      )))

#define PRINTF_ERR(...) {printf("[fx:%s:err!] ", __FUNCTION__); printf(__VA_ARGS__);}

/**
 * print utility
 *
 */
u32 print_charray (u32 length, u8 *charray);

#endif // _SSV_TERMINAL_H_
