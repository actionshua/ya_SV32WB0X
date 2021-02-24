#ifndef _BLE_HOST_H_
#define _BLE_HOST_H_



#include "host_def.h"
#include "inc/bsp/msg.h"



#define MSG_EVT_OFFSET 0



typedef enum
{
    HOST_WAKELOCK_ID_HOST_TIMER = 0,
    HOST_WAKELOCK_ID_1,
    HOST_WAKELOCK_ID_2,
    HOST_WAKELOCK_ID_3,
    HOST_WAKELOCK_ID_4,
    HOST_WAKELOCK_ID_5,
    HOST_WAKELOCK_ID_6,
    HOST_WAKELOCK_ID_7,
    HOST_WAKELOCK_ID_MAX,
    HOST_WAKELOCK_ID_INVALID = HOST_WAKELOCK_ID_MAX,

} HOST_WAKELOCK_ID;



typedef struct
{
    u8      enabled;

} host_ctrlblock_st;



u8 ble_host_init(void);
u8 ble_host_enable(void);
u8 ble_host_disable(void);
u8 ble_host_pause(void);
u8 ble_host_resume(void);
u8 ble_host_reset(void);
u8 ble_host_wakelock_task(u8 wakelock_id, u8 wakelock);
u8 ble_host_send_hardfault(u8 code, u32 description);
u8 ble_host_svcmd_handle(u32 cmd, u32 *svc_args);
u8 ble_host_send_host_event(u32 host_event, u32 param0, u32 param1, u32 param2);
void ble_host_msg_hdl(void);



#endif  /// _BLE_HOST_H_

