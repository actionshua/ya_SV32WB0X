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

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include "syscfg/syscfg.h"
#include "sysinit/sysinit.h"
#include "os/os.h"
#include "mem/mem.h"
#include "nimble/ble.h"
#include "nimble/ble_hci_trans.h"
#include "transport/ram/ble_hci_ram.h"
#include "soc_assert.h"
#include "nimble/hci_common.h"
#include "syscfg/syscfg.h"
#include "os/os_mempool.h"
#include "tools/toolbox/ilog.h"


static struct os_mbuf_pool ble_hci_ram_acl_mbuf_pool;
static struct os_mempool_ext ble_hci_ram_acl_pool;

#define ACL_BLOCK_SIZE  OS_ALIGN(MYNEWT_VAL(BLE_ACL_BUF_SIZE) \
                                 + BLE_MBUF_MEMBLOCK_OVERHEAD \
                                 + BLE_HCI_DATA_HDR_SZ, OS_ALIGNMENT)

static os_membuf_t ble_hci_ram_acl_buf[
    OS_MEMPOOL_SIZE(MYNEWT_VAL(BLE_ACL_BUF_COUNT),
                        ACL_BLOCK_SIZE)
];



static ble_hci_trans_rx_cmd_fn *ble_hci_ram_rx_cmd_hs_cb;
static void *ble_hci_ram_rx_cmd_hs_arg;

static ble_hci_trans_rx_cmd_fn *ble_hci_ram_rx_cmd_ll_cb;
static void *ble_hci_ram_rx_cmd_ll_arg;

static ble_hci_trans_rx_acl_fn *ble_hci_ram_rx_acl_hs_cb;
static void *ble_hci_ram_rx_acl_hs_arg;

static ble_hci_trans_rx_acl_fn *ble_hci_ram_rx_acl_ll_cb;
static void *ble_hci_ram_rx_acl_ll_arg;

static struct os_mempool ble_hci_ram_cmd_pool;
static os_membuf_t ble_hci_ram_cmd_buf[
        OS_MEMPOOL_SIZE(CONFIG_BT_NIMBLE_HCI_CMD_COUNT, BLE_HCI_TRANS_CMD_SZ)
];

static struct os_mempool ble_hci_ram_evt_hi_pool;
static os_membuf_t ble_hci_ram_evt_hi_buf[
    OS_MEMPOOL_SIZE(MYNEWT_VAL(BLE_HCI_EVT_HI_BUF_COUNT),
                    MYNEWT_VAL(BLE_HCI_EVT_BUF_SIZE))
];

static struct os_mempool ble_hci_ram_evt_lo_pool;
static os_membuf_t ble_hci_ram_evt_lo_buf[
        OS_MEMPOOL_SIZE(MYNEWT_VAL(BLE_HCI_EVT_LO_BUF_COUNT),
                        MYNEWT_VAL(BLE_HCI_EVT_BUF_SIZE))
];

#if CONFIG_BLE_HCI_HISTORY_DBG
#define HCI_HISTORY_SIZE 10
u8 g_hci_cmd_history[HCI_HISTORY_SIZE][CONFIG_BT_NIMBLE_HCI_EVT_BUF_SIZE];
u8 g_hci_evt_history[HCI_HISTORY_SIZE][CONFIG_BT_NIMBLE_HCI_EVT_BUF_SIZE];
u8 g_hci_history_index = 0;
u8 stop_log = 0;
#endif

void
ble_hci_trans_cfg_hs(ble_hci_trans_rx_cmd_fn *cmd_cb,
                     void *cmd_arg,
                     ble_hci_trans_rx_acl_fn *acl_cb,
                     void *acl_arg)
{
    printf("BLE_HCI_EVT_HI_BUF_COUNT %d BLE_HCI_EVT_BUF_SIZE %d\n",
        MYNEWT_VAL(BLE_HCI_EVT_HI_BUF_COUNT), MYNEWT_VAL(BLE_HCI_EVT_BUF_SIZE));
    ble_hci_ram_rx_cmd_hs_cb = cmd_cb;
    ble_hci_ram_rx_cmd_hs_arg = cmd_arg;
    ble_hci_ram_rx_acl_hs_cb = acl_cb;
    ble_hci_ram_rx_acl_hs_arg = acl_arg;
#if CONFIG_BLE_HCI_HISTORY_DBG
    memset(g_hci_cmd_history, 0, sizeof(g_hci_cmd_history));
    memset(g_hci_evt_history, 0, sizeof(g_hci_evt_history));
#endif
}

void
ble_hci_trans_cfg_ll(ble_hci_trans_rx_cmd_fn *cmd_cb,
                     void *cmd_arg,
                     ble_hci_trans_rx_acl_fn *acl_cb,
                     void *acl_arg)
{
    ble_hci_ram_rx_cmd_ll_cb = cmd_cb;
    ble_hci_ram_rx_cmd_ll_arg = cmd_arg;
    ble_hci_ram_rx_acl_ll_cb = acl_cb;
    ble_hci_ram_rx_acl_ll_arg = acl_arg;
}

void hci_dump(u8 *data, u8 type)
{

    u32 i = 0, len = 0;

    if (type == 1) {
       printf("cmd: ");
       len = data[2] + BLE_HCI_CMD_HDR_LEN;
    } else if (type == 4) {
       printf("evt: ");
       len = data[1] + 2;
    }    
    for (i = 0; i < len; i++) {
        printf("%02X", data[i]);
    }
    printf("\n");
    return;
}


int
ble_hci_trans_hs_cmd_tx(uint8_t *cmd)
{//nimble to controller, cmd is not include hci type 0x1 here
    int rc;

    ASSERT(ble_hci_ram_rx_cmd_ll_cb != NULL);
    //printf("%s %02x %02x %02x %02x\n", __func__,
    //    cmd[0], cmd[1], cmd[2], cmd[3]);
#if CONFIG_BLE_HCI_HISTORY_DBG
    if ((!stop_log)) {
        memset(&g_hci_cmd_history[g_hci_history_index][0], 0, CONFIG_BT_NIMBLE_HCI_EVT_BUF_SIZE);
        if ((cmd[2] + 3) > CONFIG_BT_NIMBLE_HCI_EVT_BUF_SIZE)
            ASSERT(0);

        memcpy(&g_hci_cmd_history[g_hci_history_index][0], cmd, cmd[2] + 3);
    }
 #endif
    rc = ble_hci_ram_rx_cmd_ll_cb(cmd, ble_hci_ram_rx_cmd_ll_arg);
    return rc;
}

#if CONFIG_BLE_HCI_HISTORY_DBG
void ble_hci_print_hci_history(void)
{
   int i = 0;

   printf("history_index %d\n", g_hci_history_index);
   for (i = 0; i < HCI_HISTORY_SIZE; i++) {
       hci_dump(&g_hci_cmd_history[i][0], 1);
       hci_dump(&g_hci_evt_history[i][0], 4);
   }
}
#endif
int
ble_hci_trans_ll_evt_tx(uint8_t *hci_ev)
{//send event to host
    int rc;

    ASSERT(ble_hci_ram_rx_cmd_hs_cb != NULL);

    uint8_t *buf;
    uint8_t param_len = 0;
    uint8_t event_len = 0;
    uint16_t buf_count = 0;
    static uint64_t print = 0;
    buf_count = ble_hci_trans_acl_buf_free_count(BLE_HCI_TRANS_BUF_EVT_HI);

    if ((buf_count < CONFIG_BT_MIN_AVAILABLE_BUFFER_SIZE_TO_NIMBLE) &&
        hci_ev[0] == BLE_HCI_EVCODE_LE_META) {
        if (!(print%100))//drop adv report if buffer is not enough
            printf("br %d %llu, param_len %d\n",  buf_count, print, hci_ev[1]);

        print++;
        return 0;
    }

    buf = ble_hci_trans_buf_alloc(BLE_HCI_TRANS_BUF_EVT_HI);
    if (buf == NULL) {
        printf("!!!!!!!!!!!!!!buf is NULL\n");
        return 0;
    }

    param_len = hci_ev[1];
    event_len = param_len + 2;
    if (event_len > (CONFIG_BT_NIMBLE_HCI_EVT_BUF_SIZE - 1)) {
        printf("event_len %d\n", event_len);
        ASSERT(0);
    }

    memcpy(buf, hci_ev, event_len);
#if CONFIG_BLE_HCI_HISTORY_DBG
    if (hci_ev && (!stop_log)) {
        memset(&g_hci_evt_history[g_hci_history_index][0], 0, CONFIG_BT_NIMBLE_HCI_EVT_BUF_SIZE);
        memcpy(&g_hci_evt_history[g_hci_history_index][0], hci_ev, event_len);
        g_hci_history_index++;
        if(g_hci_history_index >= HCI_HISTORY_SIZE)
            g_hci_history_index = 0;
    }
    if (event_len == 6 && 
        (hci_ev[5] == BLE_ERR_CMD_DISALLOWED || hci_ev[5] == 0X52/*command not process in link layer*/)) {
        printf("****stop_log***\n");
        stop_log = 1;
        ble_hci_print_hci_history();
    }
#endif
    rc = ble_hci_ram_rx_cmd_hs_cb(buf, ble_hci_ram_rx_cmd_hs_arg);
    return rc;
}

int
ble_hci_trans_hs_acl_tx(struct os_mbuf *om)
{
    int rc;

    ASSERT(ble_hci_ram_rx_acl_ll_cb != NULL);
    //printf("%s\n");
    rc = ble_hci_ram_rx_acl_ll_cb(om, ble_hci_ram_rx_acl_ll_arg);
    return rc;
}

int
ble_hci_trans_ll_acl_tx(struct os_mbuf *om)
{//nimble tx acl to host
    int rc;

    ASSERT(ble_hci_ram_rx_acl_hs_cb != NULL);

    rc = ble_hci_ram_rx_acl_hs_cb(om, ble_hci_ram_rx_acl_hs_arg);
    return rc;
}

//++werner ->
struct os_mbuf *
ble_hci_trans_acl_buf_alloc(void)
{
    uint8_t usrhdr_len;

#if MYNEWT_VAL(BLE_HS_FLOW_CTRL)
    usrhdr_len = BLE_MBUF_HS_HDR_LEN;
#else
    usrhdr_len = 0;
#endif

    return os_mbuf_get_pkthdr(&ble_hci_ram_acl_mbuf_pool, usrhdr_len);
}

uint16_t ble_hci_trans_acl_buf_free_count(int type)
{
    uint16_t count = 0;

    switch (type) {
        case BLE_HCI_TRANS_BUF_CMD:
            count = ble_hci_ram_cmd_pool.mp_num_free;
            break;

        case BLE_HCI_TRANS_BUF_EVT_HI:
            count = ble_hci_ram_evt_hi_pool.mp_num_free;        
            break;

        case BLE_HCI_TRANS_BUF_EVT_LO:
            count = ble_hci_ram_evt_lo_pool.mp_num_free;        
            break;

        case BLE_HCI_TRANS_BUF_ACL:
            count = ble_hci_ram_acl_mbuf_pool.omp_pool->mp_num_free;        
            break;

        default:
            ASSERT(0);
    }
    return count;
}
//++wenrer <-
uint8_t *
ble_hci_trans_buf_alloc(int type)
{
    uint8_t *buf = NULL;

    switch (type) {
    case BLE_HCI_TRANS_BUF_CMD:
        buf = os_memblock_get(&ble_hci_ram_cmd_pool);
        break;

    case BLE_HCI_TRANS_BUF_EVT_HI:
        buf = os_memblock_get(&ble_hci_ram_evt_hi_pool);
        if (buf == NULL) {
            /* If no high-priority event buffers remain, try to grab a
             * low-priority one.
             */
           
            buf = ble_hci_trans_buf_alloc(BLE_HCI_TRANS_BUF_EVT_LO);
        }
        break;

    case BLE_HCI_TRANS_BUF_EVT_LO:
        buf = os_memblock_get(&ble_hci_ram_evt_lo_pool);
        break;

    default:
        ASSERT(0);
        buf = NULL;
    }

    if (buf == NULL) {
        printf("****%s buf NULL****\n", __func__);
        ASSERT(0);
    }

    return buf;
}

void
ble_hci_trans_buf_free(uint8_t *buf)
{
    int rc;

    /* XXX: this may look a bit odd, but the controller uses the command
    * buffer to send back the command complete/status as an immediate
    * response to the command. This was done to insure that the controller
    * could always send back one of these events when a command was received.
    * Thus, we check to see which pool the buffer came from so we can free
    * it to the appropriate pool
    */
    if (os_memblock_from(&ble_hci_ram_evt_hi_pool, buf)) {
        rc = os_memblock_put(&ble_hci_ram_evt_hi_pool, buf);
        ASSERT(rc == 0);
    } else if (os_memblock_from(&ble_hci_ram_evt_lo_pool, buf)) {
        rc = os_memblock_put(&ble_hci_ram_evt_lo_pool, buf);
        ASSERT(rc == 0);
    } else if (os_memblock_from(&ble_hci_ram_cmd_pool, buf)) {
        //ASSERT(os_memblock_from(&ble_hci_ram_cmd_pool, buf));
        rc = os_memblock_put(&ble_hci_ram_cmd_pool, buf);
        ASSERT(rc == 0);
    }
}

/**
 * Unsupported; the RAM transport does not have a dedicated ACL data packet
 * pool.
 */
int
ble_hci_trans_set_acl_free_cb(os_mempool_put_fn *cb, void *arg)
{
    ble_hci_ram_acl_pool.mpe_put_cb = cb;
    ble_hci_ram_acl_pool.mpe_put_arg = arg;
    return 0;
}

int
ble_hci_trans_reset(void)
{
    /* No work to do.  All allocated buffers are owned by the host or
     * controller, and they will get freed by their owners.
     */
    return 0;
}

void
ble_hci_ram_init(void)
{
    int rc;

    /* Ensure this function only gets called by sysinit. */
    SYSINIT_ASSERT_ACTIVE();

    /*
     * Create memory pool of HCI command buffers. NOTE: we currently dont
     * allow this to be configured. The controller will only allow one
     * outstanding command. We decided to keep this a pool in case we allow
     * allow the controller to handle more than one outstanding command.
     */
    rc = os_mempool_init(&ble_hci_ram_cmd_pool,
                         1,
                         BLE_HCI_TRANS_CMD_SZ,
                         ble_hci_ram_cmd_buf,
                         "ble_hci_ram_cmd_pool");
    SYSINIT_PANIC_ASSERT(rc == 0);

    //printf("evt size %d, count %d\n", MYNEWT_VAL(BLE_HCI_EVT_BUF_SIZE),
    //    MYNEWT_VAL(BLE_HCI_EVT_BUF_SIZE));
    rc = os_mempool_init(&ble_hci_ram_evt_hi_pool,
                         MYNEWT_VAL(BLE_HCI_EVT_HI_BUF_COUNT),
                         MYNEWT_VAL(BLE_HCI_EVT_BUF_SIZE),
                         ble_hci_ram_evt_hi_buf,
                         "ble_hci_ram_evt_hi_pool");
    SYSINIT_PANIC_ASSERT(rc == 0);

    rc = os_mempool_init(&ble_hci_ram_evt_lo_pool,
                         MYNEWT_VAL(BLE_HCI_EVT_LO_BUF_COUNT),
                         MYNEWT_VAL(BLE_HCI_EVT_BUF_SIZE),
                         ble_hci_ram_evt_lo_buf,
                         "ble_hci_ram_evt_lo_pool");
    SYSINIT_PANIC_ASSERT(rc == 0);

    rc = os_mempool_ext_init(&ble_hci_ram_acl_pool,
                             MYNEWT_VAL(BLE_ACL_BUF_COUNT),
                             ACL_BLOCK_SIZE,
                             ble_hci_ram_acl_buf,
                             "ble_hci_uart_acl_pool");
    SYSINIT_PANIC_ASSERT(rc == 0);

    rc = os_mbuf_pool_init(&ble_hci_ram_acl_mbuf_pool,
                           &ble_hci_ram_acl_pool.mpe_mp,
                           ACL_BLOCK_SIZE,
                           MYNEWT_VAL(BLE_ACL_BUF_COUNT));
    //printf("ACL_BLOCK_SIZE %d BLE_ACL_BUF_COUNT %d\n", ACL_BLOCK_SIZE, MYNEWT_VAL(BLE_ACL_BUF_COUNT));
    SYSINIT_PANIC_ASSERT(rc == 0);
}
