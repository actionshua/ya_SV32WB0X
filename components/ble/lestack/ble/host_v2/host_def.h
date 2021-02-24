#ifndef _HOST_DEF_H_
#define _HOST_DEF_H_


#include "ssv_types.h"
#include "ssv_lib.h"
#include "patch.h"
#include "ble/ble_lib_v2.h"
#include "inc/bsp/intl_mem.h"
#include "inc/bsp/intl_power.h"
#include "les_if/api/inc/les_api.h"
#include "host_timer.h"



#ifdef __SSV_LINUX_SIM__

#define HOST_FX_ALLOC(SIZE)         malloc(SIZE)
#define HOST_FX_FREE(PTR)           free(PTR)

#else

#define HOST_FX_ALLOC(SIZE)         OS_MemAlloc(SIZE)
#define HOST_FX_FREE(PTR)           OS_MemFree(PTR)

#endif



/// Host log operation
#define HOST_DEBUG

#ifdef HOST_DEBUG
#include "ilog.h"
#define HOST_LOG_VERBOSE(...)                   \
    do {                                        \
        HOST_ILOG(LOG_VERBOSE, __VA_ARGS__);    \
    } while(0)

#define HOST_LOG_DBG(...)                       \
    do {                                        \
        HOST_ILOG(LOG_DBG, __VA_ARGS__);        \
    } while(0)

#define HOST_LOG_INFO(...)                      \
    do {                                        \
        HOST_ILOG(LOG_INFO, __VA_ARGS__);       \
    } while(0)

#define HOST_LOG_ERR(...)                       \
    do {                                        \
        HOST_ILOG(LOG_ERR, __VA_ARGS__);        \
    } while(0)

#define HOST_LOG_HARDFAULT(...)                 \
    do {                                        \
        HOST_ILOG(LOG_CRIT, __VA_ARGS__);       \
    } while(0)

#define HOST_LOG_ARRAY(array, len)              \
    do {                                        \
        IDUMP(LOG_INFO, array, len);    \
    } while(0)

#else

#define HOST_LOG_VERBOSE(...)
#define HOST_LOG_DBG(...)
#define HOST_LOG_INFO(...)
#define HOST_LOG_ERR(...)
#define HOST_LOG_HARDFAULT(...)
#define HOST_LOG_ARRAY(array, len)

#endif  /// #ifdef HOST_DEBUG



#define ERR_HOST_COMMON_NUM             (0x08)
#define ERR_HOST_ATTS_NUM               (0x02)
#define ERR_HOST_ATTC_NUM               (0x02)
#define ERR_HOST_GAP_NUM                (0x05)
#define ERR_HOST_GATTM_NUM              (0x04)
#define ERR_HOST_GATTS_NUM              (0x02)
#define ERR_HOST_GATTC_NUM              (0x02)
#define ERR_HOST_L2CAP_NUM              (0x02)
#define ERR_HOST_SMP_NUM                (0x02)

#define ERR_HOST_COMMON                 (ERR_HOST)
#define ERR_HOST_ATTS                   (ERR_HOST_COMMON + ERR_HOST_COMMON_NUM)
#define ERR_HOST_ATTC                   (ERR_HOST_ATTS + ERR_HOST_ATTS_NUM)
#define ERR_HOST_GAP                    (ERR_HOST_ATTC + ERR_HOST_ATTC_NUM)
#define ERR_HOST_GATTM                  (ERR_HOST_GAP + ERR_HOST_GAP_NUM)
#define ERR_HOST_GATTS                  (ERR_HOST_GATTM + ERR_HOST_GATTM_NUM)
#define ERR_HOST_GATTC                  (ERR_HOST_GATTS + ERR_HOST_GATTS_NUM)
#define ERR_HOST_L2CAP                  (ERR_HOST_GATTC + ERR_HOST_GATTC_NUM)
#define ERR_HOST_SMP                    (ERR_HOST_L2CAP + ERR_HOST_L2CAP_NUM)
#define ERR_HOST_END                    (ERR_HOST_SMP + ERR_HOST_SMP_NUM)

#if ((ERR_HOST_END - ERR_HOST) > ERR_HOST_NUM)
#error "ERR_HOST OVERFLOW"
#endif

typedef enum
{
    ERR_HOST_SUCCESS = ERR_SUCCESS,
    ERR_HOST_MIN = ERR_HOST_COMMON,

    ERR_HOST_FAIL = ERR_HOST_MIN,
    ERR_HOST_INVALID_PARAM,
    ERR_HOST_INVALID_OPERATION,
    ERR_HOST_INVALID_HANDLE,
    ERR_HOST_INSUFF_RESOURCE,
    ERR_HOST_CANCEL,
    ERR_HOST_TIMEOUT,
    ERR_HOST_DISCONNECT,

    ERR_HOST_MAX,

    ERR_HOST_INVALID_CONNECTION = 0xC3,

} ERR_HOST_ENUM;



typedef enum
{
    HARDFAULT_HOST_NONE = HARDFAULT_NONE,
    HARDFAULT_HOST_MIN = HARDFAULT_HOST,
    HARDFAULT_HOST_SEND_HOST_EVENT_FAIL = HARDFAULT_HOST_MIN,
    HARDFAULT_HOST_MAX,

} HARDFAULT_HOST_ENUM;



typedef enum
{
    HOST_EVENT_L2CAP_SEND_UPPER_REQUEST = 0,
    HOST_EVENT_MAX,
    HOST_EVENT_INVALID = HOST_EVENT_MAX,

} HOST_EVENT;



#endif  /// end of _HOST_DEF_H_
