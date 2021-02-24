#ifndef _L2CAP_API_H_
#define _L2CAP_API_H_


#include "les_if/api/inc/svc_def.h"
#include "les_if/api/inc/les_def.h"



#define L2CAP_DYNAMIC_CID_DATA_MAX                      23



typedef enum
{
    L2CAP_SVCMD_REGISTER_CID = L2CAP_SVC_NUM_MIN,
    L2CAP_SVCMD_UNREGISTER_CID,
    L2CAP_SVCMD_SEND_DYNAMIC_CID_DATA,

} L2CAP_SVCMD;



typedef enum
{
    L2CAP_LES_EVENT_DYNAMIC_CID_DATA = L2CAP_LES_EVENT_ID_MIN,

} L2CAP_LES_EVENT;



typedef struct 
{
    uint16_t cid;
    uint16_t data_len;
    uint8_t  data[L2CAP_DYNAMIC_CID_DATA_MAX];

} l2cap_dynamic_cid_data_st;



typedef struct 
{
    uint16_t conn_hdl;

    union
    {
        l2cap_dynamic_cid_data_st dynamic_cid_data;     /// GATTS_LES_EVENT_INDICATION_STATUS

    } data;

} l2cap_les_event_st;



DEF_SVC(L2CAP_SVCMD_REGISTER_CID,           uint32_t,   les_l2cap_register_cid(uint16_t conn_hdl, uint16_t dynamic_cid));
DEF_SVC(L2CAP_SVCMD_UNREGISTER_CID,         uint32_t,   les_l2cap_unregister_cid(uint16_t conn_hdl));
DEF_SVC(L2CAP_SVCMD_SEND_DYNAMIC_CID_DATA,  uint32_t,   les_l2cap_send_dynamic_cid_data(uint16_t conn_hdl, l2cap_dynamic_cid_data_st *dynamic_cid_data));



#endif  // end of _L2CAP_API_H_