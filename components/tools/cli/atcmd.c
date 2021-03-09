
//standard libary include
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "soc_types.h"
#include "atcmd.h"
#include "error.h"
#include "Cabrio-conf.h"

#include "atcmd_general.h"
#include "atcmd_gpio.h"
#include "atcmd_socket.h"
#include "atcmd_wifi.h"

#if BLE_GAP_ATCMD_EN
#include "atcmd_ble.h"
#endif
#if defined(SETTING_BLE_UART) && (SETTING_BLE_UART == 1)
#include "atcmd_ble_uart.h"
#endif

#if MESH_BLE_EN
#include "atcmd_ble_mesh.h"
#endif

#include "toolbox.h"

#include "cli.h"
#include "wifi_api.h"
#include "ssv_lib.h"

#if defined(SUPPORT_PARTITION_CFG_TABLE)
#include "atcmd_cfg.h"
#endif


extern const at_cmd_info atcmd_homekit_tbl[];

extern s32 host_cmd_log_write(const char* fmt, ...);
void At_RespOK (char* pStr)
{
	char szResp[64] = {0};
	int len = strlen(pStr);
	if( *(pStr+len-1) == '?' && *(pStr+len-2) == '=' )
		len-=2;
	else if( *(pStr+len-1) == '=' )
		len-=1;
	memcpy(szResp, pStr, len);
	//ATCMD_LOG_I("%s=OK\n", szResp);
    ATCMD_LOG_I("%s=", szResp);
    ATCMD_LOG_I("OK\n");
}

int parseBuff2Param(char* bufCmd, stParam* pParam, uint8_t maxargu)
{
	int buflen, i;
	const char delimiters = ',';

    buflen = strlen (bufCmd);
	if (strlen (bufCmd) == 0)
		return ERROR_INVALID_PARAMETER;

    if(maxargu == 0)
        maxargu = MAX_ARGUMENT;

    pParam->argc = 1;
    pParam->argv[pParam->argc - 1] = &bufCmd[0];
    i = 0;
    while(pParam->argc < maxargu)
    {
        for(; i < buflen ; i++)
        {
            if(bufCmd[i] == delimiters)
            {
                bufCmd[i] = 0;
                break;
            }
        }
        if(i == buflen)
			break;
        if(bufCmd[i + 1] != 0)
        {
            pParam->argc += 1;
            pParam->argv[pParam->argc - 1] = &bufCmd[i + 1];
        }
        else
            break;
    }

	return 0;
}


int At_dtimperoid(stParam *param)
{
    u32 val=0;
    if (param->argc == 1)
    {
        val = strtoul(param->argv[0], NULL, 10);
        if(val < 0xFF)
        {
            set_user_dtim_period((u8)val);
            return ERROR_SUCCESS;
        }
        else
            return ERROR_INVALID_PARAMETER;
    }
    else
        return ERROR_INVALID_PARAMETER;
}

const at_cmd_info atcmdicomm_info_tbl[] =
{
    {ATCMD_LIST,      At_CmdList,      0},
//#ifdef ATCMD_GENERAL_EN
    {ATCMD_REBOOT ,            At_Reboot,             0},
    {ATCMD_VERSION,            At_GetVersion,         0},
    {ATCMD_MINFO ,            At_GetManufactureInfo,             0},
    {ATCMD_RADIO_WRITE_MAC1,            At_RadioWriteMAC1,            1},
    {ATCMD_RADIO_READ_MAC1,            At_RadioReadMAC1,            1},
    {ATCMD_RADIO_WRITE_MAC2,            At_RadioWriteMAC2,            1},
    {ATCMD_RADIO_READ_MAC2,            At_RadioReadMAC2,            1},
#if BLE_EN
    {ATCMD_RADIO_WRITE_MAC3,            At_RadioWriteMAC3,            1},
    {ATCMD_RADIO_READ_MAC3,            At_RadioReadMAC3,            1},
#endif


    {ATCMD_EFUSE_READ_MAC,            At_EfuseReadMAC,            1},
    {ATCMD_UART_CONFIG,        At_UartConfig,   4},
    {ATCMD_USER_RAW_CONFIG,            At_UserRaw,           0},
    {ATCMD_POWERSAVE,          At_POWERSAVE,          0},
#if defined(SUPPORT_PARTITION_CFG_TABLE)
    {ATCMD_CFGPARSER,          At_CfgParser,            0},
    {ATCMD_CFG_TESTER,          At_CfgTester,            0},
    {ATCMD_CFG_MAC_TESTER,          At_CfgWifiTester,            0},
#endif

#if defined(SUPPORT_UASCENT_USER_CFG)
	{ATCMD_USER_FLASH,			At_User_Flsh,		0},
#endif
    //{ATCMD_TEST_PERIPHERAL,    At_TEST_PERIPHERAL,    0},
    {ATCMD_SYSINFO,            At_SYSINFO,            0},
    {ATCMD_ILOG_LEVEL,         At_ilog_set_level,     0},
    {ATCMD_ILOG_TSAK,          At_ilog_set_task,      0},
#if defined(SUPPORT_FFS)
    {ATCMD_FSINFO,             At_FSINFO,             0},
    {ATCMD_FSINFO_PERSONAL,    At_FSINFO_personal,    0},
    {ATCMD_FSRESET,            At_FSRESET,            0},
#endif
    {ATCMD_MEMINFO,            At_MEMINFO,            0},
    {ATCMD_MEMDUMP,            At_MEMDUMP,            2},
    {ATCMD_WRITE_REG,          At_WriteReg32,         0},
    {ATCMD_READ_REG,           At_ReadReg32,          2},
//#endif  //ATCMD_GENERAL_EN

//#ifdef ATCMD_WIFI_EN
    {ATCMD_DUT_START,          At_DUTSTART,      0},
    {ATCMD_NETSCAN,            At_NetScan,            0},
    {ATCMD_SETWIFICONFIG,      At_SetWifiConfig,      0},
    {ATCMD_SETIFCONFIG ,            At_SetIfConfigure,             0},
    {ATCMD_CONNECT,            At_Connect,            0},
    {ATCMD_DISCONNECT,         At_Disconnect,         0},
    {ATCMD_GETCONFIG,      At_GetConfigure,      0},
    {ATCMD_NETSTATUS ,            At_GetNetStatus,             0},
    {ATCMD_SHOWALLAP,          At_ShowAllAP,          0},
    {ATCMD_SHOWCONNECTAP,      At_ShowConnectAP,      0},
    {ATCMD_CONNECT_ACTIVE,          At_ConnectActive,      0},
    {ATCMD_SET_AUTO_CONNECT,      At_SetAutoConnect,      1},
#if(SOFTAP_EN==1)
    {ATCMD_AP,                 At_AP,                 0},
    {ATCMD_AP_EXIT,            At_AP_EXIT,            0},
    {ATCMD_SET_AP_HIDDENID,    At_SET_AP_HIDDENID,    0},
    {ATCMD_SET_APCONFIG,       At_SET_APCONFIG,       0},
    {ATCMD_GET_APCONFIG,       At_GET_APCONFIG,       0},
    {ATCMD_GET_APMODE,         At_GET_APMODE,         0},
    {ATCMD_LIST_STA,         At_ListStation,         0},
    {ATCMD_KICK_STA,               At_KickStation,               0},
#endif
#if(WIFI_REPEATER_EN==1)
    {ATCMD_SET_REPTCONFIG,     At_SET_REPTCONFIG,     0},
#endif
    {ATCMD_SET_COUNTRY_CODE,      At_CmdSetCountryCode,      0},
    {ATCMD_NETSCAN_HIDDEN,            At_NetScanHidden,            0},

    {ATCMD_SETWIFICONFIG2,      At_SetWifiConfig2,      0},
    {ATCMD_SETIFCONFIG2 ,            At_SetIfConfigure2,             0},
    {ATCMD_CONNECT2,            At_Connect2,            0},
    {ATCMD_DISCONNECT2,         At_Disconnect2,         0},
    {ATCMD_NETSTATUS2 ,            At_GetNetStatus2,             0},
    {ATCMD_ICMP_BASERATE,       At_icmp_baserate,         0},
    {ATCMD_24G_HT40,            At_24g_HT40,         0},
    {ATCMD_CCI_ENABLE,          At_cci_enable,         0},
#if(ENABLE_HK==1)
    {ATCMD_HKAP,               At_HKAP,               0},
#endif
    //check ATCMD_WPS
    {ATCMD_MAC_HW_QUEUE,       At_MacHWQueue,         0},
    {ATCMD_MAC_HW_MIB,         At_MacHWMIB,         0},
    {ATCMD_AMPDU_MIB,          At_AMPDUMIB,           0},
    {ATCMD_PHY_HWINFO,         At_PhyHWInfo,         4},
    {ATCMD_RCINFO,             At_RCINFO,             0},
    {ATCMD_RC_MASK,            At_RCMASK,             0},
    {ATCMD_RC_FIXRATE,       At_fixrate,            0},
#if 0 //AMPDU_RX_EN
    {ATCMD_AMPDURX_INFO,       At_AMPDURX_INFO,         0},
#endif
    {ATCMD_NOW_TEST,            At_TestNow,             0},
    {ATCMD_SETTXQCONFIG,        At_SetTxQConfig,        2},
    {ATCMD_SETAMPDUCONFIG,      At_SetAmpduConfig,      3},
    {ATCMD_DBGQUEUESTAT,        At_DbgQueueStat,        2},
#if CSI_EN
    {ATCMD_CSI_CONFIG_B,        At_CsiConfigB,          3},
    {ATCMD_CSI_CONFIG_GN,       At_CsiConfigGN,         3},
#endif
#if LWIP_MEMP_DEBUG_EN
    {ATCMD_TCPIP_STATUS,        At_TcpipStatus,         2},
#endif
    //check ATCMD_MAC_DBG
    //check ATCMD_SET_APCONFIG_2
    //check ATCMD_SET_REPTCONFIG
    //cehck ATCMD_REPT_IP_MAC_TBL
//#endif   //ATCMD_WIFI_EN

#ifdef TCPIPSTACK_EN
    {ATCMD_TCPCONNECT,         At_TCPConnect,         0},
    {ATCMD_TCPSEND,            At_TCPSend,            2},
    {ATCMD_TCPDISCONNECT,      At_TCPDisconnect,      0},
    {ATCMD_TCPLISTEN,          At_TCPListen,          0},
    {ATCMD_TCPUNLISTEN,        At_TCPUnlisten,        0},
    {ATCMD_MESHCOEXTEST,       At_MeshCoexTest,        0},
    {ATCMD_MESHCOEXCONNECT,       At_MeshCoexConnect,        0},

    {ATCMD_UDPCREATE,          At_UDPCreate,          0},
    {ATCMD_UDPSEND,            At_UDPSend,            4},
    {ATCMD_UDPCLOSE,           At_UDPClose,           0},
    {ATCMD_NSLOOKUP,           At_NSLookup,           1},
    {ATCMD_SNTP_SYNC,           At_SNTPSync,           0},
    {ATCMD_SNTP_TIME,           At_SNTPTime,           0},
    {ATCMD_IPERF,    		   At_IPERF,              0},
    {ATCMD_PING,               At_Ping,               0},
    {ATCMD_REMBERIP,               At_RemberIP,               0},
#ifdef JD_CLOUD_EN
    {ATCMD_JD_DEVICE_REMOVE,       At_JDDeviceRemove,       0},
    {ATCMD_JD_START,        At_JDStart,        0},
#endif
#if (LWIP_IPV6==1)
    {ATCMD_TCPSEND6,            At_TCPSend6,            2},
    {ATCMD_TCPLISTEN6,          At_TCPListen6,          0},
#endif
#ifdef MBEDTLS_EN
    //{ATCMD_SSLTEST,            At_SSLTest,            0},//modify by hua
#endif
#ifdef SMARTCONFIG_EN
    {ATCMD_SMARTCONFIG,      At_SmartConfig,      0},
#endif
#if defined(FOTA_OPTION) && (FOTA_OPTION != 0)
    {ATCMD_OTASETSERVER,       At_OTASetServer,       0},
    {ATCMD_OTASETPARAM,        At_OTASetParam,        0},
    {ATCMD_OTASTART,           At_OTAStart,           0},
    {ATCMD_OTASTOP,            At_OTAStop,           0},
    {ATCMD_OTAREBOOT,          At_OTAReboot,          0},
#endif

#endif   //TCPIPSTACK_EN

    {ATCMD_RF,            At_ShowRfCommand,            0},
#if(CHIP_ID == 6006) || (CHIP_ID==6020)
    {ATCMD_RADIO_RF_START,            At_RadioRFStart,            2},
    {ATCMD_RADIO_CHANNEL,            At_RadioChannel,            0},
    {ATCMD_RADIO_CHANNEL_HT40,            At_RadioChannelHT40,            0},
    {ATCMD_RADIO_RF_RATE,            At_RadioRFRate,            1},
    {ATCMD_RADIO_RF_PACKET_LEN,            At_RadioRFPacketLen,            1},
    {ATCMD_RADIO_RF_BANDGAIN,            At_RadioRFBandGain,            1},
    //{ATCMD_RADIO_RF_GAIN,            At_RadioRFGain,            1},
    {ATCMD_RADIO_RF_RATEGAIN,            At_RadioRFRateGain,            2},
    {ATCMD_RADIO_RF_READ_TEMPCS,            At_RadioRFReadTempcs,            0},
    {ATCMD_RADIO_RF_STOP,            At_RadioRFStop,            0},
    {ATCMD_RADIO_RF_RESET,            At_RadioRFReset,            0},
    {ATCMD_RADIO_RF_COUNT,            At_RadioRFCount,            1},
    {ATCMD_RADIO_RF_RSSI,            At_RadioRFRSSI,            0},
#if BLE_EN
    {ATCMD_RADIO_RF_BLE_START,            At_RadioRFBleStart,            4},
    {ATCMD_RADIO_BLE_CHANNEL,            At_RadioBleChannel,            0},
    {ATCMD_RADIO_RF_BLE_RATE,            At_RadioRFBleRate,            1},
    {ATCMD_RADIO_RF_BLE_STOP,            At_RadioRFBleStop,            0},
    {ATCMD_RADIO_RF_BLE_RESET,            At_RadioRFBleReset,            0},
    {ATCMD_RADIO_RF_BLE_COUNT,            At_RadioRFBleCount,            0},
#endif
    {ATCMD_RADIO_RF_ENABLE_TCSR,   At_RadioEnableTCSR,     1},
    {ATCMD_RADIO_RF_DUMP,            At_RadioRFDump,            0},

    {ATCMD_RF_CALI_DPD,            At_RfCaliDPD,            1},
    {ATCMD_RF_MANU_DPD,            At_RfManuDPD,            0},
    {ATCMD_RF_FREQOFFSET,            At_RadioRFFreqoffset,            2},
    {ATCMD_RF_FREQOFFSET_READXO,            At_RadioRFFreqoffset_readxo,            0},
    {ATCMD_RF_FREQOFFSET_READXI,            At_RadioRFFreqoffset_readxi,            0},

    //{ATCMD_RADIO_RF_2GPA1,            At_RadioRF2Gpa1,            1},
    //{ATCMD_RADIO_RF_2GPA2,            At_RadioRF2Gpa2,            1},
    //{ATCMD_RADIO_RF_2GPA3,            At_RadioRF2Gpa3,            1},
    //{ATCMD_RADIO_RF_2GPABIAS,            At_RadioRF2GpaBias,            1},
    //{ATCMD_RADIO_RF_2GPACELL,            At_RadioRF2GpaCell,            1},
    //{ATCMD_RADIO_RF_2GPACAP,            At_RadioRF2GpaCap,            1},

    {ATCMD_RADIO_RF_LDO,            At_RadioRFLdo,            1},
    {ATCMD_RADIO_RF_DCDC,            At_RadioRFDcdc,            1},
    {ATCMD_RADIO_RF_DCDCV,            At_RadioRFDcdcv,            1},
    {ATCMD_RADIO_RF_DLDOV,            At_RadioRFDldov,            1},
    {ATCMD_RADIO_RF_XOLDO,            At_RadioRFXoldo,            1},
    {ATCMD_RADIO_RF_RXPAD_CH13,            At_RadioRFRxPadCh13,            1},

    {ATCMD_RADIO_TEMP_BOUNDARY,            At_RadioRFTempBoundary,            2},
    {ATCMD_RF_TABLE_RT,            At_RfTableRT,            18},
    {ATCMD_RF_TABLE_HT,            At_RfTableHT,            18},
    {ATCMD_RF_TABLE_LT,            At_RfTableLT,            18},
#if BLE_EN
    {ATCMD_ENBLEMODE,            At_EnableBleMode,            2},
    {ATCMD_RF_BLE_TABLE_RT,            At_Rf_BleTableRT,            2},
    {ATCMD_RF_BLE_TABLE_HT,            At_Rf_BleTableHT,            2},
    {ATCMD_RF_BLE_TABLE_LT,            At_Rf_BleTableLT,            2},
#endif
    {ATCMD_RF_TABLE_GAIN,            At_RfTableGain,            18},
    {ATCMD_RF_TABLE_BRATE_GAIN,            At_RfTableBRateGain,            1},
    {ATCMD_RF_TABLE_GRATE_GAIN,            At_RfTableGRateGain,            4},
    {ATCMD_RF_TABLE_20NRATE_GAIN,            At_RfTable20NRateGain,            4},
    {ATCMD_RF_TABLE_40NRATE_GAIN,            At_RfTable40NRateGain,            4},
    {ATCMD_RF_TABLE_DCDC,            At_RfTableDcdc,            1},
    {ATCMD_RF_TABLE_TX_LOWPOWER,            At_RfTableTxlowpower,            1},
    {ATCMD_RF_TABLE_EXTPADPD,               At_RfTableExtpadpd,              1},
    {ATCMD_RF_TABLE_EXTPADPD_SET,           At_RfTableExtpadpd_setting,      59},
    {ATCMD_RF_TABLE_PADPD_GET,           At_RfTablePadpd_get,      0},

#if EXTPA_EN
    {ATCMD_RF_TABLE_EXTPA,         At_RfTableExtpa,         7},
    {ATCMD_RF_EXTPA_EN,            At_RfExtpaEn,            0},
    {ATCMD_RF_EXTPA_STATUS,        At_RfExtpaStatus,        0},
    {ATCMD_RF_AUTOLNA_EN,          At_RfAutoLnaEn,          0},
    {ATCMD_RF_SET_EXTLNA,          At_RfSetExtLNA,          0},
#endif
#if(CHIP_ID==6006)
    {ATCMD_RF_5G_BB_SCALE,            At_Rf5GBBScale,            0},
    {ATCMD_RF_5G_BIAS1,            At_Rf5GBias1,            0},
    {ATCMD_RF_5G_BIAS2,            At_Rf5GBias2,            0},

    {ATCMD_RF_5GTABLE_RT,            At_Rf5GTableRT,            0},
    {ATCMD_RF_5GTABLE_HT,            At_Rf5GTableHT,            0},
    {ATCMD_RF_5GTABLE_LT,            At_Rf5GTableLT,            0},
    {ATCMD_RF_5GTABLE_BIAS1,            At_Rf5GTableBIAS1,            0},
    {ATCMD_RF_5GTABLE_BIAS2,            At_Rf5GTableBIAS2,            0},
    {ATCMD_RF_5GTABLE_BAND_THRESHOLD,            At_Rf5GBandThreshold,            0},
#endif
    {ATCMD_RADIO_RF_SINGLE_TONE,            At_RfSingleTone,            0},
    {ATCMD_RF_WORK_MODE,                         At_RfWorkMode,            0},
#endif

//#ifdef ATCMD_GPIO_EN
    {ATCMD_SET_GPIO_TRI_STATE, At_SetGpioTriState,    0},
    {ATCMD_SET_GPIO_DIR, At_SetGpioDir,    0},
    {ATCMD_SET_GPIO_LOGIC,     At_SetGpioLogic,       0},
    {ATCMD_SET_GPIO_PULL,      At_SetGpioPull,        0},
    {ATCMD_READ_GPIO,          At_ReadGpio,           0},
    {ATCMD_SET_GPIO_INT,       At_SetGpioInt,         0},
#if defined(SUPPORT_PERIPHERAL_PWM) && (SUPPORT_PERIPHERAL_PWM==1)
    {ATCMD_SET_PWM,            At_SetPWM,             0},
    {ATCMD_SET_PWM_DISABLE,    At_SetPWMDisable,      0},
    {ATCMD_SET_PWM_ENABLE,     At_SetPWMEnable,       0},
    {ATCMD_SET_PWM_RECONFIG,   At_SetPWMReconfig,     0},
#endif
//#endif  //ATCMD_GPIO_EN
    {ATCMD_SNIFFER,            At_Sniffer,           3},
    {ATCMD_MGMT_WATCH,         At_mgmt_watch,           0},
#if defined(SUPPORT_LOW_POWER) && (SUPPORT_LOW_POWER == 1)
    {ATCMD_GPIO_WAKEUP       , At_gpio_wakeup, 2},       //GPIO INT with PMU wakeup
    {ATCMD_POWERMODE         , At_power_mode, 1},
    {ATCMD_POWERCONF         , At_power_conf, 3},
    {ATCMD_SETDTIMPERIOD     , At_dtimperoid, 1},
    {ATCMD_DORMANT           , At_dormant, 2},
#endif

#if defined(SETTING_BLE_UART) && (SETTING_BLE_UART == 1)
    {ATCMD_BLE_UART_START    , At_ble_uart_init, 0},
    {ATCMD_BLE_UART_TX       , At_ble_uart_send, 1},
#endif
#if BLE_GAP_ATCMD_EN
    {ATCMD_BLEINIT              , At_ble_init, 0},
    {ATCMD_BLESETSCANPARAMS     , At_ble_set_scan_params, 6},
    {ATCMD_BLESTARTSCAN         , At_ble_start_scan, 1},
    {ATCMD_BLEADVSTART          , At_ble_start_adv, 0},
    {ATCMD_BLEDISCONNECT        , At_ble_disconnect, 0},
#endif
#if BLE_GATTS_ATCMD_EN
    {ATCMD_BLEADDSERVICE         , At_ble_add_service, 0},
    {ATCMD_BLESENDINDICATION     , At_ble_send_indication, 6},
#endif
#if BLE_GATTC_ATCMD_EN
    {ATCMD_BLEGATTCOPEN         , At_ble_gattc_open, 4},
    {ATCMD_BLEGATTCWRITECHAR         , At_ble_gattc_write_char, 7},
#endif
#if MESH_BLE_EN
    {ATCMD_BMGPIO             , At_bmreg, 1},
    {ATCMD_BMREG             , At_bmreg, 1},
    {ATCMD_BMOOB             , At_bmoob, 15},
    {ATCMD_BMINIT            , At_bminit, 7},
    {ATCMD_BMTXPOWER         , At_bmtxpower, 4},
    {ATCMD_BMNBEARER         , At_bmnbearer, 5},

    {ATCMD_BMSTCORELOAD      , At_bmstcoreload, 1},
    {ATCMD_BMSTCORECOMMIT    , At_bmstcoreci, 1},
    {ATCMD_BMLOGLVL          , At_bmloglvl, 3},
    {ATCMD_BMPRIMARYADDR          , At_bmprimaryaddr, 1},
    {ATCMD_BMSETSCANWIN          , At_bmsetscanwin, 3},
#if CONFIG_PERFORMANCE_CLIENT_MODEL
    {ATCMD_BMTPCVM           , At_bmtpcvm, 19},
#endif
    {ATCMD_BMGOCM            , At_bmgocm, 23},

    {ATCMD_BMTPCVM           , At_bmtpcvm, 19},
    {ATCMD_BMGOCM            , At_bmgocm, 23},
    {ATCMD_BMVMCM            , At_bmvmcm, 21},
#if CONFIG_BLE_MESH_PROVISIONER
    {ATCMD_BMPBEARER         , At_bmpbearer, 5},
    {ATCMD_BMPDEV            , At_bmpdev, 15},
    {ATCMD_BMPGETN           , At_bmpgetn, 3},
    {ATCMD_BMPADDN           , At_bmpaddn, 13},
    {ATCMD_BMPBIND           , At_bmpbind, 11},
    {ATCMD_BMPKEY            , At_bmpkey, 9},
#endif
    {ATCMD_BMCCM             , At_bmccm, 25},
    {ATCMD_BMNRESET          , At_bmnreset, 1},
    {ATCMD_BMNSUSPEND          , At_bmnsuspend, 1},
    {ATCMD_BMNRESUME          , At_bmnresume, 1},
#if CONFIG_PERFORMANCE_CLIENT_MODEL
    {ATCMD_BMSPERF           , At_bmsperf, 5},
#endif
    {ATCMD_BMNNWK            , At_bmnnwk, 15},
    {ATCMD_BMGETPUBLISHACK   , At_bmgetpublishack, 1},
#endif//MESH_BLE_EN
#if defined(BLE_EN) && (BLE_EN == 1)
    {ATCMD_BLEMODE           , At_BLEMode,    0},
#endif
};

int At_CmdList (stParam *param)
{
    int i = 0;
    ATCMD_LOG_I("\r\n");
    int num = sizeof(atcmdicomm_info_tbl)/sizeof(at_cmd_info);
    for(i = 0;i<num;i++)
    {
        if( strncmp(atcmdicomm_info_tbl[i].atCmd, "AT+", strlen("AT+")) == 0 )
            ATCMD_LOG_I("%s\n", atcmdicomm_info_tbl[i].atCmd);
    }

    return ERROR_SUCCESS;
}
int At_ShowRfCommand (stParam *param)
{
    int i = 0;
    ATCMD_LOG_I("\r\n");
    int num = sizeof(atcmdicomm_info_tbl)/sizeof(at_cmd_info);
    for(i = 0;i<num-1;i++)
    {
        if( strncmp(atcmdicomm_info_tbl[i].atCmd, "AT+RF", strlen("AT+RF")) == 0 )
            ATCMD_LOG_I("%s\n", atcmdicomm_info_tbl[i].atCmd);
    }

    return ERROR_SUCCESS;
}

int At_Parser (char *buff, int len)
{
	int i = 0;
	int	nRet = ERROR_UNKNOWN_COMMAND;
    char cmd[MAX_CMD_LEN], operat = 0; //cmd len 32 should be enough
    stParam param;

#if 0
	memset(atcmd_buffer,0 , CLI_BUFFER_SIZE+1);
	memcpy(atcmd_buffer, buff, len);
	buff = atcmd_buffer;
#endif

#if 1
    buff[len] = 0x0;  //chomp!! replace \r\n with null string
    len++;
#endif


    memset(&param, 0, sizeof(stParam));
    if( (1==len) && (buff[0]=='\r' || buff[0]=='\n')){
        nRet = ERROR_SUCCESS;
        goto exit;
    }

	if (0 == len) {
		ATCMD_LOG_I (ATRSP_ERROR, ERROR_INVALID_PARAMETER);
		return ERROR_INVALID_PARAMETER;
	}


    for(i = 0; i < MAX_CMD_LEN; i++)
    {
        if(buff[i] == 0 || buff[i] == '=' || buff[i] == ' ')
        {
            memcpy(cmd, buff, i);
            operat = buff[i];
            cmd[i] = 0;
            break;
        }
    }

    for(i = 0; i < sizeof(atcmdicomm_info_tbl)/sizeof(at_cmd_info); i++)
    {
#if 0
        ATCMD_LOG_I("atCmd = %s\n", atcmdicomm_info_tbl[i].atCmd);
        ATCMD_LOG_I("buff=%s\n",buff);
        ATCMD_LOG_I("cmd=%s\n",cmd);
        ATCMD_LOG_I("strlen=%d\n",strlen(atcmdicomm_info_tbl[i].atCmd));
#endif

        //if(strncmp(atcmdicomm_info_tbl[i].atCmd, cmd, strlen(atcmdicomm_info_tbl[i].atCmd)) == 0)
        if(strcmp(atcmdicomm_info_tbl[i].atCmd, cmd) == 0)
        {
            if(operat != 0)
                parseBuff2Param(buff + strlen(atcmdicomm_info_tbl[i].atCmd) + 1, &param, atcmdicomm_info_tbl[i].maxargu);

            nRet = atcmdicomm_info_tbl[i].pfHandle(&param);
            goto exit_rsp;
        }
    }
#ifdef WAC_EN
    for(i = 0; i < get_atcmd_homekit_size()/sizeof(at_cmd_info); i++)
    {
        if(strncmp(atcmd_homekit_tbl[i].atCmd, cmd, strlen(atcmd_homekit_tbl[i].atCmd)) == 0)
        {
            if(operat != 0)
                parseBuff2Param(buff + strlen(atcmd_homekit_tbl[i].atCmd) + 1, &param, atcmd_homekit_tbl[i].maxargu);
            nRet = atcmd_homekit_tbl[i].pfHandle(&param);
            goto exit_rsp;
        }
    }
#endif


exit_rsp:

    if( ERROR_UNKNOWN_COMMAND == nRet )
    {
       //command not found move cli to print
       //ATCMD_LOG_I (ATRSP_ERROR, nRet);
    }
    else if (ERROR_SUCCESS > nRet)
    {
		ATCMD_LOG_I (ATRSP_ERROR, nRet);
    }
    else if(ERROR_SUCCESS == nRet)
    {
        At_RespOK(cmd);
    }

exit:
	return nRet;
}

#if 1 //AT cmd log to buffer.
#include <stdarg.h>
/* Private API */
#define AT_CMD_LOG_BUFSIZE        (512)

bool _gbAtCmdLogBufEnable = FALSE;
u8 *_gpu8AtCmdLogBuf = NULL;
u32 _gu32AtCmdLogBufSize = 0;
u32 _gu32AtCmdLogBufUsedSize = 0;

static inline s32 _at_cmd_log_buf_remain_size(void)
{
    return (_gu32AtCmdLogBufSize-_gu32AtCmdLogBufUsedSize);
}

static inline u8* _at_cmd_log_buf_alloc(u32 len)
{
    OS_EnterCritical();
    _gpu8AtCmdLogBuf = (u8 *)OS_MemAlloc(len);
    if(NULL != _gpu8AtCmdLogBuf)
    {
        _gu32AtCmdLogBufSize = len;
        memset((void *)_gpu8AtCmdLogBuf, 0, len);
    }
    OS_ExitCritical();
    return _gpu8AtCmdLogBuf;
}

static inline void _at_cmd_log_buf_free(void)
{
    OS_EnterCritical();
    if(NULL != _gpu8AtCmdLogBuf)
    {
        OS_MemFree(_gpu8AtCmdLogBuf);
        _gpu8AtCmdLogBuf = NULL;
        _gu32AtCmdLogBufSize = 0;
        _gu32AtCmdLogBufUsedSize = 0;
    }
    OS_ExitCritical();
}

static inline bool _at_cmd_log_is_enable(void)
{
    bool ret = FALSE;
    OS_EnterCritical();
    if((TRUE == _gbAtCmdLogBufEnable) && (NULL != _gpu8AtCmdLogBuf))
    {
        ret = TRUE;
    }
    OS_ExitCritical();
    return ret;
}

static inline bool _at_cmd_log_buf_init(void)
{
    if(NULL == _at_cmd_log_buf_alloc(AT_CMD_LOG_BUFSIZE))
    {
        ATCMD_LOG_E("allocate atcmd log buffer failed!\n", __FUNCTION__);
        return FALSE;
    }
    return TRUE;
}

static inline bool _at_cmd_log_buf_deinit(void)
{
    _at_cmd_log_buf_free();
    return TRUE;
}

/* Public API */
int at_cmd_log_init(void)
{
    if(NULL == _at_cmd_log_buf_alloc(AT_CMD_LOG_BUFSIZE))
    {
        ATCMD_LOG_E("allocate atcmd log buffer failed!\n", __FUNCTION__);
        return -1;
    }
    return 0;
}

int at_cmd_log_deinit(void)
{
    _at_cmd_log_buf_free();
    return 0;
}

int at_cmd_log_enable(void)
{
    int ret = -1;

    OS_EnterCritical();
    if(NULL != _gpu8AtCmdLogBuf)
    {
        _gbAtCmdLogBufEnable = TRUE;
        ret = 0;
    }
    OS_ExitCritical();

    return ret;
}

int at_cmd_log_disable(void)
{
    int ret = -1;

    OS_EnterCritical();
    _gbAtCmdLogBufEnable = FALSE;
    OS_ExitCritical();
    ret = 0;

    return ret;
}

int at_cmd_log_buf_get(char **buf, unsigned int *buflen)
{
    int ret = -1;

    OS_EnterCritical();
    if((NULL == _gpu8AtCmdLogBuf) || (0 == _gu32AtCmdLogBufSize)
        || (0 == _gu32AtCmdLogBufUsedSize))
    {
        goto EXIT;
    }
    *buf = (char *)_gpu8AtCmdLogBuf;
    *buflen = (unsigned int)_gu32AtCmdLogBufUsedSize;
    ret = 0;

EXIT:
    OS_ExitCritical();
    return ret;
}

int at_cmd_log_write(const char* fmt, ...)
{
    int ret = -1;
    va_list va;

    OS_EnterCritical();
    if((TRUE != _at_cmd_log_is_enable()) || (0 >= _at_cmd_log_buf_remain_size()))
    {
        goto EXIT;
    }

    va_start(va, fmt);
    ret = (s32)vsnprintf((char *)(_gpu8AtCmdLogBuf+_gu32AtCmdLogBufUsedSize), _at_cmd_log_buf_remain_size(), fmt, va);
    va_end(va);

    if(-1 != ret)
    {
        _gu32AtCmdLogBufUsedSize += ret;
    }

EXIT:
    OS_ExitCritical();
    return ret;
}
#endif
