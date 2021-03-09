#include <stdio.h>
#include <string.h>
#include <osal.h>
#include <bsp.h>
#include "drv_gpio.h"
#include "drv_i2s.h"
#include "drv_adc.h"
#include "drv_adcbtn.h"
#if(CHIP_ID!=6006)
#include "drv_pdm.h"
#endif
#include "speexdsp/include/speex/speex_echo.h"
#include "speexdsp/include/speex/speex_preprocess.h"
#include "webrtc/common_audio/vad/include/webrtc_vad.h"
#include "ml_kws/Source_C/KWS_C/kws.h"
#include "../ringbuf/ringbuf.h"
#include  "codec_common.h"

#define USE_BUF_NUM   2
#define CHANNELS        2
#define RECORD_SAMPLE    160
#define BYTES_WIDTH    sizeof(short)
#define RECORD_LEN    RECORD_SAMPLE*BYTES_WIDTH*CHANNELS
#define SAMPLE_RATE     SampleRate_16000HZ
#define TAIL RECORD_SAMPLE*20

//  ZCR stands for Zero Crossing Rate
#define ZCR_MIN  5
#define ZCR_MAX 30

//  Defines minimal permissible energy value
#define NOISE_ENERGY_MIN    10000

#define ALL_VOICE 20
#define NEED_VAD_ACTIVE 10

#define SOCKET_DEBUG
#define ENG_TH 0x140000
#define TIME_OUT 10 //10ms
#define KWS_RE_EN (100)//10ms * 100
#define VAD_GROUP_NUM 3
#define DUMMY_VOICE_NUM ( 5 - VAD_GROUP_NUM)
#define REAL_VOICE_DATA (ALL_VOICE*RECORD_SAMPLE*BYTES_WIDTH*VAD_GROUP_NUM)
#define MAX_CLASS_LEN 8
#define OUTPUT_CLASSES { "Silence", "Unknown","yes","no","up","down","left","right","on","off","stop","go" }

#define DEBOUNCE_TIME 300

struct _args {
    char args;
    char argv[8][256];
};
int16_t outbuf[VAD_GROUP_NUM][ALL_VOICE][1+RECORD_SAMPLE];
static int sg_tx_use[2] = {1,0};
static int sg_rx_use[2] = {0,0};
int alg_exit = 0;
#if(DEMO_TYPE==2)
int rx_mode = 1;
#else
int rx_mode = 0;
#endif

static struct RingBuf *aec_rb = NULL;
static SpeexEchoState *st;
static SpeexPreprocessState *den;
static VadInst* vadhandle = NULL;
static char *expect_class = NULL;

extern int16_t* kws_audio_buffer;
extern int kws_audio_buffer_size;
extern int kws_audio_block_size;
extern int kws_frame_len;
extern int kws_frame_shift;
extern int8_t *kws_averaged_output;
extern int8_t *kws_predictions;
extern int8_t *kws_output;
extern int kws_num_out_classes;
extern void helix_fsal_player(void *param);
extern int g_mp3_fsal_player_stop;
extern int g_mp3_fsal_player_pause;
extern int g_mp3_fsal_player_exit;

int player_en = 0;
int have_sd = 0;
int total_music = 0;
int music_cnt = 0;
int now_music = 1;
int adjust_music = 0;
uint32_t btn_begin_time = 0;
adc_arr_t btns[USER_BUTTON_MAX];

void guiTask(void *arg);
void terminal_add(const char * txt_in);

static char *getExtension(char *fileName){
    int len = strlen(fileName);
    int i = len;
    while( fileName[i]!='.' && i>0 ){ i--; }

    if(fileName[i]=='.'){
        return &fileName[i+1];
    }else{
        return &fileName[len];
    }
}

static int get_sdc_mp3_name(int idx, char* path, char *name)
{
    FRESULT res;
    DIR dir;
    UINT i, j;
    static FILINFO fno;
    char *extension, txtformat[]="mp3";
    res = f_opendir(&dir, path);
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno);
            if (res != FR_OK || fno.fname[0] == 0) break;

            if (fno.fattrib & AM_DIR) {
                i = strlen(path);
                j = strlen(fno.fname);
                if (j < 254 && (i+j) < 254) {
                    if (!strcmp(path, "/")) {
                        sprintf(&path[i], "%s", fno.fname);
                    } else {
                        sprintf(&path[i], "/%s", fno.fname);
                    }
                    res = get_sdc_mp3_name(idx, path, name);
                    if ((res != FR_OK) && (res != FR_INVALID_NAME)) {
                        //printf("##path=%s break: %d##\n", path, res);
                        break;
                    }
                } else {
                    //printf("%s/%s is too long!\n", path, fno.fname);
                }
                path[i] = 0;
            } else {
                extension = getExtension(fno.fname);
                if(strcmp(extension,txtformat)!=0)
                    continue;
                music_cnt++;
                if(idx == music_cnt) {
                    if (!strcmp(path, "/")) {
                        sprintf(&name[0], "/sdcard/%s\n", fno.fname);
                    } else {
                        sprintf(&name[0], "/sdcard%s/%s\n", path, fno.fname);
                    }
                    break;
                }
            }
        }
        f_closedir(&dir);
    }
    return res;
}

static int get_sdc_mp3_num(char* path)
{
    FRESULT res;
    DIR dir;
    UINT i, j;
    static FILINFO fno;
    char *extension, txtformat[]="mp3";
    res = f_opendir(&dir, path);
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno);
            if (res != FR_OK || fno.fname[0] == 0) break;

            if (fno.fattrib & AM_DIR) {
                i = strlen(path);
                j = strlen(fno.fname);
                if (j < 254 && (i+j) < 254) {
                    if (!strcmp(path, "/")) {
                        sprintf(&path[i], "%s", fno.fname);
                    } else {
                        sprintf(&path[i], "/%s", fno.fname);
                    }
                    res = get_sdc_mp3_num(path);
                    if ((res != FR_OK) && (res != FR_INVALID_NAME)) {
                        //printf("##path=%s break: %d##\n", path, res);
                        break;
                    }
                } else {
                    //printf("%s/%s is too long!\n", path, fno.fname);
                }
                path[i] = 0;
            } else {
                extension = getExtension(fno.fname);
                if(strcmp(extension,txtformat)!=0)
                    continue;
                total_music++;
                printf("#%s#\n", fno.fname);
            }
        }
        f_closedir(&dir);
    }
    return res;
}

void echo_player_evthandler(SSV_FS_EVENT evt) {
    char path[256];
    switch (evt) {
        case SSV_SDC_PLUGIN:
            have_sd = 1;
            strcpy(path,"/");
            OS_EnterISR();
            get_sdc_mp3_num(path);
            printf("total_numic: %d\n", total_music);
            OS_ExitISR();
            break;
        case SSV_SDC_UNPLUG:
            printf("=====unplug=====\n");
            player_en = 0;
            have_sd = 0;
            total_music = 0;
            now_music = 1;
            g_mp3_fsal_player_exit = 1;
            g_mp3_fsal_player_pause = 0;
            break;
        default:
            printf("%s: %d: %s(): Unknown event. (%d)\n", __FILE__, __LINE__, __func__, evt);
            total_music = 0;
            break;
    }
}

void kws_adc_button_callback (void *user_data, int adc, int id, adc_btn_state_t state)
{
    uint32_t btn_end_time = OS_GetSysTick();
    int vol = 0;
    //printf("%d btna is %d (%d)\n", id, state, g_mp3_fsal_player_pause);
    if((id >= 1) && (id <= 6)) {
        if((btn_end_time -btn_begin_time) > 500) {
            btn_begin_time = OS_GetSysTick();

            if (id == 1){
                if(player_en == 0) {
                    if(total_music > 0) {
                        player_en = 1;
                    }
                } else {
                    g_mp3_fsal_player_pause = !g_mp3_fsal_player_pause;
                }
            }
            else if (id == 2){
                if(player_en == 1) {
                    player_en = 0;
                    now_music = 0;
                    adjust_music = 0;
                    g_mp3_fsal_player_exit = 1;
                    g_mp3_fsal_player_stop = 1;
                    g_mp3_fsal_player_pause = 0;
                }
            }
            else if (id == 3){
                if(player_en == 1) {
                    g_mp3_fsal_player_exit = 1;
                    adjust_music++;
                    printf("music id: %d\n", adjust_music);
                }
            }
            else if (id == 4){
                if(player_en == 1) {
                    g_mp3_fsal_player_exit = 1;
                    adjust_music--;
                    printf("music id: %d\n", adjust_music);
                }
            }
            else if (id == 5){
                codec_get_volume(&vol);
                vol = vol+5;
                codec_set_volume(vol);
                printf("vol+: %d\n", vol);
            }
            else if (id == 6){
                codec_get_volume(&vol);
                vol = vol-5;
                codec_set_volume(vol);
                printf("vol-: %d\n", vol);
            }
        }
    } 
    //printf("%d btna is %d (%d)\n", id, state, g_mp3_fsal_player_pause);
}

static void i2s_buf_deinit(i2s_buffer *i2s_buf)
{
    int cnt = 0;
    for(cnt = 0; cnt < USE_BUF_NUM; cnt++) {
        if(i2s_buf->ping_pong[cnt].buffer != NULL) {
            OS_MemFree(i2s_buf->ping_pong[cnt].buffer);
        }
    }
}

static int i2s_buf_init(i2s_buffer *i2s_buf, int buf_len)
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

uint32_t VADFrameCalculateEnergy(int16_t *frames, int size) {
    uint32_t energy = 0;
    int16_t normal_frame = 0;
    for (size_t i = 0; i < size; i++) {
        normal_frame = abs(frames[i]);
        //energy += normal_frame;
        energy += (normal_frame*normal_frame);
    }
    //printf("==energy: %d size: %d ==\n", energy, size);
    return (energy /size);
}

uint32_t VADFrameCalculateZeroCrossingRate(int16_t*frame, int size) {
    int32_t zcr = 0;
    int32_t sign = 0;
    int32_t last_sign = 0;
    for (int16_t i = 0; i < size; i++) {
        sign = (frame[i] > 0) ? 1 : -1;

        if ((last_sign != 0) && (sign != last_sign)) {
            zcr++;
        }
        last_sign = sign;
    }

    return zcr;
}

void kws_task_init()
{
#if 1
#if 1
    kws_audio_buffer = (int16_t *)OS_MemAlloc(sizeof(int16_t) * 16000);
    if(kws_audio_buffer != NULL) {
    memset(kws_audio_buffer, 0, (sizeof(int16_t) * 16000));
    kws_nn_init_with_buffer(kws_audio_buffer);
    } else {
        printf("kws_task_init malloc fail\n");
    }
#else
    kws_nn_init(recording_win,averaging_window_len);
    kws_audio_buffer = malloc(sizeof(int16_t) * kws_audio_buffer_size);
    memset(kws_audio_buffer, 0, (sizeof(int16_t) * kws_audio_buffer_size));
#endif
#endif
}

void kws_deinit()
{
#if 1
    kws_nn_deinit();
    OS_MemFree(kws_audio_buffer);
#endif
}

void run_kws(int16_t *data)
{
#if 1
    int i = 0, max_ind = 0;
    char output_class[][MAX_CLASS_LEN] = OUTPUT_CLASSES;
#if 0
    if(kws_frame_len!=kws_frame_shift) {
        arm_copy_q7((int8_t *)(kws_audio_buffer)+2*(kws_audio_buffer_size-(kws_frame_len-kws_frame_shift)), (int8_t *)kws_audio_buffer, 2*(kws_frame_len-kws_frame_shift));
    }
    // copy the new recording data
    printf("kws_audio_block_size: %d %d %d\n", kws_audio_block_size, kws_frame_len, kws_frame_shift);
    for (int i=0;i<kws_audio_block_size;i++) {
        kws_audio_buffer[kws_frame_len-kws_frame_shift+i] = data[i * 1];
    }
#endif
    kws_extract_features();    //extract mfcc features
    kws_classify();        //classify using dnn
    //kws_average_predictions();
    max_ind = kws_get_top_class((char *)kws_output);
    //printf("avg: %d %s\n", kws_averaged_output[max_ind], output_class[max_ind]);
    //if((kws_averaged_output[max_ind]>detection_threshold*128/100)) {
    printf("Detected %s (%d%%)\r\n",output_class[max_ind],((int)kws_output[max_ind]*100/128));
    if(max_ind == 10) {
        //printf("%d%% %s\n",((int)kws_averaged_output[max_ind]*100/128),output_class[max_ind]);
        if(player_en == 1) {
            player_en = 0;
            now_music = 0;
            adjust_music = 0;
            g_mp3_fsal_player_exit = 1;
            g_mp3_fsal_player_stop = 1;
            g_mp3_fsal_player_pause = 0;
        }
    } else if(max_ind == 11) {
        //printf("%d%% %s\n",((int)kws_averaged_output[max_ind]*100/128),output_class[max_ind]);
        if(player_en == 0) {
            player_en = 1;
        }
    } else {
        printf("unknown: %d\n", max_ind);
    }
    if (expect_class && strcmp(expect_class, output_class[max_ind]))
        printf("Wrong! expect: %s\n", expect_class);
    //}
#endif
}

void speex_init(int sampleRate)
{
    st = speex_echo_state_init(RECORD_SAMPLE, TAIL);
    den = speex_preprocess_state_init(RECORD_SAMPLE, sampleRate);
    speex_echo_ctl(st, SPEEX_ECHO_SET_SAMPLING_RATE, &sampleRate);
    speex_preprocess_ctl(den, SPEEX_PREPROCESS_SET_ECHO_STATE, st);
}

void speex_deinit()
{
    speex_echo_state_destroy(st);
    speex_preprocess_state_destroy(den);
}

void vad_init()
{
    WebRtcVad_Create(&vadhandle);
    WebRtcVad_Init(vadhandle);
    WebRtcVad_set_mode(vadhandle, 3);
}

void vad_deinit()
{
    WebRtcVad_Free(vadhandle);
    vadhandle = NULL;
}

void sppex_vad_run(int16_t *in, int16_t *ref) ATTRIBUTE_SECTION_FAST;
void sppex_vad_run(int16_t *in, int16_t *ref)
{
    uint8_t tmp[(RECORD_SAMPLE*BYTES_WIDTH)];
    int status = 0, check_en = 0, i = 0, j = 0, idx = 0, now = 0;
    static int rb_idx = 0, offset = 0, vad_have = 0, energy = 0, dump_en = 0, trash =  0;
    speex_echo_cancellation(st, in, ref, &(outbuf[rb_idx][offset][1]));
    speex_preprocess_run(den, &(outbuf[rb_idx][offset][1]));
    //memcpy(&(outbuf[rb_idx][offset][1]), in, (RECORD_SAMPLE*BYTES_WIDTH));
    status = WebRtcVad_Process(vadhandle, SAMPLE_RATE, &(outbuf[rb_idx][offset][1]), (RECORD_SAMPLE));
    if(status == 1) {
        outbuf[rb_idx][offset][0] = 1;
        vad_have++;
        energy += VADFrameCalculateEnergy(&(outbuf[rb_idx][offset][1]), (RECORD_SAMPLE));
    } else {
        outbuf[rb_idx][offset][0] = 0;
    }
    check_en = ((offset + 1) ==ALL_VOICE) ? 1 : 0;
    if(check_en == 1) {
        if(trash == 0) {
            if(dump_en == 1) {
                idx = (rb_idx <= 1) ? (VAD_GROUP_NUM - 2+rb_idx): (rb_idx - 2);
                //printf("dump: %d avg: %x\n", idx, rb_idx);
                for(j = 0; j < VAD_GROUP_NUM; j++) {
                    now = ((j+idx)%VAD_GROUP_NUM);
                    if(rb_isFull(aec_rb)) {
                        printf("====full read: %d====\n", rb_isFull(aec_rb));
                        for(i = 0; i < ALL_VOICE; i++)
                            rb_read(aec_rb, tmp, (RECORD_SAMPLE*BYTES_WIDTH), portMAX_DELAY, 0);
                    } else {
                        //printf("now: %d\n", now);
                        for(i = 0; i < ALL_VOICE; i++) {
                            //printf("== now: %d idx: (%d  %d) rb_idx: %d ==\n", now, idx, i, rb_idx);
                            rb_write(aec_rb, (uint8_t *)&(outbuf[now][i][1]), (RECORD_SAMPLE*BYTES_WIDTH), portMAX_DELAY, 0);
                        }
                    }
                }
                dump_en = 0;
                trash = 2;
            } else {
                dump_en = (vad_have >= NEED_VAD_ACTIVE) ? 1 : 0;
                if(vad_have > 0) {
                   // printf("energy: %x vad_have: %d avg: %x\n", energy, vad_have, energy /vad_have);
                    //energy = energy /vad_have;
                    if((energy/vad_have) < ENG_TH)
                        dump_en = 0;
                }
            }
        } else {
            trash--;
        }
        energy = 0;
        vad_have = 0;
    }

    //printf("offset: %d rb_idx: %d\n", offset, rb_idx);
    offset = (offset + 1) % ALL_VOICE;
    rb_idx = (offset == 0) ? ((rb_idx+1)%VAD_GROUP_NUM) : rb_idx;
    //energy = (offset == 0) ? 0 : energy;
}

void kws_task(void *param)
{
    int status = 0, i = 0;
    int len = (RECORD_SAMPLE*BYTES_WIDTH*100);
    int read = (RECORD_SAMPLE*BYTES_WIDTH*60);
    uint8_t buf[len];
    int kws_re_en = 0, real_voice = 0;
    kws_task_init();
    OS_EnterCritical();
    printf("\n==enter kws: %d %d==\n", sizeof(int16_t) * kws_audio_buffer_size, len);
    OS_ExitCritical();

    while(alg_exit == 0) {
        memset(kws_audio_buffer, 0, len);
        status = rb_read(aec_rb, (uint8_t *)(kws_audio_buffer), read, TIME_OUT, 0);
        //printf("kws: %d %d\n", real_voice, REAL_VOICE_DATA);
        if(status == -1) {
            real_voice = 0;
            if(++kws_re_en >= KWS_RE_EN) {
                kws_re_en = 0;
            }
            continue;
        } else {
            kws_re_en = 0;
            real_voice += len;
            printf("w\n");
            run_kws((int16_t *)kws_audio_buffer);
            //if(real_voice >= REAL_VOICE_DATA) {
                //memset(buf, 0 , len);
                //for(i = 0; i < DUMMY_VOICE_NUM; i++) {

                    //run_kws((int16_t *)buf);
                //}
                //real_voice = 0;
            //}
        }
    }

    OS_EnterCritical();
    printf("\n==exit kws==\n");
    OS_ExitCritical();
    kws_deinit();

    OS_TaskDelete(NULL);
}

void echo_record(void *param)
{
    alg_exit = 0;
    sg_rx_use[rx_mode] = 1;
    i2s_buffer i2s_buf;
    int16_t tmp1[RECORD_SAMPLE];
    int16_t tmp2[RECORD_SAMPLE];
    int i = 0, idx = 0, no_data_cnt = 0;
    int buf_len = RECORD_LEN;

    OS_EnterCritical();
    printf("\n==enter echo record==\n");
    OS_ExitCritical();

    if(i2s_buf_init(&i2s_buf, buf_len) < 0)
        goto FREE;
    speex_init(SAMPLE_RATE);
    vad_init();

    aec_rb = rb_init(100*RECORD_LEN);
    OS_TaskCreate(kws_task, "kws", 1600, NULL, OS_TASK_LOW_PRIO, NULL);

    drv_i2s_init_ex(rx_mode, mode_master, SampleRate_16000HZ, Resolution_16bit);
    drv_i2s_set_buffer_ex(rx_mode, &i2s_buf, USE_BUF_NUM, NULL, 0);
    drv_i2s_rx_start_ex(rx_mode, DRV_SampleRate_mormal, 1);
        
    while(sg_rx_use[rx_mode]) {
        no_data_cnt++;
        while(i2s_buf.ping_pong[idx].data_ready && (sg_rx_use[rx_mode])) {
            no_data_cnt = 0;
            struct _i2s_buffer_st *buf = &i2s_buf.ping_pong[idx];
            uint16_t *local_buf = (uint16_t *)buf->buffer;
            int local_len = buf->buffer_len;
            for(i = 0; i < RECORD_SAMPLE; i++) {
                *(tmp2 + i) = *(local_buf + (i*CHANNELS));
                *(tmp1 + i) = *(local_buf + ((i*CHANNELS) + 1));
            }
            sppex_vad_run(tmp1, tmp2);
            i2s_buf.ping_pong[idx].data_ready = 0;
            idx = ((idx + 1) % USE_BUF_NUM);
        }
        if (no_data_cnt > 10000) {
            printf("no data input\n");
        }
        OS_MsDelay(1);
    }
FREE:
    i2s_buf_deinit(&i2s_buf);
    speex_deinit();
    vad_deinit();

    OS_EnterCritical();
    printf("\n==exit echo record==\n");
    OS_ExitCritical();
 
    OS_TaskDelete(NULL);
}

void echo_player(void *param)
{
    char name[256], path[256];
    int echo_en = 0;
    static int change = 0;
    OS_MsDelay(1000);
    printf("\n==enter echo player==\n");    

    //REG32(0xc0000590)  = 0xffffffff;
    //OS_TaskCreate(guiTask, "gui_init", 512, NULL, ( OS_TASK_MIDDLE_PRIO ), NULL);

    adc_btn_init(btns ,USER_BUTTON_MAX, ADC_EXT_VOLTAGE_GPIO_GPIO02, kws_adc_button_callback);

    while(sg_tx_use[0] == 1) {

        if(echo_en == 0) {
            codec_init();
#if(DEMO_TYPE==2)
            drv_i2s_init_ex(0, mode_master, SampleRate_16000HZ, Resolution_16bit);
            drv_i2s_loopback_start_ex(0, 1);
            drv_i2s_loopback_stop_ex(0);
#endif
            OS_TaskCreate(echo_record, "echo record", 900, NULL, OS_TASK_HIGH_PRIO, NULL);
            echo_en =1;
        }
        while((player_en == 0) || (have_sd == 0)) {
            OS_MsDelay(10);
            if(sg_tx_use[0] == 0)
                goto EXIT;
        }

        g_mp3_fsal_player_stop = 0;
        g_mp3_fsal_player_exit = 0;
        struct _args *cmd_args = (struct _args *)OS_MemAlloc(sizeof(struct _args));
        strcpy(cmd_args->argv[0], "start_mp3");
        memset(path, 0, 256);
        strcpy(path,"/");
        music_cnt = 0;
        get_sdc_mp3_name(now_music, path, name);
        strcpy(cmd_args->argv[1], name);
        strcpy(cmd_args->argv[2], "0");
        strcpy(cmd_args->argv[3], "1");
        strcpy(cmd_args->argv[4], "0");
        printf("play[%d]: %s (%d)\n",now_music, name);
        //terminal_add(name);
        //terminal_add("\n");
        OS_TaskCreate(helix_fsal_player, "helix", 1024*2, cmd_args, OS_TASK_MIDDLE_PRIO, NULL);

        while(g_mp3_fsal_player_stop == 0) {
            OS_MsDelay(1);
        }

        printf("==== play music finish ====\n");

        if(adjust_music == 0)
            now_music++;
        else if(adjust_music < 0) {
            adjust_music = adjust_music % total_music;
            now_music = now_music + adjust_music;
            if(now_music <= 0)
                now_music = total_music;
        } else {
            adjust_music = adjust_music % total_music;
            now_music = now_music + adjust_music;
            if(now_music > total_music)
                now_music = 1;
        }
        adjust_music = 0;
        OS_MsDelay(500);
    }

EXIT:
    sg_tx_use[0] = 0;
    sg_rx_use[1] = 0;
    OS_EnterCritical();
    printf("\n==exit echo player==\n");
    OS_ExitCritical();
    alg_exit = 1;
    rb_abort(aec_rb, 1);
    rb_unint(aec_rb);

    OS_TaskDelete(NULL);
}

