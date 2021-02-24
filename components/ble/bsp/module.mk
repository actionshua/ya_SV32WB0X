LIB_SRC := msg.c
#LIB_SRC += rc32_cfg_p7005.c
#LIB_SRC += heap.c
#LIB_SRC += patch_p7005.c
LIB_SRC += power.c
#LIB_SRC += power_cfg_p7005.c
#LIB_SRC += rc32_cali.c
#LIB_SRC += ilog.c
LIB_SRC += bsp_p7005.c
#LIB_SRC += nmi.c
LIB_SRC += cs.c
#LIB_SRC += ilog.c

LIB_ASRC :=
LIBRARY_NAME := ble_bsp
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -I$(TOPDIR)/components/ble/bsp
LOCAL_INC := -I$(TOPDIR)/components/ble/lestack/cli
LOCAL_INC += -I$(TOPDIR)/components/inc
LOCAL_INC += -I$(TOPDIR)/components/drv
LOCAL_INC += -I$(TOPDIR)/components/tools/toolbox
LOCAL_INC += -I$(TOPDIR)/components
LOCAL_INC += -I$(TOPDIR)/components/ble
LOCAL_INC += -I$(TOPDIR)/components/ble/inc
LOCAL_INC += -I$(TOPDIR)/components/ble/lib
LOCAL_INC += -I$(TOPDIR)/components/ble/lestack
LOCAL_INC += -I$(TOPDIR)/components/ble/lestack/drv
LOCAL_INC += -I$(TOPDIR)/components/ble/lestack/ble/host_v2
RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
