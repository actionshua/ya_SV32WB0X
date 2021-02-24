
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pvmp3decoder_api.h"
#include  "codec_common.h"

#include "osal.h"
#include "fsal.h"
#include "bsp.h"

#include <drv_i2s.h>
#if(CHIP_ID!=6006)
#include <drv_pdm.h>
#endif

//#define M_PERFORMANCE_CHECK
#include "lwip/sockets.h"

struct _args {
    char args;
    char argv[8][256];
};

#define INPUT_SIZE (1* 1024)
#define OUTPUT_SIZE (2304*2)

int g_mp3_fsal_player_stop = 1;
int g_mp3_fsal_player_pause = 0;
int g_mp3_fsal_player_exit = 0;

tPVMP3DecoderExternal mConfig;

uint32_t mCurrentPos = 0;
uint32_t mFixedHeader = 0;
uint32_t mSampleRate = 0;
uint32_t mNumChannels = 0;
uint32_t mBitrate = 0;

// Mask to extract the version, layer, sampling rate parts of the MP3 header,
// which should be same for all MP3 frames.
static const uint32_t kMask = 0xfffe0c00;

static SSV_FILE g_mp3_file_handler;

static uint32_t U32_AT(const uint8_t *ptr) {
    return ptr[0] << 24 | ptr[1] << 16 | ptr[2] << 8 | ptr[3];
}

static bool parseHeader(
        uint32_t header, size_t *frame_size,
        uint32_t *out_sampling_rate, uint32_t *out_channels ,
        uint32_t *out_bitrate, uint32_t *out_num_samples) {
    *frame_size = 0;

    if (out_sampling_rate) {
        *out_sampling_rate = 0;
    }

    if (out_channels) {
        *out_channels = 0;
    }

    if (out_bitrate) {
        *out_bitrate = 0;
    }

    if (out_num_samples) {
        *out_num_samples = 1152;
    }

    if ((header & 0xffe00000) != 0xffe00000) {
        return false;
    }

    unsigned version = (header >> 19) & 3;

    if (version == 0x01) {
        return false;
    }

    unsigned layer = (header >> 17) & 3;

    if (layer == 0x00) {
        return false;
    }

    unsigned bitrate_index = (header >> 12) & 0x0f;

    if (bitrate_index == 0 || bitrate_index == 0x0f) {
        // Disallow "free" bitrate.
        return false;
    }

    unsigned sampling_rate_index = (header >> 10) & 3;

    if (sampling_rate_index == 3) {
        return false;
    }

    static const int kSamplingRateV1[] = { 44100, 48000, 32000 };
    int sampling_rate = kSamplingRateV1[sampling_rate_index];
    if (version == 2 /* V2 */) {
        sampling_rate /= 2;
    } else if (version == 0 /* V2.5 */) {
        sampling_rate /= 4;
    }

    unsigned padding = (header >> 9) & 1;

    if (layer == 3) {
        // layer I

        static const int kBitrateV1[] = {
            32, 64, 96, 128, 160, 192, 224, 256,
            288, 320, 352, 384, 416, 448
        };

        static const int kBitrateV2[] = {
            32, 48, 56, 64, 80, 96, 112, 128,
            144, 160, 176, 192, 224, 256
        };

        int bitrate =
            (version == 3 /* V1 */)
                ? kBitrateV1[bitrate_index - 1]
                : kBitrateV2[bitrate_index - 1];

        if (out_bitrate) {
            *out_bitrate = bitrate;
        }

        *frame_size = (12000 * bitrate / sampling_rate + padding) * 4;

        if (out_num_samples) {
            *out_num_samples = 384;
        }
    } else {
        // layer II or III

        static const int kBitrateV1L2[] = {
            32, 48, 56, 64, 80, 96, 112, 128,
            160, 192, 224, 256, 320, 384
        };

        static const int kBitrateV1L3[] = {
            32, 40, 48, 56, 64, 80, 96, 112,
            128, 160, 192, 224, 256, 320
        };

        static const int kBitrateV2[] = {
            8, 16, 24, 32, 40, 48, 56, 64,
            80, 96, 112, 128, 144, 160
        };

        int bitrate;
        if (version == 3 /* V1 */) {
            bitrate = (layer == 2 /* L2 */)
                ? kBitrateV1L2[bitrate_index - 1]
                : kBitrateV1L3[bitrate_index - 1];

            if (out_num_samples) {
                *out_num_samples = 1152;
            }
        } else {
            // V2 (or 2.5)

            bitrate = kBitrateV2[bitrate_index - 1];
            if (out_num_samples) {
                *out_num_samples = (layer == 1 /* L3 */) ? 576 : 1152;
            }
        }

        if (out_bitrate) {
            *out_bitrate = bitrate;
        }

        if (version == 3 /* V1 */) {
            *frame_size = 144000 * bitrate / sampling_rate + padding;
        } else {
            // V2 or V2.5
            size_t tmp = (layer == 1 /* L3 */) ? 72000 : 144000;
            *frame_size = tmp * bitrate / sampling_rate + padding;
        }
    }

    if (out_sampling_rate) {
        *out_sampling_rate = sampling_rate;
    }

    if (out_channels) {
        int channel_mode = (header >> 6) & 3;

        *out_channels = (channel_mode == 3) ? 1 : 2;
    }

    return true;
}

static int sourceReadAt(uint32_t offset, void *data, int size)
{
    int nRead;
    if(FS_lseek(fs_handle, g_mp3_file_handler, offset, SSV_SEEK_SET) !=offset) {
        printf("fs lseek fail\n");
        return 0;
    }

    nRead = FS_read(fs_handle, g_mp3_file_handler, data, size);
    if(nRead <= 0) {
        printf("fs read fail: %d\n", nRead);
        return -1;
    }
    return nRead;
}

// Resync to next valid MP3 frame in the file.
static bool resync(uint32_t match_header, uint32_t *inout_pos, uint32_t *out_header) {

    if (*inout_pos == 0) {
        // Skip an optional ID3 header if syncing at the very beginning
        // of the datasource.
        for (;;) {
            uint8_t id3header[10];
            int retVal = sourceReadAt(*inout_pos, id3header,
                                      sizeof(id3header));
            if (retVal < (ssize_t)sizeof(id3header)) {
                // If we can't even read these 10 bytes, we might as well bail
                // out, even if there _were_ 10 bytes of valid mp3 audio data...
                return false;
            }

            if (memcmp("ID3", id3header, 3)) {
                break;
            }

            // Skip the ID3v2 header.

            size_t len =
                ((id3header[6] & 0x7f) << 21)
                | ((id3header[7] & 0x7f) << 14)
                | ((id3header[8] & 0x7f) << 7)
                | (id3header[9] & 0x7f);

            len += 10;

            *inout_pos += len;
            //printf("skipped ID3 tag, new starting offset is %lld (0x%016llx)\n",
                    //(long long)*inout_pos, (long long)*inout_pos);
        }
    }

    uint32_t pos = *inout_pos;
    bool valid = false;

    const int32_t kMaxReadBytes = 1024;
    const int32_t kMaxBytesChecked = 128 * 1024;
    uint8_t buf[kMaxReadBytes];
    ssize_t bytesToRead = kMaxReadBytes;
    ssize_t totalBytesRead = 0;
    ssize_t remainingBytes = 0;
    bool reachEOS = false;
    uint8_t *tmp = buf;

    do {
        if (pos >= (uint32_t)(*inout_pos + kMaxBytesChecked)) {
            // Don't scan forever.
            printf("giving up at offset %lld\n", (long long)pos);
            break;
        }

        if (remainingBytes < 4) {
            if (reachEOS) {
                break;
            } else {
                memcpy(buf, tmp, remainingBytes);
                bytesToRead = kMaxReadBytes - remainingBytes;

                /*
                 * The next read position should start from the end of
                 * the last buffer, and thus should include the remaining
                 * bytes in the buffer.
                 */
                totalBytesRead = sourceReadAt(pos + remainingBytes,
                                             buf + remainingBytes, bytesToRead);

                if (totalBytesRead <= 0) {
                    break;
                }
                reachEOS = (totalBytesRead != bytesToRead);
                remainingBytes += totalBytesRead;
                tmp = buf;
                continue;
            }
        }

        uint32_t header = U32_AT(tmp);

        if (match_header != 0 && (header & kMask) != (match_header & kMask)) {
            ++pos;
            ++tmp;
            --remainingBytes;
            continue;
        }

        size_t frame_size;
        uint32_t sample_rate, num_channels, bitrate;
        if (!parseHeader(
                    header, &frame_size,
                    &sample_rate, &num_channels, &bitrate, NULL)) {
            ++pos;
            ++tmp;
            --remainingBytes;
            continue;
        }

        // printf("found possible 1st frame at %lld (header = 0x%08x)", (long long)pos, header);
        // We found what looks like a valid frame,
        // now find its successors.

        uint32_t test_pos = pos + frame_size;

        valid = true;
        const int FRAME_MATCH_REQUIRED = 3;
        for (int j = 0; j < FRAME_MATCH_REQUIRED; ++j) {
            uint8_t tmp[4];
            ssize_t retval = sourceReadAt(test_pos, tmp, sizeof(tmp));
            if (retval < (ssize_t)sizeof(tmp)) {
                valid = false;
                break;
            }

            uint32_t test_header = U32_AT(tmp);

            if ((test_header & kMask) != (header & kMask)) {
                valid = false;
                break;
            }

            size_t test_frame_size;
            if (!parseHeader(test_header, &test_frame_size, NULL, NULL, NULL, NULL)) {
                valid = false;
                break;
            }

            //printf("found subsequent frame #%d at %lld\n", j + 2, (long long)test_pos);
            test_pos += test_frame_size;
        }

        if (valid) {
            *inout_pos = pos;

            if (out_header != NULL) {
                *out_header = header;
            }
        } else {
            printf("no dice, no valid sequence of frames found.\n");
        }

        ++pos;
        ++tmp;
        --remainingBytes;
    } while (!valid);

    return valid;
}

// Initialize the MP3 reader.
bool mp3Reader_init(char *path) {
    g_mp3_file_handler = FS_open(fs_handle, path, SSV_O_RDONLY, 0);
    if(g_mp3_file_handler == NULL) {
        printf("fs open fail\n");
        return false;
    }

    uint32_t pos = 0;
    uint32_t header;
    bool success = resync(0 /*match_header*/, &pos, &header);
    if (!success) {
        printf("%s, resync failed\n", __FUNCTION__);
        return false;
    }

    mCurrentPos  = pos;
    mFixedHeader = header;

    size_t frame_size;
    return parseHeader(header, &frame_size, &mSampleRate,
                       &mNumChannels, &mBitrate, NULL);
}

// Get the next valid MP3 frame.
bool mp3Reader_getFrame(void *buffer, uint32_t *size) {

    size_t frame_size;
    uint32_t bitrate;
    uint32_t num_samples;
    uint32_t sample_rate;
    for (;;) {
        ssize_t n = sourceReadAt(mCurrentPos, buffer, 4);
        if (n < 4) {
            return false;
        }

        uint32_t header = U32_AT((const uint8_t *)buffer);

        if ((header & kMask) == (mFixedHeader & kMask)
            && parseHeader(
                header, &frame_size, &sample_rate, NULL /*out_channels*/,
                &bitrate, &num_samples)) {
            break;
        }

        // Lost sync.
        uint32_t pos = mCurrentPos;
        if (!resync(mFixedHeader, &pos, NULL /*out_header*/)) {
            // Unable to resync. Signalling end of stream.
            return false;
        }

        mCurrentPos = pos;

        // Try again with the new position.
    }
    ssize_t n = sourceReadAt(mCurrentPos, buffer, frame_size);
    if (n < (ssize_t)frame_size) {
        return false;
    }

    *size = frame_size;
    mCurrentPos += frame_size;
    return true;
}

// Close the MP3 reader.
void mp3Reader_close() {
    FS_close(fs_handle, g_mp3_file_handler);
}

void helix_fsal_player(void *param) ATTRIBUTE_SECTION_FAST;
void helix_fsal_player(void *param)
{
    //input para init 
    struct _args *args = (struct _args *)param;
    char path[256];
    const int ARGV_PATH = 1;
    const int ARGV_MODULE = 2;
    const int ARGV_MODE = 3;
    const int PDM_EN = 4;
    int module = strtol(args->argv[ARGV_MODULE], NULL, 10);
    int data_mode = strtol(args->argv[ARGV_MODE], NULL, 10);
    int pdm_en = strtol(args->argv[PDM_EN], NULL, 10);
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

    uint8_t *inputBuf = NULL;
    void *decoderBuf = NULL;

    short *outBuf, i = 0;
    uint32_t cnt = 0;
    int one_time = 0;
    uint32_t total_samples = 0;
    uint32_t memRequirements = 0;
    uint32_t bytesRead = 0;
    uint32_t file_size = 0;
    uint32_t out_need_len = 0;
    ERROR_CODE decoderErr = 0;
    i2s_buffer i2s_buf;
 
    //Initialize the config
    mConfig.crcEnabled = false;
    mConfig.equalizerType = flat;
    memset(&i2s_buf, 0, sizeof(i2s_buffer));

    //Allocate input buffer
    inputBuf = OS_MemAlloc(INPUT_SIZE);
    if(inputBuf == NULL) {
        printf("inputBuf malloc fail\n");
        goto EXIT;
    }
    //Allocate the decoder memory
    memRequirements = pvmp3_decoderMemRequirements();
    decoderBuf = OS_MemAlloc(memRequirements);
    if(decoderBuf == NULL) {
        printf("decoderBuf malloc fail\n");
        goto EXIT;
    }

    pvmp3_InitDecoder(&mConfig, decoderBuf);

    if(mp3Reader_init(path) == false) {
        printf("Encountered error reading\n");
        goto EXIT;
    }

    int channels = mNumChannels;
    int samplerate = mSampleRate;

    i2s_buf.pingpong_idx = 0;
    i2s_buf.i2s_dup_sample_idx = 0;
    i2s_buf.ping_pong[0].buffer_idx = 0;
    i2s_buf.ping_pong[1].buffer_idx = 0;
    i2s_buf.ping_pong[2].buffer_idx = 0;
    i2s_buf.ping_pong[0].buffer_len = OUTPUT_SIZE;
    i2s_buf.ping_pong[1].buffer_len = OUTPUT_SIZE;
    i2s_buf.ping_pong[2].buffer_len = OUTPUT_SIZE;
    i2s_buf.ping_pong[0].data_ready = 0;
    i2s_buf.ping_pong[1].data_ready = 0;
    i2s_buf.ping_pong[2].data_ready = 0;
    i2s_buf.ping_pong[0].buffer = OS_MemAlloc(OUTPUT_SIZE);
    i2s_buf.ping_pong[1].buffer = OS_MemAlloc(OUTPUT_SIZE);
    i2s_buf.ping_pong[2].buffer = OS_MemAlloc(OUTPUT_SIZE);
    if(i2s_buf.ping_pong[0].buffer == NULL || i2s_buf.ping_pong[1].buffer == NULL ||
        i2s_buf.ping_pong[2].buffer == NULL) {
        goto EXIT;
    }
    i2s_buf.idle_cnt = 0;
    i2s_buf.event = NULL;
    if( pdm_en == 0) {
        codec_init();
    }

    printf("mp3 file channels: %d samplerate: %d\n", channels, samplerate);

    int pingpong_idx = i2s_buf.pingpong_idx;
    struct _i2s_buffer_st *buf = &(i2s_buf.ping_pong[pingpong_idx]);
    do
    {
        outBuf = buf->buffer;
        if(g_mp3_fsal_player_pause == 1) {
            memset(outBuf, 0, buf->buffer_len);
            buf->data_ready = 1;
            buf->buffer_idx = 0;
            pingpong_idx = ((pingpong_idx + 1) % 3);
            while((i2s_buf.ping_pong[pingpong_idx].data_ready) && (!g_mp3_fsal_player_stop)) {
                OS_MsDelay(10);
            }
            buf = &(i2s_buf.ping_pong[pingpong_idx]);
        } else {
            uint32_t mh_start = OS_GetUsSysTick();
            bool success = mp3Reader_getFrame(inputBuf, &bytesRead);
            if (!success) break;
            uint32_t mh_end = OS_GetUsSysTick();
#ifdef M_PERFORMANCE_CHECK
            printf("get: %d size: %d\n",( mh_end - mh_start), bytesRead);
#endif
            // Set the input config.
            mConfig.inputBufferCurrentLength = bytesRead;
            mConfig.inputBufferMaxLength = 0;
            mConfig.inputBufferUsedLength = 0;
            mConfig.pInputBuffer = inputBuf;
            mConfig.pOutputBuffer = outBuf;
            mConfig.outputFrameSize = OUTPUT_SIZE;
            uint32_t mh_start2 = OS_GetUsSysTick();

            decoderErr = pvmp3_framedecoder(&mConfig, decoderBuf);
            if (decoderErr != NO_DECODING_ERROR) {
                printf("Decoder encountered error=%d", decoderErr);
                goto EXIT;
            }

            uint32_t mh_end2 = OS_GetUsSysTick();
            if (!one_time) {
                if((mConfig.outputFrameSize/mNumChannels*4 )== OUTPUT_SIZE) {
                    out_need_len = OUTPUT_SIZE;
                } else {
                    out_need_len = OUTPUT_SIZE/2;
                }
                i2s_buf.ping_pong[0].buffer_len = out_need_len;
                i2s_buf.ping_pong[1].buffer_len = out_need_len;
                i2s_buf.ping_pong[2].buffer_len = out_need_len;
            }
            if(mNumChannels == 1) {
                for(cnt = out_need_len/2; cnt >= 2; cnt-=2) {
                    outBuf[cnt -1] = 0;
                    outBuf[cnt - 2] = outBuf[cnt/2 - 1];
                }
            }
#ifdef M_PERFORMANCE_CHECK
            printf("dec: %d\n",( mh_end2 - mh_start2));
#endif
            file_size += mConfig.inputBufferCurrentLength;
            total_samples += (mNumChannels == 2) ? (out_need_len / sizeof(int16_t)): (out_need_len / sizeof(int16_t) / 2);
        }
        buf->data_ready = 1;
        buf->buffer_idx = 0;
        if (!one_time) {
            one_time = !one_time;
            drv_i2s_init_ex(module, mode_master, mSampleRate, Resolution_16bit);
            if(pdm_en == 1) {
                drv_pdm_init(module);
            }
            drv_i2s_set_buffer_ex(module, NULL, 0, &i2s_buf, 3);
            drv_i2s_tx_start_ex(module, data_mode);
            if(pdm_en == 1) {
                drv_pdm_tx_enable(module, mSampleRate/1000, PDM_TX_Bit_Depth_16, PDM_TX_STEREO, 0);
            }
        }
        pingpong_idx = ((pingpong_idx + 1) % 3);
        while((i2s_buf.ping_pong[pingpong_idx].data_ready) && (!g_mp3_fsal_player_stop)) {
            OS_UsDelay(1);
        }
        buf = &(i2s_buf.ping_pong[pingpong_idx]);
    }
    while ((!g_mp3_fsal_player_stop) && (!g_mp3_fsal_player_exit));

    printf("mp3 file total size: %d bytes\n", file_size);
    printf("Total ouput sampels per channel is %d\n", total_samples);
    printf("channel is %d \n", mNumChannels);
    printf("Sample rate is %d\n", mSampleRate);
    printf("Bitrate is %d\n", mBitrate);

    mp3Reader_close();
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
#if(CHIP_ID!=6006)
    if(pdm_en == 1) {
        drv_pdm_tx_disable(module);
    }
#endif
EXIT:
    printf("pvmp3 free\n");
    if(i2s_buf.ping_pong[0].buffer != NULL)
        OS_MemFree(i2s_buf.ping_pong[0].buffer);
    if(i2s_buf.ping_pong[1].buffer != NULL)
        OS_MemFree(i2s_buf.ping_pong[1].buffer);
    if(i2s_buf.ping_pong[2].buffer != NULL)
        OS_MemFree(i2s_buf.ping_pong[2].buffer);
    if(i2s_buf.ping_pong[3].buffer != NULL)
    if(inputBuf != NULL)
        OS_MemFree(inputBuf);
    if(decoderBuf != NULL)
        OS_MemFree(decoderBuf);

    g_mp3_fsal_player_stop = 1;
    OS_TaskDelete(NULL);
    while(1);
}

