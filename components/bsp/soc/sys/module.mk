
LIB_SRC := bsp.c
LIB_ASRC :=
LIBRARY_NAME := bsp
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -I$(TOPDIR)/components/osal
LOCAL_INC += -I$(TOPDIR)/components/fsal
LOCAL_INC += -I$(TOPDIR)/components/drv
LOCAL_INC += -I$(TOPDIR)/components/bsp/soc/$(CHIP_NAME)/hal/uart
LOCAL_INC += -I$(TOPDIR)/components/sys
LOCAL_INC += -I$(TOPDIR)/components/bsp/soc/lowpower
ifeq ($(strip $(SUPPORT_SDC)),1)
LOCAL_INC += -I$(TOPDIR)/components/third_party/FatFs
endif
LOCAL_INC += -Icomponents/crypto_hw

RELEASE_SRC := 2
$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
