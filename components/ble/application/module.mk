LIB_SRC := les_if/api/src/att_api.c
#LIB_SRC += les_if/api/src/gap_api.c
#LIB_SRC += les_if/api/src/gattc_api.c
#LIB_SRC += les_if/api/src/gattm_api.c
#LIB_SRC += les_if/api/src/gatts_api.c
LIB_SRC += les_if/api/src/hci_api.c
#LIB_SRC += les_if/api/src/l2cap_api.c
#LIB_SRC += les_if/api/src/ll_api.c
#LIB_SRC += les_if/api/src/smp_api.c
LIB_SRC += les_if/api/src/sys_api.c
#LIB_SRC += appl/common/appl_array_list.c
#LIB_SRC += appl/common/appl_error.c
LIB_SRC += appl/common/appl_linked_queue.c
#LIB_SRC += appl/common/appl_log.c
LIB_SRC += appl/common/appl_lq_combo.c
LIB_SRC += appl/common/appl_mem.c
LIB_SRC += appl/common/appl_sleep.c
#LIB_SRC += appl/les/appl_les_database.c
LIB_SRC += appl/les/appl_les_event_dispatcher.c
LIB_SRC += appl/les/appl_les_event_queue.c
#LIB_SRC += appl/les/appl_les_manager.c
#LIB_SRC += appl/sys/appl_sys_nvram.c
LIB_SRC += cmd_if/cmd_if.c
LIB_SRC += cmd_if/cmd_if_les_evth.c
#LIB_SRC += drv/adc/drv_adc_p7005.c
#LIB_SRC += drv/dbg_uart/drv_dbg_uart_p7005.c
LIB_SRC += drv/dtm/two_wire_hdl.c
#LIB_SRC += drv/gpio/drv_gpio.c
#LIB_SRC += hci/drv_uart.c
LIB_SRC += hci/hci_uart.c
#LIB_SRC += hci/cli.c
#LIB_SRC += hci/cli_cmd.c
#LIB_SRC += hci/main.c

LIB_ASRC :=
LIBRARY_NAME := ble_application
LOCAL_CFLAGS :=
LOCAL_AFLAGS :=

LOCAL_INC := -I$(TOPDIR)/components/ble/bsp
LOCAL_INC += -I$(TOPDIR)/components/inc
LOCAL_INC += -I$(TOPDIR)/components/drv
LOCAL_INC += -I$(TOPDIR)/components/tools/toolbox
LOCAL_INC += -I$(TOPDIR)/components
LOCAL_INC += -I$(TOPDIR)/components/ble
LOCAL_INC += -I$(TOPDIR)/components/ble/inc
LOCAL_INC += -I$(TOPDIR)/components/ble/lib
LOCAL_INC += -I$(TOPDIR)/components/ble/application
LOCAL_INC += -I$(TOPDIR)/components/ble/application/hci
LOCAL_INC += -I$(TOPDIR)/components/third_party/apache-mynewt-nimble-1.2.0/nimble/include/nimble
LOCAL_INC += -I$(TOPDIR)/components/third_party/apache-mynewt-nimble-1.2.0/porting/nimble/include
LOCAL_INC += -I$(TOPDIR)/components/third_party/apache-mynewt-nimble-1.2.0/nimble/include
LOCAL_INC += -I$(TOPDIR)/components/third_party/apache-mynewt-nimble-1.2.0/porting/npl/freertos/include
LOCAL_INC += -I$(TOPDIR)/components/third_party/apache-mynewt-nimble-1.2.0/nimble/host/mesh/src

RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
