################################################################
# Project setting
################################################################
ROM_MODE                        := 0
ROM_VERSION                     := V1002

################################################################
# Debugger option
################################################################
#BUILD_OPTION                    := DEBUG
#BUILD_OPTION                    := RELEASE
BUILD_OPTION                     := PERFORMANCE
SUPPORT_EXCEPTION_DUMP           := 1
SUPPORT_SRM_TASK_LOG             := 0
SUPPORT_OSAL_SYS_INFO            := 1
SUPPORT_SRM_DBG_INFO             := 0

################################################################
# Partition Setting, influence FOTA
################################################################
SETTING_PARTITION_MAIN_SIZE     := 940K
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

################################################################
# utility feature option
################################################################
SUPPORT_CLI                     := 1
SUPPORT_ATCMD                   := 0
SUPPORT_CUSTOM_CMD              := 1

################################################################
# WIFI feature option
################################################################
SETTING_THROUGHPUT_HIGH         := 0
RC_MINSTREL_EN                  := 1
RC_NATIVE_EN                    := 0
WPS_EN                          := 0
EAP_EN                          := 0
WIFI_REPEATER_EN                := 0
SMARTCONFIG_EN                  := 0
TCPIPSTACK_EN                   := 1
LWIP_PATH                       := lwip-1.4.0
#LWIP_PATH                      := lwip-2.0.3
LWIP_RESOURCES_PARAMETER        := 4
# 0:PBUF_SIZE=12, 1:PBUF_SIZE=18, 2:PBUF_SIZE=24, 3:Customer modify in lwipopts.h, 4:Dynamic allocate memory
DEFAULT_RATE_MASK               := 0x2B1
COUNTRY_CODE                    := 0
# DEF=0, TW=1, CN=2, HK=3, US=4, JP=5 Please check the COUNTRY_CODE in wificonf.h


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
PING_EN                         := 1
TFTP_EN                         := 1
# 0: none, 1:pvmp3, 2:helix
SETTING_MP3_DECODER             := 1
# 0: none, 1:shine
SETTING_MP3_ENCODER             := 0
ACOUSTIC_EN                     := 1
CMSIS_EN                        := 1
# 0: none, 1:es8374, 2:es8311 3: es8388
AUDIO_CODEC_EN                  := 1
CODEC_TYPE                      ?= 2

# 0: none, 2: kws not ds demo 
DEMO_TYPE                       ?= 2

SUPPORT_LITTLEVGL               := 6.1.2
#SUPPORT_LITTLEVGL               := 7.1.0

SETTING_CACHE_WT                := 1
SUPPORT_SPI_LCM                 := 1
###################################################################
# Filesystem feature
###################################################################
SUPPORT_FFS                     := 2
# SD Card
SUPPORT_SDC                     := 1

################################################################
# Misc setting
################################################################
#UART_IO_NUM                     := defined_by_chip
UART_IO_NUM                     := 0
# 0 ==> Debug UART, 1 ==> HSUART1, 2==> HSUART2
UART_BAUD_RATE                  := 115200
SUPPORT_CXX                     := 0
ISR_STACK_SIZE                  := 2048

################################################################
# BLE option
################################################################
BLE_EN                          := 0

################################################################
# Security setting
################################################################
ANTI_CLONE_PROTECTION           := 0
SECURE_BOOT                     := 0
