#ifndef DEF_H
#define DEF_H

#include <stdarg.h>
#include <stddef.h>

typedef unsigned char		uchar;
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;

/*
 * memory barrier
 * used to prevent compile from messing stuff up
 */
#define barrier		asm volatile ("" ::: "memory")

#endif /* DEF_H */
