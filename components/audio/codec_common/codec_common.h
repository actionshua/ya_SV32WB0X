#ifndef __CODEC_COMMON_H__
#define __CODEC_COMMON_H__

typedef enum BitsLength {
    BIT_LENGTH_MIN = -1,
    BIT_LENGTH_16BITS = 0x03,
    BIT_LENGTH_18BITS = 0x02,
    BIT_LENGTH_20BITS = 0x01,
    BIT_LENGTH_24BITS = 0x00,
    BIT_LENGTH_32BITS = 0x04,
    BIT_LENGTH_MAX,
} BitsLength;

typedef enum {
    MclkDiv_MIN = -1,
    MclkDiv_1 = 1,
    MclkDiv_2 = 2,
    MclkDiv_3 = 3,
    MclkDiv_4 = 4,
    MclkDiv_6 = 5,
    MclkDiv_8 = 6,
    MclkDiv_9 = 7,
    MclkDiv_11 = 8,
    MclkDiv_12 = 9,
    MclkDiv_16 = 10,
    MclkDiv_18 = 11,
    MclkDiv_22 = 12,
    MclkDiv_24 = 13,
    MclkDiv_33 = 14,
    MclkDiv_36 = 15,
    MclkDiv_44 = 16,
    MclkDiv_48 = 17,
    MclkDiv_66 = 18,
    MclkDiv_72 = 19,
    MclkDiv_5 = 20,
    MclkDiv_10 = 21,
    MclkDiv_15 = 22,
    MclkDiv_17 = 23,
    MclkDiv_20 = 24,
    MclkDiv_25 = 25,
    MclkDiv_30 = 26,
    MclkDiv_32 = 27,
    MclkDiv_34 = 28,
    MclkDiv_7  = 29,
    MclkDiv_13 = 30,
    MclkDiv_14 = 31,
    MclkDiv_MAX,
} SclkDiv;

typedef enum {
    LclkDiv_MIN = -1,
    LclkDiv_128 = 0,
    LclkDiv_192 = 1,
    LclkDiv_256 = 2,
    LclkDiv_384 = 3,
    LclkDiv_512 = 4,
    LclkDiv_576 = 5,
    LclkDiv_768 = 6,
    LclkDiv_1024 = 7,
    LclkDiv_1152 = 8,
    LclkDiv_1408 = 9,
    LclkDiv_1536 = 10,
    LclkDiv_2112 = 11,
    LclkDiv_2304 = 12,

    LclkDiv_125 = 16,
    LclkDiv_136 = 17,
    LclkDiv_250 = 18,
    LclkDiv_272 = 19,
    LclkDiv_375 = 20,
    LclkDiv_500 = 21,
    LclkDiv_544 = 22,
    LclkDiv_750 = 23,
    LclkDiv_1000 = 24,
    LclkDiv_1088 = 25,
    LclkDiv_1496 = 26,
    LclkDiv_1500 = 27,
    LclkDiv_MAX,
} LclkDiv;

typedef enum {
    ADC_INPUT_LINPUT1_RINPUT1 = 0x00,
    ADC_INPUT_LINPUT2_RINPUT2 = 0x50,
    ADC_INPUT_DIFFERENCE = 0xf0,
    ADC_INPUT_MAX,
} AdcInput;

typedef enum {
    DAC_OUTPUT_MIN = -1,
    DAC_OUTPUT_LOUT1 = 0x04,
    DAC_OUTPUT_LOUT2 = 0x08,
    DAC_OUTPUT_ROUT1 = 0x10,
    DAC_OUTPUT_ROUT2 = 0x20,
    DAC_OUTPUT_ALL = 0x3c,
    DAC_OUTPUT_MAX,
} DacOutput;

typedef enum {
    MODULE_ADC = 0x01,
    MODULE_DAC = 0x02,
    MODULE_ADC_DAC = 0x03,
    MODULE_LINE = 0x04,
    MODULE_MAX
} CodecModule;

typedef enum {
    MODE_SLAVE = 0x00,
    MODE_MASTER = 0x01,
    MODE_MAX,
} CodecMode;

typedef enum {
    I2S_FMT_NORMAL = 0,
    I2S_FMT_LEFT = 1,
    I2S_FMT_RIGHT = 2,
    I2S_FMT_MAX
} CodecI2SFmt;

typedef struct {
    SclkDiv sclkDiv;
    LclkDiv lclkDiv;
} CodecI2sClock;

#define I2C_USE_PORT DRV_I2C_1

int codec_init();
int codec_get_volume(int *volume);
int codec_set_volume(int volume);

#endif //__CODEC_COMMON_H__

