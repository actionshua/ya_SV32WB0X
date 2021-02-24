#ifndef YA_STRIPLIGHTS_DISPLAY_H_
#define YA_STRIPLIGHTS_DISPLAY_H_


typedef enum
{
	STATIC_TYPE  = 0x00,
	STEP_TYPE,
	SHADE_TYPE,	
	BREAK_TYPE,	
	IMMEDIATELY_TYPE,	
}ya_lightchange_type;

typedef struct
{
	uint8_t cmd;
	uint8_t sceneIndex;
	uint8_t changeType;
	uint8_t changeSpeed;
	uint8_t groupNum;
	st_stripLigths_colorInfo colorInfo[8];
} ya_display_stripsLight_t; 


extern void ya_stripLights_pwmUpdate_into_queue(uint8_t *buf, uint16_t len);

extern int32_t ya_stripLights_display_start(void);

#endif
