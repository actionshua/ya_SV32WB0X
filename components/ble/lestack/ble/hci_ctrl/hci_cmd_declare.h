#ifndef _HCI_CMD_DECLARE_H_
#define _HCI_CMD_DECLARE_H_

#include "ble/hci_lib.h"

/**
 * cmd hdl:
 *  - return
 *      1:      complete
 *      else:   -status
 */
#define HCI_CMDH_RET_COMMAND_COMPLETE 1
typedef s32 (*FX_HCI_CMDH)(const bt_hci_param_st param_tbl[], bt_hci_param_st ret_param_tbl[]);

typedef struct bt_hci_cmd {

    u16 op;
    //
    u8  param_tbl_size;
    u8  ret_param_tbl_size;
    //
    FX_HCI_CMDH hdl;
    //
    const bt_hci_param_st*  param_tbl;
    const bt_hci_param_st*  ret_param_tbl;

} bt_hci_cmd_st;

// # param
#define BLE_HCI_CMD_PARAM_LEN_MAX 32

// # param tbl
#define BLE_HCI_CMDH_PARAM_TBL_SIZE_MAX     16
#define BLE_HCI_CMDH_RET_PARAM_TBL_SIZE_MAX 8

extern const bt_hci_cmd_st* const   hci_cmd_tbl[];
extern const u32                    hci_cmd_tbl_size;

#endif  // _HCI_CMD_DECLARE_H_
