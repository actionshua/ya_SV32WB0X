#ifndef _LL_API_H_
#define _LL_API_H_


#include "les_if/api/inc/svc_def.h"
#include "les_if/api/inc/les_def.h"



typedef enum
{
    LL_SVCMD_START_AIR_EVENT_SESSION = LL_SVC_NUM_MIN,
    LL_SVCMD_STOP_AIR_EVENT_SESSION,
    LL_SVCMD_SET_FEATURE_ENABLE,
    LL_SVCMD_SET_AIR_EVENT_EARLY_NOTIFY_TIME,

} LL_SVCMD;



typedef enum
{
    LL_LES_EVENT_AIR_EVENT = LL_LES_EVENT_ID_MIN,

} LL_LES_EVENT;



typedef enum
{
    LL_AIR_EVENT_TYPE_BEGIN,
    LL_AIR_EVENT_TYPE_END,

} LL_AIR_EVENT_TYPE;



typedef void (*ll_air_event_cb_t)(uint8_t type);



typedef struct
{
    uint8_t type;

} ll_air_event_st;



typedef struct
{
    union
    {
        ll_air_event_st     air_event;      /// LL_LES_EVENT_AIR_EVENT

    } data;

} ll_les_event_st;



typedef union
{

    struct
    {
        uint32_t jammer_enable              :1;
        uint32_t scan_early_stopper_enable  :1;
        uint32_t phy_agc_enable             :1;
    };

    uint32_t word;

} ll_feature_enable_t;


DEF_SVC(LL_SVCMD_START_AIR_EVENT_SESSION,   uint32_t,   les_ll_start_air_event_session(void));
DEF_SVC(LL_SVCMD_STOP_AIR_EVENT_SESSION,    uint32_t,   les_ll_stop_air_event_session(void));
DEF_SVC(LL_SVCMD_SET_FEATURE_ENABLE,        uint32_t,   les_ll_set_feature_enable(ll_feature_enable_t select, ll_feature_enable_t enable));
DEF_SVC(LL_SVCMD_SET_AIR_EVENT_EARLY_NOTIFY_TIME,
                                            uint32_t,   les_ll_set_air_event_early_notify_time(uint8_t time));


#endif  /// end of _LL_API_H_
