#include <stdio.h>
#include <string.h>
#include <osal.h>
#include <bsp.h>
#include "drv_gpio.h"
#include "drv_i2s.h"
#if(CHIP_ID!=6006)
#include "drv_pdm.h"
#endif

#define MP3_PATH "/sdcard/mp3"
#define DEBOUNCE_TIME 300
#define USE_BUF_NUM    6
extern void helix_fsal_player(void *param);
static void gpio_debouncing(int enable);
static void button_play_pause();
static void button_stop_record();
static void button_next();
static void button_prev();
static void button_vol_plus();
static void button_vol_minus();
void Cli_Task( void *args );

typedef void(*pButton)();

struct _args {
    char args;
    char argv[8][256];
};

typedef struct _but_info
{
    int but_id;
    pButton pHandle;
} but_info;

const but_info but_info_table[] =
{
#if 0//disable, need change adc button
    {GPIO_09, button_play_pause},
    {GPIO_10, button_stop_record},
    {GPIO_11, button_next},
    {GPIO_12, button_prev},
    {GPIO_14, button_vol_plus},
    {SIO_15, button_vol_minus},
#endif
};

extern int g_mp3_fsal_player_stop;
extern int g_mp3_fsal_player_pause;
extern int g_mp3_fsal_player_exit;
int player_en = 0;
int record_en = 0;
int record_stop = 0;
int total_music = 0;
int now_music = 1;
int adjust_music = 0;
static OsTimer gpio_detect_timer;

static int get_sdc_mp3_name(int idx, char *name)
{
    int cnt = 0, res = 0;
    SSV_DIR dir;
    SSV_DIRENT dirent;
    FS_opendir(fs_handle, MP3_PATH, &dir);
    if ((res = FS_derrno(dir)) == 0) { 
        if ((res = FS_derrno(dir)) == 0) {
            while (FS_readdir(&dir, &dirent)) {
                cnt++;
                if(idx == cnt) {
                    sprintf(name,"%s/%s",MP3_PATH, dirent.name);
                }
            }
            FS_closedir(&dir);
            if ((res = FS_derrno(dir)) != 0) {
                printf("dir %s close fail! res=%d\n", '/', res);
                return -1;
            }
        } else {
            printf("dir %s open fail! res=%d\n", '/', res);
            return -1;
        }
    }
    return strlen(name);
}

static int get_sdc_mp3_num()
{
    int total = 0, res = 0;
    SSV_DIR dir;
    SSV_DIRENT dirent;
    FS_opendir(fs_handle, MP3_PATH, &dir);
    if ((res = FS_derrno(dir)) == 0) { 
        if ((res = FS_derrno(dir)) == 0) {
            while (FS_readdir(&dir, &dirent)) {
                total++;
            }
            FS_closedir(&dir);
            if ((res = FS_derrno(dir)) != 0) {
                printf("dir %s close fail! res=%d\n", '/', res);
                return -1;
            }
        } else {
            printf("dir %s open fail! res=%d\n", '/', res);
            return -1;
        }
    }
    return total;
}

static void fsal_evthandler(SSV_FS_EVENT evt) {
    switch (evt) {
    case SSV_SDC_PLUGIN:
        OS_EnterISR();
        total_music = get_sdc_mp3_num();
        printf("total_numic: %d\n", total_music);
        OS_ExitISR();
        printf("%s: %d: %s(): SD Card is plugged in. (%d)\n", __FILE__, __LINE__, __func__, evt);
        drv_gpio_set_logic(28, 1);
        break;
    case SSV_SDC_UNPLUG:
        player_en = 0;
        total_music = 0;
        now_music = 1;
        adjust_music = 0;
        g_mp3_fsal_player_exit = 1;
        g_mp3_fsal_player_pause = 0;
        printf("%s: %d: %s(): SD Card is unplugged. (%d)\n", __FILE__, __LINE__, __func__, evt);
        drv_gpio_set_logic(28, 0);
        break;
    default:
        printf("%s: %d: %s(): Unknown event. (%d)\n", __FILE__, __LINE__, __func__, evt);
        total_music = 0;
        break;
    }
}

static void button_vol_minus()
{
    int val = 0; 
    if(record_en == 0) {
        if(player_en == 1) {
            val = REG32(0xc000501c);
            if(val <= 6 || val > 60)
                val = 0;
            else
                val-= 6;

            REG32(0xc000501c) = val;
            printf("val: %d\n",val);
        }
    }
}

static void button_vol_plus()
{
    int val = 0; 
    if(record_en == 0) {
        if(player_en == 1) {
            val = REG32(0xc000501c);
            if(val >= 60)
                val = 60;
            else
                val+=6;

            REG32(0xc000501c) = val;
            printf("val: %d\n", val);
        }
    }
}

static void button_prev()
{
    if(record_en == 0) {
        if(player_en == 1) {
            g_mp3_fsal_player_exit = 1;
            adjust_music--;
            printf("music id: %d\n", adjust_music);
        }
    }
}

static void button_next()
{
    if(record_en == 0) {
        if(player_en == 1) {
            g_mp3_fsal_player_exit = 1;
            adjust_music++;
            printf("music id: %d\n", adjust_music);
        }
    }
}

static void button_stop_record()
{
    if(record_en == 0) {
        if(player_en == 1) {
            player_en = 0;
            now_music = 1;
            adjust_music = 0;
            g_mp3_fsal_player_exit = 1;
            g_mp3_fsal_player_pause = 0;
        } else {
            record_en = 1;
            record_stop = 0;
        }
    } else {
        record_stop = 1;
    }
}

static void button_play_pause()
{
    if(record_en == 0) {
        if(player_en == 0) {
            if(total_music > 0) {
                player_en = 1;
            }
        } else {
            g_mp3_fsal_player_pause = !g_mp3_fsal_player_pause;
        }
    }
}

static void timer_restart()
{
	OS_TimerStop(gpio_detect_timer);
	OS_TimerStart(gpio_detect_timer);
}

static void irq_button_det(uint32_t irq_num)
{
    int cnt = 0;
    int but_num = sizeof(but_info_table)/sizeof(but_info);
	drv_gpio_intc_clear(irq_num);
    gpio_debouncing(0);
    printf("det(%d)\n", irq_num);

    for(cnt = 0; cnt < but_num; cnt++) {
        if(irq_num == but_info_table[cnt].but_id) {
            but_info_table[cnt].pHandle();
        }
    }

    timer_restart();
}

static void gpio_debouncing(int enable)
{
    int cnt = 0;
    int but_num = sizeof(but_info_table)/sizeof(but_info);
    printf("debouncing: %d %d\n", enable, but_num);
    if(enable == 1) {
        for(cnt = 0; cnt < but_num; cnt++) {
            drv_gpio_intc_clear(but_info_table[cnt].but_id);
            drv_gpio_register_isr(but_info_table[cnt].but_id, irq_button_det);
        }
    } else {
        for(cnt = 0; cnt < but_num; cnt++) {
            drv_gpio_register_isr(but_info_table[cnt].but_id, NULL) ;
        }
    }
}

static void timer_to_do()
{
    gpio_debouncing(1);
}


static void record_buf_deinit(i2s_buffer *i2s_buf)
{
    int cnt = 0;
    for(cnt = 0; cnt < USE_BUF_NUM; cnt++) {
        if(i2s_buf->ping_pong[cnt].buffer != NULL) {
            OS_MemFree(i2s_buf->ping_pong[cnt].buffer);
        }
    }
}

static int record_buf_init(i2s_buffer *i2s_buf, int buf_len)
{
    int cnt = 0;
    memset(i2s_buf, 0, sizeof(i2s_buffer));
    for(cnt = 0; cnt < USE_BUF_NUM; cnt++) {
        i2s_buf->ping_pong[cnt].buffer_idx = 0;
        i2s_buf->ping_pong[cnt].data_ready = 0;
        i2s_buf->ping_pong[cnt].buffer = OS_MemAlloc(buf_len);
        memset(i2s_buf->ping_pong[cnt].buffer,1, buf_len);
        if(i2s_buf->ping_pong[cnt].buffer == NULL) {
            printf("buf alloc fail, cnt: %d, size: %d \n", cnt, buf_len);
            return -1;
        }
        i2s_buf->ping_pong[cnt].buffer_len = buf_len;
    }
    i2s_buf->pingpong_idx = 0;
    i2s_buf->dup_sample = 0;
    i2s_buf->i2s_dup_sample_idx = 0;
    i2s_buf->idle_cnt = 0;
    i2s_buf->stereo = 1;
    i2s_buf->event = NULL;

    return 0;
}

static void record_play(void *param)
{
    int module = 0;
    int data_mode = 1;
    int pdm_en = 1;
    int buf_len = 16000;
    i2s_buffer i2s_buf;
    int no_data_cnt = 0;
    int idx = 0;
    int res = 0, ret = 0;
    int one_time = 0; 
    int nRead = 0;
    short *outBuf;
    static SSV_FILE file;

#if 1
    drv_gpio_set_logic(29, 1);
    printf("=====record begin=====\n"); 
    drv_i2s_init_ex(module, mode_master, SampleRate_48000HZ, Resolution_16bit);
#if(CHIP_ID!=6006)
    if(pdm_en == 1) {
        drv_pdm_rx_enable(module, PDM_Rx_SampleRate_16000HZ, PDM_RX_STEREO);
    }
#endif
    if(record_buf_init(&i2s_buf, buf_len) < 0)
        goto FREE;
    drv_i2s_set_buffer_ex(module, &i2s_buf, USE_BUF_NUM, NULL, 0);
    drv_i2s_rx_start_ex(module, DRV_SampleRate_mormal, data_mode);

    FS_remove(fs_handle, "/sdcard/record.pcm");
    file = FS_open(fs_handle, "/sdcard/record.pcm", SPIFFS_O_CREAT | SPIFFS_RDWR, 0);

    while(!record_stop) {
        no_data_cnt++;
        while(i2s_buf.ping_pong[idx].data_ready && (!record_stop)) {
            no_data_cnt = 0;
            struct _i2s_buffer_st *buf = &i2s_buf.ping_pong[idx];
            uint8_t *local_buf = (uint8_t *)buf->buffer; 
            int local_len = buf->buffer_len;
            ret = FS_write(fs_handle, file, local_buf, local_len);
            if ((res = FS_ferrno(file)) != 0) {
                printf("file write fail: res=%d\n", res);
                FS_close(fs_handle, file);
                record_stop = 1;
                continue;
            }
            i2s_buf.ping_pong[idx].data_ready = 0;
            idx = ((idx + 1) % USE_BUF_NUM);
        }
        if (no_data_cnt > 10000) {         
            printf("no data input\n");                                                                                                                                                                          
        }
        OS_MsDelay(1);
    }
    FS_close(fs_handle, file);
    drv_i2s_rx_stop_ex(module); 
    record_buf_deinit(&i2s_buf);
    printf("=====record play=====\n");
    file = FS_open(fs_handle, "/sdcard/record.pcm", SPIFFS_RDWR, 0);
#if(CHIP_ID!=6006)
    if(pdm_en == 1) {
        drv_pdm_tx_enable(module, 16, PDM_TX_Bit_Depth_16, PDM_TX_STEREO, 0);
    }
#endif
    buf_len = 8000;
    if(record_buf_init(&i2s_buf, buf_len) < 0)
        goto FREE;
    drv_i2s_set_buffer_ex(module, NULL, 0, &i2s_buf, USE_BUF_NUM);
    idx = 0;
    while(1) {
        struct _i2s_buffer_st *buf = &(i2s_buf.ping_pong[idx]);
        if (!buf->data_ready) {
            outBuf = buf->buffer;
            nRead = FS_read(fs_handle, file, outBuf, buf_len);
            if(nRead <= 0) {
                break;
            }
            buf->buffer_idx = 0;
            buf->buffer_len = buf_len;
            buf->data_ready = 1;
        }
        if (!one_time) {
            one_time = !one_time;
            drv_i2s_tx_start_ex(module, data_mode);
        }
        idx = ((idx + 1) % USE_BUF_NUM);
        while(i2s_buf.ping_pong[idx].data_ready) {
            OS_MsDelay(1);
        }
    }
#if(CHIP_ID!=6006)
    if(pdm_en == 1)
        drv_pdm_tx_disable(module);
#endif
    drv_i2s_tx_stop_ex(module);   

FREE:
    record_buf_deinit(&i2s_buf);
#endif
//EXIT:
    record_en = 0;
    printf("=====record exit=====\n");
    drv_gpio_set_logic(29, 0);
    OS_TaskDelete(NULL);
}

void player_and_recorder(void *param)
{
    char name[256];
    int32_t name_len = 0;

    printf("=====player begin=====\n"); 
    FS_register_evthandler(fsal_evthandler);
    while(1) { 
        if(record_en) {
            OS_TaskCreate(record_play, "recorder", 1024, NULL, OS_TASK_LOW_PRIO, NULL);
            while(record_en == 1)
                OS_MsDelay(1);
        }
        while(player_en) {
            memset(name, 0, 256);
            name_len = get_sdc_mp3_name(now_music, name);
            if(name_len <= 0) {
                printf("get music name fail\n");
                OS_MsDelay(1);
                continue;
            }
            g_mp3_fsal_player_stop = 0;
            g_mp3_fsal_player_exit = 0;
            printf("music: %s (%d %d)\n", name, now_music, total_music);
            struct _args *cmd_args = (struct _args *)OS_MemAlloc(sizeof(struct _args));
            strcpy(cmd_args->argv[0], "start_mp3");
            strcpy(cmd_args->argv[1], name);
            strcpy(cmd_args->argv[2], "0");
            strcpy(cmd_args->argv[3], "1");
            strcpy(cmd_args->argv[4], "1");

            OS_TaskCreate(helix_fsal_player, "helix", 1024*3+2048, cmd_args, OS_TASK_LOW_PRIO, NULL);
            while(g_mp3_fsal_player_stop == 0) {
                OS_MsDelay(1);
            }
            printf("==== play music finish ====\n");
            if(adjust_music == 0)
                now_music++;
            else {
                now_music += adjust_music;
                adjust_music = 0;
            }
            if((now_music >= total_music))
                now_music = 1;
            else if((now_music <= 0))
                now_music = 1;
        }
        OS_MsDelay(1);
    }
    printf("=====player exit=====\n"); 
    OS_TaskDelete(NULL);
}

void player_gpio_init()
{
#if 0//disable, need change adc button
    int cnt = 0;
    int but_num = sizeof(but_info_table)/sizeof(but_info);
	OS_TimerCreate(&gpio_detect_timer,DEBOUNCE_TIME,0,0,timer_to_do);
    for(cnt = 0; cnt < but_num; cnt++) {
        drv_gpio_set_mode(but_info_table[cnt].but_id, PIN_MODE_GPIO);
        drv_gpio_set_dir(but_info_table[cnt].but_id, GPIO_DIR_IN);
        drv_gpio_set_pull(but_info_table[cnt].but_id, GPIO_PULL_UP);
        drv_gpio_intc_trigger_mode(but_info_table[cnt].but_id, GPIO_INTC_FALLING_EDGE);
        drv_gpio_register_isr(but_info_table[cnt].but_id, irq_button_det);
    }
    drv_gpio_set_mode(16, 0);
    drv_gpio_set_dir(16, 1);
    drv_gpio_set_mode(28, 0);
    drv_gpio_set_dir(28, 1);
    drv_gpio_set_mode(29, 0);
    drv_gpio_set_dir(29, 1);
#endif
}
