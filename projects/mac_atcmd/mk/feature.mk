################################################################
# Project setting
################################################################
ROM_MODE                        := 0
ROM_VERSION                     := V1002

################################################################
# Debugger option
################################################################
#BUILD_OPTION                    := PERFORMANCE
#BUILD_OPTION                    := DEBUG
BUILD_OPTION                     := RELEASE
SUPPORT_EXCEPTION_DUMP           := 1
SUPPORT_SRM_TASK_LOG             := 0
SUPPORT_OSAL_SYS_INFO            := 1
SUPPORT_SRM_DBG_INFO             := 1

################################################################
# Partition Setting, influence FOTA
################################################################
SETTING_PARTITION_MAIN_SIZE     := 640K
SETTING_FLASH_TOTAL_SIZE        := defined_by_chip
SETTING_PARTITION_USER_RAW_SIZE := 8K
SETTING_PSRAM_HEAP_SIZE         := 0

################################################################
# System Setting
################################################################
SUPPORT_LOW_POWER               := 1

#SYS_BUS_CLK                     := 40M
#SYS_BUS_CLK                     := 80M
SYS_BUS_CLK                      := 160M

#SYS_MCU_MAX_CLK                 := 80M
#SYS_MCU_MAX_CLK                 := 160M
#SYS_MCU_MAX_CLK                 := 240M
#SYS_MCU_MAX_CLK                 := 320M
#SYS_MCU_MAX_CLK                 := 480M
SYS_MCU_MAX_CLK                  := defined_by_chip

#SYS_FLASH_CLK                   := 40M
SYS_FLASH_CLK                    := 80M

#XIP_BIT                        := 2
XIP_BIT                         := 4

# 0 ==> disable fota, 1==> filesystem fota, 2 ==> ping pong fota.
FOTA_OPTION                     := 1

# SETTING_SRAM_OPTION = 1 ==> SRAM: MAX_SRAM
# SETTING_SRAM_OPTION = 0 ==> SRAM: 256KB
SETTING_SRAM_OPTION             := 1

SUPPORT_MCU_UNALIGNMENT         := 1

################################################################
# utility feature option
################################################################
SUPPORT_CLI                     := 0
SUPPORT_ATCMD                   := 1
SUPPORT_CUSTOM_CMD              := 1
SUPPORT_ISR_USAGE               := 0

################################################################
# BLE option
################################################################
BLE_EN                          := 0
BLE_DEBUG_ONLY                  := 0

# Thirdparty
MESH_BLE_EN                     := 0
##if enable GATTS or GATTC, GAP must be enabled
BLE_GAP_EN                      := 0
BLE_GATTS_EN                    := 0
BLE_GATTC_EN                    := 0
BLE_GATTS_API_TEST_EN           := 0
BLE_GATTC_API_TEST_EN           := 0
BLE_GAP_ATCMD_EN                := 0
BLE_GATTS_ATCMD_EN              := 0
BLE_GATTC_ATCMD_EN              := 0
SETTING_BLE_UART                := 0
BLE_GPIO_PROFILE                := 0
MESH_BLE_OTHER_MODEL_EN         := 0
MESH_BLE_AUTO_RUN_EN            := 0
#BLE_AGGR_ADV_REPORT ONLY support MESH(HCI_RAM_MODE)
BLE_AGGR_ADV_REPORT             := 0

################################################################
# WIFI feature option
################################################################
SETTING_THROUGHPUT_HIGH         := 1
TCPIPSTACK_EN                   := 1
LWIP_PATH                       := lwip-1.4.0
#LWIP_PATH                      := lwip-2.0.3
LWIP_RESOURCES_PARAMETER        := 1
# 0:PBUF_SIZE=12, 1:PBUF_SIZE=18, 2:PBUF_SIZE=24, 3:Customer modify in lwipopts.h, 4:Dynamic allocate memory
RC_MINSTREL_EN                  := 0
RC_NATIVE_EN                    := 1
EAP_EN                          := 0
WIFI_REPEATER_EN                := 0
SOFTAP_EN                       := 1
SMARTCONFIG_EN                  := 1
DEFAULT_RATE_MASK               := 0x2B1
COUNTRY_CODE                    := 0
# DEF=0, TW=1, CN=2, HK=3, US=4, JP=5 Please check the COUNTRY_CODE in wificonf.h
SAE_EN                          := 1
PMF_EN                          := 1
AMPDU_RX_EN                     := 0
CSI_EN                          := 0

################################################################
# Third_Party feature option
################################################################
HTTPD_EN                        := 0
CJSON_EN                        := 1
HTTPC_EN                        := 1
MQTT_EN                         := 0
MBEDTLS_EN                      := 1
IPERF3_EN                       := 1
IPERF2_EN                       := 0
AIRKISSAES_EN                   := 1
AIRKISS_EN                      := 1
RTLINK_EN                       := 1
PING_EN                         := 1
TFTP_EN                         := 1
JD_CLOUD_EN                     := 0
CMSIS_EN                        := 0

###################################################################
# Filesystem feature
###################################################################
# 0 ==> disable FFS, 1 ==> use spiffs, 2 ==> use littlefs
SUPPORT_FFS                     := 2
# SD Card
SUPPORT_SDC                     := 0

################################################################
# Misc setting
################################################################
UART_IO_NUM                     := defined_by_chip
# 0 ==> Debug UART, 1 ==> HSUART1, 2==> HSUART2
UART_BAUD_RATE                  := 115200
BOOTLOADER_ENABLE_QE            := 0
SUPPORT_CXX						:= 0
ISR_STACK_SIZE                  := 2048
SUPPORT_LOG_RINGBUFFER          := 0
SUPPORT_LOG_RX_BUF_SIZE         := 512
SUPPORT_LOG_TX_BUF_SIZE         := 4096

################################################################
# Security setting
################################################################
ANTI_CLONE_PROTECTION           := 0
SECURE_BOOT                     := 0
