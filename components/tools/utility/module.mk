LIB_SRC := 
LIB_SRC += ssv_lib.c

LIB_ASRC :=
LIBRARY_NAME := utility
LOCAL_CFLAGS +=
LOCAL_AFLAGS +=
LOCAL_INC := -I$(SDKDIR)/components/tools/
RELEASE_SRC := 2
$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
