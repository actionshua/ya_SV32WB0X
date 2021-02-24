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

#include <lowpower.h>
#include "drv_gpio.h"
#include <phy/rf_api.h>
#include <logger.h>
#include "ble_api.h"

#if MESH_BLE_EN
extern void ble_hci_rx_ssv(uint8_t *data, uint16_t len);
extern void app_mesh_ble_init();
#endif

extern void Cli_Task();

#if 0
#if(FRONTEND == 6020)
void iq_board_init(void *pdata)
{
    ///
    //var RG_EN_RX_PADSW = 1<<27;
    //var RG_EN_RX_PADSW_MASK = 0xf7ffffff;
    //reg_read = DIList.get(0).deviceRead(0xccb0a404);  // 
    //reg_write = (reg_read&RG_EN_RX_PADSW_MASK) | RG_EN_RX_PADSW;
    //println('Turismo register 0xccb0a404 write value is '+reg_write.toString(16));
    //DIList.get(0).deviceWrite(0xccb0a404,reg_write);   // 
    //
    //var RG_EN_TXLPF_IN_PADSW = 1<<29;
    //var RG_EN_TXLPF_IN_PADSW_MASK = 0xdfffffff;
    //reg_read = DIList.get(0).deviceRead(0xccb0a404);  // 
    //reg_write = (reg_read&RG_EN_TXLPF_IN_PADSW_MASK) | RG_EN_TXLPF_IN_PADSW;
    //println('Turismo register 0xccb0a404 write value is '+reg_write.toString(16));
    //DIList.get(0).deviceWrite(0xccb0a404,reg_write);   // 
    //
    //var RG_FPGA_CLK_REF_40M_EN = 1<<0;
    //var RG_FPGA_CLK_REF_40M_EN_MASK = 0xfffffffe;
    //reg_read = DIList.get(0).deviceRead(0xccb0b07c);  // 
    //reg_write = (reg_read&RG_FPGA_CLK_REF_40M_EN_MASK) | RG_FPGA_CLK_REF_40M_EN;
    //println('Turismo register 0xccb0b07c write value is '+reg_write.toString(16));
    //DIList.get(0).deviceWrite(0xccb0b07c,reg_write);   // 
    //
    //var RG_MODUL_SCHEME_BY_HS5W = 1<<14;
    //var RG_RX_GAIN_BY_HS5W      = 1<<13;
    //var RG_TX_GAIN_BY_HS5W      = 1<<12;
    //var RG_HS_5WIRE_MANUAL      = 1<<2;
    //var RG_MODE_BY_HS5W         = 1<<1;
    //var RG_CTRL_BY_HS5W_MASK = 0xffff8ff9;
    //reg_read = DIList.get(0).deviceRead(0xccb0a88c);  // 
    //reg_write = (reg_read&RG_CTRL_BY_HS5W_MASK) | RG_MODUL_SCHEME_BY_HS5W|RG_RX_GAIN_BY_HS5W|RG_TX_GAIN_BY_HS5W|RG_HS_5WIRE_MANUAL|RG_MODE_BY_HS5W;
    //println('Turismo register 0xccb0a88c write value is '+reg_write.toString(16));
    //DIList.get(0).deviceWrite(0xccb0a88c,reg_write);   // 
    //
    //var RG_RX_AGC_MANUAL = 1<<15;
    //var RG_RX_AGC        = 1<<14;
    //var RG_RX_AGC_MASK   = 0xffff3fff;
    //reg_read = DIList.get(0).deviceRead(0xccb0a808);  // 
    //reg_write = (reg_read&RG_RX_AGC_MASK) | RG_RX_AGC_MANUAL|RG_RX_AGC;
    //println('Turismo register 0xccb0a808 write value is '+reg_write.toString(16));
    //DIList.get(0).deviceWrite(0xccb0a808,reg_write);   // 
    //
    //DIList.get(0).deviceWrite(0xc0000518, 0x10002000);// add driving
    //DIList.get(0).deviceWrite(0xc0000560, 0x00000002);
    //DIList.get(0).deviceWrite(0xc0000500, 0x1107A000);
    //println('set transceiver mode done...');
    uint32_t RG_EN_RX_PADSW = 1<<27;
    uint32_t RG_EN_RX_PADSW_MASK = 0xf7ffffff;
    uint32_t reg_read = REG32(0xccb0a404);
    REG32(0xccb0a404) = (reg_read&RG_EN_RX_PADSW_MASK) | RG_EN_RX_PADSW;

    uint32_t RG_EN_TXLPF_IN_PADSW = 1<<29;
    uint32_t RG_EN_TXLPF_IN_PADSW_MASK = 0xdfffffff;
    reg_read = REG32(0xccb0a404);
    REG32(0xccb0a404) = (reg_read&RG_EN_TXLPF_IN_PADSW_MASK) | RG_EN_TXLPF_IN_PADSW;


    uint32_t RG_FPGA_CLK_REF_40M_EN = 1<<0;
    uint32_t RG_FPGA_CLK_REF_40M_EN_MASK = 0xfffffffe;
    reg_read = REG32(0xccb0b07c);
    REG32(0xccb0b07c) = (reg_read&RG_FPGA_CLK_REF_40M_EN_MASK) | RG_FPGA_CLK_REF_40M_EN;




    uint32_t RG_MODUL_SCHEME_BY_HS5W = 1<<14;
    uint32_t RG_RX_GAIN_BY_HS5W      = 1<<13;
    uint32_t RG_TX_GAIN_BY_HS5W      = 1<<12;
    uint32_t RG_HS_5WIRE_MANUAL      = 1<<2;
    uint32_t RG_MODE_BY_HS5W         = 1<<1;
    uint32_t RG_CTRL_BY_HS5W_MASK = 0xffff8ff9;
    reg_read = REG32(0xccb0a88c);
    REG32(0xccb0a88c) = (reg_read&RG_CTRL_BY_HS5W_MASK) | RG_MODUL_SCHEME_BY_HS5W|RG_RX_GAIN_BY_HS5W|RG_TX_GAIN_BY_HS5W|RG_HS_5WIRE_MANUAL|RG_MODE_BY_HS5W;

    uint32_t RG_RX_AGC_MANUAL = 1<<15;
    uint32_t RG_RX_AGC        = 1<<14;
    uint32_t RG_RX_AGC_MASK   = 0xffff3fff;
    reg_read = REG32(0xccb0a808);
    REG32(0xccb0a808) = (reg_read&RG_RX_AGC_MASK) | RG_RX_AGC_MANUAL|RG_RX_AGC;

#define M_FLASH_PIN     (0x1f80)

    REG32(0xc0000518) = 0x10002000;
    REG32(0xc0000560) = 0x00000002;
    REG32(0xc0000500) = 0x1107A000 | M_FLASH_PIN;

    while(1) {
        __nds32__standby_no_wake_grant();
    }

    OS_TaskDelete(NULL);
}
#endif
#endif
extern int host_cmd_proc_start();
void ssvradio_init_task(void *pdata)
{
    wifi_allow_sdio_spi_reset(false);
    sys_hwif_power_on();
    RADIO_INIT(DEFAULT_COUNTRY_CODE, DEFAULT_RATE_MASK_VALUE,FALSE); 
#ifdef TCPIPSTACK_EN
    netstack_init(NULL);
#endif

#ifdef BLE_EN
#if MESH_BLE_EN
    ble_register_hcievent_callback(ble_hci_rx_ssv);
    ble_enable(HCI_RAM_MODE);
    app_mesh_ble_init();
#else
    ble_enable(HCI_UART_MODE);
#endif//MESH_BLE_EN end
#endif//BLE_EN end
//#if(FRONTEND == 6020)
//    OS_TaskCreate(iq_board_init, "iqboard", 512, NULL, 4, NULL);
//#endif
    DUT_wifi_start(DUT_TRANSPARENT);
    host_cmd_proc_start();

    OS_TaskDelete(NULL);
}

extern unsigned int __fota_option;

void alive_test(void *param) {
    while(1) {
        OS_MsDelay(500);
        printf("this is alive %d\n", OS_GetUsSysTick());
    }
    OS_TaskDelete(NULL);
}

void APP_Init(void)
{
    bsp_init();

    rf_table_init();

    OS_TaskCreate(Cli_Task, "cli", 512, NULL, OS_TASK_LOW_PRIO, NULL);
    OS_TaskCreate(ssvradio_init_task, "ssvradio_init", 512, NULL, 4, NULL);

    printf("[%s %s][%s][%d] fota option: %d\n", __DATE__, __TIME__, __func__, __LINE__, (int)&__fota_option);

    OS_StartScheduler();
}

