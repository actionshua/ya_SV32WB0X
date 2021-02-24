#ifndef _GATTS_API_H_
#define _GATTS_API_H_


#include "les_if/api/inc/svc_def.h"
#include "les_if/api/inc/les_def.h"



typedef enum
{
    GATTS_SVCMD_INDICATION = GATTS_SVC_NUM_MIN,
    GATTS_SVCMD_NOTIFICATION,

} GATTS_SVCMD;



typedef enum
{
    GATTS_LES_EVENT_INDICATION_STATUS = GATTS_LES_EVENT_ID_MIN,

} GATTS_LES_EVENT;



typedef struct 
{
    uint8_t     status;
    uint16_t    attr_hdl;

} gatts_indication_status_st;



typedef struct 
{
    uint16_t conn_hdl;

    union
    {
        gatts_indication_status_st indication_status;     /// GATTS_LES_EVENT_INDICATION_STATUS

    } data;

} gatts_les_event_st;



DEF_SVC(GATTS_SVCMD_INDICATION,     uint32_t,   les_gatts_indication(uint16_t conn_hdl, uint16_t attr_hdl));
DEF_SVC(GATTS_SVCMD_NOTIFICATION,   uint32_t,   les_gatts_notification(uint16_t conn_hdl, uint16_t attr_hdl));



#endif  // end of _GATTS_API_H_