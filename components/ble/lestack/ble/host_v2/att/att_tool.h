#ifndef _ATT_TOOL_H_
#define _ATT_TOOL_H_



#include "att_def.h"



u32 att_cat(u8* dest, u8 dest_size, u32 idx_dest, const u8* src, u8 src_size) ;
u16 att_mtu_get(u16 conn_hdl);
void att_mtu_set(u16 conn_hdl, u16 mtu);
u8 att_uuid_compare(u8 x_len, const u8 *x_uuid, u8 y_len, const u8 *y_uuid);



#endif  /// end of _ATT_TOOL_H_

