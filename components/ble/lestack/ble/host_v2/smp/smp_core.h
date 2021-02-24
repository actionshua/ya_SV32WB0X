#ifndef _SMP_CORE_H_
#define _SMP_CORE_H_



#include "smp_def.h"



#define SMP_BIT_0                                       0x01
#define SMP_BIT_1                                       0x02
#define SMP_BIT_2                                       0x04
#define SMP_BIT_3                                       0x08
#define SMP_BIT_4                                       0x10
#define SMP_BIT_5                                       0x20
#define SMP_BIT_6                                       0x40
#define SMP_BIT_7                                       0x80

#define SMP_BONDING_MASK                                (SMP_BIT_0 | SMP_BIT_1)
#define SMP_MITM_MASK                                   (SMP_BIT_2)
#define SMP_MITM_SHIFT                                  2

#define SMP_CONFIRM_MASK                                (SMP_BIT_0)
#define SMP_KEY_MASK                                    (SMP_BIT_1)

#define SMP_ENCRYPTION_KEY_MASK                         (SMP_BIT_0)
#define SMP_IDENTITY_KEY_MASK                           (SMP_BIT_1)
#define SMP_SIGNING_KEY_MASK                            (SMP_BIT_2)
#define SMP_DISTRIBUTE_KEY_MASK                         (SMP_BIT_0 | SMP_BIT_1 | SMP_BIT_2)

#define SMP_SECURITY_INFO_NONE                          0
#define SMP_SECURITY_INFO_LTK                           (SMP_BIT_0)
#define SMP_SECURITY_INFO_EDIV_RAND                     (SMP_BIT_1)
#define SMP_SECURITY_INFO_IRK                           (SMP_BIT_2)
#define SMP_SECURITY_INFO_ADDRESS_INFO                  (SMP_BIT_3)
#define SMP_SECURITY_INFO_CSRK                          (SMP_BIT_4)

//pairing request/pairing response data offset
#define PAIRING_FEATURE_IOCAP_OFFSET                    1
#define PAIRING_FEATURE_OOB_OFFSET                      2
#define PAIRING_FEATURE_AUTH_REQ_OFFSET                 3
#define PAIRING_FEATURE_MAX_ENC_KEY_SIZE_OFFSET         4
#define PAIRING_FEATURE_INIT_KEY_DIST_OFFSET            5
#define PAIRING_FEATURE_RSP_KEY_DIST_OFFSET             6

#define SMP_INVALID_CONNECTION_HANDLE                   0xffff

#define SMP_TIMER_ID                                    6
#define SMP_TIME_OUT                                    30000

#define SMP_GET_VAR(var, mask)                          (var & mask)
#define SMP_SET_VAR(var, mask)                          (var |= mask)
#define SMP_CLR_VAR(var, mask)                          (var &= ~mask)

#define SMP_MIN(a, b)                                   (a < b ? a : b)
#define SMP_MAX(a, b)                                   (a > b ? a : b)



typedef enum
{
    SMP_ID_0 = 0,
    SMP_ID_MAX,
    SMP_ID_INVALID = SMP_ID_MAX,

} SMP_ID;



typedef enum
{
    SMP_ROLE_NONE = 0,
    SMP_ROLE_MASTER,
    SMP_ROLE_SLAVE,

} SMP_ROLE;



typedef enum
{
    SMP_STATE_IDLE = 0,                             /// 0   master/slave
    SMP_STATE_WAIT_PAIRING_REQUEST,                 /// 1   slave
    SMP_STATE_WAIT_PAIRING_RESPONSE,                /// 2   master
    SMP_STATE_WAIT_SECURITY_GRANT,                  /// 3   master/slave
    SMP_STATE_WAIT_TK_RESPONSE,                     /// 4   master
    SMP_STATE_WAIT_CONFIRM,                         /// 5   master/slave
    SMP_STATE_WAIT_CONFIRM_AND_KEY,                 /// 6   slave
    SMP_STATE_WAIT_RANDOM,                          /// 7   master/slave
    SMP_STATE_ENCRYPTION_PENDING,                   /// 8   master/slave
    SMP_STATE_WAIT_PEER_DISTRIBUTION_KEY,           /// 9   master/slave
    SMP_STATE_WAIT_LOCAL_DISTRIBUTION_KEY,          /// 10  master/slave
    SMP_STATE_WAIT_ENCRYPTION,                      /// 11  slave

} SMP_STATE;



typedef enum
{
    SMP_OPERATION_PAIRING_REQUEST = 0,              /// 0
    SMP_OPERATION_PAIRING_RESPONSE,                 /// 1
    SMP_OPERATION_PAIRING_CONFIRM,                  /// 2
    SMP_OPERATION_PAIRING_RANDOM,                   /// 3
    SMP_OPERATION_PAIRING_FAILED,                   /// 4
    SMP_OPERATION_ENCRYPTION_INFO,                  /// 5
    SMP_OPERATION_MASTER_IDENTIFICATION,            /// 6
    SMP_OPERATION_IDENTITY_INFO,                    /// 7
    SMP_OPERATION_IDENTITY_ADDRESS_INFO,            /// 8
    SMP_OPERATION_SIGNING_INFO,                     /// 9
    SMP_OPERATION_SECURITY_REQUEST,                 /// 10
    SMP_OPERATION_PAIRING_START,                    /// 11
    SMP_OPERATION_PAIRING_CANCEL,                   /// 12
    SMP_OPERATION_SECURITY_GRANT_RESPONSE,          /// 13
    SMP_OPERATION_TK_REPLY,                         /// 14
    SMP_OPERATION_ENCRYPTION_CHANGED,               /// 15
    SMP_OPERATION_ENCRYPTION_KEY_REFRESH_COMPLETE,  /// 16
    SMP_OPERATION_LONG_TERM_KEY_REQUEST,            /// 17
    SMP_OPERATION_SECURITY_INFO_RESPONSE,           /// 18
    SMP_OPERATION_RECOVER_LTK_RESPONSE,             /// 19
    SMP_OPERATION_DISCONNECTION_COMPLETE,           /// 20
    SMP_OPERATION_TIMEOUT,                          /// 21
    SMP_OPERATION_MAX,

} SMP_OPERATION;



typedef enum
{
    /// Spec defined reason code
    SMP_PAIRING_FAILED_REASON_PASSKEY_ENTRY_FAILED = 0x01,
    SMP_PAIRING_FAILED_REASON_OOB_NOT_AVAILABLE,
    SMP_PAIRING_FAILED_REASON_AUTHENTICATION_REQUIREMENTS,
    SMP_PAIRING_FAILED_REASON_CONFIRM_VALUE_FAILED,
    SMP_PAIRING_FAILED_REASON_PAIRING_NOT_SUPPORTED,
    SMP_PAIRING_FAILED_REASON_ENCRYPTION_KEY_SIZE,
    SMP_PAIRING_FAILED_REASON_COMMAND_NOT_SUPPORTED,
    SMP_PAIRING_FAILED_REASON_UNSPECIFIED_REASON,
    SMP_PAIRING_FAILED_REASON_REPEATED_ATTEMPTS,
    SMP_PAIRING_FAILED_REASON_INVALID_PARAMETERS,

} SMP_PAIRING_FAILED_REASON;



typedef struct
{
    send_l2cap_msg_func_t send_l2cap_msg_func;
    send_hci_cmd_func_t send_hci_cmd_func;
    send_app_event_func_t send_app_event_func;

} smp_general_setting_st;



typedef struct
{
    SMP_STATE state;
    SMP_ROLE role;
    u16 conn_hdl;
    u8 confirm_and_key_status;
    u8 pairing_method;
    u8 local_key_expected;
    u8 peer_key_expected;
    u8 tk[SMP_KEY_SIZE_16BYTE];
    u8 htmr_id;
    u8 ltk[SMP_KEY_SIZE_16BYTE];

} smp_ctrlblock_st;



typedef struct
{
    SMP_OPERATION   op;
    u32             *param;
    u8              param_size;

} smp_operation_st;



typedef struct
{
    u8 addr_type;
    u8 addr[BD_ADDR_SIZE];
    u8 iocap;
    u8 oob;
    u8 max_enc_key_size;
    u8 min_enc_key_size;
    u8 auth;
    u8 bonding;
    u8 mitm;
    u8 init_key_distribution;
    u8 rsp_key_distribution;

} smp_device_property_st;



typedef struct
{
    u8 confirm[SMP_KEY_SIZE_16BYTE];
    u8 rand128[SMP_KEY_SIZE_16BYTE];

} smp_security_key_st;



typedef struct
{
    smp_device_property_st  device_property;
    smp_security_key_st     security_key;

} smp_device_st;



/// Global functions
u8 smp_core_reset();
u8 smp_core_obtain_resource(u16 conn_handle);
u8 smp_core_release_resource(u16 conn_handle);
u8 smp_core_clear_resource(SMP_ID id);
SMP_ID smp_core_get_valid_id(u16 conn_handle);
void smp_core_register_send_l2cap_msg_func(send_l2cap_msg_func_t l2cap_func);
void smp_core_register_send_hci_cmd_func(send_hci_cmd_func_t hci_func);
void smp_core_register_send_app_event_func(send_app_event_func_t app_func);
u8 smp_core_send_operation(SMP_ID id, smp_operation_st *operation);
void smp_core_set_role(SMP_ID id, SMP_ROLE role);
SMP_ROLE smp_core_get_role(SMP_ID id);
void smp_core_update_peer_own_addr(SMP_ID id, u16 conn_hdl);
u8 smp_core_encrypt_data(smp_encryption_data_st *encryption_data);
u8 smp_core_dump_info(SMP_ID id);



#endif // end of _SMP_CORE_H_
