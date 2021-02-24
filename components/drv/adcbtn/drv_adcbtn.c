#include <stdio.h>
#include <stdlib.h>
#include "osal.h"

#include "soc_defs.h"

#include "drv_adc.h"
#include <drv_tmr.h>

#include "drv_adcbtn.h"


#define VCC                             3300    //3.3V*1000

//#define ADC_SAMPLES_NUM                 10
//#define ADC_SAMPLE_INTERVAL_TIME_MS     20
//#define DIAL_VOL_INTERVAL_TIME_MS       150

//#define ADC_BTN_INVALID_ID              -1
//#define ADC_BTN_INVALID_ACT_ID          -2
//#define ADC_BTN_DETECT_TIME_MS          20



uint32_t btn_voltage_level[USER_BUTTON_MAX] = {490,980,1190,1330,1490,1810,2160,2310,2480}; // ex, 980=0.98V*1000
//                              Array number:  0   1   2    3    4    5    6    7    8

uint16_t g_adc_ch;    //Audio use adc channel = 7.
adc_button_callback g_cb;
adc_arr_t g_p_btn[USER_BUTTON_MAX];
static adc_btn_id_t g_btn_id;
static adc_btn_state_t g_btn_state;
static int break_task = 0;
static int break_ready = 0;

void adc_btn_task(void *pdata)
{
    uint32_t press_cnt = 0;
    break_ready = 0;
        
    while (break_task == 0){

        uint32_t voltage = adc_btn_get_voltage(g_adc_ch); //adc_btn_get_voltage(adc_ch)

        uint32_t btn_id = adc_btn_get_button_id (voltage);

        uint32_t cur_btn_st = adc_btn_get_state (btn_id,press_cnt);
        
        if (btn_id == 0){
            cur_btn_st = ADC_BTN_STATE_IDLE;
            if(g_cb){   //if g_cb=NULL(0), don't do cb. if g_cb=1, do cb.
                g_cb(NULL, g_adc_ch, btn_id, ADC_BTN_STATE_IDLE);
            }
            
            press_cnt = 0;
        }
        else 
            press_cnt++;
        
        if (cur_btn_st == ADC_BTN_STATE_PRESSED) {
            if(g_cb){
                g_cb(NULL, g_adc_ch, btn_id, ADC_BTN_STATE_PRESSED);
            }
            
        }
        else if (cur_btn_st == ADC_BTN_STATE_LONG_PRESSED){
            if(g_cb){
                g_cb(NULL, g_adc_ch, btn_id, ADC_BTN_STATE_LONG_PRESSED);
            }
            
        }
    OS_MsDelay(10);        
    }

    break_ready = 1;
    OS_TaskDelete(NULL);
    
    return ;
}


void adc_btn_init (adc_arr_t *p_btn, int num, uint16_t ch, adc_button_callback cb)
{
    g_adc_ch = ch;
    g_cb = cb;
    drv_adc_init(ch);               //init adc channel
        
    for (int i = 0; i < num; i++) {    //init every btn's voltage level
        p_btn[i].adc_level_step = btn_voltage_level[i];
        //printf ("adc_btn[%d].adc_level_step=%d\n", i, p_btn[i].adc_level_step);
    }
    
    if(break_ready == 0) {
        OS_TaskCreate(adc_btn_task, "adc_btn_task", 512, NULL, OS_TASK_LOW_PRIO, NULL);
     }
}

void adc_btn_deinit ()
{
    break_task = 1;
    while(break_ready == 1) {
        OS_MsDelay(10);        
    }
}


void adc_btn_set_cb (adc_button_callback cb)
{
    g_cb = cb;
}
    
uint32_t adc_btn_get_voltage (uint16_t ch)
{
    uint32_t adc_voltage = 0;
    uint16_t value;

    drv_adc_read(&value);                       //read adc value
    //printf("Drv_adc_value = %d\n",value);
    
    adc_voltage = (VCC * value) / 4095;         //adc value convert to adc voltage
    //printf("Drv_adc_voltage = %dv\n",adc_voltage);

    return adc_voltage;
}

uint32_t adc_btn_get_button_id (uint32_t adc_vtg)
{ 
    
    adc_btn_id_t button_id = 0;

        //voltage = adc_btn_get_voltage(7); //adc_btn_get_voltage(adc_ch)
        //printf("Drv_get_btn_id_voltage = %dv\n",adc_vtg);
        
        if (adc_vtg < ((btn_voltage_level[0] + btn_voltage_level[1])/2)){   //if adc_vtg<735, then button_id=0, i.e. No btn pressed.
            //printf ("No press!\n");

            button_id = 0;
            
        }
        else {
            for (int i=0;i<USER_BUTTON_MAX;i++){
                
                if (((adc_vtg >= btn_voltage_level[i]) && (adc_vtg <= btn_voltage_level[i+1]))) // ex, >=980 and <=1190, between S1~S2.
                {
                    
                    if ((adc_vtg < ((btn_voltage_level[i] + btn_voltage_level[i+1])/2))){   // ex, <1085, S1 pressed.
              
                        button_id = i;
                        
                    }
                    else {      //ex, >1085, S2 pressed.

                        button_id = i+1;
                        
                    }
                }
            }
        }

    return button_id;
     

}


uint32_t adc_btn_get_state (uint32_t btnid,uint32_t cnt)
{
    adc_btn_state_t current_st;
    
    
    if (btnid == 0){
        
        current_st = ADC_BTN_STATE_IDLE;
    }
    else if (cnt <= 30){
        
        //g_cb(NULL, g_adc_ch, btnid, ADC_BTN_STATE_PRESSED);
        current_st = ADC_BTN_STATE_PRESSED;
        //printf("press cnt=%d\n",cnt);
        cnt = 0;
        }
    else if (cnt > 30){
        
        //g_cb(NULL, g_adc_ch, btnid, ADC_BTN_STATE_LONG_PRESSED);
        current_st = ADC_BTN_STATE_LONG_PRESSED;
        //printf("long_press cnt=%d\n",cnt);
        cnt = 0;
        }
   
        
    return current_st;
}


