LOCAL_VAR := 

ifneq ($(strip $(BUILD_ROM)), 1)
LIB_SRC := $(LOCAL_VAR)/src/real/dqchan.c
LIB_SRC += $(LOCAL_VAR)/src/real/imdct.c
LIB_SRC += $(LOCAL_VAR)/src/real/stproc.c
LIB_SRC += $(LOCAL_VAR)/src/real/bitstream.c
LIB_SRC += $(LOCAL_VAR)/src/real/dequant.c
LIB_SRC += $(LOCAL_VAR)/src/real/scalfact.c
LIB_SRC += $(LOCAL_VAR)/src/real/subband.c
LIB_SRC += $(LOCAL_VAR)/src/real/trigtabs.c
LIB_SRC += $(LOCAL_VAR)/src/real/dct32.c
LIB_SRC += $(LOCAL_VAR)/src/real/huffman.c
LIB_SRC += $(LOCAL_VAR)/src/real/hufftabs.c
LIB_SRC += $(LOCAL_VAR)/src/real/buffers.c
LIB_SRC += $(LOCAL_VAR)/src/real/polyphase.c
LIB_SRC += $(LOCAL_VAR)/src/mp3dec.c
LIB_SRC += $(LOCAL_VAR)/src/mp3tabs.c
#LIB_SRC += $(LOCAL_VAR)/src/helix_memory.c
LIB_SRC += $(LOCAL_VAR)/src/testwrap/debug.c
LIB_SRC += $(LOCAL_VAR)/src/testwrap/timing.c
#LIB_SRC += $(LOCAL_VAR)/testwrap/main.c
else
LIB_SRC := $(LOCAL_VAR)/src/real/polyphase.c
LIB_SRC += $(LOCAL_VAR)/src/real/imdct.c
LIB_SRC += $(LOCAL_VAR)/src/real/trigtabs.c
LIB_SRC += $(LOCAL_VAR)/src/real/dct32.c
endif

LIB_ASRC :=
LIBRARY_NAME := helix
LOCAL_CFLAGS += -ffunction-sections -fdata-sections -Wno-maybe-uninitialized -Wno-missing-braces
#LOCAL_CFLAGS += -ffunction-sections -fdata-sections -DPF_COUNTER
#LOCAL_CFLAGS += -Wno-address
LOCAL_AFLAGS += -ffunction-sections -fdata-sections
LOCAL_INC :=
#LOCAL_INC += -I$(MYDIR)/include
#LOCAL_INC += -I$(TOPDIR)/components/drv
LOCAL_INC += -I$(MYDIR)/inc
LOCAL_INC += -I$(MYDIR)/inc/real
LOCAL_INC += -I$(MYDIR)/inc/real/andes
LOCAL_INC += -I$(MYDIR)/inc/pub
LOCAL_INC += -I$(MYDIR)/inc/testwrap
RELEASE_SRC := 2
$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
