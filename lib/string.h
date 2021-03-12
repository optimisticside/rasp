#ifndef STRING_H
#define STRING_H

int memset(void *addr, char val, int n);
int memcpy(void *dst, const void *src, int n);
int memmove(void *dst, const void *src, int n);

char *strcpy(char *dst, const char *src);
char *strncpy(char *dst, const char *src, int n);
int strlen(const char *str);

#endif /* STRING_H */
