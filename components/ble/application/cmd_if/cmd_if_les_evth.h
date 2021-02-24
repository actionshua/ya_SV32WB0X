/**
 * CMD interface LES event handle
 *
 */
#ifndef _CMD_IF_LES_EVTH_
#define _CMD_IF_LES_EVTH_
#include "condor_ssv_lib.h"

/**
 * query if any async event in queue
 *  return:
 *      1:      async_evt to issue
 *      0:      nothing
 *      < 0:    -err_code
 *
 */
typedef struct evt_query_result {

    s16 status;
    s16 evt_len;

} evt_query_result_st;

evt_query_result_st cmd_if_async_evt_query(u16 async_evt_len_max, u8* async_evt);

#endif // _CMD_IF_LES_EVTH_
