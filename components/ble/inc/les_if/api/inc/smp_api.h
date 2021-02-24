#ifndef _SMP_API_H_
#define _SMP_API_H_


#include "les_if/api/inc/svc_def.h"
#include "les_if/api/inc/les_def.h"



#define SMP_KEY_SIZE_16BYTE                     16
#define SMP_KEY_SIZE_2BYTE                      2
#define SMP_KEY_SIZE_8BYTE                      8

/// IO capabilities
#define SMP_IOCAP_DISPLAY_ONLY                  0
#define SMP_IOCAP_DISPLAY_YESNO                 1
#define SMP_IOCAP_KEYBOARD_ONLY                 2
#define SMP_IOCAP_NO_INPUT_OUTPUT               3
#define SMP_IOCAP_KEYBOARD_DISPLAY              4
#define SMP_IOCAP_MAX                           SMP_IOCAP_KEYBOARD_DISPLAY

/// Encryption key size
#define SMP_KEY_SIZE_MIN                        7
#define SMP_KEY_SIZE_MAX                        16

/// mitm
#define SMP_MITM_DISABLED                       0
#define SMP_MITM_ENABLED                        1



typedef enum
{
    SMP_SVCMD_PAIRING_START = SMP_SVC_NUM_MIN,
    SMP_SVCMD_PAIRING_CANCEL,
    SMP_SVCMD_SECURITY_GRANT_RESPONSE,
    SMP_SVCMD_TK_RESPONSE,
    SMP_SVCMD_SECURITY_INFO_RESPONSE,
    SMP_SVCMD_RECOVER_LTK_RESPONSE,
    SMP_SVCMD_ENCRYPT_DATA,

} SMP_SVCMD;



typedef enum
{
    SMP_LES_EVENT_SECURITY_GRANT_REQUEST = SMP_LES_EVENT_ID_MIN,
    SMP_LES_EVENT_TK_REQUEST,
    SMP_LES_EVENT_ACTION_RESULT,
    SMP_LES_EVENT_SECURITY_INFO_REQUEST,
    SMP_LES_EVENT_SECURITY_INFO_UPDATE,
    SMP_LES_EVENT_RECOVER_LTK_REQUEST,

} SMP_LES_EVENT;



typedef enum
{
    SMP_ACTION_TYPE_PAIRING,
    SMP_ACTION_TYPE_ENCRYPTION,

} SMP_ACTION_TYPE;



typedef enum
{
    SMP_PAIRING_METHOD_JUST_WORK,
    SMP_PAIRING_METHOD_PASSKEY_INPUT,
    SMP_PAIRING_METHOD_PASSKEY_DISPLAY,
    SMP_PAIRING_METHOD_OOB,

} SMP_PAIRING_METHOD;



typedef enum
{
    SMP_KEY_TYPE_NONE,
    SMP_KEY_TYPE_PASSKEY,
    SMP_KEY_TYPE_OOB,

} SMP_KEY_TYPE;



typedef enum
{
    SMP_SECURITY_INFO_TYPE_LOCAL_ENCRYPTION_LTK_INFO,
    SMP_SECURITY_INFO_TYPE_LOCAL_ENCRYPTION_EDIV_RAND64_INFO,
    SMP_SECURITY_INFO_TYPE_LOCAL_IDENTITY_IRK_INFO,
    SMP_SECURITY_INFO_TYPE_LOCAL_IDENTITY_ADDR_INFO,
    SMP_SECURITY_INFO_TYPE_LOCAL_SIGNING_CSRK_INFO,

    SMP_SECURITY_INFO_TYPE_PEER_ENCRYPTION_LTK_INFO,
    SMP_SECURITY_INFO_TYPE_PEER_ENCRYPTION_EDIV_RAND64_INFO,
    SMP_SECURITY_INFO_TYPE_PEER_IDENTITY_IRK_INFO,
    SMP_SECURITY_INFO_TYPE_PEER_IDENTITY_ADDR_INFO,
    SMP_SECURITY_INFO_TYPE_PEER_SIGNING_CSRK_INFO,

    SMP_SECURITY_INFO_TYPE_ENCRYPTION_INFO,

} SMP_SECURITY_INFO_TYPE;



typedef enum
{
    SMP_SECURITY_GRANT_RESULT_PAIRING,
    SMP_SECURITY_GRANT_RESULT_ENCRYPTION,
    SMP_SECURITY_GRANT_RESULT_ERROR,

} SMP_SECURITY_GRANT_RESULT;



typedef enum
{
    SMP_SECURITY_INFO_RESPONSE_SUCCESS,
    SMP_SECURITY_INFO_RESPONSE_ERROR,

} SMP_SECURITY_INFO_RESPONSE_REAULT;



typedef struct
{
    uint8_t iocap;
    uint8_t oob;
    uint8_t bonding;
    uint8_t mitm;
    uint8_t max_enc_key_size;
    uint8_t min_enc_key_size;
    uint8_t init_key_distribution;
    uint8_t rsp_key_distribution;

} smp_security_property_st;



typedef struct
{
    uint8_t bonding;
    uint8_t mitm;

} smp_auth_req_st;



typedef struct
{
    uint8_t ltk[SMP_KEY_SIZE_16BYTE];

} smp_encryption_ltk_info_st;



typedef struct
{
    uint8_t ediv[SMP_KEY_SIZE_2BYTE];
    uint8_t rand64[SMP_KEY_SIZE_8BYTE];

} smp_encryption_ediv_rand64_info_st;



typedef struct
{
    smp_encryption_ltk_info_st ltk;
    smp_encryption_ediv_rand64_info_st ediv_rand64;

} smp_encryption_ltk_ediv_rand64_info_st;



typedef struct
{
    bd_addr_st addr;

} smp_identity_addr_info_st;



typedef struct
{
    uint8_t irk[SMP_KEY_SIZE_16BYTE];

} smp_identity_irk_info_st;



typedef struct
{
    uint8_t csrk[SMP_KEY_SIZE_16BYTE];

} smp_signing_csrk_info_st;



typedef struct
{
    uint8_t authen;
    uint8_t key_size;

} smp_encryption_info_st;



typedef struct
{
    uint8_t type;
    uint8_t result;
    uint8_t reason;
    uint8_t mitm;
    uint8_t enc_key_size;
    uint8_t init_key_distribution;
    uint8_t rsp_key_distribution;

} smp_action_result_st;



/// SMP_SVCMD_SECURITY_GRANT_RESPONSE
typedef struct
{
    SMP_SECURITY_GRANT_RESULT security_grant_result;

    union
    {
        smp_security_property_st                property;
        smp_encryption_ltk_ediv_rand64_info_st  encryption_ltk_ediv_rand64_info;
        uint8_t                                 error_code;

    } info;

} smp_security_grant_response_st;



/// SMP_SVCMD_TK_RESPONSE
typedef struct
{
    uint8_t     key_type;
    uint32_t    passkey;
    uint8_t     oob_key[SMP_KEY_SIZE_16BYTE];

} smp_tk_response_st;



/// SMP_SVCMD_SECURITY_INFO_RESPONSE
typedef struct
{
    SMP_SECURITY_INFO_TYPE  type;
    uint8_t                 result;

    union
    {
        smp_encryption_ltk_info_st          encryption_ltk_info;
        smp_encryption_ediv_rand64_info_st  encryption_ediv_rand64_info;
        smp_identity_addr_info_st           identity_addr_info;
        smp_identity_irk_info_st            identity_irk_info;
        smp_signing_csrk_info_st            signing_csrk_info;
        smp_encryption_info_st              encryption_info;

    } info;

} smp_security_info_st;



/// SMP_SVCMD_ENCRYPT_DATA
typedef struct
{
    uint8_t key[SMP_KEY_SIZE_16BYTE];
    uint8_t plaintext_data[SMP_KEY_SIZE_16BYTE];
    uint8_t encrypted_data[SMP_KEY_SIZE_16BYTE];

} smp_encryption_data_st;



typedef struct 
{
    uint16_t conn_hdl;

    union
    {
        smp_auth_req_st auth_req;                               /// SMP_LES_EVENT_SECURITY_GRANT_REQUEST
        SMP_PAIRING_METHOD pairing_method;                      /// SMP_LES_EVENT_TK_REQUEST
        smp_action_result_st action_result;                     /// SMP_LES_EVENT_ACTION_RESULT
        SMP_SECURITY_INFO_TYPE security_info_type;              /// SMP_LES_EVENT_SECURITY_INFO_REQUEST
        smp_security_info_st security_info;                     /// SMP_LES_EVENT_SECURITY_INFO_UPDATE
        smp_encryption_ediv_rand64_info_st ediv_rand64;         /// SMP_LES_EVENT_RECOVER_LTK_REQUEST

    } data;

} smp_les_event_st;



DEF_SVC(SMP_SVCMD_PAIRING_START,            uint32_t,   les_smp_pairing_start(uint16_t conn_hdl, smp_security_property_st *security_property));
DEF_SVC(SMP_SVCMD_PAIRING_CANCEL,           uint32_t,   les_smp_pairing_cancel(uint16_t conn_hdl));
DEF_SVC(SMP_SVCMD_SECURITY_GRANT_RESPONSE,  uint32_t,   les_smp_security_grant_response(uint16_t conn_hdl, smp_security_grant_response_st *security_grant));
DEF_SVC(SMP_SVCMD_TK_RESPONSE,              uint32_t,   les_smp_tk_response(uint16_t conn_hdl, smp_tk_response_st *tk_response));
DEF_SVC(SMP_SVCMD_SECURITY_INFO_RESPONSE,   uint32_t,   les_smp_security_info_response(uint16_t conn_hdl, smp_security_info_st *security_info));
DEF_SVC(SMP_SVCMD_RECOVER_LTK_RESPONSE,     uint32_t,   les_smp_recover_ltk_response(uint16_t conn_hdl, smp_encryption_info_st *encryption_info, smp_security_info_st *security_info));
DEF_SVC(SMP_SVCMD_ENCRYPT_DATA,             uint32_t,   les_smp_encrypt_data(smp_encryption_data_st *encryption_data));



#endif  // end of _SMP_API_H_
