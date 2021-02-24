LIB_SRC := fsal_sdc_fatfs.c

LIB_ASRC :=
LIBRARY_NAME := srm_fsal_sdc
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -I$(TOPDIR)/components/third_party/spiffs
ifeq ($(strip $(SUPPORT_SDC)),1)
LOCAL_INC += -I$(TOPDIR)/components/third_party/FatFs
endif
RELEASE_SRC := 2
$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
