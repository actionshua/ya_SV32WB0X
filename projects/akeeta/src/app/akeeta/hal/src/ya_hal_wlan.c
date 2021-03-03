/*
 * Copyright(c) 2018 - 2020 Yaguan Technology Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "ya_common.h"
#include <wifi_api.h>
#include <lowpower.h>
#include <powersave/powersave.h>
#include "softap_func.h"


#define WIFI_SSID_MAX_LEN   (32)
#define WIFI_PWD_MAX_LEN    (64) // pwd string support max length is 63
extern IEEE80211STATUS gwifistatus;

static ya_hal_os_thread_t wlan_connect_event_thread = NULL;
static ya_hal_wlan_event_handler_t hEventHandler = NULL;
static uint8_t wlan_connected_flag = 0;
static uint8_t wlan_disconnected_flag = 0;
static uint8_t wlan_scan_num = 0;
static uint8_t wlan_scan_cur_index = 0;
static ya_obj_ssid_result_t ya_obj_ssid_result[2] = {0};
static SemaphoreHandle_t ya_scan_obj_ssid_sem = NULL;

static void wlan_connect_event(void *arg)
{
	while(1)
	{
		if(DUT_STA == get_DUT_wifi_mode())
		{
			if(1 == get_wifi_status()) 
			{
				if(wlan_connected_flag == 0)
				{
					wlan_connected_flag = 1;
					wlan_disconnected_flag = 0;
					hEventHandler(YA_HAL_EVT_STA_CONNECT_SUCCESS, NULL);
				}
			}
			else 
			{
				if(wlan_disconnected_flag == 0)
				{
					wlan_disconnected_flag = 1;
					wlan_connected_flag = 0;
					hEventHandler(YA_HAL_EVT_LINK_LOST, NULL);
				}
			}
		}
		ya_delay(500);
	}
	ya_hal_os_thread_delete(wlan_connect_event_thread);
	wlan_connect_event_thread = NULL;
}

int32_t ya_hal_wlan_start(ya_hal_wlan_event_handler_t event_handler)
{	
	hEventHandler = event_handler;	
	int ret;
	ret = ya_hal_os_thread_create(&wlan_connect_event_thread, "wlan_connect_event_thread", wlan_connect_event, 0, (1024), 3);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create wlan_connect_event_thread error\r\n");
		return -1;
	}
	return 0;
}

int32_t ya_hal_wlan_stop(void)
{
	DUT_wifi_stop();
	if(wlan_connect_event_thread != NULL)
	{
		ya_hal_os_thread_delete(wlan_connect_event_thread);
		wlan_connect_event_thread = NULL;
	}
	return 0;
}

int32_t ya_disable_wifi_power_saving()
{
    lowpower_mode(E_LOW_POWER_ACTIVE);
    set_power_mode(0, DUT_STA);	
	return 0;
}

int32_t ya_hal_wlan_disconnnect_wifi(void)
{
	wifi_disconnect(NULL);
	return 0;
}

int32_t ya_hal_set_sta_mode()
{
	if(get_DUT_wifi_mode() != DUT_STA)
	{
		DUT_wifi_start(DUT_STA);
		OS_MsDelay(200);		
	}
	return 0;
}

int32_t ya_hal_wlan_start_ap(ya_hal_wlan_ap_start_param_t *ap_start_param)
{
	if (ap_start_param->ssid_length > WIFI_SSID_MAX_LEN || ap_start_param->password_length > WIFI_PWD_MAX_LEN)
	{
		ya_printf(C_LOG_ERROR,"ssid_length=%d,password_length=%d\r\n",ap_start_param->ssid_length,ap_start_param->password_length);
		return -1;
	}
	if(0 == wifi_ap_easy_conf(ap_start_param->ssid,ap_start_param->ssid_length,ap_start_param->password,ap_start_param->password_length,ap_start_param->channel))
		DUT_wifi_start(DUT_AP);
	else
	{
    	ya_printf(C_LOG_ERROR,"Establish Sodt AP fail\r\n");
		return -1;
	}
    ya_printf(C_LOG_INFO,"Establish Sodt AP, SSID:%s and KEY:%s\r\n", ap_start_param->ssid, ap_start_param->password);
	return 0;
}

int32_t ya_hal_wlan_stop_ap(void)
{
	return 0;
}

int32_t ya_hal_wlan_get_mac_address(uint8_t *mac_addr)
{
    void *cfg_handle = (void *)wifi_cfg_init();
    if (cfg_handle == NULL) 
	{
        return -1;
    }

    wifi_cfg_get_addr2(cfg_handle, mac_addr);
    wifi_cfg_deinit(cfg_handle);
    
    ya_printf(C_LOG_INFO,"mac=%02X:%02X:%02X:%02X:%02X:%02X\n",mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
	if(mac_addr[0] == 0x44 && mac_addr[1] == 0x57 && mac_addr[2] == 0x18  
	&& mac_addr[3] == 0x3f && mac_addr[4] == 0x49 && mac_addr[5] == 0x01)	
	{
		ya_os_get_random(mac_addr+3,3);
		int32_t ret = ya_hal_wlan_set_mac_address(mac_addr);
	}
	return 0;
}

int32_t ya_hal_wlan_set_mac_address(uint8_t *mac_addr)
{
    void *cfg_handle = (void *)wifi_cfg_init();
	char mac_str[24] = {0};
    if (cfg_handle == NULL) 
	{
        return -1;
    }

	snprintf(mac_str, sizeof(mac_str),"%02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0],mac_addr[1],mac_addr[2], mac_addr[3],mac_addr[4],mac_addr[5]);
	
    wifi_cfg_replace_mem_addr2(cfg_handle, mac_str);
    wifi_cfg_write_cfg(cfg_handle);
    wifi_cfg_deinit(cfg_handle);

	return 0;
}

int32_t ya_hal_wlan_get_ip_address(uint32_t *ipv4_addr)
{
    uint8_t dhcpen;
    uint8_t mac[6];
    uip_ipaddr_t ipaddr, submask, gateway, dnsserver;

	if(get_wifi_status())
	{
		get_if_config_2("et0", &dhcpen, (u32*)&ipaddr, (u32*)&submask, (u32*)&gateway, (u32*)&dnsserver, mac, 6);
		memcpy(ipv4_addr, ipaddr.u8, 4);
	}
	else
	{
		*ipv4_addr = 0;
	}

	return 0;
}

int32_t ya_hal_wlan_get_ip_address_with_string(uint8_t *ip, uint8_t len)
{
    uint8_t dhcpen;
    uint8_t mac[6];
    uip_ipaddr_t ipaddr, submask, gateway, dnsserver;

	if(get_wifi_status())
	{
		get_if_config_2("et0", &dhcpen, (u32*)&ipaddr, (u32*)&submask, (u32*)&gateway, (u32*)&dnsserver, mac, 6);
		memcpy(ip, ipaddr.u8, 4);
	}
	else
	{
		memset(ip, 0, len);
	}
	return 0;
}


int32_t ya_hal_wlan_get_gateway_ip_address(uint32_t *gate_addr)
{
    uint8_t dhcpen;
    uint8_t mac[6];
    uip_ipaddr_t ipaddr, submask, gateway, dnsserver;

	if(get_wifi_status())
	{
		get_if_config_2("et0", &dhcpen, (u32*)&ipaddr, (u32*)&submask, (u32*)&gateway, (u32*)&dnsserver, mac, 6);
		memcpy(gate_addr, gateway.u8, 4);
	}
	else
	{
		*gate_addr = 0;
	}

	return 0;
}

int32_t ya_hal_wlan_get_rssi(int32_t *rssi)
{
	if(get_wifi_status())
	{
		*rssi = gwifistatus.connAP[0].rssi;
	}
	else
		return -1;
	return 0;
}

int32_t ya_hal_wlan_get_channel(uint32_t *channel)
{	
	if(get_wifi_status())
	{
		*channel = gwifistatus.connAP[0].channel;
	}
	else
		return -1;
	return 0;
}

int32_t ya_hal_wlan_set_channel(uint32_t channel)
{
	wifi_set_channel(channel, NL80211_CHAN_HT40PLUS);
	return 0;
}

static void scan_complete_cb_with_fix_channel(void)
{
	uint8_t i;
	ya_obj_ssid_result_t *p = &ya_obj_ssid_result[wlan_scan_cur_index];
    for (i = 0; i < get_ap_lsit_total_num(); i++)
    {
		//ya_printf(C_AT_CMD,"ap_list[%d].name==%s,rssi=%d,p->scan_ssid==%s\r\n",i,ap_list[i].name,ap_list[i].rssi,p->scan_ssid);
    	if(strcmp(ap_list[i].name, p->scan_ssid) == 0)
    	{
			p->scan_result = 1;
			p->rssi = ap_list[i].rssi;
			goto END;
    	}
    }
END:
	ya_printf(C_LOG_INFO,"finish scan\r\n");
	xSemaphoreGive(ya_scan_obj_ssid_sem);
}

int32_t ya_hal_wlan_scan_obj_ssid_with_fix_channel(ya_obj_ssid_result_t *obj_scan_ssid, uint8_t num)
{
	wlan_scan_num = num;
	memcpy(ya_obj_ssid_result,obj_scan_ssid,sizeof(ya_obj_ssid_result_t)*num);
	if(ya_scan_obj_ssid_sem == NULL)
		ya_scan_obj_ssid_sem = xSemaphoreCreateBinary();
	if(get_DUT_wifi_mode() != DUT_STA)
		DUT_wifi_start(DUT_STA);
	wlan_scan_cur_index = 0;
	ya_printf(C_LOG_INFO,"start scan CH 5 6 7\r\n");
	scan_AP_custom(ya_obj_ssid_result[0].scan_ssid,scan_complete_cb_with_fix_channel,0b1110000,0b1110000,300,0,0);
	xSemaphoreTake(ya_scan_obj_ssid_sem, portMAX_DELAY);
	if(2 == num && 0 == ya_obj_ssid_result[0].scan_result)
	{
		wlan_scan_cur_index = 1;
		scan_AP_custom(ya_obj_ssid_result[1].scan_ssid,scan_complete_cb_with_fix_channel,0b1110000,0b1110000,300,0,0);	
		xSemaphoreTake(ya_scan_obj_ssid_sem, portMAX_DELAY);
	}
	vSemaphoreDelete(ya_scan_obj_ssid_sem);
	memcpy(obj_scan_ssid,ya_obj_ssid_result,sizeof(ya_obj_ssid_result_t)*num);
    return 0;
}
static void scan_complete_cb(void)
{
	uint8_t i;
	uint8_t index;
	ya_obj_ssid_result_t *p = &ya_obj_ssid_result[0];
	for	(index = 0; index < wlan_scan_num; index++)
	{
	    for (i = 0; i < get_ap_lsit_total_num(); i++)
	    {
			//ya_printf(C_AT_CMD,"ap_list[%d].name==%s,rssi=%d,p->scan_ssid==%s\r\n",i,ap_list[i].name,ap_list[i].rssi,p->scan_ssid);
	    	if(strcmp(ap_list[i].name, p->scan_ssid) == 0)
	    	{
				p->scan_result = 1;
				p->rssi = ap_list[i].rssi;
				goto END;
	    	}
	    }
		p++;
	}
END:
	ya_printf(C_LOG_INFO,"finish scan\r\n");
	xSemaphoreGive(ya_scan_obj_ssid_sem);
}

int32_t ya_hal_wlan_scan_obj_ssid(ya_obj_ssid_result_t *obj_scan_ssid, uint8_t num)
{
	wlan_scan_num = num;
	memcpy(ya_obj_ssid_result,obj_scan_ssid,sizeof(ya_obj_ssid_result_t)*num);
	if(ya_scan_obj_ssid_sem == NULL)
		ya_scan_obj_ssid_sem = xSemaphoreCreateBinary();
	if(get_DUT_wifi_mode() != DUT_STA)
		DUT_wifi_start(DUT_STA);
	ya_printf(C_LOG_INFO,"\r\nstart scan\r\n");
	scan_AP(scan_complete_cb);
	xSemaphoreTake(ya_scan_obj_ssid_sem, portMAX_DELAY);
	vSemaphoreDelete(ya_scan_obj_ssid_sem);
	memcpy(obj_scan_ssid,ya_obj_ssid_result,sizeof(ya_obj_ssid_result_t)*num);
    return 0;
}

static void connect_ap_cbfunc(WIFI_RSP *msg)
{
    if(msg->wifistatus == 1)
    {
        ya_printf(C_LOG_INFO,"connect OK\n");
    }
    else
    {
        ya_printf(C_LOG_INFO,"STA disconnect!!\n");
    }
}

int32_t ya_hal_wlan_connect_ap(ya_hal_wlan_ap_connect_param_t *connect_param)
{
	if(strlen(connect_param->ssid) == 0 || strlen(connect_param->ssid) > 32 || strlen(connect_param->pwd) > 64)
	{
		hEventHandler(YA_HAL_EVT_LINK_LOST, NULL);
		return -1;
	}
	wifi_disconnect(NULL);
	DUT_wifi_stop();
	if(get_DUT_wifi_mode() != DUT_STA)
	{
		DUT_wifi_start(DUT_STA);
		OS_MsDelay(200);
	}
	if(strlen(connect_param->pwd) == 0)
		wifi_connect_active(connect_param->ssid, strlen(connect_param->ssid), NULL, (u8)strlen((char*)NULL), connect_ap_cbfunc);
	else
		wifi_connect_active(connect_param->ssid, strlen(connect_param->ssid), connect_param->pwd, strlen(connect_param->pwd), connect_ap_cbfunc);
	return 0;
}


ya_monitor_data_cb_t g_monitor_callback = NULL;

int ya_wifi_stop_monitor(void)
{
    return 0;
}

static void wifi_promisc_hdl(void *env, uint8_t *pkt, int len)
{
    if (g_monitor_callback){
        g_monitor_callback(pkt, len); 
     }
}

int ya_wifi_start_monitor(ya_monitor_data_cb_t fn)
{
	g_monitor_callback = fn;
	return 0;
}

