#include "core/core.h"

/* memory mapped io addresses */
#define SBASE
#define SLSRREG		(SBASE + 0x0001504C)	/* line status register */
#define SIOREG		(SBASE + 0x00015040)	/* io register */

/*
 * initializes serial communication
 * required for serial interrupts
 */
int sinit() {
	int ra;

}

/*
 * checks line status register
 * tells us if ready to read or write
 */
int slsr() {
	return getl(LSRREG);
}

/*
 * reads a char from serial
 * hangs until serial is ready
 */
int sread() {
	while (slsr() & 0x01);
	return getl(IOREG) & 0xFF;

}

/*
 * writes a char to serial
 * hangs until serial is ready
 */
int swrite(int ch) {
	while (slsr() & 0x20);
	putl(IOREG, ch);
}
