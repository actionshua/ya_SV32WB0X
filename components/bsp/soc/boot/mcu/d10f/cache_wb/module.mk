
LIB_SRC := cache_wb.c

LIB_ASRC := start.S
LIBRARY_NAME := cache_wb
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=
LOCAL_INC +=

RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))


