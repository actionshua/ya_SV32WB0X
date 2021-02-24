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
SETTING_PARTITION_MAIN_SIZE     := 620K
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

# in fpga SYS_MCU_MAX_CLK is not useful.
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
SUPPORT_ISR_USAGE               := 0

################################################################
# WIFI feature option
################################################################
SETTING_THROUGHPUT_HIGH         := 1
RC_MINSTREL_EN                  := 0
RC_NATIVE_EN                    := 1
EAP_EN                          := 0
WIFI_REPEATER_EN                := 0
SMARTCONFIG_EN                  := 0
TCPIPSTACK_EN                   := 1
LWIP_PATH                       := lwip-1.4.0
#LWIP_PATH                      := lwip-2.0.3

################################################################
# Third_Party feature option
################################################################
WAC_EN                          := 0
HTTPD_EN                        := 0
CJSON_EN                        := 1
HTTPC_EN                        := 1
MQTT_EN                         := 0
MBEDTLS_EN                      := 1
IPERF3_EN                       := 1
IPERF2_EN                       := 0
AIRKISSAES_EN                   := 0
AIRKISS_EN                      := 0
PING_EN                         := 1
TFTP_EN                         := 1
JD_CLOUD_EN                     := 0

###################################################################
# Filesystem feature
###################################################################
SUPPORT_FFS                     := 2
# SD Card
SUPPORT_SDC                     := 0

################################################################
# Misc setting
################################################################
UART_IO_NUM                     := 1
# 0 ==> Debug UART, 1 ==> HSUART1, 2==> HSUART2
UART_BAUD_RATE                  := 115200
SUPPORT_CXX                     := 0
ISR_STACK_SIZE                  := 2048

################################################################
# Security setting
################################################################
ANTI_CLONE_PROTECTION           := 0
SECURE_BOOT                     := 0
