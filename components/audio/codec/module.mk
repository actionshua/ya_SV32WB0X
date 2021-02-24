LOCAL_VAR := 

LIB_SRC := es8311.c
LIB_SRC += es8374.c
LIB_SRC += es8388.c

LIB_ASRC :=
LIBRARY_NAME := codec

LOCAL_INC :=
LOCAL_INC += -I$(TOPDIR)/components/audio/codec
LOCAL_INC += -I$(TOPDIR)/components/audio/codec_common

RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
