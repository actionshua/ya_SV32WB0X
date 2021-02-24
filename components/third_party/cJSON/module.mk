LIB_SRC := cJSON_test.c

LIB_ASRC :=
LIBRARY_NAME := cjson_test
LOCAL_CFLAGS += -Wno-address
LOCAL_AFLAGS +=
LOCAL_INC += -I$(TOPDIR)/components/third_party/cJSON
LOCAL_INC += -I$(TOPDIR)/components/tools/utility/SSV_cJSON

RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
