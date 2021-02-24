#ifndef _SYS_API_H_
#define _SYS_API_H_


#include "les_if/api/inc/svc_def.h"
#include "les_if/api/inc/les_def.h"
#include "les_if/api/inc/gap_api.h"
#include "les_if/api/inc/att_api.h"
#include "les_if/api/inc/gatts_api.h"
#include "les_if/api/inc/gattc_api.h"
#include "les_if/api/inc/gattm_api.h"
#include "les_if/api/inc/smp_api.h"
#include "les_if/api/inc/l2cap_api.h"
#include "les_if/api/inc/hci_api.h"
#include "les_if/api/inc/ll_api.h"
#include "power.h"
#include "ilog.h"
#include "../lestack/cli/mini_cli.h"



typedef void * les_handle;



typedef enum
{
    SYS_SVCMD_GET_LES_EVENT = SYS_SVC_NUM_MIN,
    SYS_SVCMD_GET_LES_EVENT_SIZE,
    SYS_SVCMD_GET_RAND,
    SYS_SVCMD_RESET,
    SYS_SVCMD_ENABLE_BLE,
    SYS_SVCMD_ENABLE_LOW_POWER,
    SYS_SVCMD_ENABLE_FEATURE,
    SYS_SVCMD_ADC_MEASURE,
    SYS_SVCMD_ENABLE_PATCH,
    SYS_SVCMD_GET_PATCH_STATUS,
    SYS_SVCMD_ECHO,
    SYS_SVCMD_GET_SLEEP_MODULE,
    SYS_SVCMD_GET_LOG_MODULE,
    SYS_SVCMD_LE_RECEIVER_TEST,
    SYS_SVCMD_LE_TRANSMITTER_TEST,
    SYS_SVCMD_LE_TEST_END,
    SYS_SVCMD_CLI_GET_ILOG_HANDLE,
    SYS_SVCMD_CLI_REGISTER_CMD,
    SYS_SVCMD_INTERNAL_TEST,
    SYS_SVCMD_BSP_ARG_TEST_0,
    SYS_SVCMD_BSP_ARG_TEST_1,
    SYS_SVCMD_BSP_ARG_TEST_2,
    SYS_SVCMD_BSP_ARG_TEST_3,
    SYS_SVCMD_BSP_ARG_TEST_4,

    SYS_SVCMD_WDT_OPTION,
    SYS_SVCMD_GET_LES_EVENT_QUEUE_DEPTH,

} SYS_SVCMD;



typedef enum
{
    SYS_LES_EVENT_ECHO = SYS_LES_EVENT_ID_MIN,
    SYS_LES_EVENT_HCI_ASYNC_EVT,
    SYS_LES_EVENT_HARDFAULT,

} SYS_LES_EVENT;



typedef enum
{
    SYS_RESULT_SUCCESS = ERR_SUCCESS,
    SYS_RESULT_MIN = ERR_SYS,

    SYS_RESULT_FAIL = SYS_RESULT_MIN,
    SYS_RESULT_LES_EVENT_QUEUE_FULL,
    SYS_RESULT_LES_EVENT_QUEUE_EMPTY,
    SYS_RESULT_INVALID_LES_EVENT_SIZE,
    SYS_RESULT_INVALID_PARAM,

    SYS_RESULT_ADC_ADC_READ_OUT_FAIL,
    SYS_RESULT_ADC_RESOURCE_UNAVAILABLE,

    SYS_RESULT_MAX,

} SYS_RESULT;



typedef enum
{
    SYS_HARDFAULT_NONE = HARDFAULT_NONE,
    SYS_HARDFAULT_MIN = HARDFAULT_SYS,
    SYS_HARDFAULT_LES_EVENT_QUEUE_FULL = SYS_HARDFAULT_MIN,
    SYS_HARDFAULT_MAX,

} SYS_HARDFAULT;



typedef enum
{
    SYS_PATCH_STATUS_NONE = 0,
    SYS_PATCH_STATUS_APPLIED,

} SYS_PATCH_STATUS;



#define SYS_RAND_VALUE_SIZE_MAX     8
typedef struct
{
    uint8_t value_size;
    uint8_t value[SYS_RAND_VALUE_SIZE_MAX];

} sys_rand_value_st;



typedef struct
{
    pf_do_sleep         do_sleep;
    pf_is_cold_boot     is_cold_boot;
    u32                 *can_sleep;
    u8                  *appl_wake_lock;
    u8                  *flash_low_power;

} sys_sleep_module_st;



typedef struct
{
    pf_icomm_putc ilog_putc;

} sys_log_module_st;



typedef struct
{
    uint32_t le_host_prep_exec_write_support : 1;
    uint32_t le_host_key_distribution_init : 3;
    uint32_t le_icmd_user_authentication : 1;
    uint32_t le_host_reserved : 26;
    uint32_t le_ll_scan_early_stop_workaround : 1;

} sys_feature_st;



/**
 * hardfault evt:
 *  - code: globally defined
 *  - description: a code-depedentent description
 *      + in BLE_LL, may used to store anchor tstamp
 *
 */
typedef struct
{
    uint8_t     code;
    uint32_t    description;

} sys_hardfault_st;



typedef struct
{
    union
    {
        uint32_t                echo;           /// SYS_LES_EVENT_ECHO
        sys_hardfault_st        hardfault;      /// SYS_LES_EVENT_HARDFAULT

    } data;

} sys_les_event_st;



typedef struct 
{
    uint16_t id;
    uint16_t size;

} les_event_header_st;



typedef void (*les_event_status_cb_t)(uint8_t status, uint32_t info);



typedef struct 
{
    uint32_t                info;
    les_event_status_cb_t   status_cb;

} les_event_status_st;



typedef struct
{
    les_event_header_st header;
    les_event_status_st     status;

    union
    {
        void                *void_les_event;
        gap_les_event_st    *gap_les_event;
        att_les_event_st    *att_les_event;
        smp_les_event_st    *smp_les_event;
        gatts_les_event_st  *gatts_les_event;
        gattc_les_event_st  *gattc_les_event;
        l2cap_les_event_st  *l2cap_les_event;
        sys_les_event_st    *sys_les_event;
        hci_les_event_st    *hci_les_event;
        ll_les_event_st     *ll_les_event;

    } body;

} les_event_st;


typedef enum
{
    SYS_32K_RC_1000MS_CALI      =   0x11,
    SYS_32K_RC_2000MS_CALI      =   0x12,
    SYS_32K_RC_4000MS_CALI      =   0x14,
    SYS_32K_RC_10000MS_CALI     =   0x18,
    SYS_32K_RC_16000MS_CALI     =   0x30,
} SYS_32K_SEL;



typedef struct
{
    SYS_LOW_POWER_SEL       sleep_deep;

    // only active when E_LP_HIBERNATE
    SYS_32K_SEL             cali_select;

} sys_sleep_st;



/*typedef enum
{
    WDT_DBG         = 0,                // to cli.
    WDT_MCU_RESET   = 1,          // only mcu reset.
    WDT_SYS_RESET   = 2,          // ic reset!!!

} SYS_WDT_DEFAULT_SEL;*/



DEF_SVC(SYS_SVCMD_GET_LES_EVENT,                uint32_t,   les_sys_get_les_event(les_event_st *les_event));
DEF_SVC(SYS_SVCMD_GET_LES_EVENT_SIZE,           uint32_t,   les_sys_get_les_event_size(uint16_t *les_event_size));
DEF_SVC(SYS_SVCMD_GET_RAND,                     uint32_t,   les_sys_get_rand(sys_rand_value_st *rand_value));
DEF_SVC(SYS_SVCMD_RESET,                        uint32_t,   les_sys_reset(uint8_t option));
DEF_SVC(SYS_SVCMD_ENABLE_BLE,                   uint32_t,   les_sys_enable_ble(uint8_t enable));
DEF_SVC(SYS_SVCMD_ENABLE_LOW_POWER,             uint32_t,   les_sys_enable_low_power(uint32_t power_option, uint32_t cali_option));
DEF_SVC(SYS_SVCMD_ENABLE_FEATURE,               uint32_t,   les_sys_enable_feature(sys_feature_st *feature));
DEF_SVC(SYS_SVCMD_ADC_MEASURE,                  uint32_t,   les_sys_adc_measure(uint8_t *value , const void *param));
DEF_SVC(SYS_SVCMD_ENABLE_PATCH,                 uint32_t,   les_sys_enable_patch(uint8_t enable, uint16_t version, uint32_t valid_patch));
DEF_SVC(SYS_SVCMD_GET_PATCH_STATUS,             uint32_t,   les_sys_get_patch_status(uint8_t *status));
DEF_SVC(SYS_SVCMD_ECHO,                         uint32_t,   les_sys_echo(uint32_t echo));
DEF_SVC(SYS_SVCMD_GET_SLEEP_MODULE,             uint32_t,   les_sys_get_sleep_module(sys_sleep_module_st *module));
DEF_SVC(SYS_SVCMD_GET_LOG_MODULE,               uint32_t,   les_sys_get_log_module(sys_log_module_st *module));
DEF_SVC(SYS_SVCMD_LE_RECEIVER_TEST,             uint32_t,   les_sys_le_receiver_test(uint8_t rx_freq));
DEF_SVC(SYS_SVCMD_LE_TRANSMITTER_TEST,          uint32_t,   les_sys_le_transmitter_test(uint8_t tx_freq, uint16_t num_of_packet, uint8_t length_of_test_data, uint8_t packet_payload));
DEF_SVC(SYS_SVCMD_LE_TEST_END,                  uint32_t,   les_sys_le_test_end(uint16_t *num_of_packet));
DEF_SVC(SYS_SVCMD_INTERNAL_TEST,                uint32_t,   les_sys_internal_test(uint32_t option, uint32_t arg0, uint32_t arg1, uint32_t arg2));
DEF_SVC(SYS_SVCMD_BSP_ARG_TEST_0,               uint32_t,   les_sys_bsp_arg_test_0());
DEF_SVC(SYS_SVCMD_BSP_ARG_TEST_1,               uint32_t,   les_sys_bsp_arg_test_1(uint32_t arg1));
DEF_SVC(SYS_SVCMD_BSP_ARG_TEST_2,               uint32_t,   les_sys_bsp_arg_test_2(uint32_t arg1, uint32_t arg2));
DEF_SVC(SYS_SVCMD_BSP_ARG_TEST_3,               uint32_t,   les_sys_bsp_arg_test_3(uint32_t arg1, uint32_t arg2, uint32_t arg3));
DEF_SVC(SYS_SVCMD_BSP_ARG_TEST_4,               uint32_t,   les_sys_bsp_arg_test_4(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4));
DEF_SVC(SYS_SVCMD_CLI_GET_ILOG_HANDLE,          uint32_t,   les_sys_cli_get_ilog_handle(les_handle* handle));
DEF_SVC(SYS_SVCMD_CLI_REGISTER_CMD,             uint32_t,   les_sys_cli_register_cmd(les_handle handle, mini_cli_cmd_st *cli_list));
DEF_SVC(SYS_SVCMD_WDT_OPTION,                   uint32_t,   les_sys_wdt_option(uint32_t opt));
DEF_SVC(SYS_SVCMD_GET_LES_EVENT_QUEUE_DEPTH,    uint32_t,   les_sys_get_les_event_queue_depth(uint32_t *les_event_queue_depth));



#endif  /// end of _SYS_API_H_
