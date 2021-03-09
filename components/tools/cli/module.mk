
LIB_SRC := cli.c
LIB_SRC += cli_cmd.c
LIB_SRC += atcmd.c
LIB_SRC += sysconf_api.c

ifeq ($(strip $(SETTING_BLE_UART)),1)
LIB_SRC += atcmd_ble_uart.c
endif

ifeq ($(strip $(WAC_EN)), 1)
LIB_SRC += atcmd_homekit.c
endif

ifeq ($(strip $(TCPIPSTACK_EN)), 1)
LIB_SRC += atcmd_socket.c
endif

ifeq ($(strip $(MBEDTLS_EN)), 1)
LIB_SRC += atcmd_ssl.c
endif

ifeq ($(strip $(SUPPORT_PARTITION_CFG_TABLE)), 1)
LIB_SRC += atcmd_cfg.c
endif

#ifeq ($(strip $(XXXX_EN)), 1)
LIB_SRC += atcmd_general.c
#endif

ifeq ($(strip $(SUPPORT_PERIPHERAL_GPIO)), 1)
LIB_SRC += atcmd_gpio.c
endif

#ifeq ($(strip $(XXXX_EN)), 1)
LIB_SRC += atcmd_wifi.c
#endif

ifeq ($(strip $(MESH_BLE_EN)), 1)
LIB_SRC += atcmd_ble_mesh.c
endif

ifeq ($(strip $(BLE_GAP_ATCMD_EN)), 1)
LIB_SRC += atcmd_ble.c
endif

LIB_ASRC :=
LIBRARY_NAME := cli
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC += -Icomponents/inc
LOCAL_INC += -Icomponents/drv
LOCAL_INC += -Icomponents/softmac
LOCAL_INC += -Icomponents/drv/uart
LOCAL_INC += -Icomponents/drv/timer
LOCAL_INC += -Icomponents/drv/flash
LOCAL_INC += -Icomponents/drv/flashctl
LOCAL_INC += -Icomponents/drv/wdt
LOCAL_INC += -Icomponents/drv/dma
LOCAL_INC += -Icomponents/drv/gpio
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/gpio
LOCAL_INC += -Icomponents/tools/atcmd
LOCAL_INC += -Icomponents/tools/toolbox
LOCAL_INC += -Icomponents/third_party/cJSON
LOCAL_INC += -Icomponents/ble/inc/common
ifeq ($(strip $(FOTA_OPTION)), 0)
else
LOCAL_INC += -Icomponents/tools/fota_api
endif
LOCAL_INC += -Icomponents/netstack_wrapper
LOCAL_INC += -Icomponents/net/tcpip/lwip-1.4.0/src/include
LOCAL_INC += -Icomponents/net/tcpip/lwip-1.4.0/ports/icomm/include
LOCAL_INC += -Icomponents/net/tcpip/lwip-1.4.0/src/include/ipv4
ifeq ($(strip $(SMARTCONFIG_EN)), 1)
LOCAL_INC += -Icomponents/third_party
LOCAL_INC += -Icomponents/tools/rtlinklib
LOCAL_INC += -Icomponents/tools
endif
ifeq ($(strip $(WAC_EN)), 1)
LOCAL_INC += -Icomponents/third_party/httpd/inc
endif
ifeq ($(strip $(SUPPORT_PARTITION_CFG_TABLE)), 1)
LOCAL_INC += -I$(PROJ_DIR)/src/cfg
endif

ifeq ($(strip $(MESH_BLE_EN)), 1)
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/host/nimble/host/mesh/src
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/host/nimble/host/store/config/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/mesh_common/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/mesh_core
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/mesh_core/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/mesh_models/client/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/mesh_models/server/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/mesh_models/common/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/common/osi/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/common/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/log/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/host/nimble/include/nimble
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_common/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/btc/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/common/btc/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/api/models/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/api/core/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/api
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/mesh_core/storage
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/commmon/btc/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/syslog/log/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/freertos/include/freertos
LOCAL_INC += -Icomponents/third_party/mbedtls/include
LOCAL_INC += -Icomponents/osal/freertos/nds32
endif

ifeq ($(strip $(BLE_GAP_ATCMD_EN)), 1)
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/common/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/host/bluedroid/api/include
endif

# BLE
BLE_DIR := $(TOPDIR)/components/third_party/apache-mynewt-nimble-1.2.0
LOCAL_INC += -I$(BLE_DIR)/host/nimble/include
LOCAL_INC += -I$(BLE_DIR)/porting/nimble/include
LOCAL_INC += -I$(BLE_DIR)/porting/npl/freertos/include
LOCAL_INC += -I$(BLE_DIR)/host/nimble/host/include
LOCAL_INC += -I$(BLE_DIR)/host/nimble/host/services/gap/include
LOCAL_INC += -I$(BLE_DIR)/host/nimble/host/services/gatt/include
LOCAL_INC += -I$(BLE_DIR)/host/nimble/host/services/bleuart/include

LOCAL_INC += -Icomponents/bsp/soc/lowpower

RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
