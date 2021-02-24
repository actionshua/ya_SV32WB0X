################################################################
# Detail library setting
################################################################
ifeq ($(strip $(ROM_MODE)), 1)
#IMPORT_DIR         +=  components/rom_connector
else
endif
#IMPORT_DIR              += components/crypto
ifeq ($(strip $(TCPIPSTACK_EN)), 1)
IMPORT_DIR              += components/net/tcpip/$(LWIP_PATH)
endif
#IMPORT_DIR         +=  $(PROJ_DIR)/src/cli

ifneq ($(strip $(CUSTOM_LIBC_STUB)),1)
IMPORT_DIR         += components/bsp/soc/libc_stub
endif


###################################################################
# Import OS
###################################################################
_SUPPORT_MCU_DEF = ANDES_N10 ANDES_D10 ANDES_D10F

ifneq ($(strip $(MCU_DEF)),$(filter $(strip $(MCU_DEF)), $(_SUPPORT_MCU_DEF)))
$(error not supported MCU_DEF = $(MCU_DEF))
endif
ifeq ($(strip $(MCU_DEF)), ANDES_N10)
ifneq ($(strip $(CUSTOM_N10_BOOT)),1)
IMPORT_DIR         += components/bsp/soc/boot/mcu/n10
endif
endif
ifeq ($(strip $(MCU_DEF)), ANDES_D10)
ifneq ($(strip $(CUSTOM_N10_BOOT)),1)
IMPORT_DIR         += components/bsp/soc/boot/mcu/d10
endif
endif
ifeq ($(strip $(MCU_DEF)), ANDES_D10F)
ifneq ($(strip $(CUSTOM_N10_BOOT)),1)
IMPORT_DIR         += components/bsp/soc/boot/mcu/d10f

ifeq ($(strip $(SETTING_CACHE_WT)), 0)
IMPORT_DIR         += components/bsp/soc/boot/mcu/d10f/cache_wb
else
ifeq ($(strip $(SETTING_CACHE_WT)), 1)
IMPORT_DIR         += components/bsp/soc/boot/mcu/d10f/cache_wt
else
IMPORT_DIR         += components/bsp/soc/boot/mcu/d10f/cache_wb
IMPORT_DIR         += components/bsp/soc/boot/mcu/d10f/cache_wt
endif

endif
endif
endif

ifneq ($(strip $(CUSTOM_APPLICATION)),1)
IMPORT_DIR        += components/bsp/soc/soc_init
IMPORT_DIR        += components/bsp/soc/mem_init
IMPORT_DIR        += components/bsp/soc/efuseapi
ifeq ($(strip $(SUPPORT_LOW_POWER)),1)
IMPORT_DIR        += components/bsp/soc/lowpower
endif
endif

###################################################################
# Import OSAL
###################################################################
ifeq ($(strip $(OS)), freertos)
IMPORT_DIR      += components/osal/freertos
IMPORT_DIR      += components/osal/freertos/kernel
endif
ifeq ($(strip $(OS)), rhino)
IMPORT_DIR      += components/osal/rhino
endif

ifeq ($(strip $(OSAL)),1)
IMPORT_DIR         +=  components/osal
endif

###################################################################
# Import FSAL
###################################################################
ifneq ($(strip $(SUPPORT_FFS)),0)
IMPORT_DIR         +=  components/third_party/spiffs
IMPORT_DIR         +=  components/third_party/littlefs
IMPORT_DIR         +=  components/third_party/FatFs
IMPORT_DIR         +=  components/fsal
IMPORT_DIR         +=  components/fsal/sdc/fatfs
endif

###################################################################
# Import Driver
###################################################################
IMPORT_DIR         +=  components/sys

ifeq ($(strip $(BLE_EN)),1)
IMPORT_DIR         +=  components/ble/ble_api
IMPORT_DIR         +=  components/ble/bsp
IMPORT_DIR         +=  components/ble/lib
IMPORT_DIR         +=  components/ble/lestack
IMPORT_DIR         +=  components/ble/application
IMPORT_DIR         +=  components/ble/inc
endif

ifneq ($(strip $(XIP_MODE)),0)
#not SMAC
IMPORT_DIR         +=  components/third_party/apache-mynewt-nimble-1.2.0
endif


ifneq ($(strip $(CUSTOM_WIFI)),1)
IMPORT_DIR         +=  components/drv/common
endif
ifeq ($(strip $(IDM)),1)
IMPORT_DIR         +=  components/drv/idmanage
endif
ifeq ($(strip $(MBOX)),1)
IMPORT_DIR         +=  components/drv/mbox
endif
ifneq ($(strip $(CUSTOM_HWMAC)),1)
IMPORT_DIR         +=  components/drv/hwmac
endif

# aMH temp! for SV6020B [S]
#ifneq ($(strip $(CHIP_NAME)),ssv6020B)
# aMH temp! for SV6020B [E]
ifneq ($(strip $(CUSTOM_PHY)),1)
IMPORT_DIR         +=  components/drv/phy
endif
ifneq ($(strip $(CUSTOM_SECURITY)),1)
IMPORT_DIR         +=  components/drv/security
endif
IMPORT_DIR         +=  components/softmac/lmac/nav

ifneq ($(strip $(CUSTOM_SOFTMAC)),1)
IMPORT_DIR         +=  components/softmac
IMPORT_DIR         +=  components/softmac/lmac
ifeq ($(strip $(WIFI_REPEATER_EN)),1)
IMPORT_DIR         +=  components/softmac/umac/repeater
endif
endif
ifneq ($(strip $(CUSTOM_APPLICATION)),1)
IMPORT_DIR         +=  components/iotapi
endif
# aMH temp! for SV6020B [S]
#endif
# aMH temp! for SV6020B [E]

ifeq ($(strip $(TCPIPSTACK_EN)), 1)
IMPORT_DIR         +=  components/net/udhcp
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_WATCHDOG)), 1)
IMPORT_DIR         +=  components/drv/wdt
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/wdt
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_TIMER)), 1)
IMPORT_DIR         +=  components/drv/tmr
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/tmr
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_PWM)), 1)
IMPORT_DIR         +=  components/drv/pwm
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/pwm
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_GPIO)), 1)
IMPORT_DIR         +=  components/drv/gpio
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/gpio
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_PINMUX)), 1)
IMPORT_DIR         +=  components/drv/pinmux
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/pinmux
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_I2C_MASTER)), 1)
IMPORT_DIR         +=  components/drv/i2cmst
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/i2cmst
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_I2C_SLAVE)), 1)
IMPORT_DIR         +=  components/drv/i2cslv
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/i2cslv
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_SPI_MASTER)), 1)
IMPORT_DIR         +=  components/drv/spimst
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/spimst
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_SPI_SLAVE)), 1)
IMPORT_DIR         +=  components/drv/spislv
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/spislv
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_PDM)), 1)
IMPORT_DIR         +=  components/drv/pdm
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/pdm
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_I2S)), 1)
IMPORT_DIR         +=  components/drv/i2s
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/i2s
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_UART)), 1)
IMPORT_DIR         +=  components/drv/uart
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/uart
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_HSUART)), 1)
IMPORT_DIR         +=  components/drv/hsuart
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/hsuart
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_LMDMA)), 1)
IMPORT_DIR         +=  components/drv/lmdma
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/lmdma
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_DMAC)), 1)
IMPORT_DIR         +=  components/drv/dmac
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/dmac
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_ADC)), 1)
IMPORT_DIR         +=  components/drv/adc
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/adc
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_ADCBTN)), 1)
IMPORT_DIR         +=  components/drv/adcbtn
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/adc
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_ADCBAT)), 1)
IMPORT_DIR         +=  components/drv/adcbat
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/adc
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_TOUCH)), 1)
IMPORT_DIR         +=  components/drv/touch
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/touch
endif
ifneq ($(strip $(CUSTOM_APPLICATION)),1)
IMPORT_DIR         +=  components/drv/efuse
IMPORT_DIR         +=  components/bsp/soc/$(CHIP_NAME)/hal/efuse
endif
ifneq ($(strip $(CUSTOM_APPLICATION)),1)
IMPORT_DIR         +=  components/third_party/crc16
endif

ifneq ($(strip $(CUSTOM_WIFI)),1)
ifeq ($(strip $(SUPPORT_LOW_POWER)),1)	
IMPORT_DIR         +=  components/drv/powersave
endif
IMPORT_DIR         +=  components/softmac/lmac/txrx
endif

ifneq ($(strip $(CUSTOM_APPLICATION)),1)
IMPORT_DIR         +=  components/crypto
endif

ifeq ($(strip $(TINY_LIBC)), 1)
IMPORT_DIR         +=  components/third_party/rtos-comm/libc
else
#IMPORT_DIR         +=  components/drv/terminal
endif

ifneq ($(strip $(CUSTOM_WIFI)),1)
IMPORT_DIR         +=  components/netstack_wrapper
endif

ifeq ($(strip $(AMPDU_TX_EN)), 1)
IMPORT_DIR         +=  components/drv/ampdu
endif

###################################################################
# Import Application
###################################################################

#ifeq ($(strip $(SUPPORT_WPA_SUPPLICANT)),1)
#IMPORT_DIR         +=  components/wpa_supplicant
#endif

ifneq ($(strip $(FOTA_OPTION)),0)
IMPORT_DIR         += components/tools/fotalib
IMPORT_DIR         += components/tools/fota_api
endif

ifeq ($(strip $(WAC_EN)), 1)
IMPORT_DIR         +=  components/third_party/mDNSResponder
IMPORT_DIR 		+=  components/third_party/HomeKit-ADK
endif

ifeq ($(strip $(HTTPD_EN)), 1)
IMPORT_DIR         +=  components/third_party/httpd
endif
ifeq ($(strip $(CJSON_EN)), 1)
IMPORT_DIR         +=  components/third_party/cJSON
endif
IMPORT_DIR         +=  components/tools/utility/SSV_cJSON

ifeq ($(strip $(HTTPC_EN)), 1)
IMPORT_DIR         +=  components/third_party/httpclient
endif
ifeq ($(strip $(MQTT_EN)), 1)
IMPORT_DIR         +=  components/third_party/mqtt
endif
ifeq ($(strip $(MBEDTLS_EN)), 1)
IMPORT_DIR         +=  components/third_party/mbedtls
ifneq ($(strip $(MBEDTLSTEST)), 0)
IMPORT_DIR         +=  components/third_party/mbedtls/tests
endif
endif

ifeq ($(strip $(SUPPORT_CRYPTO_ENGINE)), 1)
IMPORT_DIR              += components/crypto_hw
endif

ifeq ($(strip $(TCPIPSTACK_EN)), 1)
ifeq ($(strip $(IPERF3_EN)), 1)
IMPORT_DIR         +=  components/third_party/iperf3.0
endif
ifeq ($(strip $(IPERF2_EN)), 1)
IMPORT_DIR         +=  components/third_party/iperf-2.0.5
endif
endif

ifeq ($(strip $(SMARTCONFIG_EN)), 1)
IMPORT_DIR        +=    components/wifi_pkg_cap
ifeq ($(strip $(JOYLINK_EN)),1)
IMPORT_DIR        +=    components/third_party/joylink
endif
ifeq ($(strip $(AIRKISS_EN)),1)
IMPORT_DIR        +=    components/third_party/airkiss
endif
ifeq ($(strip $(RTLINK_EN)),1)
IMPORT_DIR        +=	components/tools/rtlinklib
IMPORT_DIR        +=	components/tools/rtlink
endif
endif

ifeq ($(strip $(PING_EN)), 1)
IMPORT_DIR        +=    components/third_party/ping
endif

ifeq ($(strip $(TFTP_EN)), 1)
IMPORT_DIR        +=    components/third_party/tftp
endif

ifeq ($(strip $(JD_CLOUD_EN)), 1)
IMPORT_DIR        +=    components/third_party/joylink_dev_sdk_2.0.4
endif

ifneq ($(strip $(CUSTOM_APPLICATION)),1)
IMPORT_DIR        +=    components/bsp/soc/sys
IMPORT_DIR        +=    components/tools/utility
IMPORT_DIR        +=    components/tools/atcmd
IMPORT_DIR        +=	components/tools/ssv_now
endif
ifeq ($(strip $(SUPPORT_TOOLBOX)), 1)
IMPORT_DIR        +=    components/tools/toolbox
endif
ifneq ($(strip $(CUSTOM_APPLICATION)),1)
IMPORT_DIR        +=    components/tools/cli
endif

ifeq ($(strip $(RC_MINSTREL_EN)), 1)
IMPORT_DIR        +=  components/softmac/lmac/rc/minstrel/core
IMPORT_DIR        +=  components/softmac/lmac/rc/minstrel
endif
ifeq ($(strip $(RC_NATIVE_EN)), 1)
IMPORT_DIR        +=  components/softmac/lmac/rc/native_rc
endif

ifneq ($(strip $(CUSTOM_APPLICATION)),1)
IMPORT_DIR        +=  components/third_party/sntp
endif

ifeq ($(origin PROJECT), undefined)
CFG_DIR           :=
else
CFG_DIR           :=    $(PROJ_DIR)/src/board/cfg
endif

ifeq ($(strip $(SETTING_MP3_DECODER)), 1)
IMPORT_DIR 		+= components/third_party/pvmp3decoder
else
ifeq ($(strip $(SETTING_MP3_DECODER)), 2)
IMPORT_DIR 		+= components/third_party/helix_mp3d
endif
endif

ifeq ($(strip $(SETTING_MP3_ENCODER)), 1)
IMPORT_DIR 		+= components/third_party/shine
endif

ifeq ($(strip $(ACOUSTIC_EN)), 1)
IMPORT_DIR      += components/audio/acoustic_algorithm
IMPORT_DIR      += components/audio/ringbuf
endif

ifeq ($(strip $(CMSIS_EN)), 1)
IMPORT_DIR      += components/audio/CMSIS
endif

ifneq ($(strip $(AUDIO_CODEC_EN)), 0)
IMPORT_DIR      += components/audio/codec
IMPORT_DIR      += components/audio/codec_common
endif

CHIP_BUS_SRAM=ssv6020B ssv6020C

ifeq ($(strip $(XIP_MODE)),0)
IMPORT_DIR      += components/osal/no_meminfo
else
ifeq ($(CHIP_NAME),$(filter $(CHIP_NAME),$(CHIP_BUS_SRAM)))
IMPORT_DIR      += components/osal/memmgr
else
ifeq ($(strip $(SUPPORT_SRM_MEM_INFO)), 0)
IMPORT_DIR      += components/osal/no_meminfo
else
ifeq ($(strip $(SUPPORT_SRM_MEM_INFO)), 1)
IMPORT_DIR      += components/osal/meminfo
else
IMPORT_DIR      += components/osal/no_meminfo
IMPORT_DIR      += components/osal/meminfo
endif
endif
endif
endif

ifeq ($(strip $(SUPPORT_FULL_LITTLEVGL)),1)
IMPORT_DIR      += components/third_party/littlevgl-7.1.0
IMPORT_DIR      += components/third_party/littlevgl-6.1.2
else
ifneq ($(origin SUPPORT_LITTLEVGL), undefined)
IMPORT_DIR      += components/third_party/littlevgl-$(SUPPORT_LITTLEVGL)
endif
endif

IMPORT_DIR      += components/acp

ifeq ($(strip $(SUPPORT_SPI_LCM)),1)
IMPORT_DIR      += components/drivers/spi_lcm
endif

