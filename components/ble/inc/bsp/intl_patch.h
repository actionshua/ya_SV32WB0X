#ifndef _INTL_PATCH_H_
#define _INTL_PATCH_H_



#include "ssv_types.h"



#define PATCH_INVALID       0x00
#define PATCH_VALID         0x01



u8 patch_get_patch_valid(void);
u8 patch_set_patch_valid(u8 enable, u16 valid_patch);
u16 patch_get_patch_version(void);
u8 patch_set_patch_version(u16 version);



#endif  /// end of _INTL_PATCH_H_
