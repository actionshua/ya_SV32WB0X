#ifndef _SSV_COMMON_H_
#define _SSV_COMMON_H_


/*******************************************************************************
 *         Include Files
 ******************************************************************************/


/*******************************************************************************
 *         Defines
 ******************************************************************************/
#ifndef SSV_PACKED_STRUCT
//SSV PACK Definition
#define SSV_PACKED_STRUCT_BEGIN
#define SSV_PACKED_STRUCT               //__attribute__ ((packed))
#define SSV_PACKED_STRUCT_END           //__attribute__((packed))
#define SSV_PACKED_STRUCT_STRUCT        __attribute__ ((packed))
#define SSV_PACKED_STRUCT_FIELD(x)      x
#endif

/* Maximum chip ID length */
#define SSV6XXX_CHIP_ID_LENGTH          (24)
#define SSV6XXX_CHIP_ID_SHORT_LENGTH    (8)

//PAGE size
#define HW_TX_PAGE_SIZE                 (186)
#define HW_RX_PAGE_SIZE                 (60)
#define HW_TX_ID_SIZE                   (62)
#define HW_RX_ID_SIZE                   (62)

// Freddie ToDo: Move firmware multi-rate retry to ssv6200.
#define SSV62XX_TX_MAX_RATES            (3)

//HCI RX AGG
#define HCI_RX_AGGR_SIZE                (0x2710)
#define MAX_HCI_RX_AGGR_SIZE            (HCI_RX_AGGR_SIZE+MAX_FRAME_SIZE)  //AGGR_SIZE+MPDU
/* reserved max sdio align */
#define MAX_RX_PKT_RSVD                 (512)

// RX mode
#define RX_NORMAL_MODE                  (0x0001)
#define RX_HW_AGG_MODE                  (0x0002)

// Maximum number of frames in AMPDU
#define MAX_AGGR_NUM                    (24)
#define MAX_AGGR_NUM_SETTING(_sh)       (_sh->cfg.max_aggr_size)

/* 30 byte 4 addr hdr, 2 byte QoS, 2304 byte MSDU, 12 byte crypt, 4 byte FCS, 80 byte rx_desc */
#define MAX_FRAME_SIZE                  (2432)
/* 802.11ad extends maximum MSDU size for DMG (freq > 40Ghz) networks
 * to 3839 or 7920 bytes, see 8.2.3 General frame format
 */
#define MAX_FRAME_SIZE_DMG            	(4096)

/* Header length of structure */
#define HOST_CMD_HDR_LEN                ((size_t)(((ssv_host_cmd *)0)->un.dat8))
#define HOST_EVT_HDR_LEN                ((size_t)(((ssv_host_event *)0)->dat))

// Log category
#define LOG_TX_DESC     		        (0x00001)
#define LOG_AMPDU_SSN   		        (0x00002)
#define LOG_AMPDU_DBG   		        (0x00004)
#define LOG_AMPDU_ERR   		        (0x00008)
#define LOG_BEACON      		        (0x00010)
#define LOG_RATE_CONTROL      	        (0x00020)
#define LOG_RATE_REPORT      	        (0x00040)
#define LOG_TX_FRAME                    (0x00080)
#define LOG_RX_DESC                     (0x00100)
#define LOG_HCI             	        (0x00200)
#define LOG_HWIF             	        (0x00400)
#define LOG_HAL                         (0x00800)
#define LOG_REGW                        (0x01000)
#define LOG_FLASH_BIN                   (0x02000)
#define LOG_KRACK                       (0x04000)
#define LOG_FLOWCTL                     (0x08000)
#define LOG_RSSI                        (0x10000)


/*******************************************************************************
 *         Enumerations
 ******************************************************************************/
typedef enum {
//==============================================================================
    IOT_HOSTCMD_NONE                    = 0, // Invalid host command
    //==========================================================================
    //Custom command
    IOT_HOSTCMD_CUSTOM_CMD              = 1, // custom command operation
    //==========================================================================
    //SSV command
    IOT_HOSTCMD_8023PKT                 = 128, // tx ethernet packet to SoC
    IOT_HOSTCMD_80211PKT                = 129, // reserved for repeater mode.
    IOT_HOSTCMD_TXTPUT_PKT              = 130, // txtput
    IOT_HOSTCMD_RXTPUT_PKT              = 131, // rxtput
    IOT_HOSTCMD_SYNC                    = 132, // sync
    //==========================================================================
    IOT_HOSTCMD_MAXID                   = 255, // Invalid host command
//==============================================================================
} iot_host_cmd_id;

typedef enum{
//==============================================================================
    //==========================================================================
    //Custom event
    IOT_SOCEVT_NONE                     = 0, // Invalid soc event.
    IOT_SOCEVT_CUSTOM_EVT               = 1, // custom event
    //==========================================================================
    //SSV event
    IOT_SOCEVT_WIFI_CONNECTED           = 128, // the offset of rx ethernet packet from SoC
    IOT_SOCEVT_8023PKT                  = 129, // rx ethernet packet from SoC
    IOT_SOCEVT_WIFI_DISCON              = 130,
    IOT_SOCEVT_TXTPUT_RESULT            = 131, //  txtput result
    IOT_SOCEVT_RXTPUT                   = 132, //  rxtput packet
    //==========================================================================
    IOT_SOCEVT_MAXID                    = 255,
//==============================================================================
} iot_soc_event;


/*******************************************************************************
 *         Structures
 ******************************************************************************/
/*
 * struct hci_rx_aggr_info - HCI RX Aggregation Format description
 */
SSV_PACKED_STRUCT_BEGIN
struct hci_rx_aggr_info {
    u32             jmp_mpdu_len:16;
    u32             accu_rx_len:16;

    u32             RSVD0:15;
    u32             tx_page_remain:9;
    u32             tx_id_remain:8;

    u32             edca0:4;
    u32             edca1:5;
    u32             edca2:5;
    u32             edca3:5;
    u32             edca4:4;
    u32             edca5:5;
    u32             RSVD1:4;
}SSV_PACKED_STRUCT_STRUCT;
SSV_PACKED_STRUCT_END

SSV_PACKED_STRUCT_BEGIN
typedef struct host_pktinfo {
    u32 wsid:8;
    u32 bssid:8;
    u32 wmmsupport:8;
    u32 powermode:8;
}SSV_PACKED_STRUCT_STRUCT host_pktinfo;
SSV_PACKED_STRUCT_END

/**
 *  struct ssv_host_cmd - Host Command Header Format description
 *
 */
SSV_PACKED_STRUCT_BEGIN
typedef struct ssv_host_cmd {
    u32 len:16;
    u32 c_type:3;
    u32 RSVD0:5;
    u32 h_cmd:8;
    u32 from_fw:1; //0: packet from host, 1: packet from fw
    u32 RSVD1:31;
    host_pktinfo pktinfo;
    u32 csum1;//calculate tx descriptor checksum
    u32	csum2;//calculate payload checksum
	u32 data_offset;//error handling
    SSV_PACKED_STRUCT_BEGIN
    union {
        u32         dummy;
        u8          dat8[4];
        u16         dat16[2];
        u32         dat32[1];
    }SSV_PACKED_STRUCT_STRUCT un;
    SSV_PACKED_STRUCT_END
}SSV_PACKED_STRUCT_STRUCT ssv_host_cmd;
SSV_PACKED_STRUCT_END

/**
 *  struct ssv_host_event - Host Event Header Format description
 *
 */
SSV_PACKED_STRUCT_BEGIN
typedef struct ssv_host_event {
    u32 len:16;
    u32 c_type:3;
    u32 RSVD0:5;
    u32 h_event:8; //------------------>ssv_host_evt
    u32 dat_len:16;
    u32 dat_offset:8;
    u32 RSVD1:8;
    u32	event_csum;
    u8 dat[0];
}SSV_PACKED_STRUCT_STRUCT ssv_host_event;
SSV_PACKED_STRUCT_END

SSV_PACKED_STRUCT_BEGIN
struct ssv_wifi_connect_info {
    u32 tx_desc_resv_len:16;
    u32 tx_page:16;
    u32 tx_id:16;
    u32 wmm_support:8;
    u32 rsvd:8;
}SSV_PACKED_STRUCT_STRUCT;
SSV_PACKED_STRUCT_END

SSV_PACKED_STRUCT_BEGIN    
struct ssv_rxtput_cfg {
    u32 size_per_frame;
	u32 total_frames;
}SSV_PACKED_STRUCT_STRUCT;
SSV_PACKED_STRUCT_END

SSV_PACKED_STRUCT_BEGIN
struct fw_rc_retry_params {
    u32 count:4;
    u32 drate:6;
    u32 crate:6;
    u32 rts_cts_nav:16;
    u32 frame_consume_time:10;
    u32 dl_length:12;
    u32 RSVD:10;
}SSV_PACKED_STRUCT_STRUCT;
SSV_PACKED_STRUCT_END

SSV_PACKED_STRUCT_BEGIN
struct ssv6xxx_tx_hw_info {
	u32 tx_id_threshold;
	u32 tx_page_threshold;
	u32 tx_lowthreshold_page_trigger;
	u32 tx_lowthreshold_id_trigger;
	u32 bk_txq_size;
	u32 be_txq_size;
	u32 vi_txq_size;
	u32 vo_txq_size;
	u32 manage_txq_size;
}SSV_PACKED_STRUCT_STRUCT;
SSV_PACKED_STRUCT_END

SSV_PACKED_STRUCT_BEGIN
struct ssv6xxx_rx_hw_info {
	u32 rx_id_threshold;
	u32 rx_page_threshold;
	u32 rx_ba_ma_sessions;
}SSV_PACKED_STRUCT_STRUCT;
SSV_PACKED_STRUCT_END
#endif	/* _SSV_COMMON_H_ */
