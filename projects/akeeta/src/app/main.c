#include <sys/backtrace.h>
#include <sys/xip.h>
#include <osal.h>
#include <wifinetstack.h>
#include <idmanage/pbuf.h>
#include <security/drv_security.h>
#include <phy/drv_phy.h>
#include <soc_defs.h>
#include <ieee80211_mgmt.h>
#include <ieee80211_mac.h>
#include <sta_func.h>
#include <wifi_api.h>
#include <netstack.h>
#include <netstack_def.h>
#include <uart/drv_uart.h>
#include <uart/drv_comport.h>
//#include <phy/rf_api.h>

#include <sysconf_api.h>
#include <toolbox.h>
#include <bsp.h>
#ifdef BLE_EN
#include "ble_api.h"
#endif
extern void ble_hci_rx_ssv(uint8_t *data, uint16_t len);

void Cli_Task( void *args );

void ssvradio_init_task(void *pdata)
{
#ifdef BLE_EN
    RADIO_INIT(DEFAULT_COUNTRY_CODE, DEFAULT_RATE_MASK_VALUE,TRUE); 
#else
    RADIO_INIT(DEFAULT_COUNTRY_CODE, DEFAULT_RATE_MASK_VALUE,FALSE); 
#endif

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

	ya_example();

    OS_TaskDelete(NULL);
}

void APP_Init(void)
{
    bsp_init();

    rf_table_init();

    OS_TaskCreate(Cli_Task, "cli", 1024, NULL, OS_TASK_LOW_PRIO, NULL);

    OS_TaskCreate(ssvradio_init_task, "ssvradio_init", 512, NULL, OS_TASK_MIDDLE_PRIO, NULL);

    init_global_conf();
	
    printf("[%s %s][%s][%d] fota option: %d\n", __DATE__, __TIME__, __func__, __LINE__, (int)&__fota_option);
    OS_StartScheduler();
}

