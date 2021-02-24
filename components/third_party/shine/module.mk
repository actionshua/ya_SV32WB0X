
LIB_SRC := lib/bitstream.c
LIB_SRC += lib/huffman.c
LIB_SRC += lib/l3bitstream.c
LIB_SRC += lib/l3loop.c
LIB_SRC += lib/l3mdct.c
LIB_SRC += lib/l3subband.c
LIB_SRC += lib/layer3.c
LIB_SRC += lib/reservoir.c
LIB_SRC += lib/tables.c

LIB_ASRC :=
LIBRARY_NAME := shine
LOCAL_CFLAGS += -Wno-address
LOCAL_AFLAGS +=
LOCAL_INC += -I$(TOPDIR)/components/third_party/shine/lib

RELEASE_SRC := 2

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))

