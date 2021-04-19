#include "ya_common.h"
#include "ya_app_main.h"
#include "ya_hal_pwm.h"
#include "ya_light_product_test.h"
#include "ya_light_example.h"
#include "ya_api_thing_uer_define.h"


#define LOWEST_LIGHT	25
#define STEP_LIGHT		1
 
typedef enum
{	
	LICENSE_TEST = 0,
	RGBCW_TEST,
	AGING_TEST,
	
	LIGHT_ROUTER_LOW_RSSI,
	LIGHT_LICENSE_FAILED,

	LIGHT_TEST_OK,
}light_test_machine_t;


typedef struct
{
	uint8_t test_state;
	uint8_t aging_time;
}ya_light_test_para_t;


ya_light_test_para_t ya_light_test_para;

void ya_pwm_led_write(unsigned int r,unsigned int g,unsigned int b,unsigned int c,unsigned int w)
{
#if (FLOAT_SUPPORT == 1)

#if (LIGHT_TYPE == 0)
	ya_hal_pwm_write(PWM_R_INDEX,(float)(r/255.0));
	ya_hal_pwm_write(PWM_G_INDEX,(float)(g/255.0));
	ya_hal_pwm_write(PWM_B_INDEX,(float)(b/255.0));
	ya_hal_pwm_write(PWM_COOL_INDEX,(float)(c/255.0));
	ya_hal_pwm_write(PWM_WARM_INDEX,(float)(w/255.0));
#else 
	ya_hal_pwm_write(PWM_COOL_INDEX,(float)(c/255.0));
	ya_hal_pwm_write(PWM_WARM_INDEX,(float)(w/255.0));
#endif

#else

#if (LIGHT_TYPE == 0)
	ya_hal_pwm_write(PWM_R_INDEX,(uint32_t)(r/255));
	ya_hal_pwm_write(PWM_G_INDEX,(uint32_t)(g/255));
	ya_hal_pwm_write(PWM_B_INDEX,(uint32_t)(b/255));
	ya_hal_pwm_write(PWM_COOL_INDEX,(uint32_t)(c/255));
	ya_hal_pwm_write(PWM_WARM_INDEX,(uint32_t)(w/255));
#else
	ya_hal_pwm_write(PWM_COOL_INDEX,(uint32_t)(c/255));
	ya_hal_pwm_write(PWM_WARM_INDEX,(uint32_t)(w/255));
#endif

#endif

}


int32_t ya_rgbcw_test(uint8_t test_type)
{
	uint16_t count = 0;

	if(test_type == 0)
	{
		for (count = 0; count < 24; count++)
		{
			ya_pwm_led_write(255*100,0,0,0,0);
			ya_delay(1000);		
			ya_pwm_led_write(0,255*100,0,0,0);
			ya_delay(1000);		
			ya_pwm_led_write(0,0,255*100,0,0);
			ya_delay(1000);	

			//cool control
			#if (CW_PWM == 1)
			ya_pwm_led_write(0,0,0,255*100,0);
			#else
			ya_pwm_led_write(0,0,0,255*100,255*100);
			#endif
			
			ya_delay(1000);	

			//warm control
			#if (CW_PWM == 1)
			ya_pwm_led_write(0,0,0,0,255*100);
			#else
			ya_pwm_led_write(0,0,0,0,255*100);
			#endif	
			ya_delay(1000);	
		}
	}else
	{
		while(1)
		{
			ya_pwm_led_write(255*100,0,0,0,0);
			ya_delay(1000);		
			ya_pwm_led_write(0,255*100,0,0,0);
			ya_delay(1000);		
			ya_pwm_led_write(0,0,255*100,0,0);
			ya_delay(1000);	

			//cool control
			#if (CW_PWM == 1)
			ya_pwm_led_write(0,0,0,255*100,0);
			#else
			ya_pwm_led_write(0,0,0,255*100,255*100);
			#endif
			
			ya_delay(1000);	

			//warm control
			#if (CW_PWM == 1)
			ya_pwm_led_write(0,0,0,0,255*100);
			#else
			ya_pwm_led_write(0,0,0,0,255*100);
			#endif
			
			ya_delay(1000);

		}
	}
	return 0;
}

int32_t ya_cw_test(uint8_t test_type)
{
	uint16_t count = 0;

	if(test_type == 0)
	{
		for (count = 0; count < 60; count++)
		{	
			#if (CW_PWM == 1)
			ya_pwm_led_write(0,0,0,255*100,0);
			#else
			ya_pwm_led_write(0,0,0,255*100,255*100);
			#endif
			
			ya_delay(1000);	

			#if (CW_PWM == 1)
			ya_pwm_led_write(0,0,0,0,255*100);
			#else
			ya_pwm_led_write(0,0,0,0,255*100);
			#endif
			
			ya_delay(1000);	
		}
	}else
	{
		while(1)
		{	

			#if (CW_PWM == 1)
			ya_pwm_led_write(0,0,0,255*100,0);
			#else
			ya_pwm_led_write(0,0,0,255*100,255*100);
			#endif
			
			ya_delay(1000);	

			#if (CW_PWM == 1)
			ya_pwm_led_write(0,0,0,0,255*100);
			#else
			ya_pwm_led_write(0,0,0,0,255*100);
			#endif
			
			ya_delay(1000);
		}
	}
	return 0;
}

int32_t ya_aging_rgbcw_test()
{
	if(ya_light_test_para.aging_time >= 50)
	{
		ya_light_test_para.aging_time = 0;
		return 0;
	}
	
	for (; ya_light_test_para.aging_time < 50; ya_light_test_para.aging_time++)
	{
		if(ya_light_test_para.aging_time < 20)
		{
			ya_printf(C_LOG_INFO, "cool long time test\r\n");
			#if (CW_PWM == 1)
			ya_pwm_led_write(0,0,0,255*100,0);
			#else
			ya_pwm_led_write(0,0,0,255*100,255*100);
			#endif
			
			ya_delay(60 *1000);		
		}else if (ya_light_test_para.aging_time < 40)
		{
			ya_printf(C_LOG_INFO, "warm long time test\r\n");
			#if (CW_PWM == 1)
			ya_pwm_led_write(0, 0, 0, 0,255*100);
			#else
			ya_pwm_led_write(0, 0, 0, 0, 255*100);
			#endif

			ya_delay(60 *1000);		
		}else 
		{
			ya_printf(C_LOG_INFO, "RGB long time test\r\n");
			ya_pwm_led_write(255*100,255*100,255*100,0,0);
			ya_delay(60 *1000);		
		}
	}
	return 0;

}

int32_t ya_aging_cw_test()
{
	if(ya_light_test_para.aging_time >= 40)
	{
		ya_light_test_para.aging_time = 0;
		return 0;
	}
	
	for (; ya_light_test_para.aging_time < 40; ya_light_test_para.aging_time++)
	{
		if(ya_light_test_para.aging_time < 20)
		{
			ya_printf(C_LOG_INFO, "cool long time test\r\n");
			#if (CW_PWM == 1)
			ya_pwm_led_write(0,0,0,255*100,0);
			#else
			ya_pwm_led_write(0,0,0,255*100,255*100);
			#endif
			
			ya_delay(60 *1000);		
		}else if (ya_light_test_para.aging_time < 40)
		{
			ya_printf(C_LOG_INFO, "warm long time test\r\n");
			#if (CW_PWM == 1)
			ya_pwm_led_write(0, 0, 0, 0,255*100);
			#else
			ya_pwm_led_write(0, 0, 0, 0, 255*100);
			#endif

			ya_delay(60 *1000);		
		}
	}
	return 0;
}

int32_t ya_ligth_router_low_rssi_with_CW()
{
	int  i = 0;
	
	while(1)
	{
		//dim to bright 	
		for (i = LOWEST_LIGHT; i <= 255; i = i + STEP_LIGHT)
		{
			if (i + STEP_LIGHT > 255)
			{
				#if (CW_PWM == 1)
				ya_pwm_led_write(0,0,0,255*100,0);
				#else
				ya_pwm_led_write(0,0,0,255*100,255*100);
				#endif
				
				ya_delay(6);
				break;
			}else
			{
				#if (CW_PWM == 1)
				ya_pwm_led_write(0,0,0,i*100,0);
				#else
				ya_pwm_led_write(0,0,0,255*100,i*100);
				#endif
				ya_delay(6);
			}
		}
		//bright to dim
		for (i = 255; i >= LOWEST_LIGHT; i = i - STEP_LIGHT)
		{
			if (i - STEP_LIGHT < LOWEST_LIGHT)
			{
				#if (CW_PWM == 1)
				ya_pwm_led_write(0, 0, 0, LOWEST_LIGHT*100, 0);
				#else
				ya_pwm_led_write(0, 0, 0, 255*100, LOWEST_LIGHT*100);
				#endif
				ya_delay(6);
				break;				
			}else
			{
				#if (CW_PWM == 1)
				ya_pwm_led_write(0, 0, 0, i*100, 0);
				#else
				ya_pwm_led_write(0, 0, 0, 255*100, i*100);
				#endif
				ya_delay(6);
			}
		}

		for (i=0; i<2; i++)
		{
			#if (CW_PWM == 1)
			ya_pwm_led_write(0,0,0,255*100,0);
			#else
			ya_pwm_led_write(0,0,0,255*100,255*100);
			#endif
			
			ya_delay(250);

			#if (CW_PWM == 1)
			ya_pwm_led_write(0,0,0,0,0);
			#else
			ya_pwm_led_write(0,0,0,255*100,0);
			#endif
			
			ya_delay(250);
		}

	}

	return 0;
}

int32_t ya_ligth_rgbcw_router_license_failed()
{
	while(1)
	{
		//on
		ya_pwm_led_write(LOWEST_LIGHT*100,0,0,0,0);
		ya_delay(3000);

		//off
		ya_pwm_led_write(0,0,0,0,0);
		ya_delay(3000);
	}
	return 0;
}

int32_t ya_ligth_cw_router_license_failed()
{
	while(1)
	{
		//on
		ya_pwm_led_write(0,0,0,LOWEST_LIGHT*100,0);
		ya_delay(3000);

		//off
		ya_pwm_led_write(0,0,0,0,0);
		ya_delay(3000);
	}
	return 0;
}

int32_t ya_ligth_rgbcw_test_ok()
{
	ya_pwm_led_write(0,LOWEST_LIGHT*100,0,0,0);
	while(1)
	{
		ya_delay(1000);
	}
	return 0;
}

int32_t ya_ligth_cw_test_ok()
{
	#if (CW_PWM == 1)
	ya_pwm_led_write(0,0,0,LOWEST_LIGHT*100,LOWEST_LIGHT*100);
	#else
	ya_pwm_led_write(0,0,0,127*100,LOWEST_LIGHT*100);
	#endif
	
	while(1)
	{
		ya_delay(1000);
	}
	return 0;
}


void ya_light_factory_test(int32_t router_rssi, uint8_t test_type, CLOUD_T cloud_type)
{
	int32_t ret = 0;

	if (router_rssi < -60)
		ya_light_test_para.test_state = LIGHT_ROUTER_LOW_RSSI;
	else
		ya_light_test_para.test_state = LICENSE_TEST;

	ya_light_test_para.aging_time = 0;

	ya_delay(200);
	
	while(1)
	{
		switch(ya_light_test_para.test_state)
		{
			case LICENSE_TEST:
			{
				ya_printf(C_LOG_INFO, "LICENSE_TEST\r\n");
				if (cloud_type == AKEETA_OVERSEA)
				{
					if (ya_check_us_license_exit()==0)
						ya_light_test_para.test_state = RGBCW_TEST;
					else
						ya_light_test_para.test_state = LIGHT_LICENSE_FAILED;
					
				}else if (cloud_type == AKEETA_CN)
				{
					if (ya_check_cn_license_exit()==0)
						ya_light_test_para.test_state = RGBCW_TEST;
					else
						ya_light_test_para.test_state = LIGHT_LICENSE_FAILED;

				}else if (cloud_type == UNKNOWN_CLOUD_TYPE)
				{
					if (ya_check_cn_license_exit()==0 && ya_check_us_license_exit()==0)
						ya_light_test_para.test_state = RGBCW_TEST;
					else
						ya_light_test_para.test_state = LIGHT_LICENSE_FAILED;
					
				}else
				{
					ya_light_test_para.test_state = LIGHT_LICENSE_FAILED;
				}
			}
			break;


			case RGBCW_TEST:
			{
				ya_printf(C_LOG_INFO, "RGBCW_TEST\r\n");
			
				//2 miniues;
				#if (LIGHT_TYPE == 1)
				ret = ya_cw_test(test_type);
				#else
				ret = ya_rgbcw_test(test_type);
				#endif
				
				if(ret == 0)
					ya_light_test_para.test_state = AGING_TEST;
			}	
			break;

			case AGING_TEST:
			{
				ya_printf(C_LOG_INFO, "AGING_TEST, %d\r\n", ya_light_test_para.aging_time);

				#if (LIGHT_TYPE == 1)
				ret = ya_aging_cw_test();
				#else
				ret = ya_aging_rgbcw_test();
				#endif
				
				if(ret == 0)
				{
					#if (LIGHT_TYPE == 1)
					ya_ligth_cw_test_ok();
					#else
					ya_ligth_rgbcw_test_ok();
					#endif
					ya_light_test_para.test_state = LIGHT_TEST_OK;
				}
			}	
			break;

			case LIGHT_ROUTER_LOW_RSSI:
			ya_printf(C_LOG_INFO, "LIGHT_ROUTER_LOW_RSSI\r\n");
			ya_ligth_router_low_rssi_with_CW();
			break;

			case LIGHT_LICENSE_FAILED:
			ya_printf(C_LOG_INFO, "LIGHT_LICENSE_FAILED\r\n");
			
			#if (LIGHT_TYPE == 1)
			ya_ligth_cw_router_license_failed();
			#else
			ya_ligth_rgbcw_router_license_failed();
			#endif
			break;

			case LIGHT_TEST_OK:

			break;

			default:

			break;
		}

	}
}


