
LIB_SRC := drv_pinmux.c

LIB_ASRC :=
LIBRARY_NAME := pinmux
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC += -Icomponents/inc
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/pinmux
LOCAL_INC += -Icomponents/inc/bsp
LOCAL_INC += -Icomponents/drv/gpio

RELEASE_SRC := 2
$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
