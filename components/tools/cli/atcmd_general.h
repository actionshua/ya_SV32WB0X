#ifndef _ATCMD_GENERAL_H_
#define _ATCMD_GENERAL_H_
#include "atcmd.h"
#include "error.h"


int At_Reboot (stParam *param);
int At_GetVersion (stParam *param);
int At_GetManufactureInfo (stParam *param);
int At_RadioWriteMAC1(stParam *param);
int At_RadioReadMAC1(stParam *param);
int At_RadioWriteMAC2(stParam *param);
int At_RadioReadMAC2(stParam *param);
#if BLE_EN
int At_RadioWriteMAC3(stParam *param);
int At_RadioReadMAC3(stParam *param);
#endif
int At_EfuseEnableWrite(stParam *param);
int At_EfuseWriteMAC(stParam *param);
int At_EfuseReadMAC(stParam *param);
int At_EfuseDump(stParam *param);
int At_UartConfig (stParam *param);
int At_UserRaw(stParam *param);
int At_POWERSAVE (stParam *param);
#if defined(SUPPORT_UASCENT_USER_CFG)
int At_User_Flsh(stParam *param);
#endif
int At_SYSINFO(stParam *param);
int At_ilog_set_level(stParam *param);
int At_ilog_set_task(stParam *param);
int At_FSINFO(stParam *param);
int At_FSINFO_personal(stParam *param);
int At_FSRESET(stParam *param);
int At_MEMINFO(stParam *param);
int At_MEMDUMP(stParam *param);
int At_WriteReg32 (stParam *param);
int At_ReadReg32 (stParam *param);

#if defined(SUPPORT_LOW_POWER) && (SUPPORT_LOW_POWER == 1)
int At_gpio_wakeup(stParam *param);
int At_power_mode(stParam *param);
int At_power_conf(stParam *param);
int At_dormant(stParam *param);
#endif
int At_sleep(stParam *param);

#endif  //_ATCMD_GENERAL_H_
