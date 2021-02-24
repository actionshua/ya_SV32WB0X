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

#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>

//#include "nvs.h"
#include "sdkconfig.h"

#include "mesh_util.h"
#include "mesh_types.h"
#include "mesh_common.h"

#include "settings_ssv.h"
#include "settings.h"
#include "wifi_api.h"
#include "osi/osi.h"

#if CONFIG_BLE_MESH_SETTINGS
/* API used to initialize, load and commit BLE Mesh related settings */

void bt_mesh_settings_foreach(void)
{
    settings_core_init();
    settings_core_load();
    settings_core_commit();
}

/* API used to get BLE Mesh related nvs handle */

/* API used to store/erase BLE Mesh related settings */

static int settings_save(const char *key, const u8_t *val, size_t len)
{/* return 0 success, other fail*/
    int rlt = 0;
    if (key == NULL)
        return 0;

    rlt = osi_fswrite(key, (void*)val, len);
    if (rlt > 0)
        return 0;
    else
        return -1;
}

int bt_mesh_save_core_settings(const char *key, const u8_t *val, size_t len)
{
    return settings_save(key, val, len);
}

/* API used to load BLE Mesh related settings */

static int settings_load(const char *key,
                         u8_t *buf, size_t buf_len, bool *exist)
{
    int rlt = 0;
    if (key == NULL)
        return 0;


    rlt = osi_fsread(key, (void*)buf, buf_len);

    if (rlt > 0) {
        *exist = 1;
        rlt = 0;
    } else {
        *exist = 0;
        rlt = -1;
    }

    return rlt;
}

int bt_mesh_load_core_settings(const char *key, u8_t *buf, size_t buf_len, bool *exist)
{
    return settings_load(key, buf, buf_len, exist);
}

/* API used to get length of BLE Mesh related settings */

static size_t settings_get_length(const char *key)
{
    size_t len = 0;
    len = osi_fsget_length(key);
    return len;

}

/* API used to get BLE Mesh related items. Here items mean model key, NetKey/AppKey
 * Index, etc. which are going to be used as the prefix of the nvs keys of the BLE
 * Mesh settings.
 */

static struct net_buf_simple *settings_get_item(const char *key)
{
    struct net_buf_simple *buf = NULL;
    size_t length;
    bool exist = 0;
    int err;

    length = settings_get_length(key);
    if (!length) {
        BT_DBG("%s, Empty %s", __func__, key);
        return NULL;
    }

    buf = bt_mesh_alloc_buf(length);
    if (!buf) {
        BT_ERR("%s, Failed to allocate memory", __func__);
        /* TODO: in this case, erase all related settings? */
        return NULL;
    }

    err = settings_load(key, buf->data, length, &exist);
    if (err) {
        BT_ERR("%s, Failed to load %s", __func__, key);
        /* TODO: in this case, erase all related settings? */
        bt_mesh_free_buf(buf);
        return NULL;
    }

    if (exist == false) {
        bt_mesh_free_buf(buf);
        return NULL;
    }

    buf->len = length;
    return buf;
}

struct net_buf_simple *bt_mesh_get_core_settings_item(const char *key)
{
    return settings_get_item(key);
}

/* API used to check if the settings item exists */

static bool is_settings_item_exist(struct net_buf_simple *buf, const u16_t val)
{
    struct net_buf_simple_state state = {0};
    size_t length;
    int i;

    if (!buf) {
        return false;
    }

    net_buf_simple_save(buf, &state);

    length = buf->len;
    for (i = 0; i < length / SETTINGS_ITEM_SIZE; i++) {
        u16_t item = net_buf_simple_pull_le16(buf);
        if (item == val) {
            net_buf_simple_restore(buf, &state);
            return true;
        }
    }

    net_buf_simple_restore(buf, &state);
    return false;
}

/* API used to add the settings item */

static int settings_add_item(const char *key, const u16_t val)
{
    struct net_buf_simple *store = NULL;
    struct net_buf_simple *buf = NULL;
    size_t length = 0;
    int err;

    buf = settings_get_item(key);

    /* Check if val already exists */
    if (is_settings_item_exist(buf, val) == true) {
        BT_DBG("%s, 0x%04x already exists", __func__, val);
        bt_mesh_free_buf(buf);
        return 0;
    }

    length = (buf ? buf->len : 0) + sizeof(val);

    store = bt_mesh_alloc_buf(length);
    if (!store) {
        BT_ERR("%s, Failed to allocate memory", __func__);
        bt_mesh_free_buf(buf);
        return -ENOMEM;
    }

    if (buf) {
        net_buf_simple_add_mem(store, buf->data, buf->len);
    }
    net_buf_simple_add_mem(store, &val, sizeof(val));

    err = settings_save(key, store->data, store->len);

    bt_mesh_free_buf(store);
    bt_mesh_free_buf(buf);
    return err;
}

int bt_mesh_add_core_settings_item(const char *key, const u16_t val)
{
    return settings_add_item(key, val);
}

/* API used to remove the settings item */

static int settings_remove_item(const char *key, const u16_t val)
{
    struct net_buf_simple *store = NULL;
    struct net_buf_simple *buf = NULL;
    size_t length = 0;
    size_t buf_len;
    int i, err;

    buf = settings_get_item(key);

    /* Check if val does exist */
    if (is_settings_item_exist(buf, val) == false) {
        BT_DBG("%s, 0x%04x does not exist", __func__, val);
        bt_mesh_free_buf(buf);
        return 0;
    }

    length = buf->len - sizeof(val);
    if (!length) {
        settings_save(key, NULL, 0);
        bt_mesh_free_buf(buf);
        return 0;
    }

    store = bt_mesh_alloc_buf(length);
    if (!store) {
        BT_ERR("%s, Failed to allocate memory", __func__);
        bt_mesh_free_buf(buf);
        return -ENOMEM;
    }

    buf_len = buf->len;
    for (i = 0; i < buf_len / SETTINGS_ITEM_SIZE; i++) {
        u16_t item = net_buf_simple_pull_le16(buf);
        if (item != val) {
            net_buf_simple_add_le16(store, item);
        }
    }

    err = settings_save(key, store->data, store->len);

    bt_mesh_free_buf(store);
    bt_mesh_free_buf(buf);
    return err;
}

int bt_mesh_remove_core_settings_item(const char *key, const u16_t val)
{
    return settings_remove_item(key, val);
}

#endif /* CONFIG_BLE_MESH_SETTINGS */
