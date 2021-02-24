#ifndef _APPL_LES_EVENT_DISPATCHER_H_
#define _APPL_LES_EVENT_DISPATCHER_H_



#include <stdint.h>
#include "les_if/api/inc/les_api.h"
#include "appl/common/appl_error.h"



typedef void (*appl_les_event_handler_t)(les_event_st *p_les_evt);



typedef enum
{
    APPL_LES_EVENT_DISPATCHER_MODE_DIRECT = 0,
    APPL_LES_EVENT_DISPATCHER_MODE_QUEUE,

} APPL_LES_EVENT_DISPATCHER_MODE;



typedef enum
{
    APPL_LES_EVENT_HANDLER_ID_0 = 0,
    APPL_LES_EVENT_HANDLER_ID_1,
    APPL_LES_EVENT_HANDLER_ID_2,
    APPL_LES_EVENT_HANDLER_ID_3,
    APPL_LES_EVENT_HANDLER_ID_4,
    APPL_LES_EVENT_HANDLER_ID_5,
    APPL_LES_EVENT_HANDLER_ID_6,
    APPL_LES_EVENT_HANDLER_ID_7,
    APPL_LES_EVENT_HANDLER_ID_8,
    APPL_LES_EVENT_HANDLER_ID_9,
    APPL_LES_EVENT_HANDLER_ID_MAX,

} APPL_LES_EVENT_HANDLER_ID;



typedef struct 
{
    appl_les_event_handler_t les_event_handler;

} appl_les_event_dispatcher_handler_st;



void appl_les_event_dispatcher_queue_init(APPL_LES_EVENT_DISPATCHER_MODE mode);
void appl_les_event_dispatcher_init(APPL_LES_EVENT_DISPATCHER_MODE use_queue);
void appl_les_event_dispatcher_pause(void);
void appl_les_event_dispatcher_resume(void);
APPL_RESULT appl_les_event_dispatcher_register_handler(appl_les_event_handler_t handler);
APPL_RESULT appl_les_event_dispatcher_unregister_handler(appl_les_event_handler_t handler);
void appl_les_event_dispatcher_handler(void);
les_event_st *appl_les_event_dispatcher_peak_event(void);
void appl_les_event_dispatcher_free_event(void);
void appl_les_event_dispatcher_flush_event(void);



#endif  /// end of _APPL_LES_EVENT_DISPATCHER_H_
