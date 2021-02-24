// Copyright 2017-2019 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//#include "ssv_bt_defs.h"

#include "provisioner_prov.h"
#include "ssv_ble_mesh_defs.h"
#include "ssv_ble_mesh_networking_api.h"
#include "ssv_ble_mesh_provisioning_api.h"
#include "ssv_ble_mesh_config_model_api.h"
#include "ble_mesh_register_provisioner_cmd.h"
#include "ble_mesh_adapter.h"
//#include "ble_mesh_console_decl.h"

#if CONFIG_BLE_MESH_PROVISIONER

typedef struct {
    struct arg_int *bearer;
    struct arg_int *enable;
    struct arg_end *end;
} ble_mesh_provisioner_bearer_t;
ble_mesh_provisioner_bearer_t provisioner_bearer;

typedef struct {
    struct arg_str *add_del;
    struct arg_str *device_addr;
    struct arg_str *device_uuid;
    struct arg_int *addr_type;
    struct arg_int *bearer;
    struct arg_int *oob_info;
    struct arg_int *flag;
    struct arg_end *end;
} ble_mesh_provisioner_addr_t;
ble_mesh_provisioner_addr_t provisioner_addr;

typedef struct {
    struct arg_int *unicast_addr;
    struct arg_end *end;
} ble_mesh_provisioner_get_node_t;
ble_mesh_provisioner_get_node_t provisioner_get_node;

typedef struct {
    struct arg_int *oob_info;
    struct arg_int *unicast_addr;
    struct arg_int *element_num;
    struct arg_int *net_idx;
    struct arg_str *dev_key;
    struct arg_str *uuid;
    struct arg_end *end;
} ble_mesh_provisioner_add_node_t;
ble_mesh_provisioner_add_node_t provisioner_add_node;

typedef struct {
    struct arg_int *appkey_index;
    struct arg_int *element_address;
    struct arg_int *network_index;
    struct arg_int *mod_id;
    struct arg_int *cid;
    struct arg_end *end;
} ble_mesh_provisioner_bind_model_t;
ble_mesh_provisioner_bind_model_t provisioner_local_bind;

typedef struct {
    struct arg_str *action_type;
    struct arg_int *net_idx;
    struct arg_int *app_idx;
    struct arg_str *key;
    struct arg_end *end;
} ble_mesh_provisioner_add_key_t;
ble_mesh_provisioner_add_key_t provisioner_add_key;

void ble_mesh_regist_provisioner_cmd(void);

void ble_mesh_prov_adv_cb(const ssv_ble_mesh_bd_addr_t addr, const ssv_ble_mesh_addr_type_t addr_type, const uint8_t adv_type,
                          const uint8_t *dev_uuid, uint16_t oob_info, ssv_ble_mesh_prov_bearer_t bearer);

void ble_mesh_register_mesh_provisioner(void)
{
    ble_mesh_regist_provisioner_cmd();
}

void ble_mesh_prov_adv_cb(const ssv_ble_mesh_bd_addr_t addr, const ssv_ble_mesh_addr_type_t addr_type, const uint8_t adv_type,
                          const uint8_t *dev_uuid, uint16_t oob_info, ssv_ble_mesh_prov_bearer_t bearer)
{
    SSV_LOGD(TAG, "enter %s\n", __func__);
    SSV_LOGI(TAG, "scan device address:");
    ssv_log_buffer_hex(TAG, addr, sizeof(ssv_ble_mesh_bd_addr_t));
    SSV_LOGI(TAG, "scan device uuid:");
    ssv_log_buffer_hex(TAG, dev_uuid, 16);
    SSV_LOGD(TAG, "exit %s\n", __func__);
}

int ble_mesh_provisioner_register(int argc, char** argv)
{
    SSV_LOGD(TAG, "enter %s \n", __func__);
    // ssv_ble_mesh_register_unprov_adv_pkt_callback(ble_mesh_prov_adv_cb);
    SSV_LOGI(TAG, "Provisioner:Reg,OK");
    SSV_LOGD(TAG, "exit %s \n", __func__);
    return 0;
}

int ble_mesh_provision_address(int argc, char **argv)
{
    ssv_err_t err = SSV_BM_OK;
    ssv_ble_mesh_unprov_dev_add_t device_addr;
    uint8_t  preset_addr_uuid[16] = DEV_UUID;
    ssv_ble_mesh_device_delete_t del_dev = {
        .flag = BIT(0),
    };

    SSV_LOGD(TAG, "enter %s \n", __func__);
    memset(&device_addr, 0, sizeof(device_addr));
    int nerrors = arg_parse(argc, argv, (void **) &provisioner_addr);
    if (nerrors != 0) {
        arg_print_errors(stderr, provisioner_addr.end, argv[0]);
        return 1;
    }
    
    if (provisioner_addr.device_addr->count != 0) {
        if (provisioner_addr.device_uuid->count != 0) {
            del_dev.flag = BIT(0) | BIT(1);
            str_2_mac((uint8_t *)provisioner_addr.device_addr->sval[0], device_addr.uuid);
            str_2_mac((uint8_t *)provisioner_addr.device_addr->sval[0], del_dev.uuid); 
        } else {
            del_dev.flag = BIT(0);
            memcpy(device_addr.uuid, preset_addr_uuid, 16);
            memcpy(del_dev.uuid, preset_addr_uuid, 16);
        }
        str_2_mac((uint8_t *)provisioner_addr.device_addr->sval[0], device_addr.addr);
        str_2_mac((uint8_t *)provisioner_addr.device_addr->sval[0], del_dev.addr);
        arg_int_to_value(provisioner_addr.addr_type, device_addr.addr_type, "address type");
        arg_int_to_value(provisioner_addr.addr_type, del_dev.addr_type, "address type");
    } else if (provisioner_addr.device_uuid->count != 0) {
        del_dev.flag = BIT(1);
        memcpy(device_addr.addr, preset_addr_uuid, 6);
        memcpy(del_dev.addr, preset_addr_uuid, 6);
        str_2_mac((uint8_t *)provisioner_addr.device_addr->sval[0], device_addr.uuid);
        str_2_mac((uint8_t *)provisioner_addr.device_addr->sval[0], del_dev.uuid); 
    }

    if (strcmp(provisioner_addr.add_del->sval[0], "add") == 0) {
        arg_int_to_value(provisioner_addr.bearer, device_addr.bearer, "bearer");
        arg_int_to_value(provisioner_addr.oob_info, device_addr.oob_info, "oob information");
        err = ssv_ble_mesh_provisioner_add_unprov_dev(&device_addr, provisioner_addr.flag->ival[0]);
    } else if (strcmp(provisioner_addr.add_del->sval[0], "del") == 0) {
        err = ssv_ble_mesh_provisioner_delete_dev(&del_dev);
    }

    SSV_LOGD(TAG, "exit %s \n", __func__);
    return err;
}

int ble_mesh_provisioner_bearer(int argc, char **argv)
{
    ssv_err_t err;

    SSV_LOGD(TAG, "enter %s \n", __func__);

    int nerrors = arg_parse(argc, argv, (void **) &provisioner_bearer);
    if (nerrors != 0) {
        arg_print_errors(stderr, provisioner_bearer.end, argv[0]);
        return 1;
    }

    if (provisioner_bearer.enable->count != 0) {
        if (provisioner_bearer.enable->ival[0]) {
            err = ssv_ble_mesh_provisioner_prov_enable(provisioner_bearer.bearer->ival[0]);
        } else {
            err = ssv_ble_mesh_provisioner_prov_disable(provisioner_bearer.bearer->ival[0]);
        }
    } else {
        return 1;
    }

    SSV_LOGD(TAG, "exit %s \n", __func__);
    return err;
}

int ble_mesh_provisioner_get_node(int argc, char **argv)
{
    uint16_t unicast_addr = 0;
    uint16_t i = 0;
    struct bt_mesh_node_t *node_info;

    SSV_LOGD(TAG, "enter %s\n", __func__);
    int nerrors = arg_parse(argc, argv, (void **) &provisioner_get_node);
    if (nerrors != 0) {
        arg_print_errors(stderr, provisioner_get_node.end, argv[0]);
        return 1;
    }

    arg_int_to_value(provisioner_get_node.unicast_addr, unicast_addr, "unicast address");
    node_info = bt_mesh_provisioner_get_node_info(unicast_addr);

    if (node_info == NULL) {
        return SSV_FAIL;
    } else {
        printf("OobInfo:0x%x,Address:0x%x,EleNum:0x%x,NetIdx:0x%x,DevKey:",
               node_info->oob_info, node_info->unicast_addr, node_info->element_num, node_info->net_idx);
        for (i = 0; i < 16; i++) {
            printf("%02x", node_info->dev_key[i]);
        }
        printf(",DevUuid:");
        for (i = 0; i < 16; i++) {
            printf("%02x", node_info->dev_uuid[i]);
        }
        printf("\n");
    }

    SSV_LOGD(TAG, "exit %s\n", __func__);
    return SSV_BM_OK;
}

int ble_mesh_provisioner_add_node(int argc, char **argv)
{
    struct bt_mesh_node_t node_info;
    ssv_err_t result;
    SSV_LOGD(TAG, " enter %s\n", __func__);

    int nerrors = arg_parse(argc, argv, (void **) &provisioner_add_node);
    if (nerrors != 0) {
        arg_print_errors(stderr, provisioner_add_node.end, argv[0]);
        return 1;
    }

    arg_int_to_value(provisioner_add_node.oob_info, node_info.oob_info, "oob information");
    arg_int_to_value(provisioner_add_node.unicast_addr, node_info.unicast_addr, "unicast address");
    arg_int_to_value(provisioner_add_node.element_num, node_info.element_num, "element number");
    arg_int_to_value(provisioner_add_node.net_idx, node_info.net_idx, "network index");
    if (provisioner_add_node.dev_key->count != 0) {
        get_value_string((char *)provisioner_add_node.dev_key->sval[0], (char *)node_info.dev_key);
    }
    if (provisioner_add_node.uuid->count != 0) {
        get_value_string((char *)provisioner_add_node.uuid->sval[0], (char *)node_info.dev_uuid); 
        get_value_string((char *)provisioner_add_node.uuid->sval[0], (char *)node_info.dev_uuid);
    }

    result = bt_mesh_provisioner_store_node_info(&node_info);
    if (result == SSV_BM_OK) {
        SSV_LOGI(TAG, "Provisioner:AddNodeInfo,OK\n");
    }

    SSV_LOGD(TAG, "exit %s\n", __func__);
    return result;
}

int ble_mesh_provisioner_add_key(int argc, char **argv)
{
    ssv_err_t err = SSV_BM_OK;
    uint8_t key[16] = {0};
    ssv_ble_mesh_prov_data_info_t info = {
        .net_idx = 1,
        .flag = NET_IDX_FLAG,
    };
    SSV_LOGD(TAG, " enter %s\n", __func__);

    int nerrors = arg_parse(argc, argv, (void **) &provisioner_add_key);
    if (nerrors != 0) {
        arg_print_errors(stderr, provisioner_add_key.end, argv[0]);
        return 1;
    }

    err = get_value_string((char *)provisioner_add_key.key->sval[0], (char *) key);
    if (strcmp(provisioner_add_key.action_type->sval[0], "appkey") == 0) {
        err = ssv_ble_mesh_provisioner_add_local_app_key(key, provisioner_add_key.net_idx->ival[0], provisioner_add_key.app_idx->ival[0]);
    } else if (strcmp(provisioner_add_key.action_type->sval[0], "netkey") == 0) {
        // choose network key
        info.net_idx = provisioner_add_key.net_idx->ival[0];
        err = ssv_ble_mesh_provisioner_add_local_net_key(key, provisioner_add_key.net_idx->ival[0]);
        err = err | ssv_ble_mesh_provisioner_set_prov_data_info(&info);
    }

    if (err != SSV_BM_OK) {
        SSV_LOGI(TAG, "Provisioner:KeyAction,Fail");
    } else {
        SSV_LOGI(TAG, "Provisioner:KeyAction,OK");
    }

    SSV_LOGD(TAG, "exit %s\n", __func__);
    return err;
}

int ble_mesh_provision_bind_local_model(int argc, char **argv)
{
    ssv_err_t err;
    uint16_t element_addr = 0;
    uint16_t app_idx = 0;
    uint16_t model_id = 0;
    uint16_t company_id = 0xFFFF;

    SSV_LOGD(TAG, " enter %s\n", __func__);

    int nerrors = arg_parse(argc, argv, (void **) &provisioner_local_bind);
    if (nerrors != 0) {
        arg_print_errors(stderr, provisioner_local_bind.end, argv[0]);
        return 1;
    }

    arg_int_to_value(provisioner_local_bind.element_address, element_addr, "element address");
    arg_int_to_value(provisioner_local_bind.appkey_index, app_idx, "appkey index");
    arg_int_to_value(provisioner_local_bind.mod_id, model_id, "model id");
    arg_int_to_value(provisioner_local_bind.cid, company_id, "company id");
    err = ssv_ble_mesh_provisioner_bind_app_key_to_local_model(element_addr, app_idx, model_id, company_id);

    if (err != SSV_BM_OK) {
        SSV_LOGE(TAG, "Provisioner:BindModel,Fail,%x\n", err);
    } else {
        SSV_LOGI(TAG, "Provisioner:BindModel,OK\n");
    }
    SSV_LOGD(TAG, "exit %s\n", __func__);
    return err;
}

void ble_mesh_regist_provisioner_cmd(void)
{
    provisioner_addr.add_del = arg_str1("z", NULL, "<add/delete>", "action type");
    provisioner_addr.device_addr = arg_str0("d", NULL, "<address>", "device address");
    provisioner_addr.device_uuid = arg_str0("u", NULL, "<uuid>", "device uuid");
    provisioner_addr.addr_type = arg_int0("a", NULL, "<type>", "address type");
    provisioner_addr.flag = arg_int0("f", NULL, "<flag>", "address flag");
    provisioner_addr.flag->ival[0] = ADD_DEV_RM_AFTER_PROV_FLAG | ADD_DEV_FLUSHABLE_DEV_FLAG;
    provisioner_addr.bearer = arg_int0("b", NULL, "<bearer>", "used bearer");
    provisioner_addr.oob_info = arg_int0("o", NULL, "<oob info>", "oob information");
    provisioner_addr.end = arg_end(1);

    provisioner_bearer.bearer = arg_int0("b", NULL, "<bearer>", "bearer supported provisioner");
    provisioner_bearer.enable = arg_int0("e", NULL, "<enable/disable>", "enable or disable bearer");
    provisioner_bearer.end = arg_end(1);

    provisioner_get_node.unicast_addr = arg_int1("u", NULL, "<address>", "get node by unicast address");
    provisioner_get_node.end = arg_end(1);

    provisioner_add_node.oob_info = arg_int0("o", NULL, "<oob info>", "oob information");
    provisioner_add_node.unicast_addr = arg_int0("a", NULL, "<unicast address>", "unicast address");
    provisioner_add_node.element_num = arg_int0("e", NULL, "<element num>", "element num");
    provisioner_add_node.net_idx = arg_int0("n", NULL, "<net index>", "net index");
    provisioner_add_node.dev_key = arg_str0("d", NULL, "<device key>", "device key");
    provisioner_add_node.uuid = arg_str0("u", NULL, "<device uuid>", "device uuid");
    provisioner_add_node.end = arg_end(1);

    provisioner_local_bind.appkey_index = arg_int1("a", NULL, "<appkey index>", "appkey index");
    provisioner_local_bind.element_address = arg_int1("e", NULL, "<element address>", "element address");
    provisioner_local_bind.network_index = arg_int1("n", NULL, "<network index>", "network index");
    provisioner_local_bind.mod_id = arg_int1("m", NULL, "<model id>", "model id");
    provisioner_local_bind.cid = arg_int0("c", NULL, "<model id>", "company id");
    provisioner_local_bind.end = arg_end(1);

    provisioner_add_key.action_type = arg_str1("z", NULL, "<action type>", "add appkey or network key");
    provisioner_add_key.net_idx = arg_int1("n", NULL, "<net key index>", "network key index");
    provisioner_add_key.key = arg_str1("k", NULL, "<key>", "appkey or network");
    provisioner_add_key.app_idx = arg_int0("a", NULL, "<app key index>", "appkey index");
    provisioner_add_key.end = arg_end(1);

}
#endif

