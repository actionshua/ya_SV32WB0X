
LIB_SRC := drv_spimst.c

LIB_ASRC :=
LIBRARY_NAME := spimst
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC += -Icomponents/inc
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/spimst
LOCAL_INC += -Icomponents/inc/bsp
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/gpio
LOCAL_INC += -Icomponents/drv/gpio
LOCAL_INC += -Icomponents/drv/pinmux
LOCAL_INC += -Icomponents/drv/dmac

RELEASE_SRC := 2
$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
