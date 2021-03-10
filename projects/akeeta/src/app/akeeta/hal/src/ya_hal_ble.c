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

#include <FreeRTOS.h>
#include <semphr.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <task.h>
#include <timers.h>
#include <ya_hal_os.h>
#include "ya_common.h"
#include "ya_hal_ble.h"
#include "infra_defs.h"
#include "ssv_hal_ble_common.h"
#include "ssv_gap_ble_api.h"
#include "ssv_gatts_api.h"
#include "ssv_gatt_common_api.h"

enum
{
    BLE_AKEETA_IDX_SVC,
    BLE_AKEETA_IDX_TX_CHAR,
    BLE_AKEETA_IDX_TX_VAL,
    BLE_AKEETA_IDX_TX_NOTIFY_CFG,
    BLE_AKEETA_IDX_RX_CHAR,
    BLE_AKEETA_IDX_RX_VAL,
    BLE_AKEETA_IDX_NB,
};

#define BLE_AKEETA_PROFILE_NUM              (1)
#define BLE_AKEETA_PROFILE_APP_IDX          (0)
#define SSV_BLE_AKEETA_APP_ID               (0)
#define BLE_AKEETA_GATTC_MTU_SIZE         	(256)
#define SVC_INST_ID							(0)
#define ADV_CONFIG_FLAG      				(1 << 0)
#define SCAN_RSP_CONFIG_FLAG 				(1 << 1)
#define CHAR_DECLARATION_SIZE       		(sizeof(uint8_t))
#define BLE_AKEETA_TX_MAX_LEN         		(256)
#define BLE_AKEETA_RX_MAX_LEN         		(256)

static ble_rcv_call_back_func_t p_rcv_fun = NULL;
static ya_ble_connected_state p_connect_state = NULL;
static uint16_t ble_akeeta_handle_table[BLE_AKEETA_IDX_NB] = {0};
static ssv_bd_addr_t st_ble_bda;
static uint8_t sg_ble_start = 0;
struct gatts_profile_inst
{
    ssv_gatts_cb_t gatts_cb;
    uint16_t gatts_if;
    uint16_t app_id;
    uint16_t conn_id;
    uint16_t service_handle;
    ssv_gatt_srvc_id_t service_id;
    uint16_t char_handle;
    ssv_bt_uuid_t char_uuid;
    ssv_gatt_perm_t perm;
    ssv_gatt_char_prop_t property;
    uint16_t descr_handle;
    ssv_bt_uuid_t descr_uuid;
};

static ssv_gatt_if_t sg_gatts_if = 0xff;
static uint16_t sg_conn_id = 0xffff;
static uint8_t adv_config_done = 0;
static ssv_ble_adv_params_t akeeta_adv_params = 
{
	.adv_int_min        = 0x20,
	.adv_int_max        = 0x40,
	.adv_type           = ADV_TYPE_IND,
	.own_addr_type      = BLE_ADDR_TYPE_PUBLIC,
	.channel_map        = ADV_CHNL_ALL,
	.adv_filter_policy  = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

static uint8_t ble_akeeta_service_uuid128[] = 
{
	//1cf0fe66-3ecf-4d6e-a9fc-e287ab124b96
    /* LSB <----------------------------------------------------------------------> MSB */
	0x96,0x4b,0x12,0xab,0x87,0xe2,0xfc,0xa9,0x6e,0x4d,0xcf,0x3e,0x66,0xfe,0xf0,0x1c
};

static uint8_t ble_akeeta_tx_uuid128[] = 
{
	//1f80af6c-2b71-4e35-94e5-00f854d8f16f
    /* LSB <----------------------------------------------------------------------> MSB */
	0x6f,0xf1,0xd8,0x54,0xf8,0x00,0xe5,0x94,0x35,0x4e,0x71,0x2b,0x6c,0xaf,0x80,0x1f
};

static uint8_t ble_akeeta_rx_uuid128[] = 
{
	//1f80af6a-2b71-4e35-94e5-00f854d8f16f
    /* LSB <----------------------------------------------------------------------> MSB */
	0x6f,0xf1,0xd8,0x54,0xf8,0x00,0xe5,0x94,0x35,0x4e,0x71,0x2b,0x6a,0xaf,0x80,0x1f
};

static ssv_ble_adv_data_t akeeta_adv_data = 
{
	.set_scan_rsp        = 0,
	.include_name        = 1,
	.include_txpower     = 1,
	.min_interval        = 0x20,
	.max_interval        = 0x40,
	.appearance          = 0x00,
	.manufacturer_len    = 0,
	.p_manufacturer_data = NULL,
	.service_data_len    = 0,
	.p_service_data      = NULL,
	.service_uuid_len    = 0,
	.p_service_uuid      = NULL,
	.flag                = (SSV_BLE_ADV_FLAG_GEN_DISC | SSV_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

static ssv_ble_adv_data_t akeeta_scan_rsp_data = 
{
    .set_scan_rsp        = 1,
    .include_name        = 0,
    .include_txpower     = 1,
    .appearance          = 0x00,
    .manufacturer_len    = 0,
    .p_manufacturer_data = NULL,
    .service_data_len    = 0,
    .p_service_data      = NULL,
	.service_uuid_len	 = 0,
	.p_service_uuid 	 = NULL,
    .flag                = (SSV_BLE_ADV_FLAG_GEN_DISC | SSV_BLE_ADV_FLAG_BREDR_NOT_SPT),
};
static const uint16_t primary_service_uuid		   = SSV_GATT_UUID_PRI_SERVICE;
static const uint16_t character_declaration_uuid   = SSV_GATT_UUID_CHAR_DECLARE;
static const uint16_t character_client_config_uuid = SSV_GATT_UUID_CHAR_CLIENT_CONFIG;
static const uint8_t char_prop_read 			   = SSV_GATT_CHAR_PROP_BIT_READ;
static const uint8_t char_prop_write			   = SSV_GATT_CHAR_PROP_BIT_WRITE;
static const uint8_t char_prop_notify			   = SSV_GATT_CHAR_PROP_BIT_NOTIFY;
static const uint8_t char_prop_read_write_notify   = SSV_GATT_CHAR_PROP_BIT_WRITE | SSV_GATT_CHAR_PROP_BIT_READ | SSV_GATT_CHAR_PROP_BIT_NOTIFY;
static const uint8_t char_prop_write_write_nr	   = SSV_GATT_CHAR_PROP_BIT_WRITE_NR | SSV_GATT_CHAR_PROP_BIT_WRITE;

static const uint8_t ble_akeeta_ccc[2]			   = {0x0, 0x0};

/* Full Database Description - Used to add attributes into the database */
static const ssv_gatts_attr_db_t ble_akeeta_gatt_db[BLE_AKEETA_IDX_NB] =
{
	// Service Declaration
	[BLE_AKEETA_IDX_SVC]			  =
	{{SSV_GATT_AUTO_RSP}, {SSV_UUID_LEN_16, (uint8_t *)&primary_service_uuid, SSV_GATT_PERM_READ,
	  sizeof(ble_akeeta_service_uuid128), sizeof(ble_akeeta_service_uuid128), (uint8_t *)ble_akeeta_service_uuid128}},

	/* Characteristic Declaration */
	[BLE_AKEETA_IDX_TX_CHAR]		  =
	{{SSV_GATT_AUTO_RSP}, {SSV_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, SSV_GATT_PERM_READ,
	  CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_notify}},

	/* Characteristic Value */
	[BLE_AKEETA_IDX_TX_VAL]		  =
	{{SSV_GATT_AUTO_RSP}, {SSV_UUID_LEN_128, (uint8_t *)&ble_akeeta_tx_uuid128, SSV_GATT_PERM_READ | SSV_GATT_PERM_WRITE,
	  BLE_AKEETA_TX_MAX_LEN, 0, NULL}},

	/* Characteristic Configuration Descriptor */
	[BLE_AKEETA_IDX_TX_NOTIFY_CFG]  =
	{{SSV_GATT_AUTO_RSP}, {SSV_UUID_LEN_16, (uint8_t *)&character_client_config_uuid, SSV_GATT_PERM_READ | SSV_GATT_PERM_WRITE,
	  sizeof(uint16_t), sizeof(ble_akeeta_ccc), (uint8_t *)ble_akeeta_ccc}},

	/* Characteristic Declaration */
	[BLE_AKEETA_IDX_RX_CHAR]		  =
	{{SSV_GATT_AUTO_RSP}, {SSV_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, SSV_GATT_PERM_READ,
	  CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_write_write_nr}},

	/* Characteristic Value */
	[BLE_AKEETA_IDX_RX_VAL]		  =
	{{SSV_GATT_RSP_BY_APP}, {SSV_UUID_LEN_128, (uint8_t *)&ble_akeeta_rx_uuid128, SSV_GATT_PERM_READ | SSV_GATT_PERM_WRITE,
	  BLE_AKEETA_RX_MAX_LEN, 0, NULL}},
};

static void gatts_ble_akeeta_profile_event_handler(ssv_gatts_cb_event_t event,ssv_gatt_if_t gatts_if,ssv_ble_gatts_cb_param_t *param)
{
    switch (event)
	{
        case SSV_GATTS_REG_EVT:
        {
            printf("[%s] SSV_GATTS_REG_EVT: %d\n", __func__, gatts_if);
            ssv_err_t set_dev_name_ret = ssv_ble_gap_set_device_name(ya_hal_ble_get_name());
            if (set_dev_name_ret)
			{
                printf("[%s] set device name failed, error code = %x", __func__, set_dev_name_ret);
            }

            //config adv data
            ssv_err_t ret = ssv_ble_gap_config_adv_data(&akeeta_adv_data);
            if (ret)
			{
                printf("[%s] config adv data failed, error code = %x", __func__, ret);
            }
            adv_config_done |= ADV_CONFIG_FLAG;

            //config scan rssvonse data
            ret = ssv_ble_gap_config_adv_data(&akeeta_scan_rsp_data);
            if (ret)
			{
                printf("[%s] config scan raw scan rsp data failed, error code = %x", __func__, ret);
            }
            adv_config_done |= SCAN_RSP_CONFIG_FLAG;

            ssv_err_t create_attr_ret = ssv_ble_gatts_create_attr_tab(ble_akeeta_gatt_db, gatts_if, BLE_AKEETA_IDX_NB, SVC_INST_ID);
            if (create_attr_ret)
			{
                printf("[%s] create attr table failed, error code = %x", __func__, create_attr_ret);
            }
        }
            break;

        case SSV_GATTS_CONNECT_EVT:
            printf("[%s] SSV_GATTS_CONNECT_EVT: %d\n", __func__, gatts_if);
            sg_gatts_if = gatts_if;
            sg_conn_id = param->connect.conn_id;
			memcpy(&st_ble_bda,&param->connect.remote_bda,sizeof(ssv_bd_addr_t));
			p_connect_state(1);
            break;

        case SSV_GATTS_CREAT_ATTR_TAB_EVT:
            printf("[%s] SSV_GATTS_CREAT_ATTR_TAB_EVT, status %d, handles 0x%x\n", __func__,param->add_attr_tab.status, param->add_attr_tab.handles[0]);

            if (param->add_attr_tab.status != SSV_GATT_OK)
			{
                printf("[%s] create attribute table failed, error code=0x%x\n", __func__, param->add_attr_tab.status);
            }
            else if (param->add_attr_tab.num_handle != BLE_AKEETA_IDX_NB)
			{
                printf("[%s] create attribute table abnormally, num_handle (%d) doesn't equal to BLE_UART_IDX_NB(%d)\n", __func__, param->add_attr_tab.num_handle, BLE_AKEETA_IDX_NB);
            }
            else 
			{
				memset(ble_akeeta_handle_table,0,BLE_AKEETA_IDX_NB);
                memcpy(ble_akeeta_handle_table, param->add_attr_tab.handles, sizeof(ble_akeeta_handle_table));
                ssv_ble_gatts_start_service(ble_akeeta_handle_table[BLE_AKEETA_IDX_SVC]);
            }
            break;
        case SSV_GATTS_DISCONNECT_EVT:
			printf("[%s] SSV_GATTS_DISCONNECT_EVT, reason = 0x%x\n", __func__, param->disconnect.reason);
			p_connect_state(0);
			if(sg_ble_start)
				ssv_ble_gap_start_advertising(&akeeta_adv_params);
            break;

        case SSV_GATTS_WRITE_EVT:
			printf("[%s] SSV_GATTS_WRITE_EVT\n", __func__);
            if (!param->write.is_prep)
			{
                // the data length of gattc write  must be less than GATTS_DEMO_CHAR_VAL_LEN_MAX.
                if (ble_akeeta_handle_table[BLE_AKEETA_IDX_RX_VAL] == param->write.handle)
				{
                    //printf("recv RX_Characteristic: %s\n", param->write.value);
					p_rcv_fun(param->write.value,param->write.len);
                } 
                /* send response when param->write.need_rsp is true*/
                if (param->write.need_rsp)
				{
                    ssv_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, SSV_GATT_OK, NULL);
                }	
            }
			else
			{           
                /* handle prepare write */
                printf("[%s] else SSV_GATTS_WRITE_EVT\n", __func__);
            }
      	    break;
        case SSV_GATTS_EXEC_WRITE_EVT:
            // the length of gattc prepare write data must be less than GATTS_DEMO_CHAR_VAL_LEN_MAX.
            printf("SSV_GATTS_EXEC_WRITE_EVT");
            break;
        case SSV_GATTS_MTU_EVT:
            printf("SSV_GATTS_MTU_EVT, MTU %d", param->mtu.mtu);
            break;
        case SSV_GATTS_CONF_EVT:
            printf("SSV_GATTS_CONF_EVT, status = %d, attr_handle %d", param->conf.status, param->conf.handle);
            break;
        case SSV_GATTS_START_EVT:
            printf("SERVICE_START_EVT, status %d, service_handle %d", param->start.status, param->start.service_handle);
            break;
        case SSV_GATTS_STOP_EVT:
        case SSV_GATTS_OPEN_EVT:
        case SSV_GATTS_CANCEL_OPEN_EVT:
        case SSV_GATTS_CLOSE_EVT:
        case SSV_GATTS_LISTEN_EVT:
        case SSV_GATTS_CONGEST_EVT:
        case SSV_GATTS_UNREG_EVT:
        case SSV_GATTS_DELETE_EVT:
        default:
            printf("[%s] event %d\n", __func__, event);
            break;
    }
}

/* One gatt-based profile one app_id and one gatts_if, this array will store the gatts_if returned by SSV_GATTS_REG_EVT */
static struct gatts_profile_inst sg_ble_akeeta_profile_table[BLE_AKEETA_PROFILE_NUM] = 
{
	[BLE_AKEETA_PROFILE_APP_IDX] = 
	{
		.gatts_cb = gatts_ble_akeeta_profile_event_handler,
		.gatts_if = SSV_GATT_IF_NONE,		/* Not get the gatt_if, so initial is SSV_GATT_IF_NONE */
	},
};

void ya_hal_ble_set_connect_state_cb(ya_ble_connected_state func)
{
	p_connect_state = func;
}

void ya_hal_ble_set_rcv_cb(ble_rcv_call_back_func_t func)
{
	p_rcv_fun = func;
}

int ya_hal_ble_send_bytes(uint8_t *data, uint16_t len)
{
	int ret = -1;
	if(!data)
		return ret;
	if(len > BLE_AKEETA_TX_MAX_LEN)
		len = BLE_AKEETA_TX_MAX_LEN;
    ret = ssv_ble_gatts_send_indicate(sg_gatts_if, sg_conn_id, ble_akeeta_handle_table[BLE_AKEETA_IDX_TX_VAL], len, data, false);
	return ret;
}

char *ya_hal_ble_get_name(void)
{
	static char ble_name[24]={0};
	uint8_t device_mac[6]={0};
	
	memset(ble_name, 0, 24);
	ya_hal_wlan_get_mac_address(device_mac);
	snprintf(ble_name, sizeof(ble_name), "ARGRACE_01%02x%02x%02x%02x%02x%02x", device_mac[0], device_mac[1], device_mac[2], device_mac[3], device_mac[4], device_mac[5]);
	return ble_name;
}

int ya_hal_ble_start_adv(uint8_t *adv_ff_string, uint8_t len)
{
	int ret = 0;
	if(sg_ble_start == 0)
	{
		if(len > 0)
		{
			akeeta_scan_rsp_data.manufacturer_len = len;
			memcpy(akeeta_scan_rsp_data.p_manufacturer_data,adv_ff_string,len); 
		}
		ret = ssv_ble_gatts_app_register(SSV_BLE_AKEETA_APP_ID);
		if (ret)
		{
			ya_printf(C_LOG_INFO,"[%s] failed in line %d gatts app register error, error code = %x\n", __func__, __LINE__, ret);
			return -1;
		}
		
		ssv_err_t ssv_ret = ssv_ble_gatt_set_local_mtu(BLE_AKEETA_GATTC_MTU_SIZE);
		if (ssv_ret)
		{
			ya_printf(C_LOG_INFO,"[%s] line %d, set local MTU failed, error code = %x", __func__, __LINE__, ssv_ret);
			return -1;
		}
		sg_ble_start = 1;		
	}
	return ret;
}

void ya_hal_disconnect_ble_conn(void)
{
	ssv_ble_gap_disconnect(st_ble_bda);
}

void ya_hal_stop_ble(void)
{
    sg_ble_start = 0;
    ssv_ble_gap_disconnect(st_ble_bda);
    ssv_ble_gap_stop_advertising();
}

static void ssv_ble_akeeta_gap_event_cb(ssv_gap_ble_cb_event_t event, ssv_ble_gap_cb_param_t *param)
{
	ya_printf(C_LOG_INFO,"[%s] event %d\n", __func__, event);
    switch (event) 
	{
        case SSV_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
            adv_config_done &= (~ADV_CONFIG_FLAG);
            if (adv_config_done == 0)
                ssv_ble_gap_start_advertising(&akeeta_adv_params);
            break;

        case SSV_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
            adv_config_done &= (~SCAN_RSP_CONFIG_FLAG);
            if (adv_config_done == 0)
                ssv_ble_gap_start_advertising(&akeeta_adv_params);
            break;

        case SSV_GAP_BLE_ADV_START_COMPLETE_EVT:
            ya_printf(C_LOG_INFO,"[%s] event SSV_GAP_BLE_ADV_START_COMPLETE_EVT\n", __func__);
            break;

        case SSV_GAP_BLE_ADV_STOP_COMPLETE_EVT:
            ya_printf(C_LOG_INFO,"[%s] event SSV_GAP_BLE_ADV_STOP_COMPLETE_EVT\n", __func__);
            break;

        default:
            ya_printf(C_LOG_INFO,"[%s] event %d\n", __func__, event);
            break;
    }
}

static void akeeta_gatts_event_handler(ssv_gatts_cb_event_t event, ssv_gatt_if_t gatts_if, ssv_ble_gatts_cb_param_t *param)
{
    /* If event is register event, store the gatts_if for each profile */
    if (event == SSV_GATTS_REG_EVT)
	{
        if (param->reg.status == SSV_GATT_OK)
		{
            if (param->reg.app_id != 0)
			{
                ya_printf(C_LOG_ERROR,"[%s] register, app_id %04x, it should be 0\n", __func__, param->reg.app_id);
                while(1);// aMH todo remove this assert!!
            }
            sg_ble_akeeta_profile_table[param->reg.app_id].gatts_if = gatts_if;
        } 
		else
		{
            ya_printf(C_LOG_ERROR,"Reg app failed, app_id %04x, status %d\n",param->reg.app_id,param->reg.status);
            return;
        }
    }

    /* If the gatts_if equal to profile A, call profile A cb handler,
     * so here call each profile's callback */
    do {
        int idx;
        for (idx = 0; idx < BLE_AKEETA_PROFILE_NUM; idx++) 
		{
            if (gatts_if == SSV_GATT_IF_NONE || /* SSV_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
                gatts_if == sg_ble_akeeta_profile_table[idx].gatts_if) 
            {
                if (sg_ble_akeeta_profile_table[idx].gatts_cb) 
				{
                    sg_ble_akeeta_profile_table[idx].gatts_cb(event, gatts_if, param);
                }
            }
        }
    } while (0);
}

int ya_hal_ble_init(void)
{
	int ret = 0;
	
	ya_printf(C_LOG_INFO,"\r\nble device name ====%s\r\n", ya_hal_ble_get_name());
	
	adv_config_done = 0;
	sg_ble_start = 0;

    ret = ssv_ble_gap_register_callback(ssv_ble_akeeta_gap_event_cb);
    if (ret)
	{
        ya_printf(C_LOG_INFO,"[%s] failed in line %d\n", __func__, __LINE__);
		return -1;
    }

    ret = ssv_hal_ble_common_init();
    if (ret)
	{
        ya_printf(C_LOG_INFO,"[%s] failed in line %d\n", __func__, __LINE__);
		return -1;
    }

    ret = ssv_ble_gatts_register_callback(akeeta_gatts_event_handler);
    if (ret)
	{
        ya_printf(C_LOG_INFO,"[%s] failed in line %d gatts register error, error code = %x\n", __func__, __LINE__, ret);
        return -1;
    }
	
	return 0;
}


