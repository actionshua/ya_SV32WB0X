#include <stdint.h>
#include "osal.h"
#include "ssv_log.h"
#include "access.h"
#include "test_data.h"
#include "ble_mesh_adapter.h"
#include "ble_mesh_reg_gen_onoff_client_cmd.h"
#include "ssv_ble_mesh_networking_api.h"
#include "ssv_private/ssv_timer_impl.h"
#include "mesh_access.h"
#include "atcmd.h"
#include "atcmd_general.h"
#include "atcmd_socket.h"
#include "transport.h"
#include "adv.h"
#if CONFIG_BLE_MESH_GPIO_DBG
#include "hal_gpio.h"
#include "TurismoE.h"
#endif

u8 g_Meshtesting = 0;

ssv_ble_mesh_test_sender_t item_4_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, ONOFF_MODEL_TEST , ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 1),
};

ssv_ble_mesh_test_sender_t item_5_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, VENDOR_MODEL_TEST , NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR0, 1),/* 1:addr1 expect publish count after device 2 receive vendor msg*/
};

ssv_ble_mesh_test_sender_t item_6_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, ONOFF_MODEL_TEST , ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 9),
};

ssv_ble_mesh_test_sender_t item_32_33_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, VENDOR_MODEL_TEST , NO_ACK, SEND_INTERVAL_1S, VENDOR_GROUP_ADDR0, 0),
};

ssv_ble_mesh_test_sender_t item_8_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, ONOFF_MODEL_TEST , ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 49),
};


ssv_ble_mesh_test_sender_t item_10_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, VENDOR_MODEL_TEST , ACK, SEND_INTERVAL_2400MS, VENDOR_GROUP_ADDR0, 49),
};

ssv_ble_mesh_test_sender_t item_11_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 1),
    SSV_BLE_MESH_TEST_SENDER(2, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 1),
    SSV_BLE_MESH_TEST_SENDER(3, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 1),
    SSV_BLE_MESH_TEST_SENDER(4, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 1),
    SSV_BLE_MESH_TEST_SENDER(5, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 1),
};

ssv_ble_mesh_test_sender_t item_12_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR0, 0),
    SSV_BLE_MESH_TEST_SENDER(2, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR0, 0),
    SSV_BLE_MESH_TEST_SENDER(3, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR0, 0),
    SSV_BLE_MESH_TEST_SENDER(4, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR0, 0),
    SSV_BLE_MESH_TEST_SENDER(5, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR0, 0),
};

ssv_ble_mesh_test_sender_t item_13_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 3),
    SSV_BLE_MESH_TEST_SENDER(2, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 3),
    SSV_BLE_MESH_TEST_SENDER(3, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 3),
};

ssv_ble_mesh_test_sender_t item_14_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR0, 0),
    SSV_BLE_MESH_TEST_SENDER(2, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR0, 0),
    SSV_BLE_MESH_TEST_SENDER(3, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR0, 0),
};

ssv_ble_mesh_test_sender_t item_15_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 3),
    SSV_BLE_MESH_TEST_SENDER(2, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 3),
    SSV_BLE_MESH_TEST_SENDER(6, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR1, 3),
    SSV_BLE_MESH_TEST_SENDER(7, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR1, 3),
};

ssv_ble_mesh_test_sender_t item_16_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR0, 0),
    SSV_BLE_MESH_TEST_SENDER(2, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR0, 0),
    SSV_BLE_MESH_TEST_SENDER(6, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR1, 0),
    SSV_BLE_MESH_TEST_SENDER(7, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR1, 0),
};

ssv_ble_mesh_test_sender_t item_17_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 6),
    SSV_BLE_MESH_TEST_SENDER(2, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 6),
    SSV_BLE_MESH_TEST_SENDER(9, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR1, 6),
    SSV_BLE_MESH_TEST_SENDER(10, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR1, 6),
    SSV_BLE_MESH_TEST_SENDER(17, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR2, 6),
    SSV_BLE_MESH_TEST_SENDER(18, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR2, 6),
};

ssv_ble_mesh_test_sender_t item_18_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR0, 0),
    SSV_BLE_MESH_TEST_SENDER(2, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR0, 0),
    SSV_BLE_MESH_TEST_SENDER(9, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR1, 0),
    SSV_BLE_MESH_TEST_SENDER(10, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR1, 0),
    SSV_BLE_MESH_TEST_SENDER(17, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR2, 0),
    SSV_BLE_MESH_TEST_SENDER(18, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR2, 0),
};

ssv_ble_mesh_test_sender_t item_19_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 8),
    SSV_BLE_MESH_TEST_SENDER(2, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR0, 8),
    SSV_BLE_MESH_TEST_SENDER(11, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR1, 8),
    SSV_BLE_MESH_TEST_SENDER(12, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR1, 8),
    SSV_BLE_MESH_TEST_SENDER(21, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR2, 8),
    SSV_BLE_MESH_TEST_SENDER(22, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR2, 8),
    SSV_BLE_MESH_TEST_SENDER(31, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR3, 8),
    SSV_BLE_MESH_TEST_SENDER(32, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR3, 8),
    SSV_BLE_MESH_TEST_SENDER(41, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR4, 8),
    SSV_BLE_MESH_TEST_SENDER(42, ONOFF_MODEL_TEST, ACK, SEND_INTERVAL_500MS, ONOFF_GROUP_ADDR4, 8),
};

ssv_ble_mesh_test_sender_t item_20_sender[] = {
    SSV_BLE_MESH_TEST_SENDER(1, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR0, 0),
    SSV_BLE_MESH_TEST_SENDER(2, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR0, 0),
    SSV_BLE_MESH_TEST_SENDER(11, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR1, 0),
    SSV_BLE_MESH_TEST_SENDER(12, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR1, 0),
    SSV_BLE_MESH_TEST_SENDER(21, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR2, 0),
    SSV_BLE_MESH_TEST_SENDER(22, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR2, 0),
    SSV_BLE_MESH_TEST_SENDER(31, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR3, 0),
    SSV_BLE_MESH_TEST_SENDER(32, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR3, 0),
    SSV_BLE_MESH_TEST_SENDER(41, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR4, 0),
    SSV_BLE_MESH_TEST_SENDER(42, VENDOR_MODEL_TEST, NO_ACK, SEND_INTERVAL_1200MS, VENDOR_GROUP_ADDR4, 0),
};

/*collect result address 2-2*/
ssv_ble_mesh_test_collect_result_addr_t collect_2_2[] = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_ADDR(2, 2),
};

ssv_ble_mesh_test_collect_result_group_t r_group_2_2 = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_GROUP(collect_2_2)
};

/*collect result address 2-10*/
ssv_ble_mesh_test_collect_result_addr_t collect2_10[] = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_ADDR(2, 10),
};

ssv_ble_mesh_test_collect_result_group_t r_group_2_10 = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_GROUP(collect2_10)
};

/*collect result address 2-50*/
ssv_ble_mesh_test_collect_result_addr_t collect2_50[] = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_ADDR(2, 50),
};

ssv_ble_mesh_test_collect_result_group_t r_group_2_50 = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_GROUP(collect2_50)
};

/*collect result address 6-6*/
ssv_ble_mesh_test_collect_result_addr_t collect6_6[] = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_ADDR(6, 6),
};

ssv_ble_mesh_test_collect_result_group_t r_group_6_6 = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_GROUP(collect6_6)
};

/*collect result address 4-6*/
ssv_ble_mesh_test_collect_result_addr_t collect4_6[] = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_ADDR(4, 6),
};

ssv_ble_mesh_test_collect_result_group_t r_group_4_6 = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_GROUP(collect4_6)
};

/*collect result address 3-5, 8-10*/
ssv_ble_mesh_test_collect_result_addr_t collect3_5_8_10[] = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_ADDR(3, 5),
    SSV_BLE_MESH_TEST_COLLECT_RESULT_ADDR(8, 10),
};

ssv_ble_mesh_test_collect_result_group_t r_group_3_5_8_10 = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_GROUP(collect3_5_8_10)
};

/*collect result address 3_8,11_16,19_24*/
ssv_ble_mesh_test_collect_result_addr_t collect3_8_11_16_19_24[] = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_ADDR(3, 8),
    SSV_BLE_MESH_TEST_COLLECT_RESULT_ADDR(11, 16),
    SSV_BLE_MESH_TEST_COLLECT_RESULT_ADDR(19, 24),
};

ssv_ble_mesh_test_collect_result_group_t r_group_3_8_11_16_19_24 = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_GROUP(collect3_8_11_16_19_24)
};

/*collect result address 3_10,13_20,23_30,33_40,43_50*/
ssv_ble_mesh_test_collect_result_addr_t collect3_10_13_20_23_30_33_40_43_50[] = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_ADDR(3, 10),
    SSV_BLE_MESH_TEST_COLLECT_RESULT_ADDR(13, 20),
    SSV_BLE_MESH_TEST_COLLECT_RESULT_ADDR(23, 30),
    SSV_BLE_MESH_TEST_COLLECT_RESULT_ADDR(33, 40),
    SSV_BLE_MESH_TEST_COLLECT_RESULT_ADDR(43, 50),
};

ssv_ble_mesh_test_collect_result_group_t r_group_3_10_13_20_23_30_33_40_43_50 = {
    SSV_BLE_MESH_TEST_COLLECT_RESULT_GROUP(collect3_10_13_20_23_30_33_40_43_50)
};


/*test items*/
ssv_ble_mesh_test_item_t item4 = SSV_BLE_MESH_TEST_TEST_ITEM(0, item_4_sender, r_group_2_2);
ssv_ble_mesh_test_item_t item5 = SSV_BLE_MESH_TEST_TEST_ITEM(1, item_5_sender, r_group_2_2);
ssv_ble_mesh_test_item_t item6 = SSV_BLE_MESH_TEST_TEST_ITEM(0, item_6_sender, r_group_2_10);
ssv_ble_mesh_test_item_t item7 = SSV_BLE_MESH_TEST_TEST_ITEM(1, item_5_sender, r_group_2_10);
ssv_ble_mesh_test_item_t item8 = SSV_BLE_MESH_TEST_TEST_ITEM(0, item_8_sender, r_group_2_50);
ssv_ble_mesh_test_item_t item9 = SSV_BLE_MESH_TEST_TEST_ITEM(1, item_5_sender, r_group_2_50);
ssv_ble_mesh_test_item_t item10 = SSV_BLE_MESH_TEST_TEST_ITEM(0, item_10_sender, r_group_2_50);
ssv_ble_mesh_test_item_t item11 = SSV_BLE_MESH_TEST_TEST_ITEM(0, item_11_sender, r_group_6_6);
ssv_ble_mesh_test_item_t item12 = SSV_BLE_MESH_TEST_TEST_ITEM(5, item_12_sender, r_group_6_6);
ssv_ble_mesh_test_item_t item13 = SSV_BLE_MESH_TEST_TEST_ITEM(0, item_13_sender, r_group_4_6);
ssv_ble_mesh_test_item_t item14 = SSV_BLE_MESH_TEST_TEST_ITEM(3, item_14_sender, r_group_4_6);
ssv_ble_mesh_test_item_t item15 = SSV_BLE_MESH_TEST_TEST_ITEM(0, item_15_sender, r_group_3_5_8_10);
ssv_ble_mesh_test_item_t item16 = SSV_BLE_MESH_TEST_TEST_ITEM(2, item_16_sender, r_group_3_5_8_10);
ssv_ble_mesh_test_item_t item17 = SSV_BLE_MESH_TEST_TEST_ITEM(0, item_17_sender, r_group_3_8_11_16_19_24);
ssv_ble_mesh_test_item_t item18 = SSV_BLE_MESH_TEST_TEST_ITEM(2, item_18_sender, r_group_3_8_11_16_19_24);
ssv_ble_mesh_test_item_t item19 = SSV_BLE_MESH_TEST_TEST_ITEM(0, item_19_sender, r_group_3_10_13_20_23_30_33_40_43_50);
ssv_ble_mesh_test_item_t item20 = SSV_BLE_MESH_TEST_TEST_ITEM(2, item_20_sender, r_group_3_10_13_20_23_30_33_40_43_50);
ssv_ble_mesh_test_item_t item32_33 = SSV_BLE_MESH_TEST_TEST_ITEM(1, item_32_33_sender, r_group_2_2);

ssv_ble_mesh_test_item_t *ble_mesh_test_item[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    &item4,//4
    &item5,//4
    &item6,//4
    &item7,//4
    &item8,//4
    &item9,//4
    &item10,//4
    &item11,//4
    &item12,//4
    &item13,//4
    &item14,//4
    &item15,//4
    &item16,//4
    &item17,//4
    &item18,//4
    &item19,//4
    &item20,
    &item5,//21 no relay between 2 test devices
    &item7,//22 no relay between 10 test devices
    NULL,//23 todo GATT 5m
    &item9,//24, connect with phone 5m
    &item20,//25, connect with phone 5m
    NULL,//26 todo GATT 10m
    &item9,//27, connect with phone 10m
    &item20,//28, connect with phone 10m
    NULL,//29 use app
    NULL,//30 use app
    NULL,//31 use app
    &item32_33,//32
    &item32_33,//33
};

#define MESH_COEX_ITEM_32 32
#define MESH_COEX_ITEM_33 33


#define MAX_TOTAL_DEVICE_NUMBER 50
uint32_t g_result[MAX_TOTAL_DEVICE_NUMBER + 1];

uint8_t g_publish_ack_count = 0;

#if CONFIG_BLE_MESH_GPIO_DBG
uint8_t g_ack_device[MAX_TOTAL_DEVICE_NUMBER];
#endif

uint8_t get_publish_ack_count(void)
{
    return g_publish_ack_count;
}
void add_publish_ack_count(uint16_t remote_addr)
{
    BM_EnterCritical();
    g_publish_ack_count++;
#if CONFIG_BLE_MESH_GPIO_DBG
    if ((remote_addr <= MAX_TOTAL_DEVICE_NUMBER) && (remote_addr >= 1))
        g_ack_device[remote_addr - 1] = 1;/*1 is acked*/
#endif
    BM_ExitCritical();
}

void set_publish_ack_count(uint8_t ack_count)
{
    BM_EnterCritical();
    g_publish_ack_count = ack_count;
#if CONFIG_BLE_MESH_GPIO_DBG
    if (0 == ack_count)
        memset(g_ack_device, 0, sizeof(g_ack_device));
#endif
    BM_ExitCritical();
}

TaskHandle_t g_mesh_test_thread_handle = NULL;
TaskHandle_t g_mesh_coex_wifi_thread_handle = NULL;

extern SemaphoreHandle_t ble_mesh_test_perf_send_sema;
EventGroupHandle_t mesh_test_evt_group = NULL;

void ble_mesh_test_event_set_bit(u16 bit)
{
    BaseType_t val = 0;
    if(mesh_test_evt_group)
    {
        if(gOsFromISR)
            xEventGroupSetBitsFromISR(mesh_test_evt_group, bit, &val);
        else
            xEventGroupSetBits(mesh_test_evt_group, bit);

    }
}
#define TIME_WAIT_TEST_RESULT_RECEIVED 5000

static uint16_t g_mesh_test_msg_count = 0;/* receive msg count int server side*/

void ble_mesh_test_clean_msg_count()
{
    printf("********clean g_mesh_test_msg_count*******\n");
    BM_EnterCritical();
    g_mesh_test_msg_count = 0;
    BM_ExitCritical();
}

uint16_t ble_mesh_test_get_msg_count()
{
    return g_mesh_test_msg_count;
}
void ble_mesh_test_add_msg_count()
{
    BM_EnterCritical();
    g_mesh_test_msg_count ++;
    BM_ExitCritical();
}


u8 g_expect_ack_count = 0;
u8 g_expect_ack_count_orig = 0;
u32 g_expect_ack_count_total = 0;
u32 g_recv_ack_count_total = 0;
u32 g_remain_ack_count_total = 0;

u8 ble_mesh_test_get_item_ack_count(void)
{
    return g_expect_ack_count_orig;
}

u8 ble_mesh_test_get_ack_count_remain(void)
{
    return g_expect_ack_count;
}

void ble_mesh_test_set_expect_ack_count(u8 ack_count)
{
    g_expect_ack_count = ack_count;
    g_expect_ack_count_orig = ack_count;
}
void ble_mesh_test_decrease_expect_ack_count(u16 type)
{
    if (!g_expect_ack_count)
        return;

    g_expect_ack_count--;
    if (!g_expect_ack_count)
        ble_mesh_test_event_set_bit(type);
}

#define WAIT_FOR_TEST_EVENT(_event, _time, __failmsg) \
    evtrlt = xEventGroupWaitBits(mesh_test_evt_group, _event, pdTRUE, pdFALSE, _time / portTICK_PERIOD_MS);  \
    if (!(evtrlt & _event)) {  \
        __failmsg;   \
        fail = 1;    \
    }    \

#define FILL_SEND_MODEL_PARAMETER(__model_id, __to_addr, __send_ttl, __send_rel, __app_idx, __net_idx)    \
        model = ble_mesh_get_model(__model_id);  \
        ctx.model = model;  \
        ctx.addr = __to_addr;  \
        ctx.send_ttl = __send_ttl;  \
        ctx.send_rel = __send_rel;    \
        ctx.app_idx = __app_idx;    \
        ctx.net_idx = __net_idx;    \


#define  WORD_TEST_RESULT "item %d, fail rate %2.4f"
#define  WORD_TEST_RESULT_NO_ACK "item %d, no ack, node %d,fail rate %2.4f"

#define WAIT_ALL pdTRUE

/*Just send to air and let tester(RD) know, sender ready to send test msg
 * RD can observe packet in the air and know which node is ready to send
 */
#define  TEST_SHOW_ADDR 0x0099

extern u8_t g_adv_send_fail;
uint8_t g_mesh_test_thread_stop = 0;

uint8_t g_new_run_begin = 0;
#if CONFIG_BLE_MESH_GPIO_DBG
u32 g_test_start_end_gpio = CONFIG_BLE_MESH_GPIO_TEST_START_END;
u32 g_test_fail_gpio = CONFIG_BLE_MESH_GPIO_TEST_FAIL;
#endif
static void mesh_test_thread(void *p)
{
    EventBits_t evtrlt;
    uint32_t pass_count = 0;
    uint8_t fail = 0;
    struct ssv_ble_mesh_test_thread_parameter *param = (struct ssv_ble_mesh_test_thread_parameter*)p;
    ssv_ble_mesh_test_sender_t *sender = NULL;
    ssv_ble_mesh_test_item_t *mesh_test_item = NULL;
    int i = 0;
    int err = SSV_BM_OK;
    uint32_t opcode = 0;
    ssv_ble_mesh_model_t *model = NULL;
    ssv_ble_mesh_msg_ctx_t ctx;
    uint8_t result_status_msg[TEST_RESULT_RETUEN_END] = {0};
    uint8_t vendor_data[BLE_MESH_TEST_VDNDOR_MODEL_LENGTH] = {0};
    uint8_t coll_start_addr = 0, coll_end_addr = 0;
    ssv_ble_mesh_generic_client_set_state_t gen_client_set;
    ssv_ble_mesh_client_common_param_t onoff_common = {
        .msg_timeout = 0,
        .ctx.send_ttl = 3,
    };
    uint64_t send_time_begin = 0,send_time_end = 0, dur_time = 0;
    uint64_t sleep_time = 0;
    uint32_t rx_count_100_percent = 0;/*rx node receive max msg count if fail rate is 0.*/

    memset(&ctx, 0, sizeof(ctx));
    mesh_test_item = ble_mesh_test_item[param->test_item];

    if (mesh_test_item == NULL)
        goto mesh_test_thread_end;

    sender = &(mesh_test_item->senders[param->sender_index]);

    if(sender == NULL)
        goto mesh_test_thread_end;

    if (!param->test_interval)
        param->test_interval = sender->send_interval * 100;
    else
        param->test_interval = param->test_interval * 100;

    /* send SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_RESULT_STATUS here
      *  Just let tester know which sender device ready to send msg
      */
    FILL_SEND_MODEL_PARAMETER(SSV_BLE_MESH_VND_MODEL_ID_TEST_PERF_CLI, TEST_SHOW_ADDR, 2, 0, 0, 0)

    err = ssv_ble_mesh_client_model_send_msg(model, &ctx,
                    SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_ITEM_SET_STATUS, TEST_RESULT_RETUEN_END, result_status_msg, 0, false, ROLE_NODE);
    k_sleep(5000);

#if 1//test

    SSV_LOGI(TAG, "is_on_off %d", sender->is_on_off);

    if (sender->is_on_off) {/*onoff msg init*/
        onoff_common.model = ble_mesh_get_model(SSV_BLE_MESH_MODEL_ID_GEN_ONOFF_CLI);
        //err = ssv_ble_mesh_register_generic_client_callback(ble_mesh_generic_onoff_client_model_cb);
        if (err != SSV_BM_OK) {
            SSV_LOGE(TAG, "mesh_test_thread GenONOFFClient:Reg,fail");
            goto mesh_test_thread_end;
        }
        opcode = BLE_MESH_MODEL_OP_GEN_ONOFF_SET;
        onoff_common.ctx.app_idx = 0;
        onoff_common.opcode = BLE_MESH_MODEL_OP_GEN_ONOFF_SET;
        onoff_common.msg_role = ROLE_NODE;
        onoff_common.ctx.addr = sender->groups;
        onoff_common.ctx.net_idx = 0;
        onoff_common.msg_timeout = param->test_interval;

        //memset(&gen_client_set.onoff_set, 0, sizeof(gen_client_set));
        gen_client_set.onoff_set.op_en = 0;
        gen_client_set.onoff_set.onoff = 0;
        gen_client_set.onoff_set.tid = 0;
        gen_client_set.onoff_set.trans_time = 0;
        gen_client_set.onoff_set.delay = 0;
        FILL_SEND_MODEL_PARAMETER(SSV_BLE_MESH_MODEL_ID_GEN_ONOFF_CLI, sender->groups, 7, 0, 0, 0)
    } else {/*vendor msg init*/
        FILL_SEND_MODEL_PARAMETER(SSV_BLE_MESH_VND_MODEL_ID_TEST_PERF_CLI, sender->groups, 7, 0, 0, 0)
        if (sender->need_ack)
            opcode = SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST;
        else
            opcode = SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_UNACK;

        ble_mesh_create_send_data((char *)vendor_data, BLE_MESH_TEST_VDNDOR_MODEL_LENGTH,
            1, opcode);
    }

    SSV_LOGI(TAG, "%s rnnning test_item %d, sender_index %d", __func__, param->test_item, param->sender_index);

    result_status_msg[TEST_RESULT_RETUEN_ACK_COUNT_A] = ((ble_mesh_test_get_msg_count() > 8) & 0xFF);
    result_status_msg[TEST_RESULT_RETUEN_ACK_COUNT_B] = (ble_mesh_test_get_msg_count() & 0xFF);
    result_status_msg[TEST_RESULT_RETUEN_ACK_ADDR] = bt_mesh_primary_addr();

    ctx.addr = sender->groups;
#if CONFIG_BLE_MESH_GPIO_DBG
    POOL_LOW_GPIO(g_test_fail_gpio);
    POOL_LOW_GPIO(g_test_start_end_gpio);
#endif

    mesh_test_evt_group = xEventGroupCreate();
    if(mesh_test_evt_group == NULL)
        goto mesh_test_thread_end;

#if 0
    for (i=0; i < 8; i++) {
        k_sleep((OS_Random()&0x7)<<2);
    }
#endif

    g_expect_ack_count_total = (param->test_count) * (sender->expect_ack_count);
    g_recv_ack_count_total = 0;
    g_remain_ack_count_total = 0;

    for(i = 1; i <= param->test_count; i++) {
        u32 remain_count = 0;
        if (g_adv_send_fail)
            goto mesh_test_thread_end;

        if (g_mesh_test_thread_stop)
            goto mesh_test_thread_end;

        fail = 0;
        ble_mesh_test_set_expect_ack_count(sender->expect_ack_count);
        SSV_LOGI(TAG, "run %d, beg", i);

        g_new_run_begin = 1;
        if (sender->is_on_off) {//onoff msg
            #if CONFIG_BLE_MESH_GPIO_DBG
            POOL_HIGH_GPIO(g_test_start_end_gpio);
            POOL_LOW_GPIO(g_test_fail_gpio);
            #endif

            err = ssv_ble_mesh_generic_client_set_state(&onoff_common, &gen_client_set);
            send_time_begin = ssv_timer_impl_get_time();
            if (sender->need_ack) {
                WAIT_FOR_TEST_EVENT(GENON_OFF_RECEIVE_ACK, param->test_interval ,
                    remain_count = ble_mesh_test_get_ack_count_remain(); SSV_LOGE(TAG, "item %d, test run %d, ack remain %d", param->test_item, i, remain_count))

#if CONFIG_BLE_MESH_GPIO_DBG
                if (fail && (g_ack_device[5] == 0)) {
                /*pull high GPIO 25, when test item6 fail and do not receive node 6 */
                    POOL_HIGH_GPIO(g_test_fail_gpio);
                    //goto mesh_test_thread_end;
                }
#endif
                WAIT_FOR_TEST_EVENT((MSG_TIMEOUT_EVT|MSG_FAIL_EVT), portMAX_DELAY,
                    SSV_LOGE(TAG, "item %d, test run %d, no msg timeout", param->test_item, i))

#if CONFIG_BLE_MESH_GPIO_DBG
                POOL_LOW_GPIO(g_test_start_end_gpio);
#endif

               if (!fail) {
                   send_time_end = ssv_timer_impl_get_time();
                   dur_time = (send_time_end - send_time_begin)/1000;
                   SSV_LOGD(TAG, "dur_time %u", dur_time);
                   if ( param->test_interval > dur_time) {
                       sleep_time = param->test_interval - dur_time;
                       SSV_LOGI(TAG, "run %d, ok sleep %u", i, sleep_time);
                       OS_MsDelay(sleep_time);
                   } else {
                       SSV_LOGI(TAG, "run %d, ok", i);
                   }
                }

                //SSV_LOGE(TAG, "delta %d orig %d remain %d", (g_expect_ack_count_orig - ble_mesh_test_get_ack_count_remain()), g_expect_ack_count_orig, remain_count);
                //SSV_LOGE(TAG, "total rx %d remain %d", g_recv_ack_count_total, g_remain_ack_count_total);
            }
        } else {//vendor msg
            ctx.send_ttl = 3;

            bt_mesh_tx_reset();
            bt_mesh_rx_reset();
            send_time_begin = ssv_timer_impl_get_time();

            #if CONFIG_BLE_MESH_GPIO_DBG
            POOL_HIGH_GPIO(g_test_start_end_gpio);
            POOL_LOW_GPIO(g_test_fail_gpio);
            #endif

            err = ssv_ble_mesh_client_model_send_msg(model, &ctx, opcode,
                BLE_MESH_TEST_VDNDOR_MODEL_LENGTH, vendor_data, param->test_interval,
                sender->need_ack, ROLE_NODE);

            if (sender->need_ack) {
                WAIT_FOR_TEST_EVENT(VENDOR_RECEIVE_ACK, param->test_interval,
                    SSV_LOGE(TAG, "item %d, test run %d, ack remain %d",
                    param->test_item, i, ble_mesh_test_get_ack_count_remain()))

                send_time_end = ssv_timer_impl_get_time();
                dur_time = (send_time_end - send_time_begin)/1000;
                if ( param->test_interval > dur_time) {
                    sleep_time = param->test_interval - dur_time;
                    SSV_LOGI(TAG, "run %d, ok sleep %u", i, sleep_time);
                    OS_MsDelay(sleep_time);
                } else {
                    SSV_LOGI(TAG, "run %d, ok", i);
                }

#if CONFIG_BLE_MESH_GPIO_DBG
                POOL_LOW_GPIO(g_test_start_end_gpio);

                if (fail) {
                    POOL_HIGH_GPIO(g_test_fail_gpio);
                    //break;
                }
#endif
                WAIT_FOR_TEST_EVENT(MSG_TIMEOUT_EVT, portMAX_DELAY,
                    SSV_LOGE(TAG, "item %d, test run %d, no msg timeout", param->test_item, i))

            } else {/*receive device will send publish msg after receive vendor msg TEST_RESULT_PUBLISH*/
                k_sleep(param->test_interval);
            }
        }

        if ((!fail) && sender->need_ack) {/* only for need_ack, and pass case */
            pass_count ++;
            SSV_LOGI(TAG, "pass_count %d", pass_count);
        }

        if (sender->need_ack) {/* only for need_ack */
            g_recv_ack_count_total += (g_expect_ack_count_orig - remain_count);
            g_remain_ack_count_total += remain_count;
        }
    }

    if (sender->need_ack) {
        SSV_LOGE(TAG, "g_test_count %d, pass_count %d", param->test_count, pass_count);
        SSV_LOGE(TAG, WORD_TEST_RESULT, param->test_item, (param->test_count - pass_count)/(float)param->test_count);
        SSV_LOGE(TAG, "rx_ack_num %d, expect_total_num %d", g_recv_ack_count_total, g_expect_ack_count_total);
    } else if ( 1 == bt_mesh_primary_addr()){/* only Node 1 collect no ack test result*/
        k_sleep((param->sbgr * 1000));//wait for other device finish test
#if 1
        /* collect result for noack msg */
        SSV_LOGI(TAG, "mesh_test_thread collect result group total count %d",
            mesh_test_item->collect_group->count);

        for (i = 0; i < mesh_test_item->collect_group->count; i++) {
            coll_start_addr = mesh_test_item->collect_group->addr[i].start;
            coll_end_addr = mesh_test_item->collect_group->addr[i].end;

            for (;coll_start_addr <= coll_end_addr; coll_start_addr++) {//send collect opcode
                uint8_t retry = 5;
                do {
                    FILL_SEND_MODEL_PARAMETER(SSV_BLE_MESH_VND_MODEL_ID_TEST_PERF_CLI, coll_start_addr, 3, 0, 0, 0)
                    fail = 0;
                    vendor_data[0] = 0;
                    ble_mesh_test_set_expect_ack_count(1);
                    SSV_LOGI(TAG, "collect result from node %d", coll_start_addr);
                    err = ssv_ble_mesh_client_model_send_msg(model, &ctx, SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_RESULT,
                        1, vendor_data, 0, false, ROLE_NODE);

                    retry--;
                    WAIT_FOR_TEST_EVENT(GET_TEST_RESULT, TIME_WAIT_TEST_RESULT_RECEIVED,
                    SSV_LOGE(TAG, "item %d, no ack test result from %d, remain retry %d", param->test_item, ctx.addr, retry))
                    if (!fail)
                        break;
                } while(retry > 0);

                SSV_LOGI(TAG, "no ackresult test_count %d, coll_start_addr %d, g_result[%d] = %d",
                    param->test_count, coll_start_addr, coll_start_addr, g_result[coll_start_addr]);
                rx_count_100_percent = (param->sender_count*param->test_count/mesh_test_item->collect_group->count);
                SSV_LOGE(TAG, WORD_TEST_RESULT_NO_ACK, param->test_item, coll_start_addr,
                    ((float)(rx_count_100_percent - g_result[coll_start_addr]))/rx_count_100_percent);
            }
        }
#endif
    }

#endif//test

mesh_test_thread_end:

    SSV_LOGW(TAG, "%s end", __func__);
#if CONFIG_BLE_MESH_GPIO_DBG
    k_sleep(100);

    POOL_LOW_GPIO(g_test_fail_gpio);
#endif
    if (mesh_test_evt_group) {
        vEventGroupDelete(mesh_test_evt_group);
        mesh_test_evt_group = NULL;
    }
    osi_free(p);
    BM_EnterCritical();
    g_mesh_test_thread_handle = NULL;
    BM_ExitCritical();
    //g_Meshtesting = 0;
    OS_TaskDelete(NULL);
}

#define DATA_FROM_AP_LEN 257
static void mesh_test_wifi_thread(void *p)
{
    stParam cmdparmd;
    char tcp_ip[ATCMD_TCP_IP_STRING_LEN] = {0};
    char tcp_port[ATCMD_TCP_PORT_STRING_LEN] = {0};
    char tcp_0[] = "0";//disconnect
    int ret = 0;
    int i = 0;
    uint16_t fail_count = 0;
    char tcp_send_data[DATA_FROM_AP_LEN] = {0};

    memset(&cmdparmd, 0, sizeof(cmdparmd));
    struct ssv_ble_mesh_test_thread_parameter *param = (struct ssv_ble_mesh_test_thread_parameter*)p;
    if (p == NULL)
        goto mesh_test_wifi_thread_end;

    //fill send data, loop 0~9
    if(param->test_count == 0xFFFF) {/*For debug purpose, only run wifi test*/
        SSV_LOGW(TAG, "Stop Mesh Test for Debug\n");
        g_mesh_test_thread_stop = 1;
    }
    for(i = 0;i < sizeof(tcp_send_data); i++)
        tcp_send_data[i] = (0x30 + i % 10);

    tcp_send_data[DATA_FROM_AP_LEN-1] = 0;

    strcpy(tcp_ip, At_TCPGetConnectIP(NULL));
    strcpy(tcp_port, At_TCPGetConnectPort(NULL));

    if (param->test_item == MESH_COEX_ITEM_32) {
        SSV_LOGW(TAG, "test %d tcp connect %s:%s\n", param->test_count, tcp_ip, tcp_port);
        for (i = 0; i < param->test_count; i++) {
            cmdparmd.argv[0] = tcp_ip;
            cmdparmd.argv[1] = tcp_port;
            cmdparmd.argc = 2;
            ret = At_TCPConnect(&cmdparmd);
            OS_MsDelay(1000);
            if (ERROR_SUCCESS == ret) {
                printf("\33[32mtcp connect ok %d\33[0m\r\n", i);
                cmdparmd.argv[0] = tcp_0;
                cmdparmd.argc = 1;
                At_TCPDisconnect(&cmdparmd);
            } else {
                fail_count++;
                printf("\33[32mtcp connect fail reason %d, fail %d \33[0m\r\n", ret, fail_count);
            }

            OS_MsDelay(1000);
        }

        printf("\33[32mtcp connect end, fail %d \33[0m\r\n", fail_count);
    } else if (param->test_item == MESH_COEX_ITEM_33) {
        SSV_LOGW(TAG, "tcp connect %s:%s\n", tcp_ip, tcp_port);
        cmdparmd.argv[0] = tcp_ip;
        cmdparmd.argv[1] = tcp_port;
        cmdparmd.argc = 2;
        ret = At_TCPConnect(&cmdparmd);
        if (ERROR_SUCCESS != ret) {
            SSV_LOGW(TAG, "TCP Connect fail %d, Please listen port 1111 at AP side\n", ret);
            goto mesh_test_wifi_thread_end;
        }
        SSV_LOGW(TAG, "test tcp send data\n");
        for (i = 0; i < param->test_count; i++) {
            cmdparmd.argv[0] = tcp_0;
            cmdparmd.argv[1] = tcp_send_data;
            cmdparmd.argc = 2;
            ret = At_TCPSend(&cmdparmd);
            OS_MsDelay(1000);
            if (ERROR_SUCCESS == ret) {
                cmdparmd.argv[0] = tcp_0;
                cmdparmd.argc = 1;
                ret = At_TCPRecvlen(&cmdparmd);
                if (ret < (DATA_FROM_AP_LEN - 2)) {
                    fail_count++;
                    printf("\33[32mtcp recv length  %d, fail %d\33[0m\r\n", ret, fail_count);
                }
            }
        }
        printf("\33[32mtcp send end, fail %d\33[0m\r\n", fail_count);
    }

mesh_test_wifi_thread_end:
    SSV_LOGW(TAG, "%s test done\n", __func__);
    osi_free(p);
    g_mesh_coex_wifi_thread_handle = NULL;
    g_mesh_test_thread_stop = 1;
    OS_TaskDelete(NULL);
}

void ble_mesh_test_get_result_return(uint16_t ack_addr, u8_t *msg_data, uint16_t length)
{
    uint32_t count = 0;

    SSV_LOGE(TAG, "get_result_return length %d, ack_addr %d", length, ack_addr);

    if (msg_data == NULL)
        return;

    if (length < TEST_RESULT_RETUEN_END)
        return;

    if (ack_addr > MAX_TOTAL_DEVICE_NUMBER)
        return;

    count = msg_data[TEST_RESULT_RETUEN_ACK_COUNT_A];
    count = (count << 8) | msg_data[TEST_RESULT_RETUEN_ACK_COUNT_B];

    g_result[ack_addr] = count;
    SSV_LOGE(TAG, "result from %d, count %d", ack_addr, count);

}

void delete_subscribe_group(u16_t modelid, u16_t start_addr, u16_t end_addr)
{
    const struct bt_mesh_comp *devcomp = NULL;
    struct bt_mesh_model *model = NULL;
    uint8_t i = 0;
    devcomp = bt_mesh_comp_get();

    if (modelid == SSV_BLE_MESH_MODEL_ID_GEN_ONOFF_SRV)
        model = bt_mesh_model_find(devcomp->elem, modelid);
    else
        model = bt_mesh_model_find_vnd(devcomp->elem, CID_SSV, modelid);

    for (i = 0;i < CONFIG_BLE_MESH_MODEL_GROUP_COUNT; i++) {
        if ((model->groups[i] >= start_addr && model->groups[i] <= end_addr)) {
            SSV_LOGI(TAG, "%s find model 0x%0x subscribe 0x%0x, delete", __func__, model, model->groups[i]);
            model->groups[i] = BLE_MESH_ADDR_UNASSIGNED;
        }
    }
}

#define CREATE_COEX_WIF_TASK()    \
    if (g_mesh_coex_wifi_thread_handle == NULL) {    \
        thread_parameter_coex = osi_malloc(sizeof(struct ssv_ble_mesh_test_thread_parameter));    \
        memcpy(thread_parameter_coex, thread_parameter, sizeof(struct ssv_ble_mesh_test_thread_parameter));    \
        ret = OS_TaskCreate(mesh_test_wifi_thread, "mesh_test_wifi_thread",    \
            CONFIG_BLE_MESH_TEST_TASK_STACK_SIZE, thread_parameter_coex,    \
            OS_TASK_HIGH, &g_mesh_coex_wifi_thread_handle);    \
    }    \


uint8_t ble_mesh_do_test_item(u8_t *msg_data, uint16_t length)
{
    struct ssv_ble_mesh_test_thread_parameter *thread_parameter, *thread_parameter_coex;
    ssv_ble_mesh_test_item_t *mesh_test_item = NULL;
    u8 ret = 0;
    uint8_t i = 0;
    uint8_t sender = 0, receiver = 0;
    u16_t sub_addr_base = 0;/*subscribe group address of tx or rx*/
    u16_t primary_addr = 0;
    u32_t test_msg_type = 0;
    struct bt_mesh_model *model = NULL;
    const struct bt_mesh_comp *devcomp = NULL;
    uint8_t find = 0;
    uint8_t test_scan_win = 0;
    uint8_t test_scan_interval = 0;

    devcomp = bt_mesh_comp_get();

    if(msg_data == NULL) {
        SSV_LOGE(TAG, "msg_data is NULL");
        goto mesh_test_done;
    }

    if(length < TEST_START_SCAN_WIN) {
        SSV_LOGE(TAG, "length %d < %d", length, TEST_START_SCAN_WIN);
        goto mesh_test_done;
    }

    if(length >= TEST_START_END) {
        test_scan_win = msg_data[TEST_START_SCAN_WIN];
        test_scan_interval = msg_data[TEST_START_SCAN_INTERVAL];
        SSV_LOGE(TAG, "get scan_win 0x%0x, scan_interval 0x%0x", test_scan_win, test_scan_interval);
    }

    if (g_mesh_test_thread_handle) {
        SSV_LOGE(TAG, "test already running");
        goto mesh_test_done;
    }

    g_mesh_test_thread_stop = 0;

    thread_parameter = osi_malloc(sizeof(struct ssv_ble_mesh_test_thread_parameter));
    thread_parameter->test_item = msg_data[TEST_START_TEST_ITEM];

    SSV_LOGW(TAG, "test_item %d", thread_parameter->test_item);

    if (thread_parameter->test_item >= ARRAY_SIZE(ble_mesh_test_item))
        goto mesh_test_done;

    mesh_test_item = ble_mesh_test_item[thread_parameter->test_item];

    if(mesh_test_item == NULL) {
        SSV_LOGW(TAG, "test_item %d is not do here", thread_parameter->test_item);
        goto mesh_test_done;
    }

    thread_parameter->test_count = (msg_data[TEST_START_TEST_COUNT_A] << 8);
    thread_parameter->test_count |= msg_data[TEST_START_TEST_COUNT_B];
    thread_parameter->test_interval = msg_data[TEST_START_INTERVAL];
    thread_parameter->sbgr = msg_data[TEST_START_SBGR];

    primary_addr = bt_mesh_primary_addr();

    memset(g_result, 0, sizeof(g_result));
    /* clean test data*/
    ble_mesh_test_clean_msg_count();
    init_sync_adv();
    bt_mesh_rpl_reset_seq();
    //delete all subscribe group address and add subscribe if rx is needed after.
    delete_subscribe_group(SSV_BLE_MESH_MODEL_ID_GEN_ONOFF_SRV, ONOFF_GROUP_ADDR0, ONOFF_GROUP_ADDR4);
    delete_subscribe_group(SSV_BLE_MESH_VND_MODEL_ID_TEST_PERF_SRV, VENDOR_GROUP_ADDR0, VENDOR_GROUP_ADDR4);
    if (mesh_test_item->senders[i].is_on_off) {
        test_msg_type = SSV_BLE_MESH_MODEL_ID_GEN_ONOFF_SRV;
        sub_addr_base = ONOFF_GROUP_ADDR0;
        model = bt_mesh_model_find(devcomp->elem, test_msg_type);
    } else {
        test_msg_type = SSV_BLE_MESH_VND_MODEL_ID_TEST_PERF_SRV;
        sub_addr_base = VENDOR_GROUP_ADDR0;
        model = bt_mesh_model_find_vnd(devcomp->elem, CID_SSV, SSV_BLE_MESH_VND_MODEL_ID_TEST_PERF_SRV);
    }

    SSV_LOGI(TAG, "%s I am device %d,", __func__, primary_addr);
    ssv_ble_mesh_set_scan_parameter(test_scan_win, test_scan_interval);

    g_Meshtesting = 1;

    for (i = 0;i < mesh_test_item->senders_count; i++) {
        if (primary_addr == mesh_test_item->senders[i].addr) {
            sender = 1;
            thread_parameter->sender_index = i;
            thread_parameter->sender_count = mesh_test_item->senders_count;
            break;
        }
    }

    if (!sender) {
        for (i = 0;i < mesh_test_item->collect_group->count; i++) {
            if (primary_addr >= mesh_test_item->collect_group->addr[i].start &&
                primary_addr <= mesh_test_item->collect_group->addr[i].end) {
                receiver = 1;
                break;
            }
        }

        if (!receiver)
            goto mesh_test_done;

        sub_addr_base += i;
        SSV_LOGI(TAG, "%s receiver, msg_type 0x%04x, subscribe 0x%04x", __func__, test_msg_type, sub_addr_base);

        /*add subscribe address*/
        for (i = 0;i < CONFIG_BLE_MESH_MODEL_GROUP_COUNT; i++) {
            if (model->groups[i] == BLE_MESH_ADDR_UNASSIGNED) {
                model->groups[i] = sub_addr_base;
                SSV_LOGI(TAG, "%s model 0x%0x subscribe 0x%0x add", __func__, test_msg_type, sub_addr_base);
                break;
            }
        }

    }

    if (receiver || sender) {
        if ((thread_parameter->test_item == MESH_COEX_ITEM_32 || thread_parameter->test_item == MESH_COEX_ITEM_33)) {
            if (g_mesh_coex_wifi_thread_handle == NULL) {
                    thread_parameter_coex = osi_malloc(sizeof(struct ssv_ble_mesh_test_thread_parameter));
                    memcpy(thread_parameter_coex, thread_parameter, sizeof(struct ssv_ble_mesh_test_thread_parameter));
                    ret = OS_TaskCreate(mesh_test_wifi_thread, "mesh_test_wifi_thread",
                        CONFIG_BLE_MESH_TEST_TASK_STACK_SIZE, thread_parameter_coex,
                        OS_TASK_HIGH, (OsTaskHandle *)&g_mesh_coex_wifi_thread_handle);
            }
            thread_parameter->test_count = 0xFFFF;/*let mesh test forever until wifi coex thread finish*/
        }

        if (receiver)
            goto mesh_test_done;
    } else
        goto mesh_test_done;

    SSV_LOGI(TAG, "%s sender, msg_type 0x%04x", __func__, test_msg_type);

    BM_EnterCritical();
    /* this device need to send msg, create  task sending msg*/

    if (g_mesh_test_thread_handle == NULL) {
        ret = OS_TaskCreate(mesh_test_thread, "mesh_test_thread", CONFIG_BLE_MESH_TEST_TASK_STACK_SIZE, thread_parameter,
            OS_TASK_LOW, (OsTaskHandle *)&g_mesh_test_thread_handle);

        configASSERT(ret == 1);
    } else
         SSV_LOGW(TAG, "test is running, please stop first");

    BM_ExitCritical();
    ret = 1;

mesh_test_done:

    return ret;
}

void ssv_handle_gen_onoff_msg(ssv_ble_mesh_model_t *model,
    ssv_ble_mesh_msg_ctx_t *ctx, ssv_ble_mesh_server_recv_gen_onoff_set_t *set)
{
    ssv_err_t rc = SSV_FAIL;
    ssv_ble_mesh_gen_onoff_srv_t *srv = model->user_data;

    switch (ctx->recv_op) {
    case SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_GET:
        ssv_ble_mesh_server_model_send_msg(model, ctx,
            SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS, sizeof(srv->state.onoff), &srv->state.onoff);
        break;
    case SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_SET:
    case SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_SET_UNACK:
        if (set->op_en == false) {
            srv->state.onoff = set->onoff;
        } else {
            /* TODO: Delay and state transition */
            srv->state.onoff = set->onoff;
        }
        if (ctx->recv_op == SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_SET) {
            rc = ssv_ble_mesh_server_model_send_msg(model, ctx,
                SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS, sizeof(srv->state.onoff), &srv->state.onoff);
            if (SSV_BM_OK != rc) {
                printf("!!!!!!!!![%s]rc=%d\n", __func__, rc);
            }
        }
        //ssv_ble_mesh_model_publish(model, SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS,
        //    sizeof(srv->state.onoff), &srv->state.onoff, ROLE_NODE);
        //example_change_led_state(model, ctx, srv->state.onoff);
        break;
    default:
        break;
    }

}



