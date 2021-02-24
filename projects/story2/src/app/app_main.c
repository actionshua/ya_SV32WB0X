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

#include <fsal.h>
#include <sysconf_api.h>

void Cli_Task( void *args );

/**********************************************************/
void ssvradio_init_task(void *pdata)
{
    RADIO_INIT(DEFAULT_COUNTRY_CODE, DEFAULT_RATE_MASK_VALUE,FALSE); 
#ifdef TCPIPSTACK_EN
    netstack_init(NULL);
#endif
    OS_TaskDelete(NULL);
}


extern void drv_uart_init(void);
void APP_Init(void)
{
    bsp_init();

    rf_table_init();

#if (DEMO_TYPE == 1)
    extern void player_gpio_init();
    extern void player_and_recorder(void *param);
    player_gpio_init();
    OS_TaskCreate(player_and_recorder, "player_and_recorder", 1024, NULL, OS_TASK_MIDDLE_PRIO, NULL);
#elif ((DEMO_TYPE == 2) || (DEMO_TYPE == 3))
    extern void echo_player(void *param);
    extern void echo_player_evthandler(SSV_FS_EVENT evt);
    FS_register_evthandler(echo_player_evthandler);
    OS_TaskCreate(echo_player, "echo_player", 512, NULL, OS_TASK_MIDDLE_PRIO, NULL);
#endif
    OS_TaskCreate(Cli_Task, "cli", 512, NULL, OS_TASK_LOW_PRIO, NULL);

    OS_TaskCreate(ssvradio_init_task, "ssvradio_init", 512, NULL, OS_TASK_MIDDLE_PRIO, NULL);

    init_global_conf();
    //this task run in low priority

    printf("[%s][%d] string: %d\n", __func__, __LINE__, CODEC_TYPE);

    OS_StartScheduler();
}

//void vAssertCalled( const char *func, int line )
//{
//    while(1);
//}

