#ifndef PCB_CONDOR_C_FPGA_H
#define PCB_CONDOR_C_FPGA_H


#include "condor_chipid.h"

//#define FPGA
//#define CONDOR_A_RF

#define MAIN_CHIP                        (P7005)



/// UART0 GPIO CONFIG
#define UART0_TXD_GPIO_PIN              (6)
#define UART0_RXD_GPIO_PIN              (5)



/// UART1 GPIO CONFIG
#define UART1_TXD_GPIO_PIN              (25)
#define UART1_RXD_GPIO_PIN              (24)
#define UART1_CTS_GPIO_PIN              (23)
#define UART1_RTS_GPIO_PIN              (26)

#endif /* end of include guard: PCB_CONDOR_C_FPGA_H */
