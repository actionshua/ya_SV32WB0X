#ifndef _SSV_NOW_H_
#define _SSV_NOW_H_

#include "soc_types.h"
#include "soc_defs.h"

#include "wificonf.h"


#define SSV_NOW_SUCCESS     0
#define SSV_NOW_FAIL             -1

typedef enum
{
    SSV_NOW_SEND_SUCCESS     = 0,
    SSV_NOW_SEND_FAIL   = 1
} ssv_now_send_status_t;

typedef enum
{
    SSV_NOW_ROLE_NONE   = 0,
    SSV_NOW_ROLE_CTRL,
    SSV_NOW_ROLE_SLAVE
} ssv_now_role_t;

/**
  * @brief     Callback function of sending SSV-NOW data
  * @param     mac_addr peer MAC address
  * @param     status status of sending SSV-NOW data
  */
typedef void (*ssv_now_send_cb_t)(const uint8_t *mac_addr, ssv_now_send_status_t status);

/**
  * @brief     Callback function of receiving SSV-NOW data
  * @param     mac_addr peer MAC address
  * @param     data received data
  * @param     data_len length of received data
  */
typedef void (*ssv_now_recv_cb_t)(const uint8_t *mac_addr, const uint8_t *data, int data_len);

typedef void (*ssv_now_recv_cb_ex_t)(const packetinfo* info, const uint8_t *mac_addr, const uint8_t *data, int data_len);
/**
  * @brief     Initialize SSV-NOW function
  *
  * @return
  *          - SSV_NOW_SUCCESS : succeed
  *          - SSV_NOW_FAIL : error
  */
int ssv_now_init();

/**
  * @brief     De-initialize SSV-NOW function
  *
  * @return
  *          - SSV_NOW_SUCCESS : succeed
  */
int ssv_now_deinit();

/**
  * @brief     Set SSV-NOW Role
  *
  * @param     role  set role as control or slave
  *
  * @return
  *          - SSV_NOW_SUCCESS : succeed
  */
int ssv_now_set_role(ssv_now_role_t role);

/**
  * @brief     Register callback function of receiving SSV-NOW data
  *
  * @param     callback  callback function of receiving SSV-NOW data
  *
  * @return
  *          - SSV_NOW_SUCCESS : succeed
  *          - SSV_NOW_FAIL : error
  */
int ssv_now_register_recv_cb(ssv_now_recv_cb_t callback);

int ssv_now_register_recv_cb_ex(ssv_now_recv_cb_ex_t callback2);
/**
  * @brief     Register callback function of sending SSV-NOW data
  *
  * @param     callback  callback function of sending SSV-NOW data
  *
  * @return
  *          - SSV_NOW_SUCCESS : succeed
  *          - SSV_NOW_FAIL : error
  */
int ssv_now_register_send_cb(ssv_now_send_cb_t callback);

/**
  * @brief     Send SSV-NOW data by Management Frame
  *
  * @attention 1. If mac_addr is Broadcast address (FF:FF:FF:FF:FF:FF), send data with Broadcast 
  * @attention 2. If mac_addr is Multicast address (such as 01:0C:CD:04:00:00), send data with Multicast 
  *
  * @param     mac_addr  peer MAC address
  * @param     data  data to send
  * @param     data_len  length of data
  *
  * @return
  *          - SSV_NOW_SUCCESS : succeed
  *          - SSV_NOW_FAIL : error
  */
int ssv_now_send_mgmt_payload(const uint8_t *mac_addr, const uint8_t *data, int data_len);

/**
  * @brief     Send SSV-NOW data by Data Frame
  *
  * @attention 1. If mac_addr is Broadcast address (FF:FF:FF:FF:FF:FF), send data with Broadcast 
  * @attention 2. If mac_addr is Multicast address (such as 01:0C:CD:04:00:00), send data with Multicast 
  *
  * @param     mac_addr  peer MAC address
  * @param     data  data to send
  * @param     data_len  length of data
  *
  * @return
  *          - SSV_NOW_SUCCESS : succeed
  *          - SSV_NOW_FAIL : error
  */
int ssv_now_send_data_payload(const uint8_t *mac_addr, const uint8_t *data, int data_len);

/**
  * @brief     Send SSV-NOW Raw Data
  *
  * @attention 1. Raw Data must be 802.11 frame Format
  *
  * @param     raw_data  data to send
  * @param     len  length of data
  *
  * @return
  *          - SSV_NOW_SUCCESS : succeed
  *          - SSV_NOW_FAIL : error
  */
int ssv_now_send_rawdata(const uint8_t *raw_data, int len);

/**
  * @brief     Set Filter address for receive data
  *
  * @param     source_addr  mac address of source
  *
  * @return
  *          - SSV_NOW_SUCCESS : succeed
  *          - SSV_NOW_FAIL : error
  */
int ssv_now_set_recv_filter_mac(const uint8_t *source_addr);

/**
  * @brief     Send SSV-NOW data by Management Frame
  *
  * @attention 1. If mac_addr is Broadcast address (FF:FF:FF:FF:FF:FF), send data with Broadcast 
  * @attention 2. If mac_addr is Multicast address (such as 01:0C:CD:04:00:00), send data with Multicast 
  *
  * @param     peer_addr  peer MAC address
  * @param     bssid_addr  BSSID address
  * @param     data  data to send
  * @param     data_len  length of data
  *
  * @return
  *          - SSV_NOW_SUCCESS : succeed
  *          - SSV_NOW_FAIL : error
  */
int ssv_now_send_mgmt_payload_ex(const uint8_t *peer_addr, const uint8_t *bssid_addr, const uint8_t *data, int len);


#endif // _SSV_NOW_H_