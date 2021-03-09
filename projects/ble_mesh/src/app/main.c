#include <stdio.h>
#include <osal.h>
#include <bsp.h>
#include <cli.h>
#include <wifi_api.h>
#include <wifinetstack.h>
#include <idmanage/pbuf.h>
#include <security/drv_security.h>
#include <phy/drv_phy.h>
#ifdef TCPIPSTACK_EN
#include <netstack.h>
//#include <netstack_def.h>
#endif
#include <toolbox.h>

#include "lowpower.h"
#include "drv_gpio.h"
#include <phy/rf_api.h>
#include <logger.h>
#include "ble_api.h"

extern void ble_hci_rx_ssv(uint8_t *data, uint16_t len);
extern void app_mesh_ble_init();
extern void app_ble_init(void);
extern void Cli_Task();
void ssvradio_init_task(void *pdata)
{
    RADIO_INIT(DEFAULT_COUNTRY_CODE, DEFAULT_RATE_MASK_VALUE,TRUE);
#ifdef TCPIPSTACK_EN
    netstack_init(NULL);
#endif

#ifdef BLE_EN
    if (get_ble_dtm_enable() == EN_BLE_DTM) {
        ble_enable(DTM_MODE);

    }
    else if (get_ble_dtm_enable() == EN_BLE_HOST) {
        ble_register_hcievent_callback(ble_hci_rx_ssv);
        ble_enable(HCI_RAM_MODE);
        #if MESH_BLE_EN
        app_mesh_ble_init();
        #else
        #if (BLE_GATTS_API_TEST || BLE_GATTC_API_TEST)
        app_ble_init();
        #endif
        #endif
    }
    else
        ble_enable(HCI_UART_MODE);
#endif//BLE_EN end
    OS_TaskDelete(NULL);
}

void APP_Init(void)
{
    bsp_init();

    rf_table_init();

    OS_TaskCreate(Cli_Task, "cli", 2048, NULL, OS_TASK_LOW_PRIO, NULL);
    OS_TaskCreate(ssvradio_init_task, "ssvradio_init", 512, NULL, 4, NULL);

    printf("[%s %s][%s][%d] fota option: %d\n", __DATE__, __TIME__, __func__, __LINE__, (int)&__fota_option);

    OS_StartScheduler();
}

