LIB_SRC := ble/ble_ipc_interrupt_v2.c
LIB_SRC += ble/ble_lib_v2.c
#LIB_SRC += ble/ble_v2.c
LIB_SRC += ble/hci_lib.c
#LIB_SRC += cli/mini_cli.c
LIB_SRC += ble/ctrl_v2/ble_ll.c
LIB_SRC += ble/ctrl_v2/ble_ll_adv.c
LIB_SRC += ble/ctrl_v2/ble_ll_hwif_init.c
LIB_SRC += ble/ctrl_v2/ble_ll_if.c
LIB_SRC += ble/ctrl_v2/ble_ll_inita.c
LIB_SRC += ble/ctrl_v2/ble_ll_jammer.c
LIB_SRC += ble/ctrl_v2/ble_ll_master.c
LIB_SRC += ble/ctrl_v2/ble_ll_msgh.c
LIB_SRC += ble/ctrl_v2/ble_ll_ring.c
LIB_SRC += ble/ctrl_v2/ble_ll_scan.c
LIB_SRC += ble/ctrl_v2/ble_ll_scan_early_stopper.c
LIB_SRC += ble/ctrl_v2/ble_ll_slave.c
LIB_SRC += ble/ctrl_v2/ble_ll_tbx.c
LIB_SRC += ble/ctrl_v2/ble_ll_ut.c
LIB_SRC += ble/ctrl_v2/ble_llcp_slave.c
LIB_SRC += ble/ctrl_v2/ble_llcp_master.c
LIB_SRC += ble/ctrl_v2/ble_ll_scan_early_stopper.c
LIB_SRC += ble/ctrl_v2/ble_ll_slave.c
#LIB_SRC += ble/ctrl_v2/rt/ble_ll_hw_security.c
LIB_SRC += ble/ctrl_v2/rt/ble_ll_hwif.c
LIB_SRC += ble/ctrl_v2/rt/ble_ll_irqh.c
LIB_SRC += ble/ctrl_v2/rt/ble_ll_security.c
#LIB_SRC += ble/hci_ctrl/hci_cmd_declare.c
#LIB_SRC += ble/hci_ctrl/hci_cmdh.c
#LIB_SRC += ble/hci_ctrl/hci_ctrl.c
#LIB_SRC += ble/hci_ctrl/hci_evt_declare.c
#LIB_SRC += ble/hci_ctrl/hci_msgh.c
LIB_SRC += les_if/src/hci_wrapper.c
LIB_SRC += les_if/src/les_event.c
LIB_SRC += les_if/src/ll_wrapper.c
LIB_SRC += les_if/src/svc_handler.c
LIB_SRC += les_if/src/sys_wrapper.c
LIB_SRC += ble/host_v2/ble_host.c
LIB_SRC += ble/host_v2/host_timer.c
#LIB_SRC += ble/host_v2/att/att_client.c
#LIB_SRC += ble/host_v2/att/att_server.c
#LIB_SRC += ble/host_v2/att/att_tool.c
#LIB_SRC += ble/host_v2/att/att_wrapper.c
#LIB_SRC += ble/host_v2/att/attc_core.c
#LIB_SRC += ble/host_v2/att/attc_if.c
#LIB_SRC += ble/host_v2/att/atts_authen.c
#LIB_SRC += ble/host_v2/att/atts_author.c
#LIB_SRC += ble/host_v2/att/atts_core.c
#LIB_SRC += ble/host_v2/att/atts_if.c
#LIB_SRC += ble/host_v2/gap/gap_core.c
#LIB_SRC += ble/host_v2/gap/gap_if.c
#LIB_SRC += ble/host_v2/gap/gap_wrapper.c
#LIB_SRC += ble/host_v2/gattm/gattm_core.c
#LIB_SRC += ble/host_v2/gattm/gattm_if.c
#LIB_SRC += ble/host_v2/gattm/gattm_mem.c
#LIB_SRC += ble/host_v2/gattm/gattm_wrapper.c
#LIB_SRC += ble/host_v2/gatts/gatts_core.c
#LIB_SRC += ble/host_v2/gatts/gatts_if.c
#LIB_SRC += ble/host_v2/gatts/gatts_wrapper.c
#LIB_SRC += ble/host_v2/gattc/gattc_core.c
#LIB_SRC += ble/host_v2/gattc/gattc_if.c
#LIB_SRC += ble/host_v2/gattc/gattc_wrapper.c
#LIB_SRC += ble/host_v2/gattc/gattc_event.c
#LIB_SRC += ble/host_v2/gattc/gattc_proc.c
#LIB_SRC += ble/host_v2/l2cap/l2cap_cm.c
#LIB_SRC += ble/host_v2/l2cap/l2cap_composer.c
#LIB_SRC += ble/host_v2/l2cap/l2cap_core.c
#LIB_SRC += ble/host_v2/l2cap/l2cap_if.c
#LIB_SRC += ble/host_v2/l2cap/l2cap_rm.c
#LIB_SRC += ble/host_v2/l2cap/l2cap_slicer.c
#LIB_SRC += ble/host_v2/l2cap/l2cap_slq.c
#LIB_SRC += ble/host_v2/l2cap/l2cap_spm.c
#LIB_SRC += ble/host_v2/l2cap/l2cap_wrapper.c
#LIB_SRC += ble/host_v2/smp/smp_core.c
#LIB_SRC += ble/host_v2/smp/smp_if.c
#LIB_SRC += ble/host_v2/smp/smp_tool.c
#LIB_SRC += ble/host_v2/smp/smp_wrapper.c
LIB_SRC += drv/phy/ble_dtm.c
LIB_SRC += drv/phy/drv_phy.c
LIB_SRC += drv/adc/drv_adc_p7005.c
#LIB_SRC += drv/cipher/drv_cipher.c
#LIB_SRC += drv/tmr/drv_timer_p7005.c
#LIB_SRC += proj/system_CondorC.c

LIB_ASRC :=
LIBRARY_NAME := ble_lestack
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

RELEASE_SRC := 1
$(eval $(call link-lib,$(LIBRARY_NAME),$(LIB_SRC),$(LIB_ASRC),$(LOCAL_CFLAGS),$(LOCAL_INC),$(LOCAL_AFLAGS),$(MYDIR)))
