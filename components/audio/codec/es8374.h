
#ifndef __ES8374_H__
#define __ES8374_H__

#include "soc_types.h"
#include "drv_i2cmst.h"
#include "codec_common.h"

/* ES8374 address */
#define ES8374_ADDR 0x10  // 0x11:CE=1;0x10:CE=0

int Es8374Init();
void Es8374Uninit();
int Es8374Start(CodecModule mode);
int Es8374Stop(CodecModule mode);

int Es8374I2sConfigClock(CodecI2sClock cfg);
int Es8374SetBitsPerSample(CodecModule mode, BitsLength bitPerSample);
int Es8374ConfigFmt(CodecModule mode, CodecI2SFmt fmt);
int Es8374ConfigDacOutput(DacOutput dacoutput);
int Es8374ConfigAdcInput(AdcInput adcinput);
int Es8374SetVoiceMute(int mute);
int Es8374GetVoiceMute(int *mute);
int Es8374SetVoiceVolume(int volume);
int Es8374GetVoiceVolume(int *volume);

int ES8374WriteReg(uint8_t regAdd, uint8_t data);
int ES8374ReadReg(uint8_t regAdd, uint8_t *regv);

#endif  //__ES8374_INTERFACE_H__

