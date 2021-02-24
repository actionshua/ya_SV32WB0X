ifeq ($(strip $(OS)), freertos)
LIB_SRC := osal_freertos.c
LIB_SRC += osal_freertos_slow.c
#LIB_SRC += heap_psram.c
LIB_SRC += heap_debug.c
LIB_SRC += osal_freertos_trace.c
LOCAL_INC += -Ifreertos
endif
ifeq ($(strip $(OS)), rhino)
LIB_SRC := osal_rhino.c
LIB_SRC += heap_psram.c
LIB_SRC += heap_debug.c
endif

ifeq ($(strip $(SUPPORT_SRM_TASK_LOG)), 1)
LIB_SRC += tasklog.c
endif

LIB_ASRC :=
LIBRARY_NAME := srm_osal
LOCAL_CFLAGS := -fno-omit-frame-pointer -mv3push -mno-fp-as-gp
LOCAL_AFLAGS :=

LOCAL_INC := -I$(TOPDIR)/components/drv
LOCAL_INC += -Icomponents/bsp/soc/lowpower
LOCAL_INC += -Icomponents/tools/toolbox

RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
