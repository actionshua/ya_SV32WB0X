#include <stdio.h>
#include "soc_types.h"
#include "ssv_lib.h"
#include "ieee80211_mgmt.h"
#include "Cabrio-conf.h"
#include "wifi_api.h"
#include "sysconf_api.h"

#include <bsp.h>

//#include "efuse/hal_efuse.h"

#define WIFI_CONFIG_FILE "wifi.conf"
#define SYS_CONFIG_FILE "sys.conf"

extern IEEE80211STATUS gwifistatus;
AP_DETAIL_INFO wifi_recode;
SYS_CONF_INFO sysconf_info;

//callback function
extern void scan_cbfunc();
extern void atwificbfunc(WIFI_RSP *msg);

//api function
void init_global_conf()
{
    int rlt = 0;
    rlt = read_wifi_config();
    rlt = read_sys_config();
}

int add_ap_to_list()
{
    memset(&ap_list[getAvailableIndex()], 0, sizeof(TAG_AP_INFO));
    
    ap_list[getAvailableIndex()].channel = wifi_recode.channel;
    memcpy(ap_list[getAvailableIndex()].mac, wifi_recode.mac, 6);
    memcpy(ap_list[getAvailableIndex()].name, wifi_recode.ssid, wifi_recode.ssid_len);
    ap_list[getAvailableIndex()].name_len = wifi_recode.ssid_len;
    ap_list[getAvailableIndex()].rssi = wifi_recode.rssi;
    ap_list[getAvailableIndex()].security_subType = wifi_recode.security_subType;
    ap_list[getAvailableIndex()].security_type = wifi_recode.security_type;
    gwifistatus.available_index++;
    
    return 0;
}
int do_scan_AP()
{
    scan_AP(scan_cbfunc);
    return 0;
}
int do_wifi_connect()
{
    return wifi_connect(atwificbfunc);
}
int do_wifi_disconnect()
{
    wifi_disconnect(atwificbfunc);
    return 0;
}
int do_wifi_auto_connect()
{ 
    if (read_wifi_config() ==0)
    {
        printf("ap channel = %d\n", wifi_recode.channel);
        printf("ap ssid = %s(%d)\n", wifi_recode.ssid, wifi_recode.ssid_len);
        printf("ap key = %s(%d)\n", wifi_recode.key, wifi_recode.key_len);
        DUT_wifi_start(DUT_STA);
        if(add_ap_to_list() != 0)
            return -1;
        
        //drv_phy_channel_change( wifi_recode.channel, 1);    
        int ret = set_wifi_config(wifi_recode.ssid, wifi_recode.ssid_len, wifi_recode.key, wifi_recode.key_len, NULL, 0);
        if(ret != 0)
            printf("set_wifi_config error %d!\n", ret);
        else
            wifi_connect(atwificbfunc);
    }

    return 0;
}

int set_auto_connect_flag(u8 bEnable)
{
    memset(&sysconf_info, 0, sizeof(sysconf_info));
    int ret = read_sys_config();
    if(ret !=0)
        printf("sys_conf isn't exist, we will create one\n");

    sysconf_info.nAutoConnect = bEnable;

    ret = write_sys_config();

    return ret;
}

int get_auto_connect_flag()
{
    int ret = read_sys_config();
    
    if(ret !=0)
        return 0;
    else
        return sysconf_info.nAutoConnect;
    
}
void recordAP()
{
    if( (wifi_recode.ssid_len ==  gwifistatus.connAP[0].ssid_len) &&
         (wifi_recode.key_len ==  gwifistatus.connAP[0].key_len) &&
         (memcmp(wifi_recode.ssid, gwifistatus.connAP[0].ssid, wifi_recode.ssid_len ) ==0 ) &&
         (memcmp(wifi_recode.key, gwifistatus.connAP[0].key, wifi_recode.key_len ) ==0)  
        )
    {
        ;//printf("ap is the same\n\n");
    }
    else
    {
    memset(&wifi_recode, 0, sizeof(wifi_recode));
    memcpy(&wifi_recode, &gwifistatus.connAP, sizeof(wifi_recode));
    write_wifi_config();
    }

}
//fs function
int write_wifi_config()
{
    int rlt = 0;

#if defined(SUPPORT_FFS)
    SSV_FILE fd = FS_open(fs_handle, WIFI_CONFIG_FILE, SSV_O_CREAT | SSV_O_TRUNC | SSV_O_RDWR, 0);
    if (fd == NULL) 
    {
        printf("FS_open error\n");
        rlt = -1;
        goto error_exit;
    } 

    if( FS_write(fs_handle, fd, &wifi_recode, sizeof(wifi_recode)) < 0 )
    {
        printf("FS_write error\n");
        rlt = FS_ferrno(fd);
        goto error_exit;
    }
    printf("write_wifi_config ok\n");

error_exit:

    FS_close(fs_handle, fd);
    printf("rlt = %d\n", rlt);
#else
    printf("[%s] filesystem feature disabled.\n", __func__);
#endif
    
    return rlt;        

}
int read_wifi_config()
{
    int rlt = 0;
    
#if defined(SUPPORT_FFS)
    SSV_FILE fd = FS_open(fs_handle, WIFI_CONFIG_FILE, SSV_O_RDWR, 0);
    if (fd == NULL) 
    {
        printf("FS_open error\n");
        rlt = -1;
        goto error_exit;
    }

    memset(&wifi_recode, 0, sizeof(wifi_recode));
    if (FS_read(fs_handle, fd, &wifi_recode, sizeof(wifi_recode)) < 0)
    {
        printf("FS_read error\n");
        rlt = FS_ferrno(fd);
        goto error_exit;
    }

    printf("read_wifi_config ok\n");

error_exit:

    FS_close(fs_handle, fd);
    printf("rlt = %d\n", rlt);
#else
    printf("[%s] filesystem feature disabled.\n", __func__);
#endif
    
    return rlt;   	
}
int remove_wifi_config()
{
    int rlt = 0;
#if defined(SUPPORT_FFS)
    rlt = FS_remove(fs_handle, WIFI_CONFIG_FILE);
#else
    printf("[%s] filesystem feature disabled.\n", __func__);
#endif
    return rlt;
}

int write_sys_config()
{
    int rlt = 0;

#if defined(SUPPORT_FFS)
    SSV_FILE fd = FS_open(fs_handle, SYS_CONFIG_FILE, SSV_O_CREAT | SSV_O_TRUNC | SSV_O_RDWR, 0);
    if (fd == NULL) 
    {
        printf("FS_open error\n");
        rlt = -1;
        goto error_exit;
    }
     
    if( FS_write(fs_handle, fd, &sysconf_info, sizeof(sysconf_info)) < 0 )
    {
        printf("FS_write error\n");
        rlt = FS_ferrno(fd);
        goto error_exit;
    }
    printf("write_wifi_config ok\n");

error_exit:

    FS_close(fs_handle, fd);
    printf("rlt = %d\n", rlt);
#else
    printf("[%s] filesystem feature disabled.\n", __func__);
#endif
    
    return rlt;      
}
int read_sys_config()
{
    int rlt = 0;
    
#if defined(SUPPORT_FFS)
    SSV_FILE fd = FS_open(fs_handle, SYS_CONFIG_FILE, SSV_O_RDWR, 0);
    if (fd == NULL) 
    {
        rlt = -1;
        goto error_exit;
    }

    if (FS_read(fs_handle, fd, &sysconf_info, sizeof(sysconf_info)) < 0)
    {
        rlt = FS_ferrno(fd);
        goto error_exit;
    }

error_exit:

    FS_close(fs_handle, fd);
    printf("read_sys_config rlt = %d\n", rlt);
#else
    printf("[%s] filesystem feature disabled.\n", __func__);
#endif
    
    return rlt;   	
}
int remove_sys_config()
{
    int rlt = 0;
#if defined(SUPPORT_FFS)
    rlt = FS_remove(fs_handle, SYS_CONFIG_FILE);
#else
    printf("[%s] filesystem feature disabled.\n", __func__);
#endif
    return rlt;   
}

int system_restore()
{
    int rlt = 0;
    rlt = remove_wifi_config();
    rlt = remove_sys_config();
    //need restore STA Mode related setting
    //need restore SoftAP Mode related setting
    //need restore Wifi Opmode setting

    return rlt;
}
