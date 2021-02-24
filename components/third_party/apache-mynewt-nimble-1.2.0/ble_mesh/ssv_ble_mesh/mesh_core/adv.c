/*  Bluetooth Mesh */

/*
 * Copyright (c) 2017 Intel Corporation
 * Additional Copyright (c) 2018 Espressif Systems (Shanghai) PTE LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <errno.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include "osi/thread.h"
#include "sdkconfig.h"
#define BT_DBG_ENABLED IS_ENABLED(CONFIG_BLE_MESH_DEBUG_ADV)

#include "mesh_util.h"
#include "mesh_buf.h"
#include "mesh_bearer_adapt.h"
#include "mesh_trace.h"
#include "mesh_hci.h"

#include "mesh.h"
#include "adv.h"
#include "net.h"
#include "foundation.h"
#include "beacon.h"
#include "prov.h"
#include "proxy_server.h"

#include "provisioner_prov.h"
#include "proxy_client.h"
#include "provisioner_beacon.h"
#include "soc_assert.h"
#include "host/ble_hs.h"
#include "access.h"
#include "attrs.h"
#if CONFIG_BLE_MESH_GPIO_DBG
#include "hal_gpio.h"
#include "TurismoE.h"
#endif

/* Window and Interval are equal for continuous scanning */
//#define MESH_SCAN_INTERVAL 0x20
//#define MESH_SCAN_WINDOW   0x20

#define MESH_SCAN_INTERVAL 0x20//0x105 0x60
#define MESH_SCAN_WINDOW   0x20//0x35   0x20

u16_t g_adv_scan_window = MESH_SCAN_WINDOW;
u16_t g_adv_scan_interval = MESH_SCAN_INTERVAL;


/* Pre-5.0 controllers enforce a minimum interval of 100ms
 * whereas 5.0+ controllers can go down to 20ms.
 */
#define ADV_INT_DEFAULT_MS 20//org 100 todo: use 100 if support 5.0
#define ADV_INT_FAST_MS    20

#if defined(CONFIG_BT_HOST_CRYPTO)
#define ADV_STACK_SIZE 1024
#else
#define ADV_STACK_SIZE 768
#endif

static const bt_mesh_addr_t *dev_addr;

static const u8_t adv_type[] = {
    [BLE_MESH_ADV_PROV]   = BLE_MESH_DATA_MESH_PROV,
    [BLE_MESH_ADV_DATA]   = BLE_MESH_DATA_MESH_MESSAGE,
    [BLE_MESH_ADV_BEACON] = BLE_MESH_DATA_MESH_BEACON,
    [BLE_MESH_ADV_URI]    = BLE_MESH_DATA_URI,
    [BLE_MESH_SSV_SYNCED_ACK] = BLE_MESH_DATA_SSV_SYNCED_ACK,
};

NET_BUF_POOL_DEFINE(adv_buf_pool, CONFIG_BLE_MESH_ADV_BUF_COUNT + 3 * CONFIG_BLE_MESH_PBA_SAME_TIME,
                    BLE_MESH_ADV_DATA_SIZE, BLE_MESH_ADV_USER_DATA_SIZE, NULL);

static struct bt_mesh_adv adv_pool[CONFIG_BLE_MESH_ADV_BUF_COUNT + 3 * CONFIG_BLE_MESH_PBA_SAME_TIME];

static QueueHandle_t xBleMeshQueue;
#define BLE_MESH_QUEUE_SIZE         CONFIG_BLE_MESH_ADV_BUF_COUNT

#if defined(CONFIG_BLE_MESH_RELAY_ADV_BUF)
NET_BUF_POOL_DEFINE(relay_adv_buf_pool, CONFIG_BLE_MESH_RELAY_ADV_BUF_COUNT,
                    BLE_MESH_ADV_DATA_SIZE, BLE_MESH_ADV_USER_DATA_SIZE, NULL);

static struct bt_mesh_adv relay_adv_pool[CONFIG_BLE_MESH_RELAY_ADV_BUF_COUNT];

static QueueHandle_t xBleMeshRelayQueue;
#define BLE_MESH_RELAY_QUEUE_SIZE   CONFIG_BLE_MESH_RELAY_ADV_BUF_COUNT

#define BLE_MESH_QUEUE_SET_SIZE     (BLE_MESH_QUEUE_SIZE + BLE_MESH_RELAY_QUEUE_SIZE)

#if CONFIG_BLE_MESH_RELAY_ADV_SSV
static OsSemaphore s_mesh_queue_set_semaphore = NULL;
#else
static QueueSetHandle_t xBleMeshQueueSet;
#endif


#define BLE_MESH_RELAY_TIME_INTERVAL     K_MSEC(100)
#define BLE_MESH_MAX_TIME_INTERVAL       0xFFFFFFFF

static bool ignore_relay_packet(u32_t timestamp);
#endif /* defined(CONFIG_BLE_MESH_RELAY_ADV_BUF) */

static struct bt_mesh_adv *adv_alloc(int id)
{
    return &adv_pool[id];
}

static inline void adv_send_start(u16_t duration, int err,
                                  const struct bt_mesh_send_cb *cb,
                                  void *cb_data)
{
    if (cb && cb->start) {
        cb->start(duration, err, cb_data);
    }
}

static inline void adv_send_end(int err, const struct bt_mesh_send_cb *cb,
                                void *cb_data)
{
    if (cb && cb->end) {
        cb->end(err, cb_data);
    }
}

extern struct ble_mesh_sync_bitmap g_st_acked_bitmap;
extern struct ble_mesh_sync_bitmap g_st_acked_golden_bitmap;

u32 g_mesh_tx_count = 1;
u32 g_mesh_tx_duration = 0;

struct bt_mesh_ssv_sync_ack ssv_ack_from_tx[NUM_TX_NODE];

void init_sync_adv(void)
{
    memset(&ssv_ack_from_tx, 0, sizeof(ssv_ack_from_tx));
}


void save_ssv_ack_info(u16_t from, u32_t seq, u32_t bitmap_low, u32_t bitmap_high)
{
    u8_t i = 0;
    u8_t test = 0;
    int first_null_location = -1;

    for (i = 0; i < NUM_TX_NODE; i++) {
        if (ssv_ack_from_tx[i].from == 0) {
            if (first_null_location == -1)
                first_null_location = i;
        } else if (ssv_ack_from_tx[i].from == from) {
            if (ssv_ack_from_tx[i].acked && (seq == ssv_ack_from_tx[i].seq))
                return;

            ssv_ack_from_tx[i].from = from;
            ssv_ack_from_tx[i].seq = seq;
            ssv_ack_from_tx[i].bitmap.low = bitmap_low;
            ssv_ack_from_tx[i].bitmap.high = bitmap_high;
            ssv_ack_from_tx[i].acked = 0;
            //printf("save %d at %d bp %llx\n", from, i, bitmap);
            return;
        }
    }

    if(first_null_location >= 0) {
        ssv_ack_from_tx[first_null_location].from = from;
        ssv_ack_from_tx[first_null_location].seq = seq;
        ssv_ack_from_tx[first_null_location].bitmap.low = bitmap_low;
        ssv_ack_from_tx[first_null_location].bitmap.high = bitmap_high;
        ssv_ack_from_tx[first_null_location].acked = 0;
        //printf("end save %d at %d bp %llx\n", from, first_null_location, bitmap);
    }
}

void get_ssv_ack_bitmap(struct ble_mesh_sync_bitmap *bitmap, u16_t from)
{
    u8_t i = 0;

    for (i = 0; i < NUM_TX_NODE; i++) {
        if (ssv_ack_from_tx[i].from == from) {
            //printf("from %d bp %08x %08x\n", from, ssv_ack_from_tx[i].bitmap.high, ssv_ack_from_tx[i].bitmap.low);
            bitmap->low = ssv_ack_from_tx[i].bitmap.low;
            bitmap->high = ssv_ack_from_tx[i].bitmap.high;
            return;
        }
    }

    //printf("get_ssv_ack_bitmap end return 0\n");
    return;
}

void clean_ssv_ack_info(u16_t from)
{
    u8_t i = 0;

    for (i = 0; i < NUM_TX_NODE; i++) {
        if (ssv_ack_from_tx[i].from == from) {
            //printf("clean %d \n", from);
            ssv_ack_from_tx[i].acked = 0;
            ssv_ack_from_tx[i].bitmap.low = 0;
            ssv_ack_from_tx[i].bitmap.high = 0;
            break;
        }
    }
}

void set_ssv_ack_info_acked(u16_t from)
{
    u8_t i = 0;

    for (i = 0; i < NUM_TX_NODE; i++) {
        if (ssv_ack_from_tx[i].from == from) {
            ssv_ack_from_tx[i].acked = 1;
            //ssv_ack_from_tx[i].bitmap.low = 0;
            //ssv_ack_from_tx[i].bitmap.high = 0;
            //printf("%d acked\n", from);
        }
    }
}

void show_ssv_ack_info_acked_node()
{
    u8_t i = 0;

    /*for (i = 0; i < NUM_TX_NODE; i++) {
        printf("f %d, ak %d, bp %llx\n",
            ssv_ack_from_tx[i].from, ssv_ack_from_tx[i].acked, ssv_ack_from_tx[i].bitmap);

    }*/
}

u8_t get_shift_bit(u16_t addr, u8_t *shift_bit, u8_t *low)/* low 1: low part, low 0: high part*/
{
    u8_t shift = 0;

    if (shift_bit == NULL || low == NULL)
        return 0;/* input fail*/

    //bt_mesh_primary_addr()
    shift = addr - 1;

    if (shift <= 31) {
        *low = 1;
        *shift_bit = shift;
    } else {
        shift -= 32;
        *low = 0;
        *shift_bit = shift;
    }

    return 1;
}

u8 is_receive_my_ack(u16_t tx_node)
{
    u8_t shift = 0, low = 0, ret = 0;
    struct ble_mesh_sync_bitmap bitmap_from_tx;
    u32_t bitmap_part = 0, bitmap_location = 0;

    memset(&bitmap_from_tx, 0, sizeof(bitmap_from_tx));
    get_ssv_ack_bitmap(&bitmap_from_tx, tx_node);
    if ((bitmap_from_tx.low == 0 && bitmap_from_tx.high == 0)
     || bt_mesh_primary_addr() == 0) {
        //printf("0 no ack\n");
        return 0;
    }
    //printf("ack bp %08X %08X\n", bitmap_from_tx.high, bitmap_from_tx.low);
    ret = get_shift_bit(bt_mesh_primary_addr(), &shift, &low);
    if (ret == 0)
        return 0;

    if (low)
        bitmap_part = bitmap_from_tx.low;
    else
        bitmap_part = bitmap_from_tx.high;

    bitmap_location |= (1 << shift);

    if (bitmap_part & bitmap_location) {
        //printf("get ack %x %x, low %d, tx_node %d\n", bitmap_part, bitmap_location, low, tx_node);
        return 1;
    }

    //printf("1 no ack\n");
    return 0;
}

#define JUDEGE_EXIT_ACK_LOOP(x)    \
    if (xmit ==0) {    \
        printf(x);    \
        goto ACK_EXIT;    \
    }    \

#define RELEASE_NET_BUFFER(buf, cb, cb_data)    \
    net_buf_unref(buf);    \
    adv_send_start(duration, err, cb, cb_data);    \
    if (err) {    \
        BT_ERR("%s, Advertising failed: err %d", __func__, err);    \
        return err;    \
    }    \
    adv_send_end(err, cb, cb_data);    \


static void bt_mesh_task_post(bt_mesh_msg_t *msg, uint32_t timeout);

extern uint8_t g_new_run_begin;

#define ACKMSG_COUNT 10

u8_t golden_bitmap_valid(void)
{
    if(g_st_acked_golden_bitmap.low || g_st_acked_golden_bitmap.high)
        return  1;
    else
        return  0;
}

u8_t golden_bitmap_match(void)
{
    if((g_st_acked_golden_bitmap.low == g_st_acked_bitmap.low) &&
        (g_st_acked_golden_bitmap.high == g_st_acked_bitmap.high))
        return  1;
    else
        return  0;
}

u8_t is_bitmap_the_same(struct ble_mesh_sync_bitmap a, struct ble_mesh_sync_bitmap b)
{
    if ((a.low == b.low) && (a.high == b.high))
        return 1;
    else
        return 0;
}

void assign_bitmap(struct ble_mesh_sync_bitmap *a, struct ble_mesh_sync_bitmap b)
{
    if (a == NULL)
        return;

    a->low = b.low;
    a->high = b.high;
}

void or_bitmap(struct ble_mesh_sync_bitmap *a, struct ble_mesh_sync_bitmap b)
{
    a->low = (a->low | b.low);
    a->high = (a->high | b.high);
}

u8 g_MeshMsgGap = 20;
u8 g_MeshSyncGap = 20;
u8 g_MeshAckGap = 30;

u8 g_MeshMsgSleepGap = 30;
u8 g_MeshSyncSleepGap = 30;
u8 g_MeshAckSleepGap = 30;

#define MSH_SEND_SEGMENT_MSG_COUNT 6 /*count * 20 (interval)*/
#define BLCOK_FIRST_ACK_COUNT 10
#define SEND_ACK_COUNT 20
#define MSH_SYNC_COUNT_UNSEG 14
#define MSH_SYNC_COUNT_SEG 50
#define MSH_MSG_SEG_STATUS_XMIT 65
u8 g_msg_seg_status_xmit = 0;
#define SEGMSG_LAST_PART_LOOP_COUNT 4

#if CONFIG_BLE_MESH_GPIO_DBG
u32 g_test_msg_sync_adv_start_end = CONFIG_BLE_MESH_GPIO_TEST_MSG_SYNC_ADV_START_END;
u32 g_test_msg_ack_start_end = CONFIG_BLE_MESH_GPIO_TEST_ACK_START_END;
#endif

void config_dbg_gpio(u32 test_start_end)
{

}
extern u8 g_Meshtesting;

//static inline int adv_send(struct net_buf *buf)//todo
static int adv_send(struct net_buf *buf)
//static int adv_send(struct net_buf *buf)
{
    const s32_t adv_int_min = ((bt_mesh_dev.hci_version >= BLE_MESH_HCI_VERSION_5_0) ?
                               ADV_INT_FAST_MS : ADV_INT_DEFAULT_MS);
    const struct bt_mesh_send_cb *cb = BLE_MESH_ADV(buf)->cb;
    void *cb_data = BLE_MESH_ADV(buf)->cb_data;
    struct bt_mesh_adv_param param = {0};
    u16_t duration, adv_int;
    struct bt_mesh_adv_data ad = {0};
    int err = 0;;
    u32 group_id;
    u8_t ack = 0;
    u8_t need_sync_adv_followed = 0;
    u8_t sync_send_count = 1;

    u32 xmit = BLE_MESH_ADV(buf)->xmit;
    //BLE_MESH_ADV(buf)->xmit = g_mesh_tx_count;
    adv_int = MAX(adv_int_min,
                  BLE_MESH_TRANSMIT_INT(BLE_MESH_ADV(buf)->xmit));
    duration = (BLE_MESH_TRANSMIT_COUNT(BLE_MESH_ADV(buf)->xmit) + 1) *
               (adv_int + 10);

    BT_DBG("adv_int_min %u , xmit %u, adv_int %d", adv_int_min, BLE_MESH_TRANSMIT_INT(BLE_MESH_ADV(buf)->xmit), adv_int);
    BT_DBG("type %u len %u: %s", BLE_MESH_ADV(buf)->type,
           buf->len, bt_hex(buf->data, buf->len));

    ad.type = adv_type[BLE_MESH_ADV(buf)->type];
    ad.data_len = buf->len;
    ad.data = buf->data;

    ack = buf->ack;
    need_sync_adv_followed = buf->need_synced_adv;
    param.options = 0U;
    param.interval_min = ADV_SCAN_UNIT(adv_int);
    param.interval_max = param.interval_min;

    BT_DBG("count %u interval %ums duration %ums, buf->type %d, ad.type %x, ack %d\n",
        BLE_MESH_TRANSMIT_COUNT(BLE_MESH_ADV(buf)->xmit) + 1, adv_int,
        duration, BLE_MESH_ADV(buf)->type, ad.type, buf->ack);

    bt_mesh_adv_buf_ref_debug(__func__, buf, 3U, BLE_MESH_BUF_REF_SMALL);
    //OS_MsDelay((OS_Random()&0xF));//++ssv

    if (need_sync_adv_followed) {
        g_Meshtesting = 1;
        struct bt_mesh_adv_data sync_adv_ad = {0};
        bt_mesh_msg_t sync_adv_msg;
        bt_mesh_msg_t segmsg[CONFIG_BLE_MESH_TX_SEG_MAX];
        struct net_buf **sync_adv_buf;
        const struct bt_mesh_send_cb *sync_cb;
        void *sync_cb_data;
        u8_t tx_msg = 1;/*disable when txnode bitmap equal to golden bitmap*/
        u8_t segmsg_count = 0;
        u8_t segmsg_last_part_loop_count = SEGMSG_LAST_PART_LOOP_COUNT;
        //printf("need_sync_adv_followed\n");
        memset(&segmsg, 0, sizeof(segmsg));
        /* message need ssv sync adv*/
        while (1) {
            xQueueReceive(xBleMeshQueue, &sync_adv_msg, K_NO_WAIT);
            sync_adv_buf = (struct net_buf **)(&sync_adv_msg.arg);
            if (!(*sync_adv_buf)) {/*no data*/
                BT_ERR("no sync_adv_msg net buf in adv send");
                ASSERT(0);
            }

            if (BLE_MESH_ADV(*sync_adv_buf)->type == BLE_MESH_SSV_SYNCED_ACK){
                //printf("SYNCED_ACK break\n");
                break;
            } else if (segmsg_count >= CONFIG_BLE_MESH_TX_SEG_MAX)
                break;
            else if ((*sync_adv_buf)->segment_seq) {
                if (segmsg_count + 1 > (*sync_adv_buf)->segment_seq)
                    break;/*sequence is not encrease, error, so break*/

                //printf("seqq %d\n", (*sync_adv_buf)->segment_seq);
                memcpy(&segmsg[segmsg_count], &sync_adv_msg, sizeof(sync_adv_msg));
                segmsg_count++;
            } else {
                //printf("adv send other, break\n");
                break;
            }
        }

        sync_adv_ad.type = adv_type[BLE_MESH_ADV(*sync_adv_buf)->type];
        sync_adv_ad.data_len = (*sync_adv_buf)->len;
        sync_adv_ad.data = (*sync_adv_buf)->data;

        sync_cb = BLE_MESH_ADV(*sync_adv_buf)->cb;
        sync_cb_data = BLE_MESH_ADV(*sync_adv_buf)->cb_data;

        g_new_run_begin = 0;
        xmit = 14;

        if (segmsg_count) {
            xmit = MSH_SYNC_COUNT_SEG;
            sync_send_count = 3;
        }

#if CONFIG_BLE_MESH_GPIO_DBG
        POOL_HIGH_GPIO(g_test_msg_sync_adv_start_end);
#endif
        //printf("g_new_run_begin %d, xmit %d\n", g_new_run_begin, xmit);
        while ((!g_new_run_begin) && xmit) {
            if (golden_bitmap_valid() &&
                (golden_bitmap_match()) &&
                (xmit > 4)) {/* receive all ack so stop tx message*/
                    xmit = 4;
                    tx_msg = 0;
                    printf("receive all\n");
            }

            /*tx message and sync adv interlance*/
            /*tx onoff message, or vendor msg*/
            if (tx_msg) {
                //k_sleep((OS_Random()&0xF));
                param.interval_min = ADV_SCAN_UNIT(g_MeshMsgGap);
                param.interval_max = ADV_SCAN_UNIT(g_MeshMsgGap);

                if (!segmsg_count) {/* unsegment msg, onoff */
                    err = bt_le_adv_start(&param, &ad, 1, NULL, 0);
                    if (err && (err != BLE_HS_ENOMEM) && (err != BLE_HS_EALREADY)) {
                        printf("adv_send error %d\n", err);
                        ASSERT(0);
                    }
                    //printf("tus %d\n", g_MeshMsgSleepGap);
                    k_sleep(K_MSEC(g_MeshMsgSleepGap));//adv_int
                    bt_le_adv_stop();
                } else {/* segment msg, vendor msg */
                    struct bt_mesh_adv_data seg_ad = {0};
                    struct net_buf **seg_adv_buf= NULL;

                    //tx seg 0
                    //printf("tx seg 0\n");
                    err = bt_le_adv_start(&param, &ad, 1, NULL, 0);
                    if (err && (err != BLE_HS_ENOMEM) && (err != BLE_HS_EALREADY)) {
                        //printf("adv_send error %d\n", err);
                        ASSERT(0);
                    }

                    k_sleep(K_MSEC(g_MeshMsgSleepGap * MSH_SEND_SEGMENT_MSG_COUNT));//adv_int
                    bt_le_adv_stop();

                    //tx seg others/* only tx one loop ex: seg 0 ~ 5, segment 6 tx with sync adv later*/
                    for (int i = 0; i < (segmsg_count - 1); i++) {
                        seg_adv_buf = (struct net_buf **)(&segmsg[i].arg);
                        seg_ad.type = adv_type[BLE_MESH_ADV(*seg_adv_buf)->type];
                        seg_ad.data_len = (*seg_adv_buf)->len;
                        seg_ad.data = (*seg_adv_buf)->data;
                        //printf("tx seg %d\n", i + 1);
                        err = bt_le_adv_start(&param, &seg_ad, 1, NULL, 0);
                        if (err && (err != BLE_HS_ENOMEM) && (err != BLE_HS_EALREADY)) {
                            printf("adv_send error %d\n", err);
                            ASSERT(0);
                        }

                        k_sleep(K_MSEC(g_MeshMsgSleepGap * MSH_SEND_SEGMENT_MSG_COUNT));//adv_int
                        bt_le_adv_stop();
                        //xmit --;
                        //if (!xmit)
                        //    break;
                    }
                    tx_msg  = 0;
                }
            }

            if (g_new_run_begin)
                break;

            if (segmsg_count) {
                struct bt_mesh_adv_data seg_ad = {0};
                struct net_buf **seg_adv_buf= NULL;

                segmsg_last_part_loop_count --;
                /* send last segment part*/
                seg_adv_buf = (struct net_buf **)(&segmsg[segmsg_count - 1].arg);
                seg_ad.type = adv_type[BLE_MESH_ADV(*seg_adv_buf)->type];
                seg_ad.data_len = (*seg_adv_buf)->len;
                seg_ad.data = (*seg_adv_buf)->data;
                //printf("tx seg %d\n", i + 1);
                if (segmsg_last_part_loop_count == (SEGMSG_LAST_PART_LOOP_COUNT - 1)) {
                /* first time, wait for rx status  segment msg*/
                    err = bt_le_adv_start(&param, &seg_ad, 1, NULL, 0);
                    if (err && (err != BLE_HS_ENOMEM) && (err != BLE_HS_EALREADY)) {
                        printf("adv_send error %d\n", err);
                        ASSERT(0);
                    }
                    k_sleep(K_MSEC(g_MeshMsgSleepGap + 10));
                    bt_le_adv_stop();

                    k_sleep(K_MSEC(200));
                } else if (segmsg_last_part_loop_count) {
                /* second to x time, wait for rx status  segment msg*/
                    err = bt_le_adv_start(&param, &seg_ad, 1, NULL, 0);
                    if (err && (err != BLE_HS_ENOMEM) && (err != BLE_HS_EALREADY)) {
                        printf("adv_send error %d\n", err);
                        ASSERT(0);
                    }
                    k_sleep(K_MSEC(g_MeshMsgSleepGap + 10));
                    bt_le_adv_stop();

                    k_sleep(K_MSEC(50));
                } else {/* last time, do not need to wait,just send sync adv*/
                    xmit = 5;/* send 5 time sync and end*/

                }
            }

            while (1) {
                struct ble_mesh_sync_bitmap zero_bitmap;
                if (g_new_run_begin)
                    break;

                taskYIELD();
                memset(&zero_bitmap, 0, sizeof(zero_bitmap));
                if(memcmp(&zero_bitmap, &g_st_acked_bitmap, sizeof(zero_bitmap)) == 0)
                    k_sleep(10);/* do not receive any ack from rx, just sleep and scan*/
                else/* receive at least one ack from rx, send sync adv*/
                    break;
            }

            for (int i = 0; i < sync_send_count; i++) {
                //printf("tsa %d\n", g_MeshMsgSleepGap);
                /* tx sync adv*/
                taskYIELD();
                if (g_new_run_begin)
                    break;

                memcpy((*sync_adv_buf)->data + ((*sync_adv_buf)->len - sizeof(g_st_acked_bitmap)), &g_st_acked_bitmap,
                    sizeof(g_st_acked_bitmap));

                //k_sleep((OS_Random()&0xF));
                param.interval_min = ADV_SCAN_UNIT(g_MeshSyncGap);
                param.interval_max = ADV_SCAN_UNIT(g_MeshSyncGap);
                err = bt_le_adv_start(&param, &sync_adv_ad, 1, NULL, 0);
                if (err && (err != BLE_HS_ENOMEM) && (err != BLE_HS_EALREADY)) {
                    printf("adv_send error %d\n", err);
                    ASSERT(0);
                }

                k_sleep(K_MSEC(g_MeshMsgSleepGap));
                bt_le_adv_stop();
                xmit --;
                if(!xmit)
                    break;

                if (g_new_run_begin)
                    break;

                if (segmsg_count)
                    k_sleep(60);
            }

            //taskYIELD();
        }
#if CONFIG_BLE_MESH_GPIO_DBG
        POOL_LOW_GPIO(g_test_msg_sync_adv_start_end);//send ssv sync ack end
#endif

        RELEASE_NET_BUFFER(buf, cb, cb_data);
        RELEASE_NET_BUFFER(*sync_adv_buf, sync_cb, sync_cb_data);

        for (int i = 0; i <segmsg_count; i++){
            struct net_buf **seg_adv_buf= NULL;
            seg_adv_buf = (struct net_buf **)(&segmsg[i].arg);
            const struct bt_mesh_send_cb *seg_cb;
            void *seg_cb_data;

            seg_cb = BLE_MESH_ADV(*seg_adv_buf)->cb;
            seg_cb_data = BLE_MESH_ADV(*seg_adv_buf)->cb_data;
            RELEASE_NET_BUFFER(*seg_adv_buf, seg_cb, seg_cb_data);
        }
    } else if (buf->ack) {
        g_Meshtesting = 1;
        //printf("ack1\n");
        /* onoff status */
        xmit = SEND_ACK_COUNT;
        struct bt_mesh_adv_param ack_param = {0};
        struct bt_mesh_adv_data ack_ad = {0};
        bt_mesh_msg_t ackmsg[ACKMSG_COUNT];
        u8    msg_acked[ACKMSG_COUNT];
        struct net_buf **ackbuf = NULL;

        memset(&ackmsg, 0, sizeof(ackmsg));
        memset(&msg_acked, 0, sizeof(msg_acked));
        u8 location = 0;
        u8 buf_acked = 0;
        u8 do_tx = 0;
        u8 seg_acked = 0;
        bt_mesh_msg_t segmsg[CONFIG_BLE_MESH_TX_SEG_MAX];
        u8 segmsg_acked[CONFIG_BLE_MESH_TX_SEG_MAX];
        u8_t segmsg_count = 0;


        memset(&segmsg, 0, sizeof(segmsg));
        memset(&segmsg_acked, 0, sizeof(segmsg_acked));
#if 0
        u8 first_tx_org_ack = 1;
        u8 block_count = 0;
#endif

#if CONFIG_BLE_MESH_GPIO_DBG
        POOL_HIGH_GPIO(g_test_msg_ack_start_end);
#endif
        ack_param.options = 0U;
        ack_param.interval_min = ADV_SCAN_UNIT(g_MeshAckGap);
        ack_param.interval_max = ack_param.interval_min;

        param.options = 0U;
        param.interval_min = ADV_SCAN_UNIT(g_MeshAckGap);
        param.interval_max = param.interval_min;

        show_ssv_ack_info_acked_node();

        if (buf->segment && g_msg_seg_status_xmit)
            xmit = g_msg_seg_status_xmit;
        else if (buf->segment)
            xmit = MSH_MSG_SEG_STATUS_XMIT;

        while(xmit > 0) {
            //printf("ih %d\n", xmit);
            bt_mesh_msg_t tempmsg;
            struct net_buf **temp_net_buf;
            while (1) {
                memset(&tempmsg, 0, sizeof(tempmsg));
                xQueueReceive(xBleMeshQueue, &tempmsg, K_NO_WAIT);
                temp_net_buf = (struct net_buf **)(&tempmsg.arg);
                if (!(*temp_net_buf))/*no data*/
                    break;
                else if ((*temp_net_buf)->segment && (*temp_net_buf)->ack) {
                    //printf("ag segmsg_count %d\n", segmsg_count);
                    memcpy(&segmsg[segmsg_count], &tempmsg, sizeof(tempmsg));
                    segmsg_count ++;
                    if (segmsg_count >= CONFIG_BLE_MESH_TX_SEG_MAX)
                        break;

                    if ((*temp_net_buf)->segment_seq == 0) {/* new seg 0 packet, new test run*/
                        struct net_buf **seg_net_buf = NULL;
                        //printf("seg new ack coming %d\n", (*temp_net_buf)->remote_addr);
                        for (int i = 0; i < segmsg_count; i++) {
                            seg_net_buf = (struct net_buf **)(&segmsg[i].arg);

                            if ((*seg_net_buf)->remote_addr == (*temp_net_buf)->remote_addr) {
                                segmsg_acked[i] = true;/* new seg ack message coming, ignore old ack*/
                                xmit = SEND_ACK_COUNT * ((*seg_net_buf)->segment_seq); /* new ack */
                            }
                        }
                    }
                } else if ((*temp_net_buf)->ack){/* unsegment ack */
                    memcpy(&ackmsg[location], &tempmsg, sizeof(tempmsg));
                    //printf("us %d\n", location);

                    if (buf->remote_addr == (*temp_net_buf)->remote_addr) {
                        printf("new ack coming %d, %d, set buf_acked = 1\n", buf->remote_addr, (*temp_net_buf)->remote_addr);
                        buf_acked = true;/* new message coming, ignore old ack*/
                        xmit = SEND_ACK_COUNT; /* new ack */
                    }

                    for (int i = 0; i < location; i++) {
                        //printf("us i %d %d\n", i, location);
                        struct net_buf **ackbuf_queue;
                        ackbuf_queue = (struct net_buf **)(&ackmsg[i].arg);
                        if (!(*ackbuf_queue))
                            break;/*no data*/
                        else {
                            if ((*temp_net_buf)->remote_addr == (*ackbuf_queue)->remote_addr) {
                                //printf("set acked %d, addr %d %d\n",
                                //    i, (*temp_net_buf)->remote_addr, (*ackbuf_queue)->remote_addr);
                                msg_acked[i] = 1;
                                xmit = SEND_ACK_COUNT; /* new ack */
                            }
                        }
                    }
                    location ++;
                } else {
                    /* not ack message, just mark receive ack and push back to queue later*/
                    //printf("get other msg at location %d\n", location);
                    memcpy(&ackmsg[location], &tempmsg, sizeof(tempmsg));
                    msg_acked[location] = 1;
                    location ++;
                }
            }

            for (int i = 0; i < location; i++) {
                /*tx ack msg in xBleMeshQueue*/
                ackbuf = (struct net_buf **)(&ackmsg[i].arg);
                if (msg_acked[i])
                    continue;

                if ((*ackbuf)) {
                    ack_ad.type = adv_type[BLE_MESH_ADV(*ackbuf)->type];
                    ack_ad.data_len = (*ackbuf)->len;
                    ack_ad.data = (*ackbuf)->data;
                    err = bt_le_adv_start(&ack_param, &ack_ad, 1, NULL, 0);
                    if (err && (err != BLE_HS_ENOMEM) && (err != BLE_HS_EALREADY)) {
                        //printf("ack adv_send error %d\n", err);
                        ASSERT(0);
                    }
                    //printf("t %d %d\n", (*ackbuf)->remote_addr, g_MeshAckSleepGap);
                    k_sleep(K_MSEC(g_MeshAckSleepGap));//adv_int + 5
                    bt_le_adv_stop();
                    OS_MsDelay((OS_Random()&0x3));
                    xmit--;
                }

                JUDEGE_EXIT_ACK_LOOP("ack queue end\n");
            }

            if((!buf_acked) &&
                (is_receive_my_ack(buf->remote_addr) || (!xmit))) {
                set_ssv_ack_info_acked(buf->remote_addr);
                //printf("tx %d get my ak\n", buf->remote_addr);
                buf_acked = 1;
            } else if ((!buf_acked) && xmit) {
            //tx buf ack
#if 0
                if (first_tx_org_ack &&/*for item 8 ,seperate 2 part for reply ack, 1-24, 25-50*/
                    (bt_mesh_primary_addr() > 24) &&
                    (location == 0)/*there is no other ack need to be send*/) {
                    k_sleep(K_MSEC(10));
                    block_count++;
                    if (block_count < BLCOK_FIRST_ACK_COUNT)
                        continue;
                }

                if (first_tx_org_ack && block_count) {
                    xmit -= (block_count/2);
                    printf("block_count %d\n", block_count);
                }
#endif
                xmit--;
                //printf("ato %d %d\n", buf->remote_addr, g_MeshAckSleepGap);
                err = bt_le_adv_start(&param, &ad, 1, NULL, 0);
                if (err && (err != BLE_HS_ENOMEM) && (err != BLE_HS_EALREADY)) {
                    //printf("original ack adv_send error %d\n", err);
                    ASSERT(0);
                }
                k_sleep(K_MSEC(g_MeshAckSleepGap));//adv_int + 5
#if 0
                first_tx_org_ack = 0;
#endif
                bt_le_adv_stop();
            }

            JUDEGE_EXIT_ACK_LOOP("atx org end\n");

            for (int i = 0; i < segmsg_count ; i++) {
                /*tx ack msg in xBleMeshQueue*/
                ackbuf = (struct net_buf **)(&segmsg[i].arg);
                if ((*ackbuf)) {
                    ack_ad.type = adv_type[BLE_MESH_ADV(*ackbuf)->type];

                    if (segmsg_acked[i])
                        continue;

                    ack_ad.data_len = (*ackbuf)->len;
                    ack_ad.data = (*ackbuf)->data;
                    //printf("ats %d\n", i);
                    err = bt_le_adv_start(&ack_param, &ack_ad, 1, NULL, 0);
                    if (err && (err != BLE_HS_ENOMEM) && (err != BLE_HS_EALREADY)) {
                        //printf("ack adv_send error %d\n", err);
                        ASSERT(0);
                    }
                    //printf("st %d %d\n", (*ackbuf)->remote_addr, g_MeshAckSleepGap);
                    k_sleep(K_MSEC(g_MeshAckSleepGap));//adv_int + 5
                    bt_le_adv_stop();
                    OS_MsDelay((OS_Random()&0x3));
                    xmit--;
                }

                JUDEGE_EXIT_ACK_LOOP("seg queue end\n");
            }

            JUDEGE_EXIT_ACK_LOOP("o buf end\n");

            //if (location)
            //    printf("location %d\n", location);

            for (int i = 0; i < location; i++) {/* check if tx get rx's ack*/
                ackbuf = (struct net_buf **)(&ackmsg[i].arg);
                if ((!msg_acked[i]) &&
                    (is_receive_my_ack((*ackbuf)->remote_addr) || (!xmit))) {
                    set_ssv_ack_info_acked((*ackbuf)->remote_addr);
                    //printf("g %d\n", (*ackbuf)->remote_addr);
                    msg_acked[i] = 1;
                }
            }

            //if (segmsg_count)
                //printf("segmsg_count %d\n", segmsg_count);

            for (int i = 0; i < segmsg_count ; i++) {/* check if tx get rx's ack*/
                ackbuf = (struct net_buf **)(&segmsg[i].arg);
                if ((!segmsg_acked[i]) &&
                    (is_receive_my_ack((*ackbuf)->remote_addr) || (!xmit))) {
                    set_ssv_ack_info_acked((*ackbuf)->remote_addr);
                    segmsg_acked[i] = 1;
                    //if (buf->remote_addr == (*ackbuf)->remote_addr)
                    //    buf_acked = 1;
                }
            }

            do_tx = 0;
            if (buf_acked == 0) {
                //printf("buf_acked = 0, do tx\n");
                do_tx = 1;
            } else if (buf_acked == 1) {//check if tx node still do not receive ack
                for (int i = 0; i < location; i++) {
                    if(msg_acked[i] == 0) {
                        do_tx = 1;
                        //printf("msg_acked %d, do tx\n", msg_acked[i]);
                        break;
                    }
                }

                if (!do_tx) {
                    for (int i = 0; i < segmsg_count; i++) {
                        if(segmsg_acked[i] == 0) {
                            //printf("segmsg_acked %d, do tx\n", segmsg_acked[i]);
                            do_tx = 1;
                            break;
                        }
                    }
                }
            }
            taskYIELD();
            if (!do_tx) {
ACK_EXIT:
                //printf("ack end %d %d %d %d %d %d, L %d\n",
                //    msg_acked[0], msg_acked[1], msg_acked[2],
                //    msg_acked[3], msg_acked[4], msg_acked[5], location);
                show_ssv_ack_info_acked_node();

                if (buf_acked)
                    clean_ssv_ack_info(buf->remote_addr);

                break;
            }
        }//while end
#if CONFIG_BLE_MESH_GPIO_DBG
        POOL_LOW_GPIO(g_test_msg_ack_start_end);
#endif
        for (int i = 0; i < location; i++) {
            ackbuf = (struct net_buf **)(&ackmsg[i].arg);
            if ((*ackbuf)->ack) {
                const struct bt_mesh_send_cb *ack_cb = BLE_MESH_ADV(*ackbuf)->cb;
                void *ack_cb_data = BLE_MESH_ADV(*ackbuf)->cb_data;

                clean_ssv_ack_info((*ackbuf)->remote_addr);

                net_buf_unref(*ackbuf);
                adv_send_start(duration, err, ack_cb, ack_cb_data);
                adv_send_end(err, cb, cb_data);
            } else/* push back non ack message*/
                bt_mesh_task_post(&ackmsg[i], portMAX_DELAY);
        }

        for (int i = 0; i < segmsg_count; i++) {
            ackbuf = (struct net_buf **)(&segmsg[i].arg);
            const struct bt_mesh_send_cb *ack_cb = BLE_MESH_ADV(*ackbuf)->cb;
            void *ack_cb_data = BLE_MESH_ADV(*ackbuf)->cb_data;

            clean_ssv_ack_info((*ackbuf)->remote_addr);

            net_buf_unref(*ackbuf);
            adv_send_start(duration, err, ack_cb, ack_cb_data);
            adv_send_end(err, cb, cb_data);
        }

        RELEASE_NET_BUFFER(buf, cb, cb_data);
        //printf("ack end\n");
    } else {/* normal */
        if (BLE_MESH_ADV(buf)->type == BLE_MESH_ADV_BEACON && g_Meshtesting) {
            net_buf_unref(buf);
            adv_send_start(duration, err, cb, cb_data);
            adv_send_end(err, cb, cb_data);
            return 0;
        }

        err = bt_le_adv_start(&param, &ad, 1, NULL, 0);
        if (err && (err != BLE_HS_ENOMEM) && (err != BLE_HS_EALREADY)) {
            printf("adv_send error %d\n", err);
            ASSERT(0);
        }
        net_buf_unref(buf);
        adv_send_start(duration, err, cb, cb_data);
        if (err) {
            BT_ERR("%s, Advertising failed: err %d", __func__, err);
            return err;
        }

        BT_DBG("Advertising started. Sleeping %u ms", duration);
        //printf("Advertising started. Sleeping %u ms, nack %d\n", duration, ack);

        k_sleep(K_MSEC(duration));

        err = bt_le_adv_stop();
        adv_send_end(err, cb, cb_data);
        if (err) {
            BT_ERR("%s, Stop advertising failed: err %d", __func__, err);
            return 0;
        }

        BT_DBG("Advertising stopped");
    }

    return 0;
}
u8_t g_adv_send_fail = 0;
extern u8 g_Meshtesting;
#define PROXY_SEND_AFTER_IDLE_TIME 3000
static void adv_thread(void *p)
{
#if defined(CONFIG_BLE_MESH_RELAY_ADV_BUF)
    #if CONFIG_BLE_MESH_RELAY_ADV_SSV
        OS_STATUS handle = OS_SUCCESS;
    #else
        QueueSetMemberHandle_t handle = NULL;
#endif

#endif

    bt_mesh_msg_t msg = {0};
    struct net_buf **buf;

    init_sync_adv();

    buf = (struct net_buf **)(&msg.arg);

    BT_DBG("%s, starts", __func__);

    while (1) {
        *buf = NULL;
#if !defined(CONFIG_BLE_MESH_RELAY_ADV_BUF)
#if CONFIG_BLE_MESH_NODE
        if (IS_ENABLED(CONFIG_BLE_MESH_PROXY)) {
            xQueueReceive(xBleMeshQueue, &msg, K_NO_WAIT);
            while (!(*buf)) {
                s32_t timeout;
                BT_DBG("Mesh Proxy Advertising start");
                timeout = bt_mesh_proxy_adv_start();
                BT_DBG("Mesh Proxy Advertising up to %d ms", timeout);
                xQueueReceive(xBleMeshQueue, &msg, timeout);
                BT_DBG("Mesh Proxy Advertising stop");
                bt_mesh_proxy_adv_stop();
            }
        } else {
            xQueueReceive(xBleMeshQueue, &msg, portMAX_DELAY);
        }
#else
        xQueueReceive(xBleMeshQueue, &msg, portMAX_DELAY);
#endif
#else /* !defined(CONFIG_BLE_MESH_RELAY_ADV_BUF) */
#if CONFIG_BLE_MESH_NODE
        if (IS_ENABLED(CONFIG_BLE_MESH_PROXY)) {
        #if CONFIG_BLE_MESH_RELAY_ADV_SSV
            handle = OS_SemWait(s_mesh_queue_set_semaphore, PROXY_SEND_AFTER_IDLE_TIME);
            if (handle == OS_SUCCESS) {
        #else
            handle = xQueueSelectFromSet(xBleMeshQueueSet, PROXY_SEND_AFTER_IDLE_TIME);
            if (handle) {
        #endif
                if (uxQueueMessagesWaiting(xBleMeshQueue)) {
                    xQueueReceive(xBleMeshQueue, &msg, K_NO_WAIT);
                } else if (uxQueueMessagesWaiting(xBleMeshRelayQueue)) {
                    xQueueReceive(xBleMeshRelayQueue, &msg, K_NO_WAIT);
                }
            } else {
                while (!(*buf)) {
                    s32_t timeout;
                    BT_DBG("Mesh Proxy Advertising start");
                    timeout = bt_mesh_proxy_adv_start();
                    BT_DBG("Mesh Proxy Advertising up to %d ms", timeout);
                #if CONFIG_BLE_MESH_RELAY_ADV_SSV
                    handle = OS_SemWait(s_mesh_queue_set_semaphore, timeout);
                #else
                    handle = xQueueSelectFromSet(xBleMeshQueueSet, timeout);
                #endif
                    BT_DBG("Mesh Proxy Advertising stop");
                    bt_mesh_proxy_adv_stop();
                    #if CONFIG_BLE_MESH_RELAY_ADV_SSV
                    if (handle == OS_SUCCESS) {
                    #else
                    if (handle) {
                    #endif

                        if (uxQueueMessagesWaiting(xBleMeshQueue)) {
                            xQueueReceive(xBleMeshQueue, &msg, K_NO_WAIT);
                        } else if (uxQueueMessagesWaiting(xBleMeshRelayQueue)) {
                            xQueueReceive(xBleMeshRelayQueue, &msg, K_NO_WAIT);
                        }
                    }
                }
            }
        } else {
            #if CONFIG_BLE_MESH_RELAY_ADV_SSV
            handle = OS_SemWait(s_mesh_queue_set_semaphore, portMAX_DELAY);
            if (handle == OS_SUCCESS) {
            #else
            handle = xQueueSelectFromSet(xBleMeshQueueSet, portMAX_DELAY);
            if (handle) {
            #endif
                if (uxQueueMessagesWaiting(xBleMeshQueue)) {
                    xQueueReceive(xBleMeshQueue, &msg, K_NO_WAIT);
                } else if (uxQueueMessagesWaiting(xBleMeshRelayQueue)) {
                    xQueueReceive(xBleMeshRelayQueue, &msg, K_NO_WAIT);
                }
            }
        }
#else
        #if CONFIG_BLE_MESH_RELAY_ADV_SSV
        handle = OS_SemWait(s_mesh_queue_set_semaphore, portMAX_DELAY);
        if (handle == OS_SUCCESS) {
        #else
        handle = xQueueSelectFromSet(xBleMeshQueueSet, portMAX_DELAY);
        if (handle) {
        #endif
            if (uxQueueMessagesWaiting(xBleMeshQueue)) {
                xQueueReceive(xBleMeshQueue, &msg, K_NO_WAIT);
            } else if (uxQueueMessagesWaiting(xBleMeshRelayQueue)) {
                xQueueReceive(xBleMeshRelayQueue, &msg, K_NO_WAIT);
            }
        }
#endif
#endif /* !defined(CONFIG_BLE_MESH_RELAY_ADV_BUF) */

        if (*buf == NULL) {
            continue;
        }

        /* busy == 0 means this was canceled */
        if (BLE_MESH_ADV(*buf)->busy) {
            BLE_MESH_ADV(*buf)->busy = 0U;
#if !defined(CONFIG_BLE_MESH_RELAY_ADV_BUF)
            if (adv_send(*buf)) {
                BT_WARN("%s, Failed to send adv packet(relay adv buf)", __func__);
                g_adv_send_fail = 1;
            }
#else /* !defined(CONFIG_BLE_MESH_RELAY_ADV_BUF) */
            if (msg.relay && ignore_relay_packet(msg.timestamp)) {
                /* If the interval between "current time - msg.timestamp" is bigger than
                 * BLE_MESH_RELAY_TIME_INTERVAL, this relay packet will not be sent.
                 */
                BT_DBG("%s, Ignore relay packet", __func__);
                net_buf_unref(*buf);
            } else {
                if (adv_send(*buf)) {
                    BT_WARN("%s, Failed to send relay adv packet", __func__);
                }
            }
#endif
        } else {
            bt_mesh_adv_buf_ref_debug(__func__, *buf, 1U, BLE_MESH_BUF_REF_EQUAL);
            net_buf_unref(*buf);
        }

        /* Give other threads a chance to run */
        taskYIELD();
    }
}

struct net_buf *bt_mesh_adv_create_from_pool(struct net_buf_pool *pool,
        bt_mesh_adv_alloc_t get_id,
        enum bt_mesh_adv_type type,
        u8_t xmit, s32_t timeout)
{
    struct bt_mesh_adv *adv;
    struct net_buf *buf;

    if (bt_mesh_atomic_test_bit(bt_mesh.flags, BLE_MESH_SUSPENDED)) {
        BT_WARN("Refusing to allocate buffer while suspended");
        return NULL;
    }

    buf = net_buf_alloc(pool, timeout);
    if (!buf) {
        BT_ERR("net_buf_alloc alloc fail buf_count %d, uninit_count %d",
            pool->buf_count, pool->uninit_count);
        ASSERT(0);
        return NULL;
    }

    BT_DBG("%s, pool = %p, buf_count = %d, uinit_count = %d", __func__,
           buf->pool, pool->buf_count, pool->uninit_count);

    adv = get_id(net_buf_id(buf));
    BLE_MESH_ADV(buf) = adv;

    (void)memset(adv, 0, sizeof(*adv));

    adv->type         = type;
    adv->xmit         = xmit;
    //printf("create_from_pool type %d, xmit %d\n", adv->type, adv->xmit);

    return buf;
}

struct net_buf *bt_mesh_adv_create(enum bt_mesh_adv_type type, u8_t xmit,
                                   s32_t timeout)
{
    return bt_mesh_adv_create_from_pool(&adv_buf_pool, adv_alloc, type,
                                        xmit, timeout);
}

void bt_mesh_adv_buf_ref_debug(const char *func, struct net_buf *buf,
                               u8_t ref_cmp, bt_mesh_buf_ref_flag_t flag)
{
    if (buf == NULL || func == NULL || flag >= BLE_MESH_BUF_REF_MAX) {
        BT_ERR("%s, Invalid parameter", __func__);
        return;
    }

    switch (flag) {
    case BLE_MESH_BUF_REF_EQUAL:
        if (buf->ref != ref_cmp) {
            BT_ERR("Unexpected ref %d in %s, expect to equal to %d", buf->ref, func, ref_cmp);
        }
        break;
    case BLE_MESH_BUF_REF_SMALL:
        if (buf->ref >= ref_cmp) {
            //todo, show when test vendor message
            BT_DBG("Unexpected ref %d in %s, expect to smaller than %d", buf->ref, func, ref_cmp);
        }
        break;
    default:
        break;
    }
}

static void bt_mesh_unref_buf(bt_mesh_msg_t *msg)
{
    struct net_buf *buf;

    if (msg->arg) {
        buf = (struct net_buf *)msg->arg;
        BLE_MESH_ADV(buf)->busy = 0U;
        net_buf_unref(buf);
    }

    return;
}

static void bt_mesh_task_post(bt_mesh_msg_t *msg, uint32_t timeout)
{
#if CONFIG_BLE_MESH_RELAY_ADV_SSV
    OS_STATUS res = OS_SUCCESS;
#endif

    BT_DBG("%s", __func__);

    if (xQueueSend(xBleMeshQueue, msg, timeout) != pdTRUE) {
        BT_ERR("%s, Failed to send item to queue", __func__);
        bt_mesh_unref_buf(msg);
    }
    #if CONFIG_BLE_MESH_RELAY_ADV_SSV
    res = OS_SemSignal(s_mesh_queue_set_semaphore);
    #endif

    BT_DBG("%s done", __func__);
}

void bt_mesh_adv_send(struct net_buf *buf, const struct bt_mesh_send_cb *cb,
                      void *cb_data)
{
    bt_mesh_msg_t msg = {
        .relay = false,
    };

    BT_DBG("adv_send type 0x%02x len %u: %s", BLE_MESH_ADV(buf)->type, buf->len,
           bt_hex(buf->data, buf->len));

    BLE_MESH_ADV(buf)->cb = cb;
    BLE_MESH_ADV(buf)->cb_data = cb_data;
    BLE_MESH_ADV(buf)->busy = 1U;

    bt_mesh_adv_buf_ref_debug(__func__, buf, 3U, BLE_MESH_BUF_REF_SMALL);

    msg.arg = (void *)net_buf_ref(buf);

    if ((buf->len + 2) > BLE_HS_ADV_MAX_SZ) {
        printf("bt_mesh_adv_send len %d, may assert\n", buf->len);
        BT_ERR("adv_send type 0x%02x len %u: %s", BLE_MESH_ADV(buf)->type, buf->len,
           bt_hex(buf->data, buf->len));
        //ASSERT(0);//length dbg
        return;
    }
    bt_mesh_task_post(&msg, portMAX_DELAY);
}

void bt_mesh_adv_update(void)
{
    bt_mesh_msg_t msg = {
        .relay = false,
        .arg = NULL,
    };

    BT_DBG("%s", __func__);

    bt_mesh_task_post(&msg, K_NO_WAIT);
}

#if defined(CONFIG_BLE_MESH_RELAY_ADV_BUF)
static bool ignore_relay_packet(u32_t timestamp)
{
    u32_t now = k_uptime_get_32();
    u32_t interval;

    if (now >= timestamp) {
        interval = now - timestamp;
    }/* else if (now == timestamp) {
        interval = BLE_MESH_MAX_TIME_INTERVAL;
    } */else {
        interval = BLE_MESH_MAX_TIME_INTERVAL - (timestamp - now) + 1;
    }

    //if (interval >= BLE_MESH_RELAY_TIME_INTERVAL)
    //    printf("interval %u, timestamp %u, now %u\n", interval, timestamp, now);

    return (interval >= BLE_MESH_RELAY_TIME_INTERVAL) ? true : false;
}

static struct bt_mesh_adv *relay_adv_alloc(int id)
{
    return &relay_adv_pool[id];
}

struct net_buf *bt_mesh_relay_adv_create(enum bt_mesh_adv_type type, u8_t xmit,
        s32_t timeout)
{
    return bt_mesh_adv_create_from_pool(&relay_adv_buf_pool, relay_adv_alloc, type,
                                        xmit, timeout);
}

static void ble_mesh_relay_task_post(bt_mesh_msg_t *msg, uint32_t timeout)
{
    QueueSetMemberHandle_t handle  = NULL;
    bt_mesh_msg_t old_msg = {0};
#if CONFIG_BLE_MESH_RELAY_ADV_SSV
    OS_STATUS res = OS_SUCCESS;
#endif

    BT_DBG("%s", __func__);

    if (xQueueSend(xBleMeshRelayQueue, msg, timeout) == pdTRUE) {
        #if CONFIG_BLE_MESH_RELAY_ADV_SSV
        res = OS_SemSignal(s_mesh_queue_set_semaphore);
        #endif
        return;
    }

    /**
     * If failed to send packet to the relay queue(queue is full), we will
     * remove the oldest packet in the queue and put the new one into it.
     */
    #if CONFIG_BLE_MESH_RELAY_ADV_SSV
    /* queue is full, just see*/
    if (uxQueueMessagesWaiting(xBleMeshRelayQueue)) {
    #else
    handle = xQueueSelectFromSet(xBleMeshQueueSet, K_NO_WAIT);
    if (handle && uxQueueMessagesWaiting(xBleMeshRelayQueue)) {
    #endif
        BT_DBG("%s, Full queue, remove the oldest relay packet", __func__);
        /* Remove the oldest relay packet from queue */
        if (xQueueReceive(xBleMeshRelayQueue, &old_msg, K_NO_WAIT) != pdTRUE) {
            BT_ERR("%s, Failed to remove item from queue", __func__);
            bt_mesh_unref_buf(msg);
            return;
        }
        /* Unref buf used for the oldest relay packet */
        bt_mesh_unref_buf(&old_msg);
        /* Send the latest relay packet to queue */
        if (xQueueSend(xBleMeshRelayQueue, msg, K_NO_WAIT) != pdTRUE) {
            BT_ERR("%s, Failed to send item to relay queue", __func__);
            bt_mesh_unref_buf(msg);
            return;
        }
        #if CONFIG_BLE_MESH_RELAY_ADV_SSV
        res = OS_SemSignal(s_mesh_queue_set_semaphore);
        #endif
    } else {
        BT_WARN("%s, Empty queue, but failed to send the relay packet", __func__);
        bt_mesh_unref_buf(msg);
    }
}

void bt_mesh_relay_adv_send(struct net_buf *buf, const struct bt_mesh_send_cb *cb,
                            void *cb_data, u16_t src, u16_t dst)
{
    bt_mesh_msg_t msg = {
        .relay = true,
    };

    BT_DBG("type 0x%02x len %u: %s", BLE_MESH_ADV(buf)->type, buf->len,
           bt_hex(buf->data, buf->len));

    BLE_MESH_ADV(buf)->cb = cb;
    BLE_MESH_ADV(buf)->cb_data = cb_data;
    BLE_MESH_ADV(buf)->busy = 1U;

    msg.arg = (void *)net_buf_ref(buf);
    msg.src = src;
    msg.dst = dst;
    msg.timestamp = k_uptime_get_32();
    /* Use K_NO_WAIT here, if xBleMeshRelayQueue is full return immediately */
    ble_mesh_relay_task_post(&msg, K_NO_WAIT);
}

u16_t bt_mesh_get_stored_relay_count(void)
{
    return (u16_t)uxQueueMessagesWaiting(xBleMeshRelayQueue);
}
#endif /* #if defined(CONFIG_BLE_MESH_RELAY_ADV_BUF) */

u16_t bt_mesh_get_stored_adv_count(void)
{
    return (u16_t)uxQueueMessagesWaiting(xBleMeshQueue);
}

const bt_mesh_addr_t *bt_mesh_pba_get_addr(void)
{
    return dev_addr;
}

#if (CONFIG_BLE_MESH_PROVISIONER && CONFIG_BLE_MESH_PB_GATT) || \
    CONFIG_BLE_MESH_GATT_PROXY_CLIENT
static bool bt_mesh_is_adv_flags_valid(struct net_buf_simple *buf)
{
    u8_t flags;

    if (buf->len != 1U) {
        BT_DBG("%s, Unexpected flags length", __func__);
        return false;
    }

    flags = net_buf_simple_pull_u8(buf);

    BT_DBG("Received adv pkt with flags: 0x%02x", flags);

    /* Flags context will not be checked curently */

    return true;
}

static bool bt_mesh_is_adv_srv_uuid_valid(struct net_buf_simple *buf, u16_t *uuid)
{
    if (buf->len != 2U) {
        BT_DBG("Length not match mesh service uuid");
        return false;
    }

    *uuid = net_buf_simple_pull_le16(buf);

    BT_DBG("Received adv pkt with service UUID: %d", *uuid);

    if (*uuid != BLE_MESH_UUID_MESH_PROV_VAL &&
            *uuid != BLE_MESH_UUID_MESH_PROXY_VAL) {
        return false;
    }

    if (*uuid == BLE_MESH_UUID_MESH_PROV_VAL &&
            bt_mesh_is_provisioner_en() == false) {
        return false;
    }

    if (*uuid == BLE_MESH_UUID_MESH_PROXY_VAL &&
            !IS_ENABLED(CONFIG_BLE_MESH_GATT_PROXY_CLIENT)) {
        return false;
    }

    return true;
}

void bt_receive_ssv_synced_ack(struct net_buf_simple *buf)
{
    u16_t vendor = 0;
    u16_t from;
    //u32_t *p_ack_bitmap_low = NULL, *p_ack_bitmap_high = NULL;
    u32_t ack_bitmap_low = 0, ack_bitmap_high = 0;
    u32_t seq = 0;

    if (buf->len != 16)
        return;

    vendor = net_buf_simple_pull_le16(buf);

    if (0x039B != vendor)
        return;

    from = net_buf_simple_pull_le16(buf);

    seq = net_buf_simple_pull_le32(buf);

    ack_bitmap_low = net_buf_simple_pull_le32(buf);

    ack_bitmap_high = net_buf_simple_pull_le32(buf);

    //BT_WARN("%d %08x %08x",
    //    from, ack_bitmap_high, ack_bitmap_low);
    save_ssv_ack_info(from, seq, ack_bitmap_low, ack_bitmap_high);
    //BT_WARN("%d %x %llx",
    //    g_synced_ack_from, g_synced_ack_seq, g_synced_ack_bitmap);

}


#define BLE_MESH_PROV_SRV_DATA_LEN      0x12
#define BLE_MESH_PROXY_SRV_DATA_LEN1    0x09
#define BLE_MESH_PROXY_SRV_DATA_LEN2    0x11

static void bt_mesh_adv_srv_data_recv(struct net_buf_simple *buf, const bt_mesh_addr_t *addr, u16_t uuid)
{
    u16_t type;

    if (!buf || !addr) {
        BT_ERR("%s, Invalid parameter", __func__);
        return;
    }

    type = net_buf_simple_pull_le16(buf);
    if (uuid != type) {
        BT_DBG("%s, Invalid Mesh Service Data UUID 0x%04x", __func__, type);
        return;
    }

    switch (type) {
#if CONFIG_BLE_MESH_PROVISIONER && CONFIG_BLE_MESH_PB_GATT
    case BLE_MESH_UUID_MESH_PROV_VAL:
        if (bt_mesh_is_provisioner_en()) {
            if (buf->len != BLE_MESH_PROV_SRV_DATA_LEN) {
                BT_WARN("%s, Invalid Mesh Prov Service Data length %d", __func__, buf->len);
                return;
            }

            BT_DBG("Start to handle Mesh Prov Service Data");
            provisioner_prov_adv_ind_recv(buf, addr);
        }
        break;
#endif
#if CONFIG_BLE_MESH_GATT_PROXY_CLIENT
    case BLE_MESH_UUID_MESH_PROXY_VAL:
        if (buf->len != BLE_MESH_PROXY_SRV_DATA_LEN1 &&
                buf->len != BLE_MESH_PROXY_SRV_DATA_LEN2) {
            BT_WARN("%s, Invalid Mesh Proxy Service Data length %d", __func__, buf->len);
            return;
        }

        BT_DBG("Start to handle Mesh Proxy Service Data");
        proxy_client_adv_ind_recv(buf, addr);
        break;
#endif
    default:
        break;
    }
}
#endif

static void bt_mesh_scan_cb(const bt_mesh_addr_t *addr, s8_t rssi,
                            u8_t adv_type, struct net_buf_simple *buf)
{
#if (CONFIG_BLE_MESH_PROVISIONER && CONFIG_BLE_MESH_PB_GATT) || \
    CONFIG_BLE_MESH_GATT_PROXY_CLIENT
    u16_t uuid;
    uuid =0;
#endif

    if (adv_type != BLE_MESH_ADV_NONCONN_IND && adv_type != BLE_MESH_ADV_IND) {
        return;
    }

    BT_DBG("%s, len %u: %s", __func__, buf->len, bt_hex(buf->data, buf->len));

    dev_addr = addr;

    while (buf->len > 1) {/* handle AD Element*/
        struct net_buf_simple_state state;
        u8_t len, type;

        len = net_buf_simple_pull_u8(buf);
        /* Check for early termination */
        if (len == 0U) {
            return;
        }

        if (len > buf->len) {
            BT_WARN("AD malformed");
            return;
        }

        /*if (len > BLE_MESH_ADV_DATA_SIZE) {
            BT_WARN("len %d err", len);//length dbg
            return;
        }*/

        net_buf_simple_save(buf, &state);

        type = net_buf_simple_pull_u8(buf);

        buf->len = len - 1;

#if 0
        /* TODO: Check with BLE Mesh BQB test cases */
        if ((type == BLE_MESH_DATA_MESH_PROV || type == BLE_MESH_DATA_MESH_MESSAGE ||
                type == BLE_MESH_DATA_MESH_BEACON) && (adv_type != BLE_MESH_ADV_NONCONN_IND)) {
            BT_DBG("%s, ignore BLE Mesh packet (type 0x%02x) with adv_type 0x%02x",
                   __func__, type, adv_type);
            return;
        }
#endif

        switch (type) {
        case BLE_MESH_DATA_MESH_MESSAGE:
            bt_mesh_net_recv(buf, rssi, BLE_MESH_NET_IF_ADV);
            break;
#if CONFIG_BLE_MESH_PB_ADV
        case BLE_MESH_DATA_MESH_PROV:
#if CONFIG_BLE_MESH_NODE
            if (!bt_mesh_is_provisioner_en()) {
                bt_mesh_pb_adv_recv(buf);
            }
#endif
#if CONFIG_BLE_MESH_PROVISIONER
            if (bt_mesh_is_provisioner_en()) {
                provisioner_pb_adv_recv(buf);
            }
#endif
            break;
#endif /* CONFIG_BLE_MESH_PB_ADV */
        case BLE_MESH_DATA_MESH_BEACON:
#if CONFIG_BLE_MESH_NODE
            if (!bt_mesh_is_provisioner_en()) {
                BT_INFO("%s, beacon type %u: addr %02X%02X%02X%02X%02X%02X", __func__, dev_addr->type,
                    dev_addr->val[0], dev_addr->val[1], dev_addr->val[2],
                    dev_addr->val[3], dev_addr->val[4], dev_addr->val[5]);
                bt_mesh_beacon_recv(buf);
            }
#endif
#if CONFIG_BLE_MESH_PROVISIONER
            if (bt_mesh_is_provisioner_en()) {
                provisioner_beacon_recv(buf);
            }
#endif
            break;
#if (CONFIG_BLE_MESH_PROVISIONER && CONFIG_BLE_MESH_PB_GATT) || \
    CONFIG_BLE_MESH_GATT_PROXY_CLIENT
        case BLE_MESH_DATA_FLAGS:
            if (!bt_mesh_is_adv_flags_valid(buf)) {
                BT_DBG("Adv Flags mismatch, ignore this adv pkt");
                return;
            }
            break;
        case BLE_MESH_DATA_UUID16_ALL:
            if (!bt_mesh_is_adv_srv_uuid_valid(buf, &uuid)) {
                BT_DBG("Adv Service UUID mismatch, ignore this adv pkt");
                return;
            }
            break;
        case BLE_MESH_DATA_SVC_DATA16:
            bt_mesh_adv_srv_data_recv(buf, addr, uuid);
            break;
#endif

        case BLE_MESH_DATA_SSV_SYNCED_ACK:
            bt_receive_ssv_synced_ack(buf);
            break;
        default:
            break;
        }

        net_buf_simple_restore(buf, &state);
        net_buf_simple_pull(buf, len);
    }

    return;
}

void bt_mesh_adv_init(void)
{
#if CONFIG_BLE_MESH_RELAY_ADV_SSV
    OS_STATUS res = 0;
#endif

    xBleMeshQueue = xQueueCreate(BLE_MESH_QUEUE_SIZE, sizeof(bt_mesh_msg_t));
    configASSERT(xBleMeshQueue);
#if defined(CONFIG_BLE_MESH_RELAY_ADV_BUF)
    xBleMeshRelayQueue = xQueueCreate(BLE_MESH_RELAY_QUEUE_SIZE, sizeof(bt_mesh_msg_t));
    configASSERT(xBleMeshRelayQueue);

    #if CONFIG_BLE_MESH_RELAY_ADV_SSV
    res = OS_SemInit(&s_mesh_queue_set_semaphore, BLE_MESH_QUEUE_SET_SIZE, 0);
    #else
    xBleMeshQueueSet = xQueueCreateSet(BLE_MESH_QUEUE_SET_SIZE);
    configASSERT(xBleMeshQueueSet);
    xQueueAddToSet(xBleMeshQueue, xBleMeshQueueSet);
    xQueueAddToSet(xBleMeshRelayQueue, xBleMeshQueueSet);
    #endif
#endif /* defined(CONFIG_BLE_MESH_RELAY_ADV_BUF) */
    /*int ret = xTaskCreatePinnedToCore(adv_thread, "BLE_Mesh_ADV_Task", 3072, NULL,
                                      configMAX_PRIORITIES - 7, NULL, ADV_TASK_CORE);*/
    BT_DBG("create adv_thread\n");
    u8 ret = OS_TaskCreate(adv_thread, "BLE_Mesh_ADV_Task", CONFIG_BLE_MESH_ADV_TASK_STACK_SIZE/*3072*/, NULL,
                                      OS_TASK_LOW, NULL);
    configASSERT(ret == 1);
}

int bt_mesh_scan_enable(void)
{
    int err;

    struct bt_mesh_scan_param scan_param = {
        .type       = BLE_MESH_SCAN_PASSIVE,
#if defined(CONFIG_BLE_MESH_USE_DUPLICATE_SCAN)
        .filter_dup = BLE_MESH_SCAN_FILTER_DUP_ENABLE,
#else
        .filter_dup = BLE_MESH_SCAN_FILTER_DUP_DISABLE,
#endif
        .interval   = g_adv_scan_interval,
        .window     = g_adv_scan_window
    };

    BT_DBG("%s", __func__);

    err = bt_le_scan_start(&scan_param, bt_mesh_scan_cb);
    if (err && err != -EALREADY) {
        BT_ERR("starting scan failed (err %d)", err);
        return err;
    }

    return 0;
}

int bt_mesh_scan_disable(void)
{
    int err;

    BT_DBG("%s", __func__);

    err = bt_le_scan_stop();
    if (err && err != -EALREADY) {
        BT_ERR("stopping scan failed (err %d)", err);
        return err;
    }

    return 0;
}
