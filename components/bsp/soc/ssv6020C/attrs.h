#ifndef ATTRS_H
#define ATTRS_H

#if defined(M_BUILD_ROM) && (M_BUILD_ROM == 1)
#define ATTRIBUTE_SECTION_FAST
#else
// define P1.
#define ATTRIBUTE_SECTION_FBOOT             __attribute__((section(".fast_boot_code")))
#define ATTRIBUTE_SECTION_OTA_FBOOT         __attribute__((section(".ota_fast_boot_code")))
#define ATTRIBUTE_SECTION_OTA_FBOOT_DATA    __attribute__((section(".ota_fast_boot_data")))
// define P2.
#define ATTRIBUTE_SECTION_RBOOT             __attribute__((section(".retention_boot")))
#define ATTRIBUTE_SECTION_ALLON             __attribute__((section(".allon")))
// define P3.
#define ATTRIBUTE_SECTION_FAST_TEXT         __attribute__((section(".prog_in_sram")))
#define ATTRIBUTE_SECTION_FAST              __attribute__((section(".prog_in_sram")))

#define ATTRIBUTE_SECTION_NORMAL_TEXT       __attribute__((section(".prog_in_bus_ram")))
#define ATTRIBUTE_SECTION_NORMAL_DATA       __attribute__((section(".data_in_bus_ram")))
#define ATTRIBUTE_SECTION_NORMAL            ATTRIBUTE_SECTION_NORMAL_DATA
#define ATTRIBUTE_SECTION_NORMAL_BSS        __attribute__((section(".bss_in_bus_ram")))

#define ATTRIBUTE_SECTION_BLE_RESTORE       __attribute__((section(".ble_restore")))

#if (0 == BLE_EN)
#define ATTRIBUTE_SECTION_FAST_L2STACK      ATTRIBUTE_SECTION_FAST_TEXT
#define ATTRIBUTE_SECTION_FAST_L3STACK      ATTRIBUTE_SECTION_FAST_TEXT
#define ATTRIBUTE_SECTION_FAST_POWERSAVE    ATTRIBUTE_SECTION_FAST_TEXT
#else
#define ATTRIBUTE_SECTION_FAST_L2STACK
#define ATTRIBUTE_SECTION_FAST_L3STACK
#define ATTRIBUTE_SECTION_FAST_POWERSAVE
#endif

#if MESH_BLE_EN
#define ATTRIBUTE_SECTION_MESH_BLE    ATTRIBUTE_SECTION_NORMAL
#else
#define ATTRIBUTE_SECTION_MESH_BLE
#endif

//#define ATTRIBUTE_SECTION_FAST_TEXT         
//#define ATTRIBUTE_SECTION_FAST              
// define P4.
#define ATTRIBUTE_SECTION_SLOW_TEXT
// define P5.
#define ATTRIBUTE_SECTION_DATA
#define ATTRIBUTE_SECTION_LP_SRAM
// define P5.
#define ATTRIBUTE_SECTION_FAST_DATA
// define P6.
#define ATTRIBUTE_SECTION_BSS
// define P7.
#define ATTRIBUTE_SECTION_RSRAM             __attribute__((section(".rsram")))


#define ATTRIBUTE_CFG_PAD                   __attribute__((section(".cfg_pad_data")))
#endif
#define ATTRIBUTE_WEAK                      __attribute__((weak))
#define ATTRIBUTE_PACK                      __attribute__ ((__packed__))  

// tools
#define ATTRIBUTE_SECTION_CLI_BUF           ATTRIBUTE_SECTION_NORMAL_BSS

// peripheral
#define ATTRIBUTE_SECTION_UART_FAST_TEXT    ATTRIBUTE_SECTION_FAST_TEXT
#define ATTRIBUTE_SECTION_UART_ISR          ATTRIBUTE_SECTION_FAST_TEXT
#define ATTRIBUTE_SECTION_HSUART_FAST_TEXT  ATTRIBUTE_SECTION_FAST_TEXT
#define ATTRIBUTE_SECTION_HSUART_ISR        ATTRIBUTE_SECTION_FAST_TEXT
#define ATTRIBUTE_SECTION_DMA_FAST_TEXT     ATTRIBUTE_SECTION_FAST_TEXT
#define ATTRIBUTE_SECTION_DMA_ISR           ATTRIBUTE_SECTION_FAST_TEXT
#endif /* end of include guard: ATTRS_H */
