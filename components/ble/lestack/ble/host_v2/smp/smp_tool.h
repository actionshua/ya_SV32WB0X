#ifndef _SMP_TOOL_H_
#define _SMP_TOOL_H_



#include "smp_def.h"
#include "smp_core.h"



void smp_tool_calculate_confirm(u8 *tk, u8 *rand128, smp_device_st device_master, smp_device_st device_slave, u8 *output);
void smp_tool_get_rand128(u8 *output);
void smp_tool_calculate_stk(u8 *tk, u8 *mrand, u8 *srand, u8 *output);
void smp_tool_calculate_hash(u8 *key, u8 *data, u8 *hash);



#endif  /// end of _SMP_TOOL_H_
