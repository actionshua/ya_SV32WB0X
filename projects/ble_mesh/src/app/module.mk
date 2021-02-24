#
#LIB_SRC := main.c
LIB_SRC := main.c custom_cmd.c
LIB_ASRC :=

LIBRARY_NAME := main
LOCAL_CFLAGS := -DLOCAL_MAIN
LOCAL_AFLAGS := -DLOCAL_AMAIN

LOCAL_INC := -Icomponents/local_lib
LOCAL_INC += -Icomponents/bsp
LOCAL_INC += -Icomponents/tools/toolbox
LOCAL_INC += -Icomponents/bsp/soc/lowpower
LOCAL_INC += -Icomponents/ble/inc/common
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/mesh_core
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_common/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/mesh_common/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/log/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/ble_mesh/ssv_ble_mesh/mesh_core/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/nimble/host/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/porting/nimble/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/nimble/include
LOCAL_INC += -Icomponents/third_party/apache-mynewt-nimble-1.2.0/porting/npl/freertos/include
LOCAL_INC += -I$(TOPDIR)/components/third_party/apache-mynewt-nimble-1.2.0/common/include

LOCAL_INC += -I$(PROJ_DIR)/src/cli

POST_BUILD_CMD += touch $(MYDIR)/main.c;

$(eval $(call build-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
