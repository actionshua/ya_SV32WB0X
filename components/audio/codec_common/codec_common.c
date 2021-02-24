
#include <stdio.h>
#include "es8374.h"
#include "es8311.h"
#include "es8388.h"
#include "codec_common.h"

struct codec_hal {
    int (*codec_init)();
    void (*codec_uninit)(void);
    int (*codec_sart)(CodecModule mode);
    int (*codec_stop)(CodecModule mode);
    int (*codec_config_fmt)(CodecModule mode, CodecI2SFmt fmt);
    int (*codec_set_bit)(CodecModule mode, BitsLength bitPerSample);
    int (*codec_set_adc_input)(AdcInput input);
    int (*codec_set_vol)(int volume);
    int (*codec_get_vol)(int *volume);
    int (*codec_set_mute)(int en);
    int (*codec_get_mute)(int *mute);
};

struct codec_hal codecConfig = {
#if (CODEC_TYPE == 1)
    .codec_init = Es8374Init,
    .codec_uninit = Es8374Uninit,
    .codec_sart = Es8374Start,
    .codec_stop = Es8374Stop,
    .codec_config_fmt = Es8374ConfigFmt,
    .codec_set_bit = Es8374SetBitsPerSample,
    .codec_set_adc_input = Es8374ConfigAdcInput,
    .codec_set_vol = Es8374SetVoiceVolume,
    .codec_get_vol = Es8374GetVoiceVolume,
    .codec_set_mute = Es8374SetVoiceMute,
    .codec_get_mute = Es8374GetVoiceMute,
#elif(CODEC_TYPE == 2)
    .codec_init = Es8311Init,
    .codec_uninit = Es8311Uninit,
    .codec_sart = Es8311Start,
    .codec_stop = Es8311Stop,
    .codec_config_fmt = Es8311ConfigFmt,
    .codec_set_bit = Es8311SetBitsPerSample,
    .codec_set_adc_input = Es8311ConfigAdcInput,
    .codec_set_vol = Es8311SetVoiceVolume,
    .codec_get_vol = Es8311GetVoiceVolume,
    .codec_set_mute = Es8311SetVoiceMute,
    .codec_get_mute = Es8311GetVoiceMute,
#elif(CODEC_TYPE == 3)
    .codec_init = Es8388Init,
    .codec_uninit = Es8388Uninit,
    .codec_sart = Es8388Start,
    .codec_stop = Es8388Stop,
    .codec_config_fmt = Es8388ConfigFmt,
    .codec_set_bit = Es8388SetBitsPerSample,
    .codec_set_adc_input = Es8388ConfigAdcInput,
    .codec_set_vol = Es8388SetVoiceVolume,
    .codec_get_vol = Es8388GetVoiceVolume,
    .codec_set_mute = Es8388SetVoiceMute,
    .codec_get_mute = Es8388GetVoiceMute,
#endif
};

int codec_init()
{
    static int init_en = 0;
    if(init_en == 1) {
        printf("codec already init\n");
        return -1;
    }
    int ret  = 0;
    ret |= codecConfig.codec_init();
    ret |= codecConfig.codec_config_fmt(MODULE_ADC_DAC, I2S_FMT_NORMAL);
    ret |= codecConfig.codec_set_bit(MODULE_ADC_DAC, BIT_LENGTH_16BITS);
#if (CODEC_TYPE == 1)
    ret |= codecConfig.codec_set_adc_input(ADC_INPUT_LINPUT2_RINPUT2);
#else
    ret |= codecConfig.codec_set_adc_input(ADC_INPUT_LINPUT1_RINPUT1);
#endif
    ret |= codecConfig.codec_sart(MODULE_ADC_DAC);
    ret |= codecConfig.codec_set_vol(60);
    init_en = 1;
    return ret;
}

int codec_get_volume(int *volume)
{
    codecConfig.codec_get_vol(volume);
    return 0;
}

int codec_set_volume(int volume)
{
    codecConfig.codec_set_vol(volume);
    return 0;
}

