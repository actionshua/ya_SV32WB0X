#ifndef _DRV_ADCBTN_H_
#define _DRV_ADCBTN_H_

//#ifndef _ADC_BUTTON_H_
//#define _ADC_BUTTON_H_

#include "soc_types.h"

#include "sys/intc.h"               // components/

#define USER_BUTTON_MAX     9       //real button number + 1

/**
* ADC channels and GPIO table
*   ADC0 - GPIO00
*   ADC1 - GPIO01
*   ADC2 - GPIO02
*   ADC3 - GPIO30
*   ADC4 - GPIO31
*   ADC5 - GPIO32
*   ADC6 - GPIO33
*   ADC7 - GPIO34
*
**/

typedef enum {
    BTN_NONE = 0,       //0: No button pressed
    BTN_1 = 1,          //1: "PLAY/PAUSE" button pressed
    BTN_2 = 2,          //2: "REC/STOP" button pressed
    BTN_3 = 3,          //3: "NEXT" button pressed
    BTN_4 = 4,          //4: "PREVIOUS" button pressed
    BTN_5 = 5,          //5: "VOL+" button pressed
    BTN_6 = 6,          //6: "VOL-" button pressed
    BTN_7 = 7,          //7: BTN7 button pressed
    BTN_8 = 8,          //8: BTN8 button pressed
} adc_btn_id_t;

typedef struct {
    int adc_ch;
    int adc_level_step;
    int total_steps;
    int press_judge_time;
} adc_arr_t;

typedef enum {
    ADC_BTN_STATE_IDLE,             // 0: idle
    ADC_BTN_STATE_ADC,              // 1: detect
    ADC_BTN_STATE_PRESSED,          // 2: pressed
    ADC_BTN_STATE_RELEASE,          // 3: press released
    ADC_BTN_STATE_LONG_PRESSED,     // 4: long pressed
} adc_btn_state_t;
/*
typedef struct {
    int         active_id;
    int         click_cnt;    // Timer tick count
    int         long_click;
} btn_decription;

typedef struct adc_btn {
    adc_arr_t adc_info;
    btn_decription *btn_dscp;
    struct adc_btn *next;
} adc_btn_list;

typedef struct {
    int task_stack;
    int task_prio;
    int task_core;
    bool ext_stack;
} adc_btn_task_cfg_t;
*/

typedef void (*adc_button_callback) (void *user_data, int adc, int id, adc_btn_state_t state);

void adc_btn_init (adc_arr_t *p_btn, int num, uint16_t ch, adc_button_callback cb);

uint32_t adc_btn_get_voltage (uint16_t ch);
uint32_t adc_btn_get_button_id (uint32_t adc_voltage);
uint32_t adc_btn_get_state (uint32_t button_id,uint32_t click_cnt);
void adc_btn_task(void *pdata);
void adc_btn_set_cb (adc_button_callback cb);



//adc_btn_list *adc_btn_create_list(adc_arr_t *adc_conf, int channels);

//esp_err_t adc_btn_destroy_list(adc_btn_list *head);

//void adc_btn_delete_task(void);




#endif
