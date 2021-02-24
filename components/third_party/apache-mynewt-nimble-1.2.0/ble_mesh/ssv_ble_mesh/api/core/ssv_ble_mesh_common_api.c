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

#include <stdint.h>

#include "FreeRTOS.h"
#include "semphr.h"

#include "btc/btc_task.h"
#include "btc/btc_manage.h"
#include "osi/alarm.h"

#include "ssv_err.h"

#include "btc_ble_mesh_prov.h"
#include "ssv_ble_mesh_defs.h"

ssv_err_t ssv_ble_mesh_init(ssv_ble_mesh_prov_t *prov, ssv_ble_mesh_comp_t *comp)
{
    btc_ble_mesh_prov_args_t arg;
    SemaphoreHandle_t semaphore = NULL;
    btc_msg_t msg = {0};
    ssv_err_t ret;

    if (prov == NULL || comp == NULL) {
        return SSV_ERR_INVALID_ARG;
    }

    SSV_BLE_HOST_STATUS_CHECK(SSV_BLE_HOST_STATUS_ENABLED);
    memset(&arg, 0, sizeof(arg));
    ret = bt_mesh_host_init();
    if (ret != SSV_BM_OK) {
        return ret;
    }

    // Create a semaphore
    if ((semaphore = xSemaphoreCreateCounting(1, 0)) == NULL) {
        LOG_ERROR("%s, Failed to allocate memory for the semaphore", __func__);
        return SSV_ERR_NO_MEM;
    }

    arg.mesh_init.prov = prov;
    arg.mesh_init.comp = comp;
    /* Transport semaphore pointer to BTC layer, and will give the semaphore in the BTC task */
    arg.mesh_init.semaphore = semaphore;

    msg.sig = BTC_SIG_API_CALL;
    msg.pid = BTC_PID_PROV;
    msg.act = BTC_BLE_MESH_ACT_MESH_INIT;

    if (btc_transfer_context(&msg, &arg, sizeof(btc_ble_mesh_prov_args_t), NULL) != BT_STATUS_SUCCESS) {
        vSemaphoreDelete(semaphore);
        LOG_ERROR("%s, BLE Mesh initialise failed", __func__);
        return SSV_FAIL;
    }

    /* Take the Semaphore, wait BLE Mesh initialization to finish. */
    xSemaphoreTake(semaphore, portMAX_DELAY);
    /* Don't forget to delete the semaphore at the end. */
    vSemaphoreDelete(semaphore);

    return SSV_BM_OK;
}
#if CONFIG_BLE_MESH_GPIO_DBG
extern u32 g_test_msg_sync_adv_start_end;
extern u32 g_test_msg_ack_start_end;
extern u32 g_test_start_end_gpio;
extern u32 g_test_fail_gpio;
#endif
ssv_err_t ssv_ble_mesh_config_dbg_gpio(u32 test_start_end, u32 test_fail, u32 syncadv_start, u32 ack_start_end)
{
    #if CONFIG_BLE_MESH_GPIO_DBG
        g_test_start_end_gpio = test_start_end;
        g_test_fail_gpio = test_fail;
        g_test_msg_sync_adv_start_end = syncadv_start;
        g_test_msg_ack_start_end = ack_start_end;
        printf("set start_end_gpio %d, fail_gpio %d, sync_adv_start_end %d, ack_start_end %d\n",
            g_test_start_end_gpio, g_test_fail_gpio, g_test_msg_sync_adv_start_end, g_test_msg_ack_start_end);
    #else
        printf("CONFIG_BLE_MESH_GPIO_DBG is not enable\n");
    #endif

	return SSV_BM_OK;
}