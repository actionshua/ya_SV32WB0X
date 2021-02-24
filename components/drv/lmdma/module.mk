
LIB_SRC := drv_lmdma.c

LIB_ASRC :=
LIBRARY_NAME := lmdma
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC :=
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/lmdma

RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
