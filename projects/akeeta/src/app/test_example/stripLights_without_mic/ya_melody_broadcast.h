
#ifndef _YA_MELODY_BROADCAST_H_
#define _YA_MELODY_BROADCAST_H_

typedef enum
{
	YA_RHYTHM_DEVICE_DISCOVER_CMD = 0x00,
	YA_RHYTHM_DEVICE_CONFIRM_CMD  = 0x01,
	YA_RHYTHM_DEVICE_CONTROL_SET_LED_COLOR_CMD = 0x10,
	YA_RHYTHM_DEVICE_CONTROL_SET_LED_ARG_CMD = 0x11,
	YA_RHYTHM_DEVICE_CONTROL_SET_LED_MODE_CMD = 0x12,
}ya_rhythm_msg_type_t;


extern int32_t ya_start_rhythm_broadcast(void);

#endif
