
LIB_SRC := hal_spimst.c

LIB_ASRC :=
LIBRARY_NAME := hal_spimst
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC += -Icomponents/inc
LOCAL_INC += -Icomponents/inc/bsp/$(CHIP_NAME)
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/dmac
LOCAL_INC += -Icomponents/inc/bsp
LOCAL_INC += -Icomponents/hal/dmac

RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
