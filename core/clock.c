#include "mmio.h"
#include "core/core.h"

/*
 * keeps track of current interrupt interval
 * used when flushing clock data
 */
static uint cint = 0;

/*
 * sets clock interrupt frequency
 * measured in microseconds
 */
int cset(int us) {
	cint = us;
	cclear();
}

/*
 * clears clock interrupts
 * used when changing frequency
 */
int cclear() {
	uint f;

	putl(CS, 2);
	f = mminl(CL0);
	f += cint;
	putl(C1, f);
}
