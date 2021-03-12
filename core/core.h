#ifndef LIB_H
#define LIB_H

#include "def.h"
#include "regs.h"

int rinit();	/* default init process */

int putchar(int ch);		/* prints a character to console */
int printf(char *fmt, ...);	/* formats and prints a message */
int panic(char *msg);		/* initiates a kernel panic (prints and hangs) */

int sinit();		/* enables serial communication */
int slsr();		/* checks serial line status register (used internally) */
int sread();		/* reads a char from serial */
int swrite(int ch);	/* writes a char to serial */

int slock(int *lk);	/* acquires a spinlock */
int srele(int *lk);	/* releases a spinlock */
int stry(int *lk);	/* trys to acquire a spinlock */

char *malloc(int size);			/* allocates n bytes of memory */
int free(char *ptr);			/* frees memory */
char *realloc(char *ptr, int size);	/* reallocates a block of memory */

int gchk(int pin);	/* gets the value of a pin */
int gset(int pin);	/* sets a pin to 1 */
int gclr(int pin);	/* sets a pin to 0 */

int pause();	/* pauses the cpu for some time */
int halt();	/* halts cpu until next interrupt */
int cli();	/* clears interrupt flag (disables interrupts) */
int sti();	/* sets interrupt flag (enables interrupts) */

int ihandle();				/* dispatches interrupts (main handler) */
int ienable(int line);			/* enables interrupts at a specific line */
int iset(int line, int (*func)());	/* registers an interrupt handler */
int iget(int *buf);			/* gets pending interrupts */

int delay(int ticks);	/* sleeps for some ticks */
int sleep(int ms);	/* sleeps for some ms (clock interrupts need to be set up) */
int cset(int us);	/* sets clock interrupt interval (in microseconds) */
int chandle();		/* called upon clock interrupt (does housecleaning) */

struct memarea;	/* memory area */
struct memhead;	/* memory block header */

#endif /* LIB_H */
