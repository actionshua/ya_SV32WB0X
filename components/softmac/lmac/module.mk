LIB_SRC := edca.c
LIB_SRC += rc/rc.c
LIB_SRC += scanproc.c
ifeq ($(strip $(PROJECT)), SMAC)
LIB_SRC += mac_compensation.c
endif

LIB_ASRC :=
LIBRARY_NAME := lmac
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -I$(TOPDIR)/components/bsp
LOCAL_INC += -I$(TOPDIR)/components/inc
LOCAL_INC += -I$(TOPDIR)/components/drv
LOCAL_INC += -I$(TOPDIR)/components/inc/bsp/$(CHIP_NAME)
LOCAL_INC += -I$(TOPDIR)/components/softmac/lmac/rc/minstrel
LOCAL_INC += -I$(TOPDIR)/components/softmac/lmac/rc/native_rc
LOCAL_INC += -I$(TOPDIR)/components/softmac/lmac/rc
LOCAL_INC += -I$(TOPDIR)/components/softmac/lmac/txrx

RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
