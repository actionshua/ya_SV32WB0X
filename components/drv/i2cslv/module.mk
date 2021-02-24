
LIB_SRC := drv_i2cslv.c

LIB_ASRC :=
LIBRARY_NAME := i2cslv
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC += -Icomponents/inc
LOCAL_INC += -Icomponents/inc/bsp/$(CHIP_NAME)
LOCAL_INC += -Icomponents/inc/bsp
LOCAL_INC += -Icomponents/drv/gpio
LOCAL_INC += -Icomponents/drv/pinmux
LOCAL_INC := -Icomponents/bsp/soc/$(CHIP_NAME)/hal/i2cslv
LOCAL_INC += -Icomponents/drv/$(CHIP_NAME)

RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
