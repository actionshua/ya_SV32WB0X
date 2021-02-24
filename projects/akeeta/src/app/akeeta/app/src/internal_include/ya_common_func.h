
#ifndef _YA_COMMOM_FUNC_H_
#define _YA_COMMOM_FUNC_H_

extern uint16_t crc16(uint8_t *addr, int num, uint16_t crc);

extern void HexArrayToString(uint8_t *hexarray, uint16_t length, char *string);

extern int StringToHexArray(uint8_t *hexarray,uint16_t length, char *string);

extern char *ya_int_to_string(uint32_t value);

#endif

