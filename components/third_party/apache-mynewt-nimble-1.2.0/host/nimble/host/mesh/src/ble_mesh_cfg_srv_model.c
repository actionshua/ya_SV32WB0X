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

#include "ble_mesh_cfg_srv_model.h"
#include "sdkconfig.h"
#include "test_data.h"

uint8_t dev_uuid[16] = DEV_UUID;//{0xdd, 0xdd};

#if CONFIG_BLE_MESH_PROVISIONER
ssv_ble_mesh_prov_t prov = {
    .prov_uuid           = dev_uuid,
    .prov_unicast_addr   = 0x0001,
    .prov_start_address  = 0x0005,
    .prov_attention      = 0x00,
    .prov_algorithm      = 0x00,
    .prov_pub_key_oob    = 0x00,
    .prov_static_oob_val = NULL,
    .prov_static_oob_len = 0x00,
    .flags               = 0x00,
    .iv_index            = 0x00,
};

#else
ssv_ble_mesh_prov_t prov = {
    .uuid = dev_uuid,
};
#endif //CONFIG_BLE_MESH_PROVISIONER

#if CONFIG_BLE_MESH_PROVISIONER
SSV_BLE_MESH_MODEL_PUB_DEFINE(model_pub_config, 2 + 1, ROLE_PROVISIONER);
#else
SSV_BLE_MESH_MODEL_PUB_DEFINE(model_pub_config, 2 + 1, ROLE_NODE);
#endif


// configure server module
struct ssv_ble_mesh_cfg_srv ssv_cfg_srv = {
    .relay = SSV_BLE_MESH_RELAY_ENABLED,
    .beacon = SSV_BLE_MESH_BEACON_ENABLED,
#if defined(CONFIG_BLE_MESH_FRIEND)
    .friend_state = SSV_BLE_MESH_FRIEND_ENABLED,
#else
    .friend_state = SSV_BLE_MESH_FRIEND_NOT_SUPPORTED,
#endif
#if defined(CONFIG_BLE_MESH_GATT_PROXY_SERVER)
    .gatt_proxy = SSV_BLE_MESH_GATT_PROXY_ENABLED,
#else
    .gatt_proxy = SSV_BLE_MESH_GATT_PROXY_NOT_SUPPORTED,
#endif
    .default_ttl = 7,

    /* 4 transmissions with 20ms interval */
    .net_transmit = SSV_BLE_MESH_TRANSMIT(2, 20),
    .relay_retransmit = SSV_BLE_MESH_TRANSMIT(2, 20),
};

ssv_ble_mesh_model_t config_models[] = {
    SSV_BLE_MESH_MODEL_CFG_SRV(&ssv_cfg_srv),
    SSV_BLE_MESH_MODEL_CFG_CLI(&cfg_cli),
};

#if CONFIG_PERFORMANCE_CLIENT_MODEL
ssv_ble_mesh_model_pub_t vendor_model_pub_config;

//CONFIG VENDOR MODEL TEST PERFORMANCE
#define SSV_BLE_MESH_VND_MODEL_ID_TEST_PERF_SRV 0x2000
#define SSV_BLE_MESH_VND_MODEL_ID_TEST_PERF_CLI 0x2001

ssv_ble_mesh_client_op_pair_t test_perf_cli_op_pair[] = {
    {SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_GET, SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_STATUS},
    {SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_SET, SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_STATUS},
    {SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_SET_UNACK, SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_STATUS},
    //++ssv -->
    {SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_ITEM_SET, SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_ITEM_SET_STATUS},
    {SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_ITEM_SET_STATUS, SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_ITEM_SET_STATUS},
    {SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST, SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_STATUS},
    {SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_UNACK, SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_STATUS},
    {SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_RESULT, SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_RESULT_STATUS},
    //++ssv <--
};

ssv_ble_mesh_client_t test_perf_cli = {
    .op_pair_size = ARRAY_SIZE(test_perf_cli_op_pair),
    .op_pair = test_perf_cli_op_pair,
};

/*server receive opcode*/
ssv_ble_mesh_model_op_t test_perf_srv_op[] = {
    SSV_BLE_MESH_MODEL_OP(SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_GET,       1),
    SSV_BLE_MESH_MODEL_OP(SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_SET,       1),
    SSV_BLE_MESH_MODEL_OP(SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_SET_UNACK, 1),
    //++ssv -->
    SSV_BLE_MESH_MODEL_OP(SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_ITEM_SET, 1),
    SSV_BLE_MESH_MODEL_OP(SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST, 1),
    SSV_BLE_MESH_MODEL_OP(SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_UNACK, 1),
    SSV_BLE_MESH_MODEL_OP(SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_STATUS, 1),
    SSV_BLE_MESH_MODEL_OP(SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_RESULT, 1),
    //++ssv <--
    SSV_BLE_MESH_MODEL_OP_END,
};

/*client receive opcode*/
ssv_ble_mesh_model_op_t test_perf_cli_op[] = {
    SSV_BLE_MESH_MODEL_OP(SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_STATUS, 1),
    SSV_BLE_MESH_MODEL_OP(SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_STATUS, 64),//++ssv
    SSV_BLE_MESH_MODEL_OP(SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_ITEM_SET_STATUS, 1),//++ssv
    SSV_BLE_MESH_MODEL_OP(SSV_BLE_MESH_VND_MODEL_OP_TEST_PERF_TEST_RESULT_STATUS, TEST_RESULT_RETUEN_END),
    SSV_BLE_MESH_MODEL_OP_END,
};

ssv_ble_mesh_model_t test_perf_cli_models[] = {
    SSV_BLE_MESH_VENDOR_MODEL(CID_SSV, SSV_BLE_MESH_VND_MODEL_ID_TEST_PERF_CLI,
    test_perf_cli_op, &vendor_model_pub_config, &test_perf_cli),
};

ssv_ble_mesh_elem_t test_perf_cli_elements[] = {
    SSV_BLE_MESH_ELEMENT(0, config_models, test_perf_cli_models),
};

ssv_ble_mesh_comp_t test_perf_cli_comp = {
    .cid = CID_SSV,
    .elements = test_perf_cli_elements,
    .element_count = ARRAY_SIZE(test_perf_cli_elements),
};

ssv_ble_mesh_model_t test_perf_srv_models[] = {
    SSV_BLE_MESH_VENDOR_MODEL(CID_SSV, SSV_BLE_MESH_VND_MODEL_ID_TEST_PERF_SRV,
    test_perf_srv_op, NULL, NULL),
};

ssv_ble_mesh_elem_t test_perf_srv_elements[] = {
    SSV_BLE_MESH_ELEMENT(0, config_models, test_perf_srv_models),
};

ssv_ble_mesh_comp_t test_perf_srv_comp = {
    .cid = CID_SSV,
    .elements = test_perf_srv_elements,
    .element_count = ARRAY_SIZE(test_perf_srv_elements),
};
#endif//CONFIG_PERFORMANCE_CLIENT_MODEL




ssv_ble_mesh_model_t config_server_models[] = {
    SSV_BLE_MESH_MODEL_CFG_SRV(&ssv_cfg_srv),
};

ssv_ble_mesh_elem_t config_server_elements[] = {
    SSV_BLE_MESH_ELEMENT(0, config_server_models, SSV_BLE_MESH_MODEL_NONE),
};

ssv_ble_mesh_comp_t config_server_comp = {
    .cid = CID_SSV,
    .elements = config_server_elements,
    .element_count = ARRAY_SIZE(config_server_elements),
};

// config client model
ssv_ble_mesh_model_t config_client_models[] = {
    SSV_BLE_MESH_MODEL_CFG_SRV(&ssv_cfg_srv),
    SSV_BLE_MESH_MODEL_CFG_CLI(&cfg_cli),
};

ssv_ble_mesh_elem_t config_client_elements[] = {
    SSV_BLE_MESH_ELEMENT(0, config_client_models, SSV_BLE_MESH_MODEL_NONE),
};

ssv_ble_mesh_comp_t config_client_comp = {
    .cid = CID_SSV,
    .elements = config_client_elements,
    .element_count = ARRAY_SIZE(config_client_elements),
};

// configure special module
ssv_ble_mesh_model_op_t gen_onoff_srv_model_op_config[] = {
    SSV_BLE_MESH_MODEL_OP(SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_GET,       0),
    SSV_BLE_MESH_MODEL_OP(SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_SET,       2),
    SSV_BLE_MESH_MODEL_OP(SSV_BLE_MESH_MODEL_OP_GEN_ONOFF_SET_UNACK, 2),
    SSV_BLE_MESH_MODEL_OP_END,
};

ssv_ble_mesh_model_t gen_onoff_srv_models[] = {
    SSV_BLE_MESH_MODEL_CFG_SRV(&ssv_cfg_srv),
    SSV_BLE_MESH_SIG_MODEL(SSV_BLE_MESH_MODEL_ID_GEN_ONOFF_SRV, gen_onoff_srv_model_op_config, &model_pub_config, NULL),
};

ssv_ble_mesh_elem_t gen_onoff_srv_elements[] = {
    SSV_BLE_MESH_ELEMENT(0, gen_onoff_srv_models, SSV_BLE_MESH_MODEL_NONE),
};

ssv_ble_mesh_comp_t gen_onoff_srv_comp = {
    .cid = CID_SSV,
    .elements = gen_onoff_srv_elements,
    .element_count = ARRAY_SIZE(gen_onoff_srv_elements),
};

// config generic onoff client
#if (CONFIG_BLE_MESH_GENERIC_ONOFF_CLI)

ssv_ble_mesh_client_t gen_onoff_cli;

SSV_BLE_MESH_MODEL_PUB_DEFINE(onoff_pub, 2 + 3, ROLE_NODE);
static ssv_ble_mesh_gen_onoff_srv_t onoff_server = {
    .rsp_ctrl.get_auto_rsp = SSV_BLE_MESH_SERVER_RSP_BY_APP,
    .rsp_ctrl.set_auto_rsp = SSV_BLE_MESH_SERVER_RSP_BY_APP,
};
#if CONFIG_BLE_MESH_PTS
SSV_BLE_MESH_MODEL_PUB_DEFINE(ssv_health_pub, 2 + 3, ROLE_NODE);
static struct bt_mesh_health_srv health_server = {
};
#endif

ssv_ble_mesh_model_t gen_onoff_cli_models[] = {
    SSV_BLE_MESH_MODEL_CFG_SRV(&ssv_cfg_srv),
    SSV_BLE_MESH_MODEL_CFG_CLI(&cfg_cli),
    SSV_BLE_MESH_MODEL_GEN_ONOFF_SRV(&onoff_pub, &onoff_server),//ssv++
    SSV_BLE_MESH_MODEL_GEN_ONOFF_CLI(&model_pub_config, &gen_onoff_cli),
#if CONFIG_BLE_MESH_PTS
    SSV_BLE_MESH_MODEL_HEALTH_SRV(&health_server, &ssv_health_pub),
#endif
};

#if CONFIG_PERFORMANCE_CLIENT_MODEL//ssv++ -->
ssv_ble_mesh_model_t gen_perf_srvcli_models[] = {
    SSV_BLE_MESH_VENDOR_MODEL(CID_SSV, SSV_BLE_MESH_VND_MODEL_ID_TEST_PERF_SRV,
        test_perf_srv_op, NULL, NULL),
    SSV_BLE_MESH_VENDOR_MODEL(CID_SSV, SSV_BLE_MESH_VND_MODEL_ID_TEST_PERF_CLI,
        test_perf_cli_op, &vendor_model_pub_config, &test_perf_cli),
};
#endif//ssv++ < --


#endif //CONFIG_BLE_MESH_GENERIC_ONOFF_CLI


ssv_ble_mesh_elem_t gen_onoff_cli_elements[] = {
#if CONFIG_PERFORMANCE_CLIENT_MODEL
    SSV_BLE_MESH_ELEMENT(0, gen_onoff_cli_models, gen_perf_srvcli_models),
#else
    SSV_BLE_MESH_ELEMENT(0, gen_onoff_cli_models, SSV_BLE_MESH_MODEL_NONE),
#endif
};

ssv_ble_mesh_comp_t gen_onoff_cli_comp = {
    .cid = CID_SSV,
    .elements = gen_onoff_cli_elements,
    .element_count = ARRAY_SIZE(gen_onoff_cli_elements),
};

