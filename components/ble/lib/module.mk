LIB_SRC := condor_ssv_lib.c
LIB_SRC += linked_queue.c
LIB_SRC += event_handler.c
LIB_SRC += aes.c

LIB_ASRC :=
LIBRARY_NAME := ble_lib
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -I$(TOPDIR)/components/bsp
LOCAL_INC := -I$(TOPDIR)/components/ble/bsp
LOCAL_INC += -I$(TOPDIR)/components/inc
LOCAL_INC += -I$(TOPDIR)/components/drv
LOCAL_INC += -I$(TOPDIR)/components
LOCAL_INC += -I$(TOPDIR)/components/tools/toolbox
LOCAL_INC += -I$(TOPDIR)/components/ble
LOCAL_INC += -I$(TOPDIR)/components/ble/inc
LOCAL_INC += -I$(TOPDIR)/components/ble/lib
RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
