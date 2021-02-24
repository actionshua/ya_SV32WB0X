
LIB_SRC := drv_uart.c
LIB_SRC += drv_comport.c

LIB_ASRC :=
LIBRARY_NAME := uart
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -Icomponents/drv
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/uart
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/hsuart

RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
