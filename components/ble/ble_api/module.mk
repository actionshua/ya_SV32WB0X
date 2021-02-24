LIB_SRC := ble_api.c

LIB_ASRC :=
LIBRARY_NAME := ble_api
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC += -I$(TOPDIR)/components/inc
LOCAL_INC += -I$(TOPDIR)/components/drv
LOCAL_INC += -I$(TOPDIR)/components
LOCAL_INC += -I$(TOPDIR)/components/ble/inc/common

RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
