
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "soc_types.h"
#include "soc_defs.h"
#include "osal.h"

#include "logger.h"

uint8_t g_TagLevel[LOG_TAG_MAX] = 
{
    LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL,
    LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL,
    LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL,
    LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL,
    LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL,
    LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL,
    LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL,
    LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL, LOG_DEFAULG_TAG_LEVEL
};

#if 1

int get_tag_level(log_tag_t tag, log_level_t* level)
{
    if( tag >= LOG_TAG_MAX )
        return -1;
        
    *level =  g_TagLevel[tag];
    return 0;
}
int set_tag_level(log_tag_t tag, log_level_t level)
{
    if( tag >= LOG_TAG_MAX )
        return -1;
        
    g_TagLevel[tag] = level;
    return 0;
}

int show_tag_level_list()
{
    return 0;
}

int clean_tag_level_list()
{
    return 0;
}

#else
typedef struct log_tag_entry
{
    struct log_tag_entry* next;
    uint8_t tag_level;
    char  tag_name[0];
} log_tag_entry_t;

static log_tag_entry_t* tag_list = NULL;


int get_tag_level(const char* tag, log_level_t* level)
{
    log_tag_entry_t *entry = NULL;

    LL_FOREACH(tag_list, entry)
    {
        if(strcmp(entry->tag_name, tag) == 0)
        {
            *level = entry->tag_level;
            return 0;
        }
    }
    
    return -1;    
}
int set_tag_level(const char* tag, log_level_t level)
{
    
    log_tag_entry_t *entry = NULL;
    
    LL_FOREACH(tag_list, entry)
    {
        if(strcmp(entry->tag_name, tag) == 0)
        {
            entry->tag_level = level;
            break;
        }
    }    

    if( entry == NULL )
    {
        char dummy[0];
        int entry_size = sizeof(log_tag_entry_t) + strlen(tag) + 1;
        //printf("total_size = %d, entry size = %d, point of entry size = %d, dummy = %d\n", entry_size, sizeof(struct log_tag_entry), sizeof(entry), sizeof(dummy));
        log_tag_entry_t *new_entry = OS_MemAlloc(entry_size);
        new_entry->tag_level = level;
        strcpy(new_entry->tag_name, tag);
        LL_APPEND(tag_list, new_entry);
    }

    return 0;
}

int show_tag_level_list()
{
    log_tag_entry_t *entry = NULL;
    
    LL_FOREACH(tag_list, entry)
    {
        printf("TAG name : %s Level is %d\n", entry->tag_name, entry->tag_level);
    }    
    
    return 0;
}

int clean_tag_level_list()
{
    return 0;
}
#endif

uint32_t log_timestamp()
{
    return OS_GetSysTick();
}

