
LIB_SRC := rf_toolbox.c
LIB_SRC += sa_fun.c
LIB_SRC += atcmd_iperf.c
LIB_SRC += logger.c
LIB_SRC += ilog.c

LIB_ASRC :=
LIBRARY_NAME := toolbox
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC += -Icomponents/inc
LOCAL_INC += -Icomponents/drv
LOCAL_INC += -Icomponents/sys
LOCAL_INC += -Icomponents/tools/atcmd
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/hsuart/
ifeq ($(strip $(BLE_EN)), 1)
LOCAL_INC += -Icomponents/ble/lestack/drv/phy
endif

ifeq ($(strip $(IPERF2_EN)),1)
LOCAL_INC += -Icomponents/third_party/iperf-2.0.5/include
endif
ifeq ($(strip $(IPERF3_EN)),1)
LOCAL_INC += -Icomponents/third_party/iperf3.0/
endif

RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
