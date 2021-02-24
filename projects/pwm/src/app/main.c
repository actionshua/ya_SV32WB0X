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
#include <bsp.h>
#include <toolbox.h>
void Cli_Task( void *args );

void ssvradio_init_task(void *pdata)
{
    RADIO_INIT(DEFAULT_COUNTRY_CODE, DEFAULT_RATE_MASK_VALUE,FALSE); 
#ifdef TCPIPSTACK_EN
    netstack_init(NULL);
#endif
    OS_TaskDelete(NULL);
}

/**********************************************************/
void APP_Init(void)
{
    bsp_init();

    rf_table_init();

    OS_TaskCreate(ssvradio_init_task, "ssvradio_init", 512, NULL, OS_TASK_MIDDLE_PRIO, NULL);
    OS_TaskCreate(Cli_Task, "cli", 1024, NULL, OS_TASK_LOW_PRIO, NULL);

    OS_StartScheduler();
}

