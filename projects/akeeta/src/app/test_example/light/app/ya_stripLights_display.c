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
#include "ya_hal_pwm.h"
#include "ya_light_io.h"
#include "hls_rgb.h"
#include "ya_stripLights_display.h"
#include "ya_light_example.h"

#define YA_STRIPLIGHTSDISPLAY_COLORCHANGE_MAXTIME    500 //ms
#define YA_STRIPLIGHTSDISPLAY_PWMCHANGE_MAXTIME      1300 //ms

typedef enum
{
	PWM_DISPLAY_IDLE,
	PWM_DISPLAY_START,
	PWM_DISPLAY_WATING,
	PWM_DISPLAY_UP,
	PWM_DISPLAY_HOLD,
	PWM_DISPLAY_DOWN,
	PWM_DISPLAY_STOP,
}ya_en_pwmDisplayCtrl;

typedef struct
{
	int32_t pwmDutyNew;
	int32_t pwmDutyStep;
}ya_st_pwmChannelInfo;

typedef struct
{
	ya_st_pwmChannelInfo pwmChannelInfo[5];
}ya_st_pwmCtrlInfo;

typedef struct
{
	int32_t displayState;
	
	int32_t timerCounter;
	int32_t timerIntervalWaiting;
	int32_t timerIntervalChangeUp;
	int32_t timerIntervalHold;
	int32_t timerIntervalChangeDown;
	
	int32_t changeType;
	int32_t changeSpeed;

	int32_t pwmGroupLen;
	int32_t pwmGroupIndex;
	ya_st_pwmCtrlInfo pwmGroupInfo[8];
	
	int32_t pwmDutyCur[5];
	
}ya_st_stripLightsDisplay_CtrlInfo;

ya_st_stripLightsDisplay_CtrlInfo ya_stripLightsDisplay_CtrlGroupInfo;

uint32_t ya_colorTemperatureToRGB_table[]=
{
	 0xffb969,//3000 K   2deg  0.4388 0.4095  2.784e+13    1.0000 0.4870 0.1411  255 185 105  #ffb969
	 0xffb46b,//3000 K  10deg  0.4404 0.4026  2.939e+13    1.0000 0.4589 0.1483  255 180 107  #ffb46b
	 0xffbd6f,//3100 K   2deg  0.4320 0.4070  3.657e+13    1.0000 0.5067 0.1602  255 189 111  #ffbd6f
	 0xffb872,//3100 K  10deg  0.4333 0.4002  3.866e+13    1.0000 0.4781 0.1677  255 184 114  #ffb872
	 0xffc076,//3200 K   2deg  0.4254 0.4044  4.725e+13    1.0000 0.5259 0.1800  255 192 118  #ffc076
	 0xffbb78,//3200 K  10deg  0.4266 0.3976  5.002e+13    1.0000 0.4970 0.1879  255 187 120  #ffbb78
	 0xffc37c,//3300 K   2deg  0.4192 0.4018  6.012e+13    1.0000 0.5447 0.2005  255 195 124  #ffc37c
	 0xffbe7e,//3300 K  10deg  0.4202 0.3950  6.374e+13    1.0000 0.5155 0.2087  255 190 126  #ffbe7e
	 0xffc682,//3400 K   2deg  0.4132 0.3990  7.545e+13    1.0000 0.5630 0.2216  255 198 130  #ffc682
	 0xffc184,//3400 K  10deg  0.4140 0.3923  8.010e+13    1.0000 0.5336 0.2301  255 193 132  #ffc184
	 0xffc987,//3500 K   2deg  0.4075 0.3962  9.349e+13    1.0000 0.5809 0.2433  255 201 135  #ffc987
	 0xffc489,//3500 K  10deg  0.4082 0.3895  9.939e+13    1.0000 0.5515 0.2520  255 196 137  #ffc489
	 0xffcb8d,//3600 K   2deg  0.4021 0.3934  1.145e+14    1.0000 0.5983 0.2655  255 203 141  #ffcb8d
	 0xffc78f,//3600 K  10deg  0.4026 0.3868  1.219e+14    1.0000 0.5689 0.2745  255 199 143  #ffc78f
	 0xffce92,//3700 K   2deg  0.3969 0.3905  1.387e+14    1.0000 0.6153 0.2881  255 206 146  #ffce92
	 0xffc994,//3700 K  10deg  0.3973 0.3841  1.479e+14    1.0000 0.5860 0.2974  255 201 148  #ffc994
	 0xffd097,//3800 K   2deg  0.3919 0.3877  1.665e+14    1.0000 0.6318 0.3112  255 208 151  #ffd097
	 0xffcc99,//3800 K  10deg  0.3922 0.3813  1.776e+14    1.0000 0.6028 0.3207  255 204 153  #ffcc99
	 0xffd39c,//3900 K   2deg  0.3872 0.3849  1.979e+14    1.0000 0.6480 0.3346  255 211 156  #ffd39c
	 0xffce9f,//3900 K  10deg  0.3873 0.3786  2.115e+14    1.0000 0.6193 0.3444  255 206 159  #ffce9f
	 0xffd5a1,//4000 K   2deg  0.3827 0.3820  2.333e+14    1.0000 0.6636 0.3583  255 213 161  #ffd5a1
	 0xffd1a3,//4000 K  10deg  0.3827 0.3759  2.496e+14    1.0000 0.6354 0.3684  255 209 163  #ffd1a3
	 0xffd7a6,//4100 K   2deg  0.3784 0.3793  2.729e+14    1.0000 0.6789 0.3823  255 215 166  #ffd7a6
	 0xffd3a8,//4100 K  10deg  0.3783 0.3733  2.923e+14    1.0000 0.6511 0.3927  255 211 168  #ffd3a8
	 0xffd9ab,//4200 K   2deg  0.3743 0.3765  3.169e+14    1.0000 0.6938 0.4066  255 217 171  #ffd9ab
	 0xffd5ad,//4200 K  10deg  0.3741 0.3707  3.397e+14    1.0000 0.6666 0.4172  255 213 173  #ffd5ad
	 0xffdbaf,//4300 K   2deg  0.3704 0.3738  3.654e+14    1.0000 0.7083 0.4310  255 219 175  #ffdbaf
	 0xffd7b1,//4300 K  10deg  0.3701 0.3681  3.922e+14    1.0000 0.6817 0.4419  255 215 177  #ffd7b1
	 0xffddb4,//4400 K   2deg  0.3666 0.3711  4.188e+14    1.0000 0.7223 0.4556  255 221 180  #ffddb4
	 0xffd9b6,//4400 K  10deg  0.3662 0.3656  4.500e+14    1.0000 0.6966 0.4668  255 217 182  #ffd9b6
	 0xffdfb8,//4500 K   2deg  0.3631 0.3685  4.771e+14    1.0000 0.7360 0.4803  255 223 184  #ffdfb8
	 0xffdbba,//4500 K  10deg  0.3625 0.3631  5.132e+14    1.0000 0.7111 0.4919  255 219 186  #ffdbba
	 0xffe1bc,//4600 K   2deg  0.3596 0.3659  5.406e+14    1.0000 0.7494 0.5051  255 225 188  #ffe1bc
	 0xffddbe,//4600 K  10deg  0.3590 0.3607  5.820e+14    1.0000 0.7253 0.5170  255 221 190  #ffddbe
	 0xffe2c0,//4700 K   2deg  0.3563 0.3634  6.093e+14    1.0000 0.7623 0.5299  255 226 192  #ffe2c0
	 0xffdfc2,//4700 K  10deg  0.3557 0.3583  6.567e+14    1.0000 0.7392 0.5422  255 223 194  #ffdfc2
	 0xffe4c4,//4800 K   2deg  0.3532 0.3609  6.835e+14    1.0000 0.7750 0.5548  255 228 196  #ffe4c4
	 0xffe1c6,//4800 K  10deg  0.3524 0.3560  7.373e+14    1.0000 0.7528 0.5675  255 225 198  #ffe1c6
	 0xffe5c8,//4900 K   2deg  0.3502 0.3585  7.632e+14    1.0000 0.7872 0.5797  255 229 200  #ffe5c8
	 0xffe3ca,//4900 K  10deg  0.3494 0.3538  8.240e+14    1.0000 0.7661 0.5928  255 227 202  #ffe3ca
	 0xffe7cc,//5000 K   2deg  0.3473 0.3561  8.485e+14    1.0000 0.7992 0.6045  255 231 204  #ffe7cc
	 0xffe4ce,//5000 K  10deg  0.3464 0.3516  9.170e+14    1.0000 0.7792 0.6180  255 228 206  #ffe4ce
	 0xffe8d0,//5100 K   2deg  0.3446 0.3538  9.396e+14    1.0000 0.8108 0.6293  255 232 208  #ffe8d0
	 0xffe6d2,//5100 K  10deg  0.3436 0.3494  1.016e+15    1.0000 0.7919 0.6433  255 230 210  #ffe6d2
	 0xffead3,//5200 K   2deg  0.3419 0.3516  1.036e+15    1.0000 0.8221 0.6541  255 234 211  #ffead3
	 0xffe8d5,//5200 K  10deg  0.3409 0.3473  1.122e+15    1.0000 0.8044 0.6685  255 232 213  #ffe8d5
	 0xffebd7,//5300 K   2deg  0.3394 0.3494  1.139e+15    1.0000 0.8330 0.6787  255 235 215  #ffebd7
	 0xffe9d9,//5300 K  10deg  0.3383 0.3453  1.234e+15    1.0000 0.8167 0.6937  255 233 217  #ffe9d9
	 0xffedda,//5400 K   2deg  0.3369 0.3472  1.248e+15    1.0000 0.8437 0.7032  255 237 218  #ffedda
	 0xffebdc,//5400 K  10deg  0.3358 0.3433  1.353e+15    1.0000 0.8286 0.7187  255 235 220  #ffebdc
	 0xffeede,//5500 K   2deg  0.3346 0.3451  1.363e+15    1.0000 0.8541 0.7277  255 238 222  #ffeede
	 0xffece0,//5500 K  10deg  0.3334 0.3413  1.479e+15    1.0000 0.8403 0.7437  255 236 224  #ffece0
	 0xffefe1,//5600 K   2deg  0.3323 0.3431  1.484e+15    1.0000 0.8642 0.7519  255 239 225  #ffefe1
	 0xffeee3,//5600 K  10deg  0.3311 0.3394  1.611e+15    1.0000 0.8518 0.7686  255 238 227  #ffeee3
	 0xfff0e4,//5700 K   2deg  0.3302 0.3411  1.611e+15    1.0000 0.8740 0.7760  255 240 228  #fff0e4
	 0xffefe6,//5700 K  10deg  0.3289 0.3376  1.750e+15    1.0000 0.8630 0.7933  255 239 230  #ffefe6
	 0xfff1e7,//5800 K   2deg  0.3281 0.3392  1.744e+15    1.0000 0.8836 0.8000  255 241 231  #fff1e7
	 0xfff0e9,//5800 K  10deg  0.3268 0.3358  1.896e+15    1.0000 0.8740 0.8179  255 240 233  #fff0e9
	 0xfff3ea,//5900 K   2deg  0.3261 0.3373  1.883e+15    1.0000 0.8929 0.8238  255 243 234  #fff3ea
	 0xfff2ec,//5900 K  10deg  0.3247 0.3341  2.049e+15    1.0000 0.8847 0.8424  255 242 236  #fff2ec
	 0xfff4ed,//6000 K   2deg  0.3242 0.3355  2.028e+15    1.0000 0.9019 0.8473  255 244 237  #fff4ed
	 0xfff3ef,//6000 K  10deg  0.3228 0.3324  2.208e+15    1.0000 0.8952 0.8666  255 243 239  #fff3ef
	 0xfff5f0,//6100 K   2deg  0.3223 0.3337  2.179e+15    1.0000 0.9107 0.8707  255 245 240  #fff5f0
	 0xfff4f2,//6100 K  10deg  0.3209 0.3307  2.374e+15    1.0000 0.9055 0.8907  255 244 242  #fff4f2
	 0xfff6f3,//6200 K   2deg  0.3205 0.3319  2.337e+15    1.0000 0.9193 0.8939  255 246 243  #fff6f3
	 0xfff5f5,//6200 K  10deg  0.3190 0.3291  2.548e+15    1.0000 0.9156 0.9147  255 245 245  #fff5f5
	 0xfff7f5,//6300 K   2deg  0.3188 0.3302  2.500e+15    1.0000 0.9276 0.9168  255 247 245  #fff7f5
	 0xfff6f8,//6300 K  10deg  0.3173 0.3275  2.728e+15    1.0000 0.9254 0.9384  255 246 248  #fff6f8
	 0xfff8f8,//6400 K   2deg  0.3171 0.3286  2.669e+15    1.0000 0.9357 0.9396  255 248 248  #fff8f8
	 0xfff8fb,//6400 K  10deg  0.3156 0.3260  2.914e+15    1.0000 0.9351 0.9619  255 248 251  #fff8fb
	 0xfff9fb,//6500 K   2deg  0.3155 0.3270  2.845e+15    1.0000 0.9436 0.9621  255 249 251  #fff9fb
	 0xfff9fd,//6500 K  10deg  0.3140 0.3245  3.108e+15    1.0000 0.9445 0.9853  255 249 253  #fff9fd
};

void ya_stripLightsDisplay_CWtoRGB(unsigned char*r, unsigned char*g, unsigned char*b, unsigned char temp, unsigned char bright)
{
	int index,len;
	#if (FLOAT_SUPPORT == 1)
	float C_Adj, W_Adj;
	#else
	uint32_t C_Adj, W_Adj;
	#endif
	
	uint32_t RGB_value;
		
	len = sizeof(ya_colorTemperatureToRGB_table)/4;
	#if (FLOAT_SUPPORT == 1)
	C_Adj = temp/100.0f;
	#else
	C_Adj = temp/100;
	#endif
	
	index = C_Adj*len;
	if(index >= len)
		index = len-1;
	else if(index <= 0)
		index =0;
	
	RGB_value =ya_colorTemperatureToRGB_table[index];
	
	*r = ((RGB_value>>16)&0xFF);
	*g = ((RGB_value>>8)&0xFF);
	*b = (C_Adj*0xEF)+10;
	
	ya_printf(C_LOG_INFO," \r\n ya_stripLightsDisplay_CWtoRGB = %X  %d \r\n",RGB_value,index);

	#if (FLOAT_SUPPORT == 1)
	W_Adj =  bright/100.0f;
	*r *= W_Adj;
	*g *= W_Adj;
	*b *= W_Adj;
	#else
	*r = (bright * (*r)) /100;
	*g = (bright * (*g)) /100;
	*b = (bright * (*b)) /100;
	#endif

}

 void ya_stripLightsDisplay_getRGB(ya_display_stripsLight_t *pcolorInfo)
{
	unsigned char r,g,b;
	unsigned char c,w;
	int i;
	int len = pcolorInfo->groupNum;
	
	for(i=0;i<len;i++)
	{
		if(pcolorInfo->colorInfo[i].type == COLORTYPE_COLOR)
		{
			if (pcolorInfo->colorInfo[i].color_H >= 360)
				pcolorInfo->colorInfo[i].color_H = 0;
			
			HSVtoRGB(&r,&g,&b,pcolorInfo->colorInfo[i].color_H,pcolorInfo->colorInfo[i].color_S,pcolorInfo->colorInfo[i].color_B);

			pcolorInfo->colorInfo[i].color_H = r;
			pcolorInfo->colorInfo[i].color_S = g;
			pcolorInfo->colorInfo[i].color_B = b;
			pcolorInfo->colorInfo[i].white_bright=0;
			pcolorInfo->colorInfo[i].white_temp= 0;
		}
		else
		{
		#if (CW_PWM == 2)
			ya_stripLightsDisplay_CWtoRGB(&r,&g,&b,pcolorInfo->colorInfo[i].white_temp,pcolorInfo->colorInfo[i].white_bright);

			pcolorInfo->colorInfo[i].color_H = r;
			pcolorInfo->colorInfo[i].color_S = g;
			pcolorInfo->colorInfo[i].color_B = b;
			pcolorInfo->colorInfo[i].white_temp= 0;
			pcolorInfo->colorInfo[i].white_bright= 0;

		#else

			#if (CW_PWM == 1)

				c = pcolorInfo->colorInfo[i].white_temp;  //cool temp
				w = 100- pcolorInfo->colorInfo[i].white_temp; //warm temp
				
				c = c*(pcolorInfo->colorInfo[i].white_bright)*255/10000;  // get cool pwm
				w = w*(pcolorInfo->colorInfo[i].white_bright)*255/10000;  // get warm pwm

			#else
				c = (pcolorInfo->colorInfo[i].white_temp)*255/100;  //get temp pwm
				w = (pcolorInfo->colorInfo[i].white_bright)*255/100; //get bright pwm
			#endif
			
			pcolorInfo->colorInfo[i].color_H = 0;
			pcolorInfo->colorInfo[i].color_S = 0;
			pcolorInfo->colorInfo[i].color_B = 0;			
			pcolorInfo->colorInfo[i].white_temp = c;
			pcolorInfo->colorInfo[i].white_bright = w;	

		#endif
		}
	}	
}

void  ya_stripLightsDisplay_writePwm(unsigned int r,unsigned int g,unsigned int b,unsigned int c,unsigned int w)
{
#if (FLOAT_SUPPORT == 1)
	ya_hal_pwm_write(PWM_R,(float)(r/255.0));
	ya_hal_pwm_write(PWM_G,(float)(g/255.0));
	ya_hal_pwm_write(PWM_B,(float)(b/255.0));
	ya_hal_pwm_write(PWM_COOL,(float)(c/255.0));
	ya_hal_pwm_write(PWM_WARM,(float)(w/255.0));
#else
	ya_hal_pwm_write(PWM_R,(float)(r/255));
	ya_hal_pwm_write(PWM_G,(float)(g/255));
	ya_hal_pwm_write(PWM_B,(float)(b/255));
	ya_hal_pwm_write(PWM_COOL,(float)(c/255));
	ya_hal_pwm_write(PWM_WARM,(float)(w/255));

#endif
}


void ya_stripLightsDisplay_getChangeStep(void)
{
	ya_st_stripLightsDisplay_CtrlInfo *pCtrlInfoGroup =&ya_stripLightsDisplay_CtrlGroupInfo;
	ya_st_pwmCtrlInfo *pCrlInfo;
	ya_st_pwmChannelInfo *pChannelInfo;
	int i;
	int temp;
	pCrlInfo = &pCtrlInfoGroup->pwmGroupInfo[pCtrlInfoGroup->pwmGroupIndex];

	for(i=0;i<5;i++)
	{
		pChannelInfo = &pCrlInfo->pwmChannelInfo[i];
		temp = pChannelInfo->pwmDutyNew - pCtrlInfoGroup->pwmDutyCur[i];
		pChannelInfo->pwmDutyStep = temp/(pCtrlInfoGroup->timerIntervalChangeUp);
		if(pChannelInfo->pwmDutyStep == 0)
		{
			if(temp>0)
				pChannelInfo->pwmDutyStep = 1;
			else if(temp<0)
				pChannelInfo->pwmDutyStep = -1;
			else
				pChannelInfo->pwmDutyStep = 0;
		}
	}

	#if (CW_PWM == 0)
	// off
	if (pCrlInfo->pwmChannelInfo[PWM_WARM].pwmDutyNew == 0)
	{
		pCrlInfo->pwmChannelInfo[PWM_COOL].pwmDutyStep = 0;
		pCtrlInfoGroup->pwmDutyCur[PWM_COOL] = pCrlInfo->pwmChannelInfo[PWM_COOL].pwmDutyNew;
	}
	#endif
}

void ya_stripLightsDisplay_getcloseStep(void)
{
	ya_st_stripLightsDisplay_CtrlInfo *pCtrlInfoGroup =&ya_stripLightsDisplay_CtrlGroupInfo;
	ya_st_pwmCtrlInfo *pCrlInfo;
	ya_st_pwmChannelInfo *pChannelInfo;
	int i;
	int temp;
	pCrlInfo = &pCtrlInfoGroup->pwmGroupInfo[pCtrlInfoGroup->pwmGroupIndex];

	for(i=0;i<5;i++)
	{
		pChannelInfo = &pCrlInfo->pwmChannelInfo[i];
		temp = 0 - pCtrlInfoGroup->pwmDutyCur[i];
		pChannelInfo->pwmDutyStep = temp/(pCtrlInfoGroup->timerIntervalChangeUp);

		if(pChannelInfo->pwmDutyStep == 0)
		{
			if (temp>0)
				pChannelInfo->pwmDutyStep = 1;
			else if (temp<0)
				pChannelInfo->pwmDutyStep = -1;
			else
				pChannelInfo->pwmDutyStep = 0;
		}
	}

#if (CW_PWM == 0)
	// off
	if (pCrlInfo->pwmChannelInfo[PWM_WARM].pwmDutyNew == 0)
	{
		pCrlInfo->pwmChannelInfo[PWM_COOL].pwmDutyStep = 0;
		pCtrlInfoGroup->pwmDutyCur[PWM_COOL] = pCrlInfo->pwmChannelInfo[PWM_COOL].pwmDutyNew;
	}
#endif

}


void ya_stripLightsDisplay_start(ya_display_stripsLight_t *pcolorInfo)
{
	ya_st_stripLightsDisplay_CtrlInfo *pCtrlInfoGroup =&ya_stripLightsDisplay_CtrlGroupInfo;
	ya_st_pwmCtrlInfo *pCrlInfo;
	ya_st_pwmChannelInfo *pChannelInfo;
	int i;

	if (pcolorInfo->groupNum == 0)
	{
		ya_stripLightsDisplay_CtrlGroupInfo.displayState = PWM_DISPLAY_STOP;
		return;
	}
	
	pCtrlInfoGroup->changeType = pcolorInfo->changeType;
	pCtrlInfoGroup->pwmGroupLen = pcolorInfo->groupNum;
	// changeSpeed = 10~100
	pcolorInfo->changeSpeed = (110 -pcolorInfo->changeSpeed);
	
	if (pcolorInfo->changeType == IMMEDIATELY_TYPE)
	{
		pCtrlInfoGroup->timerIntervalWaiting = 1;
		pCtrlInfoGroup->timerIntervalChangeUp = 1;
		pCtrlInfoGroup->timerIntervalHold = 1;
		pCtrlInfoGroup->timerIntervalChangeDown = 1;
		pCtrlInfoGroup->changeSpeed = 0;
	}
	else if (pcolorInfo->changeType == STATIC_TYPE)
	{
		pCtrlInfoGroup->timerIntervalWaiting = 1;
		pCtrlInfoGroup->timerIntervalHold = 1;
		pCtrlInfoGroup->timerIntervalChangeDown = 1;

		pCtrlInfoGroup->changeSpeed = 100;
		pCtrlInfoGroup->timerIntervalChangeUp =  pCtrlInfoGroup->changeSpeed ;
		pCtrlInfoGroup->changeSpeed = YA_STRIPLIGHTSDISPLAY_COLORCHANGE_MAXTIME/100;

		if(pcolorInfo->colorInfo[0].type == COLORTYPE_COLOR)		
		{			
			//limit bright
			if (pcolorInfo->colorInfo[0].color_B < MIN_BRIGHT_PERCENT && pcolorInfo->cmd != 0xFF)
				pcolorInfo->colorInfo[0].color_B = MIN_BRIGHT_PERCENT;
		}
		else		
		{			
			//limit bright
			if(pcolorInfo->colorInfo[0].white_bright < MIN_BRIGHT_PERCENT && pcolorInfo->cmd != 0xFF)
				pcolorInfo->colorInfo[0].white_bright = MIN_BRIGHT_PERCENT;
		}

	}
	else if(pcolorInfo->changeType == STEP_TYPE)
	{	
		pCtrlInfoGroup->timerIntervalWaiting = 1;
		pCtrlInfoGroup->timerIntervalChangeUp = 1;
		pCtrlInfoGroup->timerIntervalHold = 1;
		pCtrlInfoGroup->timerIntervalChangeDown = 1;
		pCtrlInfoGroup->changeSpeed = (pcolorInfo->changeSpeed*YA_STRIPLIGHTSDISPLAY_PWMCHANGE_MAXTIME)/100;
	}
	else if(pcolorInfo->changeType == SHADE_TYPE)
	{	
		pCtrlInfoGroup->timerIntervalWaiting = 1;
		pCtrlInfoGroup->timerIntervalChangeUp = pcolorInfo->changeSpeed;
		pCtrlInfoGroup->timerIntervalHold = 1;
		pCtrlInfoGroup->timerIntervalChangeDown = 1;
		pCtrlInfoGroup->changeSpeed = YA_STRIPLIGHTSDISPLAY_PWMCHANGE_MAXTIME/100;
	}
	else if(pcolorInfo->changeType == BREAK_TYPE)
	{	
		pCtrlInfoGroup->timerIntervalWaiting = 1;
		pCtrlInfoGroup->timerIntervalChangeUp = pcolorInfo->changeSpeed;
		pCtrlInfoGroup->timerIntervalHold = 10;
		pCtrlInfoGroup->timerIntervalChangeDown = pcolorInfo->changeSpeed;
		pCtrlInfoGroup->changeSpeed =  YA_STRIPLIGHTSDISPLAY_PWMCHANGE_MAXTIME/100;
	}
	
	ya_stripLightsDisplay_getRGB(pcolorInfo);

	for(i=0;i<pCtrlInfoGroup->pwmGroupLen;i++)
	{
		pCrlInfo = &pCtrlInfoGroup->pwmGroupInfo[i];
	
		pChannelInfo = &pCrlInfo->pwmChannelInfo[PWM_R];
		pChannelInfo->pwmDutyNew= pcolorInfo->colorInfo[i].color_H*100;

		pChannelInfo = &pCrlInfo->pwmChannelInfo[PWM_G];
		pChannelInfo->pwmDutyNew= pcolorInfo->colorInfo[i].color_S*100;

		pChannelInfo = &pCrlInfo->pwmChannelInfo[PWM_B];
		pChannelInfo->pwmDutyNew= pcolorInfo->colorInfo[i].color_B*100;
		
		pChannelInfo = &pCrlInfo->pwmChannelInfo[PWM_COOL];
		pChannelInfo->pwmDutyNew= pcolorInfo->colorInfo[i].white_temp*100;
		
		pChannelInfo = &pCrlInfo->pwmChannelInfo[PWM_WARM];
		pChannelInfo->pwmDutyNew= pcolorInfo->colorInfo[i].white_bright*100;
	}
	
	pCtrlInfoGroup->displayState = PWM_DISPLAY_START;
}

int ya_stripLightsDisplay_loop(void)
{
	ya_st_stripLightsDisplay_CtrlInfo *pCtrlInfoGroup =&ya_stripLightsDisplay_CtrlGroupInfo;
	ya_st_pwmCtrlInfo *pCrlInfo;
	ya_st_pwmChannelInfo *pChannelInfo;
	int i,temp,flag_updatePwm = 0;
		
	if(pCtrlInfoGroup->displayState == PWM_DISPLAY_IDLE)
		return 0;

	if (pCtrlInfoGroup->changeSpeed)
		ya_delay(pCtrlInfoGroup->changeSpeed);

	if(pCtrlInfoGroup->displayState == PWM_DISPLAY_STOP)
	{
		pCtrlInfoGroup->displayState = PWM_DISPLAY_IDLE;
		memset(pCtrlInfoGroup->pwmDutyCur,0,sizeof(int32_t)*5);
		flag_updatePwm = 1;
	}
	else if(pCtrlInfoGroup->displayState == PWM_DISPLAY_START)
	{
		pCtrlInfoGroup->displayState = PWM_DISPLAY_WATING;
		pCtrlInfoGroup->pwmGroupIndex= 0;		
		pCtrlInfoGroup->timerCounter = 0;
	}

	//wating
	if(pCtrlInfoGroup->displayState == PWM_DISPLAY_WATING)
	{			
		if(++pCtrlInfoGroup->timerCounter >= pCtrlInfoGroup->timerIntervalWaiting)
		{
			pCtrlInfoGroup->displayState = PWM_DISPLAY_UP;
			pCtrlInfoGroup->timerCounter = 0;
			if(pCtrlInfoGroup->pwmGroupIndex >= pCtrlInfoGroup->pwmGroupLen)
			{
				pCtrlInfoGroup->pwmGroupIndex = 0;
			}
			ya_stripLightsDisplay_getChangeStep();
		}
	}
	//change up
	if(pCtrlInfoGroup->displayState == PWM_DISPLAY_UP)
	{
		if(++pCtrlInfoGroup->timerCounter <= pCtrlInfoGroup->timerIntervalChangeUp)
		{
			//up
			pCrlInfo = &pCtrlInfoGroup->pwmGroupInfo[pCtrlInfoGroup->pwmGroupIndex];
			for(i=0;i<5;i++)
			{
				pChannelInfo = &pCrlInfo->pwmChannelInfo[i];
				temp = pCtrlInfoGroup->pwmDutyCur[i] + pChannelInfo->pwmDutyStep;
				if(pChannelInfo->pwmDutyStep > 0)
				{
					if(temp > pChannelInfo->pwmDutyNew)
						temp = pChannelInfo->pwmDutyNew;
				}
				else if(pChannelInfo->pwmDutyStep < 0)
				{
					if(temp <= pChannelInfo->pwmDutyNew)
						temp = pChannelInfo->pwmDutyNew;
				}
				if(temp <0)
					temp = pChannelInfo->pwmDutyNew;

				pCtrlInfoGroup->pwmDutyCur[i] = temp;

				if((pCtrlInfoGroup->timerCounter == pCtrlInfoGroup->timerIntervalChangeUp))
					pCtrlInfoGroup->pwmDutyCur[i] = pChannelInfo->pwmDutyNew;
			}
			
			if((pCtrlInfoGroup->timerCounter == pCtrlInfoGroup->timerIntervalChangeUp))
			{
				pCtrlInfoGroup->timerCounter = 0;
				if(pCtrlInfoGroup->changeType == STATIC_TYPE||pCtrlInfoGroup->changeType == IMMEDIATELY_TYPE)
				{
					pCtrlInfoGroup->displayState= PWM_DISPLAY_IDLE;
					pCtrlInfoGroup->pwmGroupIndex = 0;
				}else if(pCtrlInfoGroup->changeType == STEP_TYPE||pCtrlInfoGroup->changeType == SHADE_TYPE)
				{	
					pCtrlInfoGroup->displayState = PWM_DISPLAY_WATING;
					pCtrlInfoGroup->pwmGroupIndex++;
				}else if(pCtrlInfoGroup->changeType == BREAK_TYPE)
				{	
					pCtrlInfoGroup->displayState = PWM_DISPLAY_HOLD;
				}
			}
			flag_updatePwm = 1;
		}			
	}
	else if(pCtrlInfoGroup->displayState == PWM_DISPLAY_HOLD)
	{
		if(++pCtrlInfoGroup->timerCounter >= pCtrlInfoGroup->timerIntervalHold)
		{
			pCtrlInfoGroup->timerCounter = 0;
			pCtrlInfoGroup->displayState = PWM_DISPLAY_DOWN;
			ya_stripLightsDisplay_getcloseStep();

			//pCtrlInfoGroup->pwmGroupIndex++;
			//memset(&pCtrlInfoGroup->pwmDutyCur,0,sizeof(int32_t)*5);
			//pCtrlInfoGroup->displayState = PWM_DISPLAY_WATING;
		}
	}
	//change down
	if(pCtrlInfoGroup->displayState == PWM_DISPLAY_DOWN)
	{
		if(++pCtrlInfoGroup->timerCounter <= pCtrlInfoGroup->timerIntervalChangeDown)
		{
			//down
			pCrlInfo = &pCtrlInfoGroup->pwmGroupInfo[pCtrlInfoGroup->pwmGroupIndex];
			for(i=0;i<5;i++)
			{
				if (pCtrlInfoGroup->pwmDutyCur[i] != 0)
				{
					pChannelInfo = &pCrlInfo->pwmChannelInfo[i];
					temp = pCtrlInfoGroup->pwmDutyCur[i] + pChannelInfo->pwmDutyStep;
					
					if(temp < 0 || pChannelInfo->pwmDutyStep > 0)
						temp = 0;

					pCtrlInfoGroup->pwmDutyCur[i] = temp;

					if((pCtrlInfoGroup->timerCounter == pCtrlInfoGroup->timerIntervalChangeUp))
						pCtrlInfoGroup->pwmDutyCur[i] = 0;
				}
			}
			
			if((pCtrlInfoGroup->timerCounter == pCtrlInfoGroup->timerIntervalChangeDown))
			{
				pCtrlInfoGroup->timerCounter = 0;
				pCtrlInfoGroup->displayState = PWM_DISPLAY_WATING;
				pCtrlInfoGroup->pwmGroupIndex++;
			}
			flag_updatePwm = 1;
		}

	}
	//set pwm
	if(flag_updatePwm)
	{
		ya_stripLightsDisplay_writePwm(pCtrlInfoGroup->pwmDutyCur[PWM_R],pCtrlInfoGroup->pwmDutyCur[PWM_G], pCtrlInfoGroup->pwmDutyCur[PWM_B], pCtrlInfoGroup->pwmDutyCur[PWM_COOL], pCtrlInfoGroup->pwmDutyCur[PWM_WARM]);
		#if 0
		ya_printf(C_LOG_INFO," \r\n pwm %d %d,%d = %d %d  %d %d %d\r\n",
		pCtrlInfoGroup->pwmGroupIndex,
		pCtrlInfoGroup->displayState,
		flag_updatePwm,  
		pCtrlInfoGroup->pwmDutyCur[0],  
		pCtrlInfoGroup->pwmDutyCur[1], 
		pCtrlInfoGroup->pwmDutyCur[2], 
		pCtrlInfoGroup->pwmDutyCur[3], 
		pCtrlInfoGroup->pwmDutyCur[4]);
		#endif
	}

	if (pCtrlInfoGroup->changeSpeed == 0)
		return 0;

	return 1;
}

ya_hal_os_queue_t ya_striplights_display_queue = NULL;

void ya_stripLights_pwmUpdate_into_queue(uint8_t *buf, uint16_t len)
{
	int32_t ret = -1;
	msg_t msg;
	memset(&msg, 0, sizeof(msg_t));
	
	msg.addr = (uint8_t *)ya_hal_os_memory_alloc(len);
	memcpy(msg.addr, buf, len);
	msg.len = len;

	ret = ya_hal_os_queue_send(&ya_striplights_display_queue, &msg, 0);
	if (ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "ya_striplights_display_queue error\r\n");
		if (msg.addr)
			ya_hal_os_memory_free(msg.addr);
	}
}


void ya_stripLightsDisplay_task(void *arg)
{
	uint8_t control_flag = 0;
	int32_t ret = -1;
	msg_t msg_light;
	ya_display_stripsLight_t ya_stripsLihgt_display;
	
	while(1)
	{
		control_flag = 0;

		memset(&ya_stripsLihgt_display, 0, sizeof(ya_display_stripsLight_t));
		do{
			memset(&msg_light, 0, sizeof(msg_t));
			ret = ya_hal_os_queue_recv(&ya_striplights_display_queue, &msg_light, 0);
			if (ret == C_OK)
			{			
				memcpy(&ya_stripsLihgt_display, msg_light.addr, sizeof(ya_display_stripsLight_t));
				control_flag = 1;
			}

			if (msg_light.addr)
				ya_hal_os_memory_free(msg_light.addr);
			
		}while(ret == C_OK);	

		if (control_flag)
		{
			//do logic here
			ya_stripLightsDisplay_start(&ya_stripsLihgt_display);
		}	

		if (ya_stripLightsDisplay_loop() == 0)
		{//idle
			ya_delay(10);
		}
	}
}

int32_t ya_stripLights_display_start(void)
{
	int ret = -1;
	
	ret = ya_hal_os_queue_create(&ya_striplights_display_queue, "ya_striplight_queue queue", sizeof(msg_t), 16);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create os queue error\n");
		return -1;
	}

	ret = ya_hal_os_thread_create(NULL, "ya_stripLightsDisplay_task", ya_stripLightsDisplay_task, 0, (2*1024), 5);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create ya_stripLightsDisplay_task error\n");
		return -1;
	}

	return 0;
}

