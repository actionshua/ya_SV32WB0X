
LIB_SRC := drv_dmac.c

LIB_ASRC :=
LIBRARY_NAME := dmac
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC :=
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/dmac

RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
