#ifndef SVC_H
#define SVC_H

///#include "ssv_types.h"
///#include "ble/ctrl/ble_ll_if.h"
///#include "ble/host/gap_peripheral.h"


#if defined(__SSV_LINUX_SIM__)

#define DEF_SVC(num, ret_type, func) ret_type func
#define SVC(num, ret_type, func) \
    ret_type func { \
        return 0; \
    } \

#elif defined(__CC_ARM)

#define SVC(num, ret_type, func) ret_type __svc(num) func

#define DEF_SVC(num, ret_type, func) ret_type __svc(num) func

#elif defined(__GNUC__)

#define DEF_SVC(num, ret_type, func) \
__attribute__((naked, noinline)) ret_type func;

#define SVC(num, ret_type, func) \
_Pragma("GCC diagnostic push") \
_Pragma("GCC diagnostic ignored \"-Wreturn-type\"") \
_Pragma("GCC diagnostic ignored \"-Wunused-function\"") \
__attribute__((naked, noinline)) ret_type func \
{ \
    __ASM( \
            "svc %0\n\t" \
            "bx lr" \
            : \
            : "I" (num) \
            : "r0" \
         ); \
} \
_Pragma("GCC diagnostic pop")

#elif defined(__ICCARM__)

#error not implement.

#else
#error not support.
#endif


///DEF_SVC(GAP_OPERATION_SET_ADV_PARAMETER, int, SetAdvParam(ble_ll_adv_param_st *param));
///DEF_SVC(GAP_OPERATION_SET_ADV_DATA, int, SetAdvData(ble_gap_adv_data_st *data_adv,ble_gap_adv_data_st *data_scan_rsp));
///DEF_SVC(GAP_OPERATION_START_ADV, int, StartAdv(u32 timeout));
///DEF_SVC(GAP_OPERATION_STOP_ADV, int, StopAdv(u32 timeout));


#endif /* end of include guard: SVC_H */
