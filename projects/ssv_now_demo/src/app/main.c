#include <wifinetstack.h>
#include <idmanage/pbuf.h>
#include <security/drv_security.h>
#include <wifi_api.h>
#include <netstack.h>

#include <bsp.h>
#include <toolbox.h>
#include <drv_gpio.h>
#include <phy/drv_phy.h>

#include <wifi_api.h>
#include <lowpower.h>
#include <powersave/powersave.h>

#include "ssv_now.h"
#include "logger.h"
#include "ieee80211_mac.h"


#define SSV_NOW_CTRL 1
#define SSV_NOW_SLAVE 2

//SSV_NOW_CTRL mean build Control Role Firmware, you can change to SSV_NOW_SLAVE to Build Slave Role Firmware
#define SSV_NOW_ROLE SSV_NOW_SLAVE

#define LOW_POWER_ENABLE  //ssv-now control run in low power mode, you can disable it by mark this line

#define CTRL_WAKEUP_GPIO 22  //Set gpio 7 to wakeup mcu from lowpower mode       
#define SLAVE_LED_GPIO 21


OsEvent g_wakeup_event = NULL;
u8 light_flag = 0;


//function run in sram
void do_dormant(int sec) ATTRIBUTE_SECTION_FAST;
void do_wakeup() ATTRIBUTE_SECTION_FAST;
//void irq_wakeup_gpio(uint32_t irq_num) ATTRIBUTE_SECTION_FAST;

void do_dormant(int sec)
{
    struct timeval tv;
    tv.tv_sec = sec;  //max is 134217
    tv.tv_usec = 0;
    DUT_wifi_start(DUT_NONE);
    OS_EnterCritical();
    on3_shutdown();
    sys_dormant(&tv);
    OS_ExitCritical();
}          

void do_wakeup()
{
    OS_EnterCritical();
    on3_activate();
    OS_ExitCritical();
}  
#if 0
void irq_wakeup_gpio(uint32_t irq_num) 
{
    //OS_EnterCritical();
    drv_gpio_intc_clear(irq_num); 
#ifdef LOW_POWER_ENABLE    
    do_wakeup();
#endif
    OS_EventSet(g_wakeup_event);   
    //OS_ExitCritical();
}
#endif

uint8_t data_buf[1512] = {0};
void demo_ssv_now_send_task(void *pdata)
{
    u8 count=0;
    while(1) 
    {
        //printf("wait for event\n\n");             
        //if ( OS_EventWait(g_wakeup_event, portMAX_DELAY) == OS_SUCCESS ) 
        {       
     
            uint8_t peer_addr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff };   //broadcast
            //uint8_t peer_addr[6] = {0x44, 0x57, 0x18, 0x3f, 0x49, 0x00 }; //unicast
            //uint8_t data_buf[] = {'H', 'E', 'L', 'L', 'O', ' ', 'S', 'S', 'V', '-', 'N', 'O', 'W', '!'};
            uint32_t data_len = sizeof(data_buf);

            data_buf[0]=count++;
            data_buf[252]=count++;
            data_buf[252*2]=count++;
            data_buf[252*3]=count++;
            data_buf[252*4]=count++;
            data_buf[252*5]=count++;
            ssv_now_send_mgmt_payload(peer_addr, data_buf, data_len);

            //check wakeup gpio status in case repeat trggle gpio
           int retry_count = 90;
           while( drv_gpio_get_logic(CTRL_WAKEUP_GPIO) == 1 )
           {
                OS_MsDelay(10);
                retry_count--;
                
                if(retry_count == 0)
                    break;
            }

            do_dormant(3600);   //sleep 3600 sec then wake up
            
            OS_MsDelay(1);
            do_wakeup();
			OS_MsDelay(1);
            
        }
    }

    OS_TaskDelete(NULL);
}

void custom_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    if(data_len > 0)
    {
        printf("receive %d bytes from %x:%x:%x:%x:%x:%x ... %d,%d,%d,%d,%d,%d \n",
                                                            data_len, 
                                                            mac_addr[0], 
                                                            mac_addr[1], 
                                                            mac_addr[2], 
                                                            mac_addr[3], 
                                                            mac_addr[4], 
                                                            mac_addr[5],
                                                            data[5],
                                                            data[257+5],
                                                            data[257*2+5],
                                                            data[257*3+5],
                                                            data[257*4+5],
                                                            data[257*5+5]);

        //light or dark the led  
        if(light_flag == 1)
        {
                    light_flag = 0;
        }
        else
        {
                    light_flag = 1;
        }
            
        drv_gpio_set_logic(SLAVE_LED_GPIO, light_flag);
    }
}

void custom_send_cb(const uint8_t *mac_addr, ssv_now_send_status_t status)
{
    printf("send status %d to %x:%x:%x:%x:%x:%x \n", status, mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
}

int demo_ssv_now_init()
{
    printf("demo_ssv_now_init\n");

    if( ssv_now_init() != 0)
    {
        printf("ssv now initialize fails\n");
        return -1;
    } 

#if (SSV_NOW_ROLE == SSV_NOW_SLAVE)

    /*SSV-Now flow for Control*/
    printf("SSV NOW Set Role to Slave\n");
    printf("SLAVE_LED_GPIO use gpio %d\n", SLAVE_LED_GPIO);
    
    ssv_now_set_role(SSV_NOW_ROLE_SLAVE);
    
    ssv_now_register_recv_cb(custom_recv_cb);

    //uint8_t filter_addr[6] = {0x44, 0x57, 0x18, 0x3f, 0x49, 0x00 };
    //ssv_now_set_recv_filter_mac(filter_addr);   //Slave only receive the frame sending by control with mac 44:57:18:3f:49:00
    ssv_now_set_recv_filter_mac(NULL); //Slave will receive all frame
    
    //for demo led dark or light, set SLAVE_LEG_GPIO is output 
    drv_gpio_set_mode(SLAVE_LED_GPIO, 0);
    drv_gpio_set_dir(SLAVE_LED_GPIO, 1);

#else    
    /*SSV-Now flow for Control*/
    printf("SSV NOW Set Role to CTRL\n");
    printf("CTRL_WAKEUP_GPIO use gpio %d\n", CTRL_WAKEUP_GPIO);
    
    ssv_now_set_role(SSV_NOW_ROLE_CTRL);
    ssv_now_register_send_cb(custom_send_cb);

    drv_gpio_set_mode(CTRL_WAKEUP_GPIO, PIN_MODE_GPIO);
    drv_gpio_set_dir(CTRL_WAKEUP_GPIO, GPIO_DIR_IN);
    drv_gpio_set_pull(CTRL_WAKEUP_GPIO, GPIO_PULL_DOWN);

    //Attach GPIO ISR
    ///drv_gpio_register_isr(CTRL_WAKEUP_GPIO, irq_wakeup_gpio);
    
//#ifdef LOW_POWER_ENABLE
    drv_gpio_set_wakeup_enable(CTRL_WAKEUP_GPIO);
    drv_gpio_intc_trigger_mode(CTRL_WAKEUP_GPIO,GPIO_INTC_RISING_EDGE);
//#endif
    drv_gpio_set_wakeup_detect(GPIO_INTC_RISING_EDGE);

    
    //Create  Task and event
    /*
    OS_EventCreate(&g_wakeup_event);
    if( g_wakeup_event == NULL )
    {
        printf("Create Event fail\n");
        return -1;
    }
    */
    printf("OS will enter Dormant mode\n");
    //printf("create demo_ssv_now_send_task \n");
    OS_TaskCreate(demo_ssv_now_send_task, "demo_ssv_now_send_task", 1024, NULL, OS_TASK_MIDDLE_PRIO, NULL);
 
 #endif


    return 0;
    
}

void Cli_Task( void *args );
void ssvradio_init_task(void *pdata)
{

    RADIO_INIT(DEFAULT_COUNTRY_CODE, DEFAULT_RATE_MASK_VALUE,FALSE); 
 
#ifdef TCPIPSTACK_EN
    netstack_init(NULL);
#endif
    OS_TaskDelete(NULL);
}

void demo_ssv_now_init_task(void *pdata)
{
	rf_set_ch(11, 0, 1);
    demo_ssv_now_init(); 
    OS_TaskDelete(NULL);
}

void APP_Init(void)
{
    bsp_init();    
    rf_table_init();

    OS_TaskCreate(ssvradio_init_task, "ssvradio_init", 1024, NULL, OS_TASK_MIDDLE_PRIO, NULL);
    OS_TaskCreate(Cli_Task, "cli", 512, NULL, OS_TASK_LOW_PRIO, NULL);    

    //ssv-now entry point
    //demo_ssv_now_init(); //ssv now must wait ssvradio task run finish, 
    OS_TaskCreate(demo_ssv_now_init_task, "ssv_now_task", 1024, NULL, OS_TASK_LOW_PRIO, NULL);
    
    OS_StartScheduler();
}
