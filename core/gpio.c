#include "core/core.h"

/* gpio pin range */
#define GPMIN	2
#define GPMAX	27

/*
 * validates a gpio pin
 * used when performing operations on gpio pins
 * used as a sanity check
*/
int gvalid(int pin) {
	return pin>=GPMIN && pin<=GPMAX;
}

/*
 * sets a gpio pin
 * turns the pin on
 * ensures pin exists
 */
int gset(int pin) {
	if(!gvalid(pin))
		panic("invalid gpio pin");
	putl(GPSET+4 * (pin/32), 1 << (pin%32));
}

/*
 * clears a gpio pin
 * turns the pin off
 * ensures pin exists
*/
int gclr(int pin) {
	if(!gvalid(pin))
		panic("invalid gpio pin");
	putl(GPCLR+4 * (pin/32), 1 << (pin%32))
}
