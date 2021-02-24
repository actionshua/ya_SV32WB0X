#ifndef _HCI_EVT_DECLARE_H_
#define _HCI_EVT_DECLARE_H_

#include "ble/hci_lib.h"
#include "ble/ctrl_v2/ble_ll_op.h"

/**
 * event implementation (msg-to-evt)
 *
 */
typedef s16 (*FX_HCI_MSGH)(ble_ll_evt_hci_un msg_param, u16 evt_len_max, u16* evt_len, u8* evt, const void** les_memory);

typedef struct bt_hci_evt {

    u8  op;
    u8  sub_op;
    //
    FX_HCI_MSGH msgh;

} bt_hci_evt_st;

// # param
#define BLE_HCI_EVT_PARAM_LEN_MAX 48

// # param tbl
#define BLE_HCI_EVT_PARAM_TBL_SIZE_MAX 12

extern const bt_hci_evt_st hci_evt_disconnection_complete;
extern const bt_hci_evt_st hci_evt_encryption_change;
extern const bt_hci_evt_st hci_evt_read_remote_version_information_complete;
extern const bt_hci_evt_st hci_evt_number_of_completed_packets;
extern const bt_hci_evt_st hci_evt_data_buffer_overflow;
extern const bt_hci_evt_st hci_evt_encryption_key_refresh_complete;
extern const bt_hci_evt_st hci_evt_le_connection_complete;
extern const bt_hci_evt_st hci_evt_le_advertising_report;
extern const bt_hci_evt_st hci_evt_le_connection_update_complete;
extern const bt_hci_evt_st hci_evt_le_read_remote_used_features_complete;
extern const bt_hci_evt_st hci_evt_le_long_term_key_request;
extern const bt_hci_evt_st hci_evt_ssv_air_evt_early_notify;
extern const bt_hci_evt_st hci_evt_ssv_air_evt_end_notify;
extern const bt_hci_evt_st hci_evt_ssv_version_exchanged_notify;

extern const bt_hci_evt_st* const   hci_evt_tbl[];
extern const u32                    hci_evt_tbl_size;

#endif  // end of _HCI_EVT_DECLARE_H_
