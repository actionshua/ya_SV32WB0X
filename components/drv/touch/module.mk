
LIB_SRC := drv_touch.c

LIB_ASRC :=
LIBRARY_NAME := touch
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -Icomponents/bsp/soc/$(CHIP_NAME)/hal/touch
LOCAL_INC += -Icomponents/drv/touch

RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
