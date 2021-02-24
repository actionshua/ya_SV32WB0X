
/*
 * 
 * Author: Tim Li
 *
 */
#include <stdio.h>
#include <string.h>
#include "osal.h"
#include "fota_api.h"
#include "fota_process.h"

static ota_param_st *ota_param = NULL;

OTA_RET_TYPE ota_stop(void)
{
    OTA_RET_TYPE ret = O_SUCCESS;
    if(ota_param == NULL) 
    {
        return OT_ERROR;
    }
    ret = ota_process_stop();
    return ret;
}

OTA_RET_TYPE ota_update(void)
{
    OTA_RET_TYPE ret = O_SUCCESS;
    if(ota_param == NULL) 
    {
        return OT_ERROR;
    }
    ret = ota_process_run(ota_param);
    return ret;
}

OTA_RET_TYPE ota_set_server(OTA_PROTOCOL_TYPE nProtocol, char *pIP, unsigned short port)
{
    if(nProtocol > RAW)
    {
        log_e(PRINT_FOTA_TAG, "Error [%d] %s protocol: %d\n", __LINE__, __func__, nProtocol);
        return OA_ERROR;
    }
    if(ota_param == NULL) 
    {
        ota_param = (ota_param_st *)OS_MemAlloc(sizeof(ota_param_st)) ;
        if(ota_param == NULL) 
        {
            log_e(PRINT_FOTA_TAG, "Error [%d] %s\n", __LINE__, __func__);
            return OA_ERROR;
        }
        memset(ota_param, 0x0, sizeof(ota_param_st));
    }
    ota_param->download_protocol = nProtocol;
    ota_param->server_port = port;
    memset(ota_param->server_name , 0, MAX_PATH);
    memcpy(ota_param->server_name, pIP, strlen((char *)pIP));
    log_i(PRINT_FOTA_TAG, "\nota_set_server ip:%s, port:%d\n", ota_param->server_name, ota_param->server_port);
    return O_SUCCESS;
}

OTA_RET_TYPE ota_set_parameter(char* filename, char* filepath)
{
    if(ota_param == NULL)
    {
        log_e(PRINT_FOTA_TAG, "Error [%d] %s\n", __LINE__, __func__);
        return OP_ERROR;
    }
    if(filename == NULL ||(strlen((char *)filename) >= MAX_PATH))
    {
        log_e(PRINT_FOTA_TAG, "Error [%d] %s\n", __LINE__, __func__);
        return OP_ERROR;
    }
    memset(ota_param->bin_filename, 0, MAX_PATH);
    memset(ota_param->bin_filepath, 0, MAX_PATH);
    memcpy(ota_param->bin_filename, filename, strlen((char *)filename));
    if(filepath != NULL && (strlen((char *)filepath) < MAX_PATH && strlen((char *)filepath) > 0)) 
    {
        if( *filepath == '/')
            memcpy(ota_param->bin_filepath, filepath+1, strlen((char *)filepath)-1);
        else
            memcpy(ota_param->bin_filepath, filepath, strlen((char *)filepath));

        if(ota_param->bin_filepath[strlen((char *)ota_param->bin_filepath)-1] != '/' ) 
        {
            ota_param->bin_filepath[strlen((char *)ota_param->bin_filepath)] = '/';
        }	
    }
    log_i(PRINT_FOTA_TAG, "\nfilename:%s\n", ota_param->bin_filename);
    log_i(PRINT_FOTA_TAG, "filenpath:%s\n", ota_param->bin_filepath);
    return O_SUCCESS;
}

OTA_RET_TYPE ota_register_progress_callback(void (*ota_progress_cbfn)(int))
{
    if(ota_param == NULL)
    {
        log_e(PRINT_FOTA_TAG, "Error [%d] %s\n", __LINE__, __func__);
        return OP_ERROR;
    }
    ota_param->ota_progress_ptr = ota_progress_cbfn;
    return O_SUCCESS;
}

OTA_RET_TYPE ota_register_status_callback(void (*ota_status_cbfn)(OTA_STATUS))
{
    if(ota_param == NULL)
    {
        log_e(PRINT_FOTA_TAG, "Error [%d] %s\n", __LINE__, __func__);
        return OP_ERROR;
    }
    ota_param->ota_status_ptr = ota_status_cbfn;
    return O_SUCCESS;
}

OTA_RET_TYPE ota_register_state_callback(void (*ota_state_cbfn)(OTA_STATE_TYPE))
{
    if(ota_param == NULL)
    {
        log_e(PRINT_FOTA_TAG, "Error [%d] %s\n", __LINE__, __func__);
        return OP_ERROR;
    }
    ota_param->ota_state_ptr = ota_state_cbfn;
    return O_SUCCESS;
}

OTA_RET_TYPE ota_reboot(void)
{
    OTA_RET_TYPE ret = O_SUCCESS;
    ret = process_reboot();
    return ret;
}
