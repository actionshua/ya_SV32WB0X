
LIB_SRC := main.c
LIB_SRC += custom_cmd.c

LIB_ASRC :=
LIBRARY_NAME := application
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -I$(TOPDIR)/components/inc/bsp
LOCAL_INC += -I$(TOPDIR)/components/drv
LOCAL_INC += -I$(TOPDIR)/components/softmac
LOCAL_INC += -I$(TOPDIR)/components/iotapi
LOCAL_INC += -I$(TOPDIR)/components/netstack_wrapper
LOCAL_INC += -I$(TOPDIR)/components/third_party/fdk_aac_dec_andes/include
LOCAL_INC += -I$(TOPDIR)/components/third_party/fdk_aac_dec_andes/libAACdec/include
LOCAL_INC += -I$(TOPDIR)/components/third_party/fdk_aac_dec_andes/libSYS/include

LOCAL_INC += -I$(TOPDIR)/components/net/tcpip/lwip-1.4.0/src/include
LOCAL_INC += -I$(TOPDIR)/components/net/tcpip/lwip-1.4.0/src/include/ipv4
LOCAL_INC += -I$(TOPDIR)/components/net/tcpip/lwip-1.4.0/ports/icomm/include

ifeq ($(strip $(BLE_EN)),1)
LOCAL_INC += -Icomponents/ble/inc/common
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/mesh_core
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_common/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/mesh_common/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/log/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/mesh_core/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/nimble/host/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/porting/nimble/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/nimble/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/porting/npl/freertos/include
LOCAL_INC += -I$(TOPDIR)/components/third_party/apache-mynewt-nimble-1.2.0/common/include
endif

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
