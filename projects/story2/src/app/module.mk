
LIB_SRC := app_main.c custom_cmd.c
ifeq ($(strip $(DEMO_TYPE)), 1)
LIB_SRC += player_task.c
endif
ifeq ($(strip $(DEMO_TYPE)), 2)
LIB_SRC += kws_task.c
endif
ifeq ($(strip $(DEMO_TYPE)), 3)
LIB_SRC += kws_task.c
endif
LIB_ASRC :=
LIBRARY_NAME := story
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -Icomponents/local_lib
LOCAL_INC += -Icomponents/bsp
LOCAL_INC += -Icomponents/tools/toolbox
LOCAL_INC += -Icomponents/bsp/soc/lowpower
LOCAL_INC += -I$(PROJ_DIR)/src/cli
LOCAL_INC += -Icomponents/audio/acoustic_algorithm
LOCAL_INC += -Icomponents/audio/codec_common
LOCAL_INC += -Icomponents/third_party/shine/lib

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
