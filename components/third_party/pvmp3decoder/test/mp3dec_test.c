/*
 * Copyright (C) 2014 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "pvmp3decoder_api.h"
#include "mp3reader.h"

#include <osal.h>
#include <fsal.h>
#include <bsp.h>

extern bool Mp3Reader_init(const char *file);
extern bool Mp3Reader_getFrame(void *buffer, uint32_t *size);

int mp3dec_test(char *filename) 
{
    int res = 0, ret = 0;
    int kInputBufferSize = 10 * 1024;
    int kOutputBufferSize = 4608 * 2;

    // Initialize the config.
    tPVMP3DecoderExternal config;
    config.equalizerType = flat;
    config.crcEnabled = false;
    static SSV_FILE file;

    // Allocate the decoder memory.
    uint32_t memRequirements = pvmp3_decoderMemRequirements();
    void *decoderBuf = malloc(memRequirements);
    if(decoderBuf == NULL) {
        printf("decoderBuf malloc fail\n");
        return -1;
    }

    // Initialize the decoder.
    pvmp3_InitDecoder(&config, decoderBuf);

    // Open the input file.
    bool success = Mp3Reader_init(filename);
    if (!success) {
        printf("Encountered error reading %s\n", filename);
        free(decoderBuf);
        return -2;
    }

    int channels = Mp3Reader_getNumChannels();
    int samplerate = Mp3Reader_getSampleRate();
    printf("== channels: %d samplerate: %d ==\n", channels, samplerate);
    //FS_remove(fs_handle, "/sdcard/test.pcm");
    ///file = FS_open(fs_handle, "/sdcard/test.pcm", SPIFFS_O_CREAT | SPIFFS_RDWR, 0);

    // Allocate input buffer.
    uint8_t *inputBuf = malloc(kInputBufferSize);
    if(decoderBuf == NULL) {
        printf("inputBuf malloc fail\n");
        return -3;
    }

    // Allocate output buffer.
    int16_t *outputBuf = malloc(kOutputBufferSize);
    if(decoderBuf == NULL) {
        printf("outputBuf malloc fail\n");
        return -4;
    }

    // Decode loop.
    int retVal = 0;
    while (1) {
        // Read input from the file.
        uint32_t bytesRead;
        bool success = Mp3Reader_getFrame((void *)inputBuf, (uint32_t *)&bytesRead);
        if (!success) break;

        // Set the input config.
        config.inputBufferCurrentLength = bytesRead;
        config.inputBufferMaxLength = 0;
        config.inputBufferUsedLength = 0;
        config.pInputBuffer = inputBuf;
        config.pOutputBuffer = outputBuf;
        config.outputFrameSize = kOutputBufferSize / sizeof(int16_t);

        ERROR_CODE decoderErr;
        decoderErr = pvmp3_framedecoder(&config, decoderBuf);
        if (decoderErr != NO_DECODING_ERROR) {
            printf("Decoder encountered error: %d\n", decoderErr);
            retVal = -5;
            break;
        }
        printf("== size: %d ==\n", (config.outputFrameSize / channels * 4));
#if 0
        ret = FS_write(fs_handle, file, outputBuf, config.outputFrameSize / channels * 4);
        if ((res = FS_ferrno(file)) != 0) {
            printf("file write fail: res=%d\n", res);
            FS_close(fs_handle, file);
            retVal = -6;
            break;
        }
#endif
    }

    // Close input reader and output writer.
    Mp3Reader_close();
    //_close(fs_handle, file);
    // Free allocated memory.
    free(inputBuf);
    free(outputBuf);
    free(decoderBuf);

    return retVal;
}
