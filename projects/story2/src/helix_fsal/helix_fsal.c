/* ***** BEGIN LICENSE BLOCK *****
 * Version: RCSL 1.0/RPSL 1.0
 *
 * Portions Copyright (c) 1995-2002 RealNetworks, Inc. All Rights Reserved.
 *
 * The contents of this file, and the files included with this file, are
 * subject to the current version of the RealNetworks Public Source License
 * Version 1.0 (the "RPSL") available at
 * http://www.helixcommunity.org/content/rpsl unless you have licensed
 * the file under the RealNetworks Community Source License Version 1.0
 * (the "RCSL") available at http://www.helixcommunity.org/content/rcsl,
 * in which case the RCSL will apply. You may also obtain the license terms
 * directly from RealNetworks.  You may not use this file except in
 * compliance with the RPSL or, if you have a valid RCSL with RealNetworks
 * applicable to this file, the RCSL.  Please see the applicable RPSL or
 * RCSL for the rights, obligations and limitations governing use of the
 * contents of the file.
 *
 * This file is part of the Helix DNA Technology. RealNetworks is the
 * developer of the Original Code and owns the copyrights in the portions
 * it created.
 *
 * This file, and the files included with this file, is distributed and made
 * available on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND REALNETWORKS HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 *
 * Technology Compatibility Kit Test Suite(s) Location:
 *    http://www.helixcommunity.org/content/tck
 *
 * Contributor(s):
 *
 * ***** END LICENSE BLOCK ***** */

/**************************************************************************************
 * Fixed-point MP3 decoder
 * Jon Recker (jrecker@real.com), Ken Cooke (kenc@real.com)
 * June 2003
 *
 * main.c - command-line test app that uses C interface to MP3 decoder
 **************************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "wdt/drv_wdt.h"

#include "mp3dec.h"
#include  "codec_common.h"

#define M_PERFORMANCE_CHECK         (0)
#include "osal.h"
#include "fsal.h"
#include "bsp.h"

#include <drv_i2s.h>
#if(CHIP_ID!=6006)
#include <drv_pdm.h>
#endif
//#include "hw_regs.h"


#define READBUF_SIZE        (1024*2)   /* feel free to change this, but keep big enough for >= one frame at high bitrates */
#define MAX_ARM_FRAMES      100
#define ARMULATE_MUL_FACT   1

static SSV_FILE g_mp3_file_handler;

static __attribute__ ((noinline)) int FillReadBuffer(unsigned char *readBuf, unsigned char *readPtr, int bufSize, int bytesLeft/*, FILE *infile*/)
{
    uint32_t mh_total_time_start = OS_GetSysTick();
    int nRead;
    /* move last, small chunk from end of buffer to start, then fill with new data */
    memmove(readBuf, readPtr, bytesLeft);
    nRead = FS_read(fs_handle, g_mp3_file_handler, readBuf+bytesLeft, bufSize - bytesLeft);
    if(nRead <= 0) {
        printf("fs read fail: %d\n", nRead);
        return -1;
    }
    uint32_t mh_total_time_end = OS_GetSysTick();
    if((mh_total_time_end - mh_total_time_start) > 20) {
        printf("==time %d size: %d==\n", mh_total_time_end - mh_total_time_start,  bufSize - bytesLeft);
    }
    /* zero-pad to avoid finding false sync word after last frame (from old data in readBuf) */
    if (nRead < bufSize - bytesLeft)
        memset(readBuf + bytesLeft + nRead, 0, bufSize - bytesLeft - nRead);

    return nRead;
}


//#define PERFORMANCE_TESTER

#if defined(PERFORMANCE_TESTER)
#define PERFORMANCE_ARR_SIZE            (256)
static uint16_t sg_performance_tester[PERFORMANCE_ARR_SIZE];
static uint16_t sg_sample_size[PERFORMANCE_ARR_SIZE];
static uint16_t sg_max_decode_time = 0xFFFF;
#endif

struct _args {
    char args;
    char argv[8][256];
};

int g_mp3_fsal_player_stop = 1;
int g_mp3_fsal_player_pause = 0;
int g_mp3_fsal_player_exit = 0;
//extern void hal_dmac_enable_all_register_isr();


void helix_fsal_player(void *param) ATTRIBUTE_SECTION_FAST;
void helix_fsal_player(void *param)
{
    struct _args *args = (struct _args *)param;
    char path[256];
    const int ARGV_PATH = 1;
    const int ARGV_MODULE = 2;
    const int ARGV_MODE = 3;
    const int PDM_EN = 4;
    int module = strtol(args->argv[ARGV_MODULE], NULL, 10);
    int data_mode = strtol(args->argv[ARGV_MODE], NULL, 10);
    int pdm_en = strtol(args->argv[PDM_EN], NULL, 10);
    int buf_len = 0;
    int cnt = 0;
    int tmp = 0;
    strncpy(path, args->argv[ARGV_PATH], 256);
#if(CHIP_ID==6006)
    if(module == DRV_I2S_1) {
        printf("%d only support i2s1 port\n", CHIP_ID);
        module = DRV_I2S_0;//6006 only support i2s0
    }
    if(data_mode == DMAC_MODE) {
        printf("%d only support mcu mode, not support dma mode\n", CHIP_ID);
        data_mode = MCU_MODE; //6006 only support mcu ode
    }
    if(pdm_en == 1) {
        printf("%d only support i2s, not support pdm\n", CHIP_ID);
        pdm_en = 0;//6006 only support i2s
    }
#endif
    OS_MemFree(param);

    int one_time = 0;
    int bytesLeft, nRead, err, offset, outOfData, eofReached;
    unsigned char readBuf[READBUF_SIZE], *readPtr;
    MP3FrameInfo mp3FrameInfo;
    HMP3Decoder hMP3Decoder;
    int nFrames;
#if defined(PERFORMANCE_TESTER)
    int performance_idx = 0;
#endif

    i2s_buffer i2s_buf;
    i2s_buf.pingpong_idx = 0;
    i2s_buf.ping_pong[0].buffer_idx = 0;
    i2s_buf.ping_pong[1].buffer_idx = 0;
    i2s_buf.ping_pong[2].buffer_idx = 0;
    i2s_buf.ping_pong[0].buffer_len = MAX_NCHAN * MAX_NGRAN * MAX_NSAMP * sizeof(short);
    i2s_buf.ping_pong[1].buffer_len = MAX_NCHAN * MAX_NGRAN * MAX_NSAMP * sizeof(short);
    i2s_buf.ping_pong[2].buffer_len = MAX_NCHAN * MAX_NGRAN * MAX_NSAMP * sizeof(short);
    i2s_buf.ping_pong[0].data_ready = 0;
    i2s_buf.ping_pong[1].data_ready = 0;
    i2s_buf.ping_pong[2].data_ready = 0;
    i2s_buf.dup_sample = 2;
    i2s_buf.i2s_dup_sample_idx = 0;
    i2s_buf.ping_pong[0].buffer = OS_MemAlloc(MAX_NCHAN * MAX_NGRAN * MAX_NSAMP * sizeof(short));
    i2s_buf.ping_pong[1].buffer = OS_MemAlloc(MAX_NCHAN * MAX_NGRAN * MAX_NSAMP * sizeof(short));
    i2s_buf.ping_pong[2].buffer = OS_MemAlloc(MAX_NCHAN * MAX_NGRAN * MAX_NSAMP * sizeof(short));
    i2s_buf.idle_cnt = 0;
    i2s_buf.event = NULL;
    if( pdm_en == 0) {
        codec_init();
    }

    short *outBuf;


#ifdef __NDS32__
    long long total_samples = 0;
#endif

    g_mp3_file_handler = FS_open(fs_handle, path, SSV_O_RDONLY, 0);
    if(g_mp3_file_handler == NULL) {
        printf("fs open fail\n");
        goto EXIT;
    }
    if ( (hMP3Decoder = MP3InitDecoder()) == 0 )
    {
        FS_close(fs_handle, g_mp3_file_handler);
        return;
    }

    bytesLeft = 0;
    outOfData = 0;
    eofReached = 0;
    readPtr = readBuf;
    nRead = 0;
    nFrames = 0;

    int pingpong_idx = i2s_buf.pingpong_idx;
    struct _i2s_buffer_st *buf = &(i2s_buf.ping_pong[pingpong_idx]);

#if defined(M_PERFORMANCE_CHECK) && (M_PERFORMANCE_CHECK == 1)
    int64_t mh_start;
    int64_t mh_total_time_start = OS_GetUsSysTick();
    int64_t mh_fs_time = 0;
    int64_t mh_max_fs_lock_time = 0;
    int64_t mh_fs_lock_time = 0;
    HW_TU3_US_REG->TIMER = 0xFFFF;
#endif
    do
    {
        outBuf = buf->buffer;
        if((g_mp3_fsal_player_pause == 1) && (one_time)) {
            memset(outBuf, 0, buf->buffer_len);
            buf->data_ready = 1;
            buf->buffer_idx = 0;
            pingpong_idx = ((pingpong_idx + 1) % 3);
            while((i2s_buf.ping_pong[pingpong_idx].data_ready) && (!g_mp3_fsal_player_stop)) {
                OS_MsDelay(10);
            }

            buf = &(i2s_buf.ping_pong[pingpong_idx]);
        } else {
            /* somewhat arbitrary trigger to refill buffer - should always be enough for a full frame */
#if defined(M_PERFORMANCE_CHECK) && (M_PERFORMANCE_CHECK == 1)
            mh_start = OS_GetUsSysTick();
#endif
            if (bytesLeft < 2 * MAINBUF_SIZE && !eofReached)
            {
                nRead = FillReadBuffer(readBuf, readPtr, READBUF_SIZE, bytesLeft/*, infile*/);
                bytesLeft += nRead;
                readPtr = readBuf;
                if (nRead <= 0) {
                    eofReached = 1;
                    outOfData = 1;
                    break;
                }
            }
#if defined(M_PERFORMANCE_CHECK) && (M_PERFORMANCE_CHECK == 1)
            mh_fs_time += (mh_fs_lock_time = OS_GetUsSysTick() - mh_start);
            if (mh_max_fs_lock_time < mh_fs_lock_time) {
                mh_max_fs_lock_time = mh_fs_lock_time;
            }
#endif

            /* find start of next MP3 frame - assume EOF if no sync found */
            offset = MP3FindSyncWord(readPtr, bytesLeft);
            if (offset < 0)
            {
                outOfData = 1;
                break;
            }
            readPtr += offset;
            bytesLeft -= offset;
            /* decode one MP3 frame - if offset < 0 then bytesLeft was less than a full frame */
            err = MP3Decode(hMP3Decoder, &readPtr, &bytesLeft, outBuf, 0);
            nFrames++;
            //hal_dmac_enable_all_register_isr();
            if (err)
            {

                /* error occurred */
                switch (err)
                {
                case ERR_MP3_INDATA_UNDERFLOW:
                    outOfData = 1;
                    break;
                case ERR_MP3_MAINDATA_UNDERFLOW:
                    /* do nothing - next call to decode will provide more mainData */
                    break;
                case ERR_MP3_FREE_BITRATE_SYNC:
                default:
                    outOfData = 1;
                    break;
                }
            }
            else
            {
                /* no error */
                MP3GetLastFrameInfo(hMP3Decoder, &mp3FrameInfo);
    			if(mp3FrameInfo.layer == 0) {
    				printf("mp3 layer not support\n");
    				continue;
    			}
#ifdef __NDS32__
                total_samples += (mp3FrameInfo.outputSamps / mp3FrameInfo.nChans);
                if(mp3FrameInfo.nChans == 1) {
                    tmp = mp3FrameInfo.outputSamps * mp3FrameInfo.bitsPerSample / 8 * 2;
                    for(cnt = tmp/2; cnt >= 2; cnt-=2) {
                        outBuf[cnt -1] = 0;
                        outBuf[cnt - 2] = outBuf[cnt/2 - 1];
                    }
                }
                buf->data_ready = 1;
                buf->buffer_idx = 0;
#if defined(PERFORMANCE_TESTER)
                if (performance_idx < PERFORMANCE_ARR_SIZE) {
                    sg_sample_size[performance_idx] = (mp3FrameInfo.outputSamps / mp3FrameInfo.nChans);
                    sg_performance_tester[performance_idx++] = HW_TU3_US_REG->CURRENT_TIME_VALUE;
                }
                if (HW_TU3_US_REG->CURRENT_TIME_VALUE < sg_max_decode_time) {
                    sg_max_decode_time = HW_TU3_US_REG->CURRENT_TIME_VALUE;
                }
#endif
            }
            if (!one_time) {
                 i2s_buf.ping_pong[0].buffer_len = mp3FrameInfo.outputSamps * mp3FrameInfo.bitsPerSample / 8;
                 i2s_buf.ping_pong[1].buffer_len = mp3FrameInfo.outputSamps * mp3FrameInfo.bitsPerSample / 8;
                 i2s_buf.ping_pong[2].buffer_len = mp3FrameInfo.outputSamps * mp3FrameInfo.bitsPerSample / 8;
                i2s_buf.stereo = (mp3FrameInfo.nChans>1);
                if(mp3FrameInfo.nChans == 1) {
                    i2s_buf.ping_pong[0].buffer_len *= 2;
                    i2s_buf.ping_pong[1].buffer_len *= 2;
                    i2s_buf.ping_pong[2].buffer_len *= 2;
                }
                drv_i2s_set_buffer_ex(module, NULL, 0, &i2s_buf, 3);
                switch(mp3FrameInfo.samprate) {
                    case 44100:
                        i2s_buf.dup_sample = 0;
                        drv_i2s_init_ex(module, mode_master, SampleRate_44100HZ, Resolution_16bit);
                        break;
                    case 48000:
                        i2s_buf.dup_sample = 0;
                        drv_i2s_init_ex(module, mode_master, SampleRate_48000HZ, Resolution_16bit);
                        break;
                    case 22050:
                        i2s_buf.dup_sample = 1;
                        drv_i2s_init_ex(module, mode_master, SampleRate_44100HZ, Resolution_16bit);
                        break;
                    case 24000:
                        i2s_buf.dup_sample = 1;
                        drv_i2s_init_ex(module, mode_master, SampleRate_48000HZ, Resolution_16bit);
                        break;
                    case 11025:
                        i2s_buf.dup_sample = 3;
                        drv_i2s_init_ex(module, mode_master, SampleRate_44100HZ, Resolution_16bit);
                        break;
                    case 16000:
                        i2s_buf.dup_sample = 0;
                        drv_i2s_init_ex(module, mode_master, SampleRate_16000HZ, Resolution_16bit);
                        break;
                    case 8000:
                        i2s_buf.dup_sample = 5;
                        drv_i2s_init_ex(module, mode_master, SampleRate_48000HZ, Resolution_16bit);
                        break;
                }
#if(CHIP_ID!=6006)
                if(pdm_en == 1) {
                    drv_pdm_init(module);
                    drv_pdm_tx_enable(module, mp3FrameInfo.samprate/1000, PDM_TX_Bit_Depth_16, PDM_TX_STEREO, 0);
                }
#endif
                one_time = !one_time;
                drv_i2s_tx_start_ex(module, data_mode);
            }
            pingpong_idx = ((pingpong_idx + 1) % 3);
            while((i2s_buf.ping_pong[pingpong_idx].data_ready) && (!g_mp3_fsal_player_stop)) {
                OS_UsDelay(1);
            }
#if defined(PERFORMANCE_TESTER)
            HW_TU3_US_REG->TIMER = 0xFFFF;
#endif
            buf = &(i2s_buf.ping_pong[pingpong_idx]);
#endif
        }
    }
    while ((!outOfData) && (!g_mp3_fsal_player_stop) && (!g_mp3_fsal_player_exit));

#if defined(PERFORMANCE_TESTER)
    {
        int i;
        for (i = 0; i < PERFORMANCE_ARR_SIZE; i++) {
            printf("performance = %d\n", 0xFFFF-sg_performance_tester[i]);
        }
        printf("max_decode time = %d\n", 0xFFFF - sg_max_decode_time);
    }
#endif
#if defined(M_PERFORMANCE_CHECK) && (M_PERFORMANCE_CHECK == 1)
    int64_t mh_finish = OS_GetUsSysTick();
    printf("total ticks %lld\n", mh_finish - mh_total_time_start);
    printf("total fs ticks %lld\n", mh_fs_time);
    printf("max fs ticks %lld\n", mh_max_fs_lock_time);
#endif
    printf("\nDecoded %d frames\n", nFrames);
    printf("Total ouput sampels per channel is %d\n", (int)total_samples);
    printf("PCM width is %d \n", (mp3FrameInfo.bitsPerSample / 8));
    printf("Sample rate is %d\n", mp3FrameInfo.samprate);
    printf("Bitrate is %d\n", mp3FrameInfo.bitrate);

    MP3FreeDecoder(hMP3Decoder);

    FS_close(fs_handle, g_mp3_file_handler);
    drv_i2s_tx_stop_ex(module);

    printf("ping wait ready\n");
    while(1) {
        if (!i2s_buf.ping_pong[0].data_ready) {
            break;
        }
        OS_MsDelay(1);
    }
    printf("pong wait ready\n");
    while(1) {
        if (!i2s_buf.ping_pong[1].data_ready) {
            break;
        }
        OS_MsDelay(1);
    }
    printf("pong pong wait ready\n");
    while(1) {
        if (!i2s_buf.ping_pong[2].data_ready) {
            break;
        }
        OS_MsDelay(1);
    }
    printf("idle wait ready\n");
#if 0
    while(1) {
        if (i2s_buf.buf.idle_cnt > 12000) {
            break;
        }
        OS_MsDelay(1);
    }
#endif
EXIT:
    printf("helix free\n");
#if(CHIP_ID!=6006)
    if(pdm_en == 1) {
        drv_pdm_tx_disable(module);
    }
#endif
    OS_MemFree(i2s_buf.ping_pong[0].buffer);
    OS_MemFree(i2s_buf.ping_pong[1].buffer);
    OS_MemFree(i2s_buf.ping_pong[2].buffer);
    g_mp3_fsal_player_stop = 1;
    OS_TaskDelete(NULL);
    while(1);
}


