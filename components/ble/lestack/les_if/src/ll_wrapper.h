#ifndef _LL_WRAPPER_H_
#define _LL_WRAPPER_H_



#include "les_if/api/inc/ll_api.h"



u32 ll_svcmd_handle(u32 svcmd, u32 *svc_args);
u8 ll_wrapper_send_air_event(LL_AIR_EVENT_TYPE type);


#endif  /// end of _LL_WRAPPER_H_
