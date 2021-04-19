#include "ya_common.h"
#include "ya_log_update.h"
#include "ya_config.h"
#include "cJSON.h"
#include "ya_flash.h"

#if (LOG_UPLOAD_ENABLE == 1)

#define YA_LOG_LEN		(256 + 64)
uint8_t ya_log_data[YA_LOG_LEN+16];
uint16_t cur_log_len = 0;


#define YA_FLASH_LOG_LEN	(256 + 64)
uint8_t ya_sys_error_log[YA_FLASH_LOG_LEN+16];
uint16_t cur_sys_error_len = 0;

SemaphoreHandle_t log_msgs_handle = NULL;

void ya_updata_log_string(char *log_string)
{
	char time_stamp[32];
	memset(time_stamp, 0, 32);
	snprintf(time_stamp, 32, "%lu-", ya_hal_os_ticks_to_msec());

	xSemaphoreTake(log_msgs_handle, portMAX_DELAY);

	if (cur_log_len + strlen(time_stamp) + strlen(log_string) + 2 > YA_LOG_LEN)
		goto out;

	memcpy(ya_log_data + cur_log_len, time_stamp, strlen(time_stamp));
	cur_log_len += strlen(time_stamp);


	memcpy(ya_log_data + cur_log_len, log_string, strlen(log_string));
	cur_log_len += strlen(log_string);

	memcpy(ya_log_data + cur_log_len, "::", 2);
	cur_log_len += 2;

	out:
	xSemaphoreGive(log_msgs_handle);
}

void ya_save_flash_log_string(char *log_string)
{
	char time_stamp[32];
	memset(time_stamp, 0, 32);
	snprintf(time_stamp, 32, "%lu-", ya_hal_os_ticks_to_msec());

	xSemaphoreTake(log_msgs_handle, portMAX_DELAY);

	if (cur_sys_error_len + strlen(time_stamp) + strlen(log_string) + 2 > YA_FLASH_LOG_LEN)
		goto out;

	memcpy(ya_sys_error_log + cur_sys_error_len, time_stamp, strlen(time_stamp));
	cur_sys_error_len += strlen(time_stamp);

	memcpy(ya_sys_error_log + cur_sys_error_len, log_string, strlen(log_string));
	cur_sys_error_len += strlen(log_string);

	memcpy(ya_sys_error_log + cur_sys_error_len, "::", 2);
	cur_sys_error_len += 2;

	ya_write_flash(YA_FLASH_ERROR_LOG, ya_sys_error_log, cur_sys_error_len, 1, FLASH_AES_DISABLE);

	out:
	xSemaphoreGive(log_msgs_handle);
}

void ya_read_flash_log_string(void)
{
	int32_t ret = -1;
	memset(ya_sys_error_log, 0, YA_FLASH_LOG_LEN + 16);
	cur_sys_error_len = YA_FLASH_LOG_LEN;
	ret = ya_read_flash_with_var_len(YA_FLASH_ERROR_LOG, ya_sys_error_log, &cur_sys_error_len, 1, FLASH_AES_DISABLE);
	if (ret != 0)
	{
		memset(ya_sys_error_log, 0, YA_FLASH_LOG_LEN + 16);
		cur_sys_error_len = 0;
	}
}

void ya_updata_log_string_value(char *event_string, int event_data)
{
	char time_stamp[32];
	char event_data_string[32];
	
	memset(time_stamp, 0, 32);
	snprintf(time_stamp, 32, "%lu-", ya_hal_os_ticks_to_msec());

	memset(event_data_string, 0, 32);
	snprintf(event_data_string, 32, "%d::", event_data);
	
	xSemaphoreTake(log_msgs_handle, portMAX_DELAY);

	if (cur_log_len + strlen(time_stamp) + strlen(event_string) + strlen(event_data_string) > YA_LOG_LEN)
		goto out;

	memcpy(ya_log_data + cur_log_len, time_stamp, strlen(time_stamp));
	cur_log_len += strlen(time_stamp);

	memcpy(ya_log_data + cur_log_len, event_string, strlen(event_string));
	cur_log_len += strlen(event_string);

	memcpy(ya_log_data + cur_log_len, event_data_string, strlen(event_data_string));
	cur_log_len += strlen(event_data_string);

	out:
	xSemaphoreGive(log_msgs_handle);
}


void ya_update_log(void)
{
	cJSON *cmd = NULL;
	char *data = NULL;

	if(cur_log_len == 0)
		return;

	cmd = cJSON_CreateObject();
	if(!cmd)
		return;

	cJSON_AddStringToObject(cmd, "method", "thing.log.raw.report");

	xSemaphoreTake(log_msgs_handle, portMAX_DELAY);
	ya_log_data[cur_log_len] = '\0';
	cJSON_AddStringToObject(cmd, "property", (char *)ya_log_data);
	xSemaphoreGive(log_msgs_handle);

	data = cJSON_PrintUnformatted(cmd); 

	if(data)
	{
		cloud_report_msg((uint8_t *)data, strlen(data));
		ya_hal_os_memory_free(data);
	}

	if(cmd)
		cJSON_Delete(cmd);

	xSemaphoreTake(log_msgs_handle, portMAX_DELAY);
	memset(ya_log_data, 0, YA_LOG_LEN);
	cur_log_len = 0;
	xSemaphoreGive(log_msgs_handle);
}

void ya_update_flash_log(void)
{
	cJSON *cmd = NULL;
	char *data = NULL;

	if(cur_sys_error_len == 0)
		return;

	cmd = cJSON_CreateObject();
	if(!cmd)
		return;

	cJSON_AddStringToObject(cmd, "method", "thing.log.raw.report");

	xSemaphoreTake(log_msgs_handle, portMAX_DELAY);
	ya_sys_error_log[cur_sys_error_len] = '\0';
	cJSON_AddStringToObject(cmd, "property", (char *)ya_sys_error_log);
	xSemaphoreGive(log_msgs_handle);

	data = cJSON_PrintUnformatted(cmd); 

	if(data)
	{
		cloud_report_msg((uint8_t *)data, strlen(data));
		ya_hal_os_memory_free(data);
	}

	if(cmd)
		cJSON_Delete(cmd);

	xSemaphoreTake(log_msgs_handle, portMAX_DELAY);
	memset(ya_sys_error_log, 0, YA_FLASH_LOG_LEN);
	cur_sys_error_len = 0;
	ya_hal_flash_erase(YA_FLASH_ERROR_LOG, 0x1000);
	xSemaphoreGive(log_msgs_handle);
}




void ya_update_log_init(void)
{
	memset(ya_log_data, 0, YA_LOG_LEN);
	cur_log_len = 0;
	ya_read_flash_log_string();
	log_msgs_handle = xSemaphoreCreateMutex();
}

#else

void ya_updata_log_string(char *log_string)
{


}

void ya_save_flash_log_string(char *log_string)
{

}

void ya_updata_log_string_value(char *event_string, int event_data)
{


}

void ya_update_log(void)
{


}

void ya_update_flash_log(void)
{


}

void ya_update_log_init(void)
{


}
#endif


