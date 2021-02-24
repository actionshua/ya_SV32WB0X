
LIB_SRC := drv_phy.c
LIB_SRC += drv_phy_isr.c
LIB_SRC += rf_api.c
LIB_SRC += rssi_api.c
LIB_SRC += extpa_api.c
LIB_SRC += ./$(CHIP_NAME)/turismo_common.c
ifeq ($(strip $(TARGET_DEF)), ASIC)
LIB_SRC += ./$(CHIP_NAME)/ssv6020_common.c
endif

LIB_ASRC :=
LIBRARY_NAME := phy
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -Icomponents/bsp
LOCAL_INC := -Icomponents/bsp/soc
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/gpio
LOCAL_INC += -Icomponents/inc
LOCAL_INC += -Icomponents/drv
LOCAL_INC += -Icomponents/drv/phy
LOCAL_INC += -Icomponents/drv/phy/$(CHIP_NAME)
LOCAL_INC += -Icomponents/drv/phy/$(CHIP_NAME)/$(TARGET_DEF)
LOCAL_INC += -Icomponents/drv/phy/$(CHIP_NAME)/$(TARGET_DEF)/$(FRONTEND)
LOCAL_INC += -Icomponents/inc/bsp/$(CHIP_NAME)
LOCAL_INC += -Icomponents/ble/lestack
LOCAL_INC += -Icomponents/ble
LOCAL_INC += -Icomponents/ble/inc
LOCAL_INC += -Icomponents/ble/lib

RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
