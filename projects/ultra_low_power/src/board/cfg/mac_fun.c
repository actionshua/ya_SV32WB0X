#include <stdio.h>
#include <stdint.h>
#include <SSV_cJSON.h>
#include <string.h>
#include "flash.h"
struct wifi_cfg {
    char mac_string[4096];
};

#define M_MAC_ADDR_SIZE      (36)

extern const struct wifi_cfg g_wifi_cfg __attribute__((section(".cfg_mac_data")));

const static char sg_basic_mac[] = {
    0x7b, 0x22, 0x61, 0x64, 0x64, 0x72, 0x31, 0x22, 0x3a, 0x22, 0x34, 0x34,
    0x3a, 0x35, 0x37, 0x3a, 0x31, 0x38, 0x3a, 0x33, 0x66, 0x3a, 0x37, 0x39,
    0x3a, 0x41, 0x31, 0x22, 0x2c, 0x22, 0x61, 0x64, 0x64, 0x72, 0x32, 0x22,
    0x3a, 0x22, 0x34, 0x34, 0x3a, 0x35, 0x37, 0x3a, 0x31, 0x38, 0x3a, 0x33,
    0x66, 0x3a, 0x37, 0x39, 0x3a, 0x41, 0x32, 0x22, 0x7d, 0x0a, 0x00
};

SSV_cJSON *wifi_cfg_init() {
    return SSV_cJSON_Parse(g_wifi_cfg.mac_string);
}

void macstring_parser(char *macstr, char *addr)
{
    u8 len = strlen(macstr);
    u8 i, index = 0;

    if(len > 17)
    {
        goto err;
    }

    addr[index] = 0;
    for(i = 0; i < len; i++)
    {
        if(index > 5)
            goto  err;
        
        if('0' <= macstr[i] && macstr[i] <= '9')
        {
            addr[index] = (addr[index] << 4) + macstr[i] - '0';
        }
        else if('a' <= macstr[i] && macstr[i] <= 'f')
        {
            addr[index] = (addr[index] << 4) + macstr[i] - 'a' + 10;
        }
        else if('A' <= macstr[i] && macstr[i] <= 'F')
        {
            addr[index] = (addr[index] << 4) + macstr[i] - 'A' + 10;
        }
        else if(macstr[i] == ':')
        {
            index++;
            addr[index] = 0;
        }
        else
        {
            goto err;
        }
        
    
}

    return;

err:
    printf("Illegal mac string : %s\n", macstr);
}

void wifi_cfg_get_addr1(const SSV_cJSON *handle, char addr[6]) {
    char *tmpchar = SSV_cJSON_GetObjectItem(handle, "addr1")->valuestring;
    macstring_parser(tmpchar, addr);
//    printf("addr1:%s\n", tmpchar);
}

void wifi_cfg_get_addr2(const SSV_cJSON *handle, char addr[6]) {
    char *tmpchar = SSV_cJSON_GetObjectItem(handle, "addr2")->valuestring;
    macstring_parser(tmpchar, addr);
//    printf("addr2:%s\n", tmpchar);
}

void wifi_cfg_replace_mem_addr1(SSV_cJSON *handle, char *str) {
    SSV_cJSON_ReplaceItemInObject(handle, "addr1", SSV_cJSON_CreateString(str));
}

void wifi_cfg_replace_mem_addr2(SSV_cJSON *handle, char *str) {
    SSV_cJSON_ReplaceItemInObject(handle, "addr2", SSV_cJSON_CreateString(str));
}

void wifi_cfg_write_cfg(struct SSV_cJSON *handle) {
	OS_DeclareCritical();
    char *buf = (char *)sg_basic_mac;
    if (handle != NULL) {
        buf = SSV_cJSON_Print(handle);
    }
    printf("%s\n", buf);
    flash_init();
    uint32_t ptr = (uint32_t)((uint32_t)(&g_wifi_cfg) & (0xFFFFFF));
    OS_EnterCritical();
    flash_sector_erase((unsigned int)ptr);
    int i;
    
    for (i = 0; i < FLASH_SECTOR_SIZE; i+=FLASH_PAGE_SIZE) {
        flash_page_program(ptr+i, FLASH_PAGE_SIZE, (unsigned char *)&(buf[i]));
    }
    OS_ExitCritical();
    if (handle != NULL) {
        SSV_cJSON_free(buf);
    }
}

void wifi_cfg_deinit(SSV_cJSON *handle) {
    SSV_cJSON_Delete(handle);
}

