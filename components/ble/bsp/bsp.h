/**
 * todo: to add some basic bsp function
 *  - (stack) message send/get
 *      + operation by pointer
 *  - (app) message send/get
 *      + operation by value
 *      + should reference ssv_msg_sent/ssv_msg_get by Felix.
 *  - memory alloc/free (need discussion)
 *      + should reference ssv_mem_alloc/ssv_mem_free by Felix.
 *
 */

/**
 *
 *
 */
#ifndef _BSP_H_
#define _BSP_H_

#include "ssv_types.h"
#include "drv/tmr/drv_timer.h"
//#include "ssv_condor_memory.h"

//#define NO_DISCARD       __attribute__ ((externally_visible))

typedef struct
{
    u32 *from_addr, *to_addr;
    u32 size;
} flash_write_st;

typedef struct
{
    volatile u32 *ptr;
    u32 data;
} phy_write_st;

typedef struct
{
    volatile u32 *ptr;
    u32 data;
    u8 bit_offset, bit_len;
} phy_write_set_bit_st;

typedef struct
{
    volatile u32 *ptr;
    u32 data, mask;
    u8 bit_len;
} phy_write_set_bit_v2_st;

typedef struct
{
    volatile u32 *ptr;
    u32 data, mask;
} phy_write_set_bit_v3_st;

typedef enum{
    E_RAM_SLEEP,
    E_RAM_HIB,
    E_RAM_READ_PHY,
    E_RAM_WRITE_PHY,
#if 0
    E_RAM_WRITE_PHY_SET_BIT,
    E_RAM_WRITE_PHY_SET_BIT_V2,
#endif
    E_RAM_WRITE_PHY_SET_BIT_V3,
    E_RAM_FLASH_WRITE,
    E_RAM_FLASH_ERASE_PAGE,
    E_RAM_UNLIMIT_LOOP,
    E_RAM_LOCK_LOOP,
    E_RAM_WFI,
    E_RAM_WFE,
} ram_oper;

typedef enum{
    E_RAMOP_NOT_FOUND = -1,
    E_RAMOP_SUCCESS = 0,
} ram_op_err;

typedef ram_op_err (*run_in_ram)(ram_oper oper, void *input, void *output);
//extern run_in_ram call_ram;

#define call_ram(oper, input, output) \
    ((run_in_ram)(M_CONDOR_TEXT_SRAM_ADDR|0x01))(oper, input, output)

enum E_ALL_HANDLER{
    E_TIMER_HANDLER,
    E_GPIO_HANDLER,
    E_MAX_HANDLER,
};

s32 ble_bsp_init(void);
void fence_init();

typedef s32 (*TMR_EVENT_HANDLER)(enum E_TIMER_ID tmrid, void *data);

extern TMR_EVENT_HANDLER bsp_register_timer_event(TMR_EVENT_HANDLER handler);
void ssv_process_event();

#include "pcb_config.h"

#if (MAIN_CHIP == P7003)
#define PHY_WRITE(addr, d)   \
    do { \
        phy_write_st p; \
        p.ptr = (u32*)addr; \
        p.data = d; \
        call_ram(E_RAM_WRITE_PHY, &p, NULL); \
    } while(0)
#elif (MAIN_CHIP == P7005)
#define PHY_WRITE(addr, d) \
    do { \
        REG32(addr) = d; \
    } while(0)
#else
#error please check your main chipid.
#endif


#if 0
#define PHY_WRITE_SET_BIT(addr, d, bo, bl)   \
    do { \
        phy_write_set_bit_st p; \
        p.ptr = (u32*)addr; \
        p.data = d; \
        p.bit_offset = bo; \
        p.bit_len = bl; \
        call_ram(E_RAM_WRITE_PHY_SET_BIT, &p, NULL); \
    } while(0)

#define PHY_WRITE_SET_BIT_V2(addr, d, m, bl)   \
    do { \
        phy_write_set_bit_v2_st p; \
        p.ptr = (u32*)addr; \
        p.data = d; \
        p.mask = m; \
        p.bit_len = bl; \
        call_ram(E_RAM_WRITE_PHY_SET_BIT_V2, &p, NULL); \
    } while(0)
#endif
#if (MAIN_CHIP == P7003)
#define PHY_WRITE_SET_BIT_V3(addr, d, m)   \
    do { \
        phy_write_set_bit_v3_st p; \
        p.ptr = (u32*)addr; \
        p.data = d; \
        p.mask = m; \
        call_ram(E_RAM_WRITE_PHY_SET_BIT_V3, &p, NULL); \
    } while(0)
#elif (MAIN_CHIP == P7005)
#define PHY_WRITE_SET_BIT_V3(addr, d, m) \
    do { \
        REG32(addr) &= m;   \
        REG32(addr) |= d;   \
    } while(0)
#else
#error please check your main chipid.
#endif

#if (MAIN_CHIP == P7003)
#define PHY_READ(addr) \
    ({ \
        u32 ret; \
        call_ram(E_RAM_READ_PHY, (void *)addr, &ret); \
        ret; })
#elif (MAIN_CHIP == P7005)
#define PHY_READ(addr) REG32(addr)
#else
#error please check your main chipid.
#endif

/*#if (__ARM_ARCH_ISA_THUMB==1)
#define __LOOP()  __asm__ volatile ("b .")
#elif (__NDS32_ISA_V3M__==1)
#define __LOOP()  __asm__ volatile ("1: b 1b")
#else
#error please check your mcu ISA.
#endif*/


#endif /* _BSP_H_ */

