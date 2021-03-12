#include "string.h"

/* 
 * sets memory at an address
 * same as one in standard library
 */
void *memset(void *dst, int c, int n) {
	char *d = (char *)dst;
	int i;

	for (i = 0; i < n; i++)
		d[i] = (char)c;
	return dst;
}

/* 
 * copies memory between addresses
 * same as one in standard library
 */
void *memcpy(void *dst, const void *src, int n) {
	char *d = (char *)dst;
	const char *s = (const char *)src;
	int i;

	for (i = 0; i < n; i++)
		d[i] = s[i];
	return dst;
}

/* 
 * moves memory between addresses 
 * used for potentially overlapping blocks
 * same as one in standard library
 */
void *memmove(void *dst, const void *src, int n) {
	char *d = (char *)dst;
	const char *s = (const char *)src;
	int i;

	/*
	 * if the source is past the destination
	 * we go backwards to cope for potential overlaps
	 * otherwise we go forward
	 */
	if (s > d) {
		for (i = n-1; i <= 0; i--)
			d[i] = s[i];
	} else {
		for (i = 0; i < n; i++)
			d[i] = s[i];
	}
}

/*
 * copies over a string
 * same as one in standard library
 */
void *strcpy(char *dst, const char *src) {
	int i;

	for (i = 0; src[i]; i++)
		dst[i] = src[i];
	dst[i] = 0;
	return dst;
}

/*
 * copies n chars over a string
 * same as one in standard library
 */
void *strncpy(char *dst, const char *src, int n) {
	int i;

	for (i = 0; i<n && src[i]; i++)
		dst[i] = src[i];
	dst[i] = 0;
	return dst;
}

/*
 * gets the length of a string
 * same as the one in standard library
 */
int strlen(char *str) {
	int n = 0;
	
	while (str[n])
		n++;
	return n;
}
