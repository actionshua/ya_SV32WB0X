LOCAL_VAR := 

LIB_SRC := pvmp3_fsal.c

LIB_ASRC :=
LIBRARY_NAME := pvmp3_fsal_fs
LOCAL_CFLAGS += -ffunction-sections -fdata-sections
#LOCAL_CFLAGS += -ffunction-sections -fdata-sections -DPF_COUNTER
#LOCAL_CFLAGS += -Wno-address
LOCAL_AFLAGS += -ffunction-sections -fdata-sections
LOCAL_INC :=
#LOCAL_INC += -I$(MYDIR)/include
#LOCAL_INC += -I$(TOPDIR)/components/drv
LOCAL_INC += -Icomponents/third_party/pvmp3decoder/include
LOCAL_INC += -Icomponents/third_party/pvmp3decoder/src
LOCAL_INC += -Icomponents/audio/codec_common

RELEASE_SRC := 2
$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
