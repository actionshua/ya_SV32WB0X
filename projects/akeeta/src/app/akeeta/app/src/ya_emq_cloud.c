

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
#include "cJSON.h"
#include "ya_config.h"
#include "MQTTClient.h"
#include "ya_emq_cloud.h"

#if (EMQ_ENABLE)

#if (CLOUD_SUPPORT == US_CN_CLOUD_SUPPORT || CLOUD_SUPPORT == US_CLOUD_SUPPORT)
#include "ya_emq_cloud.h"

typedef enum
{
	EMQ_CLOUD_INIT	   				= 0x00,
	EMQ_TO_CONNECT_CLOUD,
	EMQ_CONNECTED_CLOUD,
	EMQ_CONNECT_ERROR,
	EMQ_RECONNECT_WAIT,
}ya_emq_cloud_state_t;

typedef enum
{
	YA_PUBLISH_RESPONSE	   				= 0x00,
	YA_HARDWARE_REPORT,
}ya_emq_cloud_queue_msg_type_t;

typedef struct ya_emq_cloud_event_callbackhandler{
	char *task_name;
	cloud_event_type_t event_type;
	cloud_event_callback	 ya_cloud_event_handler;

	struct ya_emq_cloud_event_callbackhandler *ya_emq_cloud_event_callbackhandler_next;
}ya_emq_cloud_event_callbackhandler_t;

ya_emq_cloud_event_callbackhandler_t *ya_emq_cloud_callback_list = NULL;
uint8_t *emq_send_buf = NULL, *emq_rece_buf = NULL;

ya_hal_os_thread_t ya_emq_app_cloud = NULL;
ya_hal_os_queue_t ya_emq_cloud_msg_queue = NULL;

ya_emq_cloud_state_t ya_emq_cloud_state = EMQ_CLOUD_INIT;
static uint8_t ya_cloud_connected = 0;
static char *subscribe_topic = NULL;

MQTTClient emq_client;
Network emq_network;

uint8_t emq_cloud_domain = WIFI_US;

int32_t ya_add_emq_cloud_event_listener(char *task_name, cloud_event_type_t event_type, cloud_event_callback ya_cloud_event_chandler)
{
	ya_emq_cloud_event_callbackhandler_t *list_node = NULL, *add_node = NULL;

	if(!task_name)
		return C_ERROR;

	list_node = ya_emq_cloud_callback_list;

	while(list_node)
	{
		if(list_node->task_name)
		{
			if(strcmp(list_node->task_name, task_name) == 0 && list_node->event_type == event_type)
				return C_OK;
		}

		if(!(list_node->ya_emq_cloud_event_callbackhandler_next))
			break;
		else
			list_node = list_node->ya_emq_cloud_event_callbackhandler_next;
	}

	add_node = (ya_emq_cloud_event_callbackhandler_t *)ya_hal_os_memory_alloc(sizeof(ya_emq_cloud_event_callbackhandler_t));
	if(!add_node)
		return C_ERROR;

	add_node->task_name = (char *)ya_hal_os_memory_alloc(strlen(task_name) + 1);
	if(!add_node->task_name)
	{
		if(add_node)
			ya_hal_os_memory_free(add_node);
		
		return C_ERROR;
	}

	strcpy(add_node->task_name,  task_name);
	add_node->event_type = event_type;
	add_node->ya_cloud_event_handler = ya_cloud_event_chandler;

	add_node->ya_emq_cloud_event_callbackhandler_next = NULL;

	if(list_node)
		list_node->ya_emq_cloud_event_callbackhandler_next = add_node;
	else
		ya_emq_cloud_callback_list = add_node;

	ya_printf(C_LOG_INFO,"ya_add_emq_cloud_event_listener: %s\r\n", task_name);
	return C_OK;
}

int32_t ya_remove_emq_cloud_event_listener(char *task_name, cloud_event_type_t event_type)
{
	ya_emq_cloud_event_callbackhandler_t *list_node = NULL, *pre_node = NULL;

	if(!task_name)
		return C_ERROR;

	list_node = ya_emq_cloud_callback_list;
	pre_node = list_node;
		
	while(list_node)
	{
		if(list_node->task_name)
		{
			if(strcmp(list_node->task_name, task_name) == 0 && list_node->event_type == event_type)
				break;
		}

		if(!(list_node->ya_emq_cloud_event_callbackhandler_next))
			return C_ERROR;
		else
		{
			pre_node = list_node;
			list_node = list_node->ya_emq_cloud_event_callbackhandler_next;
		}
	}

	if(list_node)
		return C_ERROR;

	if(list_node == ya_emq_cloud_callback_list && ya_emq_cloud_callback_list->ya_emq_cloud_event_callbackhandler_next == NULL)
		ya_emq_cloud_callback_list = NULL;
	else
	{
		if(list_node == ya_emq_cloud_callback_list)
			ya_emq_cloud_callback_list = list_node->ya_emq_cloud_event_callbackhandler_next;
		else
			pre_node->ya_emq_cloud_event_callbackhandler_next = list_node->ya_emq_cloud_event_callbackhandler_next;
	}
	
	if(list_node->task_name)
	{
		ya_hal_os_memory_free(list_node->task_name);
		list_node->task_name = NULL;
	}
	
	if(list_node)
		ya_hal_os_memory_free(list_node);

	ya_printf(C_LOG_INFO,"listener: %s, event: %d\r\n", task_name, event_type);

	return C_OK;
}

int32_t ya_trigger_emq_cloud_event_listener(uint8_t event_type, uint8_t *data, uint16_t data_len)
{ 
	ya_emq_cloud_event_callbackhandler_t *list_node = NULL;
	list_node = ya_emq_cloud_callback_list;
		
	while(list_node)
	{
		if(list_node->task_name)
		{
			if(list_node->event_type == event_type)
			{
				list_node->ya_cloud_event_handler(data, data_len);
			}
		}

		if(!(list_node->ya_emq_cloud_event_callbackhandler_next))
			return C_OK;
		else
		{
			list_node = list_node->ya_emq_cloud_event_callbackhandler_next;
		}
	}

	return C_OK;
}

void ya_emq_disconnectCallbackHandler(MQTTClient *pClient, void *data)
{
	ya_emq_cloud_state = EMQ_CONNECT_ERROR;	
}

static int32_t ya_send_cloud_status(uint8_t cloud_status)
{	
	uint8_t buf[1];
	buf[0] = cloud_status;
	return ya_trigger_emq_cloud_event_listener(CLOUD_ONOFF_EVENT, buf, 1);
}


int32_t ya_emq_subscribe_event_transfer(uint8_t *buf, uint16_t data_len)
{
	cJSON *cmd = NULL, *method = NULL;

	cmd = cJSON_Parse((char *)buf);
	if(!cmd)
		goto err;

	method = cJSON_GetObjectItem(cmd, "method");
	if(!method)
		goto err;

	if(strstr(method->valuestring, "set"))
	{
		ya_trigger_emq_cloud_event_listener(CLOUD_SET_EVENT, buf, data_len);
	}else if(strstr(method->valuestring, "upgrade"))
	{
		ya_trigger_emq_cloud_event_listener(CLOUD_UPGRADE_EVENT, buf, data_len);
	}else if(strstr(method->valuestring, "unregister"))
	{
		ya_send_cloud_status(YA_CLOUD_DEBIND);
	}

	if(cmd)
		cJSON_Delete(cmd);

	return C_OK;

	err:

	if(cmd)
		cJSON_Delete(cmd);

	return C_ERROR;	
}

static void ya_emq_messageHandler(MessageData *emq_data)
{
	int32_t ret = -1;
	msg_t ms_msg;
	char *p = NULL;
	uint8_t *buff = NULL;
	char *topic_get = NULL;
	uint16_t msg_id_len = 0;
	
	char *payload = (char *)emq_data->message->payload;
	
	topic_get = (char *)ya_hal_os_memory_alloc(emq_data->topicName->lenstring.len + 1);
	memset(topic_get, 0, emq_data->topicName->lenstring.len + 1);
	memcpy(topic_get, emq_data->topicName->lenstring.data, emq_data->topicName->lenstring.len);
	payload[emq_data->message->payloadlen] = '\0';

	ya_printf(C_LOG_INFO,"rece topic %s\r\n", topic_get);
	ya_printf(C_LOG_INFO,"rece buffer %s\r\n", payload);

	//get the messige id
	p = strstr(topic_get, "/request/");

	if(p)
	{
		p = p + strlen("/request/");
		msg_id_len = strlen(p);
		if(msg_id_len)
		{
			buff = (uint8_t *)ya_hal_os_memory_alloc(msg_id_len + 1);
			memset( buff, 0, (msg_id_len + 1));
			memcpy( buff, p, msg_id_len);

			memset(&ms_msg, 0, sizeof(msg_t));
			ms_msg.addr = buff;
			ms_msg.len = (msg_id_len + 1);
			ms_msg.type = YA_PUBLISH_RESPONSE;

			ret = ya_hal_os_queue_send(&ya_emq_cloud_msg_queue, &ms_msg, 10);
			if(ret != C_OK)
			{
				ya_printf(C_LOG_ERROR,"cloud queue error\r\n");

				if(ms_msg.addr)
					ya_hal_os_memory_free(ms_msg.addr);

				if(topic_get)
					ya_hal_os_memory_free(topic_get);

				return;
			}
		}

		ya_emq_subscribe_event_transfer(emq_data->message->payload, emq_data->message->payloadlen);
		
	}else
	{
		ya_printf(C_LOG_ERROR,"topic error\r\n");
	}	

	if(topic_get)
		ya_hal_os_memory_free(topic_get);

	return;
}

static int32_t ya_get_subscribe_topic(void)
{
	const char *fmt = "/%s/rrpc/%s/request/+";
    int topic_len = 0;
	char *pClientId = NULL, *pthingType = NULL;

	pClientId = ya_get_client_id();
	pthingType = ya_get_thing_type();

	if (pClientId && pthingType)
	{
	    topic_len = strlen(fmt) + strlen(pClientId) + strlen(pthingType) + 1;
	    subscribe_topic = ya_hal_os_memory_alloc(topic_len);

	   if (subscribe_topic == NULL) {
			ya_printf(C_LOG_ERROR, "memory not enough\r\n");
			return C_ERROR;
	    }
		
	    memset(subscribe_topic, 0, topic_len);
	    snprintf(subscribe_topic, topic_len, fmt, pthingType, pClientId);
		return C_OK;
	}

	return C_ERROR;
}

int ya_emq_subscribe(MQTTClient* client)
{
    int rc = 0;
	ya_printf(C_LOG_INFO, "subscribe topic is: %s\r\n", subscribe_topic);
	
	rc = MQTTSubscribe(client, subscribe_topic, QOS0, ya_emq_messageHandler);
	if(0 != rc) {
		ya_printf(C_LOG_ERROR, "Error subscribing : %d\r\n", rc);
	}

	return rc;
}

//finish the publish ack
int ya_emq_publish_ack(MQTTClient* client, char *msgid, char *buf)
{
	// /%s/rrpc/%s/response/{meesageId}
	int rc = 0;
	MQTTMessage paramsQOS0;
	char *pClientId = NULL;

	const char *fmt = "/%s/rrpc/%s/response/";
	char *topic = NULL;
	int topic_len = 0;

	pClientId = ya_get_client_id();
    topic_len = strlen(fmt) + strlen(pClientId) + strlen(ya_get_thing_type()) + strlen(msgid) + 1 ;
    topic = ya_hal_os_memory_alloc(topic_len);
    if (topic == NULL) 
	{
       ya_printf(C_LOG_ERROR, "memory not enough\r\n");
       goto err;
    }

    memset(topic, 0, topic_len);
    snprintf(topic, topic_len, fmt, ya_get_thing_type(), pClientId);
	memcpy(topic+strlen(topic), msgid, strlen(msgid));

	memset(&paramsQOS0, 0, sizeof(MQTTMessage));
	paramsQOS0.qos = QOS0;
	paramsQOS0.payload = (void *) buf;
	paramsQOS0.payloadlen = strlen(buf);
	paramsQOS0.retained = 0;

	ya_printf(C_LOG_INFO,"send ack topic %s\r\n", topic);
	ya_printf(C_LOG_INFO,"send buffer %s\r\n", buf);

	rc = emq_MQTTPublish(client, topic, &paramsQOS0);
	if (rc != 0) 
	{
		ya_printf(C_LOG_ERROR, "QOS0 publish ack not received.\r\n");
		 goto err;
	}

	ya_hal_os_memory_free(topic);
	return C_OK;
	
	err:
	ya_hal_os_memory_free(topic);
    return C_ERROR;
}

int32_t ya_report_msg_to_emq_cloud(uint8_t *data, uint16_t data_len)
{
	int32_t ret = -1;
	uint8_t *buf = NULL;
	msg_t ms_msg;
	
	buf = (uint8_t *)ya_hal_os_memory_alloc(data_len + 1);
	memset( buf, 0, (data_len + 1));
	memcpy( buf, data, data_len);
	
	memset(&ms_msg, 0, sizeof(msg_t));
	ms_msg.addr = buf;
	ms_msg.len = (data_len + 1);
	ms_msg.type = YA_HARDWARE_REPORT;
	
	ret = ya_hal_os_queue_send(&ya_emq_cloud_msg_queue, &ms_msg, 10);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR,"cloud queue error\n");
	
		if(ms_msg.addr)
			ya_hal_os_memory_free(ms_msg.addr);
	
		return -1;
	}
	
	return 0;
}


int ya_emq_report(MQTTClient* client, char *buf)
{
	// /productKey/deviceName/update
	int rc = 0;
	MQTTMessage paramsQOS0;
	char *pClientId = NULL;

	const char *fmt = "/%s/%s/update";
	char *topic = NULL;
	int topic_len = 0;

	pClientId = ya_get_client_id();
    topic_len = strlen(fmt) + strlen(pClientId) + strlen(ya_get_thing_type()) + 1 ;
    topic = ya_hal_os_memory_alloc(topic_len);
    if (topic == NULL) 
	{
       ya_printf(C_LOG_ERROR, "memory not enough\r\n");
       goto err;
    }

    memset(topic, 0, topic_len);
    snprintf(topic, topic_len, fmt, ya_get_thing_type(), pClientId);

	memset(&paramsQOS0, 0, sizeof(MQTTMessage));

	paramsQOS0.qos = QOS0;
	paramsQOS0.payload = (void *) buf;
	paramsQOS0.payloadlen = strlen(buf);
	paramsQOS0.retained = 0;

	ya_printf(C_LOG_INFO,"send topic %s\r\n", topic);
	ya_printf(C_LOG_INFO,"send buffer %s\r\n", buf);

	rc = emq_MQTTPublish(client, topic, &paramsQOS0);
	if (rc != 0) 
	{
		ya_printf(C_LOG_ERROR, "QOS0 publish not received.\r\n");
		 goto err;
	}

	if(topic)
		ya_hal_os_memory_free(topic);
	
	return C_OK;
	
	err:
	if(topic)
		ya_hal_os_memory_free(topic);

    return C_ERROR;

}

static int32_t ya_updata_device_version(void)
{
	cJSON *cmd = NULL, *property = NULL;
	char *data = NULL;

	char value[64+1] = {0};
	
	cmd = cJSON_CreateObject();
	if(!cmd)
		return C_ERROR;

	property = cJSON_CreateObject();
	if(!property)
	{
		if(cmd)
			cJSON_Delete(cmd);
		return C_ERROR;
	}

	cJSON_AddStringToObject(cmd, "method", "thing.service.device.bootInfo.report");
	cJSON_AddItemToObject(cmd, "property", property);

	cJSON_AddStringToObject(property, "startType", "2");

	memset(value, 0, 65);
	ya_get_ver_string(value);
	cJSON_AddStringToObject(property, "version", value);

	memset(value, 0, 65);
	ya_get_mcu_ver_string(value);
	if(value[0] != 0)
		cJSON_AddStringToObject(property, "mcuVersion", value);
	
	ya_get_mac_addr_string(value);
	cJSON_AddStringToObject(property, "mac", value);
	cJSON_AddStringToObject(property, "type", "wifi");

	data = cJSON_PrintUnformatted(cmd);	

	if(data)
	{
		ya_report_msg_to_emq_cloud((uint8_t *)data, strlen(data));
		ya_hal_os_memory_free(data);
	}

	if(cmd)
		cJSON_Delete(cmd);

	return C_OK;
}

static int32_t ya_updata_debind_information(void)
{
	cJSON *cmd = NULL, *property = NULL;
	char *data = NULL;

	cmd = cJSON_CreateObject();
	if(!cmd)
		return C_ERROR;

	property = cJSON_CreateObject();
	if(!property)
	{
		if(cmd)
			cJSON_Delete(cmd);
		return C_ERROR;
	}

	cJSON_AddStringToObject(cmd, "method", "thing.service.device.allow.bind");
	cJSON_AddItemToObject(cmd, "property", property);

	cJSON_AddStringToObject(property, "bind", "1");
	cJSON_AddStringToObject(cmd, "productKey", ya_emq_get_thing_type());
	cJSON_AddStringToObject(cmd, "deviceName", ya_emq_get_client_id());

	data = cJSON_PrintUnformatted(cmd);	

	if(data)
	{
		ya_report_msg_to_emq_cloud((uint8_t *)data, strlen(data));
		ya_hal_os_memory_free(data);
	}

	if(cmd)
		cJSON_Delete(cmd);

	return C_OK;
}

static int32_t ya_updata_random_information(void)
{
	int ret = -1;
	cJSON *cmd = NULL, *property = NULL;
	char *data = NULL;
	char random[33];

	memset(random, 0, 33);
	ret = ya_get_randomnum(random);

	if (ret == -1)
		return C_ERROR;

	ya_clear_randomnum();

	cmd = cJSON_CreateObject();
	if(!cmd)
		return C_ERROR;

	property = cJSON_CreateObject();
	if(!property)
	{
		if(cmd)
			cJSON_Delete(cmd);
		return C_ERROR;
	}

	cJSON_AddStringToObject(cmd, "method", "thing.service.device.bindToken.report");
	cJSON_AddItemToObject(cmd, "property", property);

	cJSON_AddStringToObject(property, "bindToken", random);
	cJSON_AddStringToObject(cmd, "productKey", ya_emq_get_thing_type());
	cJSON_AddStringToObject(cmd, "deviceName", ya_emq_get_client_id());

	data = cJSON_PrintUnformatted(cmd);	

	if(data)
	{
		ya_report_msg_to_emq_cloud((uint8_t *)data, strlen(data));
		ya_hal_os_memory_free(data);
	}

	if(cmd)
		cJSON_Delete(cmd);

	return C_OK;
}


int ya_emq_gen_ack_publish_and_send(MQTTClient* client, char *msgid)
{
	int32_t ret = -1;
	cJSON *emq_ack = NULL;
	char *buf = NULL;

	emq_ack = cJSON_CreateObject();

	if(!emq_ack)
		goto err;

	cJSON_AddStringToObject(emq_ack, "message", "success");
	cJSON_AddNumberToObject(emq_ack, "code", 0);

	buf = cJSON_PrintUnformatted(emq_ack);	
	
	ret = ya_emq_publish_ack(client, msgid, buf);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR,"ya_emq_publish_ack error\n");
		goto err;
	}

	if(emq_ack)
		cJSON_Delete(emq_ack);

	if(buf)
		ya_hal_os_memory_free(buf);

	return C_OK;
	
	err:
	if(emq_ack)
		cJSON_Delete(emq_ack);

	if(buf)
		ya_hal_os_memory_free(buf);

	return C_ERROR;
}


int ya_emq_cloud_connect(MQTTClient *client) 
{
	int rc = -1;

	MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;

	ya_printf(C_LOG_INFO, "ya_emq_cloud_connect\r\n");

	NetworkInit(&emq_network);
	MQTTClientInit(client, &emq_network, CMD_TIMOUT, emq_send_buf, EMQ_SEND_BUF, emq_rece_buf, EMQ_RECE_BUF);

	if ((rc = NetworkConnect(&emq_network, EMQ_DOMAIN, EMQ_PORT)) != 0) {
		ya_printf(C_LOG_ERROR, "Return code from emq_network connect is %d\r\n", rc);
		return rc;
	}
	
	connectData.MQTTVersion = 4;
	connectData.clientID.cstring = ya_emq_get_client_id();
	connectData.keepAliveInterval = EMQ_PING_INTERVAL;	

	ya_printf(C_LOG_INFO, "emq Connecting...\r\n");
	rc = emq_MQTTConnect(client, &connectData);
	if(0 != rc) {
		ya_printf(C_LOG_ERROR, "Error connect to emq cloud: %d\r\n", rc);
		return rc;
	}

	ya_printf(C_LOG_INFO, "Success and then, Subscribing...\r\n");
	
	rc = ya_emq_subscribe(client);
	if(0 != rc) {
		ya_printf(C_LOG_INFO, "Error subscribing : %d\r\n", rc);
		return rc;
	}

	ya_printf(C_LOG_INFO, "subscribe success\r\n");
	return rc;
}


int32_t ya_emq_get_cloud_status(void)
{
	if(ya_cloud_connected == 1)
		return 1;

	return 0;
}

static void ya_cloud_app(void *arg)
{
	uint16_t count = 0;
	int32_t ret = -1;
	msg_t ms_msg;
	Ya_Timer ya_emq_cloud_timer;

	ya_get_subscribe_topic();
	ya_cloud_connected = 0;
	memset(&emq_client, 0, sizeof(MQTTClient));
	
	while(1)
	{
		if(ya_get_app_status() == YA_APP_CONNECTED && ya_emq_cloud_state == EMQ_CLOUD_INIT)
		{
			ya_emq_cloud_state = EMQ_TO_CONNECT_CLOUD;
		}else if(ya_get_app_status() != YA_APP_CONNECTED && ya_emq_cloud_state != EMQ_CLOUD_INIT)
		{
			ret = MQTTDisconnect(&emq_client);
			if(ret != 0)
				ya_printf(C_LOG_ERROR,"emq_iot_mqtt_disconnect error: %d\r\n", ret);

			ya_printf_remain_heap();
			ya_cloud_connected = 0;
			ya_emq_cloud_state = EMQ_CLOUD_INIT;
		}


		switch(ya_emq_cloud_state)
		{
			case EMQ_CLOUD_INIT:
			break;

			case EMQ_TO_CONNECT_CLOUD:
				memset(&emq_client, 0, sizeof(MQTTClient));
				ret = ya_emq_cloud_connect(&emq_client);
				if(ret != C_OK)
				{
					ya_emq_cloud_state = EMQ_CONNECT_ERROR;
				}
				else
				{
					ya_cloud_connected = 1;
					ya_emq_cloud_state = EMQ_CONNECTED_CLOUD;
					ya_send_cloud_status(YA_CLOUD_ONLINE);

					//update the device version
					if(ya_get_debind_enable())
					{
						ya_debind_disable();
						ya_updata_debind_information();
					}

					ya_updata_random_information();
					
					ya_updata_device_version();
					ya_printf_remain_heap();					
					ya_printf(C_LOG_INFO, "connect emq cloud success\r\n");
				}
			break;

			case EMQ_CONNECTED_CLOUD:
				
			break;

			case EMQ_CONNECT_ERROR:
				if(ya_cloud_connected)
				{
					ya_cloud_connected = 0;
					ya_send_cloud_status(YA_CLOUD_OFFLINE);
				}
				ya_init_timer(&ya_emq_cloud_timer);
				ya_countdown_ms(&ya_emq_cloud_timer, 5000);

				ret = MQTTDisconnect(&emq_client);
				if(ret != 0)
					ya_printf(C_LOG_ERROR,"emq_iot_mqtt_disconnect error\r\n");
				
				ya_printf_remain_heap();
				ya_emq_cloud_state = EMQ_RECONNECT_WAIT;
			break;
			
			case EMQ_RECONNECT_WAIT:
				if(ya_has_timer_expired(&ya_emq_cloud_timer) == C_OK)
				{
					ya_printf(C_LOG_INFO, "wait reconnect ok\r\n");
					ya_emq_cloud_state = EMQ_TO_CONNECT_CLOUD;
				}
			break;

			default:

			break;
		}

		if(ya_emq_cloud_state == EMQ_CONNECTED_CLOUD)
		{
			ret = MQTTYield(&emq_client, 100);
			if(ret != 0) 
			{
				ya_printf(C_LOG_ERROR, "yield error: %d\r\n", ret);
				ya_emq_cloud_state = EMQ_CONNECT_ERROR;
			}else
			{
				if(count >=  100)
				{
					ya_printf(C_LOG_INFO, "emq yielding\r\n");
					count = 0;
				}else
					count++;
			}
		}
		
		memset(&ms_msg, 0, sizeof(msg_t));
		ret = ya_hal_os_queue_recv(&ya_emq_cloud_msg_queue, &ms_msg, 20);

		if(ret == C_OK)
		{
			ya_printf(C_LOG_INFO, "[C-T]: %02x\r\n",ms_msg.type);
			ya_printf_remain_heap();

			if(ya_cloud_connected)
			{
				switch(ms_msg.type)
				{
					case YA_PUBLISH_RESPONSE:
						ret = ya_emq_gen_ack_publish_and_send(&emq_client, (char *)ms_msg.addr);
						if(ret != C_OK)
						{
							ya_printf(C_LOG_ERROR,"ya_emq_gen_ack_publish_and_send error\r\n");
						}
					break;

					case YA_HARDWARE_REPORT:
						ret = ya_emq_report(&emq_client, (char *)ms_msg.addr);
						if(ret != C_OK)
						{
							ya_printf(C_LOG_ERROR,"ya_emq_report error\r\n");
						}
					break;

					default:

					break;
				}
			}
			if(ms_msg.addr)
				ya_hal_os_memory_free(ms_msg.addr);
		}
	}

}

int32_t ya_start_cloud_emq_app()
{
	int32_t ret = 0;

	emq_send_buf = (uint8_t *)ya_hal_os_memory_alloc(EMQ_SEND_BUF);

	if (!emq_send_buf)
		return C_ERROR;

	emq_rece_buf = (uint8_t *)ya_hal_os_memory_alloc(EMQ_RECE_BUF);

	if (!emq_rece_buf)
		return C_ERROR;

	ret = ya_hal_os_queue_create(&ya_emq_cloud_msg_queue, "ya emq hardware queue", sizeof(msg_t), MSG_QUEUE_LENGTH);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create os queue error\n");
		return C_ERROR;
	}

	ret = ya_hal_os_thread_create(&ya_emq_app_cloud, "ya_emq_app_main_thread", ya_cloud_app, 0, (8*1024), 5);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create ya_emq_app_main error\n");
		return C_ERROR;
	}
		
	return C_OK;
}


cloud_context_t* ya_emq_cloud_create(MODULE_DOMAIN cloud_type)
{	
	emq_cloud_domain = cloud_type;

	cloud_context_t* cloud_conn = NULL;
	cloud_conn = (cloud_context_t *)ya_hal_os_memory_alloc(sizeof(cloud_context_t));

	if(cloud_conn)
	{
		cloud_conn->add_listener = &ya_add_emq_cloud_event_listener;
		cloud_conn->remove_listener = &ya_remove_emq_cloud_event_listener;
		cloud_conn->send_msg = &ya_report_msg_to_emq_cloud;
		cloud_conn->start_cloud = &ya_start_cloud_emq_app;
		cloud_conn->cloud_get_thing_name = &ya_emq_get_thing_type;
		cloud_conn->cloud_get_client_id = &ya_emq_get_client_id;
		cloud_conn->cloud_get_status  = &ya_emq_get_cloud_status;
	}
	
	return cloud_conn;
}

#endif
#endif


