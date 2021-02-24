#include <string.h>
#include "sdkconfig.h"

#include "atcmd_ble_mesh.h"

#include "ssv_ble_mesh_main.h"
#include "ble_mesh_reg_gen_onoff_client_cmd.h"
#include "ble_mesh_register_provisioner_cmd.h"
#include "ble_mesh_register_node_cmd.h"
#include "ble_mesh_reg_cfg_client_cmd.h"
#if CONFIG_PERFORMANCE_CLIENT_MODEL
#include "ble_mesh_reg_test_perf_client_cmd.h"
#endif
#include "settings.h"
#include "access.h"
#include "ssv_ble_mesh_networking_api.h"
#include "ssv_ble_mesh_common_api.h"
int At_bmreg(stParam *param)
{
    if (ble_mesh_register_node_cb(param->argc, param->argv) < 0)
        return ERROR_MEMORY_FAILED;

    ble_mesh_register_mesh_node();
    ble_mesh_register_configuration_client_model();
#if CONFIG_BLE_MESH_GENERIC_ONOFF_CLI
    ble_mesh_register_gen_onoff_client();
#endif
#if CONFIG_BLE_MESH_PROVISIONER
    ble_mesh_register_mesh_provisioner();
#endif
#if CONFIG_PERFORMANCE_CLIENT_MODEL
    ble_mesh_register_mesh_test_performance_client();
#endif

    return ERROR_SUCCESS;
}

int At_bmoob(stParam *param)
{
    u32 val=0;
    if (param->argc > 1)
    {
        if (ble_mesh_load_oob(param->argc, param->argv) < 0)
            return ERROR_MEMORY_FAILED;
        else
            return ERROR_SUCCESS;
    }
    else
        return ERROR_INVALID_PARAMETER;
}

int At_bminit(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 1)
    {
        ret = ble_mesh_init(param->argc, param->argv);

        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;
}

int At_bmtxpower(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 1)
    {
        ret = ble_mesh_power_set(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;
}

int At_bmnbearer(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 1)
    {
        ret = ble_mesh_node_enable_bearer(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;
}

int At_bmtpcvm(stParam *param)
{
    u32 val=0;
    int ret =0;
    if (param->argc > 1)
    {
#if CONFIG_PERFORMANCE_CLIENT_MODEL
        ret = ble_mesh_test_performance_client_model(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;
#else
        printf("***Performance client is disable***\n");
        return ERROR_SUCCESS;
#endif
    }
    else
        return ERROR_INVALID_PARAMETER;
}

int At_bmgocm(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 1)
    {
        ret = ble_mesh_generic_onoff_client_model(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}

int At_bmvmcm(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 1)
    {
        ret = ble_mesh_test_performance_client_model_ssv_test(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}

#if CONFIG_BLE_MESH_PROVISIONER
int At_bmpdev(stParam *param)
{//"ble mesh provisioner: add/delete unprovisioned device"
    u32 val=0;
    s32 ret =0;
    if (param->argc > 1)
    {
        ret = ble_mesh_provision_address(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}

int At_bmpgetn(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 1)
    {
        ret = ble_mesh_provisioner_get_node(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}

int At_bmpaddn(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 1)
    {
        ret = ble_mesh_provisioner_add_node(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}

int At_bmpbind(stParam *param)
{//ble mesh provisioner: bind local model
    u32 val=0;
    s32 ret =0;
    if (param->argc > 1)
    {
        ret = ble_mesh_provision_bind_local_model(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}

int At_bmpkey(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 1)
    {
        ret = ble_mesh_provisioner_add_key(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}
#endif//CONFIG_BLE_MESH_PROVISIONER
int At_bmpbearer(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 1)
    {
        ret = ble_mesh_provisioner_bearer(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}

int At_bmccm(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 1)
    {
        ret = ble_mesh_configuration_client_model_operation(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}
int At_bmnreset(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 0)
    {
        ret = ble_mesh_node_reset(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}

int At_bmnsuspend(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 0)
    {
        ret = ble_mesh_node_suspend(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}

int At_bmnresume(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 0)
    {
        ret = ble_mesh_node_resume(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}


#if CONFIG_PERFORMANCE_CLIENT_MODEL
int At_bmsperf(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 1)
    {
        ret = ble_mesh_node_statistics_regist(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}
#endif
int At_bmnnwk(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 1)
    {
        ret = ble_mesh_node_enter_network_auto(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}

int At_bmgetpublishack(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 0)
    {
        ret = ble_mesh_get_publish_ack_count(param->argc, param->argv);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}

int At_bmstcoreload(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 0)
    {
#if  CONFIG_BLE_MESH_SETTINGS
        ret = settings_core_load();
#endif
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}
int At_bmstcoreci(stParam *param)
{
    u32 val=0;
    s32 ret =0;
    if (param->argc > 0)
    {
#if  CONFIG_BLE_MESH_SETTINGS
        ret = settings_core_commit();
#endif
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}

int At_bmloglvl(stParam *param)
{
    u32 val=0;
    s32 ret =0;

    u8 app_level = 0;
    u8 meshcore_level = 0;
    if (param->argc > 2)
    {
        meshcore_level = atoi(param->argv[1]);
        app_level = atoi(param->argv[2]);
        ssv_log_level_set_app(app_level);
        ssv_log_level_set_core(meshcore_level);
        printf("set mesh core %d, app %d\n", meshcore_level, app_level);
        if (ret != 0)
        {
            return ret;
        }
        else
            return ERROR_SUCCESS;

    }
    else
        return ERROR_INVALID_PARAMETER;

}
int At_bmprimaryaddr(stParam *param)
{
    u16 val=0;
    s32 ret =0;

    if (param->argc > 0)
    {
        val = bt_mesh_primary_addr();
        printf("primary addr %d\n", val);
        return ERROR_SUCCESS;
    }
    else
        return ERROR_INVALID_PARAMETER;

}

int At_bmsetscanwin(stParam *param)
{
    uint16_t win = 0, interval = 0;
    s32 ret =0;

    if (param->argc > 2)
    {
        win = strtoul(param->argv[1], NULL, 16);
        interval = strtoul(param->argv[2], NULL, 16);
        ssv_ble_mesh_set_scan_parameter(win, interval);
        return ERROR_SUCCESS;
    }
    else
        return ERROR_INVALID_PARAMETER;


}

int At_bmgpio(stParam *param)
{
    uint16_t test_start_end = 0, test_fail = 0, syncadv_start = 0, ack_start_end = 0;
    if (param->argc > 3)
    {
        test_start_end = atoi(param->argv[1]);
        test_fail = atoi(param->argv[2]);
        syncadv_start = atoi(param->argv[3]);
        ack_start_end = atoi(param->argv[4]);
        ssv_ble_mesh_config_dbg_gpio(test_start_end, test_fail, syncadv_start, ack_start_end);
        return ERROR_SUCCESS;
    }
    else
        return ERROR_INVALID_PARAMETER;
    return ERROR_SUCCESS;
}