/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "hal/hal_uart_mesh.h"
#include "hsuart/drv_hsuart.h"

struct hal_uart mesh_uart;

int hal_uart_close(int port)
{
	return 0;
}

int hal_uart_init_cbs(int uart, hal_uart_tx_char tx_func,
	hal_uart_tx_done tx_done, hal_uart_rx_char rx_func, void * arg)
{
	struct hal_uart *u;
	u = &mesh_uart;
	u->u_rx_func = rx_func;
    u->u_tx_func = tx_func;
    u->u_tx_done = tx_done;
    u->u_func_arg = arg;
    return 0;
}

int hal_uart_tx_fill_fifo(struct hal_uart *u)
{
    int data = 0;
	//uint8_t type = 0;

	data = u->u_tx_func(u->u_func_arg);
    if (data < 0) {
        printf("%s no packet or error data to send\n", __func__);
    } else {
        //type = data;
		//printf("%s tx 0x%02X\n", __func__, type);
		//drv_hsuart_write_fifo(&type, 1, HSUART_BLOCKING);/* cmd type*/

		/*(ble_hci_uart_state.tx_cmd.data,
			ble_hci_uart_state.tx_cmd.len, HSUART_BLOCKING);*/
    }
    return data;
}

int hal_uart_start_tx(int port)
{
	struct hal_uart *u;
	int rc;
	uint8_t type;
	
	u = &mesh_uart;
	rc = hal_uart_tx_fill_fifo(u);
	printf("%s rc %d\n", __func__, rc);
	/*if (rc > 0) {
		type = rc;
		printf("%s TX type 0x%02X, rc 0x%02X\n", __func__, type, rc);
		drv_hsuart_write_fifo(&type, 1, HSUART_BLOCKING);
	}*/
	
    return rc;
}

int hal_uart_config(int uart, int32_t speed, uint8_t databits,
	uint8_t stopbits, enum hal_uart_parity parity, enum hal_uart_flow_ctl flow_ctl)
{
	return 0;
}