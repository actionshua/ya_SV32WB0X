################################################################
# Project global
################################################################
FLASH_MODE                                       ?= 1
FLASH_ROM                                        ?= 0
XIP_MODE                                         ?= 1
ROM_MODE                                         ?= 0
ROM_VERSION                                      ?= V1002

################################################################
# TCP/IP option
################################################################
LWIP_PATH                                        ?= lwip-1.4.0
TCPIPSTACK_EN                                    ?= 1

################################################################
# BLE option
################################################################
BLE_EN                                           ?= 0
SUPPORT_BLE_UART                                 ?= 0

################################################################
# Wifi option
################################################################
WIFI_REPEATER_EN                                 ?= 0
SOFTAP_EN                                 		 ?= 1
HK_EN											 ?= 0
LWIP_RESOURCES_PARAMETER                         ?= 2
RC_MINSTREL_EN                                   ?= 1
RC_NATIVE_EN                                     ?= 0
WPS_EN                                           ?= 0
EAP_EN                                           ?= 0
SUPPORT_WPA_SUPPLICANT                           ?= 1
DEFAULT_RATE_MASK                                ?= 0x2B1
COUNTRY_CODE                                     ?= 0
SAE_EN                                           ?= 0
PMF_EN                                           ?= 1
EXTPA_EN                                         ?= 0
CSI_EN                                           ?= 0
BEACON_LOSS_DETECT_EN			                 ?= 0
PHY_SNIFFER_EN			                         ?= 0

AMPDU_TX_EN                                      ?= 0
AMPDU_RX_EN                                      ?= 0
LWIP_MEMP_DEBUG_EN                               ?= 0
IDM                                              := 1
MBOX                                             := 1

SKIP_DHCP_DOES_ARP_CHECK                         ?= 0

################################################################
# Performance option
################################################################
SETTING_THROUGHPUT_HIGH                          ?= 1
SETTING_ICACHE                                   ?= 1
SYS_BUS_CLK                                      ?= 80M
SYS_MCU_MAX_CLK                                  ?= defined_by_chip
SYS_FLASH_CLK                                    ?= 80M
XIP_BIT                                          ?= 2

# 6020 SRAM option 0: 256KB (ILM/DLM off)
#           option 1: MAX SRAM
SETTING_SRAM_OPTION                              ?= 1

# 6020 CACHE option 0: WB
#            option 1: WT
SETTING_CACHE_WT                                 ?= 0
SUPPORT_MCU_UNALIGNMENT                          ?= 0
################################################################
# Debugger option
################################################################
BUILD_OPTION                                     ?= RELEASE
SUPPORT_EXCEPTION_DUMP                           ?= 1
SUPPORT_SRM_TASK_LOG                             ?= 0
SUPPORT_OSAL_SYS_INFO                            ?= 1
SUPPORT_SRM_DBG_INFO                             ?= 1
SUPPORT_SRM_MEM_INFO                             ?= 1
ifneq ($(strip $(CHIP_ID)),$(filter $(strip $(CHIP_ID)), $(_CHIP_NO_HSP_LIST)))
SUPPORT_HSP                                      ?= 1
endif

################################################################
# Partition option
################################################################
SUPPORT_BOOTLOADER                               ?= 1
SUPPORT_PARTITION_MP_TABLE                       ?= 1
SUPPORT_PARTITION_CFG_TABLE                      ?= 1
SUPPORT_PARTITION_USER_RAW                       ?= 1
SETTING_PARTITION_MAIN_SIZE                      ?= 634880
SETTING_FLASH_TOTAL_SIZE                         ?= defined_by_chip
SETTING_PARTITION_BL_SIZE                        ?= 65536

ifeq ($(strip $(CHIP_NAME)),$(filter $(strip $(CHIP_NAME)), $(_CHIP_MEM_V1_LIST)))
SETTING_PSRAM_HEAP_BASE                          ?= 0x38800000
else
SETTING_PSRAM_HEAP_BASE                          ?= 0x80000000
endif
SETTING_PSRAM_HEAP_SIZE                          ?= 0
SETTING_PARTITION_USER_RAW_SIZE                  ?= 8192

################################################################
# System Servics option
################################################################
SETTING_OTA_METHOD                               ?= 0
SETTING_UART_UPGRADE_EN                          ?= 0
SETTING_UART_UPGRADE_BOOTLOADER                  ?= 0
SETTING_ROM_BOOT                                 ?= 0
SUPPORT_LOW_POWER                                ?= 0
#SETTING_RTC_CALI_INTERVAL                        ?= 10000
SETTING_RTC_CALI_INTERVAL                        ?= 0
BOOTLOADER_ENABLE_QE                             ?= 0
SUPPORT_WIFI_POSITIONING                         ?= 0

################################################################
# Build System Detail setting
################################################################
BUILD_SHOW_ILM_INFO                              ?= 1
BUILD_SHOW_DLM_INFO                              ?= 1

################################################################
# Application setting
################################################################
WAC_EN                                           ?= 0
HTTPD_EN                                         ?= 0
CJSON_EN                                         ?= 1
HTTPC_EN                                         ?= 0
MQTT_EN                                          ?= 0
MBEDTLS_EN                                       ?= 0
MBED_TURN                                        ?= 0
MBEDTLSTEST                                      ?= 0
IPERF3_EN                                        ?= 0
IPERF2_EN                                        ?= 0
SMARTCONFIG_EN                                   ?= 0
PING_EN                                          ?= 0
TFTP_EN                                          ?= 0

# 0 ==> no FOTA, 1 ==> file system FOTA, 2 ==> Ping Pong FOTA
FOTA_OPTION                                      ?= 0
JD_CLOUD_EN                                      ?= 0
AIRKISSAES_EN                                    ?= 0
AIRKISS_EN                                       ?= 0
JOYLINK_EN                                       ?= 0
RTLINK_EN                                        ?= 0
SETTING_MP3_DECODER                              ?= 0
SETTING_MP3_ENCODER                              ?= 0
ACOUSTIC_EN                                      ?= 0
CMSIS_EN                                         ?= 0
AUDIO_CODEC_EN                                   ?= 0

################################################################
# Misc setting
################################################################
VERBOSE                                          ?= 0

# 0 ==> Debug UART, 1==> Data UART
UART_IO_NUM                                      ?= 0
UART_BAUD_RATE                                   ?= 115200
SETTING_LOCK_CHIP_ID                             ?= 1
COSIM                                            ?= 0

# unit 4bytes, for idle task with floating swap, 160 word is safe.
MINIMAL_STACK_SIZE                               ?= 160
# unit 1bytes
MAIN_STACK_SIZE                                  ?= 512
ISR_STACK_SIZE                                   ?= 2048
CLI_HISTORY_ENABLE                               ?= 0
SUPPORT_CXX                                      ?= 0

SUPPORT_HOST_IF                                  ?= 0

###################################################################
# Filesystem feature
###################################################################
OSAL                                             := 1
# 0 ==> disable FFS, 1 ==> use spiffs, 2 ==> use littlefs
SUPPORT_FFS                                      ?= 2
# SD Card
SUPPORT_SDC                                      ?= 0

################################################################
# utility feature option
################################################################
SUPPORT_CLI                                      ?= 0
SUPPORT_ATCMD                                    ?= 0
SUPPORT_CUSTOM_CMD                               ?= 0
SUPPORT_TOOLBOX                                  ?= 1
SUPPORT_ISR_USAGE                                ?= 1
SUPPORT_ILOG                                     ?= 0
SUPPORT_HCILOG                                   ?= 0
SUPPORT_FULL_LITTLEVGL                           ?= 0
SUPPORT_SPI_LCM                                  ?= 0
SUPPORT_LOG_RINGBUFFER                           ?= 0
SUPPORT_LOG_RX_BUF_SIZE                          ?= 0
SUPPORT_LOG_TX_BUF_SIZE                          ?= 0


################################################################
# Peripheral setting
################################################################
SUPPORT_PERIPHERAL_WATCHDOG                      ?= 1
SUPPORT_PERIPHERAL_TIMER                         ?= 1
SUPPORT_PERIPHERAL_PWM                           ?= 1
SUPPORT_PERIPHERAL_GPIO                          ?= 1
SUPPORT_PERIPHERAL_PINMUX                        ?= 1
SUPPORT_PERIPHERAL_I2C_MASTER                    ?= 1
SUPPORT_PERIPHERAL_I2C_SLAVE					 ?= 1
SUPPORT_PERIPHERAL_SPI_MASTER                    ?= 1
SUPPORT_PERIPHERAL_SPI_SLAVE                     ?= 0
SUPPORT_PERIPHERAL_PDM                           ?= 1
SUPPORT_PERIPHERAL_I2S                           ?= 1
SUPPORT_PERIPHERAL_UART                          ?= 1
SUPPORT_PERIPHERAL_HSUART                        ?= 1
SUPPORT_PERIPHERAL_LMDMA                         ?= 1
SUPPORT_PERIPHERAL_DMAC                          ?= 1
SUPPORT_PERIPHERAL_ADC                           ?= 1
SUPPORT_PERIPHERAL_ADCBTN                        ?= 1
SUPPORT_PERIPHERAL_EFUSE                         ?= 1

###################################################################
# Crypto engine feature
# ###################################################################
SUPPORT_CRYPTO_ENGINE                            ?= 0      
SECURE_BOOT                                      ?= 0
ANTI_CLONE_PROTECTION                            ?= 0

################################################################
# not common code setting
################################################################
CUSTOM_HWMAC                                     ?= 0
CUSTOM_SECURITY                                  ?= 0
CUSTOM_N10_BOOT                                  ?= 0
CUSTOM_SOFTMAC                                   ?= 0
CUSTOM_APPLICATION                               ?= 0
CUSTOM_LIBC_STUB                                 ?= 0
CUSTOM_WIFI                                      ?= 0
CUSTOM_PHY                                       ?= 0
SETTING_MULTI_BINARY                             ?= 0
