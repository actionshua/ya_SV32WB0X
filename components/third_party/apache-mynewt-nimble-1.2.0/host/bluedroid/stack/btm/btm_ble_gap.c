/******************************************************************************
 *
 *  Copyright (C) 2008-2014 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/******************************************************************************
 *
 *  This file contains functions for BLE GAP.
 *
 ******************************************************************************/

#include <string.h>
//#include <stdio.h>
#include <stddef.h>

#include "bt_types.h"
//#include "common/bt_trace.h"
#include "btm_ble_int.h"
#include "btm_ble_api.h"


/*******************************************************************************
**
** Function         BTM_CheckAdvData
**
** Description      This function is called to get ADV data for a specific type.
**
** Parameters       p_adv - pointer of ADV data
**                  type   - finding ADV data type
**                  p_length - return the length of ADV data not including type
**
** Returns          pointer of ADV data
**
*******************************************************************************/
UINT8 *BTM_CheckAdvData( UINT8 *p_adv, UINT8 type, UINT8 *p_length)
{
    UINT8 *p = p_adv;
    UINT8 length;
    UINT8 adv_type;
    //BTM_TRACE_API("BTM_CheckAdvData type=0x%02X", type);

    STREAM_TO_UINT8(length, p);

    while ( length && (p - p_adv <= BTM_BLE_CACHE_ADV_DATA_MAX)) {
        STREAM_TO_UINT8(adv_type, p);

        if ( adv_type == type ) {
            /* length doesn't include itself */
            *p_length = length - 1; /* minus the length of type */
            return p;
        }
        p += length - 1; /* skip the length of data */
        STREAM_TO_UINT8(length, p);
    }

    *p_length = 0;
    return NULL;
}