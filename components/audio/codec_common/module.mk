LOCAL_VAR := 

LIB_SRC := codec_common.c

LIB_ASRC :=
LIBRARY_NAME := codec_common

LOCAL_INC :=
LOCAL_INC += -I$(TOPDIR)/components/audio/codec
LOCAL_INC += -I$(TOPDIR)/components/audio/codec_common

RELEASE_SRC := 2
$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
