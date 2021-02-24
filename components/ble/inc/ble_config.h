#ifndef _CONFIG_H_
#define _CONFIG_H_

#define BLE_LINK_LAYER_DBG 1

/**
 * ssv fw configuration file.
 *  -todo: need some bsp related configurations
 *      + message
 *      + timer
 *  -todo: need some stack configurations
 *      + about packets (trade-off between heap space with throughput)
 *      + about link-layer abilities:
 *          + state combination
 *          + preferred parameters
 *
 */

/*
 * ONLY for test code
 */
#define CH_SEL_ALG2         (0)
#define CON_INI_BV_04_C     (0) //Connection Initiation Timeout
#define CON_INI_BV_03_C     (0) //Connection_Initiation_Missed_Replies
#define PAC_MAS_BV_01_C     (0) //Unknown Packet From Slave, slave tx LL_CONNECTION_UPDATE_IND
#define CON_MAS_BV_19_C     (0) //Connection Control Timeout
/**
 * ssv fw identification
 *
 */

#define CONFIG_VENDOR           "South Silicon Valley"
#define CONFIG_VENDOR_ID
#ifndef PROJECT_SMAC
#define CONFIG_PRODUCT_STR      "Condor"
#endif
#define CONFIG_PRODUCT_ID
#define CONFIG_PRODUCT_VERSION
#define CONFIG_FW_NAME_STR
#define CONFIG_FW_VERSION

/**
 * system configuration
 *
 */

// # for operation clock
// # for operation clock
#define SYS_FCLK                32000               // kHz
#define SYS_FCLK_SCA            25                  // ppm
// # for fast boot
#define SYS_BOOTCLK             32000               // kHz
#define SYS_BOOTCLK_SCA         500                 // ppm

#define SYS_SCLK                32
#define SYS_SCLK_SCA            1000                // ppm

#ifdef __SSV_LINUX_SIM__                            // sram base address
#define SYS_SRAM_BADDR          0x00000004          // use a non-zero dummpy number
#else
#define SYS_SRAM_BADDR_DLM         (0x00100000-4)      // a trick
                                                    // to make offset-addr 0x0000000 stands for null.
#define SYS_SRAM_BADDR_BUSRAM      (0x60000000-4)
#endif

/**
 * Timer setup
 */
#define MAX_SW_TIMER            5
#define SW_TMR_TICK             100                 // sw timer 1 tick = 100ms
#define M_TIMER_DYNAMIC_IRQ       (0)

/**
 *  Cli UART
 */

#define CLI_UART_BR             115200              // CPU(CLI) UART Baud Rate
#define CLI_ENABLE              1                   // Enable/Disable CLI
#define CLI_BUFFER_SIZE         80                  // CLI Buffer size (char)
#ifndef PROJECT_SMAC
#define CLI_ARG_SIZE            12                  // The number of arguments
#define CLI_PROMPT              "ble> "
#endif

/**
 * protocol configuration
 *
 */
#define CFG_BLE_TX_PDUS 32
#define CFG_BLE_RX_PDUS 32

#define CFG_BD_ADDR     0xcc9876543210  // TODO: to update
#define CFG_BD_ADDR_U8  {0x10, 0x32, 0x54, 0x76, 0x98, 0xcc}

/**
 * link-layer configuration
 *
 */
#define LL_ADVS         1                   // 1 ADV, NOT configurable
#define LL_SCANS        1                   // 1 SCAN NOT configurable
#define LL_INITS        1                   // 1 INIT NOT configurable
#define LL_SLAVES       1                   // 1 SLAVE, NOT configurable
#define CFG_LL_MASTERS  1
#define CFG_LL_MASTERS_MAX  3
#define CFG_LL_CONNS    (LL_ADVS +LL_SCANS +LL_INITS +LL_SLAVES +CFG_LL_MASTERS_MAX)

// WARNING (CFI-80): msg size for link-layer and CFG_LL_CONN_PDUS are strongly co-related.
#define CFG_LL_CONN_PDUS    8   // (max) RX PDUs in a connection event
#define CFG_LL_CONN_ACTIONS 8   // (max) t/rx actions in a connection event

#define CFG_ADV_AIR_EVENT_WINDOW                1200
#ifdef FPGA
#define CFG_NONCONN_ADV_AIR_EVENT_WINDOW        2000
#define CFG_ADV_AIR_EVENT_POST_PROCESS_TIME     500
#else
#define CFG_NONCONN_ADV_AIR_EVENT_WINDOW        400
#define CFG_ADV_AIR_EVENT_POST_PROCESS_TIME     20
#endif

#define CFG_SCAN_AIR_EVENT_WINDOW               250000
#ifdef FPGA
#define CFG_SCAN_AIR_EVENT_POST_PROCESS_TIME    500
#else
#define CFG_SCAN_AIR_EVENT_POST_PROCESS_TIME    100
#endif

#define CFG_INITA_AIR_EVENT_POST_PROCESS_TIME    500

#define CFG_DATA_AIR_EVENT_WINDOW               9000    // 8T/8R
#define CFG_DATA_AIR_EVENT_WINDOW_MAX           50000
#define CFG_DATA_AIR_EVENT_POST_PROCESS_TIME    500

// CondorA RF use SPI as interface, take around extra 100us
#include "pcb_config.h"
// TODO: make pre process time configurable
#ifdef CONDOR_A_RF
#define CFG_ADV_AIR_EVENT_PRE_PROCESS_TIME      (500 +100)
#define CFG_SCAN_AIR_EVENT_PRE_PROCESS_TIME     (500 +100)
#define CFG_INITA_AIR_EVENT_PRE_PROCESS_TIME    (500 +100)
#define CFG_DATA_AIR_EVENT_PRE_PROCESS_TIME     (500 +100)
#else
#ifdef FPGA
#define CFG_AIR_PROTO_PRE_PROCESS_TIME          210
#define CFG_ADV_AIR_EVENT_PRE_PROCESS_TIME      500
#define CFG_SCAN_AIR_EVENT_PRE_PROCESS_TIME     500
#else
#define CFG_AIR_PROTO_PRE_PROCESS_TIME          (150)
#define CFG_ADV_AIR_EVENT_PRE_PROCESS_TIME      (CFG_AIR_PROTO_PRE_PROCESS_TIME+100)
#define CFG_SCAN_AIR_EVENT_PRE_PROCESS_TIME     (CFG_AIR_PROTO_PRE_PROCESS_TIME+100)
#endif

#define CFG_INITA_AIR_EVENT_PRE_PROCESS_TIME    (500 +100)
#define CFG_DATA_AIR_EVENT_PRE_PROCESS_TIME     (500)
#endif

#define CFG_EARLY_NOTIFY_TIME_ADVCH     CFG_ADV_AIR_EVENT_PRE_PROCESS_TIME
#define CFG_EARLY_NOTIFY_TIME_DATACH    CFG_DATA_AIR_EVENT_PRE_PROCESS_TIME

#define CFG_SLAVE_SUBRATE_LOCK                  0
#define CFG_SLAVE_SUBRATE_MINIMUM_TX_LATENCY    true

#define CFG_MASTER_SUBRATE_LOCK                  0
#define CFG_MASTER_SUBRATE_MINIMUM_TX_LATENCY    true
/**
 * default link-layer scheduing parameters
 *
 */
#define CFG_ADV_INTV_MIN        ((BLE_LL_US)20000)
#define CFG_SCAN_SUB_WINDOW     ((BLE_LL_US)250000)
#define CFG_INITA_SUB_WINDOW    ((BLE_LL_US)250000)
#define CFG_MASTER_SLOT_INTV    ((BLE_LL_US)7500)
#define CFG_MASTER_SLOT_INC_MIN 10

#endif /* _CONFIG_H_ */

