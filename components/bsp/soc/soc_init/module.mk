#LIB_SRC := init_mem.c
LIB_SRC := soc_init.c
#LIB_SRC += soc_pad_cfg.c

LIB_ASRC :=
LIBRARY_NAME := soc_init
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=
LOCAL_INC +=
LOCAL_INC += -Icomponents/drv
ifeq ($(strip $(CHIP_NAME)),ssv6006)
LOCAL_INC += -I$(PROJ_DIR)/src/board/inc/custom
else
LOCAL_INC += -I$(PROJ_DIR)/src/board/inc/custom/$(CHIP_NAME)/$(IC_PACKAGE)/
endif
LOCAL_INC += -Icomponents/bsp/soc/$(CHIP_NAME)/hal
LOCAL_INC += -Icomponents/sys
LOCAL_INC += -Icomponents/tools/fotalib/inc
LOCAL_INC += -Icomponents/acp

RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
