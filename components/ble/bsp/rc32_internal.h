#ifndef RC32_INTERNAL_H
#define RC32_INTERNAL_H


#define M_SW2_MAX               (0xFF)
#define M_SW1_MAX               (0x1FF)

#if defined(FPGA)
static uint8_t sg_rc_count = 0;
static uint32_t sg_sw1 = 64;
static uint32_t sg_sw2 = 64;
#endif

__STATIC_INLINE void rc32_rc_start_count_workaround(uint8_t rccount) {
}

__STATIC_INLINE void rc32_rc_start_count(uint8_t rccount) {
#if !defined(FPGA)
    OS_EnterCritical();
    PHY_WRITE(&(CONDOR_CSR_PHY->_32KRC_COUNTER_), (0x01 << CSR_PHY__32KRC_COUNTER__RG_EN_RCCOUNT_Pos) | (rccount << CSR_PHY__32KRC_COUNTER__RG_RC_COUNT_Pos) | (0x00 << CSR_PHY__32KRC_COUNTER__RG_COUNT_BEGIN_Pos) | (PHY_READ(&(CONDOR_CSR_PHY->_32KRC_COUNTER_)) & 0xC0));
    __NOP(); // 1
    __NOP(); // 2
    __NOP(); // 3
    __NOP(); // 4
    __NOP(); // 5
    __NOP(); // 6
    __NOP(); // 7  (must!!)
    __NOP(); // 8
    __NOP(); // 9
    __NOP(); // 10
    __NOP(); // 11
    __NOP(); // 12
    __NOP(); // 13
    __NOP(); // 14
    __NOP(); // 15
    __NOP(); // 16
    __NOP(); // 17
    __NOP(); // 18
    __NOP(); // 19
    PHY_WRITE(&(CONDOR_CSR_PHY->_32KRC_COUNTER_), (0x01 << CSR_PHY__32KRC_COUNTER__RG_EN_RCCOUNT_Pos) | (rccount << CSR_PHY__32KRC_COUNTER__RG_RC_COUNT_Pos) | (0x01 << CSR_PHY__32KRC_COUNTER__RG_COUNT_BEGIN_Pos) | (PHY_READ(&(CONDOR_CSR_PHY->_32KRC_COUNTER_)) & 0xC0));
    OS_ExitCritical();
#else
    sg_rc_count = rccount;
#endif
}

__STATIC_INLINE uint32_t rc32_get_counter_out();
__STATIC_INLINE void rc32_rc_count_disable(uint8_t rccount) {
#if !defined(FPGA)
    OS_EnterCritical();
    PHY_WRITE(&(CONDOR_CSR_PHY->_32KRC_COUNTER_),  (0x00 << CSR_PHY__32KRC_COUNTER__RG_EN_RCCOUNT_Pos) | (rccount << CSR_PHY__32KRC_COUNTER__RG_RC_COUNT_Pos) | (0x00 << CSR_PHY__32KRC_COUNTER__RG_COUNT_BEGIN_Pos) | (PHY_READ(&(CONDOR_CSR_PHY->_32KRC_COUNTER_)) & 0xC0));
    while(rc32_get_counter_out());
    OS_ExitCritical();
#else
    sg_rc_count = 0;
#endif
}

__STATIC_INLINE void rc32_por_rc_start_count() {
#if !defined(FPGA)
    PHY_WRITE(&(CONDOR_CSR_PHY->_32KRC_COUNTER_),  (0x01 << CSR_PHY__32KRC_COUNTER__RG_EN_RCCOUNT_Pos) | (0x00 << CSR_PHY__32KRC_COUNTER__RG_RC_COUNT_Pos) | (0x01 << CSR_PHY__32KRC_COUNTER__RG_COUNT_BEGIN_Pos));
#endif
}

__STATIC_INLINE uint32_t rc32_get_counter_out() {
#if !defined(FPGA)
    if ((PHY_READ(&(CONDOR_CSR_PHY->_32KRC_COUNTER_)) & (0x01 << CSR_PHY__32KRC_COUNTER__RG_COUNT_BEGIN_Pos)) == 0) {
        return (PHY_READ(&(CONDOR_CSR_PHY->RC_COUNTER_OUT)) & CSR_PHY_RC_COUNTER_OUT_RG_RC_COUNT_OUT_Msk);
    } else {
        return 0;
    }
#else
    return ((sg_rc_count+1) * 1952 + ((CONDOR_SYS_REG->LFSR_RAND&0x1F) * ((CONDOR_SYS_REG->LFSR_RAND&1)?-1:1)));
#endif
}

__STATIC_INLINE void rc32_por_set_sw2_bitn(uint8_t bit) {
#if !defined(FPGA)
    CONDOR_CSR_PMU->REG_RC32K |= ((1<<bit)<<CSR_PMU_REG_RC32K_RG_SX_RC32K_SW2_Pos);
#endif
}

__STATIC_INLINE void rc32_por_clr_sw2_bitn(uint8_t bit) {
#if !defined(FPGA)
    CONDOR_CSR_PMU->REG_RC32K &= ~((1<<bit)<<CSR_PMU_REG_RC32K_RG_SX_RC32K_SW2_Pos);
#endif
}

//__STATIC_INLINE void rc32_por_sw_init() {
//    CONDOR_CSR_PMU->REG_RC32K = ((1<<M_POR_N_START)<<CSR_PMU_REG_RC32K_RG_SX_RC32K_SW2_Pos) | ((M_POR_SW1_DEF) << CSR_PMU_REG_RC32K_RG_SX_RC32K_SW1_Pos);
//}

__STATIC_INLINE uint32_t rc32_get_sw2() {
#if !defined(FPGA)
    return CONDOR_CSR_PMU->REG_RC32K_b.RG_SX_RC32K_SW2;
#else
    return sg_sw2;
#endif
}

__STATIC_INLINE void rc32_set_sw2(uint32_t sw2) {
#if !defined(FPGA)
    CONDOR_CSR_PMU->REG_RC32K_b.RG_SX_RC32K_SW2 = sw2;
#else
    sg_sw2 = sw2 & M_SW2_MAX;
#endif
}

__STATIC_INLINE void rc32_set_sw1_bitn(uint8_t bit) {
#if !defined(FPGA)
    CONDOR_CSR_PMU->REG_RC32K |= ((1<<bit)<<CSR_PMU_REG_RC32K_RG_SX_RC32K_SW1_Pos);
#endif
}

__STATIC_INLINE void rc32_clr_sw1_bitn(uint8_t bit) {
#if !defined(FPGA)
    CONDOR_CSR_PMU->REG_RC32K &= ~((1<<bit)<<CSR_PMU_REG_RC32K_RG_SX_RC32K_SW1_Pos);
#endif
}

__STATIC_INLINE uint16_t rc32_get_sw1() {
#if !defined(FPGA)
    return (CONDOR_CSR_PMU->REG_RC32K & CSR_PMU_REG_RC32K_RG_SX_RC32K_SW1_Msk) >> CSR_PMU_REG_RC32K_RG_SX_RC32K_SW1_Pos;
#else
    return sg_sw1;
#endif
}

__STATIC_INLINE void rc32_set_sw1(uint16_t sw1) {
#if !defined(FPGA)
    register uint32_t orig = CONDOR_CSR_PMU->REG_RC32K;
    orig &= ~CSR_PMU_REG_RC32K_RG_SX_RC32K_SW1_Msk;
    orig |= ((sw1 << CSR_PMU_REG_RC32K_RG_SX_RC32K_SW1_Pos) & CSR_PMU_REG_RC32K_RG_SX_RC32K_SW1_Msk);
    CONDOR_CSR_PMU->REG_RC32K = orig;
#else
    sg_sw1 = sw1 & M_SW1_MAX;
#endif
}

__STATIC_INLINE void rc32_por_rc_counter_setup() {
    // aMH workaround check!!.
    // condorC unknown.
}
#endif /* end of include guard: RC32_INTERNAL_H */

