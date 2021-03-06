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
#include "ya_stripLights_app.h"
#include "ya_stripLights_display.h"
#include "ya_config.h"
#include "ya_ir_app.h"
#include "ya_common_func.h"
#include "ya_stripLights_example.h"
#include "ya_ble_app.h"
#include "ya_flash.h"

#define MAX_W_COLOR  			6500 
#define MIN_W_COLOR 			2000 
#define W_COLOR_GET_VALUE(W)    ((((W)- MIN_W_COLOR) * 100)/(MAX_W_COLOR - MIN_W_COLOR))
#define YA_APPUSER_DATA_ADDR 	(YA_DEVICE_TIMER_ADDR + 0x2000)

#define SCENE_MAX_LEN	48

typedef struct
{
	bool 	 switchstate;		
	uint8_t  work_mode;					
	uint8_t  white_temp;			
	uint8_t  white_bright;
	uint16_t color_H;
	#if (STRIP_LIGHT == 1)
	uint8_t  color[3];
	#else
	uint16_t  color[3];
	#endif
	uint8_t  scene[SCENE_MAX_LEN + 1];
	uint8_t  music;
	uint8_t  mic_sensitivity;
	uint8_t  mic_rate;
} st_stripLigths_thingModel; 


typedef struct
{
	uint8_t lightSwitch;
	en_stripLigths_work_mode  workMode;
	uint16_t corlor_H;
	uint8_t corlor_S;
	uint8_t corlor_B;
	uint8_t white_temp;
	uint8_t white_bright;

	uint8_t mic_index;
	st_stripLigths_micInfo  micInfo;
	st_stripLigths_sceneInfo sceneInfo;
} ya_control_workData; 

static char app_token[32+1] = {0};

uint8_t ya_update_stripLights_data_to_cloud_enable = 0;
ya_hal_os_queue_t ya_striplight_queue = NULL;

ya_control_workData cur_control_data;
ya_control_workData new_control_data;
ya_display_stripsLight_t ya_display_value_control;
st_ya_stripLigths_workData ya_stripLigths_workData;

st_stripLigths_thingModel ya_stripLights_thing_mode;


void ya_stripLights_app_SceneInit(int scene,st_stripLigths_sceneInfo *pSceneInfo)
{
	st_stripLigths_sceneInfo initSceneInfo[SCENE_MAX]=
	{	
		#if (STRIP_LIGHT == 1)
		{2,  SCENE_READING,     	STATIC_TYPE,  0,  1,  {COLORTYPE_WHITE,0,0,0,75,W_COLOR_GET_VALUE(4500)}},
		{2,  SCENE_WORK,  			STATIC_TYPE,  0,  1,  {COLORTYPE_WHITE,0,0,0,75,W_COLOR_GET_VALUE(6000)}},
		{2,  SCENE_GOOD_NIGHT,  	STATIC_TYPE,  0,  1,  {COLORTYPE_WHITE,0,0,0,75,W_COLOR_GET_VALUE(3000)}},
		{2,  SCENE_LEISURE,     	STATIC_TYPE,  0,  1,  {COLORTYPE_WHITE,0,0,0,75,W_COLOR_GET_VALUE(3500)}},
		#else
		{2,  SCENE_READING,     	STATIC_TYPE,  0,  1,  {COLORTYPE_WHITE,0,0,0,W_COLOR_GET_VALUE(4500),75}},
		{2,  SCENE_WORK,  			STATIC_TYPE,  0,  1,  {COLORTYPE_WHITE,0,0,0,W_COLOR_GET_VALUE(3000),80}},
		{2,  SCENE_GOOD_NIGHT,  	STATIC_TYPE,  0,  1,  {COLORTYPE_WHITE,0,0,0,W_COLOR_GET_VALUE(6000),5}},
		{2,  SCENE_LEISURE,     	STATIC_TYPE,  0,  1,  {COLORTYPE_WHITE,0,0,0,W_COLOR_GET_VALUE(3500),50}},		
		#endif
		{2,  SCENE_DINNER,      	STATIC_TYPE,  0,  1,  {COLORTYPE_COLOR,0x28,0x64,0x4B,0,0}},
		{2,  SCENE_DATE,  			STATIC_TYPE,  0,  1,  {COLORTYPE_COLOR,0x28,0x64,0x32,0,0}},
		{2,  SCENE_PARTY,  			STATIC_TYPE,  0,  1,  {COLORTYPE_COLOR,0x3C,0x64,0x64,0,0}},
		{2,  SCENE_CINEMA,    		STATIC_TYPE,  0,  1,  {COLORTYPE_COLOR,0xF0,0x64,0x32,0,0}},

		{2,  SCENE_SOFT_LIGHT,      BREAK_TYPE,   90,  2,  {COLORTYPE_COLOR,0x0,0x64,0x32,0,0,COLORTYPE_COLOR,0xb4,0x64,0x32,0,0}},
		{2,  SCENE_PROFUSION, 		SHADE_TYPE,  90,  3,  {COLORTYPE_COLOR,0x0,0x64,0x3E,0,0,COLORTYPE_COLOR,0x78,0x64,0x3E,0,0,COLORTYPE_COLOR,0xf0,0x64,0x3E,0,0}},
		{2,  SCENE_DAZZLE_COLOUR,   BREAK_TYPE,  90,  4,  {COLORTYPE_COLOR,30, 100, 67,0,0,COLORTYPE_COLOR,120, 100, 83,0,0,COLORTYPE_COLOR,210, 100, 67,0,0,COLORTYPE_COLOR,297, 36, 51,0,0}},
		{2,  SCENE_COLORS,  		STEP_TYPE,   100,  6,  {COLORTYPE_COLOR,0x00,0x64,0x32,0,0,COLORTYPE_COLOR,0x78,0x64,0x32,0,0,COLORTYPE_COLOR,0xf0,0x64,0x32,0,0,COLORTYPE_COLOR,0x12c,0x64,0x32,0,0,COLORTYPE_COLOR,0xb4,0x64,0x32,0,0,COLORTYPE_COLOR,0x3C,0x64,0x32,0,0}},
	};

	if (scene < SCENE_MAX)
	{
		memcpy(pSceneInfo,&initSceneInfo[scene],sizeof(st_stripLigths_sceneInfo));
	} else
	{
		memcpy(pSceneInfo,&initSceneInfo[SCENE_SOFT_LIGHT],sizeof(st_stripLigths_sceneInfo));
	}
}


int32_t ya_stripLights_app_sceneSave(void)
{
	int32_t ret = -1;

	if (ya_stripLigths_workData.lightSwitch != 0)
	{
		ret= ya_write_flash(YA_APPUSER_DATA_ADDR, (uint8_t *)&ya_stripLigths_workData,sizeof(st_ya_stripLigths_workData),1);
	}
	
	if(ret == 0)
	{
		ya_printf(C_LOG_INFO, "striplights scene save ok\r\n");
	}
	return ret;
}

int32_t ya_stripLights_app_sceneRead(st_ya_stripLigths_workData *pya_stripLigths_flashData,int len)
{
	int i;
	int32_t ret = -1;
	
	ret = ya_read_flash_with_fix_len(YA_APPUSER_DATA_ADDR, (uint8_t *)pya_stripLigths_flashData,len,1);
	
	if(ret == 0)
	{
		ya_printf(C_LOG_INFO, "striplights scene read ok\r\n");
	}

	return ret;
}

void ya_clear_user_data(void)
{
	int32_t ret = 0;
	
	ret= ya_erase_flash(YA_APPUSER_DATA_ADDR,sizeof(st_ya_stripLigths_workData));
	
	return ret;
}


void ya_stripLights_app_localToCloud(unsigned char *pDes,st_stripLigths_colorInfo *pColorInfo, int len)
{
	int i = 0;
	int index = 0;
	for(i=0;i<len;i++)
	{
		index = i*4;
		if(pColorInfo[i].type == COLORTYPE_WHITE)
		{
			pDes[index+0] = pColorInfo[i].type;
			pDes[index+1] = 0;
			pDes[index+2] = pColorInfo[i].white_temp;
			pDes[index+3] = pColorInfo[i].white_bright;
		}
		else if(pColorInfo[i].type == COLORTYPE_COLOR)
		{

			pDes[index+0] = pColorInfo[i].type;
			pDes[index+1] = (pColorInfo[i].color_H * 100)/360;
			pDes[index+2] = pColorInfo[i].color_S;
			pDes[index+3] = pColorInfo[i].color_B;
		}
	}
}
void ya_stripLights_app_cloudToLocal(st_stripLigths_colorInfo *pColorInfo,unsigned char *pSrc,int len)
{
	int i = 0;
	int index = 0;
	for(i=0;i<len;i++)
	{
		index = i*4;
		if(pSrc[index+0] == COLORTYPE_WHITE)
		{
			pColorInfo[i].type = pSrc[index+0] ;
			pColorInfo[i].color_H = 0 ;
			pColorInfo[i].color_S = 0 ;
			pColorInfo[i].color_B = 0 ;
			pColorInfo[i].white_temp = pSrc[index+2] ;
			pColorInfo[i].white_bright = pSrc[index+3] ;
		}
		else if(pSrc[index+0] == COLORTYPE_COLOR)
		{
			pColorInfo[i].type = pSrc[index+0] ;
			pColorInfo[i].color_H = (pSrc[index+1] * 360)/100 ;
			pColorInfo[i].color_S = pSrc[index+2] ;
			pColorInfo[i].color_B = pSrc[index+3] ;
		}
		else
		{
			ya_printf(C_LOG_INFO," \r\n ya_stripLights_app_cloudToLocal error= %d  \r\n",i);
		}
	}
}

bool ya_get_updata_stripLights(void)
{
	return ya_update_stripLights_data_to_cloud_enable;
}	

void ya_clear_updata_stripLights(void)
{
	ya_update_stripLights_data_to_cloud_enable = 0;
}

void ya_get_cur_thing_model(st_stripLigths_thingModel *thing_mode)
{
	thing_mode->switchstate = cur_control_data.lightSwitch;
	thing_mode->work_mode = cur_control_data.workMode;
	thing_mode->white_temp = cur_control_data.white_temp;
	thing_mode->white_bright = cur_control_data.white_bright;

	if (cur_control_data.corlor_H != thing_mode->color_H)
	{
		thing_mode->color_H = cur_control_data.corlor_H;
		thing_mode->color[0] = (cur_control_data.corlor_H * 100)/360;
	} else
	{
		thing_mode->color[0] = cur_control_data.corlor_H;
	}
	
	thing_mode->color[1] = cur_control_data.corlor_S;
	thing_mode->color[2] = cur_control_data.corlor_B;
	thing_mode->music = cur_control_data.mic_index;
	thing_mode->mic_sensitivity = cur_control_data.micInfo.mic_sensitivity;
	thing_mode->mic_rate = cur_control_data.micInfo.mic_rate;
	
	thing_mode->scene[0] = cur_control_data.sceneInfo.groupNum*4+4;
	thing_mode->scene[1] = cur_control_data.sceneInfo.cmd;
	thing_mode->scene[2] = cur_control_data.sceneInfo.sceneIndex;
	thing_mode->scene[3] = cur_control_data.sceneInfo.changeType;
	thing_mode->scene[4] = cur_control_data.sceneInfo.changeSpeed;
	
	ya_stripLights_app_localToCloud(&thing_mode->scene[5], cur_control_data.sceneInfo.colorInfo, cur_control_data.sceneInfo.groupNum);

}

void  ya_stripLights_app_updatePwm(st_ya_stripLigths_workData *pworkInfo, uint8_t save_flag)
{
	memset(&new_control_data, 0, sizeof(ya_control_workData));

	new_control_data.lightSwitch = pworkInfo->lightSwitch;
	new_control_data.workMode = pworkInfo->workMode;
	new_control_data.corlor_H = pworkInfo->corlor_H;
	new_control_data.corlor_S = pworkInfo->corlor_S;
	new_control_data.corlor_B = pworkInfo->corlor_B;
	new_control_data.white_temp = pworkInfo->white_temp;
	new_control_data.white_bright = pworkInfo->white_bright;
	new_control_data.mic_index = pworkInfo->cur_music_index;
	memcpy(&new_control_data.micInfo, &(pworkInfo->micInfo[pworkInfo->cur_music_index]), sizeof(st_stripLigths_micInfo));

	if (pworkInfo->sceneInfo_temp_flag)
	{
		memcpy(&new_control_data.sceneInfo, &(pworkInfo->sceneInfo_temp), sizeof(st_stripLigths_sceneInfo));
		pworkInfo->sceneInfo_temp_flag = 0;
		memset(&(pworkInfo->sceneInfo_temp), 0, sizeof(st_stripLigths_sceneInfo));
	}else
	{
		memcpy(&new_control_data.sceneInfo, &(pworkInfo->sceneInfo[pworkInfo->cur_scene_index]), sizeof(st_stripLigths_sceneInfo));
	}
	
	if(memcmp(&cur_control_data, &new_control_data, sizeof(ya_control_workData)) == 0)
		return;
	else
	{		
		memcpy(&cur_control_data, &new_control_data, sizeof(ya_control_workData));

		if (cur_control_data.lightSwitch == 1)
		{
			if (cur_control_data.workMode == WORKMODE_WHITE)
			{
				#if (STRIP_LIGHT == 1)
				set_music_param(0,0,0,0,0);
				#endif
				ya_display_value_control.groupNum = 1;
				ya_display_value_control.changeSpeed = 0;
				ya_display_value_control.changeType = STATIC_TYPE;
				ya_display_value_control.sceneIndex = 0;
				ya_display_value_control.colorInfo[0].type = COLORTYPE_WHITE;
				ya_display_value_control.colorInfo[0].color_H = 0;
				ya_display_value_control.colorInfo[0].color_S = 0;		
				ya_display_value_control.colorInfo[0].color_B = 0;
				ya_display_value_control.colorInfo[0].white_temp = cur_control_data.white_temp;
				ya_display_value_control.colorInfo[0].white_bright = cur_control_data.white_bright;
			}
			else if (cur_control_data.workMode == WORKMODE_COLOR)
			{
				#if (STRIP_LIGHT == 1)
				set_music_param(0,0,0,0,0);
				#endif
				ya_display_value_control.groupNum = 1;
				ya_display_value_control.changeSpeed = 0;
				ya_display_value_control.changeType = STATIC_TYPE;
				ya_display_value_control.sceneIndex = 0;
				ya_display_value_control.colorInfo[0].type = COLORTYPE_COLOR;
				ya_display_value_control.colorInfo[0].color_H = cur_control_data.corlor_H;
				ya_display_value_control.colorInfo[0].color_S = cur_control_data.corlor_S;			
				ya_display_value_control.colorInfo[0].color_B = cur_control_data.corlor_B;
				ya_display_value_control.colorInfo[0].white_temp = 0;
				ya_display_value_control.colorInfo[0].white_bright = 0;
				
			}
			else if (cur_control_data.workMode == WORKMODE_SCENE)
			{
				#if (STRIP_LIGHT == 1)
				set_music_param(0,0,0,0,0);
				#endif
				memcpy(&ya_display_value_control, &cur_control_data.sceneInfo, sizeof(st_stripLigths_sceneInfo));
			}
			else if (cur_control_data.workMode == WORKMODE_MUSIC)
			{
				memset(&ya_display_value_control, 0, sizeof(ya_display_stripsLight_t));
				#if (STRIP_LIGHT == 1)
				set_music_param(1, WORKMODE_MUSIC, cur_control_data.mic_index, cur_control_data.micInfo.mic_sensitivity, cur_control_data.micInfo.mic_rate);
				#endif
				memset(&ya_display_value_control,0,sizeof(ya_display_value_control));
			}
			else
				return;
		}
		else
		{
			#if (STRIP_LIGHT == 1)
			set_music_param(0,0,0,0,0);
			#endif
			memset(&ya_display_value_control,0,sizeof(ya_display_value_control));
		}
		
		//save data here
		if (save_flag)
		{
			ya_stripLights_app_sceneSave();
		}
		ya_update_stripLights_data_to_cloud_enable = 1; 
		
		ya_stripLights_pwmUpdate_into_queue((uint8_t *)&ya_display_value_control, sizeof(ya_display_stripsLight_t));
	}
}

void ya_stripLights_app_button_event_into_queue(uint8_t msg_event)
{
	msg_t msg;
	memset(&msg, 0, sizeof(msg_t)); 		
	msg.type = msg_event;
	ya_hal_os_queue_send(&ya_striplight_queue, &msg, 0);
}

void ya_stripLights_app_cloud_event_into_queue(uint8_t *buf, uint16_t len)
{
	int32_t ret = -1;
	msg_t msg;
	memset(&msg, 0, sizeof(msg_t)); 		
	msg.type = CLOUD_TYPE;

	msg.addr = (uint8_t *)ya_hal_os_memory_alloc(len);
	memcpy(msg.addr, buf, len);
	msg.len = len;

	ret = ya_hal_os_queue_send(&ya_striplight_queue, &msg, 0);
	if (ret != C_OK)
	{
		if (msg.addr)
			ya_hal_os_memory_free(msg.addr);
	}
}

void ya_stripLights_app_ble_event_into_queue(uint8_t *buf, uint16_t len, uint8_t cmd)
{
	int32_t ret = -1;
	msg_t msg;
	memset(&msg, 0, sizeof(msg_t)); 		
	msg.type = BLE_TYPE;
	msg.subtype = cmd;

	msg.addr = (uint8_t *)ya_hal_os_memory_alloc(len);
	memcpy(msg.addr, buf, len);
	msg.len = len;

	ret = ya_hal_os_queue_send(&ya_striplight_queue, &msg, 0);
	if (ret != C_OK)
	{
		if (msg.addr)
			ya_hal_os_memory_free(msg.addr);
	}
}

int32_t ya_stripLights_cloud_attriReport(void)
{
	char temp_string[100];
	uint32_t hsb_value = 0;
	int32_t ret = -1;
	cJSON *property = NULL;
	char *buf = NULL;
	
	property = cJSON_CreateObject();
	if(!property)
		return -1;

	ya_get_cur_thing_model(&ya_stripLights_thing_mode);
	
	if (app_token[0] != 0)
	{
		cJSON_AddStringToObject(property, "appToken", app_token);
		memset(app_token, 0, 32+1);
	}
#if (STRIP_LIGHT == 1)
	cJSON_AddStringToObject(property, "switch", ya_int_to_string(ya_stripLights_thing_mode.switchstate));
#else
	cJSON_AddStringToObject(property, "Switch", ya_int_to_string(ya_stripLights_thing_mode.switchstate));
#endif
	if (ya_stripLights_thing_mode.switchstate)
	{
		#if (STRIP_LIGHT == 1)
		cJSON_AddStringToObject(property, "work_mode", ya_int_to_string(ya_stripLights_thing_mode.work_mode));
		#else
		cJSON_AddStringToObject(property, "WorkMode", ya_int_to_string(ya_stripLights_thing_mode.work_mode));	
		#endif
		switch (ya_stripLights_thing_mode.work_mode)
		{
			case WORKMODE_WHITE:
				#if (STRIP_LIGHT == 1)
				cJSON_AddStringToObject(property, "white_temp", ya_int_to_string(ya_stripLights_thing_mode.white_temp));
				cJSON_AddStringToObject(property, "white_bright", ya_int_to_string(ya_stripLights_thing_mode.white_bright));
				#else
				cJSON_AddStringToObject(property, "Luminance", ya_int_to_string(ya_stripLights_thing_mode.white_bright));
				cJSON_AddStringToObject(property, "ColorTemperature", ya_int_to_string(ya_stripLights_thing_mode.white_temp));
				cJSON_AddStringToObject(property, "LightScene", ya_int_to_string(ya_stripLights_thing_mode.scene[2]));
				#if (LIGHT_TYPE != 1)
				cJSON_AddStringToObject(property, "Hue",  ya_int_to_string(ya_stripLights_thing_mode.color[0]));
				cJSON_AddStringToObject(property, "Saturation",  ya_int_to_string(ya_stripLights_thing_mode.color[1]));
				cJSON_AddStringToObject(property, "Brightness",  ya_int_to_string(ya_stripLights_thing_mode.color[2]));
				#endif
				#endif
				break;

			case WORKMODE_COLOR:
				#if (STRIP_LIGHT == 1)
				memset(temp_string, 0, 100);
				HexArrayToString(&ya_stripLights_thing_mode.color[0], 3, temp_string);
				cJSON_AddStringToObject(property, "color", temp_string);
				#else
				cJSON_AddStringToObject(property, "Luminance", ya_int_to_string(ya_stripLights_thing_mode.white_bright));
				cJSON_AddStringToObject(property, "ColorTemperature", ya_int_to_string(ya_stripLights_thing_mode.white_temp));
				cJSON_AddStringToObject(property, "LightScene", ya_int_to_string(ya_stripLights_thing_mode.scene[2]));
				cJSON_AddStringToObject(property, "Hue",  ya_int_to_string(ya_stripLights_thing_mode.color[0]));
				cJSON_AddStringToObject(property, "Saturation",  ya_int_to_string(ya_stripLights_thing_mode.color[1]));
				cJSON_AddStringToObject(property, "Brightness",  ya_int_to_string(ya_stripLights_thing_mode.color[2]));
				#endif
				break;			

			case WORKMODE_SCENE:
				#if (STRIP_LIGHT == 1)
				memset(temp_string, 0, 100);
				HexArrayToString(ya_stripLights_thing_mode.scene+1, ya_stripLights_thing_mode.scene[0], temp_string);
				cJSON_AddStringToObject(property, "scene", temp_string);
				#else
				cJSON_AddStringToObject(property, "Luminance", ya_int_to_string(ya_stripLights_thing_mode.white_bright));
				cJSON_AddStringToObject(property, "ColorTemperature", ya_int_to_string(ya_stripLights_thing_mode.white_temp));
				cJSON_AddStringToObject(property, "LightScene", ya_int_to_string(ya_stripLights_thing_mode.scene[2]));
				#if (LIGHT_TYPE != 1)
				cJSON_AddStringToObject(property, "Hue",  ya_int_to_string(ya_stripLights_thing_mode.color[0]));
				cJSON_AddStringToObject(property, "Saturation",  ya_int_to_string(ya_stripLights_thing_mode.color[1]));
				cJSON_AddStringToObject(property, "Brightness",  ya_int_to_string(ya_stripLights_thing_mode.color[2]));
				#endif
				#endif
				break;

			case WORKMODE_MUSIC:
				cJSON_AddStringToObject(property, "music", ya_int_to_string(ya_stripLights_thing_mode.music));
				cJSON_AddStringToObject(property, "mic_sensitivity", ya_int_to_string(ya_stripLights_thing_mode.mic_sensitivity));
				cJSON_AddStringToObject(property, "mic_rate", ya_int_to_string(ya_stripLights_thing_mode.mic_rate));
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

void ya_stripLights_app_cloudScenehandle(uint8_t *buf, uint16_t len)
{
	uint8_t index = 0, scene_para_get = 0;
	uint8_t scene_data[SCENE_MAX_LEN + 1];
	st_ya_stripLigths_workData *pworkInfo = &ya_stripLigths_workData;
	st_stripLigths_sceneInfo *psceneInfo;

	uint32_t value = 0;
	uint8_t save_flag = 1, tmp_value = 0;

	cJSON *root = NULL, *json_key = NULL;

	memset(scene_data, 0, SCENE_MAX_LEN + 1);

	ya_get_cur_thing_model(&ya_stripLights_thing_mode);
	root = cJSON_Parse((char *)buf);
	if (!root) return;

	memset(app_token, 0, 32+1);
	json_key = cJSON_GetObjectItem(root, "appToken");
	if (json_key && json_key->type == cJSON_String)
	{
		if (strlen(json_key->valuestring) < (32+1))
			strcpy(app_token, json_key->valuestring);
	}

#if (STRIP_LIGHT == 1)
	json_key = cJSON_GetObjectItem(root, "switch");
#else
	json_key = cJSON_GetObjectItem(root, "Switch");
#endif
	if (json_key && json_key->type == cJSON_String)
	{
		value = atoi(json_key->valuestring);
		if (value > 0)
			ya_stripLights_thing_mode.switchstate = 1;
		else
			ya_stripLights_thing_mode.switchstate = 0;
	} 
	else
	{
		#if (STRIP_LIGHT == 1)
		json_key = cJSON_GetObjectItem(root, "work_mode");
		#else
		json_key = cJSON_GetObjectItem(root, "WorkMode");
		#endif
		if (json_key && json_key->type == cJSON_String)
		{
			ya_stripLights_thing_mode.switchstate = 1;
			value = atoi(json_key->valuestring);
			if (value < WORKMODE_MAX)
				ya_stripLights_thing_mode.work_mode = atoi(json_key->valuestring);
		} 
#if (STRIP_LIGHT == 1)
		json_key = cJSON_GetObjectItem(root, "white_temp");
#else
		json_key = cJSON_GetObjectItem(root, "ColorTemperature");
#endif
		if (json_key && json_key->type == cJSON_String)
		{
			value = atoi(json_key->valuestring);
			if (value <= 100)
			{
				ya_stripLights_thing_mode.white_temp = atoi(json_key->valuestring);
				ya_stripLights_thing_mode.work_mode = WORKMODE_WHITE;
				ya_stripLights_thing_mode.switchstate = 1;
			}
		} 		
#if (STRIP_LIGHT == 1)
		json_key = cJSON_GetObjectItem(root, "white_bright");
#else
		json_key = cJSON_GetObjectItem(root, "Luminance");
#endif
		if (json_key && json_key->type == cJSON_String)
		{
			value = atoi(json_key->valuestring);
			if (value <= 100)
			{
				ya_stripLights_thing_mode.white_bright = atoi(json_key->valuestring);
				ya_stripLights_thing_mode.work_mode = WORKMODE_WHITE;
				ya_stripLights_thing_mode.switchstate = 1;
			}
		} 	
#if (STRIP_LIGHT == 1)		
		json_key = cJSON_GetObjectItem(root, "color");
		if (json_key && json_key->type == cJSON_String && strlen(json_key->valuestring) == 6)
		{
			ya_stripLights_thing_mode.switchstate = 1;
			StringToHexArray(&ya_stripLights_thing_mode.color[0], 3, json_key->valuestring);
			ya_stripLights_thing_mode.color_H = (ya_stripLights_thing_mode.color[0] * 360)/100;
			ya_stripLights_thing_mode.work_mode = WORKMODE_COLOR;
		} 
#else
		json_key = cJSON_GetObjectItem(root, "Hue");
		if (json_key && json_key->type == cJSON_String)
		{
			ya_stripLights_thing_mode.color[0] = atoi(json_key->valuestring);
			ya_stripLights_thing_mode.color_H = ya_stripLights_thing_mode.color[0];
			ya_stripLights_thing_mode.switchstate = 1;
			ya_stripLights_thing_mode.work_mode = WORKMODE_COLOR;
		}
		json_key = cJSON_GetObjectItem(root, "Saturation");
		if (json_key && json_key->type == cJSON_String)
		{
			ya_stripLights_thing_mode.color[1] = atoi(json_key->valuestring);
			ya_stripLights_thing_mode.switchstate = 1;
			ya_stripLights_thing_mode.work_mode = WORKMODE_COLOR;
		}
		json_key = cJSON_GetObjectItem(root, "Brightness");
		if (json_key && json_key->type == cJSON_String)
		{
			ya_stripLights_thing_mode.color[2] = atoi(json_key->valuestring);
			ya_stripLights_thing_mode.switchstate = 1;
			ya_stripLights_thing_mode.work_mode = WORKMODE_COLOR;
		}
#endif
#if (STRIP_LIGHT == 1)
		json_key = cJSON_GetObjectItem(root, "scene");
		if (json_key && json_key->type == cJSON_String && strlen(json_key->valuestring) <= (SCENE_MAX_LEN*2) && strlen(json_key->valuestring) >= 4)
		{
			scene_para_get = 1;
			scene_data[0] = StringToHexArray(scene_data + 1, SCENE_MAX_LEN, json_key->valuestring);
			ya_stripLights_thing_mode.work_mode = WORKMODE_SCENE;
			ya_stripLights_thing_mode.switchstate = 1;
		}
#else
		json_key = cJSON_GetObjectItem(root, "LightScene");
		if (json_key && json_key->type == cJSON_String)
		{
			scene_para_get = 1;
			scene_data[0] = 4;
			scene_data[1] = CTRLCMD_RESTORE_FACTORY;
			scene_data[2] = atoi(json_key->valuestring);
			ya_stripLights_thing_mode.work_mode = WORKMODE_SCENE;
			ya_stripLights_thing_mode.switchstate = 1;
		}
#endif
#if (STRIP_LIGHT == 1)
		json_key = cJSON_GetObjectItem(root, "music");
		if (json_key && json_key->type == cJSON_String)
		{
			value = atoi(json_key->valuestring);
			if (value < MUSICMODE_MAX)
			{
				ya_stripLights_thing_mode.switchstate = 1;
				ya_stripLights_thing_mode.music = atoi(json_key->valuestring);
				ya_stripLights_thing_mode.mic_sensitivity = pworkInfo->micInfo[ya_stripLights_thing_mode.music].mic_sensitivity;
				ya_stripLights_thing_mode.mic_rate = pworkInfo->micInfo[ya_stripLights_thing_mode.music].mic_rate;
				ya_stripLights_thing_mode.work_mode = WORKMODE_MUSIC;
			}
		}

		json_key = cJSON_GetObjectItem(root, "mic_sensitivity");
		if (json_key && json_key->type == cJSON_String)
		{
			value = atoi(json_key->valuestring);
			if (value <= 100)
			{
				ya_stripLights_thing_mode.switchstate = 1;
				ya_stripLights_thing_mode.mic_sensitivity = atoi(json_key->valuestring);
				ya_stripLights_thing_mode.work_mode = WORKMODE_MUSIC;
			}
		}

		json_key = cJSON_GetObjectItem(root, "mic_rate");
		if (json_key && json_key->type == cJSON_String)
		{
			value = atoi(json_key->valuestring);
			if (value <= 100)
			{
				ya_stripLights_thing_mode.switchstate = 1;
				ya_stripLights_thing_mode.mic_rate = atoi(json_key->valuestring);
				ya_stripLights_thing_mode.work_mode = WORKMODE_MUSIC;
			}
		}
#endif		
	}
	
	ya_printf(C_LOG_INFO,"s: %d, w: %d, l_w: %d, l_b: %d, l_h: %d, l_s: %d, l_c: %d, l_m: %d, l_m_s: %d, l_m_r %d\r\n",
	ya_stripLights_thing_mode.switchstate,
	ya_stripLights_thing_mode.work_mode,
	ya_stripLights_thing_mode.white_temp,
	ya_stripLights_thing_mode.white_bright,
	ya_stripLights_thing_mode.color[0],
	ya_stripLights_thing_mode.color[1],
	ya_stripLights_thing_mode.color[2],
	ya_stripLights_thing_mode.music,
	ya_stripLights_thing_mode.mic_sensitivity,
	ya_stripLights_thing_mode.mic_rate);

	if (scene_para_get == 0 && ya_stripLights_thing_mode.work_mode == WORKMODE_SCENE)
	{
		memcpy(scene_data, ya_stripLights_thing_mode.scene, (SCENE_MAX_LEN + 1));
	}
	
	for (index = 1; index < (scene_data[0] + 1); index++)
		ya_printf(C_LOG_INFO, " %02x", scene_data[index]);

	ya_printf(C_LOG_INFO, "\r\n");

	if (root) cJSON_Delete(root);

	pworkInfo->lightSwitch = ya_stripLights_thing_mode.switchstate;
	pworkInfo->workMode = ya_stripLights_thing_mode.work_mode;
	
	if(pworkInfo->lightSwitch)
	{
		switch(pworkInfo->workMode)
		{
			case WORKMODE_WHITE:
					pworkInfo->white_temp = ya_stripLights_thing_mode.white_temp;
					pworkInfo->white_bright = ya_stripLights_thing_mode.white_bright;
				break;
				
			case WORKMODE_COLOR:
					pworkInfo->corlor_H = ya_stripLights_thing_mode.color_H;
					pworkInfo->corlor_S = ya_stripLights_thing_mode.color[1];
					pworkInfo->corlor_B = ya_stripLights_thing_mode.color[2];
				break;
				
			case WORKMODE_SCENE:
					if (scene_data[2] >=  SCENE_MAX)
					{
						ya_printf(C_LOG_ERROR, "scene index overflow\n");
						pworkInfo->cur_scene_index = SCENE_MAX - 1; 
						psceneInfo = &pworkInfo->sceneInfo[pworkInfo->cur_scene_index];
					}
					else
					{
						if (scene_data[1] == CTRLCMD_DYNAMICALLY_NOTSAVE)
						{
							pworkInfo->sceneInfo_temp_flag = 1;
							psceneInfo = &pworkInfo->sceneInfo_temp;
							save_flag = 0;
						}
						else 
						{
							pworkInfo->cur_scene_index = scene_data[2];	
							psceneInfo = &pworkInfo->sceneInfo[pworkInfo->cur_scene_index];
						}
						if ((scene_data[1] == CTRLCMD_DYNAMICALLY_NOTSAVE || scene_data[1] == CTRLCMD_DYNAMICALLY_SAVE) && scene_data[0] > 4)
						{	
							psceneInfo->groupNum =  (scene_data[0] - 4)/4;
							psceneInfo->cmd = scene_data[1];
							psceneInfo->sceneIndex = scene_data[2];
							psceneInfo->changeType = scene_data[3];
							psceneInfo->changeSpeed = scene_data[4];
							ya_stripLights_app_cloudToLocal(&psceneInfo ->colorInfo[0], &scene_data[5],psceneInfo->groupNum);
						}
						else 
						{
							if(scene_data[1] == CTRLCMD_RESTORE_FACTORY)
							{
								ya_stripLights_app_SceneInit(pworkInfo->cur_scene_index, psceneInfo);
							}
							psceneInfo->cmd = scene_data[1];
						}
					}
					ya_update_stripLights_data_to_cloud_enable = 1; 
				break;
					
			case WORKMODE_MUSIC:
					pworkInfo->cur_music_index = ya_stripLights_thing_mode.music;
					pworkInfo->micInfo[pworkInfo->cur_music_index].mic_sensitivity = ya_stripLights_thing_mode.mic_sensitivity;
					pworkInfo->micInfo[pworkInfo->cur_music_index].mic_rate = ya_stripLights_thing_mode.mic_rate;
				break;

			default:
				break;
		}
 	}

	ya_stripLights_app_updatePwm(&ya_stripLigths_workData, save_flag);
}


void ya_striplights_ir_updown_step(uint8_t *value, uint8_t flag)
{
	if (flag)
	{
		(*value) += 10; 
		if ((*value) >= 100)
			(*value) = 100;
	} else 
	{
		if ((*value) < 10)
			(*value) = 10;
		else
		{
			(*value) -= 10;
			if ((*value) < 10)
				(*value) = 10;
		}
	}
}

void ya_stripLights_IR_handle(uint8_t subtype)
{
	bool add = 0;
	st_ya_stripLigths_workData *pworkInfo = &ya_stripLigths_workData;

	if (subtype != KEYCMD_ON && pworkInfo->lightSwitch == 0)
		return;

	pworkInfo->lightSwitch = 1;
	switch(subtype)
	{
		case KEYCMD_UP:
		case KEYCMD_DOWN:
			
			add = (subtype == KEYCMD_UP) ? 1:0;
			if (pworkInfo->sceneInfo_temp_flag == 0)
			{
				if (pworkInfo->workMode == WORKMODE_COLOR)
				{
					ya_striplights_ir_updown_step(&pworkInfo->corlor_B, add);
				} else if (pworkInfo->workMode == WORKMODE_WHITE)
				{
					ya_striplights_ir_updown_step(&pworkInfo->white_bright, add);
				} else if (pworkInfo->workMode == WORKMODE_SCENE)
				{
					if (pworkInfo->sceneInfo[pworkInfo->cur_scene_index].changeType == 0)
					{
						if (pworkInfo->sceneInfo[pworkInfo->cur_scene_index].colorInfo[0].type == 0)
						{
							ya_striplights_ir_updown_step(&(pworkInfo->sceneInfo[pworkInfo->cur_scene_index].colorInfo[0].white_bright), add);
						}else
						{
							ya_striplights_ir_updown_step(&(pworkInfo->sceneInfo[pworkInfo->cur_scene_index].colorInfo[0].color_B), add);
						}
					} else 
					{
						ya_striplights_ir_updown_step(&(pworkInfo->sceneInfo[pworkInfo->cur_scene_index].changeSpeed), add);
					}
				} else if (pworkInfo->workMode == WORKMODE_MUSIC)
				{	
					ya_striplights_ir_updown_step(&(pworkInfo->micInfo[pworkInfo->cur_music_index].mic_sensitivity), add);
				}
			} 
			break;
			
		case KEYCMD_OFF:
			pworkInfo->lightSwitch = 0;
			break;

		case KEYCMD_ON:
			pworkInfo->lightSwitch = 1;
			break;
			
		case KEYCMD_COLOR_R:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 0;
			pworkInfo->corlor_S = 100;
			break;

		case KEYCMD_COLOR_G:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 120;
			pworkInfo->corlor_S = 100;
			break;

		case KEYCMD_COLOR_B:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 240;
			pworkInfo->corlor_S = 100;	
			break;

		case KEYCMD_COLOR_W:
			pworkInfo->workMode = WORKMODE_WHITE;
			//pworkInfo->white_temp = 100;//use flash data
			break;

		case KEYCMD_COLOR_3_1:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 3;
			pworkInfo->corlor_S = 100;
			break;

		case KEYCMD_COLOR_3_2:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 135;
			pworkInfo->corlor_S = 100;
			break;

		case KEYCMD_COLOR_3_3:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 255;
			pworkInfo->corlor_S = 100;

			break;

		case KEYCMD_COLOR_4_1:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 18;
			pworkInfo->corlor_S = 100;
			break;

		case KEYCMD_COLOR_4_2:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 150;
			pworkInfo->corlor_S = 100;
			break;
			
		case KEYCMD_COLOR_4_3:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 270;
			pworkInfo->corlor_S = 100;
			break;


		case KEYCMD_COLOR_5_1:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 33;
			pworkInfo->corlor_S = 100;
			break;

		case KEYCMD_COLOR_5_2:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 165;
			pworkInfo->corlor_S = 100;
			break;

		case KEYCMD_COLOR_5_3:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 312;
			pworkInfo->corlor_S = 100;
			break;

		case KEYCMD_COLOR_6_1:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 48;
			pworkInfo->corlor_S = 100;
			break;

		case KEYCMD_COLOR_6_2:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 180;
			pworkInfo->corlor_S = 100;

			break;

		case KEYCMD_COLOR_6_3:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 300;
			pworkInfo->corlor_S = 100;
			break;

		case KEYCMD_MODE_COLOR_PROFUSION:
			pworkInfo->workMode = WORKMODE_SCENE;
			pworkInfo->cur_scene_index = 0x09;
			break;

		case KEYCMD_MODE_COLOR_DAZZLE_COLOUR:
			pworkInfo->workMode = WORKMODE_SCENE;
			pworkInfo->cur_scene_index = 0x0A;
			break;

		case KEYCMD_MODE_COLOR_COLORS:
			pworkInfo->workMode = WORKMODE_SCENE;
			pworkInfo->cur_scene_index = 0x0B;
			break;
			
		case KEYCMD_MODE_MUSI:
			pworkInfo->workMode = WORKMODE_MUSIC;
			pworkInfo->cur_music_index = 0x00;
			break;

		default:
			break;
	}

	ya_stripLights_app_updatePwm(&ya_stripLigths_workData, 1);
}


void ya_stripLights_button_handle()
{
	static uint8_t button_index = 0;
	st_ya_stripLigths_workData *pworkInfo = &ya_stripLigths_workData;

	pworkInfo->lightSwitch = 1;
	switch(button_index)
	{
		case BUTTON_OFF:
			pworkInfo->lightSwitch = 0;
			break;

		case BUTTON_COOL:
			pworkInfo->workMode = WORKMODE_WHITE;
			pworkInfo->white_temp = 100;
			pworkInfo->white_bright = 100;
			break;

		case BUTTON_WARM:
			pworkInfo->workMode = WORKMODE_WHITE;
			pworkInfo->white_temp = 0;
			pworkInfo->white_bright = 100;
			break;
			
		case BUTTON_RED:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 0;
			pworkInfo->corlor_S = 100;
			pworkInfo->corlor_B = 100;
			break;
			
		case BUTTON_GREEN:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 120;
			pworkInfo->corlor_S = 100;
			pworkInfo->corlor_B = 100;
			break;

		case BUTTON_BLUE:
			pworkInfo->workMode = WORKMODE_COLOR;
			pworkInfo->corlor_H = 240;
			pworkInfo->corlor_S = 100;
			pworkInfo->corlor_B = 100;
			break;

		case BUTTON_SCENE1:
			pworkInfo->workMode = WORKMODE_SCENE;
			pworkInfo->cur_scene_index = SCENE_SOFT_LIGHT;
			break;

		case BUTTON_SCENE2:
			pworkInfo->workMode = WORKMODE_SCENE;
			pworkInfo->cur_scene_index = SCENE_PROFUSION;
			break;

		case BUTTON_SCENE3:
			pworkInfo->workMode = WORKMODE_SCENE;
			pworkInfo->cur_scene_index = SCENE_DAZZLE_COLOUR;
			break;
			
		case BUTTON_SCENE4:
			pworkInfo->workMode = WORKMODE_SCENE;
			pworkInfo->cur_scene_index = SCENE_COLORS;
			break;

		case BUTTON_MISC1:
			pworkInfo->workMode = WORKMODE_MUSIC;
			pworkInfo->cur_music_index = MUSICMODE_MADDEN;
			break;

		case BUTTON_MISC2:
			pworkInfo->workMode = WORKMODE_MUSIC;
			pworkInfo->cur_music_index = MUSICMODE_ROCK;
			break;

		case BUTTON_MISC3:
			pworkInfo->workMode = WORKMODE_MUSIC;
			pworkInfo->cur_music_index = MUSICMODE_CLASSIC;
			break;

		case BUTTON_MISC4:
			pworkInfo->workMode = WORKMODE_MUSIC;
			pworkInfo->cur_music_index = MUSICMODE_SOFT;
			break;

		default:
			break;
	}

	button_index++;
	if (button_index >= BUTTON_EVENT_MAX)
		button_index = 0;

	ya_stripLights_app_updatePwm(&ya_stripLigths_workData, 1);


}
extern  int ya_ble_app_device_reply_msg_handle(uint8_t* data,uint16_t len,uint8_t cmd_type);
extern void ya_ble_app_debug_array(char *string_start, uint8_t *buf, uint16_t buf_len);

void ya_stripLights_ble_attriReport()
{
	//do report logic here
	//ya_ble_app_device_reply_msg_handle(data,len,cmd_type);
}
void ya_stripLights_app_ble_Scenehandle(uint8_t *buf, uint16_t len)
{
	uint8_t index = 0, scene_para_get = 0;
	uint8_t scene_data[SCENE_MAX_LEN + 1];
	st_ya_stripLigths_workData *pworkInfo = &ya_stripLigths_workData;
	st_stripLigths_sceneInfo *psceneInfo;

	uint32_t value = 0;
	uint8_t save_flag = 0, tmp_value = 0;

	memset(scene_data, 0, SCENE_MAX_LEN + 1);

	ya_get_cur_thing_model(&ya_stripLights_thing_mode);
	ya_ble_app_debug_array("get app data",buf,len);
	switch(buf[0])
	{
		case YA_BLE_SET_LED_COLOR:
			ya_stripLights_thing_mode.switchstate = 1;
			memcpy(ya_stripLights_thing_mode.color,buf+1,3);
			ya_stripLights_thing_mode.color_H = (ya_stripLights_thing_mode.color[0] * 360)/100;
			ya_stripLights_thing_mode.work_mode = WORKMODE_COLOR;
			break;
		case YA_BLE_SET_LED_ARG:
			if(buf[1] == 0x01)
			{
				if (buf[2] <= 100)
				{
					ya_stripLights_thing_mode.white_bright = buf[2];
					ya_stripLights_thing_mode.work_mode = WORKMODE_WHITE;
					ya_stripLights_thing_mode.switchstate = 1;
				}				
			}
			else if(buf[1] == 0x02)
			{
				if (buf[2] <= 100)
				{
					ya_stripLights_thing_mode.switchstate = 1;
					ya_stripLights_thing_mode.mic_sensitivity = buf[2];
					ya_stripLights_thing_mode.work_mode = WORKMODE_MUSIC;
				}				
			}
			break;
		case YA_BLE_SET_LED_MODE:
			scene_para_get = 1;
			scene_data[0] = 4;
			scene_data[1] = CTRLCMD_RESTORE_FACTORY;
			scene_data[2] = buf[1];
			ya_stripLights_thing_mode.work_mode = WORKMODE_SCENE;
			ya_stripLights_thing_mode.switchstate = 1;
			break;			
	}
	#if 0
	ya_printf(C_LOG_INFO,"s: %d, w: %d, l_w: %d, l_b: %d, l_h: %d, l_s: %d, l_c: %d, l_m: %d, l_m_s: %d, l_m_r %d\r\n",
	ya_stripLights_thing_mode.switchstate,
	ya_stripLights_thing_mode.work_mode,
	ya_stripLights_thing_mode.white_temp,
	ya_stripLights_thing_mode.white_bright,
	ya_stripLights_thing_mode.color[0],
	ya_stripLights_thing_mode.color[1],
	ya_stripLights_thing_mode.color[2],
	ya_stripLights_thing_mode.music,
	ya_stripLights_thing_mode.mic_sensitivity,
	ya_stripLights_thing_mode.mic_rate);
	#endif
	if (scene_para_get == 0 && ya_stripLights_thing_mode.work_mode == WORKMODE_SCENE)
	{
		memcpy(scene_data, ya_stripLights_thing_mode.scene, (SCENE_MAX_LEN + 1));
	}
	
	for (index = 1; index < (scene_data[0] + 1); index++)
		ya_printf(C_LOG_INFO, " %02x", scene_data[index]);
	pworkInfo->lightSwitch = ya_stripLights_thing_mode.switchstate;
	pworkInfo->workMode = ya_stripLights_thing_mode.work_mode;
	
	if(pworkInfo->lightSwitch)
	{
		switch(pworkInfo->workMode)
		{
			case WORKMODE_WHITE:
					pworkInfo->white_temp = ya_stripLights_thing_mode.white_temp;
					pworkInfo->white_bright = ya_stripLights_thing_mode.white_bright;
				break;
				
			case WORKMODE_COLOR:
					pworkInfo->corlor_H = ya_stripLights_thing_mode.color_H;
					pworkInfo->corlor_S = ya_stripLights_thing_mode.color[1];
					pworkInfo->corlor_B = ya_stripLights_thing_mode.color[2];
				break;
				
			case WORKMODE_SCENE:
					if (scene_data[2] >=  SCENE_MAX)
					{
						ya_printf(C_LOG_ERROR, "scene index overflow\n");
						pworkInfo->cur_scene_index = SCENE_MAX - 1; 
						psceneInfo = &pworkInfo->sceneInfo[pworkInfo->cur_scene_index];
					}
					else
					{
						if (scene_data[1] == CTRLCMD_DYNAMICALLY_NOTSAVE)
						{
							pworkInfo->sceneInfo_temp_flag = 1;
							psceneInfo = &pworkInfo->sceneInfo_temp;
							save_flag = 0;
						}
						else 
						{
							pworkInfo->cur_scene_index = scene_data[2];	
							psceneInfo = &pworkInfo->sceneInfo[pworkInfo->cur_scene_index];
						}
						if ((scene_data[1] == CTRLCMD_DYNAMICALLY_NOTSAVE || scene_data[1] == CTRLCMD_DYNAMICALLY_SAVE) && scene_data[0] > 4)
						{	
							psceneInfo->groupNum =  (scene_data[0] - 4)/4;
							psceneInfo->cmd = scene_data[1];
							psceneInfo->sceneIndex = scene_data[2];
							psceneInfo->changeType = scene_data[3];
							psceneInfo->changeSpeed = scene_data[4];
							ya_stripLights_app_cloudToLocal(&psceneInfo ->colorInfo[0], &scene_data[5],psceneInfo->groupNum);
						}
						else 
						{
							if(scene_data[1] == CTRLCMD_RESTORE_FACTORY)
							{
								ya_stripLights_app_SceneInit(pworkInfo->cur_scene_index, psceneInfo);
							}
							psceneInfo->cmd = scene_data[1];
						}
					}
					ya_update_stripLights_data_to_cloud_enable = 1; 
				break;
					
			case WORKMODE_MUSIC:
					pworkInfo->cur_music_index = ya_stripLights_thing_mode.music;
					pworkInfo->micInfo[pworkInfo->cur_music_index].mic_sensitivity = ya_stripLights_thing_mode.mic_sensitivity;
					pworkInfo->micInfo[pworkInfo->cur_music_index].mic_rate = ya_stripLights_thing_mode.mic_rate;
				break;

			default:
				break;
		}
 	}

	ya_stripLights_app_updatePwm(&ya_stripLigths_workData, save_flag);

}

void  ya_stripLights_app_infraredHandle(uint8_t type, uint8_t subtype, uint8_t *buf, uint16_t len)
{	
	switch(type)
	{
		case IR_TYPE:
			ya_stripLights_IR_handle(subtype);
		break;

		case BUTTON_TYPE:
			ya_stripLights_button_handle();
		break;

		case CLOUD_TYPE:
			ya_stripLights_app_cloudScenehandle(buf, len);
		break;
		
		case BLE_TYPE:
			ya_stripLights_app_ble_Scenehandle(buf, len);
		break;

		default:

		break;
	}
}


void ya_striplights_app_init_mode()
{
	ya_stripLights_app_updatePwm(&ya_stripLigths_workData, 0);
}

void ya_stripLights_app_netConfigDisplay(void)
{
	#if (STRIP_LIGHT == 1)
	set_music_param(0,0,0,0,0);
	#endif
	ya_display_value_control.groupNum = 1;
	ya_display_value_control.changeSpeed = 0;
	ya_display_value_control.changeType = STATIC_TYPE;
	ya_display_value_control.sceneIndex = 0;
	#if (STRIP_LIGHT == 1)
	ya_display_value_control.colorInfo[0].type = COLORTYPE_COLOR;
	ya_display_value_control.colorInfo[0].color_H = 0;
	ya_display_value_control.colorInfo[0].color_S = 100; 		
	ya_display_value_control.colorInfo[0].color_B = 100;
	ya_display_value_control.colorInfo[0].white_temp = 0;
	ya_display_value_control.colorInfo[0].white_bright = 0;
	#else
	ya_display_value_control.colorInfo[0].type = COLORTYPE_WHITE;
	ya_display_value_control.colorInfo[0].color_H = 0;
	ya_display_value_control.colorInfo[0].color_S = 100; 		
	ya_display_value_control.colorInfo[0].color_B = 100;
	ya_display_value_control.colorInfo[0].white_temp = 50;
	ya_display_value_control.colorInfo[0].white_bright = 50;
	
	#endif

	ya_stripLights_pwmUpdate_into_queue((uint8_t *)&ya_display_value_control, sizeof(ya_display_stripsLight_t));
}

void ya_stripLights_app_factory_test(void)
{
	#if (STRIP_LIGHT == 1)
	set_music_param(0,0,0,0,0);
	#endif
	ya_display_value_control.groupNum = 1;
	ya_display_value_control.changeSpeed = 0;
	ya_display_value_control.changeType = STATIC_TYPE;
	ya_display_value_control.sceneIndex = 0;
	ya_display_value_control.colorInfo[0].type = COLORTYPE_COLOR;
	ya_display_value_control.colorInfo[0].color_H = 120;
	ya_display_value_control.colorInfo[0].color_S = 100; 		
	ya_display_value_control.colorInfo[0].color_B = 100;
	ya_display_value_control.colorInfo[0].white_temp = 0;
	ya_display_value_control.colorInfo[0].white_bright = 0;

	ya_stripLights_pwmUpdate_into_queue((uint8_t *)&ya_display_value_control, sizeof(ya_display_stripsLight_t));
}


void ya_stripLights_switchoff(void)
{
	#if (STRIP_LIGHT == 1)
	set_music_param(0,0,0,0,0);
	#endif
	memset(&ya_display_value_control, 0, sizeof(ya_display_stripsLight_t));
	ya_stripLights_pwmUpdate_into_queue((uint8_t *)&ya_display_value_control, sizeof(ya_display_stripsLight_t));

}

void ya_stripLights_app_sceneInit(void)
{
	int index = 0;

	memset(&ya_stripLigths_workData,0,sizeof(st_ya_stripLigths_workData));
	if(ya_stripLights_app_sceneRead(&ya_stripLigths_workData,sizeof(st_ya_stripLigths_workData)) != 0)
	{
		ya_printf(C_LOG_ERROR, "read scene data failed, then init again\n");
		
		ya_stripLigths_workData.lightSwitch = 1;
		#if (STRIP_LIGHT == 1)
		ya_stripLigths_workData.workMode = WORKMODE_COLOR;
		ya_stripLigths_workData.corlor_H = 0;
		ya_stripLigths_workData.corlor_S = 100;
		ya_stripLigths_workData.corlor_B = 100;
		ya_stripLigths_workData.white_temp = 100;
		ya_stripLigths_workData.white_bright = 50;
		ya_stripLigths_workData.cur_scene_index= SCENE_SOFT_LIGHT;
		ya_stripLigths_workData.cur_music_index = MUSICMODE_MADDEN;
		ya_stripLigths_workData.micInfo[MUSICMODE_MADDEN].mic_sensitivity= 60;
		ya_stripLigths_workData.micInfo[MUSICMODE_MADDEN].mic_rate= 60;
		ya_stripLigths_workData.micInfo[MUSICMODE_ROCK].mic_sensitivity = 90;
		ya_stripLigths_workData.micInfo[MUSICMODE_ROCK].mic_rate = 90;
		ya_stripLigths_workData.micInfo[MUSICMODE_CLASSIC].mic_sensitivity = 75;
		ya_stripLigths_workData.micInfo[MUSICMODE_CLASSIC].mic_rate = 80;
		ya_stripLigths_workData.micInfo[MUSICMODE_SOFT].mic_sensitivity = 50;
		ya_stripLigths_workData.micInfo[MUSICMODE_SOFT].mic_rate = 60;		
		#else
		ya_stripLigths_workData.workMode = WORKMODE_WHITE;
		ya_stripLigths_workData.corlor_H = 0;
		ya_stripLigths_workData.corlor_S = 100;
		ya_stripLigths_workData.corlor_B = 100;
		ya_stripLigths_workData.white_temp = 50;
		ya_stripLigths_workData.white_bright = 50;	
		ya_stripLigths_workData.cur_scene_index= SCENE_READING;
		#endif
		for(index=0; index<SCENE_MAX; index++)
		{
			ya_stripLights_app_SceneInit(index,&ya_stripLigths_workData.sceneInfo[index]);
		}
	}
	
	ya_stripLigths_workData.sceneInfo_temp_flag = 0;
	memset(&ya_stripLigths_workData.sceneInfo_temp, 0, sizeof(st_stripLigths_sceneInfo));

}

