#ifndef _HCI_MSGH_H_
#define _HCI_MSGH_H_

#include "ssv_types.h"
#include "ble/ctrl_v2/ble_ll_op.h"

/**
 * - return -1, if something wrong, the msg is ignored.
 * - otherwise, return length of the paramter composed.
 *
 */
s16 hci_msgh_disconnection_complete                     (const ble_ll_evt_hci_un evt, u16 evt_buf_len_max,
                                                            u16* evt_buf_len, u8* evt_buf, const void** les_memory);
s16 hci_msgh_encryption_change                          (const ble_ll_evt_hci_un evt, u16 evt_buf_len_max,
                                                            u16* evt_buf_len, u8* evt_buf, const void** les_memory);
s16 hci_msgh_read_remote_version_information_complete   (const ble_ll_evt_hci_un evt, u16 evt_buf_len_max,
                                                            u16* evt_buf_len, u8* evt_buf, const void** les_memory);
s16 hci_msgh_number_of_completed_packets                (const ble_ll_evt_hci_un evt, u16 evt_buf_len_max,
                                                            u16* evt_buf_len, u8* evt_buf, const void** les_memory);
s16 hci_msgh_data_buffer_overflow                       (const ble_ll_evt_hci_un evt, u16 evt_buf_len_max,
                                                            u16* evt_buf_len, u8* evt_buf, const void** les_memory);
s16 hci_msgh_encryption_key_refresh_complete            (const ble_ll_evt_hci_un evt, u16 evt_buf_len_max,
                                                            u16* evt_buf_len, u8* evt_buf, const void** les_memory);
s16 hci_msgh_le_connection_complete                     (const ble_ll_evt_hci_un evt, u16 evt_buf_len_max,
                                                            u16* evt_buf_len, u8* evt_buf, const void** les_memory);
s16 hci_msgh_le_advertising_report                      (const ble_ll_evt_hci_un evt, u16 evt_buf_len_max,
                                                            u16* evt_buf_len, u8* evt_buf, const void** les_memory);
s16 hci_msgh_le_connection_update_complete              (const ble_ll_evt_hci_un evt, u16 evt_buf_len_max,
                                                            u16* evt_buf_len, u8* evt_buf, const void** les_memory);
s16 hci_msgh_le_read_remote_used_features_complete      (const ble_ll_evt_hci_un evt, u16 evt_buf_len_max,
                                                            u16* evt_buf_len, u8* evt_buf, const void** les_memory);
s16 hci_msgh_le_long_term_key_request                   (const ble_ll_evt_hci_un evt, u16 evt_buf_len_max,
                                                            u16* evt_buf_len, u8* evt_buf, const void** les_memory);
s16 hci_msgh_le_data_length_change                      (const ble_ll_evt_hci_un evt, u16 evt_buf_len_max,
                                                            u16* evt_buf_len, u8* evt_buf, const void** les_memory);
s16 hci_msgh_ssv_air_evt_early_notify                   (const ble_ll_evt_hci_un evt, u16 evt_buf_len_max,
                                                            u16* evt_buf_len, u8* evt_buf, const void** les_memory);
s16 hci_msgh_ssv_air_evt_end_notify                     (const ble_ll_evt_hci_un evt, u16 evt_buf_len_max,
                                                            u16* evt_buf_len, u8* evt_buf, const void** les_memory);
s16 hci_msgh_ssv_version_exchanged_notify               (const ble_ll_evt_hci_un evt, u16 evt_buf_len_max,
                                                            u16* evt_buf_len, u8* evt_buf, const void** les_memory);

#endif // _HCI_MSGH_H_
