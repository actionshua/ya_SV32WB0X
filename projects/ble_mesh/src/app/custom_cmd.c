
#include <stdio.h>
#include <string.h>
#include "soc_types.h"
#include "soc_defs.h"
#include "osal.h"
#include "atcmd.h"
#include "cli.h"
#include "error.h"

#include <lowpower.h>
#include <logger.h>
#include <drv_tim_timer.h>

#define CMD_TAG       LOG_TAG_CMD
#define CMD_LOG_E(format, ...) log_e(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_W(format, ...) log_w(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_I(format, ...) log_i(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_D(format, ...) log_d(CMD_TAG, format, ##__VA_ARGS__)
#define CMD_LOG_V(format, ...) log_v(CMD_TAG, format, ##__VA_ARGS__)

#if MESH_BLE_EN
#include "net.h"
#endif

int Cmd_meminfo(s32 argc, char *argv[])
{
    printf("\n");
    OS_MemInfo();
    return ERROR_SUCCESS;
}

int Cmd_sysinfo(s32 argc, char *argv[])
{
    printf("\n");
    OS_SysInfo();
    return ERROR_SUCCESS;
}

int Cmd_WriteReg32 (s32 argc, char *argv[])
{
    char *pkey = 0, *pvalue = 0;

    if (argc < 3) {
        return ERROR_INVALID_PARAMETER;
    }

    pkey = argv[1];
    pvalue = argv[2];

    if( pkey == 0 || pvalue == 0)
        return ERROR_INVALID_PARAMETER;

    unsigned int address = strtoul(pkey, NULL, 16);
    unsigned int data = strtoul(pvalue, NULL, 16);

    printf("reg : write 0x%x  0x%x \n", address, data);

    REG32(address)  = data;

    return ERROR_SUCCESS;
}

int Cmd_ReadReg32 (s32 argc, char *argv[])
{
    char *pkey = 0;
    unsigned int address;
    if (argc < 2) {
        return ERROR_INVALID_PARAMETER;
    }

    pkey = argv[1];

    address = strtoul(pkey, NULL, 16);

    printf("reg : read 0x%08x  0x%08x \n", address, (unsigned int)REG32(address));
    return ERROR_SUCCESS;
}

#if MESH_BLE_EN

#if 0
extern int bt_mesh_dbg_flag;
int Cmd_dbg (s32 argc, char *argv[])
{
    unsigned int address;
    if (argc < 2) {
        return ERROR_INVALID_PARAMETER;
    }

    bt_mesh_dbg_flag = atoi(argv[1]);

    return ERROR_SUCCESS;
}

extern u32 g_adv_delay_group_num;
extern u32 g_adv_delay_group_gap;
extern u32 g_adv_delay_group_offset;
extern u32 g_adv_delay_group_threshold;
extern u32 g_adv_delay_group_shift;
extern u32 g_adv_delay_group_mod;
extern u32 g_adv_delay_group_rand;
extern u32 g_adv_delay_group_sub_grp;
extern u32 g_adv_delay_group_sub;

extern u32 g_adv_delay_group_profile;
extern u32 g_adv_delay_group_profile_cnt;

extern u32 g_adv_relay_group_mask;
extern u32 g_adv_relay_group_num;
extern u32 g_adv_relay_group_threshold;
extern u32 g_adv_relay_group_offset;
extern u32 g_adv_relay_group_profile;
extern u32 g_adv_relay_group_profile_cnt;

extern u32 g_mesh_tx_count;
extern u32 g_mesh_tx_duration;
extern u32 g_adv_random_hop;
extern u32 g_ll_adv_gap_rand;

extern int rf_enable_tcsr(uint8_t enable);

extern u8 g_ble_adv_ch_min;
extern u8 g_ble_adv_ch_max;

int Cmd_adv_delay (s32 argc, char *argv[])
{
    unsigned int address;
    if (argc < 9) {
        printf("\nread adv delay group num(%d) gap(%d) offset(%d) threshold(%d) shift(%d) mod(%d) rand(%d) subgrp(%d) sub(%d) profile(%d) cnt(%d) avg(%d)\n",
                g_adv_delay_group_num,
                g_adv_delay_group_gap,
                g_adv_delay_group_offset,
                g_adv_delay_group_threshold,
                g_adv_delay_group_shift,
                g_adv_delay_group_mod,
                g_adv_delay_group_rand,
                g_adv_delay_group_sub_grp,
                g_adv_delay_group_sub,
                g_adv_delay_group_profile,
                g_adv_delay_group_profile_cnt,
                (g_adv_delay_group_profile_cnt>0)?(g_adv_delay_group_profile/g_adv_delay_group_profile_cnt):0
              );
        return ERROR_SUCCESS;
    }

    g_adv_delay_group_num = atoi(argv[1]);
    g_adv_delay_group_gap = atoi(argv[2]);
    g_adv_delay_group_offset = atoi(argv[3]);
    g_adv_delay_group_threshold = atoi(argv[4]);
    g_adv_delay_group_shift = atoi(argv[5]);
    g_adv_delay_group_mod = atoi(argv[6]);
    g_adv_delay_group_rand = atoi(argv[7]);
    g_adv_delay_group_sub_grp = atoi(argv[8]);

    printf("\nadv_delay group_num(%d) gap(%d) offset(%d) threshold(%d) shift(%d) mod(%d) rand(%d) subgrp(%d)\n",
            g_adv_delay_group_num,
            g_adv_delay_group_gap,
            g_adv_delay_group_offset,
            g_adv_delay_group_threshold,
            g_adv_delay_group_shift,
            g_adv_delay_group_mod,
            g_adv_delay_group_rand,
            g_adv_delay_group_sub_grp
          );

    return ERROR_SUCCESS;
}
int Cmd_adv_relay (s32 argc, char *argv[])
{
    unsigned int address;
    if (argc < 5) {
        printf("\nread adv relay group relay_mask(%d) relay_num(%d) threshold(%d) offset(%d) profile(%d) cnt(%d) avg(%d)\n",
            g_adv_relay_group_mask,
            g_adv_relay_group_num,
            g_adv_relay_group_threshold,
            g_adv_relay_group_offset,
            g_adv_relay_group_profile,
            g_adv_relay_group_profile_cnt,
            (g_adv_relay_group_profile_cnt>0)?(g_adv_relay_group_profile/g_adv_relay_group_profile_cnt):0
          );
        return ERROR_SUCCESS;
    }

    g_adv_relay_group_mask = atoi(argv[1]);
    g_adv_relay_group_num = atoi(argv[2]);
    g_adv_relay_group_threshold = atoi(argv[3]);
    g_adv_relay_group_offset = atoi(argv[4]);

    printf("\nadv_relay relay_mask(%d) relay_num(%d) threshold(%d) offset(%d)\n",
            g_adv_relay_group_mask,
            g_adv_relay_group_num,
            g_adv_relay_group_threshold,
            g_adv_relay_group_offset
          );

    return ERROR_SUCCESS;
}

int Cmd_adv_tx (s32 argc, char *argv[])
{
    unsigned int address;
    static u8 mesh_disable_tc = 1;

    if (argc < 8) {
        printf("\nread adv tx count(%d), duration(%d) hop(%d) ll_adv_gap(%d) disble_tc(%d) ch_min(%d) ch_max(%d)\n",
            g_mesh_tx_count,
            g_mesh_tx_duration,
            g_adv_random_hop,
            g_ll_adv_gap_rand,
            mesh_disable_tc,
            g_ble_adv_ch_min,
            g_ble_adv_ch_max
          );
        return ERROR_SUCCESS;
    }

    g_mesh_tx_count = atoi(argv[1]);
    g_mesh_tx_duration = atoi(argv[2]);
    g_adv_random_hop = atoi(argv[3]);
    g_ll_adv_gap_rand = atoi(argv[4]);
    mesh_disable_tc = atoi(argv[5]);
    g_ble_adv_ch_min = atoi(argv[6]);
    g_ble_adv_ch_max = atoi(argv[7]);

    if (mesh_disable_tc) {
        rf_enable_tcsr(false);
    } else {
        rf_enable_tcsr(true);
    }

    printf("\nadv_tx count(%d) duration(%d) hop(%d) ll_adv_gap(%d) disable_tc(%d) ch_min(%d) ch_max(%d)\n",
            g_mesh_tx_count,
            g_mesh_tx_duration,
            g_adv_random_hop,
            g_ll_adv_gap_rand,
            mesh_disable_tc,
            g_ble_adv_ch_min,
            g_ble_adv_ch_max
          );

    return ERROR_SUCCESS;
}
#endif
extern u8 g_Meshtesting;
int Cmd_mesh_test (s32 argc, char *argv[])
{
    if (argc < 2) {
        printf("\nCmd mesh test g_Meshtesting(%d)\n", g_Meshtesting);
        return ERROR_SUCCESS;
    }

    g_Meshtesting = atoi(argv[1]);
    printf("\nSet g_Meshtesting(%d)\n", g_Meshtesting);
    return ERROR_SUCCESS;
}

int Cmd_mesh_rpl_reset_seq(s32 argc, char *argv[])
{
    printf("\nCmd_mesh_rpl_reset_seq\n");

    bt_mesh_rpl_reset_seq();
    return ERROR_SUCCESS;
}

int Cmd_mesh_rpl_show(s32 argc, char *argv[])
{
    bt_mesh_rpl_show();
    return ERROR_SUCCESS;
}

extern u8 g_msg_seg_status_xmit;
int Cmd_mesh_seg_param(s32 argc, char *argv[])
{
    if (argc < 2) {
        printf("\nCmd g_msg_seg_status_xmit(%d)\n", g_msg_seg_status_xmit);
        return ERROR_SUCCESS;
    }

    g_msg_seg_status_xmit = g_Meshtesting = atoi(argv[1]);
    return ERROR_SUCCESS;
}

extern u8 g_MeshMsgGap;
extern u8 g_MeshSyncGap;
extern u8 g_MeshAckGap;

extern u8 g_MeshMsgSleepGap;
extern u8 g_MeshSyncSleepGap;
extern u8 g_MeshAckSleepGap;
int Cmd_mesh_sync_param(s32 argc, char *argv[])
{
    if (argc < 4) {
        printf("\nCmd mesh test g_MeshMsgGap(%d), g_MeshMsgSleepGap(%d)\n",
            g_MeshMsgGap, g_MeshMsgSleepGap);
        printf("\nCmd mesh test g_MeshSyncGap(%d), g_MeshSyncSleepGap(%d)\n",
            g_MeshSyncGap, g_MeshSyncSleepGap);
        return ERROR_SUCCESS;
    } else {
        g_MeshMsgGap = atoi(argv[1]);
        g_MeshMsgSleepGap = atoi(argv[2]);

        g_MeshSyncGap = atoi(argv[3]);
        g_MeshSyncSleepGap = atoi(argv[4]);
    }

    return ERROR_SUCCESS;
}

int Cmd_mesh_ack_param(s32 argc, char *argv[])
{
    if (argc < 2) {
        printf("\nCmd mesh test g_MeshAckGap(%d), g_MeshAckSleepGap(%d)\n",
            g_MeshAckGap, g_MeshAckSleepGap);
        return ERROR_SUCCESS;
    } else {
        g_MeshAckGap = atoi(argv[1]);
        g_MeshAckSleepGap = atoi(argv[2]);
    }

    return ERROR_SUCCESS;
}

#endif

#if BLE_GAP_ATCMD_EN
extern int At_ble_init(stParam *param);
extern int At_ble_start_adv(stParam *param);

int Cmd_ble_test1(s32 argc, char *argv[])
{
    stParam param;
    printf("%s\n",__FUNCTION__);
    //AT+bleinit
    param.argv[0]=NULL;
    param.argc=0;
    At_ble_init(&param);

    //AT+bleADV=1
    printf("ADV on\n");
    param.argv[0]="1";
    param.argc=1;
    At_ble_start_adv(&param);
    printf("%s end\n",__FUNCTION__);
    return ERROR_SUCCESS;
}

int Cmd_ble_test2(s32 argc, char *argv[])
{
    uint8_t i=0;
    stParam param;
    printf("%s\n",__FUNCTION__);
    //AT+bleinit
    param.argv[0]=NULL;
    param.argc=0;
    At_ble_init(&param);

    for(i=0;i<100;i++)
    {
        //AT+bleADV=1
        printf("ADV on\n");
        param.argv[0]="1";
        param.argc=1;
        At_ble_start_adv(&param);

        OS_MsDelay(20);

        //AT+bleADV=1
        printf("ADV off\n");
        param.argv[0]="0";
        param.argc=1;
        At_ble_start_adv(&param);
    }
    printf("%s end\n",__FUNCTION__);
    return ERROR_SUCCESS;
}

int Cmd_ble_test3(s32 argc, char *argv[])
{
    uint8_t i=0;
    char dev_name[32]={0};
    stParam param;
    printf("%s\n",__FUNCTION__);
    //AT+bleinit
    param.argv[0]=NULL;
    param.argc=0;
    At_ble_init(&param);

    for(i=0;i<100;i++)
    {
        //AT+bleADV=1
        printf("ADV off\n");
        param.argv[0]="0";
        param.argc=1;
        At_ble_start_adv(&param);

        //AT+bleADV=1
        param.argv[0]="1";
        memset(dev_name,0,sizeof(dev_name));
        snprintf(dev_name,sizeof(dev_name),"ble_test3 %d",i);
        param.argv[1]=(char *)dev_name;
        param.argc=2;
        printf("ADV on %s\n",dev_name);
        At_ble_start_adv(&param);

        OS_MsDelay(20);


    }
    printf("%s end\n",__FUNCTION__);
    return ERROR_SUCCESS;
}
#endif

#if (BLE_GAP_ATCMD_EN && BLE_GATTC_ATCMD_EN && BLE_GATTS_ATCMD_EN)

#define CUSTOM_BLE_TEST_COUNT_20S 720
#define CUSTOM_BLE_TEST_COUNT_200MS 10000
extern int At_ble_gattc_write_char(stParam *param);
int Cmd_ble_test6(s32 argc, char *argv[])
{
    int16_t test_count = 0;
    char *ptest_count = NULL;
    char *gattc_if = NULL, *conn_id = NULL, *handle = NULL;
    char *value_len = NULL, *value = NULL, *write_type = NULL;
    char *auth_req = NULL;
    char *send_interval = NULL;
    char *send_data = NULL;
    unsigned char send_seg_count = 0;

    stParam param;
    param.argv[0] = NULL;
    param.argc = 0;

    send_interval = argv[1];
    ptest_count = argv[2];
    gattc_if = argv[3];
    conn_id = argv[4];
    handle = argv[5];
    value_len = argv[6];
    write_type = argv[7];
    auth_req = argv[8];

    unsigned int v_send_interval = strtoul(send_interval, NULL, 10);
    unsigned char v_gattc_if = strtoul(gattc_if, NULL, 10);
    unsigned char v_conn_id = strtoul(conn_id, NULL, 10);
    unsigned char v_handle = strtoul(handle, NULL, 10);
    unsigned char v_value_len = strtoul(value_len, NULL, 10);
    unsigned char v_write_type = strtoul(write_type, NULL, 10);
    unsigned char v_auth_req = strtoul(auth_req, NULL, 10);

    test_count = strtoul(ptest_count, NULL, 10);

    if (v_value_len > 0 && v_value_len < 1024) {
        printf("%s OS_MemZalloc %d\n",__FUNCTION__, v_value_len);
        send_data = OS_MemZalloc(v_value_len);

        for (int i = 0; i < v_value_len; i ++)
            send_data[i] = i;
    } else {
        printf("%s send_data_len is %d\n",__FUNCTION__, v_value_len);
        return ERROR_INVALID_PARAMETER;
    }

    param.argv[0] = argv[3];
    param.argv[1] = argv[4];
    param.argv[2] = argv[5];
    param.argv[3] = argv[6];
    param.argv[4] = send_data;
    param.argv[5] = argv[7];
    param.argv[6] = argv[8];
    param.argc = 7;

    do {
        At_ble_gattc_write_char(&param);
        test_count--;
        printf("%s test_count %d, v_send_interval %d\n",__FUNCTION__, test_count, v_send_interval);
        OS_MsDelay(v_send_interval);
    } while(test_count > 0);

    if (send_data)
        OS_MemFree(send_data);

    printf("%s end\n",__FUNCTION__);
    return ERROR_SUCCESS;
}

extern int At_ble_send_indication(stParam *param);
int Cmd_ble_test12(s32 argc, char *argv[])
{
    char *ptest_count = NULL;
    char *send_interval = NULL, *gatts_if = NULL, *conn_id = NULL;
    char *att_handle = NULL, *need_confirm = NULL;
    char *send_data = NULL, *send_data_len = NULL;
    unsigned char send_seg_count = 0;

    printf("%s\n",__FUNCTION__);
    stParam param;
    param.argv[0] = NULL;
    param.argc = 0;

    if (argc < 5) {
        return ERROR_INVALID_PARAMETER;
    }

    send_interval = argv[1];
    ptest_count = argv[2];
    gatts_if = argv[3];
    conn_id = argv[4];
    att_handle = argv[5];
    send_data_len = argv[6];
    need_confirm = argv[7];

    unsigned int v_send_interval = strtoul(send_interval, NULL, 10);
    unsigned char v_gatts_if = strtoul(gatts_if, NULL, 10);
    unsigned char v_conn_id = strtoul(conn_id, NULL, 10);
    unsigned char v_att_handle = strtoul(att_handle, NULL, 10);
    unsigned char v_send_data_len = strtoul(send_data_len, NULL, 10);
    unsigned char v_need_confirm = strtoul(need_confirm, NULL, 10);

    unsigned int test_count = strtoul(ptest_count, NULL, 10);

    if (v_send_data_len > 0 && v_send_data_len < 1024) {
        printf("%s OS_MemZalloc %d\n",__FUNCTION__, v_send_data_len);
        send_data = OS_MemZalloc(v_send_data_len);
        for (int i = 0; i < v_send_data_len;i++)
            send_data[i] = i;
    } else {
        printf("%s send_data_len is %d\n",__FUNCTION__, v_send_data_len);
        return ERROR_INVALID_PARAMETER;
    }

    //argv[1]; interval
    param.argv[0] = argv[3];
    param.argv[1] = argv[4];
    param.argv[2] = argv[5];
    param.argv[3] = argv[6];
    param.argv[4] = send_data;
    param.argv[5] = argv[7];
    param.argc = 6;

    do {
        printf("%s test_count %d\n",__FUNCTION__, test_count);
        At_ble_send_indication(&param);
        OS_MsDelay(v_send_interval);
    } while (test_count > 0);

    printf("%s end\n",__FUNCTION__);
    return ERROR_SUCCESS;
}

#endif

/* ---------------------- Registered CMDs to CMD Table ---------------------- */
const CLICmds gCustomCmdTable[] =
{
    { "regw",               Cmd_WriteReg32,     "regw"},
    { "regr",               Cmd_ReadReg32,      "regr"},

    { "meminfo",            Cmd_meminfo,        "meminfo"},
    { "sysinfo",            Cmd_sysinfo,        "sysinfo"},
#if MESH_BLE_EN
    //{ "dbg",                Cmd_dbg,            "dbg"},
    //{ "adv_delay",          Cmd_adv_delay,      "adv_delay"},
    //{ "adv_relay",          Cmd_adv_relay,      "adv_relay"},
    //{ "adv_tx",             Cmd_adv_tx,         "adv_tx"},
    { "mesh_test",          Cmd_mesh_test,       "mesh_test"},
    { "mesh_rpl_reset_seq", Cmd_mesh_rpl_reset_seq,       "mesh_rpl_reset_seq"},
    { "mesh_rpl_show",      Cmd_mesh_rpl_show,       "mesh_rpl_show"},
    { "mesh_sync_param",      Cmd_mesh_sync_param,       "mesh_sync_param"},
    { "mesh_ack_param",      Cmd_mesh_ack_param,       "mesh_ack_param"},
#endif
#if BLE_GAP_ATCMD_EN
    { "ble_test1",         Cmd_ble_test1,       "ble_test1"},
    { "ble_test2",         Cmd_ble_test2,       "ble_test2"},
    { "ble_test3",         Cmd_ble_test3,       "ble_test3"},
#endif
#if (BLE_GAP_ATCMD_EN && BLE_GATTC_ATCMD_EN && BLE_GATTS_ATCMD_EN)
    { "ble_test6",         Cmd_ble_test6,       "ble_test7 and 8"},
    { "ble_test7",         Cmd_ble_test6,       "ble_test7 and 8"},
    { "ble_test12",         Cmd_ble_test12,       "ble_test12 and 13"},
    { "ble_test13",         Cmd_ble_test12,       "ble_test12 and 13"},
#endif
    { (const char *)NULL, (CliCmdFunc)NULL,   (const char *)NULL },
};


