#ifndef _LES_DEF_H_
#define _LES_DEF_H_


#include <stdint.h>



/// USER SVC command
#define USER_SVC_NUM_MIN                0x00
#define USER_SVC_NUM_MAX                0x0F

/// GAP SVC command
#define GAP_SVC_NUM_MIN                 0x10
#define GAP_SVC_NUM_MAX                 0x37

/// ATT SVC command
#define ATT_SVC_NUM_MIN                 0x38
#define ATT_SVC_NUM_MAX                 0x3F

/// GATTS SVC command
#define GATTS_SVC_NUM_MIN               0x40
#define GATTS_SVC_NUM_MAX               0x47

/// GATTM SVC command
#define GATTM_SVC_NUM_MIN               0x48
#define GATTM_SVC_NUM_MAX               0x4F

/// GATTC SVC command
#define GATTC_SVC_NUM_MIN               0x50
#define GATTC_SVC_NUM_MAX               0x5F

/// SMP SVC command
#define SMP_SVC_NUM_MIN                 0x60
#define SMP_SVC_NUM_MAX                 0x6F

/// L2CAP SVC command
#define L2CAP_SVC_NUM_MIN               0x70
#define L2CAP_SVC_NUM_MAX               0x77

/// System SVC command
#define SYS_SVC_NUM_MIN                 0x80
#define SYS_SVC_NUM_MAX                 0x9B

/// HCI SVC command
#define HCI_SVC_NUM_MIN                 0x9C
#define HCI_SVC_NUM_MAX                 0x9F

/// LL SVC command
#define LL_SVC_NUM_MIN                  0xA0
#define LL_SVC_NUM_MAX                  0xA3

/// Reserved SVC command
#define RSV_SVC_NUM_MIN                 0xA4
#define RSV_SVC_NUM_MAX                 0xFF

/// HOST SVC command
#define HOST_SVC_NUM_MIN                GAP_SVC_NUM_MIN
#define HOST_SVC_NUM_MAX                L2CAP_SVC_NUM_MAX



/// GAP LES event
#define GAP_LES_EVENT_ID_MIN            0x10
#define GAP_LES_EVENT_ID_MAX            0x2F

/// ATT LES event
#define ATT_LES_EVENT_ID_MIN            0x30
#define ATT_LES_EVENT_ID_MAX            0x37

/// GATTM LES event
#define GATTS_LES_EVENT_ID_MIN          0x38
#define GATTS_LES_EVENT_ID_MAX          0x3F

/// GATTM LES event
#define GATTM_LES_EVENT_ID_MIN          0x40
#define GATTM_LES_EVENT_ID_MAX          0x43

/// GATTC LES event
#define GATTC_LES_EVENT_ID_MIN          0x44
#define GATTC_LES_EVENT_ID_MAX          0x4F

/// SMP LES event
#define SMP_LES_EVENT_ID_MIN            0x50
#define SMP_LES_EVENT_ID_MAX            0x5F

/// L2CAP LES event
#define L2CAP_LES_EVENT_ID_MIN          0x60
#define L2CAP_LES_EVENT_ID_MAX          0x67

/// SYS LES event
#define SYS_LES_EVENT_ID_MIN            0x80
#define SYS_LES_EVENT_ID_MAX            0x9B

/// HCI LES event
#define HCI_LES_EVENT_ID_MIN            0x9C
#define HCI_LES_EVENT_ID_MAX            0x9F

/// LL LES event
#define LL_LES_EVENT_ID_MIN             0xA0
#define LL_LES_EVENT_ID_MAX             0xA3



/// Error code range assignment
#define ERR_SUCCESS                     0x00
#define ERR_SIG                         0x01
#define ERR_CONTROLLER                  0x50
#define ERR_PROFILE                     0x70
#define ERR_HOST                        0x80
#define ERR_SYS                         0xB0
#define ERR_HCI                         0xBC
#define ERR_ICMD                        0xC0
#define ERR_GATT                        0xD0
#define ERR_RESERVED                    0xE0

#define ERR_SIG_NUM                     0x4F
#define ERR_CONTROLLER_NUM              0x20
#define ERR_PROFILE_NUM                 0x10
#define ERR_HOST_NUM                    0x30
#define ERR_SYS_NUM                     0x0C
#define ERR_HCI_NUM                     0x04
#define ERR_ICMD_NUM                    0x10
#define ERR_GATT_NUM                    0x10
#define ERR_RESERVED_NUM                0x20



/// Hardfault code range assignment
#define HARDFAULT_NONE                  0x00
#define HARDFAULT_CONTROLLER            0x01
#define HARDFAULT_HOST                  0x40
#define HARDFAULT_SYS                   0x60
#define HARDFAULT_HCI                   0x80
#define HARDFAULT_ICMD                  0xA0
#define HARDFAULT_RESERVED              0xC0



/// LES BLE definition
#define KEY_SIZE_16BYTE                 16
#define KEY_SIZE_8BYTE                  8
#define KEY_SIZE_2BYTE                  2

#define BD_ADDR_SIZE                    6
#define BD_ADDR_TYPE_PUBLIC             0
#define BD_ADDR_TYPE_RANDOM             1

#define ATT_MTU                         23

#define UUID_16_SIZE                    2
#define UUID_128_SIZE                   16



typedef enum
{
    UUID_TYPE_16BIT = 0,
    UUID_TYPE_32BIT,
    UUID_TYPE_RSV,
    UUID_TYPE_128BIT,

} UUID_TYPE;



typedef struct
{
    uint8_t     val[BD_ADDR_SIZE];      /// Little endian
    uint8_t     type;

} bd_addr_st;



typedef struct
{
    uint16_t    value_offset;
    uint16_t    value_size;
    uint8_t     *value;

} attr_value_st;



typedef struct
{
    uint8_t     type;

    union
    {
        uint8_t uuid_16[UUID_16_SIZE];
        uint8_t uuid_128[UUID_128_SIZE];
    };

} uuid_st;



typedef struct
{
    uint8_t uuid_16[UUID_16_SIZE];

} uuid_16_st;



typedef struct
{
    uint8_t uuid_128[UUID_128_SIZE];

} uuid_128_st;



#endif  /// end of _LES_DEF_H_