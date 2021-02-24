//#include <stdio.h>
#include <string.h>
//#include <stdint.h>
//#include <stdlib.h>
//#include "ssv_lib.h"
//#include "attrs.h"

#include "atcmd_general.h"

#include "sw_version.h"
#include <wdt/drv_wdt.h>
#include <uart/drv_uart.h>
#include <wifi_api.h>
#include <bsp/soc/efuseapi/efuse_api.h>
#if defined(SUPPORT_PARTITION_CFG_TABLE)
#include <mac_cfg.h>
#endif
#if defined(SUPPORT_FFS)
#include <fsal.h>
#endif
#include <lowpower.h>
#include <powersave/powersave.h>
#include <drv_gpio.h>
#include <bsp.h>
#include <uart/drv_comport.h>
#include <pinmux/drv_pinmux.h>
#include "sys/system_api.h"
#include "ilog.h"
static int bEfuseEnableWrite = 0;

static bool raw_dump_ex(char *data, s32 len, bool with_addr, u8 addr_radix, char line_cols, u8 radix)
{
    int i;

	// check input parameters
	if ((addr_radix != 10) && (addr_radix != 16))
	{
		ATCMD_LOG_I("%s(): invalid value 'addr_radix' = %d\n\r", __FUNCTION__, addr_radix);
		return false;
	}
	if ((line_cols != 8) && (line_cols != 10) && (line_cols != 16) && (line_cols != -1))
	{
		ATCMD_LOG_I("%s(): invalid value 'line_cols' = %d\n\r", __FUNCTION__, line_cols);
		return false;
	}
	if ((radix != 10) && (radix != 16))
	{
		ATCMD_LOG_I("%s(): invalid value 'radix' = %d\n\r", __FUNCTION__, radix);
		return false;
	}

	if (len == 0)	return true;

	// if ONLY have one line
	if (line_cols == -1)
	{
		//LOG_TAG_SUPPRESS_ON();
		// only print addr heading at one time
		if ((with_addr == true))
		{
			if      (addr_radix == 10)	ATCMD_LOG_I("%08d: ", 0);
			else if (addr_radix == 16)	ATCMD_LOG_I("0x%08x: ", 0);
		}

		for (i=0; i<len; i++)
		{
			// print data
			if	    (radix == 10)	ATCMD_LOG_I("%4d ",  (u8)data[i]);
			else if (radix == 16)	ATCMD_LOG_I("%02x ", (u8)data[i]);
		}
		ATCMD_LOG_I("\n\r");
		//LOG_TAG_SUPPRESS_OFF();
		return true;
	}

	// normal case
	//LOG_TAG_SUPPRESS_ON();
    for (i=0; i<len; i++)
	{
		// print addr heading
		if ((with_addr == true) && (i % line_cols) == 0)
		{
			if      (addr_radix == 10)	ATCMD_LOG_I("%08d: ", i);
			else if (addr_radix == 16)	ATCMD_LOG_I("0x%08x: ", i);
		}
		// print data
		if	    (radix == 10)	ATCMD_LOG_I("%4d ",  (u8)data[i]);
		else if (radix == 16)	ATCMD_LOG_I("%02x ", (u8)data[i]);
		// print newline
        if (((i+1) % line_cols) == 0)
            ATCMD_LOG_I("\n\r");
    }
    ATCMD_LOG_I("\n\r");
	//LOG_TAG_SUPPRESS_OFF();
	return true;
}
static void raw_dump(char *data, s32 len)
{
	raw_dump_ex(data, len, true, 10, 10, 16);
	return;
}

//AT Command General Function
int At_Reboot (stParam *param)
{
    int sec = 0;
    if(param->argc >=1 )
        sec = atoi(param->argv[0]);

    ATCMD_LOG_I("\r\n");
    if( sec == 0 )
    {
        ATCMD_LOG_I("System will reboot after %d seconds\n", sec);
        drv_wdt_init();
        drv_wdt_enable(SYS_WDT, 100);
    }
    else
    {
        ATCMD_LOG_I("System will reboot after %d seconds\n", sec);
        drv_wdt_init();
        drv_wdt_enable(SYS_WDT, sec*1000);
    }
    return ERROR_SUCCESS;
}
int At_GetVersion (stParam *param)
{
    ATCMD_LOG_I("\r\n");
    ATCMD_LOG_I(ATRSP_VERSION, sw_version);
#if defined(ROM_MODE)
    ATCMD_LOG_I(ATRSP_VERSION, version);
#endif
    
    return ERROR_SUCCESS;
}
int At_GetManufactureInfo (stParam *param)
{
    ATCMD_LOG_I("\r\n");
    ATCMD_LOG_I(ATRSP_MANUFACTURE, "iComm Company");
    return ERROR_SUCCESS;
}
int At_RadioWriteMAC1(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    if( strlen(param->argv[0]) != 17 )
    {
        ATCMD_LOG_I("EX:%s=00:23:45:67:89:AB\n", ATCMD_RADIO_WRITE_MAC1);
        return ERROR_INVALID_PARAMETER;
    }
    
    void *cfg_handle = wifi_cfg_init();
    if (cfg_handle == NULL) {
        return ERROR_MEMORY_FAILED;
    }
   
    wifi_cfg_replace_mem_addr1(cfg_handle, param->argv[0]);
    wifi_cfg_write_cfg(cfg_handle);
    wifi_cfg_deinit(cfg_handle);

    return ret;
}
int At_RadioReadMAC1(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    void *cfg_handle = wifi_cfg_init();
    char mac_addr[6] = {0};
    wifi_cfg_get_addr1(cfg_handle, mac_addr);
    wifi_cfg_deinit(cfg_handle);
    
    ATCMD_LOG_I("%s=%02X:%02X:%02X:%02X:%02X:%02X\n", ATCMD_RADIO_READ_MAC1, (uint8_t)mac_addr[0], (uint8_t)mac_addr[1], (uint8_t)mac_addr[2], (uint8_t)mac_addr[3], (uint8_t)mac_addr[4], (uint8_t)mac_addr[5]);
    return ret;
}
int At_RadioWriteMAC2(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    if( strlen(param->argv[0]) != 17 )
    {
        ATCMD_LOG_I("EX:%s=00:23:45:67:89:AB\n", ATCMD_RADIO_WRITE_MAC2);
        return ERROR_INVALID_PARAMETER;
    }
    
    void *cfg_handle = wifi_cfg_init();
    if (cfg_handle == NULL) {
        return ERROR_MEMORY_FAILED;
    }
   
    wifi_cfg_replace_mem_addr2(cfg_handle, param->argv[0]);
    wifi_cfg_write_cfg(cfg_handle);
    wifi_cfg_deinit(cfg_handle);

    return ret;
}
int At_RadioReadMAC2(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    void *cfg_handle = wifi_cfg_init();
    char mac_addr[6] = {0};
    wifi_cfg_get_addr2(cfg_handle, mac_addr);
    wifi_cfg_deinit(cfg_handle);
    
    ATCMD_LOG_I("%s=%02X:%02X:%02X:%02X:%02X:%02X\n", ATCMD_RADIO_READ_MAC2, (uint8_t)mac_addr[0], (uint8_t)mac_addr[1], (uint8_t)mac_addr[2], (uint8_t)mac_addr[3], (uint8_t)mac_addr[4], (uint8_t)mac_addr[5]);
    return ret; 
}
#if BLE_EN
int At_RadioWriteMAC3(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;

    if( strlen(param->argv[0]) != 17 )
    {
        ATCMD_LOG_I("EX:%s=10:32:45:67:98:BA\n", ATCMD_RADIO_WRITE_MAC3);
        return ERROR_INVALID_PARAMETER;
    }
    
    void *cfg_handle = wifi_cfg_init();
    if (cfg_handle == NULL) {
        return ERROR_MEMORY_FAILED;
    }
   
    wifi_cfg_replace_mem_addr2(cfg_handle, param->argv[0]);//change to wifi_cfg_replace_mem_addr3 later
    wifi_cfg_write_cfg(cfg_handle);
    wifi_cfg_deinit(cfg_handle);

    return ret;
}

int At_RadioReadMAC3(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    void *cfg_handle = wifi_cfg_init();
    char mac_addr[6] = {0};
    wifi_cfg_get_addr2(cfg_handle, mac_addr);//change to wifi_cfg_get_addr3 later
    wifi_cfg_deinit(cfg_handle);
    
    ATCMD_LOG_I("%s=%02X:%02X:%02X:%02X:%02X:%02X\n", ATCMD_RADIO_READ_MAC3, (uint8_t)mac_addr[0], (uint8_t)mac_addr[1], (uint8_t)mac_addr[2], (uint8_t)mac_addr[3], (uint8_t)mac_addr[4], (uint8_t)mac_addr[5]);
    return ret; 
}
#endif

#if 0
int At_EfuseEnableWrite(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;

    bEfuseEnableWrite = 1;
    ATCMD_LOG_I("Now you can write efuse\n");
    
    return ret; 
}
int At_EfuseWriteMAC(stParam *param)
{
    int ret = ERROR_SUCCESS;
    int i = 0;
    const char delimiters[] = ":";
    char *pMac = 0, *ptmp;
    unsigned long int toul_val;
    uint8_t efuse_mac[6] = {0};

    ATCMD_LOG_I("\n");
    
    if(param->argc <1)
        return ERROR_INVALID_PARAMETER;
    
    if( strlen(param->argv[0]) != 17 )
    {
        ATCMD_LOG_I("EX:%s=00:23:45:67:89:AB\n", ATCMD_EFUSE_WRITE_MAC);
        return ERROR_INVALID_PARAMETER;
    }

    pMac = param->argv[0];

    if(pMac != NULL) 
    {
        ptmp = strtok (pMac, delimiters);
        for(i=0; i<=5; i++) 
        {
            toul_val =  strtoul(ptmp, NULL, 16);
            efuse_mac[i] = toul_val;
            ptmp = strtok (NULL, delimiters);
        }
    }

    ATCMD_LOG_I("Parse mac -> %02X:%02X:%02X:%02X:%02X:%02X\n", efuse_mac[0], efuse_mac[1], efuse_mac[2], efuse_mac[3], efuse_mac[4], efuse_mac[5]);

    if(bEfuseEnableWrite == 0)
    {
        ATCMD_LOG_I("Please run %s first\n", ATCMD_EFUSE_ENABLE_WRITE);
        return ERROR_NOT_IMPLEMENT;
    }
    bEfuseEnableWrite = 0;

    ret = efuse_write_mac(efuse_mac);

    return ret;
}
#endif
int At_EfuseReadMAC(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    uint8_t efuse_mac[6] = {0};

    ret = efuse_read_mac(efuse_mac);
    
    if(ret == 0)
    {
        ATCMD_LOG_I("%s=%02X:%02X:%02X:%02X:%02X:%02X\n", ATCMD_EFUSE_READ_MAC, efuse_mac[0], efuse_mac[1], efuse_mac[2], efuse_mac[3], efuse_mac[4], efuse_mac[5]);
     
        //efuse_read_mac_increase(efuse_mac);
        //ATCMD_LOG_I("MAC INCREASE=%02X:%02X:%02X:%02X:%02X:%02X\n", efuse_mac[0], efuse_mac[1], efuse_mac[2], efuse_mac[3], efuse_mac[4], efuse_mac[5]);
    }
    else
    {
        ATCMD_LOG_I("No MAC in Efuse\n");
    }
    
    return ret; 
}  
#if 0
int At_EfuseDump(stParam *param)
{
    ATCMD_LOG_I("\n");
    int ret = ERROR_SUCCESS;
    int len = 0;
    uint8_t efuse_mac[6] = {0};
    uint16_t usb_vid = 0;
    uint16_t usb_pid = 0;
    uint8_t power_tx1 = 0;
    uint8_t power_tx2 = 0;
    uint8_t xtal = 0;

    len = efuse_dump_data();

    ATCMD_LOG_I("efuse free bits = %d\n", efuse_get_free_bits());
    
    if( efuse_read_mac(efuse_mac) == 0 )
    {
        ATCMD_LOG_I("MAC = %02x:%02x:%02x:%02x:%02x:%02x\n", efuse_mac[0], efuse_mac[1], efuse_mac[2], efuse_mac[3], efuse_mac[4], efuse_mac[5]);
    }
    else
    {
        ATCMD_LOG_I("NO MAC\n");
    }

    if( efuse_read_usb_vid(&usb_vid) == 0 )
    {
        ATCMD_LOG_I("VID = 0x%x\n", usb_vid);
    }
    else
    {
        ATCMD_LOG_I("NO VID\n");
    }

    if( efuse_read_usb_pid(&usb_pid) == 0 )
    {
        ATCMD_LOG_I("PID = 0x%x\n", usb_pid);
    }
    else
    {
        ATCMD_LOG_I("NO PID\n");
    }
    
    if( efuse_read_tx_power1(&power_tx1) == 0 )
    {
        ATCMD_LOG_I("TX Power1 = 0x%x\n", power_tx1);
    }
    else
    {
        ATCMD_LOG_I("NO TX Power1\n");
    }
    
    if( efuse_read_tx_power2(&power_tx2) == 0 )
    {
        ATCMD_LOG_I("TX Power1 = 0x%x\n", power_tx2);
    }
    else
    {
        ATCMD_LOG_I("NO TX Power2\n");
    }

     if( efuse_read_xtal(&xtal) == 0 )
    {
        ATCMD_LOG_I("XTAL = 0x%x\n", xtal);
    }
    else
    {
        ATCMD_LOG_I("NO XTAL\n");
    }   
   
    return ret; 
}
#endif
int At_UartConfig (stParam *param)
{
    int ret;

    uint8_t uart_num = 0;
    uint32_t nBaudrate = 115200;
    uint8_t nDatabits = 3;
    uint8_t nStopbits = 0;
    uint8_t nParity = 0;
    
    ATCMD_LOG_I("\r\n");
    
    if( param->argc < 2 )
    {
        ATCMD_LOG_I("\n");
        ATCMD_LOG_I("Usage   :AT+UART_CONFIG=<uart_num>,<baudrate>,<databits>,<stopbits>,<parity>\n");
        ATCMD_LOG_I("<uart_num> : 0:debug UART; 1:data UART\n");
        ATCMD_LOG_I("<baudrate> : uart baud rate\n");
        ATCMD_LOG_I("<databits> : 0:5 bits; 1:6 bits; 2:7 bits; 3:8 bits\n");
        ATCMD_LOG_I("<stopbits> : 0:one bit; 1:two bits\n");
        ATCMD_LOG_I("<parity> : 0:none; 1:odd; 3:even\n");
        
        return ERROR_INVALID_PARAMETER;
    }
    
    if(param->argc >=1 )
        uart_num = atoi(param->argv[0]);   
    if(param->argc >=2 )
        nBaudrate = atoi(param->argv[1]);
    if(param->argc >=3 )
        nDatabits = atoi(param->argv[2]);
    if(param->argc >=4 )
        nStopbits = atoi(param->argv[3]);
    if(param->argc >=5 )
        nParity = atoi(param->argv[4]);    

    if( uart_num == 1 )
        drv_pinmux_manual_function_select_enable(SEL_UART1);

    drv_comport_init(uart_num);
    ret = drv_comport_set_format(nBaudrate, nDatabits, nStopbits, nParity);
        
    return ret;
}

int At_UserRaw(stParam *param)
{

    if(param->argc < 4) {
        ATCMD_LOG_E("ex: raw=offset,data,backup_en,dump_len\n");
        return -1;
    }
    int i = 0, ret = 0;
    int offset = atoi(param->argv[0]);
    char *save_data = param->argv[1];
    int backup_en = atoi(param->argv[2]);
    int load_data_size = atoi(param->argv[3]);
    int save_data_size = strlen(param->argv[1]);
    char *load_data = malloc(load_data_size);
    if(load_data == NULL) {
        ATCMD_LOG_E("malloc fail\n");
        return -1;
    }
    ATCMD_LOG_I("\nbootloader version: %s\n", system_get_boot_version());
    ATCMD_LOG_I("flash size: %d KB\n", system_get_flash_size());
    ATCMD_LOG_I("main size: %d KB\n", system_get_main_size());
    ATCMD_LOG_I("fota method: %d\n", system_get_fota_method());
    ATCMD_LOG_I("man address: %x\n", system_get_userbin_addr());

    ATCMD_LOG_I("save len: %d offset: %d backup_en: %d dump len: %d\n", save_data_size, offset, backup_en, load_data_size);
    ret = system_save_raw_with_protect(offset, save_data,save_data_size, backup_en);
    if(ret < 0) {
        ATCMD_LOG_E("system_save_raw_with_protect fail\n");
        return -1;
    }
    ret = system_road_raw_with_protect(0, load_data,load_data_size, backup_en);
    if(ret < 0) {
        ATCMD_LOG_E("system_road_raw_with_protect fail\n");
        return -1;
    }
    ATCMD_LOG_I("[");
    for(i = 1; i <= load_data_size; i++) {
        ATCMD_LOG_I("%c ",  load_data[i -1]);
        if(i % 16 == 0)
            ATCMD_LOG_I("\n");
    }
    ATCMD_LOG_I("]\n");
    free(load_data);
    return 0;
}

int At_POWERSAVE (stParam *param)
{
	uint8_t pwmode = 0;

    if (param->argc < 1) {
        return ERROR_INVALID_PARAMETER;
    }
          
    pwmode = (u8)atoi(param->argv[0]);
	set_power_mode((u8)pwmode, 0);

	return ERROR_SUCCESS;
}

#if defined(SUPPORT_UASCENT_USER_CFG)
int At_User_Flsh(stParam *param)
{
	u8 action;
	u8 write_offset = 0;

	if(param->argc == 0 )
	{
		return ERROR_INVALID_PARAMETER;
	}
	ATCMD_LOG_I("\n");
	if( *(param->argv[0]) == 'w' )//write
	{
		action = 1;
		if(param->argc != 3 )
		{
			ATCMD_LOG_I("argc =%d\n",param->argc);
			return ERROR_INVALID_PARAMETER;
		}

		write_offset = atoi(param->argv[1]);
		if( write_offset < 0 || write_offset >3)
		{
			ATCMD_LOG_I("write_offset error %d\n",write_offset);
			return ERROR_INVALID_PARAMETER; 
		}
		if(strlen(param->argv[2]) != RW_BLOCK_SIZE)
		{
			ATCMD_LOG_I("write data Error.Len=%d\n",strlen(param->argv[2]));
			return ERROR_INVALID_PARAMETER; 
		}
	}
	else if( *(param->argv[0]) == 'r')//read
	{
		action = 0;
	}
	return do_At_User_Flsh(action, write_offset ,param->argv[2]);

}
#endif

int At_SYSINFO(stParam *param)
{
    ATCMD_LOG_I("\n");
    OS_SysInfo();
    return 0;
}
int At_ilog_set_level(stParam *param)
{
    ilog_level(param->argc, (s8**)param->argv);

    return 0;
}
int At_ilog_set_task(stParam *param)
{
    ilog_task(param->argc, (s8**)param->argv);
    
    return 0;
}
#if defined(SUPPORT_FFS)
extern SSV_FS fs_handle;
int At_FSINFO(stParam *param)
{
	ATCMD_LOG_I("\n");
	FS_list(fs_handle);
	return 0;
}

void fs_info_task(void *pdata)
{
	FS_list_personal(fs_handle);
    OS_TaskDelete(NULL);
}
int At_FSINFO_personal(stParam *param)
{
	ATCMD_LOG_I("\n");
    OS_TaskCreate(fs_info_task, "fs_info_task", 2048, NULL, OS_TASK_LOW_PRIO, NULL);
	return 0;
}
int At_FSRESET(stParam *param)
{
	ATCMD_LOG_I("\n");
	fs_handle = FS_reset();
	return 0;
}
#endif
int At_MEMINFO(stParam *param)
{
	ATCMD_LOG_I("\n");
	OS_MemInfo();
	return 0;
}
int At_MEMDUMP(stParam *param)
{
    unsigned int address = 0;
    unsigned int len = 0;
    ATCMD_LOG_I("\r\n");
    if(param->argc<2)
    {
        ATCMD_LOG_I("md=[address],[size]\r\n");
        return -1;
    }
    address = strtoul(param->argv[0], NULL, 16);
    len = strtoul(param->argv[1], NULL, 16);
    ATCMD_LOG_I("\r\n");
    ATCMD_LOG_I("md 0x%x 0x%x\r\n",address,len);
    raw_dump((char*)address, (s32)len);
    return ERROR_SUCCESS;
}
int At_WriteReg32 (stParam *param)
{
	char *pkey = 0, *pvalue = 0;

    if (param->argc < 2) {
        return ERROR_INVALID_PARAMETER;
    }

	pkey = param->argv[0];
	pvalue = param->argv[1];
    
	if( pkey == 0 || pvalue == 0)
		return ERROR_INVALID_PARAMETER;

	uint32_t address = strtoul(pkey, NULL, 16);
	uint32_t data = strtoul(pvalue, NULL, 16);

	ATCMD_LOG_I("reg : write 0x%lx  0x%lx \n", address, data);

	REG32(address)  = data;
	
	return ERROR_SUCCESS;
}
int At_ReadReg32 (stParam *param)
{
	char *pkey = 0;
       char *pnum = 0;
       int i =0;

    if (param->argc < 1) {
        return ERROR_INVALID_PARAMETER;
    }

	pkey = param->argv[0];
       pnum = param->argv[1];

	uint32_t address = strtoul(pkey, NULL, 16);
       int num = atoi(pnum);
       ATCMD_LOG_I("\n");
       if(num ==0)
       {
         ATCMD_LOG_I("reg : read 0x%lx  0x%lx \n", address, REG32(address));
       }
       else
       {
           for(i=0;i<num;i++)
           {
                ATCMD_LOG_I("0x%08lX = 0x%08lx\n", (address+i*0x04), REG32(address+i*0x04));
           }
       }
	return ERROR_SUCCESS;
}

#if defined(SUPPORT_LOW_POWER) && (SUPPORT_LOW_POWER == 1)
void power_mode_usage() {
    ATCMD_LOG_I("usage:\n");
    ATCMD_LOG_I("\t0: mcu always on, rf always on.\n");
    ATCMD_LOG_I("\t1: mcu standby, rf always on.\n");
    ATCMD_LOG_I("\t2: mcu always on, DTIM\n");
    ATCMD_LOG_I("\t3: mcu standby, DTIM\n");
    ATCMD_LOG_I("\t4: sleep, DTIM\n");
}

void dormant_usage() {
    ATCMD_LOG_I("usage:\n");
    //ATCMD_LOG_I("\tparam1: seconds.(0-134217)\n");
    // prevent rtc issue.
    ATCMD_LOG_I("\tparam1: seconds.(0-120000)\n");
    ATCMD_LOG_I("\tparam2: micro seconds.(0-1000000)\n");
    ATCMD_LOG_I("\tmin sleep time need over 2000us\n");
}

int At_sleep(stParam *param) ATTRIBUTE_SECTION_FAST;
int At_sleep(stParam *param) {
    DUT_wifi_start(DUT_NONE);
    DUT_wifi_OFF();
    ATCMD_LOG_I("!sleep start!!\n");
    OS_EnterCritical();
    sys_sleep(0);
    OS_ExitCritical();
    ATCMD_LOG_I("wakeup!!\n");
    return 0;
}

int At_dormant(stParam *param) ATTRIBUTE_SECTION_FAST;
int At_dormant(stParam *param) {
    if (param->argc != 2) {
        dormant_usage();
        return 0;
    }
    struct timeval tv;
    tv.tv_sec = strtol(param->argv[0], NULL, 10);
    tv.tv_usec = strtol(param->argv[1], NULL, 10);
    if (tv.tv_sec < 0) {
        ATCMD_LOG_I("not support little time sleep for %dsec\n", tv.tv_sec);
        return 0;
    }
    if (tv.tv_sec > 134217) {
        ATCMD_LOG_I("not support super big time sleep for %dsec\n", tv.tv_sec);
        return 0;
    }
    DUT_wifi_start(DUT_NONE);
    DUT_wifi_OFF();
    OS_EnterCritical();
    //sys_rtc_cali();
    sys_dormant(&tv);
    OS_ExitCritical();
    ATCMD_LOG_I("time=%d.%06d\n", tv.tv_sec, tv.tv_usec);
    return 0;
}

int At_power_mode(stParam *param) {
    if (param->argc != 1) {
        power_mode_usage();
        return 0;
    }
    switch(param->argv[0][0]) {
        case '1':
            lowpower_mode(E_LOW_POWER_STANDBY);
            set_power_mode(0, DUT_STA);
            break;
        case '2':
            lowpower_mode(E_LOW_POWER_ACTIVE);
            set_power_mode(1, DUT_STA);
            break;
        case '3':
            lowpower_mode(E_LOW_POWER_STANDBY);
            set_power_mode(1, DUT_STA);
            break;
        case '4':
            lowpower_mode(E_LOW_POWER_SLEEP);
            set_power_mode(1, DUT_STA);
            break;
        case '0':
        default:
            lowpower_mode(E_LOW_POWER_ACTIVE);
            set_power_mode(0, DUT_STA);
            break;
    }
    return 0;
}

int At_power_conf(stParam *param) {
    if (param->argc != 3) {
        printf("argc:%d %s\n", param->argc, param->argv[0]);
        return 0;
    }

    u8 id, mode, tsec;
    id = (u8)strtol(param->argv[0], NULL, 10);
    mode = (u8)strtol(param->argv[1], NULL, 10);
    tsec = (u8)strtol(param->argv[2], NULL, 10);

    if((mode >= 4) || (id >= 2))
    {

        return ERROR_INVALID_PARAMETER;
    }

    printf("conf:%d %d %d\n", id, mode, tsec);
    wifi_set_sta_l2keepalive(id, mode, tsec);
    return 0;

}

int At_gpio_wakeup(stParam *param) {
    uint32_t sleep_time_us  ;//= strtol(param->argv[0], NULL, 10);
    uint32_t counter        ;//= strtol(param->argv[1], NULL, 10);
    uint32_t gpio           = strtol(param->argv[0], NULL, 10);
    uint32_t int_mode       = strtol(param->argv[1], NULL, 10);

    rtc_sleep_st rtc_sleep = {0};
    uint32_t counter2 = 0;
    sleep_time_us = 0xFFFFFFFF;
    counter = 1;

    ATCMD_LOG_I("\n");
    ATCMD_LOG_I("GPIO     (%d)\n", gpio);
    ATCMD_LOG_I("INT_MODE (%d)\n", int_mode);

    //limitation :
    //low to high, multiple pin
    //high to low , single pin

    drv_gpio_set_mode(gpio,PIN_MODE_GPIO);
    drv_gpio_set_dir(gpio,GPIO_DIR_IN);

    drv_gpio_set_wakeup_enable(gpio);
    drv_gpio_intc_trigger_mode(gpio,int_mode);

    drv_gpio_set_wakeup_detect(int_mode);

    return ERROR_SUCCESS_NO_RSP;
}
#endif

