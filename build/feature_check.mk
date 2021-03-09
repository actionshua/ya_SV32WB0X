ifeq ($(strip $(BLE_EN)), 1)

ifeq ($(BOARD),SV6020B_P40_26M)
ifeq ($(strip $(UART_IO_NUM)), 0)
$(error please set UART_IO_NUM = 1.)
endif
endif

ifeq ($(BOARD),SV6020B_P52_26M)
ifeq ($(strip $(UART_IO_NUM)), 1)
$(error please set UART_IO_NUM = 0.)
endif
endif

endif

ifeq ($(strip $(TCPIPSTACK_EN)), 0)
ifeq ($(strip $(WAC_EN)), 1)
$(error please trun off WAC_EN when TCPIPSTACK_EN = 0.)
endif
ifeq ($(strip $(HTTPD_EN)), 1)
$(error please trun off HTTPD_EN when TCPIPSTACK_EN = 0.)
endif
ifeq ($(strip $(HTTPC_EN)), 1)
$(error please trun off HTTPC_EN when TCPIPSTACK_EN = 0.)
endif
ifeq ($(strip $(MQTT_EN)), 1)
$(error please trun off MQTT_EN when TCPIPSTACK_EN = 0.)
endif
ifeq ($(strip $(MBEDTLS_EN)), 1)
$(error please trun off MBEDTLS_EN when TCPIPSTACK_EN = 0.)
endif
ifeq ($(strip $(SMARTCONFIG_EN)), 1)
$(error please trun off SMARTCONFIG_EN when TCPIPSTACK_EN = 0.)
endif
ifeq ($(strip $(PING_EN)), 1)
$(error please trun off PING_EN when TCPIPSTACK_EN = 0.)
endif
ifeq ($(strip $(TFTP_EN)), 1)
$(error please trun off TFTP_EN when TCPIPSTACK_EN = 0.)
endif
ifeq ($(strip $(FOTA_OPTION)), 1)
$(error please trun off FOTA_OPTION when TCPIPSTACK_EN = 0.)
endif
ifeq ($(strip $(JD_CLOUD_EN)), 1)
$(error please trun off JD_CLOUD_EN when TCPIPSTACK_EN = 0.)
endif
endif

ifeq ($(strip $(IPERF3_EN)), 1)
ifeq ($(strip $(IPERF2_EN)), 1)
$(error please trun off IPERF2_EN when IPERF3_EN = 1.)
endif
endif

ifeq ($(strip $(WPS_EN)), 1)
ifeq ($(strip $(EPA_EN)), 0)
$(error please trun on EPA_EN when WPS_EN = 1.)
endif
endif

ifneq ($(strip $(CUSTOM_WIFI)),1)
ifeq ($(strip $(RC_NATIVE_EN)), 1)
ifeq ($(strip $(RC_MINSTREL_EN)), 1)
$(error please trun off RC_MINSTREL_EN when RC_NATIVE_EN = 1.)
endif
endif

ifeq ($(strip $(RC_NATIVE_EN)), 0)
ifeq ($(strip $(RC_MINSTREL_EN)), 0)
$(error please trun on RC_MINSTREL_EN when RC_NATIVE_EN = 0.)
endif
endif
endif

ifeq ($(CHIP_ID),6006)
ifeq ($(strip $(SUPPORT_CRYPTO_ENGINE)), 1)
$(error this chip not support SUPPORT_CRYPTO_ENGINE.)
endif  
endif

ifneq ($(SECURE_ROM),1)
ifeq ($(strip $(SECURE_BOOT)), 1)
$(error this chip not support SECURE_BOOT.)
endif
ifeq ($(strip $(ANTI_CLONE_PROTECTION)), 1)
$(error this chip not support ANTI_CLONE_PROTECTION.)
endif
endif

#ifeq ($(strip $(RC_MINSTREL_EN)), 1)
#ifeq ($(strip $(MBEDTLS_EN)), 1)
#$(error please trun off MBEDTLS_EN when RC_MINSTREL_EN = 1.)
#endif
#endif

ifeq ($(strip $(AIRKISSAES_EN)), 1)
ifeq ($(strip $(AIRKISS_EN)), 0)
$(error please trun on AIRKISS_EN before enable AIRKISSAES_EN feature.)
endif
endif

#ifeq ($(strip $(SUPPORT_LOW_POWER)),1)
#ifeq ($(strip $(SETTING_RTC_CALI_INTERVAL)),0)
#$(error please setup SETTING_RTC_CALI_INTERVAL to support SUPPORT_LOW_POWER feature.)
#endif
#endif

ifeq ($(strip $(SUPPORT_CLI)), 1)
ifeq ($(strip $(SUPPORT_ATCMD)), 1)
$(error SDK not Support CLI and ATCMD at the same time.)
endif
endif

SETTING_PARTITION_MAIN_SIZE                      := $(call unit_conv,$(SETTING_PARTITION_MAIN_SIZE))
SETTING_FLASH_TOTAL_SIZE                         := $(call unit_conv,$(SETTING_FLASH_TOTAL_SIZE))
SETTING_PSRAM_HEAP_SIZE                          := $(call unit_conv,$(SETTING_PSRAM_HEAP_SIZE))
SETTING_PARTITION_USER_RAW_SIZE                  := $(call unit_conv,$(SETTING_PARTITION_USER_RAW_SIZE))

CFLAGS      += -DSETTING_MP3_DECODER=$(SETTING_MP3_DECODER)
CFLAGS      += -DSETTING_MP3_ENCODER=$(SETTING_MP3_ENCODER)

ifeq ($(true),$(call and,$(call set_equal,$(CHIP_ID),6020),$(call set_equal,$(CHIP_SUB_ID),2)))
ifeq ($(strip $(TARGET_DEF)),FPGA)
ifeq ($(strip $(SYS_BUS_CLK)),160M)
$(error fpga only support bus 40MHz or 80MHz)
endif
endif
else
ifeq ($(strip $(TARGET_DEF)),FPGA)
ifeq ($(strip $(SYS_BUS_CLK)),80M)
$(error fpga only support bus 40MHz)
endif
ifeq ($(strip $(SYS_BUS_CLK)),160M)
$(error fpga only support bus 40MHz)
endif
endif
endif

ifeq ($(strip $(AMPDU_TX_EN)), 1)
ifneq ($(strip $(RC_MINSTREL_EN)), 1)
$(error please trun on RC_MINSTREL_EN when AMPDU_TX_EN = 1.)
endif
endif

_6020_ROM_LIST:=V1002
_6006_ROM_LIST:=v0002 v0006 V0014 V0015 V0016
__ROM_LIST:=
ifeq ($(strip $(ROM_MODE)),1)
 ifeq ($(strip $(CHIP_ID)),6020)
  ifeq ($(strip $(CHIP_SUB_ID)),2)
   __ROM_LIST:=$(_6020_ROM_LIST)
  endif
 else
  ifeq ($(strip $(CHIP_ID)),6006)
   __ROM_LIST:=$(_6006_ROM_LIST)
  endif
 endif
 ifneq ($(strip $(ROM_VERSION)),$(filter $(strip $(ROM_VERSION)),$(__ROM_LIST)))
  $(error $(CHIP_ID) no ROM_VERSION: $(ROM_VERSION) Please fix it.)
 endif
endif

ifeq ($(strip $(SUPPORT_FFS)),0)
ifeq ($(strip $(FOTA_OPTION)),1)
$(error SDK option issue FOTA_OPTION=1 means filesystem fota, must SUPPORT_FFS=1.)
endif
endif

ifeq ($(CHIP_ID),6006)
ifneq ($(SYS_MCU_MAX_CLK),160M)
$(error SV6166/SV6266 only support MCU 160MHz.)
endif
ifeq ($(SYS_BUS_CLK),160M)
$(error SV6166/SV6266 only support BUS 40M,80MHz.)
endif
ifneq ($(strip $(SYS_BUS_CLK)),$(strip $(SYS_FLASH_CLK)))
$(error SV6166/SV6266 only support Flash clock same as bus clock.)
endif
endif

ifeq ($(CHIP_SUB_ID),0)
__BUS_160M_MCU_FILTER:= 320M 160M
__BUS_80M_MCU_FILTER:= 320M 240M 160M 80M
__BUS_40M_MCU_FILTER:= 320M 240M 160M 80M 40M
else
__BUS_160M_MCU_FILTER:= 480M 320M 160M
__BUS_80M_MCU_FILTER:= 480M 320M 240M 160M 80M
__BUS_40M_MCU_FILTER:= 480M 320M 240M 160M 80M 40M
endif

ifeq ($(CHIP_NAME),ssv6020)
ifneq ($(strip $(SYS_FLASH_CLK)),40M)
$(error SV6020A only Flash clock = 40M.)
endif
endif
ifeq ($(CHIP_ID),6020)
ifeq ($(SYS_BUS_CLK),160M)
ifneq ($(strip $(SYS_MCU_MAX_CLK)),$(filter $(strip $(SYS_MCU_MAX_CLK)),$(__BUS_160M_MCU_FILTER)))
$(error SV6020A only support MCU $(__BUS_160M_MCU_FILTER) when BUS = $(SYS_BUS_CLK).)
endif
endif
ifeq ($(SYS_BUS_CLK),80M)
ifneq ($(strip $(SYS_MCU_MAX_CLK)),$(filter $(strip $(SYS_MCU_MAX_CLK)),$(__BUS_80M_MCU_FILTER)))
$(error SV6020A only support MCU $(__BUS_80M_MCU_FILTER) when BUS = $(SYS_BUS_CLK).)
endif
endif
ifeq ($(SYS_BUS_CLK),40M)
ifneq ($(strip $(SYS_MCU_MAX_CLK)),$(filter $(strip $(SYS_MCU_MAX_CLK)),$(__BUS_40M_MCU_FILTER)))
$(error SV6020A only support MCU $(__BUS_40M_MCU_FILTER) when BUS = $(SYS_BUS_CLK).)
endif
endif
endif

ifeq ($(strip $(SUPPORT_SDC)), 1)
ifneq ($(strip $(SUPPORT_PERIPHERAL_SPI_MASTER)),1)
$(error please define SUPPORT_PERIPHERAL_SPI_MASTER when SUPPORT_SDC = 1.)
endif
ifneq ($(strip $(SUPPORT_PERIPHERAL_PINMUX)),1)
$(error please define SUPPORT_PERIPHERAL_PINMUX when SUPPORT_SDC = 1.)
endif
endif

ifeq ($(strip $(SUPPORT_LOG_RINGBUFFER)),1)
ifeq ($(strip $(UART_IO_NUM)),0)
$(error please check UART_IO_NUM & SUPPORT_LOG_RINGBUFFER only hsuart support ringbuffer mode)
endif
endif
