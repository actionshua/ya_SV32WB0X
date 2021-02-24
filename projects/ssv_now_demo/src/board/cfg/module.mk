
LIB_SRC :=
#ifeq ($(strip $(SUPPORT_PARTITION_MP_TABLE)), 1)
#LIB_SRC += sa_fun.c
#endif
ifeq ($(strip $(SUPPORT_PARTITION_CFG_TABLE)), 1)
LIB_SRC += mac_fun.c
endif
ifeq ($(strip $(SUPPORT_PARTITION_USER_RAW)), 1)
LIB_SRC += user_fun.c
endif

LIB_ASRC :=
LIBRARY_NAME := cfg
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -Icomponents/bsp -Icomponents/sys
LOCAL_INC += -Icomponents/tools/utility/SSV_cJSON
LOCAL_INC += -Icomponents/tools/atcmd
LOCAL_INC += -Icomponents/tools/toolbox

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
