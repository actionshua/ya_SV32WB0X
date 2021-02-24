
LIB_SRC := fsal.c
ifeq ($(strip $(SUPPORT_FFS)), 1)
LIB_SRC += flash/spiffs/fsal_flash_spiffs.c
endif
ifeq ($(strip $(SUPPORT_FFS)), 2)
LIB_SRC += flash/littlefs/fsal_flash_littlefs.c
endif
LIB_ASRC :=
LIBRARY_NAME := srm_fsal
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -I$(TOPDIR)/components/third_party/spiffs
LOCAL_INC += -I$(TOPDIR)/components/third_party/littlefs
ifeq ($(strip $(SUPPORT_SDC)),1)
LOCAL_INC += -I$(TOPDIR)/components/third_party/FatFs
endif
RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
