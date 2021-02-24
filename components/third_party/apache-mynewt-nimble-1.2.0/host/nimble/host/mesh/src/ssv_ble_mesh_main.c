
#include "transport/ram/ble_hci_ram.h"
#include "soc_assert.h"
#include "hci_common.h"

/*Mesh API include*/
#include "ssv_ble_mesh_defs.h"
#include "ssv_ble_mesh_common_api.h"
#include "ssv_ble_mesh_networking_api.h"
#include "ssv_ble_mesh_provisioning_api.h"
#include "ssv_ble_mesh_config_model_api.h"
#include "ssv_ble_mesh_generic_model_api.h"
#include "ssv_ble_mesh_local_data_operation_api.h"

/*nimble*/
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "host/util/util.h"
#include "host/ble_hs.h"
#include "store/config/ble_store_config.h"
#include "ssv_timer.h"
#include "ssv_log.h"
#include "argtable3.h"
#include "ble_mesh_console_lib.h"
#include "ssv_ble_mesh_main.h"
#include "ble_mesh_cfg_srv_model.h"
#include "ble_mesh_adapter.h"
#include "ble_mesh_reg_gen_onoff_client_cmd.h"
#include "ble_mesh_register_provisioner_cmd.h"
#include "ble_mesh_register_node_cmd.h"
#include "ble_mesh_reg_cfg_client_cmd.h"
#if CONFIG_PERFORMANCE_CLIENT_MODEL
#include "ble_mesh_reg_test_perf_client_cmd.h"
#endif

#include "tools/toolbox/ilog.h"
#include "ble_api.h"

#if MESH_BLE_AUTO_RUN_EN
#include "atcmd_ble_mesh.h"
#include "atcmd.h"
#include "atcmd_general.h"
#endif

#if CONFIG_BLE_MESH_GPIO_DBG
#include "hal_gpio.h"
#include "TurismoE.h"
#endif

extern void app_ble_init(void);



extern char *sw_version;
#if MESH_BLE_AUTO_RUN_EN
static void mesh_run_func(void *p)
{
    ssv_err_t err;
    uint8_t *static_val;
    ssv_ble_mesh_comp_t *local_component = NULL;
    ssv_ble_mesh_model_t *model;
    stParam cmdparmd;
    char bmoob[] = "bmoob";
    char bm_o[] = "-o";
    char bm_y[] = "-y";
    char val_0[] = "0";
    char bm_m[] = "-m";

    char bminit[] = "bminit";
    char bm_1001[] = "0x1001";

    char bmnbearer[] = "bmnbearer";
    char bm_b[] = "-b";
    char bm_3[] = "3";
    char bm_e[] = "-e";
    char bm_1[] = "1";

    char bmgocm[] = "bmgocm";
    char bm_z[] = "-z";
    char bm_reg[] = "reg";
    char bm_init[] = "init";

    char bmvmcm[] = "bmvmcm";

    //k_sleep(100);
    At_bmreg(NULL);

    cmdparmd.argv[0] = bmoob;
    cmdparmd.argv[1] = bm_o;
    cmdparmd.argv[2] = val_0;
    cmdparmd.argv[3] = bm_y;
    cmdparmd.argv[4] = val_0;

    cmdparmd.argc = 5;
    if(At_bmoob(&cmdparmd) != 0) {
        k_sleep(100);
        printf("bmoob fail\n");
        goto mesh_run_task_end;
    }

    cmdparmd.argv[0] = bminit;
    cmdparmd.argv[1] = bm_m;
    cmdparmd.argv[2] = bm_1001;

    cmdparmd.argc = 3;
    if(At_bminit(&cmdparmd) != 0) {
        k_sleep(100);
        printf("bminit fail\n");
        goto mesh_run_task_end;
    }

    cmdparmd.argv[0] = bmnbearer;
    cmdparmd.argv[1] = bm_b;
    cmdparmd.argv[2] = bm_3;
    cmdparmd.argv[3] = bm_e;
    cmdparmd.argv[4] = bm_1;

    cmdparmd.argc = 5;
    if(At_bmnbearer(&cmdparmd) != 0) {
        k_sleep(100);
        printf("bmnbearer fail\n");
        goto mesh_run_task_end;
    }

    cmdparmd.argv[0] = bmgocm;
    cmdparmd.argv[1] = bm_z;
    cmdparmd.argv[2] = bm_reg;

    cmdparmd.argc = 3;
    if(At_bmgocm(&cmdparmd) != 0) {
        k_sleep(100);
        printf("bmgocm fail\n");
        goto mesh_run_task_end;
    }

    cmdparmd.argv[0] = bmvmcm;
    cmdparmd.argv[1] = bm_z;
    cmdparmd.argv[2] = bm_init;

    cmdparmd.argc = 3;
    if(At_bmvmcm(&cmdparmd) != 0) {
        k_sleep(100);
        printf("bmvmcm fail\n");
        goto mesh_run_task_end;
    }

    At_GetVersion(NULL);

mesh_run_task_end:
    printf("\n%s %s\n", sw_version, __TIME__);
    return;
}
#endif//MESH_BLE_AUTO_RUN_EN end

void app_mesh_ble_init()
{
#if MESH_BLE_AUTO_RUN_EN
    int ret = 0;
#endif

#if CONFIG_BLE_MESH_GPIO_DBG
    hal_gpio_set_mode(GPIO_25, 0);
    hal_gpio_set_dir(GPIO_25, 1);

    hal_gpio_set_mode(SIO_28, 0);
    hal_gpio_set_dir(SIO_28, 1);

    hal_gpio_set_mode(GPIO_24, 0);
    hal_gpio_set_dir(GPIO_24, 1);

    hal_gpio_set_mode(GPIO_02, 0);
    hal_gpio_set_dir(GPIO_02, 1);

    hal_gpio_set_mode(SIO_13, 0);
    hal_gpio_set_dir(SIO_13, 1);
#endif

    app_ble_init();
    ssv_timer_init();

#if MESH_BLE_AUTO_RUN_EN
    mesh_run_func(NULL);
#endif

}