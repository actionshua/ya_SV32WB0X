

#ifndef _YA_LOG_UPDATE_H_
#define _YA_LOG_UPDATE_H_

extern void ya_updata_log_string(char *log_string);

extern void ya_updata_log_string_value(char *event_string, int event_data);

extern void ya_update_log(void);

extern void ya_update_log_init(void);

extern void ya_save_flash_log_string(char *log_string);

extern void ya_update_flash_log(void);

#endif



