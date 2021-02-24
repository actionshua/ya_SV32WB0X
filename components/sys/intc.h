#ifndef _INTC_H_
#define _INTC_H_

#include <stdint.h>
#include <stddef.h>

#if (CHIP_ID == 6020)
#if ((CHIP_SUB_ID == 1) || (CHIP_SUB_ID == 2))
#define INTC_BLE
#define INTC_NEW_GPIO
#endif
#endif
typedef void (*isr_func) (uint32_t irq_num);

void intc_init (void);

#if defined(INTC_BLE)
// aMH: sv6020B TDI FPGA HIGHEST = HIGH
#define INTC_LL_PRI_HIGHEST         (0)
#define INTC_LL_PRI_HIGH            (1)
#define INTC_LL_PRI_MIDDLE          (2)
#define INTC_LL_PRI_LOW             (3)

void intc_ll_register_isr(uint32_t irq_num, isr_func isr);
void intc_ll_set_priority(uint32_t irq_num, uint32_t irq_pri);
void intc_ll_irq_enable(uint32_t irq_num);
void intc_ll_irq_disable(uint32_t irq_num);
void intc_ll_irq_all_disable();
void intc_ll_irq_all_enable();
void intc_ll_sw_irq_force(uint32_t irq_num);
void intc_ll_sw_irq_clr(uint32_t irq_num);

#endif

void intc_register_isr (uint32_t irq_num, isr_func isr);
void intc_irq_clean (uint32_t irq_num);
void intc_irq_clean_all (void);

void intc_irq_set_priority (uint32_t irq_num, uint32_t irq_pri);
void intc_irq_set_priority_all (uint32_t irq_pri1, uint32_t irq_pri2);

void intc_irq_enable (uint32_t irq_num);
void intc_irq_disable (uint32_t irq_num);
void intc_irq_disable_all (void);
uint32_t intc_irq_status (void);

void intc_group02_irq_enable (uint32_t group02_irq_num, isr_func isr);
void intc_group02_irq_disable (uint32_t group02_irq_num);
uint32_t intc_group02_irq_status (void);

void intc_group15_irq_enable (uint32_t group15_irq_num, isr_func isr);
void intc_group15_irq_disable (uint32_t group15_irq_num);
uint32_t intc_group15_irq_status (void);

void intc_group31_irq_enable (uint32_t group31_irq_num, isr_func isr);
void intc_group31_irq_disable (uint32_t group31_irq_num);
uint32_t intc_group31_irq_status (void);

#endif // #ifndef  _INTC_H_
