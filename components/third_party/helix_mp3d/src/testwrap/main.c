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

#include "mp3dec.h"
#include "debug.h"
#include "timing.h"

#if defined(__NDS32__) & defined(PF_COUNTER)
#include "nds32_pfcounter.h"
#endif

//#define READ_MP3DATA_FROM_ARRAY
//#define DECODE_MP3_FOLDER
#define NUM_OF_MP3          92
#define WRITE_OUT_PCM


#ifdef READ_MP3DATA_FROM_ARRAY
#include "mp3data_sine1k.h"
#endif

#define READBUF_SIZE        (1024*16)   /* feel free to change this, but keep big enough for >= one frame at high bitrates */
#define MAX_ARM_FRAMES      1000
#define ARMULATE_MUL_FACT   1

#ifdef READ_MP3DATA_FROM_ARRAY
char *mp3data_read_ptr;
int mp3data_total_size = sizeof(mp3data);

static int ReadMp3Data(unsigned char *dst, int read_size)
{
    if (mp3data_total_size <= 0)
        return 0;

    if (read_size > mp3data_total_size)
    {
        read_size = mp3data_total_size;
    }
    memcpy(dst, mp3data_read_ptr, read_size);
    mp3data_total_size -= read_size;
    mp3data_read_ptr += read_size;
    return read_size;
}
#endif

const char mp3_path[] = "../mp3_dir/";

char *mp3_list[NUM_OF_MP3] =
{
    "01-1kHz_ref_tone_at-14dB_FS.mp3",
    "02-Pink_noise_L.mp3",
    "03-Pink_noise_R.mp3",
    "04-Pink_noise_L+R_and_phase_check.mp3",
    "05-Pink_noise_bass_0-200Hz_and_phase_check.mp3",
    "06-Pink_noise_low_mid_200Hz-1kHz_and_phase_check.mp3",
    "07-Pink_noise_high_mid_1kHz-inf._and_phase_check.mp3",
    "08-Pink_noise_HF_7kHz-inf._and_phase_check.mp3",
    "09-1_3_octave_1kHz_ref._tone.mp3",
    "10-1_3_octave_20Hz.mp3",
    "11-1_3_octave_25Hz.mp3",
    "12-1_3_octave_31.5Hz.mp3",
    "13-1_3_octave_40Hz.mp3",
    "14-1_3_octave_50Hz.mp3",
    "15-1_3_octave_63Hz.mp3",
    "16-1_3_octave_80Hz.mp3",
    "17-1_3_octave_100Hz.mp3",
    "18-1_3_octave_125Hz.mp3",
    "19-1_3_octave_160Hz.mp3",
    "20-1_3_octave_200Hz.mp3",
    "21-1_3_octave_250Hz.mp3",
    "22-1_3_octave_315Hz.mp3",
    "23-1_3_octave_400Hz.mp3",
    "24-1_3_octave_500Hz.mp3",
    "25-1_3_octave_630Hz.mp3",
    "26-1_3_octave_800Hz.mp3",
    "27-1_3_octave_1kHz.mp3",
    "28-1_3_octave_1.25kHz.mp3",
    "29-1_3_octave_1.6kHz.mp3",
    "30-1_3_octave_2kHz.mp3",
    "31-1_3_octave_2.5kHz.mp3",
    "32-1_3_octave_3.15kHz.mp3",
    "33-1_3_octave_4kHz.mp3",
    "34-1_3_octave_5kHz.mp3",
    "35-1_3_octave_6kHz.mp3",
    "36-1_3_octave_8kHz.mp3",
    "37-1_3_octave_10kHz.mp3",
    "38-1_3_octave_12.5kHz.mp3",
    "39-1_3_octave_16kHz.mp3",
    "40-1_3_octave_20kHz.mp3",
    "41-Sweeps_1kHz_ref._warble.mp3",
    "42-Sweeps_1kHz-500Hz_500Hz-250Hz_250Hz-125Hz_125Hz-20Hz.mp3",
    "43-Sweeps_1kHz-2kHz_2kHz-4kHz_4kHz-8kHz.mp3",
    "44-Sine_1kHz_ref._tone_at_-14dB_FS.mp3",
    "45-Sine_60Hz.mp3",
    "46-Sine_100Hz.mp3",
    "47-Sine_250Hz.mp3",
    "48-Sine_500Hz.mp3",
    "49-Sine_1kHz.mp3",
    "50-Sine_2kHz.mp3",
    "51-Sine_3kHz.mp3",
    "52-Sine_5kHz.mp3",
    "53-Sine_10kHz.mp3",
    "54-Sine_12kHz.mp3",
    "55-Sine_15kHz.mp3",
    "56-Sine_sweep_20Hz-20kHz.mp3",
    "57-Square_1kHz_at_-20dB_FS.mp3",
    "58-Square_5kHz_at_-20dB_FS.mp3",
    "59-Max_level_tone_1kHz_sine_at_0dB_FS.mp3",
    "60-Spoken_word.mp3",
    "61-Piano.mp3",
    "62-Acoustic_guitar-finger-style.mp3",
    "63-Acoustic_guitar-strummed.mp3",
    "64-Spanish_guitar.mp3",
    "65-Electric_guitar-clean.mp3",
    "66-Electric_guitar-distorted.mp3",
    "67-Bass_guitar.mp3",
    "68-Flute.mp3",
    "69-Saxophone.mp3",
    "70-Vocal.mp3",
    "71-Bongos.mp3",
    "72-Tambourine.mp3",
    "73-Kick_drum.mp3",
    "74-Snare_drum.mp3",
    "75-Cymbals_and_hi-hat.mp3",
    "76-Toms.mp3",
    "77-Whole_drum_kit.mp3",
    "78-Violins.mp3",
    "79-Cellos_and_violas.mp3",
    "80-The_Race_Yello.mp3",
    "81-Limelight_Alan_Parsons_Project.mp3",
    "82-Seasons_Of_Our_Lives_Graham_de_Wilde_and_Mitch_Dalton.mp3",
    "83-Bach_Toccata_and_Fugue_in_D_minor.mp3",
    "84-Sub-machine_gun.mp3",
    "85-Chieftain_tank.mp3",
    "86-Thunderstorm.mp3",
    "87-Steam_trains.mp3",
    "88-1000mph_jet_flypast.mp3",
    "89-EBU_25_frame_timecode_10_00_00_to_10_05_00.mp3",
    "90-SMPTE_non-drop_frame_timecode_10_00_00_to_10_05_00.mp3",
    "91-91-SMPTE_drop_frame_timecode_10_00_00_to_10_05_00.mp3",
    "92-A-440_tuning_reference.mp3"
};


static int FillReadBuffer(unsigned char *readBuf, unsigned char *readPtr, int bufSize, int bytesLeft, FILE *infile)
{
    int nRead;

    /* move last, small chunk from end of buffer to start, then fill with new data */
    memmove(readBuf, readPtr, bytesLeft);

#ifdef READ_MP3DATA_FROM_ARRAY
    nRead = ReadMp3Data(readBuf + bytesLeft, bufSize - bytesLeft);
#else
    nRead = fread(readBuf + bytesLeft, 1, bufSize - bytesLeft, infile);
#endif

    /* zero-pad to avoid finding false sync word after last frame (from old data in readBuf) */
    if (nRead < bufSize - bytesLeft)
        memset(readBuf + bytesLeft + nRead, 0, bufSize - bytesLeft - nRead);

    return nRead;
}


int Get_MP3_Filename(char *fileName)
{
    int nRead, nextNum = 0;
    FILE *numFile;

    numFile = fopen("decode_mp3_num", "r+");
    if (numFile)
    {
        fscanf(numFile, "%d", &nextNum);
        rewind(numFile);
    }
    else
    {
        numFile = fopen("decode_mp3_num", "w");
        if (!numFile)
        {
            printf("Can not open file (decode_mp3_num)\n");
            return -1;
        }
    }

    if (nextNum > NUM_OF_MP3)
    {
        return -1;
    }
    else
    {
        strcpy(fileName, mp3_list[nextNum]);
    }

    nextNum++;
    printf("[%d]", nextNum);

    fprintf(numFile, "%d", nextNum);
    //fflush(numFile);
    fclose(numFile);
    return 0;
}

int main(int argc, char **argv)
{
    int bytesLeft, nRead, err, offset, outOfData, eofReached;
    unsigned char readBuf[READBUF_SIZE], *readPtr;
    short outBuf[MAX_NCHAN * MAX_NGRAN * MAX_NSAMP];
    FILE *infile, *outfile;
    MP3FrameInfo mp3FrameInfo;
    HMP3Decoder hMP3Decoder;
    int startTime, endTime, diffTime, totalDecTime, nFrames;
#ifdef DECODE_MP3_FOLDER
    char inFilename[256];
    char outFilename[256];
#endif

#ifdef ARM_ADS
    float audioSecs;
    volatile float temp;
#endif

#ifdef __NDS32__
    long long total_samples = 0;
#ifdef PF_COUNTER
    acc_result pfmResult = {0, 0};
#endif
#endif


#ifdef READ_MP3DATA_FROM_ARRAY
    mp3data_read_ptr = (char *)mp3data;
#endif

#if 0
    if (argc != 3)
    {
        printf("argc=%d argv[0]=\n", argc);
        printf("usage: mp3dec infile.mp3 outfile.pcm\n");
        return -1;
    }

    infile = fopen(argv[1], "rb");
    if (!infile)
    {
        printf("file open error (%s)\n", argv[1]);
        return -1;
    }
    else
    {
        printf("file open OK (%s)\n", argv[1]);
    }

    if (strcmp(argv[2], "nul"))
    {
        outfile = fopen(argv[2], "wb");
        if (!outfile)
        {
            printf("file open error (%s)\n", argv[2]);
            return -1;
        }
        else
        {
            printf("file open OK (%s)\n", argv[2]);
        }
    }
    else
    {
        outfile = 0;    /* nul output */
    }
#endif

#ifdef __NDS32__
#ifndef READ_MP3DATA_FROM_ARRAY
    if (Get_MP3_Filename(outFilename) < 0)
    {
        printf("[Error] End main.adx\n");
        return -1;
    }
    // else
    // {
    //     printf("Now mp3 filename is %s \n", outFilename);
    // }

    //infile = fopen("../49-Sine_1kHz.mp3", "rb");
    strcpy(inFilename, mp3_path);
    strcat(inFilename, outFilename);
    infile = fopen(inFilename, "rb");
    if (!infile)
    {
        printf("file open error (%s)\n", inFilename);
        return -1;
    }
    else
    {
        printf("file open OK (%s)\n", inFilename);
    }
#endif

#ifdef WRITE_OUT_PCM
#ifdef READ_MP3DATA_FROM_ARRAY
    outfile = fopen("sine_array.pcm", "wb");
#else
    strcat(outFilename, ".pcm");
    outfile = fopen(outFilename, "wb");
    if (!outfile)
    {
        printf("file open error (%s)\n", outFilename);
        return -1;
    }
    else
    {
        printf("file open OK (%s)\n", outFilename);
    }
#endif
#endif
#endif


    DebugMemCheckInit();
    InitTimer();

    DebugMemCheckStartPoint();

    if ( (hMP3Decoder = MP3InitDecoder()) == 0 )
        return -2;

    DebugMemCheckEndPoint();

    bytesLeft = 0;
    outOfData = 0;
    eofReached = 0;
    readPtr = readBuf;
    nRead = 0;
    totalDecTime = 0;
    nFrames = 0;
    do
    {
        /* somewhat arbitrary trigger to refill buffer - should always be enough for a full frame */
        if (bytesLeft < 2 * MAINBUF_SIZE && !eofReached)
        {
            nRead = FillReadBuffer(readBuf, readPtr, READBUF_SIZE, bytesLeft, infile);
            bytesLeft += nRead;
            readPtr = readBuf;
            if (nRead == 0)
                eofReached = 1;
        }

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
#if defined(__NDS32__) & defined(PF_COUNTER)
        startPFM;
#else
        startTime = ReadTimer();
#endif
        err = MP3Decode(hMP3Decoder, &readPtr, &bytesLeft, outBuf, 0);

#if defined(__NDS32__) & defined(PF_COUNTER)
        stopPFM;
        ACC_Result(&pfmResult);
#else
        endTime = ReadTimer();
        diffTime = CalcTimeDifference(startTime, endTime);
        totalDecTime += diffTime;
#endif

        nFrames++;

#if defined(__NDS32__) & defined(PF_COUNTER)
        printf(".");
        //Read_ACC_Result(&pfmResult);
        fflush(stdout);
#else
        //defined ARM_ADS && defined MAX_ARM_FRAMES
        printf("frame %5d  start = %10d, end = %10d elapsed = %10d ticks\r",
               nFrames, startTime, endTime, diffTime);
        fflush(stdout);
#endif

        if (err)
        {

#ifdef __NDS32__
            printf("Error[%d %x] after MP3Decode\n", err, err);
#endif

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
#ifdef __NDS32__
            //printf("Write pcm_width:%d samples:%d \n", (mp3FrameInfo.bitsPerSample / 8), mp3FrameInfo.outputSamps);
            total_samples += (mp3FrameInfo.outputSamps / mp3FrameInfo.nChans);

#ifdef WRITE_OUT_PCM
            if (outfile)
                fwrite(outBuf, mp3FrameInfo.bitsPerSample / 8, mp3FrameInfo.outputSamps, outfile);
#endif
#endif
        }

#if (defined __NDS32__ || defined ARM_ADS) && defined MAX_ARM_FRAMES
        if (nFrames >= MAX_ARM_FRAMES)
            break;
#endif
    }
    while (!outOfData);

    printf("\nDecoded %d frames\n", nFrames);
    printf("Total ouput sampels per channel is %d\n", (int)total_samples);
    printf("PCM width is %d \n", (mp3FrameInfo.bitsPerSample / 8));
    printf("Sample rate is %d\n", mp3FrameInfo.samprate);
    printf("Bitrate is %d\n", mp3FrameInfo.bitrate);

#if defined(__NDS32__) & defined(PF_COUNTER)
    Read_ACC_Result(&pfmResult);
    printf("MHz is %.02f \n\n", (pfmResult.cycle * mp3FrameInfo.samprate / (double)total_samples) / 1000000.0);
#endif

    fflush(stdout);


#ifdef ARM_ADS
    MP3GetLastFrameInfo(hMP3Decoder, &mp3FrameInfo);
    audioSecs = ((float)nFrames * mp3FrameInfo.outputSamps) / ( (float)mp3FrameInfo.samprate * mp3FrameInfo.nChans);
    temp = ARMULATE_MUL_FACT * (1.0f / audioSecs) * totalDecTime * GetClockDivFactor() / 1e6f;

    //printf("\nTotal clock ticks = %d, MHz usage = %.2f\n", totalDecTime, ARMULATE_MUL_FACT * (1.0f / audioSecs) * totalDecTime * GetClockDivFactor() / 1e6f);
    //printf("nFrames = %d, output samps = %d, sampRate = %d, nChans = %d\n", nFrames, mp3FrameInfo.outputSamps, mp3FrameInfo.samprate, mp3FrameInfo.nChans);
#endif

    MP3FreeDecoder(hMP3Decoder);

#ifndef READ_MP3DATA_FROM_ARRAY
    fclose(infile);
#endif

#ifdef WRITE_OUT_PCM
    if (outfile)
        fclose(outfile);
#endif

    FreeTimer();
    DebugMemCheckFree();

    return 0;
}
