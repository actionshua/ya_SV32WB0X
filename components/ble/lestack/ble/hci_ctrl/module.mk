
LIB_SRC := hci_cmd_declare.c
LIB_SRC += hci_cmdh.c
LIB_SRC += hci_ctrl.c
LIB_SRC += hci_evt_declare.c
LIB_SRC += hci_msgh.c

LIB_ASRC :=
LIBRARY_NAME := ble_les_hci
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -I$(TOPDIR)/components/ble/bsp
LOCAL_INC += -I$(TOPDIR)/components/inc
LOCAL_INC += -I$(TOPDIR)/components/drv
LOCAL_INC += -I$(TOPDIR)/components
LOCAL_INC += -I$(TOPDIR)/components/tools/toolbox
LOCAL_INC += -I$(TOPDIR)/components/ble
LOCAL_INC += -I$(TOPDIR)/components/ble/inc
LOCAL_INC += -I$(TOPDIR)/components/ble/lib
LOCAL_INC += -I$(TOPDIR)/components/ble/lestack
LOCAL_INC += -I$(TOPDIR)/components/ble/lestack/drv
LOCAL_INC += -I$(TOPDIR)/components/ble/lestack/ble/host_v2
LOCAL_INC += -I$(TOPDIR)/components/third_party/apache-mynewt-nimble-1.2.0/host/nimble/include/nimble
LOCAL_INC += -I$(TOPDIR)/components/third_party/apache-mynewt-nimble-1.2.0/porting/nimble/include
LOCAL_INC += -I$(TOPDIR)/components/third_party/apache-mynewt-nimble-1.2.0/host/nimble/include
LOCAL_INC += -I$(TOPDIR)/components/third_party/apache-mynewt-nimble-1.2.0/porting/npl/freertos/include
LOCAL_INC += -I$(TOPDIR)/components/third_party/apache-mynewt-nimble-1.2.0/host/nimble/host/mesh/src

RELEASE_SRC := 0
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
