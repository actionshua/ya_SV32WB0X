/*
 * Copyright(c) 2018 - 2020 Yaguan Technology Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
UART0 pin mappings used in this test demo:
            PA23(TX)
            PA18(RX)
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <FreeRTOS.h>

#include "ya_hal_uart.h"

int ya_uart_socket = -1;

// static void hsuart_isr ()
// {
//     uint8_t Buffer[32] = {0};
//     int32_t retval;

//     retval = drv_hsuart_read_fifo (Buffer, 32, HSUART_NON_BLOCKING);
//     // retval = drv_hsuart_write_fifo (Buffer, retval, HSUART_BLOCKING);
//     printf ("received length: %ld\n", retval);
//     retval = drv_hsuart_write_fifo (Buffer, retval, HSUART_NON_BLOCKING);
//     printf ("received length: %ld\n", retval);
//     printf ("\n");
// }

int32_t ya_hal_uart_open()
{
	drv_hsuart_init ();
    drv_hsuart_sw_rst ();
    drv_hsuart_set_fifo (2);//HSUART_INT_RX_FIFO_TRIG_LV_16
    drv_hsuart_set_format (BAUD_RATE, 3, 0, 0);
    // drv_hsuart_register_isr (0, hsuart_isr);//HSUART_RX_DATA_READY_IE
	return 0;
}


int32_t ya_hal_uart_write(uint8_t *buffer, uint32_t len)
{
    int32_t retval;
    retval = drv_hsuart_write_fifo (buffer, len, 1);//HSUART_NON_BLOCKING:0 HSUART_BLOCKING:1
	return 0;
}


int32_t ya_hal_uart_recv(uint8_t *buffer, uint32_t len, uint32_t timeout)
{
	int res = 0;
	uint32_t _timeout = timeout;
	uint8_t buf;
	uint8_t _len = 0;

	while(1)
	{
		res = drv_hsuart_read_fifo (&buf, 1, 0);//HSUART_NON_BLOCKING: 0
		if (res <= 0) {
			OS_MsDelay(1);
			if(_timeout-- == 0)
				break;	
		}
		else
		{
			if(_len <= len)
				buffer[_len++]=buf;
			else
				break;
			_timeout = timeout;	
		}
	}
	return _len;
}


