#ifndef _ATCMD_BLE_MESH_H_
#define _ATCMD_BLE_MESH_H_
#include "atcmd.h"
#include "error.h"

int At_bmreg(stParam *param);
int At_bmoob(stParam *param);
int At_bminit(stParam *param);
int At_bmnbearer(stParam *param);
int At_bmtxpower(stParam *param);
int At_bmtpcvm(stParam *param);
int At_bmgocm(stParam *param);
int At_bmvmcm(stParam *param);
int At_bmpdev(stParam *param);
int At_bmpgetn(stParam *param);
int At_bmpaddn(stParam *param);
int At_bmpbind(stParam *param);
int At_bmpkey(stParam *param);
int At_bmccm(stParam *param);
int At_bmnreset(stParam *param);
int At_bmsperf(stParam *param);
int At_bmnnwk(stParam *param);
int At_bmpbearer(stParam *param);
int At_bmgetpublishack(stParam *param);
int At_bmstcoreload(stParam *param);
int At_bmstcoreci(stParam *param);//ci is commit
int At_bmloglvl(stParam *param);
int At_bmnsuspend(stParam *param);
int At_bmnresume(stParam *param);
int At_bmprimaryaddr(stParam *param);
int At_bmsetscanwin(stParam *param);
#endif  //_ATCMD_BLE_MESH_H_
