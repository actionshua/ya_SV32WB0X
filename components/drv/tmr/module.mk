
LIB_SRC := drv_tmr.c
LIB_SRC += drv_tim_timer.c

LIB_ASRC :=
LIBRARY_NAME := tmr
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -Icomponents/sys
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/tmr

RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
