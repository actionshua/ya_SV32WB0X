LIB_SRC := 
LIB_SRC += acp_core.c

LIB_ASRC :=
LIBRARY_NAME := acp
LOCAL_CFLAGS += -Wno-address
LOCAL_AFLAGS +=
LOCAL_INC += -I$(TOPDIR)/components/tools/fotalib/inc
LOCAL_INC += -I$(TOPDIR)/components/osal/freertos/kernel/Source/include
LOCAL_INC += -I$(TOPDIR)/components/osal/freertos
LOCAL_INC += -I$(TOPDIR)/components/osal/freertos/nds32
LOCAL_INC += -I$(TOPDIR)/components/tools/toolbox
LOCAL_INC += -I$(SDKDIR)/components/third_party/mbedtls
LOCAL_INC += -I$(SDKDIR)/components/third_party/mbedtls/include
RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
