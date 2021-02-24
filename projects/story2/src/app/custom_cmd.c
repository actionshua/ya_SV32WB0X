
#include <stdio.h>
#include <string.h>
#include "soc_types.h"
#include "soc_defs.h"
#include "osal.h"

#include "cli.h"
#include "error.h"

#include <lowpower.h>
#include <logger.h>
#include <drv_i2s.h>
#include <hal_i2s.h>
#if(CHIP_ID!=6006)
#include <drv_pdm.h>
#endif
#include <drv_i2cmst.h>
#include <bsp.h>
#include "lwip/sockets.h"
#include "wificonf.h"
#include "wifi_api.h"
#include "toolbox.h"
#include "ieee80211_mgmt.h"
#include "drv_hsuart.h"
#include "hal_dmac.h"
#include  "codec_common.h"
#ifdef ACOUSTIC_EN
#include "speexdsp/include/speex/speex_echo.h"
#include "speexdsp/include/speex/speex_preprocess.h"
#include "webrtc/common_audio/vad/include/webrtc_vad.h"
#include "webrtc/modules/audio_processing/ns/include/noise_suppression_x.h"
#include "webrtc/modules/audio_processing/agc/include/gain_control.h"
#include "webrtc/modules/audio_processing/agc/analog_agc.h"
#include "webrtc/modules/audio_processing/agc/digital_agc.h"
#include "../ringbuf/ringbuf.h"
#endif
#if(SETTING_MP3_ENCODER == 1)
#include "layer3.h"
#endif
#define CMD_TAG        LOG_TAG_CMD
#define CMD_LOG_E(format, ...) log_e(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_W(format, ...) log_w(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_I(format, ...) log_i(CMD_TAG, "[%s] Line:%d, " format, __func__, __LINE__,##__VA_ARGS__)
#define CMD_LOG_D(format, ...) log_d(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_V(format, ...) log_v(CMD_TAG, format, ##__VA_ARGS__)

struct _args {
    char args;
    char argv[10][256];
};

#ifdef ACOUSTIC_EN
SpeexEchoState *st;
SpeexPreprocessState *den;
void *aechandle = NULL;
void *agcHandles = NULL;
NsxHandle *nsxHandles = NULL;
VadInst* vadhandle = NULL;
struct RingBuf *aec_rb = NULL;
struct RingBuf *ns_rb = NULL;
struct RingBuf *agc_rb = NULL;
struct RingBuf *vad_rb = NULL;
static int alg_exit = 0;
static int record_type_back = 0;
static int alg_type_back = 0;
static int socket_fd_back = 0;
#endif

extern void helix_fsal_player(void *param);
extern int g_mp3_fsal_player_stop;
static int sg_tx_use[2] = {0,0};
static int sg_rx_use[2] = {0,0};
static SSV_DIR *sg_cli_folder;
static SSV_FILE rec_file;
#if(SETTING_MP3_ENCODER == 1)
shine_config_t config;
shine_t s;
#endif
static int sg_sin_1k_48000_wave[] = {
        #include "sample_1k_48000.h"
};

static int sg_sin_1k_44100_wave[] = {
        #include "sample_1k_44100.h"
};

static int sg_sin_1k_8000_16b_wave[] = {
        #include "1k_tone_8khz_sign_16bit_mono.h"
};

static int sg_sin_1k_8000_24b_wave[] = {
        #include "1k_tone_8khz_sign_24bit_mono.h"
};

static int sg_sin_1k_8000_8b_wave[] = {
        #include "1k_tone_8khz_unsign_8bit_mono.h"
};

static int sg_sin_1k_16000_16b_wave[] = {
        #include "1k_tone_16khz_sign_16bit_mono.h"
};

static int sg_sin_1k_16000_16b_wave2[] = {
        #include "1k_tone_16khz_sign_16bit_mono2.h"
};
static int sg_sin_1k_16000_24b_wave[] = {
        #include "1k_tone_16khz_sign_24bit_mono.h"
};

static int sg_sin_1k_16000_8b_wave[] = {
        #include "1k_tone_16khz_unsign_8bit_mono.h"
};

static int sg_sin_1k_48000_16b_wave[] = {
        #include "1k_tone_48khz_sign_16bit_mono.h"
};

static int sg_sin_1k_48000_24b_wave[] = {
        #include "1k_tone_48khz_sign_24bit_mono.h"
};

static int sg_sin_1k_48000_8b_wave[] = {
        #include "1k_tone_48khz_unsign_8bit_mono.h"
};

static int sg_sin_1k_22050_16b_wave[] = {
        #include "1k_tone_22.05khz_sign_16bit_mono.h"
};

static int sg_sin_1k_22050_24b_wave[] = {
        #include "1k_tone_22.05khz_sign_24bit_mono.h"
};

static int sg_sin_1k_22050_8b_wave[] = {
        #include "1k_tone_22.05khz_unsign_8bit_mono.h"
};

static int sg_sin_1k_44100_16b_wave[] = {
        #include "1k_tone_44.1khz_sign_16bit_mono.h"
};

static int sg_sin_1k_44100_24b_wave[] = {
        #include "1k_tone_44.1khz_sign_24bit_mono.h"
};

static int sg_sin_1k_44100_8b_wave[] = {
        #include "1k_tone_44.1khz_unsign_8bit_mono.h"
};

#define RND_MAX_SIZE        (1024)
#define RND_FNAME_MAX_LEN   (8)
#define USE_BUF_NUM   36
#define RECORD_FILE_NAME "/sdcard/record.pcm"
#define CHANNELS        2
#define RECORD_SAMPLE    576
#define BYTES_WIDTH    sizeof(short)
#define RECORD_LEN    RECORD_SAMPLE*BYTES_WIDTH*CHANNELS
#define SAMPLE_RATE     SampleRate_16000HZ
#define TAIL RECORD_SAMPLE*20

int check_start_input_parameter(int module, int data_mode, int pdm_en, int rate)
{
#if(CHIP_ID==6006)
    if(module == DRV_I2S_1) {
        printf("%d only support i2s1 port\n", CHIP_ID);//6006 only support i2s1
        return -1;
    }
    if(data_mode == DMAC_MODE) {
        printf("%d only support mcu mode, not support dma mode\n", CHIP_ID);//6006 only support mcu ode
        return -1;
    }
    if(pdm_en == 1) {
        printf("%d only support i2s, not support pdm\n", CHIP_ID);//6006 only support i2s
        return -1;
    }
#endif
    if(rate != 0 && rate != 8000 && rate != 16000 && rate != 22050 &&
        rate != 44100 && rate != 48000) {
        printf("not support rate: %d\n", rate);
        return -1;
    }
    return 0;
}

int check_stop_input_parameter(int module)
{
#if(CHIP_ID==6006)
    if(module == DRV_I2S_1) {
        printf("%d only support i2s1 port\n", CHIP_ID);//6006 only support i2s1
        return -1;
    }
#endif
    return 0;
}

static int send_data(int record_type, int socket_fd, uint8_t *local_buf,int local_len)
{
    int status = 0;
    int written;
    unsigned char *data;
    uint32_t mh_total_time_start, mh_total_time_end;
#if(SETTING_MP3_ENCODER == 1)
    data = shine_encode_buffer_interleaved(s, (int16_t *)local_buf, &written);
    local_buf = data;
    local_len = written;
#endif
    if(record_type == 0) {
        int sent = 0;
        int send_timeout = 10000;
        do {
            if ((sent = send(socket_fd, local_buf, ((local_len>1024)?1024:local_len), 0)) > 0) {
                local_len -= sent;
                local_buf += sent;
            } else {
                CMD_LOG_I("socket issue\n");
                return -1;
            }
        } while((local_len != 0) && (--send_timeout));
        if (send_timeout) {
            //CMD_LOG_I("send buffer success!\n");
        } else {
            CMD_LOG_I("send buffer timeout!\n");
            return -1;
        }
    } else if(record_type == 1) {
        drv_hsuart_write_fifo (local_buf, local_len, 0x1);
    } else if(record_type == 2) {
        status = FS_write(fs_handle, rec_file, local_buf, local_len);
        if ((status = FS_ferrno(rec_file)) != 0) {
            printf("file write fail: res=%d\n", status);
            FS_close(fs_handle, rec_file);
            return -1;
        }
    } else {
        //printf("record empty send\n");
    }
    return 0;
}

#ifdef ACOUSTIC_EN
void vad_task(void *param)
{
    int status = 0, i = 0;
    uint8_t tmp[(RECORD_SAMPLE*BYTES_WIDTH*2)];
    int16_t *check =(int16_t *)tmp;

    vad_rb = rb_init(4*RECORD_LEN);
    WebRtcVad_Create(&vadhandle);
    WebRtcVad_Init(vadhandle);
    WebRtcVad_set_mode(vadhandle, 1);

    while(alg_exit == 0) {
        rb_read(vad_rb, (uint8_t *)tmp, (RECORD_SAMPLE*BYTES_WIDTH*2), portMAX_DELAY, 0);
        status = WebRtcVad_Process(vadhandle, SAMPLE_RATE, check, (RECORD_SAMPLE*2));
        if(status == 1) {
            send_data(record_type_back, socket_fd_back, (uint8_t *)check, (RECORD_SAMPLE*BYTES_WIDTH*2));
        }
    }
    WebRtcVad_Free(vadhandle);
    vadhandle = NULL;
    printf("vad exit\n");
    OS_TaskDelete(NULL);
    while(1);
}

void agc_task(void *param)
{
    int16_t tmp[(RECORD_SAMPLE*BYTES_WIDTH)];
    int16_t tmp1[(RECORD_SAMPLE*BYTES_WIDTH)];
    int32_t minLevel = 0;
    int32_t maxLevel = 255;
    int sampleRate = SAMPLE_RATE;
    WebRtcAgc_config_t AgcConfig;

    agc_rb = rb_init(4*RECORD_LEN);
    AgcConfig.compressionGaindB = 15;
    AgcConfig.limiterEnable = 1;
    AgcConfig.targetLevelDbfs = -3;
    WebRtcAgc_Create(&agcHandles);
    WebRtcAgc_Init(agcHandles, minLevel, maxLevel, 3, sampleRate);
    WebRtcAgc_set_config(agcHandles, AgcConfig);
    while(alg_exit == 0) {
        rb_read(agc_rb, (uint8_t *)tmp, (RECORD_SAMPLE*BYTES_WIDTH), portMAX_DELAY, 0);
        uint8_t saturationWarning;
        int32_t inMicLevel = 0;
        int32_t outMicLevel = 0;
        WebRtcAgc_Process(agcHandles, (short *)tmp , NULL, RECORD_SAMPLE, (short *)tmp1, NULL, inMicLevel,&outMicLevel, 0, &saturationWarning);
        if((alg_type_back & 0x8) == 0x8) {
            rb_write(vad_rb, (uint8_t *)tmp1, (RECORD_SAMPLE*BYTES_WIDTH), portMAX_DELAY, 0);
        } else {
            send_data(record_type_back, socket_fd_back, (uint8_t *)tmp1, (RECORD_SAMPLE*BYTES_WIDTH));
        }
    }

    WebRtcAgc_Free(agcHandles);
    agcHandles = NULL;
    printf("agc exit\n");
    OS_TaskDelete(NULL);
    while(1);
}

void ns_task(void *param)
{
    int status = 0;
    int16_t tmp[(RECORD_SAMPLE*BYTES_WIDTH)];
    int16_t tmp1[(RECORD_SAMPLE*BYTES_WIDTH)];

    ns_rb = rb_init(48*RECORD_LEN);
    WebRtcNsx_Create(&nsxHandles);
    WebRtcNsx_Init(nsxHandles, SAMPLE_RATE);
    WebRtcNsx_set_policy(nsxHandles, 1);

    while(alg_exit == 0) {
        rb_read(ns_rb, (uint8_t *)tmp, (RECORD_SAMPLE*BYTES_WIDTH), portMAX_DELAY, 0);
        WebRtcNsx_Process(nsxHandles, (short *)tmp, NULL, (short *)tmp1, NULL);
        if((alg_type_back & 0x4) == 0x4) {
            rb_write(agc_rb, (uint8_t *)tmp1, (RECORD_SAMPLE*BYTES_WIDTH), portMAX_DELAY, 0);
        } else if((alg_type_back & 0x8) == 0x8) {
            rb_write(vad_rb, (uint8_t *)tmp1, (RECORD_SAMPLE*BYTES_WIDTH), portMAX_DELAY, 0);
        } else {
            send_data(record_type_back, socket_fd_back, (uint8_t *)tmp1, (RECORD_SAMPLE*BYTES_WIDTH));
        }
    }

    WebRtcNsx_Free(nsxHandles);
    nsxHandles = NULL;
    printf("ns exit\n");
    OS_TaskDelete(NULL);
    while(1);
}

void aec_task(void *param)
{
    static unsigned  short cnt = 0;
    int i = 0, status = 1;
    int16_t buf[RECORD_LEN];
    int16_t tmp1[RECORD_SAMPLE];
    int16_t tmp2[RECORD_SAMPLE];
    int16_t tmp3[RECORD_SAMPLE];
    int sampleRate = SAMPLE_RATE;

    aec_rb = rb_init(62*RECORD_LEN);

    st = speex_echo_state_init(RECORD_SAMPLE, TAIL);
    den = speex_preprocess_state_init(RECORD_SAMPLE, sampleRate);
    speex_echo_ctl(st, SPEEX_ECHO_SET_SAMPLING_RATE, &sampleRate);
    speex_preprocess_ctl(den, SPEEX_PREPROCESS_SET_ECHO_STATE, st);

    while(alg_exit == 0) {
        rb_read(aec_rb, (uint8_t *)buf, RECORD_LEN, portMAX_DELAY, 0);
        for(i = 0; i < RECORD_SAMPLE; i++) {
            *(tmp2 + i) = *(buf + (i*CHANNELS));
            *(tmp1 + i) = *(buf + ((i*CHANNELS) + 1));
        }
        speex_echo_cancellation(st, tmp1, tmp2, buf);
        speex_preprocess_run(den, buf);

        if((alg_type_back & 0x2) == 0x2) {
            rb_write(ns_rb, (uint8_t *)buf, (RECORD_SAMPLE*BYTES_WIDTH), portMAX_DELAY, 0);
        } else if((alg_type_back & 0x4) == 0x4) {
            rb_write(agc_rb, (uint8_t *)buf, (RECORD_SAMPLE*BYTES_WIDTH), portMAX_DELAY, 0);
        } else if((alg_type_back & 0x8) == 0x8) {
            rb_write(vad_rb, (uint8_t *)buf, (RECORD_SAMPLE*BYTES_WIDTH), portMAX_DELAY, 0);
        } else {
            send_data(record_type_back, socket_fd_back, (uint8_t *)buf, (RECORD_SAMPLE*BYTES_WIDTH));
        }
    }
    speex_echo_state_destroy(st);
    speex_preprocess_state_destroy(den);

    printf("aec exit\n");
    OS_TaskDelete(NULL);
    while(1);
}

int audio_alg_close(int alg_type)
{
    if((alg_type & 0x1) != 0x1)
        return 0;

    alg_exit = 1;
    if((alg_type & 0x1) == 1) {
        rb_abort(aec_rb, 1);
        rb_unint(aec_rb);
    }
    if((alg_type & 0x2) == 2) {
        rb_abort(ns_rb, 1);
        rb_unint(ns_rb);
    }
    if((alg_type & 0x4) == 4) {
        rb_abort(agc_rb, 1);
        rb_unint(agc_rb);
    }
    if((alg_type & 0x8) == 8) {
        rb_abort(vad_rb, 1);
        rb_unint(vad_rb);
    }
    return 0;
}

int audio_alg_process(int alg_type, uint8_t *local_buf,int local_len)
{
    int status = 0;
    if((alg_type & 0x1) != 0x1) {
        status = send_data(record_type_back, socket_fd_back, local_buf, local_len);
        return status;
    }
    rb_write(aec_rb, (uint8_t *)local_buf, local_len, portMAX_DELAY, 0);

    return 0;
}

int audio_alg_open(int alg_type)
{
    if((alg_type & 0x1) != 0x1)
        return 0;

    alg_exit = 0;

    if((alg_type & 0x1) == 0x1)
        OS_TaskCreate(aec_task, "aec", 1100, NULL, OS_TASK_HIGH_PRIO, NULL);
    if((alg_type & 0x2) == 0x2)
        OS_TaskCreate(ns_task, "ns", 2900, NULL, OS_TASK_HIGH_PRIO, NULL);
    if((alg_type & 0x4) == 0x4)
        OS_TaskCreate(agc_task, "agc", 600, NULL, OS_TASK_LOW_PRIO, NULL);
    if((alg_type & 0x8) == 0x8)
        OS_TaskCreate(vad_task, "vad", 680, NULL, OS_TASK_HIGH_PRIO, NULL);

    return 0;
}
#endif
#if(SETTING_MP3_ENCODER == 1)
/* Use these default settings, can be overridden */
static void set_defaults(shine_config_t *config)
{
  shine_set_config_mpeg_defaults(&config->mpeg);
}
#endif
int recoord_close(int record_type, int alg_type, int socket_fd)
{
#ifdef ACOUSTIC_EN
    audio_alg_close(alg_type);
#endif
#if(SETTING_MP3_ENCODER == 1)
    /* Close encoder. */
    shine_close(s);
#endif
    if(record_type == 0) {
        close(socket_fd);
    } else if(record_type == 1) {
        drv_hsuart_deinit();
    } else if(record_type == 2) {
        FS_close(fs_handle, rec_file);
    } else {
        printf("record empty close\n");
    }
    return 0;
}

int recoord_send(int record_type, int alg_type, int socket_fd, uint8_t *local_buf,int local_len)
{
    int status = 0;
#ifdef ACOUSTIC_EN
    status = audio_alg_process(alg_type, local_buf, local_len);
#else
    status = send_data(record_type, socket_fd, local_buf, local_len);
#endif
    return status;
}

int recoord_connect(int record_type, int alg_type, char *addr, char *port)
{
    int fd = 0;
    int samples_per_pass;

    if(record_type == 0) {
        struct sockaddr_in sa;
        int lport = strtol(port, NULL, 10);
        
        fd = socket(PF_INET, SOCK_STREAM, 0);
        if ( fd < 0 ) {
            CMD_LOG_I("socket call failed");
            return -1;
        }
        memset(&sa, 0, sizeof(struct sockaddr_in));
        sa.sin_family = AF_INET;
        sa.sin_addr.s_addr = inet_addr(addr);
        sa.sin_port = htons(lport);

        if(connect(fd,(struct sockaddr*)&sa,sizeof(struct sockaddr_in)) < 0)
        {
            CMD_LOG_I("connect failed \n");
            close(fd);
            return -1;
        }
    } else if(record_type == 1) {
        drv_hsuart_init ();
        drv_hsuart_sw_rst ();
        drv_hsuart_set_fifo (0x2);
        drv_hsuart_set_format (4000000, 3, 0, 0);
    } else if(record_type == 2) {
        FS_remove(fs_handle, RECORD_FILE_NAME);
        rec_file = FS_open(fs_handle, RECORD_FILE_NAME, SPIFFS_O_CREAT | SPIFFS_RDWR, 0);
    } else {
        printf("record empty connect\n");
    }
#ifdef ACOUSTIC_EN
    audio_alg_open(alg_type);
    alg_type_back = alg_type;
    record_type_back = record_type;
    socket_fd_back = fd;
#endif
#if(SETTING_MP3_ENCODER == 1)
    set_defaults(&config);
    config.wave.channels = CHANNELS;
    config.wave.samplerate = SAMPLE_RATE;
    /* See if samplerate and bitrate are valid */
    if (shine_check_config(config.wave.samplerate, config.mpeg.bitr) < 0) {
        printf("Unsupported samplerate/bitrate configuration.");
        return -1;
    }
    config.mpeg.mode = STEREO;
    config.mpeg.bitr = 32;
    /* Initiate encoder */
    s = shine_initialise(&config);
    samples_per_pass = shine_samples_per_pass(s);
    printf("samples_per_pass: %d\n", samples_per_pass);
    if(samples_per_pass != RECORD_SAMPLE) {
        printf("mp3 per sample not match\n");
        return -1;
    }
#endif
    return fd;
}

void i2s_buf_deinit(i2s_buffer *i2s_buf)
{
    int cnt = 0;
    for(cnt = 0; cnt < USE_BUF_NUM; cnt++) {
        if(i2s_buf->ping_pong[cnt].buffer != NULL) {
            OS_MemFree(i2s_buf->ping_pong[cnt].buffer);
            i2s_buf->ping_pong[cnt].buffer = NULL;
        }
    }
}

int i2s_buf_init(i2s_buffer *i2s_buf, int buf_len)
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

void start_mp3(void *param) 
{
    struct _args *args = (struct _args *)param;
    int module = strtol(args->argv[2], NULL, 10);
    int data_mode = strtol(args->argv[3], NULL, 10);
    int pdm_en = strtol(args->argv[4], NULL, 10);

    if(check_start_input_parameter(module, data_mode, pdm_en, 0) < 0)
        goto EXIT;

    OS_TaskCreate(helix_fsal_player, "helix", 1024*3+2048, args, OS_TASK_HIGH_PRIO, NULL);

    while(sg_tx_use[module] && !g_mp3_fsal_player_stop ) {
        OS_MsDelay(1);
    }

EXIT:
    sg_tx_use[module] = 0;
    OS_TaskDelete(NULL);
}

void start_sin(void *param)
{
    struct _args *args = (struct _args *)param;
    int module = strtol(args->argv[1], NULL, 10);
    int data_mode = strtol(args->argv[2], NULL, 10);
    int pdm_en = strtol(args->argv[3], NULL, 10);
    int rate = strtol(args->argv[4], NULL, 10);
    OS_MemFree(param);

    if(check_start_input_parameter(module, data_mode, pdm_en, rate) < 0)
        goto EXIT;

    short *outBuf;
    int sin_idx = 0;
    int buf_len = RECORD_LEN;
    int pingpong_idx = 0;
    int one_time = 0;
    i2s_buffer i2s_buf;

    if(pdm_en == 0) {
        codec_init();
    }
    drv_i2s_init_ex(module, mode_master, rate, Resolution_16bit);
#if(CHIP_ID!=6006)
    if(pdm_en == 1) {
        drv_pdm_init(module);
    }
#endif
    if(i2s_buf_init(&i2s_buf, buf_len) < 0)
        goto FREE;
    drv_i2s_set_buffer_ex(module, NULL, 0, &i2s_buf, USE_BUF_NUM);

    while(sg_tx_use[module]) {
        struct _i2s_buffer_st *buf = &(i2s_buf.ping_pong[pingpong_idx]);
        if (!buf->data_ready) {
            outBuf = buf->buffer;
            int i;
            for (i = 0; i < buf_len/(2 * sizeof(short)); i++) {
                outBuf[i*2] = sg_sin_1k_48000_16b_wave[sin_idx];
                outBuf[i*2+1] = sg_sin_1k_48000_16b_wave[sin_idx];
                sin_idx++;
                if (sin_idx == (sizeof(sg_sin_1k_48000_16b_wave)/sizeof(int))) {
                    sin_idx = 0;
                }
            }
            buf->buffer_idx = 0;
            buf->buffer_len = buf_len;
            buf->data_ready = 1;
        }
        if (!one_time) {
            one_time = !one_time;
            drv_i2s_tx_start_ex(module, data_mode);
#if(CHIP_ID!=6006)
            if(pdm_en == 1) {
                drv_pdm_tx_enable(module, (float)(rate/1000), PDM_TX_Bit_Depth_16, 0, 0);
            }
#endif
        }
        pingpong_idx = ((pingpong_idx + 1) % USE_BUF_NUM);
        while((i2s_buf.ping_pong[pingpong_idx].data_ready) && (sg_tx_use[module])) {
            OS_MsDelay(1);
        }
    }
#if(CHIP_ID!=6006)
    if(pdm_en == 1)
        drv_pdm_tx_disable(module);
#endif

FREE:
    i2s_buf_deinit(&i2s_buf);
EXIT:
    sg_tx_use[module] = 0;
    OS_TaskDelete(NULL);
}

void start_record(void *param) {
    struct _args *args = (struct _args *)param;
    int record_type = strtol(args->argv[1], NULL, 10);
    int module = strtol(args->argv[4], NULL, 10);
    int data_mode = strtol(args->argv[5], NULL, 10);
    int pdm_en = strtol(args->argv[6], NULL, 10);
    int alg_type = strtol(args->argv[7], NULL, 10);
    int downsample = strtol(args->argv[8], NULL, 10);
    int rate = strtol(args->argv[9], NULL, 10);
    if(check_start_input_parameter(module, data_mode, pdm_en, rate) < 0)
        goto EXIT;

    int socket_fd = recoord_connect(record_type, alg_type, args->argv[2], args->argv[3]);
    if(socket_fd< 0) {
        OS_MemFree(param);
        goto EXIT;
    }
    OS_MemFree(param);

    int idx = 0;
    int no_data_cnt = 0;
    int buf_len = RECORD_LEN;
    i2s_buffer i2s_buf;

    if(pdm_en == 0) {
        codec_init();
    }

    drv_i2s_init_ex(module, mode_master, rate, Resolution_16bit);
#if(CHIP_ID!=6006)
    if(pdm_en == 1) {
        drv_pdm_init(module);
    }
#endif
    if(i2s_buf_init(&i2s_buf, buf_len) < 0)
        goto FREE;
    drv_i2s_set_buffer_ex(module, &i2s_buf, USE_BUF_NUM, NULL, 0);
    drv_i2s_rx_start_ex(module, downsample, data_mode);
#if(CHIP_ID!=6006)
    if(pdm_en == 1) {
        drv_pdm_rx_enable(module, rate, PDM_RX_STEREO);
    }
#endif
    while(sg_rx_use[module]) {
        no_data_cnt++;
        while(i2s_buf.ping_pong[idx].data_ready && (sg_rx_use[module])) {
            no_data_cnt = 0;
            struct _i2s_buffer_st *buf = &i2s_buf.ping_pong[idx];
            uint8_t *local_buf = (uint8_t *)buf->buffer;
            int local_len = buf->buffer_len;
            if(recoord_send(record_type, alg_type, socket_fd, local_buf, local_len) < 0)
                sg_rx_use[module] = 0;
            i2s_buf.ping_pong[idx].data_ready = 0;
            idx = ((idx + 1) % USE_BUF_NUM);
        }
        if (no_data_cnt > 10000) {
            CMD_LOG_I("no data input\n");
        }
        OS_MsDelay(1);
    }
    recoord_close(record_type, alg_type, socket_fd);
#if(CHIP_ID!=6006)
    if(pdm_en == 1) {
        drv_pdm_rx_disable(module);
    }
#endif
FREE:
    i2s_buf_deinit(&i2s_buf);

EXIT:
    sg_rx_use[module] = 0;
    OS_TaskDelete(NULL);
}
    
void start_loopback(void *param) 
{
    struct _args *args = (struct _args *)param;
    int module = strtol(args->argv[1], NULL, 10);
    int data_mode = strtol(args->argv[2], NULL, 10);
    int pdm_en = strtol(args->argv[3], NULL, 10);
    int rate = strtol(args->argv[4], NULL, 10);
    OS_MemFree(param);

    if(check_start_input_parameter(module, data_mode, pdm_en, rate) < 0)
        goto EXIT;

    if(pdm_en == 0) {
        codec_init();
    }

    drv_i2s_init_ex(module, mode_master, rate, Resolution_16bit);
#if(CHIP_ID!=6006)
    if(pdm_en == 1) {
        drv_pdm_init(module);
        drv_pdm_rx_enable(module,rate, PDM_RX_STEREO);
        drv_pdm_tx_enable(module,(float)(rate/1000), PDM_TX_Bit_Depth_16, PDM_TX_STEREO, 0);
    }
#endif

    drv_i2s_loopback_start_ex(module, data_mode);
    while(sg_tx_use[module] && sg_rx_use[module]) {
        OS_MsDelay(1);
    }

EXIT:
#if(CHIP_ID!=6006)
    if(pdm_en == 1) {
        drv_pdm_rx_disable(module);
        drv_pdm_tx_disable(module);
    }
#endif
    sg_rx_use[module] = 0;
    sg_tx_use[module] = 0;
    OS_TaskDelete(NULL);
}

void start_scan_cbfunc()
{
    u8 i;

    CMD_LOG_I("\nCount:%d\n", getAvailableIndex());
    for(i = 0; i < getAvailableIndex(); i++)
    {
        CMD_LOG_I("%2d - name:%32s, rssi:-%2d CH:%2d mac:%02x-%02x-%02x-%02x-%02x-%02x\n", i, ap_list[i].name, ap_list[i].rssi, ap_list[i].channel
                , ap_list[i].mac[0], ap_list[i].mac[1], ap_list[i].mac[2], ap_list[i].mac[3], ap_list[i].mac[4], ap_list[i].mac[5]);
    }
    CMD_LOG_I("end\n");
}

void start_wificbfunc(WIFI_RSP *msg)
{
    uint8_t dhcpen;
    u8 mac[6];
    uip_ipaddr_t ipaddr, submask, gateway, dnsserver;

    if(msg->wifistatus == 1)
    {
        CMD_LOG_I("connect OK\n");
        if(msg->id == 0)
            get_if_config_2("et0", &dhcpen, (u32*)&ipaddr, (u32*)&submask, (u32*)&gateway, (u32*)&dnsserver, mac, 6);
        else
            get_if_config_2("et1", &dhcpen, (u32*)&ipaddr, (u32*)&submask, (u32*)&gateway, (u32*)&dnsserver, mac, 6);
        CMD_LOG_I("STA%d:\n", msg->id);
        CMD_LOG_I("mac addr        - %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        CMD_LOG_I("ip addr         - %d.%d.%d.%d\n", ipaddr.u8[0], ipaddr.u8[1], ipaddr.u8[2], ipaddr.u8[3]);
        CMD_LOG_I("netmask         - %d.%d.%d.%d\n", submask.u8[0], submask.u8[1], submask.u8[2], submask.u8[3]);
        CMD_LOG_I("default gateway - %d.%d.%d.%d\n", gateway.u8[0], gateway.u8[1], gateway.u8[2], gateway.u8[3]);
        CMD_LOG_I("DNS server      - %d.%d.%d.%d\n", dnsserver.u8[0], dnsserver.u8[1], dnsserver.u8[2], dnsserver.u8[3]);
    }
    else
    {
        CMD_LOG_I("disconnect OK\n");
    }
}

int Cmd_meminfo(s32 argc, char *argv[])
{
    CMD_LOG_I("\n");
    OS_MemInfo();
    return ERROR_SUCCESS;
}

int Cmd_sysinfo(s32 argc, char *argv[])
{
    CMD_LOG_I("\n");
    OS_SysInfo();
    return ERROR_SUCCESS;
}

int Cmd_fsal_fsa(s32 argc, char *argv[])
{
    CMD_LOG_I("fs all list\n");
    FS_list(fs_handle);
    return 0;
}

int Cmd_fsal_rm(s32 argc, char *argv[])
{
    const int ARG_FILE = 1;
    if (argc < 2) {
        CMD_LOG_I("please assign folder.");
        return 0;
    }
    CMD_LOG_I("fs remove file: %s\n", argv[ARG_FILE]);
    if (!FS_remove(fs_handle, argv[ARG_FILE])) {
        CMD_LOG_I("fs removed file: %s\n", argv[ARG_FILE]);
        return 0;
    }
    return 0;
}

int Cmd_fsal_cat(s32 argc, char *argv[])
{
    const int BUF_LEN = 256;
    const int ARG_FILE = 1;
    char buf[BUF_LEN];
    int cnt;
    if (argc < 2) {
        CMD_LOG_I("please assign folder.");
        return 0;
    }
    SSV_FILE f;
    CMD_LOG_I("fs cat file: %s\n", argv[ARG_FILE]);
    f = FS_open(fs_handle, argv[ARG_FILE], SPIFFS_RDWR, 0);
    do {
        cnt = FS_read(fs_handle, f, buf, BUF_LEN);
        if (cnt < 0) {
            CMD_LOG_I("dump error number: %d\n", cnt);
        }
        int i;
        for (i = 0; i < cnt; i++) {
            if ((i%16) == 0) {
                CMD_LOG_I("\n");
            }
            CMD_LOG_I("0x%X ", buf[i]);
        }
    } while (cnt > 0);

    FS_close(fs_handle, f);
    return 0;
}

int Cmd_start_mp3(s32 argc, char *argv[])
{
    if (argc != 5) {
        CMD_LOG_I("input parameters fail: ex: start_mp3=path,module,mode,pdm_en\n");
        return 0;
    }
    int module = strtol(argv[2], NULL, 10);
    if(sg_tx_use[module] == 1) {
        printf("tx: %d already use, need stop\n", module);
        return -1;
    }
    if(g_mp3_fsal_player_stop == 0) {
        printf("already run sin\n");
        return 0;
    }

    struct _args *cmd_args = (struct _args *)OS_MemAlloc(sizeof(struct _args));
    strcpy(cmd_args->argv[0], argv[0]);
    strcpy(cmd_args->argv[1], argv[1]);
    strcpy(cmd_args->argv[2], argv[2]);
    strcpy(cmd_args->argv[3], argv[3]);
    strcpy(cmd_args->argv[4], argv[4]);
    g_mp3_fsal_player_stop = 0;
    sg_tx_use[module] = 1;

    OS_TaskCreate(start_mp3, "mp3 task", 512, cmd_args, OS_TASK_LOW_PRIO, NULL);
    return 0;
}

int Cmd_stop_mp3(s32 argc, char *argv[])
{
    CMD_LOG_I("stop mp3!");
    g_mp3_fsal_player_stop = 1;
    return 0;
}

int Cmd_start_sin(s32 argc, char *argv[])
{
    if (argc != 5) {
        CMD_LOG_I("input parameters fail: ex: start_sin=module,mode,pdm_en,rate\n");
        return 0;
    }

    int module = strtol(argv[1], NULL, 10);
    if(sg_tx_use[module] == 1) {
        printf("tx: %d already use, need stop\n", module);
        return -1;
    }
    struct _args *cmd_args = (struct _args *)OS_MemAlloc(sizeof(struct _args));
    strcpy(cmd_args->argv[0], argv[0]);
    strcpy(cmd_args->argv[1], argv[1]);
    strcpy(cmd_args->argv[2], argv[2]);
    strcpy(cmd_args->argv[3], argv[3]);
    strcpy(cmd_args->argv[4], argv[4]);
    sg_tx_use[module] = 1;

    OS_TaskCreate(start_sin, "sin", 512, cmd_args, OS_TASK_LOW_PRIO, NULL);
    return 0;
}

int Cmd_stop_sin(s32 argc, char *argv[])
{
    int status = 0;
    if (argc != 2) {
        CMD_LOG_I("input parameters fail: ex: stopt_sin=module\n");
        return 0;
    }

    int module = strtol(argv[1], NULL, 10);
    if(check_stop_input_parameter(module) < 0)
        return -1;
    
    status = drv_i2s_tx_stop_ex(module);
    if(status == DRV_I2S_STATUS_OK) {
        CMD_LOG_I("stop sin!");
        sg_tx_use[module] = 0;
    }
    return 0;
}

int Cmd_start_record(s32 argc, char *argv[])
{
    if (argc !=10) {
        CMD_LOG_I("input parameters fail: ex: start_record=record_type, ip,port,module,mode,pdm_en,acoustic,downsample,rate\n");
        return -1;
    }
    int module = strtol(argv[4], NULL, 10);

    if(sg_rx_use[module] == 1) {
        printf("rx: %d already use, need stop\n", module);
        return -1;
    }
    struct _args *cmd_args = (struct _args *)OS_MemAlloc(sizeof(struct _args));
    strcpy(cmd_args->argv[0], argv[0]);
    strcpy(cmd_args->argv[1], argv[1]);
    strcpy(cmd_args->argv[2], argv[2]);
    strcpy(cmd_args->argv[3], argv[3]);
    strcpy(cmd_args->argv[4], argv[4]);
    strcpy(cmd_args->argv[5], argv[5]);
    strcpy(cmd_args->argv[6], argv[6]);
    strcpy(cmd_args->argv[7], argv[7]);    
    strcpy(cmd_args->argv[8], argv[8]);
    strcpy(cmd_args->argv[9], argv[9]);
    sg_rx_use[module] = 1;

    OS_TaskCreate(start_record, "recorder", 1024, cmd_args, OS_TASK_HIGH_PRIO, NULL);
    return 0;
}

int Cmd_stop_record(s32 argc, char *argv[])
{
    int status = 0;
    if (argc != 2) {
        CMD_LOG_I("input parameters fail: ex: stop_record=module\n");
        return 0;
    }

    int module = strtol(argv[1], NULL, 10);
    if(check_stop_input_parameter(module) < 0)
        return -1;

    status = drv_i2s_rx_stop_ex(module);
    if(status == DRV_I2S_STATUS_OK) {
        CMD_LOG_I("stop record!");
        sg_rx_use[module] = 0;
    }
    return 0;
}

int Cmd_start_loopback(s32 argc, char *argv[])
{
    if (argc != 5) {
        CMD_LOG_W("input parameters fail: ex: start_loopback=module,mode,pdm_en, rate\n");
        return -1;
    }
    int module = strtol(argv[1], NULL, 10);
    int pdm_en = strtol(argv[3], NULL, 10);

    if(module == 1 && pdm_en == 1) {
        CMD_LOG_W("pdm tx only have module0\n");
        return -1;
    }

    if(sg_tx_use[module] == 1) {
        printf("tx: %d already use, need stop\n", module);
        return -1;
    }

    if(sg_rx_use[module] == 1) {
        printf("rx: %d already use, need stop\n", module);
        return -1;
    }

    struct _args *cmd_args = (struct _args *)OS_MemAlloc(sizeof(struct _args));
    strcpy(cmd_args->argv[0], argv[0]);
    strcpy(cmd_args->argv[1], argv[1]);
    strcpy(cmd_args->argv[2], argv[2]);
    strcpy(cmd_args->argv[3], argv[3]);
    strcpy(cmd_args->argv[4], argv[4]);
    sg_tx_use[module] = 1;
    sg_rx_use[module] = 1;
    OS_TaskCreate(start_loopback, "loopback", 512, cmd_args, OS_TASK_LOW_PRIO, NULL);

    return 0;
}

int Cmd_stop_loopback(s32 argc, char *argv[])
{
    if (argc != 2) {
        CMD_LOG_W("input parameters fail: ex: stop_loopback=module\n");
        return -1;
    }
    int module = strtol(argv[1], NULL, 10);

    if(check_stop_input_parameter(module) < 0)
        return -1;

    CMD_LOG_I("stop loopback!");
    drv_i2s_loopback_stop_ex(module);

    sg_tx_use[module] = 0;
    sg_rx_use[module] = 0;

    return 0;
}

int Cmd_Scan(s32 argc, char *argv[])
{
    DUT_wifi_start(DUT_STA);
    if(scan_AP(start_scan_cbfunc))
        return ERROR_INVALID_PARAMETER;
    return ERROR_SUCCESS;
}

int Cmd_Connect(s32 argc, char *argv[])
{
    int ret;
    if (argc < 2)  {
        CMD_LOG_I("parameter error.\n");
        CMD_LOG_I("%s <ssid> [password]\n", argv[0]);
        return ERROR_INVALID_PARAMETER;
    }

    CMD_LOG_I("ssid = %s\n", argv[1]);
    if (argc > 1) {
        CMD_LOG_I("password = %s\n", argv[2]);
        ret = set_wifi_config((u8*)argv[1], strlen(argv[1]),  (u8*)argv[2], strlen(argv[2]), NULL, 0);
    } else {
        ret = set_wifi_config((u8*)argv[1], strlen(argv[1]), NULL, 0, NULL, 0);
    }
    wifi_connect(start_wificbfunc);
    return ERROR_SUCCESS;
}

#if (CHIP_ID==6020)
int Cmd_ob_volume(s32 argc, char *argv[])
{
    int vol = atoi(argv[1]);
    CMD_LOG_I("set volume: %d\n", vol);
    drv_pdm_tx_vol(DRV_PDM_1, vol);
    return 0;
}
#endif

#if (CHIP_ID==6020 && CHIP_SUB_ID !=0)
int Cmd_start_tone(s32 argc, char *argv[])
{
    if (argc != 2) {
        CMD_LOG_W("input parameters fail: ex: tone=tone_id\n");
        return -1;
    }
    if(sg_tx_use[0] == 1) {
        printf("tx0 already use, need stop\n");
        return -1;
    }
    if(sg_rx_use[0] == 1) {
        printf("rx0 already use, need stop\n");
        return -1;
    }

    int tone_id = strtol(argv[1], NULL, 10);
    if(tone_id < DRV_PDM_TX_01KTONE ||tone_id > DRV_PDM_TX_15KTONE) {
        CMD_LOG_W("input parameters tone_id fail: ex: tone=tone_id [1, 16]\n");
    } else {
        drv_pdm_tx_tonegen_enable(DRV_PDM_1, tone_id);
    }
    return 0;
}

int Cmd_stop_tone(s32 argc, char *argv[])
{
    drv_pdm_tx_tonegen_disable(DRV_PDM_1);
    return 0;
}
#endif

/* ---------------------- Registered CMDs to CMD Table ---------------------- */
const CLICmds gCustomCmdTable[] =
{
    { "meminfo",            Cmd_meminfo,        "meminfo"},
    { "sysinfo",            Cmd_sysinfo,        "sysinfo"},

    { "lsa",                Cmd_fsal_fsa,     "list all files"},
    { "rm",                 Cmd_fsal_rm,     "remove file"},
    { "cat",                Cmd_fsal_cat,     "show file"},
    { "start_mp3",          Cmd_start_mp3,     "decode mp3"},
    { "stop_mp3",           Cmd_stop_mp3,     "stop mp3"},
    { "start_sin",          Cmd_start_sin,     "play sin wave"},
    { "stop_sin",           Cmd_stop_sin,     "stop sin wave"},
    { "start_record",       Cmd_start_record,     "record to socket"},
    { "stop_record",        Cmd_stop_record,     "stop record to socket"},
    { "start_loopback",       Cmd_start_loopback,     "start i2s loopback"},
    { "stop_loopback",       Cmd_stop_loopback,     "stop i2s loopback"},
#if (CHIP_ID==6020)
    {"vol",                Cmd_ob_volume,  "vol"},
#if (CHIP_SUB_ID != 0)
    {"start_tone",                Cmd_start_tone,  "start tone test"},
    {"stop_tone",                Cmd_stop_tone,  "stop tone test"},    
#endif
#endif
    {"AT+SCAN", Cmd_Scan, "do scan"},
    {"AT+CONNECT", Cmd_Connect, "test connect to ssid password"},
    { (const char *)NULL,   (CliCmdFunc)NULL,   (const char *)NULL },
};


