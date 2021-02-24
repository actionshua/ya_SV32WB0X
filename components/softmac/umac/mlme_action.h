#ifndef __MLME_ACTION_H__
#define __MLME_ACTION_H__


/*******************************************************************************
 *         Include Files
 ******************************************************************************/


/*******************************************************************************
 *         Defines
 ******************************************************************************/
#define AMPDU_AGG_SIZE          (64)    /// Aggregate size
#define AMPDU_START_SEQ_NUM     (0)     /// Start sequence number
#define AMPDU_TIMEOUT           (0)     /// Timeout: Set 0 to disable Timer


/*******************************************************************************
 *         Enumerations
 ******************************************************************************/


/*******************************************************************************
 *         Structures
 ******************************************************************************/
/// Structure for AMPDU TX information
typedef struct _st_ampdu_tx_info
{
    u32 u32UpdateTime;                  ///< Update time of send ADDBA request
    u16 u16Ssn;                         ///< Start sequence number
    u8 u8DialogToken;                   ///< Dialog token
}__attribute__ ((packed)) ST_AMPDU_TX_INFO;

/// Structure for AMPDU TX config.
typedef struct _st_ampdu_tx_config
{
    u32 u32ChkTimeInMs;                 ///< Check time period in ms
}__attribute__ ((packed)) ST_AMPDU_TX_CONFIG;

/// Union for BA parameter.
typedef union un_ba_param_set
{
    u16 u16ShortData;                   ///< whole data of this parameter
    /// Structure for ADDBA parameter field.
    struct
    {
        u16 u16AmsduSupport:1;          ///< A-MSDU support
        u16 u16BaPolicy:1;              ///< BA policy
        u16 u16Tid:4;                   ///< TID
        u16 u16BufferSize:10;           ///< Buffer size
    }__attribute__ ((packed)) stField;
}UN_BA_PARAM_SET;

/// Union for DELBA parameter.
typedef union un_delba_param_set
{
    u16 u16ShortData;                   ///< whole data of this parameter
    /// Structure for DELBA parameter field.
    struct
    {
        u16 u16Reserved:11;             /**< Reserved bits */
        u16 u16Initiator:1;             /**< Initiator */
        u16 u16Tid:4;                   /**< TID */
    }__attribute__ ((packed)) stField;
}UN_DELBA_PARAM_SET;


/*******************************************************************************
 *         Variables
 ******************************************************************************/
extern ST_AMPDU_TX_INFO gstAmpduTxInfo[];
extern ST_AMPDU_TX_CONFIG gstAmpduTxCfg;


/*******************************************************************************
 *         Funcations
 ******************************************************************************/
extern inline void ampdu_set_tx_check_time(u32 u32ChkTime);
extern inline u32 ampdu_get_tx_check_time(void);

/**
 * @brief Send ADDBA request.
 * @param u8Wsid                        [IN] WSID
 * @param u8Bssid                       [IN] BSSID
 * @param pu8DstAddr                    [IN] Pointer to destination MAC address
 * @param u8DialogToken                 [IN] Dialog token
 * @param punParam                      [IN] Pointer to BA parameter set.
 * @param u16Timeout                    [IN] Timeout value.
 * @return the result.   0 : Successful, -1 : Failed.
 */
s32 mgmt_addba_req_send(u8 u8Wsid, u8 u8Bssid, u8 *pu8DstAddr, u8 u8DialogToken, UN_BA_PARAM_SET *punParam, u16 u16Timeout);

/**
 * @brief Send ADDBA response.
 * @param u8Wsid                        [IN] WSID
 * @param u8Bssid                       [IN] BSSID
 * @param pu8DstAddr                    [IN] Pointer to destination MAC address
 * @param u8DialogToken                 [IN] Dialog token
 * @param punParam                      [IN] Pointer to BA parameter set.
 * @param u16Status                     [IN] Status value.
 * @param u16Timeout                    [IN] Timeout value.
 * @return the result.   0 : Successful, -1 : Failed.
 */
s32 mgmt_addba_resp_send(u8 u8Wsid, u8 u8Bssid, u8 *pu8DstAddr, u8 u8DialogToken, UN_BA_PARAM_SET *punParam, u16 u16Status, u16 u16Timeout);

/**
 * @brief Send DELBA.
 * @param u8Wsid                        [IN] WSID
 * @param u8Bssid                       [IN] BSSID
 * @param pu8DstAddr                    [IN] Pointer to destination MAC address
 * @param punParam                      [IN] Pointer to DELBA parameter set.
 * @param u16ReasonCode                 [IN] Reason code value.
 * @return the result.   0 : Successful, -1 : Failed.
 */
s32 mgmt_delba_send(u8 u8Wsid, u8 u8Bssid, u8 *pu8DstAddr, UN_DELBA_PARAM_SET *punParam, u16 u16ReasonCode);

s32 mlme_saquery_send(u8 wsid, u8 bssid, u8 action, u8 *tran_id);

#endif /* __MLME_ACTION_H__ */
