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
#include "ya_common.h"
#include "ya_hal_uart.h"
#include "hal_hsuart.h"

static ya_hal_os_thread_t  ya_uart_read_thread_handle=NULL;
static SemaphoreHandle_t ya_uart_read_semaphore = NULL;
#define MAX_UART_BUFFER_DATA 		1024
static uint8_t uart_data_buffer[MAX_UART_BUFFER_DATA];
static uint16_t uart_recv_len = 0;
static uint16_t uart_read_len = 0;

static void ya_uart_rx_task(void *arg)
{ 	
	int32_t res;
	uint8_t ch;
	while(1)
	{	 
		res = drv_hsuart_read_fifo (&ch, 1, HSUART_BLOCKING);
		if(res > 0)
		{
			uart_data_buffer[uart_recv_len++] = ch;
			if(uart_recv_len >= uart_read_len)
				xSemaphoreGive(ya_uart_read_semaphore);
		}
	}		 
}

int32_t ya_hal_uart_open()
{
	int32_t ret;
	drv_hsuart_init ();
    drv_hsuart_sw_rst ();
    drv_hsuart_set_fifo (HSUART_INT_RX_FIFO_TRIG_LV_16);
    drv_hsuart_set_format (BAUD_RATE, HSUART_WLS_8, HSUART_STB_1, HSUART_PARITY_DISABLE);
	if(ya_uart_read_semaphore == NULL)
		ya_uart_read_semaphore = xSemaphoreCreateBinary();
	if(ya_uart_read_thread_handle == NULL)
	{
		ret = ya_hal_os_thread_create(&ya_uart_read_thread_handle, "ya_uart_read_thread", ya_uart_rx_task, 0, 1024, 5);
		if(ret != 0)
		{
			return -1;
		}		
	}
	return 0;
}


int32_t ya_hal_uart_write(uint8_t *buffer, uint32_t len)
{
	if(!len || !buffer)
	{
		return -1;
	}

    int32_t retval;
    retval = drv_hsuart_write_fifo (buffer, len, HSUART_NON_BLOCKING);
	return 0;
}


int32_t ya_hal_uart_recv(uint8_t *buffer, uint32_t len, uint32_t timeout)
{
	if(!len || !buffer)
	{
		return -1;
	}
	uart_read_len = len;
	xSemaphoreTake(ya_uart_read_semaphore, ya_hal_os_msec_to_ticks(timeout)); 
	if(uart_recv_len >= len)
	{
		memcpy(buffer,uart_data_buffer,len);
		uart_recv_len = 0;
		return len;
	}
	return 0;
}


