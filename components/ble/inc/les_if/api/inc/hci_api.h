#ifndef _HCI_API_H_
#define _HCI_API_H_


#include "les_if/api/inc/svc_def.h"
#include "les_if/api/inc/les_def.h"
#include "osal.h"



typedef enum
{
    HCI_SVCMD_ENABLE = HCI_SVC_NUM_MIN,
    HCI_SVCMD_CMD,
    HCI_SVCMD_LES_FREE,
    HCI_SVCMD_RESERVED_CMD,

} HCI_SVCMD;



typedef enum
{
    HCI_LES_EVENT_HCI_ASYNC_EVT = HCI_LES_EVENT_ID_MIN,
    HCI_LES_EVENT_RESERVED_EVT,

} HCI_LES_EVENT;



typedef enum
{
    HCI_RESULT_SUCCESS = ERR_SUCCESS,
    HCI_RESULT_MIN = ERR_HCI,

    HCI_RESULT_FAIL = HCI_RESULT_MIN,

    HCI_RESULT_MAX,

} HCI_RESULT;


#define HCI_ASYNC_EVT_LEN_MAX   256  // MAX: advertising report
// used for LES event extension
#define HCI_RESERVED_EVT_SIZE   261  // sizeof(hci_async_evt_st) -1
typedef struct
{
    uint16_t evt_len;
    uint8_t evt[HCI_ASYNC_EVT_LEN_MAX];

    const void* les_memory;

} hci_async_evt_st;


typedef struct
{
    uint8_t evt_len;
    uint8_t evt[HCI_RESERVED_EVT_SIZE];

} hci_reserved_evt_st;



typedef struct
{
    union
    {
        hci_async_evt_st        hci_async_evt;      /// HCI_LES_EVENT_HCI_ASYNC_EVT
        hci_reserved_evt_st     hci_reserved_evt;   /// HCI_LES_EVENT_RESERVED_EVT

    } data;

} hci_les_event_st;

typedef struct hci_cmd_param
{
    u32 svc_hcicmd;
    u32 argv[4];
    u32 retval;
    OsSemaphore hcisem;
    OsMutex hcimutex;
}HCI_CMD_PARAM;

uint32_t les_hci_enable(uint32_t     enable);
uint32_t les_hci_cmd(uint32_t    cmd_len, const uint8_t* cmd, uint32_t  sync_evt_len_max, uint8_t* sync_evt);
uint32_t les_hci_free(const void* les_memory);
uint32_t les_hci_reserved_cmd(uint32_t sub_opcode, uint32_t arg0, uint32_t arg1, uint32_t arg2);

#endif  /// end of _HCI_API_H_
