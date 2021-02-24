#ifndef _L2CAP_SLICER_H_
#define _L2CAP_SLICER_H_



#include "l2cap_def.h"



u16 l2cap_slicer_get_sdu_pld_value(l2cap_sdu_st *sdu, u16 value_offset, u16 value_size, u8 *value);
u16 l2cap_slicer_set_sdu_pld_value(l2cap_sdu_st *sdu, u16 value_offset, u16 value_size, u8 *value);



#endif  /// end of _L2CAP_SLICER_H_
