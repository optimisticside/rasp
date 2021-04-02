#ifndef MMIO_H
#define MMIO_H

#include "def.h"

/*
 * reads a byte from memory mapped io
 * reads 8 bits
 */
static inline uchar getb(char *reg)
{
	return *((volatile uchar *)reg);
}


/*
 * reads a word from memory mapped io
 * reads 16 bits
 */
static inline ushort getw(char *reg)
{
	return *((volatile ushort *)reg);
}

/*
 * reads a long from memory mapped io
 * reads 32 bits
 */
static inline uint getl(char *reg)
{
	return *((volatile uint *)reg);
}

/*
 * reads a quadword from memory mapped io
 * reads 64 bits
 */
static inline ulong getq(char *reg)
{
	return *((volatile ulong *)reg);
}

/*
 * writes a byte to memory mapped io
 * writes 8 bits
 */
static inline int putb(char *reg, uchar val)
{
	*((volatile uchar *)reg) = val;
}

/*
 * writes a word to memory mapped io
 * writes 16 bits
 */
static inline int putw(char *reg, ushort val)
{
	*((volatile ushort *)reg) = val;
}

/*
 * writes a long to memory mapped io
 * writes 32 bits
 */
static inline int putl(char *reg, uint val)
{
	*((volatile uint *)reg) = val;
}

/*
 * writes a quadword to memory mapped io
 * writes 64 bits
 */
static inline int putq(char *reg, ulong val)
{
	*((volatile ulong *)reg) = val;
}

#endif /* MMIO_H */
