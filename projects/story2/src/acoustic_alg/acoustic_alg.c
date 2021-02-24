
#include <stdio.h>
#include <bsp.h>
#include "osal.h"
#include "fsal.h"
#include "webrtc/common_audio/vad/include/webrtc_vad.h"
#include "webrtc/modules/audio_processing/agc/include/gain_control.h"
#include "webrtc/modules/audio_processing/agc/analog_agc.h"
#include "webrtc/modules/audio_processing/agc/digital_agc.h"
#include "webrtc/modules/audio_processing/ns/include/noise_suppression_x.h"
#include "webrtc/modules/audio_processing/aec/include/echo_cancellation.h"

#include "speexdsp/include/speex/speex_echo.h"
#include "speexdsp/include/speex/speex_preprocess.h"

#define ORIGIN_FILE_NAME "/sdcard/record.pcm"
#define NS_FILE_NAME "/sdcard/record.pcm"
#define AEC_FILE_NAME "/sdcard/record.pcm.aec"
#define AGC_FILE_NAME "/sdcard/record.pcm.ns"
#define VAD_FILE_NAME "/sdcard/record.pcm.ns.agc"
#define SAMPLE_RATE 16000
#define CHANNELS 2

#define NN 160
#define NN_R NN*sizeof(short)
#define NN_RA NN_R*2
#define TAIL 1024

void speex_aec_run(void *param)
{
    SpeexEchoState *st;
    SpeexPreprocessState *den;
    int sampleRate = 16000;
    int cnt = 0;
    int16_t *aec_origin  = malloc(NN_RA);
    int16_t *aec_in  = malloc(NN_R);
    int16_t *aec_ref = malloc(NN_R);
    int16_t *aec_out = malloc(NN_R);
    static SSV_FILE file_in,file_ref, file_out;
    int nRead = 0, i = 0;

    printf("speex begin\n");
    file_in = FS_open(fs_handle, ORIGIN_FILE_NAME, SPIFFS_RDWR, 0);
    FS_remove(fs_handle, AEC_FILE_NAME);
    file_out = FS_open(fs_handle, AEC_FILE_NAME, SPIFFS_O_CREAT | SPIFFS_RDWR, 0);
    
    st = speex_echo_state_init(NN, TAIL);
    den = speex_preprocess_state_init(NN, sampleRate);
    speex_echo_ctl(st, SPEEX_ECHO_SET_SAMPLING_RATE, &sampleRate);
    speex_preprocess_ctl(den, SPEEX_PREPROCESS_SET_ECHO_STATE, st);

    while(1)
    {
        nRead = FS_read(fs_handle, file_in, aec_origin, NN_RA);
        if(nRead <= 0 || nRead != NN_RA) {
            printf("== break (%d %d) cnt: %d ==\n", nRead, NN_RA, cnt);
            break;
        }

        for(i = 0; i < NN; i++) {
            *(aec_ref + i) = *(aec_origin + (i*2));
            *(aec_in + i) = *(aec_origin + ((i*2) + 1));
        }
        speex_echo_cancellation(st, aec_in, aec_ref, aec_out);
        speex_preprocess_run(den, aec_out);
        FS_write(fs_handle, file_out, aec_out, NN_R);
        cnt++;
    }

    FS_close(fs_handle,file_in);
    FS_close(fs_handle,file_out);
    speex_echo_state_destroy(st);
    speex_preprocess_state_destroy(den);
    free(aec_origin);
    free(aec_in);
    free(aec_ref);
    free(aec_out);
    printf("speex end\n");
    OS_TaskDelete(NULL);
}

void vad_run(void *param) 
{
    char name[128];
    int i = 0, k = 0, status = 0, nRead = 0;
    int samples = SAMPLE_RATE / 50;
    int len = sizeof(int16_t) * CHANNELS * samples;
    int16_t *vad_in = (int16_t *)malloc(len);
    int16_t *frame = (int16_t *)malloc(len);
    static SSV_FILE file_in, file_out;
    VadInst* Vadhandle = NULL;

    printf("== vad test into ==\n");
    WebRtcVad_Create(&Vadhandle);
    if(Vadhandle != NULL) {
        status = WebRtcVad_Init(Vadhandle);
        if(status != 0) {
            printf("[%d] %s (%d)\n",__LINE__, __func__, status);
            goto EXIT;
        } else {
            status = WebRtcVad_set_mode(Vadhandle, 2);
            if(status != 0) {
                printf("[%d] %s (%d),need check\n",__LINE__, __func__, status);
                goto EXIT;
            }
        }
    } else {
        printf("VadHandle: %x null\n", Vadhandle);
        goto EXIT;
    }

    snprintf(name, 128, "%s.vad", VAD_FILE_NAME);
    file_in = FS_open(fs_handle, VAD_FILE_NAME, SPIFFS_RDWR, 0);
    FS_remove(fs_handle, name);
    file_out = FS_open(fs_handle, name, SPIFFS_O_CREAT | SPIFFS_RDWR, 0);

    while (1)
    {
        nRead = FS_read(fs_handle, file_in, vad_in, len);
        if((nRead <= 0) || (nRead != len)) {
            break;
        }
        for(i = 0; i < CHANNELS; i++) {
            if(i == (CHANNELS - 1)) {//only use mono channel data
                continue;
            }
            for(k = 0; k < samples; k++) {
                frame[k] = vad_in[k*CHANNELS + i];
            }
            status = WebRtcVad_Process(Vadhandle, SAMPLE_RATE, frame, samples);
            printf("status: %d\n", status);
            if(status == 1) {
                FS_write(fs_handle, file_out, frame, samples*2);
            }
        }
    }

EXIT:
    WebRtcVad_Free(Vadhandle);
    Vadhandle = NULL;
    FS_close(fs_handle,file_in);
    FS_close(fs_handle,file_out);
    free(vad_in);
    free(frame);
    printf("== vad test exit ==\n");
    OS_TaskDelete(NULL);
}

void agc_run(void *param) 
{
    char name[128];
    int i = 0, k = 0, status = 0, nRead = 0;
    int samples = SAMPLE_RATE / 100;
    int len = sizeof(int16_t) * CHANNELS * samples;
    int16_t *agc_in = (int16_t *)malloc(len);
    int16_t *agc_out = (int16_t *)malloc(len);
    int16_t *frame = (int16_t *)malloc(len);
    static SSV_FILE file_in, file_out;
    void *AgcHandles[2];

    uint8_t saturationWarning;
    int32_t inMicLevel = 0;
    int32_t outMicLevel = 0;
    int32_t minLevel = 0;
    int32_t maxLevel = 255;
    WebRtcAgc_config_t AgcConfig;

    AgcConfig.compressionGaindB = 15;
    AgcConfig.limiterEnable = 1;
    AgcConfig.targetLevelDbfs = -3;

    printf("== agc test into ==\n");
    for(i = 0; i < CHANNELS; i++) {
        WebRtcAgc_Create(&AgcHandles[i]);
        if(AgcHandles[i] != NULL) {
            status = WebRtcAgc_Init(AgcHandles[i], minLevel, maxLevel, 3, SAMPLE_RATE);
            if(status != 0) {
                printf("[%d] %s (%d %d)\n",__LINE__, __func__, i, status);
                goto EXIT;
            } else {
                status = WebRtcAgc_set_config(AgcHandles[i], AgcConfig);
                if(status != 0) {
                    printf("[%d] %s (%d %d),need check\n",__LINE__, __func__, i, status);
                    //goto EXIT;
                }
            }
        } else {
            printf("[%d] AgcHandles: %x null\n", i, AgcHandles[i]);
            goto EXIT;
        }
    }

    snprintf(name, 128, "%s.agc", AGC_FILE_NAME);
    file_in = FS_open(fs_handle, AGC_FILE_NAME, SPIFFS_RDWR, 0);
    FS_remove(fs_handle, name);
    file_out = FS_open(fs_handle, name, SPIFFS_O_CREAT | SPIFFS_RDWR, 0);

    while(1) {
        nRead = FS_read(fs_handle, file_in, agc_in, len);
        if((nRead <= 0) || (nRead != len)) {
            break;
        }
        for(i = 0; i < CHANNELS; i++) {
            for(k = 0; k < samples; k++) {
                frame[k] = agc_in[k*CHANNELS + i];
            }
            status = WebRtcAgc_Process(AgcHandles[i], (short *)frame, NULL, samples, (short *)agc_out, NULL, inMicLevel,&outMicLevel, 0, &saturationWarning);
            if(status != 0) {
                printf("[%d] %s (%d %d)\n",__LINE__, __func__, i, status);
                goto EXIT;
            }
            for(k = 0; k < samples; k++) {
                agc_in[k*CHANNELS + i] = agc_out[k];
            }
        }
        FS_write(fs_handle, file_out, agc_in, nRead);
    }

EXIT:
    for(i = 0; i < CHANNELS; i++) {
        WebRtcAgc_Free(AgcHandles[i]);
        AgcHandles[i] = NULL;
    }
    FS_close(fs_handle,file_in);
    FS_close(fs_handle,file_out);
    free(frame);
    free(agc_in);
    free(agc_out);
    printf("== agc test exit ==\n");
    OS_TaskDelete(NULL);
}

void ns_run(void *param) 
{
    char name[128];
    int i = 0, k = 0, status = 0, nRead = 0;
    int samples = SAMPLE_RATE / 100;
    int len = sizeof(int16_t) * CHANNELS * samples;
    int16_t *ns_in = (int16_t *)malloc(len);
    int16_t *ns_out = (int16_t *)malloc(len);
    int16_t *frame = (int16_t *)malloc(len);
    static SSV_FILE file_in, file_out;
    NsxHandle *NsxHandles[2];

    printf("== ns test into ==\n");
    for(i = 0; i < CHANNELS; i++) {
        WebRtcNsx_Create(&NsxHandles[i]);
        if(NsxHandles[i] != NULL) {
            status = WebRtcNsx_Init(NsxHandles[i], SAMPLE_RATE);
            if(status != 0) {
                printf("[%d] %s (%d %d)\n",__LINE__, __func__, i, status);
                goto EXIT;
            } else {
                status = WebRtcNsx_set_policy(NsxHandles[i], 3);
                if(status != 0) {
                    printf("[%d] %s (%d %d)\n",__LINE__, __func__, i, status);
                    goto EXIT;
                }
            }
        } else {
            printf("[%d] NsxHandles: %x null\n", i, NsxHandles[i]);
            goto EXIT;
        }
    }

    snprintf(name, 128, "%s.ns", NS_FILE_NAME);
    file_in = FS_open(fs_handle, NS_FILE_NAME, SPIFFS_RDWR, 0);
    FS_remove(fs_handle, name);
    file_out = FS_open(fs_handle, name, SPIFFS_O_CREAT | SPIFFS_RDWR, 0);

    while(1) {
        nRead = FS_read(fs_handle, file_in, ns_in, len);
        if((nRead <= 0) || (nRead != len)) {
            break;
        }
        for(i = 0; i < CHANNELS; i++) {
            for(k = 0; k < samples; k++) {
                frame[k] = ns_in[k*CHANNELS + i];
            }
            status = WebRtcNsx_Process(NsxHandles[i], (short *)frame, NULL, (short *)ns_out, NULL);
            if(status != 0) {
                printf("[%d] %s (%d %d)\n",__LINE__, __func__, i, status);
                goto EXIT;
            }
            for(k = 0; k < samples; k++) {
                ns_in[k*CHANNELS + i] = ns_out[k];
            }
        }
        FS_write(fs_handle, file_out, ns_in, nRead);
    }

EXIT:
    for(i = 0; i < CHANNELS; i++) {
        WebRtcNsx_Free(NsxHandles[i]);
        NsxHandles[i] = NULL;
    }
    FS_close(fs_handle,file_in);
    FS_close(fs_handle,file_out);
    free(frame);
    free(ns_in);
    free(ns_out);
    printf("== ns test exit ==\n");
    OS_TaskDelete(NULL);
}

void aec_test()
{
    OS_TaskCreate(speex_aec_run, "aec", 4096, NULL, OS_TASK_LOW_PRIO, NULL);
}

void vad_test()
{
    OS_TaskCreate(vad_run, "vad", 2048, NULL, OS_TASK_LOW_PRIO, NULL);
}

void agc_test()
{
    OS_TaskCreate(agc_run, "agc", 2048, NULL, OS_TASK_LOW_PRIO, NULL);
}

void ns_test()
{
    OS_TaskCreate(ns_run, "ns", 2048, NULL, OS_TASK_LOW_PRIO, NULL);
}
