#ifndef INTL_CS_N7_H
#define INTL_CS_N7_H

#include <nds32_intrinsic.h>

extern volatile int32_t g_cs_nesting;
//struct bsp_cs_locker
//{
//    // in contex-m0 only save the irq status.
//    u32  primask;
//};

// level 1. is only for ble framework.
// level 2. for user call.

// level 1. implement 1. (fast)
__STATIC_INLINE void critical_section_enter( void )
{
    __nds32__setgie_dis();
    __nds32__dsb();
    g_cs_nesting++;
}
/*-----------------------------------------------------------*/

__STATIC_INLINE void critical_section_leave( void )
{
    //ASSERT_COND((__nds32__mfsr(NDS32_SR_PSW) & 0x01) == 0);
    g_cs_nesting--; //ASSERT_COND(g_cs_nesting >= 0);
    if( g_cs_nesting <= 0)
    {
        __nds32__setgie_en();
        __nds32__dsb();
    }
}

// level 1. implement 2. (most fast but not support nest).
#define simple_cs_enter()   \
    do { \
        __nds32__setgie_dis(); \
        __nds32__dsb(); \
    } while(0)
#define simple_cs_leave()   \
    do { \
        __nds32__setgie_en(); \
        __nds32__dsb(); \
    } while(0)
//#define simple_cs_enter() __nds32__gie_dis()
//#define simple_cs_leave() __nds32__gie_en()

//// level 1. implement 3. (fast but nest need many locker.)
//////__STATIC_INLINE void cs_locker_init(struct bsp_cs_locker *locker)
//{
//}
//
////__STATIC_INLINE void cs_locker_enter(struct bsp_cs_locker *locker)
//{
//    //critical_section_enter();
//    locker->primask = __nds32__mfsr(NDS32_SR_PSW) & 0x01;
//    __nds32__setgie_dis();
//    __nds32__dsb();
////    locker->primask = __get_PRIMASK();
////    __disable_irq();
//}
//
////__STATIC_INLINE void cs_locker_leave(struct bsp_cs_locker *locker)
//{
//    //critical_section_leave();
//    ASSERT_COND((__nds32__mfsr(NDS32_SR_PSW) & 0x01) == 0);
//    if (locker->primask) {
//        __nds32__setgie_en();
//        __nds32__dsb();
//    } else {
//        __nds32__setgie_dis();
//        __nds32__dsb();
//    }
////    __set_PRIMASK(locker->primask);
//}


#endif /* end of include guard: INTL_CS_N7_H */
