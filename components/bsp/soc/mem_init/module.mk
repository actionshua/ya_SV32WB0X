LIB_SRC := init_mem.c
#LIB_SRC += soc_pad_cfg.c

LIB_ASRC :=
LIBRARY_NAME := mem_init
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=
LOCAL_INC +=
LOCAL_INC += -Icomponents/drv
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal
LOCAL_INC += -Icomponents/sys
LOCAL_INC += -Icomponents/tools/fotalib/inc
LOCAL_INC += -Icomponents/acp

RELEASE_SRC := 1

$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
