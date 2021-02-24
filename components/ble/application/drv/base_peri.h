#ifndef BASE_PERI_H
#define BASE_PERI_H

typedef struct base_peripheral {
    //volatile uint32_t *reset
    volatile uint32_t *enable;
    uint8_t reset_offset;
    uint8_t enable_offset;
} base_peri_st;

__STATIC_INLINE void bsp_peripheral_reset(base_peri_st *module) {
    // aMH todo remove mcu enable in sw reset.
    // reset not to clean mcu enable.
    CONDOR_SYS_REG->BRG_SW_RST = (1 << (module->reset_offset));// | (1<<SYS_REG_BRG_SW_RST_MCU_ENABLE_Pos);
}

__STATIC_INLINE void bsp_peripheral_enable(base_peri_st *module, bool enable) {
    if (enable) {
        *(module->enable) |= (1 << (module->enable_offset));
    } else {
        *(module->enable) &= ~(1 << (module->enable_offset));
    }
}

#endif /* end of include guard: BASE_PERI_H */
