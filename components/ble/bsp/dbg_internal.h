#ifndef DBG_INTERNAL_H
#define DBG_INTERNAL_H

// aMH todo: finish this.
#define CONDOR_DBG                      ((CONDOR_UART_Type        *) UART_REG_BASE)

#define DBG_ENABLE_IER()    \
    CONDOR_DBG->IER |= ((1<<UART_IER_THR_EMPTY_IE_Pos) | (1<<UART_IER_TX_THRL_IE_Pos))
#define DBG_DISABLE_IER()   \
    CONDOR_DBG->IER &= ~((1<<UART_IER_THR_EMPTY_IE_Pos) | (1<<UART_IER_TX_THRL_IE_Pos))
#define DBG_INT_STATUS()    (CONDOR_DBG->INT_MAP)

#define DBG_TX_L(status)    (status & UART_INT_MAP_TX_L_Msk)

#define DBG_PUT_DATA(data)  \
    (CONDOR_DBG->DATA = data)
#define DBG_GET_DATA()      (CONDOR_DBG->DATA)
#define DBG_RX_REV_STATUS() (DBG_INT_STATUS() & UART_INT_MAP_RX_RECIEVED_Msk)

#define DBG_GPIO_SETUP()
#define DBG_BAUDRATE()  do { CONDOR_DBG->SPR = 34; } while(0)
#define DBG_INIT_THR()  do { CONDOR_DBG->TTHR = 0xF0; } while(0)

#define DBG_INT_TX_INIT() \
    NVIC_EnableIRQ(DBG_TX_IRQn); \
    NVIC_SetPriority(DBG_TX_IRQn, 2);

#define DBG_INT_RX_INIT() \
    NVIC_EnableIRQ(DBG_RX_IRQn); \
    NVIC_SetPriority(DBG_RX_IRQn, 3);

#define DBG_WAIT_TX_EMPTY() \
    do { \
        while ((CONDOR_DBG->LSR_b.TX_EMPTY == 0)) {} \
    } while(0)

#define DBG_INIT_IER() \
    do { \
        CONDOR_DBG->IER = \
             ((1<<(UART_IER_DATA_RDY_IE_Pos)) | (1<<UART_IER_THR_EMPTY_IE_Pos) | (1<<UART_IER_TX_THRL_IE_Pos)); \
    } while (0)

#define DBG_INIT_MASK() \
    do { \
        CONDOR_INT_REG->INT1_MASK_b.MASK1_DBG_UART_TX = 0; \
        CONDOR_INT_REG->INT1_MASK_b.MASK1_DBG_UART_RX = 0; \
    } while(0)

#endif /* end of include guard: DBG_INTERNAL_H */
