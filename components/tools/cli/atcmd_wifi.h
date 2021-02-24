#ifndef _ATCMD_WIFI_H_
#define _ATCMD_WIFI_H_
#include "atcmd.h"
#include "error.h"

int At_DUTSTART (stParam *param);
int At_NetScan (stParam *param);
int At_SetWifiConfig (stParam *param);
int At_SetIfConfigure (stParam *param);
int At_Connect (stParam *param);
int At_Disconnect (stParam *param);
int At_GetConfigure (stParam *param);
int At_GetNetStatus (stParam *param);
int At_ShowAllAP (stParam *param);
int At_ShowConnectAP (stParam *param);
int At_ConnectActive (stParam *param);
int At_SetAutoConnect(stParam *param);
int At_AP (stParam *param);
int At_AP_EXIT (stParam *param);
int At_SET_REPTCONFIG (stParam *param);
int At_SET_AP_HIDDENID(stParam *param);
int At_SET_APCONFIG (stParam *param);
int At_GET_APCONFIG (stParam *param);
int At_GET_APMODE (stParam *param);
int At_CmdSetCountryCode(stParam *param);
int At_ListStation (stParam *param);
int At_KickStation (stParam *param);
int At_NetScanHidden (stParam *param);

int At_SetWifiConfig2 (stParam *param);
int At_SetIfConfigure2 (stParam *param);
int At_Connect2 (stParam *param);
int At_Disconnect2 (stParam *param);
int At_GetNetStatus2 (stParam *param);
int At_HKAP(stParam *param);
int At_Ping(stParam *param);
int At_Sniffer(stParam *param);
int At_fixrate(stParam *param);
int At_mgmt_watch(stParam *param);
int At_TestNow(stParam *param);
int At_SetTxQConfig(stParam *param);
int At_SetAmpduConfig(stParam *param);
#if CSI_EN
int At_CsiConfigB(stParam *param);
int At_CsiConfigGN(stParam *param);
#endif
int At_MacHWQueue(stParam *param);
int At_PhyHWInfo(stParam *param);
int At_MacHWMIB(stParam *param);
int At_RCMASK(stParam *param);
int At_RCINFO(stParam *param);
int At_TcpipStatus(stParam *param);
int At_AMPDUMIB(stParam *param);
int At_DbgQueueStat(stParam *param);
int At_BLEMode(stParam *param);
int At_icmp_baserate(stParam *param);
int At_24g_HT40(stParam *param);
int At_cci_enable(stParam *param);

#endif  //_ATCMD_WIFI_H_
