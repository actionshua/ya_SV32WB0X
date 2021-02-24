ifeq ($(strip $(SUPPORT_SDC)),1)
LIB_SRC := diskio.c
LIB_SRC += ffsystem.c
LIB_SRC += ff.c
LIB_SRC += ffunicode.c
LIB_SRC += sd_diskio.c
else
LIB_SRC := ff_dummy.c
endif


LIB_ASRC :=
LIBRARY_NAME := fatfs
LOCAL_CFLAGS += -Wno-address -DCONFIG_STORAGE_TYPE=1
LOCAL_AFLAGS +=
LOCAL_INC += -I$(TOPDIR)/components/third_party/FatFs
LOCAL_INC += -I$(PROJ_DIR)/src/board/param/
RELEASE_SRC := 2
$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
