#ifndef _PATCH_H_
#define _PATCH_H_



#include "ssv_types.h"



#define SW_PATCH_SRAM_BADDR     0x00100000



#define DECLARE_SW_PATCHABLE_FUNCTION(func_name, func_return_t, ...) \
    func_return_t func_name(__VA_ARGS__)



#define CHECK_SW_PATCH(func_name, ...) \
    do { \
    } while(0)



#define CHECK_SW_PATCH_NO_RETURN(func_name, ...) \
    do { \
    } while(0)



#define DECLARE_SW_GROUP_PATCHABLE_FUNCTION(func_name, func_return_t, ...) \
    func_return_t func_name(__VA_ARGS__)



#define CHECK_SW_GROUP_PATCH(func_name, ...) \
    do { \
    } while(0)



#define CHECK_SW_GROUP_PATCH_NO_RETURN(func_name, ...) \
    do { \
    } while(0)



#endif  /// _PATCH_H_
