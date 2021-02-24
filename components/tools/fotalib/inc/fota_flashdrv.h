#ifndef _OTA_FLASHDRV_H
#define _OTA_FLASHDRV_H

void ota_flashdrv_write(unsigned int dst_addr, unsigned char* buf, unsigned int buflen);
void ota_flashdrv_erase(unsigned int offset, unsigned int len);
int ota_flashdrv_get_uid(unsigned char* unique, unsigned int id_len);

#endif
