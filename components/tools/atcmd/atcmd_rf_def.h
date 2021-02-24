/**
 *
 * @page ATCMD AT Command Manual V2.0
 *
 * @section ATCMD_rf RF AT Command
 * 
 * @subsection ATCMD_rf_1 Start TX
 * | command     | AT+RF_START=<count>,<interval>
 * |---------------|-------------------|
 * | param         | <count>: must set to 0, mean continuous<br><interval>:  interval time ms (0-16383)         |
 * | return value  | AT+RF_START=OK               |
 * | example       | AT+RF_START=0<br>AT+RF_START=0,1466 |
 *
 * @subsection ATCMD_rf_2 Set Channel
 * | command     | AT+RF_CHANNEL=<ch_number>,<ch_type> |
 * |---------------|-------------------|
 * | param         | <ch_number>: channel number (1-14)<br><ch_type>: +,- 40MHz        |
 * | return value  | AT+RF_CHANNEL=OK              |
 * | example       | AT+RF_CHANNEL=6<br>AT+RF_CHANNEL=9,+ |
 *
 * @subsection ATCMD_rf_3 Set Rate 
 * | command     | AT+RF_RATE=<rate_idx> |
 * |---------------|-------------------|
 * | param         | <rate_idx>: (0-38)<br>0: 11b 1M<br>1: 11b 2M<br>2: 11b 5.5M<br>3: 11b 11M<br>7: 11g 6M<br>8: 11g 9M<br>9: 11g 12M<br>10: 11g 18M<br>11: 11g 24M<br>12: 11g 36M<br>13: 11g 48M<br>14: 11g 54M<br>15: 11n HT20 MCS0<br>16: 11n HT20 MCS1<br>17: 11n HT20 MCS2<br>18: 11n HT20 MCS3<br>19: 11n HT20 MCS4<br>20: 11n HT20 MCS5<br>21: 11n HT20 MCS6<br>22: 11n HT20 MCS7<br>31: 11n HT40 MCS0<br>32: 11n HT40 MCS1<br>33: 11n HT40 MCS2<br>34: 11n HT40 MCS3<br>35: 11n HT40 MCS4<br>36: 11n HT40 MCS5<br>37: 11n HT40 MCS6<br>38: 11n HT40 MCS7<br>         |
 * | return value  | AT+RF_RATE=OK               |
 * | example       | AT+RF_RATE=22 |
 *
 *
 * @subsection ATCMD_rf_4 Set 2.4G Band Gain
 * | command     | AT+RF_2GBAND_GAIN=<gain> |
 * |---------------|-------------------|
 * | param         | <gain>: 2.4G digital gain (1-19)         |
 * | return value  | AT+RF_2GBAND_GAIN=OK               |
 * | example       | AT+RF_2GBAND_GAIN=7 |
 *
 * @subsection ATCMD_rf_5 Set Rate Gain
 * | command     | AT+RF_RATE_GAIN=<rate_type>,<gain> |
 * |---------------|-------------------|
 * | param         | <rate_type>: <br>b: b mode all rate<br>g6: g mode 6M, 9M<br>g12: g mode 12M, 18M<br>g24: g mode 24M, 36M<br>g48: g mode 48M, 54M<br>20n0: n mode HT20 MCS0<br>20n1: n mode HT20 MCS1,MCS2<br>20n3: n mode HT20 MCS3,MCS4<br>20n5: n mode HT20 MCS5,MCS6,MCS7<br>40n0: n mode HT40 MCS0<br>40n1: n mode HT40 MCS1,MCS2<br>40n3: n mode HT40 MCS3,MCS4<br>40n5: n mode HT40 MCS5,MCS6,MCS7<br><gain>: rate gain (1-13)         |
 * | return value  | AT+RF_RATE_GAIN=OK              |
 * | example       | AT+RF_RATE_GAIN=b,7<br>AT+RF_RATE_GAIN=g6,7 |
 *
 * @subsection ATCMD_rf_6 Read Chip Temperature
 * | command     | AT+RF_READ_TEMPCS=? |
 * |---------------|-------------------|
 * | param         | none         |
 * | return value  | temperature = 15<br>AT+RF_READ_TEMPCS=OK              |
 * | example       | AT+RF_READ_TEMPCS=? |
 *
 * @subsection ATCMD_rf_7 Stop TX 
 * | command     | AT+RF_STOP |
 * |---------------|-------------------|
 * | param         | none         |
 * | return value  | AT+RF_STOP=OK               |
 * | example       | AT+RF_STOP |
 *
 * @subsection ATCMD_rf_8 Read b/gn mode package count
 * | command     | AT+RF_COUNT=<mode> |
 * |---------------|-------------------|
 * | param         | <mode>: 1: b mode, 2: g/n mode  (1,2)       |
 * | return value  | B Mode Count:<br>crc count = '42'<br>total count='1000'               |
 * | example       | AT+RF_COUNT=1 |
 *
 * @subsection ATCMD_rf_9 Reset packet count
 * | command     | AT+RF_RESET |
 * |---------------|-------------------|
 * | param         | none         |
 * | return value  |  AT+RF_RESET=OK             |
 * | example       | AT+RF_RESET |
 *
 * @subsection ATCMD_rf_10 Set frequency offset
 * | command     | AT+RF_FREQOFFSET=<offset_xi>,<offset_xo> |
 * |---------------|-------------------|
 * | param         | <offset_xi>: frequency xi offset value (0-255)<br><offset_xo>: frequency xo offset value (0-255)        |
 * | return value  | AT+RF_FREQOFFSET=OK               |
 * | example       | AT+RF_FREQOFFSET=151,151 |
 *
 * @subsection ATCMD_rf_11 Read Frequency XO
 * | command     | AT+RF_FREQOFFSET_READXO=? |
 * |---------------|-------------------|
 * | param         | none        |
 * | return value  | AT+RF_FREQOFFSET_READXO=151               |
 * | example       | AT+RF_FREQOFFSET_READXO=? |
 *
 * @subsection ATCMD_rf_12 Read Frequency XI
 * | command     | AT+RF_FREQOFFSET_READXI=? |
 * |---------------|-------------------|
 * | param         | none         |
 * | return value  | AT+RF_FREQOFFSET_READXI=151               |
 * | example       | AT+RF_FREQOFFSET_READXI=?|
 *
 * @subsection ATCMD_rf_13 Dump RF Setting
 * | command     | AT+RF_DUMP |
 * |---------------|-------------------|
 * | param         | none         |
 * | return value  | AT+RF_DUMP=OK            |
 * | example       | AT+RF_DUMP |
 *
 * @subsection ATCMD_rf_14 Write or Read  RT Table to flash
 * | command     | AT+RF_TABLE_RT=<gain1>,<gain2>,<gain3>,<gain4>,<gain5>,<gain6>,<gain7>,<freq_xi>,<freq_xo>,<rxafe>,<dcdcv>,<dldov>,<vcas1>,<vcas2>,<vcas3>,<bias>,<cap>,<padpd> |
 * |---------------|-------------------|
 * | param         | <gain1>: ch1, ch2 gain (1-19)<br><gain2>: ch3, ch4 gain (1-19)<br><gain3>: ch5, ch6 gain (1-19)<br><gain4>: ch7, ch8 gain (1-19)<br><gain5>: ch9, ch10 gain (1-19)<br><gain6>: ch11, ch12 gain (1-19)<br><gain7>: ch13, ch14 gain (1-19)<br><freq_xi>: frequency offset xi value (0-255)<br><freq_xo>: frequency offset xo value (0-255)<br><rxafe>: RXAFE value (3-10)<br><dcdcv>: DCDCV value (3-13)<br><dldov>: DLDOV value (6-10)<br><vcas1>VCAS1 value (3-10)<br><vcas2>VCAS2value (3-10)<br><vcas3>VCAS3 value (3-10)<br><bias>BIAS value (3-11)<br><cap>CAP value (4-7)<br><padpd>padpd Off/On (0,1)         |
 * | return value  | AT+RF_TABLE_RT=OK               |
 * | example       | AT+RF_TABLE_RT=?<br>AT+RF_TABLE_RT=7,7,7,7,7,7,7,151,151,7,9,10,7,7,7,7,7,0 |
 *
 * @subsection ATCMD_rf_15 Write or Read  HT Table to flash
 * | command     | AT+RF_TABLE_HT=<gain1>,<gain2>,<gain3>,<gain4>,<gain5>,<gain6>,<gain7>,<freq_xi>,<freq_xo>,<rxafe>,<dcdcv>,<dldov>,<vcas1>,<vcas2>,<vcas3>,<bias>,<cap>,<padpd> |
 * |---------------|-------------------|
 * | param         | <gain1>: ch1, ch2 gain (1-19)<br><gain2>: ch3, ch4 gain (1-19)<br><gain3>: ch5, ch6 gain (1-19)<br><gain4>: ch7, ch8 gain (1-19)<br><gain5>: ch9, ch10 gain (1-19)<br><gain6>: ch11, ch12 gain (1-19)<br><gain7>: ch13, ch14 gain (1-19)<br><freq_xi>: frequency offset xi value (0-255)<br><freq_xo>: frequency offset xo value (0-255)<br><rxafe>: RXAFE value (3-10)<br><dcdcv>: DCDCV value (3-13)<br><dldov>: DLDOV value (6-10)<br><vcas1>VCAS1 value (3-10)<br><vcas2>VCAS2value (3-10)<br><vcas3>VCAS3 value (3-10)<br><bias>BIAS value (3-11)<br><cap>CAP value (4-7)<br><padpd>padpd Off/On (0,1)          |
 * | return value  | AT+RF_TABLE_HT=OK              |
 * | example       | AT+RF_TABLE_HT=?<br>AT+RF_TABLE_HT=7,7,7,7,7,7,7,151,151,7,9,10,7,7,7,7,7,0 |
 *
 * @subsection ATCMD_rf_16 Write or Read  LT Table to flash
 * | command     | AT+RF_TABLE_LT=<gain1>,<gain2>,<gain3>,<gain4>,<gain5>,<gain6>,<gain7>,<freq_xi>,<freq_xo>,<rxafe>,<dcdcv>,<dldov>,<vcas1>,<vcas2>,<vcas3>,<bias>,<cap>,<padpd> |
 * |---------------|-------------------|
 * | param         | <gain1>: ch1, ch2 gain (1-19)<br><gain2>: ch3, ch4 gain (1-19)<br><gain3>: ch5, ch6 gain (1-19)<br><gain4>: ch7, ch8 gain (1-19)<br><gain5>: ch9, ch10 gain (1-19)<br><gain6>: ch11, ch12 gain (1-19)<br><gain7>: ch13, ch14 gain (1-19)<br><freq_xi>: frequency offset xi value (0-255)<br><freq_xo>: frequency offset xo value (0-255)<br><rxafe>: RXAFE value (3-10)<br><dcdcv>: DCDCV value (3-13)<br><dldov>: DLDOV value (6-10)<br><vcas1>VCAS1 value (3-10)<br><vcas2>VCAS2value (3-10)<br><vcas3>VCAS3 value (3-10)<br><bias>BIAS value (3-11)<br><cap>CAP value (4-7)<br><padpd>padpd Off/On (0,1)         |
 * | return value  | AT+RF_TABLE_LT=OK               |
 * | example       | AT+RF_TABLE_LT=?<br>AT+RF_TABLE_LT=7,7,7,7,7,7,7,151,151,7,9,10,7,7,7,7,7,0 |
 *
 * @subsection ATCMD_rf_17 Write or Read  B Rate Gain to flash
 * | command     | AT+RF_TABLE_BRATE_GAIN=<gain> |
 * |---------------|-------------------|
 * | param         |   <gain>: rate gain (1-13)      |
 * | return value  | B Mode Rate Gain = 7<br>AT+RF_TABLE_BRATE_GAIN=OK          |
 * | example       | AT+RF_TABLE_BRATE_GAIN=?<br>AT+RF_TABLE_BRATE_GAIN=7 |
 *
 * @subsection ATCMD_rf_18 Write or Read  G Rate Gain to flash
 * | command     | AT+RF_TABLE_GRATE_GAIN=<g6/g9>,<g12/g18>,<g24/g36>,<g48/g54> |
 * |---------------|-------------------|
 * | param         |   <g6/g9>: G Mode 6M,9M gain (1-13)<br><g12/g18>: G Mode 12M,18M gain (1-13)<br><g24/g36>: G Mode 24M,36M gain (1-13)<br><g48/g54>: G Mode 48M,54M gain (1-13)      |
 * | return value  | +OKG Mode Rate Gain = 13,11,9,7<br>AT+RF_TABLE_GRATE_GAIN=OK               |
 * | example       | AT+RF_TABLE_GRATE_GAIN=?<br>AT+RF_TABLE_GRATE_GAIN=13,11,9,7 |
 *
 * @subsection ATCMD_rf_19 Write or Read  20N Rate Gain to flash
 * | command     | AT+RF_TABLE_20NRATE_GAIN=<M0>,<M1/2>,<M3/4>,<M5/6/7> |
 * |---------------|-------------------|
 * | param         |   <M0>: N Mode HT20 MCS0 gain (1-13)<br><M1/2>: N Mode HT20 MCS1,MCS2 gain (1-13)<br><M3/4>: N Mode HT2 MCS3,MCS4 gain (1-13)<br><M5/6/7>: N Mode HT20 MCS5,MCS6,MCS7 gain (1-13)       |
 * | return value  | 20N Mode Rate Gain = 13,11,9,7<br>AT+RF_TABLE_20NRATE_GAIN=OK            |
 * | example       | AT+RF_TABLE_20NRATE_GAIN=?<br>AT+RF_TABLE_20NRATE_GAIN=13,11,9,7 |
 *
 * @subsection ATCMD_rf_20 Write or Read  40N Rate Gain to flash
 * | command     | AT+RF_TABLE_40NRATE_GAIN=<M0>,<M1/2>,<M3/4>,<M5/6/7> |
 * |---------------|-------------------|
 * | param         |   <M0>: N Mode HT40 MCS0 gain (1-13)<br><M1/2>: N Mode HT40 MCS1,MCS2 gain (1-13)<br><M3/4>: N Mode HT40 MCS3,MCS4 gain (1-13)<br><M5/6/7>: N Mode HT40 MCS5,MCS6,MCS7 gain (1-13)       |
 * | return value  | 40N Mode Rate Gain = 13,11,9,7<br>AT+RF_TABLE_40NRATE_GAIN=OK             |
 * | example       | AT+RF_TABLE_40NRATE_GAIN=?<br>AT+RF_TABLE_40NRATE_GAIN=13,11,9,7 |
 *
 * 
 * @subsection ATCMD_rf_21 Tune 5G Band Gain
 * | command     | AT+RF_5G_BB_SCALE=<band0_gain>,<band1_gain>,<band2_gain>,<band3_gain> |
 * |---------------|-------------------|
 * | param         |   <band0_gain>: Gain for 5G Band0 (1-13)<br><band1_gain>: Gain for 5G Band1 (1-13)<br><band2_gain>: Gain for 5G Band2 (1-13)<br><band3_gain>: Gain for 5G Band3 (1-13)       |
 * | return value  | AT+RF_5G_BB_SCALE=OK             |
 * | example       | AT+RF_5G_BB_SCALE=13,13,10,8 |
 *
 * @subsection ATCMD_rf_22 Tune BIAS for 5G Band0 and Band1
 * | command     | AT+RF_5G_BIAS1=<band0/band1 BIAS> |
 * |---------------|-------------------|
 * | param         |   <band0/band1 BIAS>: BIAS Value for band0 and band1       |
 * | return value  | AT+RF_5G_BIAS1=OK             |
 * | example       | AT+RF_5G_BIAS1=92a4924d |
 *
 * @subsection ATCMD_rf_23 Tune BIAS for 5G Band2 and Band3
 * | command     | AT+RF_5G_BIAS2=<band2/band3 BIAS> |
 * |---------------|-------------------|
 * | param         |   <band2/band3 BIAS>: BIAS Value for band2 and band3  |
 * | return value  | AT+RF_5G_BIAS2=OK             |
 * | example       | AT+RF_5G_BIAS2=b6cab6cc |
 *
 * @subsection ATCMD_rf_24 Write or Read 5G RT Table to flash
 * | command     | AT+RF_5GTABLE_RT=<band0_gain>,<band1_gain>,<band2_gain>,<band3_gain> |
 * |---------------|-------------------|
 * | param         |   <band0_gain>: Gain for 5G Band0 (1-13)<br><band1_gain>: Gain for 5G Band1 (1-13)<br><band2_gain>: Gain for 5G Band2 (1-13)<br><band3_gain>: Gain for 5G Band3 (1-13)       |
 * | return value  | AT+RF_5GTABLE_RT=OK             |
 * | example       | AT+RF_5GTABLE_RT=13,11,9,7 |
 *
 * @subsection ATCMD_rf_25 Write or Read 5G HT Table to flash
 * | command     | AT+RF_5GTABLE_HT=<band0_gain>,<band1_gain>,<band2_gain>,<band3_gain> |
 * |---------------|-------------------|
 * | param         |   <band0_gain>: Gain for 5G Band0 (1-13)<br><band1_gain>: Gain for 5G Band1 (1-13)<br><band2_gain>: Gain for 5G Band2 (1-13)<br><band3_gain>: Gain for 5G Band3 (1-13)       |
 * | return value  | AT+RF_5GTABLE_HT=OK             |
 * | example       | AT+RF_5GTABLE_HT=13,11,9,7 |
 *
 * @subsection ATCMD_rf_26 Write or Read 5G LT Table to flash
 * | command     | AT+RF_5GTABLE_LT=<band0_gain>,<band1_gain>,<band2_gain>,<band3_gain> |
 * |---------------|-------------------|
 * | param         |   <band0_gain>: Gain for 5G Band0 (1-13)<br><band1_gain>: Gain for 5G Band1 (1-13)<br><band2_gain>: Gain for 5G Band2 (1-13)<br><band3_gain>: Gain for 5G Band3 (1-13)       |
 * | return value  | AT+RF_5GTABLE_LT=OK             |
 * | example       | AT+RF_5GTABLE_LT=13,11,9,7 |
 *
 * @subsection ATCMD_rf_27 Write or Read RT,HT,LT BIAS for band0 and ban1 to flash
 * | command     | AT+RF_5GTABLE_BIAS1=<RT_BIAS>,<HT_BIAS>,<LT_BIAS> |
 * |---------------|-------------------|
 * | param         |   <RT_BIAS>: BIAS for band0 and band1 at Room Temperature<br><HT_BIAS>: BIAS for band0 and band1 at High Temperature<br><LT_BIAS>: BIAS for band0and band1 at Low Temperature       |
 * | return value  | AT+RF_5GTABLE_BIAS1=OK             |
 * | example       | AT+RF_5GTABLE_BIAS1=92a4924d,92a4924d,92a4924d |
 *
 * @subsection ATCMD_rf_28 Write or Read RT,HT,LT BIAS for band2 and band3 to flash
 * | command     | AT+RF_5GTABLE_BIAS2=<RT_BIAS>,<HT_BIAS>,<LT_BIAS> |
 * |---------------|-------------------|
 * | param         |   <RT_BIAS>: BIAS for band0 and band1 at Room Temperature<br><HT_BIAS>: BIAS for band0 and band1 at High Temperature<br><LT_BIAS>: BIAS for band0and band1 at Low Temperature        |
 * | return value  | AT+RF_5GTABLE_BIAS2=OK             |
 * | example       | AT+RF_5GTABLE_BIAS2=b6cab6cc,b6cab6cc,b6cab6cc |
 *
 * @subsection ATCMD_rf_29 Write or Read BAND Threshold for 5G Band
 * | command     | AT+RF_5GTABLE_BAND_THRESHOLD=<F0_Band_Threshold>,<F1_Band_Threshold>,<F2_Band_Threshold> |
 * |---------------|-------------------|
 * | param         |   <F0_Band_Threshold>: threshold between band0 and band1<br><F1_Band_Threshold>: threshold between band1 and band2<br><F2_Band_Threshold>: threshold between band2 and band3       |
 * | return value  | AT+RF_5GTABLE_BAND_THRESHOLD=OK             |
 * | example       | AT+RF_5GTABLE_BAND_THRESHOLD=5100, 5500, 5700 |
 *
 * @subsection ATCMD_rf_31 Generate Single Tone
 * | command     | AT+RF_TONE_GEN=<on/off> |
 * |---------------|-------------------|
 * | param         |   <on/off>: 1: start single tone, 0: stop single tone |
 * | return value  | AT+RF_TONE_GEN=OK            |
 * | example       | ===Start Single tone===<br>AT+RF_STOP<br>AT+RF_TONE_GEN=1<br>AT+RF_CHANNEL=6<br>AT+RF_START=0<br>===Stop Single tone===<br>AT+RF_TONE_GEN=0<br>AT+RF_SOP=0 |
 *
 * @subsection ATCMD_rf_32 Change Work Mode
 * | command     | AT+RF_WORK_MODE=<mode> |
 * |---------------|-------------------|
 * | param         |   <mode>: 0: Enable Work Normal, 1: Enable Work Engineer     |
 * | return value  | AT+RF_WORK_MODE=OK             |
 * | example       | AT+RF_WORK_MODE=0 |
 *
 * @subsection ATCMD_rf_33 List RF Command
 * | command     | rf |
 * |---------------|-------------------|
 * | param         |   none       |
 * | return value  | rf=OK             |
 * | example       | rf |
 *
 */
#ifndef ATCMD_RF_DEF_H__
#define ATCMD_RF_DEF_H__


//RF Test AT Command
#define ATCMD_RADIO_CHANNEL			"AT+RF_CHANNEL"
#define ATCMD_RADIO_CHANNEL_HT40		"AT+RF_CHANNEL_HT40"
#define ATCMD_RADIO_RF_START			"AT+RF_START"
#define ATCMD_RADIO_RF_RATE			"AT+RF_RATE"
#define ATCMD_RADIO_RF_PACKET_LEN	"AT+RF_PACKET_LEN"
#define ATCMD_RADIO_RF_STOP			"AT+RF_STOP"
#define ATCMD_RADIO_RF_RESET			"AT+RF_RESET"
#define ATCMD_RADIO_RF_COUNT			"AT+RF_COUNT"
#define ATCMD_RADIO_RF_RSSI			"AT+RF_RSSI"
#if BLE_EN
#define ATCMD_RADIO_BLE_CHANNEL			"AT+RF_BLE_CHANNEL"
#define ATCMD_RADIO_RF_BLE_START			"AT+RF_BLE_START"
#define ATCMD_RADIO_RF_BLE_RATE			"AT+RF_BLE_RATE"
#define ATCMD_RADIO_RF_BLE_STOP			"AT+RF_BLE_STOP"
#define ATCMD_RADIO_RF_BLE_RESET			"AT+RF_BLE_RESET"
#define ATCMD_RADIO_RF_BLE_COUNT			"AT+RF_BLE_COUNT"
#endif
#define ATCMD_RADIO_RF_READ_TEMPCS	"AT+RF_READ_TEMPCS"
#define ATCMD_RADIO_RF_ENABLE_TCSR	"AT+RF_ENABLE_TCSR"
#define ATCMD_RADIO_RF_BANDGAIN		"AT+RF_2GBAND_GAIN"
//#define ATCMD_RADIO_RF_GAIN			"AT+RF_GAIN"
#define ATCMD_RADIO_RF_RATEGAIN		"AT+RF_RATE_GAIN"
#define ATCMD_RADIO_RF_DUMP			"AT+RF_DUMP"
#define ATCMD_RADIO_RF_SINGLE_TONE     "AT+RF_TONE_GEN"
#define ATCMD_RF             			       "rf"

//rf tune
#define ATCMD_RF_CALI_DPD			"AT+RF_CALI_DPD"
#define ATCMD_RF_MANU_DPD			"AT+RF_MANU_DPD"
#define ATCMD_RF_FREQOFFSET			"AT+RF_FREQOFFSET"
#define ATCMD_RF_FREQOFFSET_READXO			"AT+RF_FREQOFFSET_READXO"
#define ATCMD_RF_FREQOFFSET_READXI			"AT+RF_FREQOFFSET_READXI"
//#define ATCMD_RADIO_RF_2GPA1			"AT+RF_2GPA1"
//#define ATCMD_RADIO_RF_2GPA2		"AT+RF_2GPA2"
//#define ATCMD_RADIO_RF_2GPA3		"AT+RF_2GPA3"
//#define ATCMD_RADIO_RF_2GPABIAS		"AT+RF_2GPABIAS"
//#define ATCMD_RADIO_RF_2GPACELL	       "AT+RF_2GPACELL"
//#define ATCMD_RADIO_RF_2GPACAP		"AT+RF_2GPACAP"
#define ATCMD_RADIO_RF_LDO			"AT+RF_LDO"
#define ATCMD_RADIO_RF_DCDC		"AT+RF_DCDC"
#define ATCMD_RADIO_RF_DCDCV		"AT+RF_DCDCV"
#define ATCMD_RADIO_RF_DLDOV		"AT+RF_DLDOV"
#define ATCMD_RADIO_RF_XOLDO	       "AT+RF_XOLDO"
#define ATCMD_RADIO_RF_RXPAD_CH13	       "AT+RF_RXPAD_CH13"


//rf flash write 
#define ATCMD_RADIO_TEMP_BOUNDARY	"AT+RF_TEMP_BOUNDARY"
#define ATCMD_RF_TABLE_HT			"AT+RF_TABLE_HT"
#define ATCMD_RF_TABLE_RT			"AT+RF_TABLE_RT"
#define ATCMD_RF_TABLE_LT			"AT+RF_TABLE_LT"
#if BLE_EN
#define ATCMD_RF_BLE_TABLE_HT         "AT+RF_BLE_TABLE_HT"
#define ATCMD_RF_BLE_TABLE_RT         "AT+RF_BLE_TABLE_RT"
#define ATCMD_RF_BLE_TABLE_LT         "AT+RF_BLE_TABLE_LT"
#endif


#define ATCMD_RF_TABLE_GAIN			"AT+RF_TABLE_GAIN"
#define ATCMD_RF_TABLE_BRATE_GAIN			"AT+RF_TABLE_BRATE_GAIN"
#define ATCMD_RF_TABLE_GRATE_GAIN			"AT+RF_TABLE_GRATE_GAIN"
#define ATCMD_RF_TABLE_20NRATE_GAIN			"AT+RF_TABLE_20NRATE_GAIN"
#define ATCMD_RF_TABLE_40NRATE_GAIN			"AT+RF_TABLE_40NRATE_GAIN"
#define ATCMD_RF_TABLE_DCDC			        "AT+RF_TABLE_DCDC"
#define ATCMD_RF_TABLE_TX_LOWPOWER			"AT+RF_TABLE_TX_LOWPOWER"
#define ATCMD_RF_TABLE_EXTPADPD             "AT+RF_TABLE_EXTPADPD"
#define ATCMD_RF_TABLE_EXTPADPD_SET         "AT+RF_TABLE_EXTPADPD_SET"
#define ATCMD_RF_TABLE_PADPD_GET         "AT+RF_TABLE_PADPD_GET"

#define ATCMD_RF_TABLE_EXTPA            "AT+RF_TABLE_EXTPA"
#define ATCMD_RF_EXTPA_EN		"AT+RF_EXTPA_EN"
#define ATCMD_RF_EXTPA_STATUS   	"AT+RF_EXTPA_STATUS"
#define ATCMD_RF_AUTOLNA_EN		"AT+RF_AUTOLNA_EN"
#define ATCMD_RF_SET_EXTLNA		"AT+RF_SET_EXTLNA"

#define ATCMD_RF_5G_BB_SCALE 	                            "AT+RF_5G_BB_SCALE"
#define ATCMD_RF_5G_BIAS1                            	"AT+RF_5G_BIAS1"
#define ATCMD_RF_5G_BIAS2                             	"AT+RF_5G_BIAS2"

#define ATCMD_RF_5GTABLE_HT 	                            "AT+RF_5GTABLE_HT"
#define ATCMD_RF_5GTABLE_RT                             	"AT+RF_5GTABLE_RT"
#define ATCMD_RF_5GTABLE_LT                             	"AT+RF_5GTABLE_LT"
#define ATCMD_RF_5GTABLE_BIAS1                             	"AT+RF_5GTABLE_BIAS1"
#define ATCMD_RF_5GTABLE_BIAS2                             	"AT+RF_5GTABLE_BIAS2"
#define ATCMD_RF_5GTABLE_BAND_THRESHOLD 	"AT+RF_5GTABLE_BAND_THRESHOLD"
#define ATCMD_RF_WORK_MODE       "AT+RF_WORK_MODE"

#endif
