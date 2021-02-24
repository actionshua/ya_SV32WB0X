#ifndef CHIP_REG_H
#define CHIP_REG_H

#include "pcb_config.h"

#ifndef MAIN_CHIP
#error ! MAIN_CHIP not defined
#endif

#if (MAIN_CHIP == P7003)
#include "regs/p7003_reg.h"
#elif (MAIN_CHIP == P7005)
#include "soc_regs.h"
#else
#error please check your main chipid.
#endif

#endif /* end of include guard: CHIP_REG_H */
