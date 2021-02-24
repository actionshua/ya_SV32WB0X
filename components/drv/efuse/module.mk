
LIB_SRC := drv_efuse.c
#LIB_SRC += hal_efuse.c

LIB_ASRC :=
LIBRARY_NAME := efuse
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC += -Icomponents/inc
LOCAL_INC += -Icomponents/inc/bsp
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal/efuse

RELEASE_SRC := 0

$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
