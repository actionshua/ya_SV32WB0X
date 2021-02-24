
LIB_SRC := heap_mem.c heap_psram.c heap_ilm.c heap_dlm.c heap_bus.c

LIB_ASRC :=
LIBRARY_NAME := memmgr
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -I$(TOPDIR)/components/drv
LOCAL_INC += -I$(TOPDIR)/components/bsp/soc/lowpower
LOCAL_INC += -I$(TOPDIR)/components/tools/toolbox
LOCAL_INC += -I$(TOPDIR)/components/osal
LOCAL_INC += -I$(TOPDIR)/components/osal/freertos/kernel/Source/include
LOCAL_INC += -I$(TOPDIR)/components/osal/freertos
LOCAL_INC += -I$(TOPDIR)/components/osal/freertos/nds32
LOCAL_INC += -I$(TOPDIR)/components/tools/toolbox

RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))

