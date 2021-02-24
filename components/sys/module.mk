
LIB_SRC := intc.c systick.c proftick.c backtrace.c sys_clock.c exception_info.c debug_module.c sys_dbg.c sys_random.c sys_info.c sys_rtc_mem.c system_api.c cxx_init.c
ifeq ($(strip $(XIP_MODE)), 1)
LIB_SRC += xip.c flash.c
endif

LIB_ASRC :=
LIBRARY_NAME := srm_sys
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC += -I$(TOPDIR)/components/drv
LOCAL_INC += -I$(TOPDIR)/components/inc
LOCAL_INC += -I$(TOPDIR)/components/bsp/soc/efuseapi
LOCAL_INC += -I$(TOPDIR)/components/bsp/soc/lowpower
LOCAL_INC += -I$(TOPDIR)/components/osal/freertos/kernel/Source/include
LOCAL_INC += -I$(TOPDIR)/components/osal/freertos
LOCAL_INC += -I$(TOPDIR)/components/osal/freertos/nds32
LOCAL_INC += -I$(TOPDIR)/components/tools/toolbox

RELEASE_SRC := 1

$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
