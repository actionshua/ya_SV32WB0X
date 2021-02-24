#ifndef _BLE_LL_SECURITY_H_
#define _BLE_LL_SECURITY_H_

#include "condor_ssv_lib.h"
#include "ble/ble_lib_v2.h"

#include "ble/ctrl_v2/ble_ll.h"

#define BLE_LL_AES_CCM_KEY_SIZE    16
#define BLE_LL_AES_CCM_DBLOCK_SIZE 16

/**
 *  RAND/EDIV
 *
 */
#define BLE_LL_SECURITY_RAND_SIZE   8
#define BLE_LL_SECURITY_EDIV_SIZE   2

/**
 * BLE AES-CCM session-key
 *
 */
#define BLE_LL_AES_CCM_SKDX_SIZE    8
#define BLE_LL_AES_CCM_SKDM_SIZE    BLE_LL_AES_CCM_SKDX_SIZE
#define BLE_LL_AES_CCM_SKDS_SIZE    BLE_LL_AES_CCM_SKDX_SIZE
#define BLE_LL_AES_CCM_SKD_SIZE     (BLE_LL_AES_CCM_SKDM_SIZE  +BLE_LL_AES_CCM_SKDS_SIZE)

#define BLE_LL_AES_CCM_IVX_SIZE     4
#define BLE_LL_AES_CCM_IVM_SIZE     BLE_LL_AES_CCM_IVX_SIZE
#define BLE_LL_AES_CCM_IVS_SIZE     BLE_LL_AES_CCM_IVX_SIZE
#define BLE_LL_AES_CCM_IV_SIZE      (BLE_LL_AES_CCM_IVM_SIZE   +BLE_LL_AES_CCM_IVS_SIZE)

#define BLE_LL_AES_CCM_FROM_MASTER 1
#define BLE_LL_AES_CCM_FROM_SLAVE  0

#define BLE_LL_AES_CCM_PDU_CNT_SIZE 5
#define BLE_LL_AES_CCM_PDU_CNT_BW   (8*BLE_LL_AES_CCM_PDU_CNT_SIZE -1)

#define BLE_LL_AES_CCM_PLD_LEN_SIZE         2
#define BLE_LL_AES_CCM_PLD_LEN_BEND_IDX_LSO (BLE_LL_AES_CCM_PLD_LEN_SIZE -1)

#define BLE_LL_AES_CCM_AX_CNT_SIZE      2
#define BLE_LL_AES_CCM_AX_CNT_BEND_IDX_LSO  (BLE_LL_AES_CCM_AX_CNT_SIZE -1)

#define BLE_LL_AES_CCM_AAD_SIZE 1
#define BLE_LL_AES_CCM_MIC_SIZE 4

#define BLE_LL_AES_CCM_SK_M_PDU_CNT_INIT    ((u64)BLE_LL_AES_CCM_FROM_MASTER    << BLE_LL_AES_CCM_PDU_CNT_BW)
#define BLE_LL_AES_CCM_SK_S_PDU_CNT_INIT    ((u64)BLE_LL_AES_CCM_FROM_SLAVE     << BLE_LL_AES_CCM_PDU_CNT_BW)

#define BLE_LL_AES_CCM_SK_M_PDU_CNT_MAX     (BLE_LL_AES_CCM_SK_M_PDU_CNT_INIT + (((u64)1 << BLE_LL_AES_CCM_PDU_CNT_BW) -1))
#define BLE_LL_AES_CCM_SK_S_PDU_CNT_MAX     (BLE_LL_AES_CCM_SK_S_PDU_CNT_INIT + (((u64)1 << BLE_LL_AES_CCM_PDU_CNT_BW) -1))

typedef struct ble_ll_aes_ccm_sk {

    ble_ll_cypher_key_un    key;
    u8                      iv[BLE_LL_AES_CCM_IV_SIZE];

    union {
        u64 m_pdu_cnt_u64;
        struct {
            u64 val         :39;
            u64 direction   :1;
        } m_pdu_cnt;
    };

    union {
        u64 s_pdu_cnt_u64;
        struct {
            u64 val         :39;
            u64 direction   :1;
        } s_pdu_cnt;
    };

    u8  vld;

} ble_ll_aes_ccm_sk_st;


void ble_ll_aes_ccm_sk_init (ble_ll_aes_ccm_sk_st* sk, const ble_ll_cypher_key_un* ltk,
    u8* skdm, u8* ivm, u8* skds, u8* ivs);

/**
 * PDU encryption/decryption
 *
 */
ble_ll_pduq_st ble_aes_ccm_encrypt(ble_ll_pduq_st pduq, u8 role, ble_ll_aes_ccm_sk_st* sk);
ble_ll_pduq_st ble_aes_ccm_decrypt(ble_ll_pduq_st pduq, u8 role, ble_ll_aes_ccm_sk_st* sk, u8* mic_err);

/**
 * PDU encryption/decryption (with hw booster)
 *
 */
ble_ll_pduq_st ble_aes_ccm_hw_encrypt(ble_ll_pduq_st pduq, u8 role, ble_ll_aes_ccm_sk_st* sk);
ble_ll_pduq_st ble_aes_ccm_hw_decrypt(ble_ll_pduq_st pduq, u8 role, ble_ll_aes_ccm_sk_st* sk, u8* mic_err);

/**
 * security toolbox
 *
 */
void ble_ll_security_rand_gen(u8 rand_len, u8* rand, u32* seed);

#endif
