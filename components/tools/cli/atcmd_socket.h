#ifndef _ATCMD_SOCKET_H_
#define _ATCMD_SOCKET_H_
#include "atcmd.h"
#include "error.h"

#define ATCMD_TCP_IP_STRING_LEN 64
#define ATCMD_TCP_PORT_STRING_LEN 8

int At_TCPConnect (stParam *param);
int At_TCPSend (stParam *param);
int At_TCPRecvlen (stParam *param);
int At_TCPDisconnect (stParam *param);
int At_TCPListen (stParam *param);
int At_TCPUnlisten (stParam *param);
int At_MeshCoexTest (stParam *param);
int At_MeshCoexConnect (stParam *param);
int At_UDPCreate (stParam *param);
int At_UDPSend (stParam *param);
int At_UDPClose (stParam *param);
int At_NSLookup(stParam *param);
int At_SNTPSync(stParam *param);
int At_SNTPTime(stParam *param);
int At_IPERF(stParam *param);
int At_RemberIP(stParam *param);
char* At_TCPGetConnectIP (stParam *param);
char* At_TCPGetConnectPort (stParam *param);
//#ifdef IPERF_ENABLE
//int At_iperf_main(stParam *param);
//#endif
#ifdef JD_CLOUD_EN
int At_JDDeviceRemove (stParam *param);
int At_JDStart (stParam *param);
#endif
#if (LWIP_IPV6==1) 
int At_TCPSend6 (stParam *param);
int At_TCPListen6(stParam *param);
#endif
#ifdef MBEDTLS_EN
int At_SSLTest(stParam *param);
#endif
#ifdef SMARTCONFIG_EN
int At_SmartConfig(stParam *param);
#endif

#if defined(FOTA_OPTION) && (FOTA_OPTION != 0)
int At_OTASetServer (stParam *param);
int At_OTASetParam (stParam *param);
int At_OTAStart (stParam *param);
int At_OTAStop (stParam *param);
int At_OTAReboot (stParam *param);
#endif



#endif  //_ATCMD_SOCKET_H_
