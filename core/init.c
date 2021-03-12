#include "core/core.h"

/*
 * default init process
 * if you don't know what you're doing
 * it's a good idea to call this in the beginning
 * sets up serial (needed for printing), irqs, and memory manageement
 */
int rinit() {
	cli();
	sinit();
	minit();
	iinit();
	sti();
}
