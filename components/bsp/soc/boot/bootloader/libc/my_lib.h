#ifndef _MY_LIB_H
#define _MY_LIB_H

int my_memcmp(const void *dest, const void *src, unsigned int n);
void* my_memcpy(void *dest, const void *src, unsigned int n);
void* my_memset(void *s, int c, unsigned int n);
char* my_strcpy(char *dest, const void *src);
char* my_strncpy(char *dest, const void *src, unsigned int n);
int my_strcmp(const char *s1, const char *s2);
int my_strncmp(const char *s1, const char *s2, unsigned int n);
unsigned int my_strlen(const char *s);

#endif
