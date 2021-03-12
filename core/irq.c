#include "core/core.h"

/* sizes */
#define NIRQ		32	/* amount of interrupt numbers */

/* pic register offsets */
#define PICSTAT		0x81
#define PICIENABL	0x84

/*
 * programmable interrupt controller
 * memory mapped array of integers
 */
static int *pic = 0x200B000

/*
 * interrupt vector
 * just a table of interrupt handlers
 * refenced by dispatcher
 */
static int (*ivec[NIRQ])()

/*
 * registers an interrupt handler
 * just adds it as an entry in the vector
 * to be called by the dispatcher
*/
int iset(int line, int (*func)()) {
	ienable(line);
	ivec[line] = func;
}

/*
 * dispatches interrupts
 * called when an interrupt occurs
 * finds the correct line to jab
 */
int ihandle() {
	int i, *pe = 0;
	int (*fn)();

	iget(pe);
	for (i = 0; i < NIRQ; i++) {
		if (pe[i] != 0) {
			fn = ivec[i];
			if (fn != NULL)
				fn();
		}
	}
}

/*
 * enables an interrupt line
 * this allows interrupts to be called in that line
 * and then be dispatched
*/
int ienable(int line) {
	pic[PICIENABL] = (1 << line);
}

/*
 * gets a list of pending interrupts
 * and puts them into a buffer
 */
int iget(int *buf) {
	int i = 0;
	uint st = pic[PICSTAT];

	memset(buf, 0, NIRQ * sizeof(int));
	for (i = 0; i < NIRQ; i++) {
		if ((st&(1u<<i)) != NULL)
			buf[i] = 1;
	}
}
