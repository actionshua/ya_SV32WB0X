#ifndef _HCI_LIB_H_
#define _HCI_LIB_H_

#include "condor_ssv_lib.h"

/**
 * indicator format
 *
 */
#define BT_HCI_W_INDICATOR     1
#define BT_HCI_IDX_INDICATOR   0

/**
 * acl data format
 *
 */
#define BT_HCI_W_ACL_CONN_HDL  2
#define BT_HCI_W_ACL_LEN       2
#define BT_HCI_W_ACL_HDR       (BT_HCI_W_INDICATOR +BT_HCI_W_ACL_CONN_HDL +BT_HCI_W_ACL_LEN)
#define BT_HCI_W_ACL_PLD       255

#define BT_HCI_IDX_ACL_CONN_HDL    (BT_HCI_IDX_INDICATOR      +BT_HCI_W_INDICATOR    )
#define BT_HCI_IDX_ACL_LEN         (BT_HCI_IDX_ACL_CONN_HDL   +BT_HCI_W_ACL_CONN_HDL )
#define BT_HCI_IDX_ACL_PLD         (BT_HCI_IDX_ACL_LEN        +BT_HCI_W_ACL_LEN      )


/**
 * cmd format
 *
 */
#define BT_HCI_W_CMD_OP     2
#define BT_HCI_W_CMD_LEN    1
#define BT_HCI_W_CMD_HDR    (BT_HCI_W_INDICATOR +BT_HCI_W_CMD_OP +BT_HCI_W_CMD_LEN)

#define BT_HCI_IDX_CMD_OP       (BT_HCI_IDX_INDICATOR   +BT_HCI_W_INDICATOR ) //1
#define BT_HCI_IDX_CMD_LEN      (BT_HCI_IDX_CMD_OP      +BT_HCI_W_CMD_OP    ) //3
#define BT_HCI_IDX_CMD_PARAM    (BT_HCI_IDX_CMD_LEN     +BT_HCI_W_CMD_LEN   ) //4

#define BT_HCI_BITW_CMD_OP_OCF  10
#define BT_HCI_BITW_CMD_OP_OGF  6

#define BT_HCI_BITIDX_CMD_OP_OCF    0
#define BT_HCI_BITIDX_CMD_OP_OGF    (BT_HCI_BITIDX_CMD_OP_OCF +BT_HCI_BITW_CMD_OP_OCF)

#define BT_HCI_CMD_OPCODE(OGF, OCF) (((OGF) << BT_HCI_BITIDX_CMD_OP_OGF) | ((OCF) << BT_HCI_BITIDX_CMD_OP_OCF))

/**
 * event format
 *
 */
#define BT_HCI_W_EVT_OP     1
#define BT_HCI_W_EVT_LEN    1
#define BT_HCI_W_EVT_HDR    (BT_HCI_W_INDICATOR +BT_HCI_W_EVT_OP +BT_HCI_W_EVT_LEN) //3


#define BT_HCI_IDX_EVT_OP       (BT_HCI_IDX_INDICATOR   +BT_HCI_W_INDICATOR )
#define BT_HCI_IDX_EVT_LEN      (BT_HCI_IDX_EVT_OP      +BT_HCI_W_EVT_OP    )
#define BT_HCI_IDX_EVT_PARAM    (BT_HCI_IDX_EVT_LEN     +BT_HCI_W_EVT_LEN   )

// about return parameter
#define BT_HCI_IDX_RET_PARAM    (BT_HCI_IDX_EVT_PARAM +3)   // Num_HCI_Command_Packets 1-byte, Command_Opcode: 2-byte

/**
 * le event format
 *
 */
#define BT_HCI_W_LE_EVT_OP 1

#define BT_HCI_IDX_LE_EVT_OP    (BT_HCI_IDX_EVT_PARAM)
#define BT_HCI_IDX_LE_EVT_PARAM (BT_HCI_IDX_LE_EVT_OP +BT_HCI_W_LE_EVT_OP)

/**
 *  parameter format
 *
 */
#define BT_HCI_W_PARAM_MAX  255

/**
 * indicator constants
 *
 */
#define BT_HCI_INDICATOR_COMMAND   0x01
#define BT_HCI_INDICATOR_ACL_DATA  0x02
#define BT_HCI_INDICATOR_SCO_DATA  0x03
#define BT_HCI_INDICATOR_EVENT     0x04

/**
 * command constants
 *
 */
// # OGF
#define BT_HCI_CMD_OGF_NOP                      0x00
#define BT_HCI_CMD_OGF_LINK_CONTROL             0x01
#define BT_HCI_CMD_OGF_LINK_POLICY              0x02
#define BT_HCI_CMD_OGF_CONTROL_BASEBAND         0x03
#define BT_HCI_CMD_OGF_INFORMATION_PARAMETERS   0x04
#define BT_HCI_CMD_OGF_STATUS_PARAMETERS        0x05
#define BT_HCI_CMD_OGF_TESTING                  0x06
#define BT_HCI_CMD_OGF_LE_CONTROLLER            0x08
#define BT_HCI_CMD_OGF_VENDOR_SPECIFIC          0x3f

// # OCF: nop commands
#define BT_HCI_CMD_OCF_NOP  0x0000

// # OCF: link control commands
#define BT_HCI_CMD_OCF_DISCONNECT                       0x0006
#define BT_HCI_CMD_OCF_READ_REMOTE_VERSION_INFORMATION  0x001d

// # OCF: link policy commands

// # OCF: control baseband command
#define BT_HCI_CMD_OCF_SET_EVENT_MASK                       0x0001
#define BT_HCI_CMD_OCF_RESET                                0x0003
#define BT_HCI_CMD_OCF_READ_TRANSMIT_POWER_LEVEL            0x002d
#define BT_HCI_CMD_OCF_SET_CONTROLLER_TO_HOST_FLOW_CONTROL  0x0031
#define BT_HCI_CMD_OCF_HOST_BUFFER_SIZE                     0x0033
#define BT_HCI_CMD_OCF_HOST_NUMBER_OF_COMPLETED_PACKETS     0x0035
#define BT_HCI_CMD_OCF_READ_LE_HOST_SUPPORT                 0x006c
#define BT_HCI_CMD_OCF_WRITE_LE_HOST_SUPPORT                0x006d

// # OCF: information parameters command
#define BT_HCI_CMD_OCF_LOCAL_VERSION_INFORMATION        0x0001
#define BT_HCI_CMD_OCF_READ_LOCAL_SUPPORTED_COMMANDS    0x0002
#define BT_HCI_CMD_OCF_READ_LOCAL_SUPPORTED_FEATURES    0x0003
#define BT_HCI_CMD_OCF_READ_BUFFER_SIZE                 0x0005
#define BT_HCI_CMD_OCF_READ_BD_ADDR                     0x0009

// # OCF: status parameters command
#define BT_HCI_CMD_OCF_READ_RSSI    0x0005

// # OCF: testing command

// # OCF: LE controller commands
#define BT_HCI_CMD_OCF_LE_SET_EVENT_MASK                        0x0001
#define BT_HCI_CMD_OCF_LE_READ_BUFFER_SIZE                      0x0002
#define BT_HCI_CMD_OCF_LE_READ_LOCAL_SUPPORTED_FEATURES         0x0003
#define BT_HCI_CMD_OCF_LE_SET_RANDOM_ADDRESS                    0x0005
#define BT_HCI_CMD_OCF_LE_SET_ADVERTISING_PARAMETERS            0x0006
#define BT_HCI_CMD_OCF_LE_READ_ADVERTISING_CHANNEL_TX_POWER     0x0007
#define BT_HCI_CMD_OCF_LE_SET_ADVERTISING_DATA                  0x0008
#define BT_HCI_CMD_OCF_LE_SET_SCAN_RESPONSE_DATA                0x0009
#define BT_HCI_CMD_OCF_LE_SET_ADVERTISE_ENABLE                  0x000a
#define BT_HCI_CMD_OCF_LE_SET_SCAN_PARAMETERS                   0x000b
#define BT_HCI_CMD_OCF_LE_SET_SCAN_ENABLE                       0x000c
#define BT_HCI_CMD_OCF_LE_CREATE_CONNECTION                     0x000d
#define BT_HCI_CMD_OCF_LE_CREATE_CONNECTION_CANCEL              0x000e
#define BT_HCI_CMD_OCF_LE_READ_WHITE_LIST_SIZE                  0x000f
#define BT_HCI_CMD_OCF_LE_CLEAR_WHITE_LIST                      0x0010
#define BT_HCI_CMD_OCF_LE_ADD_DEVICE_TO_WHITE_LIST              0x0011
#define BT_HCI_CMD_OCF_LE_REMOVE_DEVICE_FROM_WHITE_LIST         0x0012
#define BT_HCI_CMD_OCF_LE_CONNECTION_UPDATE                     0x0013
#define BT_HCI_CMD_OCF_LE_SET_HOST_CHANNEL_CLASSIFICATION       0x0014
#define BT_HCI_CMD_OCF_LE_READ_CHANNEL_MAP                      0x0015
#define BT_HCI_CMD_OCF_LE_READ_REMOTE_USED_FEATURES             0x0016
#define BT_HCI_CMD_OCF_LE_ENCRYPT                               0x0017
#define BT_HCI_CMD_OCF_LE_RAND                                  0x0018
#define BT_HCI_CMD_OCF_LE_START_ENCRYPTION                      0x0019
#define BT_HCI_CMD_OCF_LE_LONG_TERM_KEY_REQUEST_REPLY           0x001a
#define BT_HCI_CMD_OCF_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY  0x001b
#define BT_HCI_CMD_OCF_LE_READ_SUPPORTED_STATES                 0x001c
#define BT_HCI_CMD_OCF_LE_RECEIVER_TEST                         0x001d
#define BT_HCI_CMD_OCF_LE_TRANSMITTER_TEST                      0x001e
#define BT_HCI_CMD_OCF_LE_TEST_END                              0x001f
#define BT_HCI_CMD_OCF_LE_SET_DATA_LENGTH                       0x0022
#define BT_HCI_CMD_OCF_LE_READ_SUGGESTED_DEFAULT_DATA_LENGTH    0x0023
#define BT_HCI_CMD_OCF_LE_WRITE_SUGGESTED_DEFAULT_DATA_LENGTH   0x0024
#define BT_HCI_CMD_OCF_LE_READ_MAXIMUM_DATA_LENGTH              0x002F
#define BT_HCI_CMD_OCF_LE_READ_TRANSMIT_POWER                   0x004B

// OCF: SSV-VS command
#define BT_HCI_CMD_OCF_SSV_REG_READ                         0x0001
#define BT_HCI_CMD_OCF_SSV_REG_WRITE                        0x0002
// #define BT_HCI_CMD_OCF_SSV_ENABLE                        0x0003   // not adopted
#define BT_HCI_CMD_OCF_SSV_SLAVE_SUBRATE                    0x0004
#define BT_HCI_CMD_OCF_SSV_SET_ADVERTISING_CHANNEL_PRIORITY 0x0005
#define BT_HCI_CMD_OCF_SSV_ACL_EVT_TO_EXTERNAL_HOST         0x0006
#define BT_HCI_CMD_OCF_SSV_SET_PUBLIC_BD_ADDR                0x0007
#define BT_HCI_CMD_OCF_SSV_LE_TRANSMITTER_TEST              0x00f0

/**
 * event constant
 *
 */
// event op
#define BT_HCI_EVT_OP_DISCONNECTION_COMPLETE                    0x05
#define BT_HCI_EVT_OP_ENCRYPTION_CHANGE                         0x08
#define BT_HCI_EVT_OP_READ_REMOTE_VERSION_INFORMATION_COMPLETE  0x0c
#define BT_HCI_EVT_OP_COMMAND_COMPLETE                          0x0e
#define BT_HCI_EVT_OP_COMMAND_STATUS                            0x0f
#define BT_HCI_EVT_OP_HARDWARE_ERROR                            0x10
#define BT_HCI_EVT_OP_NUMBER_OF_COMPLETED_PACKETS               0x13
#define BT_HCI_EVT_OP_DATA_BUFFER_OVERFLOW                      0x1a
#define BT_HCI_EVT_OP_ENCRYPTION_KEY_REFRESH_COMPLETE           0x30
#define BT_HCI_EVT_OP_LE_EVENT                                  0x3e
#define BT_HCI_EVT_OP_SSV                                       0xff

#define BT_HCI_LE_EVT_OP_NONE                               0x00
#define BT_HCI_LE_EVT_OP_CONNECTION_COMPLETE                0x01
#define BT_HCI_LE_EVT_OP_ADVERTISING_REPORT                 0x02
#define BT_HCI_LE_EVT_OP_CONNECTION_UPDATE_COMPLETE         0x03
#define BT_HCI_LE_EVT_OP_READ_REMOTE_USED_FEATURES_COMPLETE 0x04
#define BT_HCI_LE_EVT_OP_LONG_TERM_KEY_REQUEST              0x05
#define BT_HCI_LE_EVT_OP_DATA_LENGTH_CHANGE                 0x07

#define BT_HCI_SSV_EVT_OP_AIR_EVT_EARLY_NOTIFY      0x01
#define BT_HCI_SSV_EVT_OP_AIR_EVT_END_NOTIFY        0x02
#define BT_HCI_SSV_EVT_OP_VERSION_EXCHANGED_NOTIFY  0x03

/**
 * common constant
 *
 */
#define BT_HCI_CONN_HDL_INVLD   0x0fff

#define BT_HCI_LE_MASTER    0x00
#define BT_HCI_LE_SLAVE     0X01

/**
 *  hci parameter table implementation
 *
 */
#define BT_HCI_PARAM_PROP_U8    0x01
#define BT_HCI_PARAM_PROP_U16   0x02
#define BT_HCI_PARAM_PROP_PTR   0x08
#define BT_HCI_PARAM_PROP_VLEN  0x18 //  variable length, only legel in last element of the table

typedef struct bt_hci_param {
    u8      len;
    u8      prop;
    union {
        u8      val_u8;
        u16     val_u16;
        ptr_u16 val_ptr;
        ptr_u32 val_ptr32;
    };
} bt_hci_param_st;

#define BT_HCI_PARAM_TBL_SIZE(TBL) (sizeof(TBL)/sizeof(bt_hci_param_st))

u32 bt_hci_param_disassemble(u32 param_tbl_size, bt_hci_param_st* param_tbl,
                             u32 param_len, const u8* param);

u32 bt_hci_param_assemble(u32 param_tbl_size, const bt_hci_param_st* param_tbl,
                          u32 param_len_max, u8* param);
u32 bt_hci_param_assemble_u32addr(u32 param_tbl_size, const bt_hci_param_st* param_tbl,
                          u32 param_len_max, u8* param);

#define BT_HCI_PARAM_DECLARE_U8(_VALUE_)            {1,         BT_HCI_PARAM_PROP_U8,   {.val_u16   = (_VALUE_)}}
#define BT_HCI_PARAM_DECLARE_U16(_VALUE_)           {2,         BT_HCI_PARAM_PROP_U16,  {.val_u16   = (_VALUE_)}}
#define BT_HCI_PARAM_DECLARE_PTR(_LEN_, _PTR_)      {(_LEN_),   BT_HCI_PARAM_PROP_PTR,  {.val_ptr   = (_PTR_)}}
#define BT_HCI_PARAM_DECLARE_VLEN(_PTR_)            {0,         BT_HCI_PARAM_PROP_VLEN, {.val_ptr   = (_PTR_)}}

/**
 * command/event implementation
 *
 */

// TODO: move to hci_ctrl
/**
 * acl data implementation
 *
 */
#define BT_HCI_ACL_PB_FLAG_FIRST_NON_FLUSHABLE  0X00
#define BT_HCI_ACL_PB_FLAG_CONTINUE_FRAGMENT    0x01
#define BT_HCI_ACL_PB_FLAG_FIRST_FLUSHABLE      0X02
#define BT_HCI_ACL_PB_FLAG_FLUSHABLE            0x03

#define BT_HCI_ACL_BC_FLAG_NO_BROADCAST 0x00

#define BT_HCI_ACL_B_FRAME_GET_CONN_HDL(_B1B0_)    (((_B1B0_) & 0x0fff) >> 0 )
#define BT_HCI_ACL_B_FRAME_GET_PB_FLAG(_B1B0_)     (((_B1B0_) & 0x3000) >> 12)
#define BT_HCI_ACL_B_FRAME_GET_BC_FLAG(_B1B0_)     (((_B1B0_) & 0xc000) >> 14)

#define BT_HCI_ACL_B_FRAME_SET_CONN_HDL(_B1B0_, _CONN_HDL_) \
            _B1B0_ = (_B1B0_ & 0xf000) | (((_CONN_HDL_) & 0x0fff) << 0)
#define BT_HCI_ACL_B_FRAME_SET_PB_FLAG(_B1B0_,  _PB_FLAG_) \
            _B1B0_ = (_B1B0_ & 0xcfff) | (((_PB_FLAG_)  & 0x0003) << 12)
#define BT_HCI_ACL_B_FRAME_SET_BC_FLAG(_B1B0_,  _BC_FLAG_) \
            _B1B0_ = (_B1B0_ & 0x3fff) | (((_BC_FLAG_)  & 0x0003) << 14)

/**
 * HCI cmd parameter macro
 *
 */
#define BT_HCI_LE_ADVERTISING_PARAM_TYPE_ADV_IND           0x00
#define BT_HCI_LE_ADVERTISING_PARAM_TYPE_ADV_DIRECT_IND    0x01
#define BT_HCI_LE_ADVERTISING_PARAM_TYPE_ADV_SCAN_IND      0x02
#define BT_HCI_LE_ADVERTISING_PARAM_TYPE_ADV_NONCONN_IND   0x03

#endif  /// end of _HCI_LIB_H_
