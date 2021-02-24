#ifndef _DRV_MAC_H_
#define _DRV_MAC_H_

#include <turismo/regs.h>
#include <wificonf.h>
#include <attrs.h>
//#include <hw_regs_api.h>

#define RX_QUEUE_LEN (128)   //it must be power of 2
#define RX_QUEUE_MASK (RX_QUEUE_LEN-1)

#define TYPE_MASK            0xC
#define TYPE_OFFSET          2
#define TYPE_MGMT            0x0
#define TYPE_CTRL            0x1
#define TYPE_DATA            0x2

typedef struct rx_info
{
  u8    isoccupied;
  u8    channel;
  u8    *pbuf_addr;
  u32   pktlen;
  u32   systick;
  u32   ht_signal_23_0;
  u32   ht_signal_47_24;
} rx_info_t;
 
typedef struct rx_queue
{
  rx_info_t queue[RX_QUEUE_LEN];
  u8 save_index;
  u8 proc_index;
  u8 clear_index;
} rx_queue_t;

struct sk_pbuff {
    u8 *pkt;
    u8 *data;
    u32 expire_time;
    u16 len;
    u8 rssi;
    u8 bssid;
    u8 wsid;
};

/**
 *  @brief  Structure of Beacon configurations.
 */
typedef struct st_drv_mac_beacon_config
{
    u32 u32PacketSize;      ///< Beacon packet size.
    u32 u32DtimOffset;      ///< DTIM field offset.
    u16 u16Interval;        ///< Beacon interval.
    u8 u8DtimPeriod;        ///< DTIM period.
    u32 u32Reserved;        ///< Reserved.
}__attribute__ ((packed)) ST_DRV_MAC_BEACON_CONFIG;


#define drv_mac_set_op_mode(sm)             SET_OP_MODE(sm)
#define drv_mac_get_op_mode()               GET_OP_MODE

#define drv_mac_set_ht_mode(hm)             SET_HT_MODE(hm)
#define drv_mac_get_ht_mode()               GET_HT_MODE

#define DRV_MAC_GET_STA_TX_SEQ(wsid, tx_tid) (REG_WSID_ENTRY[wsid].s[tx_tid].UP_TX_SEQCTL)

#define drv_mac_set_pbuf_offset(s)          SET_PB_OFFSET(s)
#define drv_mac_get_pbuf_offset()           GET_PB_OFFSET

#define drv_mac_set_dup_detect(s)           SET_DUP_FLT(s)
#define drv_mac_get_dup_detect()            GET_DUP_FLT

#define drv_mac_set_promis_mode(s)
#define drv_mac_get_promis_mode()

#define drv_mac_set_null_trap(s)
#define drv_mac_get_null_trap()

#define drv_mac_set_hdr_strip(s)            SET_HDR_STRIP(s)
#define drv_mac_get_hdr_strip()             GET_HDR_STRIP

#define drv_mac_set_rx2host(s)              SET_RX_2_HOST(s)
#define drv_mac_get_rx2host()               GET_RX_2_HOST

//#define drv_mac_set_rx2host_m2(s)           SET_RX2HOST_M2_ENA(s)
//#define drv_mac_get_rx2host_m2()            GET_RX2HOST_M2_ENA

#define drv_mac_set_group_seq_ctrl(s)       SET_SEQ_CTRL(s)
#define drv_mac_get_group_seq_ctrl()        GET_SEQ_CTRL

#define drv_mac_set_tx_ether_trap_en(s)     SET_TX_ETHER_TRAP_EN(s)
#define drv_mac_get_tx_ether_trap_en()        GET_TX_ETHER_TRAP_EN

#define drv_mac_set_rx_ether_trap_en(s)     SET_RX_ETHER_TRAP_EN(s)
#define drv_mac_get_rx_ether_trap_en()        GET_RX_ETHER_TRAP_EN

#define drv_mac_set_group_ack_policy(s)
#define drv_mac_get_group_ack_policy

#define drv_mac_set_rx_null_data_trap_en(s)            SET_RX_NULL_TRAP_EN(s)
#define drv_mac_get_rx_null_data_trap_en()             GET_RX_NULL_TRAP_EN

#define drv_mac_set_erp_protect(s)          SET_ERP_PROTECT(s)
#define drv_mac_get_erp_protect()           GET_ERP_PROTECT

#define drv_mac_set_rx_info_size(s)       SET_RX_INFO_SIZE(s)
#define drv_mac_get_rx_info_size()        GET_RX_INFO_SIZE

#define drv_mac_set_tx_pboffset(s)       SET_TX_PBOFFSET(s)
#define drv_mac_get_tx_pboffset()        GET_TX_PBOFFSET

#define drv_mac_set_tx_info_size(s)       SET_TX_INFO_SIZE(s)
#define drv_mac_get_tx_info_size()        GET_TX_INFO_SIZE

#define drv_mac_set_rx_last_phy_size(s)       SET_RX_LAST_PHY_SIZE(s)
#define drv_mac_get_rx_info_last_phy_size()        GET_RX_LAST_PHY_SIZE

#define drv_mac_set_auto_seqno(s)           SET_AUTO_SEQNO(s)
#define drv_mac_get_auto_seqno()            GET_AUTO_SEQNO

#define drv_mac_set_rts_threshold(s)        SET_DOT11RTSTHRESHOLD(s)
#define drv_mac_get_rts_threshold()         GET_DOT11RTSTHRESHOLD

#define drv_mac_set_txpkt_rsvd(s)            SET_TX_PKT_RSVD(s)
#define drv_mac_get_txpkt_rsvd()             GET_TX_PKT_RSVD

#define drv_mac_set_nav(s)                   SET_MTX_NAV(s)
#define drv_mac_get_nav()                    GET_MTX_NAV

#define drv_mac_set_bypass_tx_parser_encap(s)     SET_BYPASSS_TX_PARSER_ENCAP(s)
#define drv_mac_get_bypass_tx_parser_encap()      GET_BYPASSS_TX_PARSER_ENCAP

#define drv_mac_set_pro_ver(s)     SET_PRO_VER(s)
#define drv_mac_get_pro_ver()      GET_PRO_VER

/**
*
*/
#define drv_mac_set_global_ack_policy(s)
#define drv_mac_get_global_ack_policy()

#define drv_mac_set_txf_id(s)               SET_TXF_ID(s)
#define drv_mac_get_txf_id()                GET_TXF_ID

#define drv_mac_set_mgmt_txqid(s)           SET_TXQ_ID0(s)
#define drv_mac_get_mgmt_txqid()            GET_TXQ_ID0

#define drv_mac_set_nonqos_txqid(s)         SET_TXQ_ID1(s)
#define drv_mac_get_nonqos_txqid()          GET_TXQ_ID1

#define drv_mac_set_mac_loopback(s)         SET_RG_MAC_LPBK(s)
#define drv_mac_get_mac_loopback()          GET_RG_MAC_LPBK

#define drv_mac_set_mac_loopback_without_rx_check(s) SET_RG_LPBK_RX_EN(s)
#define drv_mac_get_mac_loopback_without_rx_check() GET_RG_LPBK_RX_EN

#define drv_mac_set_mac_m2m(s)              SET_RG_MAC_M2M(s)
#define drv_mac_get_mac_m2m()               GET_RG_MAC_M2M

#define drv_mac_set_phy_loopback(s)         SET_RG_PHY_LPBK(s)
#define drv_mac_get_phy_loopback()          GET_RG_PHY_LPBK

#define drv_mac_set_sniffer_mode(s)         SET_SNIFFER_MODE(s)
#define drv_mac_set_ampdu_sniffer(s)        SET_AMPDU_SNIFFER(s)

/* obsolete: */
#define drv_mac_set_qos_en(s)                SET_QOS_EN(s)
#define drv_mac_get_qos_en()                 GET_QOS_EN

void drv_mactrx_init(void) ATTRIBUTE_SECTION_FAST_L2STACK;
void drv_macfilter_setting(WIFI_OPMODE mode, SNIFFER_RECVINDEX recvsetting) ATTRIBUTE_SECTION_FAST_L2STACK;

/**
* STA Infomation Definition:
*
* @ STA_INFO_MODE()
* @ STA_INFO_HT()
* @ STA_INFO_QOS()
*/
#define STA_INFO_MODE(x)            ((x)&(3<<0))
#define STA_INFO_HT(x)              ((x)&(3<<2))
#define STA_INFO_QOS(x)             ((x)&(1<<4))

/**
* Define flags for WSID INFO field:
*
* @ WSID_INFO_VALID
*/
#define SET_WSID_INFO_VALID(s, v)       do {(s)->info = (((s)->info & ~(1<<0)) | ((v)<<0)); } while (0)
#define SET_WSID_INFO_QOS_EN(s, v)      do {(s)->info = (((s)->info & ~(1<<1)) | ((v)<<1)); } while (0)
#define SET_WSID_INFO_OP_MODE(s, v)     do {(s)->info = (((s)->info & ~(3<<2)) | ((v)<<2)); } while (0)
#define SET_WSID_INFO_HT_MODE(s, v)     do {(s)->info = (((s)->info & ~(3<<4)) | ((v)<<4)); } while (0)

#define GET_WSID_INFO_VALID(s)          ((s)->info&0x01)
#define GET_WSID_INFO_QOS_EN(s)         (((s)->info >>1) & 0x01)
#define GET_WSID_INFO_OP_MODE(s)        (((s)->info >>2) & 0x03)
#define GET_WSID_INFO_HT_MODE(s)        (((s)->info >>3) & 0x03)


s32 drv_mac_set_regmac(u32 macreg, const u8 *mac) ATTRIBUTE_SECTION_FAST_L2STACK;

s32 drv_mac_init(void);
s32 drv_mac_set_tx_flow_data(const u32 *cflow);
s32 drv_mac_get_tx_flow_data(u32 *cflow);
s32 drv_mac_set_tx_flow_mgmt(const u32 *cflow);
s32 drv_mac_get_tx_flow_mgmt(u32 *cflow);
s32 drv_mac_set_tx_flow_ctrl(const u32 *cflow);
s32 drv_mac_get_tx_flow_ctrl(u32 *cflow);
s32 drv_mac_set_rx_flow_data(const u32 *cflow);
s32 drv_mac_get_rx_flow_data(u32 *cflow);
s32 drv_mac_set_rx_flow_mgmt(const u32 *cflow);
s32 drv_mac_get_rx_flow_mgmt(u32 *cflow);
s32 drv_mac_set_rx_flow_ctrl(const u32 *cflow);
s32 drv_mac_get_rx_flow_ctrl(u32 *cflow);

s32 drv_mac_hw_queue_status(void);

//HW MIB counter
int drv_mac_mib_reset(void);
int drv_mac_mib_on(void);
int drv_mac_mib_off(void);
int drv_mac_mib_rx(void);
int drv_mac_mib_tx(void);
void get_random_bytes(u8* rand_num, u32 byte_cnt);

/**
 * @brief   Initialization Beacon function.
 * @param   pstCfg          [IN] Beacon parameters
 * @return  the result.     0 : Successful, -1 : Failed.
 */
s32 drv_mac_init_beacon(ST_DRV_MAC_BEACON_CONFIG *pstCfg);

/**
 * @brief   De-initialization Beacon function.
 * @return  the result.     0 : Successful, -1 : Failed.
 */
s32 drv_mac_deinit_beacon(void);

/**
 * @brief   Update Beacon frame body
 * @param   pu8BufAddr      [IN] Pointer to store buffer address
 * @param   u32BufSize      [IN] Buffer size
 * @return  the result.     0 : Successful, -1 : Failed.
 */
s32 drv_mac_update_beacon(u8 *pu8BufAddr, u32 u32BufSize);

/**
 * @brief   Start Beacon function.
 * @return  the result.     0 : Successful, -1 : Failed.
 */
s32 drv_mac_start_beacon(void);

/**
 * @brief   Stop Beacon function.
 * @return  the result.     0 : Successful, -1 : Failed.
 */
s32 drv_mac_stop_beacon(void);

/**
 * @brief   Enable/Disable HW Tx queue.
 * @param   bEnable         [IN] TRUE: enable; FALSE: disable
 * @param   u32TxQMask      [IN] HW Tx queue mask: EDCA_0: 0x01, EDCA_1: 0x02, EDCA_2: 0x04, EDCA_3: 0x08, MGMT: 0x10
 * @return  None.
 */
//void drv_mac_txq_enable(bool bEnable, u32 u32TxQMask);
#endif /* _DRV_MAC_H_ */
