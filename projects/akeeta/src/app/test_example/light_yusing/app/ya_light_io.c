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
#include "ya_light_io.h"
#include "hls_rgb.h"
#include "ya_hal_pwm.h"
#include "ya_light_example.h"
#include "ya_flash.h"
#include "ya_mode_api.h"

void ya_pwm_led_write(unsigned int r,unsigned int g,unsigned int b,unsigned int c,unsigned int w)
{
#if (FLOAT_SUPPORT == 1)
	ya_hal_pwm_write(PWM_R,(float)(r/255.0));
	ya_hal_pwm_write(PWM_G,(float)(g/255.0));
	ya_hal_pwm_write(PWM_B,(float)(b/255.0));
	ya_hal_pwm_write(PWM_COOL,(float)(c/255.0));
	ya_hal_pwm_write(PWM_WARM,(float)(w/255.0));
#else
	ya_hal_pwm_write(PWM_R,(uint32_t)(r/255));
	ya_hal_pwm_write(PWM_G,(uint32_t)(g/255));
	ya_hal_pwm_write(PWM_B,(uint32_t)(b*/255));
	ya_hal_pwm_write(PWM_COOL,(uint32_t)(c/255));
	ya_hal_pwm_write(PWM_WARM,(uint32_t)(w/255));
#endif

}

uint8_t R_set = 0;
uint8_t G_set = 0;
uint8_t B_set = 0;
uint8_t C_set = 0;
uint8_t W_set = 0;


void ya_pwm_control_step(YA_PWM_NAME ya_pwm_num, uint8_t begin_value, uint8_t end_value)
{
	uint8_t index = 0, start_value = 0, delta_value = 0; uint8_t count = 0;
	
	if (end_value > begin_value)
	{
		start_value = begin_value;
		delta_value = end_value - begin_value;

		count = 0;
		for (index = 0; index < delta_value; index++)
		{
			#if (FLOAT_SUPPORT == 1)
			ya_hal_pwm_write(ya_pwm_num,(float)((start_value + 1 + index)/255.0));
			#else
			ya_hal_pwm_write(ya_pwm_num,(float)((start_value + 1 + index)/255));
			#endif
			if (count > 3)
			{
				ya_delay(10);
				count = 0;
			} else
			{
				count++;
			}
				
		}

	}else 
	{
		start_value = begin_value;
		delta_value = begin_value - end_value;

		count = 0;
		for (index = 0; index < delta_value; index++)
		{
			#if (FLOAT_SUPPORT == 1)
			ya_hal_pwm_write(ya_pwm_num,(float)((start_value - 1 - index)/255.0));
			#else
			ya_hal_pwm_write(ya_pwm_num,(float)((start_value - 1 - index)/255));
			#endif
			if (count > 3)
			{
				ya_delay(4);
				count = 0;
			} else
			{
				count++;
			}

		}

	}
}

void ya_pwm_led_write_with_step(unsigned char r,unsigned char g,unsigned char b,unsigned char c,unsigned char w)
{
	//ya_printf(C_LOG_INFO, "2r=%d, g=%d, b=%d, c=%d, w=%d\n",r,g,b,c,w);

	ya_pwm_control_step(PWM_R, R_set, r);
	ya_pwm_control_step(PWM_G, G_set, g);
	ya_pwm_control_step(PWM_B, B_set, b);
	
	ya_pwm_control_step(PWM_COOL, C_set, c);
	ya_pwm_control_step(PWM_WARM, W_set, w);


	R_set = r;
	G_set = g;
	B_set = b;
	C_set = c;
	W_set = w;

	//ya_printf(C_LOG_INFO, "end control\r\n");
}


void ya_write_light_para(ya_cloud_light_data_t ya_ligth_para)
{
	//ya_printf(C_LOG_INFO, "set light para: %d, %d, %d, %d, %d\n", ya_ligth_para.w_l, ya_ligth_para.w_color,  ya_ligth_para.c_h,ya_ligth_para.c_s,ya_ligth_para.c_b);
	unsigned char r,g,b;
	unsigned char c,w;

	HSVtoRGB(&r,&g,&b,ya_ligth_para.c_h,ya_ligth_para.c_s,ya_ligth_para.c_b);

	c=100- ya_ligth_para.w_color;
	w=ya_ligth_para.w_color;
#if (FLOAT_SUPPORT == 1)
	c=c*(ya_ligth_para.w_l)*2.55/100;
	w=w*(ya_ligth_para.w_l)*2.55/100; 
#else
	c=c*(ya_ligth_para.w_l)*255/10000;
	w=w*(ya_ligth_para.w_l)*255/10000; 
#endif
	ya_pwm_led_write_with_step(r,g,b,c,w);
}

extern void ya_clear_user_data(void);
void ya_light_read_power_on_flag(void)
{
	uint8_t buf[10];
	int32_t ret = -1;
	uint16_t flash_read_len = 0;

	memset(buf, 0, 10);
	flash_read_len = 10;
	ret = ya_read_flash_with_var_len(YA_LIGHT_FLASH_PARA_ADDR, buf, &flash_read_len, 1, FLASH_AES_DISABLE);

	if (ret != 0)
		memset(buf, 0, 10);

	buf[0]++;

	ya_printf(C_LOG_INFO,"power flag: %d\r\n", buf[0]); 	

	if (buf[0] >= 3)
	{
		ya_clear_user_data();
		ya_set_toggle_mode(1);
		buf[0] = 0;
	}
		
	ret = ya_write_flash(YA_LIGHT_FLASH_PARA_ADDR, buf, 10, 1, FLASH_AES_DISABLE);
}

void ya_light_clear_power_on_flag(void)
{
	int32_t ret = -1;
	uint8_t buf[10];

	memset(buf, 0, 10);
	ret = ya_write_flash(YA_LIGHT_FLASH_PARA_ADDR, buf, 10,1, FLASH_AES_DISABLE);

	if(ret == 0)
		ya_printf(C_LOG_INFO,"ya_light_clear_power_on_flag ok\r\n");		
}

static void ya_clear_power_on_flag_callback( TimerHandle_t xTimer )
{
	ya_light_clear_power_on_flag();
}

void ya_init_light_io(void)
{
	TimerHandle_t xTimer;
	xTimer = xTimerCreate("power_on_clear_flag", ya_hal_os_msec_to_ticks(5000), pdFALSE, (void * )0, ya_clear_power_on_flag_callback);
	if( xTimer != NULL )
	{
		xTimerStart(xTimer, 0);
	}

	ya_light_read_power_on_flag();	
}

