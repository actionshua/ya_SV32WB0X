
/*
 * 
 * Author: Tim Li
 *
 */

#include <stdio.h>
#include <string.h>
#include "soc_types.h"
#include "fota_util.h"

static int atoi_base(const char *s, unsigned int base)
{
    unsigned int  index, upbound=base-1;
    unsigned int  value = 0, v;
    while( (v = (unsigned)*s) != 0 )
    {
        index = v - '0';
        if ( index > 10 && base==16 )
        {
            index = (v >= 'a') ? (v - 'a') : (v - 'A');
            index += 10;
        }
        if ( index > upbound )
            break;
        value = value * base + index;
        s++;
    }
    return value;
}

void const_string_to_integer(char *a, unsigned char max,unsigned char *value)
{
    const char  *ptr = a;
    unsigned char loop = 0;
    int integer = 0;
    unsigned char valid_byte = 0;
    char one_byte[3];
    if(!a || !value)
    {
        log_e(PRINT_FOTA_TAG, "# input param is NULL!\n");
        return;
    }
    memset(value, 0x00, max);
    while((loop < strlen(a)) && (valid_byte < max))
    {
        //has one byte or not
        strncpy(one_byte, ptr+loop ,2);
        one_byte[2] = '\0';
        loop += 2;
        integer = atoi_base(one_byte, 16);
        value[valid_byte++]=(unsigned char)integer;
    }
}

