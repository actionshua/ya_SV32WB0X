
LIB_SRC := drv_ampdu.c

LIB_ASRC :=
LIBRARY_NAME := ampdu
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -I$(PROJ_DIR)/src/fw/driver
LOCAL_INC += -Icomponents/drv
LOCAL_INC += -I$(PROJ_DIR)/src/fw/RedBull-turismo
LOCAL_INC += -I$(PROJ_DIR)/src/fw/RedBull-turismo/include
LOCAL_INC += -I$(PROJ_DIR)/src/fw/RedBull-turismo/include/ieee80211
LOCAL_INC += -I$(PROJ_DIR)/src/fw/RedBull-turismo/mac80211
LOCAL_INC += -I$(PROJ_DIR)/src/fw/RedBull-turismo/mac80211/rc
LOCAL_INC += -I$(PROJ_DIR)/src/fw/RedBull-turismo/mac80211/supplicant

RELEASE_SRC := -1

$(eval $(call link-obj,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
