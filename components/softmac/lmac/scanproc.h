#ifndef _SCANPROC_H_
#define _SCANPROC_H_

#include "wificonf.h"

typedef enum en_mgmt_scan_op
{
    E_MGMT_SCAN_OP_NONE = 0,
    E_MGMT_SCAN_OP_INIT,
    E_MGMT_SCAN_OP_WAIT_ACK,
    E_MGMT_SCAN_OP_RECV_ACK,
    E_MGMT_SCAN_OP_EXIT,
    E_MGMT_SCAN_OP_MAX
}EN_MGMT_SCAN_OP;

typedef struct HOME_CHANNEL_INFO {
	u8 channel;
	u8 bandwidth;
} HOME_CHANNEL_INFO;

typedef struct SCAN_SEQ_ARGS {
    u8 channel;
    u8 dfs;
} SCAN_SEQ_ARGS;

typedef struct _AT_SCAN_PRIV_ARGS {
    void (*preproc)(void *);
    void (*postproc)(void *);
    s32 (*txnulldata)(u8);
    s32 (*txprobereq)(void *);
    void (*callbackfn)(void *);
    SCAN_SEQ_ARGS scan_seq[MAX_AVAIL_CHANNEL];
    HOME_CHANNEL_INFO chinfo;
    bool online_scan;       ///< Enable/Disable online scan mode.    u8 probe_req_period;
    u16 scantime_in_ms;
    u16 staytime_in_ms;     ///< Stay time in ms after switch to home channel for online scan.
    u16 delaytime_in_ms;    ///< Delay time in ms before switch to scan channel for online scan.
    char  ssid[32];
    u8 ssid_len;
    u8 rssi_threshold;
    u8 probe_req_period;
    u8 max_apcnt;
} AT_SCAN_PRIV_ARGS;

u8 check_scan_task_running();
s32 start_scan(AT_SCAN_PRIV_ARGS *argv);
void stop_scan();

#endif /* _SCANPROC_H_ */

