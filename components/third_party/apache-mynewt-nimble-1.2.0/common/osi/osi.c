// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
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


#include "osi/osi.h"
#include "osi/mutex.h"
#include "sdkconfig.h"
#if CONFIG_BLE_MESH_SETTINGS
#include "fsal.h"
#endif
#include "mesh_trace.h"
#include "ssv_timer.h"

int osi_init(void)
{
    int ret = 0;

    if (osi_mutex_global_init() != 0) {
        ret = -1;
    }

    return ret;
}

void osi_deinit(void)
{
    osi_mutex_global_deinit();
}

#if CONFIG_BLE_MESH_SETTINGS
#define PATH_MAX 512

#define PATH_A "A_"
#define PATH_B "B_"
extern SSV_FS fs_handle;

typedef enum {
    OSI_FILE_OK,
    OSI_FILE_OPEN_FAIL,
    OSI_FILE_OUTBUF_FAIL,
    OSI_FILE_PARAM_FAIL,
    OSI_FILE_PATH_FAIL
} bt_mesh_osi_file_error_t;

typedef enum {
    OSI_FILE_WRITE,
    OSI_FILE_READ,
} bt_mesh_osi_file_rw_t;

typedef enum {
    OSI_FILE_ZONE_A,
    OSI_FILE_ZONE_B,
} bt_mesh_osi_file_zone_t;

char g_tmp_path[PATH_MAX] = {0};
extern SSV_FS fs_handle;
uint8_t osi_fs_getpath(const char* path, uint8_t zone, char* out, uint16_t outlen)
{

    char *zone_str = NULL;

    memset(g_tmp_path, 0, PATH_MAX);

    if (OSI_FILE_ZONE_A == zone)
        zone_str = PATH_A;
    else if (OSI_FILE_ZONE_B == zone)
        zone_str = PATH_B;
    else
        return OSI_FILE_PARAM_FAIL;

    if (outlen < (strlen(zone_str) + strlen(path)))
        return OSI_FILE_OUTBUF_FAIL;

    strcpy(out, zone_str);
    strcat(out, path);
    return OSI_FILE_OK;
}


SSV_FILE osi_fsopen_path(const char* path, uint8_t zone, uint32_t flags, uint32_t mode, uint8_t type)
{
    SSV_FILE fd = 0;
    char tmp_path[PATH_MAX] = {0};

    memset(tmp_path, 0, PATH_MAX);
    if (osi_fs_getpath(path, zone, tmp_path, PATH_MAX) != OSI_FILE_OK)
        return NULL;

    if (OSI_FILE_WRITE == type)
        FS_remove(fs_handle, tmp_path);

    fd = FS_open(fs_handle, tmp_path, flags, 0);
    if (fd == NULL)
    {
        BT_WARN("FS_open error %s\n", tmp_path);
        return NULL;
    }

    return fd;
}

uint32_t osi_cal_fs_crc(uint8_t *data, size_t data_len)
{
    uint32_t crc = 0;
    int i = 0;

    for (i = 0; i < data_len; i++)
        crc += data[i];

    return crc;
}

int32_t osi_fsopen_fswrite(const char *key,void*data, size_t data_len, uint32_t crc, uint8_t zone)
{/* return > 0, success, others fail*/
    int rltdata = -1, rltcrc = 0;
    SSV_FILE fd = 0;

    fd = osi_fsopen_path(key, zone, SSV_O_CREAT | SSV_O_TRUNC | SSV_O_RDWR, 0, OSI_FILE_WRITE);
    if (fd != NULL)
    {
        rltdata = FS_write(fs_handle, fd, (void*)data, data_len);
        if( rltdata  < 0 )
            BT_ERR("write key %s error\n", key);

        rltcrc = FS_write(fs_handle, fd, (void*)&crc, sizeof(crc));
        if( rltcrc  < 0 )
            BT_ERR("write key %s crc error\n", key);

        rltdata = 0;
        FS_close(fs_handle, fd);
    } else
        FS_close(fs_handle, fd);

    if (rltdata & rltcrc)
        return -1;
    else
        return 1;

}

#define CRC_LEN sizeof(uint32_t)
int32_t osi_fsopen_fsread(const char *key,void *buf, size_t buf_len, uint8_t zone, uint32_t *crcresult)
{
    SSV_FILE fd = 0;
    uint32_t crc = 0, filecrc = 0;
    int32_t read_len = 0;
    int rlt = 0;
    uint8_t *bufp = buf;
    uint8_t tempbuf[512] = {0};
    int32_t retlen = 0;
    //uint64_t time0 = 0, time1 = 0;

    if (buf_len > 512) {
        printf("%s buf_len %d > 512 !!!!\n", __func__, buf_len);
        return 0;
    }
    memset(tempbuf, 0, sizeof(tempbuf));
    //time0 = ssv_timer_get_time();
    fd = osi_fsopen_path(key, zone, SSV_O_RDWR, 0, OSI_FILE_READ);
    if (fd != NULL)
    {
        read_len = FS_read(fs_handle, fd, tempbuf, sizeof(tempbuf));
        if (read_len <= CRC_LEN || (buf_len < (read_len - CRC_LEN)))
        {
            rlt = FS_ferrno(fd);
            FS_close(fs_handle, fd);
            return 0;
        }

        crc = osi_cal_fs_crc(tempbuf, (read_len - CRC_LEN));

        //filecrc = (uint32_t)tempbuf[read_len - CRC_LEN];
        memcpy(&filecrc, (void*)&tempbuf[read_len - CRC_LEN], CRC_LEN);
        if (filecrc == crc) {
            retlen = read_len - CRC_LEN;
        }
        else
            retlen = -1;

        FS_close(fs_handle, fd);
        //memcpy(&filecrc, &bufp[read_len - CRC_LEN], CRC_LEN);
    }/* else
        FS_close(fs_handle, fd);*/

    //time1 = ssv_timer_get_time();
    //printf("load %s time %llu", key, time1 - time0);
    if (retlen > 0) {
        memcpy(bufp, tempbuf, retlen);
        *crcresult = crc;
        return retlen;
    }
    else
        return -1;

}

int32_t osi_fswrite(const char *key,void *data, size_t data_len)
{/* return > 0 success, others fail*/
    int32_t len = 0;
    uint32_t crc = 0;


    crc = osi_cal_fs_crc(data, data_len);
    printf("~w:%s\n", key);
    /*remove first in osi_fsopen_path*/
    len = osi_fsopen_fswrite(key, data, data_len, crc, OSI_FILE_ZONE_A);
#if(UART_IO_NUM == 0)
    REG32(0xc0000c00) = 'A';
    REG32(0xc0000c00) = '-';
#elif(UART_IO_NUM == 1)
    REG32(0xc0000d00) = 'A';
    REG32(0xc0000d00) = '-';
#endif
    len = osi_fsopen_fswrite(key, data, data_len, crc, OSI_FILE_ZONE_B);
#if(UART_IO_NUM == 0)
    REG32(0xc0000c00) = 'B';
    REG32(0xc0000c00) = 0xA;
    REG32(0xc0000c00) = 0xD;
#elif(UART_IO_NUM == 1)
    REG32(0xc0000d00) = 'B';
    REG32(0xc0000d00) = 0xA;
    REG32(0xc0000d00) = 0xD;
#endif

    return len;
}

int osi_fsread(const char *key,u8_t *buf, size_t buf_len)
{
    int32_t len = 0;
    uint32_t crc;
    u8 tmpbuf[512];
    int32_t tmplen;

    len = osi_fsopen_fsread(key, buf, buf_len, OSI_FILE_ZONE_A, &crc);
    if (len <= 0)
    {
        len = osi_fsopen_fsread(key, buf, buf_len, OSI_FILE_ZONE_B, &crc);
        if(len > 0)
        {
            osi_fsopen_fswrite(key, buf, len, crc, OSI_FILE_ZONE_A);
        }
    }
    else
    {
        tmplen = osi_fsopen_fsread(key, tmpbuf, 512, OSI_FILE_ZONE_B, &crc);
        if(tmplen <= 0)
        {
            osi_fsopen_fswrite(key, buf, len, crc, OSI_FILE_ZONE_B);
        }
    }

    return len;
}

size_t osi_fsget_length(const char* path)
{
    int  len = 0;
    SSV_FILE fd = 0;
    uint8_t tempbuf[512] = {0};

    memcpy(tempbuf, 0, sizeof(tempbuf));
    len = osi_fsread(path,tempbuf, sizeof(tempbuf));
    if (len > 0)
        return len;
    else
        return 0;
}
#endif//#if CONFIG_BLE_MESH_SETTINGS