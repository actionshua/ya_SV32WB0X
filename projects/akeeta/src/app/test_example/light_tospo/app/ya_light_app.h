#ifndef YA_STRIPLIGHTS_APP_H_
#define YA_STRIPLIGHTS_APP_H_
#include "ya_common.h"

typedef enum
{
	SCENE_READING,
	SCENE_WORK,
	SCENE_GOOD_NIGHT,
	SCENE_LEISURE,
	
	SCENE_MAX,
 } en_light_SCENE;

typedef enum
{
	WORKMODE_WHITE = 0,
	WORKMODE_COLOR,
	WORKMODE_SCENE,

	WORKMODE_MAX,
}en_light_work_mode;

	
typedef struct
{
	unsigned char type;
	unsigned short color_H;
	unsigned char color_S;
	unsigned char color_B;
	unsigned char white_temp;
	unsigned char white_bright;
} st_light_colorInfo; 

typedef struct
{
	uint8_t cmd;
	uint8_t sceneIndex;
	uint8_t changeType;
	uint8_t changeSpeed;
	uint8_t groupNum;
	st_light_colorInfo colorInfo[8];
} st_light_sceneInfo; 


typedef struct
{
	uint8_t lightSwitch;
	en_light_work_mode  workMode;

	uint16_t corlor_H;
	uint8_t corlor_S;
	uint8_t corlor_B;

	uint8_t white_temp;
	uint8_t white_bright;

	uint8_t cur_scene_index;
	st_light_sceneInfo sceneInfo[4];
} st_ya_light_workData; 

extern ya_hal_os_queue_t ya_light_queue;

//cloud event to queue
extern void ya_light_app_cloud_event_into_queue(uint8_t *buf, uint16_t len);

//get update flag
extern bool ya_get_updata_light(void);

//clear update flag
extern void ya_clear_updata_light(void);

//report all state to cloud
extern int32_t ya_light_cloud_attriReport_All(void);

//report state to cloud
int32_t ya_light_cloud_attriReport(void);

//init the light app
extern void ya_light_app_init(void);

//init the config network display
extern void ya_light_app_netConfigDisplay(void);

//config ok display
extern void ya_light_app_ConfigOkDisplay(void);

//swtich the light off
extern void ya_light_switchoff(void);

//app cloud handle
extern void ya_light_app_cloud_handle(uint8_t *buf, uint16_t len);
#endif

