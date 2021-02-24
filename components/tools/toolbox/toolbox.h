#ifndef TOOLBOX_H
#define TOOLBOX_H
#include <stdint.h>
#include "soc_types.h"
#include "phy/rf_api.h"
#include "atcmd.h"

extern struct st_rf_table ssv_rf_table;
int load_rf_table_from_flash();
int save_rf_table_to_flash();
int rf_table_init();

int At_RadioRFStart(stParam *param);
int At_RadioChannel(stParam *param);
#if BLE_EN
int At_EnableBleMode(stParam *param);
int At_RadioRFBleStart(stParam *param);
int At_RadioBleChannel(stParam *param);
int At_RadioRFBleRate(stParam *param);
int At_RadioRFBleStop(stParam *param);
int At_RadioRFBleReset(stParam *param);
int At_RadioRFBleCount(stParam *param);
#endif

int At_RadioChannelHT40(stParam *param);
int At_RadioRFRate(stParam *param);
int At_RadioRFPacketLen(stParam *param);
int At_RadioRFBandGain(stParam *param);
int At_RadioRFGain(stParam *param);
int At_RadioRFRateGain(stParam *param);
int At_RadioRFReadTempcs(stParam *param);
int At_RadioRFStop(stParam *param);
int At_RadioRFReset(stParam *param);
int At_RadioRFCount(stParam *param);
int At_RadioRFRSSI(stParam *param);
int At_RadioEnableTCSR(stParam *param);
int At_RadioRFDump(stParam *param);
int At_RfCaliDPD(stParam *param);
int At_RfManuDPD(stParam *param);
int At_RadioRFFreqoffset(stParam *param);
int At_RadioRFFreqoffset_readxo(stParam *param);
int At_RadioRFFreqoffset_readxi(stParam *param);
int At_RadioRF2Gpa1(stParam *param);
int At_RadioRF2Gpa2(stParam *param);
int At_RadioRF2Gpa3(stParam *param);
int At_RadioRF2GpaBias(stParam *param);
int At_RadioRF2GpaCell(stParam *param);
int At_RadioRF2GpaCap(stParam *param);
int At_RadioRFLdo(stParam *param);
int At_RadioRFDcdc(stParam *param);
int At_RadioRFDcdcv(stParam *param);
int At_RadioRFDldov(stParam *param);
int At_RadioRFXoldo(stParam *param);
int At_RadioRFRxPadCh13(stParam *param);
int At_RadioRFTempBoundary(stParam *param);
int At_RfTableRT(stParam *param);
int At_RfTableHT(stParam *param);
int At_RfTableLT(stParam *param);
int At_Rf_BleTableRT(stParam *param);
int At_Rf_BleTableHT(stParam *param);
int At_Rf_BleTableLT(stParam *param);
int At_RfTableGain(stParam *param);
int At_RfTableBRateGain(stParam *param);
int At_RfTableGRateGain(stParam *param);
int At_RfTable20NRateGain(stParam *param);
int At_RfTable40NRateGain(stParam *param);
int At_RfTableDcdc(stParam *param);
int At_RfTableTxlowpower(stParam *param);
int At_RfTableExtpadpd(stParam *param);
int At_RfTableExtpadpd_setting(stParam *param);
int At_RfTablePadpd_get(stParam *param);
int At_RfTableExtpa(stParam *param);
int At_RfExtpaEn(stParam *param);
int At_RfExtpaStatus(stParam *param);
int At_RfAutoLnaEn(stParam *param);
int At_RfSetExtLNA(stParam *param);

int At_Rf5GBBScale(stParam *param);
int At_Rf5GBias1(stParam *param);
int At_Rf5GBias2(stParam *param);
int At_Rf5GTableRT(stParam *param);
int At_Rf5GTableHT(stParam *param);
int At_Rf5GTableLT(stParam *param);
int At_Rf5GTableBIAS1(stParam *param);
int At_Rf5GTableBIAS2(stParam *param);
int At_Rf5GBandThreshold(stParam *param);
int At_RfSingleTone(stParam *param);
int At_RfWorkMode(stParam *param);



#endif /* end of include guard: TOOLBOX_H */
