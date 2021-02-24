#ifndef _DRV_PHY_H_
#define _DRV_PHY_H_

#include <attrs.h>
#include "drv_phy_common.h"
#include "rssi_api.h"


/**
 *  @brief  Enumeration of Phy Sniffer action type
 */
typedef enum _en_drv_phy_sniffer_action_type
{
    E_DRV_PHY_SNIFFER_ACT_TYPE_NONE = 0,     ///< None.
    E_DRV_PHY_SNIFFER_ACT_TYPE_ENABLE,       ///< Enable Phy sniffer.
    E_DRV_PHY_SNIFFER_ACT_TYPE_DISABLE,      ///< Disable Phy sniffer.
    E_DRV_PHY_SNIFFER_ACT_TYPE_GET,          ///< Get Phy sniffer counter.
    E_DRV_PHY_SNIFFER_ACT_TYPE_RESET,        ///< Reset Phy sniffer.
    E_DRV_PHY_SNIFFER_ACT_TYPE_MAX,          ///< Max.
}EN_DRV_PHY_SNIFFER_ACT_TYPE;

/**
 *  @brief  Enumeration of Phy Sniffer parameter type
 */
typedef enum _en_drv_phy_sniffer_param_type
{
    E_DRV_PHY_SNIFFER_PARAM_TYPE_NONE = 0,      ///< None.
    E_DRV_PHY_SNIFFER_PARAM_TYPE_ADDR1,         ///< Address 1: pointer to the MAC address with 6 bytes.
    E_DRV_PHY_SNIFFER_PARAM_TYPE_ADDR2,         ///< Address 2: pointer to the MAC address with 6 bytes.
    E_DRV_PHY_SNIFFER_PARAM_TYPE_ADDR3,         ///< Address 3: pointer to the MAC address with 6 bytes.
    E_DRV_PHY_SNIFFER_PARAM_TYPE_FRAMETYPE,     ///< Frame type with u16 data type.
    E_DRV_PHY_SNIFFER_PARAM_TYPE_MAX,           ///< Max.
}EN_DRV_PHY_SNIFFER_PARAM_TYPE;


/**
 *  @brief  Structure of Phy Sniffer parameter.
 */
typedef struct _st_drv_phy_sniffer_param
{
    EN_DRV_PHY_SNIFFER_PARAM_TYPE enType;       ///< Parameter type.
    union
    {
        void *pData;
        u32 u32Data;
        u16 u16Data;
        u8 u8Data;
        bool bData;
    }uData;                                     ///< Union of parameter data.
}ST_DRV_PHY_SNIFFER_PARAM;


typedef void (*hw_bcn_miss) (void);
typedef void (*phy_sniffer_isr) (u8 channel, u32 ht_signal_23_0, u32 ht_signal_47_24);


void drv_rfphy_backup(void) ATTRIBUTE_SECTION_FAST_L2STACK;
void drv_rfphy_restore(void) ATTRIBUTE_SECTION_FAST_L2STACK;
void drv_rf_restore(void) ATTRIBUTE_SECTION_FAST_L2STACK;
void drv_phy_restore(void) ATTRIBUTE_SECTION_FAST_L2STACK;
void drv_phy_cali(u8 Support5G, u8 dcdc, u32 xtal, u32 bus_clk);
s32 drv_phy_channel_change(u32 channel_id, u32 ch_type);
void drv_phy_set_dpd_disable_mask(u8 mask);
void drv_phy_init(void);
void drv_phy_off(void);
void drv_phy_on(void);
void drv_phy_b_only(void);
void drv_phy_bgn(void);
s32 drv_phy_clean_dpd_cali(void);
void drv_2G_physetting() ATTRIBUTE_SECTION_FAST_L2STACK;
void drv_5G_physetting() ATTRIBUTE_SECTION_FAST_L2STACK;
void drv_pmu_tu2 (u32 t_us);
void drv_phy_beacon_loss_enable(void);
void drv_phy_beacon_loss_disable(void);
void drv_phy_hw_beacon_loss_monitor(u8 bssid, u8 beacon_interval, u8 loss_count,hw_bcn_miss handler, bool enable);
void drv_phy_pmu(void);
void drv_phy_xtal(void);
void drv_phy_sx(void);
void drv_phy_cali_result(void);
void drv_phy_txband(void);
void drv_phy_txgain(void);
void drv_phy_dpd_show(void);
void drv_phy_sniffer_irq_enable(bool en);
void drv_phy_register_sniffer_isr(phy_sniffer_isr user_isr);
void drv_phy_unregister_sniffer_isr(void);
int drv_phy_get_cur_channel(void);
int drv_phy_get_cur_channel_type(void);
void drv_phy_set_channel_busy(void);
void drv_phy_release_channel(void);
void drv_phy_set_external_pa(u8 ext_pa);
void drv_phy_turn_on_rf(bool val);
int drv_phy_reg_len(void);
void drv_phy_get_reg_context(void *buf, u32 offset);
int drv_rf_reg_len(void);
void drv_rf_get_reg_context(void *buf, u32 offset);
void drv_phy_init_cali(u8 support5G); 
void drv_phy_restore_cali(u8 support5G);
void drv_phy_dpd_on(void);
void drv_phy_dpd_off(void);
void drv_phy_backup_dpd(void);
void drv_phy_restore_dpd(void);
void drv_phy_init_dpd(u32 chan, u32 ch_type);
void drv_phy_init_pll(void);
int ssv6006_get_pa_band(int ch);

/**
 * @brief   Set Phy sniffer config.
 * @param   pstParam        [IN] Pointer to configuration parameter
 * @return  None.
 */
void drv_phy_set_sniffer_config(ST_DRV_PHY_SNIFFER_PARAM *pstParam);

/**
 * @brief   Set Phy sniffer action.
 * @param   enType          [IN] Action type
 * @return  None.
 */
void drv_phy_set_sniffer_action(EN_DRV_PHY_SNIFFER_ACT_TYPE enType);
void dry_phy_set_external_pa(u8 ext_pa);
int ssv6006_get_pa_band(int ch);

struct drv_phy_csi_status {
    int idx;
    int csi_i;
    int csi_q;
};

struct drv_phy_csi_report {
    struct drv_phy_csi_status stat[128];
    u64 timestamp;
    u32 rssi;
    u32 snr;
    u16 frame_ctl;
    u8  addr1[6];
    u8  addr2[6];
    u8  addr3[6];
    int len;
    bool done;
};

/**
 * @brief   Enable/Disable b/g/n csi phy function.
 */
typedef void (*phy_csi_isr) (void *csi_result);
void drv_phy_csi_enable_b(bool en);
void drv_phy_csi_config_b(u8 *addr1, u8 *addr2, u8 *addr3, u16 fc, u16 fc_mask);
void drv_phy_csi_enable_gn(bool en);
void drv_phy_csi_config_gn(u8 *addr1, u8 *addr2, u8 *addr3, u16 fc, u16 fc_mask);
void drv_phy_ungister_csi_isr(void);
void drv_phy_register_csi_isr(phy_csi_isr user_isr, void *csi_result);
void drv_phy_csi_irq_enable(bool en);

void drv_phy_irq_register(void);
void drv_phy_irq_unregister(void);
void drv_phy_wifi_block_switch_to_wifi(void);
void drv_phy_wifi_block_switch_to_ble(void);
void drv_phy_wifi_block_enable(bool en);
void drv_phy_ble_en(bool en);
/**
 * @Get wifi calibration result size
 * @return wifi calibration result size
 */
int drv_phy_get_cal_result_size(void);

/**
 * @Get wifi calibration result 
 * @param _cal_result     [OUT] output the WIFI calibration results
 * @return the result. 0 : Successful, -1 : Failed.
 */
int drv_phy_get_cal_result(void *_cal_result);

/**
 * @Set wifi calibration result 
 * @param _cal_result     [IN] Input the WIFI calibration results
 * @return the result. 0 : Successful, -1 : Failed.
 */
int drv_phy_set_cal_result(void *_cal_result);
#endif /* _DRV_PHY_H_ */
