
ifeq ($(strip $(CHIP_NAME)),ssv6020B)
LIB_SRC := drv_i2s.c
else
LIB_SRC := drv_i2s.c
endif

LIB_ASRC :=
LIBRARY_NAME := i2s
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC += -Icomponents/inc
LOCAL_INC += -Icomponents/inc/bsp/$(CHIP_NAME)
LOCAL_INC += -Icomponents/inc/bsp
LOCAL_INC += -Icomponents/drv/gpio
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/i2s
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/gpio
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/dmac
LOCAL_INC += -Icomponents/drv/pinmux
LOCAL_INC += -Icomponents/drv/dmac
LOCAL_INC += -Icomponents/drv/$(CHIP_NAME)


RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
