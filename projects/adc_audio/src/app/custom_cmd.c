#include <stdio.h>
#include <string.h>
#include "osal.h"

#include "cli.h"
#include "error.h"

#include <drv_adc.h>
#include <drv_pwm.h>

#if defined(SUPPORT_PERIPHERAL_ADCBTN) && (SUPPORT_PERIPHERAL_ADCBTN==1)
#include <drv_adcbtn.h>
#endif

#include <drv_tmr.h>
#include <drv_comport.h>
#include "logger.h"

#include <bsp.h>

#if defined(SUPPORT_PERIPHERAL_ADCBAT) && (SUPPORT_PERIPHERAL_ADCBAT==1)
#include <drv_adcbat.h>
#endif


#define CMD_TAG       LOG_TAG_CMD
#define CMD_LOG_E(format, ...) log_e(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_W(format, ...) log_w(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_I(format, ...) log_i(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_D(format, ...) log_d(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_V(format, ...) log_v(CMD_TAG, format, ##__VA_ARGS__)

/*---------------------------------- CMDs -----------------------------------*/
static uint8_t read_count = 10;
int Cmd_echo(int32_t argc, char *argv[])
{
	int loop_i;
	for (loop_i = 0;loop_i < argc; loop_i++) {
		printf("argv[%d] = %s\n", loop_i, argv[loop_i]);
	}
    return 0;
}

int Cmd_adc_cali_start(s32 argc, char *argv[])
{
    
    int i=0;
    uint32_t audio_ch = 0;
	
	audio_ch = strtoul(argv[1], NULL, 10);

    if ((argc != 2) || (audio_ch > 7) || (audio_ch < 0)) {
        printf("Usage   : adc_cali_start <id>\n");
        printf("<id>    : adc id(0-7)\n");
        return 0;
    }

    //set adc ctrl    
    drv_adc_init(audio_ch);
    drv_adc_fifo_ctrl(ADC_FIFO_TH_1);   

    drv_adc_trigger_event_en(audio_ch, ADC_TRIGGLE_AUTO); //trigger event set auto

    drv_adc_fifo_rst();
    drv_adc_enable();
   
    for(i=0;i<20;i++)
    {
        drv_adc_fifo_rst();
        OS_MsDelay(100);
        printf("adc code = %d\n", hal_adc_fifo_read()&0xfff);     
    }
 
    drv_adc_disable();

        return 0;
}


/////////////
// adc audio example
////////////

#define ADC_VOICE_FILE "adc_voice.csv"

#define USE_BUF_NUM MAX_ADC_AUDIO_BUF_NUM
#define AUDIO_BUF_LEN 160 

#define RECORD_TIME_SECOND 20

struct _args {
    char args;
    char argv[4][256];
};

static int adc_audio_buf_init(adc_audio_buffer *audio_buf, int buf_len)
{
    int cnt = 0;
    memset(audio_buf, 0, sizeof(adc_audio_buffer));
    audio_buf->use_buf_num = USE_BUF_NUM;
    for(cnt = 0; cnt < USE_BUF_NUM; cnt++) 
    {
        audio_buf->ping_pong[cnt].buffer_idx = 0;
        audio_buf->ping_pong[cnt].data_ready = 0;
        audio_buf->ping_pong[cnt].buffer = OS_MemAlloc(buf_len*2);  // sizeof(uint16_t) = 2 
        memset(audio_buf->ping_pong[cnt].buffer,0, buf_len);
        if(audio_buf->ping_pong[cnt].buffer == NULL) 
        {
            printf("buf alloc fail, cnt: %d, size: %d \n", cnt, buf_len);
            return -1;
        }
        audio_buf->ping_pong[cnt].buffer_len = buf_len;
    }
    audio_buf->pingpong_idx = 0;


    return 0;
}

void adc3_audio_record(void *pdata)
{
    struct _args *args = (struct _args *)pdata;
    
    int rlt = 0;
    int idx = 0;
    int buf_len = AUDIO_BUF_LEN;
    int audio_channel = strtol(args->argv[1], NULL, 10);
    int sampling_rate = strtol(args->argv[2], NULL, 10);
    int noise_offset = strtol(args->argv[3], NULL, 10);

    uint32_t start_record_time = 0;

    printf("use ADC%d to Record\n", audio_channel);
    printf("sample_rate = %d\n", sampling_rate);
    printf("noise offset = %d\n", noise_offset);
    
    //init audio buffer    
    adc_audio_buffer audio_buf;
    adc_audio_buf_init(&audio_buf, buf_len);

    drv_adc_audio_init(audio_channel, noise_offset);
    drv_adc_audio_set_buffer(&audio_buf);
    drv_adc_audio_start(sampling_rate);

    start_record_time = OS_GetSysTick();
    while( (OS_GetSysTick() - start_record_time) < RECORD_TIME_SECOND*1000)
    {
        while(audio_buf.ping_pong[idx].data_ready)
        {
            struct _adc_audio_buffer_st *buf = &audio_buf.ping_pong[idx];
            uint8_t *local_buf = (uint8_t*)buf->buffer;
            int local_len = buf->buffer_len;

            //output to uart
            drv_comport_write_fifo((uint8_t*)&local_buf[0], local_len*2, UART_BLOCKING);
            
            audio_buf.ping_pong[idx].data_ready = 0;
            audio_buf.ping_pong[idx].buffer_idx = 0;
            idx = ((idx + 1) % USE_BUF_NUM);
        }
        OS_UsDelay(10);     
    }

    drv_adc_audio_stop();
    drv_adc_audio_deinit();

    OS_MemFree(audio_buf.ping_pong[0].buffer);
    OS_MemFree(audio_buf.ping_pong[1].buffer);
   
    OS_TaskDelete(NULL);
            
}

int Cmd_start_audio_record(s32 argc, char *argv[])
{
    if(argc < 4)
    {
        printf("Command Error\n");
        printf("CMD: %s ch sampling offset\n", argv[0]);
        printf("EX: %s 3 16000 0\n", argv[0]);
        return -1;
    }
    struct _args *cmd_args = (struct _args *)OS_MemAlloc(sizeof(struct _args));
    strcpy(cmd_args->argv[0], argv[0]); //
    strcpy(cmd_args->argv[1], argv[1]); //ch
    strcpy(cmd_args->argv[2], argv[2]); //sample rate 
    strcpy(cmd_args->argv[3], argv[3]); //noise offset   



    OS_TaskCreate(adc3_audio_record, "audio record", 512, cmd_args, OS_TASK_MIDDLE_PRIO, NULL);   

    return 0;
}
/* ---------------------- ADC Battery example code (Start)---------------------- */
#if defined(SUPPORT_PERIPHERAL_ADCBAT) && (SUPPORT_PERIPHERAL_ADCBAT==1)

int Cmd_adc_bat(s32 argc, char *argv[])
{
    //adc_bat_init(ADC_EXT_VOLTAGE_GPIO_GPIO30);
    adc_bat_init(6);    //Ex. WB02, GPIO02 ADC2

    return 0;
}

#endif

/* ---------------------- Registered CMDs to CMD Table ---------------------- */
const CLICmds gCustomCmdTable[] =
{
    { "adc_cali_start",              Cmd_adc_cali_start,          "adc_cali_start <id>"        },
    { "start_record",       Cmd_start_audio_record,     "start_record <id> <sampling_rate> <offset> "},
    #if defined (SUPPORT_PERIPHERAL_ADCBAT) && (SUPPORT_PERIPHERAL_ADCBAT==1)
    //{ "adc_bat",                Cmd_adc_bat,               "adc battery function"  },
    #endif

    { (const char *)NULL,       (CliCmdFunc)NULL,          (const char *)NULL      },
};


