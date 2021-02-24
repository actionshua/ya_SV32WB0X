#ifndef POWERSAVE_H_
#define POWERSAVE_H_
#include <attrs.h>

// define WOW trigger
#define SSV_WOW_TRIGGER_ANY             0x0001
#define SSV_WOW_TRIGGER_MAGIC_PKT       0x0002
#define SSV_WOW_TRIGGER_EAPOL           0x0004
#define SSV_WOW_TRIGGER_DEAUTH          0x0008
#define SSV_WOW_TRIGGER_DISASSOC        0x0010

typedef enum {
    NULL_SUCC_ACTIVE    = 0x0,
    NULL_SUCC_POWERSAVE,
    NULL_FAIL,
}NULL_TXRSP;

struct dtim_data
{
    u8 dtim_cnt;
    u8 dtim_peroid;
    u8 keepdata;
    u16 dtim_position_offset;
};

typedef enum t_MCU_CFG
{
    MCU_ON = 0,
    MCU_OFF,
} MCU_CFG;

typedef enum t_RFPHY_STA
{
    RFPHY_ON = 0,
    RFPHY_OFF,
} RFPHY_STA;

typedef struct _POWERSAVE_STA_INFO
{
    int (*txnullfn)(u8);
    void (*txarpfn)(void);
    int (*pw_arp_resp)(void*, u8 *, u8 *, u32);
    void (*backupmacsettings)(void);
    void (*restoremacsettings)(void);
    void (*txexcpt)(void);
    void (*on3offexfn)(void);
    u32 keepalive_period;
    u8 keepalive_en;
    u8 keepalive_type;
    u8 associd;
    u8 ch;
    u8 tx_reserved_id;
    u8 user_dtim_period;
    u32 prewakeuptime;
    u8 ap_mac[6];
    u8 dataretx_guard;
    u8 beaconloss_guard;
    u8 beaconloss_maxcnt;
} POWERSAVE_STA_INFO;

typedef enum t_POWER_MODE
{
	PSACTIVE_MODE = 0,
	PSSAVING_MODE,
    TEMP_ACTIVE, //There is data to send or receive, go to active mode temporarily.
    TRANS_TO_PS, //Means there is a packet send to AP with the power management bit is power save mode.
    TRANS_TO_AC, //Means there is a packet send to AP with the power management bit is active mode.
} POWER_MODE;

#define PMU_ON3_STATE       (ADR_PMU_RAM_12)
#define PMU_ON1_STATE       (ADR_PMU_RAM_13)

// Need to be synced with driver
typedef enum _en_pmu_on3_state
{
    E_PMU_ON3_TRIGGER_FW_OFF = 0,
    E_PMU_ON3_FW_OFF_READY,
    E_PMU_ON3_TRIGGER_FW_ON,
    E_PMU_ON3_FW_ON_READY,
    E_PMU_ON3_MAX
} EN_PMU_ON3_STATE;

// Need to be synced with driver
typedef enum _en_pmu_on1_state
{
    E_PMU_ON1_TRIGGER_FW_OFF = 0,
    E_PMU_ON1_TRIGGER_FW_ON,
    E_PMU_ON1_MAX
} EN_PMU_ON1_STATE;



void pwsave_init();
void pwsave_set_powermode(u8 powermode);
void pwsave_conf(POWERSAVE_STA_INFO *stainfo);
void checkpwstate();
void pwsave_null_report(NULL_TXRSP response);
u8 beacon_handler(u8 *pkt, u16 len, u32 intime, bool *unicast_trig) ATTRIBUTE_SECTION_FAST;
u8 pwsave_frame_handler(void *pkt, u16 len, u32 intime, u32 wow_trig, bool *wow_wake, u32 *reason, u8 *sta_mac, u8 *bssid, u32 host_ipv4_addr);
u8 pwsave_set_radiotask_state(u8 state);
void pwsave_do_keepalive();
s8 activate_powersave(POWERSAVE_STA_INFO *stainfo);
s8 deactivate_powersave(u8 wificonn);
s32 switch_Power_mode(u8 enable, u8 mcumode);
void on3_shutdown();
int on3_shutdown_ex();
void on3_activate();
void on3_activate_ex();
u8 check_final_dtimperiod(u8 user_dtim, u8 sys_dtim);
u8 get_txclose();
void pwsave_check_phycnt_enable(u8 en);
u8 pwsave_braodcast_period_status(void);
void pwsave_early_terminate_config(u8 value) ATTRIBUTE_SECTION_FAST_POWERSAVE;

#endif /* POWERSAVE_H_ */

