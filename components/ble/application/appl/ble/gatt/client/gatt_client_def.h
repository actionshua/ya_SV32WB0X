#ifndef _GATT_CLIENT_DEF_H_
#define _GATT_CLIENT_DEF_H_



#include "stdint.h"
#include "gatt_client_api.h"
#include "appl/ble/gatt/gatt_def.h"



#define GATT_CLIENT_INVALID_CONNECTION_HANDLE           0xFFFF
#define GATT_CLIENT_INVALID_ATTRIBUTE_HANDLE            0x0000
#define GATT_CLIENT_ATTRIBUTE_HANDLE_MIN                0x0001
#define GATT_CLIENT_ATTRIBUTE_HANDLE_MAX                0xFFFF
#define GATT_CLIENT_ERR_REASON_ATTRIBUTE_NOT_FOUND      0x0A

#define UUID_LEN(_TYPE_)                                (2 << (_TYPE_))



#endif  /// end of _GATT_CLIENT_DEF_H_
