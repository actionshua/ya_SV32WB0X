LIB_SRC := 
LIB_SRC += ssv_now.c

LIB_ASRC :=
LIBRARY_NAME := ssv_now
LOCAL_CFLAGS += -Wno-address
#LOCAL_CFLAGS += -Wno-address
LOCAL_AFLAGS +=
LOCAL_INC := -I$(TOPDIR)/components/tools/ssv_now
#LOCAL_INC += -I$(TOPDIR)/components/wifi_pkg_cap
#LOCAL_INC += -I$(TOPDIR)/components/third_party/mbedtls/include
#LOCAL_INC += -I$(TOPDIR)/components/drv
#LOCAL_INC += -I$(TOPDIR)/components/softmac
LOCAL_INC += -I$(TOPDIR)/components/iotapi
RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
