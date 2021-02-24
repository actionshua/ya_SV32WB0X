
LIB_SRC := lfs.c
LIB_SRC += lfs_util.c
LIB_SRC += bd/lfs_filebd.c
LIB_SRC += bd/lfs_rambd.c
LIB_SRC += bd/lfs_testbd.c

LIB_ASRC :=
LIBRARY_NAME := littlefs
LOCAL_CFLAGS +=
LOCAL_AFLAGS +=
LOCAL_INC += -I$(TOPDIR)/components/third_party/littlefs-master
LOCAL_INC += -I$(TOPDIR)/components/third_party/littlefs-master/bd
LOCAL_INC += -I$(PROJ_DIR)/src/board/param/
RELEASE_SRC := 2
$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
