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
#include "ya_common_func.h"
#include "cJSON.h"
#include "ya_config.h"
#include "ya_light_example.h"
#include "ya_light_app.h"
#include "ya_light_io.h"
#include "ya_stripLights_display.h"
#include "ya_flash.h"
#include "ya_thing_data_api.h"

#define MAX_W_COLOR  			6500 
#define MIN_W_COLOR 			2700 
#define W_COLOR_GET_VALUE(W)    ((((W)- MIN_W_COLOR) * 100)/(MAX_W_COLOR - MIN_W_COLOR))

typedef struct
{
	bool 	 switchstate;		
	uint8_t  work_mode;					
	uint8_t  white_temp;			
	uint8_t  white_bright;
	uint16_t  color[3];
	uint8_t  scene_index;
} st_light_thingModel; 


typedef struct
{
	uint8_t lightSwitch;
	en_light_work_mode  workMode;
	uint16_t corlor_H;
	uint8_t corlor_S;
	uint8_t corlor_B;
	uint8_t white_temp;
	uint8_t white_bright;
	
	st_light_sceneInfo sceneInfo;
} ya_control_workData; 

static char app_token[32+1] = {0};

uint8_t ya_update_light_data_to_cloud_enable = 0;
ya_hal_os_queue_t ya_light_queue = NULL;

st_light_thingModel ya_light_thing_mode;
ya_control_workData cur_control_data;
ya_control_workData new_control_data;
ya_display_stripsLight_t ya_display_value_control;
st_ya_light_workData ya_light_workData;

void ya_light_app_SceneInit(int scene,st_light_sceneInfo *pSceneInfo)
{
	st_light_sceneInfo initSceneInfo[SCENE_MAX]=
	{	
		{2,  SCENE_READING,     	STATIC_TYPE,  0,  1,  {{COLORTYPE_WHITE,0,0,0,W_COLOR_GET_VALUE(4500), 75}}},
		{2,  SCENE_WORK,  			STATIC_TYPE,  0,  1,  {{COLORTYPE_WHITE,0,0,0,W_COLOR_GET_VALUE(3000), 80}}},
		{2,  SCENE_GOOD_NIGHT,  	STATIC_TYPE,  0,  1,  {{COLORTYPE_WHITE,0,0,0,W_COLOR_GET_VALUE(6000), 10}}},
		{2,  SCENE_LEISURE,     	STATIC_TYPE,  0,  1,  {{COLORTYPE_WHITE,0,0,0,W_COLOR_GET_VALUE(3500), 50}}},		
	};

	if (scene < SCENE_MAX)
	{
		memcpy(pSceneInfo,&initSceneInfo[scene],sizeof(st_light_sceneInfo));
	} else
	{
		memcpy(pSceneInfo,&initSceneInfo[SCENE_READING],sizeof(st_light_sceneInfo));
	}
}


int32_t ya_light_app_sceneSave(void)
{
	int32_t ret = -1;

	if (ya_light_workData.lightSwitch != 0)
	{
		ret= ya_write_flash(YA_LIGHT_DATA_ADDR, (uint8_t *)&ya_light_workData,sizeof(st_ya_light_workData),1, FLASH_AES_DISABLE);
	} 
	
	if(ret == 0)
	{
		ya_printf(C_LOG_INFO, "light scene save ok\r\n");
		ya_printf_remain_heap();
	}
	return ret;
}

int32_t ya_light_app_sceneRead(st_ya_light_workData *pya_light_flashData,int len)
{
	int32_t ret = -1;
	uint16_t flash_read_len = len;
	
	ret = ya_read_flash_with_var_len(YA_LIGHT_DATA_ADDR, (uint8_t *)pya_light_flashData, &flash_read_len, 1, FLASH_AES_DISABLE);
	
	if(ret == 0)
	{
		ya_printf(C_LOG_INFO, "light scene read ok\r\n");
	}

	return ret;
}

void ya_clear_user_data(void)
{
	ya_erase_flash(YA_LIGHT_DATA_ADDR,sizeof(st_ya_light_workData));	 
}

bool ya_get_updata_light(void)
{
	return ya_update_light_data_to_cloud_enable;
}	

void ya_clear_updata_light(void)
{
	ya_update_light_data_to_cloud_enable = 0;
}

void ya_get_cur_thing_model(st_light_thingModel *thing_mode)
{
	thing_mode->switchstate = cur_control_data.lightSwitch;
	thing_mode->work_mode = cur_control_data.workMode;
	thing_mode->white_temp = cur_control_data.white_temp;
	thing_mode->white_bright = cur_control_data.white_bright;

	thing_mode->color[0] = cur_control_data.corlor_H;		
	thing_mode->color[1] = cur_control_data.corlor_S;
	thing_mode->color[2] = cur_control_data.corlor_B;

	thing_mode->scene_index = cur_control_data.sceneInfo.sceneIndex;
}

void  ya_light_app_updatePwm(st_ya_light_workData *pworkInfo, uint8_t save_flag)
{
	memset(&new_control_data, 0, sizeof(ya_control_workData));

	new_control_data.lightSwitch = pworkInfo->lightSwitch;
	new_control_data.workMode = pworkInfo->workMode;
	new_control_data.corlor_H = pworkInfo->corlor_H;
	new_control_data.corlor_S = pworkInfo->corlor_S;
	new_control_data.corlor_B = pworkInfo->corlor_B;
	new_control_data.white_temp = pworkInfo->white_temp;
	new_control_data.white_bright = pworkInfo->white_bright;

	memcpy(&new_control_data.sceneInfo, &(pworkInfo->sceneInfo[pworkInfo->cur_scene_index]), sizeof(st_light_sceneInfo));
	
	if(memcmp(&cur_control_data, &new_control_data, sizeof(ya_control_workData)) == 0)
		return;
	else
	{		
		memcpy(&cur_control_data, &new_control_data, sizeof(ya_control_workData));
		memset(&ya_display_value_control,0,sizeof(ya_display_value_control));

		if (cur_control_data.lightSwitch == 1)
		{
			if (cur_control_data.workMode == WORKMODE_WHITE)
			{
				ya_display_value_control.groupNum = 1;
				ya_display_value_control.changeSpeed = 0;
				ya_display_value_control.changeType = STATIC_TYPE;
				ya_display_value_control.sceneIndex = 0;
				ya_display_value_control.colorInfo[0].type = COLORTYPE_WHITE;
				ya_display_value_control.colorInfo[0].white_temp = cur_control_data.white_temp;
				ya_display_value_control.colorInfo[0].white_bright = cur_control_data.white_bright;
			}
			else if (cur_control_data.workMode == WORKMODE_COLOR)
			{
				ya_display_value_control.groupNum = 1;
				ya_display_value_control.changeSpeed = 0;
				ya_display_value_control.changeType = STATIC_TYPE;
				ya_display_value_control.sceneIndex = 0;
				ya_display_value_control.colorInfo[0].type = COLORTYPE_COLOR;
				ya_display_value_control.colorInfo[0].color_H = cur_control_data.corlor_H;
				ya_display_value_control.colorInfo[0].color_S = cur_control_data.corlor_S;
				ya_display_value_control.colorInfo[0].color_B = cur_control_data.corlor_B;				
			}
			else if (cur_control_data.workMode == WORKMODE_SCENE)
			{
				memcpy(&ya_display_value_control, &cur_control_data.sceneInfo, sizeof(st_light_sceneInfo));
			}
			else
				return;
		}
		else
		{
			ya_display_value_control.cmd = 0xFF;
			ya_display_value_control.groupNum = 1;
			ya_display_value_control.changeSpeed = 0;
			ya_display_value_control.changeType = STATIC_TYPE;			
		}
		
		//save data here
		if (save_flag)
			ya_light_app_sceneSave();

		ya_update_light_data_to_cloud_enable = 1; 
		ya_stripLights_pwmUpdate_into_queue((uint8_t *)&ya_display_value_control, sizeof(ya_display_stripsLight_t));
	}
}

void ya_light_app_cloud_event_into_queue(uint8_t *buf, uint16_t len)
{
	int32_t ret = -1;
	msg_t msg;
	memset(&msg, 0, sizeof(msg_t)); 		
	msg.addr = (uint8_t *)ya_hal_os_memory_alloc(len + 1);
	if (!msg.addr)
		return;
	
	memset(msg.addr, 0, len + 1);
	memcpy(msg.addr, buf, len);
	msg.len = len + 1;

	ret = ya_hal_os_queue_send(&ya_light_queue, &msg, 0);
	if (ret != C_OK)
	{
		if (msg.addr)
			ya_hal_os_memory_free(msg.addr);
	}
}

int32_t ya_light_cloud_attriReport_All(void)
{
	int32_t ret = -1;
	cJSON *property = NULL;
	char *buf = NULL;
	
	property = cJSON_CreateObject();
	if(!property)
		return -1;

	ya_get_cur_thing_model(&ya_light_thing_mode);

	cJSON_AddStringToObject(property, "Switch", ya_int_to_string(ya_light_thing_mode.switchstate));
	cJSON_AddStringToObject(property, "WorkMode", ya_int_to_string(ya_light_thing_mode.work_mode));	
	cJSON_AddStringToObject(property, "ColorTemperature", ya_int_to_string(ya_light_thing_mode.white_temp));
	cJSON_AddStringToObject(property, "Luminance", ya_int_to_string(ya_light_thing_mode.white_bright));

	#if (LIGHT_TYPE == 0)
	cJSON_AddStringToObject(property, "Hue",  ya_int_to_string(ya_light_thing_mode.color[0]));
	cJSON_AddStringToObject(property, "Saturation",  ya_int_to_string(ya_light_thing_mode.color[1]));
	cJSON_AddStringToObject(property, "Brightness",  ya_int_to_string(ya_light_thing_mode.color[2]));
	#endif
	
	cJSON_AddStringToObject(property, "LightScene", ya_int_to_string(ya_light_thing_mode.scene_index));

	buf = cJSON_PrintUnformatted(property);	
	if(buf)
	{
		ret = ya_thing_report_to_cloud((uint8_t *)buf, strlen(buf));
		if(ret != 0)
			ya_printf(C_LOG_ERROR, "ya_thing_to_cloud_translate error\n");

		ya_hal_os_memory_free(buf);
	}

	if(property)
		cJSON_Delete(property);

	return 0;
}


int32_t ya_light_cloud_attriReport(void)
{
	int32_t ret = -1;
	cJSON *property = NULL;
	char *buf = NULL;
	
	property = cJSON_CreateObject();
	if(!property)
		return -1;

	ya_get_cur_thing_model(&ya_light_thing_mode);
	
	if (app_token[0] != 0)
	{
		cJSON_AddStringToObject(property, "appToken", app_token);
		memset(app_token, 0, 32+1);
	}

	cJSON_AddStringToObject(property, "Switch", ya_int_to_string(ya_light_thing_mode.switchstate));
	if (ya_light_thing_mode.switchstate)
	{
		cJSON_AddStringToObject(property, "WorkMode", ya_int_to_string(ya_light_thing_mode.work_mode));	
		switch (ya_light_thing_mode.work_mode)
		{
			case WORKMODE_WHITE:
				cJSON_AddStringToObject(property, "ColorTemperature", ya_int_to_string(ya_light_thing_mode.white_temp));
				cJSON_AddStringToObject(property, "Luminance", ya_int_to_string(ya_light_thing_mode.white_bright));
				break;

			case WORKMODE_COLOR:
				cJSON_AddStringToObject(property, "Hue",  ya_int_to_string(ya_light_thing_mode.color[0]));
				cJSON_AddStringToObject(property, "Saturation",  ya_int_to_string(ya_light_thing_mode.color[1]));
				cJSON_AddStringToObject(property, "Brightness",  ya_int_to_string(ya_light_thing_mode.color[2]));
				break;			

			case WORKMODE_SCENE:
				cJSON_AddStringToObject(property, "LightScene", ya_int_to_string(ya_light_thing_mode.scene_index));
				break;

			default:
				break;
		}

	}

	buf = cJSON_PrintUnformatted(property);	
	if(buf)
	{
		ret = ya_thing_report_to_cloud((uint8_t *)buf, strlen(buf));
		if(ret != 0)
			ya_printf(C_LOG_ERROR, "ya_thing_to_cloud_translate error\n");

		ya_hal_os_memory_free(buf);
	}

	if(property)
		cJSON_Delete(property);

	return 0;

}

void ya_light_app_cloud_handle(uint8_t *buf, uint16_t len)
{
	st_ya_light_workData *pworkInfo = &ya_light_workData;
	st_light_sceneInfo *psceneInfo = NULL;

	uint32_t value = 0;
	cJSON *root = NULL, *json_key = NULL;

	ya_printf_remain_heap();
	ya_get_cur_thing_model(&ya_light_thing_mode);
	root = cJSON_Parse((char *)buf);
	if (!root) return;

	memset(app_token, 0, 32+1);
	json_key = cJSON_GetObjectItem(root, "appToken");
	if (json_key && json_key->type == cJSON_String)
	{
		if (strlen(json_key->valuestring) < (32+1))
			strcpy(app_token, json_key->valuestring);
	}

	json_key = cJSON_GetObjectItem(root, "Switch");

	if (json_key && json_key->type == cJSON_String)
	{
		value = atoi(json_key->valuestring);
		if (value > 0)
			ya_light_thing_mode.switchstate = 1;
		else
			ya_light_thing_mode.switchstate = 0;
	} 
	else
	{

		json_key = cJSON_GetObjectItem(root, "WorkMode");
		if (json_key && json_key->type == cJSON_String)
		{
			ya_light_thing_mode.switchstate = 1;
			value = atoi(json_key->valuestring);
			if (value < WORKMODE_MAX)
				ya_light_thing_mode.work_mode = atoi(json_key->valuestring);

			#if (LIGHT_TYPE == 1)
			if (value == WORKMODE_COLOR)
				ya_light_thing_mode.work_mode = WORKMODE_WHITE;
			#endif
		} 

		json_key = cJSON_GetObjectItem(root, "ColorTemperature");
		if (json_key && json_key->type == cJSON_String)
		{
			value = atoi(json_key->valuestring);
			if (value <= 100)
			{
				ya_light_thing_mode.white_temp = atoi(json_key->valuestring);
				ya_light_thing_mode.work_mode = WORKMODE_WHITE;
				ya_light_thing_mode.switchstate = 1;
			}
		} 		

		json_key = cJSON_GetObjectItem(root, "Luminance");
		if (json_key && json_key->type == cJSON_String)
		{
			value = atoi(json_key->valuestring);
			if (value <= 100)
			{
				ya_light_thing_mode.white_bright = atoi(json_key->valuestring);
				ya_light_thing_mode.work_mode = WORKMODE_WHITE;
				ya_light_thing_mode.switchstate = 1;
			}
		} 

		#if (LIGHT_TYPE == 0)
		json_key = cJSON_GetObjectItem(root, "Hue");
		if (json_key && json_key->type == cJSON_String)
		{
			ya_light_thing_mode.color[0] = atoi(json_key->valuestring);
			ya_light_thing_mode.switchstate = 1;
			ya_light_thing_mode.work_mode = WORKMODE_COLOR;
		}
		json_key = cJSON_GetObjectItem(root, "Saturation");
		if (json_key && json_key->type == cJSON_String)
		{
			ya_light_thing_mode.color[1] = atoi(json_key->valuestring);
			ya_light_thing_mode.switchstate = 1;
			ya_light_thing_mode.work_mode = WORKMODE_COLOR;
		}
		json_key = cJSON_GetObjectItem(root, "Brightness");
		if (json_key && json_key->type == cJSON_String)
		{
			ya_light_thing_mode.color[2] = atoi(json_key->valuestring);
			ya_light_thing_mode.switchstate = 1;
			ya_light_thing_mode.work_mode = WORKMODE_COLOR;
		}
		#endif

		json_key = cJSON_GetObjectItem(root, "LightScene");
		if (json_key && json_key->type == cJSON_String)
		{
			ya_light_thing_mode.scene_index = atoi(json_key->valuestring);
			ya_light_thing_mode.work_mode = WORKMODE_SCENE;
			ya_light_thing_mode.switchstate = 1;
		}
	
	}
	
	ya_printf(C_LOG_INFO,"s: %d, w: %d, l_w: %d, l_b: %d, l_h: %d, l_s: %d, l_c: %d, l_sc: %d\r\n",
	ya_light_thing_mode.switchstate,
	ya_light_thing_mode.work_mode,
	ya_light_thing_mode.white_temp,
	ya_light_thing_mode.white_bright,
	ya_light_thing_mode.color[0],
	ya_light_thing_mode.color[1],
	ya_light_thing_mode.color[2],
	ya_light_thing_mode.scene_index);

	if (root) cJSON_Delete(root);

	pworkInfo->lightSwitch = ya_light_thing_mode.switchstate;
	pworkInfo->workMode = ya_light_thing_mode.work_mode;
	
	if(pworkInfo->lightSwitch)
	{
		switch(pworkInfo->workMode)
		{
			case WORKMODE_WHITE:
					pworkInfo->white_temp = ya_light_thing_mode.white_temp;
					pworkInfo->white_bright = ya_light_thing_mode.white_bright;
				break;
				
			case WORKMODE_COLOR:
					pworkInfo->corlor_H = ya_light_thing_mode.color[0];
					pworkInfo->corlor_S = ya_light_thing_mode.color[1];
					pworkInfo->corlor_B = ya_light_thing_mode.color[2];
				break;
				
			case WORKMODE_SCENE:
					pworkInfo->cur_scene_index = ya_light_thing_mode.scene_index;	
					psceneInfo = &pworkInfo->sceneInfo[pworkInfo->cur_scene_index];
			
					ya_light_app_SceneInit(pworkInfo->cur_scene_index, psceneInfo);
				break;

			default:
				break;
		}
 	}

	ya_light_app_updatePwm(&ya_light_workData, 1);
}

void ya_light_app_netConfigDisplay(void)
{
	ya_display_value_control.groupNum = 1;
	ya_display_value_control.changeSpeed = 30;
	ya_display_value_control.changeType = STATIC_TYPE;
	ya_display_value_control.sceneIndex = 0;
	
	ya_display_value_control.colorInfo[0].type = COLORTYPE_WHITE;
	ya_display_value_control.colorInfo[0].color_H = 0;
	ya_display_value_control.colorInfo[0].color_S = 100; 		
	ya_display_value_control.colorInfo[0].color_B = 100;
	ya_display_value_control.colorInfo[0].white_temp = 50;
	ya_display_value_control.colorInfo[0].white_bright = 50;

	ya_stripLights_pwmUpdate_into_queue((uint8_t *)&ya_display_value_control, sizeof(ya_display_stripsLight_t));
}

void ya_light_app_ConfigOkDisplay(void)
{
	ya_display_value_control.groupNum = 1;
	ya_display_value_control.changeSpeed = 30;
	ya_display_value_control.changeType = STATIC_TYPE;
	ya_display_value_control.sceneIndex = 0;
	
	ya_display_value_control.colorInfo[0].type = COLORTYPE_WHITE;
	ya_display_value_control.colorInfo[0].color_H = 0;
	ya_display_value_control.colorInfo[0].color_S = 100; 		
	ya_display_value_control.colorInfo[0].color_B = 100;
	ya_display_value_control.colorInfo[0].white_temp = 50;
	ya_display_value_control.colorInfo[0].white_bright = 100;

	ya_stripLights_pwmUpdate_into_queue((uint8_t *)&ya_display_value_control, sizeof(ya_display_stripsLight_t));
}


void ya_light_switchoff(void)
{
	memset(&ya_display_value_control, 0, sizeof(ya_display_stripsLight_t));
	ya_display_value_control.cmd = 0xFF;
	ya_display_value_control.groupNum = 1;
	ya_display_value_control.changeSpeed = 30;
	ya_display_value_control.changeType = STATIC_TYPE;
	ya_stripLights_pwmUpdate_into_queue((uint8_t *)&ya_display_value_control, sizeof(ya_display_stripsLight_t));
}

void ya_light_app_init(void)
{
	int index = 0;
	int ret = -1;

	ya_stripLights_display_start();
	memset(&ya_light_workData,0,sizeof(st_ya_light_workData));

	ret = ya_light_app_sceneRead(&ya_light_workData, sizeof(st_ya_light_workData));
	if (ret == 0)
	{
		if (ya_light_workData.lightSwitch > 1)
			ret = -1;
		else if (ya_light_workData.corlor_H > 360 || ya_light_workData.corlor_S > 100 || ya_light_workData.corlor_B > 100)
			ret = -1;
		else if (ya_light_workData.white_temp > 100 || ya_light_workData.white_bright > 100)
			ret = -1;
		else if (ya_light_workData.cur_scene_index >= 4 || ya_light_workData.workMode >= WORKMODE_MAX)
			ret = -1;
		else
		{
			for (index = 0; index < 4; index++)
			{
				if (ya_light_workData.sceneInfo[index].groupNum > 8)
				{
					ret = -1;
					break;
				}
			}
		}
	}
	
	if (ret != 0)
	{
		ya_printf(C_LOG_ERROR, "read scene data failed, then init again\n");
		memset(&ya_light_workData,0,sizeof(st_ya_light_workData));
		ya_light_workData.lightSwitch = 1;

		ya_light_workData.workMode = WORKMODE_WHITE;
		ya_light_workData.corlor_H = 0;
		ya_light_workData.corlor_S = 100;
		ya_light_workData.corlor_B = 100;
		ya_light_workData.white_temp = 50;
		ya_light_workData.white_bright = 100;	
		ya_light_workData.cur_scene_index= SCENE_READING;

		for(index=0; index<SCENE_MAX; index++)
		{
			ya_light_app_SceneInit(index, &ya_light_workData.sceneInfo[index]);
		}
	}

	ya_light_app_updatePwm(&ya_light_workData, 0);

	ya_printf(C_LOG_INFO, "end ya_light_app_updatePwm\n");
}



