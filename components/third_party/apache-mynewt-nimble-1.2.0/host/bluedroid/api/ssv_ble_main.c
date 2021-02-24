
#include "transport/ram/ble_hci_ram.h"
#include "soc_assert.h"
#include "hci_common.h"

/*Mesh API include*/
#include "ssv_ble_mesh_defs.h"
#include "ssv_ble_mesh_common_api.h"
#include "ssv_ble_mesh_networking_api.h"
#include "ssv_ble_mesh_provisioning_api.h"
#include "ssv_ble_mesh_config_model_api.h"
#include "ssv_ble_mesh_generic_model_api.h"
#include "ssv_ble_mesh_local_data_operation_api.h"

/*nimble*/
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "host/util/util.h"
#include "host/ble_hs.h"
#include "store/config/ble_store_config.h"
#include "ssv_timer.h"
#include "ssv_log.h"
#include "argtable3.h"
#include "ble_mesh_console_lib.h"
#include "ssv_ble_mesh_main.h"
#include "ble_mesh_cfg_srv_model.h"
#include "ble_mesh_adapter.h"
#include "ble_mesh_reg_gen_onoff_client_cmd.h"
#include "ble_mesh_register_provisioner_cmd.h"
#include "ble_mesh_register_node_cmd.h"
#include "ble_mesh_reg_cfg_client_cmd.h"
#if CONFIG_PERFORMANCE_CLIENT_MODEL
#include "ble_mesh_reg_test_perf_client_cmd.h"
#endif

#include "tools/toolbox/ilog.h"
#include "ble_api.h"

#if MESH_BLE_AUTO_RUN_EN
#include "atcmd_ble_mesh.h"
#include "atcmd.h"
#include "atcmd_general.h"
#endif

#if CONFIG_BLE_MESH_GPIO_DBG
#include "hal_gpio.h"
#include "TurismoE.h"
#endif


#if BLE_GATTS_API_TEST
#include "ssv_gatts_test.h"
#endif


#if BLE_GATTC_API_TEST
#include "ssv_gattc_test.h"
#endif

static SemaphoreHandle_t ble_sem;
static uint8_t own_addr_type;
void ble_store_config_init(void);
static uint8_t addr_val[6] = {0};
static void ble_on_reset(int reason)
{
    printf("Resetting state; reason=%d\n", reason);
}

static void ble_on_sync(void)
{
    int rc;

    rc = ble_hs_util_ensure_addr(0);
    assert(rc == 0);

    /* Figure out address to use while advertising (no privacy for now) */
    rc = ble_hs_id_infer_auto(0, &own_addr_type);
    if (rc != 0) {
        printf("error determining address type; rc=%d\n", rc);
        return;
    }

    rc = ble_hs_id_copy_addr(own_addr_type, addr_val, NULL);

    xSemaphoreGive(ble_sem);
}

void ble_host_task(void *param)
{
    printf("BLE Host Task Started");
    /* This function will return only when nimble_port_stop() is executed */
    nimble_port_run();

    nimble_port_freertos_deinit();
}

ssv_err_t bluetooth_init(void)
{
    ble_sem = xSemaphoreCreateBinary();
    if (ble_sem == NULL) {
        printf("***Failed to create mesh semaphore***");
        return SSV_FAIL;
    }

    nimble_port_init();
    /* Initialize the NimBLE host configuration. */
    ble_hs_cfg.reset_cb = ble_on_reset;
    ble_hs_cfg.sync_cb = ble_on_sync;
    ble_hs_cfg.store_status_cb = ble_store_util_status_rr;

    ble_store_config_init();
    nimble_port_freertos_init(ble_host_task);

    xSemaphoreTake(ble_sem, portMAX_DELAY);

    return SSV_BM_OK;
}

#define BLE_HCI_CMD         0x01
#define BLE_HCI_ACL         0x02
#define BLE_HCI_SCO         0x03
#define BLE_HCI_EVT         0x04

extern void cmd_if_ble_rx(u8 *cmd, u8 tx_len);

void ble_to_nimble_rx_evt_ssv(uint8_t *data, uint16_t len)
{
    int rc = 0;
    uint16_t event_len = 0;
    //ASSERT(ble_hci_uart_rx_cmd_cb != NULL);
    //rc = ble_hci_uart_rx_cmd_cb(data, ble_hci_uart_rx_cmd_arg);
    HCILOG_2(DIR_CTRL_TO_HOST, BLE_HCI_EVT, data, len);

    if (len < 6) {
        printf("len %d < 6 drop\n", len);
        return;
    }

    event_len = data[1] + 2;
    if (event_len > (CONFIG_BT_NIMBLE_HCI_EVT_BUF_SIZE - 1) || (event_len != len)) {
        printf("event_len %d, len %d, drop\n", event_len, len);
        return;
    }
    ble_hci_trans_ll_evt_tx(data);
}

void ble_to_nimble_rx_acl_ssv(const uint8_t *data, uint16_t len)
{//control to host
    int rc = 0;
    uint16_t count = 0;
    struct os_mbuf *m = NULL;

    HCILOG_2(DIR_CTRL_TO_HOST, BLE_HCI_ACL, (u8 *)data, len);

    count = ble_hci_trans_acl_buf_free_count(BLE_HCI_TRANS_BUF_ACL);
    if (count < 2) {
        printf("acl_ssv %d\n", count);
    }

    m = ble_hci_trans_acl_buf_alloc();
    if (!m) {
        printf("%s ble_hci_trans_acl_buf_alloc fail return\n", __func__);
        return;
    }

    memcpy(m->om_data, data, len);
    OS_MBUF_PKTLEN(m) = len;// + BLE_HCI_DATA_HDR_SZ;
    m->om_len = len;// + BLE_HCI_DATA_HDR_SZ;

    /*printf("%s %02X %02X %02X %02X len %d, OS_MBUF_PKTLEN(m) %d\n",
        __func__, data[0], data[1], data[2], data[3], len, OS_MBUF_PKTLEN(m));*/
    rc = ble_hci_trans_ll_acl_tx(m);

    if (rc != 0) {
        goto err;
    }
    return;

err:
    printf("%s ble_hci_uart_rx_acl_cb err %d\n", __func__, rc);
    os_mbuf_free_chain(m);
    return;

}

void ble_hci_rx_ssv(uint8_t *data, uint16_t len)
{/*data and len are include hci type(01 or 02)*/
    uint8_t *evbuf;

    if (len < 3) {
        printf("%s invalid input len %d\n", __func__, len);
        return;// invalid input
    }

    if (data == NULL) {
        printf("%s invalid input data = NULL\n", __func__);
        return;// invalid input
    }
    //remove hci type(01 or 02)
    if (data[0] == BLE_HCI_EVT) {
        ble_to_nimble_rx_evt_ssv(&data[1], len - 1);
    } else if (data[0] == BLE_HCI_ACL) {
        ble_to_nimble_rx_acl_ssv(&data[1], len - 1);
    }
}

void cmd_if_ble_rx(u8 *cmd, u8 tx_len) {//mesh hci cmd to controller
    u8  sg_mesh_sync_evt_buf[256];
    u16  sg_mesh_sync_evt_len = 0;

    sg_mesh_sync_evt_len = les_hci_cmd(tx_len, cmd, sizeof(sg_mesh_sync_evt_buf), sg_mesh_sync_evt_buf);
    if(sg_mesh_sync_evt_len)
    {
        ble_hci_rx_ssv(sg_mesh_sync_evt_buf, sg_mesh_sync_evt_len);
    }

    return;
}

ATTRIBUTE_SECTION_BLE_RESTORE uint8_t g_hci_cmd[BLE_HCI_SET_DATALEN_TX_OCTETS_MAX + 1] = {0};
int ble_hci_trans_rx_cmd_fn_ssv(uint8_t *cmd, void *arg)//nimble to controller, hci cmd
{

    uint8_t cmd_len = cmd[2] + BLE_HCI_CMD_HDR_LEN + 1;/*include hci type 01*/
    if ((cmd_len + BLE_HCI_CMD_HDR_LEN) > sizeof(g_hci_cmd))
        ASSERT(0);

    g_hci_cmd[0] = BLE_HCI_CMD;
    ASSERT(cmd_len < BLE_HCI_SET_DATALEN_TX_OCTETS_MAX);
    memcpy(&g_hci_cmd[1], cmd, cmd_len);
    ble_hci_trans_buf_free(cmd);
    cmd_if_ble_rx(g_hci_cmd, cmd_len);
    return 0;
}

//extern s16 hci_aclh( u32 acl_len, const u8* acl);


uint8_t *g_acl_data = NULL;
#define ACL_DATA_LEN 2000
int ble_hci_trans_rx_acl_fn_ssv(struct os_mbuf *om, void *arg)//nimble to controller, acl data
{
    uint8_t len = 0;
    struct os_mbuf *cur;

    if (g_acl_data == NULL) {
        printf("%s ***** g_acl_data is NULL ****\n", __func__);
        return 0;
    }

    //om = os_mbuf_prepend_pullup(om, 1);
    //om->om_data[0] = BLE_HCI_ACL;

    g_acl_data[0] = BLE_HCI_ACL;
    len = 1;

    cur = om;

    //cal buffer len
    while (cur != NULL) {
        memcpy(g_acl_data + len, cur->om_data, cur->om_len);
        len += cur->om_len;
        if (len > ACL_DATA_LEN) {
            printf("%s ***** len %d error ****\n", __func__,len);
            os_mbuf_free_chain(om);
            return 0;
        }
        cur = SLIST_NEXT(cur, om_next);

        if (!cur)
            break;

        if (cur->om_len + len > ACL_DATA_LEN) {
            printf("%s ***** om_len %d error ****\n", __func__,cur->om_len);
            os_mbuf_free_chain(om);
            return 0;
        }
    }

    HCILOG(DIR_HOST_TO_CTRL, g_acl_data, len);
//    hci_aclh(len, g_acl_data);
	cmd_if_ble_rx(g_acl_data, len);

    os_mbuf_free_chain(om);
    return 0;
}

void app_ble_init(void)
{
    ssv_err_t err;

    /*init default init for ssv mesh core*/
    ble_hci_ram_init();
    if (g_acl_data == NULL) {
        g_acl_data = osi_malloc(sizeof(uint8_t)*ACL_DATA_LEN);
        if (g_acl_data == NULL)
            printf("%s malloc g_acl_data error", __func__);
    }


    /* set callback func, nimble to controller hci and acl data*/
    ble_hci_trans_cfg_ll(ble_hci_trans_rx_cmd_fn_ssv, NULL, ble_hci_trans_rx_acl_fn_ssv, NULL);

    err = bluetooth_init();
    if (err) {
        printf("mesh bluetooth_init failed (err %d)", err);
        return;
    }

#if (BLE_GATTS_API_TEST || BLE_GATTC_API_TEST)
    #if (BLE_GATTS_API_TEST)
    ble_gatts_test_run();
    #endif

    #if (BLE_GATTC_API_TEST)
    ble_gattc_test_run();
    #endif
#endif

}
