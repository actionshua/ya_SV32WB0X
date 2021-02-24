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

/*
 * Provides HCI transport over sockets. Either over
 * TCP sockets, or Linux bluetooth socket.
 *
 * E.g. to connect to TCP target, start in another window
 * socat -x PIPE:/dev/ttyACM1 TCP4-LISTEN:14433,fork,reuseaddr
 * When building this package, set BLE_SOCK_USE_TCP=1 and
 * BLE_SOCK_TCP_PORT controls the target port this transport
 * connects to.
 *
 * To use Linux Bluetooth sockets, create an interface:
 * sudo hciattach -r -n /dev/ttyUSB0 any 57600
 * And build this package with BLE_SOCK_USE_LINUX_BLUE=1,
 * BLE_SOCK_LINUX_DEV=<interface index of the target interface>
 *
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include "nimble/ble_hci_trans.h"

#include "transport/spi/ble_hci_spi.h"
#include "nimble/hci_common.h"



/**
 * Resets the HCI UART transport to a clean state.  Frees all buffers and
 * reconfigures the UART.
 *
 * @return                      0 on success;
 *                              A BLE_ERR_[...] error code on failure.
 */
int
ble_hci_trans_reset(void)
{
    icmd_reset();
}

/**
 * Sends ACL data from host to controller.
 *
 * @param om                    The ACL data packet to send.
 *
 * @return                      0 on success;
 *                              A BLE_ERR_[...] error code on failure.
 */
int
ble_hci_trans_hs_acl_tx(struct os_mbuf *om)
{
    int rc;

    printf("%s\n", __func__);
    //rc = ble_hci_uart_acl_tx(om);
    return rc;
}

static ble_hci_trans_rx_cmd_fn *ble_hci_spi_rx_cmd_cb;
static void *ble_hci_spi_rx_cmd_arg;

static ble_hci_trans_rx_acl_fn *ble_hci_spi_rx_acl_cb;
static void *ble_hci_spi_rx_acl_arg;


/**
 * Configures the HCI transport to call the specified callback upon receiving
 * HCI packets from the controller.  This function should only be called by by
 * host.
 *
 * @param cmd_cb                The callback to execute upon receiving an HCI
 *                                  event.
 * @param cmd_arg               Optional argument to pass to the command
 *                                  callback.
 * @param acl_cb                The callback to execute upon receiving ACL
 *                                  data.
 * @param acl_arg               Optional argument to pass to the ACL
 *                                  callback.
 */
void
ble_hci_trans_cfg_hs(ble_hci_trans_rx_cmd_fn *cmd_cb,
                     void *cmd_arg,
                     ble_hci_trans_rx_acl_fn *acl_cb,
                     void *acl_arg)
{
//host register callback upon receiving HCI packets from the controller
    printf("%s in ble_hci_trans_cfg_hs\n", __func__);
    ble_hci_spi_rx_cmd_cb = cmd_cb;
    ble_hci_spi_rx_cmd_arg = cmd_arg;
    ble_hci_spi_rx_acl_cb = acl_cb;
    ble_hci_spi_rx_acl_arg = acl_arg;

}


/**
 * Allocates a flat buffer of the specified type.
 *
 * @param type                  The type of buffer to allocate; one of the
 *                                  BLE_HCI_TRANS_BUF_[...] constants.
 *
 * @return                      The allocated buffer on success;
 *                              NULL on buffer exhaustion.
 */
uint8_t *ble_hci_trans_buf_alloc(int type)
{
    return 0;//should be used by controller
}


/**
 * Sends an HCI command from the host to the controller.
 *
 * @param cmd                   The HCI command to send.  This buffer must be
 *                                  allocated via ble_hci_trans_buf_alloc().
 *
 * @return                      0 on success;
 *                              A BLE_ERR_[...] error code on failure.
 */

int ble_hci_trans_hs_cmd_tx(uint8_t *cmd)
{/* 01 cmd type is not include */
    uint16_t opcode;
    uint8_t ogf, ocf;
    opcode = ((cmd[1] << 8) | cmd[0]);
    ogf = BLE_HCI_OGF(opcode);
    ocf = BLE_HCI_OCF(opcode);
    printf("%s %02X%02X%02X%02X\n", __func__, cmd[0], cmd[1], cmd[2], cmd[3]);

    switch (ogf) {
        case BLE_HCI_OGF_LINK_CTRL:
            break;
        case BLE_HCI_OGF_LINK_POLICY:
            break;
        case BLE_HCI_OGF_CTLR_BASEBAND:
            if (ocf == BLE_HCI_OCF_CB_RESET)
                icmd_reset();
            break;
        case BLE_HCI_OGF_INFO_PARAMS:
            break;
        case BLE_HCI_OGF_STATUS_PARAMS:
            break;
        case BLE_HCI_OGF_TESTING:
            break;
        case BLE_HCI_OGF_LE:
            break;
        case BLE_HCI_OGF_VENDOR:
            break;

        default:
            break;
    }
    
    return 0;
}


/**
 * Frees the specified flat buffer.  The buffer must have been allocated via
 * ble_hci_trans_buf_alloc().
 *
 * @param buf                   The buffer to free.
 */
void ble_hci_trans_buf_free(uint8_t *buf)
{

}
