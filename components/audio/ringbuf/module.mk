LOCAL_VAR := 

LIB_SRC := ringbuf.c

LIB_ASRC :=
LIBRARY_NAME := ringbuf
LOCAL_CFLAGS += -ffunction-sections -fdata-sections
LOCAL_AFLAGS += -ffunction-sections -fdata-sections
LOCAL_INC :=
RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
