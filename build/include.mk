INC += -I$(SDKDIR)/components/bsp/soc/$(CHIP_NAME)/layout

ifneq ($(strip $(SUPPORT_FFS)),0)
INC += -I$(SDKDIR)/components/fsal/spiffs
INC += -I$(SDKDIR)/components/fsal/littlefs
INC += -I$(SDKDIR)/components/fsal
endif

INC += -I$(SDKDIR)/components/bsp/soc/sys
INC += -I$(SDKDIR)/components/bsp/mcu/$(MCU_DEF)
INC += -I$(SDKDIR)/components/bsp/soc/$(CHIP_NAME)/$(TARGET_DEF)
INC += -I$(SDKDIR)/components/bsp/soc/$(CHIP_NAME)
INC += -I$(SDKDIR)/components/osal
INC += -I$(SDKDIR)/components/drv

ifeq ($(strip $(OS)), freertos)
INC += -I$(SDKDIR)/components/osal/freertos/nds32
INC += -I$(SDKDIR)/components/osal/freertos/kernel/Source/include
INC += -I$(SDKDIR)/components/osal/freertos
endif
ifeq ($(strip $(OS)), rhino)
INC += -I$(SDKDIR)/components/osal/rhino/core/include
INC += -I$(SDKDIR)/components/osal/rhino/port
endif
INC += -I$(SDKDIR)/components/inc/rom
INC += -I$(SDKDIR)/components/inc
INC += -I$(SDKDIR)/components
INC += -I$(PROJ_DIR)/src/inc
#INC += -I$(PROJ_DIR)/src/inc/custom

##############################################################
# Build Application flags
##############################################################
INC += -I$(SDKDIR)/components/net/tcpip/$(LWIP_PATH)/ports/icomm/include
INC += -I$(SDKDIR)/components/net/tcpip/$(LWIP_PATH)/src/include
INC += -I$(SDKDIR)/components/net/tcpip/$(LWIP_PATH)/src/include/ipv4
INC += -I$(SDKDIR)/components/net/tcpip/$(LWIP_PATH)/src/include/ipv6
ifeq ($(strip $(WAC_EN)), 1)
INC += -I$(SDKDIR)/components/third_party/mDNSResponder/inc
endif
ifeq ($(strip $(CJSON_EN)), 1)
INC += -I$(SDKDIR)/components/third_party/cJSON
endif
ifeq ($(strip $(MBEDTLS_EN)), 1)
INC += -I$(SDKDIR)/components/third_party/mbedtls
INC += -I$(SDKDIR)/components/third_party/mbedtls/include
endif
INC += -I$(SDKDIR)/components/third_party/crc16
INC += -I$(SDKDIR)/components/inc/crypto
INC += -I$(SDKDIR)/components/crypto_hw
INC += -I$(SDKDIR)/components/softmac
INC += -I$(SDKDIR)/components/softmac/umac
INC += -I$(SDKDIR)/components/softmac/lmac
INC += -I$(SDKDIR)/components/iotapi
INC += -I$(SDKDIR)/components/netstack_wrapper
ifeq ($(strip $(SUPPORT_TOOLBOX)),1)
INC += -I$(SDKDIR)/components/tools/toolbox
endif
INC += -I$(SDKDIR)/components/tools/cli
INC += -I$(SDKDIR)/components/tools/atcmd
INC += -I$(SDKDIR)/components/tools/ssv_now
INC += -I$(PROJ_DIR)/src/board/cfg
INC += -I$(PROJ_DIR)/src/board/param

ifeq ($(strip $(MCU_DEF)), ANDES_N10)
INC         += -I$(SDKDIR)/components/bsp/soc/boot/mcu/n10
endif
ifeq ($(strip $(MCU_DEF)), ANDES_D10)
INC         += -I$(SDKDIR)/components/bsp/soc/boot/mcu/d10
endif
ifeq ($(strip $(MCU_DEF)), ANDES_D10F)
INC         += -I$(SDKDIR)/components/bsp/soc/boot/mcu/d10f
endif

ifeq ($(strip $(BUILD_SDK)),1)
INC += -I$(PROJ_DIR)/src/board/inc
endif
#INC         += $(INCLUDE)
ifeq ($(strip $(SUPPORT_PERIPHERAL_WATCHDOG)), 1)
INC                +=  -Icomponents/drv/wdt
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/wdt
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_TIMER)), 1)
INC                +=  -Icomponents/drv/tmr
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/tmr
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_PWM)), 1)
INC                +=  -Icomponents/drv/pwm
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/pwm
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_GPIO)), 1)
INC                +=  -Icomponents/drv/gpio
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/gpio
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_PINMUX)), 1)
INC                +=  -Icomponents/drv/pinmux
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/pinmux
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_I2C_MASTER)), 1)
INC                +=  -Icomponents/drv/i2cmst
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/i2cmst
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_I2C_SLAVE)), 1)
INC                +=  -Icomponents/drv/i2cslv
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/i2cslv
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_SPI_MASTER)), 1)
INC                +=  -Icomponents/drv/spimst
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/spimst
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_SPI_SLAVE)), 1)
INC                +=  -Icomponents/drv/spislv
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/spislv
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_PDM)), 1)
INC                +=  -Icomponents/drv/pdm
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/pdm
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_I2S)), 1)
INC                +=  -Icomponents/drv/i2s
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/i2s
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_UART)), 1)
INC                +=  -Icomponents/drv/uart
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/uart
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_HSUART)), 1)
INC                +=  -Icomponents/drv/hsuart
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/hsuart
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_LMDMA)), 1)
INC                +=  -Icomponents/drv/lmdma
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/lmdma
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_DMAC)), 1)
INC                +=  -Icomponents/drv/dmac
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/dmac
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_ADC)), 1)
INC                +=  -Icomponents/drv/adc
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/adc
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_ADCBTN)), 1)
INC                +=  -Icomponents/drv/adcbtn
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_ADCBAT)), 1)
INC                +=  -Icomponents/drv/adcbat
endif
ifeq ($(strip $(SUPPORT_PERIPHERAL_EFUSE)), 1)
INC                +=  -Icomponents/drv/efuse
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/efuse
endif
INC                +=  -I$(PROJ_DIR)/src/board/inc/custom/$(CHIP_NAME)/$(IC_PACKAGE)

ifeq ($(strip $(SUPPORT_PERIPHERAL_TOUCH)), 1)
INC                +=  -Icomponents/drv/touch
INC                +=  -Icomponents/bsp/soc/$(CHIP_NAME)/hal/touch
endif