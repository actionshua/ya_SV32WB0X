/**
 * basic libraries:
 *  - nothing about protocol
 *  - platform dependent implementation
 *
 */
#ifndef _CONDOR_SSV_LIB_H_
#define _CONDOR_SSV_LIB_H_

#include <stddef.h>
#include "ssv_types.h"

#include "ble_config.h" // for ptr_u16 operation
#include "osal.h"
#include "string.h"

// TODO: should be removed in near future
//#define printf(...)
#if 0
SSV_API s32 strcmp( const s8 *s0, const s8 *s1 );
SSV_API s8 *strcat(s8 *s, const s8 *append);
SSV_API s8 *strncpy(s8 *dst, const s8 *src, size_t n);
SSV_API size_t strlen(const s8 *s);
SSV_API void *memset(void *s, s32 c, size_t n);
SSV_API void *memcpy(void *dest, const void *src, size_t n);
SSV_API s32 memcmp(const void *s1, const void *s2, size_t n);
#endif
SSV_API void *memcpy_swap(void *dest, const void *src, size_t n);
SSV_API u32 ssv_atoi_base( const s8 *s, u32 base );
SSV_API s32 ssv_atoi( const s8 *s );

//SSV_API s32 abs(s32 i);
SSV_API u32 ssv_div(u32 dividend, u32 divisor);
SSV_API u32 ssv_mod(u32 dividend, u32 divisor);

SSV_API u8 ssv_u8div(u8 dividend, u8 divisor);
SSV_API u8 ssv_u8mod(u8 dividend, u8 divisor);

void *regcpybyte(u32 *dest, const u32* src, size_t n);
void *regset(u32 *dest, u32 c, size_t n);
void *b2wcpy(u32 *dest, const u8*  src, size_t n);


// # macro to idenity where "intentional" no break bewteen case
#define NO_BREAK do{} while(0)

//#define REG32(addr) (*(volatile u32 *)(ul32)((addr)))

#define BIT_GET(_WORD_, _IDX_)          ((_WORD_ >> _IDX_) &1)
#define BIT_SET(_WORD_, _IDX_, _BIT_)   _WORD_ = (_WORD_ & ~(1 << _IDX_)) | (_BIT_ << _IDX_)

#define U64_BIT_SHIFT(_VAL_, _IDX_)         (((u64)(_VAL_ &1)) << _IDX_)
#define U64_BIT_GET(_VAL_, _IDX_)           ((u32)((_VAL_ >> _IDX_) &1))
#define U64_BIT_SET(_DST_, _IDX_, _VAL_) \
        _DST_ = ((_DST_ & ~U64_BIT_SHIFT(1, _IDX_)) | U64_BIT_SHIFT(_VAL_, _IDX_))

#define U64_BIT_OR(_DST_, _IDX_, _VAL_)     _DST_ |=  U64_BIT_SHIFT(_VAL_, _IDX_)
#define U64_BIT_CLR(_DST_, _IDX_)           _DST_ &= ~U64_BIT_SHIFT(1,     _IDX_)

#define U64_HWORD(_VAL_)   ((u32)(_VAL_ >> 32))
#define U64_LWORD(_VAL_)   ((u32)(_VAL_      ))

#define U64_BUILD(_HWORD_, _LWORD_) ((((u64)(_HWORD_)) << 32) | ((u64)(_LWORD_)))
#define U32_BUILD(_W0_, _W1_, _W2_, _W3_)   ((((u32)(_W3_)) << 24) | (((u32)(_W2_)) << 16) | \
                                             (((u32)(_W1_)) << 8)  | (((u32)(_W0_)) << 0))

SSV_API u64 u8_to_u64(const u8* src, u8 size);
SSV_API u32 u8_to_u32(const u8* src, u8 size);

SSV_API void u64_to_u8(u64 src, u8* dst, u8 size);
SSV_API void u32_to_u8(u32 src, u8* dst, u8 size);

#define U8_TO_U16(_SRC_)        ((((u16)((_SRC_)[1])) << 8) | ((u16)((_SRC_)[0])))
#define U8_TO_S16(_SRC_)        ((s16)(U8_TO_U16(_SRC_)))
#define U16_TO_U8(_SRC_, _DST_) \
    (_DST_)[1] = (u8)((_SRC_) >> 8); \
    (_DST_)[0] = (u8)(_SRC_)

#define U16_BYTE0(_U16_) ((u8)((_U16_) >> 0))
#define U16_BYTE1(_U16_) ((u8)((_U16_) >> 8))

#define U32_BYTE3(_U32_) ((u8)((_U32_) >>  24))
#define U32_BYTE2(_U32_) ((u8)((_U32_) >>  16))
#define U32_BYTE1(_U32_) ((u8)((_U32_) >>   8))
#define U32_BYTE0(_U32_) ((u8)((_U32_) >>   0))

/**
 * conversion between 32-bit-pointer/16-bit-pointer
 *  - require definition of "SYS_SRAM_BADDR" (config.h)
 *
 */
uint32_t ll_isDlm(u32 pv);
uint32_t ll_isDlm_p(void *pv);

typedef u16 ptr_u16;
typedef u32 ptr_u32;

extern u16 ptr2u16(u32 ptr);
void* u162ptr(u16 ptr);
#define PTR2U16(ptr)        ptr2u16((u32)ptr)
#define U162PTR(ptr)    u162ptr((u16)ptr)//((void*)((u32)ptr_u16 +SYS_SRAM_BADDR))
//#define U162PTR(ptr_u16)    ((void*)((u32)ptr_u16 +SYS_SRAM_BADDR_DLM))

#define PTR_NULL 0

#endif /* _CONDOR_SSV_LIB_H_ */
