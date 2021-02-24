#
#LIB_SRC := main.c 
LIB_SRC := main.c custom_cmd.c host_cmd_handler.c
LIB_ASRC :=

LIBRARY_NAME := main
LOCAL_CFLAGS := -DLOCAL_MAIN
LOCAL_AFLAGS := -DLOCAL_AMAIN

LOCAL_INC := -Icomponents/local_lib
LOCAL_INC += -Icomponents/bsp
LOCAL_INC += -Icomponents/tools/toolbox
LOCAL_INC += -Icomponents/bsp/soc/lowpower
LOCAL_INC += -Icomponents/ble/inc/common
LOCAL_INC += -I$(PROJ_DIR)/src/cli

POST_BUILD_CMD += touch $(MYDIR)/main.c;

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
