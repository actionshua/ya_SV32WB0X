
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
#include "ya_stripLights_example.h"
#if (STRIP_LIGHT == 1)

#include "ya_common.h"
#include "cJSON.h"
#include "ya_app_main.h"
#include "ya_thing_data_api.h"
#include "ya_mode_api.h"
#include "ya_api_thing_uer_define.h"
#include "ya_hal_gpio.h"
#include "ya_hal_button.h"
#include "ya_example.h"
//#include "analogin_api.h"
#include "ya_hal_pwm.h"
#include "ya_light_io.h"
#include "mqtt_wrapper.h"

extern int LOGUART_SetBaud(uint32_t BaudRate);
#define Sleep ya_delay
#define REF_Up    710//750
#define REF_Down  300//300

uint32_t g_VALUE_GAIN   = 3;
int   g_VALUE_OFFSET = 0x0500;
int g_beatCnt = 0;
int g_bEnabeLog = 0;
int g_adc_delay = 5;
int g_ref_value = REF_Up;
int g_ref_value2 = REF_Down;
uint8_t  g_switchStatus = 0;
uint8_t  g_mic_mode = 0;
uint8_t  g_mic_sensitivity = 50;
uint8_t  g_mic_rate = 60;



ya_hal_os_queue_t ya_music_msg_queue = NULL;


int g_colorGroupRGB[7][3]= //RGB
{
	{0xff,0x00,0x00},//红
	{0xff,0xff,0x00},//黄
	{0x00,0xff,0x00},//绿
	{0x00,0xff,0xff},//青
	{0x00,0x00,0xff},//蓝
	{0xff,0x00,0xff},//紫
	{0xff,0xff,0xff},//白
};

int g_colorGroupRGB2[4][3]= //RGB
{
	{0xff,0x00,0x00},//红
	{0x00,0xff,0x00},//绿
	{0x00,0x00,0xff},//蓝
	{0xff,0xff,0xff},//白
};


int g_colorGroupHSV[7][3]= //HSV
{
	{0x00,0x64,0x64}, 
	{0x11,0x64,0x64},
	{0x21,0x64,0x64},
	{0x32,0x64,0x64},
	{0x43,0x64,0x64},
	{0x53,0x64,0x64},
	{0x00,0x64,0x64},
};

int g_color_R = 0;
int g_color_G = 0;
int g_color_B = 0;
int g_brightMax = 100;

int  g_color_H = 0;
int  g_color_S = 0;
uint32_t  g_color_V = 0;//亮度

void *g_mutexCnt = NULL;


//// R,G,B from 0-255, H from 0-360, S,V from 0-100
void HSVtoRGB(unsigned char*r, unsigned char*g, unsigned char*b, unsigned short int h, unsigned short int s, unsigned short int v);
void RGB2HSV( unsigned short int * h, unsigned short int * s, unsigned short int * v, unsigned char r,  unsigned char g,  unsigned char b);

//ya_hal_pwm_write(PWM_R,(float)(r/255.0));


typedef struct{
	uint8_t switchStatus;
	uint8_t work_mode;
	uint8_t music; //music_type,0~~4
	uint8_t mic_sensitivity;//1--100
	uint8_t mic_rate; //1--100
} ya_music_led_data_t;



void set_music_param(uint8_t switchStatus,uint8_t work_mode, uint8_t music,uint8_t mic_sensitivity,uint8_t mic_rate){

	msg_t ms_msg;
	ya_music_led_data_t musicled_data;
	uint8_t data_len = sizeof( ya_music_led_data_t );

	ya_music_led_data_t *buf = (ya_music_led_data_t *)HAL_Malloc(data_len + 1);

	memset( buf, 0, (data_len + 1));
	buf->switchStatus = switchStatus ;
    buf->music = music;
    buf->mic_sensitivity = mic_sensitivity;
	buf->mic_rate =mic_rate;
	memset(&ms_msg, 0, sizeof(msg_t));	
	ms_msg.addr = buf;
	ms_msg.len = (data_len + 1);
	ms_msg.type = 1;		 	 
	ya_hal_os_queue_send(&ya_music_msg_queue,&ms_msg,10);	
}
//diy temp cmd test
int my_log_handler(char* cmdStr){
	
  char cmdP1[20]={0};
  char cmdP2[20]={0};
  int j,len =strlen( cmdStr );
  int index = 0;
  int wParam = 0;
  ya_printf(C_LOG_INFO,"#command input: [%s] ",cmdStr );
  if(len>=sizeof(cmdP1) )
  {
	ya_printf(C_LOG_INFO,"#command is too long ,len=%d!",len);
	return 0;
  }
  for(j=0;j<len;j++){
	if( cmdStr[j] == ' ')
	 break;
    cmdP1[index++]=cmdStr[j];
  }
  if( j != len ){
      //get space
      index = 0;
      for( int i=j+1;i<len;i++){
		cmdP2[index++]=cmdStr[i];
      }
      wParam = atoi( cmdP2 );
  }

  index = 1;//复用于指令有效判断
  
  if( 0 == strcmp(cmdP1,"openLog") ){
     g_bEnabeLog = 1;
  }
  else if( 0 == strcmp(cmdP1,"closeLog") ){
     g_bEnabeLog = 0;	 
  }
  else if( 0 == strcmp(cmdP1,"setRef") ){
     g_ref_value = wParam;	
  }
   else if( 0 == strcmp(cmdP1,"setRef") ){
     g_ref_value = wParam;	
  } 
  else if( 0 == strcmp(cmdP1,"setBeat") ){
     
	 AddBeatTimes(wParam,100);	
  }
  else if( 0 == strcmp(cmdP1,"setMaxBright") ){
     g_brightMax = wParam;	
  }   
  else if( 0 == strcmp(cmdP1,"setMicMode") ){
     set_music_param(1,0,wParam,g_mic_sensitivity,g_mic_rate);
  } 
  else if( 0 == strcmp(cmdP1,"setMicSens") ){
	  set_music_param(1,0,g_mic_mode,wParam,g_mic_rate);		 
  } 
  else if( 0 == strcmp(cmdP1,"setMicRate") ){
	  set_music_param(1,0,g_mic_mode,g_mic_sensitivity,wParam);		 
  }     
  else{
	  index = 0; 
  }

  if( index >0 ){
	  ya_printf(C_LOG_INFO,"#cmd config ok! ");
	  return 1;
  }

  return 0;
}

#if 0
void printf(char* fmt, ...){

    if( g_bEnabeLog)//enable-adc-part
      return;
	const int BUFFER_SIZE =  200;
	char* buf= (char*) malloc(BUFFER_SIZE);
	memset(buf,BUFFER_SIZE,0);

	va_list args;
	va_start(args,fmt);
	vsprintf(buf,fmt, args);
	va_end(args);

	uint32_t curTick = HAL_UptimeMs();
    ya_printf(C_LOG_INFO,"[%ld]%s\n",curTick,buf);
	
	free(buf);	

}
#endif

void AddBeatTimes(int tm,int maxBright){	
	HAL_MutexLock( g_mutexCnt );
	  if( maxBright>0 ){
	    g_brightMax = maxBright;
	  }
	  g_beatCnt+=tm;
	  if(g_beatCnt> 3)
	    g_beatCnt = 3;
	  else if( g_beatCnt<0)
	   g_beatCnt = 0;
	HAL_MutexUnlock( g_mutexCnt );
}

//0.劲爆模式
//亮度：A::0～～100%————CLOSE————————B::0～～100%
void Music_Shine_Mode0(int mode){

    static uint8_t swType = 0;
	static uint8_t swFinish = 0;
	static uint8_t bSetFree = 0;
    static uint8_t lastMode = -1;
	static uint8_t delayTm = 20;
    uint8_t bInit = 0;
    if( lastMode!=mode){
	   bInit = 1;//有模式切换，可以根据需要做初始化
    }
   lastMode = mode;	

	if( mode != 0 )
	  return;//=====================================

	if ( g_color_V >= g_brightMax )
	{
		printf("#[M0]brightMax=%d,beatLeft=%d",g_brightMax,g_beatCnt);
		swFinish = 1;//最亮时
		for(int i =0 ;i<10;i++){
		  ya_delay(10);
		  if( g_beatCnt>0 )
		    break;
	    }		
        g_color_V = 0;//reset_v
	}else{
		if(g_beatCnt>0){
		  g_color_V+=1.5; //有节奏时快速，200ms完成一次闪烁
		  bSetFree = 1;
		  ya_delay(2);
		}else{
           g_color_V+=0.1;//空闲状态
		   if( bSetFree == 1 ){
			   bSetFree = 0;
		       AddBeatTimes(0,10);
			   delayTm = 20;
		   }
		   ya_delay(delayTm);
		  
		}
	}

	
    if ( g_beatCnt>0 )
	{
		if( swFinish ==1 ){
		 swFinish = 0; //节拍减少一次
		 swType = (swType+1)%7;
		 int saveV = g_color_V;
		 RGB2HSV(&g_color_H,&g_color_S,&g_color_V,g_colorGroupRGB[swType][0],g_colorGroupRGB[swType][1],g_colorGroupRGB[swType][2]);
		 g_color_V = 0;//重置亮度
		 //printf("#Get_beat_times=%d,BMax=%d,V1=%d,V2=%d",g_beatCnt,g_brightMax,(int)g_color_V,saveV);
		 AddBeatTimes(-1,-1);
		}else{
          delayTm = 2;//快速完成本次样式
		}
	}
		
}


//1摇滚
void Music_Shine_Mode1(int mode){
   
    static uint8_t swType = 0;
	static uint8_t swFinish = 0;
	static uint8_t bSetFree = 0;
    static uint8_t lastMode = -1;
	static uint8_t delayTm = 30;
	static uint8_t delayCnt = 0;
    uint8_t bInit = 0;
    if( lastMode!=mode){
	   bInit = 1;//有模式切换，可以根据需要做初始化
    }
   lastMode = mode;	

	if( mode != 1 )
	  return;//=====================================


	if( g_beatCnt > 0)
	{	   
       delayTm = 10;	
	   if( swFinish == 0)
	     delayTm = 1;//超快速结束本次
	}else{
	   delayTm = 30;  //空闲
	}

	if( delayCnt++>100){
		delayCnt = 0;
		swFinish = 1;
	}

	if( swFinish == 1 ){
        swFinish = 0; 
		swType = (swType+1)%7;  
		printf("(M1)#sw_type=%d,g_beatCnt=%d",swType,g_beatCnt);
		RGB2HSV(&g_color_H,&g_color_S,&g_color_V,g_colorGroupRGB[swType][0],g_colorGroupRGB[swType][1],g_colorGroupRGB[swType][2]); 
		ya_delay(10);
		if( g_beatCnt > 0)
		{
            g_color_V = 100; //柔和亮度100->0->100	
			delayCnt = 0;	
			AddBeatTimes(-1,-1);

		}else{
		}
	}

	ya_delay( delayTm );


}
	

//2.经典
void Music_Shine_Mode2(int mode){

   static uint8_t swType = 0;
   static uint8_t swFinish = 0;
   static uint8_t bSetFree = 0;
   static uint8_t lastMode = -1;
   static uint8_t cntTime = 0;
   uint8_t bInit = 0;
   if( lastMode!=mode){
	   bInit = 1;//有模式切换，可以根据需要做初始化
   }
   lastMode = mode;

  	if( mode != 2 )
	  return; //==============================

	if ( g_beatCnt>0 )
	{
	   swFinish = 0;	
	   AddBeatTimes(-1,-1);
	   swType = (swType+1)%7;   
	   RGB2HSV(&g_color_H,&g_color_S,&g_color_V,g_colorGroupRGB[swType][0],g_colorGroupRGB[swType][1],g_colorGroupRGB[swType][2]);
	   g_color_V = 99; //经典亮度不变
	   cntTime = 0;
	   for( int i=0;i<10;i++){
           if( g_beatCnt>0 )
		     break;
		   ya_delay(10);
	   }
	}

	ya_delay(10);
	if(cntTime++>200){
		cntTime = 0;
		swFinish = 1;
		printf("(M2)#sw_type=%d,g_beatCnt=%d",swType,g_beatCnt);
		AddBeatTimes(1,-2);//模拟产生一个切换信号
	}
	
}


//3.柔和 亮度 0--100--0
void Music_Shine_Mode3(int mode){

   static uint8_t swType = 0;
   static uint8_t swFinish = 0;
   static uint8_t bSetFree = 0;
   static uint8_t lastMode = -1;
   static uint8_t cntTime = 0;
   static uint8_t ledOp = 1;//1:增，0减
   static uint8_t localBrightMax = 100; //g_brightMax
   static uint8_t delayTm = 15;
   static uint8_t adder = 2;

   uint8_t bInit = 0;
   if( lastMode!=mode){
	   bInit = 1;//有模式切换，可以根据需要做初始化
   }
   lastMode = mode;

  	if( mode != 3 )
	  return; //==============================

   localBrightMax = g_brightMax;

    if( ledOp ==0 ){
		g_color_V-=1;
		if( g_color_V < 0 ){
			g_color_V = 0;
            ledOp = 1;
			swFinish = 1;
		}
	}else{
		g_color_V+=2;
		if( g_color_V > localBrightMax ){
			g_color_V = localBrightMax;
            ledOp = 0;			
		}

	}

	if( g_beatCnt > 0)
	{      
	   if( swFinish == 0)
	     delayTm = 0;//超快速结束本次
	   else
	     delayTm = 2;	

	}else{
       localBrightMax = 100;
	   delayTm = 20;  //空闲	
	}

	if( swFinish == 1 ){
        swFinish = 0; 
		swType = (swType+1)%4;  
		printf("(M3)#sw_type=%d,g_beatCnt=%d ,localBrightMax=%d,sleep=%d",swType,g_beatCnt,localBrightMax,delayTm);
		RGB2HSV(&g_color_H,&g_color_S,&g_color_V,g_colorGroupRGB2[swType][0],g_colorGroupRGB2[swType][1],g_colorGroupRGB2[swType][2]); 
		ya_delay(10);
		if( g_beatCnt > 0)
		{
            g_color_V = 0; //柔和亮度0->100->0
			ledOp = 1;			
			AddBeatTimes(-1,-1);
			adder = 10;

		}else{
			adder = 2;
		}
	}

	ya_delay( delayTm );


}


void ya_led_show_task(void *arg){

   //uint8_t ledShineMode = 1;//LED闪动模式
   uint8_t r,g,b;
   uint8_t lastStatus = 0;
   uint8_t delayTm = 20;
   int32_t ret = 0;
   msg_t ms_msg;
   ya_music_led_data_t *musicData;
 
   ret = ya_hal_os_queue_create(&ya_music_msg_queue, "ya_music_msg_queue", sizeof(msg_t), MSG_QUEUE_LENGTH);
   memset(&ms_msg, 0, sizeof(msg_t));
   ya_delay(100);

   while(1){

	   if( g_beatCnt>0 )
	   		delayTm = 5;
		else
			delayTm = 20;
		
	    ret = ya_hal_os_queue_recv(&ya_music_msg_queue,&ms_msg,delayTm);
		if ( ret ==0 )
		{    //得到消息
			/* code */
			 musicData = (ya_music_led_data_t*) ms_msg.addr;
			if( musicData != NULL ){
			   g_switchStatus = musicData->switchStatus;
               g_mic_mode = musicData->music;
			   g_mic_sensitivity = musicData->mic_sensitivity;
			   g_mic_rate = musicData->mic_rate;
			   printf("adc_task_recv,mode=%d,sensitivity=%d,rate=%d",g_mic_mode,g_mic_sensitivity,g_mic_rate);
               g_ref_value = 650+(850-650)*(100-g_mic_sensitivity)/100;//(650上升最敏感)
			   g_ref_value2 = 100+(300-100)*(g_mic_sensitivity)/100;//(300下降最敏感)
			   HAL_Free(musicData);
			}
		}
		if (  g_switchStatus == 0 )
		{
			if( lastStatus != g_switchStatus ){
				lastStatus = g_switchStatus;
				g_color_H = 0;
				g_color_S = 0;
				g_color_V = 0;
	            ya_hal_pwm_write(PWM_R,0 );
		        ya_hal_pwm_write(PWM_G,0 );
		        ya_hal_pwm_write(PWM_B,0 );				
			}
			 ya_delay(10);

		     continue;
		}
		
		lastStatus = g_switchStatus;
	
	    Music_Shine_Mode0( g_mic_mode );
		Music_Shine_Mode1( g_mic_mode );
		Music_Shine_Mode2( g_mic_mode );
		Music_Shine_Mode3( g_mic_mode );
		HSVtoRGB(&r,&g,&b,g_color_H,g_color_S,g_color_V);
	    ya_hal_pwm_write(PWM_R,(float)(	r/255.0) );
		ya_hal_pwm_write(PWM_G,(float)( g/255.0) );
		ya_hal_pwm_write(PWM_B,(float)( b/255.0));
		
		//ya_printf(C_LOG_INFO,"#@%02X%02X%02X\n",r,g,b);

   }//<<while
}

#if (1 == STRIP_LIGHT_WITH_ADC)
void ya_adc_task(void *arg){

 int iTemp=0,cnt=0;
 int brightPercent = 0;
 analogin_t   adc;
 uint16_t adcDat=0,adcLast=0;
 uint16_t drawYValue=0,avgValue=0;
 uint16_t minValue = -1,maxValue=0;
 uint16_t subUnit = 0; 
 uint16_t subUnit2 = 0;
 uint32_t  allDataSum = 0;
 uint8_t bTrigger = 0;
 uint8_t bTrigger2 = 0;
 uint8_t bGotHit = 0;
 uint32_t curTick = 0;
 uint32_t lastTick = 0;
 uint16_t xxTm = 0;

  
  if( g_mutexCnt == NULL ){
		printf("Initial mutext error!");
   }

   //LOGUART_SetBaud(921600);//reset the logger baudrate
 
 ya_printf(C_LOG_INFO, "ADC example (CH2), OFFSET, %d, GAIN=%.1f\r\n",g_VALUE_OFFSET,g_VALUE_GAIN );
 //ya_hal_pwm_init(); //R_G_B_CW_WW ::5 load
 analogin_init(&adc, AD_2);//2
  g_ref_value = REF_Up;
  g_ref_value2 = REF_Down; 
 
  while(1){

	    if (  g_switchStatus == 0 )
		{
			ya_delay(10);
		    continue;
		}
  		  
		adcDat = (analogin_read_u16(&adc)>>4);//12Bit—ADC //原始值
		adcDat =  ((analogin_read_u16(&adc)>>4)+adcDat)/2;
		drawYValue = (adcDat-g_VALUE_OFFSET)*g_VALUE_GAIN; //计算转换后的数据(示波器显示的线Y：0～～1024)
		allDataSum+=drawYValue;
		cnt++;
        avgValue = allDataSum/cnt;
        if( drawYValue> maxValue){
			maxValue = drawYValue;
		}
		if( drawYValue<minValue){
			minValue = drawYValue;
		}

		curTick = HAL_UptimeMs();

		if( drawYValue < g_ref_value){
		   bTrigger = 1; //上升沿触发
		}else if ( bTrigger == 1 )
		{
			bTrigger = 0;
			if ( (curTick-lastTick)>=100)
			{		
				lastTick = curTick;	
				brightPercent = (drawYValue-g_ref_value)*100/(maxValue-g_ref_value);			       
				printf("Add_Beat_UP,cntIndex=%d,left=%d,percent=%d",++xxTm,g_beatCnt,brightPercent);
				AddBeatTimes(1,brightPercent);
			}			
		}

		if( drawYValue > g_ref_value2 ){
		   bTrigger2 = 1;  //下降沿触发
		}else if ( bTrigger2 == 1 )
		{
			bTrigger2 = 0;
			if ( (curTick-lastTick)>=100)
			{	lastTick = curTick;	
			      brightPercent = (g_ref_value2-drawYValue)*100/(g_ref_value2-minValue);						     
				  printf("Add_Beat_DN,cntIndex=%d,left=%d,percent=%d",++xxTm,g_beatCnt,brightPercent);
				  AddBeatTimes(1,brightPercent);
			}			
		}

		if(  g_beatCnt>5 ) {
			g_beatCnt = 5;//满载
		}

		if( g_bEnabeLog>0 ){
		 ya_printf(C_LOG_INFO,"#@%04x\n",drawYValue);
		 ya_printf(C_LOG_INFO,"#.%04x\n",adcDat);
		}
		 
		if (iTemp++>300)
		{
		    iTemp = 0;			
			subUnit = (maxValue - avgValue)/100*5; //1.5s最大值减少5%
			subUnit2 = (avgValue - minValue)/100*5; //1.5s最小值递增5%
			//printf(">Avg=%d,VMax=%d,Ref1=%d,Ref2=%d",avgValue,maxValue,g_ref_value,g_ref_value2);
			maxValue -= subUnit; 
			minValue +=	subUnit2; 		
		}
		        
        //ya_delay(g_adc_delay);//5
		ya_delay(5);
		        	       
  }
  analogin_deinit(&adc);  

}
#endif

void ya_stripLights_adc(void){

	int ret = -1;
	
	g_mutexCnt = HAL_MutexCreate();

#if (1 == STRIP_LIGHT_WITH_ADC)	
	ret = ya_hal_os_thread_create(NULL, "ya_adc_task", ya_adc_task, 0, (2*1024), 3);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create ya_adc_task error\n");
	}else{
		ya_printf(C_LOG_ERROR, "create ya_adc_task ok!\n");
	}
#endif	

	ret = ya_hal_os_thread_create(NULL, "ya_led_show_task", ya_led_show_task, 0, (2*1024), 3);
	if(ret != C_OK)
	{
		ya_printf(C_LOG_ERROR, "create ya_led_show_task error\n");
	}else{
		ya_printf(C_LOG_ERROR, "create ya_led_show_task ok!\n");
	}	

}
#endif
