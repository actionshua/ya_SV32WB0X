#ifndef YA_STRIPLIGHTS_APP_H_
#define YA_STRIPLIGHTS_APP_H_
#include "ya_common.h"

typedef enum
{
	BUTTON_OFF = 0,
	BUTTON_COOL,
	BUTTON_WARM,
	BUTTON_RED,
	BUTTON_GREEN,
	BUTTON_BLUE,
	BUTTON_SCENE1,
	BUTTON_SCENE2,
	BUTTON_SCENE3,
	BUTTON_SCENE4,
	BUTTON_MISC1,
	BUTTON_MISC2,
	BUTTON_MISC3,
	BUTTON_MISC4,

	BUTTON_EVENT_MAX,
}en_stripLigths_button_event;

typedef enum
{
	#if 0
	KEYCMD_UP,
	KEYCMD_DOWN,
	KEYCMD_OFF,
	KEYCMD_ON,
	
	KEYCMD_COLOR_R,
	KEYCMD_COLOR_G,
	KEYCMD_COLOR_B,
	KEYCMD_COLOR_W,

	KEYCMD_COLOR_3_1,
	KEYCMD_COLOR_3_2,
	KEYCMD_COLOR_3_3,
	KEYCMD_MODE_COLOR_PROFUSION,
	
	KEYCMD_COLOR_4_1,
	KEYCMD_COLOR_4_2,
	KEYCMD_COLOR_4_3,
	KEYCMD_MODE_COLOR_DAZZLE_COLOUR,

	KEYCMD_COLOR_5_1,
	KEYCMD_COLOR_5_2,
	KEYCMD_COLOR_5_3,
	KEYCMD_MODE_COLOR_COLORS,

	KEYCMD_COLOR_6_1,
	KEYCMD_COLOR_6_2,
	KEYCMD_COLOR_6_3,
	KEYCMD_MODE_MUSI,
	#else
	KEYCMD_ON,
	KEYCMD_OFF,
	KEYCMD_UP,
	KEYCMD_DOWN,
	
	KEYCMD_COLOR_R,
	KEYCMD_COLOR_G,
	KEYCMD_COLOR_B,
	KEYCMD_COLOR_MODE_UP,
	
	KEYCMD_COLOR_3_1,
	KEYCMD_COLOR_3_2,
	KEYCMD_COLOR_3_3,
	KEYCMD_COLOR_MODE_DOWN,
	
	KEYCMD_COLOR_4_1,
	KEYCMD_COLOR_4_2,
	KEYCMD_COLOR_4_3,
	KEYCMD_WHILE_CCT_UP,

	KEYCMD_WHILE_WW,
	KEYCMD_WHILE_NW,
	KEYCMD_WHILE_CW,
	KEYCMD_WHILE_CCT_DOWN,

	KEYCMD_COLOR_FASH,
	KEYCMD_COLOR_SLOW,
	KEYCMD_MODE_NIGHT,
	KEYCMD_TIMING_OFF,
	#endif
	KEYCMD_CONFIG = 0xF1,
 } en_stripLigths_keyCmd;


 typedef enum
 {
	IR_TYPE = 0,
	BUTTON_TYPE,
	CLOUD_TYPE,
	CONFIG_TYPE,
	UDP_TYPE,
 }ya_striplight_control_msg_type_t;


typedef enum
{
	SCENE_READING,
	SCENE_WORK,
	SCENE_GOOD_NIGHT,
	SCENE_LEISURE,
	
	SCENE_DINNER,
	SCENE_DATE,
	SCENE_PARTY,
	SCENE_CINEMA,
	
	SCENE_SOFT_LIGHT,
	SCENE_PROFUSION,
	SCENE_DAZZLE_COLOUR,
	SCENE_COLORS,

	SCENE_MAX,
 } en_stripLigths_SCENE;

typedef enum
{
	COLORTYPE_WHITE,
	COLORTYPE_COLOR,
 } en_stripLigths_colorType;

typedef enum
{
	WORKMODE_WHITE = 0,
	WORKMODE_COLOR,
	WORKMODE_SCENE,
	WORKMODE_MUSIC,

	WORKMODE_MAX,
}en_stripLigths_work_mode;

typedef enum
{
	MUSICMODE_MADDEN = 0,
	MUSICMODE_ROCK,
	MUSICMODE_CLASSIC,
	MUSICMODE_SOFT,
	
	MUSICMODE_MAX,
}en_stripLigths_music;

typedef enum
{
	CTRLCMD_DYNAMICALLY_NOTSAVE,
	CTRLCMD_DYNAMICALLY_SAVE,
	CTRLCMD_STATE,
	CTRLCMD_RESTORE_FACTORY,
} en_stripLigths_CMD;
	
typedef struct
{
	unsigned char mic_sensitivity;
	unsigned char mic_rate;
	//uint16_t corlor_H;
	//uint8_t corlor_S;
	//uint8_t corlor_B;
} st_stripLigths_micInfo; 

typedef struct
{
	unsigned char type;
	unsigned short color_H;
	unsigned char color_S;
	unsigned char color_B;
	unsigned char white_temp;
	unsigned char white_bright;
} st_stripLigths_colorInfo; 

typedef struct
{
	uint8_t cmd;
	uint8_t sceneIndex;
	uint8_t changeType;
	uint8_t changeSpeed;
	uint8_t groupNum;
	st_stripLigths_colorInfo colorInfo[8];
} st_stripLigths_sceneInfo; 


typedef struct
{
	uint8_t lightSwitch;
	en_stripLigths_work_mode  workMode;

	uint16_t corlor_H;
	uint8_t corlor_S;
	uint8_t corlor_B;

	uint8_t white_temp;
	uint8_t white_bright;
	
	uint8_t cur_music_index;
	st_stripLigths_micInfo  micInfo[MUSICMODE_MAX];

	uint8_t cur_scene_index;
	st_stripLigths_sceneInfo sceneInfo[20];

	uint8_t sceneInfo_temp_flag;
	st_stripLigths_sceneInfo sceneInfo_temp;
} st_ya_stripLigths_workData; 

extern ya_hal_os_queue_t ya_striplight_queue;

//adc api
extern void set_music_param(uint8_t swtich,uint8_t mode,uint8_t music,uint8_t mic_sensitivity,uint8_t mic_rate);
extern void ya_stripLights_adc(void);

//clear all scene data
//extern int32_t ya_clear_user_data(void);

//button to queue
extern void ya_stripLights_app_button_event_into_queue(uint8_t msg_event,uint8_t msg_subtype);

//cloud event to queue
extern void ya_stripLights_app_cloud_event_into_queue(uint8_t *buf, uint16_t len);

//get update flag
extern bool ya_get_updata_stripLights(void);

//clear update flag
extern void ya_clear_updata_stripLights(void);

//report state to cloud
int32_t ya_stripLights_cloud_attriReport(void);

void ya_stripLights_app_factory_test(void);

void ya_striplights_check_OFF(void);

void  ya_stripLights_app_infraredHandle(uint8_t type, uint8_t subtype, uint8_t *buf, uint16_t len);

void ya_stripLights_app_sceneInit(void);

void ya_stripLights_switchoff(void);

void ya_stripLights_app_netConfigDisplay(void);

void ya_stripLights_app_factory_test(void);

void ya_striplights_app_init_mode(void);


#endif

